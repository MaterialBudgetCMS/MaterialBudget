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

Send crab job with python:

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

All root-file will be merged to new.root. Move it to 

    /store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/reReco2015D/
    

How to calculate luminosity for Run2
===

please follow instructions at (OLD):

     https://twiki.cern.ch/twiki/bin/view/CMS/lcr2
