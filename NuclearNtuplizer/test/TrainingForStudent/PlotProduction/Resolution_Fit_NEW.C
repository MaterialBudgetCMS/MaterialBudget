#include <TH2.h>
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

Double_t Fit_Landau(Double_t *x,Double_t *par)
{
 double norm = par[0];
 double mean = par[1];
 double sigma = par[2];

 return norm*TMath::Landau(x[0]-mean,sigma,0);
}

Double_t Fit_Voigt(Double_t *x,Double_t *par)
{
 double norm = par[0];
 double mean = par[1];
 double sigma = par[2];
 double lg = par[3];

 if ((sigma < 0 || lg < 0) || (sigma==0 && lg==0))
 {
  //cout << "CHECK FIT" << endl;
  //return 10.0;
  //sigma+=1.0e-06;
 }

 return norm*TMath::Voigt(x[0]-mean,sigma,lg);
}

Double_t Fit_Cauchy(Double_t *x,Double_t *par)
{
/* 
 //to fit with voigt
 TF1* func = new TF1("func", Fit_Voigt, 0.0, 0.95/PerpendicularFactor, 4);
 func->SetParameter(0,2.0*(vect_hist[i]->Integral()));
 func->SetParameter(1,0.0);
 func->SetParameter(2,0.002*vect_hist[i]->GetRMS());
 func->SetParameter(3,2.0*vect_hist[i]->GetRMS());
 
 //func->SetParLimits(0,0.000001,10000000.0);
 //func->SetParLimits(1,-10.0,1.0);
 //func->SetParLimits(2,0.00000001,100000.0);
 //func->SetParLimits(3,0.00000001,100000.0);
 func->SetParName(0,"norm");
 func->SetParName(1,"mean");
 func->SetParName(2,"sigma");
 func->SetParName(3,"lg");
*/
   Double_t pi = TMath::Pi();
   Double_t norm = par[0];
   Double_t x0 = par[1];
   Double_t b = par[2];
   return norm*(b/(pi * ((x[0]-x0)*(x[0]-x0) + b*b)));
}

vector<TH1*> list_histos(const char *fname)
{
 std::vector<TH1*> vect_hist;
 TKey *key;
 TFile *f = TFile::Open(fname,"READ");
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
   vect_hist.push_back(h);
  }
 }
 return vect_hist;
}

void Results (std::vector<TString> vect_status_landau, std::vector<TString> vect_status_cauchy)
{
cout << endl << "FIT RESULTS Cauchy" << endl;
int success_cauchy = 0;
int problems_cauchy = 0;
int failed_cauchy = 0;
int failure_cauchy = 0;
int call_limit_cauchy = 0;

for(int i=0; i<vect_status_cauchy.size(); i++)
{
 if(vect_status_cauchy[i] == "SUCCESSFUL")
 {
  success_cauchy++;
 }
 if(vect_status_cauchy[i] == "PROBLEMS  ")
 {
  problems_cauchy++;
 }
 if(vect_status_cauchy[i] == "FAILED    ")
 {
  failed_cauchy++;
 }
 if(vect_status_cauchy[i] == "FAILURE   ")
 {
  failure_cauchy++;
 }
 if(vect_status_cauchy[i] == "CALL LIMIT")
 {
  call_limit_cauchy++;
 }
}
 cout << "Total Successful fits = " << success_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*success_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Problems fits = " << problems_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*problems_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Failed fits = " << failed_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*failed_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Failure fits = " << failure_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*failure_cauchy/vect_status_cauchy.size()) << "%" << endl; 
 cout << "Total Call Limit fits = " << call_limit_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*call_limit_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Fits = " << success_cauchy+problems_cauchy+failed_cauchy+failure_cauchy+call_limit_cauchy << "/" << vect_status_cauchy.size() << endl;

cout << endl << "FIT RESULTS Landau" << endl;
int success_landau = 0;
int problems_landau = 0;
int failed_landau = 0;
int failure_landau = 0;
int call_limit_landau = 0;

for(int i=0; i<vect_status_cauchy.size(); i++)
{
 if(vect_status_landau[i] == "SUCCESSFUL")
 {
  success_landau++;
 }
 if(vect_status_landau[i] == "PROBLEMS  ")
 {
  problems_landau++;
 }
 if(vect_status_landau[i] == "FAILED    ")
 {
  failed_landau++;
 }
 if(vect_status_landau[i] == "FAILURE   ")
 {
  failure_landau++;
 }
 if(vect_status_landau[i] == "CALL LIMIT")
 {
  call_limit_landau++;
 }
}
 cout << "Total Successful fits = " << success_landau << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*success_landau/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Problems fits = " << problems_landau << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*problems_landau/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Failed fits = " << failed_landau << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*failed_landau/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Failure fits = " << failure_landau << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*failure_landau/vect_status_cauchy.size()) << "%" << endl; 
 cout << "Total Call Limit fits = " << call_limit_landau << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*call_limit_landau/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Fits = " << success_landau+problems_landau+failed_landau+failure_landau+call_limit_landau << "/" << vect_status_cauchy.size() << endl;
 
 cout << endl;

}


