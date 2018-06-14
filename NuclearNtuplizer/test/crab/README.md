
How to check collections inside file:
====

     edmDumpEventContent FileName.root| grep DisplacedVertex

CRAB3
====

For Data Run2015D use CMSSW_7_6_5 make if neccessary:

     export SCRAM_ARCH=slc6_amd64_gcc493


See details here:

https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial#CRAB_configuration_parameters

https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile

Check if you have writing permissions:

    source /cvmfs/cms.cern.ch/crab3/crab.sh
    source /cvmfs/cms.cern.ch/crab3/crab.csh

    crab checkwrite --site=T2_CH_CERN
    crab checkwrite --site=T2_CH_CERN --lfn=/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/reReco2015D/

Usual send the jobs:

    crab submit -c crab_example1.py
    crab status

MultiCRAB
====

Set enviroment:

    cmsenv

Sent crab job with python for 2018:

    python crab_Run2018_run315646.py samples/sample_ZeroBias_Run2018_run315646.py

Send crab job with python for 2017:

    python crab_Run2017E_9212.py samples/sample_SingleMu_Run2017E_PromptReco_v1.py  # dataset is not availble in crab, need to be checked
    python crab_Run2017E_9212.py samples/sample_ZeroBias_Run2017E_PromptReco_v1.py 

    python crab_Run2017B_930.py samples/sample_SingleMu_Run2017B_04Jul2017_v2.py 
    python crab_Run2017B_930.py samples/sample_SingleMu_Run2017B_PromptReco_v1.py
    python crab_Run2017B_930.py samples/sample_SingleMu_Run2017B_PromptReco_v2.py
    python  crab_Run2017A_921.py samples/sample_Run2017A_921.py
    python  crab_Run2017B_923.py samples/sample_Run2017B_923.py

Send crab job with python for 2015:

    python multicrab_Run2015D_25ns_RECO.py samples/samples_Run2015D_25ns_reRECO.py


Check crab status:

    crab status -d folder_name
    crab status -d projects_Run2015/crab_Run2015D_16Dec2015_v1_25ns_SingleMuon/

Resubmit jobs which are failed:

    crab resubmit --dir/-d <CRAB-project-directory>
    crab resubmit -d projects_Run2015/crab_Run2015D_16Dec2015_v1_25ns_SingleMuon/

How to acess to /store via mounting
===

    cd /tmp/kropiv ### to have enough place
    mkdir eos
    eosmount eos eos ### mount eos 
    cd eos/cms/store/group/phys_higgs/cmshww/kropiv
you could make link to your current working directory
    cd <WokingDirectory>
    ln -s /tmp/<nice-login>/eos 

Correct what you want and unmount it: 

    eosumount eos eos ### do not forget unmount


How to merger all output root files in one
===

After mounting eos, go to directory with root files and run:

    hadd new.root *root

If hadd doesn't work, then you have to run cmsenv from any CMSSW and try again. hadd is part of the root commands. 

All root-file will be merged to new.root. Move it to 

    /store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/reReco2015D/
    

How to calculate luminosity for Run2
===

please follow instructions at (OLD):

     https://twiki.cern.ch/twiki/bin/view/CMS/lcr2

Information about Run2017 A B good for Pixel:
===

Run Era     | configuration     | run list of GOOD for Pixel and Tracker

Run2017A        case-1          297003 296980 296979 296978 296977 296976 296972 296971 296970 296969 296968 296967 296966
                                296898 296897 296888 296881 296880 296879 296867 296866 296801 296799 296791 296788 296787 296786

Run2017B        case-1          297176 297175 297114 297113 297101 297100 297099 297057 297056 297050

Run2017B        case-2          297227 297225 297224 297218 297215

Run2017B        case-2 - HV=200 297474 297469 297433 297432 297430 297429 297425 297411 297359 297308 297296 297293 297292

note: 296801 296799 are Low_stat runs

if needed DC will update these list here : [1]

Configuration meaning:( also described in [1])â?¨

case 1          is the first stable timing configuration Pixel adopted, not optimal for Layer 1 but quite ok
case 2          is a better timing configuration (optimizing Layer one response)â?¨
case 2 HV 200   is the last setting Pixel is using, with the timing as above, but the HV in the Layer one has been moved from 100V to 200V



