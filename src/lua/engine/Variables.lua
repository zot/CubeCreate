function getOnModifyPrefix ()
	if Global.CLIENT then
		return "client_onModify_"
	else
		return "onModify_"
	end
end

Variable = class()
function Variable:__toString ()
	return "Variable"
end

function isVariable (v)
	return is_a(v, Variable)
end

------------------------------------------------

__SV_PREFIX = "__SV_"

function __getVariable (uniqueId, variableName)
	return getEntity(uniqueId)[__SV_PREFIX .. variableName]
end

function __getVariableGuiName (uniqueId, variableName)
	local entity = getEntity(uniqueId)
	local variable = entity[__SV_PREFIX .. variableName]
	if variable.guiName then
		return variable.guiName
	else
		return variableName
	end
end

------------------------------------------------

StateVariable = class(Variable)

function StateVariable:__tostring ()
	return "StateVariable"
end

function isStateVariable (v)
	return (tostring(v) == "StateVariable")
end

function StateVariable:__init (kwargs)
	log(INFO, "StateVariable.create")
	self._name = nil

	if not kwargs then
		kwargs = {}
	end

	self.clientRead = defaultValue(kwargs.clientRead, true)
	self.clientWrite = defaultValue(kwargs.clientWrite, true)
	self.customSynch = defaultValue(kwargs.customSynch, false)
	self.clientSet = defaultValue(kwargs.clientSet, false)
	self.guiName = kwargs.guiName
	self.altName = kwargs.altName
	self.reliable = defaultValue(kwargs.reliable, true)
	self.hasHistory = defaultValue(kwargs.hasHistory, true)
	self.clientPrivate = defaultValue(kwargs.clientPrivate, false)
end

function StateVariable:_register (_name, parent)
	self._name = _name
	parent[__SV_PREFIX .. _name] = self
	parent[_name] = nil

	log(INFO, string.format("Setting up setter/getter for %s", _name))
	assert(self.getter)
	assert(self.setter)
	parent.getters[_name] = self.getter
	parent.setters[_name] = self.setter
	parent.getterself[_name] = self
	parent.setterself[_name] = self
	if self.altName then
		parent[__SV_PREFIX .. self.altName] = self
		parent.getters[self.altName] = self.getter
		parent.setters[self.altName] = self.setter
		parent.getterself[self.altName] = self
		parent.setterself[self.altName] = self
	end
end

function StateVariable:readTests (entity)
	if not (Global.SERVER or self.clientRead) then
		assert(false)
	end
end

function StateVariable:writeTests (entity)
	if entity.deactivated then
		log(ERROR, string.format("Trying to write a field %s of %i,%s", self._name, entity.uniqueId, tostring(entity)))
		assert(false)
	end
	if not (Global.SERVER or self.clientWrite) then
		assert(Global.SERVER or self.clientWrite)
	end
	if not entity.initialized then
		assert(entity.initialized)
	end
end

function StateVariable:getter (variable)
	log(INFO, "getter.readtests: " .. tostring(variable:readTests(self)))
	return self.stateVariableValues[variable._name]
end

function StateVariable:setter (variable, value)
--	log(INFO, "StateVariable::setter")

	variable:writeTests(self)
	self:_setStateDatum(variable._name, value, nil)
end

function StateVariable:validate (value)
	return true
end

function StateVariable:shouldSend (entity, targetClientNumber)
	return (not self.clientPrivate) or (entity.clientNumber == targetClientNumber)
end

------------------------------------------------

-- let's wrap stuff so it takes self argument
-- if no val is present, take self as val
function selftostring (self, val)
	if not val then
		return tostring(self)
	else
		return tostring(val)
	end
end

function selftointeger (self, val)
	if not val then
		return math.round(self)
	else
		return math.round(val)
	end
end

function selftodouble (self, val)
	if not val then
		return tonumber(self)
	else
		return tonumber(val)
	end
end

function selftoboolean (self, val)
	if not val then
		return toboolean(self)
	else
		return toboolean(val)
	end
end

function selftojson (self, val)
	if not val then
		return encodeJSON(self)
	else
		return encodeJSON(val)
	end
end

function selffromjson (self, val)
	if not val then
		return decodeJSON(self)
	else
		return decodeJSON(val)
	end
end

StateInteger = class(StateVariable)
StateInteger.toWire = selftostring
StateInteger.fromWire = selftointeger
StateInteger.toData = selftostring
StateInteger.fromData = selftointeger


function decimal2 (self, x)
	if math.abs(x) < 0.01 then return '0' end
	local ret = tostring(x)
	local spl = string.split(ret, '.')
	if not spl[2] then
		return {ret, "0"}
	else
		return spl
	end
