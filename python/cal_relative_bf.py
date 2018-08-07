#!/usr/bin/env python
"""
Calculate relative branching fraction of jpsi->invi over jpsi->mumu
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-04-13 Fri 11:14]"

import math

def error_mul(A, a, B, b):
    D = A * B
    d = D * math.sqrt( (a/A)**2 + (b/B)**2 )
    return D, d

def error_div(A, a, B, b):
    D = A / B
    d = D * math.sqrt( (a/A)**2 + (b/B)**2 )
    return D, d

def error_sub(A, a, B, b):
	D = A - B
	d = math.sqrt(a**2 + b**2)
	return D, d

# for data 2009
# inv_down, e_inv_down = error_mul(40.48, 0.07, 0.994, 0.001)
# inv, e_inv = error_div(-670, 2979, inv_down, e_inv_down)
# print "invi = %.2f +- %.2f" %(inv, e_inv)
# mumu, e_mumu = error_div(713652, 3497, 32.36, 0.03)
# print "mumu = %.2f +- %.2f" %(mumu, e_mumu)

# for data 2012
inv_down, e_inv_down = error_mul(39.25, 0.07, 0.998, 0.0004)
c = 443620.0+13779.0*0.998
f = 396471.0*0.0047
aaa, bbb = error_sub(396471.0, f, c, 9725.0)
print "N_invi = %.2f +- %.2f" %(aaa, bbb)
inv, e_inv = error_div(aaa, bbb, inv_down, e_inv_down)
print "invi = %.2f +- %.2f" %(inv, e_inv)
g = 2224671.0*0.0049
print "N_mumu = %.2f +- %.2f" %(2224671.0, g)
mumu, e_mumu = error_div(2224671.0, g, 31.44, 0.03) 
print "mumu = %.2f +- %.2f" %(mumu, e_mumu)

E, e = error_div(inv, e_inv, mumu, e_mumu)
invi_1 = aaa/0.998/39.25
invi_2 = 683.0/0.998/39.25
mumu_1 = 2224671.0/31.44
mumu_2 = 1275.0/31.44
stat, stat_err = error_div(invi_1, invi_2, mumu_1, mumu_2)

print "B/B = (%f +- %f +- %f)*10^-4" %(E*10000, stat_err*10000,  e*10000)
print "%f =? %f" %(E*10000, stat*10000)



