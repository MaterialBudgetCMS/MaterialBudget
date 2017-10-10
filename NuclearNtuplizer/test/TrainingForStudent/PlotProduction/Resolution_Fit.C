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

void Resolution_Fit(){

        gROOT->Clear();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(1);
        gStyle->SetPalette(1);
        gStyle->SetOptTitle(0);

// open file:
TFile *f1 = new TFile("ResolutionPlots.root");

//read histogram from file f1, here example with the same name but you could give any new name:
const char* HistogramName="hMC_deltaR3d";
TH1F* hMC_TrkV_associationPFDV = (TH1F*)f1->Get(HistogramName);

//add rms value
gStyle->SetOptStat(000002000);
TCanvas *c1=new TCanvas;
//rename pars

c1->cd();
// fit with landau function
hMC_TrkV_associationPFDV->Fit("landau", "EB", "", 0., 0.95);
bool Perpendicular=false;
//test if Histogram is deltaR perpendicular
std::string HistogramStringName(HistogramName);
for(int i=0; i<HistogramStringName.length(); i++)
{
 if(HistogramStringName.at(i)=='P' && HistogramStringName.at(i+1)=='e' && HistogramStringName.at(i+2)=='r' && HistogramStringName.at(i+3)=='p' && HistogramStringName.at(i+4)=='e' && HistogramStringName.at(i+5)=='n' && HistogramStringName.at(i+6)=='d' && HistogramStringName.at(i+7)=='i' && HistogramStringName.at(i+8)=='c' && HistogramStringName.at(i+9)=='u' && HistogramStringName.at(i+10)=='l' && HistogramStringName.at(i+11)=='a' && HistogramStringName.at(i+12)=='r')
 {
  Perpendicular=true;
  break;
 }
 else
 {
  Perpendicular=false;
 }
}
if(Perpendicular==true)
{
 std::cout << "Perpendicular: yes \n";
}
if(Perpendicular==false)
{
 std::cout << "Perpendicular: no \n";
}
//calculate Gamma
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
if(Perpendicular==true)
{
 double PerpendicularFactor=10.0;
}
if(Perpendicular==false)
{
 double PerpendicularFactor=1.0;
}
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
//draw lines for Gamma and sigma
TLine *line = new TLine(widthP,0.,widthP,landau(widthP));
line->SetLineColor(kBlue);
line->SetLineWidth(2);
line->Draw();
TLine *line2 = new TLine(widthP*2.,0., widthP*2.0, landau(widthP*2.0));
line2->SetLineColor(kBlue);
line2->SetLineWidth(2);
line2->Draw();
TLine *line3 = new TLine(widthP*3.,0., widthP*3.0, landau(widthP*3.0));
line3->SetLineColor(kBlue);
line3->SetLineWidth(2);
line3->Draw();
TLine *line4 = new TLine(sigma68,0.,sigma68,landau(sigma68));
line4->SetLineColor(kRed);
line4->SetLineWidth(2);
line4->Draw();

//Formatting stats box
//add FWHM to stats box
//must be manually updated
c1->Update();
TPaveStats *st = (TPaveStats*)hMC_TrkV_associationPFDV->GetListOfFunctions()->FindObject("stats"); 
hMC_TrkV_associationPFDV->SetBit(TH1::kNoStats);
st->AddText("Red=Sigma at 68%");
st->AddText("Blue= 1 #Gamma, 2 #Gamma, 3 #Gamma");
//Remove unwanted lines in stats box

TList *listOfLines = st->GetListOfLines();

TText *tconst1 = st->GetLineWith("MPV");
listOfLines->Remove(tconst1);
TText *tconst2 = st->GetLineWith("Constant");
listOfLines->Remove(tconst2);

TText *tconst3 = st->GetLineWith("Sigma");
listOfLines->Remove(tconst3);
//Update Canvas
c1->Update();

c1->SaveAs("c1.png");
}
