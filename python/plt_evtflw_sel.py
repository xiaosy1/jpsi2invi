#!/usr/bin/env python
"""
Generate plots
"""
 
__author__ = "XIAO Suyu <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) XIAO Suyu"
__created__ = "[2018-11-09 Fri 16:01]"

import sys 
import ROOT
from ROOT import gStyle, TCanvas, TString, TChain, TStyle
from ROOT import TH1D, TFile, TLegend

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
# mbc.SetLogx()

logdir = sys.argv[1:]
print logdir

if logdir in [['nunu_pim_costhe'], ['ee_pim_costhe'], ['mumu_pim_costhe'], ['nn_pim_costhe'], ['pp_pim_costhe']]:
    histo = 'h_pim_costhe'
elif logdir in [['nunu_pip_costhe'], ['ee_pip_costhe'], ['mumu_pip_costhe'], ['nn_pip_costhe'], ['pp_pip_costhe']]:
    histo = 'h_pip_costhe'
elif logdir in [['any_pre']]:
    histo = 'hcutflw'
# elif logdir in [['ee_mc_costhe_pip'], ['mumu_mc_costhe_pip'], ['nn_mc_costhe_pip'], ['pp_mc_costhe_pip']]:
#     histo = 'h_mc_costhe_pip'
# elif logdir in [['ee_mc_costhe_pim'], ['mumu_mc_costhe_pim'], ['nn_mc_costhe_pim'], ['pp_mc_costhe_pim']]:
#     histo = 'h_mc_costhe_pim'
else:
    histo = 'hevtflw'

if 'any_pre' in logdir:
    f0 = TFile("run/gen_mc/jpsi2any_09/job_text/hist/jpsi2incl_gen_mc_any_09_event_merged_evtflw.root")
    f1 = TFile("run/gen_mc/jpsi2any/job_text/hist/jpsi2incl_gen_mc_any_event_merged_evtflw.root")

if 'any_sel' in logdir:
    f0 = TFile("run/gen_mc/jpsi2any_09/job_text/hist/jpsi2incl_gen_mc_any_09_event_merged_fit.root")
    f1 = TFile("run/gen_mc/jpsi2any/job_text/hist/jpsi2incl_gen_mc_any_event_merged_fit.root")

if 'pp_01' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_01.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_01.root")

elif 'nn_01' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_01.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_01.root")

elif 'ee_01' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_01.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_01.root")

elif 'mumu_01' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_01.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_01.root")

elif 'pp_02' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_02.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_02.root")

elif 'nn_02' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_02.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_02.root")

elif 'ee_02' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_02.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_02.root")

elif 'mumu_02' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_02.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_02.root")

elif 'pp_03' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_03.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_03.root")

elif 'nn_03' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_03.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_03.root")

elif 'ee_03' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_03.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_03.root")

elif 'mumu_03' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_03.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_03.root")

elif 'pp_04' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_04.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_04.root")

elif 'nn_04' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_04.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_04.root")

elif 'ee_04' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_04.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_04.root")

elif 'mumu_04' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_04.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_04.root")

elif 'pp_05' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_05.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_05.root")

elif 'nn_05' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_05.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_05.root")

elif 'ee_05' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_05.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_05.root")

elif 'mumu_05' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_05.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_05.root")

elif 'pp_06' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_06.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_06.root")

elif 'nn_06' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_06.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_06.root")

elif 'ee_06' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_06.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_06.root")

elif 'mumu_06' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_06.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_06.root")

elif 'pp_07' in logdir:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_07.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_07.root")

elif 'nn_07' in logdir:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_07.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_07.root")

elif 'ee_07' in logdir:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_07.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_07.root")

elif 'mumu_07' in logdir:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_07.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_07.root")

