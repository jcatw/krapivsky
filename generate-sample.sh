#!/bin/bash
# $1: tag
# $2: p
# $3: lambda
# $4: mu
# $5: target_n_nodes
# $6: n_samples

dir="results/$1_$2_$3_$4_$5"
if [ -d "${dir}" ]; then
    echo "${dir} already exists, please choose a different tag"
else
    mkdir ${dir}
    ./krapivsky $2 $3 $4 $5 $6 ${dir}/sample.csv ${dir}/all.csv ${dir}/nodes.csv ${dir}/edges.csv

    echo "./krapivsky $2 $3 $4 $5 $6 ${dir}/sample.csv ${dir}/all.csv ${dir}/nodes.csv ${dir}/edges.csv" > ${dir}/command.txt
fi
