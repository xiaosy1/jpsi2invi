#!/bin/bash

JobText_SaveDir=../job_text/mc12_evtflw

for num in {1..394}
do
    jobOptions=jobOptions_jpsi2invi_psip_mc12_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_evtflw.py run/jpsi2invi/rootfile_mc12/jpsi2invi_psip_mc12-${num}.root run/jpsi2invi/evtflw_mc12/jpsi2invi_psip_mc12_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

