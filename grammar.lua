re = require "re"

g = re.compile([[
   block <- {| {:block::}
      {:indent: s*:} line
      (
         blankline / 
         (=indent !s line) /
         &(=indent s) block
      )*
   |}

   line <- 
		statement (eol / comment)
	
	statement <- s* (
		  classdef
		/ funcdef
		/ [^%nl/]+
	) s*

	classdef <- {| {:classdef::}
		"class" (s* {:name: id :} )?
	|}

	funcdef <- {| {:funcdef::}
		"def" (s* {:name: id :} )? s*
		"(" s* {:args: arglist :} s* ")"
		((s* "->" s* {:rets: retlist :} ) / ({:rets:{| |}:}))
	|}

	arglist <- {| ( id  (s* "," s*  id )* ("," s* {:elips: "..." :} )? )? |}
	retlist <- {| id  / ( "(" s*  id  (s* "," s*  id )* ("," s* {:elips: "..." :} )? s* ")" ) |}

	id <- {[a-zA-Z:.]+}

   s <- (%tab / " ")
   blankline <- s* (%nl / comment)
   comment <- ("//" [^%nl]* eol )
	eol <- %nl / !.
  
]], {tab = "\t"})

local function examine(t, indent)
   indent = indent or ""
   print (indent.."{")
   local oldindent = indent
   indent = indent.."  "
   for _, x in ipairs(t) do
      if type(x) == "string" then
         print(indent..'"'..x..'"')
      elseif type(x) == "table" then
         examine(x, indent)
      end
   end
   print(oldindent.."}")
end

local file, error = io.open("sample/funcs.src")
if file then
   src = file:read("*all")
   print(src) 
   ast = g:match(src)
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