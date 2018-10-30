#!/bin/bash

JobText_SaveDir=../job_text/data09

for num in {1..314}
do
    file_list=data_664-1_psip_20G-${num}.txt
    rootfile=jpsi2incl_data_psip_data09-${num}.root
    jobOptions=jobOptions_jpsi2incl_data_psip_data09-${num}.txt
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_ReadRec.txt\"        "  > ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MAGNETICFIELDROOT/share/MagneticField.txt\"      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ABSCORROOT/share/jobOptions_AbsCor.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$HOME/bes/jpsi2invi/v0.1/run/samples/data09/$file_list\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.DLLs += {\"Jpsi2incl\"};                       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.TopAlg += { \"Jpsi2incl\" };                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL ) " >> ${JobText_SaveDir}/${jobOptions}
    echo   "MessageSvc.OutputLevel = 5;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Number of events to be processed (default is 10)           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//ApplicationMgr.EvtMax = 5000;                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.EvtMax = -1;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "Jpsi2incl.IsMonteCarlo=\"false\";                             " >> ${JobText_SaveDir}/${jobOptions}
    echo   "Jpsi2incl.OutputFileName=\"/besfs/groups/nphy/users/xiaosy/bes/jpsi2invi/v0.1/run/jpsi2incl/rootfile_data09/$rootfile\"; " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

