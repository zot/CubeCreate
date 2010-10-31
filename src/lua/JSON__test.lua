log(DEBUG, "---- JSON TEST BEGIN ----")

local arr = { 1, 2, 3, "blah", xyz = 15, false, true, { 5, 10, 15, 20 } }

local encoded = encodeJSON(arr)
log(DEBUG, encoded)
assert(type(encoded) == "string")
assert(type(decodeJSON(encoded)["xyz"]) == "number")
assert(type(decodeJSON(encoded)["4"]) == "string")
assert(decodeJSON(encoded)["xyz"] == arr["xyz"])

arr = { 5, 10, 15, 20, 25, 30, 31 }
encoded = encodeJSON(arr)
log(DEBUG, encoded)
assert(type(encoded) == "string")
assert(type(decodeJSON(encoded)[0]) == "nil")
assert(type(decodeJSON(encoded)[1]) == "number")
assert(type(decodeJSON(encoded)[2]) == "number")
assert(type(decodeJSON(encoded)[3]) == "number")
assert(type(decodeJSON(encoded)[4]) == "number")
assert(type(decodeJSON(encoded)[5]) == "number")
assert(type(decodeJSON(encoded)[6]) == "number")
assert(type(decodeJSON(encoded)[7]) == "number")
assert(decodeJSON(encoded)[7] == 31)

log(DEBUG, "---- JSON TEST END ----")