end

StateFloat = class(StateVariable)
StateFloat.toWire = decimal2
StateFloat.fromWire = selftodouble
StateFloat.toData = decimal2
StateFloat.fromData = selftodouble

StateEnum = class(StateInteger)

StateBoolean = class(StateVariable)
StateBoolean.toWire = selftostring
StateBoolean.fromWire = selftoboolean
StateBoolean.toData = selftostring
StateBoolean.fromData = selftoboolean

StateString = class(StateVariable)
StateString.toWire = selftostring
StateString.fromWire = selftostring
StateString.toData = selftostring
StateString.fromData = selftostring

------------------------------------------------

local ArraySurrogate = class()

function ArraySurrogate:__init (entity, variable)
	log(INFO, "Setting up ArraySurrogate")

	self.entity = entity
	self.variable = variable
end

function ArraySurrogate:__tostring ()
	return "ArraySurrogate"
end

function ArraySurrogate:length ()
	return self.variable:getLength(self.entity)
end

function ArraySurrogate:push (value)
	self:set(self:length(), value)
end

function ArraySurrogate:get (index)
	return self.variable:getItem(self.entity, index)
end

function ArraySurrogate:set (index, value)
	self.variable:setItem(self.entity, index, value)
end

function ArraySurrogate:asArray ()
	log(INFO, "asArray: " .. tostring(self))

	local ret = {}
	for i = 1, self:length() do
		log(INFO, string.format("asArray(%i)", i))
		table.insert(ret, self:get(i))
	end

	return ret
end

------------------------------------------------

StateArray = class(StateVariable)
StateArray.separator = "|"
StateArray.surrogateClass = ArraySurrogate

function StateArray:__tostring ()
	return "StateArray"
end

function StateArray:emptyValue ()
	return {}
end

function StateArray:getter (variable)
	log(INFO, "StateArray.getter " .. tostring(variable:readTests(self)))

	if not variable:getRaw(self) then
		return nil
	end

	log(INFO, string.format("StateArray.getter (%s,%s): Creating surrogate", variable._name, tostring(variable)))

	local cacheName = '__arraysurrogate_' .. variable._name
	if not self[cacheName] then
		self[cacheName] = variable.surrogateClass(self, variable)
	end
	return self[cacheName]
end

function StateArray:setter (variable, value)
	log(INFO, "StateArray.setter: " .. encodeJSON(value))
	if value.x then
		log(INFO, string.format("StateArray.setter: %f, %f, %f", value.x, value.y, value.z))
	end
	if value:get(1) then
		log(INFO, string.format("StateArray.setter: %f, %f, %f", value:get(1), value:get(2), value:get(3)))
	end

	local data

	if value.asArray then
		data = value:asArray()
	else
		data = {}
		local val
		if tostring(value) == "ArraySurrogate" then
			for i = 1, value.length() do
				val = value:get(i)
				table.insert(data, val)
			end
		else
			for i = 1, table.maxn(value) do
				val = value[i]
				table.insert(data, val)
			end
		end
	end

	self:_setStateDatum(variable._name, data, nil)
end

StateArray.toWireItem = selftostring

function StateArray:toWire (value)
	log(INFO, "toWire of StateArray: " .. encodeJSON(value))
	if value.asArray then
		value = value:asArray()
	end

	return '{' .. table.concat(table.map(value, self.toWireItem), self.separator) .. '}'
end

StateArray.fromWireItem = selftostring

function StateArray:fromWire (value)
	log(DEBUG, "fromWire of StateArray: " .. encodeJSON(value))

	if value == "{}" then
		return {}
	else
		return string.split(table.map(value, self.fromWireItem), self.separator)
	end
end

StateArray.toDataItem = selftostring

function StateArray:toData (value)
	log(INFO, string.format("(1) StateArray.toData: %s %s %s", tostring(value), type(value), encodeJSON(value)))

	if value.asArray then
		log(INFO, "(1.5) StateArray.toData: using asArray")
		value = value:asArray()
	end

	log(INFO, string.format("(2) StateArray.toData: %s %s %s", tostring(value), type(value), encodeJSON(value)))

	return '{' .. table.concat(table.map(value, self.toDataItem), self.separator) .. '}'
end

StateArray.fromDataItem = selftostring

function StateArray:fromData (value)
	log(DEBUG, string.format("StateArray.fromData %s::%s", self._name, tostring(value)))
	if value == "{}" then
		return {}
	else
		return string.split(table.map(value, self.fromDataItem), self.separator)
	end
end

function StateArray:getRaw (entity)
	log(INFO, "getRaw: " .. tostring(self))
	log(INFO, encodeJSON(entity.stateVariableValues))
	local value = entity.stateVariableValues[self._name]

	if not value then
		value = {}
	end
	return value
