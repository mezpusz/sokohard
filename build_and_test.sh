#!/bin/bash

bazel build //:sokohard

readonly SEED2x2w3="1517341101"
readonly SEED3x3w2="1517341110"
time bazel-bin/sokohard --width 2 --height 2 --numBoxes 3 --seed ${SEED2x2w3}
time bazel-bin/sokohard --width 3 --height 3 --numBoxes 2 --seed ${SEED3x3w2}

#Random seed is 1517341101
#Generating level....................................................................................................finished!
#
#Size: 6x6
#Number of boxes: 3
#Difficulty (measured as the sum of
#box lines and box changes): 20
#
#Writing result map to file...completed!
#
#real	0m9.936s
#user	0m9.705s
#sys	0m0.079s
#Random seed is 1517341110
#Generating level....................................................................................................finished!
#
#Size: 9x9
#Number of boxes: 2
#Difficulty (measured as the sum of
#box lines and box changes): 21
#
#Writing result map to file...completed!
#
#real	0m17.667s
#user	0m17.290s
#sys	0m0.117s
