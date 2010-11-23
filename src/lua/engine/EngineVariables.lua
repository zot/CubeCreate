-------------------------------------------------------------------------------
-- Engine variable system (Lua part). This manages getting/setting of internal
-- variables. There is a C++ representation of this too to minimize stack
-- manipulation, and the two get sync'd together.
-- Remember, the Lua part won't handle persistency (not required)
--
-- Licensed under MIT/X11 (see the COPYING.txt).
--
-- @author q66 (quaker66@gmail.com)
--
-- @copyright 2010 CubeCreate project
-------------------------------------------------------------------------------

-- Class storing actual vars and managing getters/setters for them + storage table.
_VARS = class()
_VARS.storage = {}


function _VARS:reg(var, skipReg)
	if not is_a(var, _VAR) then log(ERROR, "Cannot register variable because wrong class was provided.") return nil end
	if self.storage[var.name] then return nil end -- Do not register registered vars, but do not error either
	self.storage[var.name] = var
	self:__defineGetter(var.name, function (self, var) return var.curv end, var)
	self:__defineSetter(var.name .. "_ns", function (self, var, val)
		if var:isInReach(val) then
			local oval = var.curv
			var.curv = val
			if var.chng and type(var.chng) == "function" then
				var:chng(oval, val)
			end
		end
	end, var)
	self:__defineSetter(var.name, function (self, var, val)
		if var:isInReach(val) then
			local oval = var.curv
			var.curv = val
			if var.chng and type(var.chng) == "function" then
				var:chng(oval, val)
			end
			CAPI.syncVariableFromLua(var.name, tostring(var), val)
		--else
			--CAPI.syncVariableFromLua(var.name, tostring(var), var.curv) -- run the callback anyway, sync with the same value
		end
	end, var)
	if not skipReg then CAPI.registerVariableFromLua(var.name, tostring(var), var.minv, var.curv, var.maxv) end -- in order to simplify things, no need to pass minv, maxv
end

function _VARS:r(vtype, name, ...)
	self:reg(_G[vtype](name, ...))
end

function _VARS:clear()
	self.storage = {} -- simple way to clear the storage, doesn't take care of C++ status (that's done separately)
end

EV = _VARS()

_VAR = class()
function _VAR:__init(name, minv, curv, maxv, onchange, readonly)
	assert(name, "Cannot register variable: name is missing.")
	assert(curv, "Cannot register variable: no value set.")
	self.name = name
	self.minv = minv
	self.maxv = maxv
	self.curv = curv
	self.chng = onchange
	self.read = readonly
end

IVAR = class(_VAR)
function IVAR:__tostring() return "IVAR" end
function IVAR:__init(name, minv, curv, maxv, readonly)
	assert(type(minv) == "number" and type(curv) == "number" and type(maxv) == "number", "Wrong value type provided to IVAR.")
	self[_VAR].__user_init(self, name, minv, curv, maxv, nil, readonly)
end
function IVAR:isInReach(v)
	if self.read then
		log(ERROR, "Variable is read only.")
		return false
	end
	if type(v) ~= "number" then
		log(ERROR, "Wrong value type passed to variable.")
		return false
	end
	if v < self.minv or v > self.maxv then
		log(ERROR, "Variable accepts only values of range " .. self.minv .. " to " .. self.maxv)
		return false
	end
	return true
end

IVARF = class(IVAR)
function IVARF:__tostring() return "IVARF" end
function IVARF:__init(name, minv, curv, maxv, onchange, readonly)
	assert(type(minv) == "number" and type(curv) == "number" and type(maxv) == "number", "Wrong value type provided to IVARF.")
	assert(onchange and type(onchange) == "function", "Wrong type of onchange callback to IVARF.")
	self[_VAR].__user_init(self, name, minv, curv, maxv, onchange, readonly)
end

FVAR = class(IVAR)
function FVAR:__tostring() return "FVAR" end
FVARF = class(IVARF)
function FVARF:__tostring() return "FVARF" end

SVAR = class(_VAR)
function SVAR:__tostring() return "SVAR" end
function SVAR:__init(name, curv)
	assert(type(curv) == "string", "Wrong value type provided to SVAR.")
	self[_VAR].__user_init(self, name, nil, curv, nil, nil)
end
function SVAR:isInReach(v)
	if type(v) ~= "string" then
		log(ERROR, "Wrong value type passed to variable.")
		return false
	end
	return true
end

SVARF = class(SVAR)
function SVARF:__tostring() return "SVARF" end
function SVARF:__init(name, curv, onchange)
	assert(type(curv) == "string", "Wrong value type provided to SVARF.")
	assert(onchange and type(onchange) == "function", "Wrong type of onchange callback to SVARF.")
	self[_VAR].__user_init(self, name, nil, curv, nil, onchange, false)
end

function ivar  (name, ...) EV:r("IVAR",   name, ...) end
function ivarf (name, ...) EV:r("IVARF",  name, ...) end
function fvar  (name, ...) EV:r("FVAR",   name, ...) end
function fvarf (name, ...) EV:r("FVARF",  name, ...) end
function svar  (name, ...) EV:r("SVAR",   name, ...) end
function svarf (name, ...) EV:r("SVARF",  name, ...) end