end

function StateArray:setItem (entity, i, value)
	log(INFO, string.format("setItem: %i : %s", i, encodeJSON(value)))
	local array = self:getRaw(entity)
	log(INFO, string.format("gotraw: %s", encodeJSON(array)))
	if type(value) == "string" then
		assert(not string.find(value, "|"))
	end
	array[i] = value
	entity:_setStateDatum(self._name, array, nil)
end

function StateArray:getItem (entity, i)
	log(INFO, string.format("StateArray.getItem for %i", i))
	local array = self:getRaw(entity)
	log(INFO, string.format("StateArray.getItem %s ==> %s", encodeJSON(array), tostring(array[i])))
	return array[i]
end

function StateArray:getLength (entity)
	local array = self:getRaw(entity)
	if not array then
		assert(false)
	end
	return table.maxn(array)
end

------------------------------------------------

StateArrayString = class(StateArray)
function StateArrayString:__tostring ()
	return "StateArrayString"
end

StateArrayStringComma = class(StateArrayString)
StateArrayStringComma.separator = ","

------------------------------------------------

StateArrayFloat = class(StateArray)
function StateArrayFloat:__tostring ()
	return "StateArrayFloat"
end

StateArrayFloat.toWireItem = decimal2
StateArrayFloat.fromWireItem = selftodouble
StateArrayFloat.toDataItem = decimal2
StateArrayFloat.fromDataItem = selftodouble

------------------------------------------------

StateArrayInteger = class(StateArray)
function StateArrayInteger:__tostring ()
	return "StateArrayInteger"
end

StateArrayInteger.toWireItem = selftostring
StateArrayInteger.fromWireItem = selftointeger
StateArrayInteger.toDataItem = selftostring
StateArrayInteger.fromDataItem = selftointeger

------------------------------------------------

VariableAlias = class(Variable)

function VariableAlias:__init (targetName)
	self.targetName = targetName
end

function VariableAlias:_register (_name, parent)
	self._name = _name

	parent[_name] = nil
	local target = parent[__SV_PREFIX .. self.targetName]
	parent[__SV_PREFIX .. _name] = target

	parent.getters[_name] = target.getter
	parent.setters[_name] = target.setter
	parent.getterself[_name] = target
	parent.setterself[_name] = target

	assert(not self.altName)
end

------------------------------------------------

WrappedCVariable = {
	__init = function (self, kwargs)
		log(INFO, "WrappedCVariable.create")

		self.cGetterRaw = kwargs.cGetter
		self.cSetterRaw = kwargs.cSetter

		kwargs.cGetter = nil
		kwargs.cSetter = nil

		self[StateVariable].__user_init(self, kwargs)
	end,

	_register = function (self, _name, parent)
		self[StateVariable]._register(self, name, parent)

		self.cGetter = self.cGetterRaw
		self.cSetter = self.cSetterRaw

		if type(self.cGetter) == "string" then
			self.cGetter = loadstring("return " .. self.cGetter)()
		end

		if type(self.cSetter) == "string" then
			self.cSetter = loadstring("return " .. self.cSetter)()
		end

		if self.cSetter then
			local prefix = getOnModifyPrefix()
			parent.connect(prefix .. _name, function (value)
				if Global.CLIENT or parent:canCallCFuncs() then
					log(INFO, string.format("Calling cSetter for %s, with %s (%s)", self._name, tostring(value), type(value)))
					self:cSetter(parent, value)

					parent.stateVariableValues[self._name] = value
					parent.stateVariableValueTimestamps[self._name] = Global.currTimestamp
				else
					parent:_queueStateVariableChange(self._name, value)
				end
			end)
		else
			log(DEBUG, "No cSetter for " .. _name .. "; not connecting to signal")
		end
	end,

	getter = function (self, variable)
		log(INFO, "WCV getter readtests " .. tostring(variable:readTests(self)))

		local cachedTimestamp = self.stateVariableValueTimestamps[variable._name]
		if cachedTimestamp == Global.currTimestamp then
			return self.stateVariableValues[variable._name]
		end

		log(INFO, "WCV getter " .. variable._name)
		if variable.cGetter and (Global.CLIENT or self:canCallCFuncs()) then
			log(INFO, "WCV getter: call C")
			local value = variable:cGetter(self)

			if Global.CLIENT or self._queuedStateVariableChangesComplete then
				self.stateVariableValues[variable._name] = value
				self.stateVariableValueTimestamps[variable._name] = Global.currTimestamp
			end

			return value
		else
			log(INFO, "WCV getter: fallback to stateData since " .. tostring(variable.cGetter))
			return self[StateVariable].getter(self, variable)
		end
	end
}

