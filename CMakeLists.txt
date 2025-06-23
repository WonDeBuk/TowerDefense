cmake_minimum_required(VERSION 3.10)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add _CRT_SECURE_NO_WARNINGS definition
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# Define asset paths
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")

# Add header files
set(HEADERS
    src/Game/GameManager.h
    src/Game/Enemy.h
    src/Game/Attack.h
    src/Game/Tower.h
)

# Add source files
set(SOURCES
    src/main.cpp
    src/game/GameManager.cpp
    src/Game/Attack.cpp
    src/Game/Enemy.cpp
    src/Game/Tower.cpp
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

# Create directories for assets in build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/maps
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets/ui
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/saves
)

# Copy assets to build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_DIR}"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)

# Add preprocessor definition for asset path
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ASSETS_PATH="${ASSETS_DIR}"
) 