#!/bin/bash

JobText_SaveDir=job_text/jobs/

for num in {1..15}
do
    jobOptions=jobOptions_jpsi2any_09_gen_mc_invi_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py run/gen_mc/jpsi2any_09/job_text/rootfile_invi_09/gen_mc_any_09_invi-${num}.root run/gen_mc/jpsi2any_09/job_text/event_any_09/invi/jpsi2invi_gen_mc_any_09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

