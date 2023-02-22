cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Raytracer VERSION 0.1)

include(FetchContent)

FetchContent_Declare(sfml
        GIT_REPOSITORY "https://github.com/SFML/SFML.git"
        GIT_TAG "origin/master"
        SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/sfml"
        )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug
            CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

### Dependency population ###
set(BUILD_SHARED_LIBS OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)

set(SFML_BUILD_NETWORK OFF)

set(SFML_BUILD_AUDIO ON)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_WINDOW ON)

FetchContent_GetProperties(sfml)
if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR})
endif()


### Project headers ###
include_directories(include)

### Project sources ###
file(GLOB_RECURSE SRCS ./srcs/*)

add_executable(
        Raytracer
        srcs/main.cpp
        srcs/Application.class.cpp
        srcs/Color.cpp
        srcs/Drawer.class.cpp
        include/Color.hpp
        include/Drawer.hpp
        include/Raytracer.hpp
        include/Vec3.h include/Camera.h srcs/Camera.cpp include/Hittable.h include/Sphere.h srcs/Sphere.cpp include/HittableList.h srcs/HittableList.cpp include/Constants.h srcs/Vec3.cpp srcs/Vec3.cpp)

target_link_libraries(
        Raytracer
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

install(TARGETS Raytracer)