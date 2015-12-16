local function reverseBinary(num)
	local binary = {}
	local shouldInsert = false
	for i = 16, 0, -1 do
		if num / 2^i >= 1 then
			table.insert(binary, 1)
			shouldInsert = true
			num = num % 2^i
		elseif shouldInsert then
			table.insert(binary, 0)
		end
	end
	print(table.concat())
end

reverseBinary(14)