elif logdir in [['pp'], ['pp_pim_costhe'], ['pp_pip_costhe'], ['pp_mc_costhe_pip'], ['pp_mc_costhe_pim']]:
    f0 = TFile("run/gen_mc/jpsi2pp_09/job_text/hist/jpsi2invi_gen_mc_pp_09_event_merged_08.root")
    f1 = TFile("run/gen_mc/jpsi2pp/job_text/hist/jpsi2invi_gen_mc_pp_event_merged_08.root")

elif logdir in [['nn'], ['nn_pim_costhe'], ['nn_pip_costhe'], ['nn_mc_costhe_pip'], ['nn_mc_costhe_pim']]:
    f0 = TFile("run/gen_mc/jpsi2nn_09/job_text/hist/jpsi2invi_gen_mc_nn_09_event_merged_08.root")
    f1 = TFile("run/gen_mc/jpsi2nn/job_text/hist/jpsi2invi_gen_mc_nn_event_merged_08.root")

elif logdir in [['ee'], ['ee_pim_costhe'], ['ee_pip_costhe'], ['ee_mc_costhe_pip'], ['ee_mc_costhe_pim']]:
    f0 = TFile("run/gen_mc/jpsi2ee_09/job_text/hist/jpsi2invi_gen_mc_ee_09_event_merged_08.root")
    f1 = TFile("run/gen_mc/jpsi2ee/job_text/hist/jpsi2invi_gen_mc_ee_event_merged_08.root")

elif logdir in [['mumu'], ['mumu_pim_costhe'], ['mumu_pip_costhe'], ['mumu_mc_costhe_pip'], ['mumu_mc_costhe_pim']]:
    f0 = TFile("run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_08.root")
    f1 = TFile("run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_08.root")

elif 'mumu_pre' in logdir:
    f0 = TFile('run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2invi_gen_mc_mumu_09_event_merged_evtflw.root')
    f1 = TFile('run/gen_mc/jpsi2mumu/job_text/hist/jpsi2invi_gen_mc_mumu_event_merged_evtflw.root')

elif logdir in [['nunu_pre']]:
    f0 = TFile("run/gen_mc/jpsi2nunu_09/job_text/hist/evtflw/jpsi2invi_gen_mc_nunu_09_event_merged_ncharged.root")
    f1 = TFile("run/gen_mc/jpsi2nunu/job_text/evtflw_nunu/jpsi2invi_gen_mc_nunu_event-ncharged.root")
 
elif logdir in [['nunu_pre_fit']]:
    f0 = TFile('run/gen_mc/jpsi2nunu_09/job_text/hist/evtflw/jpsi2invi_gen_mc_nunu_09_event_merged_fit.root')
    f1 = TFile('run/gen_mc/jpsi2nunu/job_text/evtflw_nunu/jpsi2invi_gen_mc_nunu_event-fit.root')

elif logdir in [['nunu_sel_fit']]:
    f0 = TFile('run/gen_mc/jpsi2nunu_09/job_text/hist/jpsi2invi_gen_mc_nunu_09_event_merged_fit.root')
    f1 = TFile('run/gen_mc/jpsi2nunu/job_text/event_nunu/hist/jpsi2invi_gen_mc_nunu_event-fit.root')

elif logdir in [['nunu_sel'], ['nunu_pim_costhe'], ['nunu_pip_costhe']]:
    f0 = TFile("run/gen_mc/jpsi2nunu_09/job_text/hist/jpsi2invi_gen_mc_nunu_09_event_merged_ncharged.root")
    f1 = TFile("run/gen_mc/jpsi2nunu/job_text/event_nunu/hist/jpsi2invi_gen_mc_nunu_event-ncharged.root")

elif 'data_pre' in logdir:
    mbc.SetLogy()
    f0 = TFile("run/jpsi2invi/hist_data09/jpsi2invi_data_psip_data09_event_merged_evtflw.root")
    f1 = TFile("run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_evtflw.root")

elif 'data_sel' in logdir:
    mbc.SetLogy()
    f0 = TFile("run/jpsi2invi/hist_data09/jpsi2invi_data_psip_data09_event_merged_ncharged.root")
    f1 = TFile("run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_ncharged.root")

