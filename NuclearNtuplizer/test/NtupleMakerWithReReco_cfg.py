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

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')

### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/12DC640A-25A6-E411-8D85-0025905964C0.root'
#    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-DIGI-RAW-HLTDEBUG/PU50ns_MCRUN2_73_V9_GenSim_7113-v1/00000/EEAF333A-2FB1-E411-A0BB-0025905A60D6.root'
  ),
  secondaryFileNames = cms.untracked.vstring(
  )
)


### Define number of events to be processed (-1 means all)
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

### Define text output
process.MessageLogger = cms.Service("MessageLogger",
  destinations = cms.untracked.vstring('MyNtupleMaker.log'), ### Output filename
    default = cms.untracked.PSet( reportEvery = cms.untracked.int32(1000) ),
)

### Define Ntuplizer
process.MyNtupleMaking = cms.EDAnalyzer("NtupleMakerNuclearInteractions",
)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string('Ntuple_MC_prova_1.root' )
)

process.out = cms.OutputModule("PoolOutputModule",
  outputCommands = cms.untracked.vstring ('keep *'),
  fileName = cms.untracked.string('myOutputFileMC.root')
)


### Additional stuff
#process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertex_cff')
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertexCandidate_cff')
process.particleFlowDisplacedVertex.primaryVertexCut = cms.double(1.8)
process.particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.8)


process.disp = cms.Sequence(process.particleFlowDisplacedVertexCandidate + process.particleFlowDisplacedVertex)
#process.disp = cms.Sequence(process.particleFlowDisplacedVertex)


process.ana_step = cms.Path( process.disp*process.MyNtupleMaking )

#process.e = cms.EndPath(process.out)

### Schedule definition
#process.schedule = cms.Schedule(process.ana_step, process.e)
process.schedule = cms.Schedule(process.ana_step)
