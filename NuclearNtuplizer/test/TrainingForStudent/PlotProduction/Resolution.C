#define Resolution_cxx
#include "Resolution.h"
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

void Resolution::Loop()
{
   if (fChain == 0) return;
   Float_t dR_xmin = 0.;
   Float_t dR_xmax = 1.0;
   Float_t dR_xmax_Loose = 20.;
   Int_t  dR_Nbin = 50;
   
   TFile* outputFile;
   //outputFile = new TFile("ResolutionPlots_10GeV_2018.root", "RECREATE");
   outputFile = new TFile("ResolutionPlots_2015.root", "RECREATE");
   //initialize histograms
   TH1D* hMC_deltaR3d;
   TH1D* hMC_deltaR3d_Parallel;
   TH1D* hMC_deltaR3d_Perpendicular;
   TH1D* hMC_deltaR3d_EndCap;
   TH1D* hMC_deltaR3d_Parallel_EndCap;
   TH1D* hMC_deltaR3d_Perpendicular_EndCap;
   TH1D* hMC_deltaR3d_Barrel;
   TH1D* hMC_deltaR3d_Parallel_Barrel;
   TH1D* hMC_deltaR3d_Perpendicular_Barrel;
   TH1D* hMC_deltaR3d_Outer;
   TH1D* hMC_deltaR3d_Parallel_Outer;
   TH1D* hMC_deltaR3d_Perpendicular_Outer;
   TH1D* hMC_deltaR3d_Outer_EndCap;
   TH1D* hMC_deltaR3d_Parallel_Outer_EndCap;
   TH1D* hMC_deltaR3d_Perpendicular_Outer_EndCap;
   TH1D* hMC_deltaR3d_Outer_Barrel;
   TH1D* hMC_deltaR3d_Parallel_Outer_Barrel;
   TH1D* hMC_deltaR3d_Perpendicular_Outer_Barrel;
   TH1D* hMC_deltaR3d_Inner;
   TH1D* hMC_deltaR3d_Parallel_Inner;
   TH1D* hMC_deltaR3d_Perpendicular_Inner;
   TH1D* hMC_deltaR3d_Inner_EndCap;
   TH1D* hMC_deltaR3d_Parallel_Inner_EndCap;
   TH1D* hMC_deltaR3d_Perpendicular_Inner_EndCap;
   TH1D* hMC_deltaR3d_Inner_Barrel;
   TH1D* hMC_deltaR3d_Parallel_Inner_Barrel;
   TH1D* hMC_deltaR3d_Perpendicular_Inner_Barrel;

   //create histograms
   hMC_deltaR3d = new TH1D("hMC_deltaR3d", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d->Sumw2();
   hMC_deltaR3d_Parallel = new TH1D("hMC_deltaR3d_Parallel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel->Sumw2();
   hMC_deltaR3d_Perpendicular = new TH1D("hMC_deltaR3d_Perpendicular", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular->Sumw2();
   hMC_deltaR3d_EndCap = new TH1D("hMC_deltaR3d_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_EndCap->Sumw2();
   hMC_deltaR3d_Parallel_EndCap = new TH1D("hMC_deltaR3d_Parallel_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_EndCap->Sumw2();
   hMC_deltaR3d_Perpendicular_EndCap = new TH1D("hMC_deltaR3d_Perpendicular_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_EndCap->Sumw2();
   hMC_deltaR3d_Barrel = new TH1D("hMC_deltaR3d_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Barrel->Sumw2();
   hMC_deltaR3d_Parallel_Barrel = new TH1D("hMC_deltaR3d_Parallel_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Barrel->Sumw2();
   hMC_deltaR3d_Perpendicular_Barrel = new TH1D("hMC_deltaR3d_Perpendicular_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Barrel->Sumw2();
   hMC_deltaR3d_Outer = new TH1D("hMC_deltaR3d_Outer", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Outer->Sumw2();
   hMC_deltaR3d_Parallel_Outer = new TH1D("hMC_deltaR3d_Parallel_Outer", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Outer->Sumw2();
   hMC_deltaR3d_Perpendicular_Outer = new TH1D("hMC_deltaR3d_Perpendicular_Outer", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Outer->Sumw2();
   hMC_deltaR3d_Outer_EndCap = new TH1D("hMC_deltaR3d_Outer_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Outer_EndCap->Sumw2();
   hMC_deltaR3d_Parallel_Outer_EndCap = new TH1D("hMC_deltaR3d_Parallel_Outer_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Outer_EndCap->Sumw2();
   hMC_deltaR3d_Perpendicular_Outer_EndCap = new TH1D("hMC_deltaR3d_Perpendicular_Outer_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Outer_EndCap->Sumw2();
   hMC_deltaR3d_Outer_Barrel = new TH1D("hMC_deltaR3d_Outer_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Outer_Barrel->Sumw2();
   hMC_deltaR3d_Parallel_Outer_Barrel = new TH1D("hMC_deltaR3d_Parallel_Outer_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Outer_Barrel->Sumw2();
   hMC_deltaR3d_Perpendicular_Outer_Barrel = new TH1D("hMC_deltaR3d_Perpendicular_Outer_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Outer_Barrel->Sumw2();
   hMC_deltaR3d_Inner = new TH1D("hMC_deltaR3d_Inner", "CMS work in Progress", dR_Nbin, dR_xmin, 0.25*dR_xmax);
   hMC_deltaR3d_Inner->Sumw2();
   hMC_deltaR3d_Parallel_Inner = new TH1D("hMC_deltaR3d_Parallel_Inner", "CMS work in Progress", dR_Nbin, dR_xmin, 0.25*dR_xmax);
   hMC_deltaR3d_Parallel_Inner->Sumw2();
   hMC_deltaR3d_Perpendicular_Inner = new TH1D("hMC_deltaR3d_Perpendicular_Inner", "CMS work in Progress", dR_Nbin, dR_xmin, 0.25*dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Inner->Sumw2();
   hMC_deltaR3d_Inner_EndCap = new TH1D("hMC_deltaR3d_Inner_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Inner_EndCap->Sumw2();
   hMC_deltaR3d_Parallel_Inner_EndCap = new TH1D("hMC_deltaR3d_Parallel_Inner_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Inner_EndCap->Sumw2();
   hMC_deltaR3d_Perpendicular_Inner_EndCap = new TH1D("hMC_deltaR3d_Perpendicular_Inner_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Inner_EndCap->Sumw2();
   hMC_deltaR3d_Inner_Barrel = new TH1D("hMC_deltaR3d_Inner_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin,0.25*dR_xmax);
   hMC_deltaR3d_Inner_Barrel->Sumw2();
   hMC_deltaR3d_Parallel_Inner_Barrel = new TH1D("hMC_deltaR3d_Parallel_Inner_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, 0.25*dR_xmax);
   hMC_deltaR3d_Parallel_Inner_Barrel->Sumw2();
   hMC_deltaR3d_Perpendicular_Inner_Barrel = new TH1D("hMC_deltaR3d_Perpendicular_Inner_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, 0.25*dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Inner_Barrel->Sumw2();

   Long64_t nentries = fChain->GetEntriesFast();

   double ni_MC_x, ni_MC_y, ni_MC_z, ni_MC_rho;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       if (Cut(ientry) < 0) continue;
      //Get Branch addresses for cuts
      b_MC_TrkV_numberOfChargedParticles_0p2->GetEntry(ientry);
      b_MC_TrkV_momentumOut_pt->GetEntry(ientry);
      // print how many events are done:
      if( jentry%100000 == 0 )
           std::cout << "Loop over entry " << jentry << "/" << nentries << "." << std::endl;
      int NumberNI=0;
      for ( int i = 0; i < numberOfMC_TrkV; i++ )
      {
       //get values of x, y, and z of MC tracks
       ni_MC_x = MC_TrkV_x->at(i);
       ni_MC_y = MC_TrkV_y->at(i);
       ni_MC_z = MC_TrkV_z->at(i);
       ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );
       //default cuts
       if (MC_TrkV_numberOfChargedParticles_0p2->at(i) < 3 ) continue;
       if (MC_TrkV_momentumOut_pt->at(i) < 0.5 ) continue;
       if (ni_MC_rho < 1.7) continue;
       if (ni_MC_rho > 65) continue;
       NumberNI++;
      }
         if ( (NumberNI != 1) || numberOfPFDV != 1) continue;
      for ( int j = 0; j < numberOfMC_TrkV; j++ )
      {
         ni_MC_x = MC_TrkV_x->at(j);
         ni_MC_y = MC_TrkV_y->at(j);
         ni_MC_z = MC_TrkV_z->at(j);
         ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );
         double DeltaR3d_Min_Val=1000.;
         double DeltaR3dParallel_Min_Val=0.0;
         double DeltaR3dPerpendicular_Min_Val=0.0;
          //default cuts
          if (ni_MC_rho < 1.7) continue;
	  if (MC_TrkV_numberOfChargedParticles_0p2->at(j) < 3 ) continue;
          if (MC_TrkV_momentumOut_pt->at(j) < 0.5 ) continue;
          if (ni_MC_rho > 22) continue;
          //find the minimum deltaR
          if(DeltaR3d_Min_Val>(MC_TrkV_associationPFDV_deltaR3d->at(j)))
           {
	    DeltaR3d_Min_Val=(MC_TrkV_associationPFDV_deltaR3d->at(j));
            DeltaR3dParallel_Min_Val=(MC_TrkV_associationPFDV_deltaR3dParallel->at(j));
            DeltaR3dPerpendicular_Min_Val=(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(j));
            ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );
           }
   	  //fill histograms based on each region
          hMC_deltaR3d->Fill(DeltaR3d_Min_Val);
          hMC_deltaR3d_Parallel->Fill(DeltaR3dParallel_Min_Val);
          hMC_deltaR3d_Perpendicular->Fill(DeltaR3dPerpendicular_Min_Val);
          if(ni_MC_z > 25)
          {
           hMC_deltaR3d_EndCap->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_EndCap->Fill(DeltaR3dParallel_Min_Val);
           hMC_deltaR3d_Perpendicular_EndCap->Fill(DeltaR3dPerpendicular_Min_Val);
          }
          if(ni_MC_z < 25)
	  {
	   hMC_deltaR3d_Barrel->Fill(DeltaR3d_Min_Val);
 	   hMC_deltaR3d_Parallel_Barrel->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Barrel->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho > 19)
  	  {
	   hMC_deltaR3d_Outer->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Outer->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Outer->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho > 19 && ni_MC_z > 25)
	  {
	   hMC_deltaR3d_Outer_EndCap->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Outer_EndCap->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Outer_EndCap->Fill(DeltaR3dPerpendicular_Min_Val);
 	  }
	  if(ni_MC_rho > 19 && ni_MC_z < 25)
	  {
	   hMC_deltaR3d_Outer_Barrel->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Outer_Barrel->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Outer_Barrel->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho < 5)
	  {
	   hMC_deltaR3d_Inner->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Inner->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Inner->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho < 5 && ni_MC_z > 25)
	  {
	   hMC_deltaR3d_Inner_EndCap->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Inner_EndCap->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Inner_EndCap->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho < 5 && ni_MC_z < 25)
	  {
	   hMC_deltaR3d_Inner_Barrel->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Inner_Barrel->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Inner_Barrel->Fill(DeltaR3dPerpendicular_Min_Val);
 	  }
       }
   }

   outputFile->Write();
   outputFile->Close();

}
