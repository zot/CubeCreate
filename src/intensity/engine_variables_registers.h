// engine/animmodel.h

REGVAR("lightmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("envmapmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("glowmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("bumpmodels", 0, 1, 1, ICB({ preloadmodelshaders(); }), true);
REGVAR("fullbrightmodels", 0, 0, 200, NULL, true);

// engine/blend.cpp

REGVAR("blendpaintmode", 0, 0, 5, ICB({
    if(!cur) stoppaintblendmap();
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

REGVAR("rate", 0, 0, 25000, ICB({ setrate(cur); }));
REGVAR("throttle_interval", 0, 5, 30, ICB({ throttle(); }));
REGVAR("throttle_accel", 0, 2, 32, ICB({ throttle(); }));
REGVAR("throttle_decel", 0, 2, 32, ICB({ throttle(); }));
REGVAR("connectname", "");
REGVAR("connectport", 0, 0, 0xFFFF);

#ifdef CLIENT
// engine/console.cpp

extern vector<cline> conlines;

REGVAR("maxcon", 10, 200, 1000, ICB({ while(conlines.length() > cur) delete[] conlines.pop().line; }), true);
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

// engine/shader.cpp - just for test now

REGVAR("shaders", -1, -1, 1, ICB({ initwarning("shaders"); }));
#endif
