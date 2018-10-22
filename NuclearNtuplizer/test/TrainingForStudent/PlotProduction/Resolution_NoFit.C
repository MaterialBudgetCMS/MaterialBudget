#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1.h>
#include "TAxis.h"
#include <TMatrixD.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include <TMath.h>
#include "Fit/BinData.h"
#include <TF1.h>
#include <TROOT.h>
#include <string>
#include <TMinuit.h>
#include <TLine.h>
#include <stdlib.h>
#include <TSystem.h>
#include <sstream>
#include <TPaveStats.h>
#include <TLegend.h>
#include <TKey.h>
#include <TFile.h>
#include <TClass.h>
#include <Math/Minimizer.h>

void ResolutionCalc(TH1* hist, double& sigma, double& sigmay)
{
 double entries68 = 0.68*hist->GetEntries();
 double count = 0.0;
 int NBins = hist->GetNbinsX();
 for(int i = 0; i < NBins; i++)
 {
  count += hist->GetBinContent(i+1);
  if(count >= entries68)
  {
   sigma = hist->GetBinCenter(i+1);
   sigmay = hist->GetBinContent(i+1);
   break;
  }
 }
}

void Drawing(TH1* hist, string filename)
{
 string canvas_name = hist->GetName();
 canvas_name += "_canvas";
 TCanvas *canvas = new TCanvas(canvas_name.c_str(),canvas_name.c_str(),750,500);
 canvas->cd();
 hist->Draw();
 double sigma = 0.0;
 double sigmay = 0.0;
 ResolutionCalc(hist,sigma,sigmay);
 TLine* sigma_line = new TLine(sigma,0.0,sigma,sigmay);
 sigma_line->SetLineColor(kBlue);
 sigma_line->SetLineStyle(7);
 sigma_line->SetLineWidth(2);
 sigma_line->Draw("SAMES");
 canvas->Update();

 char sigma_char[50];
 sprintf(sigma_char,"%.2lf",10000.0*sigma);
 string sigma_str = "Resolution = ";
 sigma_str += sigma_char;
 sigma_str += " #mum";
 TString sigma_tstr = sigma_str;

 TLegend* leg = new TLegend(0.72,0.5,0.98,0.6,"");
 leg->SetFillColor(kWhite);
 leg->SetTextColor(kBlue);
 leg->AddEntry((TObject*)0, sigma_tstr, "");
 leg->Draw("SAMES");
 canvas->Update();
 
 canvas->SaveAs(filename.c_str());
 delete leg;
 delete sigma_line;
 delete canvas;
}

vector<TH1*> list_histos(const char *fname)
{
 std::vector<TH1*> vect_hist;
 TKey *key;
 TFile *f = TFile::Open(fname,"READ");
 string skip = "Inner_EndCap";
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return vect_hist;
 }
 TIter next((TList *)f->GetListOfKeys());
 while((key = (TKey *)next()))
 {
  TClass *cl = gROOT->GetClass(key->GetClassName());
  if(cl->InheritsFrom("TH1"))
  {
   TH1 *h = (TH1*)key->ReadObj();
   string name = h->GetName();
   if(name.find(skip) != std::string::npos) continue;
   vect_hist.push_back(h);
  }
 }
 return vect_hist;
}

void Resolution_NoFit(){

gROOT->Clear();
gStyle->SetOptStat(1);
gStyle->SetOptFit(1111);
gStyle->SetPalette(1);
gStyle->SetOptTitle(0);
string fname;

for(int k = 0; k < 3; k++)
{
 if(k==0)
 {
  fname = "ResolutionPlots_10GeV_2018.root";
 }
 if(k==1)
 {
  fname = "ResolutionPlots_50GeV_2018.root";
 }
 if(k==2)
 {
  fname = "ResolutionPlots_100GeV_2018.root";
 }

//const char *fname1 = "ResolutionPlots_2015.root";

// open file:
std::vector<TH1*> vect_hist = list_histos(fname.c_str());
std::vector<string> vect_filename;

int vect_hist_size = vect_hist.size();
for (int i = 0; i < vect_hist_size; i++)
{
 string dir = "Resolution_NoFit/";
 if(k == 0)
 {
  dir += "10GeV_2018_Results/";
 }
 if(k == 1)
 {
  dir += "50GeV_2018_Results/";
 }
 if(k == 2)
 {
  dir += "100GeV_2018_Results/";
 }
 string filename = vect_hist[i]->GetName();
 dir += filename;
 dir += ".png";
 vect_filename.push_back(dir);
}

for (int i = 0; i < vect_hist_size; i++)
 {
  vect_hist[i]->GetXaxis()->SetTitle("DeltaR [cm]");
  vect_hist[i]->GetYaxis()->SetTitle("Number Of Events");
  vect_hist[i]->SetLineColor(kBlack);
  Drawing(vect_hist[i],vect_filename[i]);
 }
}
}

