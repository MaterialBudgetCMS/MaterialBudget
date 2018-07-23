# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step2 --conditions auto:phase1_2018_realistic -s DIGI:pdigi_valid,L1,DIGI2RAW,HLT:@relval2018 --datatier GEN-SIM-DIGI-RAW -n 10 --geometry DB:Extended --era Run2_2018 --eventcontent FEVTDEBUGHLT
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('HLT',eras.Run2_2018)

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
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    dropDescendantsOfDroppedBranches = cms.untracked.bool(False),
    fileNames = cms.untracked.vstring(


'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_0.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_1.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_10.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_100.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_101.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_102.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_103.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_104.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_105.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_106.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_107.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_108.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_109.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_11.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_110.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_111.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_112.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_113.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_114.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_115.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_116.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_117.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_118.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_119.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_12.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_120.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_121.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_122.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_123.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_124.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_125.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_126.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_127.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_128.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_129.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_13.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_130.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_131.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_132.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_133.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_134.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_135.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_136.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_137.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_138.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_139.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_14.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_140.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_141.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_142.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_143.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_144.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_145.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_146.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_147.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_148.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_149.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_15.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_150.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_151.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_152.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_153.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_154.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_155.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_156.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_157.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_158.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_159.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_16.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_160.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_161.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_162.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_163.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_164.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_165.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_166.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_167.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_168.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_169.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_17.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_170.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_171.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_172.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_173.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_174.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_175.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_176.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_177.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_178.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_179.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_18.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_180.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_181.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_182.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_183.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_184.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_185.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_186.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_187.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_188.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_189.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_19.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_190.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_191.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_192.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_193.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_194.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_195.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_196.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_197.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_198.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_199.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_2.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_20.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_200.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_201.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_202.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_203.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_204.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_205.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_206.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_207.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_208.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_209.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_21.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_210.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_211.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_212.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_213.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_214.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_215.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_216.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_217.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_218.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_219.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_22.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_220.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_221.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_222.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_223.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_224.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_225.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_226.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_227.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_228.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_229.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_23.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_230.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_231.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_232.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_233.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_234.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_235.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_236.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_237.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_238.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_239.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_24.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_240.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_241.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_242.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_243.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_244.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_245.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_246.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_247.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_248.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_249.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_25.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_250.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_251.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_252.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_253.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_254.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_255.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_256.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_257.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_258.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_259.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_26.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_260.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_261.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_262.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_263.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_264.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_265.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_266.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_267.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_268.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_269.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_27.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_270.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_271.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_272.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_273.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_274.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_275.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_276.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_277.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_278.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_279.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_28.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_280.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_281.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_282.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_283.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_284.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_285.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_286.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_287.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_288.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_289.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_29.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_290.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_291.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_292.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_293.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_294.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_295.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_296.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_297.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_298.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_299.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_3.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_30.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_300.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_301.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_302.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_303.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_304.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_305.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_306.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_307.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_308.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_309.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_31.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_310.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_311.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_312.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_313.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_314.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_315.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_316.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_317.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_318.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_319.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_32.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_320.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_321.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_322.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_323.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_324.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step1/SinglePiPt100_pythia8_cfi_GEN_SIM_325.root'








),
    inputCommands = cms.untracked.vstring(
        'keep *', 
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
        'drop *_genMetIC5GenJs_*_*'
    ),
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

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step2_DIGI_L1_DIGI2RAW_HLT.root'),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
process.mix.digitizers = cms.PSet(process.theDigitizersValid)
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '')

# Path and EndPath definitions
process.digitisation_step = cms.Path(process.pdigi_valid)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.FEVTDEBUGHLToutput_step])
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from HLTrigger.Configuration.customizeHLTforMC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC 

#call to customisation function customizeHLTforMC imported from HLTrigger.Configuration.customizeHLTforMC
process = customizeHLTforMC(process)

# End of customisation functions

# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
