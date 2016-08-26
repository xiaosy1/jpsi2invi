#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-08-15 Mon 09:25] 

#PBS -N jmcpsip12
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/mc_psip12/jpsi2invi_mc_psip12.log 
#PBS -t 1-394%200


date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh 
cd pbs 
boss.exe jobOptions_jpsi2invi_mc_psip12.pbs

date


