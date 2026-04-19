---@meta

---@class KEYBOARD
KEYBOARD = {}

KEYBOARD.SPACE = 32

---@param keycode integer
---@return boolean
function KeyIsDown(keycode) end

---@class vec3
---@field x number
---@field y number
---@field z number
vec3 = {}

---@param x number?
---@param y number?
---@param z number?
---@return vec3
function vec3(x, y, z) end