local grammar = require "grammar"

local fname = arg[1]

if fname then
	local file, error = io.open(fname)
	if file then
		src = file:read("*all")
		ast = grammar:compile():match(src)
		for _, block in ipairs(ast) do
			if block.funcdef then
				print ("name: "..block.name)
				print ("args: "..table.concat(block.args, " "))
				print ("rets: "..table.concat(block.rets, " "))
				print()
			end
		end
	else
		error(error)
	end
else
	print("no source file specified")
	os.exit(1)
end