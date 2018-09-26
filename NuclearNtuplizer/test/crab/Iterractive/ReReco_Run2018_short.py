# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: RECO -s RAW2DIGI,RECO,ALCA:SiStripCalMinBias --runUnscheduled --nThreads 8 --data --era Run2_2018 --scenario pp --conditions 102X_dataRun2_Prompt_EgammaRepro_v2 --eventcontent RECO --datatier RECO --customise Configuration/DataProcessing/RecoTLR.customisePostEra_Run2_2018 --filein file:pippo.root -n 100 --python_filename=recoskim_Run2018D_SingleMuon.py --no_exec
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.Reconstruction_Data_cff')
process.load('Configuration.StandardSequences.AlCaRecoStreams_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000)
)

# Input source
process.source = cms.Source("PoolSource",
    #fileNames = cms.untracked.vstring('file:pippo.root'),
    #fileNames = cms.untracked.vstring('file:/eos/cms/store/data/Run2018D/SingleMuon/RAW/v1/000/323/526/00000/FF5CE96F-CF53-DD47-B478-183334D19809.root'),
    fileNames = cms.untracked.vstring('file:/eos/cms/store/data/Run2018D/SingleMuon/RAW/v1/000/323/526/00000/BEB225B0-E99D-AB45-B910-8793C9E030DC.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('RECO nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

### Displaced Reco:

DisplacedRecoEventContent = cms.PSet(
    outputCommands = cms.untracked.vstring('drop *'),
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize=cms.untracked.int32(5*1024*1024)
)

##DisplacedRecoEventContent.outputCommands.extend(process.RecoLocalTrackerRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoLocalMuonRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoLocalCaloRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoEcalRECO.outputCommands)
##DisplacedRecoEventContent.outputCommands.extend(process.TrackingToolsRECO.outputCommands)
DisplacedRecoEventContent.outputCommands.extend(process.RecoTrackerRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoJetsRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoMETRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoMuonRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoBTauRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoBTagRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoTauTagRECO.outputCommands)
DisplacedRecoEventContent.outputCommands.extend(process.RecoVertexRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(RecoEgammaRECO.outputCommands)
DisplacedRecoEventContent.outputCommands.extend(process.RecoPixelVertexingRECO.outputCommands)
DisplacedRecoEventContent.outputCommands.extend(process.RecoParticleFlowRECO.outputCommands)
DisplacedRecoEventContent.outputCommands.extend(process.BeamSpotRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(L1TriggerRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(HLTriggerRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(MEtoEDMConverterRECO.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(EvtScalersRECO.outputCommands)
DisplacedRecoEventContent.outputCommands.extend(process.CommonEventContent.outputCommands)
#DisplacedRecoEventContent.outputCommands.extend(EITopPAGEventContent.outputCommands)
### end Displaced Reco

# Output definition

process.RECOoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('RECO_RAW2DIGI_RECO_ALCA_short.root'),
    #outputCommands = process.RECOEventContent.outputCommands,
    outputCommands = DisplacedRecoEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)





# Additional output definition
process.ALCARECOStreamSiStripCalMinBias = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('pathALCARECOSiStripCalMinBias')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALCARECO'),
        filterName = cms.untracked.string('SiStripCalMinBias')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('SiStripCalMinBias.root'),
    outputCommands = cms.untracked.vstring(
        'drop *', 
        'keep *_ALCARECOSiStripCalMinBias_*_*', 
        'keep *_siStripClusters_*_*', 
        'keep *_siPixelClusters_*_*', 
        'keep DetIdedmEDCollection_siStripDigis_*_*', 
        'keep L1AcceptBunchCrossings_*_*_*', 
        'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*', 
        'keep LumiScalerss_scalersRawToDigi_*_*', 
        'keep DcsStatuss_scalersRawToDigi_*_*', 
        'keep *_TriggerResults_*_*'
    )
)

# Other statements
process.ALCARECOEventContent.outputCommands.extend(process.OutALCARECOSiStripCalMinBias_noDrop.outputCommands)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_dataRun2_Prompt_EgammaRepro_v2', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOoutput_step = cms.EndPath(process.RECOoutput)
process.ALCARECOStreamSiStripCalMinBiasOutPath = cms.EndPath(process.ALCARECOStreamSiStripCalMinBias)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.pathALCARECOSiStripCalMinBias,process.endjob_step,process.RECOoutput_step,process.ALCARECOStreamSiStripCalMinBiasOutPath)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

#Setup FWK for multithreaded
process.options.numberOfThreads=cms.untracked.uint32(8)
process.options.numberOfStreams=cms.untracked.uint32(0)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customisePostEra_Run2_2018 

#call to customisation function customisePostEra_Run2_2018 imported from Configuration.DataProcessing.RecoTLR
process = customisePostEra_Run2_2018(process)

# End of customisation functions
#do not add changes to your config after this point (unless you know what you are doing)
from FWCore.ParameterSet.Utilities import convertToUnscheduled
process=convertToUnscheduled(process)


# Customisation from command line

#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

