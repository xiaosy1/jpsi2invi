#!/bin/bash

JobText_SaveDir=job_text/jobs

for num in {1..6}
do
    jobOptions=jobOptions_jpsi2geta_gen_mc_geta_09_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_geta.py run/gen_mc/jpsi2geta_09/job_text/rootfile_geta_09/gen_mc_geta_09_jpsi2geta-${num}.root run/gen_mc/jpsi2geta_09/job_text/event_geta_09/geta/jpsi2geta_gen_mc_geta_09_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

