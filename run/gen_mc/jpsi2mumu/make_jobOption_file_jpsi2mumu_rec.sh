#!/bin/bash

JobText_SaveDir=job_text/rec

for num in {1..300}
do
    dstfile=jpsi2mumu_rec-${num}.dst
	rndmseed=`expr ${num} + 1000`
	jobOptions=jobOptions_rec_mumu-${num}.txt
    echo   "//input ROOT MC data                                          " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_ReadRoot.txt\"          " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$OFFLINEEVENTLOOPMGRROOT/share/OfflineEventLoopMgr_Option.txt\"                                                                                                     " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// background mixing                                          " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$BESEVENTMIXERROOT/share/jobOptions_EventMixer_rec.txt\"                                                                                                            " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$CALIBSVCROOT/share/job-CalibData.txt\"              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MAGNETICFIELDROOT/share/MagneticField.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ESTIMEALGROOT/share/job_EsTimeAlg.txt\"             " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// PAT+TSF method for MDC reconstruction                      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MDCXRECOROOT/share/jobOptions_MdcPatTsfRec.txt\"    " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$KALFITALGROOT/share/job_kalfit_numf_data.txt\"      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MDCDEDXALGROOT/share/job_dedx_all.txt\"             " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$TRKEXTALGROOT/share/TrkExtAlgOption.txt\"           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$TOFRECROOT/share/jobOptions_TofRec.txt\"            " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$TOFENERGYRECROOT/share/TofEnergyRecOptions_MC.txt\" " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$EMCRECROOT/share/EmcRecOptions.txt\"                " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$MUCRECALGROOT/share/jobOptions_MucRec.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$EVENTASSEMBLYROOT/share/EventAssembly.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$PRIMARYVERTEXALGROOT/share/jobOptions_kalman.txt\"  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$VEEVERTEXALGROOT/share/jobOptions_veeVertex.txt\"   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$HLTMAKERALGROOT/share/jobOptions_HltMakerAlg.txt\"  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$EVENTNAVIGATORROOT/share/EventNavigator.txt\"       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//output ROOT REC data                                        " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_Dst2Root.txt\"          " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//configure of calibration constants for MC                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$CALIBSVCROOT/share/calibConfig_rec_mc.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//**************job options for random number*************    ">> ${JobText_SaveDir}/${jobOptions}
    echo   "BesRndmGenSvc.RndmSeed = $rndmseed;                           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL )                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "MessageSvc.OutputLevel = 5;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
	echo   "//ROOT input data file                                        " >> ${JobText_SaveDir}/${jobOptions}
    echo   "EventCnvSvc.digiRootInputFile = {\"../rtraw/mumu-${num}.rtraw\"};                 " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
	echo   "//ROOT output data file                                       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "EventCnvSvc.digiRootOutputFile =\"../dst/mumu-${num}.dst\";                     " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Number of events to be processed (default is 10)           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.EvtMax = -1;                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

