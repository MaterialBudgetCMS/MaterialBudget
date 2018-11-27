#define PlotProduction_cxx
#include "PlotProduction.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TVector3.h>

void PlotProduction::Loop()
{
   if (fChain == 0) return;
   Float_t dR_xmin = 0.;
   Float_t dR_xmax = 1.0;
   Float_t dR_xmax_Loose = 25.;
   Int_t  dR_Nbin = 100;

   TFile* outputFile;
   outputFile = new TFile( "PlotProduced_2018.root", "RECREATE" );
   double Bins[12];
   Bins[0]=     1.8;
   Bins[1]=     2.5;
   Bins[2]=     6.;
   Bins[3]=     9.;
   Bins[4]=     11.5;
   Bins[5]=     22.;
   Bins[6]=     30.;
   Bins[7]=     38.;
   Bins[8]=     45.5;
   Bins[9]=    53.5;
   Bins[10]=    57.;
   Bins[11]=    65.;    

    TH1D* hPFDV_CountEventsWithNI; //
    TH1D* hMC_NumberNI; //
    TH1D* hMC_TrkV_R; //
    TH1D* hMC_TrkV_R_Barrel; //
    TH1D* hMC_TrkV_R_isNuclearInteraction; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2;
    TH1D* hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2;
    TH1D* hMC_TrkV_R_isNuclearInteraction_Barrel; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5; //
    TH1D* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0; //
    TH1D* hMC_TrkV_R_isAssociatedPF; //
    TH1D* hMC_TrkV_R_isAssociatedPF_Barrel; //
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel; //
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2; //
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5; //
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0; // 
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2; //
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5; // 
    TH1D* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0; //
    //TH1D* hMC_TrkV_R_associationPFDVIdx;
    //TH1D* hMC_TrkV_R_associationPFDVIdx_Barrel;
    TH1D* hMC_TrkV_isNuclearInteraction;
    TH1D* hMC_TrkV_isNuclearInteraction_Barrel;
    TH1D* hMC_TrkV_isAssociatedPF;
    TH1D* hMC_TrkV_isAssociatedPF_Barrel;
    TH1D* hMC_TrkV_associationPFDVIdx;
    TH1D* hMC_TrkV_associationPFDVIdx_Barrel;
    TH1D* hMC_TrkV_associationPFDV_deltaR2d;
    TH1D* hMC_TrkV_associationPFDV_deltaR2d_Barrel;
    //Zach's histograms deltaRs
    /*TH1D* hMC_TrkV_associationPFDV_deltaR3d_PixelSupport_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_PixelSupport_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_PixelSupport_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_With_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_With_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_With_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Without_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Without_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3d_Without_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_With_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_With_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_With_EndCap_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Both_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Barrel_Landau;
    TH1D* hMC_TrkV_associationPFDV_deltaR3dParallel_Without_EndCap_Landau;
    TH2D* hMC_XY_Map;
    TH2D* hMC_RhoPhi_PixelSupport;
    TH2D* hMC_XY_Map_Pipe;
    TH2D* hMC_XY_PixelSupport_AbsZ25;
    TH2D* hMC_XY_PixelSupport;*/
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
    TH2D* hPFDV_RhoPhi_Map_Pipe;
    TH2D* hPFDV_XY_PixelSupport;
    TH2D* hPFDV_RhoPhi_PixelSupport;
    TH2D* hPFDV_XY_PixelSupport_AbsZ25;
    TH2D* hPFDV_RhoPhi_PixelSupport_AbsZ25;
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
    TH2D* hPFDV_XY_Pixel_AbsZ25;
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
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_BPix;
    std::map<int, TH2D*> m_hPFDV_XY_Map_Pipe;
    std::map<int, TH2D*> m_hPFDV_RhoPhi_Map_Pipe;

  /*hMC_TrkV_associationPFDV_deltaR3d_PixelSupport_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_PixelSupport_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_PixelSupport_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_PixelSupport_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_PixelSupport_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_PixelSupport_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_PixelSupport_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_PixelSupport_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_PixelSupport_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_With_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax/10.0);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_EndCap_Landau->Sumw2();  
  hMC_TrkV_associationPFDV_deltaR3d_With_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_With_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_With_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_With_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_With_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_With_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_With_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_With_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_With_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_Without_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_Without_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_Without_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_Without_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_Without_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_Without_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3d_Without_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3d_Without_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d_Without_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_With_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_With_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_With_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_With_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_With_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_With_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_With_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_With_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_With_EndCap_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Both_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Both_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Both_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Barrel_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Barrel_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_Without_Barrel_Landau->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_Without_EndCap_Landau = new TH1D("hMC_TrkV_associationPFDV_deltaR3dParallel_Without_EndCap_Landau", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_Without_EndCap_Landau->Sumw2();
*/
  hMC_NumberNI = new TH1D( "hMC_NumberNI", "# NI pass good sel. per event", 31, -0.5, 30.5 );
  hMC_NumberNI->Sumw2();

  hMC_TrkV_isNuclearInteraction = new TH1D( "hMC_TrkV_isNuclearInteraction", "N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isNuclearInteraction->Sumw2();

  hMC_TrkV_isAssociatedPF = new TH1D( "hMC_TrkV_isAssociatedPF","N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isAssociatedPF->Sumw2();

  hMC_TrkV_associationPFDVIdx = new TH1D( "hMC_TrkV_associationPFDVIdx", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_associationPFDVIdx->Sumw2();
 
  hMC_TrkV_associationPFDV_deltaR2d = new TH1D( "hMC_TrkV_associationPFDV_deltaR2d", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR2d->Sumw2();

  hMC_TrkV_associationPFDV_deltaR2d_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR2d_Barrel", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR2d_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3d = new TH1D( "hMC_TrkV_associationPFDV_deltaR3d", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3d->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3d_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3d_Barrel", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR3d_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3d_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaR3d_Forward", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR3d_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicular = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicular", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaChargeSource_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaChargeSource_Barrel", "N.I. in Tracker", 16, -0.5, 15.5 );
  hMC_TrkV_associationPFDV_deltaChargeSource_Barrel->Sumw2();

  hMC_TrkV_momentumOut_pt_Barrel = new TH1D( "hMC_TrkV_momentumOut_pt_Barrel", "N.I. in Tracker", 125, 0., 105. );
  hMC_TrkV_momentumOut_pt_Barrel->Sumw2();
  hMC_TrkV_momentumInc_pt_Barrel = new TH1D( "hMC_TrkV_momentumInc_pt_Barrel", "N.I. in Tracker", 125, 0., 105. );
  hMC_TrkV_momentumInc_pt_Barrel->Sumw2();
  //hMC_TrkV_momentum_dtheta_Barrel = new TH1D( "hMC_TrkV_momentum_dtheta_Barrel", "N.I. in Tracker", 100, 0., 3.142 );
  hMC_TrkV_momentum_dtheta_Barrel = new TH1D( "hMC_TrkV_momentum_dtheta_Barrel", "N.I. in Tracker", 100, 0., 0.5 );
  hMC_TrkV_momentum_dtheta_Barrel->Sumw2();
  hMC_TrkV_momentumOut_mass_Barrel = new TH1D( "hMC_TrkV_momentumOut_mass_Barrel", "N.I. in Tracker", 200, 0., 10.);
  hMC_TrkV_momentumOut_mass_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_pdgIdSource_Barrel = new TH1D( "hMC_TrkV_associationPFDV_pdgIdSource_Barrel", "N.I. in Tracker", 601, -300.5 ,300.5 );
  hMC_TrkV_associationPFDV_pdgIdSource_Barrel->Sumw2();
  hMC_TrkV_associationPFDV_deltaChargeSource_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaChargeSource_Forward", "N.I. in Tracker", 16, -0.5 ,15.5 );
  hMC_TrkV_associationPFDV_deltaChargeSource_Forward->Sumw2();
  hMC_TrkV_associationPFDV_pdgIdSource_Forward = new TH1D( "hMC_TrkV_associationPFDV_pdgIdSource_Forward", "N.I. in Tracker", 601, -300.5 ,300.5 );
  hMC_TrkV_associationPFDV_pdgIdSource_Forward->Sumw2();

  hMC_TrkV_pdgIdSource_Barrel = new TH1D( "hMC_TrkV_pdgIdSource_Barrel", "N.I. in Tracker", 601, -300.5 ,300.5 );
  hMC_TrkV_pdgIdSource_Barrel->Sumw2();
  hMC_TrkV_pdgIdSource_Forward = new TH1D( "hMC_TrkV_pdgIdSource_Forward", "N.I. in Tracker", 601, -300.5 ,300.5 );
  hMC_TrkV_pdgIdSource_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel", "N.I. in Tracker", 200, 0, 0.5);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel->Sumw2();
  hMC_TrkV_associationPFDV_deltaR3dParallel_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel_Forward", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax );
  hMC_TrkV_associationPFDV_deltaR3dParallel_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallelRel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallelRel", "N.I. in Tracker", 200, 0, 0.5);
  hMC_TrkV_associationPFDV_deltaR3dParallelRel->Sumw2();


  //Duplicate
  hMC_TrkV_associationPFDV_DuplicateR3d = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3d", "N.I. in Tracker", 600, 0, 100.0 );
  hMC_TrkV_associationPFDV_DuplicateR3d->Sumw2();


  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular", "N.I. in Tracker", 100, 0, 0.20 );
  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs", "N.I. in Tracker", 100, 0, 10. );
  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR3dParallel = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3dParallel", "N.I. in Tracker", 100, 0, 0.20 );
  hMC_TrkV_associationPFDV_DuplicateR3dParallel->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR", "N.I. in Tracker", 600, 0, 100.0 );
  hMC_TrkV_associationPFDV_DuplicateR->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateVerR = new TH1D( "hMC_TrkV_associationPFDV_DuplicateVerR", "N.I. in Tracker", 600, 0, 100.0 );
  hMC_TrkV_associationPFDV_DuplicateVerR->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateVerXY = new TH1D( "hMC_TrkV_associationPFDV_DuplicateVerXY", "N.I. in Tracker", 600, 0, 100.0 );
  hMC_TrkV_associationPFDV_DuplicateVerXY->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateVerZ = new TH1D( "hMC_TrkV_associationPFDV_DuplicateVerZ", "N.I. in Tracker", 600, 0, 100.0 );
  hMC_TrkV_associationPFDV_DuplicateVerZ->Sumw2();

  hMC_TrkV_isNuclearInteraction_Barrel = new TH1D( "hMC_TrkV_isNuclearInteraction_Barrel", "N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isNuclearInteraction_Barrel->Sumw2();

  hMC_TrkV_isAssociatedPF_Barrel = new TH1D( "hMC_TrkV_isAssociatedPF_Barrel","N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isAssociatedPF_Barrel->Sumw2();

  hMC_TrkV_associationPFDVIdx_Barrel = new TH1D( "hMC_TrkV_associationPFDVIdx_Barrel", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_associationPFDVIdx_Barrel->Sumw2();


  hMC_TrkV_R_isNuclearInteraction = new TH1D( "hMC_TrkV_R_isNuclearInteraction", "N.I. in Tracker",500, 0, 60 );
  hMC_TrkV_R_isNuclearInteraction->Sumw2();

  hMC_TrkV_R_isNuclearInteraction_Barrel = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Barrel", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_isNuclearInteraction_Barrel->Sumw2();

  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel->Sumw2();


  hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_eta", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2->Sumw2();
  hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2 = new TH1D( "hMC_TrkV_R_isAssociatedPF_eta", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2->Sumw2();
  

  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0->Sumw2();

  hMC_TrkV_R_isAssociatedPF = new TH1D( "hMC_TrkV_R_isAssociatedPF", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_isAssociatedPF->Sumw2();

  hMC_TrkV_R_isAssociatedPF_Barrel = new TH1D( "hMC_TrkV_R_isAssociatedPF_Barrel","N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_isAssociatedPF_Barrel->Sumw2();

  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel->Sumw2();


  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0->Sumw2();

  hMC_TrkV_R = new TH1D( "hMC_TrkV_R", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R->Sumw2();

  hMC_TrkV_R_Barrel = new TH1D( "hMC_TrkV_R_Barrel", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_Barrel->Sumw2();


  hMC_TrkV_numberOftracks_0p2 = new TH1D( "hMC_TrkV_numberOftracks_0p2", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_0p2->Sumw2();

  hMC_TrkV_numberOftracks_0p5 = new TH1D( "hMC_TrkV_numberOftracks_0p5", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_0p5->Sumw2();

  hMC_TrkV_numberOftracks_1p0 = new TH1D( "hMC_TrkV_numberOftracks_1p0", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_numberOftracks_1p0->Sumw2();


  // only for one Sim Vertex with max pT out
  hMC_TrkV_associationPFDV_deltaR3dParallel_MaxCut = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel_MaxCut", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dParallel_MaxCut->Sumw2();
  
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_MaxCut = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicularMaxCut", "N.I. in Tracker", dR_Nbin, dR_xmin, dR_xmax);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_MaxCut->Sumw2();

  hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_eta_Rlt4_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isNuclearInteraction_eta_Rlt4_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isNuclearInteraction_eta_Rlt4_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isAssociatedPF_eta_Rlt4_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isAssociatedPF_eta_Rlt4_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isAssociatedPF_eta_Rlt4_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_eta_Rlt15_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isNuclearInteraction_eta_Rlt15_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isNuclearInteraction_eta_Rlt15_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isAssociatedPF_eta_Rlt15_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isAssociatedPF_eta_Rlt15_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isAssociatedPF_eta_Rlt15_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_eta_Rgt15_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isNuclearInteraction_eta_Rgt15_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isNuclearInteraction_eta_Rgt15_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isAssociatedPF_eta_Rgt15_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isAssociatedPF_eta_Rgt15_3Tr0p2_MaxCut", "N.I. in Tracker", 50, -2.5, 2.5);
  hMC_TrkV_R_isAssociatedPF_eta_Rgt15_3Tr0p2_MaxCut->Sumw2();
  
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2_MaxCut", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2_MaxCut", "N.I. in Tracker", 11, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2_MaxCut","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2_MaxCut->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2_MaxCut = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2_MaxCut","N.I. in Tracker", 11, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2_MaxCut->Sumw2();

  hMC_TrkV_momentumOut_pt_Barrel_MaxCut = new TH1D( "hMC_TrkV_momentumOut_pt_Barrel_MaxCut", "N.I. in Tracker", 125, 0., 105. );
  hMC_TrkV_momentumOut_pt_Barrel_MaxCut->Sumw2();
  hMC_TrkV_momentumOut_pt_Forward_MaxCut = new TH1D( "hMC_TrkV_momentumOut_pt_Forward_MaxCut", "N.I. in Tracker", 125, 0., 105. );
  hMC_TrkV_momentumOut_pt_Forward_MaxCut->Sumw2();

  /// Output histograms and graphs etc
  hPFDV_CountEventsWithNI = new TH1D( "hPFDV_CountEventsWithNI", "N.I. in Tracker", 3, 0, 2 );
  hPFDV_CountEventsWithNI->Sumw2();

  hPFDV_isAssociatedMC = new TH1D( "hPFDV_isAssociatedMC", "CMS work in progress", 10, -5, 5 );
  hPFDV_isAssociatedMC->Sumw2();

  hPFDV_deltaR3d_Associated = new TH1D( "hPFDV_deltaR3d_Associated", "CMS work in progress", dR_Nbin, dR_xmin, dR_xmax );
  hPFDV_deltaR3d_Associated->Sumw2();

  hPFDV_deltaR3d_Associated_Barrel = new TH1D( "hPFDV_deltaR3d_Associated_Barrel", "CMS work in progress", dR_Nbin, dR_xmin, dR_xmax );
  hPFDV_deltaR3d_Associated_Barrel->Sumw2();

  hPFDV_deltaR3d_Associated_Forward = new TH1D( "hPFDV_deltaR3d_Associated_Forward", "CMS work in progress", dR_Nbin, dR_xmin, dR_xmax );
  hPFDV_deltaR3d_Associated_Forward->Sumw2();

  hPFDV_deltaR3d_Associated_Rebin = new TH1D( "hPFDV_deltaR3d_Associated_Rebin", "CMS work in progress", dR_Nbin, dR_xmin, dR_xmax );
  hPFDV_deltaR3d_Associated_Rebin->Sumw2();

  hPFDV_deltaR3d_Associated_Barrel_Rebin = new TH1D( "hPFDV_deltaR3d_Associated_Barrel_Rebin", "CMS work in progress", dR_Nbin, dR_xmin, dR_xmax );
  hPFDV_deltaR3d_Associated_Barrel_Rebin->Sumw2();

  hPFDV_deltaR3d_Associated_Forward_Rebin = new TH1D( "hPFDV_deltaR3d_Associated_Forward_Rebin", "CMS work in progress", dR_Nbin, dR_xmin, dR_xmax );
  hPFDV_deltaR3d_Associated_Forward_Rebin->Sumw2();

  hPFDV_deltaR2d_Associated = new TH1D( "hPFDV_deltaR2d_Associated", "CMS work in progress", 100, -2, 2 );
  hPFDV_deltaR2d_Associated->Sumw2();

  hPFDV_deltaR2d_Associated_Barrel = new TH1D( "hPFDV_deltaR2d_Associated_Barrel", "CMS work in progress", 100, -2, 2 );
  hPFDV_deltaR2d_Associated_Barrel->Sumw2();


  hPFDV_isAssociatedMC_Barrel = new TH1D( "hPFDV_isAssociatedMC_Barrel", "CMS work in progress", 10, -5, 5 );
  hPFDV_isAssociatedMC_Barrel->Sumw2();

  hPFDV_isAssociatedMC_isNuclear_Barrel = new TH1D( "hPFDV_isAssociatedMC_isNuclear_Barrel", "CMS work in progress", 10, -5, 5 );
  hPFDV_isAssociatedMC_isNuclear_Barrel->Sumw2();

  hPFDV_associationMC_TrkVIdx = new TH1D( "hPFDV_associationMC_TrkVIdx", "CMS work in progress", 100, 0, 100 );
  hPFDV_associationMC_TrkVIdx->Sumw2();

  hPFDV_associationMC_TrkVIdx_Barrel = new TH1D( "hPFDV_associationMC_TrkVIdx_Barrel", "CMS work in progress", 100, 0, 100 );
  hPFDV_associationMC_TrkVIdx_Barrel->Sumw2();

  hPFDV_R_isAssociatedMC = new TH1D( "hPFDV_R_isAssociatedMC", "CMS work in progress", 500, 0, 60 );
  hPFDV_R_isAssociatedMC->Sumw2();

  hPFDV_R_isAssociatedMC_Barrel = new TH1D( "hPFDV_R_isAssociatedMC_Barrel", "CMS work in progress", 500, 0, 60 );
  hPFDV_R_isAssociatedMC_Barrel->Sumw2();

  hPFDV_numberOftracks_0p0 = new TH1D( "hPFDV_numberOftracks_0p0", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p0->Sumw2();

  hPFDV_numberOftracks_0p2 = new TH1D( "hPFDV_numberOftracks_0p2", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p2->Sumw2();

  hPFDV_numberOftracks_0p5 = new TH1D( "hPFDV_numberOftracks_0p5", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p5->Sumw2();

  hPFDV_numberOftracks_1p0 = new TH1D( "hPFDV_numberOftracks_1p0", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_1p0->Sumw2();

  hPFDV_vTrack_pt = new TH1D( "hPFDV_vTrack_pt", "CMS work in progress", 500, 0, 60 );
  hPFDV_vTrack_pt->Sumw2();

  hPFDV_R = new TH1D( "hPFDV_R", "CMS work in progress", 500, 0, 60 );
  hPFDV_R->Sumw2();

  hPFDV_R_BPix = new TH1D( "hPFDV_R_BPix", "CMS work in progress", 500, 0, 60 );
  hPFDV_R_BPix->Sumw2();

  hPFDV_R_Pipe = new TH1D( "hPFDV_R_Pipe", "CMS work in progress", 50, 2, 2.5 );
  hPFDV_R_Pipe->Sumw2();

  hPFDV_ZR_Map = new TH2D( "hPFDV_ZR_Map", "CMS work in progress", 800, -200, 200, 140, 0, 70 );
  hPFDV_ZR_Map->Sumw2();

  hPFDV_XY_Map = new TH2D( "hPFDV_XY_Map", "CMS work in progress", 1000, -70, 70, 1000, -70, 70 );
  hPFDV_RhoPhi_Map = new TH2D( "hPFDV_RhoPhi_Map", "CMS work in progress", 200, -TMath::Pi(), TMath::Pi(), 280, 0, 70 );
  hPFDV_XY_Map->Sumw2();
  hPFDV_RhoPhi_Map->Sumw2();

  hPFDV_XY_PixelSupport = new TH2D( "hPFDV_XY_PixelSupport", "CMS work in progress", 1200, -25, 25, 1200, -25, 25 );
  hPFDV_RhoPhi_PixelSupport = new TH2D( "hPFDV_RhoPhi_PixelSupport", "CMS work in progress", 400, -TMath::Pi(), TMath::Pi(), 1000, 0, 25 );
  hPFDV_XY_PixelSupport->Sumw2();
  hPFDV_RhoPhi_PixelSupport->Sumw2();

  hPFDV_XY_PixelSupport_AbsZ25 = new TH2D( "hPFDV_XY_PixelSupport_AbsZ25", "CMS work in progress", 1200, -25, 25, 1200, -25, 25 );
  hPFDV_RhoPhi_PixelSupport_AbsZ25 = new TH2D( "hPFDV_RhoPhi_PixelSupport_AbsZ25", "CMS work in progress", 400, -TMath::Pi(), TMath::Pi(), 1000, 0, 25 );
  hPFDV_XY_PixelSupport_AbsZ25->Sumw2();
  hPFDV_RhoPhi_PixelSupport_AbsZ25->Sumw2();

  hPFDV_XY_Map_Pipe = new TH2D( "hPFDV_XY_Map_Pipe", "CMS work in progress", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe = new TH2D( "hPFDV_RhoPhi_Map_Pipe", "CMS work in progress", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Pipe->Sumw2();
  hPFDV_RhoPhi_Map_Pipe->Sumw2();



//  hPFDV_XY_Map_Corr = new TH2D( "hPFDV_XY_Map_Corr", "N.I. in Tracker, BS Corr", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr = new TH2D( "hPFDV_RhoPhi_Map_Corr", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr->Sumw2();
//  hPFDV_RhoPhi_Map_Corr->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix = new TH2D( "hPFDV_XY_Map_Corr_BPix", "N.I. in Tracker, BS Corr", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe = new TH2D( "hPFDV_XY_Map_Corr_Pipe", "N.I. in Tracker, BS Corr", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe->Sumw2();
//
//  /// BPix length only
//  hPFDV_XY_Map_AbsZ25 = new TH2D( "hPFDV_XY_Map_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_BPix_AbsZ25 = new TH2D( "hPFDV_XY_Map_BPix_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_BPix_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_BPix_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_BPix_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_BPix_AbsZ25->Sumw2();
//
  hPFDV_XY_Map_Pipe_AbsZ25 = new TH2D( "hPFDV_XY_Map_Pipe_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Pipe_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_RhoPhi_Map_Pipe_AbsZ25->Sumw2();

  hPFDV_XY_Pixel_AbsZ25 = new TH2D( "hPFDV_XY_Pixel_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 5000, -25, 25, 5000, -25, 25 );
  hPFDV_XY_Pixel_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Corr_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_BPix_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_Pipe_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25->Sumw2();
//
//  /// Reweighted
//  hPFDV_XY_Map_Weight = new TH2D( "hPFDV_XY_Map_Weight", "N.I. in Tracker", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Weight = new TH2D( "hPFDV_RhoPhi_Map_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Weight->Sumw2();
//
//  hPFDV_XY_Map_BPix_Weight = new TH2D( "hPFDV_XY_Map_BPix_Weight", "N.I. in Tracker", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_BPix_Weight = new TH2D( "hPFDV_RhoPhi_Map_BPix_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_BPix_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_BPix_Weight->Sumw2();
//
//  hPFDV_XY_Map_Pipe_Weight = new TH2D( "hPFDV_XY_Map_Pipe_Weight", "N.I. in Tracker", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Pipe_Weight = new TH2D( "hPFDV_RhoPhi_Map_Pipe_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Pipe_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Pipe_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_Weight = new TH2D( "hPFDV_XY_Map_Corr_Weight", "N.I. in Tracker, BS Corr", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix_Weight = new TH2D( "hPFDV_XY_Map_Corr_BPix_Weight", "N.I. in Tracker, BS Corr", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe_Weight = new TH2D( "hPFDV_XY_Map_Corr_Pipe_Weight", "N.I. in Tracker, BS Corr", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe_Weight->Sumw2();
//
//  hPFDV_XY_Map_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_BPix_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_BPix_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_BPix_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Pipe_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Pipe_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight->Sumw2();
// 
  
  std::ostringstream histoName;
  std::ostringstream histoTitle; 

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Pipe_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Pipe.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Pipe_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
    m_hPFDV_RhoPhi_Map_Pipe.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if( jentry%100000 == 0 )
      std::cout << "Loop over entry " << jentry << "/" << nentries << "." << std::endl; 

    /// Here all the branches are available
    double ni_x, ni_y, ni_z, ni_rho, ni_phi;
    int ni_z_i;

    double ni_MC_x, ni_MC_y, ni_MC_z, ni_MC_rho;
 
    int N_MCassociatePF = 0;
    double deltaR3dPerpendicular_Previouse = -1.;
    double deltaR3dParallel_Previouse = -1.;

    //for matching Duplicates
    std::vector< double > MatchingDuplicates_dR3;                               
    MatchingDuplicates_dR3.clear();
    std::vector< double > MatchingDuplicates_R;                               
    MatchingDuplicates_R.clear();
    std::vector< double > MatchingDuplicates_VerX;                               
    MatchingDuplicates_VerX.clear();
    std::vector< double > MatchingDuplicates_VerY;                               
    MatchingDuplicates_VerY.clear();
    std::vector< double > MatchingDuplicates_VerZ;                               
    MatchingDuplicates_VerZ.clear();
    std::vector< double > MatchingDuplicates_VerZonly;                               
    MatchingDuplicates_VerZonly.clear();
    std::vector< double > MatchingDuplicates_VerX_XY;                               
    MatchingDuplicates_VerX_XY.clear();
    std::vector< double > MatchingDuplicates_VerY_XY;                               
    MatchingDuplicates_VerY_XY.clear();

// start MC part

    // calculate number of good NI vertices per event
    int NumberNI = 0;
    for ( unsigned int i = 0; i < numberOfMC_TrkV; i++ )
    {
      ni_MC_x = MC_TrkV_x->at(i);
      ni_MC_y = MC_TrkV_y->at(i);
      ni_MC_z = MC_TrkV_z->at(i);
      ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );


      // remove very soft vertex:
      if (ni_MC_rho < 1.7) continue; // we don't reconstruct vertex with r < 1.8
      if (MC_TrkV_numberOfChargedParticles_0p2->at(i) < 3 ) continue;
      if (MC_TrkV_momentumOut_pt->at(i) < 0.5 ) continue;
      // reject Sim event with R > 65 cm, because we don't have after reco 
      if (ni_MC_rho > 65) continue;
      //if (ni_MC_rho > 60) cout << "ni_MC_rho = " << ni_MC_rho << endl;
      //if (MC_TrkV_momentumOut_pt->at(i) >10. ) continue;
      //if (MC_TrkV_momentumInc_pt->at(i) < 90. ) continue;
      NumberNI ++;
    }

    if (NumberNI <= 30)hMC_NumberNI -> Fill (NumberNI);
    else hMC_NumberNI -> Fill (30); 

    //if (NumberNI < 1 || numberOfPFDV > 1) continue; // for MC only: avoid event with more then 1 good SIM Ver. or more then 1 RECO Ver. for eff. calculation 
    //if ( (NumberNI != 1) || numberOfPFDV > 1) continue; // avoid event with more then 1 good SIM Ver. or more then 1 RECO Ver. for eff. calculation 
    //if ( (NumberNI != 3) ) continue; // avoid event with more then 1 good SIM Ver. or more then 1 RECO Ver. for eff. calculation 
    //test for assosiation


   // find one Sim Verxt with max pT out:
   int SimVer_MaxCut_Pointer = -100.;
   bool SimVer_MaxCut_Previous = false;

    for ( unsigned int i = 0; i < numberOfMC_TrkV; i++ )
    {
      ni_MC_x = MC_TrkV_x->at(i);
      ni_MC_y = MC_TrkV_y->at(i);
      ni_MC_z = MC_TrkV_z->at(i);
      ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );

      TVector3 VerSim;
      VerSim.SetXYZ(ni_MC_x, ni_MC_y, ni_MC_z);
      double eta_VerSim = VerSim.Eta();

      // fine min charge between RECO and MC source:
      //
      double deltaCharge = 15.;
      if(numberOfPFDV > 0)for ( unsigned int j = 0; j < numberOfPFDV; j++ )
      {
         double dCharge = MC_TrkV_Inc_charge->at(i) - PFDV_Inc_charge->at(j); // MC -1:1, PF: -10:1
         if (fabs(dCharge) < deltaCharge) deltaCharge = fabs(dCharge); 
      }

      //check for assosiation MC_TrkV_isAssociatedPF->at(i) is dR3 < 20 is very big, need to do our serlf dR3 < 1 cm
      //bool isMC_assosiated_PF = MC_TrkV_isAssociatedPF->at(i);
      bool isMC_assosiated_PF = false;
      if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 2. && MC_TrkV_associationPFDV_deltaR3dParallel->at(i)< 20. ) isMC_assosiated_PF = true;  
      //if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 300. && MC_TrkV_associationPFDV_deltaR3dParallel->at(i)< 300. ) isMC_assosiated_PF = true;  
      //if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 2.) isMC_assosiated_PF = true;  
      //if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20. && MC_TrkV_associationPFDV_deltaR3dParallel->at(i)< 20. ) isMC_assosiated_PF = true;  
      if (deltaCharge == 1 || deltaCharge == 2 || deltaCharge == 10 || deltaCharge == 15 ) isMC_assosiated_PF = false; // this MC is not assosiaded with PF by charge

      // remove very soft vertex:
      if (ni_MC_rho < 1.7) continue; // we don't reconstruct vertex with r < 1.8
      if (MC_TrkV_numberOfChargedParticles_0p2->at(i) < 3 ) continue;
      if (MC_TrkV_momentumOut_pt->at(i) < 0.5 ) continue;
      // reject Sim event with R > 65 cm, because we don't have after reco 
      if (ni_MC_rho > 65) continue;

      //if (MC_TrkV_momentumOut_pt->at(i) >10. ) continue;
      //if (MC_TrkV_momentumInc_pt->at(i) < 90. ) continue;

      //cout << "eta_VerSim = " << eta_VerSim << endl;  

     // find min charge between RECO and MC source:
     if ( !SimVer_MaxCut_Previous )  SimVer_MaxCut_Pointer = i;        
     else if (MC_TrkV_momentumOut_pt->at(i) > MC_TrkV_momentumOut_pt->at(SimVer_MaxCut_Pointer)) SimVer_MaxCut_Pointer = i; 
          
     SimVer_MaxCut_Previous = true;


      ///////////     
      // test for assosiation
      double deltaMatchingDuplicates = -100;
      double deltaMatchingDuplicatesR = -100;
      double deltaMatchingDuplicatesVerR = -100;
      double deltaMatchingDuplicatesVerXY = -100;
      double deltaMatchingDuplicatesVerZ = -100;
      //double MatchDuplicatesCut_dR3 = 0.1;
      //double MatchDuplicatesCut_R = 0.05;
      double MatchDuplicatesCut_dR3 = 0.5;
      double MatchDuplicatesCut_R = 0.5;

      //if(isMC_assosiated_PF){
          //std::cout << "MC_TrkV_associationPFDV_deltaR3d = " << MC_TrkV_associationPFDV_deltaR3d->at(i) << std::endl; 
          //std::cout << "Radius of MC NI ni_MC_rho = " << ni_MC_rho << std::endl;
          //std::cout << "MC_TrkV_associationPFDV_deltaR3dPerpendicular = " << MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) << std::endl; 
          //std::cout << "MC_TrkV_associationPFDV_deltaR3dParallel = " << MC_TrkV_associationPFDV_deltaR3dParallel->at(i) << std::endl; 

          // DeltaR3d matching
          //if (MC_TrkV_associationPFDV_deltaR3d->at(i) > 0) {
          //     if (i == 0) MatchingDuplicates_dR3.push_back( MC_TrkV_associationPFDV_deltaR3d->at(i) );
          //if (MC_TrkV_associationPFDV_deltaR3d->at(i) > 0 && MC_TrkV_associationPFDV_deltaR3d->at(i) < 20.) {// if it is 20 then no assosiation
          if (MC_TrkV_associationPFDV_deltaR3d->at(i) > 0 && MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax_Loose) {// if it is 20 then no assosiation
               bool flag_1stFill = false;
               if (MatchingDuplicates_dR3.size() < 1) {
                  MatchingDuplicates_dR3.push_back( MC_TrkV_associationPFDV_deltaR3d->at(i) );
                  flag_1stFill = true; 
               }
               double deltaMatching = 900.;
               if (MatchingDuplicates_dR3.size() > 0 && !flag_1stFill){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_dR3.size(); imatch++ )
                  {
                      //double deltaMatching_imatch = fabs(MC_TrkV_associationPFDV_deltaR3d->at(i) - MatchingDuplicates_dR3.at(imatch))/(MC_TrkV_associationPFDV_deltaR3d->at(i) > 0);  
                      double deltaMatching_imatch = fabs(MC_TrkV_associationPFDV_deltaR3d->at(i) - MatchingDuplicates_dR3.at(imatch));  
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                      //if (deltaMatching>=280.) cout << "Alarm: deltaMatching = " << deltaMatching << " MC_TrkV_associationPFDV_deltaR3d->at(i) = " << MC_TrkV_associationPFDV_deltaR3d->at(i) << " MatchingDuplicates_dR3.at(imatch) = " << MatchingDuplicates_dR3.at(imatch) << endl;
                  } 
                  if (deltaMatching < 100.0)hMC_TrkV_associationPFDV_DuplicateR3d ->Fill(deltaMatching);//check that previouse value exist
                  if (deltaMatching >= 100.0 && deltaMatching < 900.)hMC_TrkV_associationPFDV_DuplicateR3d ->Fill(99.999999);//check that previouse value exist
                  deltaMatchingDuplicates = deltaMatching;
                  if (deltaMatchingDuplicates >= MatchDuplicatesCut_dR3) MatchingDuplicates_dR3.push_back( MC_TrkV_associationPFDV_deltaR3d->at(i) ); //next non Duplicate vertex
               }
          }

          // Radius matching
          if ( ni_MC_rho > 0) {
               bool flag_1stFill = false;
               if (MatchingDuplicates_R.size() < 1){
                  MatchingDuplicates_R.push_back( ni_MC_rho );
                  flag_1stFill = true;
               }
               double deltaMatching = 900.;
               if (MatchingDuplicates_R.size() > 0 && !flag_1stFill){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_R.size(); imatch++ )
                  {
                      //double deltaMatching_imatch = fabs(ni_MC_rho - MatchingDuplicates_R.at(imatch))/ni_MC_rho;
                      double deltaMatching_imatch = fabs(ni_MC_rho - MatchingDuplicates_R.at(imatch));
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                  }
                  if (deltaMatching < 100.0)hMC_TrkV_associationPFDV_DuplicateR ->Fill(deltaMatching);//check that previouse value exist
                  if (deltaMatching >= 100.0 && deltaMatching < 900.)hMC_TrkV_associationPFDV_DuplicateR ->Fill(99.999999);//check that previouse value exist
                  deltaMatchingDuplicatesR = deltaMatching;
                  if (deltaMatchingDuplicatesR >= MatchDuplicatesCut_R) MatchingDuplicates_R.push_back( ni_MC_rho ); //next non Duplicate vertex
               }
          } 

          // calculate min dXY between 2 vertices
          if ( ni_MC_rho > 0) {
               bool flag_1stFill = false;
               if (MatchingDuplicates_VerX_XY.size() < 1){
                  MatchingDuplicates_VerX_XY.push_back( ni_MC_x );
                  MatchingDuplicates_VerY_XY.push_back( ni_MC_y );
                  flag_1stFill = true;
               }
               double deltaMatching = 900.;
               if (MatchingDuplicates_VerX_XY.size() > 0 && !flag_1stFill){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_VerX_XY.size(); imatch++ )
                  {

                      double deltaMatching_imatch = TMath::Sqrt ( (ni_MC_x - MatchingDuplicates_VerX_XY.at(imatch))*(ni_MC_x - MatchingDuplicates_VerX_XY.at(imatch)) + (ni_MC_y - MatchingDuplicates_VerY_XY.at(imatch))*(ni_MC_y - MatchingDuplicates_VerY_XY.at(imatch))  );
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                  }
                  if (deltaMatching < 100.0)hMC_TrkV_associationPFDV_DuplicateVerXY ->Fill(deltaMatching);//check that previouse value exist
                  if (deltaMatching >= 100.0 && deltaMatching < 900.)hMC_TrkV_associationPFDV_DuplicateVerXY ->Fill(99.999999);//check that previouse value exist
                  deltaMatchingDuplicatesVerXY = deltaMatching;
                  if (deltaMatchingDuplicatesVerXY >= MatchDuplicatesCut_R) {
                      MatchingDuplicates_VerX_XY.push_back( ni_MC_x ); //next non Duplicate vertex
                      MatchingDuplicates_VerY_XY.push_back( ni_MC_y ); //next non Duplicate vertex
                  }
               }
          }
          // calculate min dZ between 2 vertices
          if ( ni_MC_rho > 0) {
               bool flag_1stFill = false;
               if (MatchingDuplicates_VerZonly.size() < 1){
                  MatchingDuplicates_VerZonly.push_back( ni_MC_z );
                  flag_1stFill = true;
               }
               double deltaMatching = 900.;
               if (MatchingDuplicates_VerZonly.size() > 0 && !flag_1stFill){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_VerZonly.size(); imatch++ )
                  {

                      double deltaMatching_imatch = fabs (ni_MC_z - MatchingDuplicates_VerZonly.at(imatch));
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                  }
                  if (deltaMatching < 100.0)hMC_TrkV_associationPFDV_DuplicateVerZ ->Fill(deltaMatching);//check that previouse value exist
                  if (deltaMatching >= 100.0 && deltaMatching < 900.)hMC_TrkV_associationPFDV_DuplicateVerZ ->Fill(99.999999);//check that previouse value exist
                  deltaMatchingDuplicatesVerZ = deltaMatching;
                  if (deltaMatchingDuplicatesVerZ >= MatchDuplicatesCut_R) MatchingDuplicates_VerZonly.push_back( ni_MC_z ); //next non Duplicate vertex
               }
          }

          // calculated dR 3d vertex matching: dRver
          if ( ni_MC_rho > 0) {
               bool flag_1stFill = false;
               if (MatchingDuplicates_VerX.size() < 1){
                  MatchingDuplicates_VerX.push_back( ni_MC_x );
                  MatchingDuplicates_VerY.push_back( ni_MC_y );
                  MatchingDuplicates_VerZ.push_back( ni_MC_z );
                  flag_1stFill = true;
               }
               double deltaMatching = 900.;
               if (MatchingDuplicates_VerX.size() > 0 && !flag_1stFill){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_VerX.size(); imatch++ )
                  {
                      // normal 3d dR for sim. ver. and the closest one
                      //double deltaMatching_imatch = TMath::Sqrt ( (ni_MC_x - MatchingDuplicates_VerX.at(imatch))*(ni_MC_x - MatchingDuplicates_VerX.at(imatch)) + (ni_MC_y - MatchingDuplicates_VerY.at(imatch))*(ni_MC_y - MatchingDuplicates_VerY.at(imatch)) + (ni_MC_z - MatchingDuplicates_VerZ.at(imatch))*(ni_MC_z - MatchingDuplicates_VerZ.at(imatch))   );
                      // Z res ~ 4 cm, R(x,y) res ~ 1 cm -> Z correction 4*sqrt(2) ~ 5.7  
                      double deltaMatching_imatch = TMath::Sqrt ( (ni_MC_x - MatchingDuplicates_VerX.at(imatch))*(ni_MC_x - MatchingDuplicates_VerX.at(imatch)) + (ni_MC_y - MatchingDuplicates_VerY.at(imatch))*(ni_MC_y - MatchingDuplicates_VerY.at(imatch)) + (ni_MC_z - MatchingDuplicates_VerZ.at(imatch))*(ni_MC_z - MatchingDuplicates_VerZ.at(imatch))/5.7/5.7   ); // correction on z resolution
                      // z resolution only
                      //double deltaMatching_imatch = TMath::Sqrt (  (ni_MC_z - MatchingDuplicates_VerZ.at(imatch))*(ni_MC_z - MatchingDuplicates_VerZ.at(imatch))   );
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                  }

                  //if (numberOfPFDV == 1 && deltaMatching < 100.0)hMC_TrkV_associationPFDV_DuplicateVerR ->Fill(deltaMatching);//check that previouse value exist
                  //if (numberOfPFDV == 1 && deltaMatching >= 100.0 && deltaMatching < 900.)hMC_TrkV_associationPFDV_DuplicateVerR ->Fill(99.999999);//check that previouse value exist
                  if (deltaMatching < 100.0)hMC_TrkV_associationPFDV_DuplicateVerR ->Fill(deltaMatching);//check that previouse value exist
                  if (deltaMatching >= 100.0 && deltaMatching < 900.)hMC_TrkV_associationPFDV_DuplicateVerR ->Fill(99.999999);//check that previouse value exist


                  deltaMatchingDuplicatesVerR = deltaMatching;
                  if (deltaMatchingDuplicatesVerR >= MatchDuplicatesCut_R){
                       MatchingDuplicates_VerX.push_back( ni_MC_x ); //next non Duplicate vertex
                       MatchingDuplicates_VerY.push_back( ni_MC_y ); //next non Duplicate vertex
                       MatchingDuplicates_VerZ.push_back( ni_MC_z ); //next non Duplicate vertex
                  }
               } // end if (MatchingDuplicates_VerX.size() > 0 ...
          }


          //if (numberOfPFDV == 1 && deltaMatchingDuplicatesVerR >-1) cout << "Sim to Sim dR = " << deltaMatchingDuplicatesVerR << endl;

          // this is wrong because make all combination even we don't have assosiation, so at 0 we have some duplicates and a lot of fake non-assosiated with PF RECO vertex 
          if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) > 0) {
               double deltaMatching = fabs(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) - deltaR3dPerpendicular_Previouse)/(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) > 0);
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatching < 0.2)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular ->Fill(deltaMatching);//check that previouse value exist
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatching >= 0.2)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular ->Fill(0.1999999);//check that previouse value exist

               double deltaMatchingAbs = fabs(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) - deltaR3dPerpendicular_Previouse);
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatchingAbs < 10.)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs ->Fill(deltaMatchingAbs);//check that previouse value exist
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatchingAbs >= 10.)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs ->Fill(9.999999);//check that previouse value exist

               deltaR3dPerpendicular_Previouse = MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i);
          } 
          if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) > 0) {
               double deltaMatching = fabs(MC_TrkV_associationPFDV_deltaR3dParallel->at(i) - deltaR3dParallel_Previouse)/(MC_TrkV_associationPFDV_deltaR3dParallel->at(i) > 0);
               if (deltaR3dParallel_Previouse > 0 && deltaMatching < 0.2)hMC_TrkV_associationPFDV_DuplicateR3dParallel ->Fill(deltaMatching);//check that previouse value exist
               if (deltaR3dParallel_Previouse > 0 && deltaMatching >= 0.2)hMC_TrkV_associationPFDV_DuplicateR3dParallel ->Fill(0.1999999);//check that previouse value exist
               deltaR3dParallel_Previouse = MC_TrkV_associationPFDV_deltaR3dParallel->at(i);
          } 
      //} 

      //reject Duplicates:
      //if ( fabs(deltaMatchingDuplicates) < MatchDuplicatesCut_dR3) continue;
      //if ( fabs(deltaMatchingDuplicates) < MatchDuplicatesCut_dR3 || fabs(deltaMatchingDuplicatesR) < MatchDuplicatesCut_R) continue;

      if(isMC_assosiated_PF) N_MCassociatePF++;
      if(N_MCassociatePF > 1){
          //std::cout << "MC_TrkV_associationPFDV_deltaR3d = " << MC_TrkV_associationPFDV_deltaR3d->at(i) << std::endl; 
          //std::cout << "Radius of MC NI ni_MC_rho = " << ni_MC_rho << std::endl;
      }
      ///////////
      
      hMC_TrkV_R->Fill( ni_MC_rho );
 
      hMC_TrkV_numberOftracks_0p2->Fill(MC_TrkV_numberOfChargedParticles_0p2->at(i));
      hMC_TrkV_numberOftracks_0p5->Fill(MC_TrkV_numberOfChargedParticles_0p5->at(i));
      hMC_TrkV_numberOftracks_1p0->Fill(MC_TrkV_numberOfChargedParticles_1p0->at(i));

      if ( MC_TrkV_isNuclearInteraction->at(i)){
      hMC_TrkV_isNuclearInteraction -> Fill (1.);
      hMC_TrkV_R_isNuclearInteraction->Fill( ni_MC_rho );
        if ( isMC_assosiated_PF ){
        hMC_TrkV_R_isAssociatedPF -> Fill ( ni_MC_rho );
        }
      }
      else{
      hMC_TrkV_isNuclearInteraction -> Fill (0.); 
      }

      
      if ( isMC_assosiated_PF ){
      hMC_TrkV_isAssociatedPF -> Fill (1.);
      }
      else{
	      hMC_TrkV_isAssociatedPF -> Fill (0.);
      }
      
      if (MC_TrkV_associationPFDV_deltaR2d->at(i) < dR_xmax)hMC_TrkV_associationPFDV_deltaR2d -> Fill (MC_TrkV_associationPFDV_deltaR2d->at(i));
      else if (MC_TrkV_associationPFDV_deltaR2d->at(i) < dR_xmax_Loose)hMC_TrkV_associationPFDV_deltaR2d -> Fill (dR_xmax-0.00001);

      if (MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax) hMC_TrkV_associationPFDV_deltaR3d -> Fill (MC_TrkV_associationPFDV_deltaR3d->at(i));
      else if (MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3d -> Fill(dR_xmax-0.00001);

      if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < dR_xmax) hMC_TrkV_associationPFDV_deltaR3dPerpendicular -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i));
      else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3dPerpendicular -> Fill(dR_xmax-0.00001);

      if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < dR_xmax) hMC_TrkV_associationPFDV_deltaR3dParallel -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
      else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3dParallel -> Fill(dR_xmax-0.00001);

      double Rel_deltaR3dPerp = -1.;
      if (ni_MC_rho > 0.) Rel_deltaR3dPerp = MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i)/ni_MC_rho;
      if (Rel_deltaR3dPerp < 0.5 && Rel_deltaR3dPerp > 0.) hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel -> Fill (Rel_deltaR3dPerp);
      if (Rel_deltaR3dPerp >= 0.5 && MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel -> Fill(0.4999);

      double Rel_deltaR3dPar = -1.;
      if (ni_MC_rho > 0.) Rel_deltaR3dPar = MC_TrkV_associationPFDV_deltaR3dParallel->at(i)/ni_MC_rho;
      if (Rel_deltaR3dPar < 0.5 && Rel_deltaR3dPar > 0.) hMC_TrkV_associationPFDV_deltaR3dParallelRel -> Fill (Rel_deltaR3dPar);
      if (Rel_deltaR3dPar >= 0.5 && MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallelRel -> Fill(0.4999);

      hMC_TrkV_associationPFDVIdx -> Fill (MC_TrkV_associationPFDVIdx->at(i));


      if(fabs(ni_MC_z) <20)
      {

        if (isMC_assosiated_PF) {
            hMC_TrkV_associationPFDV_deltaChargeSource_Barrel -> Fill (deltaCharge);
            if(fabs(MC_TrkV_Inc_pdgId->at(i))< 300)hMC_TrkV_associationPFDV_pdgIdSource_Barrel -> Fill (MC_TrkV_Inc_pdgId->at(i));
               else {
                       hMC_TrkV_associationPFDV_pdgIdSource_Barrel -> Fill (300.);
                       std::cout << "assos. source pdgId = " << MC_TrkV_Inc_pdgId->at(i) << std:: endl;
                    } 
        }

        if(fabs(MC_TrkV_Inc_pdgId->at(i))< 300)hMC_TrkV_pdgIdSource_Barrel -> Fill (MC_TrkV_Inc_pdgId->at(i));
           else hMC_TrkV_pdgIdSource_Barrel -> Fill (300.);

        if (MC_TrkV_associationPFDV_deltaR2d->at(i) < dR_xmax) hMC_TrkV_associationPFDV_deltaR2d_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR2d->at(i));
        else if (MC_TrkV_associationPFDV_deltaR2d->at(i) < dR_xmax_Loose)hMC_TrkV_associationPFDV_deltaR2d_Barrel -> Fill (dR_xmax-0.00001);

        if (MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax) hMC_TrkV_associationPFDV_deltaR3d_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3d->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3d_Barrel -> Fill(dR_xmax-0.00001);

        if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < dR_xmax) {
            hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i));
            hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
        }
        else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel -> Fill(dR_xmax-0.00001);

        //if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
        //else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel -> Fill(4.999);


      }

      if(fabs(ni_MC_z) >20)
      {
        if (isMC_assosiated_PF) {
            hMC_TrkV_associationPFDV_deltaChargeSource_Forward -> Fill (deltaCharge);
            if(fabs(MC_TrkV_Inc_pdgId->at(i))< 300)hMC_TrkV_associationPFDV_pdgIdSource_Forward -> Fill (MC_TrkV_Inc_pdgId->at(i));
               else {
                       hMC_TrkV_associationPFDV_pdgIdSource_Forward -> Fill (300.);
                       //std::cout << "assos. source pdgId = " << MC_TrkV_Inc_pdgId->at(i) << std:: endl;
                    } 
        }

        if(fabs(MC_TrkV_Inc_pdgId->at(i))< 300)hMC_TrkV_pdgIdSource_Forward -> Fill (MC_TrkV_Inc_pdgId->at(i));
           else hMC_TrkV_pdgIdSource_Forward -> Fill (300.);

        if (MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax) hMC_TrkV_associationPFDV_deltaR3d_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3d->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3d->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3d_Forward -> Fill(dR_xmax-0.00001);

        if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < dR_xmax){
            hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i));
            hMC_TrkV_associationPFDV_deltaR3dParallel_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
        }
        else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward -> Fill(dR_xmax-0.00001);

        //if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dParallel_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
        //else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallel_Forward -> Fill(4.999);

      }

      hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2 -> Fill (eta_VerSim);
      if (isMC_assosiated_PF) hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2 -> Fill (eta_VerSim);
      
      //Barrel region only 
      if(fabs(ni_MC_z) <20)
      {
        hMC_TrkV_R_Barrel->Fill( ni_MC_rho );
        if ( isMC_assosiated_PF ){
        hMC_TrkV_isAssociatedPF_Barrel -> Fill (1.);
        }
        else{
        hMC_TrkV_isAssociatedPF_Barrel -> Fill (0.);
        }
        
        hMC_TrkV_associationPFDVIdx_Barrel -> Fill (MC_TrkV_associationPFDVIdx->at(i));

        if ( MC_TrkV_isNuclearInteraction->at(i)){
        hMC_TrkV_isNuclearInteraction_Barrel -> Fill (1.);
        hMC_TrkV_R_isNuclearInteraction_Barrel->Fill( ni_MC_rho );
        hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel->Fill( ni_MC_rho );
          if ( isMC_assosiated_PF ){
            hMC_TrkV_R_isAssociatedPF_Barrel -> Fill ( ni_MC_rho );
            hMC_TrkV_R_isAssociatedPF_Rebin_Barrel -> Fill ( ni_MC_rho );
          }
        }
        else{
        hMC_TrkV_isNuclearInteraction_Barrel -> Fill (0.);
        }
        
        if ( (MC_TrkV_numberOfChargedParticles_Out0p2->at(i) > 2 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_0p2->at(i) > 2 && ni_MC_rho >= 20 ) ){
        //if ( (MC_TrkV_numberOfChargedParticles_Out0p2->at(i) > 8 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_0p2->at(i) > 8 && ni_MC_rho >= 20 ) ){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
            hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2->Fill( ni_MC_rho );
            hMC_TrkV_momentumOut_pt_Barrel-> Fill (MC_TrkV_momentumOut_pt->at(i));
            hMC_TrkV_momentumInc_pt_Barrel-> Fill (MC_TrkV_momentumInc_pt->at(i));
            double dtheta = fabs(MC_TrkV_momentumInc_theta->at(i)-MC_TrkV_momentumOut_theta->at(i));
            if (dtheta > 3.14) dtheta = fabs(2*3.14 - dtheta); 
            if (dtheta <= 0.5)hMC_TrkV_momentum_dtheta_Barrel-> Fill (dtheta);
            else hMC_TrkV_momentum_dtheta_Barrel-> Fill (0.4999);
            hMC_TrkV_momentumOut_mass_Barrel-> Fill (MC_TrkV_momentumOut_mass->at(i));
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2 -> Fill ( ni_MC_rho );
            }
          }
        }
        if ( (MC_TrkV_numberOfChargedParticles_Out0p5->at(i) > 2 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_0p5->at(i) > 2 && ni_MC_rho >= 20 )){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5 -> Fill ( ni_MC_rho );
            }
          }
        }
        if ( (MC_TrkV_numberOfChargedParticles_Out1p0->at(i) > 2 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_1p0->at(i) > 2 && ni_MC_rho >= 20 )){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0 -> Fill ( ni_MC_rho );
            }
          }
        }


      }
      // Forward region only 
      if(fabs(ni_MC_z) >= 20){
        if ( (MC_TrkV_numberOfChargedParticles_Out0p2->at(i) > 2 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_0p2->at(i) > 2 && ni_MC_rho >= 20 ) ){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2 -> Fill ( ni_MC_rho );
            }
          }
        }
        if ( (MC_TrkV_numberOfChargedParticles_Out0p5->at(i) > 2 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_0p5->at(i) > 2 && ni_MC_rho >= 20 ) ){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5 -> Fill ( ni_MC_rho );
            }
          }
        }
        if ( (MC_TrkV_numberOfChargedParticles_Out1p0->at(i) > 2 && ni_MC_rho < 20 ) || (MC_TrkV_numberOfChargedParticles_1p0->at(i) > 2 && ni_MC_rho >= 20 ) ){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0 -> Fill ( ni_MC_rho );
            }
          }
        }
      } 


    }

    //if(N_MCassociatePF > 1){ 
       //std::cout << "size of MC_TrkV_associationPFDV_deltaR3dPerpendicular = " << MC_TrkV_associationPFDV_deltaR3dPerpendicular->size() << std::endl; 
       //std::cout << "N_MCassociatePF per event = " << N_MCassociatePF << std::endl;
    //}  