void Resolution_Fit_NEW(){

cout << endl << endl << endl << endl;

gROOT->Clear();
gStyle->SetOptStat(0);
gStyle->SetOptFit(1111);
gStyle->SetPalette(1);
gStyle->SetOptTitle(0);

const char *fname = "ResolutionPlots_10GeV_2018.root";
//const char *fname = "ResolutionPlots_2015.root";

// open file:
TFile *f1 = new TFile(fname,"READ");
//bool FixMean=true;
bool FixMean=false;
std::vector<TH1*> vect_hist = list_histos(fname);

std::vector<TCanvas*> vect_canvas;
std::vector<string> vect_filename;
std::vector<TString> vect_status_landau;
std::vector<TString> vect_status_cauchy;

for (int i = 0; i < vect_hist.size(); i++)
{
 string canvasname = vect_hist[i]->GetName();
 canvasname += "_canvas";
 TCanvas* dummy_canvas = new TCanvas((canvasname).c_str(),(canvasname).c_str(),750,500);
 vect_canvas.push_back(dummy_canvas);
 string dir = "10GeV_2018_Results";
 //string dir = "2015_Results";
 if(FixMean)
 {
  dir+="_ZeroMean/";
 }
 else
 {
  dir+="_Default/";
 }
 string filename = vect_hist[i]->GetName();
 dir += filename;
 dir += ".png";
 vect_filename.push_back(dir);
}

for (int i = 0; i < vect_hist.size(); i++)
{
 vect_hist[i]->GetXaxis()->SetTitle("DeltaR");
 vect_hist[i]->GetYaxis()->SetTitle("Number Of Events");
 vect_canvas[i]->cd();
 cout << endl << "Fitting " << vect_hist[i]->GetName() << "   (" << i+1 << "/27)" << endl;
 const char* histname = vect_hist[i]->GetName();
 string histname_str = histname;
 string perp = "Perpendicular";
 double PerpendicularFactor;
 if(histname_str.find(perp) != std::string::npos)
 {
  PerpendicularFactor=10.0;
 }
 else
 {
  PerpendicularFactor=1.0;
 }

 //Cauchy
 TF1 *func = new TF1("func", Fit_Cauchy, 0.0, 0.95*vect_hist[i]->GetXaxis()->GetXmax(), 3);
 
 func->SetParameter(0,0.5*vect_hist[i]->GetNormFactor());
 if(FixMean)
 {
  func->FixParameter(1,0.0);
 }
 else
 {
  func->SetParameter(1,0.0);
 }
 func->SetParameter(2,0.07*vect_hist[i]->GetRMS());

 //func->SetParLimits(0,0.0,10000.0);
 //func->SetParLimits(1,-1.0,0.5/PerpendicularFactor);
 func->SetParLimits(2,0.0,10.0);

 func->SetParName(0,"norm");
 func->SetParName(1,"mean");
 func->SetParName(2,"gamma");

 vect_hist[i]->SetLineColor(kBlack);
 TH1* vect_hist_clone = (TH1*)(vect_hist[i]->Clone());

 //cout << endl << "Fit Cauchy" << endl;

 //func->SetLineColor(kRed); 
 func->SetLineColorAlpha(kRed,0.0); 
 vect_hist[i]->Fit(func,"QEMR");

 TString status_cauchy = gMinuit->fCstatu;
 vect_status_cauchy.push_back(status_cauchy);

 func->Draw("SAMES");

 vect_canvas[i]->Update();


 TPaveStats *stats_cauchy = (TPaveStats*)vect_hist[i]->GetListOfFunctions()->FindObject("stats");
 stats_cauchy->SetTextColor(kRed);
 stats_cauchy->SetLineColor(kRed);
 stats_cauchy->SetY1NDC(0.9);
 stats_cauchy->SetY2NDC(0.7);
 //stats_cauchy->Draw("SAMES");
 vect_canvas[i]->Update(); 

//Landau
 cout << endl << "Fit Landau" << endl;
 //vect_hist_clone->Fit("landau","EMR","SAMES",0.,0.95/PerpendicularFactor); //default fit
 //TF1* landau_fit = (TF1*)vect_hist_clone->GetFunction("landau");

 //fix MPV of Landau to 0
 TF1* landau_fit = new TF1("func_landau","landau");//,0.0,0.95/PerpendicularFactor);
 landau_fit->SetLineColor(kBlue);
 landau_fit->SetParameter(0,0.5*vect_hist_clone->GetNormFactor());
 if(FixMean)
 {
  landau_fit->FixParameter(1,0.0);
 }
 else
 {
  landau_fit->SetParameter(1,0.0);
 }
 landau_fit->SetParameter(2,0.08*vect_hist_clone->GetRMS());
 vect_hist_clone->Fit(landau_fit,"QEMR","SAMES",0.0,0.95*vect_hist_clone->GetXaxis()->GetXmax());
 vect_canvas[i]->Update();
 
 TPaveStats *stats_landau = (TPaveStats*)vect_hist_clone->FindObject("stats");
 stats_landau->SetTextColor(kBlue);
 stats_landau->SetLineColor(kBlue);
 stats_landau->SetY1NDC(0.9);
 stats_landau->SetY2NDC(0.7);
 vect_canvas[i]->Update(); 

 TString status_landau = gMinuit->fCstatu;
 vect_status_landau.push_back(status_landau);
 vect_canvas[i]->Update();

 TString status_landau_leg = "Landau Status = ";
 status_landau_leg+=status_landau;

 TString status_cauchy_leg = "Cauchy Status = ";
 status_cauchy_leg+=status_cauchy;

double widthTest=0.0;
double width=0.0;
double widthP=0.0;
double range=100.0;
int counts=0;
std::cout <<"Max Landau/histo Value/2 = " << vect_hist_clone->GetMaximum()/2.0 << std::endl;
for(int i=0; i<vect_hist_clone->GetMaximum()*100000; i++)
{
 //break;
 if(i%100000==0)
 {
  //std::cout << "Looped Through: " << i*0.00001 << std::endl;
 }
 widthTest=landau_fit->Eval((i)*0.00001);
 if(widthTest<=((vect_hist_clone->GetMaximum()/2.0)+1.0/range) && widthTest>=((vect_hist_clone->GetMaximum()/2.0)-1.0/range))
 {
  widthP=i*0.00001;
  counts++;
 }
 if(counts>0) break;
}
width=landau_fit->Eval(widthP);
std::cout << "Width Value Checker  = " << width << std::endl;
double integral=landau_fit->Integral(0.,100.0/PerpendicularFactor);
std::cout << "Integral(0->100.0)=" << integral << std::endl;

//calculate sigma at 68%
double sigmaTest=0.0;
double integralTest=0.0;
double sigma68=0.0;
int count=0;
double sigma68value=integral*0.68;
std::cout << "68% of integral from 0->100.0 = " << sigma68value << std::endl;
double ranges=500.0;
for(int i=0; i<vect_hist_clone->GetMaximum()*10000000; i++)
{ 
 //break;
 sigmaTest=i*0.000001;
 //if(sigmaTest>1.0/PerpendicularFactor) break;
 //if(sigmaTest<widthP) continue;
 integralTest=landau_fit->Integral(0.0,sigmaTest);
 if(i%10000 == 0 )
 {
  std::cout << "Looped Through sigma = " << sigmaTest << std::endl;
 }
 if(integralTest<=(sigma68value+1.0/ranges) && integralTest>=(sigma68value-1.0/ranges))
 {
  count++;
  sigma68=i*0.000001;
 }
 if(count>0) break;
}
sigma68 = abs(sigma68);
if(sigma68 == 0.0)
{
 cout << "\033[1;31mCheck Landau\033[0m\n" << endl;
}
std::cout << "sigma68=" << sigma68*10000 << " um" << std::endl;
double sigma68integral=landau_fit->Integral(0.,sigma68);
std::cout << "Integral Checker (0->sigma (68%))=" << sigma68integral << std::endl;

TLine* landau_sigma_line = new TLine(sigma68,0.0,sigma68,landau_fit->Eval(sigma68));
landau_sigma_line->SetLineColor(kBlue);
landau_sigma_line->SetLineStyle(7);
landau_sigma_line->SetLineWidth(2);
landau_sigma_line->Draw("SAMES");
vect_canvas[i]->Update();

double cauchy_sigma68 = abs(func->GetParameter(2)*TMath::Tan(0.34*TMath::Pi())+func->GetParameter(1));
//if(cauchy_sigma68 > (1.0/PerpendicularFactor))
if(cauchy_sigma68 == 0.0)
{
 cout << "\033[1;31mCheck Cauchy\033[0m\n " << cauchy_sigma68 << endl;
}

//cout << "Cauchy Sigma68 = " << cauchy_sigma68 << endl;

TLine* cauchy_sigma_line = new TLine(cauchy_sigma68,0.0,cauchy_sigma68,func->Eval(cauchy_sigma68));
cauchy_sigma_line->SetLineColor(kRed);
cauchy_sigma_line->SetLineStyle(2);
cauchy_sigma_line->SetLineWidth(2);
//cauchy_sigma_line->Draw("SAMES");
vect_canvas[i]->Update();

TLine* cauchy_gamma_line = new TLine(func->GetParameter(2),0.0,func->GetParameter(2),func->Eval(func->GetParameter(2)));
cauchy_gamma_line->SetLineColor(kGreen+2);
cauchy_gamma_line->SetLineStyle(5);
cauchy_gamma_line->SetLineWidth(2);
//cauchy_gamma_line->Draw("SAMES");
vect_canvas[i]->Update();

 string cauchy_sigma68_start = "Cauchy #sigma68 = ";
 string landau_sigma68_start = "Landau #sigma68 = ";

 char cauchy_sigma68_char[50];
 char landau_sigma68_char[50];

 sprintf(cauchy_sigma68_char, "%.0lf", cauchy_sigma68*10000.0);
 sprintf(landau_sigma68_char, "%.0lf", sigma68*10000.0);
 
 string units = "#mum";

 cauchy_sigma68_start += cauchy_sigma68_char;
 cauchy_sigma68_start += units; 
 TString cauchy_sigma68_tstr = cauchy_sigma68_start;
 
 landau_sigma68_start += landau_sigma68_char; 
 landau_sigma68_start += units; 
 TString landau_sigma68_tstr = landau_sigma68_start;

 TLegend* leg_cauchy = new TLegend(0.55,0.3,0.98,0.4,"");
 leg_cauchy->SetTextFont(42);
 leg_cauchy->SetTextSize(0.04);
 leg_cauchy->SetFillColor(kWhite);
 leg_cauchy->SetTextColor(kRed);
 leg_cauchy->AddEntry((TObject*)0, status_cauchy_leg, "");
 leg_cauchy->AddEntry((TObject*)0, cauchy_sigma68_tstr, "");
 //leg_cauchy->Draw("SAMES");
 
 vect_canvas[i]->Update();

 TLegend* leg_landau = new TLegend(0.62,0.6,0.98,0.7,"");
 leg_landau->SetTextFont(42);
 leg_landau->SetTextSize(0.04);
 leg_landau->SetFillColor(kWhite);
 leg_landau->SetTextColor(kBlue);
 //leg_landau->AddEntry((TObject*)0, status_landau_leg, "");
 leg_landau->AddEntry((TObject*)0, landau_sigma68_tstr, "");
 leg_landau->Draw("SAMES");
 
 vect_canvas[i]->Update();

 vect_canvas[i]->SaveAs(vect_filename[i].c_str()); 

 delete landau_sigma_line;
 delete cauchy_sigma_line;
 delete cauchy_gamma_line;
}
 //Results(vect_status_landau, vect_status_cauchy);
}

