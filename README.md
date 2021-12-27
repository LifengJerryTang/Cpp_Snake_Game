# CPPND: Capstone Snake Game Example

<img src="snake_game.gif"/>

In this project, I chose to extend the Snake Game by following the principles I have learned throughout this Nanodegree Program.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## How the Game works

1. The game will ask you to choose the level of the game that you want to play.
  * Level 1: The player simply controls the snake to eat as much food as possible to earn as many points as possible.
  * Level 2: In this level, a bonus food (red colored) will appear and change its location concurrently when the player
    is controlling the snake. When the snake eats the bonus food, it will earn 5 points and will not grow its body. HOWEVER, the bonus food will randomly toggle itself between a bomb and the actual edible food WITHOUT changing its
    appearance. The snake dies if it ends up eating the bomb.
  * Level 3: Everything in level 2 will be included in level 3, but what's different is that the boundary of the 
    game window will serve as walls. The snake dies if it hits any of the 4 walls.
2. Play the game by controlling the snake and earn as many points as possible!
3. If the snake dies, the game terminates and will display the earned points and your final size in the console.

## Addressed Rubric Points
1. Loop, Functions, I/O - The project demostrates an understanding of C++ functions and control structures
  * In my implementation, the ChooseLevel() function in game.cpp uses a while loop structure to ask the user to choose   game level. If the user were to enter a invalid input, the while loop will keep asks the user to input game level until the user enters a valid level.

2. Object Oriented Programming - The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  * I created the Food class to encapsulate all the data and logic that a food object needs. I also created a GameObject super class to hold the data that any game object might need (In my implementation, food and snake are deemed as game objects, and they extend the game object class).

3. Object Oriented Programming - One member function in an inherited class overrides a virtual base class member function.
  * Both the Snake class and the Food class extend the GameObject class, and they override the Update() virtual member function in the GameObject class.

4. Concurrency - The project uses multiple threads in the execution.
  * My game concurrently changes the position of the bonus food when the game level is 2 or above. At the very beginning of the Run() method in game.cpp, it starts a new thread for the RandomlyPlaceBonusFood() function in game.cpp.

5. Concurrency - A mutex or lock is used in the project
  * Because the snake member variable and the bonus food member variable of the Game class are shared variables between the RandomlyPlaceBonusFood thread and the main thread, unique locks are used in order to avoid data races.
  


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
