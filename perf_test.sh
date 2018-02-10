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
