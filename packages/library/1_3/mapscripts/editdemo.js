/*
 *=============================================================================
 * Copyright (C) 2010 Alon Zakai ('Kripken') kripkensteiner@gmail.com
 *
 * This file is part of the Intensity Engine project,
 *    http://www.intensityengine.com
 *
 * The Intensity Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * The Intensity Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with the Intensity Engine.  If not, see
 *     http://www.gnu.org/licenses/
 *     http://www.gnu.org/licenses/agpl-3.0.html
 *=============================================================================
 */


Library.include('library/1_3/');

Library.include('library/' + Global.LIBRARY_VERSION + '/Plugins');
Library.include('library/' + Global.LIBRARY_VERSION + '/Health');
Library.include('library/' + Global.LIBRARY_VERSION + '/GameManager');
Library.include('library/' + Global.LIBRARY_VERSION + '/Editing');

// Default materials, etc.

Library.include('library/' + Global.LIBRARY_VERSION + '/MapDefaults');

// Textures

Library.include('yo_frankie/');

// Map settings

Map.fogColor(0, 0, 0);
Map.fog(9999);
Map.loadSky("skyboxes/philo/sky3");
Map.skylight(100, 100, 100);
Map.ambient(20);
Map.shadowmapAmbient("0x010101");
Map.shadowmapAngle(300);

//// Player class

GamePlayer = registerEntityClass(
    bakePlugins(
        Player,
        [
            Health.plugin,
            GameManager.playerPlugin,
            {
                _class: "GamePlayer",
                init: function() { this.movementSpeed = 90; },
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

    clientClick: function(button, down) {
        if (down) {
            Editing.createCube(640, 640, 640, 128);
        }
    },
}));

GameManager.setup([
    GameManager.managerPlugins.messages,
    GameManager.managerPlugins.eventList,
]);

//// Load permanent entities

if (Global.SERVER) { // Run this only on the server - not the clients
    var entities = CAPI.readFile("./entities.json");
    loadEntities(entities);

    GameManager.getSingleton().registerTeams([
        {
            _name: 'players',
            setup: function(player) {
                player.defaultModelName = 'stromar_1_1/red';
            },
        },
    ]);
}

//Global.profiling = { interval: 10.0 };

