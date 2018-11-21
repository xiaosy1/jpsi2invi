#!/bin/bash

JobText_SaveDir=../job_text/data09_evtflw

for num in {1..314}
do
    jobOptions=jobOptions_jpsi2invi_data_psip_data09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_evtflw.py run/jpsi2invi/rootfile_data09/jpsi2invi_data_psip_data09-${num}.root run/jpsi2invi/evtflw_data09/jpsi2invi_data_psip_data09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

