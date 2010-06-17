// Copyright 2010 quaker66. All rights reserved.
// This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

//! New cutscene system for Syntensity
//!
//! This is a marker-based cutscene system for Syntensity, not needing any modifications in Javascript (unless you want your own actions or baseactions or anything else)
//! It's composed of four basic entities, with possibility of baking new ones
//! The entities are:
//!
//! 1) CutsceneController
//!  - this is a main controller for your cutscene. You can have more ones in map, handling different cutscenes (like, intro and outro)
//!  - you can connect controllers together, and then when one finishes, it'll skip to another. You can loop them.
//!  - controllers should have first tag in format "ctl_NUM" - i.e. ctl_0, ctl_1, don't skip the numbers.
//!  - it has properties:
//!    - canBeCancelled - specifies if you can cancel the cutscene. Boolean.
//!    - cancelConnected - do we want to cancel also connected controller? Boolean. 
//!    - secondsPerMarker - specifies how long it'll take from one point to another; basically specifies speed. Float.
//!    - delayBefore - specifies delay before cutscene, in seconds. Float.
//!    - delayAfter - same as delayBefore, but after cutscene. Float.
//!    - nextController - number of controller you want your current controller connected to. If you don't want to connect it, keep -1 (or anything below 0). Connecting causes points not loop if you loop them (because when looped it can't skip to next controller) Integer.
//!    - factor - every subtitle time is multiplied by this - 4/3 by default, you propably don't want to modify this. Float.
//!    - beforeScene, afterScene - by default empty functions, ran before cutscene starts and after cutscene starts. Modifeable from JS in combination with getEntitiesByTag. You'll most likely want to use CutsceneAction entity described later.
//!    - started - not kept in entity, available just for game run-time, for changing cutscene state. Boolean.
//!    - cancel - not kept in entity, available just for game run-time. Marks if the controller is scheduled for cancel. Boolean.
//!
//! 2) CutscenePoint
//!  - this is a point in your cutscene. Cutscene goes from one point to another and creates its path like that. Point is linked to controller.
//!  - points should have first tag in format ctl_NUM_pnt_NUM2 (NUM is controller number, NUM2 is point number) i.e ctl_0_pnt_5. Don't skip numbers - begin with pnt_0,
//!  - through pnt_1 and pnt_2 to pnt_X.
//!  - it has properties:
//!    - nextPoint - next point entity it's linked to. It's strongly recommended that if you have pnt_1, you should link to pnt_2, otherwise it'll not work. (But for looping, you can of course link from last point to first again) Integer.
//!    - pointYaw - yaw of current point, used to do various angle changes when flying through cutscene. Float.
//!    - pointPitch - pitch of current point, used to do various angle changes too. Float.
//!
//! 3) CutsceneSubtitle
//!  - optional marker. Displays subtitles when running cutscene. Linked to point and controller.
//!  - subtitles should have first tag in format ctl_NUM_sub_NUM2, i.e. ctl_0_sub_4. Same with CutscenePoint, don't skip numbers. It won't work.
//!  - it has properties:
//!    - cutscenePoint - number of point it's linked to. i.e. for ctl_0_pnt_5, write 5. Integer.
//!    - subtitleStartTime - start time of subtitle, relative to its marker. (i.e. when marker starts at 15 seconds, and starttime is 2, it starts at 17 seconds) Float.
//!    - subtitleTotalTime - time that subtitle is shown. i.e. when it starts at 17 and totaltime is 3, it ends at 20. Float.
//!    - subtitleText - text of subtitle. String.
//!    - subtitleX - X coords of subtitle. Float.
//!    - subtitleY - Y coords of subtitle. Float.
//!    - subtitleSize - size of subtitle. Float.
//!    - subtitleColorR, G, B - red, green, blue amount of subtitle text color, from 0 to 255. Integers.
//!
//! 4) CutsceneBaseAction
//!  - optional marker. Allows to customize base action of cutscene, i.e. subtitle handling or background/subtitle image. Basically here just to bake your own ones.
//!  - it has two properties by default tho, backgroundImage and subtitleBackground, both are strings, you enter filename in format packages/meh.png.
//!  - first tag must be ctl_NUM_baseact, so it gets linked to controller. Itself it has no number, because there is just one baseaction allowed per controller.
//!
//! 5) CutsceneAction
//!  - by default it does nothing and is there as skeleton for baking custom actions ran in parallel with smoothaction (the one which moves from one marker to another)
//!  - useful for example when you want to render some models for controller or play music. It partially overlaps with beforeScene and afterScene functions in controller,
//!  - but beforeScene and afterScene is ran a bit earlier / later. For most of cases it doesn't matter tho - so use CutsceneAction where you can.
//!  - there is one cutsceneaction allowed per controller, but you can run more things in functions of entity - allowed are three functions, doStart, doExecute (ran every frame), doFinish.
//!  - first tag must be ctl_NUM_act.
//!
//! I think there is no need to describe more things. Just place some entities, link them properly and play with it, you'll learn how it works pretty soon.
//! If needed, read the code.
//! Good luck.

