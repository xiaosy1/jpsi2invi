#!/usr/bin/env python
"""
Calculate trigger efficiency error
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-02-06 Tue 15:25]"

import math

#n1 = 4212.0
#n2 = 4237.0
#N = 5000.0

# n1 = 11911.0
# n2 = 11934.0

n1 = 16123.0
n2 = 16171.0

eff = n1 / n2
err = math.sqrt(eff*(1-eff)/n2)

print 'trig_eff = %.4f +- %f'  % (eff, err)
