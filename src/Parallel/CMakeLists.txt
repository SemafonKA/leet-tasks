set(SRC_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(PARALLEL_INC_ROOT ${SRC_ROOT}/include)


add_subdirectory(
    ${SRC_ROOT}/thread_pool
)

add_library(Parallel INTERFACE)

target_include_directories(Parallel
  INTERFACE
    ${PARALLEL_INC_ROOT}
)

target_link_libraries(Parallel
#   PRIVATE
#     leet_tasks_options
  INTERFACE
    thread_pool
)
