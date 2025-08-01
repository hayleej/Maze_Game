# Maze_Game
A command line maze game. Get from one end of the maze to the other without the enemy catching you.

# Installation

1. Download the game using the command 
```
$ git clone https://github.com/hayleej/Maze_Game/
```

2. Move to the project directory
```
$ cd Maze_Game/
```

3. Run make command
```
$ make
```

# How to Play the Game

Run the following command.
```
maze path/to/map.txt
```

## Commands in Game

Use `w`, `s`, `a`, `d` to move the player icon.

`u` can be used to undo the previous move.

## Symbols on Map

The following table outlines the symbols that can be found on the map of the maze and their meaning.

| Symbol                 | Meaning                                 |
|------------------------|-----------------------------------------|
| ^                      | user/player                             |
| x                      | the end goal the player is trying to reach|
| o                      | obstacles and walls in the maze         |
| ~                      | Enemy. They are trying to catch player. |
| #--#<br>\| &nbsp; &nbsp;  \|<br>#--# | Border of the maze.                     |

# Map File

`map.txt` is the file containing the the set up of the maze.

The first line contains three numbers, the amount of objects, the number of rows and number of columns in the map.

The rest of the file lists the objects and their location in the format: `row_number column_number object_code`

An object can be player (0), enemy (1), goal (2), or wall (3).
