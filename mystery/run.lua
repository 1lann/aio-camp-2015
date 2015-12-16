local input = io.open("primes.txt"):read("*a")

local registers = {
    A = 1,
    B = 0,
    C = 0,
    D = 0,
    F = 0,
    E = 0,
    G = 0,
    H = 0,
    I = 0,
    J = 0,
    K = 0,
    L = 0,
    M = 0,
    N = 0,
    O = 0,
    P = 0,
    Q = 0,
    R = 0,
    S = 0,
    T = 0,
    U = 0,
    V = 0,
    W = 0,
    X = 0,
    Y = 0,
    Z = 0,
}

local alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

local numNodes = 0
local numLines = 0
local instructions = {}

for line in input:gmatch("[^\n]+") do
    numLines = numLines + 1
    if tostring(tonumber(line)) == line then
        if numNodes > 0 then
            error("unexepcted single number on line " .. numLines)
        end
        numNodes = tonumber(line)
    elseif line:match("[A-Z] %+ %-?%d+") then
        local register, gotoSuccess, breakpoint = line:match("([A-Z]) %+ (%-?%d+) ?(b?)")
        gotoSuccess = tonumber(gotoSuccess)
        if gotoSuccess >= numNodes then
           error("goto on line " .. numLines .. " goes beyond the number of nodes") 
        end
        table.insert(instructions, {register = register, operator = "+", gotoSuccess = gotoSuccess, breakpoint = breakpoint})
    elseif line:match("[A-Z] %- %-?%d+ %-?%d+") then
        local register, gotoFail, gotoSuccess, breakpoint = line:match("([A-Z]) %- (%-?%d+) (%-?%d+) ?(b?)")
        gotoSuccess = tonumber(gotoSuccess)
        if gotoSuccess >= numNodes then
           error("goto success on line " .. numLines .. " goes beyond the number of nodes") 
        end
        gotoFail = tonumber(gotoFail)
        if gotoFail >= numNodes then
           error("goto fail on line " .. numLines .. " goes beyond the number of nodes") 
        end
        table.insert(instructions, {register = register, operator = "-", gotoSuccess = gotoSuccess, gotoFail = gotoFail, breakpoint = breakpoint})
    else
        error("invalid syntax on line " .. numLines)
    end
end

if #instructions ~= numNodes then
    print(#instructions)
    error("number of nodes defined at top of input does not match number of inputted nodes") 
end

if numNodes == 0 then
    error("you did not input any nodes") 
end

-- Execute

print("successfully compiled, now executing...")

local currentNode = 0
local numInstructions = 0


local function printResults(message)
    for i = 0, 4 do
        local line = ""
        for j = 1, 5 do
            local register = alphabet:sub(i * 5 + j, i * 5 + j)
            line = line .. register .. " = " .. registers[register] .. "  "
        end
        print(line)
    end

    print("Z" .. " = " .. registers["Z"])
    
    print(numInstructions .. " instructions executed")
    print(message)
end

while currentNode >= 0 and numInstructions < 5000000 do
    numInstructions = numInstructions + 1
    
    local thisInstruction = instructions[currentNode + 1]
    if thisInstruction.operator == "+" then
        registers[thisInstruction.register] = registers[thisInstruction.register] + 1
        if thisInstruction.breakpoint == "b" then
            printResults("breakpoint at node " .. currentNode .. " reached\npress enter to resume execution...")
            io.read()
        end
        currentNode = thisInstruction.gotoSuccess
    else
        if registers[thisInstruction.register] == 0 then
            if thisInstruction.breakpoint == "b" then
                printResults("breakpoint at node " .. currentNode .. " reached (about to goto failure node)\npress enter to resume execution...")
                io.read()
            end
            currentNode = thisInstruction.gotoFail
        else
            registers[thisInstruction.register] = registers[thisInstruction.register] - 1
            if thisInstruction.breakpoint == "b" then
                printResults("breakpoint at node " .. currentNode .. " reached (about to goto success node)\npress enter to resume execution...")
                io.read()
            end
            currentNode = thisInstruction.gotoSuccess
        end
    end
end

if currentNode >= 0 then
    printResults("instruction limit reached, execution terminated at node " .. currentNode)
    return
end

if currentNode < -1 then
    printResults("execution terminated at invalid instruction " .. currentNode)
    return
end

printResults("execution terminated normally")