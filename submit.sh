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
    printf "\n\t%-9s  %-40s"  "0.1.3"    "Submit Condor jobs on data"
    printf "\n\t%-9s  %-40s"  "0.1.4"    "Check Condor jobs on data."
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Select events."
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Submit events selection jobs on data."
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Check events jobs on data."
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Merge events files." 
    printf "\n\t%-9s  %-40s"  "0.1.9"    "Plot summary with data."
    printf "\n\t%-9s  %-40s"  "0.1.10"   "Split con3650 data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.11"   "Submit Condor jobs on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.12"   "Check Condor jobs on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.13"   "Select events on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.14"   "Merge events on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.1.15"   "Plot summary with data and con3650"
    printf "\n\t%-9s  %-40s"  "0.1.16"   "Split data09 sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.17"   "Submit Condor jobs on 09 data sample"
    printf "\n\t%-9s  %-40s"  "0.1.18"   "Check Condor PBS jobs on 09 data sample"
    printf "\n\t%-9s  %-40s"  "0.1.19"   "Event selecion on 09 data"
    printf "\n\t%-9s  %-40s"  "0.1.20"   "PBS jobs for event selecion on 09 data"
    printf "\n\t%-9s  %-40s"  "0.1.21"   "Check Condor jobs for event selecion on 09 data"
    printf "\n\t%-9s  %-40s"  "0.1.22"   "Merge event file on 09 data"
    printf "\n\t%-9s  %-40s"  "0.1.23"   "Plot summary on 09 data"
    printf "\n\t%-9s  %-40s"  "0.1.24"   "Run with Jpsi2incl on a few 09 data events "
    printf "\n\t%-9s  %-40s"  "0.1.25"   "Submit Jpsi2incl Condor jobs on data09"
    printf "\n\t%-9s  %-40s"  "0.1.26"   "Check Jpsi2incl Condor jobs on data09"
    printf "\n\t%-9s  %-40s"  "0.1.27"   "Select Jpsi2incl events on data09"
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
    printf "\n\t%-9s  %-40s"  "0.2.10"   "Run a few events on 09 psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "0.2.11"   "Split 09 psi(2S) MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.12"   "Submit PBS jobs on 09 psi(2S) MC sample"         
    printf "\n\t%-9s  %-40s"  "0.2.13"   "Check PBS jobs on 09 psi(2S) MC sample"         
    printf "\n\t%-9s  %-40s"  "0.2.14"   "Select events on 09 psi(2S) MC sample"         
    printf "\n\t%-9s  %-40s"  "0.2.15"   "Submit PBS jobs to select events on 09 psi(2S) MC sample"         
    printf "\n\t%-9s  %-40s"  "0.2.16"   "Check PBS jobs to select events on 09 psi(2S) MC sample"         
    printf "\n\t%-9s  %-40s"  "0.2.17"   "Merge events file on 09 psi(2S) MC sample"         
    printf "\n\t%-9s  %-40s"  "0.2.18"   "Plot summary with 09 data and 09 psi(2S) MC sample"         
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
	   boss.exe condor/jobOptions_jpsi2invi.txt
	   ;;
    
    0.1.2) echo "Split data sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/dst run/samples/data_664p03_psip.txt 20G
	   # made 633 groups 
	   ;;

    0.1.3) echo "Submit Condor jobs on data..." 
	   mkdir -p run/jpsi2invi/job_text/Data12
	   mkdir -p run/jpsi2invi/rootfile
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_Data12_jpsi2invi.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2invi_data_psip_data12-633.txt jobOptions_jpsi2invi_data_psip_data12-0.txt
	   boss.condor -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12-%{ProcId}.txt
	   ;;

    0.1.4) echo "Check Condor jobs on data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile  633
	   ;;
    
    0.1.5) echo  "Select events on data..."
	   mkdir -p  run/jpsi2invi/event 
	   ./python/sel_events.py  run/jpsi2invi/rootfile/jpsi2invi_data_psip_data12-1.root  run/jpsi2invi/event/jpsi2invi_data_psip_data12-1.root 
	   ;; 

    0.1.6) echo "Submit selection Condor jobs on data..."
	   cd
	   mkdir run/jpsi2invi/event
	   mkdir run/jpsi2invi/job_text/Data12_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2invi_data_psip_data12_event-633.sh jobOptions_jpsi2invi_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2invi_data_psip_data12_event-*
	   hep_sub -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12_event-%{ProcId}.sh
	   cd 
	   cd bes/jpsi2invi/v0.1
	   ;;

    0.1.7) echo "Check Condor jobs on events data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event  633
	   ;;

    0.1.8) echo  "Merge event root file on data..."
	   mkdir run/jpsi2invi/hist
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event run/jpsi2invi/hist
	   ;; 

    0.1.9) echo  "Plot summary with data..."
	   ./python/plt_summary.py hist 
	   ;; 

    0.1.10) echo "Split con3650 data sample with each group 20G ..."
	    ./python/get_samples.py  /bes3fs/offline/data/663p01/3650/dst $HOME/bes/jpsi2invi/v0.1/run/samples/data_663p01_3650.txt 20G
	    # made 11 groups 
	    ;;

    0.1.11) echo "Submit Condor jobs on con3650 data..."
	    mkdir run/jpsi2invi/job_text/data3650
	    mkdir run/jpsi2invi/rootfile_data3650  
	    cd run/jpsi2invi/gen_script
		./make_jobOption_file_data3650.sh
		cd ../job_text/data3650
		mv jobOptions_jpsi2invi_data3650-11.txt jobOptions_jpsi2invi_data3650-0.txt
		boss.condor -g physics -n 11 jobOptions_jpsi2invi_data3650-%{ProcId}.txt
	    cd 
	    cd bes/jpsi2invi/v0.1
		;;

    0.1.12) echo "Check Condor jobs on con3650 data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile_data3650  11 
	   ;;

    0.1.13) echo  "Select events on con3650 data..."
	   mkdir run/jpsi2invi/event_data3650
	   mkdir run/jpsi2invi/job_text/data3650_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_data3650_event.sh
	   cd ../job_text/data3650_event
	   mv jobOptions_jpsi2invi_data3650_event-11.sh jobOptions_jpsi2invi_data3650_event-0.sh
	   chmod 755 jobOptions_jpsi2invi_data3650_event-*
	   hep_sub -g physics -n 11 jobOptions_jpsi2invi_data3650_event-%{ProcId}.sh
	   ;; 
    
	0.1.14)echo "Check event Condor jobs on con3650 data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_data3650 11
	   ;;
    
	0.1.15) echo  "Merge event root file on con3650 data..."
	   mkdir run/jpsi2invi/hist_data3650
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_data3650 run/jpsi2invi/hist_data3650
	   ;; 

    0.1.16) echo  "Plot summary with data and con3650..."
	   mkdir run/jpsi2invi/hist_data3650
	   ./python/plt_summary.py data3650 
	   ;;

    0.1.17) echo "Submit Condor jobs on data for incl..." 
	   mkdir -p run/jpsi2incl/job_text/Data12
	   mkdir -p run/jpsi2incl/rootfile
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_Data12_jpsi2invi.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2incl_data_psip_data12-633.txt jobOptions_jpsi2incl_data_psip_data12-0.txt
	   boss.condor -g physics -n 633 jobOptions_jpsi2incl_data_psip_data12-%{ProcId}.txt
	   ;;

    0.1.18) echo "Check Condor jobs on data..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile  633
	   ;;
    
    0.1.19) echo "Submit selection Condor jobs on data..."
	   mkdir run/jpsi2incl/event
	   mkdir run/jpsi2incl/job_text/Data12_event
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2incl_data_psip_data12_event-633.sh jobOptions_jpsi2incl_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2incl_data_psip_data12_event-*
	   hep_sub -g physics -n 633 jobOptions_jpsi2incl_data_psip_data12_event-%{ProcId}.sh
	   cd 
	   cd bes/jpsi2invi/v0.1
	   ;;

    0.1.20) echo "Check Condor jobs on events data..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event  633
	   ;;

    0.1.21) echo  "Merge event root file on data..."
	   mkdir run/jpsi2incl/hist
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event run/jpsi2incl/hist
	   ;; 

    0.1.22) echo  "Plot summary with data..."
	   ./python/plt_summary.py hist_incl 
	   ;; 
	


    # --------------------------------------------------------------------------
    #  0.2 MC Sample 
    # --------------------------------------------------------------------------
    
    0.2) echo "Running on MC sample..."
	 ;;

    0.2.1) echo "Run with a few events ..."
	   boss.exe pbs/jobOptions_jpsi2invi.txt
	   ;;
    0.2.2) echo "Split psi(2S) MC sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/12mc/dst $HOME/bes/jpsi2invi/v0.1/run/samples/mc_664p03_psip_12mc.txt 20G
	   # made 394 groups 
	   ;;

    0.2.3) echo "Submit Condor jobs on psi(2S) MC sample..."
	   mkdir -p run/jpsi2invi/job_text/mc12
	   mkdir -p run/jpsi2invi/rootfile_mc12
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc12_jpsi2invi.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2invi_psip_mc12-394.txt jobOptions_jpsi2invi_psip_mc12-0.txt
	   boss.condor -g physics -n 394 jobOptions_jpsi2invi_psip_mc12-%{ProcId}.txt 
	   cd 
	   cd bes/jpsi2invi/v0.1
	   ;;

    0.2.4) echo "Check Condor jobs on psi(2S) MC sample..."
	   ./python/chk_condorjobs.py $HOME/bes/jpsi2invi/v0.1/run/jpsi2invi/rootfile_mc12  394 
	   ;;

    0.2.5) echo  "Select events on psi(2S) MC sample..."
	   mkdir run/jpsi2invi/event_mc12 
	   ./python/sel_events.py  run/jpsi2invi/rootfile_mc12/jpsi2invi_psip_mc12-1.root  run/jpsi2invi/event_mc12/jpsi2invi_psip_mc12-1.root 
	   ;; 

    0.2.6) echo "Submit selection Condor jobs on psi(2S) sample..."
	   mkdir run/jpsi2invi/event_mc12
	   mkdir run/jpsi2invi/job_text/mc12_event  
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2invi_psip_mc12_event-394.sh jobOptions_jpsi2invi_psip_mc12_event-0.sh
	   chmod 755 jobOptions_jpsi2invi_psip_mc12_event-*
	   hep_sub -g physics -n 394 jobOptions_jpsi2invi_psip_mc12_event-%{ProcId}.sh
	   ;;

    0.2.7) echo "Check events selection jobs on psi(2S) MC sample..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_mc12  394 
	   ;;

    0.2.8) echo  "Merge events files..."
	   mkdir run/jpsi2invi/hist_mc12
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_mc12 run/jpsi2invi/hist_mc12
	   ;; 

    0.2.9) echo  "Plot summary with data and psip(2S) MC ..."
	   ./python/plt_summary.py mc12
	   ;; 

    0.2.10) echo "Submit Condor jobs on psip(2S) for incl..." 
	   mkdir -p run/jpsi2incl/job_text/mc12
	   mkdir -p run/jpsi2incl/rootfile_mc12
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc12_jpsi2incl.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2incl_psip_mc12-394.txt jobOptions_jpsi2incl_psip_mc12-0.txt
	   boss.condor -g physics -n 394 jobOptions_jpsi2incl_psip_mc12-%{ProcId}.txt
	   ;;

    0.2.11) echo "Check Condor jobs on psip(2S)..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_mc12  394
	   ;;
    
    0.2.12) echo "Submit selection Condor jobs on psip(2S)..."
	   mkdir run/jpsi2incl/event_mc12
	   mkdir run/jpsi2incl/job_text/mc12_event
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2incl_psip_mc12_event-394.sh jobOptions_jpsi2incl_psip_mc12_event-0.sh
       chmod 755 jobOptions_jpsi2incl_psip_mc12_event-*
	   hep_sub -g physics -n 394 jobOptions_jpsi2incl_psip_mc12_event-%{ProcId}.sh
	   cd 
	   cd bes/jpsi2invi/v0.1
	   ;;

    0.2.13) echo "Check Condor jobs on events psip(2S)..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_mc12  394
	   ;;

    0.2.14) echo  "Merge event root file on psip(2S)..."
	   mkdir run/jpsi2incl/hist_mc12
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_mc12 run/jpsi2incl/hist_mc12
	   ;; 

    0.2.15) echo  "Plot summary with psip(2S)..."
	   ./python/plt_summary.py mc12_incl 
	   ;; 
	

esac

