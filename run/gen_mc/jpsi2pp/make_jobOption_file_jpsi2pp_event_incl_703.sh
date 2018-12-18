#!/bin/bash

JobText_SaveDir=job_text/jobs703

for num in {1..11}
do
    jobOptions=jobOptions_jpsi2incl_gen_mc_pp_event_703-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd \$HOME/bes/jpsi2invi/v0.1                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_inclusive.py run/gen_mc/jpsi2pp/job_text/rootfile_pp_703/gen_mc_pp_jpsi2incl_703-${num}.root run/gen_mc/jpsi2pp/job_text/event_pp_703/incl/jpsi2incl_gen_mc_pp_event_703-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

