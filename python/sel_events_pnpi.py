#!/usr/bin/env python
"""
Following sel_events.py 

Event Selection 
"""

__author__ = "R. Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryuta Kiuchi"
__created__ = "[2017-03-02 Thu 15:00]" 

import sys
import os
import math 
import ROOT 
from progressbar import Bar, Percentage, ProgressBar
from time import time 
from tools import duration, check_outfile_path

#TEST=True 
TEST=False

# Global constants 
JPSI_MASS = 3.096916; 
NEUTRON_MASS = 0.939565;

# Global histograms

h_evtflw = ROOT.TH1F('hevtflw', 'eventflow', 10, 0, 10) 
h_evtflw.GetXaxis().SetBinLabel(1, 'raw')
h_evtflw.GetXaxis().SetBinLabel(2, '0.91<M_{n}<0.97')
h_evtflw.GetXaxis().SetBinLabel(3, 'M_{p#pi}>1.15')
h_evtflw.GetXaxis().SetBinLabel(4, 'Neutron|p|>1.0') 
h_evtflw.GetXaxis().SetBinLabel(5, 'Neutron: |cos#theta|<0.8 or ||') 
h_evtflw.GetXaxis().SetBinLabel(6, 'Proton|p|<2.0') 
h_evtflw.GetXaxis().SetBinLabel(7, 'Pion|p|<2.0') 


 
h_nbar_mass = ROOT.TH1D('h_nbar_mass', 'nbar_mass', 60, 0.80, 1.10)
h_nbar_mass_woMassSigCut = ROOT.TH1D('h_nbar_mass_woMassSigCut', 'nbar_mass_woMassSigCut', 60, 0.80, 1.10)
h_nbar_ngam = ROOT.TH1D('h_nbar_ngam', 'nbar_ngam', 15, 0, 15)
h_nbar_ngam_dangcut = ROOT.TH1D('h_nbar_ngam_dangcut', 'nbar_ngam_dangcut', 15, 0, 15)
h_nbar_ppi_mass = ROOT.TH1D('h_nbar_ppi_mass', 'nbar_ppi_mass', 110, 0.9, 2.0) 
h_nbar_nmom = ROOT.TH1D('h_nbar_nmom', 'nbar_nmom', 200, 0.0, 2.0) 
h_nbar_nmom_comfig = ROOT.TH1D('h_nbar_nmom_comfig', 'nbar_nmom_comfig', 40, 0.0, 2.0) 
h_nbar_pmom = ROOT.TH1D('h_nbar_pmom', 'nbar_pmom', 200, 0.0, 2.0) 
h_nbar_pimom = ROOT.TH1D('h_nbar_pimom', 'nbar_pimom', 200, 0.0, 2.0) 
h_nbar_ncostheta = ROOT.TH1D('h_nbar_ncostheta', 'nbar_costheta', 100, -1.0, 1.0)
h_nbar_gn_dang = ROOT.TH1D('h_nbar_gn_dang', 'nbar_gn_dang',180, 0, 180) 
 
h_n_mass = ROOT.TH1D('h_n_mass', 'n_mass', 60, 0.80, 1.10)
h_n_mass_woMassSigCut = ROOT.TH1D('h_n_mass_woMassSigCut', 'n_mass_woMassSigCut', 60, 0.80, 1.10)
h_n_ngam = ROOT.TH1D('h_n_ngam', 'n_ngam', 15, 0, 15)
h_n_ngam_dangcut = ROOT.TH1D('h_n_ngam_dangcut', 'n_ngam_dangcut', 15, 0, 15)
h_n_ppi_mass = ROOT.TH1D('h_n_ppi_mass', 'n_ppi_mass', 110, 0.9, 2.0) 
h_n_nmom = ROOT.TH1D('h_n_nmom', 'n_nmom', 200, 0.0, 2.0) 
h_n_nmom_comfig = ROOT.TH1D('h_n_nmom_comfig', 'n_nmom_comfig', 40, 0.0, 2.0) 
h_n_pmom = ROOT.TH1D('h_n_pmom', 'n_pmom', 200, 0.0, 2.0) 
h_n_pimom = ROOT.TH1D('h_n_pimom', 'n_pimom', 200, 0.0, 2.0) 
h_n_ncostheta = ROOT.TH1D('h_n_ncostheta', 'n_costheta', 100, -1.0, 1.0)
h_n_gn_dang = ROOT.TH1D('h_n_gn_dang', 'n_gn_dang',180, 0, 180) 


