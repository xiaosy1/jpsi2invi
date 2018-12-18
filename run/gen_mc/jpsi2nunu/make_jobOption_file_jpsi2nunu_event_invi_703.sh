#!/bin/bash

JobText_SaveDir=job_text/jobs703

for num in {1..2}
do
    jobOptions=jobOptions_jpsi2invi_gen_mc_nunu_event_703-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events.py run/gen_mc/jpsi2nunu/job_text/rootfile_nunu_703/gen_mc_nunu_jpsi2invi_703-${num}.root run/gen_mc/jpsi2nunu/job_text/event_nunu_703/invi/jpsi2invi_gen_mc_nunu_event_703-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

