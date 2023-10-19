#===============================================================================
cmake_minimum_required(VERSION 3.22.0)
project(tp_worms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

#===============================================================================
include(FetchContent)

#===============================================================================
# Box2D
set(BOX2D_BUILD_TESTBED OFF)

FetchContent_Declare(
    Box2D
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(Box2D)

#===============================================================================
# libSDL2pp
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

FetchContent_Declare(
    libSDL2pp
    GIT_REPOSITORY https://github.com/libSDL2pp/libSDL2pp.git
    GIT_TAG        0.16.2
)

FetchContent_MakeAvailable(libSDL2pp)

#===============================================================================
# GTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#===============================================================================
add_subdirectory(client)
add_subdirectory(common_base)
add_subdirectory(server)

add_subdirectory(test)
