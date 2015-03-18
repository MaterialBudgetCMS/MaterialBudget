#!/bin/bash

# Can be Ntuple or LegacyNtuple
# TODO: only Ntuple implemented so far
export type=Ntuple

# Can be Data or MC
export datasettype=Data

export dataset=/DoubleMu/Run2011A-03Oct2011-v1/RECO
export globaltag=FT_R_42_V21A

export name=DoubleMu__Run2011A-03Oct2011-v1__DoubleMuTriggers-AllSelections

# firstrun and lastrun are not used for MC
export firstrun=160404
export lastrun=180252

export numberofjobs=400

# json is not used for MC
export json=Cert_160404-180252_7TeV_PromptReco_Collisions11_JSON.txt

# Name of trigger path to select events
#export triggerpath=HLT_DoubleMu0_Quarkonium_v1


# No changes by user below this point

export crabtemplatename=pippo
export cfgtemplatename=pippo
export cfgname=pippo
export newdirname=pippo

if [[ $type == "Ntuple" ]]
  then
  if [[ $datasettype == "Data" ]]
    then
    crabtemplatename=TEMPLATE__Ntuple__crab__Data.cfg
    cfgtemplatename=TEMPLATE__MyNtupleMaker__Data_cfg.py
    cfgname=MyNtupleMaker__${name}_cfg.py
    newdirname=crab__MyNtupleMaker__${name}__$firstrun-$lastrun
  elif [[ $datasettype == "MC" ]]
    then
    crabtemplatename=TEMPLATE__Ntuple__crab__MC.cfg
    cfgtemplatename=TEMPLATE__MyNtupleMaker__MC_cfg.py
    cfgname=MyNtupleMaker__${name}_cfg.py
    newdirname=crab__MyNtupleMaker__${name}
  fi
fi

mkdir $newdirname
cd $newdirname

if [[ $type == "Ntuple" ]]
  then
  if [[ $datasettype == "Data" ]]
    then
    sed s#CHANGEMEDATASET#$dataset#g ../$crabtemplatename | sed s#CHANGEMENAME#$name#g | sed s#CHANGEMEFIRSTRUN#$firstrun#g | sed s#CHANGEMELASTRUN#$lastrun#g | sed s#CHANGEMEJSON#$json#g | sed s#CHANGEMENUMBEROFJOBS#$numberofjobs#g > crab.cfg
    sed s#CHANGEMEGLOBALTAG#$globaltag#g ../$cfgtemplatename | sed s#CHANGEMENAME#$name#g | sed s#CHANGEMETRIGGERPATH#$triggerpath#g > $cfgname
    cp ../$json .
  elif [[ $datasettype == "MC" ]]
    then
    sed s#CHANGEMEDATASET#$dataset#g ../$crabtemplatename | sed s#CHANGEMENAME#$name#g | sed s#CHANGEMENUMBEROFJOBS#$numberofjobs#g > crab.cfg
    sed s#CHANGEMEGLOBALTAG#$globaltag#g ../$cfgtemplatename | sed s#CHANGEMENAME#$name#g > $cfgname 
        ######| sed s#CHANGEMETRIGGERPATH#$triggerpath#g > $cfgname
  fi
fi

