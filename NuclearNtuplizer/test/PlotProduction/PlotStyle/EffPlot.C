#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1.h>
#include "TAxis.h"
#include<TMatrixD.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::max

TString NtupleName = "MCplot_100GeVpion";


void EffPlot(){

        gROOT->Clear();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(1);
        gStyle->SetPalette(1);
        gStyle->SetOptTitle(0);

TFile *f1 = new TFile(Form("../%s.root",NtupleName.Data()));

TH1F* hMC_TrkV_numberOftracks_0p2 = (TH1F*)f1->Get("hMC_TrkV_numberOftracks_0p2");
TH1F* hMC_TrkV_numberOftracks_0p5 = (TH1F*)f1->Get("hMC_TrkV_numberOftracks_0p5");
TH1F* hMC_TrkV_numberOftracks_1p0 = (TH1F*)f1->Get("hMC_TrkV_numberOftracks_1p0");
TH1F* hPFDV_numberOftracks_0p2 = (TH1F*)f1->Get("hPFDV_numberOftracks_0p2");
TH1F* hPFDV_numberOftracks_0p5 = (TH1F*)f1->Get("hPFDV_numberOftracks_0p5");
TH1F* hPFDV_numberOftracks_1p0 = (TH1F*)f1->Get("hPFDV_numberOftracks_1p0");


///////////////////////////
TCanvas *c1=new TCanvas("c1","Background",600,400);
  c1->Divide(2,1);
  //c1->SetBottomMargin(0.15);
  //c1->SetLeftMargin(0.15);
  c1->cd(1);
  hMC_TrkV_numberOftracks_0p2->GetXaxis()->SetTitleOffset(1.2);
  hMC_TrkV_numberOftracks_0p2->GetYaxis()->SetTitleOffset(1.7);
  hMC_TrkV_numberOftracks_0p2->GetXaxis()->SetTitleSize(0.04);
  hMC_TrkV_numberOftracks_0p2->GetYaxis()->SetTitleSize(0.04);
  hMC_TrkV_numberOftracks_0p2->GetXaxis()->SetLabelSize(0.04);
  hMC_TrkV_numberOftracks_0p2->GetYaxis()->SetLabelSize(0.04);
  hMC_TrkV_numberOftracks_0p2->SetLineStyle(1);
  hMC_TrkV_numberOftracks_0p2->SetLineColor(kBlue);
  hMC_TrkV_numberOftracks_0p2->SetMarkerStyle(11);
  hMC_TrkV_numberOftracks_0p2->SetMarkerColor(kBlue);
  hMC_TrkV_numberOftracks_0p2->SetLineWidth(2);
  hMC_TrkV_numberOftracks_0p2-> GetYaxis()->SetTitle("entries");
  hMC_TrkV_numberOftracks_0p2-> GetXaxis()->SetTitle("# of charged tracks with p_{T}>0.2 GeV/c");

  hPFDV_numberOftracks_0p2->SetLineColor(kRed);
  hPFDV_numberOftracks_0p2->SetMarkerColor(kRed);
  hPFDV_numberOftracks_0p2->SetLineWidth(2);

  hMC_TrkV_numberOftracks_0p2 -> Draw("hist");
  hPFDV_numberOftracks_0p2 -> Draw("esame");

  c1->cd(2);
  EffPlot_0p2 = (TH1F*)hPFDV_numberOftracks_0p2->Clone("EffPlot_0p2");
  EffPlot_0p2->Divide(hMC_TrkV_numberOftracks_0p2);
  EffPlot_0p2-> Draw("e");

  c1->Print("Plots/EffPlot.png");
///////////////////////////

f1->Close();

}//end main program:EffPlot 
