cmake_minimum_required(VERSION 2.6)
project(magen)
# SDL is required for pretty much everything
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(.)
include_directories(./libs)

add_executable(magen
    main.cpp
    AppState.cpp
   # AppState.h
)

target_link_libraries(magen ${SDL2_LIBRARIES} )
