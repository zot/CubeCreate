-- Exceptions handler for lua
-- taken from here http://failboat.me/2010/lua-exception-handling/

local _mtg = {}
local _orig = getmetatable(_G)
function _mtg.__index(self, k)
	return rawget(self,k.."___macro")
end

Exceptions = {}
setmetatable(Exceptions, {__index = function(self,k) return k end})
Exceptions.resolve = function(exception)
	local exceptions = {GenericError = true}
	if not exception then return {} end
	for pat, ks in pairs(__exceptions) do
		if exception:gfind(pat)() then
			for _,k in ipairs(ks) do
				exceptions[k] = true
			end
		end
	end
	return exceptions
end

local getlocals = function(func)
     local n = 1
     local locals = {}
     func = (type(func) == "number") and func + 1 or func
     while true do
          local lname, lvalue = debug.getlocal(func, n)
          if lname == nil then break end
          if lvalue == nil then lvalue = mynil end
          locals[lname] = lvalue
          n = n + 1
     end
     return locals
end

function try(fn, ...)
	real_args = {...}
	if type(fn) == "table" then fn = fn[1] end
	if type(fn) == "string" then fn = loadstring(fn) end
	if type(fn) ~= "function" then return nil end
	local locals = getlocals(2)

	for _,obj in pairs(locals) do rawset(_G,_.."___macro",obj) end
	setmetatable(_G,_mtg)

	local ok = {pcall(function() return fn(unpack(real_args)) end)}

	setmetatable(_G,_orig)
	for k,__ in pairs(locals) do rawset(_G,k.."___macro",nil) end

	local returns = {}
	local exception = nil
	if ok[1] then
		table.remove(ok, 1)
		returns.values = ok
	else
		exception = ok[2]
	end
	returns.except = function(catch, _fn)
		if not catch then return returns.except("GenericError") end
		if type(catch) == "string" and not _fn then return function(fn) return returns.except(catch, fn) end end
		if type(catch) == "table" then _fn = catch[1]; catch = "GenericError" end
		if type(catch) == "function" then _fn = catch end
		if type(_fn) == "table" then _fn = _fn[1] end
		if not (_fn and type(_fn) == "function") then return end
		local exps = Exceptions.resolve(exception)
		setmetatable(exps, {__tostring = function(self)
							local _r = "{";
							for k,_ in pairs(exps) do
								_r = _r .. k .. ", "
							end;
							return _r:sub(0,#_r-2).."}";
						end})
		if exps[catch] or (type(catch) ~= "string" and exception) then
			return _fn(catch, exps, exception)
		elseif exception then
			error(exception)
		else
			return unpack(returns.values)
		end
		if returns.values then
			return unpack(returns.values)
		end
	end
	setmetatable(returns, {__call = function(self) return self.values end})
	return returns
end

--~ Exceptions.TypeError = "TypeError"
--~ Exceptions.TableError = "TableError"
--~ Exceptions.TableArithmeticError = "TableArithmeticError"
--~ Exceptions.NilArithmeticError = "NilArithmeticError"
--~ Exceptions.ArithmeticError = "ArithmeticError"
--~ Exceptions.NilError = "NilError"
--~ Exceptions.ValueError = "ValueError"
--~ Exceptions.ConcatenationError = "ConcatenationError"
--~ Exceptions.NilConcatenationError = "NilConcatenationError"
--~ Exceptions.FunctionError = "FunctionError"
--~ Exceptions.ParameterError = "ParameterError"
--~ Exceptions.GeneratorError = "GeneratorError"
--~ ETC: Replaced by Exceptions.__index accessor

__exceptions = {
	["attempt to concatenate .+"] = {
			Exceptions.ConcatenationError,
		},
	["attempt to perform arithmetic .+"] = {
			Exceptions.ArithmeticError,
	},
	["attempt to call .+"] = {
			Exceptions.FunctionError,
			Exceptions.TypeError,
	},
	["bad argument .+"] = {
			Exceptions.ParameterError,
	},
	["(.+ generator)"] = {
			Exceptions.GeneratorError,
	},
	["(a .+ value)"] = {
			Exceptions.TypeError,
			Exceptions.ValueError,
	},
	["(a function value)"] = {
			Exceptions.FunctionError,
	},
	["(a nil value)"] = {
			Exceptions.NilError,
	},
	["(a table value)"] = {
			Exceptions.TableError,
	},
	["(a number value)"] = {
			Exceptions.NumberError,
			Exceptions.ArithmeticError,
	},
	["(a string value)"] = {
			Exceptions.StringError,
	},
	[".+ local .+"] = {
			Exceptions.LocalError,
	},
	[".+ global .+"] = {
			Exceptions.GlobalError,
	},
	["assertion"] = {
			Exceptions.AssertionError,
			Exceptions.ValueError,
	},
	["no function environment"] = {
			Exceptions.EnvironmentError,
	},
	["attempt to compare .+"] = {
			Exceptions.ComparisonError,
	},

}
