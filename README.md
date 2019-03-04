checkout
--------

```
git clone https://github.com/d31m05z/piHome.git
cd piHome
git submodule update --init
```

requirements
------------

```
apt install cmake libegl1-mesa-dev libgles2-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev 
```

build project
-------------

You should to go to the root project folder and call the build.sh script.

```
./build.sh
```

cross-compile build
-------------------

```
./setup-cross-compile.sh
USE_CROSS_COMPILE=true ./build.sh
```
