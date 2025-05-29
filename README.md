# Tower Defense Game

A tower defense game implemented in C++ using Raylib for graphics and the State pattern for the menu system.

## Project Structure
```
TowerDefense/
├── src/
│   ├── GUI/
│   │   ├── MenuDirector.hpp
│   │   ├── MenuDirector.cpp
│   │   ├── MenuState.hpp
│   │   ├── MainMenu.hpp
│   │   ├── DictionaryMenuState.hpp
│   │   ├── PlayMenuState.hpp
│   │   ├── SettingsMenuState.hpp
│   │   ├── TowerInfo.hpp
│   │   ├── TowerListContainer.hpp
│   │   ├── PagedContainer.hpp
│   │   ├── MenuType.hpp
│   │   └── MenuItem.hpp
│   └── main.cpp
├── raylib/
│   ├── include/
│   │   └── raylib.h
│   ├── lib/
│   │   └── raylib.lib
│   └── bin/
│       └── raylib.dll
├── assets/
│   ├── textures/
│   ├── sounds/
│   ├── music/
│   └── fonts/
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