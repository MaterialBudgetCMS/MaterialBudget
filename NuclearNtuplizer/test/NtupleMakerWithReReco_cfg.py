# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:run1_data -s RAW2DIGI,L1Reco,RECO,EI,ALCAPRODUCER:@allForPrompt,DQM,ENDJOB --process RECO --data --eventcontent RECO,AOD,ALCARECO,DQM --scenario pp --datatier RECO,AOD,ALCARECO,DQMIO --customise Configuration/DataProcessing/RecoTLR.customisePrompt -n 100 --filein filelist:step1_dasquery.log --lumiToProcess step1_lumiRanges.log --fileout file:step2.root
import FWCore.ParameterSet.Config as cms

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
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(#'/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/12DC640A-25A6-E411-8D85-0025905964C0.root'
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/12DC640A-25A6-E411-8D85-0025905964C0.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/167F590F-2FA6-E411-8FF6-003048FFCBB0.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/220FF210-2BA6-E411-B176-002618943857.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/5E9416C6-26A6-E411-94CC-0026189437EC.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/6A443257-27A6-E411-ADF4-0025905B85D8.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/7697B09E-7AA6-E411-BC7B-0025905A60F2.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/B0A02540-35A6-E411-BB10-002354EF3BDB.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/E47A9325-24A6-E411-9F7E-003048D15DE0.root',
    '/store/relval/CMSSW_7_3_1_patch1/RelValTTbar_13/GEN-SIM-RECO/PU50ns_MCRUN2_73_V9-v1/00000/FEBAD062-2CA6-E411-8E80-00261894392B.root',
),
    secondaryFileNames = cms.untracked.vstring()
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
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run1_data', '')


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
  fileName = cms.string('Ntuple_MC_prova_1.root' )
)


# Path and EndPath definitions
process.niReReconstruction_step = cms.Path(process.particleFlowDisplacedVertexCandidate
                                           +process.particleFlowDisplacedVertex
                                           +process.MyNtupleMaking)

process.AODoutput_step = cms.EndPath(process.AODoutput)

# Schedule definition
process.schedule = cms.Schedule(process.niReReconstruction_step)
#,process.AODoutput_step)