elif 'mc_pre' in logdir:
    mbc.SetLogy() 
    f0 = TFile("run/jpsi2invi/hist_mc09/jpsi2invi_psip_mc09_event_merged_evtflw.root")
    f1 = TFile("run/jpsi2invi/hist_mc12/jpsi2invi_psip_mc12_event_merged_evtflw.root")

elif 'mc_sel' in logdir:
    mbc.SetLogy() 
    f0 = TFile("run/jpsi2invi/hist_mc09/jpsi2invi_psip_mc09_event_merged_ncharged.root")
    f1 = TFile("run/jpsi2invi/hist_mc12/jpsi2invi_psip_mc12_event_merged_ncharged.root")

elif '09_pre' in logdir:
    mbc.SetLogy() 
    f0 = TFile("run/jpsi2invi/hist_mc09/jpsi2invi_psip_mc09_event_merged_evtflw.root")
    f1 = TFile("run/jpsi2invi/hist_data09/jpsi2invi_data_psip_data09_event_merged_evtflw.root")

elif '09_sel' in logdir:
    mbc.SetLogy() 
    f0 = TFile("run/jpsi2invi/hist_mc09/jpsi2invi_psip_mc09_event_merged_ncharged.root")
    f1 = TFile("run/jpsi2invi/hist_data09/jpsi2invi_data_psip_data09_event_merged_ncharged.root")

elif '12_pre' in logdir:
    mbc.SetLogy() 
    f0 = TFile("run/jpsi2invi/hist_mc12/jpsi2invi_psip_mc12_event_merged_evtflw.root")
    f1 = TFile("run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_evtflw.root")

elif '12_sel' in logdir:
    mbc.SetLogy() 
    f0 = TFile("run/jpsi2invi/hist_mc12/jpsi2invi_psip_mc12_event_merged_ncharged.root")
    f1 = TFile("run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_ncharged.root")

# elif 'any' in logdir:
#     mbc.SetLogy() 
#     f0 = TFile("run/gen_mc/jpsi2any_09/job_text/hist/jpsi2incl_gen_mc_any_09_event_merged_ncharged.root")
#     f1 = TFile("run/gen_mc/jpsi2any/job_text/hist/jpsi2incl_gen_mc_any_event_merged_fit.root")

h0_E = f0.Get(histo)
h1_E = f1.Get(histo)

if logdir in [['any_pre']]:
    # h0_E.GetYaxis().SetRangeUser(2200000, 30000000)
    h0_E.GetYaxis().SetRangeUser(0, 35000000)

if logdir in [['data_sel'], ['data_pre']]:
    h0_E.Scale(341.0/107.0) # 09 and 12 data

elif logdir in [['mc_sel'], ['mc_pre']]:
    h0_E.Scale(400.0/107.0) # 09 and 12 mc

elif logdir in [['12_sel'], ['12_pre']]:
    h0_E.Scale(341.0/400.0) # 12 mc and data

else:
    h0_E.Scale(1.0)
    
h0_E.SetTitle("")
h0_E.SetLineColor(ROOT.kRed)
h1_E.SetLineColor(ROOT.kBlue)
h1_E.SetLineWidth(2)
h0_E.SetLineWidth(2)
h0_E.Draw("")
h1_E.Draw("same")

h0_E.GetYaxis().SetName("")
h0_E.GetYaxis().SetTitleOffset(1.5)

if logdir in [['nunu_pim_costhe'], ['nunu_pip_costhe'], ['ee_mc_costhe_pim'], ['mumu_mc_costhe_pim'], ['nn_mc_costhe_pim'], ['pp_mc_costhe_pim'], ['ee_mc_costhe_pip'], ['mumu_mc_costhe_pip'], ['nn_mc_costhe_pip'], ['pp_mc_costhe_pip'], ['ee_pip_costhe'], ['mumu_pip_costhe'], ['nn_pip_costhe'], ['pp_pip_costhe'], ['ee_pim_costhe'], ['mumu_pim_costhe'], ['nn_pim_costhe'], ['pp_pim_costhe']]:
    legend = TLegend(0.28, 0.29, 0.68, 0.38)

