// animmodel

REGVAR("lightmodels", 0, 1, 1, _lambda_(int a,int b,int c,int d) { preloadmodelshaders(); });
REGVAR("envmapmodels", 0, 1, 1, _lambda_(int a,int b,int c,int d) { preloadmodelshaders(); });
REGVAR("glowmodels", 0, 1, 1, _lambda_(int a,int b,int c,int d) { preloadmodelshaders(); });
REGVAR("bumpmodels", 0, 1, 1, _lambda_(int a,int b,int c,int d) { preloadmodelshaders(); });
