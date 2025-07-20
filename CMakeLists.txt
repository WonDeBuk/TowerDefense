cmake_minimum_required(VERSION 3.10)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add _CRT_SECURE_NO_WARNINGS definition
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Define asset paths
set(RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resource")
set(RESOURCE_OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resource")

# Add header files
set(HEADERS
    src/Utils/Define.h
    src/Utils/ResourceManager.h
    src/Utils/Champion.h
    src/GUI/Director.h
    src/Utils/MathUtils.hpp
    src/Utils/UnicodeText.hpp
    src/GUI/RenderState.h
    src/GUI/State/DictionaryState.h
    src/GUI/State/LoadGameState.h
    src/GUI/State/MainState.h
    src/GUI/State/PlayState.h
    src/GUI/State/SettingState.h
    src/GUI/State/WaitingState.h
    src/GUI/State/GameState.h
    src/GUI/Element/PagedContainer.h
    src/GUI/Element/ChampionListContainer.h
    src/Game/GameManager.h
    src/Game/WaveManager.h
    src/Game/VisualManager.h
    src/Game/Enemy.h
    src/Game/Attack.h
    src/Game/Tower.h
    src/Game/Attack/Projectile.h
    src/Game/Attack/Missile.h
    src/Game/Enemy/Slime.h
    src/Game/Enemy/Dino.h
    src/Game/Enemy/Bandit.h
    src/Game/Enemy/Hornet.h
    src/Game/Enemy/Golem.h
    src/Game/Enemy/Grumble.h
    src/Game/Enemy/Titan.h
    src/Game/Enemy/Revenant.h
    src/Game/Enemy/Brawler.h
    src/Game/Tower/Frieren.h
    src/Game/Tower/Milim.h
    src/Game/Tower/Rimuru.h
    src/Game/Tower/Fern.h
    src/Game/Tower/Shuna.h
    src/Game/Tower/Stark.h
)

# Add source files
set(SOURCES
    src/main.cpp
    src/Utils/ResourceManager.cpp
    src/Utils/MathUtils.cpp
    src/Utils/Champion.cpp
    src/Utils/UnicodeText.hpp
    src/GUI/Director.cpp
    src/GUI/RenderState.cpp
    src/GUI/State/DictionaryState.cpp
    src/GUI/State/LoadGameState.cpp
    src/GUI/State/MainState.cpp
    src/GUI/State/PlayState.cpp
    src/GUI/State/SettingState.cpp
    src/GUI/State/WaitingState.cpp
    src/GUI/State/GameState.cpp
    src/GUI/Element/PagedContainer.h
    src/GUI/Element/ChampionListContainer.cpp
    src/game/GameManager.cpp
    src/game/WaveManager.cpp
    src/Game/VisualManager.cpp
    src/game/Enemy.cpp
    src/Game/Enemy/Slime.cpp
    src/Game/Enemy/Dino.cpp
    src/Game/Enemy/Bandit.cpp
    src/Game/Enemy/Hornet.cpp
    src/Game/Enemy/Golem.cpp
    src/Game/Enemy/Grumble.cpp
    src/Game/Enemy/Titan.cpp
    src/Game/Enemy/Revenant.cpp
    src/Game/Enemy/Brawler.cpp
    src/Game/Attack.cpp
    src/Game/Attack/Projectile.cpp
    src/Game/Attack/Missile.cpp
    src/Game/Tower.cpp
    src/Game/Tower/Frieren.cpp
    src/Game/Tower/Milim.cpp
    src/Game/Tower/Rimuru.cpp
    src/Game/Tower/Fern.cpp
    src/Game/Tower/Shuna.cpp
    src/Game/Tower/Stark.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify the path to Raylib library and include directories
# You'll need to modify these paths according to your Raylib installation
set(RAYLIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/raylib")
set(RAYLIB_LIBRARY "${RAYLIB_PATH}/lib/raylib.lib")
set(RAYLIB_INCLUDE_DIR "${RAYLIB_PATH}/include")

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${RAYLIB_INCLUDE_DIR}
)

# Link Raylib and required Windows libraries
target_link_libraries(${PROJECT_NAME} PRIVATE 
    ${RAYLIB_LIBRARY}
    winmm.lib 
    gdi32.lib 
    user32.lib 
    shell32.lib 
    opengl32.lib
)

# Set MSVCRT linking options
if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        LINK_FLAGS "/NODEFAULTLIB:MSVCRT"
    )
endif()

# Copy raylib.dll to output directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${RAYLIB_PATH}/bin/raylib.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/raylib.dll
)

# Add preprocessor definition for asset path
target_compile_definitions(${PROJECT_NAME} PRIVATE
    RESOURCE_PATH="${RESOURCE_DIR}"
) 