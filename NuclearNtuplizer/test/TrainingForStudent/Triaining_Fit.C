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

//TCanvas *c1 = new TCanvas("", "", 750, 500);


Double_t func1(Double_t*, Double_t* );
Double_t func1(Double_t *x ,Double_t *par)
{
 //Double_t value= par[0]*exp(par[1]*x[0]);
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 //std::cout << "x[0] = " << x[0] << std::endl;
 //par[0]=0.1;
 //par[2]=0.3;
 //x[0]=x[0]*0.00001;
 //Double_t Gauss_a=1/(par[0]*sqrt(2*3.14));
 //par[0]=0.135;
 //par[1]=100;
 Double_t Gauss_a=par[1]; //old fit
 Double_t Gauss_b=0; //old fit
 //Double_t GaussianFit = Gauss_a*exp(-((x[0]-Gauss_b)*(x[0]-Gauss_b))/(2*(par[0]*par[0])));
 Double_t GaussianFit = Gauss_a*exp(-((x[0]-Gauss_b)*(x[0]-Gauss_b))/(2*(par[0]*par[0]))); //old fit
 //GaussianFit=GaussianFit*100;
 return GaussianFit; //old fit
 //return value;
}

void Triaining_Fit(){

        gROOT->Clear();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(1);
        gStyle->SetPalette(1);
        gStyle->SetOptTitle(0);
//gROOT->Reset();

// open file:
//TFile *f1 = new TFile("prova.root");
//TFile *f1 = new TFile("prova2015.root");
TFile *f1 = new TFile("prova2017.root");

//read histogram from file f1, here example with the same name but you could give any new name:
const char* HistogramName="hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Without_Both_Landau";
TH1F* hMC_TrkV_associationPFDV = (TH1F*)f1->Get(HistogramName);

//hPFDV_deltaR3d_Associated ->Fit("epxo");

//                                        xmin xmax # parameters
TF1* fit_func = new TF1("fit_func", func1, 0.,  0.5, 2);
TF1* fit_func_landau = new TF1("fit_func_landau", "landau", 0., 0.5);
//TF1* fit_func = new TF1("fit_func", func2, 0.,  0.5, 3);

// set value for fit parametes par[0] and par[2]
//std::cout << "check" << endl;
fit_func->SetParameters(1, 0.3);
fit_func->SetParameters(0, 100.0);
//fit_func->FixParameters(0, 100.0);
//fit_func->FixParameters(1, 0.0);
//fit_func->FixParameters(2, 0.3);

//fit_func_landau->FixParameter(1,10000.0);
//fit_func_landau->FixParameter(1,0.001);
//fit_func_landau->SetParLimits(1,0.001,0.9);


//add rms value
gStyle->SetOptStat(000002000);
TCanvas *c1=new TCanvas;
//rename pars
fit_func->SetParName(1,"A");
fit_func->SetParName(0,"Sigma");

// set name to par[1]
//fit_func->SetParName(1,"exp degree");

c1->cd();
//fit_func -> Draw("");
//fit_func_landau->Draw("");
//rename pars
fit_func->SetParName(1,"A");
fit_func->SetParName(0,"Sigma");
//std::cout << "exp(1) =" << par[0] <<std::endl;
//Gaussian with Horizontal Parameter
// fit with your funtion func:
hMC_TrkV_associationPFDV->Fit("landau", "EB", "", 0., 1.0);
bool Perpendicular=false;
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
  //std::cout << "TEST=" << widthP << std::endl;
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
  //std::cout << "TEST=" << sigma68 << std::endl;
  //std::cout << "INTEGRAL=" << integralTest << std::endl;
 }
 if(count>0) break;
}
std::cout << "sigma68=" << sigma68*10000 << " um" << std::endl;
double sigma68integral=landau->Integral(0.,sigma68);
std::cout << "Integral Checker (0->sigma (68%))=" << sigma68integral << std::endl;

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

//exmple to fit with default function: polinom of 5th degree:
//hPFDV_deltaR3d_Associated ->Fit("pol5");
//
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
//c1 -> SaveAs(("Resolution_Plots/"+HistogramName+".png"));
}
