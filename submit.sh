#!/usr/bin/env bash

# Main driver to submit jobs 
# Author SHI Xin <shixin@ihep.ac.cn>
# Created [2016-03-28 Mon 07:58]


usage() {
    printf "NAME\n\tsubmit.sh - Main driver to submit jobs\n"
    printf "\nSYNOPSIS\n"
    printf "\n\t%-5s\n" "./submit.sh [OPTION]" 
    printf "\nOPTIONS\n" 
    
    printf "\n\t%-9s  %-40s"  "0.1"      "[run data sample for jpsi2invi]" 
 
    printf "\n\n" 
}


usage_0_1() {
    printf "\n\t%-9s  %-40s"  ""         ""   
    printf "\n\t%-9s  %-40s"  "0.1.1"    "Split data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.2"    "Generate Condor jobs on data ---- 1"
    printf "\n\t%-9s  %-40s"  "0.1.3"    "Test for data"
    printf "\n\t%-9s  %-40s"  "0.1.4"    "Submit Condor jobs on data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Check Condor jobs on data"
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Generate Selection Condor jobs on data ---- 1."
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Test for data event"
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Submit selection Condor jobs on data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.9"     "Check Condor jobs on events data"
	printf "\n\t%-9s  %-40s"  "0.1.10"    "Merge event root file on data" 
    printf "\n\t%-9s  %-40s"  "0.1.11"    "Plot summary with data"
    printf "\n\t%-9s  %-40s"  ""          ""
    printf "\n" 
}

if [[ $# -eq 0 ]]; then
    usage
    echo "Please enter your option: "
    read option
else
    option=$1    
fi

sub_0_1() {

case $option in
    
    # --------------------------------------------------------------------------
    #  Data  
    # --------------------------------------------------------------------------

    0.1.1) echo "Split data sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/dst run/samples/data_664p03_psip.txt 20G
	   # made 633 groups 
	   ;;

    0.1.2) echo "Generate Condor jobs on data ---- 1..." 
	   mkdir -p run/jpsi2invi/job_text/Data12
	   mkdir -p run/jpsi2invi/rootfile
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_Data12_jpsi2invi.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2invi_data_psip_data12-633.txt jobOptions_jpsi2invi_data_psip_data12-0.txt
	   ;;

    0.1.3) echo "Test for data" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/Data12/jobOptions_jpsi2invi_data_psip_data12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/Data12
            boss.exe jobOptions_jpsi2invi_data_psip_data12-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

           0.1.4) echo "Submit Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/Data12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../rootfile/jpsi2invi_data_psip_data12-*
		boss.condor -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12-%{ProcId}.txt
	    ;;

    0.1.5) echo "Check Condor jobs on data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile  633
	   ;;
    
    0.1.6) echo "Generate selection Condor jobs on data ---- 1..."
	   mkdir run/jpsi2invi/event
	   mkdir run/jpsi2invi/job_text/Data12_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2invi_data_psip_data12_event-633.sh jobOptions_jpsi2invi_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2invi_data_psip_data12_event-*
	   ;;

    0.1.7) echo "Test for data event" 
		cd run/jpsi2invi/job_text/Data12_event
		./jobOptions_jpsi2invi_data_psip_data12_event-0.sh
        ;;

    0.1.8) echo "Submit selection Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/Data12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../event/jpsi2invi_data_psip_data12_event-*	
	    hep_sub -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12_event-%{ProcId}.sh
	   ;;

    0.1.9) echo "Check Condor jobs on events data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event  633
	   ;;

    0.1.10) echo  "Merge event root file on data..."
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event run/jpsi2invi/hist
	   ;; 

    0.1.11) echo  "Plot summary with data..."
	   ./python/plt_summary.py hist 
	   ;;

esac

}



case $option in
    
    # --------------------------------------------------------------------------
    #  Data  
    # --------------------------------------------------------------------------

    0.1) echo "Running on data sample..."
        usage_0_1 
        echo "Please enter your option: " 
        read option  
        sub_0_1 option 
	    ;;

esac

