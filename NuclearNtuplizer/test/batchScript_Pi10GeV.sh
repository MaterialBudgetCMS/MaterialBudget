#!/bin/bash
#BSUB -q 8nm

REMOTEDIR=/afs/cern.ch/work/k/kropiv/Tracker/CMSSW_10_1_6/src/MaterialBudget/NuclearNtuplizer/test

cd $REMOTEDIR

eval `scramv1 ru -sh`

rm out_Pi10GeV.txt

cmsRun $REMOTEDIR/NtupleMaker_Pi10GeV_1016_cfg.py > out_Pi10GeV.txt
