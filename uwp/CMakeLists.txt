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
    WINAPI_FAMILY=WINAPI_FAMILY_APP
)

# C++/WinRT + UWP
target_link_libraries(RubyLauncher PRIVATE
    WindowsApp
    runtimeobject
)

# Helpful when generating a VS UWP-style project
set_target_properties(RubyLauncher PROPERTIES
    VS_WINDOWS_TARGET_PLATFORM_MIN_VERSION "10.0.17763.0"
    VS_GLOBAL_MinimalCoreWin "true"
)
