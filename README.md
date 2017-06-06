# MaterialBudget
git clone git@github.com:MaterialBudgetCMS/MaterialBudget.git
cd MaterialBudget/NuclearNtuplizer/test
git branch UpdatesFromKorea
________________
git status
----> look on  you see a new branch was created by you are not yet in. To go there
_________

git checkout UpdatesFromKorea

_________________________
now you are there
see with
git status
__________________________

Create now a new dummy file.

Myfile.txt

Do then:

git commit -a -m"test"
git push origin UpdatesFromKorea

Go to

https://github.com/MaterialBudgetCMS/MaterialBudget/tree/UpdatesFromKorea/NuclearNtuplizer/test

and choose your branch. You shall see your file there.

===========================

cmsrel CMSSW_9_0_0

cd CMSSW_9_0_0/src

cmsenv

cd MaterialBudget/NuclearNtuplizer/test
eosmount .
cmsBatch.py 10 SinglePiPt10_pythia8_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO.py -o TEST5 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017/TEST5 -b 'bsub -q 1nh < ./batchScript.sh'

