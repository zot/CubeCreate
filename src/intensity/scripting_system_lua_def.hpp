/*
 * lua_system_lua_def.hpp, version 1
 * Header file for Lua binding functions
 *
 * author: q66 <quaker66@gmail.com>
 * license: MIT/X11
 *
 * Copyright (c) 2010 q66
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

using namespace lua;

/*
 * Some prototypes for binds, TODO: remove after headers are properly organized
 */
void removeentity(extentity* entity);
void addentity(extentity* entity);

void startmusic(char *name, char *cmd);
int preload_sound(char *name, int vol);

extern float GRAVITY;

void texturereset(int n);
void texture(const char *type, const char *name, int rot, int xoffset, int yoffset, float scale, int forcedindex);

void mapmodelreset(int *n);
void mmodel(char *name);
extern vector<mapmodelinfo> mapmodels;
void clearmodel(char *name);

void autograss(char *name);
void texlayer(int *layer, char *name, int *mode, float *scale);
void texalpha(float *front, float *back);
void texcolor(float *r, float *g, float *b);
void texscroll(float *scrollS, float *scrollT);
void texffenv(int *ffenv);
void materialreset();

void shader(int *type, char *name, char *vs, char *ps);
void variantshader(int *type, char *name, int *row, char *vs, char *ps);
void setshader(char *name);
void addshaderparam(const char *name, int type, int n, float x, float y, float z, float w);
void altshader(char *origname, char *altname);
void fastshader(char *nice, char *fast, int *detail);
void defershader(int *type, const char *name, const char *contents);
Shader *useshaderbyname(const char *name);

void isshaderdefined(char *name);
void isshadernative(char *name);

void addpostfx(const char *name, int bind, int scale, const char *inputs, float x, float y, float z, float w);
void setpostfx(const char *name, float x, float y, float z, float w);
void clearpostfx();

void mdlname();
void mdlalphatest(float *cutoff);
void mdlalphablend(int *blend);
void mdlalphadepth(int *depth);
void mdldepthoffset(int *offset);
void mdlcullface(int *cullface);
void mdlcollide(int *collide);
void mdlellipsecollide(int *collide);
void mdlspec(int *percent);
void mdlambient(int *percent);
void mdlglow(int *percent);
void mdlglare(float *specglare, float *glowglare);
void mdlenvmap(float *envmapmax, float *envmapmin, char *envmap);
void mdlfullbright(float *fullbright);
void mdlshader(char *shader);
void mdlspin(float *yaw, float *pitch);
void mdlscale(int *percent);
void mdltrans(float *x, float *y, float *z);
void mdlyaw(float *angle);
void mdlpitch(float *angle);
void mdlshadow(int *shadow);
void mdlbb(float *rad, float *h, float *eyeheight);
void mdlextendbb(float *x, float *y, float *z);
void mdlcollisionsonlyfortriggering(int *val);
void mdlperentitycollisionboxes(int *val);
void rdvert(float *x, float *y, float *z, float *radius);
void rdeye(int *v);
void rdtri(int *v1, int *v2, int *v3);
void rdjoint(int *n, int *t, char *v1, char *v2, char *v3);
void rdlimitdist(int *v1, int *v2, float *mindist, float *maxdist);
void rdlimitrot(int *t1, int *t2, float *maxangle, float *qx, float *qy, float *qz, float *qw);
void rdanimjoints(int *on);

void objload(char *model, float *smooth);
void objpitch(float *pitchscale, float *pitchoffset, float *pitchmin, float *pitchmax);
void objskin(char *meshname, char *tex, char *masks, float *envmapmax, float *envmapmin);
void objspec(char *meshname, int *percent);
void objambient(char *meshname, int *percent);
void objglow(char *meshname, int *percent);
void objglare(char *meshname, float *specglare, float *glowglare);
void objalphatest(char *meshname, float *cutoff);
void objalphablend(char *meshname, int *blend);
void objcullface(char *meshname, int *cullface);
void objenvmap(char *meshname, char *envmap);
void objbumpmap(char *meshname, char *normalmap, char *skin);
void objfullbright(char *meshname, float *fullbright);
void objshader(char *meshname, char *shader);
void objscroll(char *meshname, float *scrollu, float *scrollv);
void objnoclip(char *meshname, int *noclip);

void setmd5dir(char *name);  
void md5load(char *meshfile, char *skelname, float *smooth);
void md5tag(char *name, char *tagname);        
void md5pitch(char *name, float *pitchscale, float *pitchoffset, float *pitchmin, float *pitchmax);
void md5adjust(char *name, float *yaw, float *pitch, float *roll, float *tx, float *ty, float *tz);
void md5skin(char *meshname, char *tex, char *masks, float *envmapmax, float *envmapmin);
void md5spec(char *meshname, int *percent);
void md5ambient(char *meshname, int *percent);
void md5glow(char *meshname, int *percent);
void md5glare(char *meshname, float *specglare, float *glowglare);
void md5alphatest(char *meshname, float *cutoff);
void md5alphablend(char *meshname, int *blend);
void md5cullface(char *meshname, int *cullface);
void md5envmap(char *meshname, char *envmap);
void md5bumpmap(char *meshname, char *normalmap, char *skin);
void md5fullbright(char *meshname, float *fullbright);
void md5shader(char *meshname, char *shader);
void md5scroll(char *meshname, float *scrollu, float *scrollv);
void md5anim(char *anim, char *animfile, float *speed, int *priority);
void md5animpart(char *maskstr);
void md5link(int *parent, int *child, char *tagname, float *x, float *y, float *z);
void md5noclip(char *meshname, int *noclip);

void setiqmdir(char *name);  
void iqmload(char *meshfile, char *skelname);
void iqmtag(char *name, char *tagname);        
void iqmpitch(char *name, float *pitchscale, float *pitchoffset, float *pitchmin, float *pitchmax);
void iqmadjust(char *name, float *yaw, float *pitch, float *roll, float *tx, float *ty, float *tz);
void iqmskin(char *meshname, char *tex, char *masks, float *envmapmax, float *envmapmin);
void iqmspec(char *meshname, int *percent);
void iqmambient(char *meshname, int *percent);
void iqmglow(char *meshname, int *percent);
void iqmglare(char *meshname, float *specglare, float *glowglare);
void iqmalphatest(char *meshname, float *cutoff);
void iqmalphablend(char *meshname, int *blend);
void iqmcullface(char *meshname, int *cullface);
void iqmenvmap(char *meshname, char *envmap);
void iqmbumpmap(char *meshname, char *normalmap, char *skin);
void iqmfullbright(char *meshname, float *fullbright);
void iqmshader(char *meshname, char *shader);
void iqmscroll(char *meshname, float *scrollu, float *scrollv);
void iqmanim(char *anim, char *animfile, float *speed, int *priority);
void iqmanimpart(char *maskstr);
void iqmlink(int *parent, int *child, char *tagname, float *x, float *y, float *z);
void iqmnoclip(char *meshname, int *noclip);

void setsmddir(char *name);  
void smdload(char *meshfile, char *skelname);
void smdtag(char *name, char *tagname);        
void smdpitch(char *name, float *pitchscale, float *pitchoffset, float *pitchmin, float *pitchmax);
void smdadjust(char *name, float *yaw, float *pitch, float *roll, float *tx, float *ty, float *tz);
void smdskin(char *meshname, char *tex, char *masks, float *envmapmax, float *envmapmin);
void smdspec(char *meshname, int *percent);
void smdambient(char *meshname, int *percent);
void smdglow(char *meshname, int *percent);
void smdglare(char *meshname, float *specglare, float *glowglare);
void smdalphatest(char *meshname, float *cutoff);
void smdalphablend(char *meshname, int *blend);
void smdcullface(char *meshname, int *cullface);
void smdenvmap(char *meshname, char *envmap);
void smdbumpmap(char *meshname, char *normalmap, char *skin);
void smdfullbright(char *meshname, float *fullbright);
void smdshader(char *meshname, char *shader);
void smdscroll(char *meshname, float *scrollu, float *scrollv);
void smdanim(char *anim, char *animfile, float *speed, int *priority);
void smdanimpart(char *maskstr);
void smdlink(int *parent, int *child, char *tagname, float *x, float *y, float *z);
void smdnoclip(char *meshname, int *noclip);

extern bool getkeydown();
extern bool getkeyup();
extern bool getmousedown();
extern bool getmouseup();

void clearmodel(char *name);
void keymap(int *code, char *key);
void newfont(char *name, char *tex, int *defaultw, int *defaulth, int *offsetx, int *offsety, int *offsetw, int *offseth);
void fontoffset(char *c);
void fontchar(int *x, int *y, int *w, int *h);
void registersound(char *name, int *vol);

typedef hashtable<const char *, ident> identtable;
extern identtable *idents; // we must extern out ident table.
// Externing ident table is temporary till proper API is written
// (which will be done after cubescript is completely out)

// here we must also extern some setters
void setvarchecked(ident *id, int val);
void setfvarchecked(ident *id, float val);
void setsvarchecked(ident *id, const char *val);
void alias(const char *name, const char *action);

void run_python(char *code);

