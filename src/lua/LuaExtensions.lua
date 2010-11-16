-------------------------------------------------------------------------------
-- Various functions added to standard table module, used to simplify coding.
-- Licensed under MIT/X11 (see the COPYING.txt).
--
-- @author q66 (quaker66@gmail.com)
--
-- @copyright 2010 CubeCreate project
-------------------------------------------------------------------------------

--- Remaps an array to different type.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local myarr = { 5, 10, 15, 20, 25 } -- here we have an array of numbers<br/>
-- myarr = table.map(mytable, function (x) return tostring(x) end)<br/>
-- -- and now myarr is full of strings<br/>
-- </code>
-- @param tbl The array to re-map.
-- @param func The function accepting the array item and returning converted.
-- @return The re-mapped table. If you want to overwrite the old one, you have to do it explicitly.
function table.map(tbl, func)
	local ret = {}
	for i = 1, #tbl do
		ret[i] = func(tbl[i])
	end
	return ret
end

--- Merges two tables together.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { a = 5, b = 10 }<br/>
-- local b = { c = 15, d = 20 }<br/>
-- table.merge(a, b)<br/>
-- -- table a is now something like { a = 5, b = 10, c = 15, d = 20 }<br/>
-- </code>
-- @param tbl The table to merge the second one into.
-- @param tbl2 The second table to merge into first one.
-- @return The merged table. You don't have to explicitly overwrite the table, it is done automatically.
function table.merge(tbl, tbl2)
	for a, b in pairs(tbl2) do
		tbl[a] = b
	end
	return tbl
end

--- Copies a table.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { a = 5, b = 10 }<br/>
-- local b = table.copy(a)<br/>
-- assert(a.b == b.b)<br/>
-- </code>
-- @param tbl The table to copy.
-- @return A new table, containing contents of provided table.
function table.copy(tbl)
	local ret = {}
	for a, b in pairs(tbl) do
		ret[a] = b
	end
	return ret
end

--- Copies an array.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { 5, 10 }<br/>
-- local b = table.copy(a)<br/>
-- assert(a[2] == b[2])<br/>
-- </code>
-- @param tbl The array to copy.
-- @return A new array, containing contents of provided array.
function table.copyarray(tbl)
	local ret = {}
	for i = 1, #tbl do
		ret[i] = tbl[i]
	end
	return ret
end

--- Filters a table.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { a = 5, b = 10 }<br/>
-- local b = table.filter(a, function (k, v) if v == 5 then return true else return false end end)<br/>
-- -- now b contains only 'a' item<br/>
-- </code>
-- @param tbl The table to filter.
-- @param func The function accepting key and value, returning true if to keep the item, false otherwise.
-- @return A new table, containing filtered contents.
function table.filter(tbl, func)
	local ret = {}
	for a,b in pairs(tbl) do
		if func(a, b) then
			ret[a] = b
		end
	end
	return ret
end

--- Filters an array.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { 5, 10 }<br/>
-- local b = table.filter(a, function (v) if v == 5 then return true else return false end end)<br/>
-- -- now b contains only item of index 1<br/>
-- </code>
-- @param tbl The array to filter.
-- @param func The function accepting value, returning true if to keep the item, false otherwise.
-- @return A new array, containing filtered contents.
function table.filterarray(tbl, func)
	local ret = {}
	local a = 1
	for i = 1, #tbl do
		if func(tbl[i]) then
			ret[a] = tbl[i]
			a = a + 1
		end
	end
	return ret
end

--- Finds a value in the table, returning its key.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { a = 5, b = 10 }<br/>
-- local b = table.find(a, 10)<br/>
-- assert(b == 'b')<br/>
-- </code>
-- @param tbl The table to find item in
-- @param val The value to find.
-- @return A key (string) belonging to the value, or nil.
function table.find(tbl, val)
	for a,b in pairs(tbl) do
		if b == val then
			return a
		end
	end
	return nil
end

--- Finds a value in the array, returning its index.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { 5, 10 }<br/>
-- local b = table.findarray(a, 10)<br/>
-- assert(b == 2)<br/>
-- </code>
-- @param tbl The array to find item in
-- @param val The value to find.
-- @return An index (integer) belonging to the value, or nil.
function table.findarray(tbl, val)
	for i = 1, #tbl do
		if tbl[i] == val then
			return i
		end
	end
	return nil
end

--- Gets an array of table keys.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { a = 5, b = 10, c = 15 }<br/>
-- local b = table.keys(a)<br/>
-- assert(table.concat(b) == 'abc')<br/>
-- </code>
-- @param tbl The table to get keys from.
-- @return An array of keys belonging to table specified as parameter.
function table.keys(tbl)
	local ret = {}
	for a,b in pairs(tbl) do
		table.insert(ret, tostring(a))
	end
	return ret
end

--- Gets an array of table values.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = { a = 5, b = 10, c = 15 }<br/>
-- local b = table.values(a)<br/>
-- assert(table.concat(b) == '51015')<br/>
-- </code>
-- @param tbl The table to get values from.
-- @return An array of values belonging to table specified as parameter.
function table.values(tbl)
	local ret = {}
	for a,b in pairs(tbl) do
		table.insert(ret, b)
	end
	return ret
