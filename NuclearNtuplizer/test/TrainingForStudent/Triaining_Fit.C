#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1.h>
#include "TAxis.h"
#include<TMatrixD.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include<TMath.h>
#include "Fit/BinData.h"

Double_t func(Double_t*, Double_t* );
Double_t func(Double_t *x ,Double_t *par)
{
 Double_t value= par[0]*exp(par[1]*x[0]);
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}

void Triaining_Fit(){

        gROOT->Clear();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(1);
        gStyle->SetPalette(1);
        gStyle->SetOptTitle(0);
//gROOT->Reset();

// open file:
TFile *f1 = new TFile("prova.root");

//read histogram from file f1, here example with the same name but you could give any new name:
TH1F* hPFDV_deltaR3d_Associated = (TH1F*)f1->Get("hPFDV_deltaR3d_Associated");

//hPFDV_deltaR3d_Associated ->Fit("epxo");

//                                        xmin xmax # parameters
TF1* fit_func = new TF1("fit_func", func, 0.,  5.,  2);

// set value for fit parametes par[0] and par[2]
fit_func->SetParameters(1000., -0.1);

// set name to par[1]
fit_func->SetParName(1,"exp degree");

//fit_func -> Draw("");
//std::cout << "exp(1) =" << exp(1) <<std::endl;

// fit with your funtion func:
hPFDV_deltaR3d_Associated ->Fit(fit_func, "E", "", 0., 3.);

//exmple to fit with default function: polinom of 5th degree:
//hPFDV_deltaR3d_Associated ->Fit("pol5");

}