void showgui(const char *name);
int cleargui(int n);
void guionclear(char *action);
void guistayopen(char *contents);
void guinoautotab(char *contents);
void guibutton(char *name, char *action, char *icon);
void guiimage(char *path, char *action, float *scale, int *overlaid, char *alt);
void guicolor(int *color);
void guitextbox(char *text, int *width, int *height, int *color);
void guitext(char *name, char *icon);
void guititle(char *name);
void guitab(char *name);
void guibar();
void guistrut(float *strut, int *alt);
void guislider(char *var, int *min, int *max, char *onchange);
void guilistslider(char *var, char *list, char *onchange);
void guinameslider(char *var, char *names, char *list, char *onchange);
void guicheckbox(char *name, char *var, float *on, float *off, char *onchange);
void guiradio(char *name, char *var, float *n, char *onchange);
void guibitfield(char *name, char *var, int *mask, char *onchange);
void guifield(char *var, int *maxlength, char *onchange, int *password);
void guieditor(char *name, int *maxlength, int *height, int *mode);
void guikeyfield(char *var, int *maxlength, char *onchange);
void guilist(char *contents);
void guialign(int *align, char *contents);
void newgui(char *name, char *contents, char *header);

void force_quit();
void quit();
void screenres(int *w, int *h);
void resetgl();
void getfps_(int *raw);

void resetlightmaps(bool fullclean);
void calclight(int *quality);
void patchlight(int *quality);
void clearlightmaps();
void dumplms();

void clearblendbrushes();
void delblendbrush(const char *name);
void addblendbrush(const char *name, const char *imgname);
void nextblendbrush(int *dir);
void setblendbrush(const char *name);
void getblendbrushname(int *n);
void curblendbrush();
void rotateblendbrush(int *val);
void paintblendmap(bool msg);

extern int paintingblendmap;

void clearblendmapsel();
void invertblendmapsel();
void invertblendmap();
void showblendmap();
void optimizeblendmap();
void resetblendmap();

extern int conskip, miniconskip;
void setconskip(int &skip, int filter, int n);
extern vector<cline> conlines;
void bindkey(char *key, char *action, int state, const char *cmd);
void getbind(char *key, int type);
void searchbinds(char *action, int type);
void inputcommand(char *init, char *action = NULL, char *prompt = NULL);
void addfilecomplete(char *command, char *dir, char *ext);
void addlistcomplete(char *command, char *list);
void history_(int *n);
void onrelease(char *s);

void movie(char *name);
void recalc();
void glext(char *ext);
void loadcrosshair_(const char *name, int *i);
void tabify(const char *str, int *numtabs);
void resetsound();
void trydisconnect();
void printcube();
void remip_();
void phystest();
void clearpvs();
void testpvs(int *vcsize);
void genpvs(int *viewcellsize);
void pvsstats();
void startlistenserver(int *usemaster);
void stoplistenserver();

/* Here begin the binds. Close them in C++ namespace */
namespace lua_binds
{

/*
 * Things to go into Logging Lua namespace
 */
LUA_BIND_DEF(log, Logging::log_noformat(e.Get<int>(1), e.Get<std::string>(2));)
LUA_BIND_DEF(echo, conoutf("\f1%s", e.Get<const char*>(1));)

/*
 * Things to go into CAPI Lua namespace
 */

// General
LUA_BIND_DEF(currTime, e.Push(Utility::SystemInfo::currTime());)

// Math extensions
LUA_BIND_DEF(lsh, e.Push(e.Get<int>(1) << e.Get<int>(2));)
LUA_BIND_DEF(rsh, e.Push(e.Get<int>(1) >> e.Get<int>(2));)
LUA_BIND_DEF(bor, {
    int out = e.Get<int>(1);
    int n   = e.TopStackItemIndex();
    for (int i = 2; i <= n; i++) out |= e.Get<int>(i);
    e.Push(out);
})
LUA_BIND_DEF(band, {
    int out = e.Get<int>(1);
    int n   = e.TopStackItemIndex();
    for (int i = 2; i <= n; i++) out &= e.Get<int>(i);
    e.Push(out);
})
LUA_BIND_DEF(bnot, e.Push(~e.Get<int>(1));)

// Entity management
LUA_BIND_DEF(unregisterLogicEntity, LogicSystem::unregisterLogicEntityByUniqueId(e.Get<int>(1));)
LUA_BIND_DEF(placeInWorld, WorldSystem::placeInWorld(e.Get<int>(1), e.Get<int>(2));)

LUA_BIND_SE(setupExtent, LogicSystem::setupExtent(ref,
    e.Get<int>(2),
    e.Get<double>(3),
    e.Get<double>(4),
    e.Get<double>(5),
    e.Get<int>(6),
    e.Get<int>(7),
    e.Get<int>(8),
    e.Get<int>(9));
)
LUA_BIND_SE(setupCharacter,     LogicSystem::setupCharacter(ref);)
LUA_BIND_SE(setupNonSauer,      LogicSystem::setupNonSauer(ref);)
LUA_BIND_SE(dismantleExtent,    LogicSystem::dismantleExtent(ref);)
LUA_BIND_SE(dismantleCharacter, LogicSystem::dismantleCharacter(ref);)

// Entity attribs
LUA_BIND_LE(setAnimation, self.get()->setAnimation(e.Get<int>(2));)
LUA_BIND_LE(getStartTime, e.Push(self.get()->getStartTime());)
LUA_BIND_LE(setModelName, {
    Logging::log(Logging::DEBUG, "setModelName(%s)\r\n", e.Get<const char*>(2));
    self.get()->setModel(e.Get<std::string>(2));
})
LUA_BIND_LE(setSoundName, {
    Logging::log(Logging::DEBUG, "setSoundName(%s)\r\n", e.Get<const char*>(2));
    self.get()->setSound(e.Get<std::string>(2));
})
LUA_BIND_LE(setSoundVolume, {
    Logging::log(Logging::DEBUG, "setSoundVolume(%i)\r\n", e.Get<int>(2));
    extentity *ext = self.get()->staticEntity;
    assert(ext);
    if (!WorldSystem::loadingWorld) removeentity(ext);
    ext->attr4 = e.Get<int>(2);
    if (!WorldSystem::loadingWorld) addentity(ext);
    // finally reload sound, so everything gets applied
    self.get()->setSound(self.get()->soundName.c_str());
})
LUA_BIND_LE(setAttachments_raw, self.get()->setAttachments(e.Get<std::string>(2));)
LUA_BIND_LE(getAttachmentPosition, {
    vec& vp = self->getAttachmentPosition(e.Get<std::string>(2));
    e.Push(vp);
})
LUA_BIND_LE(setCanMove, self.get()->setCanMove(e.Get<bool>(2));)

// Extents

#define EXTENT_ACCESSORS(name, attribName) \
LUA_BIND_LE(get##name, { \
    extentity *ext = self.get()->staticEntity; \
    assert(ext); \
    e.Push(ext->attribName); \
}) \
LUA_BIND_LE(set##name, { \
    extentity *ext = self.get()->staticEntity; \
    assert(ext); \
    if (!WorldSystem::loadingWorld) removeentity(ext); /* Need to remove, then add, to the world on each change, if not during load. */ \
    ext->attribName = e.Get<int>(2); \
    if (!WorldSystem::loadingWorld) addentity(ext); \
}) \
LUA_BIND_LE(FAST_set##name, { \
    /* Fast version - no removeentity/addentity. Use with care! */ \
    extentity *ext = self.get()->staticEntity; \
    assert(ext); \
    ext->attribName = e.Get<int>(2); \
})

EXTENT_ACCESSORS(Attr1, attr1)
EXTENT_ACCESSORS(Attr2, attr2)
EXTENT_ACCESSORS(Attr3, attr3)
EXTENT_ACCESSORS(Attr4, attr4)

#define EXTENT_LE_ACCESSORS(name, attribName) \
LUA_BIND_LE(get##name, e.Push(self->attribName);) \
LUA_BIND_LE(set##name, { \
    Logging::log(Logging::DEBUG, "ACCESSOR: Setting %s to %f\r\n", #attribName, e.Get<double>(2)); \
    assert(self->staticEntity); \
    if (!WorldSystem::loadingWorld) removeentity(self->staticEntity); /* Need to remove, then add, to the octa world on each change. */ \
    self->attribName = e.Get<double>(2); \
    if (!WorldSystem::loadingWorld) addentity(self->staticEntity); \
})

EXTENT_LE_ACCESSORS(CollisionRadiusWidth, collisionRadiusWidth)
EXTENT_LE_ACCESSORS(CollisionRadiusHeight, collisionRadiusHeight)

// Add 'FAST' versions of accessors - no addentity/removeentity. Good to change e.g. particle parameters

LUA_BIND_LE(getExtent0_raw, {
    int arg2 = e.Get<int>(2);
    extentity *ext = self.get()->staticEntity;
    assert(ext);
    assert(arg2 >= 0 && arg2 <= 2);

    Logging::log(Logging::INFO, "getExtentO_raw(%d): %f\r\n", arg2, ext->o[arg2]);

    e.Push(ext->o[arg2]);
})

LUA_BIND_LE(setExtent0_raw, {
    extentity *ext = self.get()->staticEntity;
    assert(ext);

    removeentity(ext); /* Need to remove, then add, to the octa world on each change. */
    ext->o.x = e.Get<double>(2);
    ext->o.y = e.Get<double>(3);
    ext->o.z = e.Get<double>(4);
    addentity(ext);
})

// Dynents

#define DYNENT_ACCESSORS(name, type, attribName) \
LUA_BIND_LE(get##name, { \
    fpsent *d = (fpsent*)self.get()->dynamicEntity; \
    assert(d); \
    e.Push((type)d->attribName); \
}) \
LUA_BIND_LE(set##name, { \
    fpsent *d = (fpsent*)self.get()->dynamicEntity; \
    assert(d); \
    d->attribName = e.Get<type>(2); \
})

