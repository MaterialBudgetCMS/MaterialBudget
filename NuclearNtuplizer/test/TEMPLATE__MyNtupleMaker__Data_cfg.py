# -*- coding: utf-8 -*-
#############################################################

#############################################################

import FWCore.ParameterSet.Config as cms

process = cms.Process("MyNtupleMaker")

from MyCode.Configuration.ConditionsDefs_cff import *
loadConditionsDefs(process)

from MyCode.Configuration.EventSelectionData_cff import *
customizeTrigger(process)
#process.MuTriggerFilter.triggerConditions = cms.vstring('CHANGEMETRIGGERPATH')
process.MuTriggerFilter.triggerConditions = cms.vstring(
  #################################################################################################
  "HLT_DoubleMu3_v3",                # 5.0e32
  "HLT_DoubleMu3_v4",                # 5.0e32
  "HLT_DoubleMu3_v5",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu3_v6",                         # 1.0e33
  "HLT_DoubleMu3_v7",                                  # 1.4e33
  #
  "HLT_DoubleMu3_v9",                                           # 2.0e33
  "HLT_DoubleMu3_v10",                                                   # 3.0e33
  #
  #
  "HLT_DoubleMu3_v13",                                                            # 5.0e33
  "HLT_DoubleMu3_v14",                                                            # 5.0e33
  #################################################################################################
  "HLT_DoubleMu4_Acoplanarity03_v1", # 5.0e32
  "HLT_DoubleMu4_Acoplanarity03_v2", # 5.0e32
  "HLT_DoubleMu4_Acoplanarity03_v3",          # 1.0e33
  "HLT_DoubleMu4_Acoplanarity03_v4",          # 1.0e33 # 1.4e33
  "HLT_DoubleMu4_Acoplanarity03_v5",          # 1.0e33
  "HLT_DoubleMu4_Acoplanarity03_v6",                   # 1.4e33
  #
  "HLT_DoubleMu4_Acoplanarity03_v8",                            # 2.0e33
  #################################################################################################
  "HLT_DoubleMu5_Acoplanarity03_v1",          # 1.0e33 # 1.4e33
  "HLT_DoubleMu5_Acoplanarity03_v2",          # 1.0e33
  "HLT_DoubleMu5_Acoplanarity03_v3",                   # 1.4e33
  #
  "HLT_DoubleMu5_Acoplanarity03_v5",                            # 2.0e33
  "HLT_DoubleMu5_Acoplanarity03_v6",                                     # 3.0e33
  #################################################################################################
  "HLT_DoubleMu5_IsoMu5_v5",                           # 1.4e33
  #
  "HLT_DoubleMu5_IsoMu5_v7",                                    # 2.0e33
  "HLT_DoubleMu5_IsoMu5_v8",                                             # 3.0e33
  #
  #
  "HLT_DoubleMu5_IsoMu5_v11",                                                     # 5.0e33
  "HLT_DoubleMu5_IsoMu5_v12",                                                     # 5.0e33
  #################################################################################################
  "HLT_DoubleMu5_v1",                                                    # 3.0e33
  #
  #
  "HLT_DoubleMu5_v4",                                                             # 5.0e33
  "HLT_DoubleMu5_v5",                                                             # 5.0e33
  #################################################################################################
  "HLT_DoubleMu6_Acoplanarity03_v1",                                     # 3.0e33
  #################################################################################################
  "HLT_DoubleMu6_v1",                # 5.0e32
  "HLT_DoubleMu6_v2",                # 5.0e32
  "HLT_DoubleMu6_v3",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu6_v4",                         # 1.0e33
  "HLT_DoubleMu6_v5",                                  # 1.4e33
  #
  "HLT_DoubleMu6_v7",                                           # 2.0e33
  "HLT_DoubleMu6_v8",                                                    # 3.0e33
  #################################################################################################
  "HLT_DoubleMu7_Acoplanarity03_v3",                                              # 5.0e33
  "HLT_DoubleMu7_Acoplanarity03_v4",                                              # 5.0e33
  #################################################################################################
  "HLT_DoubleMu7_v1",                # 5.0e32
  "HLT_DoubleMu7_v2",                # 5.0e32
  "HLT_DoubleMu7_v3",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu7_v4",                         # 1.0e33
  "HLT_DoubleMu7_v5",                                  # 1.4e33
  #
  "HLT_DoubleMu7_v7",                                           # 2.0e33
  "HLT_DoubleMu7_v8",                                                    # 3.0e33
  #
  #
  "HLT_DoubleMu7_v11",                                                            # 5.0e33
  "HLT_DoubleMu7_v12",                                                            # 5.0e33
  #################################################################################################
  "HLT_TripleMu5_v2",                # 5.0e32
  "HLT_TripleMu5_v3",                # 5.0e32
  "HLT_TripleMu5_v4",                         # 1.0e33 # 1.4e33
  "HLT_TripleMu5_v5",                         # 1.0e33
  "HLT_TripleMu5_v6",                                  # 1.4e33
  #
  "HLT_TripleMu5_v8",                                           # 2.0e33
  "HLT_TripleMu5_v9",                                                    # 3.0e33
  #
  #
  "HLT_TripleMu5_v12",                                                            # 5.0e33
  "HLT_TripleMu5_v13",                                                            # 5.0e33
  #################################################################################################
)



