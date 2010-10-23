StaticEntity = class(AnimatableLogicEntity)

function StaticEntity:__tostring ()
	return "StaticEntity"
end

StaticEntity.shouldAct = false
StaticEntity.useRenderDynamicTest = true
StaticEntity._sauerType = "extent"
StaticEntity._sauerTypeIndex = 0

StaticEntity.position = WrappedCVector3({ cGetter = "CAPI.getExtent0", cSetter = "CAPI.setExtent0" })
StaticEntity.radius = StateFloat()

StaticEntity.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1" })
StaticEntity.attr2 = WrappedCInteger({ cGetter = "CAPI.getAttr2", cSetter = "CAPI.setAttr2" })
StaticEntity.attr3 = WrappedCInteger({ cGetter = "CAPI.getAttr3", cSetter = "CAPI.setAttr3" })
StaticEntity.attr4 = WrappedCInteger({ cGetter = "CAPI.getAttr4", cSetter = "CAPI.setAttr4" })

function StaticEntity:init (uniqueId, kwargs)
	log(DEBUG, "StaticEntity.init")

	kwargs = defaultValue(kwargs, {})
	kwargs._persistent = true

	self.__parent.init(self, uniqueId, kwargs)

	if not kwargs or not kwargs.position then
		self.position = { 511, 512, 513 }
	else
		self.position = { tonumber(kwargs.position.x), tonumber(kwargs.position.y), tonumber(kwargs.position.z) }
	end

	self.radius = 0

	log(DEBUG, "StaticEntity.init complete")
end

function StaticEntity:activate (kwargs)
	kwargs = defaultValue(kwargs, {})

	log(DEBUG, string.format("%i SE: self.__parent.activate() %s", self.uniqueId, encodeJSON(kwargs)))

	self.__parent.activate(self, kwargs)

	if not kwargs._type then
		kwargs._type = self._sauerTypeIndex
	end

	log(DEBUG, "StaticEntity defaults:")

	kwargs.x = defaultValue(self.position.x, 512)
	kwargs.y = defaultValue(self.position.y, 512)
	kwargs.z = defaultValue(self.position.z, 512)
	kwargs.attr1 = defaultValue(self.attr1, 0)
	kwargs.attr2 = defaultValue(self.attr2, 0)
	kwargs.attr3 = defaultValue(self.attr3, 0)
	kwargs.attr4 = defaultValue(self.attr4, 0)

	log(DEBUG, "SE: setupExtent:")

	CAPI.setupExtent(self, kwargs._type, kwargs.x, kwargs.y, kwargs.z, kwargs.attr1, kwargs.attr2, kwargs.attr3, kwargs.attr4)

	log(DEBUG, "SE: Flush:")

	self:_flushQueuedStateVariableChanges()

	log(DEBUG, "Ensuring SD values - deprecate")
	log(DEBUG, string.format("position: %f, %f, %f", self.position.x, self.position.y, self.position.z))
	log(DEBUG, string.format("position class: %s", tostring(self.position)))
	self.position = self.position
	log(DEBUG, string.format("position(2): %f, %f, %f", self.position.x, self.position.y, self.position.z))
	log(DEBUG, "Ensuring SD values (2)")
	self.attr1 = self.attr1
	self.attr2 = self.attr2
	self.attr3 = self.attr3
	self.attr4 = self.attr4
	log(DEBUG, "Ensuring SD values - complete")
end

function StaticEntity:deactivate ()
	CAPI.dismantleExtent(self)
	self.__parent.deactivate(self)
end

function StaticEntity:clientActivate (kwargs)
	if not kwargs._type then
		kwargs._type = self._sauerTypeIndex
		kwargs.x = 512
		kwargs.y = 512
		kwargs.z = 512
		kwargs.attr1 = 0
		kwargs.attr2 = 0
		kwargs.attr3 = 0
		kwargs.attr4 = 0
	end

	CAPI.setupExtent(self, kwargs._type, kwargs.x, kwargs.y, kwargs.z, kwargs.attr1, kwargs.attr2, kwargs.attr3, kwargs.attr4)
	self.__parent.clientActivate(self, kwargs)
end

function StaticEntity:clientDeactivate ()
	CAPI.dismantleExtent(self)
	self.__parent.clientDeactivate(self)
end

function StaticEntity:sendCompleteNotification (clientNumber)
	clientNumber = defaultValue(clientNumber, MessageSystem.ALL_CLIENTS)
	local clientNumbers = sif(clientNumber == MessageSystem.ALL_CLIENTS, getClientNumbers(), { clientNumber })

	log(DEBUG, "StaticE.sendCompleteNotification:")

	for i = 1, table.maxn(clientNumbers) do
		MessageSystem.send( currClientNumber,
							CAPI.ExtentCompleteNotification,
							self.uniqueId,
							tostring(self),
							self:createStateDataDict(clientNumbers[i], { compressed = true }),
							self.position.x, self.position.y, self.position.z,
							self.attr1, self.attr2, self.attr3, self.attr4 )
	end

	log(DEBUG, "StaticE.sendCompleteNotification complete")
