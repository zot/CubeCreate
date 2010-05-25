// Copyright 2010 quaker66. All rights reserved.
// This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

//! these are required libraries to include, since we use functions from them.
Library.include('library/' + Global.LIBRARY_VERSION + '/Firing');
Library.include('library/' + Global.LIBRARY_VERSION + '/Editing');

Flashlight = {
    plugins: {
        //! Client effect handler, in our case it shows some light.
        handleClientEffect: function(flashlightPlayer, targetPosition, minLightRadius, maxLightRadius, lightColor, carLightsDistance, targetPositionB, targetPositionC) {
            // check distances .. based on that, scale light as needed. Don't scale it below minLightRadius or above maxLightRadius
            if (distance(flashlightPlayer.position, targetPosition) > maxLightRadius)
              var dist = maxLightRadius;
            else if (distance(flashlightPlayer.position, targetPosition) < minLightRadius)
              var dist = minLightRadius;
            else
              var dist = distance(flashlightPlayer.position, targetPosition);
            // add our light, finally. Don't show if we're in edit mode.
            if (!isPlayerEditing(flashlightPlayer)) 
              if (carLightsDistance < 0) Effect.addDynamicLight(targetPosition, dist, lightColor, 0);
              else { // car lights - special occasion
                  Effect.addDynamicLight(targetPositionB, dist, lightColor, 0);
                  Effect.addDynamicLight(targetPositionC, dist, lightColor, 0);
              }
        },

        //! this is called every frame, so actions can be in sync every frame
        doServerRequest: function(flashlightPlayer, targetPosition, minLightRadius, maxLightRadius, lightColor, carLightsDistance, targetPositionB, targetPositionC) {
            // Send network protocol message
            flashlightPlayer.lightingInfo = [targetPosition.x, targetPosition.y, targetPosition.z, minLightRadius, maxLightRadius, lightColor, carLightsDistance, targetPositionB.x, targetPositionB.y, targetPositionB.z, targetPositionC.x, targetPositionC.y, targetPositionC.z];
        },

        //! Network protocol so it can be all sync between clients
        protocol: {
            // this is array where we store the target position for clients, has 3 elements (x,y,z)
            lightingInfo: new StateArrayFloat({ clientSet: true, hasHistory: false }),

            // this gets called on server.
            activate: function() {
                this.connect('onModify_lightingInfo', this.onLightingInfo);
            },

            // and this on client.
            clientActivate: function() {
                this.connect('client_onModify_lightingInfo', this.onLightingInfo);
            },

            // finally function doing something visually (calls client effect)
            onLightingInfo: function(info) {
                if (info.length !== 13) return;
                var targetPosition = new Vector3(info.slice(0,3));
                var minLightRadius = info[3];
                var maxLightRadius = info[4];
                var lightColor = info[5];
                var carLightsDistance = info[6];
                var targetPositionB = new Vector3(info.slice(7,10));
                var targetPositionC = new Vector3(info.slice(10,13));
                if (Global.CLIENT) { // under every client, onLightingInfo gets called and visual effect is shown.
                    Flashlight.plugins.handleClientEffect(this, targetPosition, minLightRadius, maxLightRadius, lightColor, carLightsDistance, targetPositionB, targetPositionC); // targetPosition is different under every client.
                }
            },
        },

        //! Player plugin. Takes care of HUD and flashlight battery control.
        player: {
            // counter used to take care of battery charge
            lightCounter: 10,
            // actionKey index used to turn flashlight on/off
            flashlightKeyIndex: 17,
            // the total battery capacity
            lightTime: 10,
            // color of flashlight beam
            lightColor: 0xFFEECC,
            // minimal radius. (light gets smaller as we get closer to wall)
            minLightRadius: 3,
            // maximal radius.
            maxLightRadius: 50,
            // X position of HUD
            hudX: 0.1,
            // Y position of HUD
            hudY: 0.9,
            // width of HUD
            hudW: 0.166,
            // height of HUD
            hudH: 0.041,

            // Car lights:
            // distance between lights
            carLightsDistance: 25,
            // enable them?
            carLightsEnabled: 0,

            // function to do HUD, meant to be replaced.
            doHUD: function(count) {
               if (CAPI.showHUDImage) {
                   if (count >= this.lightTime)
                      var image = "data/battery-11r.png";
                   else if (count >= ((this.lightTime / 11.0) * 10))
                      var image = "data/battery-10r.png";
                   else if (count >= ((this.lightTime / 11.0) * 9))
                      var image = "data/battery-9r.png";
                   else if (count >= ((this.lightTime / 11.0) * 8))
                      var image = "data/battery-8r.png";
                   else if (count >= ((this.lightTime / 11.0) * 7))
                      var image = "data/battery-7r.png";
                   else if (count >= ((this.lightTime / 11.0) * 6))
                      var image = "data/battery-6r.png";
                   else if (count >= ((this.lightTime / 11.0) * 5))
                      var image = "data/battery-5r.png";
                   else if (count >= ((this.lightTime / 11.0) * 4))
                      var image = "data/battery-4r.png";
                   else if (count >= ((this.lightTime / 11.0) * 3))
                      var image = "data/battery-3r.png";
                   else if (count >= ((this.lightTime / 11.0) * 2))
                      var image = "data/battery-2r.png";
                   else if (count >= ((this.lightTime / 11.0) * 1))
                      var image = "data/battery-1r.png";
                   else
                      var image = "data/battery-0r.png";

                   CAPI.showHUDImage(image, this.hudX, this.hudY, this.hudW, this.hudH); // it's wrong for now. FIXME
               }
            },

            flashlightOff: function() {
                if (!this.carLightsEnabled) Sound.play("olpc/AdamKeshen/BeatBoxCHIK.wav", this.position);
            },

            flashlightOn: function() {
                if (!this.carLightsEnabled) Sound.play("olpc/AdamKeshen/BeatBoxCHIK.wav", this.position);
            },

            // in clientActivate, we begin stuff .. by default, make flashlight off and add charging / discharging mechanism which does something every second.
            clientActivate: function() {
                this.flashlightActivated = false;
                if (!this.eventman) {
                   this.eventman = GameManager.getSingleton().eventManager.add({
                        secondsBefore: 0,
                        secondsBetween: 1,
                        func: bind(function() {
                            if (!isPlayerEditing(this) && !this.carLightsEnabled) { // in edit mode, disallow all modifications of counter.
                                if (this.flashlightActivated) {
                                    this.lightCounter -= 1;
                                    if (this.lightCounter <= 0) { this.lightCounter = 0; this.flashlightDeactivate(); }
                                } else if (this.lightCounter < this.lightTime) this.lightCounter += 1;
                            }
                        }, this),
                        entity: this,
                    });
                }
            },

            // this is function repeated every frame. Here, we get the target and send server request.
            clientAct: function(seconds) {
                if (this !== getPlayerEntity()) return;

                if (this.flashlightActivated) {
                    if (this.carLightsEnabled) this.lightCounter = 1; // make it proceed if counter is normally disabled in car lights mode
                    if (this.lightCounter > 0) {
                        var posCopy = this.position.copy();
                        posCopy.z += this.upperHeight;
                        var posCopyB = this.position.copy();
                        posCopyB.z += this.eyeHeight;

                        if (!this.carLightsEnabled) {
                            var autoTargetDirection = posCopy.subNew(posCopyB).normalize();
                            var currentOriginPosition = autoTargetDirection.copy();
                            currentOriginPosition.add(this.position);
                            currentOriginPosition.z += this.upperHeight;

                            var targetData = Firing.findTarget(this, 
                                                               currentOriginPosition,
                                                               posCopyB,
                                                               this.position.addNew(new Vector3().fromYawPitch(this.yaw, this.pitch)),
                                                               Editing.getWorldSize());
                            // include some more info in request, like colors or radiuses.
                            Flashlight.plugins.doServerRequest(this, targetData.target, this.minLightRadius, this.maxLightRadius, this.lightColor, -1, new Vector3(0, 0, 0), new Vector3(0, 0, 0));
                        } else {
                            var posCopyC = posCopyB.copy();
                            var posCopyD = posCopyB.copy();
                            posCopyC.add(new Vector3().fromYawPitch(this.yaw - 90, 0).mul(this.carLightsDistance * -1));
                            posCopyD.add(new Vector3().fromYawPitch(this.yaw + 90, 0).mul(this.carLightsDistance * -1));

                            var autoTargetDirection = posCopy.subNew(posCopyB).normalize();
                            var currentOriginPosition = autoTargetDirection.copy();
                            currentOriginPosition.add(this.position);
                            currentOriginPosition.z += this.upperHeight;

                            var autoTargetDirectionB = posCopy.subNew(posCopyC).normalize();
                            var currentOriginPositionB = autoTargetDirectionB.copy();
                            currentOriginPositionB.add(this.position);
                            currentOriginPositionB.z += this.upperHeight;

                            var autoTargetDirectionC = posCopy.subNew(posCopyD).normalize();
                            var currentOriginPositionC = autoTargetDirectionC.copy();
                            currentOriginPositionC.add(this.position);
                            currentOriginPositionC.z += this.upperHeight;
                    
                            var targetData = Firing.findTarget(this, 
                                                               currentOriginPosition,
                                                               posCopyB,
                                                               this.position.addNew(new Vector3().fromYawPitch(this.yaw, 0)),
                                                               Editing.getWorldSize());

                            var targetDataB = Firing.findTarget(this, 
                                                               currentOriginPositionB,
                                                               posCopyC,
                                                               this.position.addNew(new Vector3().fromYawPitch(this.yaw, 0)),
                                                               Editing.getWorldSize());

                            var targetDataC = Firing.findTarget(this, 
                                                               currentOriginPositionC,
                                                               posCopyD,
                                                               this.position.addNew(new Vector3().fromYawPitch(this.yaw, 0)),
                                                               Editing.getWorldSize());

                            Flashlight.plugins.doServerRequest(this, targetData.target, this.minLightRadius, this.maxLightRadius, this.lightColor, this.carLightsDistance, targetDataB.target, targetDataC.target);
                        }
                    }
                }

                // do HUD stuff here
                if (!this.carLightsEnabled) this.doHUD(this.lightCounter);
            },

            // we start flashlight. If already started, then stop it.
            flashlightActivate: function() {
                if (this.flashlightActivated) {
                    this.flashlightActivated = false;
                    this.flashlightOff();
                } else {
                    this.flashlightActivated = true;
                    this.flashlightOn();
                }
            },

            // we stop flashlight. No need to start again.
            flashlightDeactivate: function() {
                this.flashlightActivated = false;
                this.flashlightOff();
            },
        },
    },

    //! this is our action key. Needed to be activated.
    actionKey: function(index, down) {
       if (!down) return;
       if (index == 17) {
           log(ERROR, "Start doing sth..");
           getPlayerEntity().flashlightActivate();
       }
    },
};
