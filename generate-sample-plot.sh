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

    echo "Generating network..."
    ./krapivsky $2 $3 $4 $5 $6 ${dir}/sample.csv ${dir}/all.csv ${dir}/nodes.csv ${dir}/edges.csv

    echo "Plotting degree distribution..."
    ./src/py/plot-krapivsky.py ${dir}/all.csv ${dir}/log-ccdf_$1_$2_$3_$4_$5.png $2 $3 $4
    
    echo "./krapivsky $2 $3 $4 $5 $6 ${dir}/sample.csv ${dir}/all.csv ${dir}/nodes.csv ${dir}/edges.csv" > ${dir}/command.txt

    echo "Done."
fi
