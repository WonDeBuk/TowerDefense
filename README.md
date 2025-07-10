# Tower Defense Game

A tower defense game implemented in C++ using Raylib for graphics and the State pattern for the menu system.

## Project Structure
```
TowerDefense/
├── src/
│   ├── main.cpp
│   ├── Utils/
│   │   ├── AssetManager.cpp
│   │   ├── AssetManager.h
│   │   ├── MathUtils.hpp
│   │   └── UnicodeText.hpp
│   ├── Game/
│   │   ├── Attack.cpp
│   │   ├── Attack.h
│   │   ├── Enemy.cpp
│   │   ├── Enemy.h
│   │   ├── GameManager.cpp
│   │   ├── GameManager.h
│   │   ├── Tower.cpp
│   │   ├── Tower.h
│   │   ├── Attack/
│   │   │   ├── Area.h
│   │   │   ├── Bullet.h
│   │   │   ├── Laser.h
│   │   │   ├── Missile.h
│   │   │   └── Projectile.h
│   │   ├── Enemy/
│   │   │   └── Slime.h
│   │   └── Tower/
│   │       └── Frieren.h
│   └── GUI/
│       ├── Director.cpp
│       ├── Director.h
│       ├── RenderState.cpp
│       ├── RenderState.h
│       ├── State/
│       │   ├── DictionaryState.cpp
│       │   ├── DictionaryState.h
│       │   ├── GameState.cpp
│       │   ├── GameState.h
│       │   ├── LoadGameState.cpp
│       │   ├── LoadGameState.h
│       │   ├── MainState.cpp
│       │   ├── MainState.h
│       │   ├── PlayState.cpp
│       │   ├── PlayState.h
│       │   ├── SettingState.cpp
│       │   ├── SettingState.h
│       │   ├── WaitingState.cpp
│       │   └── WaitingState.h
│       └── Element/
│           ├── ChampionListContainer.cpp
│           ├── ChampionListContainer.h
│           └── PagedContainer.h
├── raylib/
│   ├── include/
│   │   ├── raylib.h
│   │   ├── raymath.h
│   │   └── rlgl.h
│   ├── lib/
│   │   └── raylib.lib
│   └── bin/
│       └── raylib.dll
├── assets/
│   ├── fonts/
│   │   └── CoderCrux.otf
│   └── textures/
│       └── ui/
│           └── [various image and shader files]
├── CMakeLists.txt
└── README.md
```

## Prerequisites
- CMake (version 3.10 or higher)
- C++ compiler with C++17 support
- Raylib library files (included in the `raylib` directory)

## Setup Instructions

1. Create the project directory structure as shown above.

2. Download Raylib for Windows and copy the following files:
   - Copy `raylib.h` to `raylib/include/`
   - Copy `raylib.lib` to `raylib/lib/`
   - Copy `raylib.dll` to `raylib/bin/`

3. Build the project:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

4. Run the game:
```bash
./TowerDefense
```