cmake_minimum_required(VERSION 3.30)

# Set export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set colorful output
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(leet_tasks
    VERSION 0.0.1
    LANGUAGES CXX
)

include(cmake/PreventInSourceBuilds.cmake)
include(cmake/SetOutputDirectories.cmake)

include(cmake/AddFlagsLibrary.cmake)
AddFlagsLibrary("leet_tasks_options")

add_subdirectory(src)
