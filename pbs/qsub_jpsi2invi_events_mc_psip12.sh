#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-08-25 Thu 07:08] 

#PBS -N sel
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/events/mc_psip12/jpsi2invi_mc_psip_12mc.log 
#PBS -t 1-394%200

date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh

./python/sel_events.py run/mc_psip12/jpsi2invi_mc_psip_12mc-$PBS_ARRAYID.root run/events/mc_psip12/jpsi2invi_mc_psip_12mc-$PBS_ARRAYID.root


date




