set(SRC_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(ALL_SRC
    ${SRC_ROOT}/main.cpp
)

add_executable(${PROJECT_NAME} 
    ${ALL_SRC}
)

add_subdirectory(Parallel)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    leet_tasks_options
    Parallel
)
