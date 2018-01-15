#!/bin/bash

JobText_SaveDir=../job_text/data3650_event

for num in {1..84}
do
    jobOptions=jobOptions_jpsi2invi_data3650_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py run/jpsi2invi/rootfile_data3650/jpsi2invi_data3650-${num}.root run/jpsi2invi/event_data3650/jpsi2invi_data3650_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}

done

