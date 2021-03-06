![Linux Tests](https://github.com/gloomyzen/slayer-escape/workflows/Linux%20Tests/badge.svg?branch=master)
# Slayer Escape

#### Project submodules structure:

- (root) [Current game project](https://github.com/gloomyzen/slayer-escape)
- (src/common) [Common modules for all games](https://github.com/gloomyzen/cocos2d-common)
- (cocos2d) [Modified core](https://github.com/gloomyzen/cocos2d)
- (lib/dragonbones) [dragonBones for cocos2d v4](https://github.com/gloomyzen/cocos2d-dragonbones)
- (lib/imgui) [ImGui for cocos2d v4](https://github.com/gloomyzen/cocos2d-x-imgui)

#### First of all, be sure to clone all submodules:
```bash
git clone --recurse-submodules git@github.com:gloomyzen/slayer-escape.git slayer-escape 
cd slayer-escape
```

#### Install cocos2d v4:
1. Install Boost, CMake and Python 2.7 on your system
2. Install VS for win32 or XCode for macOS
3. Download Cocos2d-x (cocos2d-x-4.0.zip) from www.cocos2d-x.org and unzip it in a folder that you want.
For example, for Win32 -> unzip to C:/bin/cocos2dx, for MacOs /Application/Develpment/cocos2dx
4. Just run `python setyp.py` in cocos2dx folder

#### Build from sources :
```bash
cmake .. -DDEBUG=1
make -j$(nproc)
```

#### Generate project file (VS, Xcode, Android studio) :

For XCode - mac project
```bash
cd proj.ios_mac/mac/
cmake ../.. -GXcode -DDEBUG=1
sudo xcode-select --reset
```

For XCode - ios project
```bash
mkdir build && cd build
cmake ../.. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphoneos
sudo xcode-select --reset
```

For iOS destribution
```bash
cmake -S . -B build -GXcode -DCMAKE_TOOLCHAIN_FILE=cmake/ios.mini.cmake 
cmake --build build --config Release --target slayer-escape -- -quiet -jobs 16
```

For Visual Studio Community 2019
```bash
cmake -S . -B build -G "Visual Studio 16 2019" -A Win32 -DDEBUG=1
and open $(PROJECT_NAME).sln file from `build` folder and set $(PROJECT_NAME) target as "startup project" in "solution explorer"
```

For Android studio:
android gradle plugin version: 3.6.3
gradle version: 5.6.4
NDK 21.0.6011959


#Credits
- SF Pro Text Regular Font - https://fontsfree.net/sf-pro-text-regular-font-download.html
- Amazing tilesets, used for demo - https://cainos.itch.io/pixel-art-top-down-basic