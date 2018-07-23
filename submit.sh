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
    printf "\n\t%-9s  %-40s"  "0.1.1"    "Split data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.1.2"    "Generate Condor jobs on data ---- 1"
    printf "\n\t%-9s  %-40s"  "0.1.3"    "Test for data"
    printf "\n\t%-9s  %-40s"  "0.1.4"    "Submit Condor jobs on data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.5"    "Check Condor jobs on data"
    printf "\n\t%-9s  %-40s"  "0.1.6"    "Generate Selection Condor jobs on data ---- 1."
    printf "\n\t%-9s  %-40s"  "0.1.7"    "Test for data event"
    printf "\n\t%-9s  %-40s"  "0.1.8"    "Submit selection Condor jobs on data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.1.9"    "Check Condor jobs on events data"
	printf "\n\t%-9s  %-40s"  "0.1.10"    "Merge event root file on data" 
    printf "\n\t%-9s  %-40s"  "0.1.11"    "Plot summary with data"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.2"      "[run con3650 data for jpsi2invi]" 
    printf "\n\t%-9s  %-40s"  "0.2.1"   "Split con3650 data sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "0.2.2"    "Generate Condor jobs on con3650 data ---- 1"
    printf "\n\t%-9s  %-40s"  "0.2.3"    "Test for con3650 data"
    printf "\n\t%-9s  %-40s"  "0.2.4"    "Submit Condor jobs on con3650 data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.2.5"    "Check Condor jobs on con3650 data"
    printf "\n\t%-9s  %-40s"  "0.2.6"    "Generate Selection Condor jobs on con3650 data ---- 1."
    printf "\n\t%-9s  %-40s"  "0.2.7"    "Test for con3650 data event"
    printf "\n\t%-9s  %-40s"  "0.2.8"    "Submit selection Condor jobs on con3650 data ---- 2"
    printf "\n\t%-9s  %-40s"  "0.2.9"    "Check Condor jobs on events con3650 data"
	printf "\n\t%-9s  %-40s"  "0.2.10"    "Merge event root file on con3650 data" 
    printf "\n\t%-9s  %-40s"  "0.2.11"    "Plot summary with con3650 data"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.3"      "[run data sample]" 
    printf "\n\t%-9s  %-40s"  "0.3.2"    "Generate Condor jobs on data for incl ---- 1"
    printf "\n\t%-9s  %-40s"  "0.3.3"    "Test for data for incl"
    printf "\n\t%-9s  %-40s"  "0.3.4"    "Submit Condor jobs on data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.3.5"    "Check Condor jobs on data for incl"
    printf "\n\t%-9s  %-40s"  "0.3.6"    "Generate Selection Condor jobs on data for incl ---- 1."
    printf "\n\t%-9s  %-40s"  "0.3.7"    "Test for data event for incl"
    printf "\n\t%-9s  %-40s"  "0.3.8"    "Submit selection Condor jobs on data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.3.9"    "Check Condor jobs on events data for incl"
	printf "\n\t%-9s  %-40s"  "0.3.10"    "Merge event root file on data for incl" 
    printf "\n\t%-9s  %-40s"  "0.3.11"    "Plot summary with data for incl"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.4"      "[run data sample for jpsi2lplm]" 
    printf "\n\t%-9s  %-40s"  "0.4.2"    "Generate Condor jobs on data for lplm ---- 1"
    printf "\n\t%-9s  %-40s"  "0.4.3"    "Test for data for lplm"
    printf "\n\t%-9s  %-40s"  "0.4.4"    "Submit Condor jobs on data for lplm ---- 2"
    printf "\n\t%-9s  %-40s"  "0.4.5"    "Check Condor jobs on data for lplm"
    printf "\n\t%-9s  %-40s"  "0.4.6"    "Generate Selection Condor jobs on data for lplm ---- 1."
    printf "\n\t%-9s  %-40s"  "0.4.7"    "Test for data event for lplm"
    printf "\n\t%-9s  %-40s"  "0.4.8"    "Submit selection Condor jobs on data for lplm ---- 2"
    printf "\n\t%-9s  %-40s"  "0.4.9"    "Check Condor jobs on events data for lplm"
	printf "\n\t%-9s  %-40s"  "0.4.10"    "Merge event root file on data for lplm" 
    printf "\n\t%-9s  %-40s"  "0.4.11"    "Plot summary with data for lplm"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "0.7"      "[run con3650 data for jpsi2incl]" 
    printf "\n\t%-9s  %-40s"  "0.7.2"    "Generate Condor jobs on con3650 data for incl ---- 1"
    printf "\n\t%-9s  %-40s"  "0.7.3"    "Test for con3650 data for incl"
    printf "\n\t%-9s  %-40s"  "0.7.4"    "Submit Condor jobs on con3650 data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.7.5"    "Check Condor jobs on con3650 data for incl"
    printf "\n\t%-9s  %-40s"  "0.7.6"    "Generate Selection Condor jobs on con3650 data for incl ---- 1."
    printf "\n\t%-9s  %-40s"  "0.7.7"    "Test for con3650 data event for incl"
    printf "\n\t%-9s  %-40s"  "0.7.8"    "Submit selection Condor jobs on con3650 data for incl ---- 2"
    printf "\n\t%-9s  %-40s"  "0.7.9"    "Check Condor jobs on events con3650 data for incl"
	printf "\n\t%-9s  %-40s"  "0.7.10"    "Merge event root file on con3650 data for incl" 

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.1"      "[run on MC sample]"
    printf "\n\t%-9s  %-40s"  "1.1.1"    "Split psi(2S) MC sample with each group 20G"
    printf "\n\t%-9s  %-40s"  "1.1.2"    "Generate Condor jobs on psi(2S) MC sample ---- 1"     
    printf "\n\t%-9s  %-40s"  "1.1.3"    "Test for psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "1.1.4"    "Submit Condor jobs on psi(2S) MC sample ---- 2"     
    printf "\n\t%-9s  %-40s"  "1.1.5"    "Check Condor jobs on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "1.1.6"    "Generate Selection jobs on psi(2S) MC sample"     
    printf "\n\t%-9s  %-40s"  "1.1.7"    "Test for psi(2S) MC sample event"     
    printf "\n\t%-9s  %-40s"  "1.1.8"    "Submit Selection jobs on psi(2S) MC sample"        
    printf "\n\t%-9s  %-40s"  "1.1.9"    "Check events selection jobs on psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "1.1.10"    "Merge events files on psi(2S) MC"
    printf "\n\t%-9s  %-40s"  "1.1.11"    "Plot summary with data and psi(2S) MC"
	
    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.3"      "[run on MC sample for jpsi2incl]"
    printf "\n\t%-9s  %-40s"  "1.3.2"    "Generate Condor jobs on psi(2S) MC sample for incl ---- 1"     
    printf "\n\t%-9s  %-40s"  "1.3.3"    "Test for psi(2S) MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.4"    "Submit Condor jobs on psi(2S) MC sample for incl ---- 2"     
    printf "\n\t%-9s  %-40s"  "1.3.5"    "Check Condor jobs on psi(2S) MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.6"    "Generate Selection jobs on psi(2S) MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.7"    "Test for psi(2S) MC sample event for incl"     
    printf "\n\t%-9s  %-40s"  "1.3.8"    "Submit Selection jobs on psi(2S) MC sample for incl"        
    printf "\n\t%-9s  %-40s"  "1.3.9"    "Check events selection jobs on psi(2S) MC for incl"
    printf "\n\t%-9s  %-40s"  "1.3.10"    "Merge events files on psi(2S) MC for incl"
    printf "\n\t%-9s  %-40s"  "1.3.11"    "Plot summary with data and psi(2S) MC for incl"
        
    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.5"      "[run on generated MC sample]"
    printf "\n\t%-9s  %-40s"  "1.5.3"    "Test for generated MC sample"     
    printf "\n\t%-9s  %-40s"  "1.5.4"    "Submit Condor jobs on generated MC sample ---- 2"         
    printf "\n\t%-9s  %-40s"  "1.5.5"    "Check Condor jobs on generated MC sample"     
    printf "\n\t%-9s  %-40s"  "1.5.7"    "Test for generated MC sample event"     
    printf "\n\t%-9s  %-40s"  "1.5.8"    "Submit Selection jobs on generated MC sample"        
    printf "\n\t%-9s  %-40s"  "1.5.9"    "Check events selection jobs on generated MC"
    printf "\n\t%-9s  %-40s"  "1.5.10"    "Merge events files on generated MC"

    printf "\n\t%-9s  %-40s"  ""         ""
    printf "\n\t%-9s  %-40s"  "1.6"      "[run on generated MC sample for incl]"
    printf "\n\t%-9s  %-40s"  "1.6.3"    "Test for generated MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.6.4"    "Submit Condor jobs on generated MC sample for incl ---- 2"         
    printf "\n\t%-9s  %-40s"  "1.6.5"    "Check Condor jobs on generated MC sample for incl"     
    printf "\n\t%-9s  %-40s"  "1.6.7"    "Test for generated MC sample event for incl"     
    printf "\n\t%-9s  %-40s"  "1.6.8"    "Submit Selection jobs on generated MC sample for incl"        
    printf "\n\t%-9s  %-40s"  "1.6.9"    "Check events selection jobs on generated MC for incl"
    printf "\n\t%-9s  %-40s"  "1.6.10"    "Merge events files on generated MC for incl"


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
    #  Data  
    # --------------------------------------------------------------------------

    0.1) echo "Running on data sample..."
	 ;;

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
	   cd $HOME/bes/jpsi2invi/v0.1
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
            cd $HOME/bes/jpsi2invi/v0.1
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
	    cd $HOME/bes/jpsi2invi/v0.1
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
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.1.7) echo "Test for data event" 
		cd run/jpsi2invi/job_text/Data12_event
		./jobOptions_jpsi2invi_data_psip_data12_event-0.sh
		cd $HOME/bes/jpsi2invi/v0.1
        ;;

    0.1.8) echo "Submit selection Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/Data12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../event/jpsi2invi_data_psip_data12_event-*	
	    hep_sub -g physics -n 633 jobOptions_jpsi2invi_data_psip_data12_event-%{ProcId}.sh
	    cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.1.9) echo "Check Condor jobs on events data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event  633
	   ;;

    0.1.10) echo  "Merge event root file on data..."
	   mkdir run/jpsi2invi/hist
	   rm jpsi2invi_data_psip_data12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event run/jpsi2invi/hist
	   ;; 

    0.1.11) echo  "Plot summary with data..."
	   ./python/plt_summary.py hist 
	   ;;

    0.2) echo "Running on con3650 data..."
	 ;;

    0.2.1) echo "Split con3650 data sample with each group 20G ..."
	   mkdir run/samples/data3650 
	   ./python/get_samples.py  /bes3fs/offline/data/664-1/3650/dst $HOME/bes/jpsi2invi/v0.1/run/samples/data3650/data_663p01_3650.txt 20G
	    # made 84 groups 
	    ;;

    0.2.2) echo "Generate Condor jobs on con3650 data ---- 1..."
	    mkdir run/jpsi2invi/job_text/data3650
	    mkdir run/jpsi2invi/rootfile_data3650  
	    cd run/jpsi2invi/gen_script
		./make_jobOption_file_data3650.sh
		cd ../job_text/data3650
		mv jobOptions_jpsi2invi_data3650-84.txt jobOptions_jpsi2invi_data3650-0.txt
	    cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.2.3) echo "test for data3650" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/data3650/jobOptions_jpsi2invi_data3650-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/data3650
            boss.exe jobOptions_jpsi2invi_data3650-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.2.4) echo "Submit Condor jobs on data ---- 2..." 
	    cd run/jpsi2invi/job_text/data3650
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		boss.condor -g physics -n 84 jobOptions_jpsi2invi_data3650-%{ProcId}.txt
	    cd 
	    cd bes/jpsi2invi/v0.1
		;;

    0.2.5) echo "Check Condor jobs on con3650 data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/rootfile_data3650  84 
	   ;;

    0.2.6) echo  "Generate selection Condor jobs on con3650 data ---- 1..."
	   mkdir run/jpsi2invi/event_data3650
	   mkdir run/jpsi2invi/job_text/data3650_event
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_data3650_event.sh
	   cd ../job_text/data3650_event
	   mv jobOptions_jpsi2invi_data3650_event-84.sh jobOptions_jpsi2invi_data3650_event-0.sh
	   chmod 755 jobOptions_jpsi2invi_data3650_event-*
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.2.7) echo "test for data event" 
		cd run/jpsi2invi/job_text/data3650_event
		./jobOptions_jpsi2invi_data3650_event-0.sh
		cd $HOME/bes/jpsi2invi/v0.1
        ;;

    0.2.8) echo "Submit selection Condor jobs on con3650 data ---- 2..." 
	    cd run/jpsi2invi/job_text/data3650_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm
 		rm ../../event_data3650/jpsi2invi_data3650_event-*		
	    hep_sub -g physics -n 84 jobOptions_jpsi2invi_data3650_event-%{ProcId}.sh
	    ;; 
    
	0.2.9)echo "Check event Condor jobs on con3650 data..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_data3650 11
	   ;;
    
	0.2.10) echo  "Merge event root file on con3650 data..."
	   mkdir run/jpsi2invi/hist_data3650
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_data3650 run/jpsi2invi/hist_data3650
	   ;; 

    0.2.11) echo  "Plot summary with data and con3650..."
	   mkdir run/jpsi2invi/hist_data3650
	   ./python/plt_summary.py data3650 
	   ;;

    0.3) echo "Running on data for jpsi2incl..."
	 ;;

    0.3.2) echo "Generate Submit Condor jobs on data for incl..." 
	   mkdir -p run/jpsi2incl/job_text/Data12
	   mkdir -p run/jpsi2incl/rootfile
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_Data12_jpsi2invi.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2incl_data_psip_data12-633.txt jobOptions_jpsi2incl_data_psip_data12-0.txt
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.3.3) echo "test for data for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/Data12/jobOptions_jpsi2incl_data_psip_data12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/Data12
            boss.exe jobOptions_jpsi2incl_data_psip_data12-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.3.4) echo "Submit Condor jobs on data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/Data12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	    rm ../../rootfile/jpsi2incl_data_psip_data12-*	
	    boss.condor -g physics -n 633 jobOptions_jpsi2incl_data_psip_data12-%{ProcId}.txt
	    ;;

    0.3.5) echo "Check Condor jobs on data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile  633
	   ;;
    
    0.3.6) echo "Generate Submit selection Condor jobs on data for incl ---- 1..."
	   mkdir run/jpsi2incl/event
	   mkdir run/jpsi2incl/job_text/Data12_event
	   cd run/jpsi2incl/gen_script
	   rm ../job_text/Data12_event/jobOptions_jpsi2incl_data_psip_data12_event-*
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2incl_data_psip_data12_event-633.sh jobOptions_jpsi2incl_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2incl_data_psip_data12_event-*
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.3.7) echo "Test for data event for incl" 
		cd run/jpsi2incl/job_text/Data12_event
		./jobOptions_jpsi2incl_data_psip_data12_event-0.sh
		cd $HOME/bes/jpsi2invi/v0.1
        ;;

    0.3.8) echo "Submit selection Condor jobs on data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/Data12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../event/jpsi2incl_data_psip_data12_event-*
	    hep_sub -g physics -n 633 jobOptions_jpsi2incl_data_psip_data12_event-%{ProcId}.sh
	    cd 
	    cd bes/jpsi2invi/v0.1
	    ;;

    0.3.9) echo "Check Condor jobs on events data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event  633
	   ;;

    0.3.10) echo  "Merge event root file on data for incl..."
	   mkdir run/jpsi2incl/hist
	   rm run/jpsi2incl/hist/jpsi2incl_data_psip_data12_event_merged_1.root
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event run/jpsi2incl/hist
	   ;; 

    0.3.11) echo  "Plot summary with data for incl..."
	   ./python/plt_summary.py hist_incl 
	   ;; 
	
    0.4) echo "Running on data for jpsi2lplm..."
	 ;;
	
     0.4.2) echo "Generate Condor jobs on data for lplm ---- 1 ..." 
	   mkdir -p run/jpsi2lplm/job_text/Data12
	   mkdir -p run/jpsi2lplm/rootfile
	   cd run/jpsi2lplm/gen_script
	   ./make_jobOption_file_Data12_jpsi2lplm.sh
	   cd ../job_text/Data12
	   mv jobOptions_jpsi2lplm_data_psip_data12-633.txt jobOptions_jpsi2lplm_data_psip_data12-0.txt
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    0.4.3) echo "test for data for lplm" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2lplm/job_text/Data12/jobOptions_jpsi2lplm_data_psip_data12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2lplm/job_text/Data12
            boss.exe jobOptions_jpsi2lplm_data_psip_data12-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.4.4) echo "Submit Condor jobs on data for lplm ---- 2..." 
	    cd run/jpsi2lplm/job_text/Data12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
	    boss.condor -g physics -n 633 jobOptions_jpsi2lplm_data_psip_data12-%{ProcId}.txt
	    ;;

     0.4.5) echo "Check Condor jobs on data for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/rootfile  633
	   ;;
    
     0.4.6) echo "Submit selection Condor jobs on data for lplm..."
	   mkdir run/jpsi2lplm/event
	   mkdir run/jpsi2lplm/job_text/Data12_event
	   cd run/jpsi2lplm/gen_script
	   ./make_jobOption_file_Data12_event.sh
	   cd ../job_text/Data12_event
	   mv jobOptions_jpsi2lplm_data_psip_data12_event-633.sh jobOptions_jpsi2lplm_data_psip_data12_event-0.sh
       chmod 755 jobOptions_jpsi2lplm_data_psip_data12_event-*
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

 	0.4.7) echo "Test for data event for lplm" 
		cd run/jpsi2lplm/job_text/Data12_event
		./jobOptions_jpsi2lplm_data_psip_data12_event-0.sh
		cd $HOME/bes/jpsi2invi/v0.1
		;;

	0.4.8) echo "Submit selection Condor jobs on data for lplm ---- 2..." 
		cd run/jpsi2lplm/job_text/Data12_event
		find . -name "*.out.*" | xargs rm
		find . -name "*.err.*" | xargs rm	   
	    rm ../../event/jpsi2lplm_data_psip_data12_event-*
		hep_sub -g physics -n 633 jobOptions_jpsi2lplm_data_psip_data12_event-%{ProcId}.sh
	    cd 
	    cd bes/jpsi2invi/v0.1
	    ;;

     0.4.9) echo "Check Condor jobs on events data for lplm..."
	   ./python/chk_condorjobs.py run/jpsi2lplm/event  633
	   ;;

     0.4.10) echo  "Merge event root file on data for lplm..."
	   mkdir run/jpsi2lplm/hist
	   ./python/mrg_rootfiles.py  run/jpsi2lplm/event run/jpsi2lplm/hist
	   ;; 

     0.4.11) echo  "Plot summary with data for lplm..."
	   ./python/plt_summary.py hist_lplm 
	   ;; 


    0.7) echo "Running on con3650 data for jpsi2incl..."
	 ;;

    0.7.2) echo "Generate Condor jobs on con3650 data for incl---- 1..."
	    mkdir run/jpsi2incl/job_text/data3650
	    mkdir run/jpsi2incl/rootfile_data3650  
	    cd run/jpsi2incl/gen_script
		./make_jobOption_file_data3650.sh
		cd ../job_text/data3650
		mv jobOptions_jpsi2incl_data3650-84.txt jobOptions_jpsi2incl_data3650-0.txt
	   ;;

    0.7.3) echo "test for data3650 for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/data3650/jobOptions_jpsi2incl_data3650-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/data3650
            boss.exe jobOptions_jpsi2incl_data3650-0.txt
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    0.7.4) echo "Submit Condor jobs on data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/data3650
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	
        rm ../../rootfile_data3650/jpsi2incl_data3650-
		boss.condor -g physics -n 84 jobOptions_jpsi2incl_data3650-%{ProcId}.txt
		;;

    0.7.5) echo "Check Condor jobs on con3650 data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_data3650  84 
	   ;;

    0.7.6) echo  "Generate selection Condor jobs on con3650 data for incl ---- 1..."
	   mkdir run/jpsi2incl/event_data3650
	   mkdir run/jpsi2incl/job_text/data3650_event
	   cd run/jpsi2incl/gen_script
       rm ../job_text/data3650_event/jobOptions_jpsi2incl_data3650_event-*
	   ./make_jobOption_file_data3650_event.sh
	   cd ../job_text/data3650_event
	   mv jobOptions_jpsi2incl_data3650_event-84.sh jobOptions_jpsi2incl_data3650_event-0.sh
	   chmod 755 jobOptions_jpsi2incl_data3650_event-*
	   ;;

    0.7.7) echo "test for data event for incl" 
		cd run/jpsi2incl/job_text/data3650_event
		./jobOptions_jpsi2incl_data3650_event-0.sh
        ;;

    0.7.8) echo "Submit selection Condor jobs on con3650 data for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/data3650_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm
 		rm ../../event_data3650/jpsi2incl_data3650_event-*		
	    hep_sub -g physics -n 84 jobOptions_jpsi2incl_data3650_event-%{ProcId}.sh
	    ;; 
    
	0.7.9)echo "Check event Condor jobs on con3650 data for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_data3650 84
	   ;;
    
	0.7.10) echo  "Merge event root file on con3650 data for incl..."
	   mkdir run/jpsi2incl/hist_data3650
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_data3650 run/jpsi2incl/hist_data3650
	   ;; 



    # --------------------------------------------------------------------------
    #  MC Sample 
    # --------------------------------------------------------------------------
    
    1.1) echo "Running on MC sample..."
	 ;;

    1.1.1) echo "Split psi(2S) MC sample with each group 20G ..."
	   ./python/get_samples.py  /bes3fs/offline/data/664p03/psip/12mc/dst $HOME/bes/jpsi2invi/v0.1/run/samples/mc_664p03_psip_12mc.txt 20G
	   # made 394 groups 
	   ;;

    1.1.2) echo "Generate Condor jobs on psi(2S) MC sample ---- 1..."
	   mkdir -p run/jpsi2invi/job_text/mc12
	   mkdir -p run/jpsi2invi/rootfile_mc12
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc12_jpsi2invi.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2invi_psip_mc12-394.txt jobOptions_jpsi2invi_psip_mc12-0.txt
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    1.1.3) echo "Test for psi(2S) MC sample" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2invi/job_text/mc12/jobOptions_jpsi2invi_psip_mc12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2invi/job_text/mc12
            boss.exe jobOptions_jpsi2invi_psip_mc12-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.1.4) echo "Submit Condor jobs on psi(2S) MC sample ---- 2..." 
	    cd run/jpsi2invi/job_text/mc12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	   boss.condor -g physics -n 394 jobOptions_jpsi2invi_psip_mc12-%{ProcId}.txt 
	   cd 
	   cd bes/jpsi2invi/v0.1
	   ;;

    1.1.5) echo "Check Condor jobs on psi(2S) MC sample..."
	   ./python/chk_condorjobs.py $HOME/bes/jpsi2invi/v0.1/run/jpsi2invi/rootfile_mc12  394 
	   ;;

    1.1.6) echo "Generate selection Condor jobs on psi(2S) MC sample ---- 1..."
	   mkdir run/jpsi2invi/event_mc12
	   mkdir run/jpsi2invi/job_text/mc12_event  
	   cd run/jpsi2invi/gen_script
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2invi_psip_mc12_event-394.sh jobOptions_jpsi2invi_psip_mc12_event-0.sh
	   chmod 755 jobOptions_jpsi2invi_psip_mc12_event-*
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    1.1.7) echo "Test for psi(2S) MC sample event" 
		cd run/jpsi2invi/job_text/mc12_event
		./jobOptions_jpsi2invi_psip_mc12_event-0.sh
		cd $HOME/bes/jpsi2invi/v0.1
        ;;

    1.1.8) echo "Submit selection Condor jobs on psi(2S) MC sample ---- 2..." 
	    cd run/jpsi2invi/job_text/mc12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   
		rm ../../event_mc12/jpsi2invi_psip_mc12_event-*
	    hep_sub -g physics -n 394 jobOptions_jpsi2invi_psip_mc12_event-%{ProcId}.sh
	    ;;

    1.1.9) echo "Check events selection jobs on psi(2S) MC sample..."
	   ./python/chk_condorjobs.py run/jpsi2invi/event_mc12  394 
	   ;;

    1.1.10) echo  "Merge events files..."
	   mkdir run/jpsi2invi/hist_mc12
	   ./python/mrg_rootfiles.py  run/jpsi2invi/event_mc12 run/jpsi2invi/hist_mc12
	   ;; 

    1.1.11) echo  "Plot summary with data and psip(2S) MC sample..."
	   ./python/plt_summary.py mc12
	   ;; 

    1.3) echo "Running on psip(2S) MC sample for jpsi2incl..."
	 ;;

    1.3.2) echo "Generate Condor jobs on psip(2S) MC sample for incl..." 
	   mkdir -p run/jpsi2incl/job_text/mc12
	   mkdir -p run/jpsi2incl/rootfile_mc12
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc12_jpsi2incl.sh
	   cd ../job_text/mc12
	   mv jobOptions_jpsi2incl_psip_mc12-394.txt jobOptions_jpsi2incl_psip_mc12-0.txt
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    1.3.3) echo "test for psip(2S) MC sample for incl" 
        echo "have you changed test number?(yes / no)
        ./run/jpsi2incl/job_text/mc12/jobOptions_jpsi2incl_psip_mc12-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/jpsi2incl/job_text/mc12
            boss.exe jobOptions_jpsi2incl_psip_mc12-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.3.4) echo "Submit Condor jobs on psip(2S) MC sample for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/mc12
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	  
	   rm ../../rootfile_mc12/jpsi2incl_psip_mc12-*	
	   boss.condor -g physics -n 394 jobOptions_jpsi2incl_psip_mc12-%{ProcId}.txt
	   ;;

    1.3.5) echo "Check Condor jobs on psip(2S) MC sample for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/rootfile_mc12  394
	   ;;
    
    1.3.6) echo "Generate selection Condor jobs on psip(2S) MC sample for incl..."
	   mkdir run/jpsi2incl/event_mc12
	   mkdir run/jpsi2incl/job_text/mc12_event
	   cd run/jpsi2incl/gen_script
	   ./make_jobOption_file_mc12_event.sh
	   cd ../job_text/mc12_event
	   mv jobOptions_jpsi2incl_psip_mc12_event-394.sh jobOptions_jpsi2incl_psip_mc12_event-0.sh
       chmod 755 jobOptions_jpsi2incl_psip_mc12_event-*
	   cd $HOME/bes/jpsi2invi/v0.1
	   ;;

    1.3.7) echo "Test for psip(2S) MC sample event for incl" 
		cd run/jpsi2incl/job_text/mc12_event
		./jobOptions_jpsi2incl_psip_mc12_event-0.sh
		cd $HOME/bes/jpsi2invi/v0.1
        ;;

    1.3.8) echo "Submit selection Condor jobs on psip(2S) MC sample for incl ---- 2..." 
	    cd run/jpsi2incl/job_text/mc12_event
        find . -name "*.out.*" | xargs rm
        find . -name "*.err.*" | xargs rm	   	   
	   hep_sub -g physics -n 394 jobOptions_jpsi2incl_psip_mc12_event-%{ProcId}.sh
	   cd 
	   cd bes/jpsi2invi/v0.1
	   ;;

    1.3.9) echo "Check Condor jobs on events psip(2S) MC sample for incl..."
	   ./python/chk_condorjobs.py run/jpsi2incl/event_mc12  394
	   ;;

    1.3.10) echo  "Merge event root file on psip(2S) MC sample for incl..."
	   mkdir run/jpsi2incl/hist_mc12
	   ./python/mrg_rootfiles.py  run/jpsi2incl/event_mc12 run/jpsi2incl/hist_mc12
	   ;; 

    1.3.11) echo  "Plot summary with psip(2S) MC sample for incl..."
	   ./python/plt_summary.py mc12_incl 
	   ;; 
	
    1.5) echo "Running on generated MC sample..."
	 ;;

    1.5.3) echo "test for generated MC sample" 
        echo "have you changed test number?(yes / no)
        ./run/gen_mc/jpsi2ee/job_text/jobs/jobOptions_jpsi2invi_gen_mc_ee-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/gen_mc/jpsi2ee/job_text/jobs
            boss.exe jobOptions_jpsi2invi_gen_mc_ee-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.5.4) echo "Submit Condor jobs on generated MC sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu/gen_mc_mumu_jpsi2invi-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2invi_gen_mc_mumu-%{ProcId}.txt
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_ee/gen_mc_ee_jpsi2invi-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2invi_gen_mc_ee-%{ProcId}.txt
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nn/gen_mc_nn_jpsi2invi-1.root
	    boss.condor -g physics jobOptions_jpsi2invi_gen_mc_nn-1.txt
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_pp/gen_mc_pp_jpsi2invi-*
	    boss.condor -g physics -n 2 jobOptions_jpsi2invi_gen_mc_pp-%{ProcId}.txt
	   ;;

    1.5.5) echo "Check Condor jobs on generated MC sample..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu/job_text/rootfile_mumu  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee/job_text/rootfile_ee  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn/job_text/rootfile_nn  1
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp/job_text/rootfile_pp  2
	   ;;

    1.5.7) echo "Test for generated MC sample event" 
		./python/sel_events.py run/gen_mc/jpsi2ee/job_text/rootfile_ee/gen_mc_ee_jpsi2invi-1.root run/gen_mc/jpsi2ee/job_text/event_ee/invi/jpsi2invi_gen_mc_ee_event-1.root
        ;;

    1.5.8) echo "Submit selection Condor jobs on generated MC sample ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu/invi/jpsi2invi_gen_mc_mumu_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2invi_gen_mc_mumu_event-%{ProcId}.sh
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_ee/invi/jpsi2invi_gen_mc_ee_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2invi_gen_mc_ee_event-%{ProcId}.sh
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nn/invi/jpsi2invi_gen_mc_nn_event-1.root
	    hep_sub -g physics jobOptions_jpsi2invi_gen_mc_nn_event-1.sh
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_pp/invi/jpsi2invi_gen_mc_pp_event-*
	    hep_sub -g physics -n 2 jobOptions_jpsi2invi_gen_mc_pp_event-%{ProcId}.sh
	   ;;

    1.5.10) echo  "Merge event root file on generated MC sample..."
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu/job_text/event_mumu/invi run/gen_mc/jpsi2mumu/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2ee/job_text/event_ee/invi run/gen_mc/jpsi2ee/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nn/job_text/event_nn/invi run/gen_mc/jpsi2nn/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2pp/job_text/event_pp/invi run/gen_mc/jpsi2pp/job_text/hist
	   ;;

    1.6) echo "Running on generated MC sample for incl..."
	 ;;

    1.6.3) echo "test for generated MC sample for incl" 
        echo "have you changed test number?(yes / no)
        ./run/gen_mc/jpsi2ee/job_text/jobs/jobOptions_jpsi2incl_gen_mc_ee-0.txt"
        read opt
        if [ $opt == "yes" ]
            then
            echo "now in yes"  
            cd run/gen_mc/jpsi2ee/job_text/jobs
            boss.exe jobOptions_jpsi2incl_gen_mc_ee-0.txt
            cd $HOME/bes/jpsi2invi/v0.1
        else
            echo "Default value is 'no', please change test number."
        fi
        ;;

    1.6.4) echo "Submit Condor jobs on generated MC sample for incl ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_mumu/gen_mc_mumu_jpsi2incl-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2incl_gen_mc_mumu-%{ProcId}.txt
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_ee/gen_mc_ee_jpsi2incl-*
	    boss.condor -g physics -n 3 jobOptions_jpsi2incl_gen_mc_ee-%{ProcId}.txt
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_nn/gen_mc_nn_jpsi2incl-1.root
	    boss.condor -g physics jobOptions_jpsi2incl_gen_mc_nn-1.txt
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.txt.*" | xargs rm	   
        rm ../rootfile_pp/gen_mc_pp_jpsi2incl-*
	    boss.condor -g physics -n 2 jobOptions_jpsi2incl_gen_mc_pp-%{ProcId}.txt
	   ;;

    1.6.5) echo "Check Condor jobs on generated MC sample for incl..."
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2mumu/job_text/rootfile_mumu  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2ee/job_text/rootfile_ee  3
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2nn/job_text/rootfile_nn  1
	   ./python/chk_condorjobs.py run/gen_mc/jpsi2pp/job_text/rootfile_pp  2
	   ;;

    1.6.7) echo "Test for generated MC sample event for incl" 
		./python/sel_events_inclusive.py run/gen_mc/jpsi2ee/job_text/rootfile_ee/gen_mc_ee_jpsi2incl-1.root run/gen_mc/jpsi2ee/job_text/event_ee/incl/jpsi2incl_gen_mc_ee_event-1.root
        ;;

    1.6.8) echo "Submit selection Condor jobs on generated MC sample for incl ---- 2..." 
	    cd run/gen_mc/jpsi2mumu/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_mumu/incl/jpsi2incl_gen_mc_mumu_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2incl_gen_mc_mumu_event-%{ProcId}.sh
        cd ../../../jpsi2ee/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_ee/incl/jpsi2incl_gen_mc_ee_event-*
	    hep_sub -g physics -n 3 jobOptions_jpsi2incl_gen_mc_ee_event-%{ProcId}.sh
        cd ../../../jpsi2nn/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_nn/incl/jpsi2incl_gen_mc_nn_event-1.root
	    hep_sub -g physics jobOptions_jpsi2incl_gen_mc_nn_event-1.sh
        cd ../../../jpsi2pp/job_text/jobs
        find . -name "*.sh.*" | xargs rm
        rm ../event_pp/incl/jpsi2incl_gen_mc_pp_event-*
	    hep_sub -g physics -n 2 jobOptions_jpsi2incl_gen_mc_pp_event-%{ProcId}.sh
	   ;;

    1.6.10) echo  "Merge event root file on generated MC sample for incl..."
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2mumu/job_text/event_mumu/incl run/gen_mc/jpsi2mumu/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2ee/job_text/event_ee/incl run/gen_mc/jpsi2ee/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2nn/job_text/event_nn/incl run/gen_mc/jpsi2nn/job_text/hist
	   ./python/mrg_rootfiles.py  run/gen_mc/jpsi2pp/job_text/event_pp/incl run/gen_mc/jpsi2pp/job_text/hist
	   ;;


esac

