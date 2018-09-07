#!/bin/bash

JobText_SaveDir=../job_text/data09_event

for num in {1..314}
do
    jobOptions=jobOptions_jpsi2incl_data_psip_data09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_inclusive.py run/jpsi2incl/rootfile_data09/jpsi2incl_data_psip_data09-${num}.root run/jpsi2incl/event_data09/jpsi2incl_data_psip_data09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done