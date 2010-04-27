/*
 *=============================================================================
 * Copyright (c) 2010 T7g t7gt7g@gmail.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *-----------------------------------------------------------------------------
 * SkyManager.js - Sky Manager plugin for the Intensity Engine platform.
 * As of writing the additional functionality needed for this script is not 
 * included in the base engine. It may be in the future but if you have problems
 * keep this in mind.
 *=============================================================================
 */

Library.include('library/' + Global.LIBRARY_VERSION + '/Editing');

// These values are "leashes" that the cloud manager will keep on certain variables. Lower/upper limit.
fArrCloudLayerAlpha = [ 0.0, 1.0 ];			fArrAltCloudLayerAlpha = [ 0.0, 1.0 ];
fArrCloudLayerHeight = [ 0.03, 0.47 ];		fArrAltCloudLayerHeight = [ 0.01, 0.37 ];
fArrCloudLayerScale = [ 0.37, 3.0 ];		fArrAltCloudLayerScale = [ 0.3, 7.0 ];
fArrCloudLayerScroll = [ -0.001 , -0.007 ];	fArrAltCloudLayerScroll = [ 0.001, 0.007 ];
fArrCloudLayerSpin = [ -0.001, -1.0 ];		fArrAltCloudLayerSpin = [ 0.001, 1.0 ];

fArrModelAmbient = [ 1.0, 37.0 ]; // The extents we want our models to light between.

sArrCloudLayers = [ 't7g/clouds0', 't7g/clouds1', 't7g/clouds2', 't7g/clouds3', 't7g/clouds4', 't7g/clouds5' ];
rainCloudLayer = 't7g/clouds5';

