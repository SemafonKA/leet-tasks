set(SRC_ROOT ${CMAKE_CURRENT_LIST_DIR})


set(ALL_SRC
    ${SRC_ROOT}/thread_pool.cpp
    ${PARALLEL_INC_ROOT}/Parallel/thread_pool.hpp
)

add_library(thread_pool
    ${ALL_SRC}
)

target_include_directories(thread_pool
  PRIVATE
    ${PARALLEL_INC_ROOT}
)

target_link_libraries(thread_pool
  PRIVATE
    leet_tasks_options
)
