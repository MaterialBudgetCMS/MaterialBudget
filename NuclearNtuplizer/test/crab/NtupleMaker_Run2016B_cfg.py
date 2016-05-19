# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:run1_data -s RAW2DIGI,L1Reco,RECO,EI,ALCAPRODUCER:@allForPrompt,DQM,ENDJOB --process RECO --data --eventcontent RECO,AOD,ALCARECO,DQM --scenario pp --datatier RECO,AOD,ALCARECO,DQMIO --customise Configuration/DataProcessing/RecoTLR.customisePrompt -n 100 --filein filelist:step1_dasquery.log --lumiToProcess step1_lumiRanges.log --fileout file:step2.root
import FWCore.ParameterSet.Config as cms


## start init. variables

# The line below always has to be included to make VarParsing work 
from FWCore.ParameterSet.VarParsing import VarParsing
# In teh line below 'analysis' is an instance of VarParsing object 
options = VarParsing ('analysis')
options.register ('globalTag',
                  '80X_dataRun2_Prompt_v8',
                   VarParsing.multiplicity.singleton,
                   VarParsing.varType.string,
                  'GlobalTag')

#-------------------------------------------------------------------------------
# defaults
options.maxEvents = -1 #all events ---> already the default
#options.maxEvents = 500 #all events ---> already the default
options.outputFile = 'Run2015B_PromptRecoOut.root'
print " options.maxEvents = ",options.maxEvents
print " options.outputFile = ",options.outputFile
#-------------------------------------------------------------------------------

options.parseArguments()

# load configurations
#label = options.label
globalTag = options.globalTag + "::All"
globalTag = options.globalTag
print " globalTag = ",globalTag

## end init. variables



process = cms.Process('niReRECO')

# import of standard configurations
#process.load('CondCore.CondDB.CondDB_cfi.py')
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
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.maxEvents = cms.untracked.PSet(
    #input = cms.untracked.int32(100)
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/k/kropiv/public/SingleMu_Run2016B_PromptReco_v1_XX.root'),
    #fileNames = cms.untracked.vstring()
    #secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

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

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, globalTag, '')


### Additional stuff
#process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertex_cff')
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertexCandidate_cff')
process.particleFlowDisplacedVertex.primaryVertexCut = cms.double(1.8)
process.particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.8)



### Define Ntuplizer
process.MyNtupleMaking = cms.EDAnalyzer("NtupleMakerNuclearInteractions",
)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string(options.outputFile)
)


# Path and EndPath definitions
#process.niReReconstruction_step = cms.Path(process.particleFlowDisplacedVertexCandidate
#                                           +process.particleFlowDisplacedVertex
#                                           +process.MyNtupleMaking)
process.niReReconstruction_step = cms.Path(process.MyNtupleMaking)

process.AODoutput_step = cms.EndPath(process.AODoutput)

# Schedule definition
process.schedule = cms.Schedule(process.niReReconstruction_step)
#,process.AODoutput_step)

