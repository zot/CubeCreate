
// Copyright 2010 quaker66. All rights reserved.
// This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

TeleporterPlugin = {
    _class: "Teleporter",

    target: new StateArrayFloat(),
    targetYaw: new StateInteger(),
    teledest: new StateInteger(),
    soundName: new StateString(),

    init: function() {
		this.target = [0, 0, 0]; // some default target
		this.targetYaw = this.yaw; // allow to modify yaw when teledest not specified
        this.teledest = -1; // will not use teledests by default
        this.soundName = "0ad/alarmcreatemiltaryfoot_1.ogg"; // default sound when teleporting
    },

    clientOnCollision: function(collider) {
        if (this.teledest && this.teledest >= 0) {
            var teleDests = getEntitiesByTag('teledest_' + this.teledest);
            if (teleDests.length == 1) {
                collider.position = teleDests[0].position.copy();
                collider.yaw = teleDests[0].yaw;
                collider.velocity = [0, 0, 0]; // reset velocity ..
                if (this.soundname) Sound.play(this.soundName); // play teleport sound
            }
            else log(ERROR, "Wrong number of teledests (0 or > 1): " + teleDests.length);
        }
        else {
            collider.position = this.target; // Simply place the collider at the target
            collider.yaw = (this.targetYaw) ? this.targetYaw : collider.yaw; // adjust yaw, too.
            collider.velocity = [0, 0, 0];
            if (this.soundname) Sound.play(this.soundName); // play teleport sound
        }
    }
};

registerEntityClass(bakePlugins(AreaTrigger, [TeleporterPlugin]));

