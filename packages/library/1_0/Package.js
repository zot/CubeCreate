
// Copyright 2010 Alon Zakai ('kripken'). All rights reserved.
// This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

Global.LIBRARY_VERSION = '1_0';

// Intensity version comparing

function isIntensityVersionAtLeast(test) {
    function makeComparable(str) {
        var values = str.split('.');
        var ret = 0, mul = 1;
        for (var i = values.length-1; i >= 0; i--) {
            eval(assert(' Math.floor(values[i]) < 100 '));
            ret += mul*Math.floor(values[i]);
            mul *= 100;
        }
        return ret;
    }
    return makeComparable(Global.version) >= makeComparable(test);
}


// Replacements for src/javascript stuff

_logicEntityClasses = {}; // Clear old classes, make room for new

Library.include('library/' + Global.LIBRARY_VERSION + '/Tools', true);
Library.include('library/' + Global.LIBRARY_VERSION + '/__CorePatches', true);
