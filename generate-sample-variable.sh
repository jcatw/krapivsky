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

    ./krapivsky --p $2 --lambda $3 --mu $4 --nsamples $6 --samplefile ${dir}/sample.csv --allfile ${dir}/all.csv --nodefile ${dir}/nodes.csv --edgefile ${dir}/edges.csv --variable-fitness $5

    echo "./krapivsky --p $2 --lambda $3 --mu $4 --nsamples $6 --samplefile ${dir}/sample.csv --allfile ${dir}/all.csv --nodefile ${dir}/nodes.csv --edgefile ${dir}/edges.csv $5" > ${dir}/command.txt
fi
