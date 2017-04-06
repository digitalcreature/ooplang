local semantics = {}

local function block(node)
	for _, n in ipairs(node) do
		if n.classdef then
			classdef(n)
		elseif n.funcdef then
			funcdef(n)
		end
	end
end

function semantics.eval(tree)
	return block(tree)
end

return semantics