h_nbar_nhit = ROOT.TH1D('h_nbar_nhit', 'nbar_nhit', 200, 0, 200)
h_nbar_secmom = ROOT.TH1D('h_nbar_secmom', 'nbar_secmom', 200, 0, 200)
h_nbar_cstat = ROOT.TH1D('h_nbar_cstat', 'nbar_cstat', 30000, 0, 30000)

h_nbar_nhit_c0 = ROOT.TH1D('h_nbar_nhit_c0', 'nbar_nhit_c0', 200, 0, 200)
h_nbar_secmom_c0 = ROOT.TH1D('h_nbar_secmom_c0', 'nbar_secmom_c0', 200, 0, 200)
h_nbar_nhit_c1 = ROOT.TH1D('h_nbar_nhit_c1', 'nbar_nhit_c1', 200, 0, 200)
h_nbar_secmom_c1 = ROOT.TH1D('h_nbar_secmom_c1', 'nbar_secmom_c1', 200, 0, 200)

h_n_nhit = ROOT.TH1D('h_n_nhit', 'n_nhit', 200, 0, 200)
h_n_secmom = ROOT.TH1D('h_n_secmom', 'n_secmom', 200, 0, 200)
h_n_cstat = ROOT.TH1D('h_n_cstat', 'n_cstat', 30000, 0, 30000)

h_n_nhit_c0 = ROOT.TH1D('h_n_nhit_c0', 'n_nhit_c0', 200, 0, 200)
h_n_secmom_c0 = ROOT.TH1D('h_n_secmom_c0', 'n_secmom_c0', 200, 0, 200)
h_n_nhit_c1 = ROOT.TH1D('h_n_nhit_c1', 'n_nhit_c1', 200, 0, 200)
h_n_secmom_c1 = ROOT.TH1D('h_n_secmom_c1', 'n_secmom_c1', 200, 0, 200)



def usage():
    sys.stdout.write('''
NAME
    sel_events_pnpi.py 

SYNOPSIS

    ./sel_events_pnpi.py infile outfile 

AUTHOR 
    R. Kiuchi <kiuchi@ihep.ac.cn> 

DATE
    March 2017
\n''')

    
def main():

    if TEST:
        sys.stdout.write('Run in TEST mode! \n')
    
    args = sys.argv[1:]
    if len(args) < 2:
        return usage()
    
    infile = args[0]
    outfile = args[1]
    check_outfile_path(outfile)

    fin = ROOT.TFile(infile)
    t = fin.Get('tree')
    entries = t.GetEntriesFast()

    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()

    for jentry in xrange(entries):
        pbar.update(jentry+1)
        # get the next tree in the chain and verify
        ientry = t.LoadTree(jentry)
        if ientry < 0:
            break
        # copy next entry into memory and verify

        if TEST and ientry > 10000:
            break
        
        nb = t.GetEntry(jentry)
        if nb<=0:
            continue

        fill_histograms(t)
        
        if select_jpsi_to_pnpi(t): 
            ngam = t.ngam
            num_n_related_gamma = 0

            for gentry in range(ngam):
                if( t.gn_dang[gentry] < 30 ):
                    num_n_related_gamma += 1
            
            if( t.pnpi_flag == 1 ):
                h_nbar_mass.Fill(t.vtx_neutron_m)
                h_nbar_ngam_dangcut.Fill(num_n_related_gamma)
                h_nbar_pmom.Fill(t.vtx_proton_p)
                h_nbar_pimom.Fill(t.vtx_pion_p)

                for gentry in range(ngam):
                    if( t.gn_dang[gentry] < 30 ):
                        h_nbar_nhit.Fill(t.raw_nhit[gentry])
                        h_nbar_secmom.Fill(t.raw_secmom[gentry])
                        h_nbar_cstat.Fill(t.raw_cstat[gentry])
                        if( t.raw_cstat[gentry]%2 == 0 ):
                            h_nbar_nhit_c0.Fill(t.raw_nhit[gentry])
                            h_nbar_secmom_c0.Fill(t.raw_secmom[gentry])
                        if( t.raw_cstat[gentry]%2 == 1 ):
                            h_nbar_nhit_c1.Fill(t.raw_nhit[gentry])
                            h_nbar_secmom_c1.Fill(t.raw_secmom[gentry])

            if( t.pnpi_flag == 2 ):
                h_n_mass.Fill(t.vtx_neutron_m)
                h_n_ngam_dangcut.Fill(num_n_related_gamma)
                h_n_pmom.Fill(t.vtx_proton_p)
                h_n_pimom.Fill(t.vtx_pion_p)

                for gentry in range(ngam):
                    if( t.gn_dang[gentry] < 30 ):
                        h_n_nhit.Fill(t.raw_nhit[gentry])
                        h_n_secmom.Fill(t.raw_secmom[gentry])
                        h_n_cstat.Fill(t.raw_cstat[gentry])
                        if( t.raw_cstat[gentry]%2 == 0 ):
                            h_n_nhit_c0.Fill(t.raw_nhit[gentry])
                            h_n_secmom_c0.Fill(t.raw_secmom[gentry])
                        if( t.raw_cstat[gentry]%2 == 1 ):
                            h_n_nhit_c1.Fill(t.raw_nhit[gentry])
                            h_n_secmom_c1.Fill(t.raw_secmom[gentry])

 
    fout = ROOT.TFile(outfile, "RECREATE")
    write_histograms() 
    fout.Close()
    pbar.finish()
    
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur) 


