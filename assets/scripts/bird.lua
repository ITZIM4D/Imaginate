function update(self)
    if KeyIsDown(KEYBOARD.W) and self.position.y < 1 then
        self.position.y = self.position.y + 0.01;
    end
    if KeyIsDown(KEYBOARD.A) and self.position.x > -1.5 then
        self.position.x = self.position.x - 0.01;
    end
    if KeyIsDown(KEYBOARD.S) and self.position.y > -1 then
        self.position.y = self.position.y - 0.01;
    end
    if KeyIsDown(KEYBOARD.D) and self.position.x < 1.5 then
        self.position.x = self.position.x + 0.01
    end 
end
