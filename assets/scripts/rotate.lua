function on_update(x, y, z, dt)
    local speed = 0.5
    return x + dt * speed, y, z
end
