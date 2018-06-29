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

void Resolution_Fit_NEW(){

gROOT->Clear();
gStyle->SetOptStat(0);
gStyle->SetOptFit(1);
gStyle->SetPalette(1);
gStyle->SetOptTitle(0);

const char *fname = "ResolutionPlots.root";

// open file:
TFile *f1 = new TFile("ResolutionPlots.root","READ");

std::vector<TH1*> vect_hist = list_histos(fname);

std::vector<TCanvas*> vect_canvas;
std::vector<string> vect_filename;

for (int i = 0; i < vect_hist.size(); i++)
{
 string canvasname = vect_hist[i]->GetName();
 canvasname += "_canvas";
 TCanvas* dummy_canvas = new TCanvas((canvasname).c_str(),(canvasname).c_str(),750,500);
 vect_canvas.push_back(dummy_canvas);
 string filename = vect_hist[i]->GetName();
 filename += ".png";
 vect_filename.push_back(filename);
}

for (int i = 0; i < vect_hist.size(); i++)
{
 //if( i != 2 ) continue; //|| i != 11 || i != 18 || i != 19 || i != 20 || i != 23 || i != 26) continue;
 vect_canvas[i]->cd();
 cout << endl << "Fitting " << vect_hist[i]->GetName() << "   (" << i+1 << "/27)" << endl;
 const char* histname = vect_hist[i]->GetName();
 string histname_str = histname;
 string perp = "Perpendicular";
 double PerpendicularFactor;
 if(histname_str.find(perp) != std::string::npos)
 {
  PerpendicularFactor=10.0;
  //vect_hist[i]->Fit("landau","BER","",0.,0.095); 
 }
 else
 {
  PerpendicularFactor=1.0;
  //vect_hist[i]->Fit("landau","BER","",0.,0.95);
 }

 //Cauchy
 /*cout << "Max " << vect_hist[i]->GetMaximum() << " Mean " << vect_hist[i]->GetMean() << " StdDev " << vect_hist[i]->GetStdDev() << endl;
 TF1 *func = new TF1("func", Fit_Cauchy, 0.0, 0.95/PerpendicularFactor, 3);
 //func->SetParameter(0,vect_hist[i]->Integral());
 func->SetParameter(0,vect_hist[i]->GetMaximum());
 func->SetParameter(1,(vect_hist[i]->GetMean())*0.1);
 func->SetParameter(2,vect_hist[i]->GetRMS());
 func->SetParLimits(0,0.0,10000.0);
 func->SetParLimits(1,-2.0*abs(vect_hist[i]->GetMean()),2.0*abs(vect_hist[i]->GetMean()));
 func->SetParLimits(2,0.0,1.0);
 func->SetParName(0,"norm");
 func->SetParName(1,"mean");
 func->SetParName(2,"gamma");
*/

 //voigt
 TF1* func = new TF1("func", Fit_Voigt, 0.0, 0.99/PerpendicularFactor, 4);
 func->SetParameter(0,2.0*(vect_hist[i]->Integral()));
 func->SetParameter(1,0.0);
 func->SetParameter(2,0.002*vect_hist[i]->GetRMS());
 func->SetParameter(3,2.0*vect_hist[i]->GetRMS());
 /*
 func->SetParameter(0,vect_hist[i]->GetMaximum());
 func->SetParameter(1,vect_hist[i]->GetMean());
 func->SetParameter(2,vect_hist[i]->GetStdDev());
 func->SetParameter(3,vect_hist[i]->GetRMS());
 */
 //func->SetParLimits(0,0.000001,10000000.0);
 //func->SetParLimits(1,-10.0,1.0);
 //func->SetParLimits(2,0.00000001,100000.0);
 //func->SetParLimits(3,0.00000001,100000.0);
 func->SetParName(0,"norm");
 func->SetParName(1,"mean");
 func->SetParName(2,"sigma");
 func->SetParName(3,"lg");

 //cout << "RMS " << vect_hist[i]->GetRMS() << endl;
 
 vect_hist[i]->Fit(func,"EMR");
 func->SetNpx(10000000);
 vect_canvas[i]->SaveAs(vect_filename[i].c_str());
}

}





/*
cout << vect_hist[26]->GetName() << endl;

TH1F* hMC_TrkV_associationPFDV=vect_hist[26];

double widthTest=0.0;
double width=0.0;
double widthP=0.0;
double range=10.0;
int counts=0;
std::cout <<"Max Landau/histo Value/2 = " << hMC_TrkV_associationPFDV->GetMaximum()/2 << std::endl;
for(int i=0; i<hMC_TrkV_associationPFDV->GetMaximum()*100000; i++)
{
 //break;
 if(i%100000==0)
 {
  std::cout << "Looped Through: " << i*0.00001 << std::endl;
 }
 widthTest=landau((i)*0.00001);
 if(widthTest<=((hMC_TrkV_associationPFDV->GetMaximum()/2)+1.0/range) && widthTest>=((hMC_TrkV_associationPFDV->GetMaximum()/2)-1.0/range))
 {
  widthP=i*0.00001;
  counts++;
 }
 if(counts>0) break;
}
width=landau(widthP);
std::cout << "Width Value Checker  = " << width << std::endl;
std::cout << "Width Value Position (#Gamma) = " << widthP*10000 << " um" << std::endl;
//calculate integrals
double integral1=landau->Integral(0.,1.0/PerpendicularFactor);
std::cout << "Integral(0->1.0)=" << integral1 << std::endl;

double integral2=landau->Integral(0.,2.0/PerpendicularFactor);
std::cout << "Integral(0->2.0)=" << integral2 << std::endl;

double integral3=landau->Integral(0.,20.0/PerpendicularFactor);
std::cout << "Integral(0->20.0)=" << integral3 << std::endl;

double integral7=landau->Integral(0.,100.0/PerpendicularFactor);
std::cout << "Integral(0->100.0)=" << integral7 << std::endl;

double integral4=landau->Integral(0.,widthP);
std::cout << "Integral(0->1 width)=" << integral4 << " (" << (integral4/integral7*100) << "%)" << std::endl;

double integral5=landau->Integral(0.,widthP*2);
std::cout << "Integral(0->2 width)=" << integral5 << " (" << (integral5/integral7*100) << "%)" << std::endl;

double integral6=landau->Integral(0.,widthP*3);
std::cout << "Integral(0->3 width)=" << integral6 << " (" << (integral6/integral7*100) << "%)" << std::endl;

//calculate sigma at 68%
double sigmaTest=0.0;
double integralTest=0.0;
double sigma68=0.0;
int count=0;
double sigma68value=integral7*0.68;
std::cout << "68% of integral from 0->100.0 = " << sigma68value << std::endl;
double ranges=1000.0;
for(int i=0; i<hMC_TrkV_associationPFDV->GetMaximum()*10000; i++)
{ 
 //break;
 sigmaTest=i*0.00001;
 if(sigmaTest>1.0/PerpendicularFactor) break;
 //if(sigmaTest<widthP) continue;
 integralTest=landau->Integral(0.0,sigmaTest);
 if(i%10000 == 0 )
 {
  std::cout << "Looped Through sigma = " << sigmaTest << std::endl;
 }
 if(integralTest<=(sigma68value+1.0/ranges) && integralTest>=(sigma68value-1.0/ranges))
 {
  count++;
  sigma68=i*0.00001;
 }
 if(count>0) break;
}
std::cout << "sigma68=" << sigma68*10000 << " um" << std::endl;
double sigma68integral=landau->Integral(0.,sigma68);
std::cout << "Integral Checker (0->sigma (68%))=" << sigma68integral << std::endl;

}*/
