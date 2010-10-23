#include <cmath>

#ifndef WIN32
    #define ISNAN(x) std::isnan(x)
#else
    #define ISNAN(x) _isnan(x)
#endif

#ifdef CLIENT
    #include "client_engine_additions.h"
    #include "intensity_gui.h"
    #include "intensity_texture.h"
#endif

#ifdef SERVER
    #include "NPC.h"
#endif

#include "intensity_physics.h"

// Temporary till cubescript is out of game.
#define CSSUDO(script) \
    { \
        bool old = overrideidents; \
        overrideidents = true; \
        execute(script); \
        overrideidents = old; \
    }

#define RETURN_VECTOR3(sauervec) \
{ \
    LuaEngine::getGlobal("Vector3"); \
    LuaEngine::pushValue(sauervec.x); \
    LuaEngine::pushValue(sauervec.y); \
    LuaEngine::pushValue(sauervec.z); \
    /* after call, the vec is on stack */ \
    LuaEngine::call(3, 1); \
}

// done before everything else, required during initialization.
LUA_EMBED_is(log, 0, {
    Logging::log_noformat(arg1, arg2);
});

// HERE BEGINS CAPI, exports of functions from C++ to Lua.
LUA_EMBED_s(echo, 0, {
    conoutf("\f1%s", arg1.c_str());
});

// General
LUA_EMBED_NOPARAM(currTime, 1, {
    LuaEngine::pushValue(Utility::SystemInfo::currTime());
});

// Math extensions
LUA_EMBED_ii(lsh, 1, {
    LuaEngine::pushValue(arg1 << arg2);
});

LUA_EMBED_ii(rsh, 1, {
    LuaEngine::pushValue(arg1 >> arg2);
});

LUA_EMBED_NOPARAM(bor, 1, {
    int out = 0;
    int n = LuaEngine::gettop();
    for (int i = 1; i <= n; i++) out |= LuaEngine::getInteger(i);
    LuaEngine::pushValue(out);
});

LUA_EMBED_NOPARAM(band, 1, {
    int out = 0;
    int n = LuaEngine::gettop();
    for (int i = 1; i <= n; i++) out &= LuaEngine::getInteger(i);
    LuaEngine::pushValue(out);
});

// Lua extensions
LUA_EMBED_NOPARAM(getFuncName, 1, {
    if (!LuaEngine::getName(1).empty()) LuaEngine::pushValue(LuaEngine::getName(1));
    else LuaEngine::pushValue();
});

// Entity management

//LUA_EMBED_i(registerLogicEntityNonSauer, 0, {
//    LogicSystem::registerLogicEntityNonSauer(arg1);
//}); DEPRECATED

LUA_EMBED_i(unregisterLogicEntity, 0, {
    LogicSystem::unregisterLogicEntityByUniqueId(arg1);
});

LUA_EMBED_ii(placeInWorld, 0, {
    WorldSystem::placeInWorld(arg1, arg2);
});

LUA_EMBED_Z(setupExtent, 0, idddiiii, {
    
    LogicSystem::setupExtent(ref, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
});

LUA_EMBED_Z(setupCharacter, 0, , {
    LogicSystem::setupCharacter(ref);
});

LUA_EMBED_Z(setupNonSauer, 0, , {
    LogicSystem::setupNonSauer(ref);
});

LUA_EMBED_Z(dismantleExtent, 0, , {
    LogicSystem::dismantleExtent(ref);
});

LUA_EMBED_Z(dismantleCharacter, 0, , {
    LogicSystem::dismantleCharacter(ref);
});

// Worldsystem
extern void removeentity(extentity* entity);
extern void addentity(extentity* entity);

// Entity attribs

LUA_EMBED_T(setAnimation, 1, i, {
    self.get()->setAnimation(arg2);
});

LUA_EMBED_T(getStartTime, 0, , {
    LuaEngine::pushValue(self.get()->getStartTime());
});

LUA_EMBED_T(setModelName, 0, s, {
    Logging::log(Logging::DEBUG, "setModelName(%s)\r\n", arg2.c_str());
    self.get()->setModel(arg2);
});

LUA_EMBED_T(setSoundName, 0, s, {
    Logging::log(Logging::DEBUG, "setSoundName(%s)\r\n", arg2.c_str());
    self.get()->setSound(arg2);
});

LUA_EMBED_T(setSoundVolume, 0, i, {
    Logging::log(Logging::DEBUG, "setSoundVolume(%i)\r\n", arg2);
    extentity* e = self.get()->staticEntity;
    assert(e);
    if (!WorldSystem::loadingWorld) removeentity(e);
    e->attr4 = arg2;
    if (!WorldSystem::loadingWorld) addentity(e);
    // finally reload sound, so everything gets applied
    self.get()->setSound(self.get()->soundName.c_str());
});

LUA_EMBED_T(setAttachments_raw, 0, s, { self.get()->setAttachments(arg2); } );

LUA_EMBED_T(getAttachmentPosition, 1, s, {
    vec& vposition = self->getAttachmentPosition(arg2);
    RETURN_VECTOR3(vposition);
});

LUA_EMBED_T(setCanMove, 0, i, {
    self.get()->setCanMove(arg2);
});

// Extents

#define EXTENT_ACCESSORS(getterName, setterName, attribName) \
LUA_EMBED_T(getterName, 1, , { \
    extentity* e = self.get()->staticEntity; \
    assert(e); \
    LuaEngine::pushValue(e->attribName); \
}); \
 \
LUA_EMBED_T(setterName, 0, i, { \
    extentity* e = self.get()->staticEntity; \
    assert(e); \
    if (!WorldSystem::loadingWorld) removeentity(e); /* Need to remove, then add, to the world on each change, if not during load. */ \
    e->attribName = arg2; \
    if (!WorldSystem::loadingWorld) addentity(e); \
}); \
 \
LUA_EMBED_T(FAST_##setterName, 0, i, { /* Fast version - no removeentity/addentity. Use with care! */ \
    extentity* e = self.get()->staticEntity; \
    assert(e); \
    e->attribName = arg2; \
});

EXTENT_ACCESSORS(getAttr1, setAttr1, attr1);
EXTENT_ACCESSORS(getAttr2, setAttr2, attr2);
EXTENT_ACCESSORS(getAttr3, setAttr3, attr3);
EXTENT_ACCESSORS(getAttr4, setAttr4, attr4);

#define EXTENT_LE_ACCESSORS(getterName, setterName, attribName) \
LUA_EMBED_T(getterName, 1, , { \
    LuaEngine::pushValue(self->attribName); \
}); \
 \
