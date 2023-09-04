cmake_minimum_required(VERSION 3.14)

project(LoveLetter-BoardGame VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -Wall -Wextra -Wpedantic -pedantic")
# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -DNDEBUG -g0 -O3")

add_executable(LoveLetter-BoardGame
               src/main.cpp
               src/game.cpp
               src/player.cpp
               src/card.cpp)

target_include_directories(LoveLetter-BoardGame PUBLIC
                            "${PROJECT_SOURCE_DIR}/include")


include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


enable_testing()

add_executable(
  unittest
  unittest/testCard.cpp
  unittest/testGame.cpp
  unittest/testPlayer.cpp
  src/game.cpp
  src/player.cpp
  src/card.cpp)

  target_include_directories(unittest PUBLIC
                            "${PROJECT_SOURCE_DIR}/include")

target_link_libraries(
  unittest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unittest)