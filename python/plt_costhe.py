#!/usr/bin/env python
"""
Generate costhe without eff
"""

__author__ = "Suyu XIAO <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) Suyu XIAO"
__created__ = "[2018-11-20 Tue 16:19]"

import sys
import ROOT
from ROOT import gStyle, TCanvas, TString, TChain, TStyle
from ROOT import TH1D, TFile, TLegend

c1 = TCanvas('c1', '', 800, 600)
c1.SetFillColor(0)
c1.SetFrameFillColor(0)
gStyle.SetPadColor(0)
gStyle.SetCanvasColor(0)
gStyle.SetOptStat(0)
c1.SetLeftMargin(0.15)
c1.SetRightMargin(0.15)
c1.SetTopMargin(0.1)
c1.SetBottomMargin(0.15)

logdir = sys.argv[1:]
print logdir
 
costhe_09 = TH1D('costhe_09', '', 100, -1.0, 1.0)
costhe_12 = TH1D('costhe_12', '', 100, -1.0, 1.0)

root_09 = TChain('tree')
root_12 = TChain('tree')

if logdir in [['mumu_pip'], ['mumu_pim']]:
    root_09.Add('run/gen_mc/jpsi2mumu_09/job_text/hist/gen_mc_mumu_09_truth_merged_1.root')
    root_12.Add('run/gen_mc/jpsi2mumu/job_text/hist/gen_mc_mumu_truth_merged_1.root')
elif logdir in [['ee_pip'], ['ee_pim']]:
    root_09.Add('run/gen_mc/jpsi2ee_09/job_text/hist/gen_mc_ee_09_truth_merged_1.root')
    root_12.Add('run/gen_mc/jpsi2ee/job_text/hist/gen_mc_ee_truth_merged_1.root')
elif logdir in [['nn_pip'], ['nn_pim']]:
    root_09.Add('run/gen_mc/jpsi2nn_09/job_text/hist/gen_mc_nn_09_truth_merged_1.root')
    root_12.Add('run/gen_mc/jpsi2nn/job_text/hist/gen_mc_nn_truth_merged_1.root')
elif logdir in [['pp_pip'], ['pp_pim']]:
    root_09.Add('run/gen_mc/jpsi2pp_09/job_text/hist/gen_mc_pp_09_truth_merged_1.root')
    root_12.Add('run/gen_mc/jpsi2pp/job_text/hist/gen_mc_pp_truth_merged_1.root')
else:
    print 'input error'

if logdir in [['mumu_pip'], ['ee_pip'], ['nn_pip'], ['pp_pip']]:
    root_09.Project('costhe_09', 'mc_costhe_pip')
    root_12.Project('costhe_12', 'mc_costhe_pip')
elif logdir in [['mumu_pim'], ['ee_pim'], ['nn_pim'], ['pp_pim']]:
    root_09.Project('costhe_09', 'mc_costhe_pim')
    root_12.Project('costhe_12', 'mc_costhe_pim')

costhe_09.SetLineColor(ROOT.kRed)
costhe_09.SetFillColor(ROOT.kRed)
costhe_09.SetFillStyle(3005)
costhe_09.SetLineWidth(2)
costhe_12.SetLineColor(ROOT.kBlue)
costhe_12.SetLineWidth(2)
# costhe_09.Scale()

costhe_09.Draw()
costhe_12.Draw('same')

if logdir in [['mumu_pip'], ['ee_pip'], ['nn_pip'], ['pp_pip']]:
    costhe_09.GetXaxis().SetTitle('costhe_pip')
elif logdir in [['mumu_pim'], ['ee_pim'], ['nn_pim'], ['pp_pim']]:
    costhe_09.GetXaxis().SetTitle('costhe_pim')

costhe_09.GetYaxis().SetTitle()
costhe_09.GetYaxis().SetTitleOffset(1.5)

if logdir in [['mumu_pip'], ['ee_pip'], ['mumu_pim'], ['ee_pim']]:
    costhe_09.GetYaxis().SetRangeUser(20000, 33000)
elif logdir in [['nn_pip'], ['pp_pip'], ['nn_pim'], ['pp_pim']]:
    costhe_09.GetYaxis().SetRangeUser(10000, 23000)

legend = TLegend(0.28, 0.28, 0.72, 0.48)

if logdir in [['mumu_pip'], ['mumu_pim']]:
    legend.AddEntry('costhe_09', "2009 J/psi->mumu MC sample")
    legend.AddEntry('costhe_12', "2012 J/psi->mumu MC sample")
elif logdir in [['ee_pip'], ['ee_pim']]:
    legend.AddEntry('costhe_09', "2009 J/psi->ee MC sample")
    legend.AddEntry('costhe_12', "2012 J/psi->ee MC sample")
elif logdir in [['nn_pip'], ['nn_pim']]:
    legend.AddEntry('costhe_09', "2009 J/psi->nn MC sample")
    legend.AddEntry('costhe_12', "2012 J/psi->nn MC sample")
elif logdir in [['pp_pip'], ['pp_pim']]:
    legend.AddEntry('costhe_09', "2009 J/psi->pp MC sample")
    legend.AddEntry('costhe_12', "2012 J/psi->pp MC sample")

legend.SetBorderSize(0)
legend.SetFillColor(0)
legend.Draw()

figfile = 'python/plots/%s.pdf' %'_'.join(logdir)

c1.SaveAs(figfile)
