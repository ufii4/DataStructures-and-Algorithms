project(tests)

add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests tests.cpp ../DisjointSet.cpp)

target_link_libraries(tests gtest gtest_main)

