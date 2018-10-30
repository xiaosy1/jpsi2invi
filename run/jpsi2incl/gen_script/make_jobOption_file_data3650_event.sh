#!/bin/bash

JobText_SaveDir=../job_text/data3650_event

for num in {1..84}
do
    jobOptions=jobOptions_jpsi2incl_data3650_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_inclusive.py run/jpsi2incl/rootfile_data3650/jpsi2incl_data3650-${num}.root run/jpsi2incl/event_data3650/jpsi2incl_data3650_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