//! We need this always included. Nothing else.
Library.include('library/' + Global.LIBRARY_VERSION + '/CutScenes.js');

//! First, some lightning debug system so we don't need to repeat code. Tag is tag of target entity, origin is origin entity,
//! color is hex value which will colorize lightning and flare, seconds is passed from clientAct.
function MarkerConnectionDebug(tag, origin, color, seconds)
{
    // get entity.
    var entity = getEntitiesByTag(tag);
    if (entity.length == 1) { // do stuff just if there is just one entity with the tag. Don't do anything when there are more ones or none.
        Effect.lightning(entity[0].position, origin.position, 0, color, 1.0); // Display the lightning ..

        var direction = entity[0].position.subNew(origin.position); // this piece of code will display flares going in direction of connection.
        origin.currPosition = clamp(origin.currPosition + seconds/4, 0, 1);
        if (origin.currPosition === 1) origin.currPosition = 0;
        var nextPosition = clamp(origin.currPosition + 0.2, 0, 1);
        Effect.flare(PARTICLE.STREAK,
            origin.position.addNew(direction.mulNew(origin.currPosition)),
            origin.position.addNew(direction.mulNew(nextPosition)),
            0,
            color,
            1
        );
    }
}

//! Cutscene controller
registerEntityClass(bakePlugins(WorldMarker, [{
    _class: 'CutsceneController',

    shouldAct: true,

    // properties kept in entity through restarts.
    canBeCancelled: new StateBoolean(),
    cancelConnected: new StateBoolean(),
    secondsPerMarker: new StateFloat(),
    delayBefore: new StateFloat(),
    delayAfter: new StateFloat(),
    nextController: new StateInteger(),
    factor: new StateFloat(),

    // you'll most likely not use, there are CutsceneActions.
    beforeScene: function() { },
    afterScene: function() { },

    // are we started?
    started: false,
    // are we going to cancel?
    cancel: false,

    // okay, let's start.
    start: function() {
        if (Global.noCutscenes) return; // just return if we don't want globally no cutscenes.

        // now do you see where this is run? very early, but not needed in most cases
        this.beforeScene();
        // save "this" into variable, so we can re-use it in extends
        var entity = this;

        // do we have some baseaction marker linked? if not, use default baseaction.
        var baseact = getEntitiesByTag(this.tags.asArray()[0] + '_baseact');
        if (baseact.length !== 1)
            var baseaction = CutScenes.BaseAction;
        else
            var baseaction = baseact[0].baseAction;

        // now .. do we have any cutsceneaction linked? if yes, let there be some action =)
        // and if not, get some dummy there
        var act = getEntitiesByTag(this.tags.asArray()[0] + '_act');
        if (act.length !== 1)
            var action = { };
        else
            var action = act[0].action;

        // extend the baseaction and start.
        getPlayerEntity().queueAction(new (baseaction.extend({
            canBeCancelled: entity.canBeCancelled,

            cancel: function() {
                if (this.canBeCancelled && entity.started && (CAPI.isKeyDown() || CAPI.isMouseDown())) {
                    this.finish();
                }
            },

            // in doStart, we push subtitles inside.
            doStart: function() {
                this._super();
                
                if (entity.cancel) this.cancel();

                // this is a counter.
                var i = 1;
                var startmark = getEntitiesByTag(entity.tags.asArray()[0] + '_sub_0'); // we get subtitle 0.
                if (startmark.length !== 1) return; // and return if there isnt any, not depending anyhow if there are any others.
                if (startmark[0].cutscenePoint >= 0) // if it's linked, compute starttime, endtime and push it into array.
                {
                    var starttime = startmark[0].subtitleStartTime + (entity.secondsPerMarker * startmark[0].cutscenePoint) + entity.delayBefore;
                    var endtime = starttime + startmark[0].subtitleTotalTime;
                    this.subtitles.push(
                        new (CutScenes.Subtitle.extend({
                                start: starttime*entity.factor, end: endtime*entity.factor, text: startmark[0].subtitleText,
                                x: startmark[0].subtitleX, y: startmark[0].subtitleY, size: startmark[0].subtitleSize, color: Color.rgbToHex(startmark[0].subtitleColorR, startmark[0].subtitleColorG, startmark[0].subtitleColorB),
                            }))()
                    );
                }
                for (;;) { // now run infinite for loop ..
                    var nextmark = getEntitiesByTag(entity.tags.asArray()[0] + '_sub_' + i); // get next subtitle entities
                    if (nextmark.length !== 1) break; // if we dont find some, we break, thats why skipping numbers makes it not work.
                    if (nextmark[0].cutscenePoint >= 0) // if it's linked, compute starttime, endtime and push it into array again.
                    {
                        var starttime = nextmark[0].subtitleStartTime + (entity.secondsPerMarker * nextmark[0].cutscenePoint) + entity.delayBefore;
                        var endtime = starttime + nextmark[0].subtitleTotalTime;
                        this.subtitles.push(
                            new (CutScenes.Subtitle.extend({
                                    start: starttime*entity.factor, end: endtime*entity.factor, text: nextmark[0].subtitleText,
                                    x: nextmark[0].subtitleX, y: nextmark[0].subtitleY, size: nextmark[0].subtitleSize, color: Color.rgbToHex(nextmark[0].subtitleColorR, nextmark[0].subtitleColorG, nextmark[0].subtitleColorB),
                                }))()
                        );
                    }
                    i++; // add 1 to i so we can get next subtitle.
                }
            },

            doFinish: function() {
                this._super();
                // start next controller when set
                var nextcontrol = getEntitiesByTag('ctl_' + entity.nextController);
                if (nextcontrol.length == 1)
                {
                    nextcontrol[0].started = true;
                    if (entity.cancelConnected) nextcontrol[0].cancel = true;
                }
            },

            subtitles: [ ], // array of subtitles. Empty by default.
            }))(
                [
                    new (CutScenes.SmoothAction.extend(merge({ // here we extend smoothaction, the one handling moving between markers.
                        secondsPerMarker: entity.secondsPerMarker, // we set seconds per marker.

                        initMarkers: function() {
                            var startmark = getEntitiesByTag(entity.tags.asArray()[0] + '_pnt_0'); // it's all very simillar to subtitles ..
                            if (startmark.length !== 1) return;
                            var prevmark = startmark;
                            this.markers.push({ position: startmark[0].position.copy(), yaw: startmark[0].pointYaw, pitch: startmark[0].pointPitch });

                            for (;;) {
                                var nextmark = getEntitiesByTag(entity.tags.asArray()[0] + '_pnt_' + prevmark[0].nextPoint);
                                if (nextmark.length !== 1) break;
                                prevmark = nextmark;
                                this.markers.push({ position: nextmark[0].position.copy(), yaw: nextmark[0].pointYaw, pitch: nextmark[0].pointPitch });
                                if (nextmark[0].nextPoint == 0) // If next marker is 0, it means we're looped.
                                {
                                    if (entity.nextController < 0) this.looped = true; // but we won't loop if our controller is linked to another one.
                                    var nextmark = getEntitiesByTag(entity.tags.asArray()[0] + '_pnt_' + prevmark[0].nextPoint); // we'll add the 0 marker always tho, so we fly to the beginning.
                                    this.markers.push({ position: nextmark[0].position.copy(), yaw: nextmark[0].pointYaw, pitch: nextmark[0].pointPitch });
                                    break;
                                }
                            }
                        },
                        delayBefore: entity.delayBefore, // set delay before, after ..
                        markers: [ ], // this is simillar to subtitles array.
                        delayAfter: entity.delayAfter,
                    }, action)))(), // see? we link the action from actionmarker, or dummy if not connected.
                ]
            )
        );

        this.afterScene(); // and run afterscene .. it's ran at end.
    },

    init: function() { // this is where we init sane defaults on first entity placement
        this.canBeCancelled = false;
        this.cancelConnected = true;
        this.secondsPerMarker = 4.0;
        this.delayBefore = 0;
        this.delayAfter = 0;
        this.nextController = -1;
        this.factor = 4/3;
    },

    clientActivate: function() { // some stuff for debug lightning/flares.
        this.currPosition = 0;
    },

    clientAct: function(seconds) { // here we start it and lock if not started.. also start the debug lightning.
        if (this.started && !isPlayerEditing() && !this.startLocked) { // we block start when we edit. It'll start as soon as we leave edit.
            this.start();
            this.startLocked = true;
        }

        if (!this.started && this.startLocked) this.startLocked = false; // let's unlock starting if we're not started anymore.

        if (isPlayerEditing()) {
            if (this.nextController >= 0)
                MarkerConnectionDebug('ctl_' + this.nextController, this, 0xFFED22, seconds);
        }
    },
}])); // next entities won't be as heavily commented since i would just repeat myself.

