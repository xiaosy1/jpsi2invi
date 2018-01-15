#!/bin/bash

JobText_SaveDir=job_text/jobs

for num in {1..2}
do
    jobOptions=jobOptions_jpsi2invi_gen_mc_pp_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py run/gen_mc/jpsi2pp/job_text/rootfile_pp/gen_mc_pp_jpsi2invi-${num}.root run/gen_mc/jpsi2pp/job_text/event_pp/invi/jpsi2invi_gen_mc_pp_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