DYNENT_ACCESSORS(MaxSpeed, double, maxspeed)
DYNENT_ACCESSORS(Radius, double, radius)
DYNENT_ACCESSORS(EyeHeight, double, eyeheight)
DYNENT_ACCESSORS(Aboveeye, double, aboveeye)
DYNENT_ACCESSORS(Yaw, double, yaw)
DYNENT_ACCESSORS(Pitch, double, pitch)
DYNENT_ACCESSORS(Move, int, move)
DYNENT_ACCESSORS(Strafe, int, strafe)
DYNENT_ACCESSORS(Yawing, int, turn_move)
DYNENT_ACCESSORS(Pitching, int, look_updown_move)
DYNENT_ACCESSORS(Jumping, bool, jumping)
DYNENT_ACCESSORS(Blocked, bool, blocked)
DYNENT_ACCESSORS(MapDefinedPositionData, int, mapDefinedPositionData) // XXX Should be unsigned
DYNENT_ACCESSORS(ClientState, int, state);
DYNENT_ACCESSORS(PhysicalState, int, physstate);
DYNENT_ACCESSORS(InWater, int, inwater)
DYNENT_ACCESSORS(TimeInAir, int, timeinair)

// For dynents, 'o' is at their head, not their feet like static entities. We make this uniform by
// letting lua specify a feet position, and we work relative to their height - add to
// assignments, subtract from readings
LUA_BIND_LE(getDynent0_raw, {
    int arg2 = e.Get<int>(2);
    fpsent *d = (fpsent*)self.get()->dynamicEntity;
    assert(d);
    assert(arg2 >= 0 && arg2 <= 2);

    if (arg2 != 2) {
        e.Push(d->o[arg2]);
    } else {
        e.Push(d->o.z - d->eyeheight);// - d->aboveeye);
    }
})

LUA_BIND_LE(setDynent0_raw, {
    fpsent *d = (fpsent*)self.get()->dynamicEntity;
    assert(d);

    d->o.x = e.Get<double>(2);
    d->o.y = e.Get<double>(3);
    d->o.z = e.Get<double>(4) + d->eyeheight;// + d->aboveeye;

    // Also set 'newpos', otherwise this change may get overwritten
    d->newpos = d->o;

    d->resetinterp(); // No need to interpolate to last position - just jump

    Logging::log(Logging::INFO, "(%d).setDynentO(%f, %f, %f)\r\n", d->uniqueId, d->o.x, d->o.y, d->o.z);
})

LUA_BIND_LE(getDynentVel_raw, {
    int arg2 = e.Get<int>(2);
    fpsent *d = (fpsent*)self.get()->dynamicEntity;
    assert(d);
    assert(arg2 >= 0 && arg2 <= 2);

    e.Push(d->vel[arg2]);
})

LUA_BIND_LE(setDynentVel_raw, {
    fpsent *d = (fpsent*)self.get()->dynamicEntity;
    assert(d);

    d->vel.x = e.Get<double>(2);
    d->vel.y = e.Get<double>(3);
    d->vel.z = e.Get<double>(4);
})

LUA_BIND_LE(getDynentFalling_raw, {
    int arg2 = e.Get<int>(2);
    fpsent *d = (fpsent*)self.get()->dynamicEntity;
    assert(d);
    assert(arg2 >= 0 && arg2 <= 2);

    e.Push(d->falling[arg2]);
})

LUA_BIND_LE(setDynentFalling_raw, {
    fpsent *d = (fpsent*)self.get()->dynamicEntity;
    assert(d);

    d->falling.x = e.Get<double>(2);
    d->falling.y = e.Get<double>(3);
    d->falling.z = e.Get<double>(4);
})

// Geometry utilities

