#!/bin/bash

JobText_SaveDir=../job_text/data09_event

for num in {1..314}
do
    jobOptions=jobOptions_jpsi2lplm_data_psip_data09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_lplm.py run/jpsi2lplm/rootfile_data09/jpsi2lplm_data_psip_data09-${num}.root run/jpsi2lplm/event_data09/jpsi2lplm_data_psip_data09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