process.MuTriggerFilter.hltResults = cms.InputTag( "TriggerResults", "", "HLT" )

from MyCode.Configuration.JetCorrections_cff import *
produceAK5PFJetsL2L3(process)

from MyCode.Configuration.BTagging_cff import *
produceBTagging(process)

from MyCode.Configuration.PATMuonMaker_cff import *
customizePAT(process)
process.myMuonTriggerMatchHLTMuons.andOr = cms.bool( True )
#process.myMuonTriggerMatchHLTMuons.pathNames = cms.vstring( 'CHANGEMETRIGGERPATH' )
process.myMuonTriggerMatchHLTMuons.pathNames = cms.vstring(
  #################################################################################################
  "HLT_DoubleMu3_v3",                # 5.0e32
  "HLT_DoubleMu3_v4",                # 5.0e32
  "HLT_DoubleMu3_v5",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu3_v6",                         # 1.0e33
  "HLT_DoubleMu3_v7",                                  # 1.4e33
  #
  "HLT_DoubleMu3_v9",                                           # 2.0e33
  "HLT_DoubleMu3_v10",                                                   # 3.0e33
  #
  #
  "HLT_DoubleMu3_v13",                                                            # 5.0e33
  "HLT_DoubleMu3_v14",                                                            # 5.0e33
  #################################################################################################
  "HLT_DoubleMu4_Acoplanarity03_v1", # 5.0e32
  "HLT_DoubleMu4_Acoplanarity03_v2", # 5.0e32
  "HLT_DoubleMu4_Acoplanarity03_v3",          # 1.0e33
  "HLT_DoubleMu4_Acoplanarity03_v4",          # 1.0e33 # 1.4e33
  "HLT_DoubleMu4_Acoplanarity03_v5",          # 1.0e33
  "HLT_DoubleMu4_Acoplanarity03_v6",                   # 1.4e33
  #
  "HLT_DoubleMu4_Acoplanarity03_v8",                            # 2.0e33
  #################################################################################################
  "HLT_DoubleMu5_Acoplanarity03_v1",          # 1.0e33 # 1.4e33
  "HLT_DoubleMu5_Acoplanarity03_v2",          # 1.0e33
  "HLT_DoubleMu5_Acoplanarity03_v3",                   # 1.4e33
  #
  "HLT_DoubleMu5_Acoplanarity03_v5",                            # 2.0e33
  "HLT_DoubleMu5_Acoplanarity03_v6",                                     # 3.0e33
  #################################################################################################
  "HLT_DoubleMu5_IsoMu5_v5",                           # 1.4e33
  #
  "HLT_DoubleMu5_IsoMu5_v7",                                    # 2.0e33
  "HLT_DoubleMu5_IsoMu5_v8",                                             # 3.0e33
  #
  #
  "HLT_DoubleMu5_IsoMu5_v11",                                                     # 5.0e33
  "HLT_DoubleMu5_IsoMu5_v12",                                                     # 5.0e33
  #################################################################################################
  "HLT_DoubleMu5_v1",                                                    # 3.0e33
  #
  #
  "HLT_DoubleMu5_v4",                                                             # 5.0e33
  "HLT_DoubleMu5_v5",                                                             # 5.0e33
  #################################################################################################
  "HLT_DoubleMu6_Acoplanarity03_v1",                                     # 3.0e33
  #################################################################################################
  "HLT_DoubleMu6_v1",                # 5.0e32
  "HLT_DoubleMu6_v2",                # 5.0e32
  "HLT_DoubleMu6_v3",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu6_v4",                         # 1.0e33
  "HLT_DoubleMu6_v5",                                  # 1.4e33
  #
  "HLT_DoubleMu6_v7",                                           # 2.0e33
  "HLT_DoubleMu6_v8",                                                    # 3.0e33
  #################################################################################################
  "HLT_DoubleMu7_Acoplanarity03_v3",                                              # 5.0e33
  "HLT_DoubleMu7_Acoplanarity03_v4",                                              # 5.0e33
  #################################################################################################
  "HLT_DoubleMu7_v1",                # 5.0e32
  "HLT_DoubleMu7_v2",                # 5.0e32
  "HLT_DoubleMu7_v3",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu7_v4",                         # 1.0e33
  "HLT_DoubleMu7_v5",                                  # 1.4e33
  #
  "HLT_DoubleMu7_v7",                                           # 2.0e33
  "HLT_DoubleMu7_v8",                                                    # 3.0e33
  #
  #
  "HLT_DoubleMu7_v11",                                                            # 5.0e33
  "HLT_DoubleMu7_v12",                                                            # 5.0e33
  #################################################################################################
  "HLT_TripleMu5_v2",                # 5.0e32
  "HLT_TripleMu5_v3",                # 5.0e32
  "HLT_TripleMu5_v4",                         # 1.0e33 # 1.4e33
  "HLT_TripleMu5_v5",                         # 1.0e33
  "HLT_TripleMu5_v6",                                  # 1.4e33
  #
  "HLT_TripleMu5_v8",                                           # 2.0e33
  "HLT_TripleMu5_v9",                                                    # 3.0e33
  #
  #
  "HLT_TripleMu5_v12",                                                            # 5.0e33
  "HLT_TripleMu5_v13",                                                            # 5.0e33
  #################################################################################################
)


