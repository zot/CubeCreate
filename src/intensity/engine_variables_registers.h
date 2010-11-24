// engine/animmodel.h

REGVAR("lightmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("envmapmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("glowmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("bumpmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("fullbrightmodels", 0, 0, 200, NULL, true);

// engine/blend.cpp

REGVAR("blendpaintmode", 0, 0, 5, ICB({
    if(!curv) stoppaintblendmap();
}));

REGVAR("paintblendmapdelay", 1, 500, 3000);
REGVAR("paintblendmapinterval", 1, 30, 3000);

// engine/blob.cpp

#ifdef CLIENT
REGVAR("blobs", 0, 1, 1, NULL, true); // globalname was showblobs
REGVAR("blobintensity", 0, 60, 100, ICB({ resetblobs(); }), true);
REGVAR("blobheight", 1, 32, 128, ICB({ resetblobs(); }), true);
REGVAR("blobfadelow", 1, 8, 32, ICB({ resetblobs(); }), true);
REGVAR("blobfadehigh", 1, 8, 32, ICB({ resetblobs(); }), true);
REGVAR("blobmargin", 0, 1, 16, ICB({ resetblobs(); }), true);
REGVAR("dbgblob", 0, 0, 1);
REGVAR("blobstattris", 128, 4096, 1<<16, ICB({ initblobs(BLOB_STATIC); }), true);
REGVAR("blobdyntris", 128, 4096, 1<<16, ICB({ initblobs(BLOB_DYNAMIC); }), true);
#endif

// engine/client.cpp

void setrate(int rate);
void throttle();

REGVAR("rate", 0, 0, 25000, ICB({ setrate(curv); }));
REGVAR("throttle_interval", 0, 5, 30, ICB({ throttle(); }));
REGVAR("throttle_accel", 0, 2, 32, ICB({ throttle(); }));
REGVAR("throttle_decel", 0, 2, 32, ICB({ throttle(); }));
REGVAR("connectname", "");
REGVAR("connectport", 0, 0, 0xFFFF);

#ifdef CLIENT
// engine/console.cpp

extern vector<cline> conlines;

REGVAR("maxcon", 10, 200, 1000, ICB({ while(conlines.length() > curv) delete[] conlines.pop().line; }), true);
REGVAR("fullconsole", 0, 0, 1);
REGVAR("consize", 0, 5, 100, NULL, true);
REGVAR("miniconsize", 0, 5, 100, NULL, true);
REGVAR("miniconwidth", 0, 40, 100, NULL, true);
REGVAR("confade", 0, 30, 60, NULL, true);
REGVAR("miniconfade", 0, 30, 60, NULL, true);
REGVAR("fullconsize", 0, 75, 100, NULL, true);
REGVAR("confilter", 0, 0x7FFFFFF, 0x7FFFFFF, NULL, true);
REGVAR("fullconfilter", 0, 0x7FFFFFF, 0x7FFFFFF, NULL, true);
REGVAR("miniconfilter", 0, 0, 0x7FFFFFF, NULL, true);
REGVAR("maxhistory", 0, 1000, 10000);

// engine/decal.cpp

REGVAR("maxdecaltris", 1, 1024, 16384, ICB({ initdecals(); }), true);
REGVAR("decalfade", 1000, 10000, 60000, NULL, true);
REGVAR("dbgdec", 0, 0, 1);
REGVAR("decals", 0, 1, 1, NULL, true); // globalname was showdecals
REGVAR("maxdecaldistance", 1, 512, 10000, NULL, true);

// engine/depthfx.h

void cleanupdepthfx();

REGVAR("depthfxfpscale", 1, 1<<12, 1<<16, NULL, true);
REGVAR("depthfxscale", 1, 1<<6, 1<<8, NULL, true);
REGVAR("depthfxblend", 1, 16, 64, NULL, true);
REGVAR("depthfxpartblend", 1, 8, 64, NULL, true);
REGVAR("depthfxmargin", 0, 16, 64);
REGVAR("depthfxbias", 0, 1, 64);
REGVAR("fpdepthfx", 0, 0, 1, ICB({ cleanupdepthfx(); }), true);
REGVAR("depthfxprecision", 0, 0, 1, ICB({ cleanupdepthfx(); }), true);
REGVAR("depthfxemuprecision", 0, 1, 1, NULL, true);
REGVAR("depthfxsize", 6, 7, 12, ICB({ cleanupdepthfx(); }), true);
REGVAR("depthfx", 0, 1, 1, NULL, true);
REGVAR("depthfxparts", 0, 1, 1, NULL, true);
REGVAR("depthfxrect", 0, 0, 1, ICB({ cleanupdepthfx(); }), true);
REGVAR("depthfxfilter", 0, 1, 1, ICB({ cleanupdepthfx(); }), true);
REGVAR("blurdepthfx", 0, 1, 7, NULL, true);
REGVAR("blurdepthfxsigma", 1, 50, 200, NULL, true);
REGVAR("depthfxscissor", 0, 2, 2);
REGVAR("debugdepthfx", 0, 0, 1);

// engine/dynlight.cpp
REGVAR("ffdynlights", 0, min(5, DYNLIGHTMASK), DYNLIGHTMASK, NULL, true);
REGVAR("maxdynlights", 0, min(3, MAXDYNLIGHTS), MAXDYNLIGHTS, NULL, true);
REGVAR("dynlightdist", 0, 1024, 10000, NULL, true);

// engine/explosion.h

REGVAR("explosion2d", 0, 0, 1, NULL, true);

// engine/glare.cpp

void cleanupglare();

REGVAR("glaresize", 6, 8, 10, ICB({ cleanupglare(); }), true);
REGVAR("glare", 0, 0, 1, NULL, true);
REGVAR("blurglare", 0, 4, 7, NULL, true);
REGVAR("blurglaresigma", 1, 50, 200, NULL, true);
REGVAR("debugglare", 0, 0, 1);
REGVAR("glarescale", 0.0f, 1.0f, 8.0f, NULL, true);

// engine/grass.cpp

extern bvec grasscolor;

REGVAR("grass", 0, 0, 1, NULL, true);
REGVAR("dbggrass", 0, 0, 1);
REGVAR("grassdist", 0, 256, 10000, NULL, true);
REGVAR("grasstaper", 0.0f, 0.2f, 1.0f, NULL, true);
REGVAR("grassstep", 0.5f, 2.0f, 8.0f, NULL, true);
REGVAR("grassheight", 1, 4, 64, NULL, true);
REGVAR("grassanimmillis", 0, 3000, 60000); // override
REGVAR("grassanimscale", 0.0f, 0.03f, 1.0f); // override
REGVAR("grassscale", 1, 2, 64); // override
REGVAR("grasscolour", 0, 0xFFFFFF, 0xFFFFFF, ICB({
	int c = curv;
    if(!curv)
    {
		EngineVariables::get("grasscolour").get()->set(0xFFFFFF);
		c = 0xFFFFFF;
	}
    grasscolor = bvec((c>>16)&0xFF, (c>>8)&0xFF, c&0xFF);
})); // override
REGVAR("grassalpha", 0, 1, 1); // override

// engine/lensflare.h

REGVAR("flarelights", 0, 0, 1);
REGVAR("flarecutoff", 0, 1000, 10000, NULL, true);
REGVAR("flaresize", 20, 100, 500, NULL, true);

// engine/lightmap.cpp

void setfullbrightlevel(int fullbrightlevel);
void cleanuplightmaps();

REGVAR("lightprecision", 1, 32, 1024); // override
REGVAR("lighterror", 1, 8, 16); // override
REGVAR("bumperror", 1, 3, 16); // override
REGVAR("lightlod", 0, 0, 10); // override
REGVAR("ambient", 1, 0x191919, 0xFFFFFF, ICB({
	int c = curv;
    if(curv <= 255)
    {
		EngineVariables::get("ambient").get()->set(curv | (curv<<8) | (curv<<16));
		c = curv | (curv<<8) | (curv<<16);
	}
    ambientcolor = bvec((c>>16)&0xFF, (c>>8)&0xFF, c&0xFF);
})); // override
REGVAR("skylight", 0, 0, 0xFFFFFF, ICB({
	int c = curv;
    if(curv <= 255)
    {
		EngineVariables::get("skylight").get()->set(curv | (curv<<8) | (curv<<16));
		c = curv | (curv<<8) | (curv<<16);
	}
    skylightcolor = bvec((c>>16)&0xFF, (c>>8)&0xFF, c&0xFF);
})); // override
REGVAR("lmshadows", 0, 2, 2); // global name was lmshadows_
REGVAR("lmaa", 0, 3, 3); // global name was lmaa_
REGVAR("lightcompress", 0, 3, 6);
REGVAR("skytexturelight", 0, 1, 1); // override
REGVAR("blurlms", 0, 0, 2); // override
REGVAR("blurskylight", 0, 0, 2); // override
REGVAR("edgetolerance", 1, 4, 8);
REGVAR("adaptivesample", 0, 2, 2);
REGVAR("lightcachesize", 4, 6, 12, ICB({ clearlightcache(); }));
REGVAR("lightthreads", 1, 1, 16, NULL, true);
REGVAR("patchnormals", 0, 0, 1);
REGVAR("fullbright", 0, 0, 1, ICB({ if (lightmaptexs.length()) initlights(); }));
REGVAR("fullbrightlevel", 0, 128, 255, ICB({ setfullbrightlevel(curv); }));
REGVAR("convertlms", 0, 1, 1, ICB({ cleanuplightmaps(); initlights(); allchanged(); }));
REGVAR("roundlightmaptex", 0, 4, 16, ICB({ cleanuplightmaps(); initlights(); allchanged(); }));
REGVAR("batchlightmaps", 0, 4, 256, ICB({ cleanuplightmaps(); initlights(); allchanged(); }));

// engine/lightning.h

REGVAR("lnjittermillis", 0, 100, 1000);
REGVAR("lnjitterradius", 0, 4, 100);
REGVAR("lnjitterscale", 0.0f, 0.5f, 10.0f);
REGVAR("lnscrollmillis", 1, 300, 5000);
REGVAR("lnscrollscale", 0.0f, 0.125f, 10.0f);
REGVAR("lnblendpower", 0.0f, 0.25f, 1000.0f);

// engine/main.cpp

// TODO: remove those defines
#define SCR_MINW 320
#define SCR_MINH 200
#define SCR_MAXW 10000
#define SCR_MAXH 10000

void setfullscreen(bool enable);
void clockreset();

REGVAR("scr_w", SCR_MINW, -1, SCR_MAXW, ICB({ initwarning("screen resolution"); }));
REGVAR("scr_h", SCR_MINH, -1, SCR_MAXH, ICB({ initwarning("screen resolution"); }));
REGVAR("colorbits", 0, 0, 32, ICB({ initwarning("color depth"); }));
REGVAR("depthbits", 0, 0, 32, ICB({ initwarning("depth-buffer precision"); }));
REGVAR("stencilbits", 0, 0, 32, ICB({ initwarning("stencil-buffer precision"); }));
REGVAR("fsaa", -1, -1, 16, ICB({ initwarning("anti-aliasing"); }));
REGVAR("vsync", -1, -1, 1, ICB({ initwarning("vertical sync"); }));
REGVAR("fullscreen", 0, 0, 1, ICB({ setfullscreen(curv!=0); }));
REGVAR("gamma", 30, 100, 300, ICB({
    float f = curv/100.0f;
    if(SDL_SetGamma(f,f,f)==-1)
    {
        conoutf(CON_ERROR, "Could not set gamma (card/driver doesn't support it?)");
        conoutf(CON_ERROR, "sdl: %s", SDL_GetError());
    }
}), true);
REGVAR("dbgmodes", 0, 0, 1);
REGVAR("iskeydown", 0, 0, 1);
REGVAR("iskeyup", 0, 0, 1);
REGVAR("ismousedown", 0, 0, 1);
REGVAR("ismouseup", 0, 0, 1);
REGVAR("gamespeed", 10, 100, 1000, ICB({ if(multiplayer()) EngineVariables::get("gamespeed").get()->set(100); }));
REGVAR("paused", 0, 0, 1, ICB({ if(multiplayer()) EngineVariables::get("paused").get()->set(0); }));
REGVAR("mainmenufps", 0, 60, 1000);
REGVAR("maxfps", 0, 100, 1000, NULL, true);
REGVAR("clockerror", 990000, 1000000, 1010000, ICB({ clockreset(); }), true);
REGVAR("clockfix", 0, 0, 1, ICB({ clockreset(); }), true);

// engine/material.cpp

REGVAR("optmats", 0, 1, 1, ICB({ allchanged(); }));
REGVAR("showmat", 0, 1, 1, NULL, true);
REGVAR("glassenv", 0, 1, 1, NULL, true);
REGVAR("waterfallenv", 0, 1, 1, ICB({ preloadwatershaders(); }), true);

// engine/menus.cpp

REGVAR("menudistance", 16, 10, 256, NULL, true);
REGVAR("menuautoclose", 32, 120, 4096, NULL, true);
REGVAR("applydialog", 0, 1, 1, NULL, true);
REGVAR("mainmenu", 1, 1, 0);

// engine/movie.cpp

REGVAR("dbgmovie", 0, 0, 1);
REGVAR("movieaccelblit", 0, 0, 1);
REGVAR("movieaccelyuv", 0, 0, 1);
REGVAR("movieaccel", 0, 1, 1, NULL, true);
REGVAR("moviesync", 0, 0, 1, NULL, true);
REGVAR("moview", 0, 320, 10000, NULL, true);
REGVAR("movieh", 0, 240, 10000, NULL, true);
REGVAR("moviefps", 1, 24, 1000, NULL, true);
REGVAR("moviesound", 0, 1, 1, NULL, true);
#endif

// engine/normal.cpp
REGVAR("lerpangle", 0, 44, 180); // override
REGVAR("lerpsubdiv", 0, 2, 4); // override
REGVAR("lerpsubdivsize", 4, 4, 128); // override

// engine/octa.cpp
REGVAR("mipvis", 0, 0, 1);
REGVAR("minface", 0, 1, 1);
REGVAR("maxmerge", 0, 6, 12);

// engine/octaedit.cpp

extern selinfo sel;
extern int orient, gridsize;
extern ivec cor, lastcor;
extern ivec cur, lastcur;
extern int horient;
extern bool havesel;
// TODO: get rid of those
#define MAXBRUSH    64
#define MAXBRUSH2   32

REGVAR("dragging", 0, 0, 1, ICB({
    if(!curv || cor[0]<0) return;
    lastcur = cur;
    lastcor = cor;
    sel.grid = gridsize;
    sel.orient = orient;
}));

REGVAR("moving", 0, 0, 1, ICB({
    if(!curv) return;
    vec v(cur.v); v.add(1);
    EngineVariables::get("moving").get()->set(pointinsel(sel, v));
    if(EngineVariables::get("moving").get()->getInteger()) havesel = false; // tell cursorupdate to create handle
}));

REGVAR("gridpower", 0, 3, 12, ICB({
    if(EngineVariables::get("dragging").get()->getInteger()) return;
    gridsize = 1<<curv;
    if(gridsize>=worldsize) gridsize = worldsize/2;
    cancelsel();
}));

REGVAR("passthroughsel", 0, 0, 1);
REGVAR("editing", 1, 0, 0);
REGVAR("selectcorners", 0, 0, 1);
REGVAR("hmapedit", 0, 0, 1, ICB({ horient = sel.orient; }));
REGVAR("gridlookup", 0, 0, 1);
REGVAR("passthroughcube", 0, 1, 1);
REGVAR("undomegs", 0, 5, 100, NULL, true); // bounded by n megs
REGVAR("nompedit", 0, 1, 1, NULL, true);
REGVAR("brushx", 0, MAXBRUSH2, MAXBRUSH);
REGVAR("brushy", 0, MAXBRUSH2, MAXBRUSH);
REGVAR("bypassheightmapcheck", 0, 0, 1, NULL, true); // temp
REGVAR("invalidcubeguard", 0, 1, 1);
REGVAR("selectionsurf", 0, 0, 1);
REGVAR("usevdelta", 1, 0, 0);
REGVAR("allfaces", 0, 0, 1);
REGVAR("texguiwidth", 1, 12, 1000, NULL, true);
REGVAR("texguiheight", 1, 8, 1000, NULL, true);
REGVAR("texguitime", 0, 25, 1000, NULL, true);
REGVAR("texgui2d", 0, 1, 1);

// engine/octarender.cpp

REGVAR("printvbo", 0, 0, 1);
REGVAR("vbosize", 0, 1<<14, 1<<16, ICB({ allchanged(); })); // globalname was maxvbosize
REGVAR("filltjoints", 0, 1, 1, ICB({ allchanged(); }), true);
REGVAR("vacubemax", 64, 512, 256*256, ICB({ allchanged(); }));
REGVAR("vacubesize", 32, 128, 0x1000, ICB({ allchanged(); }));
REGVAR("vacubemin", 0, 128, 256*256, ICB({ allchanged(); }));

// engine/physics.cpp

REGVAR("dynentsize", 4, 7, 12, ICB({ cleardynentcache(); }));
REGVAR("maxroll", 0, 3, 20, NULL, true);
REGVAR("straferoll", 0.0f, 0.033f, 90.0f);
REGVAR("floatspeed", 10, 100, 1000);
REGVAR("physicsinterp", 0, 1, 1);

// engine/pvs.cpp

void lockpvs_(bool lock);

REGVAR("maxpvsblocker", 1, 512, 1<<16);
REGVAR("pvsleafsize", 1, 64, 1024);
REGVAR("pvsthreads", 1, 1, 16, NULL, true);
REGVAR("lockpvs", 0, 0, 1, ICB({ lockpvs_(curv!=0); }));
REGVAR("pvs", 0, 1, 1); // globalname was usepvs
REGVAR("waterpvs", 0, 1, 1); // globalname was usewaterpvs

// engine/ragdoll.h

REGVAR("ragdolltimestepmin", 1, 5, 50);
REGVAR("ragdolltimestepmax", 1, 10, 50);
REGVAR("ragdollrotfric", 0.0f, 0.85f, 1.0f);
REGVAR("ragdollrotfricstop", 0.0f, 0.1f, 1.0f);
REGVAR("ragdollconstrain", 1, 5, 100);
REGVAR("ragdollbodyfric", 0.0f, 0.95f, 1.0f);
REGVAR("ragdollbodyfricscale", 0.0f, 2.0f, 10.0f);
REGVAR("ragdollwaterfric", 0.0f, 0.85f, 1.0f);
REGVAR("ragdollgroundfric", 0.0f, 0.8f, 1.0f);
REGVAR("ragdollairfric", 0.0f, 0.996f, 1.0f);
REGVAR("ragdollexpireoffset", 0, 1500, 30000);
REGVAR("ragdollwaterexpireoffset", 0, 3000, 30000);
REGVAR("ragdolleyesmooth", 0.0f, 0.5f, 1.0f);
REGVAR("ragdolleyesmoothmillis", 1, 250, 10000);

// engine/rendergl.cpp

#ifdef CLIENT
extern int zoommillis, damageblendmillis;
extern bvec fogcolor;
extern bvec minimapcolor;
extern GLuint minimaptex;
void cleanupmotionblur();

REGVAR("renderpath", 1, 0, 0);
REGVAR("ati_skybox_bug", 0, 0, 1, NULL, true);
REGVAR("ati_oq_bug", 0, 0, 1);
REGVAR("ati_minmax_bug", 0, 0, 1);
REGVAR("ati_dph_bug", 0, 0, 1);
REGVAR("ati_teximage_bug", 0, 0, 1);
REGVAR("ati_line_bug", 0, 0, 1);
REGVAR("ati_cubemap_bug", 0, 0, 1);
REGVAR("ati_ubo_bug", 0, 0, 1);
REGVAR("nvidia_scissor_bug", 0, 0, 1);
REGVAR("apple_glsldepth_bug", 0, 0, 1);
REGVAR("apple_ff_bug", 0, 0, 1);
REGVAR("apple_vp_bug", 0, 0, 1);
REGVAR("sdl_backingstore_bug", -1, 0, 1);
REGVAR("intel_quadric_bug", 0, 0, 1);
REGVAR("mesa_program_bug", 0, 0, 1);
REGVAR("avoidshaders", 1, 0, 0);
REGVAR("minimizetcusage", 1, 0, 0);
REGVAR("emulatefog", 1, 0, 0);
REGVAR("usevp2", 1, 0, 0);
REGVAR("usevp3", 1, 0, 0);
REGVAR("usetexrect", 1, 0, 0);
REGVAR("hasglsl", 1, 0, 0);
REGVAR("useubo", 1, 0, 0);
REGVAR("usebue", 1, 0, 0);
REGVAR("rtscissor", 0, 1, 1);
REGVAR("blurtile", 0, 1, 1);
REGVAR("rtsharefb", 0, 1, 1);
REGVAR("dbgexts", 0, 0, 1);
REGVAR("wireframe", 0, 0, 1);
REGVAR("zoominvel", 0, 250, 5000, NULL, true);
REGVAR("zoomoutvel", 0, 100, 5000, NULL, true);
REGVAR("zoomfov", 10, 35, 60, NULL, true);
REGVAR("fov", 10, 100, 150, NULL, true);
REGVAR("avatarzoomfov", 10, 25, 60);
REGVAR("avatarfov", 10, 65, 150);
REGVAR("avatardepth", 0.0f, 0.5f, 1.0f);
REGVAR("zoom", -1, 0, 1, ICB({ if(curv) zoommillis = totalmillis; }));
REGVAR("zoomsens", 1e-3f, 1.0f, 1000.0f, NULL, true);
REGVAR("zoomaccel", 0.0f, 0.0f, 1000.0f, NULL, true);
REGVAR("zoomautosens", 0, 1, 1, NULL, true);
REGVAR("sensitivity", 1e-3f, 3.0f, 1000.0f, NULL, true);
REGVAR("sensitivityscale", 1e-3f, 1.0f, 1000.0f, NULL, true);
REGVAR("invmouse", 0, 0, 1, NULL, true);
REGVAR("mouseaccel", 0.0f, 0.0f, 1000.0f, NULL, true);
REGVAR("thirdperson", 0, 0, 2);
REGVAR("thirdpersondistance", 0.0f, 20.0f, 1000.0f);
REGVAR("nearplane", 1e-3f, 0.54f, 1e3f);
REGVAR("reflectclip", 0, 6, 64);
REGVAR("reflectclipavatar", -64, 0, 64);
REGVAR("polygonoffsetfactor", -1e4f, -3.0f, 1e4f);
REGVAR("polygonoffsetunits", -1e4f, -3.0f, 1e4f);
REGVAR("depthoffset", -1e4f, -0.01f, 1e4f);
REGVAR("fog", 16, 4000, 1000024); // override
REGVAR("fogcolour", 0, 0x8099B3, 0xFFFFFF, ICB({ fogcolor = bvec((curv>>16)&0xFF, (curv>>8)&0xFF, curv&0xFF); })); // override
REGVAR("skyboxglare", 0, 1, 1, NULL, true);
REGVAR("reflectmms", 0, 1, 1, NULL, true);
REGVAR("refractsky", 0, 0, 1); // override
REGVAR("minimapheight", 0, 0, 2<<16); // override
REGVAR("minimapcolour", 0, 0, 0xFFFFFF, ICB({ minimapcolor = bvec((curv>>16)&0xFF, (curv>>8)&0xFF, curv&0xFF); })); // override
REGVAR("minimapclip", 0, 0, 1); // override
REGVAR("minimapsize", 7, 8, 10, ICB({ if (minimaptex) drawminimap(); }), true);
REGVAR("motionblur", 0, 0, 1, ICB({ if (!curv) cleanupmotionblur(); }), true);
REGVAR("motionblurmillis", 1, 5, 1000, NULL, true);
REGVAR("motionblurscale", 0.0f, 0.5f, 1.0f, NULL, true);
REGVAR("damagecompass", 0, 1, 1, NULL, true); // globalname was usedamagecompass
REGVAR("damagecompassfade", 1, 1000, 10000, NULL, true);
REGVAR("damagecompasssize", 1, 30, 100, NULL, true);
REGVAR("damagecompassalpha", 1, 25, 100, NULL, true);
REGVAR("damagecompassmin", 1, 25, 1000, NULL, true);
REGVAR("damagecompassmax", 1, 200, 1000, NULL, true);
REGVAR("damagescreen", 0, 1, 1, ICB({ if (!curv) damageblendmillis = 0; }), true);
REGVAR("damagescreenfactor", 1, 7, 100, NULL, true);
REGVAR("damagescreenalpha", 1, 45, 100, NULL, true);
REGVAR("damagescreenfade", 0, 125, 1000, NULL, true);
REGVAR("damagescreenmin", 1, 10, 1000, NULL, true);
REGVAR("damagescreenmax", 1, 100, 1000, NULL, true);
REGVAR("hidestats", 0, 0, 1);
REGVAR("hidehud", 0, 0, 1);
REGVAR("crosshairsize", 0, 15, 50, NULL, true);
REGVAR("cursorsize", 0, 30, 50, NULL, true);
REGVAR("crosshairfx", 0, 1, 1, NULL, true);
REGVAR("wallclock", 0, 0, 1, NULL, true);
REGVAR("wallclock24", 0, 0, 1, NULL, true);
REGVAR("wallclocksecs", 0, 0, 1, NULL, true);
REGVAR("showfps", 0, 1, 1, NULL, true);
REGVAR("showfpsrange", 0, 0, 1, NULL, true);
REGVAR("showeditstats", 0, 0, 1);
REGVAR("statrate", 1, 200, 1000);
REGVAR("conscale", 1e-3f, 0.33f, 1e3f, NULL, true);
#endif

// engine/rendermodel.cpp

REGVAR("oqdynent", 0, 1, 1, NULL, true);
REGVAR("animationinterpolationtime", 0, 150, 1000, NULL, true);
REGVAR("showboundingbox", 0, 0, 2);
REGVAR("modeltweaks", 0, 0, 1); // INTENSITY: SkyManager: tweaks for models (like ambience, glow, so we can sync it with ambientlight
REGVAR("tweakmodelspec", 0.0f, 1.0f, 100.0f);
REGVAR("tweakmodelambient", 0.0f, 1.0f, 100.0f);
REGVAR("tweakmodelglow", 0.0f, 1.0f, 100.0f);
REGVAR("tweakmodelspecglare", 0.0f, 1.0f, 100.0f);
REGVAR("tweakmodelglowglare", 0.0f, 1.0f, 100.0f);
REGVAR("tweakmodelscale", 0.001f, 1.0f, 100.0f); // override // end INTENSITY
REGVAR("maxmodelradiusdistance", 10, 200, 1000, NULL, true);
REGVAR("animoverride", -1, 0, NUMANIMS-1);
REGVAR("testanims", 0, 0, 1);
REGVAR("testpitch", -90, 0, 90);
#ifdef CLIENT
// engine/renderparticles.cpp

REGVAR("particlesize", 20, 100, 500, NULL, true);
REGVAR("emitmillis", 1, 17, 1000, NULL, true);
REGVAR("dbgpseed", 0, 0, 1);
REGVAR("outlinemeters", 0, 0, 1, NULL, true);
REGVAR("maxparticles", 10, 4000, 40000, ICB({ particleinit(); }), true);
REGVAR("fewparticles", 10, 100, 40000, ICB({ particleinit(); }), true);
REGVAR("particleglare", 0, 2, 100, NULL, true);
REGVAR("debugparticles", 0, 0, 1);
REGVAR("maxparticledistance", 256, 1024, 4096, NULL, true);
REGVAR("maxtrail", 1, 500, 10000, NULL, true);
REGVAR("particletext", 0, 1, 1, NULL, true);
REGVAR("maxparticletextdistance", 0, 128, 10000, NULL, true);
REGVAR("showparticles", 0, 1, 1, NULL, true);
REGVAR("cullparticles", 0, 1, 1);
REGVAR("replayparticles", 0, 1, 1);
REGVAR("seedparticles", 0, 3000, 10000); // globalname was seedmillis
REGVAR("dbgpcull", 0, 0, 1);
REGVAR("editpartsize", 0.0f, 2.0f, 100.0f, ICB({ particleinit(); }), true);

// engine/rendersky.cpp

extern Texture *sky[6], *clouds[6], *stars[6], *sun[6];
extern Texture *cloudoverlay, *altcloudoverlay;
void loadsky(const char *basename, Texture *texs[6]);
Texture *loadskyoverlay(const char *basename);
extern bvec fogdomecolor;

REGVAR("starbox", "", SCB({ if (!curv.empty()) loadsky(curv.c_str(), stars); })); // override // INTENSITY: SkyManager: various star and sun variables
REGVAR("starboxtint", 0, 0xFFFFFF, 0xFFFFFF); // override
REGVAR("spinstars", -720.0f, 0.0f, 720.0f); // override
REGVAR("yawstars", 0, 0, 360); // override // end INTENSITY
REGVAR("skybox", "", SCB({ if (!curv.empty()) loadsky(curv.c_str(), sky); })); // override
REGVAR("skyboxalpha", 0.0f, 0.999f, 1.0f); // override // INTENSITY: Less than one so it won't occlude and cause starbox to be culled.
REGVAR("skyboxtint", 0, 0xFFFFFF, 0xFFFFFF); // INTENSITY: was skyboxcolour
REGVAR("spinsky", -720.0f, 0.0f, 720.0f); // override
REGVAR("yawsky", 0, 0, 360); // override
REGVAR("sunbox", "", SCB({ if (!curv.empty()) loadsky(curv.c_str(), sun); })); // override
REGVAR("sunboxalpha", 0.0f, 1.0f, 1.0f); // override
REGVAR("sunboxtint", 0, 0xFFFFFF, 0xFFFFFF); // override
REGVAR("spinsun", -720.0f, 0.0f, 720.0f); // override
REGVAR("yawsun", 0, 0, 360, ICB({ skymillis = 1; })); // override
REGVAR("cloudbox", "", SCB({ if (!curv.empty()) loadsky(curv.c_str(), clouds); })); // override
REGVAR("cloudboxalpha", 0.0f, 0.999f, 1.0f); // override // INTENSITY: was 1
REGVAR("cloudboxtint", 0, 0xFFFFFF, 0xFFFFFF); // override
REGVAR("spinclouds", -720.0f, 0.0f, 720.0f); // override
REGVAR("yawclouds", 0, 0, 360); // override
REGVAR("cloudclip", 0.0f, 0.5f, 1.0f); // override
REGVAR("cloudlayer", "", SCB({ if (!curv.empty()) cloudoverlay = loadskyoverlay(curv.c_str()); })); // override
REGVAR("cloudscrollx", -16.0f, 0.0f, 16.0f); // override
REGVAR("cloudscrolly", -16.0f, 0.0f, 16.0f); // override
REGVAR("cloudscale", 0.001f, 1.0f, 64.0f); // override
REGVAR("spincloudlayer", -720.0f, 0.0f, 720.0f); // override
REGVAR("yawcloudlayer", 0, 0, 360); // override
REGVAR("cloudheight", -1.0f, 0.2f, 1.0f); // override
REGVAR("cloudfade", 0.0f, 0.2f, 1.0f); // override
REGVAR("cloudalpha", 0.0f, 1.0f, 1.0f); // override
REGVAR("cloudsubdiv", 4, 16, 64); // override
REGVAR("cloudtint", 0, 0xFFFFFF, 0xFFFFFF); // override
REGVAR("altcloudlayer", "", SCB({ if (!curv.empty()) altcloudoverlay = loadskyoverlay(curv.c_str()); })); // override
REGVAR("altcloudscrollx", -16.0f, 0.0f, 16.0f); // override
REGVAR("altcloudscrolly", -16.0f, 0.0f, 16.0f); // override
REGVAR("altcloudscale", 0.001f, 1.0f, 64.0f); // override
REGVAR("spinaltcloudlayer", -720.0f, 0.0f, 720.0f); // override
REGVAR("yawaltcloudlayer", 0, 0, 360); // override
REGVAR("altcloudheight", -1.0f, 0.1f, 1.0f); // override
REGVAR("altcloudfade", 0.0f, 0.1f, 1.0f); // override
REGVAR("altcloudalpha", 0.0f, 0.0f, 1.0f); // override
REGVAR("altcloudsubdiv", 4, 16, 64); // override
REGVAR("altcloudtint", 0, 0xFFFFFF, 0xFFFFFF); // override
REGVAR("fogdomeheight", -1.0f, -0.5f, 1.0f); // override
REGVAR("fogdomemin", 0.0f, 0.0f, 1.0f); // override
REGVAR("fogdomemax", 0.0f, 0.0f, 1.0f); // override
REGVAR("fogdomecap", 0, 1, 1); // override
REGVAR("fogdomeclip", 0.0f, 1.0f, 1.0f); // override
REGVAR("fogdomecolour", 0, 0, 0xFFFFFF, ICB({ fogdomecolor = bvec((curv>>16)&0xFF, (curv>>8)&0xFF, curv&0xFF); })); // override
REGVAR("sparklyfix", 0, 0, 1, NULL, true);
REGVAR("showsky", 0, 1, 1);
REGVAR("clipsky", 0, 1, 1);
REGVAR("clampsky", 0, 1, 1);
REGVAR("fogdomeclouds", 0, 1, 1); // override
REGVAR("skytexture", 0, 1, 1); // override // globalname was useskytexture

#endif

#ifdef CLIENT
// engine/shader.cpp - just for test now

REGVAR("shaders", -1, -1, 1, ICB({ initwarning("shaders"); }));
#endif

/*
engine/renderva.cpp:VAR(oqfrags, 0, 8, 64);
engine/renderva.cpp:VAR(oqwait, 0, 1, 1);
engine/renderva.cpp:VAR(oqmm, 0, 4, 8);
engine/renderva.cpp:HVAR(outline, 0, 0, 0xFFFFFF);
engine/renderva.cpp:VAR(dtoutline, 0, 1, 1);
engine/renderva.cpp:HVAR(blendbrushcolor, 0, 0x0000C0, 0xFFFFFF);
engine/renderva.cpp:VAR(oqdist, 0, 256, 1024);
engine/renderva.cpp:VAR(zpass, 0, 1, 1);
engine/renderva.cpp:VAR(glowpass, 0, 1, 1);
engine/renderva.cpp:VAR(envpass, 0, 1, 1);
engine/renderva.cpp:VAR(batchgeom, 0, 1, 1);
engine/renderva.cpp:VARR(causticscale, 0, 100, 10000);
engine/renderva.cpp:VARR(causticmillis, 0, 75, 1000);
engine/renderva.cpp:VARFP(caustics, 0, 1, 1, loadcaustics());
engine/renderva.cpp:VAR(oqgeom, 0, 1, 1);
engine/renderva.cpp:VAR(dbgffsm, 0, 0, 1);
engine/renderva.cpp:VAR(dbgffdl, 0, 0, 1);
engine/renderva.cpp:VAR(ffdlscissor, 0, 1, 1);
engine/serverbrowser.cpp:VARP(searchlan, 0, 0, 1);
engine/serverbrowser.cpp:VARP(servpingrate, 1000, 5000, 60000);
engine/serverbrowser.cpp:VARP(servpingdecay, 1000, 15000, 60000);
engine/serverbrowser.cpp:VARP(maxservpings, 0, 10, 1000);
engine/server.cpp:VARN(updatemaster, allowupdatemaster, 0, 1, 1);
engine/server.cpp:SVARF(mastername, server::defaultmaster(), disconnectmaster());
engine/server.cpp:VAR(serveruprate, 0, 0, INT_MAX);
engine/server.cpp:SVAR(serverip, "");
engine/server.cpp:VARF(serverport, 0, server::serverport(), 0xFFFF, { if(!serverport) serverport = server::serverport(); });
engine/shader.cpp:VAR(reservevpparams, 1, 16, 0);
engine/shader.cpp:VAR(maxvpenvparams, 1, 0, 0);
engine/shader.cpp:VAR(maxvplocalparams, 1, 0, 0);
engine/shader.cpp:VAR(maxfpenvparams, 1, 0, 0);
engine/shader.cpp:VAR(maxfplocalparams, 1, 0, 0);
engine/shader.cpp:VAR(maxtexcoords, 1, 0, 0);
engine/shader.cpp:VAR(maxvsuniforms, 1, 0, 0);
engine/shader.cpp:VAR(maxfsuniforms, 1, 0, 0);
engine/shader.cpp:VAR(maxvaryings, 1, 0, 0);
engine/shader.cpp:VAR(dbgshader, 0, 0, 2);
engine/shader.cpp:VAR(dbgubo, 0, 0, 1);
engine/shader.cpp:VARFN(shaders, useshaders, -1, -1, 1, initwarning("shaders"));
engine/shader.cpp:VARF(shaderprecision, 0, 0, 2, initwarning("shader quality"));
engine/shader.cpp://VARF(forceglsl, 0, 0, 1, initwarning("shaders"));
engine/shader.cpp:VAR(reserveshadowmaptc, 1, 0, 0);
engine/shader.cpp:VAR(reservedynlighttc, 1, 0, 0);
engine/shader.cpp:VAR(minimizedynlighttcusage, 1, 0, 0);
engine/shader.cpp:VAR(defershaders, 0, 1, 1);
engine/shader.cpp:VARF(nativeshaders, 0, 1, 1, fixshaderdetail());
engine/shader.cpp:VARFP(shaderdetail, 0, MAXSHADERDETAIL, MAXSHADERDETAIL, fixshaderdetail());
engine/shader.cpp:VAR(maxtmus, 1, 0, 0);
engine/shader.cpp:VAR(nolights, 1, 0, 0);
engine/shader.cpp:VAR(nowater, 1, 0, 0);
engine/shader.cpp:VAR(nomasks, 1, 0, 0);
engine/shadowmap.cpp:VARP(shadowmap, 0, 0, 1);
engine/shadowmap.cpp:VARFP(shadowmapsize, 7, 9, 11, cleanshadowmap());
engine/shadowmap.cpp:VARP(shadowmapradius, 64, 96, 256);
engine/shadowmap.cpp:VAR(shadowmapheight, 0, 32, 128);
engine/shadowmap.cpp:VARP(ffshadowmapdist, 128, 1024, 4096);
engine/shadowmap.cpp:VARP(shadowmapdist, 128, 256, 512);
engine/shadowmap.cpp:VARFP(fpshadowmap, 0, 0, 1, cleanshadowmap());
engine/shadowmap.cpp:VARFP(shadowmapprecision, 0, 0, 1, cleanshadowmap());
engine/shadowmap.cpp:HVARFR(shadowmapambient, 0, 0, 0xFFFFFF,
engine/shadowmap.cpp:VARP(shadowmapintensity, 0, 40, 100);
engine/shadowmap.cpp:VARP(blurshadowmap, 0, 1, 3);
engine/shadowmap.cpp:VARP(blursmsigma, 1, 100, 200);
engine/shadowmap.cpp:VAR(shadowmapcasters, 1, 0, 0);
engine/shadowmap.cpp:VARFR(shadowmapangle, 0, 0, 360, setshadowdir(shadowmapangle));
engine/shadowmap.cpp:VARP(shadowmapbias, 0, 5, 1024);
engine/shadowmap.cpp:VARP(shadowmappeelbias, 0, 20, 1024);
engine/shadowmap.cpp:VAR(smdepthpeel, 0, 1, 1);
engine/shadowmap.cpp:VAR(smoothshadowmappeel, 1, 0, 0);
engine/shadowmap.cpp:VAR(ffsmscissor, 0, 1, 1);
engine/shadowmap.cpp:VAR(debugsm, 0, 0, 1);
engine/skelmodel.h:VARP(gpuskel, 0, 1, 1);
engine/skelmodel.h:VARP(matskel, 0, 1, 1);
engine/sound.cpp:VARFP(soundvol, 0, 255, 255, if(!soundvol) { stopchannels(); setmusicvol(0); });
engine/sound.cpp:VARFP(musicvol, 0, 128, 255, setmusicvol(soundvol ? musicvol : 0));
engine/sound.cpp:VARF(soundchans, 1, 32, 128, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));
engine/sound.cpp:VARF(soundfreq, 0, MIX_DEFAULT_FREQUENCY, 44100, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));
engine/sound.cpp:VARF(soundbufferlen, 128, 1024, 4096, initwarning("sound configuration", INIT_RESET, CHANGE_SOUND));
engine/sound.cpp:VAR(uwambient, 0, 0, 1);
engine/sound.cpp:VAR(stereo, 0, 1, 1);
engine/sound.cpp:VARP(maxsoundradius, 0, 340, 10000);
engine/sound.cpp:VARP(maxsoundsatonce, 0, 5, 100);
engine/sound.cpp:VAR(dbgsound, 0, 0, 1);
engine/sound.cpp:VARFP(mumble, 0, 1, 1, { if(mumble) initmumble(); else closemumble(); });
engine/sound.cpp:VARFP(mumble, 0, 0, 1, { if(mumble) initmumble(); else closemumble(); });
engine/texture.cpp:VAR(hwtexsize, 1, 0, 0);
engine/texture.cpp:VAR(hwcubetexsize, 1, 0, 0);
engine/texture.cpp:VAR(hwmaxaniso, 1, 0, 0);
engine/texture.cpp:VARFP(maxtexsize, 0, 0, 1<<12, initwarning("texture quality", INIT_LOAD));
engine/texture.cpp:VARFP(reducefilter, 0, 1, 1, initwarning("texture quality", INIT_LOAD));
engine/texture.cpp:VARFP(texreduce, 0, 0, 12, initwarning("texture quality", INIT_LOAD));
engine/texture.cpp:VARFP(texcompress, 0, 1<<10, 1<<12, initwarning("texture quality", INIT_LOAD));
engine/texture.cpp:VARFP(texcompressquality, -1, -1, 1, setuptexcompress());
engine/texture.cpp:VARFP(trilinear, 0, 1, 1, initwarning("texture filtering", INIT_LOAD));
engine/texture.cpp:VARFP(bilinear, 0, 1, 1, initwarning("texture filtering", INIT_LOAD));
engine/texture.cpp:VARFP(aniso, 0, 0, 16, initwarning("texture filtering", INIT_LOAD));
engine/texture.cpp:VARFP(hwmipmap, 0, 0, 1, initwarning("texture filtering", INIT_LOAD));
engine/texture.cpp:VARFP(usenp2, 0, 0, 1, initwarning("texture quality", INIT_LOAD));
engine/texture.cpp:VAR(usedds, 0, 1, 1);
engine/texture.cpp:VAR(dbgdds, 0, 0, 1);
engine/texture.cpp:VARP(autocompactvslots, 0, 256, 0x10000);
engine/texture.cpp:VARFP(envmapsize, 4, 7, 10, setupmaterials());
engine/texture.cpp:VAR(envmapradius, 0, 128, 10000);
engine/texture.cpp:VAR(aaenvmap, 0, 2, 4);
engine/texture.cpp:VARP(compresspng, 0, 9, 9);
engine/texture.cpp:VARP(compresstga, 0, 1, 1);
engine/texture.cpp:VARP(screenshotformat, 0, IMG_PNG, NUMIMG-1);
engine/texture.cpp:SVARP(screenshotdir, "");
engine/water.cpp:VARFP(waterreflect, 0, 1, 1, { cleanreflections(); preloadwatershaders(); });
engine/water.cpp:VARFP(waterrefract, 0, 1, 1, { cleanreflections(); preloadwatershaders(); });
engine/water.cpp:VARFP(waterenvmap, 0, 1, 1, { cleanreflections(); preloadwatershaders(); });
engine/water.cpp:VARFP(waterfallrefract, 0, 0, 1, { cleanreflections(); preloadwatershaders(); });
engine/water.cpp:VARP(watersubdiv, 0, 2, 3);
engine/water.cpp:VARP(waterlod, 0, 1, 3);
engine/water.cpp:VARFP(vertwater, 0, 1, 1, allchanged());
engine/water.cpp:VARP(reflectdist, 0, 2000, 10000);
engine/water.cpp:HVARFR(watercolour, 0, 0x144650, 0xFFFFFF,
engine/water.cpp:VARR(waterfog, 0, 150, 10000);
engine/water.cpp:HVARFR(waterfallcolour, 0, 0, 0xFFFFFF,
engine/water.cpp:HVARFR(lavacolour, 0, 0xFF4000, 0xFFFFFF,
engine/water.cpp:VARR(lavafog, 0, 50, 10000);
engine/water.cpp:VARR(waterspec, 0, 150, 1000);
engine/water.cpp:VAR(oqwater, 0, 2, 2);
engine/water.cpp:VARFP(waterfade, 0, 1, 1, { cleanreflections(); preloadwatershaders(); });
engine/water.cpp:VARFP(reflectsize, 6, 8, 10, cleanreflections());
engine/water.cpp:VARP(maxreflect, 1, 1, 8);
engine/water.cpp:VAR(maskreflect, 0, 2, 16);
engine/water.cpp:VAR(reflectscissor, 0, 1, 1);
engine/water.cpp:VAR(reflectvfc, 0, 1, 1);
engine/water.cpp:VARR(refractclear, 0, 0, 1);
engine/world.cpp:VARR(mapversion, 1, MAPVERSION, 0);
engine/world.cpp:VARNR(mapscale, worldscale, 1, 0, 0);
engine/world.cpp:VARNR(mapsize, worldsize, 1, 0, 0);
engine/world.cpp:SVARR(maptitle, "Untitled Map by Unknown");
engine/world.cpp:VAR(octaentsize, 0, 128, 1024);
engine/world.cpp:VAR(entselradius, 0, 2, 10);
engine/world.cpp:VARF(entediting, 0, 0, 1, { if(!entediting) { entcancel(); efocus = enthover = -1; } });
engine/world.cpp:VAR(attachradius, 1, 100, 1000);
engine/world.cpp:VAR(entselsnap, 0, 0, 1);
engine/world.cpp:VAR(entmovingshadow, 0, 1, 1);
engine/world.cpp:VAR(showentradius, 0, 1, 1);
engine/world.cpp:VAR(entitysurf, 0, 0, 1);
engine/world.cpp:VARF(entmoving, 0, 0, 2,
engine/world.cpp:VAR(entautoviewdist, 0, 25, 100);
engine/world.cpp:VAR(entdrop, 0, 2, 3);
engine/worldio.cpp:VARP(savebak, 0, 2, 2);
engine/worldio.cpp:VAR(dbgvars, 0, 0, 1);
engine/3dgui.cpp:VARP(guiautotab, 6, 16, 40);
engine/3dgui.cpp:VARP(guiclicktab, 0, 1, 1); // INTENSITY: Click to switch tabs by default
engine/3dgui.cpp:VARP(guipushdist, 1, 4, 64);
engine/3dgui.cpp:FVARP(guisens, 1e-3f, 1, 1e3f);
engine/3dgui.cpp:VARNP(guifollow, useguifollow, 0, 1, 1);
engine/3dgui.cpp:VARNP(gui2d, usegui2d, 0, 1, 1);
fpsgame/client.cpp:    SVARP(chat_sound, "olpc/FlavioGaete/Vla_G_Major");
fpsgame/entities.cpp:    VAR(triggerstate, -1, 0, 1);
fpsgame/fps.cpp:    VAR(useminimap, 0, 0, 1); // do we want the minimap? Set from JS.
fpsgame/fps.cpp:    VARP(minminimapzoom, 0, 384, 10000); // minimal and maximal scale of minimap, some sort of "zoom"
fpsgame/fps.cpp:    VARP(maxminimapzoom, 1, 1024, 10000);
fpsgame/fps.cpp:    VAR(forceminminimapzoom, -1, -1, 10000); // these are not stored in cfg or across maps and are made for map-specific forcing.
fpsgame/fps.cpp:    VAR(forcemaxminimapzoom, -1, -1, 10000);
fpsgame/fps.cpp:    FVAR(minimapradius, 0.0f, 0.3f, 10.0f); // minimap size, relative to screen height (1.0 = full height), max is 10.0f (maybe someone will find usage?)
fpsgame/fps.cpp:    FVAR(minimapxpos, -10000.0f, 0.1f, 10000.0f); // minimap x position relative from right edge of screen (1.0 = one minimap size from right edge)
fpsgame/fps.cpp:    FVAR(minimapypos, -10000.0f, 0.1f, 10000.0f); // like above, but from top edge.
fpsgame/fps.cpp:    FVAR(minimaprotation, 0.0f, 0.0f, 360.0f); // rotation of minimap
fpsgame/fps.cpp:    VAR(minimapsides, 3, 10, 1000); // number of minimap sides. No need to make it bigger than 1000, 1000 is really smooth circle at very big sizes.
fpsgame/fps.cpp:    VAR(minimaprightalign, 0, 1, 1); // do we want to align minimap right? if this is 1, then we do, if 0, then it's aligned to left.
fpsgame/fps.cpp:    VARP(smoothmove, 0, 75, 100);
fpsgame/fps.cpp:    VARP(smoothdist, 0, 32, 64);
fpsgame/fps.cpp:    IVARP(startmenu, 0, 1, 1);
fpsgame/fps.cpp:    IVARP(hudgun, 0, 1, 1);
fpsgame/fps.cpp:    IVARP(hudgunsway, 0, 1, 1);
fpsgame/fps.cpp:    IVARP(teamhudguns, 0, 1, 1);
fpsgame/scoreboard.cpp:    VARP(scoreboard2d, 0, 1, 1);
fpsgame/scoreboard.cpp:    VARP(showpj, 0, 1, 1); // Kripken
fpsgame/scoreboard.cpp:    VARP(showping, 0, 1, 1);
fpsgame/scoreboard.cpp:    VARP(showspectators, 0, 1, 1);
fpsgame/scoreboard.cpp:    VARFN(scoreboard, showscoreboard, 0, 0, 1, scoreboard.show(showscoreboard!=0));
intensity/client_engine_additions.cpp:VAR(CameraControl::cameraMoveDist, 5, 10, 200);                 // Distance camera moves per iteration
intensity/client_engine_additions.cpp://VAR(CameraControl::cameraMoveIters, MIN_CAMERA_MOVE_ITERS, 14, 18); // Number of iterations to move camera DEPRECATED
intensity/client_engine_additions.cpp:VAR(cam_dist, 0, 50, 200);
intensity/client_engine_additions.cpp:FVARP(cameraheight, 0, 10, 50); // How much higher than the player to set the camera
intensity/client_engine_additions.cpp:FVAR(smoothcamera, 0, 0.2, 100.0); // Smoothing factor for the smooth camera. 0 means no smoothing
intensity/client_engine_additions.cpp:FVARP(cameraavoid, 0, 0.33, 1); // 1 means the camera is 100% away from the closest obstacle (and therefore on the player). 0 means it is on that obstacle. 0.5 means it is midway between them.
intensity/client_engine_additions.cpp:SVAR(entity_gui_title, "");
intensity/client_engine_additions.cpp:VAR(num_entity_gui_fields, 0, 0, 13);
intensity/client_system.cpp:VAR(can_edit, 0, 0, 1);
intensity/client_system.cpp:SVARP(last_uploaded_map_asset, "");
intensity/intensity_gui.cpp:SVAR(message_title, "");
intensity/intensity_gui.cpp:SVAR(message_content, "");
intensity/intensity_gui.cpp:SVAR(input_title, "");
intensity/intensity_gui.cpp:SVAR(input_content, "");
intensity/intensity_gui.cpp:SVAR(input_data, "");
intensity/master.cpp:SVARP(entered_username, ""); // Persisted - uses "-" instead of "@", to get around sauer issue
intensity/master.cpp:SVAR(true_username, "");  // Has "@", can be sent to server to login
intensity/master.cpp:SVAR(entered_password, "");
intensity/master.cpp:SVARP(hashed_password, "");
intensity/master.cpp:VAR(have_master, 0, 1, 1);
intensity/master.cpp:VAR(logged_into_master, 0, 0, 1);
intensity/master.cpp:SVAR(error_message, ""); // TODO: Move
intensity/script_engine_lua_embedding.h:    VARP(blood, 0, 1, 1);
intensity/script_engine_lua_embedding.h:    VARP(ragdoll, 0, 1, 1);
intensity/server_system.cpp:VARR(fog, 1, 2, 300000);
intensity/server_system.cpp:VAR(thirdperson, 0, 1, 2);
intensity/targeting.cpp:VAR(has_mouse_target, 0, 0, 1);
shared/stream.cpp:VAR(dbggz, 0, 0, 1);
shared/zip.cpp:VAR(dbgzip, 0, 0, 1);*/
