#!/usr/bin/env python
"""
Event Selection 
"""

__author__ = "R. Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryuta Kiuchi"
__created__ = "[2018-01-29 Tue 18:35]" 

import sys
import os
import math 
import ROOT 
from progressbar import Bar, Percentage, ProgressBar
from time import time 
from tools import duration, check_outfile_path
from array import array

# TEST=True 
TEST=False

# Global constants 
ECMS = 3.686
cms_p4 = ROOT.TLorentzVector(0.011*ECMS, 0, 0, ECMS)

# Global histograms

h_evtflw = ROOT.TH1F('hevtflw', 'eventflow', 10, 0, 10) 
h_evtflw.GetXaxis().SetBinLabel(1, 'raw')
h_evtflw.GetXaxis().SetBinLabel(2, '0.51<Mgg<0.57')
h_evtflw.GetXaxis().SetBinLabel(3, '|cos#theta|<0.8')
h_evtflw.GetXaxis().SetBinLabel(4, '|p|<0.45') 
h_evtflw.GetXaxis().SetBinLabel(5, 'PID') 
h_evtflw.GetXaxis().SetBinLabel(6, 'cos#theta_{#pi^{+}#pi^{-}}<0.95') 
h_evtflw.GetXaxis().SetBinLabel(7, 'cos#theta_{#pi#pi sys}<0.9') 
h_evtflw.GetXaxis().SetBinLabel(8, '3<M_{#pi#pi}^{rec}<3.2') 
h_evtflw.GetXaxis().SetBinLabel(9, 'Egam from jpsi > 1.0') 
h_evtflw.GetXaxis().SetBinLabel(10, 'Mpipi in (0.2, 1.0)') 


h_mrecpipi_zc = ROOT.TH1D('h_mrecpipi_zc', 'mrecpipi_zc', 100, 3.0, 3.2)
h_mrecpipi = ROOT.TH1D('h_mrecpipi', 'mrecpipi', 140, 2.0, 4.0)
h_mpipi = ROOT.TH1D('h_mpipi', 'mpipi', 100, 0.0, 4.0)                              # 0.2 - 0.7 
h_pi_p = ROOT.TH1D('h_pi_p', 'pi_p', 100, 0.0, 1.0)                                 # 0.0 - 0.5
h_pi_invi_p = ROOT.TH1D('h_pi_invi_p', 'pi_invi_p', 100, 0.0, 1.0)                  # 0.0 - 0.5
h_pi_costhe = ROOT.TH1D('h_pi_costhe', 'pi_costhe', 100, -1.0, 1.5)
h_pi_invi_costhe = ROOT.TH1D('h_pi_invi_costhe', 'pi_invi_costhe', 100, -1.0, 1.0)
h_cospipi = ROOT.TH1D('h_cospipi', 'cospipi', 200, -1.0, 1.0)
h_cos2pisys = ROOT.TH1D('h_cos2pisys', 'cos2pisys', 100, -1.0, 1.0)
h_ngam = ROOT.TH1D('h_ngam', 'ngam', 20, 0, 20)
h_gcostheta = ROOT.TH1D('h_gcostheta', 'gcostheta', 2000, -1.0, 1.0)

h_mgg = ROOT.TH1D('h_mgg', 'mgg', 100, 0.0, 0.7)                                    # 0.4 - 0.7
h_mpipieta = ROOT.TH1D('h_mpipieta', 'h_mpipieta', 100, 0.0, 0.2)                                    # 0.4 - 0.7
#h_mpipigg = ROOT.TH1D('h_mpipigg', 'mpipigg', 100, 0.4, 2.7)
h_ch_count = ROOT.TH1D('h_ch_count', 'ch_count', 22, 0, 22)

raw_gpx = ROOT.vector('double')()
raw_gpy = ROOT.vector('double')()
raw_gpz = ROOT.vector('double')()
raw_ge = ROOT.vector('double')()
trkm_px = array('d', [999.])
trkm_py = array('d', [999.])
trkm_pz = array('d', [999.])
trkm_e  = array('d', [999.])
trkp_px = array('d', [999.])
trkp_py = array('d', [999.])
trkp_pz = array('d', [999.])
trkp_e  = array('d', [999.])
count0 = 0
count1 = 0
count2 = 0
count3 = 0
count4 = 0
count5 = 0
count6 = 0
count7 = 0
count8 = 0
count9 = 0
count10 = 0
count11 = 0
count12 = 0
count13 = 0
count14 = 0
count15 = 0
count_EMC_Track = 0
count_all = 0
fill_trig = 0 
cut_mgg =0 
cut_trk_costhe =0 
cut_trkinvi_costhe =0 
cut_trk_p =0 
cut_trkinvi_p =0 
cut_cospipi =0 
cut_cos2pisys =0 
cut_pi_PID =0 
cut_mjpsi_win =0 
cut_mpipieta =0
cut_mpipi =0

