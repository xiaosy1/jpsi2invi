#!/usr/bin/env python
"""
Plot summary histograms 
"""

__author__ = "SHI Xin <shixin@ihep.ac.cn>"
__copyright__ = "Copyright (c) SHI Xin"
__created__ = "[2016-07-25 Mon 09:22]" 

import os
import sys 
import ROOT 
from tools import check_outfile_path, set_root_style


def main():
    set_root_style(stat=0, grid=0) 
    ROOT.gStyle.SetPadLeftMargin(0.15)

    c = ROOT.TCanvas('c', 'c', 800, 800)    

    f1 = ROOT.TFile('run/hist/data/jpsi2invi_data_merged_1.root')
    f2 = ROOT.TFile('run/hist/mc_psip12/jpsi2invi_mc_psip_12mc_merged_1.root')
    f3 = ROOT.TFile('run/hist/con3650/jpsi2invi_con3650_merged_1.root')

    fs = [f1, f2, f3]
    
    draw_mrecpipi(c, fs)
    draw_mpipi(c, fs)
    draw_pip_p(c, fs) 
    draw_pim_p(c, fs) 
    draw_pip_costhe(c, fs) 
    draw_pim_costhe(c, fs)
    draw_cospipi(c, fs) 
    draw_cos2pisys(c, fs)
    draw_ngam(c, fs) 

def get_common_objects_to_draw(fs, hname, leg):
    h1 = fs[0].Get(hname)
    h1.Sumw2()
    h1.GetXaxis().SetLabelSize(0.03) 
    h1.GetYaxis().SetLabelSize(0.03) 
    h1.GetYaxis().SetTitleOffset(1.8) 
    h1.SetMarkerStyle(ROOT.kFullDotLarge)

    h2 = fs[1].Get(hname)
    h2.SetLineColor(29)
    h2.SetFillColor(29)

    h3 = fs[2].Get(hname)
    h3.SetLineColor(ROOT.kOrange)
    h3.SetFillColor(ROOT.kOrange)

    leg.SetTextSize(0.03)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetLineColor(0)
    leg.SetShadowColor(0)
    leg.AddEntry(h1, "Data","lp")
    leg.AddEntry(h2, "#psi(2S) inclusive MC")
    leg.AddEntry(h3, "Cont.")

    hs = [h1, h2, h3]
    return  hs, leg 


def draw_mrecpipi(c, fs):
    hname = 'h_mrecpipi'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    hs[0].SetXTitle('M(recoil(#pi^{+}#pi^{-})) (GeV/c^{2})') 
    hs[0].SetYTitle('Events/(0.0012 GeV/c^{2})')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()
    
    figfile = 'doc/fig/jpsi2invi_mrecpipi.pdf'
    check_outfile_path(figfile)
    c.SaveAs(figfile)


def draw_mpipi(c, fs):
    hname = 'h_mpipi'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    hs[0].SetXTitle('M(#pi^{+}#pi^{-}) (GeV/c^{2})') 
    hs[0].SetYTitle('Events/(0.0012 GeV/c^{2})')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()

    figfile = 'doc/fig/jpsi2invi_mpipi.pdf'
    c.SaveAs(figfile)


def draw_pip_p(c, fs):
    hname = 'h_pip_p' 
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    hs[0].SetXTitle('P(#pi^{+}) (GeV/c)')
    hs[0].SetYTitle('Events/(0.005 GeV/c)') 
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()
    
    figfile = 'doc/fig/jpsi2invi_pip_p.pdf'
    c.SaveAs(figfile)


def draw_pim_p(c, fs):
    hname = 'h_pim_p'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    hs[0].SetXTitle('P(#pi^{-}) (GeV/c)')
    hs[0].SetYTitle('Events/(0.005 GeV/c)') 
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()

    figfile = 'doc/fig/jpsi2invi_pim_p.pdf'
    c.SaveAs(figfile)


def draw_pip_costhe(c, fs):
    hname = 'h_pip_costhe'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    hs[0].SetXTitle('cos#theta_{#pi^{+}}')
    hs[0].SetYTitle('Events/0.02')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()

    figfile = 'doc/fig/jpsi2invi_pip_costhe.pdf'
    c.SaveAs(figfile)


def draw_pim_costhe(c, fs):
    hname = 'h_pim_costhe'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    hs[0].SetXTitle('Cos#theta_{#pi^{-}}')
    hs[0].SetYTitle('Events/0.02')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()

    figfile = 'doc/fig/jpsi2invi_pim_costhe.pdf'
    c.SaveAs(figfile)


def draw_cospipi(c, fs):
    hname = 'h_cospipi'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    hs[0].SetXTitle('cos#theta_{#pi^{+}#pi^{-}}')
    hs[0].SetYTitle('Events/0.01')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()

    figfile = 'doc/fig/jpsi2invi_cospipi.pdf'
    c.SaveAs(figfile)


def draw_cos2pisys(c, fs):
    hname = 'h_cos2pisys'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    hs[0].SetXTitle('Cos#theta_{#pi#pi sys.}')
    hs[0].SetYTitle('Events/0.02')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()

    figfile = 'doc/fig/jpsi2invi_cos2pisys.pdf'
    c.SaveAs(figfile)


def draw_ngam(c, fs):
    hname = 'h_ngam'
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    hs[0].SetXTitle('N_{#gamma}')
    hs[0].SetYTitle('Events')
    hs[0].SetMarkerStyle(ROOT.kFullDotLarge)
    hs[0].Draw()
    hs[1].Draw('same') 
    hs[2].Draw('same') 
    leg.Draw()
    
    figfile = 'doc/fig/jpsi2invi_ngam.pdf'
    c.SaveAs(figfile)

    
if __name__ == '__main__':
    main()
