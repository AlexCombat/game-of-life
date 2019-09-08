cmake_minimum_required(VERSION 3.9.1)
project(game_of_life)

file(GLOB SOURCES lib/*.cpp lib/*.hpp)
file(GLOB TEST_SOURCES test/*.cpp test/*.hpp)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_library(game_of_life STATIC ${SOURCES})
add_executable(game_of_life_test ${TEST_SOURCES})

set_target_properties(game_of_life PROPERTIES CXX_STANDARD 17)
set_target_properties(game_of_life_test PROPERTIES CXX_STANDARD 17)

target_include_directories(game_of_life PUBLIC lib)
target_include_directories(game_of_life_test PRIVATE ${GTEST_INCLUDE_DIRS} $<TARGET_PROPERTY:game_of_life,INTERFACE_INCLUDE_DIRECTORIES>)

target_link_libraries(game_of_life_test PRIVATE ${GTEST_LIBRARIES} Threads::Threads game_of_life)

if(WIN32)
    target_compile_options(game_of_life PRIVATE "/MT")
    target_compile_options(game_of_life_test PRIVATE "/MT")
endif()

enable_testing()

add_test(NAME simple_test COMMAND game_of_life_test)
