#!/usr/bin/env python
import sys
import numpy as np
import matplotlib.pyplot as plt
from itertools import groupby

tail_begins = 1    # where to begin plotting
minimum_count = 3  # minimum count of degrees considered; prevents log instability

input_file_name = sys.argv[1]
plot_name = sys.argv[2]

out_degree = []
in_degree = []

for line in open(input_file_name, 'r'):
    this_out_degree, this_in_degree = line.strip().split(',')

    out_degree.append(int(this_out_degree))
    in_degree.append(int(this_in_degree))

out_degree.sort()
in_degree.sort()

x_out = np.array(list(set(out_degree))).astype(float)
y_out = np.array([len(list(group)) for key, group in groupby(out_degree)]).astype(float)

#print x_out
#print y_out

x_in = np.array(list(set(in_degree))).astype(float)
y_in = np.array([len(list(group)) for key, group in groupby(in_degree)]).astype(float)

#print x_in
#print y_in

plt.figure()
plt.title("Degree Distribution of the Krapivsky Model")
plt.xlabel("Log Degree")
plt.ylabel("Log CCDF")

plt.plot(np.log10(x_out[np.logical_and(x_out >= tail_begins,y_out >= minimum_count)][:-1]), 
         np.log10((1. - (y_out.cumsum() / y_out.cumsum()[-1]))[np.logical_and(x_out >= tail_begins,y_out >= minimum_count)][:-1]), 
         'bx',
         np.log10(x_in[np.logical_and(x_in >= tail_begins,y_in >= minimum_count)][:-1]), 
         np.log10((1. - (y_in.cumsum() / y_in.cumsum()[-1]))[np.logical_and(x_in >= tail_begins,y_in >= minimum_count)][:-1]), 
         'gx')

plt.legend(('Out-Degree','In-Degree'))
plt.savefig(plot_name)

#print (1. - (y_out.cumsum() / y_out.cumsum()[-1]))

