#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1.h>
#include "TAxis.h"
#include<TMatrixD.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include "TROOT.h"
#include "TFile.h"
#include <TH1F.h>
#include <TPad.h>


TString NtupleName = "MCplot_100GeVpion";
TCanvas* drawOverlay(TH1F* hMC_isNI, TH1F* hMC_isAssRECO, TString TitleX, TString PicName)
{

TCanvas *c1=new TCanvas("c1","Background",600,400);
  c1->Divide(2,1);
  //c1->SetBottomMargin(5.);
  c1->cd(1);
  TPad* pad1 = (TPad*)c1 ->GetPad(1);
  //gStyle->SetPaperSize(10.,5.);
  pad1->SetLeftMargin(0.2);
  pad1->SetBottomMargin(0.35);
  hMC_isNI->GetXaxis()->SetTitleOffset(1.2);
  hMC_isNI->GetYaxis()->SetTitleOffset(1.8);
  hMC_isNI->GetXaxis()->SetTitleSize(0.05);
  hMC_isNI->GetYaxis()->SetTitleSize(0.05);
  hMC_isNI->GetXaxis()->SetLabelSize(0.05);
  hMC_isNI->GetYaxis()->SetLabelSize(0.05);
  hMC_isNI->SetLineStyle(1);
  hMC_isNI->SetLineColor(kBlue);
  hMC_isNI->SetMarkerStyle(11);
  hMC_isNI->SetMarkerColor(kBlue);
  hMC_isNI->SetLineWidth(2);
  hMC_isNI-> GetYaxis()->SetTitle("Entries");
  hMC_isNI-> GetXaxis()->SetTitle("Radius [cm]");
  hMC_isNI->SetTitle(TitleX);

  hMC_isAssRECO->SetLineColor(kRed);
  hMC_isAssRECO->SetMarkerColor(kRed);
  hMC_isAssRECO->SetLineWidth(2);

  hMC_isNI -> Draw("hist");
  hMC_isAssRECO -> Draw("esame");

  c1->cd(2);
  TPad* pad2 = (TPad*)c1 ->GetPad(2);
  //pad2->SetLeftMargin(0.2);
  pad2->SetBottomMargin(0.35);

  TH1F* h_eff = (TH1F*)hMC_isAssRECO->Clone("h_eff");
  h_eff->Divide(hMC_isNI);
  h_eff->GetXaxis()->SetTitleSize(0.05);
  h_eff->GetYaxis()->SetTitleSize(0.05);
  h_eff->GetXaxis()->SetLabelSize(0.05);
  h_eff->GetYaxis()->SetLabelSize(0.05);
  h_eff->GetYaxis()->SetTitle("Efficiency");
  h_eff->GetXaxis()->SetTitle("Radius [cm]");
  h_eff->SetTitle(TitleX);
  h_eff->GetXaxis()->SetTitleOffset(1.2);
  h_eff->GetYaxis()->SetTitleOffset(1.7);
  h_eff->GetXaxis()->SetNdivisions(510);// n = n1 + 100*n2 + 10000*n3
  h_eff->GetYaxis()->SetNdivisions(505);// n = n1 + 100*n2 + 10000*n3
  h_eff-> Draw("e");

  c1->Print("Plots/"+PicName+".png");

return c1;

delete c1;
delete hMC_isNI;
delete hMC_isAssRECO;
delete h_eff;
}

void EffPlot(){

        gROOT->Clear();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(1);
        gStyle->SetPalette(1);
        //gStyle->SetOptTitle(0);
        //gStyle->SetPadLeftMargin(0.4);
TFile *f1 = new TFile(Form("../%s.root",NtupleName.Data()));

TH1F* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2 = (TH1F*)f1->Get("hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2");
TH1F* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5 = (TH1F*)f1->Get("hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5");
TH1F* hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0 = (TH1F*)f1->Get("hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0");
TH1F* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2 = (TH1F*)f1->Get("hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2");
TH1F* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5 = (TH1F*)f1->Get("hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5");
TH1F* hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0 = (TH1F*)f1->Get("hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0");

TH1F* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2 = (TH1F*)f1->Get("hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2");
TH1F* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5 = (TH1F*)f1->Get("hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5");
TH1F* hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0 = (TH1F*)f1->Get("hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0");
TH1F* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2 = (TH1F*)f1->Get("hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2");
TH1F* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5 = (TH1F*)f1->Get("hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5");
TH1F* hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0 = (TH1F*)f1->Get("hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0");


///////////////////////////

TString ExtraTitle = "Barrel: at least 3 tracks with p_{T} > 0.2 GeV/c";
TString picName = "Eff_Barrel_pt0p2";
drawOverlay(hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2, hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2, ExtraTitle, picName);

ExtraTitle = "Barrel: at least 3 tracks with p_{T} > 0.5 GeV/c";
picName = "Eff_Barrel_pt0p5";
drawOverlay(hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5, hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5, ExtraTitle, picName);

ExtraTitle = "Barrel: at least 3 tracks with p_{T} > 1.0 GeV/c";
picName = "Eff_Barrel_pt1p0";
drawOverlay(hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0, hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0, ExtraTitle, picName);


ExtraTitle = "Forward: at least 3 tracks with p_{T} > 0.2 GeV/c";
picName = "Eff_Forward_pt0p2";
drawOverlay(hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p2, hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p2, ExtraTitle, picName);

ExtraTitle = "Forward: at least 3 tracks with p_{T} > 0.5 GeV/c";
picName = "Eff_Forward_pt0p5";
drawOverlay(hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr0p5, hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr0p5, ExtraTitle, picName);

ExtraTitle = "Forward: at least 3 tracks with p_{T} > 1.0 GeV/c";
picName = "Eff_Forward_pt1p0";
drawOverlay(hMC_TrkV_R_isNuclearInteraction_Rebin_Forward_3Tr1p0, hMC_TrkV_R_isAssociatedPF_Rebin_Forward_3Tr1p0, ExtraTitle, picName);


///////////////////////////

f1->Close();

}//end main program:EffPlot 
