# MaterialBudget

Code for Nuclear Interactions (NIs)

## Presentations
All presentations and conferences are listed at Twiki: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TrackerMaterial2017

## Machine Learning:
Public code in python for Machine learning, presented at PyHEP: https://github.com/kropiv/MLforNIatPyHEP

Internal CMS code: https://github.com/kropiv/MLforNI

## Standard code for Nuclear Interactions:
https://github.com/MaterialBudgetCMS/MaterialBudget

For 2018, use `CMSSW_10_2_1` or similar

1. Produce ntuple from AOD or RECO data with crab:https://github.com/MaterialBudgetCMS/MaterialBudget/tree/master/NuclearNtuplizer/test/crab

2. Produce histograms from crab:https://github.com/MaterialBudgetCMS/MaterialBudget/tree/master/NuclearNtuplizer/test/PlotProduction

3. Find/fit material position:
https://github.com/MaterialBudgetCMS/MaterialBudget/tree/master/NuclearNtuplizer/test/BeamPipeFit
`revisionsInnerTrackerFit_2018.C`  for position
`TrackerMaterialEstimation_2018.C` for tracker material estimation

## How to clone code

```
git clone git@github.com:MaterialBudgetCMS/MaterialBudget.git
cd MaterialBudget/NuclearNtuplizer/test
git branch Branching_wich_you_need 
```
________________
`git status`
----> look on  you see a new branch was created by you are not yet in. To go there
_________

`git checkout UpdatesFromKorea`
_________________________
now you are there
see with
git status
__________________________

Create now a new dummy file.

Myfile.txt

Do then:
```
git commit -a -m"test"
git push origin UpdatesFromKorea
```
Go to

https://github.com/MaterialBudgetCMS/MaterialBudget/tree/UpdatesFromKorea/NuclearNtuplizer/test

and choose your branch. You shall see your file there.

===========================

## Old version
cmsrel CMSSW_9_0_0

cd CMSSW_9_0_0/src

cmsenv

cd MaterialBudget/NuclearNtuplizer/test
eosmount .
cmsBatch.py 10 SinglePiPt10_pythia8_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO.py -o TEST5 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017/TEST5 -b 'bsub -q 1nh < ./batchScript.sh'

