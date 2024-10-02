#!/bin/bash

start=$(date +%s)

make REBUILD_STAGE_1 CORE_FAMILY=$1 && make REBUILD_STAGE_2 CORE_FAMILY=$1 -k -j $(getconf _NPROCESSORS_ONLN) && make REBUILD_STAGE_3 CORE_FAMILY=$1

end=$(date +%s)
execution_time=$((end - start))

echo "Total execution time: $execution_time seconds"
