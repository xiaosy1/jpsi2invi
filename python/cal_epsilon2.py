import os
import sys
from ROOT import TCanvas
from ROOT import TF1
import math
import ROOT

c1 = ROOT.TCanvas('c1', 'c1', 10000, 10000)
c1.SetLogx()
c1.SetLogy()
c1.SetFillColor(0)

m = 3096
GAMMA = 15
alpha = 1/137.
alphaD = 1

# f1 = ROOT.TF1('f1', '4*0.012*((3096*3096-x*x)*(3096*3096-x*x)+x*15*x*15)*1/137./(3096*3096*3096*3096)', 0, 10000)
# f = 4*0.012*((3096*3096-3096*3096)*(3096*3096-3096*3096)+3096*15*3096*15)*1/137./(3096*3096*3096*3096)

f1 = ROOT.TF1('f1', '4*0.012*((3096*3096-x*x)**2-(x*15)**2)*1/137./(3096*3096)**2', 0, 10000)
f = 4*0.012*((3096*3096-3096*3096)**2+(3096*15)**2)*1/137./(3096*3096)**2

print f

f1.SetMinimum(0.000000001)

#f1.GetTitle().SetTitel('')
f1.GetXaxis().SetTitle('mAprime/MeV')
f1.GetYaxis().SetTitle('epsilon^2')


f1.Draw()

# c1.Print('c1.eps')
c1.Print('c2.eps')
