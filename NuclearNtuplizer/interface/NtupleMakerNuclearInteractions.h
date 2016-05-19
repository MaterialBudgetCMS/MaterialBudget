#ifndef NtupleMakerNuclearInteractions_h
#define NtupleMakerNuclearInteractions_h

/* ****************************************** */
/*                                            */
/* Tracker Material with Nuclear Interactions */
/*                                            */
/*               Nicola Pozzobon              */
/*                    2013                    */
/*                                            */
/* ****************************************** */

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/ParticleFlowReco/interface/PFDisplacedVertex.h"
#include "DataFormats/ParticleFlowReco/interface/PFDisplacedVertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Math/interface/deltaPhi.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertexContainer.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
//#include "SimTracker/TrackAssociation/interface/ParametersDefinerForTP.h"
//#include "SimTracker/TrackAssociation/interface/TrackAssociatorBase.h" // not exist anymore
#include "TrackAssociatorBase.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"

#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"

#include <TTree.h>
#include <TFile.h>

class NtupleMakerNuclearInteractions : public edm::EDAnalyzer
{
  public :
    explicit NtupleMakerNuclearInteractions( const edm::ParameterSet& );
    ~NtupleMakerNuclearInteractions(){};

  private :
    virtual void beginJob();
//    virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    virtual void analyze( const edm::Event&, const edm::EventSetup& );
    virtual void endJob();

    bool isNuclearInteraction( const TrackingVertex& ) const;
    bool isKaonDecay( const TrackingVertex& ) const;
    bool isConversion( const TrackingVertex& ) const;
    double      VectorParallelR( const TrackingVertex& VecSim, const reco::PFDisplacedVertex& ) const;
    double VectorPerpendicularR( const TrackingVertex&, const reco::PFDisplacedVertex& ) const;

    float getKaonMass( const reco::PFDisplacedVertex& ) const;
    bool isSimVertexOutsideAssCut(const TrackingVertex&, const reco::PFDisplacedVertex&) const;


    //Data members for consumes
    edm::EDGetTokenT<reco::VertexCollection> recoVertexToken;
    edm::EDGetTokenT<std::vector<PileupSummaryInfo>> addPileupInfoToken;
    edm::EDGetTokenT<reco::BeamSpot> offlineBeamSpotToken;
    edm::EDGetTokenT<reco::PFDisplacedVertexCollection> particleFlowDisplacedVertexToken;   
    edm::EDGetTokenT<TrackingVertexCollection> trackingParticlesToken;

    TTree* outputTree;

    /// General
    bool isRealData;
    unsigned int runNumber;
    unsigned int eventNumber;
    unsigned int lumiSection;

    /// Primary vertices
    unsigned int numberOfPV;
    std::vector< double > *PV_x;
    std::vector< double > *PV_y;
    std::vector< double > *PV_z;
    std::vector< double > *PV_xError;
    std::vector< double > *PV_yError;
    std::vector< double > *PV_zError;
    std::vector< bool > *PV_isFake;

    /// MC PileUp
    unsigned int numberOfMC_PUInfo;
    std::vector< unsigned int > *MC_PUInfo_bunchCrossing;
    std::vector< unsigned int > *MC_PUInfo_numberOfInteractions;

    /// BeamSpot
    double BS_x;
    double BS_y;
    double BS_z;
    double BS_zSigma;
    double BS_dxdy;
    double BS_dydz;
    double BS_xWidth;
    double BS_yWidth;

    /// Tracking Vertices
    unsigned int numberOfMC_TrkV;
    std::vector< bool > *MC_TrkV_isNuclearInteraction;
    std::vector< bool > *MC_TrkV_isKaonDecay;
    std::vector< bool > *MC_TrkV_isConversion;
    std::vector< double > *MC_TrkV_x;
    std::vector< double > *MC_TrkV_y;
    std::vector< double > *MC_TrkV_z;
    std::vector< double > *MC_TrkV_momentumInc_pt;
    std::vector< double > *MC_TrkV_momentumInc_phi;
    std::vector< double > *MC_TrkV_momentumInc_theta;
    std::vector< double > *MC_TrkV_Inc_charge;
    std::vector< int > *MC_TrkV_Inc_pdgId;
    std::vector< double > *MC_TrkV_momentumOut_pt;
    std::vector< double > *MC_TrkV_momentumOut_phi;
    std::vector< double > *MC_TrkV_momentumOut_theta;
    std::vector< double > *MC_TrkV_momentumOut_mass;
    std::vector< unsigned int > *MC_TrkV_numberOfChargedParticles_0p2;
    std::vector< unsigned int > *MC_TrkV_numberOfChargedParticles_0p5;
    std::vector< unsigned int > *MC_TrkV_numberOfChargedParticles_1p0;
    std::vector< unsigned int > *MC_TrkV_numberOfChargedParticles_Out0p2;
    std::vector< unsigned int > *MC_TrkV_numberOfChargedParticles_Out0p5;
    std::vector< unsigned int > *MC_TrkV_numberOfChargedParticles_Out1p0;
    std::vector< bool > *MC_TrkV_isAssociatedPF;
    std::vector< unsigned int > *MC_TrkV_associationPFDVIdx;
    std::vector< double > *MC_TrkV_associationPFDV_deltaR2d;
    std::vector< double > *MC_TrkV_associationPFDV_deltaR3d;
    std::vector< double > *MC_TrkV_associationPFDV_deltaR3dPerpendicular;
    std::vector< double > *MC_TrkV_associationPFDV_deltaR3dParallel;
/*
    std::vector< double > *MC_TrkV_associationDeltaPt;
    std::vector< double > *MC_TrkV_associationDeltaPhi;
    std::vector< double > *MC_TrkV_associationDeltaTheta;
    std::vector< double > *MC_TrkV_associationDeltaX;
    std::vector< double > *MC_TrkV_associationDeltaY;
    std::vector< double > *MC_TrkV_associationDeltaZ;
    std::vector< bool > *MC_TrkV_associationIsNuclear;
    std::vector< bool > *MC_TrkV_associationIsNuclearLoose;
    std::vector< bool > *MC_TrkV_associationIsNuclearKink;
    std::vector< bool > *MC_TrkV_associationIsK0;
    std::vector< bool > *MC_TrkV_associationIsLambda;
    std::vector< bool > *MC_TrkV_associationIsLambdaBar;
    std::vector< bool > *MC_TrkV_associationIsKPlusLoose;
    std::vector< bool > *MC_TrkV_associationIsKMinusLoose;
    std::vector< bool > *MC_TrkV_associationIsConversionLoose;
    std::vector< bool > *MC_TrkV_associationIsLooper;
    std::vector< bool > *MC_TrkV_associationIsFake;
    std::vector< bool > *MC_TrkV_associationIsTherePrimaryTrack;
    std::vector< bool > *MC_TrkV_associationIsThereMergedTrack;
*/

