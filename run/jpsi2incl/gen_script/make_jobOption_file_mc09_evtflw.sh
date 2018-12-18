#!/bin/bash

JobText_SaveDir=../job_text/mc09_event

for num in {1..106}
do
    jobOptions=jobOptions_jpsi2incl_psip_mc09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_evtflw.py run/jpsi2incl/rootfile_mc09/jpsi2incl_psip_mc09-${num}.root run/jpsi2incl/event_mc09/jpsi2incl_psip_mc09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

