#ifndef NtupleReaderNuclearInteractions_2015_h
#define NtupleReaderNuclearInteractions_2015_h

/* ****************************************** */
/*                                            */
/* Tracker Material with Nuclear Interactions */
/*                                            */
/*               Nicola Pozzobon              */
/*                    2013                    */
/*                                            */
/* ****************************************** */

#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
//#include <stdlib.h>
#include <vector>

#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TVector3.h>

class NtupleReaderNuclearInteractions_2015
{
  public :
    NtupleReaderNuclearInteractions_2015( const std::string fileList, const Long64_t maxEvents = 0 );
    ~NtupleReaderNuclearInteractions_2015();
    void beginJob();
    void analyze();
    void endJob();

  private:
    TChain* inputChain; /// Pointer to the input tree or chain
    Long64_t maxEventsToProcess;

    TFile* outputFile;

    double Bins[12];

    TH1D* hPFDV_CountEventsWithNI;

    TH1D* hMC_NumberNI;
   
    TH1D* hMC_TrkV_R;
    TH1D* hMC_TrkV_R_Barrel;
    TH1D* hMC_TrkV_R_isNuclearInteraction;

    TH1D* hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2;
    TH1D* hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2;

    TH1D* hMC_TrkV_R_isNuclearInteraction_Barrel;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0;
    TH1D* hMC_TrkV_R_isAssociatedPF;
    TH1D* hMC_TrkV_R_isAssociatedPF_Barrel;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0;
    TH1D* hMC_TrkV_R_associationPFDVIdx;
    TH1D* hMC_TrkV_R_associationPFDVIdx_Barrel;
    TH1D* hMC_TrkV_isNuclearInteraction;
    TH1D* hMC_TrkV_isNuclearInteraction_Barrel;
    TH1D* hMC_TrkV_isAssociatedPF;
    TH1D* hMC_TrkV_isAssociatedPF_Barrel;
    TH1D* hMC_TrkV_associationPFDVIdx;
    TH1D* hMC_TrkV_associationPFDVIdx_Barrel;

    TH1D* hMC_TrkV_associationPFDV_deltaR2d;
    TH1D* hMC_TrkV_associationPFDV_deltaR2d_Barrel;

    TH1D* hMC_TrkV_associationPFDV_deltaR3d;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Barrel;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Forward;

    TH1D* hMC_TrkV_associationPFDV_DuplicateR;
    TH1D* hMC_TrkV_associationPFDV_DuplicateVerR;
    TH1D* hMC_TrkV_associationPFDV_DuplicateVerXY;
    TH1D* hMC_TrkV_associationPFDV_DuplicateVerZ;
    TH1D* hMC_TrkV_associationPFDV_DuplicateR3d;
    TH1D* hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular;
    TH1D* hMC_TrkV_associationPFDV_DuplicateR3dParallel;
    TH1D* hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs;

    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Forward;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallelRel;

    TH1D* hMC_TrkV_associationPFDV_deltaChargeSource_Barrel;
    TH1D* hMC_TrkV_associationPFDV_deltaChargeSource_Forward;
    TH1D* hMC_TrkV_momentumOut_pt_Barrel;
    TH1D* hMC_TrkV_momentumInc_pt_Barrel;
    TH1D* hMC_TrkV_momentum_dtheta_Barrel;
    TH1D* hMC_TrkV_momentumOut_mass_Barrel;
    TH1D* hMC_TrkV_associationPFDV_pdgIdSource_Barrel;
    TH1D* hMC_TrkV_associationPFDV_pdgIdSource_Forward;

    TH1D* hMC_TrkV_pdgIdSource_Barrel;
    TH1D* hMC_TrkV_pdgIdSource_Forward;

    TH1D* hMC_TrkV_numberOftracks_0p2;
    TH1D* hMC_TrkV_numberOftracks_0p5;
    TH1D* hMC_TrkV_numberOftracks_1p0;


