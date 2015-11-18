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

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
   
      
      if (ientry < 0) break;
      //if (ientry > 100000) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      //   if (!(isNucl || ( isNuclLoose &&  mOut > 0.5 && ((*tkDxy)[0] > 0.4 || (*tkDxy)[0] < -0.4)  &&  ((*tkDxy)[1] > 0.4 || (*tkDxy)[1] < -0.4)  ) ) || !isAssoc) continue;
      if (!(isNucl) || isAssoc) continue;
      //      if (!(( isNuclLoose &&  mOut > 0.5 && ((*tkDxy)[0] > 0.4 || (*tkDxy)[0] < -0.4)  &&  ((*tkDxy)[1] > 0.4 || (*tkDxy)[1] < -0.4)  ) ) || isAssoc) continue;

      //	  !(isNuclLoose && nOut - nOutTkStep67Poor - nOutTkStep67Good == 2 && mOut > 0.6 && ptOut > 0.5 && angle < 15)) continue;
      //if (sqrt(x*x+y*y) < 24) continue;
      // if (!isConvLoose) continue; 
      if (abs(-log(tan(thetaOut/2)))>1.4) continue;

      int maxAlgo = 0;
      for (unsigned int j=0;j<tkAlgo->size();++j) {
	//	if ((*tkSecondary)[j]){
	//cout << "trk secondary " << (*tkSecondary)[j] << endl;
	  if((*tkAlgo)[j]>maxAlgo) maxAlgo=(*tkAlgo)[j];
	  //	}
      }
      
      double rho = sqrt(x*x+y*y);

      if (maxAlgo==4) h4->Fill(rho);
      else if (maxAlgo==5) h5->Fill(rho);
      else if (maxAlgo==6) h6->Fill(rho);
      else if (maxAlgo==7) h7->Fill(rho);
      else if (maxAlgo==8) h8->Fill(rho);
      else if (maxAlgo==9) h9->Fill(rho);
      else if (maxAlgo==10) h10->Fill(rho);
      else if (maxAlgo==11) h11->Fill(rho);
      else if (maxAlgo==12) h12->Fill(rho);
      else cout << "ARGH!!!" << endl;
      
      /*
      if (thetaOut > 0 && thetaOut < TMath::Pi())
	{
	  double eta = -log(tan(thetaOut/2));
	  cout << "rho =" << rho << " theta = " << thetaOut << " eta " << -log(tan(thetaOut/2)) << endl;
	  
	if (maxAlgo==4) h4->Fill(eta);
	else if (maxAlgo==5) h5->Fill(eta);
	else if (maxAlgo==6) h6->Fill(eta);
	else if (maxAlgo==7) h7->Fill(eta);
	else if (maxAlgo==8) h8->Fill(eta);
	else if (maxAlgo==9) h9->Fill(eta);
	else if (maxAlgo==10) h10->Fill(eta);
	else if (maxAlgo==11) h11->Fill(eta);
	else cout << "ARGH" << endl;
	  
      }
      */
   }

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

   TCanvas c1;
   gStyle->SetOptStat(0);
  
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

   /*
   h4->Scale(1./((float)h12->Integral()));
   h5->Scale(1./((float)h12->Integral()));
   h6->Scale(1./((float)h12->Integral()));
   h7->Scale(1./((float)h12->Integral()));
   h8->Scale(1./((float)h12->Integral()));
   h9->Scale(1./((float)h12->Integral()));
   h10->Scale(1./((float)h12->Integral()));
   h11->Scale(1./((float)h12->Integral()));
   h12->Scale(1./((float)h12->Integral()));
   */

   h12->SetTitle("");
   h12->GetXaxis()->SetTitle("#rho");
   h12->GetYaxis()->SetTitle("Fraction of Nucl. Int.");
   h12->GetYaxis()->SetTitleOffset(1.3);
   h12->Draw();
   h11->Draw("same");
   h10->Draw("same");
   h9->Draw("same");
   h8->Draw("same");
   h7->Draw("same");
   h6->Draw("same");
   h5->Draw("same");
   h4->Draw("same");
   
   leg = new TLegend(0.1,0.9,0.9,1);
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
   
   TLatex *t1a = new TLatex(0.6,0.76,"CMS Preliminary");
   t1a->SetTextFont(42);
   t1a->SetTextSize(0.05);
   t1a->SetTextAlign(22);
   t1a->SetNDC(isNDC = kTRUE);
   t1a->Draw();

   c1.Update();
   c1.SetLogy();
   c1.SetGridy();
c1.Update();

c1.SaveAs("RNItmp_Rho_isntAssoc_3trk_log.png");

  
}