------------------------------------------------

WrappedCInteger = class(StateInteger)
table.merge(WrappedCInteger, WrappedCVariable)

WrappedCFloat = class(StateFloat)
table.merge(WrappedCFloat, WrappedCVariable)

WrappedCEnum = class(StateEnum)
table.merge(WrappedCEnum, WrappedCVariable)

WrappedCBoolean = class(StateBoolean)
table.merge(WrappedCBoolean, WrappedCVariable)

WrappedCString = class(StateString)
table.merge(WrappedCString, WrappedCVariable)

------------------------------------------------

WrappedCArray = class(StateArray)
table.merge(WrappedCArray, WrappedCVariable)
table.merge(WrappedCArray, {
	__tostring = function (self)
		return "WrappedCArray"
	end,

	getter = StateArray().getter,

	getRaw = function (self, entity)
		log(INFO, "WCA.getRaw " .. self._name .. tostring(self.cGetter))
		if self.cGetter and (Global.CLIENT or entity:canCallCFuncs()) then
			local cachedTimestamp = entity.stateVariableValueTimestamps[self._name]
			if cachedTimestamp == Global.currTimestamp then
				return entity.stateVariableValues[self._name]
			end

			log(INFO, "WCA.getRaw: call C")

			local value = self:cGetter(entity)
			if Global.CLIENT or entity._queuedStateVariableChangesComplete then
				entity.stateVariableValues[self._name] = value
				entity.stateVariableValueTimestamps[self._name] = Global.currTimestamp
			end
			return value
		else
			log(INFO, "WCA.getRaw: fallback to stateData")
			local ret = entity.stateVariableValues[self._name]
			log(INFO, "WCA.getRaw..." .. tostring(ret))
			return ret
		end
	end
})

------------------------------------------------

local Vector3Surrogate = class(ArraySurrogate)
Vector3Surrogate.getters = {
	x = function() return self:get(1) end,
	y = function() return self:get(2) end,
	z = function() return self:get(3) end
}
Vector3Surrogate.setters = {
	x = function(v) self:set(1, v) return true end,
	y = function(v) self:set(2, v) return true end,
	z = function(v) self:set(3, v) return true end
}

function Vector3Surrogate:__init (entity, variable)
	self[ArraySurrogate].__user_init(self, entity, variable)

	self.entity = entity
	self.variable = variable
	
end

function Vector3Surrogate:__tostring ()
	return "Vector3Surrogate"
end

function Vector3Surrogate:__get (i)
	if self.getters[i] then
		return self.getters[i]()
	end

	return nil
end

function Vector3Surrogate:__set (i, v)
	if self.setters[i] then
		return self.setters[i](v)
	end

	return true -- always return true, don't care about what's set
end

function Vector3Surrogate:length ()
	return 3
end

function Vector3Surrogate:push (value)
	assert(false) -- no need for push here
end

------------------------------------------------

Vector3ArrayPlugin = {
	surrogateClass = Vector3Surrogate,

	emptyValue = function (self)
		return {0,0,0}
	end,

	fromDataItem = selftodouble,
	toDataItem = decimal2,

	fromWireItem = selftodouble,
	toWireItem = decimal2
}

WrappedCVector3 = class(WrappedCArray)
table.merge(WrappedCVector3, Vector3ArrayPlugin)

function WrappedCVector3:__tostring ()
	return "WrappedCVector3"
end

StateVector3 = class(StateArray)
table.merge(StateVector3, Vector3ArrayPlugin)

function StateVector3:__tostring ()
	return "StateVector3"
end

------------------------------------------------

Vector4ArrayPlugin = table.copy(Vector3ArrayPlugin)
Vector4ArrayPlugin.surrogateClass = Vector4Surrogate

function Vector4ArrayPlugin.emptyValue ()
	return {0,0,0,0}
end

WrappedCVector4 = class(WrappedCArray)
table.merge(WrappedCVector4, Vector4ArrayPlugin)

function WrappedCVector4:__tostring ()
	return "WrappedCVector4"
end

StateVector4 = class(StateArray)
table.merge(StateVector4, Vector4ArrayPlugin)

function StateVector4:__tostring ()
	return "StateVector4"
end

------------------------------------------------


StateJSON = class(StateVariable)
StateJSON.toWire = selftojson
StateJSON.fromWire = selffromjson
StateJSON.toData = selftojson
StateJSON.fromData = selffromjson

-- TODO: equivalent in lua
--registerJSON("LogicEntity", function(val) { return val.uniqueId !== undefined; }, function(val) { return val.uniqueId; }, true);