from MyCode.Configuration.FileSourceData_cff import *
customizeSource(process)
process.GlobalTag.globaltag = 'CHANGEMEGLOBALTAG::All'

#define number of events to be processed (-1 means all)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.MessageLogger = cms.Service(
                                    "MessageLogger",
                                    destinations = cms.untracked.vstring('MyNtupleMaker__CHANGEMENAME.txt'),#qui si decide il file di output
                                    default = cms.untracked.PSet(
                                    reportEvery = cms.untracked.int32(10000)#qui riporta i messaggi ogni ()
                                   ),
)

process.load('MyCode.MyNtupleMaker.MyNtupleMaker_cfi')
process.MyNtupleMaking.jetsTag               = "ak5PFJetsL2L3"
process.MyNtupleMaking.TrackJetsTag          = "ak5TrackJets"
#process.MyNtupleMaking.SaveGenP              = True
#process.MyNtupleMaking.SaveAssociationByHits = True
#process.MyNtupleMaking.SaveAssociationByChi2 = True

#process.MyNtupleMaking.SaveDiMuonVertices = cms.bool(False)

#process.MyNtupleMaking.TriggerPaths = cms.vstring('CHANGEMETRIGGERPATH')
process.MyNtupleMaking.TriggerPaths          = cms.vstring(
  #################################################################################################
  "HLT_DoubleMu3_v3",                # 5.0e32
  "HLT_DoubleMu3_v4",                # 5.0e32
  "HLT_DoubleMu3_v5",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu3_v6",                         # 1.0e33
  "HLT_DoubleMu3_v7",                                  # 1.4e33
  #
  "HLT_DoubleMu3_v9",                                           # 2.0e33
  "HLT_DoubleMu3_v10",                                                   # 3.0e33
  #
  #
  "HLT_DoubleMu3_v13",                                                            # 5.0e33
  "HLT_DoubleMu3_v14",                                                            # 5.0e33
  #################################################################################################
  "HLT_DoubleMu4_Acoplanarity03_v1", # 5.0e32
  "HLT_DoubleMu4_Acoplanarity03_v2", # 5.0e32
  "HLT_DoubleMu4_Acoplanarity03_v3",          # 1.0e33
  "HLT_DoubleMu4_Acoplanarity03_v4",          # 1.0e33 # 1.4e33
  "HLT_DoubleMu4_Acoplanarity03_v5",          # 1.0e33
  "HLT_DoubleMu4_Acoplanarity03_v6",                   # 1.4e33
  #
  "HLT_DoubleMu4_Acoplanarity03_v8",                            # 2.0e33
  #################################################################################################
  "HLT_DoubleMu5_Acoplanarity03_v1",          # 1.0e33 # 1.4e33
  "HLT_DoubleMu5_Acoplanarity03_v2",          # 1.0e33
  "HLT_DoubleMu5_Acoplanarity03_v3",                   # 1.4e33
  #
  "HLT_DoubleMu5_Acoplanarity03_v5",                            # 2.0e33
  "HLT_DoubleMu5_Acoplanarity03_v6",                                     # 3.0e33
  #################################################################################################
  "HLT_DoubleMu5_IsoMu5_v5",                           # 1.4e33
  #
  "HLT_DoubleMu5_IsoMu5_v7",                                    # 2.0e33
  "HLT_DoubleMu5_IsoMu5_v8",                                             # 3.0e33
  #
  #
  "HLT_DoubleMu5_IsoMu5_v11",                                                     # 5.0e33
  "HLT_DoubleMu5_IsoMu5_v12",                                                     # 5.0e33
  #################################################################################################
  "HLT_DoubleMu5_v1",                                                    # 3.0e33
  #
  #
  "HLT_DoubleMu5_v4",                                                             # 5.0e33
  "HLT_DoubleMu5_v5",                                                             # 5.0e33
  #################################################################################################
  "HLT_DoubleMu6_Acoplanarity03_v1",                                     # 3.0e33
  #################################################################################################
  "HLT_DoubleMu6_v1",                # 5.0e32
  "HLT_DoubleMu6_v2",                # 5.0e32
  "HLT_DoubleMu6_v3",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu6_v4",                         # 1.0e33
  "HLT_DoubleMu6_v5",                                  # 1.4e33
  #
  "HLT_DoubleMu6_v7",                                           # 2.0e33
  "HLT_DoubleMu6_v8",                                                    # 3.0e33
  #################################################################################################
  "HLT_DoubleMu7_Acoplanarity03_v3",                                              # 5.0e33
  "HLT_DoubleMu7_Acoplanarity03_v4",                                              # 5.0e33
  #################################################################################################
  "HLT_DoubleMu7_v1",                # 5.0e32
  "HLT_DoubleMu7_v2",                # 5.0e32
  "HLT_DoubleMu7_v3",                         # 1.0e33 # 1.4e33
  "HLT_DoubleMu7_v4",                         # 1.0e33
  "HLT_DoubleMu7_v5",                                  # 1.4e33
  #
  "HLT_DoubleMu7_v7",                                           # 2.0e33
  "HLT_DoubleMu7_v8",                                                    # 3.0e33
  #
  #
  "HLT_DoubleMu7_v11",                                                            # 5.0e33
  "HLT_DoubleMu7_v12",                                                            # 5.0e33
  #################################################################################################
  "HLT_TripleMu5_v2",                # 5.0e32
  "HLT_TripleMu5_v3",                # 5.0e32
  "HLT_TripleMu5_v4",                         # 1.0e33 # 1.4e33
  "HLT_TripleMu5_v5",                         # 1.0e33
  "HLT_TripleMu5_v6",                                  # 1.4e33
  #
  "HLT_TripleMu5_v8",                                           # 2.0e33
  "HLT_TripleMu5_v9",                                                    # 3.0e33
  #
  #
  "HLT_TripleMu5_v12",                                                            # 5.0e33
  "HLT_TripleMu5_v13",                                                            # 5.0e33
  #################################################################################################
)
 

process.TFileService = cms.Service(
                                   "TFileService",
                                   fileName = cms.string('Ntuple__CHANGEMENAME.root' )
)

process.ana_step = cms.Path(
                            process.FilterSequence2011 *
                            process.ak5PFJetsL2L3 *
                            process.newJetTracksAssociator *
                            process.newBTaggingSequence *
                            process.kinkFinder *
                            process.patDefaultSequence *
#                            process.genParticlePlusGEANT *
#                            process.TrackMCMatcherByChi2 *
#                            process.globalMuonAssociatorByHits *
#                            process.globalMuonMuOnlyAssociatorByHits *
#                            process.globalMuonTkOnlyAssociatorByHits *
#                            process.standAloneMuonAssociatorByHits *
                            process.MyNtupleMaking

)

process.analyze = cms.EDAnalyzer('EventContentAnalyzer')
process.edca = cms.Path(process.analyze)
# Schedule definition
process.schedule = cms.Schedule(process.ana_step)


