CRAB3
====

For Data Run2015D use CMSSW_7_6_5

See details here:

    https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCRAB3Tutorial#CRAB_configuration_parameters
    https://twiki.cern.ch/twiki/bin/view/CMSPublic/CRAB3ConfigurationFile

Check if you have writing permissions:

    source /cvmfs/cms.cern.ch/crab3/crab.sh
    source /cvmfs/cms.cern.ch/crab3/crab.csh

    crab checkwrite --site=T2_CH_CERN
    crab checkwrite --site=T2_CH_CERN --lfn=/store/group/phys_higgs/cmshww/amassiro/RunII/test/

Send the jobs:

    crab submit -c crab_example1.py
    crab status

MultiCRAB
====

    cmsenv

    python multicrab_Run2015D_25ns_RECO.py samples/samples_Run2015D_25ns_reRECO.py



    crab status -d folder_name

How to acess to /store via mounting
===

cd /tmp/kropiv ### to have enough place

mkdir eos

eosmount eos eos ### mount eos 

cd eos/cms/store/group/phys_higgs/cmshww/kropiv

### correct what you want

eosumount eos eos ### do not forget unmount


How to calculate luminosity for Run2
===

please follow instructions at

https://twiki.cern.ch/twiki/bin/view/CMS/lcr2
