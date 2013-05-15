#!/usr/bin/env python
import sys
import numpy as np
import matplotlib.pyplot as plt

input_file_name = sys.argv[1]
plot_name = sys.argv[2]

out_degree = []
in_degree = []

for line in open(input_file_name, 'r'):
    this_out_degree, this_in_degree = line.strip().split(',')

    out_degree.append(float(this_out_degree))
    in_degree.append(float(this_in_degree))

out_degree.sort()
in_degree.sort()

out_degree = np.array(out_degree) + 1
in_degree = np.array(in_degree) + 1

plt.figure()
plt.title("Degree Distribution of the Krapivsky Model")
plt.xlabel("Log Degree")
plt.ylabel("Log CCDF")
plt.plot(np.log(out_degree), np.log(1. - (out_degree.cumsum() / out_degree.sum())), 'bx',
         np.log(in_degree), np.log(1. - (in_degree.cumsum() / in_degree.sum())), 'gx')
plt.legend(('Out-Degree','In-Degree'))
plt.savefig(plot_name)
