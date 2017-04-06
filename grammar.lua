re = require "re"

local grammar = {}

grammar.SRC = "grammar.peg"
function grammar:compile()
	local f = io.open(self.SRC, "r")
	if f then
		local src = f:read("*all")
		return re.compile(src, {tab = "\t"})
	else
		error("could not open grammar file: "..self.SRC)
	end
end

return grammar