    TH1D* hPFDV_R;
    TH1D* hPFDV_R_Pipe;
    TH1D* hPFDV_R_BPix;
    TH1D* hPFDV_R_isAssociatedMC;
    TH1D* hPFDV_R_isAssociatedMC_Barrel;
    TH1D* hPFDV_deltaR2d_Associated_Barrel;
    TH1D* hPFDV_deltaR2d_Associated;
    TH1D* hPFDV_deltaR3d_Associated;
    TH1D* hPFDV_deltaR3d_Associated_Barrel;
    TH1D* hPFDV_deltaR3d_Associated_Forward;
    TH1D* hPFDV_deltaR3d_Associated_Rebin;
    TH1D* hPFDV_deltaR3d_Associated_Barrel_Rebin;
    TH1D* hPFDV_deltaR3d_Associated_Forward_Rebin;
    TH1D* hPFDV_isAssociatedMC;
    TH1D* hPFDV_isAssociatedMC_Barrel;
    TH1D* hPFDV_isAssociatedMC_isNuclear_Barrel;
    TH1D* hPFDV_associationMC_TrkVIdx;
    TH1D* hPFDV_associationMC_TrkVIdx_Barrel;
    TH1D* hPFDV_vTrack_pt;
    TH1D* hPFDV_numberOftracks_0p0;
    TH1D* hPFDV_numberOftracks_0p2;
    TH1D* hPFDV_numberOftracks_0p5;
    TH1D* hPFDV_numberOftracks_1p0;

    //only for one Sim Vertex with max pT out
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_MaxCut; 
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_MaxCut;
    TH1D* hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isNuclearInteraction_eta_Rlt4_3Tr0p2_MaxCut; 
    TH1D* hMC_TrkV_R_isAssociatedPF_eta_Rlt4_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isNuclearInteraction_eta_Rlt15_3Tr0p2_MaxCut; 
    TH1D* hMC_TrkV_R_isAssociatedPF_eta_Rlt15_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isNuclearInteraction_eta_Rgt15_3Tr0p2_MaxCut; 
    TH1D* hMC_TrkV_R_isAssociatedPF_eta_Rgt15_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2_MaxCut;
    TH1D* hMC_TrkV_momentumOut_pt_Barrel_MaxCut;
    TH1D* hMC_TrkV_momentumOut_pt_Forward_MaxCut;

    /// Histograms
    TH2D* hPFDV_XY_Map;
    TH2D* hPFDV_RhoPhi_Map;
    TH2D* hPFDV_XY_Map_BPix;
    TH2D* hPFDV_XY_Map_BPix_AbsZ25;
    TH2D* hPFDV_XY_Map_BPix_AbsZ20;
    TH2D* hPFDV_RhoPhi_Map_BPix;
    TH2D* hPFDV_RhoPhi_Map_Pipe;
    TH2D* hPFDV_RhoPhi_Map_BPix_AbsZ25;
    TH2D* hPFDV_RhoPhi_Map_BPix_AbsZ20;

    TH2D* hPFDV_XY_Map_Pipe;

    TH2D* hPFDV_ZR_Map;

//    TH2D* hPFDV_XY_Map_Corr;
//    TH2D* hPFDV_RhoPhi_Map_Corr;
//    TH2D* hPFDV_XY_Map_Corr_BPix;
//    TH2D* hPFDV_RhoPhi_Map_Corr_BPix;
//    TH2D* hPFDV_XY_Map_Corr_Pipe;
//    TH2D* hPFDV_RhoPhi_Map_Corr_Pipe;
//
//    TH2D* hPFDV_XY_Map_AbsZ25;
//    TH2D* hPFDV_RhoPhi_Map_AbsZ25;
//    TH2D* hPFDV_XY_Map_BPix_AbsZ25;
//    TH2D* hPFDV_RhoPhi_Map_BPix_AbsZ25;
    TH2D* hPFDV_XY_Map_Pipe_AbsZ25;
    TH2D* hPFDV_RhoPhi_Map_Pipe_AbsZ25;
//
//    TH2D* hPFDV_XY_Map_Corr_AbsZ25;
//    TH2D* hPFDV_RhoPhi_Map_Corr_AbsZ25;
//    TH2D* hPFDV_XY_Map_Corr_BPix_AbsZ25;
//    TH2D* hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25;
//    TH2D* hPFDV_XY_Map_Corr_Pipe_AbsZ25;
//    TH2D* hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25;
//
//    TH2D* hPFDV_XY_Map_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Weight;
//    TH2D* hPFDV_XY_Map_BPix_Weight;
//    TH2D* hPFDV_RhoPhi_Map_BPix_Weight;
//    TH2D* hPFDV_XY_Map_Pipe_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Pipe_Weight;
//
//    TH2D* hPFDV_XY_Map_Corr_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Corr_Weight;
//    TH2D* hPFDV_XY_Map_Corr_BPix_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Corr_BPix_Weight;
//    TH2D* hPFDV_XY_Map_Corr_Pipe_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Corr_Pipe_Weight;
//
//    TH2D* hPFDV_XY_Map_AbsZ25_Weight;
//    TH2D* hPFDV_RhoPhi_Map_AbsZ25_Weight;
//    TH2D* hPFDV_XY_Map_BPix_AbsZ25_Weight;
//    TH2D* hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight;
//    TH2D* hPFDV_XY_Map_Pipe_AbsZ25_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight;
//
//    TH2D* hPFDV_XY_Map_Corr_AbsZ25_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight;
//    TH2D* hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight;
//    TH2D* hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight;
//    TH2D* hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight;

