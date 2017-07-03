# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

import FWCore.ParameterSet.Config as cms


## start init. variables

# The line below always has to be included to make VarParsing work 
from FWCore.ParameterSet.VarParsing import VarParsing
# In teh line below 'analysis' is an instance of VarParsing object 
options = VarParsing ('analysis')
options.register ('globalTag',
                  '92X_dataRun2_Express_v2', # for Run2017A CMSSW_9_2_1
                   VarParsing.multiplicity.singleton,
                   VarParsing.varType.string,
                  'GlobalTag')

#-------------------------------------------------------------------------------
# defaults
options.maxEvents = -1 #all events ---> already the default
#options.maxEvents = 500 #all events ---> already the default
options.outputFile = 'Run2017A_921.root'
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




process = cms.Process("MyNtupleMaker")

### Import real conditions
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, globalTag, '')


### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring()
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

process.ana_step = cms.Path( process.MyNtupleMaking )

#process.e = cms.EndPath(process.out)

### Schedule definition
#process.schedule = cms.Schedule(process.ana_step, process.e)
process.schedule = cms.Schedule(process.ana_step)
