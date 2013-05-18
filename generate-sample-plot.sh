#!/bin/bash

dir="results/$1_$2_$3_$4_$5"
mkdir ${dir}
./krapivsky $2 $3 $4 $5 $6 ${dir}/sample.csv ${dir}/all.csv
./plot-krapivsky.py ${dir}/all.csv ${dir}/log-ccdf_$1_$2_$3_$4_$5.png $2 $3 $4

echo "./krapivsky $2 $3 $4 $5 $6 ${dir}/sample.csv ${dir}/all.csv" > ${dir}/command.txt
