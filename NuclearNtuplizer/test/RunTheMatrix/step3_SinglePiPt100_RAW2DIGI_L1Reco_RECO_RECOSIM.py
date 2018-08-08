# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step3 --conditions auto:phase1_2018_realistic -n 10 --era Run2_2018 --eventcontent FEVTDEBUGHLT --runUnscheduled -s RAW2DIGI,L1Reco,RECO,RECOSIM --datatier GEN-SIM-RECO --geometry DB:Extended
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('RECO',eras.Run2_2018)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.RecoSim_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
#'file:step3_DIGI2RAW.root'
# part 1
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_0.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_1.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_10.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_100.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_101.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_102.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_103.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_104.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_105.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_106.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_107.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_108.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_109.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_11.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_110.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_111.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_112.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_113.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_114.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_115.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_116.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_117.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_118.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_119.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_12.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_120.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_121.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_122.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_123.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_124.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_125.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_126.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_127.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_128.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_129.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_13.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_130.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_131.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_132.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_133.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_134.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_135.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_136.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_137.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_138.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_139.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_14.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_140.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_141.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_142.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_143.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_144.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_145.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_146.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_147.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_148.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_149.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_15.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_150.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_151.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_152.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_153.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_154.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_155.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_156.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_157.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_158.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_16.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_160.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_161.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_162.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_163.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_164.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_165.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_166.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_167.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_168.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_169.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_17.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_170.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_171.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_173.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_174.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_175.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_176.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_177.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_178.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_179.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_18.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_180.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_181.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_182.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_183.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_184.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_185.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_186.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_187.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_188.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_189.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_19.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_190.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_191.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_192.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_193.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_194.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_195.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_196.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_197.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_198.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_199.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_2.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_20.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_200.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_201.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_202.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_204.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_205.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_206.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_207.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_208.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_209.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_21.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_210.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_211.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_212.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_213.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_214.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_215.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_216.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_217.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_218.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_219.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_22.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_220.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_221.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_222.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_223.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_224.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_225.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_226.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_227.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_228.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_229.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_23.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_230.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_231.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_232.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_233.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_234.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_235.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_236.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_237.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_238.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_239.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_24.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_240.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_241.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_242.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_243.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_244.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_245.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_246.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_247.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_248.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_249.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_25.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_250.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_251.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_252.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_26.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_27.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_28.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_29.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_3.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_30.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_31.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_32.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_33.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_34.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_35.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_36.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_37.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_38.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_39.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_4.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_40.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_41.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_42.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_43.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_44.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_45.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_46.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_47.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_48.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_49.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_5.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_50.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_51.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_52.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_53.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_54.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_55.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_56.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_57.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_58.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_59.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_6.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_60.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_61.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_62.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_63.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_64.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_65.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_66.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_67.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_68.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_69.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_7.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_70.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_71.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_72.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_73.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_74.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_75.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_76.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_77.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_78.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_79.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_8.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_80.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_81.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_82.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_83.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_84.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_85.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_86.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_87.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_88.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_89.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_9.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_90.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_91.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_92.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_93.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_94.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_95.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_96.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_97.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_98.root',
'file:/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion100GeV_step2/step2_DIGI_L1_DIGI2RAW_HLT_99.root'

),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('step3 nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('step3_RAW2DIGI_L1Reco_RECO_RECOSIM.root'),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.recosim_step = cms.Path(process.recosim)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.recosim_step,process.endjob_step,process.FEVTDEBUGHLToutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

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