LUA_EMBED_T(setterName, 0, d, { \
    Logging::log(Logging::DEBUG, "ACCESSOR: Setting %s to %d\r\n", #setterName, arg2); \
    assert(self->staticEntity); \
    if (!WorldSystem::loadingWorld) removeentity(self->staticEntity); /* Need to remove, then add, to the octa world on each change. */ \
    self->attribName = arg2; \
    if (!WorldSystem::loadingWorld) addentity(self->staticEntity); \
});

EXTENT_LE_ACCESSORS(getCollisionRadiusWidth, setCollisionRadiusWidth, collisionRadiusWidth);
EXTENT_LE_ACCESSORS(getCollisionRadiusHeight, setCollisionRadiusHeight, collisionRadiusHeight);


//Add 'FAST' versions of accessors - no addeneity/removeentity. Good to change e.g. particle parameters


LUA_EMBED_T(getExtentO_raw, 1, i, {
    extentity* e = self.get()->staticEntity;
    assert(e);
    assert(arg2 >= 0 && arg2 <= 2);

    Logging::log(Logging::INFO, "getExtentO_raw(%d): %f\r\n", arg2, e->o[arg2]);

    LuaEngine::pushValue(e->o[arg2]);
});

LUA_EMBED_T(setExtentO_raw, 0, ddd, {
    extentity* e = self.get()->staticEntity;
    assert(e);

    removeentity(e); /* Need to remove, then add, to the octa world on each change. */
    e->o.x = arg2;
    e->o.y = arg3;
    e->o.z = arg4;
    addentity(e);
});


// Dynents

#define DYNENT_ACCESSORS(getterName, setterName, type_code, type_BOLD, attribName) \
LUA_EMBED_T(getterName, 1, , { \
    fpsent* e = (fpsent*)(self.get()->dynamicEntity); \
    assert(e); \
    LuaEngine::pushValue((type_BOLD)e->attribName); \
}); \
 \
LUA_EMBED_T(setterName, 0, type_code, { \
    fpsent* e = dynamic_cast<fpsent*>(self.get()->dynamicEntity); \
    assert(e); \
    e->attribName = arg2; \
});

DYNENT_ACCESSORS(getMaxSpeed, setMaxSpeed, d, double, maxspeed);
DYNENT_ACCESSORS(getRadius, setRadius, d, double, radius);

DYNENT_ACCESSORS(getEyeHeight, setEyeHeight, d, double, eyeheight);
DYNENT_ACCESSORS(getAboveeye, setAboveeye, d, double, aboveeye);
DYNENT_ACCESSORS(getYaw, setYaw, d, double, yaw);
DYNENT_ACCESSORS(getPitch, setPitch, d, double, pitch);
DYNENT_ACCESSORS(getMove, setMove, i, int, move);
DYNENT_ACCESSORS(getStrafe, setStrafe, i, int, strafe);
DYNENT_ACCESSORS(getYawing, setYawing, i, int, turn_move);
DYNENT_ACCESSORS(getPitching, setPitching, i, int, look_updown_move);
DYNENT_ACCESSORS(getJumping, setJumping, b, bool, jumping);
DYNENT_ACCESSORS(getBlocked, setBlocked, b, bool, blocked);
DYNENT_ACCESSORS(getMapDefinedPositionData, setMapDefinedPositionData, i, int, mapDefinedPositionData); // XXX Should be unsigned
DYNENT_ACCESSORS(getClientState, setClientState, i, int, state);
DYNENT_ACCESSORS(getPhysicalState, setPhysicalState, i, int, physstate);
DYNENT_ACCESSORS(getInWater, setInWater, i, int, inwater);
DYNENT_ACCESSORS(getTimeInAir, setTimeInAir, i, int, timeinair);

// For dynents, 'o' is at their head, not their feet like static entities. We make this uniform by
// letting scripting specify a feet position, and we work relative to their height - add to
// assignments, subtract from readings
LUA_EMBED_T(getDynentO_raw, 1, i, {
    fpsent* d = dynamic_cast<fpsent*>(self.get()->dynamicEntity);
    assert(d);
    assert(arg2 >= 0 && arg2 <= 2);

    if (arg2 != 2) {
        LuaEngine::pushValue(d->o[arg2]);
    } else {
        LuaEngine::pushValue(d->o.z - d->eyeheight);// - d->aboveeye);
    }
});

LUA_EMBED_T(setDynentO_raw, 0, ddd, {
    fpsent* d = dynamic_cast<fpsent*>(self.get()->dynamicEntity);
    assert(d);

    d->o.x = arg2;
    d->o.y = arg3;
    d->o.z = arg4 + d->eyeheight;// + d->aboveeye;

    // Also set 'newpos', otherwise this change may get overwritten
    d->newpos = d->o;

    d->resetinterp(); // No need to interpolate to last position - just jump

    Logging::log(Logging::INFO, "(%d).setDynentO(%f, %f, %f)\r\n", d->uniqueId, d->o.x, d->o.y, d->o.z);
});

LUA_EMBED_T(getDynentVel_raw, 1, i, {
    fpsent* d = (fpsent*)(self.get()->dynamicEntity);
    assert(d);
    assert(arg2 >= 0 && arg2 <= 2);

    LuaEngine::pushValue(d->vel[arg2]);
});

LUA_EMBED_T(setDynentVel_raw, 0, ddd, {
    fpsent* d = dynamic_cast<fpsent*>(self.get()->dynamicEntity);
    assert(d);

    d->vel.x = arg2;
    d->vel.y = arg3;
    d->vel.z = arg4;
});

LUA_EMBED_T(getDynentFalling_raw, 1, i, {
    fpsent* d = (fpsent*)(self.get()->dynamicEntity);
    assert(d);
    assert(arg2 >= 0 && arg2 <= 2);

    LuaEngine::pushValue(d->falling[arg2]);
});

LUA_EMBED_T(setDynentFalling_raw, 0, ddd, {
    fpsent* d = dynamic_cast<fpsent*>(self.get()->dynamicEntity);
    assert(d);

    d->falling.x = arg2;
    d->falling.y = arg3;
    d->falling.z = arg4;
});

// Geometry utilities

LUA_EMBED_dddddd(rayLos, 1, {
    vec a(arg1, arg2, arg3);
    vec b(arg4, arg5, arg6);
    vec target;

    bool ret = raycubelos(a, b, target);
    LuaEngine::pushValue(ret);
});

LUA_EMBED_ddddddd(rayPos, 1, {
    vec o(arg1, arg2, arg3);
    vec ray(arg4, arg5, arg6);
    vec hitpos(0);

    LuaEngine::pushValue(raycubepos(o, ray, hitpos, arg7, RAY_CLIPMAT|RAY_POLY));
});

LUA_EMBED_dddd(rayFloor, 1, {
    vec o(arg1, arg2, arg3);
    vec floor(0);
    LuaEngine::pushValue(rayfloor(o, floor, 0, arg4));
});

// World

LUA_EMBED_ddddi(isColliding, 1, {
    vec position(arg1, arg2, arg3);
    LuaEngine::pushValue(PhysicsManager::getEngine()->isColliding(
        position,
        arg4,
        arg5 != -1 ? LogicSystem::getLogicEntity(arg5).get() : NULL)
    ); // TODO: Make faster, avoid this lookup
});

LUA_EMBED_d(setGravity, 0, {
    if (PhysicsManager::hasEngine())
    {
        PhysicsManager::getEngine()->setGravity(arg1);
    } else {
        Logging::log(Logging::DEBUG, "Setting gravity using sauer system, as no physics engine\r\n");
        extern float GRAVITY;
        GRAVITY = arg1;
    }
});

LUA_EMBED_ddd(getMaterial, 1, {
    LuaEngine::pushValue(lookupmaterial(vec(arg1, arg2, arg3)));
});

// Textures

#ifdef CLIENT
LUA_EMBED_ss(convertPNGtoDDS, 0, {
    assert(Utility::validateRelativePath(arg1));
    assert(Utility::validateRelativePath(arg2));
    IntensityTexture::convertPNGtoDDS(arg1, arg2);
});
#else
LUA_EMBED_ss(convertPNGtoDDS, 0, {
    arg1 = arg1; arg2 = arg2; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_sss(combineImages, 0, {
    assert(Utility::validateRelativePath(arg1));
    assert(Utility::validateRelativePath(arg2));
    assert(Utility::validateRelativePath(arg3));
    IntensityTexture::combineImages(arg1, arg2, arg3);
});
#else
LUA_EMBED_sss(combineImages, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

// Sounds

#ifdef CLIENT
    LUA_EMBED_sdddi(playSoundByName, 0, {
        vec loc(arg2, arg3, arg4);
        if (loc.x || loc.y || loc.z)
            playsoundname(arg1.c_str(), &loc, arg5);
        else
            playsoundname(arg1.c_str());
    });

    LUA_EMBED_si(stopSoundByName, 0, {
        stopsoundbyid(getsoundid(arg1.c_str(), arg2));
    });
#endif

#ifdef CLIENT
// TODO:: MUSIC
LUA_EMBED_s(music, 0, {
    assert( Utility::validateAlphaNumeric(arg1, "._/") );
    std::string command = "music \"";
    command += arg1;
    command += "\" [ run_lua \"Sound.musicCallback()\" ]";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(music, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(underwaterAmbient, 0, {
    std::string command = "uwambient ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(underwaterAmbient, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
extern int preload_sound(char *name, int vol);
LUA_EMBED_si(preloadSound, 1, {
    std::string str = "preloading sound '";
    str += arg1;
    str += "'...";
    renderprogress(0, str.c_str());

    arg2 = min(arg2, 100); // Do not let scripts set high volumes for griefing
    LuaEngine::pushValue(preload_sound((char*)arg1.c_str(), arg2));
});
#else
LUA_EMBED_si(preloadSound, 0, {
    arg1 = arg1; arg2 = arg2; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(playSound, 0, {
    playsound(arg1); // TODO: Sound position
});
#else
LUA_EMBED_i(playSound, 0, {
    MessageSystem::send_SoundToClients(
        -1,
        arg1,
        -1
    );
});
#endif

// Effects

#ifdef CLIENT

    LUA_EMBED_idddddddiiii(addDecal, 0, {
        vec  center(arg2, arg3, arg4);
        vec  surface(arg5, arg6, arg7);
        bvec color(arg9, arg10, arg11);

        adddecal(arg1, center, surface, arg8, color, arg12);
    });

    VARP(lblood, 0, 1, 1); // FIXME: remove "l"

    LUA_EMBED_iiidddidiibibi(particleSplash, 0, {
        if (arg1 == PART_BLOOD && !lblood) return 0;
        vec p(arg4, arg5, arg6);
        particle_splash(arg1, arg2, arg3, p, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14);
    });

    LUA_EMBED_iiidddidiiibi(particleSplashRegular, 0, {
        if (arg1 == PART_BLOOD && !lblood) return 0;
        vec p(arg4, arg5, arg6);
        regular_particle_splash(arg1, arg2, arg3, p, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
    });

    LUA_EMBED_ddddiiid(particleFireball, 0, {
        vec dest(arg1, arg2, arg3);
        particle_fireball(dest, arg4, arg5, arg6, arg7, arg8);
    });

    LUA_EMBED_dddiiiiii(particleExplodeSplash, 0, {
        vec o(arg1, arg2, arg3);
        particle_explodesplash(o, arg4, arg5, arg6, arg7, arg8, arg9);
    });

    LUA_EMBED_ddddddiiidii(particleFlare, 0, {
        vec p(arg1, arg2, arg3);
        vec dest(arg4, arg5, arg6);
        if (arg12 < 0)
            particle_flare(p, dest, arg7, arg8, arg9, arg10, NULL, arg11);
        else
        {
            LogicEntityPtr owner = LogicSystem::getLogicEntity(arg12);
            assert(owner.get()->dynamicEntity);
            particle_flare(p, dest, arg7, arg8, arg9, arg10, (fpsent*)(owner.get()->dynamicEntity), arg11);
        }
    });

    LUA_EMBED_ddddddiiidi(particleFlyingFlare, 0, {
        vec p(arg1, arg2, arg3);
        vec dest(arg4, arg5, arg6);
        particle_flying_flare(p, dest, arg7, arg8, arg9, arg10, arg11);
    });

    LUA_EMBED_iiddddddidib(particleTrail, 0, {
        vec from(arg3, arg4, arg5);
        vec to(arg6, arg7, arg8);
        particle_trail(arg1, arg2, from, to, arg9, arg10, arg11, arg12);
    });

    LUA_EMBED_idddddiidddi(particleFlame, 0, {
        regular_particle_flame(arg1, vec(arg2, arg3, arg4), arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);
    });

    LUA_EMBED_dddddddiiidddd(addDynlight, 0, {
        vec o(arg1, arg2, arg3);
        vec color(float(arg5)/255.0, float(arg6)/255.0, float(arg7)/255.0);
        vec initcolor(float(arg12)/255.0, float(arg13)/255.0, float(arg14)/255.0);

        LightControl::queueDynamicLight(o, arg4, color, arg8, arg9, arg10, arg11, initcolor, NULL);
    });

    LUA_EMBED_idddidddi(spawnDebris, 0, {
        vec v(arg2, arg3, arg4);
        vec debrisvel(arg6, arg7, arg8);

        LogicEntityPtr owner = LogicSystem::getLogicEntity(arg9);
        assert(owner->dynamicEntity);
        FPSClientInterface::spawnDebris(arg1, v, arg5, debrisvel, (dynent*)(owner->dynamicEntity));
    });

    LUA_EMBED_ddddii(particleMeter, 0, {
        vec s(arg1, arg2, arg3);

        particle_meter(s, arg4, arg5, arg6);
    });

    LUA_EMBED_dddsiiidi(particleText, 0, {
        vec s(arg1, arg2, arg3);
        particle_textcopy(s, arg4.c_str(), arg5, arg6, arg7, arg8, arg9);
    });

    LUA_EMBED_ii(clientDamageEffect, 0, {
        dynamic_cast<fpsent*>(player)->damageroll(arg1);
        damageblend(arg2);
    });

    LUA_EMBED_ddddid(showHUDRect, 0, { ClientSystem::addHUDRect(arg1, arg2, arg3, arg4, arg5, arg6); });

    LUA_EMBED_sddddid(showHUDImage, 0, { ClientSystem::addHUDImage(arg1, arg2, arg3, arg4, arg5, arg6, arg7); });

    LUA_EMBED_sdddi(showHUDText, 0, {
        // text, x, y, scale, color
        ClientSystem::addHUDText(arg1, arg2, arg3, arg4, arg5);
    });

#endif // CLIENT

// Messages

using namespace MessageSystem;
LUA_EMBED_iiss(PersonalServerMessage, 0, { send_PersonalServerMessage(arg1, arg2, arg3, arg4); });
LUA_EMBED_iiiiddd(ParticleSplashToClients, 0, { send_ParticleSplashToClients(arg1, arg2, arg3, arg4, arg5, arg6, arg7); });
LUA_EMBED_iiiiddd(ParticleSplashRegularToClients, 0, { send_ParticleSplashRegularToClients(arg1, arg2, arg3, arg4, arg5, arg6, arg7); });
LUA_EMBED_idddsi(SoundToClientsByName, 0, { send_SoundToClientsByName(arg1, arg2, arg3, arg4, arg5, arg6); });
LUA_EMBED_iis(StateDataChangeRequest, 0, { send_StateDataChangeRequest(arg1, arg2, arg3); });
LUA_EMBED_iis(UnreliableStateDataChangeRequest, 0, { send_UnreliableStateDataChangeRequest(arg1, arg2, arg3); });
LUA_EMBED_ii(NotifyNumEntities, 0, { send_NotifyNumEntities(arg1, arg2); });
LUA_EMBED_iiiss(LogicEntityCompleteNotification, 0, { send_LogicEntityCompleteNotification(arg1, arg2, arg3, arg4, arg5); });
LUA_EMBED_ii(LogicEntityRemoval, 0, { send_LogicEntityRemoval(arg1, arg2); });
LUA_EMBED_iiisi(StateDataUpdate, 0, { send_StateDataUpdate(arg1, arg2, arg3, arg4, arg5); });
LUA_EMBED_iiisi(UnreliableStateDataUpdate, 0, { send_UnreliableStateDataUpdate(arg1, arg2, arg3, arg4, arg5); });
LUA_EMBED_iidddi(DoClick, 0, { send_DoClick(arg1, arg2, arg3, arg4, arg5, arg6); });
LUA_EMBED_iissdddiiii(ExtentCompleteNotification, 0, { send_ExtentCompleteNotification(arg1, arg2, arg3,arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11); });

// File access

LUA_EMBED_s(readFile, 1, {
    try
    {
        REFLECT_PYTHON( read_file_safely );

        boost::python::object data = read_file_safely(arg1);
        std::string text = boost::python::extract<std::string>(data);

        LuaEngine::pushValue(text);
    }
    catch(boost::python::error_already_set const &)
    {
        printf("Error in Python execution of embedded read_file_safely\r\n");
        PyErr_Print();
        assert(0 && "Halting on Python error");
    }
});

// Mapping

extern void texturereset(int *n);
LUA_EMBED_NOPARAM(textureReset, 0, {
    int num = 0;
    texturereset(&num);
});

extern void texture(char *type, char *name, int *rot, int *xoffset, int *yoffset, float *scale, int *forcedindex);
LUA_EMBED_ssiiidi(texture, 0, {
    float arg6f = arg6;
    // XXX: arg7 may not be given, in which case it is undefined, and turns into 0.
    texture((char*)arg1.c_str(), (char*)arg2.c_str(), &arg3, &arg4, &arg5, &arg6f, &arg7);
});

extern void mapmodelreset(int *n);
LUA_EMBED_i(mapmodelReset, 0, {
    mapmodelreset(&arg1);
});

extern void mmodel(char *name);
LUA_EMBED_s(mapmodel, 0, {
    mmodel((char*)arg1.c_str());
});

extern void autograss(char *name);
LUA_EMBED_s(autograss, 0, {
    autograss((char*)arg1.c_str());
});

extern void texlayer(int *layer, char *name, int *mode, float *scale);
#ifdef CLIENT
LUA_EMBED_i(texLayer, 0, {
    int dummy1 = 0;
    float dummy2 = 0;
    texlayer(&arg1, (char*)"", &dummy1, &dummy2);
});
#else
LUA_EMBED_i(texLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_dd(texAlpha, 0, {
    std::string command = "texalpha ";
    command += Utility::toString(arg1);
    command += " " + Utility::toString(arg2);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_dd(texAlpha, 0, {
    arg1 = arg1; // warning otherwise
    arg2 = arg2;
});
#endif

#ifdef CLIENT
LUA_EMBED_ddd(texColor, 0, {
    std::string command = "texcolor ";
    command += Utility::toString(arg1);
    command += " " + Utility::toString(arg2);
    command += " " + Utility::toString(arg3);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_dd(texColor, 0, {
    arg1 = arg1; // warning otherwise
    arg2 = arg2;
});
#endif

#ifdef CLIENT
LUA_EMBED_i(texFFenv, 0, {
    std::string command = "texffenv ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(texFFenv, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_s(setShader, 0, {
    std::string command = "setshader ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1) );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(setShader, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_sdddd(setShaderParam, 0, {
    std::string command = "setshaderparam ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1) );
    command += " " + Utility::toString((float)arg2);
    command += " " + Utility::toString((float)arg3);
    command += " " + Utility::toString((float)arg4);
    command += " " + Utility::toString((float)arg5);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_sdddd(setShaderParam, 0, {
    arg1 = arg1; // warning otherwise
    arg2 = arg2; // warning otherwise
    arg3 = arg3; // warning otherwise
    arg4 = arg4; // warning otherwise
    arg5 = arg5; // warning otherwise
});
#endif

extern void materialreset();
LUA_EMBED_NOPARAM(materialReset, 0, {
    materialreset();
});

#ifdef CLIENT // SkyManager
LUA_EMBED_s(loadStars, 0, {
    std::string command = "starbox ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1, "/_<>:.,") );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(loadStars, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_s(loadSky, 0, {
    std::string command = "skybox ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1, "/_<>:.,") );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(loadSky, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_s(loadSun, 0, {
    std::string command = "sunbox ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1, "/_<>:.,") );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(loadSun, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_s(loadClouds, 0, {
    std::string command = "cloudbox ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1, "/_<>:.,") );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(loadClouds, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_s(loadCloudLayer, 0, {
    std::string command = "cloudlayer ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1, "/_<>:.,") );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(loadCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_s(loadAltCloudLayer, 0, {
    std::string command = "altcloudlayer ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1, "/_<>:.,") );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(loadAltCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_s(fogColor, 0, {
    std::string command = "fogcolour ";
    command += arg1;
    assert( Utility::validateAlphaNumeric(arg1) );
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(fogColor, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(fog, 0, {
    std::string command = "fog ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(fog, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_i(causticScale, 0, {
    std::string command = "causticscale ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(causticScale, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_i(causticMillis, 0, {
    std::string command = "causticmillis ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(causticMillis, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_i(waterSpecularity, 0, {
    std::string command = "waterspec ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(waterSpecularity, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(waterFog, 0, {
    std::string command = "waterfog ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(waterFog, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_iii(waterColor, 0, {
    std::string command = "watercolour ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(waterColor, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(waterFallTint, 0, {
    std::string command = "waterfallcolour ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(waterFallTint, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_i(lavaFog, 0, {
    std::string command = "lavafog ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(lavaFog, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(lavaTint, 0, {
    std::string command = "lavacolour ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(lavaTint, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(spinStars, 0, {
    std::string command = "spinstars ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(spinStars, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_d(spinSky, 0, {
    std::string command = "spinsky ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(spinSky, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(spinSun, 0, {
    std::string command = "spinsun ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(spinSun, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(spinClouds, 0, {
    std::string command = "spinclouds ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(spinClouds, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(spinCloudLayer, 0, {
    std::string command = "spincloudlayer ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(spinCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(spinAltCloudLayer, 0, {
    std::string command = "spinaltcloudlayer ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(spinAltCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(yawStars, 0, {
    std::string command = "yawstars ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(yawStars, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(yawSky, 0, {
    std::string command = "yawsky ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(yawSky, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(yawSun, 0, {
    std::string command = "yawsun ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(yawSun, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(yawClouds, 0, {
    std::string command = "yawclouds ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(yawClouds, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(yawCloudLayer, 0, {
    std::string command = "yawcloudlayer ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(yawCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(yawAltCloudLayer, 0, {
    std::string command = "yawaltcloudlayer ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(yawAltCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(alphaSky, 0, {
    std::string command = "skyboxalpha ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(alphaSky, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(alphaSun, 0, {
    std::string command = "sunboxalpha ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(alphaSun, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(alphaClouds, 0, {
    std::string command = "cloudboxalpha ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(alphaClouds, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(alphaCloudLayer, 0, {
    std::string command = "cloudalpha ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(alphaCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(alphaAltCloudLayer, 0, {
    std::string command = "altcloudalpha ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(alphaAltCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintStars, 0, {
    std::string command = "starboxtint ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintStars, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintSky, 0, {
    std::string command = "skyboxtint ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintSky, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintSun, 0, {
    std::string command = "sunboxtint ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintSun, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintClouds, 0, {
    std::string command = "cloudboxtint ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintClouds, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintCloudLayer, 0, {
    std::string command = "cloudtint ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintCloudLayer, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintAltCloudLayer, 0, {
    std::string command = "altcloudtint ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintAltCloudLayer, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_s(cloudLayer, 0, {
    std::string command = "cloudlayer ";
    assert(Utility::validateRelativePath(arg1));
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(cloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_s(altCloudLayer, 0, {
    std::string command = "altcloudlayer ";
    assert(Utility::validateRelativePath(arg1));
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(altCloudLayer, 0, {
    arg1 = arg1; // warning otherwise
});
#endif


#ifdef CLIENT
LUA_EMBED_d(cloudScrollX, 0, {
    std::string command = "cloudscrollx ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(cloudScrollX, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(altCloudScrollX, 0, {
    std::string command = "altcloudscrollx ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(altCloudScrollX, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_d(cloudScrollY, 0, {
    std::string command = "cloudscrolly ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(cloudScrollY, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(altCloudScrollY, 0, {
    std::string command = "altcloudscrolly ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(altCloudScrollY, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_d(cloudScale, 0, {
    std::string command = "cloudscale ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(cloudScale, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(altCloudScale, 0, {
    std::string command = "altcloudscale ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(altCloudScale, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(cloudHeight, 0, {
    std::string command = "cloudheight ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(cloudHeight, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(altCloudHeight, 0, {
    std::string command = "altcloudheight ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(altCloudHeight, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(cloudFade, 0, {
    std::string command = "cloudfade ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(cloudFade, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(altCloudFade, 0, {
    std::string command = "altcloudfade ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(altCloudFade, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(cloudClip, 0, {
    std::string command = "cloudclip ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(cloudClip, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(altCloudClip, 0, {
    std::string command = "altcloudclip ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(altCloudClip, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(skyTexture, 0, {
    std::string command = "skytexture ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(skyTexture, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_dd(texScroll, 0, {
    std::string command = "texscroll ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_dd(texScroll, 0, {
    arg1 = arg1; arg2 = arg2; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(shadowmapAngle, 0, {
    std::string command = "shadowmapangle ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(shadowmapAngle, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_s(shadowmapAmbient, 0, {
    assert( Utility::validateAlphaNumeric(arg1, "x") ); // Allow e.g. 0xFFA033
    std::string command = "shadowmapambient ";
    command += arg1;
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_s(shadowmapAmbient, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_iii(skylight, 0, {
    std::string command = "skylight ";
    command += Utility::toString(arg1) + " " + Utility::toString(arg2) + " " + Utility::toString(arg3);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(skylight, 0, {
    arg1 = arg1; // warning otherwise
    arg2 = arg2; // warning otherwise
    arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(blurSkylight, 0, {
    std::string command = "blurskylight ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(blurSkylight, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintAmbient, 0, {
    std::string command = "ambient ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintAmbient, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_iii(tintFog, 0, {
    std::string command = "fogcolour ";
    command += Utility::toString(arg1) + " ";
    command += Utility::toString(arg2) + " ";
    command += Utility::toString(arg3) + " ";
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_iii(tintFog, 0, {
    arg1 = arg1; arg2 = arg2; arg3 = arg3; // warning otherwise
});
#endif

#ifdef CLIENT
LUA_EMBED_i(ambient, 0, {
    std::string command = "ambient ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_i(ambient, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(modelTweaks, 0, {
    std::string command = "modeltweaks ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(modelTweaks, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(tweakModelAmbient, 0, {
    std::string command = "tweakmodelambient ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(tweakModelAmbient, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(tweakModelGlow, 0, {
    std::string command = "tweakmodelglow ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(tweakModelGlow, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(tweakModelSpec, 0, {
    std::string command = "tweakmodelspec ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(tweakModelSpec, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(tweakModelSpecGlare, 0, {
    std::string command = "tweakmodelspecglare ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(tweakModelSpecGlare, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(tweakModelGlowGlare, 0, {
    std::string command = "tweakmodelglowglare ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(tweakModelGlowGlare, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

#ifdef CLIENT // SkyManager
LUA_EMBED_d(tweakModelScale, 0, {
    std::string command = "tweakmodelscale ";
    command += Utility::toString(arg1);
    CSSUDO(command.c_str());
});
#else
LUA_EMBED_d(tweakModelScale, 0, {
    arg1 = arg1; // warning otherwise
});
#endif

// Models

#define ADD_CS_d(arg) \
    command += Utility::toString(arg); \
    command += " ";

#define ADD_CS_s(arg) \
    assert( Utility::validateAlphaNumeric(arg, "._/<>-:") ); \
    command += "\""; \
    command += arg; \
    command += "\" ";

#define CUBESCRIPT_i(name, cmd) \
LUA_EMBED_i(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_ii(name, cmd) \
LUA_EMBED_ii(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_iii(name, cmd) \
LUA_EMBED_iii(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_iiiii(name, cmd) \
LUA_EMBED_iiiii(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_d(name, cmd) \
LUA_EMBED_d(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_dd(name, cmd) \
LUA_EMBED_dd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_iid(name, cmd) \
LUA_EMBED_iid(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_iisddd(name, cmd) \
LUA_EMBED_iisddd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_s(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    ADD_CS_d(arg6); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_ddd(name, cmd) \
LUA_EMBED_ddd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_dddd(name, cmd) \
LUA_EMBED_dddd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_s(name, cmd) \
LUA_EMBED_s(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_si(name, cmd) \
LUA_EMBED_si(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_d(arg2); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_sd(name, cmd) \
LUA_EMBED_sd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_d(arg2); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_siidi(name, cmd) \
LUA_EMBED_siidi(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_sdd(name, cmd) \
LUA_EMBED_sdd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_ss(name, cmd) \
LUA_EMBED_ss(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_s(arg2); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_sss(name, cmd) \
LUA_EMBED_sss(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_s(arg2); \
    ADD_CS_s(arg3); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_ssdi(name, cmd) \
LUA_EMBED_ssdi(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_s(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_ssdd(name, cmd) \
LUA_EMBED_ssdd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_s(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_sssdd(name, cmd) \
LUA_EMBED_sssdd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_s(arg2); \
    ADD_CS_s(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_sdddd(name, cmd) \
LUA_EMBED_sdddd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_sdddddd(name, cmd) \
LUA_EMBED_sdddddd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_s(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    ADD_CS_d(arg6); \
    ADD_CS_d(arg7); \
    CSSUDO(command.c_str()); \
});

#define CUBESCRIPT_iiddddd(name, cmd) \
LUA_EMBED_iiddddd(name, 0, { \
    std::string command = #cmd; \
    command += " "; \
    ADD_CS_d(arg1); \
    ADD_CS_d(arg2); \
    ADD_CS_d(arg3); \
    ADD_CS_d(arg4); \
    ADD_CS_d(arg5); \
    ADD_CS_d(arg6); \
    ADD_CS_d(arg7); \
    CSSUDO(command.c_str()); \
});

CUBESCRIPT_i(modelShadow, mdlshadow);
CUBESCRIPT_i(modelCollide, mdlcollide);
CUBESCRIPT_i(modelPerEntityCollisionBoxes, mdlperentitycollisionboxes);
CUBESCRIPT_i(modelEllipseCollide, mdlellipsecollide);

CUBESCRIPT_s(objLoad, objload);

CUBESCRIPT_ss(objSkin, objskin);
CUBESCRIPT_ss(objBumpmap, objbumpmap);
CUBESCRIPT_ss(objEnvmap, objenvmap);
CUBESCRIPT_si(objSpec, objspec);

CUBESCRIPT_dddd(objPitch, objpitch);
CUBESCRIPT_si(objAmbient, objambient);
CUBESCRIPT_si(objGlow, objglow);
CUBESCRIPT_sdd(objGlare, objglare);
CUBESCRIPT_sd(objAlphatest, objalphatest);
CUBESCRIPT_si(objAlphablend, objalphablend);
CUBESCRIPT_si(objCullface, objcullface);
CUBESCRIPT_sd(objFullbright, objfullbright);
CUBESCRIPT_ss(objShader, objshader);
CUBESCRIPT_sdd(objScroll, objscroll);
CUBESCRIPT_si(objNoclip, objnoclip);

CUBESCRIPT_d(mdlAlphatest, mdlalphatest);
CUBESCRIPT_i(mdlAlphablend, mdlalphablend);
CUBESCRIPT_i(mdlAlphadepth, mdlalphadepth);

CUBESCRIPT_ddd(mdlBb, mdlbb);
CUBESCRIPT_ddd(mdlExtendbb, mdlextendbb);

CUBESCRIPT_i(mdlScale, mdlscale);
CUBESCRIPT_i(mdlSpec, mdlspec);
CUBESCRIPT_i(mdlGlow, mdlglow);
CUBESCRIPT_dd(mdlGlare, mdlglare);
CUBESCRIPT_i(mdlAmbient, mdlambient);
CUBESCRIPT_i(mdlCullface, mdlcullface);
CUBESCRIPT_i(mdlDepthoffset, mdldepthoffset);
CUBESCRIPT_d(mdlFullbright, mdlfullbright);
CUBESCRIPT_dd(mdlSpin, mdlspin);

CUBESCRIPT_s(mdlShader, mdlshader);

CUBESCRIPT_i(mdlCollisionsOnlyForTriggering, mdlcollisionsonlyfortriggering);

CUBESCRIPT_ddd(mdlTrans, mdltrans);

CUBESCRIPT_d(modelYaw, mdlyaw);
CUBESCRIPT_d(modelPitch, mdlpitch);

CUBESCRIPT_dddd(md2Pitch, md2pitch);
CUBESCRIPT_siidi(md2Anim, md2anim);

CUBESCRIPT_s(md3Load, md3load);
CUBESCRIPT_dddd(md3Pitch, md3pitch);
CUBESCRIPT_sssdd(md3Skin, md3skin);
CUBESCRIPT_si(md3Spec, md3spec);
CUBESCRIPT_si(md3Ambient, md3ambient);
CUBESCRIPT_si(md3Glow, md3glow);
CUBESCRIPT_sdd(md3Glare, md3glare);
CUBESCRIPT_sd(md3Alphatest, md3alphatest);
CUBESCRIPT_si(md3Alphablend, md3alphablend);
CUBESCRIPT_si(md3Cullface, md3cullface);
CUBESCRIPT_ss(md3Envmap, md3envmap);
CUBESCRIPT_sss(md3Bumpmap, md3bumpmap);
CUBESCRIPT_sd(md3Fullbright, md3fullbright);
CUBESCRIPT_ss(md3Shader, md3shader);
CUBESCRIPT_sdd(md3Scroll, md3scroll);
CUBESCRIPT_siidi(md3Anim, md3anim);
CUBESCRIPT_iisddd(md3Link, md3link);
CUBESCRIPT_si(md3Noclip, md3noclip);

CUBESCRIPT_s(md5Dir, md5dir);
CUBESCRIPT_ss(md5Load, md5load);

CUBESCRIPT_sssdd(md5Skin, md5skin);
CUBESCRIPT_ss(md5Bumpmap, md5bumpmap);
CUBESCRIPT_ss(md5Envmap, md5envmap);
CUBESCRIPT_sd(md5Alphatest, md5alphatest);
CUBESCRIPT_si(md5Alphablend, md5alphablend);

CUBESCRIPT_sdddddd(md5Adjust, md5adjust);
CUBESCRIPT_si(md5Spec, md5spec);
CUBESCRIPT_si(md5Ambient, md5ambient);
CUBESCRIPT_si(md5Glow, md5glow);
CUBESCRIPT_sdd(md5Glare, md5glare);
CUBESCRIPT_si(md5Cullface, md5cullface);
CUBESCRIPT_sd(md5Fullbright, md5fullbright);
CUBESCRIPT_ss(md5Shader, md5shader);
CUBESCRIPT_sdd(md5Scroll, md5scroll);
CUBESCRIPT_iisddd(md5Link, md5link);
CUBESCRIPT_si(md5Noclip, md5noclip);

CUBESCRIPT_ss(md5Tag, md5tag);
CUBESCRIPT_ssdi(md5Anim, md5anim);

CUBESCRIPT_s(md5Animpart, md5animpart);
CUBESCRIPT_sdddd(md5Pitch, md5pitch);

CUBESCRIPT_s(iqmDir, iqmdir);
CUBESCRIPT_ss(iqmLoad, iqmload);
CUBESCRIPT_ss(iqmTag, iqmtag);
CUBESCRIPT_sdddd(iqmPitch, iqmpitch);
CUBESCRIPT_sdddddd(iqmAdjust, iqmadjust);
CUBESCRIPT_sssdd(iqmSkin, iqmskin);
CUBESCRIPT_si(iqmSpec, iqmspec);
CUBESCRIPT_si(iqmAmbient, iqmambient);
CUBESCRIPT_si(iqmGlow, iqmglow);
CUBESCRIPT_sdd(iqmGlare, iqmglare);
CUBESCRIPT_sd(iqmAlphatest, iqmalphatest);
CUBESCRIPT_si(iqmAlphablend, iqmalphablend);
CUBESCRIPT_si(iqmCullface, iqmcullface);
CUBESCRIPT_ss(iqmEnvmap, iqmenvmap);
CUBESCRIPT_ss(iqmBumpmap, iqmbumpmap);
CUBESCRIPT_sd(iqmFullbright, iqmfullbright);
CUBESCRIPT_ss(iqmShader, iqmshader);
CUBESCRIPT_sdd(iqmScroll, iqmscroll);
CUBESCRIPT_s(iqmAnimpart, iqmanimpart);
CUBESCRIPT_ssdi(iqmAnim, iqmanim);
CUBESCRIPT_iisddd(iqmLink, iqmlink);
CUBESCRIPT_si(iqmNoclip, iqmnoclip);

CUBESCRIPT_s(smdDir, smddir);
CUBESCRIPT_ss(smdLoad, smdload);
CUBESCRIPT_ss(smdTag, smdtag);
CUBESCRIPT_sdddd(smdPitch, smdpitch);
CUBESCRIPT_sdddddd(smdAdjust, smdadjust);
CUBESCRIPT_sssdd(smdSkin, smdskin);
CUBESCRIPT_si(smdSpec, smdspec);
CUBESCRIPT_si(smdAmbient, smdambient);
CUBESCRIPT_si(smdGlow, smdglow);
CUBESCRIPT_sdd(smdGlare, smdglare);
CUBESCRIPT_sd(smdAlphatest, smdalphatest);
CUBESCRIPT_si(smdAlphablend, smdalphablend);
CUBESCRIPT_si(smdCullface, smdcullface);
CUBESCRIPT_ss(smdEnvmap, smdenvmap);
CUBESCRIPT_ss(smdBumpmap, smdbumpmap);
CUBESCRIPT_sd(smdFullbright, smdfullbright);
CUBESCRIPT_ss(smdShader, smdshader);
CUBESCRIPT_sdd(smdScroll, smdscroll);
CUBESCRIPT_s(smdAnimpart, smdanimpart);
CUBESCRIPT_ssdi(smdAnim, smdanim);
CUBESCRIPT_iisddd(smdLink, smdlink);
CUBESCRIPT_si(smdNoclip, smdnoclip);

CUBESCRIPT_ddd(rdVert, rdvert);
CUBESCRIPT_i(rdEye, rdeye);
CUBESCRIPT_iii(rdTri, rdtri);
CUBESCRIPT_iiiii(rdJoint, rdjoint);
CUBESCRIPT_iid(rdLimitDist, rdlimitdist);
CUBESCRIPT_iiddddd(rdLimitRot, rdlimitrot);
CUBESCRIPT_i(rdAnimJoints, rdanimjoints);

CUBESCRIPT_dd(mdlEnvmap, mdlenvmap);

// Keyboard

extern bool getkeydown();
extern bool getkeyup();
extern bool getmousedown();
extern bool getmouseup();

LUA_EMBED_NOPARAM(isKeyDown, 0, {
    LuaEngine::pushValue(getkeydown());
});

LUA_EMBED_NOPARAM(isKeyUp, 0, {
    LuaEngine::pushValue(getkeyup());
});

LUA_EMBED_NOPARAM(isMouseDown, 0, {
    LuaEngine::pushValue(getmousedown());
});

LUA_EMBED_NOPARAM(isMouseUp, 0, {
    LuaEngine::pushValue(getmouseup());
});

// Code

LUA_EMBED_s(compile, 0, {
    LuaEngine::runScript(arg1);
});

// Components

LUA_EMBED_ss(signalComponent, 1, {
    try
    {
        REFLECT_PYTHON( signal_signal_component );

        boost::python::object data = signal_signal_component(arg1, arg2);
        std::string stringData = boost::python::extract<std::string>(data);
        LuaEngine::pushValue(stringData);
    } catch(boost::python::error_already_set const &)
    {
        printf("Error in signalling python component initialization\r\n");
        PyErr_Print();
        assert(0 && "Halting on Python error");
    }
});

// Models

LUA_EMBED_s(preloadModel, 0, {
    preloadmodel(arg1.c_str());
});

LUA_EMBED_s(reloadModel, 0, {
    extern void clearmodel(char *name);
    clearmodel((char*)arg1.c_str());
    if (!loadmodel((char*)arg1.c_str())) LuaEngine::error("Cannot load model.");
});

// HUD

#ifdef CLIENT
    LUA_EMBED_NOPARAM(getTargetPosition, 1, {
        TargetingControl::determineMouseTarget(true); // Force a determination, if needed

        RETURN_VECTOR3(TargetingControl::targetPosition);
    });

    LUA_EMBED_NOPARAM(getTargetEntity, 1, {
        TargetingControl::determineMouseTarget(true); // Force a determination, if needed

        LogicEntityPtr target = TargetingControl::targetLogicEntity;
        if (target.get() && !target->isNone() && target->luaRef >= 0)
            LuaEngine::getRef(target->luaRef);
        else
            LuaEngine::pushValue();
    });

    LUA_EMBED_i(useMinimap, 0, {
        std::string command = "useminimap ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_NOPARAM(usedMinimap, 1, {
        LuaEngine::pushValue(game::usedminimap());
    });

    LUA_EMBED_i(minimapMinZoom, 0, {
        std::string command = "forceminminimapzoom ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_i(minimapMaxZoom, 0, {
        std::string command = "forcemaxminimapzoom ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_d(minimapRadius, 0, {
        std::string command = "minimapradius ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_d(minimapPositionX, 0, {
        std::string command = "minimapxpos ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_d(minimapPositionY, 0, {
        std::string command = "minimapypos ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_d(minimapRotation, 0, {
        std::string command = "minimaprotation ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_i(minimapSidesNum, 0, {
        std::string command = "minimapsides ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

    LUA_EMBED_i(minimapAlignRight, 0, {
        std::string command = "minimaprightalign ";
        command += Utility::toString(arg1);
        CSSUDO(command.c_str());
    });

// Rendering

    VARP(ragdolll, 0, 1, 1);
    static int oldThirdperson = -1;

    void prepareRagdollLua(int& anim, LogicEntityPtr self)
    {
        if (anim&ANIM_RAGDOLL)
        {
//            if (!ragdoll || loadmodel(mdl);
            fpsent* fpsEntity = (fpsent*)self->dynamicEntity;

            if (fpsEntity->clientnum == ClientSystem::playerNumber)
            {

                if (oldThirdperson == -1 && thirdperson == 0)
                {
                    oldThirdperson = thirdperson;
                    thirdperson = 1;
                }
            }

            if (fpsEntity->ragdoll || !ragdolll || !PhysicsManager::getEngine()->prepareRagdoll(self))
            {
                anim &= ~ANIM_RAGDOLL;
                LuaEngine::getRef(self->luaRef);
                LuaEngine::getTableItem("setLocalAnimation");
                LuaEngine::pushValueFromIndex(-2);
                LuaEngine::pushValue(anim);
                LuaEngine::call(2, 0); // Set new animation locally - in state data and C++
                LuaEngine::pop(1);
            }
        } else {
            if (self->dynamicEntity)
            {
                fpsent* fpsEntity = (fpsent*)self->dynamicEntity;

                if (fpsEntity->clientnum == ClientSystem::playerNumber && oldThirdperson != -1)
                {
                    thirdperson = oldThirdperson;
                    oldThirdperson = -1;
                }
            }
        }
    }

    fpsent* getProxyFpsEntityLua(LogicEntityPtr self)
    {
        LuaEngine::getRef(self->luaRef);
        LuaEngine::getTableItem("renderingHashHint");

        if (!LuaEngine::isNoneNil(-1))
        {
            static bool initialized = false;
            static fpsent* fpsEntitiesForRendering[1024];

            if (!initialized)
            {
                for (int i = 0; i < 1024; i++)
                    fpsEntitiesForRendering[i] = new fpsent;

                initialized = true;
            }

            int renderingHashHint = LuaEngine::getInteger(-1);
            LuaEngine::pop(2);
            renderingHashHint = renderingHashHint & 1023;
            assert(renderingHashHint >= 0 && renderingHashHint < 1024);
            return fpsEntitiesForRendering[renderingHashHint];
        }
        else
        {
            LuaEngine::pop(1);
            return NULL;
        }
    }

    #define PREP_RENDER_MODEL \
        int anim = arg3; \
        prepareRagdollLua(anim, self); \
        vec o(arg4, arg5, arg6); \
        fpsent *fpsEntity = NULL; \
        if (self->dynamicEntity) \
            fpsEntity = dynamic_cast<fpsent*>(self->dynamicEntity); \
        else \
            fpsEntity = getProxyFpsEntityLua(self);

    LUA_EMBED_T(renderModel2, 0, siddddddii, {
        PREP_RENDER_MODEL
        rendermodel(NULL, arg2.c_str(), anim, o, self, arg7, arg8, arg9, arg10, fpsEntity, self->attachments, arg11);
    });

    LUA_EMBED_T(renderModel3, 0, siddddddiidddd, {
        PREP_RENDER_MODEL
        quat rotation(arg12, arg13, arg14, arg15);
        rendermodel(NULL, arg2.c_str(), anim, o, self, arg7, arg8, arg9, arg10, fpsEntity, self->attachments, arg11, 0, 1, rotation);
    });

// GUI

    LUA_EMBED_s(showMessage, 0, {
        IntensityGUI::showMessage("Script message", arg1);
    });

    LUA_EMBED_s(showInputDialog, 0, {
        IntensityGUI::showInputDialog("Script input", arg1);
    });

    LUA_EMBED_i(setDefaultThirdpersonMode, 0, {
        // Only allow this to be done once
        if (LuaEngine::engineParameters.count("setDefaultThirdpersonMode") == 0)
        {
            LuaEngine::engineParameters["setDefaultThirdpersonMode"] = "set";
            thirdperson = arg1;
        } else
            Logging::log(Logging::WARNING, "Can only set default thirdperson mode once per map\r\n");
    });

// Network

    LUA_EMBED_si(connect, 0, {
        ClientSystem::connect(arg1, arg2);
    });

// Camera

    LUA_EMBED_ddddddd(forceCamera, 0, {
        vec position(arg1, arg2, arg3);
        CameraControl::forceCamera(position, arg4, arg5, arg6, arg7);
    });

    LUA_EMBED_ddd(forcePosition, 0, {
        vec position(arg1, arg2, arg3);
        CameraControl::forcePosition(position);
    });

    LUA_EMBED_d(forceYaw, 0, {
        CameraControl::forceYaw(arg1);
    });

    LUA_EMBED_d(forcePitch, 0, {
        CameraControl::forcePitch(arg1);
    });

    LUA_EMBED_d(forceRoll, 0, {
        CameraControl::forceRoll(arg1);
    });

    LUA_EMBED_d(forceFov, 0, {
        CameraControl::forceFov(arg1);
    });

    LUA_EMBED_NOPARAM(resetCamera, 0, {
        CameraControl::positionCamera(CameraControl::getCamera());
    });

    LUA_EMBED_NOPARAM(getCamera, 1, {
        physent *camera = CameraControl::getCamera();

        LuaEngine::newTable();
        LuaEngine::pushValue("position");
        RETURN_VECTOR3(camera->o); // usually used for returning, but does not actually return
        LuaEngine::setTableIndex();

        LuaEngine::setTable("yaw", camera->yaw);
        LuaEngine::setTable("pitch", camera->pitch);
        LuaEngine::setTable("roll", camera->roll);
    });

    LUA_EMBED_NOPARAM(getCameraPosition, 1, {
        physent *camera = CameraControl::getCamera();
        vec& pos = camera->o;
        RETURN_VECTOR3(pos);
    });
#endif

// Editing

#include "editing_system.h"

LUA_EMBED_NOPARAM(editing_getWorldSize, 1, {
    LuaEngine::pushValue(EditingSystem::getWorldSize());
});

LUA_EMBED_NOPARAM(editing_getGridSize, 1, {
    LuaEngine::pushValue(1<<getvar("gridpower"));
});

LUA_EMBED_NOPARAM(editing_eraseGeometry, 0, {
    EditingSystem::eraseGeometry();
});

LUA_EMBED_iiii(editing_createCube, 0, {
    EditingSystem::createCube(arg1, arg2, arg3, arg4);
});

LUA_EMBED_iiii(editing_deleteCube, 0, {
    EditingSystem::deleteCube(arg1, arg2, arg3, arg4);
});

LUA_EMBED_iiiiii(editing_setCubeTexture, 0, {
    EditingSystem::setCubeTexture(arg1, arg2, arg3, arg4, arg5, arg6);
});

LUA_EMBED_iiiii(editing_setCubeMaterial, 0, {
    EditingSystem::setCubeMaterial(arg1, arg2, arg3, arg4, arg5);
});

LUA_EMBED_iiiiiii(editing_pushCubeCorner, 0, {
    EditingSystem::pushCubeCorner(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
});

LUA_EMBED_NOPARAM(editing_getSelectedEntity, 1, {
    LogicEntityPtr ret = EditingSystem::getSelectedEntity();
    if (ret.get() && !ret->isNone() && ret->luaRef >= 0) LuaEngine::getRef(ret->luaRef);
    else LuaEngine::pushValue();
});

LUA_EMBED_ds(renderProgress, 0, {
    renderprogress(arg1, arg2.c_str());
});

LUA_EMBED_NOPARAM(getMapversion, 0, {
    LuaEngine::pushValue(mapversion);
});

// Models

#define RETURN_CENTER_RADIUS \
{ \
    LuaEngine::newTable(); \
\
    LuaEngine::pushValue("center"); \
    RETURN_VECTOR3(center); \
    LuaEngine::setTableIndex(); \
\
    LuaEngine::pushValue("radius"); \
    RETURN_VECTOR3(radius); \
    LuaEngine::setTableIndex(); \
}

LUA_EMBED_s(modelBoundingBox, 1, {
    model* theModel = loadmodel(arg1.c_str());
    if (!theModel)
    {
        LuaEngine::pushValue();
        return 1;
    }
    vec center;
    vec radius;
    theModel->boundbox(0, center, radius);

    RETURN_CENTER_RADIUS;
});

LUA_EMBED_s(modelCollisionBox, 1, {
    model* theModel = loadmodel(arg1.c_str());
    if (!theModel)
    {
        LuaEngine::pushValue();
        return 1;
    }
    vec center;
    vec radius;
    theModel->collisionbox(0, center, radius);

    RETURN_CENTER_RADIUS;
});

LUA_EMBED_s(modelMesh, 1, {
    model* theModel = loadmodel(arg1.c_str());
    if (!theModel)
    {
        LuaEngine::pushValue();
        return 1;
    }

    vector<BIH::tri> tris2[2];
    theModel->gentris(0, tris2);
    vector<BIH::tri>& tris = tris2[0];

    LuaEngine::newTable();
    LuaEngine::setTable("length", tris.length());

    for (int i = 0; i < tris.length(); i++)
    {
        BIH::tri& bt = tris[i];

        LuaEngine::pushValue(Utility::toString(i));

        LuaEngine::newTable();
        LuaEngine::pushValue("a");
        RETURN_VECTOR3(bt.a);
        LuaEngine::setTableIndex();
        LuaEngine::pushValue("b");
        RETURN_VECTOR3(bt.b);
        LuaEngine::setTableIndex();
        LuaEngine::pushValue("c");
        RETURN_VECTOR3(bt.c);
        LuaEngine::setTableIndex();

        LuaEngine::setTableIndex();
    }
});

// NPCs/bots

#ifdef SERVER
    LUA_EMBED_s(addNPC, 1, {
        int _ref = NPC::add(arg1);
        if (_ref >= 0)
            LuaEngine::getRef(_ref); // this "pushes" so it returns the table
        else
            LuaEngine::pushValue();
    });

    LUA_EMBED_T(removeNPC, 0, , {
        fpsent* fpsEntity = (fpsent*)self->dynamicEntity;
        NPC::remove(fpsEntity->clientnum);
    });
#endif

// data/ directory embeds, this is client-only, so we put it in ifdef. For server, they're just dummies
// dummies are needed because we don't want to check further in CAPIExtras.

#ifdef CLIENT
    extern void keymap(int *code, char *key);
    extern void newfont(char *name, char *tex, int *defaultw, int *defaulth, int *offsetx, int *offsety, int *offsetw, int *offseth);
    extern void fontoffset(char *c);
    extern void fontchar(int *x, int *y, int *w, int *h);
    extern void registersound(char *name, int *vol);

    LUA_EMBED_is(keymap, 0, {
        keymap(&arg1, (char *)arg2.c_str());
    });

    LUA_EMBED_si(registerSound, 0, {
        registersound((char *)arg1.c_str(), &arg2);
    });

    LUA_EMBED_ssiiiiii(font, 0, {
        newfont((char *)arg1.c_str(), (char *)arg2.c_str(), &arg3, &arg4, &arg5, &arg6, &arg7, &arg8);
    });

    LUA_EMBED_s(fontOffset, 0, {
        fontoffset((char *)arg1.c_str());
    });

    LUA_EMBED_iiii(fontChar, 0, {
        fontchar(&arg1, &arg2, &arg3, &arg4);
    });
#else
    LUA_EMBED_is(keymap, 0, {
        arg1 = arg1;
        arg2 = arg2;
    });
    LUA_EMBED_si(registerSound, 0, {
        arg1 = arg1;
        arg2 = arg2;
    });
    LUA_EMBED_ssiiiiii(font, 0, {
        arg1 = arg1;
        arg2 = arg2;
        arg3 = arg3;
        arg4 = arg4;
        arg5 = arg5;
        arg6 = arg6;
        arg7 = arg7;
        arg8 = arg8;
    });
    LUA_EMBED_s(fontOffset, 0, {
        arg1 = arg1;
    });
    LUA_EMBED_iiii(fontChar, 0, {
        arg1 = arg1;
        arg2 = arg2;
        arg3 = arg3;
        arg4 = arg4;
    });
#endif

// Variable manipulation, this is valid for BOTH client and server

typedef hashtable<const char *, ident> identtable;
extern identtable *idents; // we must extern out ident table.
// Externing ident table is temporary till proper API is written
// (which will be done after cubescript is completely out)

// here we must also extern some setters
extern void setvarchecked(ident *id, int val);
extern void setfvarchecked(ident *id, float val);
extern void setsvarchecked(ident *id, const char *val);
extern void alias(const char *name, const char *action);

LUA_EMBED_s(getVariable, 1, {
    ident *ident = idents->access(arg1.c_str());
    if (ident)
    {
        switch(ident->type)
        {
            case ID_VAR:
                LuaEngine::pushValue(*ident->storage.i);
                break;
            case ID_FVAR:
                LuaEngine::pushValue(*ident->storage.f);
                break;
            case ID_SVAR:
                LuaEngine::pushValue(std::string(*ident->storage.s));
                break;
            case ID_ALIAS:
                LuaEngine::pushValue(ident->action);
                break;
        }
    }
});

LUA_EMBED_ss(setVariable, 0, {
    ident *ident = idents->access(arg1.c_str());
    if (ident)
    {
        switch(ident->type)
        {
            case ID_VAR:
                setvarchecked(ident, atoi(arg2.c_str()));
                break;
            case ID_FVAR:
                setfvarchecked(ident, strtod(arg2.c_str(), NULL));
                break;
            case ID_SVAR:
                setsvarchecked(ident, arg2.c_str());
                break;
            case ID_ALIAS:
                alias(ident->name, arg2.c_str());
                break;
        }
    }
});
