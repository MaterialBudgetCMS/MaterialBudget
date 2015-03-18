# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

process = cms.Process("MyNtupleMaker")

### Import real conditions
from Configuration.StandardSequences.Services_cff import *
from Configuration.StandardSequences.GeometryExtended_cff import *
from Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff import *
from TrackingTools.TransientTrack.TransientTrackBuilder_cfi import *
from Configuration.StandardSequences.FrontierConditions_GlobalTag_cff import *

process.load('Configuration/StandardSequences/Services_cff')
#process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')

### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/work/m/mgouzevi/private/TRACKING/CMSSW_7_3_1/src/this_is_an_example.root'
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_0.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_1.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_2.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_3.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_4.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_5.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_6.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_8.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_10.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_11.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_12.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_13.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_14.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_15.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_16.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_17.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_18.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_20.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_21.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_23.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_24.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_25.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_26.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_27.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_28.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_29.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_30.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_31.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_32.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_33.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_34.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_35.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_36.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_37.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_38.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_40.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_41.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_42.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_43.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_44.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_45.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_46.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_47.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_48.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_49.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_50.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_51.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_52.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_54.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_55.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_56.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_57.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_58.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_59.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_60.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_61.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_62.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_63.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_64.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_65.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_66.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_67.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_69.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_70.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_71.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_72.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_73.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_74.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_75.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_76.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_77.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_78.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_79.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_80.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_81.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_82.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_83.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_84.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_85.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_87.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_88.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_89.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_90.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_91.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_92.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_93.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_95.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_96.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_97.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_98.root',
 'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun100GeVfilterNI/SinglePiPt100_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_RAW2DIGI_RECO_99.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_0.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_1.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_2.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_3.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_4.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_5.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_6.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_7.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_8.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_9.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_10.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_11.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_12.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_13.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_14.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_15.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_16.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_17.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_18.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_19.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_20.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_21.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_22.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_23.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_24.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_25.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_26.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_27.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_28.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_29.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_30.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_31.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_32.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_33.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_34.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_35.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_36.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_37.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_38.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_39.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_40.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_41.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_42.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_43.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_44.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_45.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_46.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_47.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_48.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_49.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_50.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_51.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_52.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_53.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_54.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_55.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_56.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_57.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_58.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_59.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_60.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_61.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_62.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_63.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_64.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_65.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_66.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_67.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_68.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_69.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_70.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_71.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_72.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_73.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_74.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_75.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_76.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_77.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_78.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_79.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_80.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_81.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_82.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_83.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_84.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_85.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_86.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_87.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_88.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_89.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_90.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_91.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_92.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_93.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_94.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_95.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_96.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_97.root',
  'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/PionGun10GeVfilterNI_v2/SinglePiPt10_Evt10000_98.root'
  ),
  secondaryFileNames = cms.untracked.vstring(
  )
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
)

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string('Ntuple_MC_prova_1.root' )
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
