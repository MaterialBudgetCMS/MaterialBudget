# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("MyNtupleMaker")

### Import real conditions
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '90X_upgrade2017_realistic_v20', '')


### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/work/m/mgouzevi/private/TRACKING/CMSSW_7_3_1/src/this_is_an_example.root'
  'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017/50GeV/SinglePiPt10_pythia8_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_71.root'
  ),
  secondaryFileNames = cms.untracked.vstring(
  )
)


### Define number of events to be processed (-1 means all)
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source.duplicateCheckMode = cms.untracked.string("noDuplicateCheck")

### Define text output
process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring('MyNtupleMaker.log'), ### Output filename
    default = cms.untracked.PSet( reportEvery = cms.untracked.int32(1000) ),
)

### Define Ntuplizer
process.MyNtupleMaking = cms.EDAnalyzer("NtupleMakerNuclearInteractions",
   RealData  = cms.bool(False),
)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string('Ntuple_MC_900.root' )
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
