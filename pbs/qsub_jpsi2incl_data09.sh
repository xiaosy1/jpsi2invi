#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-10-13 Thu 09:21] 

#PBS -N jdata09
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/data09/jpsi2incl_data09.log 
#PBS -t 1-314%200

date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh 
cd pbs 
boss.exe jobOptions_jpsi2incl_data09.pbs

date


