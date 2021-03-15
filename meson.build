project('LoveLetter-BoardGame', 'cpp',
  version : '0.2',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

inc = include_directories('include')
gtest_dep = [dependency('gtest'), dependency('gtest_main')]

executable(
    'LoveLetter-BoardGame',
    'src/card.cpp',
    'src/game.cpp',
    'src/main.cpp',
    'src/player.cpp',
    include_directories: inc,
)

testAll = executable(
    'testAll',
    'src/card.cpp',
    'src/game.cpp',
    'src/player.cpp',
    'unittest/testCard.cpp',
    'unittest/testPlayer.cpp',
    'unittest/testGame.cpp',
    include_directories: inc,
    dependencies: gtest_dep,
)

test('runTestAll', testAll)