LUA_BIND_DEF(rayLos, {
    vec a(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    vec b(e.Get<double>(4), e.Get<double>(5), e.Get<double>(6));
    vec target;

    bool ret = raycubelos(a, b, target);
    e.Push(ret);
})

LUA_BIND_DEF(rayPos, {
    vec o(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    vec ray(e.Get<double>(4), e.Get<double>(5), e.Get<double>(6));
    vec hitpos(0);
    e.Push(raycubepos(o, ray, hitpos, e.Get<double>(7), RAY_CLIPMAT|RAY_POLY));
})

LUA_BIND_DEF(rayFloor, {
    vec o(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    vec floor(0);
    e.Push(rayfloor(o, floor, 0, e.Get<double>(4)));
})

// World

LUA_BIND_DEF(isColliding, {
    vec pos(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    e.Push(PhysicsManager::getEngine()->isColliding(
        pos,
        e.Get<double>(4),
        e.Get<int>(5) != -1 ? LogicSystem::getLogicEntity(e.Get<int>(5)).get() : NULL)
    ); // TODO: Make faster, avoid this lookup
})

LUA_BIND_DEF(setGravity, {
    if (PhysicsManager::hasEngine())
        PhysicsManager::getEngine()->setGravity(e.Get<double>(1));
    else
    {
        Logging::log(Logging::DEBUG, "Setting gravity using sauer system, as no physics engine\r\n");
        GRAVITY = e.Get<double>(1);
    }
})

LUA_BIND_DEF(getMaterial, e.Push(lookupmaterial(vec(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3))));)

// Textures

LUA_BIND_CLIENT(convertPNGtoDDS, {
    std::string arg1 = e.Get<std::string>(1);
    std::string arg2 = e.Get<std::string>(2);
    assert(Utility::validateRelativePath(arg1));
    assert(Utility::validateRelativePath(arg2));
    IntensityTexture::convertPNGtoDDS(arg1, arg2);
})

LUA_BIND_CLIENT(combineImages, {
    std::string arg1 = e.Get<std::string>(1);
    std::string arg2 = e.Get<std::string>(2);
    std::string arg3 = e.Get<std::string>(3);
    assert(Utility::validateRelativePath(arg1));
    assert(Utility::validateRelativePath(arg2));
    assert(Utility::validateRelativePath(arg3));
    IntensityTexture::combineImages(arg1, arg2, arg3);
})

// Sounds

LUA_BIND_CLIENT(playSoundByName, {
    vec loc(e.Get<double>(2), e.Get<double>(3), e.Get<double>(4));
    if (loc.x || loc.y || loc.z)
        playsoundname(e.Get<const char*>(1), &loc, e.Get<int>(5));
    else
        playsoundname(e.Get<const char*>(1));
})
LUA_BIND_STD_CLIENT(stopSoundByName, stopsoundbyid, getsoundid(e.Get<const char*>(1), e.Get<int>(2)))
LUA_BIND_STD_CLIENT(music, startmusic, (char*)e.Get<const char*>(1), (char*)"Sound.musicCallback()")
LUA_BIND_CLIENT(preloadSound, {
    std::string str = "preloading sound '";
    str += e.Get<std::string>(1);
    str += "'...";
    renderprogress(0, str.c_str());

    e.Push(preload_sound((char*)e.Get<const char*>(1), min(e.Get<int>(2), 100)));
})

#ifdef CLIENT
LUA_BIND_STD(playSound, playsound, e.Get<int>(1)) // TODO: sound position
#else
LUA_BIND_STD(playSound, MessageSystem::send_SoundToClients, -1, e.Get<int>(1), -1)
#endif

// Effects

LUA_BIND_CLIENT(addDecal, {
    vec  center(e.Get<double>(2), e.Get<double>(3), e.Get<double>(4));
    vec  surface(e.Get<double>(5), e.Get<double>(6), e.Get<double>(7));
    bvec color(e.Get<int>(9), e.Get<int>(10), e.Get<int>(11));

    adddecal(e.Get<int>(1), center, surface, e.Get<double>(8), color, e.Get<int>(12));
})

LUA_BIND_CLIENT(particleSplash, {
    if (e.Get<int>(1) == PART_BLOOD && !GETIV(blood)) return;
    vec p(e.Get<double>(4), e.Get<double>(5), e.Get<double>(6));
    particle_splash(
        e.Get<int>(1),
        e.Get<int>(2),
        e.Get<int>(3),
        p,
        e.Get<int>(7),
        e.Get<double>(8),
        e.Get<int>(9),
        e.Get<int>(10),
        e.Get<bool>(11),
        e.Get<int>(12),
        e.Get<bool>(13),
        e.Get<int>(14)
    );
})

LUA_BIND_CLIENT(particleSplashRegular, {
    if (e.Get<int>(1) == PART_BLOOD && !GETIV(blood)) return;
    vec p(e.Get<double>(4), e.Get<double>(5), e.Get<double>(6));
    regular_particle_splash(
        e.Get<int>(1),
        e.Get<int>(2),
        e.Get<int>(3),
        p,
        e.Get<int>(7),
        e.Get<double>(8),
        e.Get<int>(9),
        e.Get<int>(10),
        e.Get<int>(11),
        e.Get<bool>(12),
        e.Get<int>(13)
    );
})

LUA_BIND_CLIENT(particleFireball, {
    vec dest(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    particle_fireball(dest, e.Get<double>(4), e.Get<int>(5), e.Get<int>(6), e.Get<int>(7), e.Get<double>(8));
})

LUA_BIND_CLIENT(particleExplodeSplash, {
    vec o(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    particle_explodesplash(o, e.Get<int>(4), e.Get<int>(5), e.Get<int>(6), e.Get<int>(7), e.Get<int>(8), e.Get<int>(9));
})

LUA_BIND_CLIENT(particleFlare, {
    vec p(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    vec dest(e.Get<double>(4), e.Get<double>(5), e.Get<double>(6));
    if (e.Get<int>(12) < 0)
        particle_flare(p, dest, e.Get<int>(7), e.Get<int>(8), e.Get<int>(9), e.Get<double>(10), NULL, e.Get<int>(11));
    else
    {
        LogicEntityPtr owner = LogicSystem::getLogicEntity(e.Get<int>(12));
        assert(owner.get()->dynamicEntity);
        particle_flare(p, dest, e.Get<int>(7), e.Get<int>(8), e.Get<int>(9), e.Get<double>(10), (fpsent*)(owner.get()->dynamicEntity), e.Get<int>(11));
    }
})

LUA_BIND_CLIENT(particleFlyingFlare, {
    vec p(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    vec dest(e.Get<double>(4), e.Get<double>(5), e.Get<double>(6));
    particle_flying_flare(p, dest, e.Get<int>(7), e.Get<int>(8), e.Get<int>(9), e.Get<double>(10), e.Get<int>(11));
})

LUA_BIND_CLIENT(particleTrail, {
    vec from(e.Get<double>(3), e.Get<double>(4), e.Get<double>(5));
    vec to(e.Get<double>(6), e.Get<double>(7), e.Get<double>(8));
    particle_trail(e.Get<int>(1), e.Get<int>(2), from, to, e.Get<int>(9), e.Get<double>(10), e.Get<int>(11), e.Get<bool>(12));
})

LUA_BIND_CLIENT(particleFlame, {
    regular_particle_flame(
        e.Get<int>(1),
        vec(e.Get<double>(2), e.Get<double>(3), e.Get<double>(4)),
        e.Get<double>(5),
        e.Get<double>(6),
        e.Get<int>(7),
        e.Get<int>(8),
        e.Get<double>(9),
        e.Get<double>(10),
        e.Get<double>(11),
        e.Get<int>(12)
    );
})

LUA_BIND_CLIENT(addDynlight, {
    vec o(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    vec color(float(e.Get<double>(5))/255.0, float(e.Get<double>(6))/255.0, float(e.Get<double>(7))/255.0);
    vec initcolor(float(e.Get<double>(12))/255.0, float(e.Get<double>(13))/255.0, float(e.Get<double>(14))/255.0);

    LightControl::queueDynamicLight(o, e.Get<double>(4), color, e.Get<int>(8), e.Get<int>(9), e.Get<int>(10), e.Get<double>(11), initcolor, NULL);
})

LUA_BIND_CLIENT(spawnDebris, {
    vec v(e.Get<double>(2), e.Get<double>(3), e.Get<double>(4));
    vec debrisvel(e.Get<double>(6), e.Get<double>(7), e.Get<double>(8));

    LogicEntityPtr owner = LogicSystem::getLogicEntity(e.Get<int>(9));
    assert(owner->dynamicEntity);
    FPSClientInterface::spawnDebris(e.Get<int>(1), v, e.Get<int>(5), debrisvel, (dynent*)(owner->dynamicEntity));
})

LUA_BIND_CLIENT(particleMeter, {
    vec s(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    particle_meter(s, e.Get<double>(4), e.Get<int>(5), e.Get<int>(6));
})

LUA_BIND_CLIENT(particleText, {
    vec s(e.Get<double>(1), e.Get<double>(2), e.Get<double>(3));
    particle_textcopy(s, e.Get<const char*>(4), e.Get<int>(5), e.Get<int>(6), e.Get<int>(7), e.Get<double>(8), e.Get<int>(9));
})

LUA_BIND_CLIENT(clientDamageEffect, {
    ((fpsent*)player)->damageroll(e.Get<int>(1));
    damageblend(e.Get<int>(2));
})

LUA_BIND_CLIENT(showHUDRect,  ClientSystem::addHUDRect (e.Get<double>(1), e.Get<double>(2), e.Get<double>(3), e.Get<double>(4), e.Get<int>(5), e.Get<double>(6));)
LUA_BIND_CLIENT(showHUDImage, ClientSystem::addHUDImage(e.Get<std::string>(1), e.Get<double>(2), e.Get<double>(3), e.Get<double>(4), e.Get<double>(5), e.Get<int>(6), e.Get<double>(7));)

// text, x, y, scale, color
LUA_BIND_CLIENT(showHUDText, ClientSystem::addHUDText(e.Get<std::string>(1), e.Get<double>(2), e.Get<double>(3), e.Get<double>(4), e.Get<int>(5));)

// Messages

using namespace MessageSystem;

LUA_BIND_DEF(PersonalServerMessage, send_PersonalServerMessage(e.Get<int>(1), e.Get<int>(2), e.Get<std::string>(3), e.Get<std::string>(4));)
LUA_BIND_DEF(ParticleSplashToClients, send_ParticleSplashToClients(e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<int>(4), e.Get<double>(5), e.Get<double>(6), e.Get<double>(7));)
LUA_BIND_DEF(ParticleSplashRegularToClients, send_ParticleSplashToClients(e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<int>(4), e.Get<double>(5), e.Get<double>(6), e.Get<double>(7));)
LUA_BIND_DEF(SoundToClientsByName, send_SoundToClientsByName(e.Get<int>(1), e.Get<double>(2), e.Get<double>(3), e.Get<double>(4), e.Get<std::string>(5), e.Get<int>(6));)
LUA_BIND_DEF(StateDataChangeRequest, send_StateDataChangeRequest(e.Get<int>(1), e.Get<int>(2), e.Get<std::string>(3));)
LUA_BIND_DEF(UnreliableStateDataChangeRequest, send_UnreliableStateDataChangeRequest(e.Get<int>(1), e.Get<int>(2), e.Get<std::string>(3));)
LUA_BIND_DEF(NotifyNumEntities, send_NotifyNumEntities(e.Get<int>(1), e.Get<int>(2));)
LUA_BIND_DEF(LogicEntityCompleteNotification, send_LogicEntityCompleteNotification(e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<std::string>(4), e.Get<std::string>(5));)
LUA_BIND_DEF(LogicEntityRemoval, send_LogicEntityRemoval(e.Get<int>(1), e.Get<int>(2));)
LUA_BIND_DEF(StateDataUpdate, send_StateDataUpdate(e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<std::string>(4), e.Get<int>(5));)
LUA_BIND_DEF(UnrealiableStateDataUpdate, send_UnreliableStateDataUpdate(e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<std::string>(4), e.Get<int>(5));)
LUA_BIND_DEF(DoClick, send_DoClick(e.Get<int>(1), e.Get<int>(2), e.Get<double>(3), e.Get<double>(4), e.Get<double>(5), e.Get<int>(6));)
LUA_BIND_DEF(ExtentCompleteNotification, send_ExtentCompleteNotification(
    e.Get<int>(1),
    e.Get<int>(2),
    e.Get<std::string>(3),
    e.Get<std::string>(4),
    e.Get<double>(5),
    e.Get<double>(6),
    e.Get<double>(7),
    e.Get<int>(8),
    e.Get<int>(9),
    e.Get<int>(10),
    e.Get<int>(11)
);)

// File access

LUA_BIND_DEF(readFile, {
    try
    {
        REFLECT_PYTHON( read_file_safely );

        boost::python::object data = read_file_safely(e.Get<std::string>(1));
        std::string text = boost::python::extract<std::string>(data);

        e.Push(text);
    }
    catch(boost::python::error_already_set const &)
    {
        printf("Error in Python execution of embedded read_file_safely\r\n");
        PyErr_Print();
        assert(0 && "Halting on Python error");
    }
})

// Mapping

LUA_BIND_DEF(textureReset, {
    texturereset(0);
})
LUA_BIND_DEF(texture, {
    // XXX: arg7 may not be given, in which case it is undefined, and turns into 0.
    texture(e.Get<const char*>(1), e.Get<const char*>(2), e.Get<int>(3), e.Get<int>(4), e.Get<int>(5), (float)e.Get<double>(6), e.Get<int>(7));
})
LUA_BIND_DEF(mapmodelReset, mapmodelreset(e.Get<int*>(1));)
LUA_BIND_DEF(mapmodel, mmodel(e.Get<char*>(1));)
LUA_BIND_DEF(numMapModels, e.Push(mapmodels.length());)
LUA_BIND_STD(clearModel, clearmodel, e.Get<char*>(1))
LUA_BIND_DEF(autograss, autograss(e.Get<char*>(1));)
LUA_BIND_STD_CLIENT(texLayer, texlayer, e.Get<int*>(1), (char*)"", new int(0), new float(0))
LUA_BIND_STD_CLIENT(texAlpha, texalpha, e.Get<float*>(1), e.Get<float*>(2))
LUA_BIND_STD_CLIENT(texColor, texcolor, e.Get<float*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD_CLIENT(texScroll, texscroll, e.Get<float*>(1), e.Get<float*>(2))
LUA_BIND_STD_CLIENT(texFFenv, texffenv, e.Get<int*>(1))
LUA_BIND_STD(materialReset, materialreset)

// shaders

LUA_BIND_STD_CLIENT(shader, shader, e.Get<int*>(1), e.Get<char*>(2), e.Get<char*>(3), e.Get<char*>(4))
LUA_BIND_STD_CLIENT(variantShader, variantshader, e.Get<int*>(1), e.Get<char*>(2), e.Get<int*>(3), e.Get<char*>(4), e.Get<char*>(5))
LUA_BIND_STD_CLIENT(setShader, setshader, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(altShader, altshader, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD_CLIENT(fastShader, fastshader, e.Get<char*>(1), e.Get<char*>(2), e.Get<int*>(3))
LUA_BIND_STD_CLIENT(deferShader, defershader, e.Get<int*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(forceShader, useshaderbyname, e.Get<char*>(1))

LUA_BIND_STD_CLIENT(isShaderDefined, isshaderdefined, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(isShaderNative, isshadernative, e.Get<char*>(1))

LUA_BIND_STD_CLIENT(setVertexParam, addshaderparam, NULL, SHPARAM_VERTEX, e.Get<int>(1), e.Get<float>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5))
LUA_BIND_STD_CLIENT(setPixelParam, addshaderparam, NULL, SHPARAM_VERTEX, e.Get<int>(1), e.Get<float>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5))
LUA_BIND_STD_CLIENT(setUniformParam, addshaderparam, e.Get<char*>(1), SHPARAM_UNIFORM, -1, e.Get<float>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5))
LUA_BIND_STD_CLIENT(setShaderParam, addshaderparam, e.Get<char*>(1), SHPARAM_LOOKUP, -1, e.Get<float>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5))
LUA_BIND_STD_CLIENT(defVertexParam, addshaderparam, e.Get<char*>(1)[0] ? e.Get<char*>(1) : NULL, SHPARAM_VERTEX, e.Get<int>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5), e.Get<float>(6))
LUA_BIND_STD_CLIENT(defPixelParam, addshaderparam, e.Get<char*>(1)[0] ? e.Get<char*>(1) : NULL, SHPARAM_PIXEL, e.Get<int>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5), e.Get<float>(6))
LUA_BIND_STD_CLIENT(defUniformParam, addshaderparam, e.Get<char*>(1), SHPARAM_UNIFORM, -1, e.Get<float>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5))

LUA_BIND_STD_CLIENT(addPostFX, addpostfx, e.Get<const char*>(1), e.Get<int>(2), e.Get<int>(3), e.Get<const char*>(4), e.Get<float>(5), e.Get<float>(6), e.Get<float>(7), e.Get<float>(8))
LUA_BIND_STD_CLIENT(setPostFX, setpostfx, e.Get<const char*>(1), e.Get<float>(2), e.Get<float>(3), e.Get<float>(4), e.Get<float>(5))
LUA_BIND_STD_CLIENT(clearPostFX, clearpostfx)

// Models

LUA_BIND_STD(mdlName, mdlname)

LUA_BIND_STD(mdlAlphatest, mdlalphatest, e.Get<float*>(1))
LUA_BIND_STD(mdlAlphablend, mdlalphablend, e.Get<int*>(1))
LUA_BIND_STD(mdlAlphadepth, mdlalphadepth, e.Get<int*>(1))

LUA_BIND_STD(mdlBb, mdlbb, e.Get<float*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(mdlExtendbb, mdlextendbb, e.Get<float*>(1), e.Get<float*>(2), e.Get<float*>(3))

LUA_BIND_STD(mdlScale, mdlscale, e.Get<int*>(1))
LUA_BIND_STD(mdlSpec, mdlspec, e.Get<int*>(1))
LUA_BIND_STD(mdlGlow, mdlglow, e.Get<int*>(1))
LUA_BIND_STD(mdlGlare, mdlglare, e.Get<float*>(1), e.Get<float*>(2))
LUA_BIND_STD(mdlAmbient, mdlambient, e.Get<int*>(1))
LUA_BIND_STD(mdlCullface, mdlcullface, e.Get<int*>(1))
LUA_BIND_STD(mdlDepthoffset, mdldepthoffset, e.Get<int*>(1))
LUA_BIND_STD(mdlFullbright, mdlfullbright, e.Get<float*>(1))
LUA_BIND_STD(mdlSpin, mdlspin, e.Get<float*>(1), e.Get<float*>(2))
LUA_BIND_STD(mdlEnvmap, mdlenvmap, e.Get<float*>(1), e.Get<float*>(2), e.Get<char*>(3))

LUA_BIND_STD(mdlShader, mdlshader, e.Get<char*>(1))

LUA_BIND_STD(mdlCollisionsOnlyForTriggering, mdlcollisionsonlyfortriggering, e.Get<int*>(1))

LUA_BIND_STD(mdlTrans, mdltrans, e.Get<float*>(1), e.Get<float*>(2), e.Get<float*>(3))

LUA_BIND_STD(modelYaw, mdlyaw, e.Get<float*>(1))
LUA_BIND_STD(modelPitch, mdlpitch, e.Get<float*>(1))
LUA_BIND_STD(modelShadow, mdlshadow, e.Get<int*>(1))
LUA_BIND_STD(modelCollide, mdlcollide, e.Get<int*>(1))
LUA_BIND_STD(modelPerEntityCollisionBoxes, mdlperentitycollisionboxes, e.Get<int*>(1))
LUA_BIND_STD(modelEllipseCollide, mdlellipsecollide, e.Get<int*>(1))

LUA_BIND_STD(objLoad, objload, e.Get<char*>(1), e.Get<float*>(2))

LUA_BIND_STD(objSkin, objskin, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(objBumpmap, objbumpmap, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD(objEnvmap, objenvmap, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(objSpec, objspec, e.Get<char*>(1), e.Get<int*>(2))

LUA_BIND_STD(objPitch, objpitch, e.Get<float*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4))
LUA_BIND_STD(objAmbient, objambient, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(objGlow, objglow, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(objGlare, objglare, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(objAlphatest, objalphatest, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(objAlphablend, objalphablend, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(objCullface, objcullface, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(objFullbright, objfullbright, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(objShader, objshader, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(objScroll, objscroll, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(objNoclip, objnoclip, e.Get<char*>(1), e.Get<int*>(2))

LUA_BIND_STD(md5Dir, setmd5dir, e.Get<char*>(1))
LUA_BIND_STD(md5Load, md5load, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3))
LUA_BIND_STD(md5Tag, md5tag, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(md5Pitch, md5pitch, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(md5Adjust, md5adjust, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6), e.Get<float*>(7))
LUA_BIND_STD(md5Skin, md5skin, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(md5Spec, md5spec, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(md5Ambient, md5ambient, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(md5Glow, md5glow, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(md5Glare, md5glare, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(md5Alphatest, md5alphatest, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(md5Alphablend, md5alphablend, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(md5Cullface, md5cullface, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(md5Envmap, md5envmap, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(md5Bumpmap, md5bumpmap, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD(md5Fullbright, md5fullbright, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(md5Shader, md5shader, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(md5Scroll, md5scroll, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(md5Animpart, md5animpart, e.Get<char*>(1))
LUA_BIND_STD(md5Anim, md5anim, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3), e.Get<int*>(4))
LUA_BIND_STD(md5Link, md5link, e.Get<int*>(1), e.Get<int*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6))
LUA_BIND_STD(md5Noclip, md5noclip, e.Get<char*>(1), e.Get<int*>(2))

LUA_BIND_STD(iqmDir, setiqmdir, e.Get<char*>(1))
LUA_BIND_STD(iqmLoad, iqmload, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(iqmTag, iqmtag, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(iqmPitch, iqmpitch, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(iqmAdjust, iqmadjust, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6), e.Get<float*>(7))
LUA_BIND_STD(iqmSkin, iqmskin, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(iqmSpec, iqmspec, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(iqmAmbient, iqmambient, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(iqmGlow, iqmglow, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(iqmGlare, iqmglare, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(iqmAlphatest, iqmalphatest, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(iqmAlphablend, iqmalphablend, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(iqmCullface, iqmcullface, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(iqmEnvmap, iqmenvmap, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(iqmBumpmap, iqmbumpmap, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD(iqmFullbright, iqmfullbright, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(iqmShader, iqmshader, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(iqmScroll, iqmscroll, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(iqmAnimpart, iqmanimpart, e.Get<char*>(1))
LUA_BIND_STD(iqmAnim, iqmanim, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3), e.Get<int*>(4))
LUA_BIND_STD(iqmLink, iqmlink, e.Get<int*>(1), e.Get<int*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6))
LUA_BIND_STD(iqmNoclip, iqmnoclip, e.Get<char*>(1), e.Get<int*>(2))

LUA_BIND_STD(smdDir, setsmddir, e.Get<char*>(1))
LUA_BIND_STD(smdLoad, smdload, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(smdTag, smdtag, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(smdPitch, smdpitch, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(smdAdjust, smdadjust, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6), e.Get<float*>(7))
LUA_BIND_STD(smdSkin, smdskin, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5))
LUA_BIND_STD(smdSpec, smdspec, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(smdAmbient, smdambient, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(smdGlow, smdglow, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(smdGlare, smdglare, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(smdAlphatest, smdalphatest, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(smdAlphablend, smdalphablend, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(smdCullface, smdcullface, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD(smdEnvmap, smdenvmap, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(smdBumpmap, smdbumpmap, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD(smdFullbright, smdfullbright, e.Get<char*>(1), e.Get<float*>(2))
LUA_BIND_STD(smdShader, smdshader, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD(smdScroll, smdscroll, e.Get<char*>(1), e.Get<float*>(2), e.Get<float*>(3))
LUA_BIND_STD(smdAnimpart, smdanimpart, e.Get<char*>(1))
LUA_BIND_STD(smdAnim, smdanim, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3), e.Get<int*>(4))
LUA_BIND_STD(smdLink, smdlink, e.Get<int*>(1), e.Get<int*>(2), e.Get<char*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6))
LUA_BIND_STD(smdNoclip, smdnoclip, e.Get<char*>(1), e.Get<int*>(2))

LUA_BIND_STD(rdVert, rdvert, e.Get<float*>(1), e.Get<float*>(2), e.Get<float*>(3), e.Get<float*>(4));
LUA_BIND_STD(rdEye, rdeye, e.Get<int*>(1));
LUA_BIND_STD(rdTri, rdtri, e.Get<int*>(1), e.Get<int*>(2), e.Get<int*>(3));
LUA_BIND_STD(rdJoint, rdjoint, e.Get<int*>(1), e.Get<int*>(2), e.Get<char*>(3), e.Get<char*>(4), e.Get<char*>(5));
LUA_BIND_STD(rdLimitDist, rdlimitdist, e.Get<int*>(1), e.Get<int*>(2), e.Get<float*>(3), e.Get<float*>(4));
LUA_BIND_STD(rdLimitRot, rdlimitrot, e.Get<int*>(1), e.Get<int*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<float*>(5), e.Get<float*>(6), e.Get<float*>(7));
LUA_BIND_STD(rdAnimJoints, rdanimjoints, e.Get<int*>(1));

// Keyboard

LUA_BIND_DEF(isKeyDown, e.Push(getkeydown());)
LUA_BIND_DEF(isKeyUp, e.Push(getkeyup());)
LUA_BIND_DEF(isMouseDown, e.Push(getmousedown());)
LUA_BIND_DEF(isMouseUp, e.Push(getmouseup());)

// Components

LUA_BIND_DEF(signalComponent, {
    try
    {
        REFLECT_PYTHON( signal_signal_component );
        boost::python::object data = signal_signal_component(e.Get<std::string>(1), e.Get<std::string>(2));
        e.Push(boost::python::extract<std::string>(data));
    }
    catch(boost::python::error_already_set const &)
    {
        printf("Error in signalling python component initialization\r\n");
        PyErr_Print();
        assert(0 && "Halting on Python error");
    }
})

// Models

LUA_BIND_STD(preloadModel, preloadmodel, e.Get<const char*>(1))
LUA_BIND_DEF(reloadModel, {
    clearmodel(e.Get<char*>(1));
    if (!loadmodel(e.Get<char*>(1))) e.Error("Cannot load model.");
});

// HUD

LUA_BIND_CLIENT(getTargetPosition, {
    TargetingControl::determineMouseTarget(true); // Force a determination, if needed
    e.Push(TargetingControl::targetPosition);
})
LUA_BIND_CLIENT(getTargetEntity, {
    TargetingControl::determineMouseTarget(true); // Force a determination, if needed
    LogicEntityPtr target = TargetingControl::targetLogicEntity;
    if (target.get() && !target->isNone() && target->luaRef >= 0)
        e.GetRef(target->luaRef);
    else
        e.Push();
})

// Rendering

#ifdef CLIENT
static int oldThirdperson = -1;

void prepareRagdoll(int& anim, LogicEntityPtr self)
{
    if (anim&ANIM_RAGDOLL)
    {
//        if (!ragdoll || loadmodel(mdl);
        fpsent* fpsEntity = (fpsent*)self->dynamicEntity;

        if (fpsEntity->clientnum == ClientSystem::playerNumber)
        {
            if (oldThirdperson == -1 && GETIV(thirdperson) == 0)
            {
                oldThirdperson = GETIV(thirdperson);
                SETV(thirdperson, 1);
            }
        }

        if (fpsEntity->ragdoll || !GETIV(ragdoll) || !PhysicsManager::getEngine()->prepareRagdoll(self))
        {
            anim &= ~ANIM_RAGDOLL;
            engine.GetRef(self.get()->luaRef).GetTableRaw("setLocalAnimation").PushIndex(-2).Push(anim).Call(2, 0);
            engine.ClearStack(1);
        }
    }
    else
    {
        if (self->dynamicEntity)
        {
            fpsent* fpsEntity = (fpsent*)self->dynamicEntity;

            if (fpsEntity->clientnum == ClientSystem::playerNumber && oldThirdperson != -1)
            {
                SETV(thirdperson, oldThirdperson);
                oldThirdperson = -1;
            }
        }
    }
}

fpsent* getProxyFpsEntityLua(LogicEntityPtr self)
{
    engine.GetRef(self.get()->luaRef).GetTableRaw("renderingHashHint");
    if (!engine.Is<void>(-1))
    {
        static bool initialized = false;
        static fpsent* fpsEntitiesForRendering[1024];

        if (!initialized)
        {
            for (int i = 0; i < 1024; i++)
                fpsEntitiesForRendering[i] = new fpsent;

            initialized = true;
        }

        int renderingHashHint = engine.Get<int>(-1);
        engine.ClearStack(2);
        renderingHashHint = renderingHashHint & 1023;
        assert(renderingHashHint >= 0 && renderingHashHint < 1024);
        return fpsEntitiesForRendering[renderingHashHint];
    }
    else
    {
        engine.ClearStack(2);
        return NULL;
    }
}

#define PREP_RENDER_MODEL \
    int anim = e.Get<int>(3); \
    prepareRagdoll(anim, self); \
    vec o(e.Get<float>(4), e.Get<float>(5), e.Get<float>(6)); \
    fpsent *fpsEntity = NULL; \
    if (self->dynamicEntity) \
        fpsEntity = (fpsent*)self->dynamicEntity; \
    else \
        fpsEntity = getProxyFpsEntityLua(self);

LUA_BIND_LE(renderModel2, {
    PREP_RENDER_MODEL
    rendermodel(NULL,
        e.Get<const char*>(2),
        anim, o, self,
        e.Get<float>(7),
        e.Get<float>(8),
        e.Get<float>(9),
        e.Get<int>(10),
        fpsEntity,
        self->attachments,
        e.Get<int>(11)
    );
})

LUA_BIND_LE(renderModel3, {
    PREP_RENDER_MODEL
    quat rotation(e.Get<float>(12), e.Get<float>(13), e.Get<float>(14), e.Get<float>(15));
    rendermodel(NULL,
        e.Get<const char*>(2),
        anim, o, self,
        e.Get<float>(7),
        e.Get<float>(8),
        e.Get<float>(9),
        e.Get<int>(10),
        fpsEntity,
        self->attachments,
        e.Get<int>(11),
        0, 1, rotation
    );
})
#else
LUA_BIND_DUMMY(renderModel2)
LUA_BIND_DUMMY(renderModel3)
#endif

// Network

LUA_BIND_STD_CLIENT(connect, ClientSystem::connect, e.Get<std::string>(1), e.Get<int>(2))

// Camera

LUA_BIND_CLIENT(forceCamera, {
    vec position(e.Get<float>(1), e.Get<float>(2), e.Get<float>(3));
    CameraControl::forceCamera(position, e.Get<float>(4), e.Get<float>(5), e.Get<float>(6), e.Get<float>(7));
})
LUA_BIND_CLIENT(forcePosition, {
    vec position(e.Get<float>(1), e.Get<float>(2), e.Get<float>(3));
    CameraControl::forcePosition(position);
})
LUA_BIND_STD_CLIENT(forceYaw, CameraControl::forceYaw, e.Get<float>(1))
LUA_BIND_STD_CLIENT(forcePitch, CameraControl::forcePitch, e.Get<float>(1))
LUA_BIND_STD_CLIENT(forceRoll, CameraControl::forceRoll, e.Get<float>(1))
LUA_BIND_STD_CLIENT(forceFov, CameraControl::forceFov, e.Get<float>(1))
LUA_BIND_STD_CLIENT(resetCamera, CameraControl::positionCamera, CameraControl::getCamera())
LUA_BIND_CLIENT(getCamera, {
    physent *camera = CameraControl::getCamera();
    e.NewTable()
        .SetTable("position", camera->o)
        .SetTable("yaw", camera->yaw)
        .SetTable("pitch", camera->pitch)
        .SetTable("roll", camera->roll);
})
LUA_BIND_CLIENT(getCameraPosition, {
    physent *camera = CameraControl::getCamera();
    e.Push(camera->o);
})

// Editing

LUA_BIND_STD(editing_getWorldSize, e.Push, EditingSystem::getWorldSize())
LUA_BIND_STD(editing_getGridSize, e.Push, 1<<GETIV(gridpower))
LUA_BIND_STD(editing_eraseGeometry, EditingSystem::eraseGeometry)
LUA_BIND_STD(editing_createCube, EditingSystem::createCube, e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<int>(4))
LUA_BIND_STD(editing_deleteCube, EditingSystem::deleteCube, e.Get<int>(1), e.Get<int>(2), e.Get<int>(3), e.Get<int>(4))
LUA_BIND_STD(editing_setCubeTexture, EditingSystem::setCubeTexture,
    e.Get<int>(1),
    e.Get<int>(2),
    e.Get<int>(3),
    e.Get<int>(4),
    e.Get<int>(5),
    e.Get<int>(6)
)
LUA_BIND_STD(editing_setCubeMaterial, EditingSystem::setCubeMaterial,
    e.Get<int>(1),
    e.Get<int>(2),
    e.Get<int>(3),
    e.Get<int>(4),
    e.Get<int>(5)
)
LUA_BIND_STD(editing_pushCubeCorner, EditingSystem::pushCubeCorner,
    e.Get<int>(1),
    e.Get<int>(2),
    e.Get<int>(3),
    e.Get<int>(4),
    e.Get<int>(5),
    e.Get<int>(6),
    e.Get<int>(7)
)
LUA_BIND_DEF(editing_getSelectedEntity, {
    LogicEntityPtr ret = EditingSystem::getSelectedEntity();
    if (ret.get() && !ret->isNone() && ret->luaRef >= 0) e.GetRef(ret.get()->luaRef);
    else e.Push();
})
LUA_BIND_STD(renderProgress, renderprogress, e.Get<float>(1), e.Get<const char*>(2))
LUA_BIND_STD(getMapversion, e.Push, GETIV(mapversion))

// Models

LUA_BIND_DEF(modelBoundingBox, {
    model* theModel = loadmodel(e.Get<const char*>(1));
    if (!theModel)
    {
        e.Push();
        return;
    }
    vec center;
    vec radius;
    theModel->boundbox(0, center, radius);

    e.NewTable().SetTable("center", center).SetTable("radius", radius);
});

LUA_BIND_DEF(modelCollisionBox, {
    model* theModel = loadmodel(e.Get<const char*>(1));
    if (!theModel)
    {
        e.Push();
        return;
    }
    vec center;
    vec radius;
    theModel->collisionbox(0, center, radius);

    e.NewTable().SetTable("center", center).SetTable("radius", radius);
});

LUA_BIND_DEF(modelMesh, {
    model* theModel = loadmodel(e.Get<const char*>(1));
    if (!theModel)
    {
        e.Push();
        return;
    }

    vector<BIH::tri> tris2[2];
    theModel->gentris(0, tris2);
    vector<BIH::tri>& tris = tris2[0];

    e.NewTable().SetTable("length", tris.length());
    for (int i = 0; i < tris.length(); i++)
    {
        BIH::tri& bt = tris[i];

        e.Push(Utility::toString(i))
            .NewTable()
            .SetTable("a", bt.a)
            .SetTable("b", bt.b)
            .SetTable("c", bt.c)
        .SetTable();
    }
});

// NPCs/bots

LUA_BIND_SERVER(addNPC, {
    int _ref = NPC::add(e.Get<std::string>(1));
    if (_ref >= 0)
        e.GetRef(_ref);
    else
        e.Push();
})

#ifdef SERVER
LUA_BIND_LE(removeNPC, {
    fpsent *fpsEntity = (fpsent*)(self.get()->dynamicEntity);
    NPC::remove(fpsEntity->clientnum);
})
#else
LUA_BIND_DUMMY(removeNPC)
#endif

// data/ directory embeds, this is client-only, so we put it in ifdef. For server, they're just dummies
// dummies are needed because we don't want to check further in CAPIExtras.

LUA_BIND_STD_CLIENT(keymap, keymap, e.Get<int*>(1), e.Get<char*>(2))
LUA_BIND_STD_CLIENT(registerSound, registersound, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD_CLIENT(font, newfont, e.Get<char*>(1), e.Get<char*>(2), e.Get<int*>(3), e.Get<int*>(4), e.Get<int*>(5), e.Get<int*>(6), e.Get<int*>(7), e.Get<int*>(8))
LUA_BIND_STD_CLIENT(fontOffset, fontoffset, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(fontChar, fontchar, e.Get<int*>(1), e.Get<int*>(2), e.Get<int*>(3), e.Get<int*>(4))

// Variable manipulation

LUA_BIND_DEF(getVariable, {
    ident *id = idents->access(e.Get<const char*>(1));
    if (id) switch(id->type)
    {
        case ID_VAR :  e.Push(*id->storage.i); break;
        case ID_FVAR:  e.Push(*id->storage.f); break;
        case ID_SVAR:  e.Push(*id->storage.s); break;
        case ID_ALIAS: e.Push(id->action);     break;
    }
})

LUA_BIND_DEF(setVariable, {
    ident *id = idents->access(e.Get<const char*>(1));
    if (id) switch(id->type)
    {
        case ID_VAR :   setvarchecked(id, atoi(e.Get<const char*>(2))); break;
        case ID_FVAR:  setfvarchecked(id, strtod(e.Get<const char*>(2), NULL)); break;
        case ID_SVAR:  setsvarchecked(id, e.Get<const char*>(2)); break;
        case ID_ALIAS: alias(id->name, e.Get<const char*>(2)); break;
    }
})

LUA_BIND_DEF(syncVariableFromLua, {
    std::string name = e.Get<std::string>(1);
    std::string type = e.Get<std::string>(2);
    switch (type[0])
    {
        case 'I':
        {
            EngineVariables::syncFromLua(name, e.Get<int>(3));
            break;
        }
        case 'F':
        {
            EngineVariables::syncFromLua(name, (float)e.Get<float>(3));
            break;
        }
        case 'S':
        {
            EngineVariables::syncFromLua(name, e.Get<std::string>(3));
            break;
        }
        default: break;
    }
})

LUA_BIND_STD(runCS, execute, e.Get<const char*>(1))
LUA_BIND_DEF(startStopLocalServer, {
    if (e.Is<void>(1))
        run_python((char*)"intensity.components.server_runner.stop_server()");
    else
    {
        std::string cmd = "intensity.components.server_runner.run_server('";
        cmd += e.Get<std::string>(1) + "'";
        if (!_EV_logged_into_master->getInteger()) cmd += ", False";
        cmd += ")";
        run_python((char*)cmd.c_str());
    }
})

// GUI

LUA_BIND_STD_CLIENT(showMessage, IntensityGUI::showMessage, "Script message", e.Get<std::string>(1))
LUA_BIND_STD_CLIENT(showInputDialog, IntensityGUI::showInputDialog, "Script input", e.Get<std::string>(1))
LUA_BIND_CLIENT(setDefaultThirdpersonMode, {
    // Only allow this to be done once
    if (!e["setDefaultThirdpersonMode"])
    {
        e["setDefaultThirdpersonMode"] = "set";
        SETV(thirdperson, e.Get<int>(1));
    } else
        Logging::log(Logging::WARNING, "Can only set default thirdperson mode once per map\r\n");
})

LUA_BIND_STD_CLIENT(newGUI, newgui, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(GUIButton, guibutton, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(GUIText, guitext, e.Get<char*>(1), e.Get<char*>(2))
LUA_BIND_STD_CLIENT(clearGUI, e.Push, cleargui(e.Get<int>(1)))
LUA_BIND_STD_CLIENT(showGUI, showgui, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUIOnClear, guionclear, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUIStayOpen, guistayopen, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUINoAutoTab, guinoautotab, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUIList, guilist, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUIAlign, guialign, e.Get<int*>(1), e.Get<char*>(2))
LUA_BIND_STD_CLIENT(GUITitle, guititle, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUIBar, guibar)
LUA_BIND_STD_CLIENT(GUIStrut, guistrut, e.Get<float*>(1), e.Get<int*>(2))
LUA_BIND_STD_CLIENT(GUIImage, guiimage, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3), e.Get<int*>(4), e.Get<char*>(5))
LUA_BIND_STD_CLIENT(GUISlider, guislider, e.Get<char*>(1), e.Get<int*>(2), e.Get<int*>(3), e.Get<char*>(4))
LUA_BIND_STD_CLIENT(GUIListSlider, guilistslider, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(GUINameSlider, guinameslider, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3), e.Get<char*>(4))
LUA_BIND_STD_CLIENT(GUIRadio, guiradio, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3), e.Get<char*>(4))
LUA_BIND_STD_CLIENT(GUIBitfield, guibitfield, e.Get<char*>(1), e.Get<char*>(2), e.Get<int*>(3), e.Get<char*>(4))
LUA_BIND_STD_CLIENT(GUICheckBox, guicheckbox, e.Get<char*>(1), e.Get<char*>(2), e.Get<float*>(3), e.Get<float*>(4), e.Get<char*>(5))
LUA_BIND_STD_CLIENT(GUITab, guitab, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(GUIField, guifield, e.Get<char*>(1), e.Get<int*>(2), e.Get<char*>(3), e.Get<int*>(4))
LUA_BIND_STD_CLIENT(GUIKeyfield, guikeyfield, e.Get<char*>(1), e.Get<int*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(GUIEditor, guieditor, e.Get<char*>(1), e.Get<int*>(2), e.Get<int*>(3), e.Get<int*>(4))
LUA_BIND_STD_CLIENT(GUIColor, guicolor, e.Get<int*>(1))
LUA_BIND_STD_CLIENT(GUITextBox, guitextbox, e.Get<char*>(1), e.Get<int*>(2), e.Get<int*>(3), e.Get<int*>(4))

LUA_BIND_STD_CLIENT(quit, quit)
LUA_BIND_STD_CLIENT(forceQuit, force_quit)
LUA_BIND_STD_CLIENT(screenRes, screenres, e.Get<int*>(1), e.Get<int*>(2))
LUA_BIND_STD_CLIENT(resetGl, resetgl)
LUA_BIND_STD_CLIENT(getFps, getfps_, e.Get<int*>(1))

LUA_BIND_STD_CLIENT(resetLightMaps, resetlightmaps, e.Get<bool>(1))
LUA_BIND_STD_CLIENT(calcLight, calclight, e.Get<int*>(1))
LUA_BIND_STD_CLIENT(patchLight, patchlight, e.Get<int*>(1))
LUA_BIND_STD_CLIENT(clearLightMaps, clearlightmaps)
LUA_BIND_STD_CLIENT(dumpLms, dumplms)

// blendmap

LUA_BIND_STD(clearBlendBrushes, clearblendbrushes)
LUA_BIND_STD(delBlendBrush, delblendbrush, e.Get<const char*>(1))
LUA_BIND_STD(addBlendBrush, addblendbrush, e.Get<const char*>(1), e.Get<const char*>(2))
LUA_BIND_STD(nextBlendBrush, nextblendbrush, e.Get<int*>(1))
LUA_BIND_STD(setBlendBrush, setblendbrush, e.Get<const char*>(1))
LUA_BIND_STD(getBlendBrushName, getblendbrushname, e.Get<int*>(1))
LUA_BIND_STD(curBlendBrush, curblendbrush)
LUA_BIND_STD(rotateBlendBrush, rotateblendbrush, e.Get<int*>(1))
LUA_BIND_DEF(paintBlendMap, {
    if (addreleaseaction("paintblendmap"))
    {
        if (!paintingblendmap)
        {
            paintblendmap(true);
            paintingblendmap = totalmillis;
        }
    }
    else stoppaintblendmap();
})
LUA_BIND_STD(clearBlendMapSel, clearblendmapsel)
LUA_BIND_STD(invertBlendMapSel, invertblendmapsel)
LUA_BIND_STD(invertBlendMap, invertblendmap)
LUA_BIND_STD(showBlendMap, showblendmap)
LUA_BIND_STD(optimizeBlendMap, optimizeblendmap)
LUA_BIND_DEF(clearBlendMap, {
    if(noedit(true) || (GETIV(nompedit) && multiplayer())) return;
    resetblendmap();
    showblendmap();
})

// console

LUA_BIND_STD_CLIENT(toggleConsole, SETV, fullconsole, GETIV(fullconsole) ^ 1)
LUA_BIND_STD_CLIENT(conSkip, setconskip, conskip, GETIV(fullconsole) ? GETIV(fullconfilter) : GETIV(confilter), e.Get<int>(1))
LUA_BIND_STD_CLIENT(miniConSkip, setconskip, miniconskip, GETIV(miniconfilter), e.Get<int>(1))
LUA_BIND_CLIENT(clearConsole, while(conlines.length()) delete[] conlines.pop().line;)
LUA_BIND_STD_CLIENT(bind, bindkey, e.Get<char*>(1), e.Get<char*>(2), keym::ACTION_DEFAULT, "bind")
LUA_BIND_STD_CLIENT(specBind, bindkey, e.Get<char*>(1), e.Get<char*>(2), keym::ACTION_SPECTATOR, "specbind")
LUA_BIND_STD_CLIENT(editBind, bindkey, e.Get<char*>(1), e.Get<char*>(2), keym::ACTION_EDITING, "editbind")
LUA_BIND_STD_CLIENT(getBind, getbind, e.Get<char*>(1), keym::ACTION_DEFAULT)
LUA_BIND_STD_CLIENT(getSpecBind, getbind, e.Get<char*>(1), keym::ACTION_SPECTATOR)
LUA_BIND_STD_CLIENT(getEditBind, getbind, e.Get<char*>(1), keym::ACTION_EDITING)
LUA_BIND_STD_CLIENT(searchBinds, searchbinds, e.Get<char*>(1), keym::ACTION_DEFAULT)
LUA_BIND_STD_CLIENT(searchSpecBinds, searchbinds, e.Get<char*>(1), keym::ACTION_SPECTATOR)
LUA_BIND_STD_CLIENT(searchEditBinds, searchbinds, e.Get<char*>(1), keym::ACTION_EDITING)
LUA_BIND_CLIENT(sayCommand, {
    std::string init = e.Get<std::string>(1);
    int n = e.TopStackItemIndex();
    for (int i = 2; i <= n; i++) init += e.Get<std::string>(i);
    inputcommand((char*)init.c_str());
})
LUA_BIND_STD_CLIENT(inputCommand, inputcommand, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(history, history_, e.Get<int*>(1))
LUA_BIND_STD_CLIENT(onRelease, onrelease, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(complete, addfilecomplete, e.Get<char*>(1), e.Get<char*>(2), e.Get<char*>(3))
LUA_BIND_STD_CLIENT(listComplete, addlistcomplete, e.Get<char*>(1), e.Get<char*>(2))

// textedit

#define LUA_BIND_TEXT(n, c) \
LUA_BIND_CLIENT(n, { \
    editor *top = currentfocus(); \
    if (!top) return; \
    c \
})
// return list of all editors
LUA_BIND_CLIENT(textList, {
    std::string s;
    loopv(editors)
    {
        if (i > 0) s += ", ";
        s += editors[i]->name;
    }
    e.Push(s);
})
// return the start of the buffer
LUA_BIND_TEXT(textShow, {
    editline line;
    line.combinelines(top->lines);
    e.Push(line.text);
    line.clear();
})
// focus on a (or create a persistent) specific editor, else returns current name
LUA_BIND_CLIENT(textFocus, {
    if (e.Is<std::string>(1))
    {
        int arg2 = e.Get<int>(2);
        useeditor(e.Get<const char*>(1), arg2 <= 0 ? EDITORFOREVER : arg2, true);
    }
    else if (editors.length() > 0) e.Push(editors.last()->name);
    else e.Push();
})
// return to the previous editor
LUA_BIND_TEXT(textPrev, editors.insert(0, top); editors.pop();)
// (1 = keep while focused, 2 = keep while used in gui, 3 = keep forever (i.e. until mode changes)) topmost editor, return current setting if no args
LUA_BIND_TEXT(textMode, {
    int arg1 = e.Get<int>(2);
    if (arg1)
    {
        top->mode = arg1;
        e.Push();
    }
    else e.Push(top->mode);
})
// saves the topmost (filename is optional)
LUA_BIND_TEXT(textSave, {
    const char *arg1 = e.Get<const char*>(1);
    if (arg1) top->setfile(path(arg1, true));
    top->save();
})
LUA_BIND_TEXT(textLoad, {
    const char *arg1 = e.Get<const char*>(1);
    if (arg1)
    {
        top->setfile(path(arg1, true));
        top->load();
        e.Push();
    }
    else if (top->filename) e.Push(top->filename);
    else e.Push();
})
LUA_BIND_TEXT(textInit, {
    editor *ed = NULL;
    const char *arg2 = e.Get<const char*>(2);
    loopv(editors) if(!e.Get<std::string>(1).compare(editors[i]->name))
    {
        ed = editors[i];
        break;
    }
    if(ed && ed->rendered && !ed->filename && arg2 && (ed->lines.empty() || (ed->lines.length() == 1 && !e.Get<std::string>(3).compare(ed->lines[0].text))))
    {
        ed->setfile(path(arg2, true));
        ed->load();
    }
})
 
#define PASTEBUFFER "#pastebuffer"

LUA_BIND_TEXT(textCopy, editor *b = useeditor(PASTEBUFFER, EDITORFOREVER, false); top->copyselectionto(b);)
LUA_BIND_TEXT(textPaste, editor *b = useeditor(PASTEBUFFER, EDITORFOREVER, false); top->insertallfrom(b);)
LUA_BIND_TEXT(textMark, {
    editor *b = useeditor(PASTEBUFFER, EDITORFOREVER, false); top->insertallfrom(b);
    int arg1 = e.Get<int>(1);
    if (arg1)
    {
        top->mark(arg1 == 1);
        e.Push();
    }
    else e.Push(top->region() ? 1 : 2);
})
LUA_BIND_TEXT(textSelectAll, top->selectall();)
LUA_BIND_TEXT(textClear, top->clear();)
LUA_BIND_TEXT(textCurrentLine, e.Push(top->currentline().text);)
LUA_BIND_TEXT(textExec, e.RunString(std::string(e.Get<int>(1) ? top->selectiontostring() : top->tostring()));)

// various commands

LUA_BIND_STD_CLIENT(movie, movie, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(recalc, recalc)
LUA_BIND_STD_CLIENT(glExt, glext, e.Get<char*>(1))
LUA_BIND_STD_CLIENT(getCamPos, e.Push, camera1->o)
LUA_BIND_STD_CLIENT(loadCrosshair, loadcrosshair_, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD_CLIENT(tabify, tabify, e.Get<char*>(1), e.Get<int*>(2))
LUA_BIND_STD_CLIENT(resetSound, resetsound)

LUA_BIND_STD(isConnected, e.Push, isconnected(e.Get<int>(1) > 0) ? 1 : 0)
LUA_BIND_DEF(connectedIP, {
    const ENetAddress *address = connectedpeer();
    string hostname;
    e.Push(address && enet_address_get_host_ip(address, hostname, sizeof(hostname)) >= 0 ? hostname : "");
})
LUA_BIND_DEF(connectedPort, {
    const ENetAddress *address = connectedpeer();
    e.Push(address ? address->port : -1);
})
LUA_BIND_STD(connectServ, connectserv, e.Get<const char*>(1), e.Get<int>(2), e.Get<const char*>(3))
LUA_BIND_STD(lanConnect, connectserv, NULL, e.Get<int>(1), e.Get<const char*>(2))
LUA_BIND_STD(disconnect, trydisconnect)
LUA_BIND_STD(localConnect, if(!isconnected() && !haslocalclients()) localconnect)
LUA_BIND_STD(localDisconnect, if(haslocalclients()) localdisconnect)

LUA_BIND_STD(printCube, printcube)
LUA_BIND_STD(remip, remip_)
LUA_BIND_STD(physTest, phystest)
LUA_BIND_STD(genPvs, genpvs, e.Get<int*>(1))
LUA_BIND_STD(testPvs, testpvs, e.Get<int*>(1))
LUA_BIND_STD(clearPvs, clearpvs)
LUA_BIND_STD(pvsStats, pvsstats)

LUA_BIND_STD(startListenServer, startlistenserver, e.Get<int*>(1))
LUA_BIND_STD(stopListenServer, stoplistenserver)

} // namespace lua_binds
