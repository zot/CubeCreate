#!/usr/bin/python

# Copyright 2010 quaker66
# based on mapmodels converter script by Alon Zakai (kripken)
# This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

'''
Usage: mapsounds.py [raw-entities-file] [map.cfg]

raw-entities-file is the output when you load a map with
entities, it is a raw JSON dump of the entities. attr1 is the sound
index, which we will convert.

map.cfg is the file that defines the sounds, using the mapsound command
'''

import sys
import re

sound_filename = sys.argv[2]
sound_file = open(sound_filename, 'r')
sounds = []
for line in sound_file:
    line = line.strip()
    if 'mapsound' in line:
        line = line.replace('  ', ' ')
        sounds.append(line.split(' ')[1].replace('"', ''))
sound_file.close()

def convert_sound(index):
    return sounds[int(index)]

filename = sys.argv[1]
output = filename + ".fixed"
outfile = open(output, 'w')
outfile.write('[\n')
for line in open(filename, 'r'):
    line = line.strip()
    if len(line)>2:
        line_sep = eval(line)[0]
        if re.search('^.*@REPLACE_SOUND_PATH@.*$', line):
            separated = convert_sound(line_sep[2]['attr1'])
            line = re.sub("\"attr1\":\"" + line_sep[2]['attr1'] + "\"", "\"attr1\":\"-1\"", line)
            outfile.write('  ' + re.sub('@REPLACE_SOUND_PATH@', separated, line) + '\n')
        else:
            outfile.write('  ' + str(line) + '\n')
outfile.write(']\n')
outfile.close()

