cmake_minimum_required(VERSION 3.16)

project(Timer VERSION 0.1 LANGUAGES CXX)

# 1. Enable Qt automatic tools
set(CMAKE_AUTOMOC ON) # Meta-Object Compiler (for signals/slots)
set(CMAKE_AUTOUIC ON) # User Interface Compiler (for .ui files)
set(CMAKE_AUTORCC ON) # Resource Compiler (for .qrc files)

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.0/msvc2022_64/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    Application.cpp
    Application.h
    dialog.h
    dialog.cpp
)

qt_add_executable(Timer
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(Timer PRIVATE 
    Qt6::Widgets 
    Qt6::Core 
    Qt6::Gui
)

# 7. Finalize the target (required for qt_add_executable)
qt_finalize_executable(Timer)
