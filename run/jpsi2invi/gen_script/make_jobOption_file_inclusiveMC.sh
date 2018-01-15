#!/bin/bash

JobText_SaveDir=./

for num in {1..3}
do
    file_list=data_664p03_psip_20G-${num}.txt
    rootfile=chic2invi_data_psip_mc-${num}.root
    jobOptions=jobOptions_chic2invi_inclusive_psip_mc-${num}.txt
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_ReadRec.txt\"        "  > ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$VERTEXFITROOT/share/jobOptions_VertexDbSvc.txt\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MAGNETICFIELDROOT/share/MagneticField.txt\"      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ABSCORROOT/share/jobOptions_AbsCor.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$HOME/bes/chic2invi/v0.1/run/samples/$file_list\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.DLLs += {\"Chic2invi\"};                       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.TopAlg += { \"Chic2invi\" };                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//Input REC or DST file name                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "EventCnvSvc.digiRootInputFile = {                             " >> ${JobText_SaveDir}/${jobOptions}
    echo   "\"/besfs/groups/nphy/users/xiaosy/bes/jpsi2invi/v0.1/run/jpsi2invi/rootfile/jpsi2invi_data_psip_data12-${num}.root\"                     " >> ${JobText_SaveDir}/${jobOptions}
    echo   "};                                                            " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL ) " >> ${JobText_SaveDir}/${jobOptions}
    echo   "MessageSvc.OutputLevel = 5;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Number of events to be processed (default is 10)           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//ApplicationMgr.EvtMax = 5000;                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.EvtMax = -1;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "Chic2invi.IsMonteCarlo=\"true\";                             " >> ${JobText_SaveDir}/${jobOptions}
    echo   "Chic2invi.OutputFileName=\"/besfs/groups/nphy/users/xiaosy/bes/chic2invi/v0.1/run/chic2invi/inclusiveMC/$rootfile\"; " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

