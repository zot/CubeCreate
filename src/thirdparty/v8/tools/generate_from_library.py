#!/usr/bin/env python
# generates cc file from JS

import os, js2c

LIBRARY_FILES = '''
src/runtime.js
src/v8natives.js
src/array.js
src/string.js
src/uri.js
src/math.js
src/messages.js
src/apinatives.js
src/date.js
src/regexp.js
src/json.js
src/liveedit-debugger.js
src/mirror-debugger.js
src/debug-debugger.js
'''.split()

library_files = [s for s in LIBRARY_FILES]
library_files.append('src/macros.py')
js2c.JS2C(library_files, ['gen/libraries.cc', 'gen/libraries-empty.cc'], { 'TYPE': 'CORE' })
