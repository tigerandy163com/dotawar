actorBase = {actorData=nil,_sprite}
actorBase.__index = actorBase
function actorBase:new(actorData)
	print(actorData.actorID)
	local object = {}
	setmetatable(object,actorBase)
    object = CCNode:create()
	object.actorData = actorData
    local png = actorData.actorID .."_6.png"
    object._sprite = CCSprite:createWithSpriteFrameName(png)
    object._sprite:retain()
    object:addChild(object._sprite)
    object._sprite:setPosition(100,100)

	return object
end


	