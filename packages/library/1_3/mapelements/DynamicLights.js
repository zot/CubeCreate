
// Copyright 2010 quaker66. All rights reserved.
// This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

//! Dynamic light entity, accepting same parameters as standard light. May replace static lights in map but doesnt cast shadows.

registerEntityClass(bakePlugins(WorldMarker, [{
    _class: 'DynamicLight',

    shouldAct: { client: true },

    attr1: new StateInteger({ guiName: "radius", altName: "radius" }),
    attr2: new StateInteger({ guiName: "red", altName: "red" }),
    attr3: new StateInteger({ guiName: "green", altName: "green" }),
    attr4: new StateInteger({ guiName: "blue", altName: "blue" }),

    radius: new VariableAlias("attr1"),
    red: new VariableAlias("attr2"),
    green: new VariableAlias("attr3"),
    blue: new VariableAlias("attr1"),

    init: function() {
        this.radius = 100;
        this.red = 128;
        this.green = 128;
        this.blue = 128;
    },

    clientAct: function(seconds) {
        CAPI.addDynlight(this.position.x, this.position.y, this.position.z, this.radius, this.red, this.green, this.blue, 0, 0, 0, 0, 0, 0, 0);
    },
}]));
