import os
import sys
from ROOT import TCanvas
from ROOT import TF1
import math
import ROOT

c1 = ROOT.TCanvas('c1', 'c1', 1900, 1900)
c1.SetLogx()
c1.SetLogy()

m = 3096
GAMMA = 15
alpha = 1/137.
alphaD = 1

f = ROOT.TF1('f', '4*0.012*((3096*3096-x*x)*(3096*3096-x*x)+x*15*x*15)*1/137./(3096*3096*3096*3096)', 3000, 3500)

#f = 4*0.012*((3096*3096-3096*3096)*(3096*3096-3096*3096)+3096*15*3096*15)*1/137./(3096*3096*3096*3096)

print f

f.SetMinimum(0.000000001)

#f.GetTitle().SetTitel('')
f.GetXaxis().SetTitle('mAprime/MeV')
f.GetYaxis().SetTitle('epsilon^2')


f.Draw()

c1.Print('c1.eps')
