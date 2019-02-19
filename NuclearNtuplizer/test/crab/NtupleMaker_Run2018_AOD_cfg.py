# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

## start init. variables

# The line below always has to be included to make VarParsing work 
from FWCore.ParameterSet.VarParsing import VarParsing
# In teh line below 'analysis' is an instance of VarParsing object 
options = VarParsing ('analysis')
options.register ('globalTag',
                  '101X_dataRun2_Prompt_v9', # for Run2017A CMSSW_9_2_1
                   VarParsing.multiplicity.singleton,
                   VarParsing.varType.string,
                  'GlobalTag')

#-------------------------------------------------------------------------------
# defaults
options.maxEvents = -1 #all events ---> already the default
#options.maxEvents = 500 #all events ---> already the default
options.outputFile = 'Run2018.root'
print " options.maxEvents = ",options.maxEvents
print " options.outputFile = ",options.outputFile
#-------------------------------------------------------------------------------

options.parseArguments()

# load configurations
#label = options.label
#globalTag = options.globalTag + "::All"
globalTag = options.globalTag
print " globalTag = ",globalTag

## end init. variables

#process = cms.Process("MyNtupleMaker")
process = cms.Process('niReRECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('CommonTools.ParticleFlow.EITopPAG_cff')
process.load('Configuration.StandardSequences.AlCaRecoStreams_cff')
process.load('DQMOffline.Configuration.DQMOffline_cff')

### Import real conditions
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, globalTag, '')

#### Additional stuff
##process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertex_cff')
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertexCandidate_cff')
process.particleFlowDisplacedVertex.primaryVertexCut = cms.double(1.3)
process.particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.3)

### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring()
)

# Output definition

process.AODoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AOD'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    fileName = cms.untracked.string('file:step_niPFrereco_inAOD.root'),
    outputCommands = process.FEVTEventContent.outputCommands
)

### Define number of events to be processed (-1 means all)
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

### Define text output
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


### Define Ntuplizer
process.MyNtupleMaking = cms.EDAnalyzer("NtupleMakerNuclearInteractions",
   RealData  = cms.bool(False),
)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string(options.outputFile)
)

process.out = cms.OutputModule("PoolOutputModule",
  outputCommands = cms.untracked.vstring ('keep *'),
  fileName = cms.untracked.string('myOutputFileMC.root')
)

# Path and EndPath definitions
process.niReReconstruction_step = cms.Path(process.particleFlowDisplacedVertexCandidate
                                           +process.particleFlowDisplacedVertex
                                           +process.MyNtupleMaking
                                           )

process.AODoutput_step = cms.EndPath(process.AODoutput)
### Schedule definition
process.schedule = cms.Schedule(process.niReReconstruction_step)
#process.schedule = cms.Schedule(process.niReReconstruction_step,process.AODoutput_step)
