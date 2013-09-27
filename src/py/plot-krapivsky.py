#!/usr/bin/env python
# args
#  1: input node csv
#  2: input edge csv
#  3: output plot filename
#  4: p
#  5: lambda
#  6: mu

import sys
import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm
import os.path
from itertools import groupby

### part 1: indegree, outdegree only

tail_begins = 1    # where to begin plotting
minimum_count = 1  # minimum count of degrees considered

input_file_name = sys.argv[1]
input_edge_file_name = sys.argv[2]
plot_name = sys.argv[3]

p = float(sys.argv[4])
lamb = float(sys.argv[5])
mu = float(sys.argv[6])

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

def plottable_ccdf(x,y):
    fx = np.log10(x[np.logical_and(x >= tail_begins,y >= minimum_count)][:-1])
    fy = np.log10((1. - (y.cumsum() / y.cumsum()[-1]))[np.logical_and(x >= tail_begins,y >= minimum_count)][:-1])

    return fx, fy

plt.figure()
plt.title("Degree Distribution of the Krapivsky Model")
plt.xlabel("Log Degree")
plt.ylabel("Log CCDF")

#fx_out = np.log10(x_out[np.logical_and(x_out >= tail_begins,y_out >= minimum_count)][:-1])
#fy_out = np.log10((1. - (y_out.cumsum() / y_out.cumsum()[-1]))[np.logical_and(x_out >= tail_begins,y_out >= minimum_count)][:-1])
#
#fx_in = np.log10(x_in[np.logical_and(x_in >= tail_begins,y_in >= minimum_count)][:-1])
#fy_in = np.log10((1. - (y_in.cumsum() / y_in.cumsum()[-1]))[np.logical_and(x_in >= tail_begins,y_in >= minimum_count)][:-1])

fx_out, fy_out = plottable_ccdf(x_out, y_out)
fx_in, fy_in = plottable_ccdf(x_in, y_in)

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

#####print (1. - (y_out.cumsum() / y_out.cumsum()[-1]))
####
####### part 2: with reciprocation
####
####edgelist = []
####
####edgefile = open(input_edge_file_name,"r")
####
####for line in edgefile:
####    edgestrings = line.strip().split(",")
####    edgelist.append( (int(edgestrings[0]), int(edgestrings[1])) )
####
#####print edgelist[0]
####    
####edgeset = set(edgelist)
####
####reciprocated_edges   = []
####unreciprocated_edges = []
####
####for efrom, eto in edgelist:
####    if (eto, efrom) in edgeset:
####        reciprocated_edges.append((eto,efrom))
####    else:
####        unreciprocated_edges.append((eto,efrom))
####
####def edgelist_to_degreedist(edgelist):
####    #print edgelist[0]
####    indeg = {}
####    outdeg = {}
####    
####    for (efrom,eto) in edgelist:
####        indeg[eto] = indeg.get(eto,0) + 1
####        outdeg[efrom] = outdeg.get(efrom,0) + 1
####    
####    indist = {}
####    outdist = {}
####    
####    for efrom in outdeg.keys():
####        outdist[outdeg[efrom]] = outdist.get(efrom,0) + 1
####    for eto in indeg.keys():
####        indist[indeg[eto]] = indist.get(eto,0) + 1
####
####    return outdist, indist
####
####reciprocated_outdist, reciprocated_indist = edgelist_to_degreedist(reciprocated_edges)
####unreciprocated_outdist, unreciprocated_indist = edgelist_to_degreedist(unreciprocated_edges)
####
####def degree_dict_to_arrays(degree_dict):
####    x = degree_dict.keys()
####    x.sort()
####
####    y = []
####    for an_x in x:
####        y.append(degree_dict[an_x])
####
####    x = np.array(x).astype(float)
####        
####    y = np.array(y).astype(float)
####    
####
####    return x,y
####
####recip_x_in, recip_y_in = degree_dict_to_arrays(reciprocated_indist)
####recip_x_in, recip_y_in = plottable_ccdf(recip_x_in, recip_y_in)
####recip_x_out, recip_y_out = degree_dict_to_arrays(reciprocated_outdist)
####recip_x_out, recip_y_out = plottable_ccdf(recip_x_out, recip_y_out)
####
####unrecip_x_in,  unrecip_y_in =  degree_dict_to_arrays(unreciprocated_indist)
####unrecip_x_in,  unrecip_y_in = plottable_ccdf(unrecip_x_in,  unrecip_y_in)
####unrecip_x_out, unrecip_y_out = degree_dict_to_arrays(unreciprocated_outdist)
####unrecip_x_out, unrecip_y_out = plottable_ccdf(unrecip_x_out, unrecip_y_out)
####
####### plot recip, unrecip without all
####plt.figure()
####plt.title("Reciprocated and Unreciprocated Degree Distributions of the Krapivsky Model")
####plt.xlabel("Log Degree")
####plt.ylabel("Log CCDF")
####
####plt.plot(recip_x_out,
####         recip_y_out,
####         'cx',
####         recip_x_in,
####         recip_y_in,
####         'rx',
####         unrecip_x_out,
####         unrecip_y_out,
####         'kx',
####         unrecip_x_in,
####         unrecip_y_in,
####         'mx')
####         
####
####plt.legend(('Reciprocated Out-Degree',
####            'Reciprocated In-Degree', 
####            'Unreciprocated Out-Degree',
####            'Unreciprocated In-Degree'), 
####            loc='best')
####
####
####splitname = os.path.splitext(plot_name)
####plotname_reciprocal = splitname[0] + '_recip' + splitname[1]
####plotname_all = splitname[0] + '_all' + splitname[1]
####
####plt.savefig(plotname_reciprocal)
####
####### plot everything
####plt.figure()
####plt.title("Degree Distributions of the Krapivsky Model")
####plt.xlabel("Log Degree")
####plt.ylabel("Log CCDF")
####
####plt.plot(fx_out, 
####         fy_out, 
####         'bx',
####         fx_in, 
####         fy_in, 
####         'gx',
####         recip_x_out,
####         recip_y_out,
####         'cx',
####         recip_x_in,
####         recip_y_in,
####         'rx',
####         unrecip_x_out,
####         unrecip_y_out,
####         'kx',
####         unrecip_x_in,
####         unrecip_y_in,
####         'mx')
####         
####plt.figtext(0.7, 0.5, 'vout: %.2f (%.2f)\nvin: %.2f (%.2f)\np: %.2f\nlambda: %.2f\nmu: %.2f' % (np.abs(l_out[0])+1., v_out, np.abs(l_in[0])+1., v_in, p, lamb, mu),bbox=dict(boxstyle='round', color='wheat', alpha=0.5))
####
####plt.plot(fx_out, l_out[0] * fx_out + l_out[1], '-', color='LightBlue')
####plt.plot(fx_in, l_in[0] * fx_in + l_in[1], '-', color='LightGreen')
####
####
####plt.legend(('Out-Degree',
####            'In-Degree',
####            'Reciprocated Out-Degree',
####            'Reciprocated In-Degree', 
####            'Unreciprocated Out-Degree',
####            'Unreciprocated In-Degree',
####            'Out-Degree Fit', 
####            'In-Degree Fit'), 
####            loc='best')
####
####plt.savefig(plotname_all)
