local grammar = require "grammar"
local ast = require "ast"

local fname = arg[1]

if fname then
	local file, error = io.open(fname)
	if file then
		local src = file:read("*all")
		local tree = grammar:compile():match(src)
		ast.print(tree)		
	else
		error(error)
	end
else
	print("no source file specified")
	os.exit(1)
end