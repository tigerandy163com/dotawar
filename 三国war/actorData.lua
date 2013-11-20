actor_a1 = {blood = 100,speed = 50,damage = 120,money = 10,range =5}
actor_a2 = {blood = 200,speed = 50 ,damage = 100 ,money = 20,range =100}
actor_a3 = {blood = 200,speed = 150 ,damage = 180 ,money = 20,range =5}
actor_a4 = {blood = 2000,speed = 50 ,damage = 40 ,money = 20,range =5}

actor_b1 = {blood = 1000,speed = 50,damage = 10,money = 10,range =5}
actor_b2 = {blood = 2000,speed = 50 ,damage = 30 ,money = 20,range =100}
actor_b3 = {blood = 200,speed = 150 ,damage = 40 ,money = 20,range =5}
actor_b4 = {blood = 1000,speed = 50 ,damage = 20 ,money = 20,range =5}

hero1 = {blood = 1000,speed = 80 ,damage = 150 ,money = 100,range =5}
hero2 = {blood = 1000,speed = 150 ,damage = 100 ,money = 100,range =5}
require "actor"
actor = {}

function main(ActorData,actorID)
print(actorID)
local obj  = actor:new(ActorData,actorID)
obj:actorData()
--actorBase_ = actorBase:new(obj)
--gameLayer:addChild(actorBase_)
end

function actor:new(game1,actorID1)
    local object = {
    game = game1,
    actorID = actorID1,
    speed = 0,
    blood = 0,
    damage = 0,
    money = 0,
    range = 0
    }
    setmetatable(object,{__index = actor})
    return object
end
function  actor:setData(data)
    self.speed = data.speed
    self.blood = data.blood
    self.damage = data.damage
    self.money = data.money
    self.range = data.range
end

function actor:actorData()
    if self.actorID == "A1" then
     self:setData(actor_a1)
     end
     if self.actorID == "A2" then
     self:setData(actor_a2)
     end
     if self.actorID == "A3" then
     self:setData(actor_a3)
     end
     if self.actorID == "A4" then
     self:setData(actor_a4)
     end
      if self.actorID == "B1" then
     self:setData(actor_b1)
     end
     if self.actorID == "B2" then
     self:setData(actor_b2)
     end
      if self.actorID == "B3" then
     self:setData(actor_b3)
     end
      if self.actorID == "B4" then
     self:setData(actor_b4)
     end
    if self.actorID == "Hero02" then
    self:setData(hero2)
    end
    if self.actorID == "Hero11" then
    self:setData(hero1)
    end
 --   print(self.actorID)
    self.game:actorData(self.speed,self.blood,self.damage,self.money,self.range)

    end