//! Movie marker - a point having yaw, pitch to set orientation, number of next marker to link to,
//! subtitle information, delay information and boolean if we can cancel the action here or not.
registerEntityClass(bakePlugins(WorldMarker, [{
    _class: 'CutscenePoint',

    shouldAct: true,

    // next marker - number of marker to be linked to
    nextPoint: new StateInteger(),

    // orientation
    pointYaw: new StateFloat(),
    pointPitch: new StateFloat(),

    init: function() {
        this.nextPoint = -1;
        this.pointYaw = 0.0;
        this.pointPitch = 0.0;
    },

    clientActivate: function() {
        this.currPosition = 0;
        this.currYawPosition = 0;
        this.currPitchPosition = 0;
    },

    clientAct: function(seconds) {
        if (isPlayerEditing()) {
               
            if (this.tags.asArray()[0] && this.nextPoint >= 0 && parseInt(this.tags.asArray()[0].slice(4,5)) >= 0)
                MarkerConnectionDebug('ctl_' + parseInt(this.tags.asArray()[0].slice(4,5)) + '_pnt_' + this.nextPoint, this, 0x22BBFF, seconds);

            if (this.tags.asArray()[0] && parseInt(this.tags.asArray()[0].slice(4,5)) >= 0)
                MarkerConnectionDebug(this.tags.asArray()[0].slice(0,5), this, 0x22FF27, seconds);

            var direction = new Vector3().fromYawPitch(this.pointYaw, this.pointPitch);
            var target = World.getRayCollisionWorld(this.position.copy(), direction, 10);
            Effect.flare(PARTICLE.STREAK,
                this.position,
                target,
                0,
                0x22BBFF,
                1
            );
        }
    },
}]));

