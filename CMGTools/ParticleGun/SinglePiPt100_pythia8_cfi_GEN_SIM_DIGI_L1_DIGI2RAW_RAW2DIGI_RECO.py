# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: SinglePiPt100_pythia8_cfi --customise SLHCUpgradeSimulations/Configuration/postLS1Customs.customisePostLS1 --relval 25000,1000 --beamspot NominalCollision2015 --conditions auto:run2_mc -s GEN,SIM,DIGI:pdigi_valid,L1,DIGI2RAW,RAW2DIGI,RECO --datatier ALL -n 10 --magField 38T_PostLS1 --eventcontent FEVTDEBUGHLT --pileup=NoPileUp --fileout step2.root
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.Geometry.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedNominalCollision2015_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5000)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('SinglePiPt100_pythia8_cfi nevts:5000'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition
process.TestEventContent = cms.PSet(
 outputCommands = cms.untracked.vstring(),
 splitLevel = cms.untracked.int32(0),
 eventAutoFlushCompressedSize=cms.untracked.int32(5*1024*1024)
 )

process.TestEventContent.outputCommands.extend(process.RECOSIMEventContent.outputCommands)
process.TestEventContent.outputCommands.extend(process.SimTrackerDEBUG.outputCommands)
process.TestEventContent.outputCommands.extend(process.SimGeneralFEVTDEBUG.outputCommands)


process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        #SelectEvents = cms.vstring('generation_step')
        SelectEvents = cms.vstring('filter')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('ALL'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(1048576),
    fileName = cms.untracked.string('pion100GeV.root'),
    #outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    outputCommands = process.TestEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

#filter:
process.displacedVertexSelector = cms.EDFilter(
     "PFDisplacedVertexSelector",
     src = cms.InputTag("particleFlowDisplacedVertex"),
 #    src = cms.InputTag("toto"),
#     cut = cms.string("position.x>20.0"),
     cut = cms.string("isNucl"),
     filter = cms.bool(True)
     )
process.filter = cms.Path(process.displacedVertexSelector)

# Additional output definition

# Other statements
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc', '')

process.generator = cms.EDFilter("Pythia8PtGun",
    PGunParameters = cms.PSet(
        AddAntiParticle = cms.bool(True),
        MaxEta = cms.double(2.5),
        MaxPhi = cms.double(3.14159265359),
        MaxPt = cms.double(100.01),
        MinEta = cms.double(-2.5),
        MinPhi = cms.double(-3.14159265359),
        MinPt = cms.double(99.99),
        ParticleID = cms.vint32(211)
    ),
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring()
    ),
    Verbosity = cms.untracked.int32(0),
    AddAntiParticle = cms.bool(False),
    firstRun = cms.untracked.uint32(1),
    psethack = cms.string('single pi pt 100')
)


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)
process.particleFlowDisplacedVertex.primaryVertexCut = 1.9

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.FEVTDEBUGHLToutput_step,process.filter)
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

# customisation of the process.

# Automatic addition of the customisation function from SLHCUpgradeSimulations.Configuration.postLS1Customs
from SLHCUpgradeSimulations.Configuration.postLS1Customs import customisePostLS1 

#call to customisation function customisePostLS1 imported from SLHCUpgradeSimulations.Configuration.postLS1Customs
process = customisePostLS1(process)

# End of customisation functions

