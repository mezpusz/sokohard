#!/bin/bash

set -euo "pipefail"

readonly SEED="1517341640"

MAX_SIZE=3
MAX_BOXES=8

for i in $(seq 2 $MAX_SIZE);
do
    for j in $(seq 2 $MAX_SIZE);
    do
        for k in $(seq 1 $MAX_BOXES);
        do
            time out/sokohard -w $i -h $j -b $k -s ${SEED}
        done
    done
done

#mhajdu-mbp:sokohard mhajdu$ ./perf_test.sh 
#Size: 6x6, boxes: 1, seed: 1517341640
#Difficulty: 6
#
#real	0m0.022s
#user	0m0.011s
#Size: 6x6, boxes: 2, seed: 1517341640
#Difficulty: 10
#
#real	0m0.110s
#user	0m0.092s
#Size: 6x6, boxes: 3, seed: 1517341640
#Difficulty: 14
#
#real	0m0.503s
#user	0m0.477s
#Size: 6x6, boxes: 4, seed: 1517341640
#Difficulty: 20
#
#real	0m0.704s
#user	0m0.680s
#Size: 6x6, boxes: 5, seed: 1517341640
#Difficulty: 22
#
#real	0m3.458s
#user	0m3.378s
#Size: 6x6, boxes: 6, seed: 1517341640
#Difficulty: 16
#
#real	0m1.944s
#user	0m1.826s
#Size: 6x6, boxes: 7, seed: 1517341640
#Difficulty: 14
#
#real	0m0.474s
#user	0m0.426s
#Size: 6x6, boxes: 8, seed: 1517341640
#Difficulty: 21
#
#real	0m3.948s
#user	0m3.775s
#Size: 6x9, boxes: 1, seed: 1517341640
#Difficulty: 7
#
#real	0m0.027s
#user	0m0.018s
#Size: 6x9, boxes: 2, seed: 1517341640
#Difficulty: 14
#
#real	0m0.222s
#user	0m0.202s
#Size: 6x9, boxes: 3, seed: 1517341640
#Difficulty: 20
#
#real	0m2.343s
#user	0m2.295s
#Size: 6x9, boxes: 4, seed: 1517341640
#Difficulty: 20
#
#real	0m13.428s
#user	0m13.194s
#Size: 6x9, boxes: 5, seed: 1517341640
#Difficulty: 35
#
#real	0m32.789s
#user	0m32.076s
#Size: 6x9, boxes: 6, seed: 1517341640
#Difficulty: 30
#
#real	3m23.519s
#user	3m18.838s
#Size: 6x9, boxes: 7, seed: 1517341640
#Difficulty: 28
#
#real	0m44.131s
#user	0m42.535s
#Size: 6x9, boxes: 8, seed: 1517341640
#Difficulty: 33
#
#real	51m6.301s
#user	23m19.752s
#Size: 9x6, boxes: 1, seed: 1517341640
#Difficulty: 7
#
#real	0m0.058s
#user	0m0.019s
#Size: 9x6, boxes: 2, seed: 1517341640
#Difficulty: 12
#
#real	0m0.343s
#user	0m0.324s
#Size: 9x6, boxes: 3, seed: 1517341640
#Difficulty: 16
#
#real	0m2.316s
#user	0m2.273s
#Size: 9x6, boxes: 4, seed: 1517341640
#Difficulty: 23
#
#real	0m24.272s
#user	0m23.659s
#Size: 9x6, boxes: 5, seed: 1517341640
#Difficulty: 27
#
#real	1m2.009s
#user	1m0.394s
#Size: 9x6, boxes: 6, seed: 1517341640
#Difficulty: 27
#
#real	3m14.173s
#user	3m5.706s
#Size: 9x6, boxes: 7, seed: 1517341640
#Difficulty: 32
#
#real	4m57.400s
#user	4m51.505s
#Size: 9x6, boxes: 8, seed: 1517341640
#Difficulty: 33
#
#real	14m6.468s
#user	4m37.978s
#Size: 9x9, boxes: 1, seed: 1517341640
#Difficulty: 8
#
#real	0m0.075s
#user	0m0.047s
#Size: 9x9, boxes: 2, seed: 1517341640
#Difficulty: 16
#
#real	0m0.984s
#user	0m0.956s
#Size: 9x9, boxes: 3, seed: 1517341640
#Difficulty: 21
#
#real	0m18.706s
#user	0m18.483s
#Size: 9x9, boxes: 4, seed: 1517341640
#Difficulty: 27
#
#real	2m31.335s
#user	2m28.637s
#Size: 9x9, boxes: 5, seed: 1517341640
#Difficulty: 34
#
#real	50m3.006s
#user	20m7.152s
#sys	0m16.104s
