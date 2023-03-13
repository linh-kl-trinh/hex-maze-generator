# Hexagon Maze Generator

A hexagon maze generator with solution using randomized maze generation algorithm based on Depth-First Search on a hexagonal grid system. Based on a programming assignment from "CPSC 221 - Basic Algorithms and Data Structures" course at the University of British Columbia, this is a modified version that integrates user input.


## The `HexCell`  class

Each `HexCell` has a position on the board given in axial coordinates. Refer to [this page](https://www.redblobgames.com/grids/hexagons/#conversions) for a detailed explanation.


## The `HexBoard` class

 The maze is generated using an depth-first search. When generating the maze, the radius and start coordinate of the maze are specified by the user and the exit is chosen during the algorithm to be the most distant cell away from the start which is also on the edge of the board. The internal shape of the maze is determined by a branch factor along with a seed. These two values determine how neighbours will be chosen during depth-first search.


## Results

- A maze will be generated and stored in the file named "maze.png".
- The same maze with every cell coloured based on the path distance from the start will be stored in the file named "maze coloured based on path distance.png".
- The solutions to the mazes are stored in the files named "maze with solutions.png" and "maze with solutions coloured based on path distance.png", respectively.


## Examples

Below are the results of a maze with a radius of 25 that starts from the center.

- Original maze

<img src="https://github.com/linh-kl-trinh/hex-maze-generator/blob/main/example-images/maze.png" width="300" height="300"><img src="https://github.com/linh-kl-trinh/hex-maze-generator/blob/main/example-images/maze%20coloured%20based%20on%20path%20distance.png" width="300" height="300">

- Solution

<img src="https://github.com/linh-kl-trinh/hex-maze-generator/blob/main/example-images/maze%20with%20solutions.png" width="300" height="300"><img src="https://github.com/linh-kl-trinh/hex-maze-generator/blob/main/example-images/maze%20with%20solutions%20coloured%20based%20on%20path%20distance.png" width="300" height="300">