def fill_histograms(t):

    cut_proton_mom = (abs(t.vtx_proton_p) < 2.0)
    cut_pion_mom = (abs(t.vtx_pion_p) < 2.0)

#    cut_neutron_mass_sig = (abs(t.vtx_neutron_m - NEUTRON_MASS) < 0.030)
    cut_neutron_mass_sig = (abs(t.vtx_neutron_m - 0.94) < 0.030)
#    cut_neutron_mass_sig = (abs(t.vtx_neutron_m - 0.85) < 0.030 or abs(t.vtx_neutron_m - 1.03) < 0.030)
    cut_proton_pion_invMass =  (t.vtx_proton_pion_m > 1.15)

    cut_neutron_mom = (abs(t.vtx_neutron_p) > 1.0 )  

#    cut_costheta_neutron = (abs(t.vtx_neutron_costheta) < 0.40)
#    cut_costheta_neutron = (abs(t.vtx_neutron_costheta) < 0.80)
    cut_costheta_neutron = (abs(t.vtx_neutron_costheta) < 0.80 or
                            (abs(t.vtx_neutron_costheta) > 0.86 and 
                             abs(t.vtx_neutron_costheta) < 0.92) )
    
    if (                      cut_proton_pion_invMass and cut_neutron_mom and 
        cut_costheta_neutron and cut_proton_mom and cut_pion_mom):
        if( t.pnpi_flag == 1 ):
            h_nbar_mass_woMassSigCut.Fill(t.vtx_neutron_m)
        if( t.pnpi_flag == 2 ):
            h_n_mass_woMassSigCut.Fill(t.vtx_neutron_m)

    if (cut_neutron_mass_sig and cut_proton_pion_invMass and cut_neutron_mom and 
        cut_costheta_neutron and cut_proton_mom and cut_pion_mom):
        if( t.pnpi_flag == 1 ):
            h_nbar_ngam.Fill(t.ngam)
            for gentry in range(t.ngam):
                h_nbar_gn_dang.Fill(t.gn_dang[gentry])
        if( t.pnpi_flag == 2 ):
            h_n_ngam.Fill(t.ngam)
            for gentry in range(t.ngam):
                h_n_gn_dang.Fill(t.gn_dang[gentry])

    if (cut_neutron_mass_sig                             and cut_neutron_mom and 
        cut_costheta_neutron and cut_proton_mom and cut_pion_mom):
        if( t.pnpi_flag == 1 ):
            h_nbar_ppi_mass.Fill(t.vtx_proton_pion_m)
        if( t.pnpi_flag == 2 ):
            h_n_ppi_mass.Fill(t.vtx_proton_pion_m)

    if (cut_neutron_mass_sig and cut_proton_pion_invMass                     and 
        cut_costheta_neutron and cut_proton_mom and cut_pion_mom): 
        if( t.pnpi_flag == 1 ):
            h_nbar_nmom.Fill(t.vtx_neutron_p)
            h_nbar_nmom_comfig.Fill(t.vtx_neutron_p)
        if( t.pnpi_flag == 2 ):
            h_n_nmom.Fill(t.vtx_neutron_p)
            h_n_nmom_comfig.Fill(t.vtx_neutron_p)

    if (cut_neutron_mass_sig and cut_proton_pion_invMass and cut_neutron_mom  
                             and cut_proton_mom and cut_pion_mom):
        if( t.pnpi_flag == 1 ):
            h_nbar_ncostheta.Fill(t.vtx_neutron_costheta)
        if( t.pnpi_flag == 2 ):
            h_n_ncostheta.Fill(t.vtx_neutron_costheta)

    
