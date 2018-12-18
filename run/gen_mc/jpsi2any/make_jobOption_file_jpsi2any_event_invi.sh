#!/bin/bash

JobText_SaveDir=job_text/jobs/event/

for num in {1..15}
do
    jobOptions=jobOptions_jpsi2any_gen_mc_invi_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py run/gen_mc/jpsi2any/job_text/rootfile_invi/mc12_any_jpsi2invi-${num}.root run/gen_mc/jpsi2any/job_text/event_any/invi/jpsi2invi_gen_mc_any_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

