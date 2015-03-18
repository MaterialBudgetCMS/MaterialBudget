# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("MyNtupleMaker")

### Import real conditions
from Configuration.StandardSequences.Services_cff import *
from Configuration.StandardSequences.GeometryExtended_cff import *
from Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff import *
from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *

process.load('Configuration/StandardSequences/Services_cff')
#process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

#process.GlobalTag.globaltag = "GR_R_53_V8::All"
process.GlobalTag.globaltag = "FT_R_53_V6::All"
#process.GlobalTag.globaltag = "FT_53_V6C_AN4::All"

### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    'file:/afs/cern.ch/work/p/pozzo/CMSSW_5_3_2/src/MaterialBudget/NuclearNtuplizer/test/7C3BDEB1-04D0-E111-8FD7-0030486791DC.root'
  ),
  secondaryFileNames = cms.untracked.vstring(
  )
)


### Define number of events to be processed (-1 means all)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

### Define text output
process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring('MyNtupleMaker.log'), ### Output filename
    default = cms.untracked.PSet( reportEvery = cms.untracked.int32(1000) ),
)

### Define Ntuplizer
process.MyNtupleMaking = cms.EDAnalyzer("NtupleMakerNuclearInteractions",
)

### HLT filter
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltfilter = process.hltHighLevel.clone(
  TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
  HLTPaths = cms.vstring(
    "HLT_MinBias*",
    "HLT_ZeroBias*",
    "HLT_Random*",
  ),                                    # provide list of HLT paths (or patterns) you want
  eventSetupPathsKey = cms.string(''),  # not empty => use read paths from AlCaRecoTriggerBitsRcd via this key
  andOr = cms.bool(True),               # how to deal with multiple triggers: True (OR) accept if ANY is true, False (AND) accept if ALL are true
  throw = cms.bool(False)               # throw exception on unknown path names
)

### Additional stuff
process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertex_cff')
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertexCandidate_cff')
process.particleFlowDisplacedVertex.primaryVertexCut = cms.double(2.0)
process.particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.8)

process.disp = cms.Sequence(process.particleFlowDisplacedVertexCandidate + process.particleFlowDisplacedVertex)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string('Ntuple_MC_prova_1.root' )
)

process.out = cms.OutputModule("PoolOutputModule",
  outputCommands = cms.untracked.vstring ('keep *'),
  fileName = cms.untracked.string('myOutputFileMC.root')
)

process.ana_step = cms.Path( process.hltfilter*process.disp*process.MyNtupleMaking )

#process.e = cms.EndPath(process.out)

### Schedule definition
#process.schedule = cms.Schedule(process.ana_step, process.e)
process.schedule = cms.Schedule(process.ana_step)
