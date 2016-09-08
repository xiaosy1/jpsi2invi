#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-09-08 Thu 09:17] 

#PBS -N selpsip09
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/events/mc_psip09/jpsi2invi_mc_psip_09mc.log 
#PBS -t 1-106


date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh

./python/sel_events.py run/mc_psip09/jpsi2invi_mc_psip_09mc-$PBS_ARRAYID.root run/events/mc_psip09/jpsi2invi_mc_psip_09mc-$PBS_ARRAYID.root



date




