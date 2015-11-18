# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:run1_data -s RAW2DIGI,L1Reco,RECO,EI,ALCAPRODUCER:@allForPrompt,DQM,ENDJOB --process RECO --data --eventcontent RECO,AOD,ALCARECO,DQM --scenario pp --datatier RECO,AOD,ALCARECO,DQMIO --customise Configuration/DataProcessing/RecoTLR.customisePrompt -n 100 --filein filelist:step1_dasquery.log --lumiToProcess step1_lumiRanges.log --fileout file:step2.root
import FWCore.ParameterSet.Config as cms

process = cms.Process('niReRECO')
from Configuration.StandardSequences.Services_cff import *
from Configuration.StandardSequences.GeometryExtended_cff import *
from Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff import *
from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *

process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")

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

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')


# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_0.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_1.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_10.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_11.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_13.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_14.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_15.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_16.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_17.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_18.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_19.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_2.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_20.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_21.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_24.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_25.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_26.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_27.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_28.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_29.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_3.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_31.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_32.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_33.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_34.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_35.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_36.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_37.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_38.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_39.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_4.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_40.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_41.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_42.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_43.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_44.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_45.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_46.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_47.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_48.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_49.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_5.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_50.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_51.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_52.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_53.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_54.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_55.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_56.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_57.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_58.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_59.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_6.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_60.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_61.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_62.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_63.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_64.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_65.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_66.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_67.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_68.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_69.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_70.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_71.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_72.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_73.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_74.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_75.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_76.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_77.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_78.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_79.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_8.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_80.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_81.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_83.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_84.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_85.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_86.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_87.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_88.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_89.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_9.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_90.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_91.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_92.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_93.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_94.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_95.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_96.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_97.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_98.root',
           '/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeV_noFilter_200K_v3/pion100GeV_99.root',
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
    fileName = cms.untracked.string(
          'file:step_niPFrereco_inAOD.root'
),
    outputCommands = process.FEVTEventContent.outputCommands
)



### Additional stuff
#process.load("RecoTracker.TrackProducer.TrackRefitters_cff")
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertex_cff')
process.load('RecoParticleFlow/PFTracking/particleFlowDisplacedVertexCandidate_cff')
process.particleFlowDisplacedVertex.primaryVertexCut = cms.double(1.8)
process.particleFlowDisplacedVertexCandidate.primaryVertexCut = cms.double(1.8)

##########################
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    #input = cms.untracked.int32(1000000)
)
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
##########################

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

