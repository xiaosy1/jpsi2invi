import os
import sys
import ROOT
import math


x0 = -7.55/10000.0
sigma = 33.6/10000.0

#x0 = -2.66/1000.0
#sigma = 3/1000.0

mu_t=[0]*30000
Prob=[0]*30000

h_gaus = ROOT.TH1F('hgaus', 'hgaus', 23000, -0.006, 0.017)

sum = 0.0
for i in range(0, 23000):
	mu_t[i] = (-6.0+i*0.001)/1000.0
	c1 = 1/math.sqrt(2*3.141592653858*sigma*sigma)
	Prob[i] = c1*math.exp(-(x0-mu_t[i])*(x0-mu_t[i])/2/sigma/sigma)
	h_gaus.SetBinContent(i+1, Prob[i])
	
	if (mu_t[i]>0.0) :
		sum = sum + Prob[i]

ROOT.gStyle.SetCanvasColor(0)
c = ROOT.TCanvas("c","",800,600)
c.cd()
h_gaus.Draw()

c.SetTicks(1,1)

ratio = 0.90
tmp_sum = 0.0
hmax = 0.0

for j in range(0, 23000):
	if Prob[j] > hmax:
		hmax = Prob[j]
			
	if mu_t[j]>=0.0 :
		tmp_sum += Prob[j]

	if tmp_sum >= sum*ratio:
		j_CL=j
		CL_mu = mu_t[j]
		break



print '90% CL limit ='
print CL_mu

t1 = ROOT.TLine(CL_mu, 0, CL_mu, hmax*1.05)
t1.Draw()

ROOT.gPad.SetLeftMargin(0.12)
ROOT.gPad.SetBottomMargin(0.17)
ROOT.gPad.GetFrame().SetBorderMode(0)

h_gaus_shaded = ROOT.TH1F('hgaus_shaded', 'hgaus_shaded', 23000, -0.006, 0.017)
for i in range(0, 23000):
	if mu_t[i]>=0.0 and CL_mu>mu_t[i]:
		h_gaus_shaded.SetBinContent(i+1, Prob[i])
	else:
		h_gaus_shaded.SetBinContent(i+1, 0.0)
h_gaus_shaded.Draw('same')
h_gaus_shaded.SetFillColor(4)
h_gaus.Draw('same')
h_gaus.SetLineColor(1)
h_gaus.SetLineWidth(2)
h_gaus_shaded.SetLineColor(1)

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

h_gaus.SetName("")
h_gaus.SetTitle("")
h_gaus.GetXaxis().SetTitleFont(22)
h_gaus.GetYaxis().SetTitleFont(22)
h_gaus.GetXaxis().SetTitleOffset(1.2)
h_gaus.GetYaxis().SetTitleOffset(0.9)
h_gaus.GetXaxis().SetTitleSize(0.06)
h_gaus.GetYaxis().SetTitleSize(0.06)
h_gaus.GetXaxis().SetLabelSize(0.05)
h_gaus.GetYaxis().SetLabelSize(0.05)
h_gaus.GetXaxis().SetTitle("Br(J/#psi#rightarrow invisible)/Br(J/#psi#rightarrow#mu^{+}#mu^{-    })")
h_gaus.GetYaxis().SetTitle("Likelihood(in arbitrary unit)")
h_gaus.GetXaxis().CenterTitle()
h_gaus.GetYaxis().CenterTitle()
h_gaus.GetYaxis().SetNdivisions(505)
h_gaus.GetYaxis().SetNdivisions(505)

c.Print("c.eps")