def write_histograms():
    h_evtflw.Write()

    h_nbar_mass.Write()
    h_nbar_mass_woMassSigCut.Write()
    h_nbar_ngam.Write()
    h_nbar_ngam_dangcut.Write()
    h_nbar_ppi_mass.Write()
    h_nbar_nmom.Write()
    h_nbar_nmom_comfig.Write()
    h_nbar_pmom.Write()
    h_nbar_pimom.Write()
    h_nbar_ncostheta.Write()
    h_nbar_gn_dang.Write()

    h_n_mass.Write()
    h_n_mass_woMassSigCut.Write()
    h_n_ngam.Write()
    h_n_ngam_dangcut.Write()
    h_n_ppi_mass.Write()
    h_n_nmom.Write()
    h_n_nmom_comfig.Write()
    h_n_pmom.Write()
    h_n_pimom.Write()
    h_n_ncostheta.Write()
    h_n_gn_dang.Write()

    h_nbar_nhit.Write()
    h_nbar_secmom.Write()
    h_nbar_cstat.Write()
    h_nbar_nhit_c0.Write()
    h_nbar_secmom_c0.Write()
    h_nbar_nhit_c1.Write()
    h_nbar_secmom_c1.Write()

    h_n_nhit.Write()
    h_n_secmom.Write()
    h_n_cstat.Write()
    h_n_nhit_c0.Write()
    h_n_secmom_c0.Write()
    h_n_nhit_c1.Write()
    h_n_secmom_c1.Write()

    
def select_jpsi_to_pnpi(t):
    h_evtflw.Fill(0) 

#    if not (abs(t.vtx_neutron_m - NEUTRON_MASS) < 0.030 ):
#    if not (abs(t.vtx_neutron_m - 0.85) < 0.030 or abs(t.vtx_neutron_m - 1.03) < 0.030):
    if not (abs(t.vtx_neutron_m - 0.94) < 0.030 ):
        return False
    h_evtflw.Fill(1) 
    
    if not (t.vtx_proton_pion_m > 1.15):
        return False
    h_evtflw.Fill(2) 

#    if not (abs(t.vtx_neutron_p) > 1.1):
    if not (abs(t.vtx_neutron_p) > 1.0):
        return False 
    h_evtflw.Fill(3) 

#    if not (abs(t.vtx_neutron_costheta) < 0.80):
#    if not (abs(t.vtx_neutron_costheta) < 0.40):
    if not (abs(t.vtx_neutron_costheta) < 0.80 or
            (abs(t.vtx_neutron_costheta) > 0.86 and 
             abs(t.vtx_neutron_costheta) < 0.92) ):
        return False
    h_evtflw.Fill(4)

    if not (abs(t.vtx_proton_p) < 2.0):
        return False
    h_evtflw.Fill(5)
                    
    if not (abs(t.vtx_pion_p) < 2.0):
        return False
    h_evtflw.Fill(6)

    
    return True
    
    
if __name__ == '__main__':
    main()
