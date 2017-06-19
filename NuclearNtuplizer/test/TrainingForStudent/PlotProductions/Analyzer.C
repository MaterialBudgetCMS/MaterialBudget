#define Analyzer_cxx
#include "Analyzer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Analyzer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Analyzer.C
//      root> Analyzer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

// creat output file:
   TFile* outputFile;
   outputFile = new TFile( "outputHisto.root", "RECREATE" );
// initialize histograms:
   // Simulated/Gen MC
   TH1D* hMC_TrkV_R;
   TH2D* hMC_XY;
   // RECO 
   TH1D* hPFDV_TrkV_R;
   TH2D* hPFDV_XY;

// creat hitgrams
  hMC_TrkV_R = new TH1D( "hMC_TrkV_R", "N.I. in Tracker",240, 0, 60 );
  hMC_TrkV_R->Sumw2();
  hMC_XY = new TH2D( "hMC_XY", "CMS work in progress", 500, -25, 25, 500, -25, 25 );
  hMC_TrkV_R->Sumw2();
  
  hPFDV_TrkV_R = new TH1D( "hPFDV_TrkV_R", "N.I. in Tracker",240, 0, 60 );
  hPFDV_TrkV_R->Sumw2();
  hPFDV_XY = new TH2D( "hPFDV_XY", "CMS work in progress", 500, -25, 25, 500, -25, 25 );
  hPFDV_TrkV_R->Sumw2();


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // print how many events are done:
      if( jentry%100000 == 0 )
           std::cout << "Loop over entry " << jentry << "/" << nentries << "." << std::endl;

      // for by Simulated/Gen vertices:
      for ( unsigned int i = 0; i < numberOfMC_TrkV; i++ )
      {
         double ni_MC_x = MC_TrkV_x->at(i);
         double ni_MC_y = MC_TrkV_y->at(i);
         double ni_MC_z = MC_TrkV_z->at(i);
         double ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );
 
         // Fill histograms:
         hMC_TrkV_R -> Fill (ni_MC_rho);
         hMC_XY -> Fill (ni_MC_x, ni_MC_y);
      }
      // for by RECO vertices:
      for ( unsigned int i = 0; i < numberOfPFDV; i++ )
      {
         double ni_x = PFDV_x->at(i);
         double ni_y = PFDV_y->at(i);
         double ni_z = PFDV_z->at(i);
         double ni_rho = TMath::Sqrt( ni_x*ni_x + ni_y*ni_y );

         // Fill histograms:
         hPFDV_TrkV_R -> Fill (ni_rho);
         hPFDV_XY -> Fill (ni_x, ni_y);
      }
   }// end by jentry

   // write histograms in output and close it:
   outputFile->Write();
   outputFile->Close();

}
