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

'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_0.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_1.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_10.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_100.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_101.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_102.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_103.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_104.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_105.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_106.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_107.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_108.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_109.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_11.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_110.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_111.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_112.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_113.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_114.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_115.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_116.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_117.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_118.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_119.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_12.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_120.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_121.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_122.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_123.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_124.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_125.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_126.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_127.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_128.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_129.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_13.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_130.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_131.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_132.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_133.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_134.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_135.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_136.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_137.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_138.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_139.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_14.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_140.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_142.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_143.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_144.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_145.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_146.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_147.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_148.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_149.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_15.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_150.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_151.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_152.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_153.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_154.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_155.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_156.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_157.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_158.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_159.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_16.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_160.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_161.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_162.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_163.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_164.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_165.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_166.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_167.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_168.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_169.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_17.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_170.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_171.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_172.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_173.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_174.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_175.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_176.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_177.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_178.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_179.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_18.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_180.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_181.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_182.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_183.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_184.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_185.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_186.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_187.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_188.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_189.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_19.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_190.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_191.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_192.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_193.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_194.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_195.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_196.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_197.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_198.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_199.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_2.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_20.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_21.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_22.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_23.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_24.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_25.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_26.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_27.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_28.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_29.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_3.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_30.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_31.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_32.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_33.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_34.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_35.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_36.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_37.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_38.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_39.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_4.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_40.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_41.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_42.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_43.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_44.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_45.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_46.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_47.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_48.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_49.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_5.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_50.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_51.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_52.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_53.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_54.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_55.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_56.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_57.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_58.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_59.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_6.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_60.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_61.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_62.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_63.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_64.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_65.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_66.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_67.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_68.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_69.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_7.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_70.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_71.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_72.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_73.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_74.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_75.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_76.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_77.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_78.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_79.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_8.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_80.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_81.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_82.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_83.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_84.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_85.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_86.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_87.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_88.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_89.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_9.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_90.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_91.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_92.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_93.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_95.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_96.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_97.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_98.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion50GeV_step1/SinglePiPt50_pythia8_cfi_GEN_SIM_99.root'









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