    std::map<int, TH2D*> m_hPFDV_XY_Map;
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map;
    std::map<int, TH2D*> m_hPFDV_XY_Map_BPix;
    std::map<int, TH2D*> m_hPFDV_XY_Map_BPix_AbsZ25;
    std::map<int, TH2D*> m_hPFDV_XY_Map_BPix_AbsZ20;
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_BPix;
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_BPix_AbsZ25;
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_BPix_AbsZ20;
    std::map<int, TH2D*> m_hPFDV_XY_Map_Pipe;
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Pipe;

//    std::map<int, TH2D*> m_hPFDV_XY_Map_Corr;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Corr;
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Corr_BPix;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Corr_BPix;
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Corr_Pipe;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Corr_Pipe;
//
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Weight;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Weight;
//    std::map<int, TH2D*> m_hPFDV_XY_Map_BPix_Weight;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_BPix_Weight;
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Pipe_Weight;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Pipe_Weight;
//
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Corr_Weight;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Corr_Weight;
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Corr_BPix_Weight;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Corr_BPix_Weight;
//    std::map<int, TH2D*> m_hPFDV_XY_Map_Corr_Pipe_Weight;
//    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Corr_Pipe_Weight;



    /// General
    bool isRealData;
    unsigned int runNumber;
    unsigned int eventNumber;
    unsigned int lumiSection;

    TBranch *b_isRealData;
    TBranch *b_runNumber;
    TBranch *b_eventNumber;
    TBranch *b_lumiSection;

    /// Primary vertices
    unsigned int numberOfPV;
    std::vector< double > *PV_x;
    std::vector< double > *PV_y;
    std::vector< double > *PV_z;
    std::vector< double > *PV_xError;
    std::vector< double > *PV_yError;
    std::vector< double > *PV_zError;
    std::vector< bool > *PV_isFake;

    TBranch *b_numberOfPV;
    TBranch *b_PV_x;
    TBranch *b_PV_y;
    TBranch *b_PV_z;
    TBranch *b_PV_xError;
    TBranch *b_PV_yError;
    TBranch *b_PV_zError;
    TBranch *b_PV_isFake;

    /// MC PileUp
    unsigned int numberOfMC_PUInfo;
    std::vector< unsigned int > *MC_PUInfo_bunchCrossing;
    std::vector< unsigned int > *MC_PUInfo_numberOfInteractions;

    TBranch *b_numberOfMC_PUInfo;
    TBranch *b_MC_PUInfo_bunchCrossing;
    TBranch *b_MC_PUInfo_numberOfInteractions;

    /// BeamSpot
    double BS_x;
    double BS_y;
    double BS_z;
    double BS_zSigma;
    double BS_dxdy;
    double BS_dydz;
    double BS_xWidth;
    double BS_yWidth;

    TBranch *b_BS_x;
    TBranch *b_BS_y;
    TBranch *b_BS_z;
    TBranch *b_BS_zSigma;
    TBranch *b_BS_dxdy;
    TBranch *b_BS_dydz;
    TBranch *b_BS_xWidth;
    TBranch *b_BS_yWidth;

    /// Tracking Vertices
    unsigned int numberOfMC_TrkV;
    std::vector< bool > *MC_TrkV_isNuclearInteraction;
    std::vector< bool > *MC_TrkV_isKaonDecay;
    std::vector< bool > *MC_TrkV_isConversion;
    std::vector< double > *MC_TrkV_x;
    std::vector< double > *MC_TrkV_y;
    std::vector< double > *MC_TrkV_z;
    std::vector< double > *MC_TrkV_momentumInc_pt;
    std::vector< double > *MC_TrkV_Inc_charge;
    std::vector< int > *MC_TrkV_Inc_pdgId;
    std::vector< double > *MC_TrkV_momentumInc_phi;
    std::vector< double > *MC_TrkV_momentumInc_theta;
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