end

function StaticEntity:getCenter ()
	local ret = self.position:copy()
	ret.z = ret.z + self.radius
	return ret
end

----------------------------------------------

Light = class(StaticEntity)

function Light:__tostring ()
	return "Light"
end

Light._sauerTypeIndex = 1
Light.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1", guiName = "radius", altName = "radius" })
Light.attr2 = WrappedCInteger({ cGetter = "CAPI.getAttr2", cSetter = "CAPI.setAttr2", guiName = "red", altName = "red" })
Light.attr3 = WrappedCInteger({ cGetter = "CAPI.getAttr3", cSetter = "CAPI.setAttr3", guiName = "green", altName = "green" })
Light.attr4 = WrappedCInteger({ cGetter = "CAPI.getAttr4", cSetter = "CAPI.setAttr4", guiName = "blue", altName = "blue" })

Light.radius = VariableAlias("attr1")
Light.red = VariableAlias("attr2")
Light.green = VariableAlias("attr3")
Light.blue = VariableAlias("attr4")

function Light:init (uniqueId, kwargs)
	self.__parent.init(self, uniqueId, kwargs)

	self.radius = 100
	self.red = 128
	self.green = 128
	self.blue = 128
end

----------------------------------------------

Spotlight = class(StaticEntity)

function Spotlight:__tostring ()
	return "Spotlight"
end

Spotlight._sauerTypeIndex = 7
Spotlight.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1", guiName = "radius", altName = "radius" })
Spotlight.radius = VariableAlias("attr1")

function Spotlight:init (uniqueId, kwargs)
	self.__parent.init(self, uniqueId, kwargs)
	self.radius = 90
end

----------------------------------------------

Envmap = class(StaticEntity)

function Envmap:__tostring ()
	return "Envmap"
end

Envmap._sauerTypeIndex = 4
Envmap.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1", guiName = "radius", altName = "radius" })
Envmap.radius = VariableAlias("attr1")

function Envmap:init (uniqueId, kwargs)
	self.__parent.init(self, uniqueId, kwargs)
	self.radius = 128
end

----------------------------------------------

SoundEffect = class(StaticEntity)

function SoundEffect:__tostring ()
	return "SoundEffect"
end

SoundEffect._sauerTypeIndex = 6

SoundEffect.attr2 = WrappedCInteger({ cGetter = "CAPI.getAttr2", cSetter = "CAPI.setAttr2", guiName = "radius", altName = "radius" })
SoundEffect.attr3 = WrappedCInteger({ cGetter = "CAPI.getAttr3", cSetter = "CAPI.setAttr3", guiName = "size", altName = "size" })
SoundEffect.attr4 = WrappedCInteger({ cGetter = "CAPI.getAttr4", cSetter = "CAPI.setAttr4", guiName = "volume", altName = "volume" })

SoundEffect.soundName = WrappedCString({ cSetter = "CAPI.setSoundName" })

SoundEffect.radius = VariableAlias("attr2")
SoundEffect.size = VariableAlias("attr3")
SoundEffect.volume = VariableAlias("attr4")

function SoundEffect:init (uniqueId, kwargs)
	self.__parent.init(self, uniqueId, kwargs)

	self.attr1 = -1
	self.radius = 100
	self.size = 0
	if not self.volume then self.volume = 100 end
	self.soundName = ""
end

----------------------------------------------

ParticleEffect = class(StaticEntity)

function ParticleEffect:__tostring ()
	return "ParticleEffect"
end

ParticleEffect._sauerTypeIndex = 5

ParticleEffect.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1", guiName = "particle_type", altName = "particle_type" })
ParticleEffect.attr2 = WrappedCInteger({ cGetter = "CAPI.getAttr2", cSetter = "CAPI.setAttr2", guiName = "value1", altName = "value1" })
ParticleEffect.attr3 = WrappedCInteger({ cGetter = "CAPI.getAttr3", cSetter = "CAPI.setAttr3", guiName = "value2", altName = "value2" })
ParticleEffect.attr4 = WrappedCInteger({ cGetter = "CAPI.getAttr4", cSetter = "CAPI.setAttr4", guiName = "value3", altName = "value3" })

ParticleEffect.particleType = VariableAlias("attr1")
ParticleEffect.value1 = VariableAlias("attr2")
ParticleEffect.value2 = VariableAlias("attr3")
ParticleEffect.value3 = VariableAlias("attr4")

function ParticleEffect:init (uniqueId, kwargs)
	self.__parent.init(self, uniqueId, kwargs)

	self.particleType = 0
	self.value1 = 0
	self.value2 = 0
	self.value3 = 0
end

----------------------------------------------

Mapmodel = class(StaticEntity)

function Mapmodel:__tostring ()
	return "Mapmodel"
end

Mapmodel._sauerTypeIndex = 2

Mapmodel.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1", guiName = "yaw", altName = "yaw" })
Mapmodel.yaw = VariableAlias("attr1")

