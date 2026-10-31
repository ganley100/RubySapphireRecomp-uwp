cmake_minimum_required(VERSION 3.20)
project(RubyLauncherUWP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(RubyLauncher WIN32 App.cpp)

target_compile_definitions(RubyLauncher PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

target_link_libraries(RubyLauncher PRIVATE user32 gdi32)
