#!/bin/bash

JobText_SaveDir=../job_text/mc12_event

for num in {1..394}
do
    jobOptions=jobOptions_jpsi2lplm_psip_mc12_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_lplm.py run/jpsi2lplm/rootfile_mc12/jpsi2lplm_psip_mc12-${num}.root run/jpsi2lplm/event_mc12/jpsi2lplm_psip_mc12_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

