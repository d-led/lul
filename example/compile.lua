local input = io.open("context.lua", "r")
assert(input)
local output = io.open("context.inl","w")
assert(output)

output:write[[
namespace generated {
 std::string Context() {
  return
]]

for line in input:lines() do
	if #line > 0 then
		output:write([[
"]]..line..[[\n"
		]])
	end
end

output:write[[
  ;
 }
}
]]

output:close()
input:close()
