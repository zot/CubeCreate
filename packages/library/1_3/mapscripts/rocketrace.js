// Copyright (C) 2009 Alon 'Kripken' Zakai

Library.include('library/1_3/');

Library.include('library/' + Global.LIBRARY_VERSION + '/__CorePatches');
Library.include('library/' + Global.LIBRARY_VERSION + '/Plugins');
Library.include('library/' + Global.LIBRARY_VERSION + '/Health');
Library.include('library/' + Global.LIBRARY_VERSION + '/GameManager');
Library.include('library/' + Global.LIBRARY_VERSION + '/Vehicles');
Library.include('library/' + Global.LIBRARY_VERSION + '/ZeroG');
Library.include('library/' + Global.LIBRARY_VERSION + '/CutScenes');
Library.include('library/' + Global.LIBRARY_VERSION + '/Chat');
Library.include('library/' + Global.LIBRARY_VERSION + '/mapelements/PlotTriggers');
Library.include('library/' + Global.LIBRARY_VERSION + '/modes/Racing');

// Default materials, etc.

Library.include('library/' + Global.LIBRARY_VERSION + '/MapDefaults');

// Textures

Library.include('textures/gk/swarm/');

// Map settings

Map.fogColor(0, 0, 0);
Map.fog(9999);
Map.loadSky("skyboxes/philo/sky3");
Map.skylight(100, 100, 100);
Map.ambient(20);
Map.shadowmapAmbient("0x000000");
Map.shadowmapAngle(300);


//// Player class

GamePlayer = registerEntityClass(
    bakePlugins(
        Player,
        [
            Vehicles.plugin,
            Health.plugin,
            GameManager.playerPlugin,
            Chat.playerPlugin,
            RacingMode.playerPlugin,
            {
                _class: "GamePlayer",

                accessories: new StateJSON(),

                init: function() {
                    this.modelName = '';
                    this.HUDModelName = '';

                    this.accessories = {};
                    this.eyeHeight = 6;
                    this.aboveEye = 6;
                    this.thrustPowerForward = 300;
                    this.thrustPowerBackward = 10;
                },

                createRenderingArgs: function(mdlname, anim, o, yaw, pitch, flags, basetime) {
                    return [this, mdlname, anim, o.x, o.y, o.z, yaw-90, pitch, 60, flags, basetime];
                },

                onCollision: function() {
                    if (this === getPlayerEntity()) {
                        CutScenes.showDeathCamera(this);
                    }

                    this.health = 0;
                    Effect.fireball(PARTICLE.EXPLOSION, this.position, 50);
                    Sound.play('yo_frankie/DeathFlash.wav', this.position);
                    this.deathDelay = 0.15;
                    this.deathSize = 40;
                },

                clientAct: function(seconds) {
                    if (this.health <= 0) {
                        Effect.splash(PARTICLE.SMOKE, 2, 2.0, this.position, 0x000000, 5.25, 35, -100);
                        this.deathDelay -= seconds;
                        if (this.deathDelay <= 0 && this.deathSize >= 15) {
                            this.deathDelay = 0.15;
                            this.deathSize *= 0.95;
                            Effect.fireball(PARTICLE.EXPLOSION, this.position, this.deathSize);
                            if (Math.random() < 0.25) Sound.play('yo_frankie/DeathFlash.wav', this.position);
                        }
                    }
                },
            },
        ]
    )
);

//// Application

ApplicationManager.setApplicationClass(Application.extend({
    _class: "GameApplication",

    getPcClass: function() {
        return "GamePlayer";
    },

    // Replace this with appropriate behaviour for when a player falls of the map
    clientOnEntityOffMap: function(entity) {
        entity.position = [600,600,600];
    },

    getScoreboardText: GameManager.getScoreboardText,

/*
    actionKey: function(index, down) {
        if (!down) return;

        var key = '';
        if (index === 0) {
            key = 'weapon_launcher/left';
        } else if (index <= 6) {
            key = 'weapon_' + index + '/left';
        } else if (index === 7) {
            key = 'armor_1';
        } else if (index === 8) {
            key = 'armor_2';
        }

        var temp = getPlayerEntity().accessories;
        if (temp[key]) {
            delete temp[key];
        } else {
            temp[key] = true;
        }
        getPlayerEntity().accessories = temp;
    },
*/

    handleTextMessage: Chat.handleTextMessage,
}));

// Setup game

GameManager.setup([
    GameManager.managerPlugins.messages,
    GameManager.managerPlugins.eventList,
//    Chat.extraPlugins.skypeManager,
    RacingMode.managerPlugin,
    {
        clientActivate: function() {
            if (!this.shownWelcome) {
//                this.addHUDMessage("Press 'H' for help", 0xCCDDFF, 8.0);
                this.shownWelcome = true;
            }
        },

        startRace: function() {
            forEach(getEntitiesByTag('start_door'), function(entity) {
                entity.state = 'open';
            });

            GameManager.getSingleton().eventManager.add({
                secondsBefore: 8,
                func: function() {
                    forEach(getEntitiesByTag('start_door'), function(entity) {
                        entity.state = 'closed';
                    });
                },
            });
        },
    },
]);

if (Global.SERVER) { // Run this only on the server - not the clients
    var entities = CAPI.readFile("./entities.json");
    loadEntities(entities);

    GameManager.getSingleton().registerTeams([
        {
            _name: 'players',
            setup: function(player) {
                player.defaultModelName = 'space/ships/1';
                player.defaultHUDModelName = '';
            },
        },
    ]);
}

Vehicles.AIR_FRICTION = 0.9;

