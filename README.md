# Tower Defense Game

A tower defense game implemented in C++ using Raylib for graphics and the Builder pattern for the menu system.

## Project Structure
```
TowerDefense/
├── src/
│   ├── GUI/
│   │   ├── MenuBuilder.hpp
│   │   ├── MainMenuBuilder.hpp
│   │   └── Menu.hpp
│   └── main.cpp
├── raylib/
│   ├── include/
│   │   └── raylib.h
│   ├── lib/
│   │   └── raylib.lib
│   └── bin/
│       └── raylib.dll
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

## Controls
- Use the mouse to interact with menu items
- Click on buttons to navigate through different screens
- Press ESC to return to the main menu from game or settings screens

## Implementation Details
The menu system is implemented using the Builder design pattern, which allows for flexible construction of different types of menus. The main components are:

- `MenuBuilder`: Abstract interface for menu construction
- `MainMenuBuilder`: Concrete implementation of the menu builder
- `Menu`: The product class that represents a complete menu
- `MenuItem`: Class representing individual menu items (buttons) 