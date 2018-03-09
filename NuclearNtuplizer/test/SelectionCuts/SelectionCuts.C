#define SelectionCuts_cxx
#include "SelectionCuts.h"
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

void SelectionCuts::Loop()
{
   if (fChain == 0) return;

   TFile* outputFile;
   outputFile = new TFile( "SelectedCuts.root", "RECREATE" );
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

    TH1D* hPFDV_CountEventsWithNI;

    TH1D* hMC_TrkV_rho;
    TH1D* hMC_TrkV_z;
    TH1D* hMC_TrkV_rho_Barrel;
    TH1D* hMC_TrkV_z_Barrel;
    TH1D* hMC_TrkV_momentumOut_pt_Barrel;
    TH1D* hMC_TrkV_momentumInc_pt_Barrel;
    TH1D* hMC_TrkV_momentumOut_phi_Barrel;
    TH1D* hMC_TrkV_momentumOut_theta_Barrel;
    TH1D* hMC_TrkV_momentumInc_theta_Barrel;
    TH1D* hMC_TrkV_momentumInc_phi_Barrel;

    TH1D* hMC_TrkV_momentumOut_mass_Barrel;

    TH1D* hMC_TrkV_numberOftracks_0p2;
    TH1D* hMC_TrkV_numberOftracks_0p5;
    TH1D* hMC_TrkV_numberOftracks_1p0;
    TH1D* hMC_TrkV_numberOftracks_Out0p2;
    TH1D* hMC_TrkV_numberOftracks_Out0p5;
    TH1D* hMC_TrkV_numberOftracks_Out1p0;

    //Cut RECO Histograms
    TH1D* hPFDV_rho_Barrel;
    TH1D* hPFDV_z_Barrel;
    TH1D* hPFDV_rho;
    TH1D* hPFDV_z;
    TH1D* hPFDV_momentumInc_pt;
    TH1D* hPFDV_Inc_charge;
    TH1D* hPFDV_momentumInc_phi;
    TH1D* hPFDV_momentumInc_theta;
    TH1D* hPFDV_momentumOut_pt;
    TH1D* hPFDV_momentumOut_mass;
    TH1D* hPFDV_momentumOut_numberOfTracks;
    TH1D* hPFDV_numberOfTracks_Out0p0;
    TH1D* hPFDV_numberOfTracks_Out0p2;
    TH1D* hPFDV_numberOfTracks_Out0p5;
    TH1D* hPFDV_numberOfTracks_Out1p0;
    TH1D* hPFDV_vTrack_algo;
    TH1D* hPFDV_vTrack_numberOfValidHits;
    TH1D* hPFDV_vTrack_numberOfExpectedOuterHits;
    TH1D* hPFDV_vTrack_closestDxyPVIdx;
    TH1D* hPFDV_vTrack_closestDxyPVIdx_dxy;
    TH1D* hPFDV_vTrack_closestDxyPVIdx_dz;
    TH1D* hPFDV_vTrack_closestDzPVIdx;
    TH1D* hPFDV_vTrack_closestDzPVIdx_dxy;
    TH1D* hPFDV_vTrack_closestDzPVIdx_dz;
    TH1D* hPFDV_vTrack_chi2;
    TH1D* hPFDV_vTrack_normalizedChi2;

    TH1D* hPFDV_vTrack_pt;
    TH1D* hPFDV_vTrack_pt_Pixel;
    TH1D* hPFDV_vTrack_eta;
    TH1D* hPFDV_vTrack_phi;
    TH1D* hPFDV_vTrack_rho;
    TH1D* hPFDV_numberOftracks_0p0;
    TH1D* hPFDV_numberOftracks_0p2;
    TH1D* hPFDV_numberOftracks_0p5;
    TH1D* hPFDV_numberOftracks_1p0;
    
    TH2D* hPFDV_XY_Map;

  hMC_TrkV_momentumOut_pt_Barrel = new TH1D( "hMC_TrkV_momentumOut_pt_Barrel", "N.I. in Tracker", 110, 0., 110.0 );
  hMC_TrkV_momentumOut_pt_Barrel->Sumw2();
  hMC_TrkV_momentumInc_pt_Barrel = new TH1D( "hMC_TrkV_momentumInc_pt_Barrel", "N.I. in Tracker", 100, 0., 110.0 );
  hMC_TrkV_momentumInc_pt_Barrel->Sumw2();
  hMC_TrkV_momentumOut_mass_Barrel = new TH1D( "hMC_TrkV_momentumOut_mass_Barrel", "N.I. in Tracker", 100, 0., 30.);
  hMC_TrkV_momentumOut_mass_Barrel->Sumw2();
  hMC_TrkV_momentumOut_phi_Barrel = new TH1D( "hMC_TrkV_momentumOut_phi_Barrel", "N.I. in Tracker", 50, -TMath::Pi(), TMath::Pi());
  hMC_TrkV_momentumOut_phi_Barrel->Sumw2();
  hMC_TrkV_momentumOut_theta_Barrel = new TH1D( "hMC_TrkV_momentumOut_theta_Barrel", "N.I. in Tracker", 100, 0.0, TMath::Pi());
  hMC_TrkV_momentumOut_theta_Barrel->Sumw2();

  hMC_TrkV_numberOftracks_0p2 = new TH1D( "hMC_TrkV_numberOftracks_0p2", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_0p2->Sumw2();

  hMC_TrkV_numberOftracks_0p5 = new TH1D( "hMC_TrkV_numberOftracks_0p5", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_0p5->Sumw2();

  hMC_TrkV_numberOftracks_1p0 = new TH1D( "hMC_TrkV_numberOftracks_1p0", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_numberOftracks_1p0->Sumw2();

  hMC_TrkV_numberOftracks_Out0p2 = new TH1D( "hMC_TrkV_numberOftracks_Out0p2", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_Out0p2->Sumw2();

  hMC_TrkV_numberOftracks_Out0p5 = new TH1D( "hMC_TrkV_numberOftracks_Out0p5", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_Out0p5->Sumw2();

  hMC_TrkV_numberOftracks_Out1p0 = new TH1D( "hMC_TrkV_numberOftracks_Out1p0", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_Out1p0->Sumw2();

  hMC_TrkV_momentumInc_theta_Barrel = new TH1D( "hMC_TrkV_momentumInc_theta_Barrel", "N.I. in Tracker", 100, 0.0, TMath::Pi());
  hMC_TrkV_momentumInc_theta_Barrel->Sumw2();
  hMC_TrkV_momentumInc_phi_Barrel = new TH1D( "hMC_TrkV_momentumInc_phi_Barrel", "N.I. in Tracker", 50, -TMath::Pi(), TMath::Pi());
  hMC_TrkV_momentumInc_phi_Barrel->Sumw2();

  /// Output histograms and graphs etc
  hPFDV_CountEventsWithNI = new TH1D( "hPFDV_CountEventsWithNI", "N.I. in Tracker", 3, 0, 2 );
  hPFDV_CountEventsWithNI->Sumw2();

  hPFDV_numberOftracks_0p0 = new TH1D( "hPFDV_numberOftracks_0p0", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p0->Sumw2();

  hPFDV_numberOftracks_0p2 = new TH1D( "hPFDV_numberOftracks_0p2", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p2->Sumw2();

  hPFDV_numberOftracks_0p5 = new TH1D( "hPFDV_numberOftracks_0p5", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p5->Sumw2();

  hPFDV_numberOftracks_1p0 = new TH1D( "hPFDV_numberOftracks_1p0", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_1p0->Sumw2();

  hPFDV_vTrack_pt = new TH1D( "hPFDV_vTrack_pt", "CMS work in progress", 100, 0, 110. );
  hPFDV_vTrack_pt->Sumw2();

  hPFDV_vTrack_pt_Pixel = new TH1D( "hPFDV_vTrack_pt_Pixel", "CMS work in progress", 100, 0, 5.0 );
  hPFDV_vTrack_pt_Pixel->Sumw2();

  hPFDV_vTrack_eta = new TH1D( "hPFDV_vTrack_eta", "CMS work in progress", 100, -2.5, 2.5);
  hPFDV_vTrack_eta->Sumw2();

  hPFDV_vTrack_phi = new TH1D( "hPFDV_vTrack_phi", "CMS work in progress", 50, -TMath::Pi(), TMath::Pi());
  hPFDV_vTrack_phi->Sumw2();

  hPFDV_vTrack_rho = new TH1D( "hPFDV_vTrack_rho", "CMS work in progress", 100, 0.0, 60.0);
  hPFDV_vTrack_rho->Sumw2();

  //RECO Cuts
  hPFDV_momentumInc_pt = new TH1D( "hPFDV_momentumInc_pt", "CMS work in progress", 100, 0., 110.);
  hPFDV_momentumInc_pt->Sumw2();

  hPFDV_Inc_charge = new TH1D( "hPFDV_Inc_charge", "CMS work in progress", 50, -5.0, 5.0);
  hPFDV_Inc_charge->Sumw2();

  hPFDV_momentumInc_phi = new TH1D( "hPFDV_momentumInc_phi", "CMS work in progress", 50, -TMath::Pi(), TMath::Pi());
  hPFDV_momentumInc_phi->Sumw2();

  hPFDV_momentumInc_theta = new TH1D( "hPFDV_momentumInc_theta", "CMS work in progress", 100, 0.0, TMath::Pi());
  hPFDV_momentumInc_theta->Sumw2();

  hPFDV_momentumOut_pt = new TH1D( "hPFDV_momentumOut_pt", "CMS work in progress", 100, 0.0, 60.);
  hPFDV_momentumOut_pt->Sumw2();

  hPFDV_momentumOut_mass = new TH1D( "hPFDV_momentumOut_mass", "CMS work in progress", 100, 0.0, 30.);
  hPFDV_momentumOut_mass->Sumw2();

  hPFDV_momentumOut_numberOfTracks = new TH1D( "hPFDV_momentumOut_numberOfTracks", "CMS work in progress", 100, 0.0, 20.0);
  hPFDV_momentumOut_numberOfTracks->Sumw2();

  hPFDV_numberOfTracks_Out0p0 = new TH1D( "hPFDV_numberOfTracks_Out0p0", "CMS work in progress", 100, 0.0, 20.0);
  hPFDV_numberOfTracks_Out0p0->Sumw2();

  hPFDV_numberOfTracks_Out0p2 = new TH1D( "hPFDV_numberOfTracks_Out0p2", "CMS work in progress", 100, 0.0, 20.0);
  hPFDV_numberOfTracks_Out0p2->Sumw2();

  hPFDV_numberOfTracks_Out0p5 = new TH1D( "hPFDV_numberOfTracks_Out0p5", "CMS work in progress", 100, 0.0, 20.0);
  hPFDV_numberOfTracks_Out0p5->Sumw2();

  hPFDV_numberOfTracks_Out1p0 = new TH1D( "hPFDV_numberOfTracks_Out1p0", "CMS work in progress", 100, 0.0, 20.0);
  hPFDV_numberOfTracks_Out1p0->Sumw2();

  hPFDV_vTrack_algo = new TH1D( "hPFDV_vTrack_algo", "CMS work in progress", 100, 0.0, 15.0);
  hPFDV_vTrack_algo->Sumw2();

  hPFDV_vTrack_numberOfValidHits = new TH1D( "hPFDV_vTrack_numberOfValidHits", "CMS work in progress", 100, 0.0, 20.0);
  hPFDV_vTrack_numberOfValidHits->Sumw2();

  hPFDV_vTrack_numberOfExpectedOuterHits = new TH1D( "hPFDV_vTrack_numberOfExpectedOuterHits", "CMS work in progress", 100, 0.0, 5.0);
  hPFDV_vTrack_numberOfExpectedOuterHits->Sumw2();

  hPFDV_vTrack_closestDxyPVIdx = new TH1D( "hPFDV_vTrack_closestDxyPVIdx", "CMS work in progress", 100, 0.0, 10.0);
  hPFDV_vTrack_closestDxyPVIdx->Sumw2();

  hPFDV_vTrack_closestDxyPVIdx_dxy = new TH1D( "hPFDV_vTrack_closestDxyPVIdx_dxy", "CMS work in progress", 100, 0.0, 5.0);
  hPFDV_vTrack_closestDxyPVIdx_dxy->Sumw2();

  hPFDV_vTrack_closestDxyPVIdx_dz = new TH1D( "hPFDV_vTrack_closestDxyPVIdx_dz", "CMS work in progress", 100, 0.0, 10.0);
  hPFDV_vTrack_closestDxyPVIdx_dz->Sumw2();

  hPFDV_vTrack_closestDzPVIdx = new TH1D( "hPFDV_vTrack_closestDzPVIdx", "CMS work in progress", 100, 0.0, 10.0);
  hPFDV_vTrack_closestDzPVIdx->Sumw2();

  hPFDV_vTrack_closestDzPVIdx_dxy = new TH1D( "hPFDV_vTrack_closestDzPVIdx_dxy", "CMS work in progress", 100, 0.0, 5.0);
  hPFDV_vTrack_closestDzPVIdx_dxy->Sumw2();

  hPFDV_vTrack_closestDzPVIdx_dz = new TH1D( "hPFDV_vTrack_closestDzPVIdx_dz", "CMS work in progress", 100, 0.0, 10.0);
  hPFDV_vTrack_closestDzPVIdx_dz->Sumw2();

  hPFDV_vTrack_chi2 = new TH1D( "hPFDV_vTrack_chi2", "CMS work in progress", 100, 0.0, 80.0);
  hPFDV_vTrack_chi2->Sumw2();

  hPFDV_vTrack_normalizedChi2 = new TH1D( "hPFDV_vTrack_normalizedChi2", "CMS work in progress", 100, 0.0, 4.0);
  hPFDV_vTrack_normalizedChi2->Sumw2();

  hPFDV_XY_Map = new TH2D( "hPFDV_XY_Map", "CMS work in progress", 1000, -70, 70, 1000, -70, 70 );
  hPFDV_XY_Map->Sumw2();

  hMC_TrkV_rho = new TH1D( "hMC_TrkV_rho", "CMS work in progress", 120, 0.0, 60.0);
  hMC_TrkV_rho->Sumw2(); 

  hMC_TrkV_z = new TH1D( "hMC_TrkV_z", "CMS work in progress", 200, -100.0, 100.0);
  hMC_TrkV_z->Sumw2();

  hPFDV_rho = new TH1D( "hPFDV_rho", "CMS work in progress", 120, 0.0, 60.0);
  hPFDV_rho->Sumw2();

  hPFDV_z = new TH1D( "hPFDV_z", "CMS work in progress", 200, -100.0, 100.0);
  hPFDV_z->Sumw2();
  
  hMC_TrkV_rho_Barrel = new TH1D( "hMC_TrkV_rho_Barrel", "CMS work in progress", 120, 0.0, 6.0);
  hMC_TrkV_rho_Barrel->Sumw2(); 

  hMC_TrkV_z_Barrel = new TH1D( "hMC_TrkV_z_Barrel", "CMS work in progress", 200, -30.0, 30.0);
  hMC_TrkV_z_Barrel->Sumw2();

  hPFDV_rho_Barrel = new TH1D( "hPFDV_rho_Barrel", "CMS work in progress", 120, 0.0, 6.0);
  hPFDV_rho_Barrel->Sumw2();

  hPFDV_z_Barrel = new TH1D( "hPFDV_z_Barrel", "CMS work in progress", 200, -30.0, 30.0);
  hPFDV_z_Barrel->Sumw2();

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if( jentry%100000 == 0 )
      {
       std::cout << "Loop over entry " << jentry << "/" << nentries << "." << std::endl;
      }

    /// Here all the branches are available
    double ni_x, ni_y, ni_z, ni_rho, ni_phi;
    int ni_z_i;

    double ni_MC_x, ni_MC_y, ni_MC_z, ni_MC_rho;

    for ( unsigned int i = 0; i < numberOfMC_TrkV; i++ )
    {
      ni_MC_x = MC_TrkV_x->at(i);
      ni_MC_y = MC_TrkV_y->at(i);
      ni_MC_z = MC_TrkV_z->at(i);
      ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );

      //initial cuts
      //remove very soft vertex:
      if (ni_MC_rho < 1.7) continue; // we don't reconstruct vertex with r < 1.8
      if (MC_TrkV_numberOfChargedParticles_0p2->at(i) < 3 ) continue;
      if (MC_TrkV_momentumOut_pt->at(i) < 0.5 ) continue;

      hMC_TrkV_rho->Fill(ni_MC_rho);
      hMC_TrkV_z->Fill(ni_MC_z);
        
        if ( ( ni_MC_rho < 5 ) && ( abs(ni_MC_z) < 25 ) ){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
            hMC_TrkV_rho_Barrel->Fill(ni_MC_rho);
            hMC_TrkV_z_Barrel->Fill(ni_MC_z);
            hMC_TrkV_momentumOut_pt_Barrel-> Fill (MC_TrkV_momentumOut_pt->at(i));
            hMC_TrkV_momentumInc_pt_Barrel-> Fill (MC_TrkV_momentumInc_pt->at(i));
            hMC_TrkV_momentumOut_phi_Barrel -> Fill (MC_TrkV_momentumOut_phi->at(i));
	    hMC_TrkV_momentumOut_theta_Barrel -> Fill (MC_TrkV_momentumOut_theta->at(i));
	    hMC_TrkV_momentumInc_theta_Barrel -> Fill (MC_TrkV_momentumInc_theta->at(i));
	    hMC_TrkV_momentumInc_phi_Barrel -> Fill (MC_TrkV_momentumInc_phi->at(i));
            hMC_TrkV_numberOftracks_0p2->Fill(MC_TrkV_numberOfChargedParticles_0p2->at(i));
            hMC_TrkV_numberOftracks_0p5->Fill(MC_TrkV_numberOfChargedParticles_0p5->at(i));
            hMC_TrkV_numberOftracks_1p0->Fill(MC_TrkV_numberOfChargedParticles_1p0->at(i));
            hMC_TrkV_numberOftracks_Out0p2->Fill(MC_TrkV_numberOfChargedParticles_Out0p2->at(i));
            hMC_TrkV_numberOftracks_Out0p5->Fill(MC_TrkV_numberOfChargedParticles_Out0p5->at(i));
            hMC_TrkV_numberOftracks_Out1p0->Fill(MC_TrkV_numberOfChargedParticles_Out1p0->at(i));
            hMC_TrkV_momentumOut_mass_Barrel-> Fill (MC_TrkV_momentumOut_mass->at(i));
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
      hPFDV_rho->Fill(ni_rho);
      hPFDV_z->Fill(ni_z);
      ni_z_i = floor( ni_z/5.0 );
	for(unsigned int j=0; j<PFDV_numberOfTracks_0p0->at(i); j++)
	{
	if ( ( ni_rho < 5 ) && (abs(ni_z) < 25) )
	{
         hPFDV_vTrack_algo->Fill(PFDV_vTrack_algo->at(i).at(j));
         hPFDV_vTrack_pt->Fill(PFDV_vTrack_pt->at(i).at(j));
	 if(PFDV_vTrack_pt->at(i).at(j) < 5.0)
	 {
          hPFDV_vTrack_pt_Pixel->Fill(PFDV_vTrack_pt->at(i).at(j));
	 }
	 hPFDV_vTrack_eta->Fill(PFDV_vTrack_eta->at(i).at(j));
         hPFDV_vTrack_phi->Fill(PFDV_vTrack_phi->at(i).at(j));
         hPFDV_vTrack_rho->Fill(PFDV_vTrack_rho->at(i).at(j));
         hPFDV_vTrack_numberOfValidHits->Fill(PFDV_vTrack_numberOfValidHits->at(i).at(j));
         hPFDV_vTrack_numberOfExpectedOuterHits->Fill(PFDV_vTrack_numberOfExpectedOuterHits->at(i).at(j));
         hPFDV_vTrack_closestDxyPVIdx->Fill(PFDV_vTrack_closestDxyPVIdx->at(i).at(j));
         hPFDV_vTrack_closestDxyPVIdx_dxy->Fill(PFDV_vTrack_closestDxyPVIdx_dxy->at(i).at(j));
         hPFDV_vTrack_closestDxyPVIdx_dz->Fill(PFDV_vTrack_closestDxyPVIdx_dz->at(i).at(j));
         hPFDV_vTrack_closestDzPVIdx->Fill(PFDV_vTrack_closestDzPVIdx->at(i).at(j));
         hPFDV_vTrack_closestDzPVIdx_dxy->Fill(PFDV_vTrack_closestDzPVIdx_dxy->at(i).at(j));
         hPFDV_vTrack_closestDzPVIdx_dz->Fill(PFDV_vTrack_closestDzPVIdx_dz->at(i).at(j));
         hPFDV_vTrack_chi2->Fill(PFDV_vTrack_chi2->at(i).at(j));
	 hPFDV_vTrack_normalizedChi2->Fill(PFDV_vTrack_normalizedChi2->at(i).at(j));
	}
	}
     if ( ( ni_rho < 5 ) && (abs(ni_z) < 25) )
     {
      hPFDV_rho_Barrel->Fill(ni_rho);
      hPFDV_z_Barrel->Fill(ni_z);
      hPFDV_numberOftracks_0p0->Fill(PFDV_numberOfTracks_0p0->at(i));
      hPFDV_numberOftracks_0p2->Fill(PFDV_numberOfTracks_0p2->at(i));
      hPFDV_numberOftracks_0p5->Fill(PFDV_numberOfTracks_0p5->at(i));
      hPFDV_numberOftracks_1p0->Fill(PFDV_numberOfTracks_1p0->at(i));
      hPFDV_numberOfTracks_Out0p0->Fill(PFDV_numberOfTracks_0p0->at(i));
      hPFDV_numberOfTracks_Out0p2->Fill(PFDV_numberOfTracks_0p2->at(i));
      hPFDV_numberOfTracks_Out0p5->Fill(PFDV_numberOfTracks_0p5->at(i));
      hPFDV_numberOfTracks_Out1p0->Fill(PFDV_numberOfTracks_1p0->at(i));
     }
	  if ( ( ni_rho < 5 ) && (abs(ni_z) < 25) ){
          if ( PFDV_isNuclear->at(i)){
            hPFDV_momentumOut_pt-> Fill (PFDV_momentumOut_pt->at(i));
	    if( abs(PFDV_Inc_charge->at(i)) < 2.0 )
	    {
	     hPFDV_Inc_charge -> Fill(PFDV_Inc_charge->at(i));
	    }
	    if(abs(PFDV_Inc_charge->at(i)) > 0.99 && abs(PFDV_Inc_charge->at(i)) < 1.01)
	    { 
             hPFDV_momentumInc_pt-> Fill (PFDV_momentumInc_pt->at(i));
             hPFDV_momentumInc_phi -> Fill (PFDV_momentumInc_phi->at(i));
	     hPFDV_momentumInc_theta -> Fill (PFDV_momentumInc_theta->at(i));
	    }
            hPFDV_momentumOut_mass -> Fill (PFDV_momentumOut_mass->at(i));
	    hPFDV_momentumOut_numberOfTracks -> Fill (PFDV_momentumOut_numberOfTracks->at(i));
          }
        }
      hPFDV_XY_Map->Fill( ni_x, ni_y );
    }
 }
   // End of loop over events
      std::cout<<"number of events with NI = "<<hPFDV_CountEventsWithNI->Integral()<<endl;
      std::cout<<"number of NI events = "<<hPFDV_XY_Map->Integral()<<endl;

   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}
