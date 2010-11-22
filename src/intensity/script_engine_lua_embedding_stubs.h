#define STDREG(name) { #name, __script__##name }

using namespace MessageSystem;

luaL_Reg CAPI[] = {
    // general
    STDREG(currTime),
    // Math extensions
    STDREG(lsh),
    STDREG(rsh),
    STDREG(bor),
    STDREG(band),
    // Entity management
    STDREG(unregisterLogicEntity),
    STDREG(placeInWorld),
    STDREG(setupExtent),
    STDREG(setupCharacter),
    STDREG(setupNonSauer),
    STDREG(dismantleExtent),
    STDREG(dismantleCharacter),
    // Entity attribs
    STDREG(setAnimation),
    STDREG(getStartTime),
    STDREG(setModelName),
    STDREG(setSoundName),
    STDREG(setSoundVolume),
    STDREG(setAttachments_raw),
    STDREG(getAttachmentPosition),
    STDREG(setCanMove),
    // Extents
    STDREG(getAttr1),
    STDREG(getAttr2),
    STDREG(getAttr3),
    STDREG(getAttr4),
    STDREG(setAttr1),
    STDREG(setAttr2),
    STDREG(setAttr3),
    STDREG(setAttr4),
    STDREG(FAST_setAttr1),
    STDREG(FAST_setAttr2),
    STDREG(FAST_setAttr3),
    STDREG(FAST_setAttr4),
    STDREG(getCollisionRadiusWidth),
    STDREG(getCollisionRadiusHeight),
    STDREG(setCollisionRadiusWidth),
    STDREG(setCollisionRadiusHeight),
    STDREG(getExtent0_raw),
    STDREG(setExtent0_raw),
    // Dynents
    STDREG(getMaxSpeed),
    STDREG(getRadius),
    STDREG(getEyeHeight),
    STDREG(getAboveeye),
    STDREG(getYaw),
    STDREG(getPitch),
    STDREG(getMove),
    STDREG(getStrafe),
    STDREG(getYawing),
    STDREG(getPitching),
    STDREG(getJumping),
    STDREG(getBlocked),
    STDREG(getMapDefinedPositionData),
    STDREG(getClientState),
    STDREG(getPhysicalState),
    STDREG(getInWater),
    STDREG(getTimeInAir),
    STDREG(setMaxSpeed),
    STDREG(setRadius),
    STDREG(setEyeHeight),
    STDREG(setAboveeye),
    STDREG(setYaw),
    STDREG(setPitch),
    STDREG(setMove),
    STDREG(setStrafe),
    STDREG(setYawing),
    STDREG(setPitching),
    STDREG(setJumping),
    STDREG(setBlocked),
    STDREG(setMapDefinedPositionData),
    STDREG(setClientState),
    STDREG(setPhysicalState),
    STDREG(setInWater),
    STDREG(setTimeInAir),
    STDREG(getDynent0_raw),
    STDREG(setDynent0_raw),
    STDREG(getDynentVel_raw),
    STDREG(setDynentVel_raw),
    STDREG(getDynentFalling_raw),
    STDREG(setDynentFalling_raw),
    // Geometry utilities
    STDREG(rayLos),
    STDREG(rayPos),
    STDREG(rayFloor),
    // World
    STDREG(isColliding),
    STDREG(setGravity),
    STDREG(getMaterial),
    // Textures
    STDREG(convertPNGtoDDS),
    STDREG(combineImages),
    // sounds
#ifdef CLIENT
    STDREG(playSoundByName),
    STDREG(stopSoundByName),
#endif
    STDREG(music),
    STDREG(preloadSound),
    STDREG(playSound),
    // effects
#ifdef CLIENT
    STDREG(addDecal),
    STDREG(particleSplash),
    STDREG(particleSplashRegular),
    STDREG(particleFireball),
    STDREG(particleExplodeSplash),
    STDREG(particleFlare),
    STDREG(particleFlyingFlare),
    STDREG(particleTrail),
    STDREG(particleFlame),
    STDREG(addDynlight),
    STDREG(spawnDebris),
    STDREG(particleMeter),
    STDREG(particleText),
    STDREG(clientDamageEffect),
    STDREG(showHUDRect),
    STDREG(showHUDImage),
    STDREG(showHUDText),
#endif
    // messages
    STDREG(PersonalServerMessage),
    STDREG(ParticleSplashToClients),
    STDREG(ParticleSplashRegularToClients),
    STDREG(SoundToClientsByName),
    STDREG(StateDataChangeRequest),
    STDREG(UnreliableStateDataChangeRequest),
    STDREG(NotifyNumEntities),
    STDREG(LogicEntityCompleteNotification),
    STDREG(LogicEntityRemoval),
    STDREG(StateDataUpdate),
    STDREG(UnreliableStateDataUpdate),
    STDREG(DoClick),
    STDREG(ExtentCompleteNotification),
    // file access
    STDREG(readFile),
    // mapping
    STDREG(textureReset),
    STDREG(texture),
    STDREG(mapmodelReset),
    STDREG(mapmodel),
    STDREG(autograss),
    STDREG(texLayer),
    STDREG(texAlpha),
    STDREG(texColor),
    STDREG(texScroll),
    STDREG(texFFenv),
    STDREG(materialReset),
    // shaders
	STDREG(shader),
	STDREG(variantShader),
	STDREG(setShader),
	STDREG(altShader),
	STDREG(fastShader),
	STDREG(deferShader),
	STDREG(forceShader),
	STDREG(isShaderDefined),
	STDREG(isShaderNative),
	STDREG(setVertexParam),
	STDREG(setPixelParam),
	STDREG(setUniformParam),
	STDREG(setShaderParam),
	STDREG(defVertexParam),
	STDREG(defPixelParam),
	STDREG(defUniformParam),
	STDREG(addPostFX),
	STDREG(setPostFX),
	STDREG(clearPostFX),
    // models
	STDREG(mdlAlphatest),
	STDREG(mdlAlphablend),
	STDREG(mdlAlphadepth),
	STDREG(mdlBb),
	STDREG(mdlExtendbb),
	STDREG(mdlScale),
	STDREG(mdlSpec),
	STDREG(mdlGlow),
	STDREG(mdlGlare),
	STDREG(mdlAmbient),
	STDREG(mdlCullface),
	STDREG(mdlDepthoffset),
	STDREG(mdlFullbright),
	STDREG(mdlSpin),
	STDREG(mdlEnvmap),
	STDREG(mdlShader),
	STDREG(mdlCollisionsOnlyForTriggering),
	STDREG(mdlTrans),
	STDREG(modelYaw),
	STDREG(modelPitch),
	STDREG(modelShadow),
	STDREG(modelCollide),
	STDREG(modelPerEntityCollisionBoxes),
	STDREG(modelEllipseCollide),
	STDREG(objLoad),
	STDREG(objSkin),
	STDREG(objBumpmap),
	STDREG(objEnvmap),
	STDREG(objSpec),
	STDREG(objPitch),
	STDREG(objAmbient),
	STDREG(objGlow),
	STDREG(objGlare),
	STDREG(objAlphatest),
	STDREG(objAlphablend),
	STDREG(objCullface),
	STDREG(objFullbright),
	STDREG(objShader),
	STDREG(objScroll),
	STDREG(objNoclip),
	STDREG(md5Dir),
	STDREG(md5Load),
	STDREG(md5Tag),
	STDREG(md5Pitch),
	STDREG(md5Adjust),
	STDREG(md5Skin),
	STDREG(md5Spec),
	STDREG(md5Ambient),
	STDREG(md5Glow),
	STDREG(md5Glare),
	STDREG(md5Alphatest),
	STDREG(md5Alphablend),
	STDREG(md5Cullface),
	STDREG(md5Envmap),
	STDREG(md5Bumpmap),
	STDREG(md5Fullbright),
	STDREG(md5Shader),
	STDREG(md5Scroll),
	STDREG(md5Animpart),
	STDREG(md5Anim),
	STDREG(md5Link),
	STDREG(md5Noclip),
	STDREG(iqmDir),
	STDREG(iqmLoad),
	STDREG(iqmTag),
	STDREG(iqmPitch),
	STDREG(iqmAdjust),
	STDREG(iqmSkin),
	STDREG(iqmSpec),
	STDREG(iqmAmbient),
	STDREG(iqmGlow),
	STDREG(iqmGlare),
	STDREG(iqmAlphatest),
	STDREG(iqmAlphablend),
	STDREG(iqmCullface),
	STDREG(iqmEnvmap),
	STDREG(iqmBumpmap),
	STDREG(iqmFullbright),
	STDREG(iqmShader),
	STDREG(iqmScroll),
	STDREG(iqmAnimpart),
	STDREG(iqmAnim),
	STDREG(iqmLink),
	STDREG(iqmNoclip),
	STDREG(smdDir),
	STDREG(smdLoad),
	STDREG(smdTag),
	STDREG(smdPitch),
	STDREG(smdAdjust),
	STDREG(smdSkin),
	STDREG(smdSpec),
	STDREG(smdAmbient),
	STDREG(smdGlow),
	STDREG(smdGlare),
	STDREG(smdAlphatest),
	STDREG(smdAlphablend),
	STDREG(smdCullface),
	STDREG(smdEnvmap),
	STDREG(smdBumpmap),
	STDREG(smdFullbright),
	STDREG(smdShader),
	STDREG(smdScroll),
	STDREG(smdAnimpart),
	STDREG(smdAnim),
	STDREG(smdLink),
	STDREG(smdNoclip),
	STDREG(rdVert),
	STDREG(rdEye),
	STDREG(rdTri),
	STDREG(rdJoint),
	STDREG(rdLimitDist),
	STDREG(rdLimitRot),
	STDREG(rdAnimJoints),
    // Keyboard
    STDREG(isKeyDown),
    STDREG(isKeyUp),
    STDREG(isMouseDown),
    STDREG(isMouseUp),
    // Code
    STDREG(compile),
    // Components
    STDREG(signalComponent),
    // Models
    STDREG(preloadModel),
    STDREG(reloadModel),
#ifdef CLIENT
    // HUD
    STDREG(getTargetPosition),
    STDREG(getTargetEntity),
    // Rendering
    STDREG(renderModel2),
    STDREG(renderModel3),
    // GUI
    STDREG(showMessage),
    STDREG(showInputDialog),
    STDREG(setDefaultThirdpersonMode),
    // Network
    STDREG(connect),
    // Camera
    STDREG(forceCamera),
    STDREG(forcePosition),
    STDREG(forceYaw),
    STDREG(forcePitch),
    STDREG(forceRoll),
    STDREG(forceFov),
    STDREG(resetCamera),
    STDREG(getCamera),
    STDREG(getCameraPosition),
#endif
    // Editing
    STDREG(editing_getWorldSize),
    STDREG(editing_getGridSize),
    STDREG(editing_eraseGeometry),
    STDREG(editing_createCube),
    STDREG(editing_deleteCube),
    STDREG(editing_setCubeTexture),
    STDREG(editing_setCubeMaterial),
    STDREG(editing_pushCubeCorner),
    STDREG(editing_getSelectedEntity),
    STDREG(renderProgress),
    STDREG(getMapversion),
    // Models
    STDREG(modelBoundingBox),
    STDREG(modelCollisionBox),
    STDREG(modelMesh),
    // NPCs/bots
#ifdef SERVER
    STDREG(addNPC),
    STDREG(removeNPC),
#endif
    // data/ stuff and var accessors
    STDREG(keymap),
    STDREG(registerSound),
    STDREG(font),
    STDREG(fontOffset),
    STDREG(fontChar),
    STDREG(keymap),
    STDREG(registerSound),
    STDREG(font),
    STDREG(fontOffset),
    STDREG(fontChar),
    STDREG(getVariable),
    STDREG(setVariable),
    STDREG(syncVariableFromLua),
    STDREG(registerVariableFromLua),
    STDREG(runCS),
    STDREG(runPython),
    // menus
#ifdef CLIENT
	STDREG(newGUI),
	STDREG(GUIButton),
	STDREG(GUIText),
	STDREG(clearGUI),
	STDREG(showGUI),
	STDREG(GUIOnClear),
	STDREG(GUIStayOpen),
	STDREG(GUINoAutoTab),
	STDREG(GUIList),
	STDREG(GUIAlign),
	STDREG(GUITitle),
	STDREG(GUIBar),
	STDREG(GUIStrut),
	STDREG(GUIImage),
	STDREG(GUISlider),
	STDREG(GUIListSlider),
	STDREG(GUINameSlider),
	STDREG(GUIRadio),
	STDREG(GUIBitfield),
	STDREG(GUICheckBox),
	STDREG(GUITab),
	STDREG(GUIField),
	STDREG(GUIKeyfield),
	STDREG(GUIEditor),
	STDREG(GUIColor),
	STDREG(GUITextBox),
#endif
    {0,0}
};
