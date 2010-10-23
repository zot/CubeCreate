function modelAttachment (tag, _name)
	assert(string.find(tag, ","))
	assert(string.find(_name, ","))

	return tag .. "," .. _name
end
