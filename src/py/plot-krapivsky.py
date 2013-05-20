#!/usr/bin/env python
# args
#  1: input node csv
#  2: output plot filename
#  3: p
#  4: lambda
#  5: mu

import sys
import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm
from itertools import groupby

tail_begins = 1    # where to begin plotting
minimum_count = 1  # minimum count of degrees considered

input_file_name = sys.argv[1]
plot_name = sys.argv[2]

p = float(sys.argv[3])
lamb = float(sys.argv[4])
mu = float(sys.argv[5])

out_degree = []
in_degree = []

for line in open(input_file_name, 'r'):
    this_out_degree, this_in_degree = line.strip().split(',')

    out_degree.append(int(this_out_degree))
    in_degree.append(int(this_in_degree))

out_degree.sort()
in_degree.sort()

x_out = np.array(list(set(out_degree))).astype(float)
x_out.sort()
y_out = np.array([len(list(group)) for key, group in groupby(out_degree)]).astype(float)

#print x_out
#print y_out

x_in = np.array(list(set(in_degree))).astype(float)
x_in.sort()
y_in = np.array([len(list(group)) for key, group in groupby(in_degree)]).astype(float)

#print x_in
#print y_in

plt.figure()
plt.title("Degree Distribution of the Krapivsky Model")
plt.xlabel("Log Degree")
plt.ylabel("Log CCDF")

fx_out = np.log10(x_out[np.logical_and(x_out >= tail_begins,y_out >= minimum_count)][:-1])
fy_out = np.log10((1. - (y_out.cumsum() / y_out.cumsum()[-1]))[np.logical_and(x_out >= tail_begins,y_out >= minimum_count)][:-1])

fx_in = np.log10(x_in[np.logical_and(x_in >= tail_begins,y_in >= minimum_count)][:-1])
fy_in = np.log10((1. - (y_in.cumsum() / y_in.cumsum()[-1]))[np.logical_and(x_in >= tail_begins,y_in >= minimum_count)][:-1])

plt.plot(fx_out, 
         fy_out, 
         'bx',
         fx_in, 
         fy_in, 
         'gx')

l_out = sm.OLS(fy_out, sm.add_constant(fx_out)).fit().params
l_in = sm.OLS(fy_in, sm.add_constant(fx_in)).fit().params

plt.plot(fx_out, l_out[0] * fx_out + l_out[1], '-', color='LightBlue')
plt.plot(fx_in, l_in[0] * fx_in + l_in[1], '-', color='LightGreen')

v_in = 2. + p * lamb
v_out = 1. + (1. / (1. - p)) + ((mu * p) / (1. - p))

plt.figtext(0.7, 0.5, 'vout: %.2f (%.2f)\nvin: %.2f (%.2f)\np: %.2f\nlambda: %.2f\nmu: %.2f' % (np.abs(l_out[0])+1., v_out, np.abs(l_in[0])+1., v_in, p, lamb, mu),bbox=dict(boxstyle='round', color='wheat', alpha=0.5))

#plt.suptitle('vout: %.2f (%.2f)\nvin: %.2f (%.2f)' % (np.abs(l_out[0])+1., v_out, np.abs(l_in[0])+1., v_in))

plt.legend(('Out-Degree','In-Degree', 'Out-Degree Fit', 'In-Degree Fit'), loc='best')
plt.savefig(plot_name)

#print (1. - (y_out.cumsum() / y_out.cumsum()[-1]))

