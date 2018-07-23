#!/usr/bin/env python
"""
Combine the results for 2009 & 2012
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-07-18 Wed 10:17]"

import os
import sys
import math

A1 = -7.55
B1 = 33.7

A2 = -219.72
B2 = 34.44

def com(A1, B1, A2, B2):
	A = ( A1 / B1**2 + A2 / B2**2 ) / ( 1 / B1**2 + 1 / B2**2 )
	B = 1 / math.sqrt( 1 / B1**2 + 1 / B2**2 )
	return A, B

A, B = com(A1, B1, A2, B2)
print "A +- B = %.4f +- %.4f" %(A, B)


