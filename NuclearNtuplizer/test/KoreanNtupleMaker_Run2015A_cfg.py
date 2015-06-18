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
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data', '')

### Define source
process.source = cms.Source("PoolSource",
  fileNames = cms.untracked.vstring(
    #'file:/afs/cern.ch/work/j/jungmin/public/tracker/CMSSW_7_4_0/src/MaterialBudget/CMGTools/ParticleGun/withNI/pion100GeV.root'
    ######100GeV withNI###########
#   'file:root://eoscms.cern.ch//eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/MC/ParticleGun/CMSSW_7_4_0/PionGun100GeVfilterNI_1M_v2/pion100GeV_237.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/0AE1AFA5-220B-E511-B7D4-02163E014239.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/0CADC28A-390B-E511-853D-02163E0121C5.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/10D9909F-260B-E511-9A53-02163E014113.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/168661B7-300B-E511-870A-02163E013653.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/1A1D4A18-2E0B-E511-9A5A-02163E012925.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/1CC6C5E8-220B-E511-8640-02163E011ACE.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/1E5ADEF5-200B-E511-B722-02163E01184D.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/1E84CAD2-230B-E511-88F9-02163E013861.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/20A71F54-550B-E511-B4DD-02163E0142F3.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/20FBFCC6-240B-E511-A826-02163E012925.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/2275F0CE-200B-E511-B714-02163E0143FC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/26CE2328-410B-E511-833A-02163E01184E.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/2A151439-2C0B-E511-A1E1-02163E01383E.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/2C44A971-230B-E511-B5E3-02163E012925.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/34DC8712-220B-E511-8CE6-02163E0146EE.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/3C37180B-220B-E511-AA12-02163E014220.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/4862A3D9-220B-E511-A2CF-02163E013491.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/4A84D28D-160B-E511-B9A2-02163E0142BF.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/542C34A0-270B-E511-862E-02163E011BDB.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/5C1F3477-230B-E511-BD27-02163E0142D7.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/62A6E7A7-250B-E511-A56F-02163E011DBC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/64F30127-290B-E511-BF4E-02163E011A8B.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/6CF3471A-420B-E511-BF19-02163E011ACE.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/6E409396-170B-E511-9F1C-02163E01288E.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/72942193-160B-E511-8134-02163E014565.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/78691E83-170B-E511-9F99-02163E01262E.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/7CC0D075-350B-E511-92A9-02163E0144DC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/7EAB39AD-2F0B-E511-A02B-02163E014565.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/84E77A7A-250B-E511-A3E3-02163E011B55.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/86F37DAA-250B-E511-B64E-02163E01475C.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/88070E70-230B-E511-B786-02163E0133E6.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/8A15372C-240B-E511-A816-02163E0118EC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/8C8C610C-280B-E511-BF59-02163E01475E.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/8E2E9AAA-250B-E511-95CE-02163E013617.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/8E40A5F7-290B-E511-A108-02163E0139C0.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/94505B6B-1C0B-E511-90AC-02163E01396D.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/9A8C4DF4-220B-E511-9340-02163E011C14.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/9CFA6FCA-230B-E511-BCC9-02163E0134CC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/A082D468-260B-E511-B4C1-02163E0121DA.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/A693F915-240B-E511-8F86-02163E011A86.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/A8C0018C-170B-E511-B139-02163E013604.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/B0472053-160B-E511-9FC9-02163E01288E.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/B628561E-240B-E511-8D9A-02163E014215.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/B89BB985-200B-E511-B12C-02163E014239.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/BC57DB97-180B-E511-A70E-02163E0138BD.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/C446636A-2B0B-E511-9DD7-02163E014110.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/CE49A1A0-310B-E511-A0B1-02163E0134D2.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/D41DC168-240B-E511-A96D-02163E01338A.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/D6C1241C-260B-E511-9142-02163E0134CC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/DA7C76C1-2E0B-E511-86C9-02163E0140E8.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/DA8EC182-240B-E511-9D19-02163E0141D2.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/DE790703-1A0B-E511-8520-02163E012028.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/E692A589-240B-E511-89BE-02163E011BD8.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/EADC9DE0-270B-E511-BE4F-02163E012028.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/EC2AF0F4-250B-E511-9248-02163E0136A3.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/EE3D9096-240B-E511-B113-02163E014267.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/F06C8362-2A0B-E511-9C99-02163E0135BC.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/F28FBC09-250B-E511-A98B-02163E014204.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/F2E1E279-230B-E511-8F7C-02163E0139C0.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/F4E11D80-2B0B-E511-AE21-02163E0141D2.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/FC11E464-160B-E511-B2DC-02163E0135CA.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/FE0F20A6-200B-E511-A4F4-02163E011DA4.root',
'file:root://eoscms.cern.ch//eos/cms/store/data/Run2015A/ZeroBias1/RECO/PromptReco-v1/000/246/908/00000/FE6F6368-240B-E511-AEC3-02163E014742.root'
  ),
  secondaryFileNames = cms.untracked.vstring(
  )
)


### Define number of events to be processed (-1 means all)
#process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

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

### Root output
process.TFileService = cms.Service("TFileService",
  fileName = cms.string('Run201A_246908.root' )
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
