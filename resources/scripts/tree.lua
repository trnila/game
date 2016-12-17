local currentDeadTime = 0.0

function tick(dt)
    if node:getScale().x > maxScale then
        node:rotate(90, 0, 0, 1)

        currentDeadTime = currentDeadTime + dt;

        if currentDeadTime > deadTime then
            node:rotate(0, 0, 0, 1);
            node:setScale(0.001, 0.001, 0.001);
            currentDeadTime = 0;
        end
    else
        node:multiplyScale(growSpeed, growSpeed, growSpeed);
    end
end