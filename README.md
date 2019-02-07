checkout
--------

```
git clone https://github.com/d31m05z/piSecurity.git
cd piSecurity
git submodule update --init
```

requirements
------------

```
apt install cmake libegl1-mesa-dev libgles2-mesa-dev libxrandr-dev libxinerama-dev libxcursor-dev 
```

build 3rdparty
--------------

Navigate to 3rdparty folder and call build.sh script.

```
cd 3rdparty
MAKEFLAGS=-j4 ./build.sh
```

build project
-------------

You should to go to the root project folder and call build.sh script with correct CMAKE_PREFIX_PATH parameter.

```
CMAKE_PREFIX_PATH=$PWD/3rdparty/install ./build.sh
```

