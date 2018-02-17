#!/bin/bash

set -euo "pipefail"

make

readonly SEED2x2w3="1517341101"
readonly SEED3x3w2="1517341110"
readonly SEED2x2w5="1517341640"

time out/sokohard -w 2 -h 2 -b 3 -s ${SEED2x2w3} -o "2x2w3lines"                 # 14
diff 2x2w3lines.sok testfiles/2x2w3lines.sok
diff 2x2w3lines_solution.sok testfiles/2x2w3lines_solution.sok
time out/sokohard -w 2 -h 2 -b 3 -s ${SEED2x2w3} --box-changes -o "2x2w3changes" # 24
diff 2x2w3changes.sok testfiles/2x2w3changes.sok
diff 2x2w3changes_solution.sok testfiles/2x2w3changes_solution.sok
time out/sokohard -w 3 -h 3 -b 2 -s ${SEED3x3w2} -o "3x3w2lines"                 # 13
diff 3x3w2lines.sok testfiles/3x3w2lines.sok
diff 3x3w2lines_solution.sok testfiles/3x3w2lines_solution.sok
time out/sokohard -w 3 -h 3 -b 2 -s ${SEED3x3w2} --box-changes -o "3x3w2changes" # 40
diff 3x3w2changes.sok testfiles/3x3w2changes.sok
diff 3x3w2changes_solution.sok testfiles/3x3w2changes_solution.sok
time out/sokohard -w 2 -h 2 -b 5 -s ${SEED2x2w5} -o "2x2w5lines"                 # 22
diff 2x2w5lines.sok testfiles/2x2w5lines.sok
diff 2x2w5lines_solution.sok testfiles/2x2w5lines_solution.sok
time out/sokohard -w 2 -h 2 -b 5 -s ${SEED2x2w5} --box-changes -o "2x2w5changes" # 35
diff 2x2w5changes.sok testfiles/2x2w5changes.sok
diff 2x2w5changes_solution.sok testfiles/2x2w5changes_solution.sok

# current bests: 14, 13, 22, 35

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
