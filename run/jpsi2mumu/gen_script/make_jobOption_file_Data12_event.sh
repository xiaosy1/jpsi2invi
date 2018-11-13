#!/bin/bash

JobText_SaveDir=../job_text/Data12_event

for num in {1..633}
do
    jobOptions=jobOptions_jpsi2incl_data_psip_data12_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_inclusive.py run/jpsi2incl/rootfile/jpsi2incl_data_psip_data12-${num}.root run/jpsi2incl/event/jpsi2incl_data_psip_data12_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

