-- Signals system rewritten from JS to Lua

__postEmitEventsStack = {}

signalEmitReturnValue = nil -- TODO: proper throw system

function _connect (self, name, callback)
	-- check if callback really is function
	if type(callback) ~= 'function' then
		error("When connecting signal must give a callback that is a function")
	end

	-- check if we already initiated the array
	if not self._signalConnections then
		self._signalConnections = {}
		self._nextConnectionId = 1
	end

	local id = self._nextConnectionId
	self._nextConnectionId = self._nextConnectionId + 1

	table.insert(self._signalConnections, { id = id, name = name, callback = callback, disconnected = false })

	return id
end

function _disconnect (self, id)
	if self._signalConncetions then
		local i
		local length = table.maxn(self._signalConnections)
		for i = 1,length do
			local connection = self._signalConnections[i]
			if connection.id == id then
				if connection.disconnected then
					error("Signal handler id " .. id .. " already disconnected")
				end
				self._signalConnections[i].disconnected = true
				table.remove(self._signalConnections, i)
				return nil
			end
		end
	end
	error("No signal connection " .. id .. " found")
end

function _disconnectAll (self)
	if self._signalConncetions then
		while table.maxn(self._signalConnections.length) > 0 do
			_disconnect(self, self._signalConnections[0].id)
		end
	end
end

function _emit (self, name, ...)
	if not self._signalConnections then return nil end

	local args = {...}
	local handlers = {}
	local length = table.maxn(self._signalConnections)

	for i = 1, length do
		local connection = self._signalConnections[i]
		if connection.name == name then table.insert(handlers, connection) end
	end

	local arg_array = {}
	length = table.maxn(args)
	for i = 1, length do
		table.insert(arg_array, args[i])
	end

	table.insert(__postEmitEventsStack, {})

	length = table.maxn(handlers)
	for i = 1, length do
		local connection = handlers[i]
		if not connection.disconnected then
			local ret = connection.callback(self, unpack(args))
			if ret == true then break end
		end
	end

	local events = __postEmitEventsStack[table.maxn(__postEmitEventsStack)]
	table.remove(__postEmitEventsStack)
	length = table.maxn(events)
	while length > 0 do
		table.insert(__postEmitEventsStack, {})
		for i = 1, table.maxn(events) do
			events[i](self)
		end
		events = __postEmitEventsStack[table.maxn(__postEmitEventsStack)]
		table.remove(__postEmitEventsStack)
		length = table.maxn(events)
	end

end

function addSignalMethods (self)
	self.connect = _connect
	self.disconnect = _disconnect
	self.emit = _emit
	self.disconnectAll = _disconnectAll
end

function addPostEmitEvent (event)
	table.insert(__postEmitEventsStack[table.maxn(__postEmitEventsStack)], event)
end