else:
    legend = TLegend(0.28, 0.79, 0.68, 0.88)

if logdir in [['mumu_pre'], ['mumu_mc_costhe_pim'], ['mumu_mc_costhe_pip'], ['mumu_01'], ['mumu_02'], ['mumu_pip_costhe'], ['mumu_pim_costhe'], ['mumu_03'], ['mumu_04'], ['mumu_05'], ['mumu_06'], ['mumu'], ['mumu_07']]:
    legend.AddEntry(h0_E,'2009 Jpsi->mumu MC sample') 
    legend.AddEntry(h1_E,'2012 Jpsi->mumu MC sample')

elif logdir in [['ee_mc_costhe_pim'], ['ee_mc_costhe_pip'], ['ee_01'], ['ee_02'], ['ee_pip_costhe'], ['ee_pim_costhe'], ['ee_03'], ['ee_04'], ['ee_05'], ['ee_06'], ['ee'], ['ee_07']]:
    legend.AddEntry(h0_E,'2009 Jpsi->ee MC sample') 
    legend.AddEntry(h1_E,'2012 Jpsi->ee MC sample')

elif logdir in [['nn_mc_costhe_pim'], ['nn_mc_costhe_pip'], ['nn_01'], ['nn_02'], ['nn_pip_costhe'], ['nn_pim_costhe'], ['nn_03'], ['nn_04'], ['nn_05'], ['nn_06'], ['nn'], ['nn_07']]:
    legend.AddEntry(h0_E,'2009 Jpsi->nn MC sample') 
    legend.AddEntry(h1_E,'2012 Jpsi->nn MC sample')

elif logdir in [['pp_mc_costhe_pim'], ['pp_mc_costhe_pip'], ['pp_01'], ['pp_02'], ['pp_pip_costhe'], ['pp_pim_costhe'], ['pp_03'], ['pp_04'], ['pp_05'], ['pp_06'], ['pp'], ['pp_07']]:
    legend.AddEntry(h0_E,'2009 Jpsi->pp MC sample') 
    legend.AddEntry(h1_E,'2012 Jpsi->pp MC sample')

elif logdir in [['nunu_pim_costhe'], ['nunu_pip_costhe'], ['nunu_pre_fit'], ['nunu_pre'], ['nunu_sel'], ['nunu_sel_fit']]:
    legend.AddEntry(h0_E,'2009 Jpsi->nunu MC sample') 
    legend.AddEntry(h1_E,'2012 Jpsi->nunu MC sample')

elif logdir in [['data_pre'], ['data_sel']]:
    legend.AddEntry(h0_E,'2009 data set')
    legend.AddEntry(h1_E,'2012 data set')

elif logdir in [['mc_pre'], ['mc_sel'], ['any_pre'], ['any_sel']]:
    legend.AddEntry(h0_E,'2009 Jpsi->incl MC sample')
    legend.AddEntry(h1_E,'2012 Jpsi->incl MC sample')

elif logdir in [['09_pre'], ['09_sel']]:
    legend.AddEntry(h0_E,'2009 Jpsi->incl MC sample')
    legend.AddEntry(h1_E,'2009 data set')

elif logdir in [['12_pre'], ['12_sel']]:
    legend.AddEntry(h0_E,'2012 Jpsi->incl MC sample')
    legend.AddEntry(h1_E,'2012 data set')



# legend.SetNColums(1)
legend.SetBorderSize(0)
legend.SetFillColor(0)
legend.Draw()
h0_E.GetXaxis().SetTitle('%s' %'_'.join(logdir))

figfile = 'python/plots/%s.pdf' %'_'.join(logdir)

mbc.SaveAs(figfile)











