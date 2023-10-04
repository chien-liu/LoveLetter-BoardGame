cmake_minimum_required(VERSION 3.15)

project(LoveLetter-BoardGame VERSION 2.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(gamelibs STATIC 
            src/game.cpp
            src/player.cpp
            src/playerGroup.cpp
            src/card.cpp
            src/cardPile.cpp)
target_include_directories(gamelibs PUBLIC "${PROJECT_SOURCE_DIR}/include")

option(TEST "Compile unittest" OFF)


add_executable(LoveLetter-BoardGame src/main.cpp)
target_include_directories(LoveLetter-BoardGame PUBLIC
                            "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(LoveLetter-BoardGame gamelibs)


if (TEST)
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
    unittest/testCardPile.cpp
    unittest/testPlayer.cpp
    unittest/testPlayerGroup.cpp
    unittest/testGame.cpp)

    target_include_directories(unittest PUBLIC
                              "${PROJECT_SOURCE_DIR}/include")

  target_link_libraries(
    unittest
    gamelibs
    GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(unittest)
endif()