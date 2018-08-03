# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("MyNtupleMaker")

### Import real conditions
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '')


### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_10.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_11.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_13.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_14.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_15.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_16.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_17.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_18.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_1.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_20.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_21.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_22.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_23.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_24.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_25.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_26.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_27.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_28.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_29.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_2.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_30.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_31.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_32.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_33.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_34.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_35.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_36.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_37.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_38.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_39.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_3.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_40.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_41.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_43.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_44.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_45.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_46.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_47.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_48.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_49.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_4.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_50.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_52.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_53.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_54.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_55.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_56.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_57.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_58.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_59.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_5.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_60.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_61.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_62.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_63.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_64.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_65.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_66.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_67.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_68.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_6.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_71.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_72.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_74.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_75.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_76.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_77.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_78.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_79.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_7.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_80.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_81.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_82.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_83.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_84.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_85.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_87.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_88.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_89.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_8.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_90.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_91.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_92.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_93.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_95.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_RECO/step3_RAW2DIGI_L1Reco_RECO_RECOSIM_9.root'
  ),
  secondaryFileNames = cms.untracked.vstring(
  )
)


### Define number of events to be processed (-1 means all)
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

### Define text output
process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring('MyNtupleMaker.log'), ### Output filename
    default = cms.untracked.PSet( reportEvery = cms.untracked.int32(1000) ),
)

### Define Ntuplizer
process.MyNtupleMaking = cms.EDAnalyzer("NtupleMakerNuclearInteractions",
#process.MyNtupleMaking = cms.EDAnalyzer("NI",
   RealData  = cms.bool(False),
)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string('Ntuple_Pi10GeV_1016.root' )
)

process.out = cms.OutputModule("PoolOutputModule",
  outputCommands = cms.untracked.vstring ('keep *'),
  fileName = cms.untracked.string('myOutputFileMC.root')
)

process.ana_step = cms.Path( process.MyNtupleMaking )

#process.e = cms.EndPath(process.out)

### Schedule definition
#process.schedule = cms.Schedule(process.ana_step, process.e)
process.schedule = cms.Schedule(process.ana_step)
