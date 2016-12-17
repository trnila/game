local test = require "./resources/scripts/fun"

function factorial(i)
    if i <= 1 then
        return 1
    end
    return factorial(i - 1) * i
end

function bernstein(i, n, t)
    return factorial(n) / (factorial(n - i) * factorial(i)) * math.pow(t, i) * math.pow(1 - t, n - i)
end

function len(t)
    local count = 0
    for k,v in pairs(t) do
        count = count + 1
    end
    return count
end


local elapsed = 0.0
local duration = 10.0

function tick(dt)
    elapsed = elapsed + dt

    if elapsed >= duration then
        elapsed = 0.0
    end

    local t = elapsed / duration

    local x = 0
    local y = 0
    local z = 0
    for i, v in ipairs(points) do
        local B = bernstein(i - 1, len(points) - 1, t);
        x = x + v.x * B;
        y = y + v.y * B;
        z = z + v.z * B;
    end

    node:setPosition(x, y, z)
end