//! Subtitle marker - a point having some information about subtitle, linked to cutscenePoint.
//! Start time is relative to cutscenepoint, end time is computed from total time when subtitle is shown.
registerEntityClass(bakePlugins(WorldMarker, [{
    _class: 'CutsceneSubtitle',

    shouldAct: true,

    // number of cutscenepoint to link this marker to
    cutscenePoint: new StateInteger(),

    // subtitle
    subtitleStartTime: new StateFloat(),
    subtitleTotalTime: new StateFloat(),
    subtitleText: new StateString(),
    subtitleX: new StateFloat(),
    subtitleY: new StateFloat(),
    subtitleSize: new StateFloat(),
    subtitleColorR: new StateInteger(),
    subtitleColorG: new StateInteger(),
    subtitleColorB: new StateInteger(),

    init: function() {
        this.cutscenePoint = -1;
        this.subtitleStartTime = 0;
        this.subtitleTotalTime = 0;
        this.subtitleText = '';
        this.subtitleX = 0.5;
        this.subtitleY = 0.92;
        this.subtitleSize = 0.5;
        this.subtitleColorR = 255;
        this.subtitleColorG = 255;
        this.subtitleColorB = 255;
    },

    clientActivate: function() {
        this.currPosition = 0;
    },

    clientAct: function(seconds) {
        if (isPlayerEditing()) {
            if (this.tags.asArray()[0] && this.cutscenePoint >= 0 && parseInt(this.tags.asArray()[0].slice(4,5)) >= 0)
                MarkerConnectionDebug('ctl_' + parseInt(this.tags.asArray()[0].slice(4,5)) + '_pnt_' + this.cutscenePoint, this, 0xFF22C3, seconds);

            if (this.tags.asArray()[0] && parseInt(this.tags.asArray()[0].slice(4,5)) >= 0)
                MarkerConnectionDebug(this.tags.asArray()[0].slice(0,5), this, 0xFF2222, seconds);
        }
    },
}]));

