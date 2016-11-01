#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-09-05 Mon 07:04] 

#PBS -N jmcpsip09
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/mc_psip09/jpsi2invi_mc_psip09.log 
#PBS -t 1-106


date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh 
cd pbs 
boss.exe jobOptions_jpsi2invi_mc_psip09.pbs

date


