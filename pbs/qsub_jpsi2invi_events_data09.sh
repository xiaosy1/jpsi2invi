#!/bin/bash
# Script to submit PBS jobs 
# Author: SHI Xin <shixin@ihep.ac.cn>
# Date: [2016-09-05 Mon 08:31] 

#PBS -N seldata09
#PBS -q "besq@torqsrv"
#PBS -o $HOME/bes/jpsi2invi/v0.1/run/log/events/data09/jpsi2invi_data09.log 
##PBS -t 1-314 
#PBS -t 137,266,77,142,141,25,159,97,184 


date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh

./python/sel_events.py run/data09/jpsi2invi_data09-$PBS_ARRAYID.root run/events/data09/jpsi2invi_data09-$PBS_ARRAYID.root

date





