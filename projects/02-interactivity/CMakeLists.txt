cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(interactivity)

include_directories(
    ../
    $ENV{CINDER}/include
)

link_directories(
    $ENV{CINDER}/lib/msw/x86
)

if (MSVC)
    message (STATUS "Setting MSVC switches")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
    set(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:LIBCMT)
endif (MSVC)

add_executable(interactivity src/interactivityApp.cpp)

if (MSVC)
    set_target_properties(interactivity PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
endif (MSVC)

target_link_libraries(interactivity
    cinder-${CMAKE_VS_PLATFORM_TOOLSET}_d.lib
)
