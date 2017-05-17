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

//TCanvas *c1 = new TCanvas("", "", 750, 500);

Double_t func(Double_t*, Double_t* );
Double_t func(Double_t *x ,Double_t *par)
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
 Double_t Gauss_a=par[1];
 Double_t Gauss_b=0;
 //Double_t GaussianFit = Gauss_a*exp(-((x[0]-Gauss_b)*(x[0]-Gauss_b))/(2*(par[0]*par[0])));
 Double_t GaussianFit = Gauss_a*exp(-((x[0]-Gauss_b)*(x[0]-Gauss_b))/(2*(par[0]*par[0])));
 //GaussianFit=GaussianFit*100;
 return GaussianFit;
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
TFile *f1 = new TFile("prova_Pixel.root");

//read histogram from file f1, here example with the same name but you could give any new name:
//TH1F* hMC_TrkV_associationPFDV_deltaR3d = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3d");
//TH1F* hMC_TrkV_associationPFDV_deltaR3dParallel = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3dParallel");
//TH1F* hMC_TrkV_associationPFDV_deltaR3dPerpendicular = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3dPerpendicular");
//TH1F* hMC_TrkV_associationPFDV_deltaR3d_Barrel = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3d_Barrel");
//TH1F* hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel");
//TH1F* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel");
//TH1F* hMC_TrkV_associationPFDV_deltaR3d_Forward = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3d_Forward");
//TH1F* hMC_TrkV_associationPFDV_deltaR3dParallel_Forward = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3dParallel_Forward");
TH1F* hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward = (TH1F*)f1->Get("hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward");

//hPFDV_deltaR3d_Associated ->Fit("epxo");

//                                        xmin xmax # parameters
TF1* fit_func = new TF1("fit_func", func, 0.,  0.5, 2);

// set value for fit parametes par[0] and par[2]
//std::cout << "check" << endl;
fit_func->SetParameters(1, 0.3);
fit_func->SetParameters(0, 100.0);
//fit_func->FixParameters(0, 100.0);
//fit_func->FixParameters(1, 0.0);
//fit_func->FixParameters(2, 0.3);

//add rms value
gStyle->SetOptStat(000002000);

//rename pars
fit_func->SetParName(1,"A");
fit_func->SetParName(0,"Sigma");

// set name to par[1]
//fit_func->SetParName(1,"exp degree");

//c1->cd();
fit_func -> Draw("");
//std::cout << "exp(1) =" << par[0] <<std::endl;

// fit with your funtion func:
//hMC_TrkV_associationPFDV_deltaR3d ->Fit(fit_func, "E", "", 0., 0.6);
//hMC_TrkV_associationPFDV_deltaR3dParallel ->Fit(fit_func, "E", "", 0., 0.6);
//hMC_TrkV_associationPFDV_deltaR3dPerpendicular ->Fit(fit_func, "E", "", 0., 0.02);
//hMC_TrkV_associationPFDV_deltaR3d_Barrel ->Fit(fit_func, "E", "", 0., 0.3);
//hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel ->Fit(fit_func, "E", "", 0., 0.2);
//hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel ->Fit(fit_func, "E", "", 0., 0.06);
//hMC_TrkV_associationPFDV_deltaR3d_Forward ->Fit(fit_func, "E", "", 0., 0.6);
//hMC_TrkV_associationPFDV_deltaR3dParallel_Forward ->Fit(fit_func, "E", "", 0., 0.6);
hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward ->Fit(fit_func, "E", "", 0., 0.04);

//exmple to fit with default function: polinom of 5th degree:
//hPFDV_deltaR3d_Associated ->Fit("pol5");

c1 -> SaveAs("c1.png");
}
