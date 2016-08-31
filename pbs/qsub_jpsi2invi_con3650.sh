#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-08-30 Tue 08:10] 

#PBS -N jdata
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/con3650/jpsi2invi_con3650.log 
#PBS -t 1-11


date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh 
cd pbs 
boss.exe jobOptions_jpsi2invi_con3650.pbs

date


