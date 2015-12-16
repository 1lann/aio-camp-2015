local primes = {2,
3,
5,
7,
11,
13,
17,
19,
23,
29,
31,
37,
41,
43,
47,
53,
59,
61,
67,
71,
73,
79,
83,
89,
97,
101,
103,
107,
109,
113,
127,
131,
137,
139,
149,
151,
157,
163,
167,
173,
179,
181,
191,
193,
197,
199,
211,
223,
227,
229}

local f = io.open("primes.txt", "w")

local currentCursor = 2
local numNodes = 1

f:write("642\nA - 1 1\n")

for i = 1, #primes do
	numNodes = numNodes + 1
	f:write("A - " .. #primes + 1 + (primes[#primes] - primes[currentCursor - 1])  .. " " .. currentCursor .. "\n")
	currentCursor = currentCursor + 1
end

for i = 1, primes[#primes] do
	numNodes = numNodes + 1
	if i == primes[#primes] then
		f:write("Z + -1\n")
	else
		f:write("Z + " .. #primes + i + 1 .. "\n")
	end
end

f:close()

print(numNodes)