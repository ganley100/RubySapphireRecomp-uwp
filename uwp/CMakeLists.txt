cmake_minimum_required(VERSION 3.20)
project(RubyLauncherUWP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Minimal UWP / Windows Store style executable (launcher shell only).
add_executable(RubyLauncher WIN32
    App.cpp
    pch.cpp
)

target_precompile_headers(RubyLauncher PRIVATE pch.h)

target_compile_definitions(RubyLauncher PRIVATE
    UNICODE
    _UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
)

# Link WinRT / system libs used by CoreApplication path
target_link_libraries(RubyLauncher PRIVATE
    windowsapp
    ole32
    oleaut32
    runtimeobject
)

# When configured with a Windows Store toolchain these properties help packaging.
set_target_properties(RubyLauncher PROPERTIES
    VS_WINDOWS_TARGET_PLATFORM_MIN_VERSION "10.0.17763.0"
)
