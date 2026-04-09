cmake_minimum_required(VERSION 3.16)
project(HighwayEscapePRO C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Ajouter le répertoire include
include_directories(${PROJECT_SOURCE_DIR}/include)

# Trouver Raylib
find_package(raylib QUIET)

if (NOT raylib_FOUND)
    message(STATUS "Raylib non trouvé. Installation via FetchContent...")
    include(FetchContent)
    
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/releases/download/4.5.0/raylib-4.5.0_win64_msvc16.zip
    )
    
    FetchContent_MakeAvailable(raylib)
endif()

# Créer l'exécutable
add_executable(highway_escape
    src/main.c
)

# Lier Raylib
target_link_libraries(highway_escape raylib)

# Options de compilation
if(MSVC)
    target_compile_options(highway_escape PRIVATE /W4)
else()
    target_compile_options(highway_escape PRIVATE -Wall -Wextra -Wpedantic)
endif()
