#!/bin/bash
# Script to submit Condor jobs
# Author: XIAO Suyu <xiaosuyu@ihep.ac.cn>
# Date: [2017-10-20 Fri 15:16]

#hep_sub -g physics
#hep_sub -o /besfs/groups/nphy/users/xiaosy/bes/jpsi2invi/v0.1/run/log/data/jpsi2invi_data.log
#hep_sub -e /besfs/groups/nphy/users/xiaosy/bes/jpsi2invi/v0.1/run/error/data/jpsi2invi_data.error
#hep_sub -n 1







date

hostname

cd $HOME/bes/jpsi2invi/v0.1/
source setup.sh
cd condor/jpsi2invi
boss.exe jobOptions_jpsi2invi_data.txt

date