// end MC cycle


  // Calculater Efficiency only with Sim Ver with max pT out with pointer: SimVer_MaxCut_Pointer
  if (SimVer_MaxCut_Pointer > -1){

     // chech for assosiation
     bool isMC_assosiated_PF_MaxCut = false;
     if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(SimVer_MaxCut_Pointer) < 2. 
          && MC_TrkV_associationPFDV_deltaR3dParallel->at(SimVer_MaxCut_Pointer)< 20. ) isMC_assosiated_PF_MaxCut = true;

     //fill dR per
     if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(SimVer_MaxCut_Pointer) < dR_xmax) {
         hMC_TrkV_associationPFDV_deltaR3dPerpendicular_MaxCut -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(SimVer_MaxCut_Pointer));
     }
     else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(SimVer_MaxCut_Pointer) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_MaxCut -> Fill(dR_xmax-0.00001);

     //fill dR par
     if (MC_TrkV_associationPFDV_deltaR3dParallel->at(SimVer_MaxCut_Pointer) < dR_xmax) {
         hMC_TrkV_associationPFDV_deltaR3dParallel_MaxCut -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(SimVer_MaxCut_Pointer));
     }
     else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(SimVer_MaxCut_Pointer) < dR_xmax_Loose) hMC_TrkV_associationPFDV_deltaR3dParallel_MaxCut -> Fill(dR_xmax-0.00001);

     // calculate vertex parameters: R, eta...
     ni_MC_x = MC_TrkV_x->at(SimVer_MaxCut_Pointer);
     ni_MC_y = MC_TrkV_y->at(SimVer_MaxCut_Pointer);
     ni_MC_z = MC_TrkV_z->at(SimVer_MaxCut_Pointer);
     ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );

     TVector3 VerSim;
     VerSim.SetXYZ(ni_MC_x, ni_MC_y, ni_MC_z);
     double eta_VerSim = VerSim.Eta();

    //fill eta
      hMC_TrkV_R_isNuclearInteraction_eta_3Tr0p2_MaxCut -> Fill (eta_VerSim);
      if (isMC_assosiated_PF_MaxCut) hMC_TrkV_R_isAssociatedPF_eta_3Tr0p2_MaxCut -> Fill (eta_VerSim);
      if(ni_MC_rho < 4){ //fill only beam pipe region
         hMC_TrkV_R_isNuclearInteraction_eta_Rlt4_3Tr0p2_MaxCut -> Fill (eta_VerSim);
         if (isMC_assosiated_PF_MaxCut) hMC_TrkV_R_isAssociatedPF_eta_Rlt4_3Tr0p2_MaxCut -> Fill (eta_VerSim);
      }
      if(ni_MC_rho < 15){ //fill only beam pipe region
         hMC_TrkV_R_isNuclearInteraction_eta_Rlt15_3Tr0p2_MaxCut -> Fill (eta_VerSim);
         if (isMC_assosiated_PF_MaxCut) hMC_TrkV_R_isAssociatedPF_eta_Rlt15_3Tr0p2_MaxCut -> Fill (eta_VerSim);
      }
      if(ni_MC_rho >=15){ //fill only beam pipe region
         hMC_TrkV_R_isNuclearInteraction_eta_Rgt15_3Tr0p2_MaxCut -> Fill (eta_VerSim);
         if (isMC_assosiated_PF_MaxCut) hMC_TrkV_R_isAssociatedPF_eta_Rgt15_3Tr0p2_MaxCut -> Fill (eta_VerSim);
      }

      if (fabs(ni_MC_z) < 20 ){
         hMC_TrkV_momentumOut_pt_Barrel_MaxCut-> Fill (MC_TrkV_momentumOut_pt->at(SimVer_MaxCut_Pointer));
 
         if ( (MC_TrkV_numberOfChargedParticles_Out0p2->at(SimVer_MaxCut_Pointer) > 2 && ni_MC_rho < 20 ) 
                  || (MC_TrkV_numberOfChargedParticles_0p2->at(SimVer_MaxCut_Pointer) > 2 && ni_MC_rho >= 20 ) ){
            hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2_MaxCut->Fill( ni_MC_rho );
            if (isMC_assosiated_PF_MaxCut) hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2_MaxCut->Fill( ni_MC_rho );
         }

      } 

      if (fabs(ni_MC_z) >= 20 ){
         hMC_TrkV_momentumOut_pt_Forward_MaxCut-> Fill (MC_TrkV_momentumOut_pt->at(SimVer_MaxCut_Pointer));

         if ( (MC_TrkV_numberOfChargedParticles_Out0p2->at(SimVer_MaxCut_Pointer) > 2 && ni_MC_rho < 20 ) 
                  || (MC_TrkV_numberOfChargedParticles_0p2->at(SimVer_MaxCut_Pointer) > 2 && ni_MC_rho >= 20 ) ){
            hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2_MaxCut->Fill( ni_MC_rho );
            if (isMC_assosiated_PF_MaxCut) hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2_MaxCut->Fill( ni_MC_rho );
         }
      } 

  }
