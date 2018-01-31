#!/bin/bash

set -euo "pipefail"

make

readonly SEED2x2w3="1517341101"
readonly SEED3x3w2="1517341110"
readonly SEED2x2w5="1517341640"

time out/sokohard --width 2 --height 2 --numBoxes 3 --seed ${SEED2x2w3}
time out/sokohard --width 3 --height 3 --numBoxes 2 --seed ${SEED3x3w2}
time out/sokohard --width 2 --height 2 --numBoxes 5 --seed ${SEED2x2w5}

#1517341101, 6x6, boxes: 3
#Difficulty: 20
#real	0m9.936s
#user	0m9.705s
#sys	0m0.079s
#1517341110, 9x9, boxes: 2
#Difficulty: 21
#real	0m17.667s
#user	0m17.290s
#sys	0m0.117s
#1517341640, 6x6, boxes: 5
#Difficulty: 49
#real	0m45.234s
#user	0m44.290s
#sys	0m0.304s