SkyManager = {

	CeilingCat: {
	////////////////////////////////////////////////////////////////////////////////////////////////
	// I see you have met my state variables, I hope you are not too distressed by their numbers-
	// they only change when absolutely necessary and I acknowledge I could've wrote a little parser
	// and done all this with just a few state variables but that would have been more work for me,
	// and probably would've at least somewhat confused anyone trying to modify this to suit them.
	////////////////////////////////////////////////////////////////////////////////////////////////
		inTransition: new StateBoolean({ clientWrite: false }),
		isRaining: new StateBoolean({ clientWrite: false }),
		syncSkyRequest: new StateBoolean({ clientSet: true }),
	// The nextXXXXX state variables signal the clients to a new transition, this is not done often.
		nextStarbox: new StateString({ clientWrite: false }),
		nextSkybox: new StateString({ clientWrite: false }),
		nextSunbox: new StateString({ clientWrite: false }),
		nextCloudbox: new StateString({ clientWrite: false }),
		nextCloudLayer: new StateString({ clientWrite: false }),
		nextAltCloudLayer: new StateString({ clientWrite: false }),

		nextTintStars: new StateInteger({ clientWrite: false }),
		nextTintSky: new StateInteger({ clientWrite: false }),
		nextTintSun: new StateInteger({ clientWrite: false }),
		nextTintClouds: new StateInteger({ clientWrite: false }),
		nextTintCloudLayer: new StateInteger({ clientWrite: false }),
		nextTintAltCloudLayer: new StateInteger({ clientWrite: false }),
		nextTintFog: new StateInteger({ clientWrite: false }),
		nextTintAmbient: new StateInteger({ clientWrite: false }),

		nextAlphaSky: new StateFloat({ clientWrite: false }),
		nextAlphaSun: new StateFloat({ clientWrite: false }),
		nextAlphaClouds: new StateFloat({ clientWrite: false }),
		nextAlphaCloudLayer: new StateFloat({ clientWrite: false }),
		nextAlphaAltCloudLayer: new StateFloat({ clientWrite: false }),

		nextAlphaAltCloudLayer: new StateFloat({ clientWrite: false }),
		nextAlphaCloudLayer: new StateFloat({ clientWrite: false }),

		nextHeightAltCloudLayer: new StateFloat({ clientWrite: false }),
		nextHeightCloudLayer: new StateFloat({ clientWrite: false }),

		nextScaleAltCloudLayer: new StateFloat({ clientWrite: false }),
		nextScaleCloudLayer: new StateFloat({ clientWrite: false }),

		nextScrollXAltCloudLayer: new StateFloat({ clientWrite: false }),
		nextScrollYAltCloudLayer: new StateFloat({ clientWrite: false }),

		nextScrollXCloudLayer: new StateFloat({ clientWrite: false }),
		nextScrollYCloudLayer: new StateFloat({ clientWrite: false }),

		nextSpinAltCloudLayer: new StateFloat({ clientWrite: false }),
		nextSpinCloudLayer: new StateFloat({ clientWrite: false }),

		nextModelAmbient: new StateFloat({ clientWrite: false }),
		nextModelSpec: new StateFloat({ clientWrite: false }), 
		
		nextFogDist: new StateInteger({ clientWrite: false }),
	// The syncXXXXX state variables are used to sync new clients with the sky manager's state.
		syncStarbox: new StateString({ clientWrite: false }),
		syncSkybox: new StateString({ clientWrite: false }),
		syncSunbox: new StateString({ clientWrite: false }),
		syncCloudbox: new StateString({ clientWrite: false }),
		syncCloudLayer: new StateString({ clientWrite: false }),
		syncAltCloudLayer: new StateString({ clientWrite: false }),

		syncTintStars: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintSky: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintSun: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintClouds: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintCloudLayer: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintAltCloudLayer: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintAmbient: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncTintFog: new StateInteger({ clientWrite: false }, { hasHistory: false }),

		syncAlphaSky: new StateFloat({ clientWrite: false }, { hasHistory: false }),
		syncAlphaSun: new StateFloat({ clientWrite: false }, { hasHistory: false }),
		syncAlphaClouds: new StateFloat({ clientWrite: false }, { hasHistory: false }),
		syncAlphaCloudLayer: new StateFloat({ clientWrite: false }, { hasHistory: false }),
		syncAlphaAltCloudLayer: new StateFloat({ clientWrite: false }, { hasHistory: false }),

		// We could also sync the yaw of the skybox and cloudbox but really, who cares?
		syncYawStars: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncYawSun: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		syncMidnight: new StateInteger({ clientWrite: false }, { hasHistory: false }),

		syncModelAmbient: new StateFloat({ clientWrite: false }, { hasHistory: false }),
		syncModelSpec: new StateFloat({ clientWrite: false }, { hasHistory: false }),

		syncFogDist: new StateInteger({ clientWrite: false }, { hasHistory: false }),
		////////////////////////////////////////////////////////////////////////////////////////////
		// Just a note, if you set vars here like this.curSkybox, the clientActivate portion doesn't
		// ever seem to acknowledge them and will spew errors at you, at least it shrieked at me.
		// I don't know why- I tried a few different ways, if you can do better, then by all means;
		////////////////////////////////////////////////////////////////////////////////////////////
        init: function() {
			this.inTransition = true;
			this.isRaining = false;
			this.syncSkyRequest = false;

			this.nextStarbox = "t7g/nightsky";
			this.nextSkybox = "t7g/haze";
			this.nextSunbox = "t7g/sun";
			this.nextCloudbox = "t7g/horizon";
			this.nextCloudLayer = "t7g/clouds2";
			this.nextAltCloudLayer = "t7g/clouds5";

			this.nextTintStars = intWHITE;
			this.nextTintSky = intRED;
			this.nextTintSun = intRED;
			this.nextTintClouds = intORANGE;
			this.nextTintCloudLayer = intWHITE;
			this.nextTintAltCloudLayer = intWHITE;
			this.nextTintFog = intRED;
			this.nextTintAmbient = intAMBIENT;

			this.nextAlphaSky = 0.0;
			this.nextAlphaSun = 1.0;
			this.nextAlphaClouds = 0.0;
			this.nextAlphaCloudLayer = 0.1;
			this.nextAlphaAltCloudLayer = 0.0;

			this.nextHeightAltCloudLayer = 0.1;
			this.nextHeightCloudLayer = 0.2;
			this.nextScaleAltCloudLayer = 2.0;
			this.nextScaleCloudLayer = 1.0;
			this.nextScrollXAltCloudLayer = 0.001;
			this.nextScrollYAltCloudLayer = 0.001;
			this.nextScrollXCloudLayer = -0.003;
			this.nextScrollYCloudLayer = -0.003;
			this.nextSpinAltCloudLayer = 0.3;
			this.nextSpinCloudLayer = 0.7;

			this.nextModelAmbient = 1.0;
			this.nextModelSpec = 1.0;

			this.dayTime = 1; 			// The server's idea of what time of day it is.
			this.secondsElapsed = 0;	// I use this to let midnightSync know when it's time.

			this.defYawStars = 0; // Default star yaw, I can't see why you'd need to change this.
			this.defYawSun = 250; // Default sun yaw, 0/360 = horizon, 270/90 = Midnight/Noon (sort-of)
        },
		////////////////////////////////////////////////////////////////////////////////////////////
		// These are the routines and variables the client uses to track and control sky transitions.
		////////////////////////////////////////////////////////////////////////////////////////////
        clientActivate: function() {
			this.curStarbox = "t7g/nightsky";
			this.curSkybox = "t7g/haze";
			this.curSunbox = "t7g/sun";
			this.curCloudbox = "t7g/horizon";
			this.curCloudLayer = "t7g/clouds2";
			this.curAltCloudLayer = "t7g/clouds5";

			this.curTintStars = intWHITE;			// Really, these can be anything, the values you
			this.curTintSky = intRED;				// see here are nothing more than the ones I used
			this.curTintSun = intRED;				// before I wrote the later code that made their
			this.curTintClouds = intORANGE;			// use this early unnecessary, that being said.
			this.curTintCloudLayer = intWHITE;		// Leave them alone if you don't know what you're
			this.curTintAltCloudLayer = intWHITE;   // doing. They need to be the same everywhere or
			this.curTintFog	= intRED;				// you'll see strange colors or other strangeness.
			this.curTintAmbient = intAMBIENT;

			this.curAlphaSky = 0.0;
			this.curAlphaSun = 1.0;
			this.curAlphaClouds = 0.0;
			this.curAlphaCloudLayer = 0.1;
			this.curAlphaAltCloudLayer = 0.0;

			this.curHeightAltCloudLayer = 0.1;
			this.curHeightCloudLayer = 0.2;
			this.curScaleAltCloudLayer = 2.0;
			this.curScaleCloudLayer = 1.0;
			this.curScrollXAltCloudLayer = 0.001;
			this.curScrollYAltCloudLayer = 0.001;
			this.curScrollXCloudLayer = -0.003;
			this.curScrollYCloudLayer = -0.003;
			this.curSpinAltCloudLayer = 0.3;
			this.curSpinCloudLayer = 0.7;

			this.curModelAmbient = 1.0;
			this.curModelSpec = 0.0;

			this.rateSpin = parseFloat(360 / this.intsecDayLength); // 360 degrees that the stars will spin.			

			this.syncSky = false;
			this.syncWait = true;	// We can't set state vars this early, so we wait a tick.
			this.syncFade = false;	// Long story...
			this.lastMidnight = 0;	// Midnight sync will let us know how long since the last.
			this.rainLock = false;	// Lets not constantly call suspend or awaken for no reason.

            GameManager.getSingleton().eventManager.add({
                secondsBefore: 0,
                secondsBetween: this.intsecActionPer,
                func: bind(function() {
					if(this.inTransition && this.syncSky) {
						this.runTransitions();
					} else if(!this.syncSky && !this.syncSkyRequest && !this.syncWait) {
						this.syncSetupSky();
					} else if(this.syncWait) {
						this.syncSkyRequest = true; this.weatherManager(); this.syncWait = false;
					}

					if(this.isRaining && this.rainLock) {
						GameManager.getSingleton().eventManager.awaken(this.addDropEvent);
						this.rainLock = false;
					}
					else if(!this.isRaining && !this.rainLock){
						GameManager.getSingleton().eventManager.suspend(this.addDropEvent);
						this.rainLock = true;
					}


					if(this.syncMidnight > this.lastMidnight) this.midnightSync();

                }, this),
                entity: this,
			});
            			
        },
		////////////////////////////////////////////////////////////////////////////////////////////
		// Client side; Sun box sync and sky state sync routines. //
		////////////////////////////////////////////////////////////////////////////////////////////
		midnightSync: function() {
			// Sauer just can't be relied upon it seems to spin the skybox at a measurable rate without drifting.
			// This little bitty is designed to help alleviate that issue, resets everyone's sun when told.
			// I'm only doing this at night as well, the player would obviously notice it during the day.
			// Keep in mind this relies on rendersky.cpp using skymillis as it's sun spin ref point, not lastmillis.
			// (It also has to have my code that resets skymillis upon yawing the sun to function properly)
			Map.yawSun(250);
			this.lastMidnight = this.syncMidnight;
		},

		syncSetupSky: function() {
			if(this.curHeightAltCloudLayer) Map.altCloudHeight(this.curHeightAltCloudLayer);
			if(this.curHeightCloudLayer) Map.cloudHeight(this.curHeightCloudLayer);
			if(this.curScaleAltCloudLayer) Map.altCloudScale(this.curScaleAltCloudLayer);
			if(this.curScaleCloudLayer) Map.cloudScale(this.curScaleCloudLayer);
			if(this.curScrollXAltCloudLayer) Map.altCloudScrollX(this.curScrollXAltCloudLayer);
			if(this.curScrollYAltCloudLayer) Map.altCloudScrollY(this.curScrollYAltCloudLayer);
			if(this.curScrollXCloudLayer) Map.cloudScrollX(this.curScrollXCloudLayer);
			if(this.curScrollYCloudLayer) Map.cloudScrollY(this.curScrollYCloudLayer);
			if(this.curSpinAltCloudLayer) Map.spinAltCloudLayer(this.curSpinAltCloudLayer);
			if(this.curSpinCloudLayer) Map.spinCloudLayer(this.curSpinCloudLayer);

			if(this.curStarbox) Map.loadStars(this.curStarbox);
			if(this.curSkybox) Map.loadSky(this.curSkybox);
			if(this.curSunbox) Map.loadSun(this.curSunbox);
			if(this.curCloudbox) Map.loadClouds(this.curCloudbox);
			if(this.curCloudLayer) Map.loadCloudLayer(this.curCloudLayer);
			if(this.curAltCloudLayer) Map.loadAltCloudLayer(this.curAltCloudLayer);

			if(this.curTintStars) Map.tintStars(this.iToR(this.curTintStars), this.iToG(this.curTintStars), this.iToB(this.curTintStars));
			if(this.curTintSky) Map.tintSky(this.iToR(this.curTintSky), this.iToG(this.curTintSky), this.iToB(this.curTintSky));
			if(this.curTintSun) Map.tintSun(this.iToR(this.curTintSun), this.iToG(this.curTintSun), this.iToB(this.curTintSun));
			if(this.curTintClouds) Map.tintClouds (this.iToR(this.curTintClouds), this.iToG(this.curTintClouds), this.iToB(this.curTintClouds));
			if(this.curTintCloudLayer) Map.tintCloudLayer(this.iToR(this.curTintCloudLayer), this.iToG(this.curTintCloudLayer), this.iToB(this.curTintCloudLayer));
			if(this.curTintAltCloudLayer) Map.tintAltCloudLayer(this.iToR(this.curTintAltCloudLayer), this.iToG(this.curTintAltCloudLayer), this.iToB(this.curTintAltCloudLayer));
			if(this.curTintFog) Map.tintFog(this.iToR(this.curTintFog), this.iToG(this.curTintFog), this.iToB(this.curTintFog));
			if(this.curTintAmbient) Map.tintAmbient(this.iToR(this.curTintAmbient), this.iToG(this.curTintAmbient), this.iToB(this.curTintAmbient));
			// Received all the state variables to describe the sky state, so lets set them now.
			this.curStarbox = this.syncStarbox;
			this.curSkybox = this.syncSkybox;
			this.curSunbox = this.syncSunbox;
			this.curCloudbox = this.syncCloudbox;
			this.curCloudLayer = this.syncCloudLayer;
			this.curAltCloudLayer = this.syncAltCloudLayer;

			Map.loadCloudLayer(this.curAltCloudLayer); Map.loadCloudLayer(this.curCloudLayer);

			this.curTintStars = this.syncTintStars;
			this.curTintSky = this.syncTintSky;
			this.curTintSun = this.syncTintSun;
			this.curTintClouds = this.syncTintClouds;
			this.curTintCloudLayer = this.syncTintCloudLayer;
			this.curTintAltCloudLayer = this.syncTintAltCloudLayer;
			this.curTintFog	= this.syncTintFog;
			this.curTintAmbient = this.syncTintAmbient;

			this.curAlphaSky = this.syncAlphaSky;
			this.curAlphaSun = this.syncAlphaSun;
			this.curAlphaClouds = this.syncAlphaClouds;
			this.curAlphaCloudLayer = this.syncAlphaCloudLayer;
			this.curAlphaAltCloudLayer = this.syncAlphaAltCloudLayer;

			this.curModelAmbient = this.syncModelAmbient;
			this.curModelSpec = this.syncModelSpec;

			this.curYawStars = this.syncYawStars;
			this.curYawSun = this.syncYawSun;

			this.curHeightAltCloudLayer = this.nextHeightAltCloudLayer;
			this.curHeightCloudLayer = this.nextHeightCloudLayer;
			this.curScaleAltCloudLayer = this.nextScaleAltCloudLayer;
			this.curScaleCloudLayer = this.nextScaleCloudLayer;
			this.curScrollXAltCloudLayer = this.nextScrollXAltCloudLayer;
			this.curScrollYAltCloudLayer = this.nextScrollYAltCloudLayer;
			this.curScrollXCloudLayer = this.nextScrollXCloudLayer;
			this.curScrollYCloudLayer = this.nextScrollYCloudLayer;
			this.curSpinAltCloudLayer = this.nextSpinAltCloudLayer;
			this.curSpinCloudLayer = this.nextSpinCloudLayer;

			Map.cloudClip(0.2);

			this.syncFade = true;
			this.syncSky = true;
		},
		////////////////////////////////////////////////////////////////////////////////////////////
		// Day/night transition client side control code. //
		////////////////////////////////////////////////////////////////////////////////////////////
		changeBoxen: function() {
			// Track and change boxes that the server tells us about.
			// One of our boxes has changed, we'll need to do something about that. Starting from the most often changed to last.
			if(this.curCloudLayer != this.nextCloudLayer && this.curAlphaCloudLayer == 0.0) {
				this.curCloudLayer = this.nextCloudLayer;
				Map.loadCloudLayer(this.curCloudLayer);							
			}
			if(this.curAltCloudLayer != this.nextAltCloudLayer && this.curAlphaAltCloudLayer == 0.0) {
				this.curAltCloudLayer = this.nextAltCloudLayer;
				Map.loadAltCloudLayer(this.curAltCloudLayer);
			}
			if(this.curCloudbox != this.nextCloudbox && this.curAlphaClouds == 0.0) {
				this.curCloudbox = this.nextCloudbox;
				Map.loadClouds(this.curCloudbox);
			}
			if(this.curSunbox != this.nextSunbox && this.curAlphaSun == 0.0) {
				this.curSunbox = this.nextSunbox;
				Map.loadSun(this.curSunbox);
			}
			if(this.curSkybox != this.nextSkybox && this.curAlphaSky == 0.0) {
				this.curSkybox = this.nextSkybox;
				Map.loadSky(this.curSkybox);
			}
			if(this.curStarbox != this.nextStarbox && this.curAlphaSky == 1.0) {
				this.curStarbox = this.nextStarbox;
				Map.loadStars(this.curStarbox);
			}
		},

		runTransitions: function() {
			// Just a cleaner way to run all the transition checks rather than doing it in clientActivate.
			this.runFadeStars();
			this.runFadeSky();
			this.runFadeSun();
			this.runFadeClouds();
			this.runFadeCloudLayer(); this.runFadeAltCloudLayer();
			this.runFadeFog();
			this.runFadeAmbient();
			this.runModelFade();
			this.runModelSpec();

			this.runCloudManagement();
			this.changeBoxen();

			if(this.syncFade) {
				Map.yawStars(parseFloat(this.curYawStars));
				Map.yawSun(parseFloat(this.curYawSun));
				Map.spinStars(this.rateSpin);
				Map.spinSun(this.rateSpin);
				Map.modelTweaks(1); // We enable this so we can tweak all models at once, which is not normal.
				this.syncFade = false;
			}
		},

		runCloudManagement: function() {
			if(this.curHeightAltCloudLayer != this.nextHeightAltCloudLayer) {
				this.curHeightAltCloudLayer = this.leashedFade(this.curHeightAltCloudLayer, this.nextHeightAltCloudLayer, fArrAltCloudLayerHeight);
				Map.altCloudHeight(this.curHeightAltCloudLayer);
			} else if(this.curHeightCloudLayer != this.nextHeightCloudLayer) {
				this.curHeightCloudLayer = this.leashedFade(this.curHeightCloudLayer, this.nextHeightCloudLayer, fArrCloudLayerHeight);
				Map.cloudHeight(this.curHeightCloudLayer);
			} else if(this.curScaleAltCloudLayer != this.nextScaleAltCloudLayer) {
				this.curScaleAltCloudLayer = this.dynamicScale(this.curScaleAltCloudLayer, this.nextScaleAltCloudLayer, fArrAltCloudLayerScale);
				Map.altCloudScale(this.curScaleAltCloudLayer);
			} else if(this.curScaleCloudLayer != this.nextScaleCloudLayer) {
				this.curScaleCloudLayer = this.dynamicScale(this.curScaleCloudLayer, this.nextScaleCloudLayer, fArrCloudLayerScale);
				Map.cloudScale(this.curScaleCloudLayer);
			} else if(this.curScrollXAltCloudLayer != this.nextScrollXAltCloudLayer) {
				this.curScrollXAltCloudLayer = this.dynamicFloatScroll(this.curScrollXAltCloudLayer, this.nextScrollXAltCloudLayer, fArrAltCloudLayerScroll);
				Map.altCloudScrollX(this.curScrollXAltCloudLayer);
			} else if(this.curScrollXCloudLayer != this.nextScrollXCloudLayer) {
				this.curScrollXCloudLayer = this.dynamicFloatScroll(this.curScrollXCloudLayer, this.nextScrollXCloudLayer, fArrCloudLayerScroll);
				Map.cloudScrollX(this.curScrollXCloudLayer);
			} else if(this.curScrollYAltCloudLayer != this.nextScrollYAltCloudLayer) {
				this.curScrollYAltCloudLayer = this.dynamicFloatScroll(this.curScrollYAltCloudLayer, this.nextScrollYAltCloudLayer, fArrAltCloudLayerScroll);
				Map.altCloudScrollY(this.curScrollYAltCloudLayer);
			} else if(this.curScrollYCloudLayer != this.nextScrollYCloudLayer) {
				this.curScrollYCloudLayer = this.dynamicFloatScroll(this.curScrollYCloudLayer, this.nextScrollYCloudLayer, fArrCloudLayerScroll);
				Map.cloudScrollY(this.curScrollYCloudLayer);
			} else if(this.curSpinAltCloudLayer != this.nextSpinAltCloudLayer) {
				this.curSpinAltCloudLayer = this.dynamicSpin(this.curSpinAltCloudLayer, this.nextSpinAltCloudLayer, fArrAltCloudLayerSpin);
				Map.spinAltCloudLayer(this.curSpinAltCloudLayer);
			} else if(this.curSpinCloudLayer != this.nextSpinCloudLayer) {
				this.curSpinCloudLayer = this.dynamicSpin(this.curSpinCloudLayer, this.nextSpinCloudLayer, fArrCloudLayerSpin);
				Map.spinCloudLayer(this.curSpinCloudLayer);
			}
		},

		runModelFade: function() { 
			if(this.curModelAmbient != this.nextModelAmbient) {
				this.curModelAmbient = this.modelAmbientFade(this.curModelAmbient, this.nextModelAmbient, fArrModelAmbient);
				Map.tweakModelAmbient(this.curModelAmbient);
			}
			if(this.syncFade) Map.tweakModelAmbient(this.curModelAmbient);
		},

		runModelSpec: function() { 
			if(this.curModelSpec != this.nextModelSpec) {
				this.curModelSpec = this.alphaFade(this.curModelSpec, this.nextModelSpec);
				Map.tweakModelSpec(this.curModelSpec);
			}
			if(this.syncFade) Map.tweakModelAmbient(this.curModelAmbient);
		},

		runFadeStars: function() {
			if(this.nextTintStars != this.curTintStars) {
				this.curTintStars = tintFade(this.curTintStars, this.nextTintStars);
				Map.tintStars(this.iToR(this.curTintStars), this.iToG(this.curTintStars), this.iToB(this.curTintStars));
			}
			if(this.syncFade) Map.tintStars(this.iToR(this.curTintStars), this.iToG(this.curTintStars), this.iToB(this.curTintStars));
		},

		runFadeSky: function() {
			if(this.nextTintSky != this.curTintSky) {
				this.curTintSky = this.tintFade(this.curTintSky, this.nextTintSky);
				Map.tintSky(this.iToR(this.curTintSky), this.iToG(this.curTintSky), this.iToB(this.curTintSky));
			}
			if(this.syncFade) Map.tintSky(this.iToR(this.curTintSky), this.iToG(this.curTintSky), this.iToB(this.curTintSky));

			if(this.nextAlphaSky != this.curAlphaSky) {
				this.curAlphaSky = this.alphaFade(this.curAlphaSky, this.nextAlphaSky);
				Map.alphaSky(this.curAlphaSky);
			}
			if(this.syncFade) Map.alphaSky(this.curAlphaSky);
		},

		runFadeSun: function() {
			if(this.nextTintSun != this.curTintSun) {
				this.curTintSun = this.tintFade(this.curTintSun, this.nextTintSun);
				Map.tintSun(this.iToR(this.curTintSun), this.iToG(this.curTintSun), this.iToB(this.curTintSun));
			}
			if(this.syncFade) Map.tintSun(this.iToR(this.curTintSun), this.iToG(this.curTintSun), this.iToB(this.curTintSun));

			if(this.nextAlphaSun != this.curAlphaSun) {
				this.curAlphaSun = this.nextAlphaSun;
				Map.alphaSun(this.curAlphaSun);
			}
			if(this.syncFade) Map.alphaSun(this.curAlphaSun);
		},

		runFadeClouds: function() {
			if(this.nextTintClouds != this.curTintClouds) { 
				this.curTintClouds = this.tintFade(this.curTintClouds, this.nextTintClouds);
				Map.tintClouds(this.iToR(this.curTintClouds), this.iToG(this.curTintClouds), this.iToB(this.curTintClouds));
			}
			if(this.syncFade) Map.tintClouds(this.iToR(this.curTintClouds), this.iToG(this.curTintClouds), this.iToB(this.curTintClouds));

			if(this.nextAlphaClouds != this.curAlphaClouds) {
				this.curAlphaClouds = this.alphaFade(this.curAlphaClouds, this.nextAlphaClouds);
				Map.alphaClouds(this.curAlphaClouds);
			}
			if(this.syncFade) Map.alphaClouds(this.curAlphaClouds);

		},

		runFadeCloudLayer: function() {
			if(this.nextTintCloudLayer != this.curTintCloudLayer) {
				this.curTintCloudLayer = this.tintFade(this.curTintCloudLayer, this.nextTintCloudLayer);
				Map.tintCloudLayer(this.iToR(this.curTintCloudLayer), this.iToG(this.curTintCloudLayer), this.iToB(this.curTintCloudLayer));
			}
			if(this.syncFade) Map.tintCloudLayer(this.iToR(this.curTintCloudLayer), this.iToG(this.curTintCloudLayer), this.iToB(this.curTintCloudLayer));

			if(this.nextAlphaCloudLayer != this.curAlphaCloudLayer) {
				this.curAlphaCloudLayer = this.alphaFade(this.curAlphaCloudLayer, this.nextAlphaCloudLayer);
				Map.alphaCloudLayer(this.curAlphaCloudLayer);
			}
			if(this.syncFade) Map.alphaCloudLayer(this.curAlphaCloudLayer);

		},

		runFadeAltCloudLayer: function() {
			if(this.nextTintAltCloudLayer != this.curTintAltCloudLayer) {
				this.curTintAltCloudLayer = this.tintFade(this.curTintAltCloudLayer, this.nextTintAltCloudLayer);
				Map.tintAltCloudLayer(this.iToR(this.curTintAltCloudLayer), this.iToG(this.curTintAltCloudLayer), this.iToB(this.curTintAltCloudLayer));
			}
			if(this.syncFade) Map.tintAltCloudLayer(this.iToR(this.curTintAltCloudLayer), this.iToG(this.curTintAltCloudLayer), this.iToB(this.curTintAltCloudLayer));

			if(this.nextAlphaAltCloudLayer != this.curAlphaAltCloudLayer) {
				this.curAlphaAltCloudLayer = this.alphaFade(this.curAlphaAltCloudLayer, this.nextAlphaAltCloudLayer);
				Map.alphaAltCloudLayer(this.curAlphaAltCloudLayer);
			}
			if(this.syncFade) Map.alphaAltCloudLayer(this.curAlphaAltCloudLayer);

		},

		runFadeFog: function() {
			if(this.curTintFog != this.nextTintFog) {
				this.curTintFog = this.tintFade(this.curTintFog, this.nextTintFog);
				Map.tintFog(this.iToR(this.curTintFog), this.iToG(this.curTintFog), this.iToB(this.curTintFog));
			}
			if(this.syncFade) Map.tintFog(this.iToR(this.curTintFog), this.iToG(this.curTintFog), this.iToB(this.curTintFog));
		},

		runFadeAmbient: function() {
			if(this.curTintAmbient != this.nextTintAmbient) {
				this.curTintAmbient = this.tintFade(this.curTintAmbient, this.nextTintAmbient);
				Map.tintAmbient(this.iToR(this.curTintAmbient), this.iToG(this.curTintAmbient), this.iToB(this.curTintAmbient));
			}
			if(this.syncFade) Map.tintAmbient(this.iToR(this.curTintAmbient), this.iToG(this.curTintAmbient), this.iToB(this.curTintAmbient));
		},
		////////////////////////////////////////////////////////////////////////////////////////////
		// This is the end of the client side aspect of the Sky Manager.
		////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////
		// The server needs it's own idea of the sky state, we handle that and the sky itself here.
		////////////////////////////////////////////////////////////////////////////////////////////
        activate: function() {
			this.curStarbox = "t7g/nightsky";
			this.curSkybox = "t7g/haze";
			this.curSunbox = "t7g/sun";
			this.curCloudbox = "t7g/horizon";
			this.curCloudLayer = "t7g/clouds2";
			this.curAltCloudLayer = "t7g/clouds5";

			this.curTintStars = intWHITE;
			this.curTintSky = intRED;
			this.curTintSun = intRED;
			this.curTintClouds = intORANGE;
			this.curTintCloudLayer = intWHITE;
			this.curTintAltCloudLayer = intWHITE;
			this.curTintFog = intRED;
			this.curTintAmbient = intAMBIENT;

			this.curAlphaSky = 0.0;
			this.curAlphaSun = 1.0;
			this.curAlphaClouds = 0.0;
			this.curAlphaCloudLayer = 0.1;
			this.curAlphaAltCloudLayer = 0.0;

			this.curHeightAltCloudLayer = 0.1;
			this.curHeightCloudLayer = 0.2;
			this.curScaleAltCloudLayer = 2.0;
			this.curScaleCloudLayer = 1.0;
			this.curScrollXAltCloudLayer = 0.001;
			this.curScrollYAltCloudLayer = 0.001;
			this.curScrollXCloudLayer = -0.003;
			this.curScrollYCloudLayer = -0.003;
			this.curSpinAltCloudLayer = 0.3;
			this.curSpinCloudLayer = 0.7;

			this.curModelAmbient = 1.0;
			this.curModelSpec = 0.0;

			this.nextStarbox = "t7g/nightsky";
			this.nextSkybox = "t7g/haze";
			this.nextSunbox = "t7g/sun";
			this.nextCloudbox = "t7g/horizon";
			this.nextCloudLayer = "t7g/clouds2";
			this.nextAltCloudLayer = "t7g/clouds5";

			this.boxWait = false;

			this.managerDelay = parseFloat((this.intsecDayLength / 24) / 4); // 24, hours in a day, 4 checks per hour.
			this.rateSpin = parseFloat(360 / parseFloat(this.intsecDayLength)); // 360 degrees that the stars will spin.

			this.curYawStars = parseFloat(this.defYawStars);
			this.curYawSun = parseFloat(this.defYawSun);

            GameManager.getSingleton().eventManager.add({
                secondsBefore: 0,
                secondsBetween: this.managerDelay,
                func: bind(function() {
					if(this.inTransition) {
						this.manageDayEvents();

						//log(ERROR, format('The game thinks it is currently ("{0}")', this.dayTime));						
						//log(ERROR, parseFloat(this.curYawSun));

						if(this.dayTime > 73 && this.dayTime < 79) {
							log(ERROR, format('The game thinks it is currently ("{0}")', this.dayTime));						
							log(ERROR, parseFloat(this.curYawSun));
						}

						this.dayTime++;
						if(this.dayTime >= 95) { 
							this.dayTime = 1; 
							log(ERROR, format('This day finished after ("{0}") seconds.', parseFloat(this.secondsElapsed))); 
							this.syncMidnight = this.secondsElapsed;
						} // That was fun, again!
					}

                }, this),
                entity: this,
            });
			// This is for keeping a rough idea of where the sun and stars are at in their rotations.
			GameManager.getSingleton().eventManager.add({
				secondsBefore: 0,
				secondsBetween: 1,
				func: bind(function() {
					if(this.inTransition) {
						this.fakeSpinStars();
						this.fakeSpinSun();
					}

					this.secondsElapsed++;
				}, this),
				entity: this,
			});
			// The server keeps track of the sky variables for syncing with new clients below.
            GameManager.getSingleton().eventManager.add({
                secondsBefore: 0,
                secondsBetween: this.intsecActionPer,
                func: bind(function() {

					if(this.inTransition) this.rollTransitions();
					if(this.syncSkyRequest) this.syncSkyState();

                }, this),
                entity: this,
            });
        },
		////////////////////////////////////////////////////////////////////////////////////////////
		// Night/Day/Weather event management and transition control // 
		////////////////////////////////////////////////////////////////////////////////////////////
		manageDayEvents: function() {
			this.cloudManager();

			this.runMorningEvents();
			this.runAfternoonEvents();
			this.runEveningEvents();
		},

		runMorningEvents: function() {
			switch (this.dayTime) {
				case 1: this.curYawStars = parseFloat(this.defYawStars); this.curYawSun = parseFloat(this.defYawSun); break;	// 12am, Midnight
				case 2: break;  // 12:15am
				case 3: break;	// 12:30am
				case 4: break;  // 12:45am
				case 5: break;	// 1am
				case 6: break;  // 1:15am
				case 7: break;	// 1:30am
				case 8: break;  // 1:45am
				case 9: break;	// 2am
				case 10: break; // 2:15am
				case 11: break; // 2:30am
				case 12: break; // 2:45am
				case 13: break;	// 3am
				case 14: break; // 3:15am
				case 15: break; // 3:30am
				case 16: break; // 3:45am
				case 17: this.nextAlphaSun = 1.0; break; // 4am
				case 18: break; // 4:15am
				case 19: break; // 4:30am
				case 20: break; // 4:45am
				case 21: break; // 5am
				case 22: break; // 5:15am
				case 23: break; // 5:30am
				case 24: break; // 5:45am
				case 25: this.nextModelAmbient = 57.0; this.nextTintAltCloudLayer = this.pickRandomWarmTint(); this.nextTintCloudLayer = this.pickRandomWarmTint(); break;	// 6am
				case 26: this.nextAlphaSky = 1.0; this.nextAlphaClouds = 0.9; break; // 6:15am
				case 27: this.nextTintSun = this.pickRandomTint(intArrYELLOW); break; // 6:30am
				case 28: this.nextTintAmbient = this.pickRandomTint(intArrORANGE); break; // 6:45am
				case 29: this.nextModelSpec = 1.0; break; // 7am
				case 30: this.nextTintAmbient = intAMBIENTFULL; break; // 7:15am
				case 31: this.nextTintAltCloudLayer = intWHITE; this.nextTintClouds = intWHITE; this.nextTintCloudLayer = intWHITE; this.nextTintSky = this.pickRandomTint(intArrBLUE); break; // 7:30am
				case 32: break; // 7:45am
				case 33: break;	// 8am
				case 34: break; // 8:15am
				case 35: break; // 8:30am
				case 36: break; // 8:45am
			}
		},

		runAfternoonEvents: function() {
			switch (this.dayTime) {
				case 37: break;	// 9am
				case 38: break; // 9:15am
				case 39: break; // 9:30am
				case 40: break; // 9:45am
				case 41: break; // 10am
				case 42: break; // 10:15am
				case 43: break; // 10:30am
				case 44: break; // 10:45am
				case 45: break; // 11am
				case 46: break; // 11:15am
				case 47: break; // 11:30am
				case 48: break; // 11:45am
				case 49: break;  // 12pm, Afternoon, just incase.
				case 50: break; // 12:15pm
				case 51: break; // 12:30pm
				case 52: break; // 12:45pm
				case 51: break; // 1pm
				case 52: break; // 1:15pm
				case 53: break; // 1:30pm
				case 54: break; // 1:45pm
				case 55: break; // 2pm
				case 56: break; // 2:15pm
				case 57: break; // 2:30pm
				case 58: break; // 2:45pm
				case 59: break; // 3pm
				case 60: break; // 3:15pm
				case 61: break; // 3:30pm
				case 62: break; // 3:45pm
				case 63: break; // 4pm
				case 64: break; // 4:15pm
				case 65: break; // 4:30pm
				case 66: break; // 4:45pm
			}
		},

		runEveningEvents: function() {
			switch (this.dayTime) {
				case 67: break; // 5pm
				case 68: this.nextTintCloudLayer = this.pickRandomWarmTint(); break; // 5:15pm
				case 69: this.nextModelAmbient = 1.0; this.nextTintSun = this.pickSunrisetTint(); break; // 5:30pm
				case 70: this.nextTintClouds = this.pickRandomWarmTint(); this.nextTintSky = this.pickSunrisetTint(); break; // 5:45pm
				case 71: this.nextTintAltCloudLayer = this.pickRandomWarmTint(); this.nextTintAmbient = this.pickRandomTint(intArrORANGE); break; // 6pm
				case 72: this.nextTintCloudLayer = this.pickRandomWarmTint(); this.nextTintAmbient = intAMBIENT; this.nextTintClouds = this.pickRandomWarmTint(); break; // 6:15pm
				case 73: this.nextModelSpec = 0.0; break; // 6:30pm
				case 74: this.nextTintCloudLayer = intWHITE; this.nextTintAltCloudLayer = intWHITE; this.nextTintClouds = this.pickRandomWarmTint(); this.nextTintSky = this.pickRandomWarmTint(); this.nextTintSun = this.pickSunrisetTint(); this.nextAlphaSky = 0.0; this.nextAlphaClouds = 0.0; break; // 6:45pm
				case 75: break; // 7pm
				case 76: break; // 7:15pm
				case 77: break; // 7:30pm
				case 78: break; // 7:45pm
				case 79: break; // 8pm
				case 80: break; // 8:15pm
				case 81: break; // 8:30pm
				case 82: break; // 8:45pm
				case 83: break; // 9pm
				case 84: break; // 9:15pm
				case 85: break; // 9:30pm
				case 86: break; // 9:45pm
				case 87: this.nextAlphaSun = 0.0; break; // 10pm
				case 88: break; // 10:15pm
				case 89: break; // 10:30pm
				case 90: break; // 10:45pm
				case 91: this.nextTintSun = intRED; break; // 11pm
				case 92: break; // 11:15pm
				case 93: break; // 11:30pm
				case 94: break; // 11:45pm
				case 95: break; // 12am, Midnight (counter resets, don't think you should ever get here)
			}
		},
		////////////////////////////////////////////////////////////////////////////////////////////
		// Server side, sky state and sync functions for new clients //
		////////////////////////////////////////////////////////////////////////////////////////////
		syncSkyState: function() {
			this.syncStarbox = this.curStarbox;
			this.syncSkybox = this.curSkybox;
			this.syncSunbox = this.curSunbox;
			this.syncCloudbox = this.curCloudbox;
			this.syncCloudLayer = this.curCloudLayer;
			this.syncAltCloudLayer = this.curAltCloudLayer;

			this.syncTintStars = this.curTintStars;
			this.syncTintSky = this.curTintSky;
			this.syncTintSun = this.curTintSun;
			this.syncTintClouds = this.curTintClouds;
			this.syncTintCloudLayer = this.curTintCloudLayer;
			this.syncTintAltCloudLayer = this.curTintAltCloudLayer;
			this.syncTintFog = this.curTintFog;
			this.syncTintAmbient = this.curTintAmbient;

			this.syncAlphaSky = this.curAlphaSky;
			this.syncAlphaSun = this.curAlphaSun;
			this.syncAlphaClouds = this.curAlphaClouds;
			this.syncAlphaCloudLayer = this.curAlphaCloudLayer;
			this.syncAlphaAltCloudLayer = this.curAlphaAltCloudLayer;

			this.syncModelAmbient = this.curModelAmbient;
			this.syncModelSpec = this.curModelSpec;

			this.syncYawStars = parseFloat(this.curYawStars);
			this.syncYawSun = parseFloat(this.curYawSun);

			this.syncSkyRequest = false;
		},

		trackBoxen: function() {
			// Keep a server side idea of what boxes are currently loaded. Change them if needed.
			if(this.curCloudLayer != this.nextCloudLayer && this.curAlphaCloudLayer == 0.0) {
				this.curCloudLayer = this.nextCloudLayer;
				this.boxWait = false;
			} else if(!this.boxWait && this.curCloudLayer != this.nextCloudLayer) {
				this.nextAlphaCloudLayer = 0.0;
				this.boxWait = true;
			}
			if(this.curAltCloudLayer != this.nextAltCloudLayer && this.curAlphaCloudLayer == 0.0) {
				this.curAltCloudLayer = this.nextAltCloudLayer;
				this.boxWait = false;
			} else if(!this.boxWait && this.curAltCloudLayer != this.nextAltCloudLayer) {
				this.nextAlphaAltCloudLayer = 0.0;
				this.boxWait = true;
			}
			if(this.curCloudbox != this.nextCloudbox && this.curAlphaClouds == 0.0) {
				this.curCloudbox = this.nextCloudbox;
				this.boxWait = false;
			} else if(!this.boxWait && this.curCloudbox != this.nextCloudbox) {
				this.nextAlphaClouds = 0.0;
				this.boxWait = true;
			}
			if(this.curSunbox != this.nextSunbox && this.curAlphaSun == 0.0) {
				this.curSunbox = this.nextSunbox;
				this.boxWait = false;
			} else if(!this.boxWait && this.curSunbox != this.nextSunbox) {
				this.nextAlphaSun = 0.0;
				this.boxWait = true;
			}
			if(this.curSkybox != this.nextSkybox && this.curAlphaSky == 0.0) {
				this.curSkybox = this.nextSkybox;
				this.boxWait = false;
			} else if(!this.boxWait && this.curSkybox != this.nextSkybox) {
				this.nextAlphaSky = 0.0;
				this.boxWait = true;
			}
			if(this.curStarbox != this.nextStarbox && this.curAlphaSky == 1.0) {
				this.curStarbox = this.nextStarbox;
				this.boxWait = false;
			}						

		},

		rollTransitions: function() {
			// Here we're just simulating what the clients are doing so we can sync new clients proper.
			this.rollFadeStars();
			this.rollFadeSky();
			this.rollFadeSun();
			this.rollFadeClouds();
			this.rollFadeCloudLayer(); this.rollFadeAltCloudLayer();
			this.rollFadeFog();
			this.rollFadeAmbient();
			this.rollModelFade();
			this.rollModelSpec();

			this.trackBoxen();
			this.gimpCloudSync();
		},

		gimpCloudSync: function() {
			this.curHeightAltCloudLayer = this.nextHeightAltCloudLayer;
			this.curHeightCloudLayer = this.nextHeightCloudLayer;
			this.curScaleAltCloudLayer = this.nextScaleAltCloudLayer;
			this.curScaleCloudLayer = this.nextScaleCloudLayer;
			this.curScrollXAltCloudLayer = this.nextScrollXAltCloudLayer;
			this.curScrollYAltCloudLayer = this.nextScrollYAltCloudLayer;
			this.curScrollXCloudLayer = this.nextScrollXCloudLayer;
			this.curScrollYCloudLayer = this.nextScrollYCloudLayer;
			this.curSpinAltCloudLayer = this.nextSpinAltCloudLayer;
			this.curSpinCloudLayer = this.nextSpinCloudLayer;
		},

		fakeSpinStars: function() {
			if(this.curYawStars >= 360)	this.curYawStars = 0;	// Too high? (not possible!)
			if(this.curYawStars < 0)	this.curYawStars = 360;	// Too low?
			this.curYawStars = parseFloat(parseFloat(this.curYawStars) + parseFloat(this.rateSpin)); // Pretend we're spinning.
		},

		fakeSpinSun: function() {
			if(this.curYawSun >= 360)	this.curYawSun = 0;
			if(this.curYawSun < 0)		this.curYawSun = 360; // Just in case...
			this.curYawSun = parseFloat(parseFloat(this.curYawSun) + parseFloat(this.rateSpin));
		},

		rollFadeStars: function() {	if(this.nextTintStars != this.curTintStars) this.curTintStars = this.tintFade(this.curTintStars, this.nextTintStars); },

		rollFadeSky: function() {
			if(this.nextTintSky != this.curTintSky) this.curTintSky = this.tintFade(this.curTintSky, this.nextTintSky);
			if(this.nextAlphaSky != this.curAlphaSky) this.curAlphaSky = this.alphaFade(this.curAlphaSky, this.nextAlphaSky);
		},

		rollFadeSun: function() {
			if(this.nextTintSun != this.curTintSun) this.curTintSun = this.tintFade(this.curTintSun, this.nextTintSun);
			if(this.nextAlphaSun != this.curAlphaSun) this.curAlphaSun = this.nextAlphaSun;
		},

		rollFadeClouds: function() {
			if(this.nextTintClouds != this.curTintClouds) this.curTintClouds = this.tintFade(this.curTintClouds, this.nextTintClouds);
			if(this.nextAlphaClouds != this.curAlphaClouds) this.curAlphaClouds = this.alphaFade(this.curAlphaClouds, this.nextAlphaClouds);
		},

		rollFadeCloudLayer: function() {
			if(this.nextTintCloudLayer != this.curTintCloudLayer) this.curTintCloudLayer = this.tintFade(this.curTintCloudLayer, this.nextTintCloudLayer);
			if(this.nextAlphaCloudLayer != this.curAlphaCloudLayer) this.curAlphaCloudLayer = this.alphaFade(this.curAlphaCloudLayer, this.nextAlphaCloudLayer);
		},

		rollFadeAltCloudLayer: function() {
			if(this.nextTintAltCloudLayer != this.curTintAltCloudLayer) this.curTintAltCloudLayer = this.tintFade(this.curTintAltCloudLayer, this.nextTintAltCloudLayer);
			if(this.nextAlphaAltCloudLayer != this.curAlphaAltCloudLayer) this.curAlphaAltCloudLayer = this.alphaFade(this.curAlphaAltCloudLayer, this.nextAlphaAltCloudLayer);
		},

		rollFadeFog: function() { if(this.curTintFog != this.nextTintFog) this.curTintFog = this.tintFade(this.curTintFog, this.nextTintFog); },

		rollModelFade: function() {	if(this.curModelAmbient != this.nextModelAmbient) this.curModelAmbient = this.modelAmbientFade(this.curModelAmbient, this.nextModelAmbient, fArrModelAmbient); },

		rollModelSpec: function() {	if(this.curModelSpec != this.nextModelSpec) this.curModelSpec = this.alphaFade(this.curModelSpec, this.nextModelSpec); },

		rollFadeAmbient: function() { if(this.curTintAmbient != this.nextTintAmbient) this.curTintAmbient = this.tintFade(this.curTintAmbient, this.nextTintAmbient); },
		////////////////////////////////////////////////////////////////////////////////////////////
		// Cloud manager functions //
		////////////////////////////////////////////////////////////////////////////////////////////
		cloudManager: function() {
			// Cloud manager randomly changes the various cloud layers as the day progresses, it runs once every 15 minutes or four times an ingame hour.
			// So first, do we want to change a cloud layer or not?
			switch (integer(Math.random())) {
				case 0: return(this.pickLayer());
				case 1: return; // bahhh, why change the clouds now when we can do it later?
			}
		},

		pickLayer: function() {
			switch (integer(Math.random())) {
				case 0: return(this.doRandomStuff(false));	// Standard cloud layer
				case 1: return(this.doRandomStuff(true));	// Alternate cloud layer
			}
		},

		doRandomStuff: function(pickedLayer) {
			switch (integer(Math.random()*6)) {
				case 0: return(this.cloudLAlpha(pickedLayer));
				case 1: return(this.cloudLHeight(pickedLayer));
				case 2: return(this.cloudLScale(pickedLayer));
				case 3: return(this.cloudLScroll(pickedLayer));
				case 4: return(this.cloudLSpin(pickedLayer));
				case 5: return(this.cloudLPickNew(pickedLayer));
				case 6: return(this.rainDance());
			}
		},

		cloudLAlpha: function(pL) {
			if(this.isRaining) this.isRaining = false;
			if(pL) this.nextAlphaAltCloudLayer = this.pickRandomFloat(fArrAltCloudLayerAlpha);
			else this.nextAlphaCloudLayer = this.pickRandomFloat(fArrCloudLayerAlpha);
		},

		cloudLHeight: function(pL) {
			if(pL) this.nextHeightAltCloudLayer = this.pickRandomFloat(fArrAltCloudLayerHeight);
			else this.nextHeightCloudLayer = this.pickRandomFloat(fArrCloudLayerHeight);
		},

		cloudLScale: function(pL) {
			if(pL) this.nextScaleAltCloudLayer = this.pickRandomFloat(fArrAltCloudLayerScale);
			else this.nextScaleCloudLayer = this.pickRandomFloat(fArrCloudLayerScale);
		},
		
		cloudLScroll: function(pL) {
			if(pL) {
				switch (integer(Math.random())) {
					case 0: this.nextScrollXAltCloudLayer = this.pickRandomFloat(fArrAltCloudLayerScroll);
					case 1: this.nextScrollYAltCloudLayer = this.pickRandomFloat(fArrAltCloudLayerScroll);
				}				
			} else {
				switch (integer(Math.random())) {
					case 0: this.nextScrollXCloudLayer = this.pickRandomFloat(fArrCloudLayerScroll);
					case 1: this.nextScrollYCloudLayer = this.pickRandomFloat(fArrCloudLayerScroll);
				}
			}
		},

		cloudLSpin: function(pL) {
			if(pL) this.nextSpinAltCloudLayer = this.pickRandomFloat(fArrAltCloudLayerSpin);
			else this.nextSpinCloudLayer = this.pickRandomFloat(fArrCloudLayerSpin);
		},

		cloudLPickNew: function(pL) {
			if(pL) {
				if(this.curAlphaAltCloudLayer == 0.0) this.nextAltCloudLayer = this.pickNewCloudLayer();
				else this.nextAlphaAltCloudLayer = 0.0;
			} else {
				if(this.curAlphaCloudLayer == 0.0) this.nextCloudLayer = this.pickNewCloudLayer();
				else this.nextAlphaCloudLayer = 0.0;			
			}
		},

		pickNewCloudLayer: function() {	return(sArrCloudLayers[integer(Math.random()*5)]); },
		////////////////////////////////////////////////////////////////////////////////////////////
		// Weather related functions //
		////////////////////////////////////////////////////////////////////////////////////////////
		rainDance: function() {
			if(this.curCloudLayer == rainCloudLayer || this.curAltCloudLayer == rainCloudLayer) {
				if(this.curAlphaCloudLayer == 1.0 || this.curAlphaAltCloudLayer == 1.0) {
					if(!this.isRaining) this.isRaining = true;
					return;
				} else if(this.curAlphaCloudLayer > 0.0) {
					this.nextAlphaCloudLayer = 1.0;
					return;
				} else if(this.curAlphaAltCloudLayer > 0.0) {
					this.nextAlphaAltCloudLayer = 1.0;
					return;
				}
			} 
		},

		weatherManager: function() {
            frequency = 0.2;
            spawnAtOnce = 137;
            maxAmount = 777;
            speed = 1337;
            size = 11;
            radius = 1337;
            dropColor = 0x373737;
            splashColor = 0x111111;
			////////////////////////////////////////////////////////////////////////////////////////
            this.drops = [];
            var worldSize = Editing.getWorldSize();
            this.addDropEvent = GameManager.getSingleton().eventManager.add({
                secondsBefore: 0,
                secondsBetween: frequency,
                func: bind(function() {
                    var camera = getPlayerEntity().position.copy();
                    var lx = Math.max(0, camera.x - radius);
                    var ly = Math.max(0, camera.y - radius);
                    var hx = Math.min(camera.x + radius, worldSize);
                    var hy = Math.min(camera.y + radius, worldSize);
                    var dx = hx-lx;
                    var dy = hy-ly;
                    var chance = dx*dy/Math.pow(worldSize, 2);
                    var amount = spawnAtOnce*chance;
                    if (this.drops.length + amount > maxAmount) {
                        amount = maxAmount - this.drops.length;
                    }
                    for (var i = 0; i < amount; i++) {
                        var origin = new Vector3(lx + Math.random()*dx, ly + Math.random()*dy, Math.random()*worldSize);
                        var floorDist = floorDistance(origin, worldSize*2);
                        if (floorDist < 0) floorDist = worldSize;
                        this.drops.push({
                            position: origin,
                            finalZ: origin.z - floorDist,
                        });
                    }
                }, this),
            }, this.addDropEvent);
			////////////////////////////////////////////////////////////////////////////////////////
            this.visualEffectEvent = GameManager.getSingleton().eventManager.add({
                secondsBefore: 0,
                secondsBetween: 0,
                func: bind(function() {
                    var delta = Global.currTimeDelta;
                    this.drops = filter(function(drop) {
                        var bottom = drop.position.copy();
                        bottom.z -= size;
                        Effect.flare(PARTICLE.STREAK, drop.position, bottom, 0, dropColor, 0.3);
                        drop.position.z -= this.speed*delta;
                        if (drop.position.z > drop.finalZ) {
                            return true;
                        } else {
                            drop.position.z = drop.finalZ - 5;
                            //Effect.splash(PARTICLE.SPARK, 3, 0.1, drop.position, splashColor, 1.0, 70, -1);
                            return false;
                        }
                    }, this.drops);
                }, this),
            }, this.visualEffectEvent);
		////////////////////////////////////////////////////////////////////////////////////////////
		},
		////////////////////////////////////////////////////////////////////////////////////////////
		// These things increment or decrement values. //
		////////////////////////////////////////////////////////////////////////////////////////////
		alphaFade: function(alpf, alpt) {
			if(alpf < alpt) alpf = alpf + 0.004; else if(alpf > alpt) alpf = alpf - 0.004;
				if(alpf + 0.004 >= alpt && alpf < alpt) alpf = alpt; 
				else if(alpf - 0.004 <= alpt && alpf > alpt) alpf = alpt;
			if(alpf >= 1.0) alpf = 1.0; if(alpf <= 0.0) alpf = 0.0;
				return(alpf);
		},
		// The below are actually only used on the client, they just looked better here than up there.
		leashedFade: function(floatingFrom, floatingTo, floatArrLeash) {
			if(floatingFrom < floatingTo) floatingFrom = floatingFrom + 0.001; else if(floatingFrom > floatingTo) floatingFrom = floatingFrom - 0.001;
				if(floatingFrom + 0.001 >= floatingTo && floatingFrom < floatingTo) floatingFrom = floatingTo; 
				else if(floatingFrom - 0.001 <= floatingTo && floatingFrom > floatingTo) floatingFrom = floatingTo;
			if(floatingFrom >= floatArrLeash[1]) floatingFrom = floatArrLeash[1]; if(floatingFrom <= floatArrLeash[0]) floatingFrom = floatArrLeash[0];
				return(floatingFrom);
		},

		modelAmbientFade: function(floatingFrom, floatingTo, floatArrLeash) {
			if(floatingFrom < floatingTo) floatingFrom = floatingFrom + 0.1; else if(floatingFrom > floatingTo) floatingFrom = floatingFrom - 0.1;
				if(floatingFrom + 0.1 >= floatingTo && floatingFrom < floatingTo) floatingFrom = floatingTo; 
				else if(floatingFrom - 0.1 <= floatingTo && floatingFrom > floatingTo) floatingFrom = floatingTo;
			if(floatingFrom >= floatArrLeash[1]) floatingFrom = floatArrLeash[1]; if(floatingFrom <= floatArrLeash[0]) floatingFrom = floatArrLeash[0];
				return(floatingFrom);
		},

		dynamicScale: function(scalingFrom, scalingTo, floatArrLeash) {
			if(scalingFrom < scalingTo) scalingFrom = scalingFrom + 0.001; else if(scalingFrom > scalingTo) scalingFrom = scalingFrom - 0.001;
				if(scalingFrom + 0.001 >= scalingTo && scalingFrom < scalingTo) scalingFrom = scalingTo; 
				else if(scalingFrom - 0.001 <= scalingTo && scalingFrom > scalingTo) scalingFrom = scalingTo;
			if(scalingFrom >= floatArrLeash[1]) scalingFrom = floatArrLeash[1]; if(scalingFrom <= floatArrLeash[0]) scalingFrom = floatArrLeash[0];
				return(scalingFrom);
		},

		dynamicFloatScroll: function(floatingFrom, floatingTo, floatArrLeash) {
			if(floatingFrom < floatingTo) floatingFrom = floatingFrom + 0.001; else if(floatingFrom > floatingTo) floatingFrom = floatingFrom - 0.001;
				if(floatingFrom + 0.001 >= floatingTo && floatingFrom < floatingTo) floatingFrom = floatingTo; 
				else if(floatingFrom - 0.001 <= floatingTo && floatingFrom > floatingTo) floatingFrom = floatingTo;
			if(floatingFrom >= floatArrLeash[1]) floatingFrom = floatArrLeash[1]; if(floatingFrom <= floatArrLeash[0]) floatingFrom = floatArrLeash[0];
				return(floatingFrom);
		},

		dynamicSpin: function(spinningFrom, spinningTo, floatArrLeash) {
			if(spinningFrom < spinningTo) spinningFrom = spinningFrom + 0.001; else if(spinningFrom > spinningTo) spinningFrom = spinningFrom - 0.001;
				if(spinningFrom + 0.001 >= spinningTo && spinningFrom < spinningTo) spinningFrom = spinningTo; 
				else if(spinningFrom - 0.001 <= spinningTo && spinningFrom > spinningTo) spinningFrom = spinningTo;
			if(spinningFrom >= floatArrLeash[1]) spinningFrom = floatArrLeash[1]; if(spinningFrom <= floatArrLeash[0]) spinningFrom = floatArrLeash[0];
				return(spinningFrom);
		},
		////////////////////////////////////////////////////////////////////////////////////////////
		// Color related you know whats //
		////////////////////////////////////////////////////////////////////////////////////////////
		tintFade: function(fromTint, toTint) {
			fromRed = this.iToR(fromTint); fromGreen = this.iToG(fromTint);	fromBlue = this.iToB(fromTint);
			toRed = this.iToR(toTint); toGreen = this.iToG(toTint);	toBlue = this.iToB(toTint);

			if(fromRed < toRed) { red = fromRed + 1; if(red > 255) red = 255; } 
			else { red = fromRed - 1; if(red < 0) red = 0;	} 
			// red // green //
			if(fromGreen < toGreen) { green = fromGreen + 1; if(green > 255) green = 255; } 
			else { green = fromGreen - 1; if(green < 0) green = 0; } 
			// green // blue //
			if(fromBlue < toBlue) {	blue = fromBlue + 1; if(blue > 255) blue = 255;	} 
			else { blue = fromBlue - 1; if(blue < 0) blue = 0; }

			if(red == toRed || green == toGreen || blue == toBlue) {
				if(red + 1 == toRed) red = toRed; if(green + 1 == toGreen) green = toGreen;	if(blue + 1 == toBlue) blue = toBlue; // To fix extent flipping, like...
				if(red - 1 == toRed) red = toRed; if(green - 1 == toGreen) green = toGreen; if(blue - 1 == toBlue) blue = toBlue; // 254,255,254,255 oscillation.
			}

			return this.rgbToInt(red, green, blue);
		},

		pickRandomTint: function(arrRange) {
			sred = this.iToR(arrRange[0]); sgreen = this.iToG(arrRange[0]); sblue = this.iToB(arrRange[0]);
			ered = this.iToR(arrRange[1]); egreen = this.iToG(arrRange[1]); eblue = this.iToB(arrRange[1]);

			red 	= Math.floor((sred-ered) * Math.random()) + ered;
			green	= Math.floor((sgreen-egreen) * Math.random()) + egreen;
			blue	= Math.floor((sblue-eblue) * Math.random()) + eblue;

			return(this.rgbToInt(red, green, blue)); 
		},

		pickSunrisetTint: function() {
			switch (integer(Math.random())) {
				case 0: return(this.pickRandomTint(intArrRED));
				case 1: return(this.pickRandomTint(intArrORANGE));
			}
		},

		pickRandomWarmTint: function() {
			switch (integer(Math.random()*3)) {
				case 0: return(this.pickRandomTint(intArrRED));
				case 1: return(this.pickRandomTint(intArrORANGE));
				case 2: return(this.pickCrazyRandomTint());
				case 3: return(this.pickRandomTint(intArrPURPLE));
			}
		},

		pickRandomCoolTint: function() {
			switch (integer(Math.random()*3)) {
				case 0: return(this.pickRandomTint(intArrBLUE));
				case 1: return(this.pickRandomTint(intArrORANGE));
				case 2: return(this.pickRandomTint(intArrPURPLE));
			}
		},

		pickCrazyRandomTint: function() {
			red 	= Math.floor(254 * Math.random()) + 1;
			green	= Math.floor(254 * Math.random()) + 1;
			blue	= Math.floor(254 * Math.random()) + 1;

			return(this.rgbToInt(red, green, blue)); 
		},

		iToR: function(color) {	return color&255; }, // Slice out our red channel as an int.

		iToG: function(color) {	return (color>>8)&255; }, // Slice out our green channel as an int.

		iToB: function(color) {	return (color>>16)&255; }, // Slice out our blue channel as an int.

	    rgbToInt: function(red, green, blue) { return 256*256*blue+256*green+red; },

		pickRandomFloat: function(floatArrLeash) { return((floatArrLeash[1]-floatArrLeash[0]) * Math.random() + floatArrLeash[0]); }

	},

};