// end MC part

// start RECO part

    if (numberOfPV <= 0) continue; // reject events with 0 reco primary vertices
    if (numberOfPFDV >= 1){
    hPFDV_CountEventsWithNI->Fill(1.);
    }

    for ( unsigned int i = 0; i < numberOfPFDV; i++ )
    {
      
      ni_x = PFDV_x->at(i);
      ni_y = PFDV_y->at(i);
      ni_z = PFDV_z->at(i);
      ni_phi = TMath::ATan2( ni_y, ni_x );
      ni_rho = TMath::Sqrt( ni_x*ni_x + ni_y*ni_y );

      ni_z_i = floor( ni_z/5.0 );

    //  if(MC_TrkV_numberOfChargedParticles_0p2->at(i) > 1){
    //  hPFDV_vTrack_pt->Fill(PFDV_vTrack_pt->at(i));
    //  }

      hPFDV_numberOftracks_0p0->Fill(PFDV_numberOfTracks_0p0->at(i));
      hPFDV_numberOftracks_0p2->Fill(PFDV_numberOfTracks_0p2->at(i));
      hPFDV_numberOftracks_0p5->Fill(PFDV_numberOfTracks_0p5->at(i));
      hPFDV_numberOftracks_1p0->Fill(PFDV_numberOfTracks_1p0->at(i));

      hPFDV_R->Fill( ni_rho );

      hPFDV_R_Pipe->Fill( ni_rho );
      
      if ( fabs(ni_z) < 20 ) {
      hPFDV_R_BPix->Fill( ni_rho );
      }

      hPFDV_XY_Map->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map->Fill( ni_phi, ni_rho );


      hPFDV_XY_PixelSupport->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_PixelSupport->Fill( ni_phi, ni_rho );
      if ( fabs(ni_z) < 25 ) {
         hPFDV_XY_PixelSupport_AbsZ25->Fill( ni_x, ni_y );
         hPFDV_RhoPhi_PixelSupport_AbsZ25->Fill( ni_phi, ni_rho );
      }

      hPFDV_XY_Map_Pipe->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map_Pipe->Fill( ni_phi, ni_rho );

      hPFDV_ZR_Map->Fill( ni_z, ni_rho );

      hPFDV_deltaR2d_Associated->Fill(PFDV_deltaR2d_Associated->at(i));
      hPFDV_deltaR3d_Associated->Fill(PFDV_deltaR3d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Rebin->Fill(PFDV_deltaR3d_Associated->at(i));


      if ( fabs(ni_z) <20)
      {
      hPFDV_deltaR2d_Associated_Barrel->Fill(PFDV_deltaR2d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Barrel->Fill(PFDV_deltaR3d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Barrel_Rebin->Fill(PFDV_deltaR3d_Associated->at(i));
      }

      if ( fabs(ni_z) >20)
      {
      hPFDV_deltaR3d_Associated_Forward->Fill(PFDV_deltaR3d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Forward_Rebin->Fill(PFDV_deltaR3d_Associated->at(i));
      }


      if ( PFDV_isAssociatedMC->at(i)){
      hPFDV_isAssociatedMC -> Fill (1.); 
      hPFDV_R_isAssociatedMC->Fill( ni_rho );
      }
      else{ 
      hPFDV_isAssociatedMC -> Fill (0.); 
      }

      if ( fabs(ni_z) <20)
      {
        hPFDV_associationMC_TrkVIdx_Barrel->Fill(PFDV_associationMC_TrkVIdx->at(i));
        if ( PFDV_isAssociatedMC->at(i)){
          if( PFDV_isNuclear->at(i)){
          hPFDV_isAssociatedMC_isNuclear_Barrel -> Fill (1.); 
          }
          else{
          hPFDV_isAssociatedMC_isNuclear_Barrel -> Fill (0.); 
          }
        hPFDV_isAssociatedMC_Barrel -> Fill (1.); 
        hPFDV_R_isAssociatedMC_Barrel->Fill( ni_rho );
        }
        else{
        hPFDV_isAssociatedMC_Barrel -> Fill (0.); 
        }
      }




      if ( fabs(ni_z) < 25 )
      {
       // hPFDV_XY_Map_AbsZ25->Fill( ni_x, ni_y );
       // hPFDV_RhoPhi_Map_AbsZ25->Fill( ni_phi, ni_rho );

       // hPFDV_XY_Map_BPix_AbsZ25->Fill( ni_x, ni_y );
       // hPFDV_RhoPhi_Map_BPix_AbsZ25->Fill( ni_phi, ni_rho );

        hPFDV_XY_Map_Pipe_AbsZ25->Fill( ni_x, ni_y );
        hPFDV_XY_Pixel_AbsZ25->Fill( ni_x, ni_y );
        hPFDV_RhoPhi_Map_Pipe_AbsZ25->Fill( ni_phi, ni_rho );

       // m_hPFDV_XY_Map.find( ni_z_i )->second->Fill( ni_x, ni_y );
       // m_hPFDV_RhoPhi_Map.find( ni_z_i )->second->Fill( ni_phi, ni_rho );

       // m_hPFDV_XY_Map_BPix.find( ni_z_i )->second->Fill( ni_x, ni_y );
       // m_hPFDV_RhoPhi_Map_BPix.find( ni_z_i )->second->Fill( ni_phi, ni_rho );

        m_hPFDV_XY_Map_Pipe.find( ni_z_i )->second->Fill( ni_x, ni_y );
        m_hPFDV_RhoPhi_Map_Pipe.find( ni_z_i )->second->Fill( ni_phi, ni_rho );
      }
//
//      /// Correct for Beamspot Position
//      ni_x_c = ni_x - BS_x;
//      ni_y_c = ni_y - BS_y;
//      ni_phi_c = TMath::ATan2( ni_y_c, ni_x_c );
//      ni_rho_c = TMath::Sqrt( ni_x_c*ni_x_c + ni_y_c*ni_y_c );
//
//      hPFDV_XY_Map_Corr->Fill( ni_x_c, ni_y_c );
//      hPFDV_RhoPhi_Map_Corr->Fill( ni_phi_c, ni_rho_c );
//
//      hPFDV_XY_Map_Corr_BPix->Fill( ni_x_c, ni_y_c );
//      hPFDV_RhoPhi_Map_Corr_BPix->Fill( ni_phi_c, ni_rho_c );
//
//      hPFDV_XY_Map_Corr_Pipe->Fill( ni_x_c, ni_y_c );
//      hPFDV_RhoPhi_Map_Corr_Pipe->Fill( ni_phi_c, ni_rho_c );
//
//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_Corr_AbsZ25->Fill( ni_x_c, ni_y_c );
//        hPFDV_RhoPhi_Map_Corr_AbsZ25->Fill( ni_phi_c, ni_rho_c );
//
//        hPFDV_XY_Map_Corr_BPix_AbsZ25->Fill( ni_x_c, ni_y_c );
//        hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25->Fill( ni_phi_c, ni_rho_c );
//
//        hPFDV_XY_Map_Corr_Pipe_AbsZ25->Fill( ni_x_c, ni_y_c );
//        hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25->Fill( ni_phi_c, ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
//        m_hPFDV_RhoPhi_Map_Corr.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_BPix.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
//        m_hPFDV_RhoPhi_Map_Corr_BPix.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_Pipe.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
//        m_hPFDV_RhoPhi_Map_Corr_Pipe.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
//      }
//
//      /// Reweighted
//
//      hPFDV_XY_Map_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_BPix_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_BPix_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_Pipe_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Pipe_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_BPix_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_Pipe_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_BPix_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_BPix_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Pipe_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Pipe_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//      }
//
//      hPFDV_XY_Map_Corr_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Corr_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_Corr_BPix_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Corr_BPix_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_Corr_Pipe_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Corr_Pipe_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_Corr_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Corr_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_BPix_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Corr_BPix_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_Pipe_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Corr_Pipe_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//      }  
      }
   }
   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}
