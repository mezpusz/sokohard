[![Build Status](https://travis-ci.org/mezpusz/sokohard.svg?branch=master)](https://travis-ci.org/mezpusz/sokohard)

# sokohard
sokohard is a [Sokoban](https://en.wikipedia.org/wiki/Sokoban) map generator that creates relatively hard-to-solve maps. Solving Sokoban levels is shown to be [PSPACE-complete](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.52.41) and the task of automatically generating hard but still solvable levels can be challenging.

Sokohard uses a procedural approach that takes certain patterns of size 3x3 to create maps of arbitrary size then places the goal fields and use backtracking to find a good start position far away from them. "Far away" can be measured by a lot of metrics, such as moves, box pushes, etc. Sokohard currently uses a mix of moves and box pushes.

The output level is written to a `.sok` file that uses the format described [here](http://www.sokobano.de/wiki/index.php?title=Level_format).
A possible solution is also outputted to a file postfixed `_solution.sok`.

## Requirements

* CMake
* clang

## Building locally

After cloning the repository open up a terminal and hit
````bash
$ cmake .
$ make
````
in the root folder.

This will create the output files with the standalone executable
`sokohard` in the `out` folder.

You can also open it in Xcode or any editor that CMake supports.
````bash
$ cmake . -G Xcode
$ open sokohard.xcodeproj
````
in the root folder.

## Usage

Running without parameters generates a 2x2 (i.e. 6x6 with the pattern size) map with 2 boxes and outputs it to the `out.sok` file.
````bash
$ ./sokohard
````
Parameters are the following:
* `-w` - Width of the map (not including pattern width) - defaults to 2
* `-h` - Height of the map (not including pattern height) - defaults to 2
* `-b` - Boxes to be placed on the map - defaults to 2
* `-o` - Output file name - defaults to `out`
* `-s` - Seed (32-bit integer) for the random generator. - default is current UNIX-epoch timestamp
* `--box-changes` - The box changes (pushes) metric is used instead of the default player moves metric.