end

--- Split string into array of tokens. Based on http://lua-users.org/wiki/SplitJoin.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = "abc|def|ghi|jkl"<br/>
-- local b = string.split(a, '|')<br/>
-- assert(table.concat(b) == "abcdefghijkl")<br/>
-- </code>
-- @param str String to split into array of tokens.
-- @param sep Separator to use to split the strings. Defaults to comma.
-- @return An array of string tokens.
function string.split(str, sep)
	sep = defaultValue(sep, ",")
	local ret = {}
	local pat = string.format("([^%s]+)", sep)
	string.gsub(str, pat, function (c) ret[#ret+1] = c end)
	return ret
end

--- Convert number or string to boolean.
-- If the value is not number or string, false is returned.
-- If the value is boolean, it just gets returned.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local a = "true"<br/>
-- local b = "false"<br/>
-- local c = 0<br/>
-- local d = 1<br/>
-- local e = -2<br/>
-- assert(toboolean(a) == true)<br/>
-- assert(toboolean(b) == false)<br/>
-- assert(toboolean(c) == false)<br/>
-- assert(toboolean(d) == true)<br/>
-- assert(toboolean(e) == true)<br/>
-- assert(toboolean(f) == false) -- nil values are false<br/>
-- </code>
-- @param val Value to convert to boolean.
-- @return A converted boolean.
function toboolean(val)
	if type(val) == "string" then
		if val == "true" then return true
		else return false end
	elseif type(val) == "number" then
		if val ~= 0 then return true else return false end
	elseif type(val) == "boolean" then
		return val
	else
		return false
	end
end

--- Convert a function into callable table.
-- If passed argument is not function, nil is returned.
-- If it is a function, then returns a callable table,
-- calling the passed function when called (but unlike
-- function, having an ability to have properties)
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local function a () return 5 end<br/>
-- a = tocalltable(a)<br/>
-- a.x = 10<br/>
-- assert(a() == 5)<br/>
-- assert(a.x == 10)<br/>
-- </code>
-- @param func The function to be called on table call.
-- @return A table with proper metatable (see description)
function tocalltable(func)
	return setmetatable({}, { __call = func })
end

--- Left bitshift surrogate.
-- @param val Integer value to shift to the left.
-- @param num Number of bits to shift val by to the left.
-- @return The shifted value.
-- @class function
-- @name math.lsh
math.lsh = CAPI.lsh

--- Right bitshift surrogate.
-- @param val Integer value to shift to the right.
-- @param num Number of bits to shift val by to the right.
-- @return The shifted value.
-- @class function
-- @name math.rsh
math.rsh = CAPI.rsh

--- Bitwise OR surrogate.
-- @param ... A variable number of arguments to perform bitwise OR on.
-- @return The result of bitwise OR between arguments.
-- @class function
-- @name math.bor
math.bor = CAPI.bor

--- Bitwise AND surrogate.
-- @param ... A variable number of arguments to perform bitwise AND on.
-- @return The result of bitwise AND between arguments.
-- @class function
-- @name math.band
math.band = CAPI.band

--- Round a float number to integer.
-- @param num The float number to round.
-- @return A rounded integer value.
function math.round(num)
	if type(num) ~= "number" then return nil end
	return math.floor(tonumber(num) + 0.5)
end

--- Not table (limitation of luadoc), multiplying this with N radians
-- results in conversion of N to degrees.
-- @class table
-- @name math.RAD
math.RAD = (math.pi / 180.0)

--- Not table (limitation of luadoc), this represents temporary emulation
-- of null value (= variable has been defined, but has no value).
-- TODO: remove this and use only nil and values.
-- @class table
-- @name null
null = { __ccnull = true }

--- Convert a script template into real script.
-- Accepts string as a script template, runs all conditionals etc inside
-- and returns a final script string.
-- Based on luadoc template system, which is licensed under MIT/X11.
-- <br/><br/>Usage:<br/><br/>
-- <code>
-- local x = 5
-- local tmpl = "foobar: <%=x%> <% if x == 5 then return 10 else return 15 end %>"<br/>
-- local scrp = template(tmpl)<br/>
-- echo(scrp)<br/>
-- -- and return value should be:<br/>
-- -- foobar: 5 10<br/>
-- </code>
-- @param s The string specifying the template.
-- @return A translated template.
function template(s)
	s = string.gsub(s, "<%%(.-)%%>", "<?lua %1 ?>")
	local res = {}
	local start = 1   -- start of untranslated part in `s'
	while true do
		local ip, fp, target, exp, code = string.find(s, "<%?(%w*)[ \t]*(=?)(.-)%?>", start)
		if not ip then break end
		table.insert(res, string.sub(s, start, ip-1))
		if exp == "=" then   -- expression?
			table.insert(res, string.format("%s", loadstring("return " .. code)()))
		else  -- command
			local ret = loadstring(code)()
			if ret then table.insert(res, string.format(" %s ", tostring(ret))) end
		end
		start = fp + 1
	end
	table.insert(res, string.sub(s, start, -1))
	return table.concat(res)
end
