re = require "re"

g = re.compile([[
   block <- {| {:block::}
      {:ident: ichar*:} line
      (
         blankline / 
         (=ident !ichar line) /
         &(=ident ichar) block
      )*
   |}

   line <- {[^%nl/]*} (%nl / comment)
   ichar <- (%tab / " ")
   blankline <- ichar* (%nl / comment)
   comment <- ("//" [^%nl]* %nl )
  
]], {tab = "\t"})

local function examine(t, indent)
   indent = indent or ""
   print (indent.."{")
   local oldindent = indent
   indent = indent.."  "
   print(t.block and true)
   for _, x in ipairs(t) do
      if type(x) == "string" then
         print(indent..'"'..x..'"')
      elseif type(x) == "table" then
         examine(x, indent)
      end
   end
   print(oldindent.."}")
end

local file, error = io.open("sample/vect.src")
if file then
   src = file:read("*all")
   print(src) 
   ast = g:match(src)
   examine(ast)
else
   error(error)
end