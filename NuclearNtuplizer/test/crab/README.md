CRAB3
====

For Data Run2015B use CMSSW_7_4_7_patch2

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

    python multicrab_data.py samples/samples_Run2015B.py
    python multicrab_data_LowPileUp.py samples/samples_Run2015B.py
    python multicrab.py samples/samples_spring15.py
 
    crab status -d folder_name

How to acess to /store via mounting
===

cd /tmp/kropiv ### to have enough place

mkdir eos

eosmount eos eos ### mount eos 

cd eos/cms/store/group/phys_higgs/cmshww/kropiv

### correct what you want

eosumount eos eos ### do not forget unmount

