local ast = {}

function ast.print(node, indent)
	indent = indent or ""
	for k, v in pairs(node) do
		if type(k) ~= "number" then
			print (indent..tostring(k).." = "..tostring(v))
		end
	end
	for _, n in ipairs(node) do
		if type(n) == "table" then
			ast.print(n, indent.."  ")
		else
			print(indent.."* \""..tostring(n).."\"")
		end
	end
	print()
end

return ast