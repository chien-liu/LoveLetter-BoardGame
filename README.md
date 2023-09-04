# Usage
An implementation of Love Letter (Board Game) with a text-based interface.\
See also: [Game Introduction](https://en.wikipedia.org/wiki/Love_Letter_(card_game))

## Game Senarios
In this implementation, the human player plays against three agents. As shown below, p0 is the human player, while p1-3 are the agents.

```
[Game info] Round:5. Turn to Player 3
        p2:X
p1:Δ            p3:O
        p0:O
```

* p0:O    // alive
* p1:Δ    // protected by Handmaid
* p2:X    // dead


# Build
```
$ git clone https://github.com/liu-chien/LoveLetter-BoardGame.git
$ cd LoveLetter-BoardGame
$ make
```

or with meson:

```
$ git clone https://github.com/liu-chien/LoveLetter-BoardGame.git
$ cd LoveLetter-BoardGame
$ meson build
$ ninja -C build  # The executable LoveLetter-BoardGame is in build/ instead of bin/
```

or with CMake
```
$ git clone https://github.com/liu-chien/LoveLetter-BoardGame.git
$ cd LoveLetter-BoardGame
$ mkdir build && cd build
$ cmake ..
$ cmake --build .
```

## Run
Execute game
```
$ ./LoveLetter-BoardGame
```

Unittest
```
$ ./unittest
```

# Tested environments
* Ubuntu 20.04
