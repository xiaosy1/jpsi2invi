#!/usr/bin/env python
"""
Calculate table 5
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-02-01 Thu 17:21]"

import math

n_anything = 57795500.0
n_anything_err = 8874
n_anything_09 = 18658100

n_invisible = 397611
n_invisible_err = 684

n_other = 16163
n_other_09 = 3877

b_mumu = 5.961
b_ee = 5.971
b_nn = 0.209
b_pp = 0.202
b_mumu_err = 0.033
b_ee_err = 0.032
b_nn_err = 0.016
b_pp_err = 0.0029

eff_mumu = 6.24
eff_ee = 6.32
eff_nn = 6.13
eff_pp = 2.64
eff_2b_err = 0.02

eff_trigger = 99.4
eff_trigger_err = 0.1

n_mumu_09 = 65558
n_ee_09 = 65668
n_nn_09 = 2361
n_pp_09 = 999
n_mumu = n_anything * b_mumu * eff_mumu * eff_trigger / 1000000
n_ee = n_anything * b_ee * eff_ee * eff_trigger / 1000000
n_nn = n_anything * b_nn * eff_nn * eff_trigger / 1000000
n_pp = n_anything * b_pp * eff_pp * eff_trigger / 1000000

print "\nn_anything = %d +- %d" % (n_anything, n_anything_err), "\tratio_12/09 = %.3f" % (n_anything / n_anything_09)
print "n_invisible = %d +- %d" % (n_invisible, n_invisible_err)

print "\nItems",      "\t\tBF(%)", "\t\teff_2B(%)", "\teff_trig(%)", "\tNumber", "\t\tNumber_09", "\tratio_12/09"
print "jpsi->mumu", "\t%.3f+-%.3f"%(b_mumu, b_mumu_err), "\t%.2f+-%.2f"%(eff_mumu, eff_2b_err), "\t%.1f+-%.1f"%(eff_trigger, eff_trigger_err), "\t%.2f"%n_mumu, "\t%d"%n_mumu_09, "\t\t%.3f"%(n_mumu/n_mumu_09)
print "jpsi->ee", "\t%.3f+-%.3f"%(b_ee, b_ee_err), "\t%.2f+-%.2f"%(eff_ee, eff_2b_err), "\t%.1f+-%.1f"%(eff_trigger, eff_trigger_err), "\t%.2f"%n_ee, "\t%d"%n_ee_09, "\t\t%.3f"%(n_ee/n_ee_09)
print "jpsi->nn", "\t%.3f+-%.3f"%(b_nn, b_nn_err), "\t%.2f+-%.2f"%(eff_nn, eff_2b_err), "\t%.1f+-%.1f"%(eff_trigger, eff_trigger_err), "\t%.2f"%n_nn, "\t%d"%n_nn_09, "\t\t%.3f"%(n_nn/n_nn_09)
print "jpsi->pp", "\t%.3f+-%.3f"%(b_pp, b_pp_err), "\t%.2f+-%.2f"%(eff_pp, eff_2b_err), "\t%.1f+-%.1f"%(eff_trigger, eff_trigger_err), "\t%.2f"%n_pp, "\t%d"%n_pp_09, "\t\t%.3f"%(n_pp/n_pp_09)

print "\nn_total_2B = %.2f" % (n_mumu + n_ee + n_nn + n_pp)
print "n_total_peaking = %.2f" % (n_mumu + n_ee + n_nn + n_pp + n_other)

a = 3.0
b = 5
print "test = %f" % math.sqrt(b/a)

print "\n"
