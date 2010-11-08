-- Logging extras module for CubeCreate's lua.
-- Exports logging as globals so it's not needed to always call Logging.st.

log = Logging.log

INFO = Logging.INFO
DEBUG = Logging.DEBUG
WARNING = Logging.WARNING
ERROR = Logging.ERROR

-- We also do our own asserts

assert_lua = assert
function assert(expression, msg)
	local ret = pcall(assert_lua, expression)
	if not ret then
		if msg then
			log(ERROR, "<<SCRIPT>> Assertion failed: " .. msg)
			assert_lua(expression, msg)
		else
			log(ERROR, "<<SCRIPT>> Assertion failed!")
			assert_lua(expression)
		end
	end
end
