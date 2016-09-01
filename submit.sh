#!/usr/bin/env bash

# Main driver to submit jobs 
# Author SHI Xin <shixin@ihep.ac.cn>
# Created [2016-03-28 Mon 07:58]


usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    printf "\n\t%-9s  %-40s"  "0.1"      "[run data sample]" 
    printf "\n\t%-9s  %-40s"  "0.1.1"    "Run with a few samples" 
    printf "\n\t%-9s  %-40s"  "0.1.2"    "Split data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.3"    "Submit PBS jobs on data"
    printf "\n\t%-9s  %-40s"  "0.1.4"    "Check PBS jobs on data."
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Select events."
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Submit events selection jobs on data."
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Check events jobs on data."
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Merge events files." 
    printf "\n\t%-9s  %-40s"  "0.1.9"    "Plot summary with data."
    printf "\n\t%-9s  %-40s"  "0.1.10"   "Split con3650 data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.11"   "Submit PBS jobs on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.12"   "Check PBS jobs on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.13"   "Select events on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.14"   "Merge events on con3650 data"
    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.2"      "[run on MC sample]"
    printf "\n\t%-9s  %-40s"  "0.2.1"    "Run with a few samples"
    printf "\n\t%-9s  %-40s"  "0.2.2"    "Split psi(2S) MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.3"    "Submit PBS jobs on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "0.2.4"    "Check PBS jobs on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "0.2.5"    "Select events on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "0.2.6"    "Submit PBS jobs to select events on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "0.2.7"    "Check events selection jobs on psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "0.2.8"    "Merge events files on psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "0.2.9"    "Plot summary with data and psi(2S) MC"
    printf "\n\n" 
}


if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi

case $option in
    
    # --------------------------------------------------------------------------
    #  0.1 Data  
    # --------------------------------------------------------------------------

    0.1) echo "Running on data sample..."
	 ;;

    0.1.1) echo "Run with a few events ..."
	   boss.exe jobOptions_jpsi2invi.txt
	   ;;
    
    0.1.2) echo "Split data sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/dst $HOME/bes/jpsi2invi/v0.1/run/samples/data_664p03_psip.txt 20G
	   # made 633 groups 
	   ;;

    0.1.3) echo "Submit PBS jobs on data..."
	   mkdir run/data
	   mkdir run/log/data  
	   qsub pbs/qsub_jpsi2invi_data.sh  
	   ;;

    0.1.4) echo "Check PBS jobs on data..."
	   ./python/chk_pbsjobs.py $HOME/bes/jpsi2invi/v0.1/run/data  633
	   ;;
    
    0.1.5) echo  "Select events on data..."
	   mkdir run/events/data 
	   ./python/sel_events.py  run/data/jpsi2invi_data-1.root  run/events/data/jpsi2invi_data-1.root 
	   ;; 

    0.1.6) echo "Submit selection PBS jobs on data..."
	   mkdir run/events/data
	   mkdir run/log/events/data   
	   qsub pbs/qsub_jpsi2invi_events_data.sh  
	   ;;

    0.1.7) echo "Check PBS jobs on events data..."
	   ./python/chk_pbsjobs.py run/events/data  633
	   ;;

    0.1.8) echo  "Merge event root file on data..."
	   mkdir run/hist/data 
	   ./python/mrg_rootfiles.py  run/events/data run/hist/data 
	   ;; 

    0.1.9) echo  "Plot summary with data..."
	   ./python/plt_summary.py 
	   ;; 

    0.1.10) echo "Split con3650 data sample with each group 20G ..."
	    ./python/get_samples.py  /bes3fs/offline/data/663p01/3650/dst $HOME/bes/jpsi2invi/v0.1/run/samples/data_663p01_3650.txt 20G
	    # made 11 groups 
	    ;;

    0.1.11) echo "Submit PBS jobs on con3650 data..."
	    mkdir run/con3650
	    mkdir run/log/con3650  
	    qsub pbs/qsub_jpsi2invi_con3650.sh  
	    ;;

    0.1.12) echo "Check PBS jobs on con3650 data..."
	   ./python/chk_pbsjobs.py run/con3650  11 
	   ;;

    0.1.13) echo  "Select events on con3650 data..."
	   mkdir run/events/con3650
	   for i in {1..11}  
	   do  
	       echo "processing run/con3650/jpsi2invi_con3650-$i.root ..."
	       ./python/sel_events.py  run/con3650/jpsi2invi_con3650-$i.root  run/events/con3650/jpsi2invi_con3650-$i.root
	   done   
	   ;; 
    
    0.1.14) echo  "Merge event root file on con3650 data..."
	   mkdir run/hist/con3650
	   ./python/mrg_rootfiles.py  run/events/con3650 run/hist/con3650 
	   ;; 

    0.1.15) echo  "Plot summary with data and con3650..."
	   ./python/plt_summary.py 
	   ;; 


    # --------------------------------------------------------------------------
    #  0.2 MC Sample 
    # --------------------------------------------------------------------------
    
    0.2) echo "Running on MC sample..."
	 ;;

    0.2.1) echo "Run with a few events ..."
	   boss.exe jobOptions_jpsi2invi.txt
	   ;;
    0.2.2) echo "Split psi(2S) MC sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/12mc/dst $HOME/bes/jpsi2invi/v0.1/run/samples/mc_664p03_psip_12mc.txt 20G
	   # made 394 groups 
	   ;;

    0.2.3) echo "Submit PBS jobs on psi(2S) MC sample..."
	   mkdir run/mc_psip12
	   mkdir run/log/mc_psip12  
	   qsub pbs/qsub_jpsi2invi_mc_psip12.sh  
	   ;;

    0.2.4) echo "Check PBS jobs on psi(2S) MC sample..."
	   ./python/chk_pbsjobs.py $HOME/bes/jpsi2invi/v0.1/run/mc_psip12  394 
	   ;;

    0.2.5) echo  "Select events on psi(2S) MC sample..."
	   mkdir run/events/mc_psip12  
	   #./python/sel_events.py  run/mc_psip12/jpsi2invi_mc_psip_12mc-1.root  run/events/mc_psip12/jpsi2invi_mc_psip_12mc-1.root
	   for i in {1..394}  
	   do  
	       echo "processing run/mc_psip12/jpsi2invi_mc_psip_12mc-$i.root ..."
	       ./python/sel_events.py  run/mc_psip12/jpsi2invi_mc_psip_12mc-$i.root  run/events/mc_psip12/jpsi2invi_mc_psip_12mc-$i.root
	   done   
	   ;; 

    0.2.6) echo "Submit selection PBS jobs on psi(2S) sample..."
	   mkdir run/events/mc_psip12
	   mkdir run/log/events/mc_psip12  
	   qsub pbs/qsub_jpsi2invi_events_mc_psip12.sh  
	   ;;

    0.2.7) echo "Check events selection jobs on psi(2s) MC sample..."
	   ./python/chk_pbsjobs.py run/events/mc_psip12  394 
	   ;;

    0.2.8) echo  "Merge events files..."
	   mkdir run/hist/mc_psip12
	   ./python/mrg_rootfiles.py  run/events/mc_psip12 run/hist/mc_psip12 
	   ;; 

    0.2.9) echo  "Plot summary with data and psip(2S) MC ..."
	   ./python/plt_summary.py 
	   ;; 


esac