Mapmodel.collisionRadiusWidth = WrappedCInteger({ cGetter = "CAPI.getCollisionRadiusWidth", cSetter = "CAPI.setCollisionRadiusWidth" })
Mapmodel.collisionRadiusHeight = WrappedCInteger({ cGetter = "CAPI.getCollisionRadiusHeight", cSetter = "CAPI.setCollisionRadiusHeight" })

function Mapmodel:init (uniqueId, kwargs)
	log(DEBUG, "Mapmodel.init")

	self.__parent.init(self, uniqueId, kwargs)

	self.attr2 = -1
	self.yaw = 0

	self.collisionRadiusWidth = 0
	self.collisionRadiusHeight = 0

	log(DEBUG, "Mapmodel.init complete")
end

function Mapmodel:clientActivate (kwargs)
	self.__parent.clientActivate (self, kwargs)
	self.defaultAnimation = CMath.bor(ANIM_TRIGGER, ANIM_START)
end

function Mapmodel:onCollision (collider)
end

function Mapmodel:clientOnCollision (collider)
end

function Mapmodel:getCenter ()
	if self.collisionRadiusHeight then
		local ret = self.position:copy()
		ret.z = ret.z + self.collisionRadiusHeight
		return ret
	else
		return self.__parent.getCenter(self)
	end
end

----------------------------------------------

AreaTrigger = class(Mapmodel)

function AreaTrigger:__tostring ()
	return "AreaTrigger"
end

AreaTrigger.scriptToRun = StateString()

function AreaTrigger:init (uniqueId, kwargs)
	self.__parent.init(self, uniqueId, kwargs)

	self.scriptToRun = ""
	self.collisionRadiusWidth = 10
	self.collisionRadiusHeight = 10
	self.modelName = "areatrigger"
end

function AreaTrigger:onCollision (collider)
	if self.scriptToRun then
		loadstring(self.scriptToRun .. "(collider)")()
	end
end

function AreaTrigger:clientOnCollision (collider)
end

----------------------------------------------

ResettableAreaTrigger = class(AreaTrigger)

function ResettableAreaTrigger:__tostring ()
	return "ResettableAreaTrigger"
end

function ResettableAreaTrigger:activate (kwargs)
	self.__parent.activate(self, kwargs)
	self:reset()
end

function ResettableAreaTrigger:clientActivate (kwargs)
	self.__parent.clientActivate(self, kwargs)
	self:reset()
end

function ResettableAreaTrigger:onCollision (collider)
	if self.readyToTrigger then
		self.readyToTrigger = false
		if self.scriptToRun ~= "" then
			self.__parent.onCollision(self, collider)
		else
			self:onTrigger(collider)
		end
	end
end

function ResettableAreaTrigger:clientOnCollision (collider)
	if self.readyToTrigger then
		self.readyToTrigger = false
		if self.scriptToRun ~= "" then
			self.__parent.clientOnCollision(self, collider)
		else
			self:clientOnTrigger(collider)
		end
	end
end

function ResettableAreaTrigger:reset ()
	self.readyToTrigger = true
	if Global.SERVER then
		self:onReset()
	else
		self:clientOnReset()
	end
end

function ResettableAreaTrigger:onReset ()
end

function ResettableAreaTrigger:clientOnReset ()
end

function ResettableAreaTrigger:onTrigger ()
end

function ResettableAreaTrigger:clientOnTrigger ()
end

----------------------------------------------

TrigerredAction = class(Action)

function TrigerredAction:init (_reverse)
	self.__parent.init(self, _reverse)

	self.secondsLeft = 1.0
	if _reverse then
		self.animation = CMath.bor(ANIM_TRIGGER, ANIM_REVERSE)
	else
		self.animation = ANIM_TRIGGER
	end
end

function TrigerredAction:getAnimation ()
	return self.animation
end

function TrigerredAction:getAnimationFrame ()
	return 0
end

----------------------------------------------

WorldMarker = class(StaticEntity)

function WorldMarker:__tostring ()
	return "WorldMarker"
end

WorldMarker.attr1 = WrappedCInteger({ cGetter = "CAPI.getAttr1", cSetter = "CAPI.setAttr1", guiName = "yaw", altName = "yaw" })
WorldMarker.yaw = VariableAlias("attr1")

WorldMarker._sauerTypeIndex = 3

function WorldMarker:placeEntity (entity)
	entity.position = self.position
	entity.yaw = self.yaw
end

----------------------------------------------

registerEntityClass(StaticEntity, "mapmodel")
registerEntityClass(Light, "light")
registerEntityClass(Spotlight, "spotlight")
registerEntityClass(Envmap, "envmap")
registerEntityClass(SoundEffect, "sound")
registerEntityClass(ParticleEffect, "particles")
registerEntityClass(Mapmodel, "mapmodel")
registerEntityClass(AreaTrigger, "mapmodel")
registerEntityClass(ResettableAreaTrigger, "mapmodel")
registerEntityClass(WorldMarker, "playerstart")
