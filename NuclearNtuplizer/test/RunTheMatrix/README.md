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


How to run in batch:

1. Compile code in src directory to have cmsBatch.py inside of the CMSSW. 

2.  Modify number of events in SinglePiPt10_pythia8_cfi_GEN_SIM.py and create 1st step:

    cmsBatch.py 10 SinglePiPt10_pythia8_cfi_GEN_SIM.py -o TEST -r /eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/test -b 'bsub -q 8nh < ./batchScript.sh'

"../test" directory shouldn't exist, otherwise could will give error.

3. Create 2nd step


