#!/bin/bash

JobText_SaveDir=../job_text/Data12_event

for num in {1..633}
do
    jobOptions=jobOptions_jpsi2lplm_data_psip_data12_event-${num}.sh
    echo   " #!/bin/bash                                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "cd ../../../../                                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "./python/sel_events_lplm.py run/jpsi2lplm/rootfile/jpsi2lplm_data_psip_data12-${num}.root run/jpsi2lplm/event/jpsi2lplm_data_psip_data12_event-${num}.root                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

