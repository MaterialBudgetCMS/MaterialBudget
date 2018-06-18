## How to find good configuration for MC without big knowleage:
Find MC examples wiht "Pi" inside

     runTheMatrix.py -n | grep 2018 | grep -v PU  | grep -v Pi

Take MC is most close to your request and use it ID in the next line (in our case 10807):

 
     runTheMatrix.py -l 10807 -ne


You get out put bellow, so modify for your needs and run:

     cmsDriver.py SinglePiPt10_pythia8_cfi  --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent FEVTDEBUG --relval 25000,100 -s GEN,SIM --datatier GEN-SIM --beamspot Realistic25ns13TeVEarly2017Collision --geometry DB:Extended 

     mv SinglePiPt10_pythia8_cfi_GEN_SIM.root step2_SIM.root

     cmsDriver.py step2  --conditions auto:phase1_2018_realistic -s DIGI:pdigi_valid,L1,DIGI2RAW,HLT:@relval2018 --datatier GEN-SIM-DIGI-RAW -n 10 --geometry DB:Extended --era Run2_2018 --eventcontent FEVTDEBUGHLT

     mv step2_DIGI_L1_DIGI2RAW_HLT.root step3_DIGI2RAW.root

In principle, both command below are working, but we don't need DQM, validation and AOD, so I used the 2nd command

     cmsDriver.py step3  --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent RECOSIM,MINIAODSIM,DQM --runUnscheduled  -s RAW2DIGI,L1Reco,RECO,RECOSIM,EI,PAT,VALIDATION:@standardValidation+@miniAODValidation,DQM:@standardDQM+@ExtraHLT+@miniAODDQM --datatier GEN-SIM-RECO,MINIAODSIM,DQMIO --geometry DB:Extended

     cmsDriver.py step3  --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent RECOSIM --runUnscheduled  -s RAW2DIGI,L1Reco,RECO,RECOSIM --datatier GEN-SIM-RECO --geometry DB:Extended

We output: 
    step3_RAW2DIGI_L1Reco_RECO_RECOSIM.root 

DisplacedVertex collection is inside.

## How to run in batch (test example for 10^4 events):

1. Compile code in src directory to have cmsBatch.py inside of the CMSSW. 

2.  Modify number of events in SinglePiPt10_pythia8_cfi_GEN_SIM.py and create 1st step:

    cmsBatch.py 10 SinglePiPt10_pythia8_cfi_GEN_SIM.py -o TEST -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/test -b 'bsub -q 8nh < ./batchScript.sh'

It will run 10 times with number of events which you have in your python.
   
"../test" directory shouldn't exist, otherwise you will have error.

When you submit jobs, please ignore error in the end: "ERROR: Cannot find release package/tag list at ..."

3. Create 2nd step, by adding all files in python file, produced in step 1 (see below how to print all files from one directory for python): 

    cmsBatch.py 1 step2_DIGI_L1_DIGI2RAW_HLT.py -o TEST_step2 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/test_step2 -b 'bsub -q 8nh < ./batchScript.sh'

It will run 1 file per job.
 
4. Submit reconstruction again by modifying another python file:

    cmsBatch.py 1 step3_RAW2DIGI_L1Reco_RECO_RECOSIM.py -o TEST_step3 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/test_step3 -b 'bsub -q 8nh < ./batchScript.sh'

It will run 1 file per job.

## For 10 GeV pions 100 files 10^6 events (Anna did it):

    cmsBatch.py 100 SinglePiPt10_pythia8_cfi_GEN_SIM.py -o CMSSW_10_1_6_Pion10GeV_step1 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_step1 -b 'bsub -q 8nh < ./batchScript.sh'
    cmsBatch.py 1 step2_SinglePiPt10_DIGI_L1_DIGI2RAW_HLT.py -o CMSSW_10_1_6_Pion10GeV_step2 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_step2 -b 'bsub -q 1nd < ./batchScript.sh'
    cmsBatch.py 1 step3_SinglePiPt10_RAW2DIGI_L1Reco_RECO_RECOSIM.py -o CMSSW_10_1_6_Pion10GeV_step3 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO -b 'bsub -q 1nd < ./batchScript.sh'

## For 100 GeV pions 100 files 10^6 events (Eilish):

    cmsBatch.py 100 SinglePiPt100_pythia8_cfi_GEN_SIM.py -o CMSSW_10_1_6_Pion100GeV_step1 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1 -b 'bsub -q 8nh < ./batchScript.sh'
    cmsBatch.py 1 step2_SinglePiPt100_DIGI_L1_DIGI2RAW_HLT.py -o CMSSW_10_1_6_Pion100GeV_step2 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2 -b 'bsub -q 1nd < ./batchScript.sh'
    cmsBatch.py 1 step3_SinglePiPt100_RAW2DIGI_L1Reco_RECO_RECOSIM.py -o CMSSW_10_1_6_Pion100GeV_step3 -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_RECO -b 'bsub -q 1nd < ./batchScript.sh'

## To Print all existing root-files in one derictory for python configuration file use the following script:

    ./FilePrint.sh dirName/
    ./FilePrint.sh /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_step1/    
