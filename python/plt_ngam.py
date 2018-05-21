#!/usr/bin/env python
"""
Generate plots
"""

__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-02-27 Tue 15:49]"

import ROOT
from ROOT import gStyle, TCanvas, TString, TChain, TStyle
from ROOT import TH1D, TFile, TLegend, THStack

mbc = TCanvas('mbc', '', 800, 600)
mbc.SetFillColor(0)
mbc.SetFrameFillColor(0)
gStyle.SetPadColor(0)
gStyle.SetCanvasColor(0)
gStyle.SetOptStat(0)
mbc.SetLeftMargin(0.15)
mbc.SetRightMargin(0.15)
mbc.SetTopMargin(0.1)
mbc.SetBottomMargin(0.15)
# mbc.SetLogy()
# mbc.SetLogx()


histo = 'h_ngam'
# xmin = 0.0
# xmax = 2.5

f0 = TFile('run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_93.root')
f1 = TFile('run/jpsi2invi/hist_mc12/jpsi2invi_psip_mc12_event_merged_93.root')
f2 = TFile('run/jpsi2invi/hist_data3650/jpsi2invi_data3650_event_merged_93.root')

h0_E = f0.Get(histo)
h1_E = f1.Get(histo)
h2_E = f2.Get(histo)

#h1_E.Scale(341.0/400.0)
a = (422149.0 - 6516.0 * 11.33)/530403.0
h1_E.Scale( a )
h2_E.Scale(11.33)
print 'h1_E.Scale = %.5f' % a

hs = THStack('hs', '')

#h0_E.GetYaxis().SetRangeUser(0, 600000)
#h0_E.GetYaxis().SetRangeUser(0, 1200000)

h1_E.SetFillColor(ROOT.kRed)
h2_E.SetFillColor(ROOT.kGreen)

hs.Add(h1_E)
hs.Add(h2_E)

hs.Draw()
h0_E.Draw("same, P")
h0_E.SetMarkerStyle(20)
h0_E.SetMarkerSize(0.55)

# h4_E.GetYaxis().SetTitle(ytitle)
h1_E.GetYaxis().SetTitleOffset(1.5)

legend = TLegend(0.55, 0.68, 0.77, 0.87)
# legend = TLegend(0.62, 0.68, 0.84, 0.87)
# legend = TLegend(0.18, 0.68, 0.48, 0.87)
legend.AddEntry(h0_E,'Data')
legend.AddEntry(h1_E,'Inclusive MC')
legend.AddEntry(h2_E,'Continuum')
#legend.SetNColums(1)
legend.SetBorderSize(0)
legend.SetFillColor(0)
legend.Draw()

h1_E.GetXaxis().SetTitle("N_{#gamma}")
mbc.SaveAs("python/plots/ngam_93.pdf")

