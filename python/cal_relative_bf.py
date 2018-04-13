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

# for data 2009
# inv_down, e_inv_down = error_mul(40.48, 0.07, 0.994, 0.001)
# inv, e_inv = error_div(-670, 2979, inv_down, e_inv_down)
# mumu, e_mumu = error_div(713652, 3497, 32.36, 0.03)

# for data 2012
inv_down, e_inv_down = error_mul(39.25, 0.07, 0.994, 0.001)
inv, e_inv = error_div(-58270, 9295, inv_down, e_inv_down)
mumu, e_mumu = error_div(2224671, 10491, 31.44, 0.03) # 10491 is the assumed error for mumu

E, e = error_div(inv, e_inv, mumu, e_mumu)
print "E = %f*10^-4, e = %f*10^-4" %(E*10000, e*10000)