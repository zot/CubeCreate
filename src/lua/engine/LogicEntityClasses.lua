_logicEntityClasses = {}

function registerEntityClass (_class, sauerType)
	local _className = tostring(_class)
	log(DEBUG, string.format("Registering LE class: %s", _className))

	if not sauerType then
		loopBases(
			_class,
			function (parentClass)
				local parentClassName = tostring(parentClass)
				log(DEBUG, string.format("Finding sauertype in ancestor %s", parentClassName))
				sauerType = getEntitySauerType(parentClassName)
			end,
			function (parentClass)
				return sauerType ~= nil or tostring(parentClass) == "LogicEntity"
			end
		)
	end

	if not sauerType then sauerType = "" end

	assert(not _logicEntityClasses[_className])
	_logicEntityClasses[_className] = {_class, sauerType}

	local stateVariableNames = {}

	local inst = _class()
	local _names = table.keys(inst)
	for i = 1, table.maxn(_names) do
		local variable = inst[ _names[i] ]
		log(INFO, string.format("Considering %s -- %s", _names[i], type(variable)))
		if isVariable(variable) then
			log(INFO, string.format("Setting up %s", _names[i]))
			table.insert(stateVariableNames, _names[i])
		end
	end

	log(DEBUG, string.format("Generating protocol data for %s", tostring(stateVariableNames)))

	MessageSystem.generateProtocolData(_className, stateVariableNames)

	return _class
end

function getEntityClass (_className)
	if _logicEntityClasses[_className] then
		return _logicEntityClasses[_className][1]
	else
		log(ERROR, "Invalid class: " .. _className)
		error("Invalid class: " .. _className)
	end
end

function getEntitySauerType (_className)
	if _logicEntityClasses[_className] then
		return _logicEntityClasses[_className][2]
	else
		log(ERROR, "Invalid class: " .. _className)
		error("Invalid class: " .. _className)
	end
end

function listEntityClasses ()
	local keys = table.keys(_logicEntityClasses)
	table.sort(keys)

	return table.filterarray(keys,
		function (_class) return getEntityClass(_class)._sauerType ~= "fpsent" end
	)
end
