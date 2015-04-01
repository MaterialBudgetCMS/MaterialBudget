# -*- coding: utf-8 -*-
import FWCore.ParameterSet.Config as cms

MyNtupleMaking = cms.EDAnalyzer(
    #"MyNtupleMaker",
    "NtupleMakerNuclearInteractions",
    primaryVerticesTag     = cms.untracked.InputTag("offlinePrimaryVertices"),
    beamSpotTag            = cms.untracked.InputTag("offlineBeamSpot"),
    generalTrackTag        = cms.untracked.InputTag("generalTracks"),
    dEdx1Tag               = cms.InputTag('dedxHarmonic2'),
    genParticleTag         = cms.untracked.InputTag("genParticlePlusGEANT"),
    #pdfWeightTags          = cms.untracked.VInputTag("pdfWeights:cteq66", "pdfWeights:MRST2006nnlo", "pdfWeights:NNPDF10_100"),
    pdfWeightTag           = cms.untracked.InputTag("pdfWeights:cteq66"),
    muonTag                = cms.untracked.InputTag("muons"),
    muonPATTag             = cms.untracked.InputTag("selectedPatMuons"),
    muonKinkTag            = cms.untracked.InputTag("kinkFinder", ""),
    muonKinkRhoTag         = cms.untracked.InputTag("kinkFinder", "decRho"),
    muonKinkZTag           = cms.untracked.InputTag("kinkFinder", "decZ"),
    jetsTag                = cms.untracked.InputTag("ak5PFJets"),
    trackGenPAssocTag      = cms.untracked.InputTag("TrackMCMatcherByChi2"),
    muonMatchTag           = cms.untracked.string("myMuonTriggerMatchHLTMuons"),
    muonMatchMu3Tag        = cms.untracked.string("myMuonTriggerMatchHLTMuonsMu3"),
    triggerEventTag        = cms.untracked.InputTag("patTriggerEvent"),
    trackingParticleTag    = cms.untracked.InputTag("mix", "MergedTrackTruth"),
    RealData               = cms.bool(True),
    SaveGenP               = cms.bool(False),
    SaveReducedGenPIPInfo  = cms.bool(True),
    SavePdfWeights         = cms.bool(True),
    SaveTracks             = cms.bool(True),
    SaveReducedTrackIPInfo = cms.bool(False),
    SaveJets               = cms.bool(True),
    SaveBTagging           = cms.bool(True),
    SaveMuons              = cms.bool(True),
    SaveDiMuonVertices     = cms.bool(True),
    SaveTrigger            = cms.bool(True),
    SaveAssociationByChi2  = cms.bool(True),
    SaveAssociationByHits  = cms.bool(False),
    TriggerPaths           = cms.vstring("HLT_DoubleMu0","HLT_DoubleMu3", "HLT_Mu3", "HLT_Mu5", "HLT_Mu7", "HLT_Mu9", "HLT_Mu11"),
    NtupleVersion          = cms.uint32(3), # Ntuple versioning, to start keeping track of changes in the definition
    NtupleMinorVersion     = cms.uint32(0),  # Ntuple versioning, to start keeping track of changes in the definition
    propagateToMuon1       = cms.PSet(
                                useStation2 = cms.bool(False), 
                                useTrack = cms.string("tracker"),
                                useState = cms.string("atVertex"),  # in AOD
                                useSimpleGeometry = cms.bool(True) # use just one cylinder and two planes, not all the fancy chambers
    ),
    propagateToMuon2      = cms.PSet(
                                useStation2 = cms.bool(True), 
                                useTrack = cms.string("tracker"),
                                useState = cms.string("atVertex"),  # in AOD
                                useSimpleGeometry = cms.bool(True) # use just one cylinder and two planes, not all the fancy chambers
    )
)