//! Base action marker
//! Allows you to set various custom stuff =) It's linked to CutsceneController.
//! Bake your own when needed =)
registerEntityClass(bakePlugins(WorldMarker, [{
    _class: 'CutsceneBaseAction',

    shouldAct: true,

    // example properties
    backgroundImage: new StateString(),
    subtitleBackground: new StateString(),

    // the extended baseaction for our usage =)
    baseAction: CutScenes.BaseAction.extend({
        backgroundImage: "",

        doExecute: function() {
            if (this.backgroundImage !== "") this.oldShowHUDImage(this.backgroundImage, 0.5, 0.5, Math.max(Global.aspectRatio, 1), Math.min(Global.aspectRatio, 1));
            return this._super.apply(this, arguments);
        },

        showSubtitleBackground: function() {
            if (Global.gameHUD)
            {
                var factors = Global.gameHUD.calcFactors();
                if (this.subtitleBackground !== "") this.oldShowHUDImage(this.subtitleBackground, 0.5, 0.9, factors.x*800/Global.screenWidth, factors.y*128/Global.screenHeight);
            }
        },
    }),

    init: function() {
        this.backgroundImage = "";
        this.subtitleBackground = "";
    },

    clientActivate: function() {
        this.currPosition = 0;
    },

    clientAct: function(seconds) {
        // if the images differ, update state
        if (this.baseAction.prototype.backgroundImage !== this.backgroundImage)
            this.baseAction.prototype.backgroundImage = this.backgroundImage;

        if (isPlayerEditing()) {
            if (this.tags.asArray()[0] && parseInt(this.tags.asArray()[0].slice(4,5)) >= 0)
                MarkerConnectionDebug(this.tags.asArray()[0].slice(0,5), this, 0xFF9A22, seconds);
        }
    },
}]));

//! Action marker
//! Allows you to make your own actions like spawning monsters etc .. there is always one per controller.
//! You'll need to bake your own to do actions, they depend just on you. This is just some sort of skeleton.
registerEntityClass(bakePlugins(WorldMarker, [{
    _class: 'CutsceneAction',

    shouldAct: true,

    // action! this is an example. you can also use doExecute (ran every frame) and doFinish.
    action: {
        /* If you want to do something, use it like this:
         * 
         * doStart: function() {
         *     this._super.apply(this, arguments);
         *     log(ERROR, "let there be action!");
         * },
         * 
         */
    },

    init: function() {
    },

    clientActivate: function() {
        this.currPosition = 0;
    },

    clientAct: function(seconds) {
        if (isPlayerEditing()) {
            if (this.tags.asArray()[0] && parseInt(this.tags.asArray()[0].slice(4,5)) >= 0)
                MarkerConnectionDebug(this.tags.asArray()[0].slice(0,5), this, 0x22FFD3, seconds);
        }
    },
}]));
