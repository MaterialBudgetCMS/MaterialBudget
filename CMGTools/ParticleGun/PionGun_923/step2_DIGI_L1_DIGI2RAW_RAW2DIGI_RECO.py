# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:phase1_2017_realistic -n 10 --era Run2_2017 --eventcontent FEVTDEBUG -s DIGI:pdigi_valid,L1,DIGI2RAW,RAW2DIGI,RECO --datatier DIGI-RECO --beamspot Realistic50ns13TeVCollision --geometry DB:Extended
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring('/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_0.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_100.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_101.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_102.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_103.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_104.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_105.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_106.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_107.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_108.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_109.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_10.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_110.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_112.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_113.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_114.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_115.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_117.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_118.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_119.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_11.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_120.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_121.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_122.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_123.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_124.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_125.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_126.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_127.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_128.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_12.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_130.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_132.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_133.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_136.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_137.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_138.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_139.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_13.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_140.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_141.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_142.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_143.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_144.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_145.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_146.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_147.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_148.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_149.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_14.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_150.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_151.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_152.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_153.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_154.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_155.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_156.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_157.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_158.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_159.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_15.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_160.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_161.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_163.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_164.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_165.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_167.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_168.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_169.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_16.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_170.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_171.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_172.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_173.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_174.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_175.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_176.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_177.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_178.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_179.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_17.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_180.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_181.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_183.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_184.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_185.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_186.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_187.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_188.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_189.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_18.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_190.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_191.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_192.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_193.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_194.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_195.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_196.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_197.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_199.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_19.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_1.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_20.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_21.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_22.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_23.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_24.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_26.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_27.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_28.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_29.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_2.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_32.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_33.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_34.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_35.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_36.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_37.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_38.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_39.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_3.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_40.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_41.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_42.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_44.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_45.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_46.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_47.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_48.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_49.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_4.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_50.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_51.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_53.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_54.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_55.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_56.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_57.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_58.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_59.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_5.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_60.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_61.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_62.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_63.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_64.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_65.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_66.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_67.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_68.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_69.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_6.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_70.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_71.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_72.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_73.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_74.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_75.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_76.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_77.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_78.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_79.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_7.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_80.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_81.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_82.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_83.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_84.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_85.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_86.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_87.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_88.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_89.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_8.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_90.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_91.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_92.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_93.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_94.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_95.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_96.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_97.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_99.root',
'/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2017_923Geom/50GeV_GEN_SIM/SinglePiPt10_pythia8_cfi_GEN_SIM_9.root'),
    inputCommands = cms.untracked.vstring('keep *', 
        'drop *_genParticles_*_*', 
        'drop *_genParticlesForJets_*_*', 
        'drop *_kt4GenJets_*_*', 
        'drop *_kt6GenJets_*_*', 
        'drop *_iterativeCone5GenJets_*_*', 
        'drop *_ak4GenJets_*_*', 
        'drop *_ak7GenJets_*_*', 
        'drop *_ak8GenJets_*_*', 
        'drop *_ak4GenJetsNoNu_*_*', 
        'drop *_ak8GenJetsNoNu_*_*', 
        'drop *_genCandidatesForMET_*_*', 
        'drop *_genParticlesForMETAllVisible_*_*', 
        'drop *_genMetCalo_*_*', 
        'drop *_genMetCaloAndNonPrompt_*_*', 
        'drop *_genMetTrue_*_*', 
        'drop *_genMetIC5GenJs_*_*'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step2 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('DIGI-RECO'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('SinglePiPt10_pythia8_cfi_RECO.root'
),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGoutput_step = cms.EndPath(process.FEVTDEBUGoutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step,process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.FEVTDEBUGoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
