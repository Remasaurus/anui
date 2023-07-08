cmake_minimum_required(VERSION 3.24.0)

project(anui)



if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()


if(WIN32)
message(STATUS ">>> Compiling for Windows with WIN32")
set(OS msw)
set(OS_COMPILE_DEFINITION ANUI_WIN32)

elseif(APPLE)
message(STATUS ">>> Compiling for Apple with COCOA")
set(OS cocoa)
set(OS_COMPILE_DEFINITION ANUI_COCOA)

elseif(UNIX)
message(STATUS ">>> Compiling for Linux with x11")
set(OS x11)
set(OS_COMPILE_DEFINITION ANUI_X11)

else()
message(FATAL_ERROR "ANUI cant recognize operating system :(")
endif()


add_library(${PROJECT_NAME} 
     ./src/${OS}/window.cpp
    #./src/${OS}/FloatingWindow.cpp 
    #"src/events.cpp"
    #"src/${OS}/Application.cpp"
    #"src/${OS}/keyboard.cpp"
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

option(CONSOLE "Create int main and log everything to the console instead of a popup window" ON)
set(CONSOLE ON)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${OS_COMPILE_DEFINITION})

if(CONSOLE)
message(STATUS " >>> Compiling for console")
target_compile_definitions(${PROJECT_NAME} PUBLIC ANUI_CONSOLE)
else()
message(STATUS " >>> Compiling for desktop")
endif()
