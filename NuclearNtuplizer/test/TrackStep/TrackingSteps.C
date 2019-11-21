#define TrackingSteps_cxx
#include "TrackingSteps.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void TrackingSteps::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L TrackingSteps.C
//      Root > TrackingSteps t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
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

   Long64_t nentries = fChain->GetEntriesFast();

   
   int nAlgo[26];
   for ( unsigned int i = 0; i < 26; i++ ){
     nAlgo[i] = 0;
   }

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if( jentry%100000 == 0 )
      std::cout << "Loop over entry " << jentry << "/" << nentries << "." << std::endl;
      if (jentry > 100000)break;// only if want process only part of data

      // if (Cut(ientry) < 0) continue;
      //cout <<  (*PFDV_isNuclear).size() << endl;
      for (unsigned int inucl = 0; inucl < (*PFDV_isNuclear).size(); inucl++){
	//	if (!(*PFDV_isNuclear)[inucl]) continue;
	
      double x = (*PFDV_x)[inucl], y = (*PFDV_y)[inucl],  z = (*PFDV_z)[inucl];

      double rho = sqrt(x*x+y*y);
      
      int maxAlgo = 0;
      double numHitMean = 0;
      // cout << ((*PFDV_vTrack_algo)[inucl]).size() << endl;
      unsigned int numTracks = ((*PFDV_vTrack_algo)[inucl]).size();
      if(numTracks > 0){
	      for (unsigned int j=0;j<numTracks;j++) {
   		//	if ((*tkSecondary)[j]){
		//cout << "trk secondary " << (*tkSecondary)[j] << endl;
		//	cout << "(*PFDV_vTrack_algo)[j] = " << (*PFDV_vTrack_algo)[inucl][j] << endl;
		if(((*PFDV_vTrack_algo)[inucl])[j]>maxAlgo) maxAlgo=((*PFDV_vTrack_algo)[inucl])[j];
		  //	}
	        double numHit = (*PFDV_vTrack_numberOfValidHits)[inucl][j];
        	numHitMean = numHitMean + numHit;
	        hNumOfValidHits -> Fill(numHit);
        	//std::cout << "NumOfValidHits = " << (*PFDV_vTrack_numberOfValidHits)[inucl][j] << std::endl;
	      }
	numHitMean = numHitMean/numTracks;
	hNumOfValidHitsMean -> Fill(numHitMean);
	// 1.8-3.5; 6.-7.5; 10-12; 15-17;
        if(rho > 1.8 && rho < 3.5) hNumOfValidHitsMeanBPL1 -> Fill(numHitMean);
        if(rho > 6. && rho < 7.5)  hNumOfValidHitsMeanL2 -> Fill(numHitMean);
        if(rho > 10. && rho < 12.) hNumOfValidHitsMeanL3 -> Fill(numHitMean);
        if(rho > 15. && rho < 17.) hNumOfValidHitsMeanL4 -> Fill(numHitMean);
      }
      

      //if (fabs(z) > 25) continue;
      if (fabs(z) > 25 || rho > 25) continue;

      if (maxAlgo==4) h4->Fill(rho);
      else if (maxAlgo==5) h5->Fill(rho);
      else if (maxAlgo==6) h6->Fill(rho);
      else if (maxAlgo==7) h7->Fill(rho);
      else if (maxAlgo==8) h8->Fill(rho);
      else if (maxAlgo==9) h9->Fill(rho);
      else if (maxAlgo==10) h10->Fill(rho);
      else if (maxAlgo==11) h11->Fill(rho);
      else if (maxAlgo==12) h12->Fill(rho);
      //else cout << "ARGH!!!   " << maxAlgo << endl;

      }

   }


   out->Write();
   /*
 h4->Write();
   h5->Write();
   h6->Write();
   h7->Write();
   h8->Write();
   h9->Write();
   h10->Write();
   h11->Write();
   h12->Write();
   out->Write();
   out->Close();
   */

   
     TCanvas* c1 = new TCanvas("c1","");
   //   gStyle->SetOptStat(0);
  
   h5->Add(h4);
   h6->Add(h5);
   h7->Add(h6);
   h8->Add(h7);
   h9->Add(h8);
   h10->Add(h9);
   h11->Add(h10);
   h12->Add(h11);

   h4->SetFillColor(kBlack);
   h5->SetFillColor(kRed);
   h6->SetFillColor(kGreen);
   h7->SetFillColor(kMagenta);
   h8->SetFillColor(kCyan);
   h9->SetFillColor(kOrange);
   h10->SetFillColor(10);
   h11->SetFillColor(10);
   h12->SetFillColor(kBlue);

   h12->SetStats(0);

   h12->SetTitle("");
   h12->GetXaxis()->SetTitle("#rho");
   h12->GetYaxis()->SetTitle("Fraction of Nucl. Int.");
   h12->GetYaxis()->SetTitleOffset(1.3);
   h12->GetXaxis()->SetRangeUser(0.,25.);
   h12->Draw();
   
   h11->Draw("same");
   h10->Draw("same");
   h9->Draw("same");
   h8->Draw("same");
   h7->Draw("same");
   h6->Draw("same");
   h5->Draw("same");
   h4->Draw("same");
   
   
   TLegend* leg = new TLegend(0.1,0.9,0.9,1);
   leg->SetNColumns(4);
   leg->SetFillColor(kWhite);
   leg->AddEntry(h4, "N_{algo}=0","f");
   leg->AddEntry(h6, "N_{algo}=2","f");
   leg->AddEntry(h8, "N_{algo}=4","f");
   //   leg->AddEntry(h10,"N_{algo}=6","f");
   leg->AddEntry(h5, "N_{algo}=1","f");
   leg->AddEntry(h7, "N_{algo}=3","f");
   leg->AddEntry(h9, "N_{algo}=5","f");
   leg->AddEntry(h12,"N_{algo}=8","f");
   leg->Draw();
      cout << "bla 3" << endl;
   TLatex *t1a = new TLatex(0.6,0.76,"CMS Preliminary");
   t1a->SetTextFont(42);
   t1a->SetTextSize(0.05);
   t1a->SetTextAlign(22);
   t1a->SetNDC(true);
   t1a->Draw();
   cout << "bla 3.1" << endl;
   c1->Update();
   //   c1.SetLogy();
   //   c1.SetGridy();
   
   c1->SaveAs("Tracking.png");
   cout << "bla 5" << endl;
     
   TCanvas* c2 = new TCanvas("c2","");
   c2->cd();
   hNumOfValidHits -> Draw();
   c2->Update();
   c2->SaveAs("NumOfValidHits.png");

   hNumOfValidHitsMean -> Draw();
   c2->Update();
   c2->SaveAs("NumOfValidHitsMean.png");

   hNumOfValidHitsMeanBPL1 -> Draw();
   c2->Update();
   c2->SaveAs("NumOfValidHitsMeanBPL1.png");

   hNumOfValidHitsMeanL2 -> Draw();
   c2->Update();
   c2->SaveAs("NumOfValidHitsMeanL2.png");

   hNumOfValidHitsMeanL3 -> Draw();
   c2->Update();
   c2->SaveAs("NumOfValidHitsMeanL3.png");

   hNumOfValidHitsMeanL4 -> Draw();
   c2->Update();
   c2->SaveAs("NumOfValidHitsMeanL4.png");


   out->Close();

}
//PFDV_vTrack_algo
