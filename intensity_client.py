#!/usr/bin/python

# Copyright 2010 Alon Zakai ('kripken'). All rights reserved.
# This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

# Initialize

import os
import sys

from intensity.base import *
Global.init_as_client()

import intensity.c_module
CModule = intensity.c_module.CModule.holder

print "Intensity Engine Client parameters:", sys.argv

execfile( os.path.join(PYTHON_SCRIPT_DIR, "init.py") )

import __main__

print "Setting home dir"

home_dir = None # Will use an OS-specific one
try:
    for arg in sys.argv[1:]:
        if arg[0] != '-':
            home_dir = arg
            break
except IndexError:
    print "Note: No home directory specified, so using default (which is tied to this operating-system level user)"
if home_dir is not None:
    set_home_dir(home_dir)

print "Initializing config"

config_filename = os.path.join( get_home_subdir(), 'settings.json' )
template_filename = os.path.join( os.getcwd(), 'data', 'client_settings_template.json' )

init_config(config_filename, template_filename)

print "Initializing logging"

CModule.init_logging()

#from storm.locals import *

log(logging.DEBUG, "Setting C home dir")

CModule.set_home_dir( get_home_subdir() )

print "Initializing scripting engine"
CModule.create_engine()

load_components()

# Utilities

log(logging.DEBUG, "Loading utilities")

from intensity.utility import *

######### Run application-specific startup script.
########
########run_startup_script()

# Client-specific imports: Auth etc.

from intensity.client.auth import *

# Console / main

if get_config('System', 'console', '') == '1':
    from intensity.console import *

    console_thread = ConsoleThread()
    console_thread.safe_console = SafeConsole(__main__.__dict__)
    console_thread.setDaemon(True) # Do not stop quitting when the main thread quits
    console_thread.start()

log(logging.DEBUG, "Running main()")
CModule.main()