    TBranch *b_numberOfMC_TrkV;
    TBranch *b_MC_TrkV_isNuclearInteraction;
    TBranch *b_MC_TrkV_isKaonDecay;
    TBranch *b_MC_TrkV_isConversion;
    TBranch *b_MC_TrkV_x;
    TBranch *b_MC_TrkV_y;
    TBranch *b_MC_TrkV_z;
    TBranch *b_MC_TrkV_momentumInc_pt;
    TBranch *b_MC_TrkV_Inc_charge;
    TBranch *b_MC_TrkV_Inc_pdgId;
    TBranch *b_MC_TrkV_momentumInc_phi;
    TBranch *b_MC_TrkV_momentumInc_theta;
    TBranch *b_MC_TrkV_momentumOut_pt;
    TBranch *b_MC_TrkV_momentumOut_phi;
    TBranch *b_MC_TrkV_momentumOut_theta;
    TBranch *b_MC_TrkV_momentumOut_mass;
    TBranch *b_MC_TrkV_numberOfChargedParticles_0p2;
    TBranch *b_MC_TrkV_numberOfChargedParticles_0p5;
    TBranch *b_MC_TrkV_numberOfChargedParticles_1p0;
    TBranch *b_MC_TrkV_numberOfChargedParticles_Out0p2;
    TBranch *b_MC_TrkV_numberOfChargedParticles_Out0p5;
    TBranch *b_MC_TrkV_numberOfChargedParticles_Out1p0;
    TBranch *b_MC_TrkV_isAssociatedPF;
    TBranch *b_MC_TrkV_associationPFDVIdx;
    TBranch *b_MC_TrkV_associationPFDV_deltaR2d;
    TBranch *b_MC_TrkV_associationPFDV_deltaR3d;
    TBranch *b_MC_TrkV_associationPFDV_deltaR3dPerpendicular;
    TBranch *b_MC_TrkV_associationPFDV_deltaR3dParallel;

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

    TBranch *b_numberOfPFDV;
    TBranch *b_PFDV_x;
    TBranch *b_PFDV_y;
    TBranch *b_PFDV_z;
    TBranch *b_PFDV_momentumInc_pt;
    TBranch *b_PFDV_Inc_charge;
    TBranch *b_PFDV_momentumInc_phi;
    TBranch *b_PFDV_momentumInc_theta;
    TBranch *b_PFDV_momentumOut_pt;
    TBranch *b_PFDV_momentumOut_phi;
    TBranch *b_PFDV_momentumOut_theta;
    TBranch *b_PFDV_momentumOut_mass;
    TBranch *b_PFDV_momentumOut_numberOfTracks;
    TBranch *b_PFDV_numberOfTracks_0p0;
    TBranch *b_PFDV_numberOfTracks_0p2;
    TBranch *b_PFDV_numberOfTracks_0p5;
    TBranch *b_PFDV_numberOfTracks_1p0;
    TBranch *b_PFDV_numberOfTracks_Out0p0;
    TBranch *b_PFDV_numberOfTracks_Out0p2;
    TBranch *b_PFDV_numberOfTracks_Out0p5;
    TBranch *b_PFDV_numberOfTracks_Out1p0;
    TBranch *b_PFDV_isNuclear;
    TBranch *b_PFDV_isNuclearLoose;
    TBranch *b_PFDV_isNuclearKink;
    TBranch *b_PFDV_isK0;
    TBranch *b_PFDV_isLambda;
    TBranch *b_PFDV_isLambdaBar;
    TBranch *b_PFDV_isKPlusLoose;
    TBranch *b_PFDV_isKMinusLoose;
    TBranch *b_PFDV_isConversionLoose;
    TBranch *b_PFDV_isLooper;
    TBranch *b_PFDV_isFake;
    TBranch *b_PFDV_isTherePrimaryTrack;
    TBranch *b_PFDV_isThereMergedTrack;
    TBranch *b_PFDV_isAssociatedMC;
    TBranch *b_PFDV_deltaR2d_Associated;
    TBranch *b_PFDV_deltaR3d_Associated;
    TBranch *b_PFDV_associationMC_TrkVIdx;
    TBranch *b_PFDV_vTrack_pt;
    TBranch *b_PFDV_vTrack_eta;
    TBranch *b_PFDV_vTrack_phi;
    TBranch *b_PFDV_vTrack_rho;
    TBranch *b_PFDV_vTrack_numberOfValidHits;
    TBranch *b_PFDV_vTrack_numberOfExpectedOuterHits;
    TBranch *b_PFDV_vTrack_closestDxyPVIdx;
    TBranch *b_PFDV_vTrack_closestDxyPVIdx_dxy;
    TBranch *b_PFDV_vTrack_closestDxyPVIdx_dz;
    TBranch *b_PFDV_vTrack_closestDzPVIdx;
    TBranch *b_PFDV_vTrack_closestDzPVIdx_dxy;
    TBranch *b_PFDV_vTrack_closestDzPVIdx_dz;
};

#endif