    /// Displaced Vertices
    unsigned int numberOfPFDV;
    std::vector< double > *PFDV_x;
    std::vector< double > *PFDV_y;
    std::vector< double > *PFDV_z;
    std::vector< double > *PFDV_momentumInc_pt;
    std::vector< double > *PFDV_Inc_charge;
    std::vector< double > *PFDV_momentumInc_phi;
    std::vector< double > *PFDV_momentumInc_theta;
    std::vector< double > *PFDV_momentumOut_pt;
    std::vector< double > *PFDV_momentumOut_phi;
    std::vector< double > *PFDV_momentumOut_theta;
    std::vector< double > *PFDV_momentumOut_mass;
    std::vector< unsigned int > *PFDV_momentumOut_numberOfTracks;
    std::vector< unsigned int > *PFDV_numberOfTracks_0p0;
    std::vector< unsigned int > *PFDV_numberOfTracks_0p2;
    std::vector< unsigned int > *PFDV_numberOfTracks_0p5;
    std::vector< unsigned int > *PFDV_numberOfTracks_1p0;
    std::vector< unsigned int > *PFDV_numberOfTracks_Out0p0;
    std::vector< unsigned int > *PFDV_numberOfTracks_Out0p2;
    std::vector< unsigned int > *PFDV_numberOfTracks_Out0p5;
    std::vector< unsigned int > *PFDV_numberOfTracks_Out1p0;
    std::vector< bool > *PFDV_isNuclear;
    std::vector< bool > *PFDV_isNuclearLoose;
    std::vector< bool > *PFDV_isNuclearKink;
    std::vector< bool > *PFDV_isK0;
    std::vector< bool > *PFDV_isLambda;
    std::vector< bool > *PFDV_isLambdaBar;
    std::vector< bool > *PFDV_isKPlusLoose;
    std::vector< bool > *PFDV_isKMinusLoose;
    std::vector< bool > *PFDV_isConversionLoose;
    std::vector< bool > *PFDV_isLooper;
    std::vector< bool > *PFDV_isFake;
    std::vector< bool > *PFDV_isTherePrimaryTrack;
    std::vector< bool > *PFDV_isThereMergedTrack;
    std::vector< bool > *PFDV_isAssociatedMC;
    std::vector< double > *PFDV_deltaR3d_Associated;
    std::vector< double > *PFDV_deltaR2d_Associated;
    std::vector< unsigned int > *PFDV_associationMC_TrkVIdx;
    std::vector< std::vector< int > > *PFDV_vTrack_algo;
    std::vector< std::vector< double > > *PFDV_vTrack_pt;
    std::vector< std::vector< double > > *PFDV_vTrack_eta;
    std::vector< std::vector< double > > *PFDV_vTrack_phi;
    std::vector< std::vector< double > > *PFDV_vTrack_rho;
    std::vector< std::vector< unsigned int > > *PFDV_vTrack_numberOfValidHits;
    std::vector< std::vector< unsigned int > > *PFDV_vTrack_numberOfExpectedOuterHits;
    std::vector< std::vector< unsigned int > > *PFDV_vTrack_closestDxyPVIdx;
    std::vector< std::vector< double > > *PFDV_vTrack_closestDxyPVIdx_dxy;
    std::vector< std::vector< double > > *PFDV_vTrack_closestDxyPVIdx_dz;
    std::vector< std::vector< unsigned int > > *PFDV_vTrack_closestDzPVIdx;
    std::vector< std::vector< double > > *PFDV_vTrack_closestDzPVIdx_dxy;
    std::vector< std::vector< double > > *PFDV_vTrack_closestDzPVIdx_dz;
};

#endif

