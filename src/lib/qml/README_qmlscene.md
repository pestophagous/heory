```
#
# Copyright (c) 2020, pestophagous (pestophagous@users.noreply.github.com)
# See LICENSE.txt
#
# https://github.com/pestophagous/
#
```

qmlscene is a Qt utility that loads and displays QML documents even before the
application is complete. It is also a great time-saver for doing small layout
touch-ups even on a completed app.

qmlscene accepts arguments that add import paths.

For convenience, we have packaged all our necessary import paths into a wrapper
script.

Therefore, instead of trying something like `qmlscene main.qml`, please use our
script like so:

```
./runscene main.qml
```
