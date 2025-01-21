# Project 2048
## File Organization

!!!jeu2048 is the only relevant folder here!!!

The folder jeu2048 includes 5 directories:

- bareme12: Old version of the game playable through the console, minimal graphical interface.

- bareme16: Old version of the game that is more dynamic and uses the ncurses library.

- fichiers-IA: The code that allows launching the AI that will attempt to win the game.

- fichiers-jeu-complet: Final version of the game, with a better graphical interface that uses SFML.

- ressources: Contains a font file useful for SFML.

Ideally, the last two folders will be the most useful.

modele.cpp and modele.hpp are also located in the jeu2048 folder and are accessible by all other .cpp files.

## How to Play
Once in the jeu2048 folder, execute `jeu` to play, or `IA` to watch the AI play.

If needed, here are some Makefile commands to execute in the terminal that apply to our project:


```Makefile
make clean    #cleans the folder by removing all compilation files and executable files

make jeu      #compiles the final version of the game in the jeu2048 folder, named "jeu"

make IA       #compiles the AI launch file in the jeu2048 folder, named "IA"

make jeu16    #compiles the "16-point scale" version of the game in the jeu2048 folder, named "jeu16"

make jeu12    #compiles the "12-point scale" version of the game in the jeu2048 folder, named "jeu12"

make test     #compiles the modele-test.cpp file in the jeu2048 folder, named "test"
```