def usage():
    sys.stdout.write('''
NAME
    sel_events.py 

SYNOPSIS

    ./sel_events.py infile outfile 

AUTHOR 
    R. Kiuchi <kiuchi@ihep.ac.cn>

DATE
    January 2018 
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
    t.SetBranchAddress("raw_gpx", raw_gpx)
    t.SetBranchAddress("raw_gpy", raw_gpy)
    t.SetBranchAddress("raw_gpz", raw_gpz)
    t.SetBranchAddress("raw_ge", raw_ge)
    # t.SetBranchAddress("trkm_px", trkm_px, "trkm_px/D")
    # t.SetBranchAddress("trkm_py", trkm_py, "trkm_py/D")
    # t.SetBranchAddress("trkm_pz", trkm_pz, "trkm_pz/D")
    # t.SetBranchAddress("trkm_e" , trkm_e , "trkm_e/D" )
    # t.SetBranchAddress("trkp_px", trkp_px, "trkp_px/D")
    # t.SetBranchAddress("trkp_py", trkp_py, "trkp_py/D")
    # t.SetBranchAddress("trkp_pz", trkp_pz, "trkp_pz/D")
    # t.SetBranchAddress("trkp_e" , trkp_e , "trkp_e/D" )
    entries = t.GetEntriesFast()
    fout = ROOT.TFile(outfile, "RECREATE")
    t_out = ROOT.TTree('tree', 'tree')

    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()

    for jentry in xrange(entries):
        pbar.update(jentry+1)
        # get the next tree in the chain and verify
        ientry = t.LoadTree(jentry)
        if ientry < 0:
            break
        # copy next entry into memory and verify

        if TEST and ientry > 500:
            break
        
        nb = t.GetEntry(jentry)
        if nb<=0:
            continue

        fill_histograms(t)
        
        if select_jpsi_to_gammaEta(t):
            t_out.Fill()

        if (fill_trig):

            ch0 = t.m_trig_channel[0]
            ch1 = t.m_trig_channel[1]
            ch2 = t.m_trig_channel[2]
            ch3 = t.m_trig_channel[3]
            ch4 = t.m_trig_channel[4]
            ch5 = t.m_trig_channel[5]
            ch6 = t.m_trig_channel[6]
            ch7 = t.m_trig_channel[7]
            ch8 = t.m_trig_channel[8]
            ch9 = t.m_trig_channel[9]
            ch10 = t.m_trig_channel[10]
            ch11 = t.m_trig_channel[11]
            ch12 = t.m_trig_channel[12]
            ch13 = t.m_trig_channel[13]
            ch14 = t.m_trig_channel[14]
            ch15 = t.m_trig_channel[15]
            global count0
            global count1
            global count2
            global count3
            global count4
            global count5
            global count6
            global count7
            global count8
            global count9
            global count10
            global count11
            global count12
            global count13
            global count14
            global count15
            global count_EMC_Track
            global count_all
            count0  = count0  + ch0
            count1  = count1  + ch1
            count2  = count2  + ch2
            count3  = count3  + ch3
            count4  = count4  + ch4
            count5  = count5  + ch5
            count6  = count6  + ch6
            count7  = count7  + ch7
            count8  = count8  + ch8
            count9  = count9  + ch9
            count10 = count10 + ch10
            count11 = count11 + ch11
            count12 = count12 + ch12
            count13 = count13 + ch13
            count14 = count14 + ch14
            count15 = count15 + ch15
            count_all = count_all + 1
            if( ch11 == 1 and ( ch0==1 or ch1==1 or ch2==1 or ch3==1 or ch4==1 or ch5==1 ) ):
                count_EMC_Track = count_EMC_Track + 1
            
        h_ch_count.Fill(0, count0)
        h_ch_count.Fill(1, count1)
        h_ch_count.Fill(2, count2)
        h_ch_count.Fill(3, count3)
        h_ch_count.Fill(4, count4)
        h_ch_count.Fill(5, count5)
        h_ch_count.Fill(6, count6)
        h_ch_count.Fill(7, count7)
        h_ch_count.Fill(8, count8)
        h_ch_count.Fill(9, count9)
        h_ch_count.Fill(10, count10)
        h_ch_count.Fill(11, count11)
        h_ch_count.Fill(12, count12)
        h_ch_count.Fill(13, count13)
        h_ch_count.Fill(14, count14)
        h_ch_count.Fill(15, count15)
        h_ch_count.Fill(19, count_EMC_Track)
        h_ch_count.Fill(21, count_all)

    t_out.Write()
    write_histograms() 
    fout.Close()
    pbar.finish()
    
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur) 

def fill_histograms(t):
    if (len(raw_ge) == 3):
        gam1_index = -1
        gam2_index = -1
        gam3_index = -1
        if ((raw_ge[0] > raw_ge[1]) and (raw_ge[0] > raw_ge[2])):
            gam1_index = 1
            gam2_index = 2
            gam3_index = 0
        elif ((raw_ge[1] > raw_ge[0]) and (raw_ge[1] > raw_ge[2])):
            gam1_index = 0
            gam2_index = 2
            gam3_index = 1
        else:
            gam1_index = 0
            gam2_index = 1
            gam3_index = 2
        gam1_p4_raw = ROOT.TLorentzVector(t.raw_gpx.at(gam1_index), t.raw_gpy.at(gam1_index), t.raw_gpz.at(gam1_index), t.raw_ge.at(gam1_index))
        gam2_p4_raw = ROOT.TLorentzVector(t.raw_gpx.at(gam2_index), t.raw_gpy.at(gam2_index), t.raw_gpz.at(gam2_index), t.raw_ge.at(gam2_index))
        gam3_p4_raw = ROOT.TLorentzVector(t.raw_gpx.at(gam3_index), t.raw_gpy.at(gam3_index), t.raw_gpz.at(gam3_index), t.raw_ge.at(gam3_index))
        eta_p4_raw = gam1_p4_raw + gam2_p4_raw
        pi_p4_raw = ROOT.TLorentzVector(0.0, 0.0, 0.0, 0.0)
        prob_pi = 0.0
        if (t.trkp_px):
            prob_pi = t.prob_pip
            pip_p4_raw = ROOT.TLorentzVector(t.trkp_px, t.trkp_py, t.trkp_pz, t.trkp_eraw)
            pi_p4_raw = pip_p4_raw
        else:
            prob_pi = t.prob_pim
            pim_p4_raw = ROOT.TLorentzVector(t.trkm_px, t.trkm_py, t.trkm_pz, t.trkm_eraw)
            pi_p4_raw = pim_p4_raw
        
        theta_g1g2 = gam1_p4_raw.Angle(gam2_p4_raw.Vect())
        theta_g1g3 = gam1_p4_raw.Angle(gam3_p4_raw.Vect())
        theta_g2g3 = gam2_p4_raw.Angle(gam3_p4_raw.Vect())

        pi_invi_p4_raw = cms_p4 - pi_p4_raw - gam1_p4_raw - gam2_p4_raw - gam3_p4_raw
        pipi_p4_raw = pi_invi_p4_raw +pi_p4_raw 
        jpsi_p4_raw = gam1_p4_raw + gam2_p4_raw + gam3_p4_raw

        # theta_pi = pi_p4_raw.Theta()
        # print theta_pi
        # theta_pi_invi = pi_invi_p4_raw.Theta()
        cospipi = math.cos(pi_p4_raw.Angle(pi_invi_p4_raw.Vect()))
        cos2pisys = (pi_p4_raw+pi_invi_p4_raw).CosTheta()
        # print cospipi

        global cut_mgg   
        global cut_trk_costhe   
        global cut_trkinvi_costhe   
        global cut_trk_p   
        global cut_trkinvi_p   
        global cut_cospipi   
        global cut_cos2pisys   
        global cut_pi_PID   
        global cut_mjpsi_win   
        global cut_mpipieta  
        global cut_mpipi  

        # cut_mgg = 1
        cut_mgg = ( eta_p4_raw.M() > 0.45 and eta_p4_raw.M() < 0.6 )
        cut_trk_costhe = (abs(pi_p4_raw.CosTheta()) < 0.8)
        cut_trk_p =  (abs(pi_p4_raw.P()) < 0.45)
        cut_trkinvi_costhe = 1
        cut_trkinvi_p = 1
        cut_cospipi = 1
        cut_cos2pisys = 1
        # cut_trkinvi_costhe = (abs(pi_invi_p4_raw.CosTheta()) < 0.8)
        # cut_trkinvi_p = (abs(pi_invi_p4_raw.P()) < 0.45)
        # cut_cospipi =  (cospipi<0.95)
        # cut_cos2pisys = (cos2pisys<0.9)
        cut_pi_PID = (prob_pi> t.prob_kp and prob_pi> t.prob_km and prob_pi> 0.001)
        cut_mpipi = (pipi_p4_raw.M()>0.2 and pipi_p4_raw.M()<1.0 )
        # cut_mpipi = 1
        cut_mjpsi_win = 1
        # cut_mjpsi_win = (jpsi_p4_raw.M()>3.0 and jpsi_p4_raw.M()<3.2)
        cut_mpipieta = 1
        # cut_mpipieta = (gam3_p4_raw.M()>1.0)

        if ( cut_mgg and  cut_trk_costhe and cut_trkinvi_costhe and cut_trk_p and cut_trkinvi_p and cut_mpipi and 
            cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_mpipi.Fill(pipi_p4_raw.M())
            h_mgg.Fill(eta_p4_raw.M())
            h_mpipieta.Fill(gam3_p4_raw.M())
            h_mrecpipi.Fill(jpsi_p4_raw.M())

        if (cut_mgg and                    cut_trkinvi_costhe and cut_trk_p and cut_trkinvi_p and cut_mpipi and
            cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_pi_costhe.Fill(pi_p4_raw.CosTheta())

        if (cut_mgg and cut_trk_costhe and                         cut_trk_p and cut_trkinvi_p and cut_mpipi and
            cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_pi_invi_costhe.Fill(pi_invi_p4_raw.CosTheta())

        if (cut_mgg and cut_trk_costhe and cut_trkinvi_costhe and               cut_trkinvi_p and cut_mpipi and
            cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_pi_p.Fill(pi_p4_raw.P())

        if (cut_mgg and cut_trk_costhe and cut_trkinvi_costhe and cut_trk_p and    cut_mpipi and
            cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_pi_invi_p.Fill(pi_invi_p4_raw.P())

        if (cut_mgg and cut_trk_costhe and cut_trkinvi_costhe and cut_trk_p and cut_trkinvi_p and cut_mpipi and
                            cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_cospipi.Fill(cospipi)

        if (cut_mgg and cut_trk_costhe and cut_trkinvi_costhe and cut_trk_p and cut_trkinvi_p and cut_mpipi and
            cut_cospipi and                   cut_pi_PID and cut_mjpsi_win and cut_mpipieta):
            h_cos2pisys.Fill(cos2pisys)

#         if (cut_mgg and cut_trk_costhe and cut_trkinvi_costhe and cut_trk_p and cut_trkinvi_p and 
#             cut_cospipi and cut_cos2pisys and cut_pi_PID and                   cut_mpipieta):
            # print jpsi_p4_raw.M()
#             h_mrecpipi.Fill(jpsi_p4_raw.M())

        if (cut_mgg and cut_trk_costhe and cut_trkinvi_costhe and cut_trk_p and cut_trkinvi_p and cut_mpipi and
            cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win and cut_mpipieta and (t.run>0) ):
            global fill_trig
            fill_trig = 1 

def write_histograms():
    h_evtflw.Write()
    h_mrecpipi.Write()
    h_mrecpipi_zc.Write()    
    h_mpipi.Write()
    h_pi_p.Write()
    h_pi_invi_p.Write()
    h_pi_costhe.Write()
    h_pi_invi_costhe.Write()
    h_cospipi.Write()
    h_cos2pisys.Write()
    h_ngam.Write()
    h_gcostheta.Write()

    h_mgg.Write()
    h_mpipieta.Write()
    h_ch_count.Write()

def select_jpsi_to_gammaEta(t):
    h_evtflw.Fill(0) 

    # Cut on the number of good photon to make the same condition as Z.C.
    if not (cut_mgg):
        return False
    h_evtflw.Fill(1) 
    
    # Selection Criteria for soft pions -- the same as invisible etc.
    if not ( cut_trk_costhe and cut_trkinvi_costhe):
        return False
    h_evtflw.Fill(2) 

    if not (cut_trk_p and cut_trkinvi_p):
        return False 
    h_evtflw.Fill(3) 

    if not (cut_pi_PID):
        return False
    h_evtflw.Fill(4)

    if not (cut_cospipi):
        return False
    h_evtflw.Fill(5)

    if not (cut_cos2pisys):
        return False
    h_evtflw.Fill(6)

    if not (cut_mjpsi_win):
        return False
    h_evtflw.Fill(7)
    
    if not (cut_mpipieta):
        return False
    h_evtflw.Fill(8)

    if not (cut_mpipi):
        return False
    h_evtflw.Fill(9)

    return True
    
    
if __name__ == '__main__':
    main()
