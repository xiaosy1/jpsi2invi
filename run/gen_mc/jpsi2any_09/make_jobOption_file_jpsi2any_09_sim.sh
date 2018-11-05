#!/bin/bash

JobText_SaveDir=job_text/sim

for num in {1..300}
do
    rtrawfile=jpsi2any_sim-${num}.rtraw
    rndmseed=`expr ${num} + 1000`
	jobOptions=jobOptions_sim-${num}.txt
    echo   "//DENG Zi-yan 2008-03-17                                      " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$OFFLINEEVENTLOOPMGRROOT/share/OfflineEventLoopMgr_Option.txt\"                                                                                                     " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//*************job options for generator (KKMC)*************  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$KKMCROOT/share/jobOptions_KKMC.txt\"                " >> ${JobText_SaveDir}/${jobOptions}
    echo   "KKMC.CMSEnergy = 3.686;                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "KKMC.BeamEnergySpread=0.0008;                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "KKMC.NumberOfEventPrinted=1;                                  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "KKMC.GeneratePsiPrime=true;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//*************job options for EvtGen***************          " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$BESEVTGENROOT/share/BesEvtGen.txt\"                 " >> ${JobText_SaveDir}/${jobOptions}
    echo   "EvtDecay.userDecayTableName = \"\$HOME/bes/jpsi2invi/v0.1/run/gen_mc/jpsi2any_09/any.dec\";             " >> ${JobText_SaveDir}/${jobOptions}
    echo   "EvtDecay.PdtTableDir = \"\$HOME/bes/jpsi2invi/v0.1/run/gen_mc/mypdt.table\";                       " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//**************job options for random number***************  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "BesRndmGenSvc.RndmSeed = $rndmseed;                                 " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//**************job options for detector simulation*********  " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$BESSIMROOT/share/G4Svc_BesSim.txt\"                 " >> ${JobText_SaveDir}/${jobOptions}
    echo   "//configure for calibration constants                         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$CALIBSVCROOT/share/calibConfig_sim.txt\"            " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// run ID                                                     " >> ${JobText_SaveDir}/${jobOptions}
    echo   "RealizationSvc.RunIdList = {-9025,0,-8093};                           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "#include \"\$ROOTIOROOT/share/jobOptions_Digi2Root.txt\"         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "RootCnvSvc.digiRootOutputFile = \"../rtraw/any-${num}.rtraw\";                         " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Set output level threshold (2=DEBUG, 3=INFO, 4=WARNING, 5=ERROR, 6=FATAL ) " >> ${JobText_SaveDir}/${jobOptions}
    echo   "MessageSvc.OutputLevel = 5;                                   " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
    echo   "// Number of events to be processed (default is 10)           " >> ${JobText_SaveDir}/${jobOptions}
    echo   "ApplicationMgr.EvtMax = 10000;                               " >> ${JobText_SaveDir}/${jobOptions}
    echo   "                                                              " >> ${JobText_SaveDir}/${jobOptions}
done

