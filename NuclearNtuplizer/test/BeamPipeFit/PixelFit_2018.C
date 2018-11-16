/* ************************************************* */
/*                                                   */
/* Tracker Material with Nuclear Interactions        */
/*                                                   */
/* Current Developer: Anna Kropivnitskaya,           */
/*                                                   */
/* ************************************************* */

#include <memory>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <vector>

#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include "TF2.h"
#include "TH2.h"
#include <TMath.h>
#include <TVirtualFitter.h>
#include <TFitter.h>
#include <TAttLine.h> // for colors and transperent
#include "Fit/DataRange.h"
#include <TStyle.h>
#include <TEllipse.h>
#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TPaveStats.h"
//#include "TColor.h" 
#include "TLegend.h" 
#include <math.h> 
#include "TArc.h"
#include "TGraph.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include <TAttFill.h>
#include <TLatex.h>

#include "tdrstyle.C"
#include "CMS_lumi.C"

using namespace std;

TH2D* h;
TH2D* h_Extra;
Double_t Rmin, Rmax, RBGmin, RBGmax, RSmin, RSmax, RPlot;

// create function to fit the plus side of the pixel support
void funPixelSupportPlus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create function to fit the minus side of the pixel support
void funPixelSupportMinus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create function to fit the pixel support with an ellipse
void funPixelSupportEllipse( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create funciton to fit the pixel shield with an ellipse
void funPixelShield2Ellipses( Int_t &, Double_t *, Double_t &, Double_t *, Int_t);

// create funciton to fit the pixel shield with an ellipse
void funPixelShield2Arcs( Int_t &, Double_t *, Double_t &, Double_t *, Int_t);
// create funciton to fit the pixel shield with an ellipse
Double_t funPixelLayer1(Double_t *x, Double_t *par);
// create funciton to fit the pixel shield with an ellipse
void fun2Lines(Double_t *Line1, Double_t *Line2, Double_t *par);

// create function to fit the plus semicircle of the pixel shield
void funArcPlus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create function to fit the minus semicircle of the pixel shield
void funArcMinus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// good fit values
// 21.70; -0.08; -0.34
// 21.68; -0.07; -0.28
//create function to fit objects in 2D with circle (Arc)
void chiSquareFunc( Int_t&, Double_t*, Double_t&, Double_t*, Int_t );

//create Fit function for background
Double_t func_fitBg(Double_t*, Double_t* );
Double_t fun2(Double_t*, Double_t* );

//create Circle/Arc  or Ellipse function in phi,R plane:
Double_t func_ArcRhoPhi(Double_t*, Double_t* );
Double_t func_EllipseRhoPhi(Double_t*, Double_t*);


// Main Program to fit Inner Tracker: Beam Pipe, Pixel Shield, Pixel Support and Pixel Support Rails

void PixelFit_2018()
{
  //  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();


Double_t Pi = 2*acos(0.);
std::cout << "*****  Pi = " << Pi << std::endl; 

  //  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  //extraText  = "";  // default extra text is "Preliminary"
  //extraText  = "Preliminary";  // default extra text is "Preliminary"
  //extraText  = "Work in Progress";  // default extra text is "Preliminary"
  extraText  = "work in progress";  // default extra text is "Preliminary"
  //lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  //lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  // BELOW IS ONE FOR 2015
  //lumi_13TeV  = "2.5 fb^{-1}";  // default is "5.1 fb^{-1}"
  lumi_13TeV  = " ";  // For MC 923 2017?
  //lumi_sqrtS = "13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

  int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

  int iPos = 11;
  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  //iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

  //  example_plot( iPeriod, 11 );  // left-aligned
  //  example_plot( iPeriod, 33 );  // right-aligned

  //  writeExtraText = false;       // remove Preliminary
  
  //  example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)

  //  example_plot( iPeriod, 11 );  // default: left-aligned
  //  example_plot( iPeriod, 22 );  // centered
  //  example_plot( iPeriod, 33 );  // right-aligned  

  //Start Initialization:
  float ScaleSize = 1. - 2.*0.16;  
  
  TH2D* h_RhoPhi;
  TH2D* h_RhoPhi_Extra;
  TH2D* h_ZR;
  TH2D* h_XY;
  TCanvas* cPlots;
  TCanvas* cQuality;
  TH1D* hQuality;
  TH1D* hYderivative;
  TH2D* hYderivative2D;
  TH2D* hXderivative2D;
  TLatex latex_circle;
         latex_circle.SetTextAlign(12);
         latex_circle.SetTextColor(kBlack);
         latex_circle.SetTextFont(42);
         latex_circle.SetTextSize(0.04*ScaleSize);    


  // fit mesurements:
  Double_t x0_PixelShieldPlus = 0.0;
  Double_t y0_PixelShieldPlus = 0.0;
  Double_t r0_PixelShieldPlus = 3.0;
  
  
  Double_t x0_PixelSupportPlus = -0.233;
  Double_t y0_PixelSupportPlus = -0.331;
  Double_t r0_PixelSupportPlus = 21.85;

Double_t x0_BeamPipe = 0.171; // from previous fits using this program that were based on 2018
Double_t y0_BeamPipe = -0.175; // from previous fits using this program that were based on 2018
  
////Average over 3 adjacent sectors to smooth differences 
  Int_t AverageBG = 0; // 0 - Default, don't average BG; 1 - sytematics, average BG
  TString FitObject = "";
  TString PlotObject = "hPFDV_XY_Map_Pipe";
  TString PlotObjectBg = "hPFDV_RhoPhi_Map_Pipe";
  Double_t RangeEstimatorQuality, x_Sys = 0, r_Sys = 0, x0 = 0, y0 = 0, r0 = 1, r0_y =1, x0_Far = 0, y0_Far = 0;
  if (r0_y < 0.) cout << "Error: r0_y < 0" << endl;

  Double_t ErrPrecision = 0.0005;  
  //Double_t ErrPrecision = 0.00000005;  

  // Set flags for fit options:

  Int_t flag_ExcludeBadFitSector = 1; // = 1 exclude; = 0 not exclude;
  Int_t  flag_Sys = 1; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
  

  //*** to fit is uncomment line:

  //FitObject = "BeamPipe"; // working well
  FitObject = "PixelShield2Arcs"; // status failed
  //FitObject = "PixelSupportEllipse"; //work well
  //FitObject = "PixelSupportRails"; // work well

  //FitObject = "BeamPipeEllipse"; //work well
  //FitObject = "PixelShield"; // work well
  //FitObject = "PixelShieldPlus"; // work well
  //FitObject = "PixelShieldMinus"; // work well 
  //FitObject = "PixelShieldEllipse"; //work well
  //FitObject = "PixelShield2Ellipses"; // status failed
  //FitObject = "PixelSupport"; // work well
  //FitObject = "PixelSupportPlus"; // work well, don't use it
  //FitObject = "PixelSupportMinus"; // work well, don't use it
  //FitObject = "PixelSupportRailsPositive"; // work well
  //FitObject = "PixelSupportRailsNegative"; // work wel
  
  //*** set parameters for Beam Pipe fit
  if(FitObject == "BeamPipe"){
     Rmin = 1.8, Rmax = /*5.*/3.0, RBGmin = 2.35/*2.4*/, RBGmax = 2.6/*3.*/, RSmin = 2.0/*1.9*/, RSmax = 2.35/*2.4*/, RPlot = /*5.*/3.5;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.003; //size of systematics in cm
     r_Sys = 0.003; //size of systematics in cm
     //x0 = 0.; // from MC
     //y0 = 0.; // from MC
     x0 = 0.171; // from previous fits using this program that were based on 2018
     y0 = -0.175; // from previous fits using this program that were based on 2018
     r0 = 2.211; // from previous fits using this program that were based on 2015
     //Rmin = 1.8, Rmax = 3., RBGmin = 2.4, RBGmax = 3., RSmin = 2., RSmax = 2.4, RPlot = 3.5;
     //RangeEstimatorQuality = 0.1;  
     //x_Sys = 0.003; //size of systematics in cm
     //r_Sys = 0.003; //size of systematics in cm
     //x0 = 0.124; // from previous fits using this program that were based on 2015
     //y0 = 0.026; // from previous fits using this program that were based on 2015
     //r0 = 2.21; // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Beam Pipe Ellipse fit
  if(FitObject == "BeamPipeEllipse") {
     extraText  = "work in progress";
     Rmin = 1.8, Rmax = 3.0, RBGmin = 2.35/*2.4*/, RBGmax = 3., RSmin = 2.0, RSmax = 2.35/*2.4*/, RPlot = 3.5;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.002; //size of systematics in cm
     r_Sys = 0.002; //size of systematics in cm
     x0 = 0.113; // from previous fits using this program that were based on 2017
     y0 = -0.118; // from previous fits using this program that were based on 2017
     r0 = 2.211; // initial x radiu, from previous fits using this program that were based on 2015
     r0_y = 2.211; // in cm, initial y radius
  }
  
  //*** set parameters for Pixel Shield
  if(FitObject == "PixelShield"){
     Rmin = 3.0, Rmax = 5.0, RBGmin = 3.0, RBGmax = 3.5, RSmin = 3.5, RSmax = 3.9, RPlot = 5.0;
     RangeEstimatorQuality = 0.1;  
     x_Sys = 0.007; //size of systematics in cm
     r_Sys = 0.007; //size of systematics in cm
     // Values for fit with a circle
     x0 = -0.029; // from previous fits using this program that were based on 2015
     y0 = -0.079; // from previous fits using this program that were based on 2015
     r0 = 3.72;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Shield Plus
  if(FitObject == "PixelShieldPlus"){
     Rmin = 3.0, Rmax = 5.0, RBGmin = 3.0, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 5.0;
     RangeEstimatorQuality = 0.1; 
     x_Sys = 0.007; // size of systematics in cm
     r_Sys = 0.007; // size of systematics in cm
     x0 = -0.112;//-0.106; // in cm
     y0 = -0.093;//-0.096; // in cm
     r0 = 3.783;//3.783; // in cm
  }
  //*** with all phi sectors: 3.736, x0 = -0.02, y0 = -0.092
  
  //*** set parameters for Pixel Shield Minus
  //*** to superimpose the fits for the Pxiel Shield Plus and Minus sides run this
  if(FitObject == "PixelShieldMinus"){
     Rmin = 3.0, Rmax = 5.0, RBGmin = 3.0, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 5.0;
     RangeEstimatorQuality = 0.1; 
     x_Sys = 0.007; // size of systematics in cm
     r_Sys = 0.007; // size of systematics in cm
     x0 = 0.052; // in cm
     y0 = -0.095; // in cm
     r0 = 3.777; // in cm
  }
  
  //*** set parameters for Pixel Shield Ellipse
  if(FitObject == "PixelShieldEllipse"){
     Rmin = 3.0, Rmax = 5.0, RBGmin = 3.0, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 5.0;
     RangeEstimatorQuality = 0.1; 
     x_Sys = 0.007; // size of systematics in cm
     r_Sys = 0.007; // size of systematics in cm
     x0 = -0.029; // in cm
     y0 = -0.086; // in cm
     r0 = 3.71; // in cm, initial x radius
     r0_y = 3.75; // in cm, initial y radius
  }
  
  //*** set parameters for Pixel Shield Ellipse with 2 semi-ellipses with the same Rx and Ry for both sides
  if(FitObject == "PixelShield2Ellipses"){
     Rmin = 3.0, Rmax = 5.0, RBGmin = 3.0, RBGmax = 3.55, RSmin = 3.55, RSmax = 4., RPlot = 5.0;
     //Rmin = 3.0, Rmax = 5.0, RBGmin = 3.0, RBGmax = 3.55, RSmin = 3.55, RSmax = 4.1, RPlot = 5.0;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.007; // size of systematics in cm
     r_Sys = 0.007; // size of systematics in cm
     x0 = -0.099; // in cm
     y0 = -0.090; // in cm
     x0_Far = 0.048; // in cm
     y0_Far = -0.104; // in cm
     r0 = 3.780; // in cm, the initial x radius
     r0_y = 3.776; // in cm, initial y radius
     //x0 = -0.115; // in cm
     //y0 = -0.092; // in cm
     //x0_Far = 0.064; // in cm
     //y0_Far = -0.098; // in cm
     //r0 = 3.794; // in cm, the initial x radius
     //r0_y = 3.777; // in cm, initial y radius
  }

  //*** set parameters for Pixel Shield with 2 Arcs with the same radius
  if(FitObject == "PixelShield2Arcs"){
     //PlotObject = "hPFDV_XY_Pixel";
     //PlotObject = "hPFDV_XY_PixelSupport";
     //PlotObjectBg = "hPFDV_RhoPhi_PixelSupport";
     Rmin = 2.28, Rmax = 4.0, RBGmin = 2.5, RBGmax = 2.55, RSmin = 2.55, RSmax = 2.6, RPlot = 4.0;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.02; // size of systematics in cm
     r_Sys = 0.02; // size of systematics in cm
     //**** for |z| < 25 cm
     x0 = 0.10;//0.10; // in cm
     y0 = -0.11;//-0.08; // in cm
     x0_Far = 0.04;//0.10; // in cm
     y0_Far = -0.18;//-0.08; // in cm
     r0 = 3.0; // in cm, the initial x radius
     //***** for z: -25 to -20 cm
     //x0 = -0.032; // in cm
     //x0_Far = -0.096; // in cm
     //r0 = 3.705; // in cm, the initial x radius
     //***** for z: -25 to -20 cm
     //x0 = 0.018; // in cm
     //x0_Far = -0.016; // in cm
     //r0 = 3.724; // in cm, the initial x radius
     //***** for z: -20 to -10 cm
     //x0 = -0.102; // in cm
     //x0_Far = 0.075; // in cm
     //r0 = 3.788; // in cm, the initial x radius
     //***** for z: -10 to 0 cm
     //x0 = -0.170; // in cm
     //x0_Far = 0.112; // in cm
     //r0 = 3.825; // in cm, the initial x radius
     //***** for z: 0-10 cm
     //x0 = -0.128; // in cm
     //x0_Far = 0.063; // in cm
     //r0 = 3.790; // in cm, the initial x radius
     //***** for z: 10-20 cm
     //x0 = -0.063; // in cm
     //x0_Far = 0.003; // in cm
     //r0 = 3.748; // in cm, the initial x radius
  }
  
  //*** set parameters for Pixel Support
  if(FitObject == "PixelSupport"){
     PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     //Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
     Rmin = 18., Rmax = 23., RBGmin = 19.6, RBGmax = 21.1, RSmin = 21.1, RSmax = 22.3, RPlot = 23.; 
     RangeEstimatorQuality = 0.5;  
     x_Sys = 0.007; //size of systematics in cm
     r_Sys = 0.007; //size of systematics in cm
     x0 = -0.075;//-0.083;// from previous fits using this program that were based on 2015
     y0 = -0.313;//-0.324; // from previous fits using this program that were based on 2015
     r0 = 21.734;//21.73;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Plus
  if(FitObject == "PixelSupportPlus"){
     PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;  
     x_Sys = 0.007; //size of systematics in cm
     r_Sys = 0.05; //size of systematics in cm
     x0 = -0.232; // from previous fits using this program that were based on 2015
     y0 = -0.331; // from previous fits using this program that were based on 2015
     r0 = 21.85;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Minus
  if(FitObject == "PixelSupportMinus"){
     PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;  
     x_Sys = 0.007; //size of systematics in cm
     r_Sys = 0.05; //size of systematics in cm
     x0 = 0.023;// from previous fits using this program that were based on 2015
     y0 = -0.317; // from previous fits using this program that were based on 2015
     r0 = 21.81; // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Ellipse
  if(FitObject == "PixelSupportEllipse"){
     PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     //PlotObject = "hPFDV_XY_PixelSupport";
     //PlotObjectBg = "hPFDV_RhoPhi_PixelSupport";
     Rmin = 18., Rmax = 23., RBGmin = 19.6, RBGmax = 21.1, RSmin = 21.1, RSmax = 22.3, RPlot = 31.;
     RangeEstimatorQuality = 0.5;
     x_Sys = 0.007; //size of systematics in cm
     r_Sys = 0.007; //size of systematics in cm
     x0 = -0.075;//-0.082;// from previous fits using this program that were based on 2015
     y0 = -0.315;//-0.324; // from previous fits using this program that were based on 2015
     r0 = 21.703;//21.701;  // initial x radius, from previous fits using this program that were based on 2015
     r0_y = 21.803;//21.779; // initial y radius, from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Rails
  if(FitObject == "PixelSupportRails"){
     PlotObject = "hPFDV_XY_PixelSupport";
     //PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     //Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 24.5; 
     Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 31.; 
     RangeEstimatorQuality = 0.5; 
     x_Sys = 0.02; //size of systematics in cm
     r_Sys = 0.02; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Rails Positive
  if(FitObject == "PixelSupportRailsPositive"){
     PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 31.; 
     RangeEstimatorQuality = 0.5; 
     x_Sys = 0.02; //size of systematics in cm
     r_Sys = 0.02; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Rails Negative
  if(FitObject == "PixelSupportRailsNegative"){
     PlotObject = "hPFDV_XY_PixelSupport_AbsZ25";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport_AbsZ25";
     Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;
     x_Sys = 0.02; //size of systematics in cm
     r_Sys = 0.02; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
 

  TH2F *hEmpty = new TH2F("hEmpty","",40,-RPlot,RPlot,40,-RPlot,RPlot);
  hEmpty->GetXaxis()->SetTitle("x (cm)");
  hEmpty->GetYaxis()->SetTitle("y (cm)"); 
  hEmpty->SetStats(0);
  //End Initialization:

  //gROOT->SetBatch(1);
  //gROOT->ForceStyle();

  // 2018 data file
  //TFile* inputFile = TFile::Open("PlotProduced_2018.root");
  //TFile* inputFile = TFile::Open("PlotProduced_MC2018_Pi10GeV.root");
  TFile* inputFile = TFile::Open("PlotProduced_2018D_RawToReco.root");

  /// Reset some Style
  ///gStyle.SetPalette(1)
  /// <=0 for default
  /// 1 for the pretty
  /// > 50 for the deep sea
  /// > 0 max number of selected colors in the default palette
  /// gStyle.SetOptFit(0000)
  /// probability, chisquare, errors, parameter (if xx1y, y must be = 1)
  /// only combination of 0 and 1
  /// dummy, kurtosis, skewness, integral, overflows, underflows, rms, mean, entries, name
  /// only combination of 0, 1 and 2: if 2 means error too
  /// dummy should better be 1
  gStyle->SetPalette(kBird);
  //gStyle->SetPalette(kVisibleSpectrum);
  //gStyle->SetPalette(1);
  gStyle->SetOptStat(1000111110);
  gStyle->SetCanvasDefW(2000);
  gStyle->SetCanvasDefH(2000);
  //gStyle->SetPadRightMargin(0.2);
  //gStyle->SetPadTopMargin(0.2);
  //gStyle->SetStatX(0.9);
  //gStyle->SetStatY(0.90);
  //gStyle->SetStatW(0.24);
  //gStyle->SetTitleW(0.585);
  //gStyle->SetTitleX(0.434);

  gStyle->SetOptFit(0011);
  //gStyle->SetCanvasBorderMode(0); //no canvas border

  Double_t resR[10];
  Double_t errR[10];
  Double_t resx0[10];
  Double_t errx0[10];
  Double_t resy0[10];
  Double_t erry0[10];
  Double_t resZ[10];
  Double_t errZ[10] = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5};

  Double_t x1L, x2L, y1L, y2L;


  //  for ( int k = -7; k < 5; k++ )
  for ( int k = -6; k < -5; k++ ) // deafault: |z| < 25 cm 
  //for ( int k = 4; k < 5; k++ ) //for for list of histograms to fit
  //for ( int k = 0; k < 1; k++ ) //for for list of histograms to fit
  {
    std::string  plot = std::string(PlotObject);
    std::string  plotBg = std::string(PlotObjectBg);
    std::string  plot2 = std::string(PlotObject);
    std::string  plotBg2 = std::string(PlotObjectBg);
    //if (FitObject == "PixelSupport")TString plot = PlotObject;
    //if (FitObject == "PixelSupport")TString plotBg = PlotObjectBg;
    //TString plot = "hPFDV_XY_Map_Pipe";
    //TString plotBg = "hPFDV_RhoPhi_Map_Pipe";
    std::ostringstream plotName;
    std::ostringstream plotNameBg;
    std::ostringstream plotName2;
    std::ostringstream plotNameBg2;

    plotName.str("");
    plotName << plot.c_str();
    plotNameBg.str("");
    plotNameBg << plotBg.c_str();
    plotName2.str("");
    plotName2 << plot.c_str();
    plotNameBg2.str("");
    plotNameBg2 << plotBg.c_str();

    /// k = -7 is the inclusive one
    /// k = -6 is only BPiz (|z| < 25 cm)
    if ( FitObject == "PixelShield" || FitObject == "BeamPipe" || FitObject == "PixelShieldPlus" || FitObject == "PixelShieldMinus" ||
         FitObject == "BeamPipeEllipse" || FitObject == "PixelShieldEllipse" ||
         FitObject == "PixelShield2Ellipses"|| FitObject == "PixelShield2Arcs" || FitObject == "PixelShieldEllipseMinus"  ) {
       if ( k == -6 )
       {
         plotName << "_AbsZ25";
         plotNameBg << "_AbsZ25";
       }
       else if ( k != -7 )
      {
        plotName << "_" << k*5 << "_" << (k+1)*5;
        plotNameBg << "_" << k*5 << "_" << (k+1)*5;
        plotName2 << "_" << (k+1)*5 << "_" << (k+2)*5;
        plotNameBg2 << "_" << (k+1)*5 << "_" << (k+2)*5;
      }
    }

    plot = TString( plotName.str().c_str() );
    plotBg = TString( plotNameBg.str().c_str() );
    plot2 = TString( plotName2.str().c_str() );
    plotBg2 = TString( plotNameBg2.str().c_str() );
    //printf(plot.c_str());
    //printf("\n");

    cout << "Function used for X:Y   = " << plot << endl;
    cout << "Function used for R:PHI = " << plot << endl;

    h_RhoPhi = new TH2D();
    h_RhoPhi = (TH2D*)inputFile->Get( plotBg.c_str() );
    h_RhoPhi->Sumw2();
    h_RhoPhi_Extra = new TH2D();
    if(k > -5 && k < 4){
       h_RhoPhi_Extra = (TH2D*)inputFile->Get( plotBg2.c_str() );
       h_RhoPhi_Extra->Sumw2();
       h_RhoPhi->Add(h_RhoPhi_Extra);
    }
    if(FitObject == "PixelSupport")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelSupportEllipse")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShield") h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShield2Ellipses") h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShield2Arcs") h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldEllipse")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldPlus")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldMinus")h_RhoPhi->Rebin2D(2,2);
    h_RhoPhi->SetStats(0);
    h_RhoPhi->GetXaxis()->SetTitle("#phi (rad)");
    h_RhoPhi->GetYaxis()->SetTitle("r (cm)");
    //h_RhoPhi->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h_RhoPhi->GetZaxis()->SetTitle(Form("Events/(%1.3f rad #times%1.2f mm)", h_RhoPhi->GetXaxis()->GetBinWidth(1),  h_RhoPhi->GetYaxis()->GetBinWidth(1)*10));
    h_RhoPhi->GetZaxis()->SetTitleOffset(1.5);
    // don't plot "0" at z axis
    Double_t MaxZhRhoPhi = h_RhoPhi->GetMaximum();
    cout << "******** Maximum Z value for h_RhoPhi = " << MaxZhRhoPhi << endl;
    /// doesn't work for PixelShield2Arcs and PixelSupportEllipse (calculate in whole range), so don't apply to it:
    if(FitObject == "PixelSupportEllipse")h_RhoPhi->GetZaxis()->SetRangeUser(0.01, 48); //only for paper version, if scale will change, all change
    if(FitObject == "BeamPipe"||FitObject == "PixelSupportRails")h_RhoPhi->GetZaxis()->SetRangeUser(0.01, MaxZhRhoPhi);

    h_ZR = new TH2D();
    h_ZR = (TH2D*)inputFile->Get("hPFDV_ZR_Map" );
    h_ZR->Sumw2();
    //h_ZR->Rebin2D(1,1);
    h_ZR->SetStats(0);
    h_ZR->GetXaxis()->SetTitle("z (cm)");
    h_ZR->GetYaxis()->SetTitle("r (cm)");
    h_ZR->GetYaxis()->SetTitleOffset(1.25);
    h_ZR->GetXaxis()->SetTitleOffset(1.2);
    h_ZR->GetYaxis()->SetLabelOffset(0.012);
    h_ZR->GetXaxis()->SetLabelOffset(0.012);

    h_XY = new TH2D();
    h_XY = (TH2D*)inputFile->Get("hPFDV_XY_PixelSupport_AbsZ25" );
    h_XY->Sumw2();
    //h_XY->Rebin2D(1,1);
    h_XY->SetStats(0);
    h_XY->GetXaxis()->SetTitle("x (cm)");
    h_XY->GetYaxis()->SetTitle("y (cm)");
    h_XY->GetZaxis()->SetTitle(Form("Events/(%1.1f#times%1.1f mm^{2})", h_XY->GetXaxis()->GetBinWidth(1)*10,  h_XY->GetYaxis()->GetBinWidth(1)*10));
    h_XY->GetZaxis()->SetTitleOffset(1.4);
    h_XY->GetXaxis()->SetTitleOffset(1.2);
    h_XY->GetYaxis()->SetTitleOffset(1.25);
    h_XY->GetYaxis()->SetLabelOffset(0.012);
    h_XY->GetXaxis()->SetLabelOffset(0.012);

    cPlots = new TCanvas(("c_"+plot).c_str(),"");

    cPlots->cd();


    h = new TH2D();
    h = (TH2D*)inputFile->Get( plot.c_str() );
    h->Sumw2();
    h_Extra = new TH2D();
    if(k > -5 && k < 4){
       h_Extra = (TH2D*)inputFile->Get( plot2.c_str() );
       h_Extra->Sumw2();
       h->Add(h_Extra);
    }
    if(FitObject == "PixelSupport" || FitObject == "PixelSupportPlus" || FitObject == "PixelSupportMinus")h->Rebin2D(4,4);
    //if(FitObject == "PixelSupportEllipse")h->Rebin2D(3,3);
    if(FitObject == "PixelSupportEllipse")h->Rebin2D(4,4);
    if(FitObject == "PixelShield") h->Rebin2D(5,5);
    if(FitObject == "PixelShield2Ellipses") h->Rebin2D(5,5);
    //if(FitObject == "PixelShield2Arcs" && k == -6) h->Rebin2D(5,5);
    //if(FitObject == "PixelShield2Arcs"&& k != -6 ) h->Rebin2D(5,5);
    if(FitObject == "PixelShieldEllipse")h->Rebin2D(5,5);
    if(FitObject == "PixelShieldPlus") h->Rebin2D(5,5);
    if(FitObject == "PixelShieldMinus")h->Rebin2D(5,5);
    if(FitObject == "BeamPipe")    h->Rebin2D(5,5);
    if(FitObject == "BeamPipeEllipse")h->Rebin2D(5,5);
    if(FitObject == "PixelSupportRails")h->Rebin2D(2,2);
    if(FitObject == "PixelSupportRailsPositive")h->Rebin2D(2,2);
    if(FitObject == "PixelSupportRailsNegative")h->Rebin2D(2,2);
    h->SetStats(0);
    h->GetXaxis()->SetTitle("x (cm)");
    h->GetYaxis()->SetTitle("y (cm)");
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    //h->Draw("col");
    //hEmpty->GetZaxis()->SetTitle(Form("Events/(%1.1f#times%1.1f mm^{2})    ", h->GetXaxis()->GetBinWidth(1)*10,  h->GetYaxis()->GetBinWidth(1)*10));
    //hEmpty->GetZaxis()->SetTitleOffset(1.4);


   // finish h_Draw
    //create empty 2d histo for backroung estimation in signal region
    TH2D* h_Draw = new TH2D( "h_Draw", h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h_Draw->GetXaxis()->SetTitle("x (cm)");
    h_Draw->GetYaxis()->SetTitle("y (cm)");

    Int_t numBinsX = h->GetNbinsX();
    Int_t numBinsY = h->GetNbinsY();

    cout << "****** numBinsX = " << numBinsX << endl;

    for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
    {
      for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
        //Double_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );
        Double_t binNum = h->GetBinContent( ix, iy );


        Double_t Radius = TMath::Sqrt( x*x + y*y );
        Double_t Radius_corr = TMath::Sqrt( (x-x0_BeamPipe)*(x-x0_BeamPipe) + (y-y0_BeamPipe)*(y-y0_BeamPipe) );

        if ( Radius_corr < Rmin || Radius > Rmax ) continue;

            h_Draw->Fill( x, y, binNum );
      }
    }
   // finish h_Draw
    h_Draw->SetStats(0);
    h_Draw->GetXaxis()->SetTitle("x (cm)");
    h_Draw->GetYaxis()->SetTitle("y (cm)");
    h_Draw->GetZaxis()->SetTitle(Form("Events/(%1.1f#times%1.1f mm^{2})    ", h_Draw->GetXaxis()->GetBinWidth(1)*10,  h_Draw->GetYaxis()->GetBinWidth(1)*10));
    h_Draw->GetZaxis()->SetTitleOffset(1.4);
    Double_t MaxZ = h_Draw->GetMaximum();     
    cout << "******** Maximum Z value = " << MaxZ << endl;
    h_Draw->GetZaxis()->SetRangeUser(0.01, MaxZ);
    h_Draw->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h_Draw->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    //if ( FitObject == "PixelSupportEllipse" || FitObject == "PixelShield2Arcs" ){
    Double_t r_l1 = 3.2;
    Double_t phi_l1 = Pi/12.;
    Double_t x0_L1 = 0.0;// Pixel Layer 1
    Double_t y0_L1 = 0.0;// Pixel Layer 1
    TF1* plot_L1 =   new TF1("plot_L1", funPixelLayer1, -0.2*r_l1,  1.2*r_l1,  4);
    TF1* plot_L1_3 = new TF1("plot_L1_3", funPixelLayer1, -0.2*r_l1,  1.2*r_l1,  4);
    TF1* plot_L1_1 = new TF1("plot_L1_1", funPixelLayer1, -0.2*r_l1,  1.2*r_l1,  4);
    plot_L1->SetParameter(0, r_l1);
    plot_L1->SetParameter(1, phi_l1);
    plot_L1->SetParameter(2, x0_L1);
    plot_L1->SetParameter(3, y0_L1);
    plot_L1->SetLineWidth(3);
    plot_L1->SetLineColor(kRed);
    plot_L1_3->SetParameter(0, r_l1);
    plot_L1_3->SetParameter(1, phi_l1+Pi/3.);
    plot_L1_3->SetParameter(2, x0_L1);
    plot_L1_3->SetParameter(3, y0_L1);
    plot_L1_3->SetLineWidth(3);
    plot_L1_3->SetLineColor(kRed);
    plot_L1_1->SetParameter(0, r_l1);
    plot_L1_1->SetParameter(1, phi_l1-Pi/3.);
    plot_L1_1->SetParameter(2, x0_L1);
    plot_L1_1->SetParameter(3, y0_L1);
    plot_L1_1->SetLineWidth(3);
    plot_L1_1->SetLineColor(kRed);
    Double_t r_l1c = 2.8;
    TF1* plot_L1c =   new TF1("plot_L1c", funPixelLayer1, -0.2*r_l1,  1.2*r_l1,  4);
    TF1* plot_L1c_3 =   new TF1("plot_L1c_3", funPixelLayer1, -0.2*r_l1,  1.2*r_l1,  4);
    TF1* plot_L1c_1 =   new TF1("plot_L1c_1", funPixelLayer1, -0.2*r_l1,  1.2*r_l1,  4);
    plot_L1c->SetParameter(0, r_l1c);
    plot_L1c->SetParameter(1, phi_l1-Pi/6.);
    plot_L1c->SetParameter(2, x0_L1);
    plot_L1c->SetParameter(3, y0_L1);
    plot_L1c->SetLineWidth(3);
    plot_L1c->SetLineColor(kRed);
    plot_L1c_3->SetParameter(0, r_l1c);
    plot_L1c_3->SetParameter(1, phi_l1-Pi/6.+Pi/3.);
    plot_L1c_3->SetParameter(2, x0_L1);
    plot_L1c_3->SetParameter(3, y0_L1);
    plot_L1c_3->SetLineWidth(3);
    plot_L1c_3->SetLineColor(kRed);
    plot_L1c_1->SetParameter(0, r_l1c);
    plot_L1c_1->SetParameter(1, phi_l1-Pi/6.-Pi/3.);
    plot_L1c_1->SetParameter(2, x0_L1);
    plot_L1c_1->SetParameter(3, y0_L1);
    plot_L1c_1->SetLineWidth(3);
    plot_L1c_1->SetLineColor(kRed);
       hEmpty -> Draw();
       //h_Draw->Draw("COLZsame");
       h_Draw->Draw("COLZ");
    //plot_L1->Draw("SAME");
    //plot_L1_3->Draw("SAME");
    //plot_L1_1->Draw("SAME");
    //plot_L1c->Draw("SAME");
    //plot_L1c_3->Draw("SAME");
    //plot_L1c_1->Draw("SAME");

    TGraph* gr_arc;
    Double_t x_arc0[1], y_arc0[1];
    x_arc0[0] = 0.;
    y_arc0[0] = 0.;
    gr_arc = new TGraph(1,x_arc0,y_arc0);
    // put a cross at (0,0)
    gr_arc->SetMarkerStyle(33);
    gr_arc->SetMarkerSize(2.5);
    //gr_arc->SetMarkerColor(kBlue);
    gr_arc->SetMarkerColor(kBlack);

    TGraph* gr_BS;
    Double_t x_BS[1], y_BS[1];
    x_BS[0] = 0.097; // in cm for 2018
    //x_BS[0] = 0.077; // in cm for 2015
    //x_BS[0] = 0.081; // in cm for 2017
    y_BS[0] = -0.061; // in cm for 2018
    //y_BS[0] = 0.092; // in cm for 2015
    //y_BS[0] = -0.035; // in cm for 2017
    gr_BS = new TGraph(1,x_BS,y_BS);
    gr_BS->SetMarkerStyle(20);
    gr_BS->SetMarkerSize(1.5);
    if (FitObject == "PixelSupportEllipse")
       {
       gr_BS->SetMarkerSize(1);
       }
    //gr_BS->SetMarkerColor(kGreen+1);
    gr_BS->SetMarkerColor(kBlue);



      TLegend* legBS = new TLegend(0.67, 0.74, 0.77, 0.81, "");
      legBS->SetTextFont(42);
      legBS->SetTextSize(0.04*ScaleSize);
      legBS->SetFillColor(kWhite);
      legBS->SetTextColor(kBlack);
      legBS->AddEntry(gr_arc,"(0,0)","P");
      legBS->AddEntry(gr_BS,"Beam spot","P");






    CMS_lumi( cPlots, iPeriod, 0 );
    if (FitObject == "BeamPipe" )latex_circle.DrawLatex(-3., 3., "Data 2018");
    if (FitObject == "PixelShield2Arcs" )latex_circle.DrawLatex(2.5, 3.5, "Data 2018");
    if (FitObject == "PixelSupportEllipse" )latex_circle.DrawLatex(15., 22., "Data 2018");
    if (FitObject == "BeamPipe"){
       gr_arc->Draw("P");
       gr_BS->Draw("P");
       legBS -> Draw("same");
    }
    //cPlots->SetLogz();
    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw.png"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw.pdf"));
    
    cPlots -> SetLogz();
    h_ZR->Draw("COLZ");
    CMS_lumi( cPlots, iPeriod, 0 ); 
    latex_circle.DrawLatex(-33., 66., "Data 2018");
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_ZR_COLZ.png"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_ZR_COLZ.pdf"));
    cPlots -> SetLogz(1);

    cPlots -> SetLogz();
    h_XY->Draw("COLZ");
    CMS_lumi( cPlots, iPeriod, 0 ); 
    latex_circle.DrawLatex(15., 22., "Data 2018");
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_XY_COLZ.png"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_XY_COLZ.pdf"));
    cPlots -> SetLogz(1);


    h_Draw->Draw("LEGO");
    h_Draw->GetXaxis()->SetTitleOffset(1.5);
    h_Draw->GetYaxis()->SetTitleOffset(1.5);
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw_LEGO.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_LEGO.png"));


   //create quality Histogram
   hQuality = new TH1D( "hQuality", "BG Quality", 100, 0., 5. );
   hQuality->Sumw2();


    /// Step 0: apply flux factor




    for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
      {
        for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          // correct flux on (0,0) (bad)
          //Double_t xc = x;
          //Double_t yc = y;
          //correct flux on beam stop (good)
          Double_t xc = x-x_BS[0];
          Double_t yc = y-y_BS[0];

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          //          if ( rc < Inf || rc > Sup ) continue;

          Double_t binNum = h->GetBinContent( ix, iy );
          Double_t binNum_Draw = h_Draw->GetBinContent( ix, iy );

          Double_t r0ref = r0;
          if (FitObject == "PixelShieldMinus" && x >= 0) r0ref = r0_PixelShieldPlus;
          if (FitObject == "PixelSupportMinus" && x >= 0) r0ref = r0_PixelSupportPlus;
          Double_t densityNum = binNum * rc*rc / (r0ref*r0ref);
          Double_t densityNum_Draw = binNum_Draw * rc*rc / (r0ref*r0ref);

          // make flux correction ofr h_Draw and h 
          h_Draw->SetBinContent(ix, iy, densityNum_Draw);
          h->SetBinContent(ix, iy, densityNum);

        }
      }
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    //h->Draw("LEGO");
    h_Draw->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h_Draw->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    //hEmpty -> Draw("");
    //h_Draw->Draw("COLZsame");
    h_Draw->Draw("LEGO");
    //cPlots->SaveAs(("Plots/"+FitObject+"_FluxCorrection_LEGO.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_FluxCorrection_LEGO.png"));
    //cPlots->SaveAs(("Plots/"+FitObject+"_FluxCorrection_COLZ.png"));

    /// Creat histograms for each facet for Pixel Layer 1
    //cPlots -> SetLogz(0);
    cPlots -> SetLogz(1);
    TH2D* hfacet[12];
    TH2D* hfacet_Phi[12];
    TH2D* hfacet_der[12];
    TH2D* hfacet_derPhi[12];
    for(int i = 0; i < 12; i++){
       //hfacet[i] -> Sumw2();
       //hfacet_der[i] -> Sumw2();
       std::ostringstream fn;
       fn.str("");
       fn << "Plots/"<<FitObject<<"_facet_" << i;
       hfacet[i] =  new TH2D( fn.str().c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );  
       hfacet[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet[i]->GetZaxis()->SetTitle(Form("Events/(%1.1f#times%1.1f mm^{2})", hfacet[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet[i]->SetStats(0);
       std::ostringstream fn_der;
       fn_der.str("");
       fn_der << "Plots/"<<FitObject<<"_facet_der_" << i;
       hfacet_der[i] =  new TH2D( fn_der.str().c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );  
       hfacet_der[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet_der[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet_der[i]->GetZaxis()->SetTitle(Form("d^{2}Events/(%1.1f#times%1.1f mm^{2})", hfacet_der[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_der[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet_der[i]->SetStats(0);

       Double_t phi_facet = Pi/12. + Pi/6.*(i-2)-Pi/6.;
       //Int_t NbinX_phi = Int_t(h->GetNbinsX()/1.); // valid if x bin width = y bin width
       //Int_t NbinY_phi = Int_t(h->GetNbinsY()/1.); // valid if x bin width = y bin width
       Int_t NbinX_phi = Int_t(h->GetNbinsX()/4.); // valid if x bin width = y bin width
       Int_t NbinY_phi = Int_t(h->GetNbinsY()/4.); // valid if x bin width = y bin width
       //cout << "NbinX_phi = " << NbinX_phi << " NbinY_phi = " << NbinY_phi << endl;
       //" h->GetXaxis()->GetBinLowEdge(1) = " << h->GetXaxis()->GetBinLowEdge(1) << " h->GetXaxis()->GetBinUpEdge(h->GetNbinsX() = " << h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()) << " h->GetYaxis()->GetBinLowEdge(1) = " << h->GetYaxis()->GetBinLowEdge(1) << " h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) = " << h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) << endl;
       std::ostringstream fn_Phi;
       fn_Phi.str("");
       fn_Phi << "Plots/"<<FitObject<<"_facet_Phi_" << i;
       hfacet_Phi[i] =  new TH2D( fn_Phi.str().c_str(), h->GetTitle(), NbinX_phi, h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      NbinY_phi, h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );  
       hfacet_Phi[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet_Phi[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet_Phi[i]->GetZaxis()->SetTitle(Form("Rotate in #phi facet: Events/(%1.1f#times%1.1f mm^{2})", hfacet_Phi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_Phi[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet_Phi[i]->SetStats(0);

       std::ostringstream fn_derPhi;
       fn_derPhi.str("");
       fn_derPhi << "Plots/"<<FitObject<<"_facet_derPhi_" << i;
       hfacet_derPhi[i] =  new TH2D( fn_derPhi.str().c_str(), hfacet_Phi[i]->GetTitle(), hfacet_Phi[i]->GetNbinsX(), hfacet_Phi[i]->GetXaxis()->GetBinLowEdge(1), 
                                                              hfacet_Phi[i]->GetXaxis()->GetBinUpEdge(hfacet_Phi[i]->GetNbinsX()),
                                                              hfacet_Phi[i]->GetNbinsY(), hfacet_Phi[i]->GetYaxis()->GetBinLowEdge(1), hfacet_Phi[i]->GetYaxis()->GetBinUpEdge(hfacet_Phi[i]->GetNbinsY()) );
       hfacet_derPhi[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet_derPhi[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet_derPhi[i]->GetZaxis()->SetTitle(Form("Rotate in #phi facet: d^{2}Events/(%1.1f#times%1.1f mm^{2})", hfacet_derPhi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_derPhi[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet_derPhi[i]->SetStats(0);
    }
    //Int_t numBinsX = h0->GetNbinsX();
    //Int_t numBinsY = h0->GetNbinsY();
    for(int i = 0; i < 12; i++){
       for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
       {
         for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
         {
           Double_t binNum = h->GetBinContent( ix, iy );
           //if(binNum < 1.) continue;
           Double_t x = hfacet[i]->GetXaxis()->GetBinCenter( ix );
           Double_t y = hfacet[i]->GetYaxis()->GetBinCenter( iy );

           // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
           // positions of the two halves so that the background subtraction is cleaner.
           Double_t x0ref = x0;
           Double_t y0ref = y0;
          if (i > 5) {x0ref = x0_Far; y0ref = y0_Far;} // for far side

           Double_t xc = x - x0ref;
           Double_t yc = y - y0ref;

           Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

           if ( rc < Rmin || rc > Rmax ) continue;

           // select facet "i"
           //Double_t phi_facetFar = Pi/12. + Pi/3.*(i-1);
           //Double_t phi_facetNear = Pi/12. + Pi/3.*(i-1)-Pi/6.;
           Double_t phi_facet = Pi/12. + Pi/6.*(i-2)-Pi/6.;
           //Double_t thikness_facet = 0.35/fabs(sin(phi_facet)); // in cm
           Double_t thikness_facet = 0.35; // in cm in phi-R facet plane
           Double_t R_facetNear = 2.8;
           Double_t R_facetFar = 3.1;
           if (i == 5 || i == 11) R_facetFar = R_facetFar + 0.2;
           Double_t x_facet[1];
           x_facet[0] = xc;
 
           //select Near facet (each even) and Far facet (odd):
           Double_t R_facet = R_facetFar;
           if (i == int(i/2)*2){
              R_facet = R_facetNear;
           }
           //cout << "Test i = " << i << " R_facet = " << R_facet << endl;

           //Rotate in phi R system of facet
           Double_t xf_0 = R_facet*cos(phi_facet);
           Double_t yf_0 = R_facet*sin(phi_facet);
           Double_t xf_prime = xc - xf_0;
           Double_t yf_prime = yc - yf_0;
           // in phi, R system:
           Double_t xf = xf_prime*cos(phi_facet) + yf_prime*sin(phi_facet);
           Double_t yf = -xf_prime*sin(phi_facet) + yf_prime*cos(phi_facet);

           //Double_t par_facet[4];
           //par_facet[0] = R_facet;
           //par_facet[1] = phi_facet;
           //par_facet[2] = x0ref;
           //par_facet[3] = y0ref;
           //Double_t y_facet = funPixelLayer1(x_facet, par_facet);

           //if (fabs(yc - y_facet) < thikness_facet){// seelect region near facet 2*i
           if (fabs(xf) < thikness_facet && fabs(yf) < 2.){// seelect region near facet 2*i
              hfacet_Phi[i]->Fill( xf, yf, binNum );  
              hfacet[i]->Fill( x, y, binNum );
              // calculate y Derivative in 2D, we use 2D histo without BG subtraction
              // formula is correct if all bins has the same width. If it is not true then you have to introduce bin width in this formula!
              if (ix>1 && Int_t(ix)<numBinsX && iy>1 && Int_t(iy)<numBinsY){
                 Double_t u0 = h->GetBinContent( ix-1, iy-1 ) + 2*h->GetBinContent( ix, iy-1 ) + h->GetBinContent( ix+1, iy-1 );
                 Double_t u2 = h->GetBinContent( ix-1, iy+1 ) + 2*h->GetBinContent( ix, iy+1 ) + h->GetBinContent( ix+1, iy+1 );
                 Double_t fyDer2D = u2-u0;// calculate derivative at iy (y1) point
                 // revert in negative y plain:
                 //if (y < 0) fyDer2D = -fyDer2D;

                 Double_t u0x = h->GetBinContent( ix-1, iy-1 ) + 2*h->GetBinContent( ix-1, iy ) + h->GetBinContent( ix-1, iy+1 );
                 Double_t u2x = h->GetBinContent( ix+1, iy-1 ) + 2*h->GetBinContent( ix+1, iy ) + h->GetBinContent( ix+1, iy+1 );
                 Double_t fxDer2D = u2x-u0x;// calculate derivative at iy (y1) point
                 // revert in negative y plain:
                 //if (x < 0) fxDer2D = -fxDer2D;
                 //Double_t fxyDer2D = fabs(fyDer2D*fxDer2D)/binNum/binNum;
                 Double_t fxyDer2D = fabs(fyDer2D*fxDer2D);
                 //if(fxyDer2D < 20000./fabs(sin(phi_facet)/cos(phi_facet))) fxyDer2D = 0;
                 //if(fxyDer2D < 20000./fabs(sin(phi_facet)) || fxyDer2D < 20000./fabs(cos(phi_facet))) fxyDer2D = 0;
                 hfacet_der[i] -> Fill (x, y, fxyDer2D);
              }
           }

        //Double_t pc = TMath::ATan2( yc, xc );
        //if(pc < 0) pc = pc + 2*TMath::Pi();

       }}

       Int_t numBinsPhiX = hfacet_Phi[i]->GetNbinsX();
       Int_t numBinsPhiY = hfacet_Phi[i]->GetNbinsY();
       for ( UInt_t ix = 1; ix <= UInt_t(numBinsPhiX); ix++ )
       {
         for ( UInt_t iy = 1; iy <= UInt_t(numBinsPhiY); iy++ )
         {
           Double_t x = hfacet_Phi[i]->GetXaxis()->GetBinCenter( ix );
           Double_t y = hfacet_Phi[i]->GetYaxis()->GetBinCenter( iy );

              // calculate y Derivative in 2D, we use 2D histo without BG subtraction
              // formula is correct if all bins has the same width. If it is not true then you have to introduce bin width in this formula!
              if (ix>1 && Int_t(ix)<numBinsX && iy>1 && Int_t(iy)<numBinsY){
                 Double_t u0 = hfacet_Phi[i]->GetBinContent( ix-1, iy-1 ) + 2*hfacet_Phi[i]->GetBinContent( ix, iy-1 ) + hfacet_Phi[i]->GetBinContent( ix+1, iy-1 );
                 Double_t u2 = hfacet_Phi[i]->GetBinContent( ix-1, iy+1 ) + 2*hfacet_Phi[i]->GetBinContent( ix, iy+1 ) + hfacet_Phi[i]->GetBinContent( ix+1, iy+1 );
                 Double_t fyDer2D = u2-u0;// calculate derivative at iy (y1) point
                 // revert in negative y plain, want to have start of the facet to be positive from both sides:
                 if(y < 0) fyDer2D = -fyDer2D;
                 //if(fyDer2D < 0) fyDer2D = 1.; // don't interest in negative parts, but still want to see of there is effect at x derivative that is why 1, but not 0

                 Double_t u0x = hfacet_Phi[i]->GetBinContent( ix-1, iy-1 ) + 2*hfacet_Phi[i]->GetBinContent( ix-1, iy ) + hfacet_Phi[i]->GetBinContent( ix-1, iy+1 );
                 Double_t u2x = hfacet_Phi[i]->GetBinContent( ix+1, iy-1 ) + 2*hfacet_Phi[i]->GetBinContent( ix+1, iy ) + hfacet_Phi[i]->GetBinContent( ix+1, iy+1 );
                 Double_t fxDer2D = u2x-u0x;// calculate derivative at iy (y1) point
                 //if(fxDer2D < 0) fxDer2D = 1.; // what to find point where structure is starting <- could be used for systematic study
                 if(fxDer2D > 0) fxDer2D = -1.; // what to find point where structure is finish <- more precise because there is no structure close to finish edge
                 fxDer2D = -fxDer2D;
                 //Double_t fxyDer2D = fabs(fyDer2D*fxDer2D)/binNum/binNum;
                 Double_t fxyDer2D = fabs(fyDer2D*fxDer2D);
                 //hfacet_derPhi[i] -> Fill (x, y, fxyDer2D);
                 //hfacet_derPhi[i] -> Fill (x, y, fyDer2D);
                 hfacet_derPhi[i] -> Fill (x, y, fxDer2D);
    }}}

} /// end hfacet


    Double_t X1_facet[12], Y1_facet[12], X2_facet[12], Y2_facet[12];
    for(int i = 0; i < 12; i++){

       hfacet_der[i]->Draw("COLZ");
       cPlots->Update();
       std::ostringstream fn_der;
       fn_der.str("");
       fn_der << "Plots/"<<FitObject<<"_facet_der_" << i <<".png";
       cPlots->SaveAs(fn_der.str().c_str());


       Double_t phi = Pi/12. + Pi/6.*(i-2)-Pi/6.;
       //Double_t Threshold = 20000.;
       Double_t Threshold = 1000.;
       //Double_t ThresholdX = Threshold/fabs(sin(phi));
       //Double_t ThresholdY = Threshold/fabs(cos(phi));
       Double_t ThresholdX = 150000;
       Double_t ThresholdY = 400.; // dx only
       //Double_t ThresholdY = 600.; // dx only


       TLine *lineY = new TLine(-5,ThresholdY,5,ThresholdY);
       lineY -> SetLineStyle(kDotted);
       lineY -> SetLineColor(kRed);
       //TH1D * projhY = hfacet_der[i]->ProjectionY();
       TH1D * projhY = hfacet_derPhi[i]->ProjectionY();
       //TH1D * projhY = hfacet_Phi[i]->ProjectionY();
       projhY->GetXaxis()->SetRangeUser(-1.9, 1.9);
       //TH1D * projhY = hfacet[i]->ProjectionY();
       Double_t YprojMin = -100.;
       Double_t YprojMax = -100.;
       Int_t iYprojMin = -100;
       Int_t iYprojMax = -100;
       Double_t YprojCut = -100.;

       Int_t numBinsYproj = projhY->GetNbinsX();
       Int_t numPhiTestY = hfacet_derPhi[i] -> GetNbinsX();
       if (numBinsYproj != numPhiTestY)cout << "Error: different binning for projection (check that there is no SetRangeUser for original histo) for i = " << i << " numBinsYproj = " << numBinsYproj << " numPhiTestY = " << numPhiTestY << endl;
       for ( UInt_t ix = 1; ix <= UInt_t(numBinsYproj); ix++ ){
           Double_t binNum = projhY->GetBinContent( ix );
           Double_t binCenter = projhY->GetXaxis()->GetBinCenter(ix);
           //cout << "Test: numBinsYproj = " << numBinsYproj << " binCenter = " << binCenter << " binNum = " << binNum << endl;
           if(fabs(binCenter) > 1.5) continue; //reject tails where derivety is not correct in edges bins
           if (binNum >= ThresholdY && YprojCut < ThresholdY) {
               YprojMin = binCenter;
               iYprojMin = ix;
               YprojCut = binNum;
           }
           if (binNum >= ThresholdY) {YprojMax = binCenter; iYprojMax = ix;}
       }
       cout << "i = " << i << " YprojMin = " << YprojMin << " YprojMax = " << YprojMax << endl;
       cout << "i = " << i << " iYprojMin = " << iYprojMin << " iYprojMax = " << iYprojMax << endl;
       projhY->Draw("e");
       lineY -> Draw("same");
       cPlots->Update();
       std::ostringstream fn_derY;
       fn_derY.str("");
       fn_derY << "Plots/"<<FitObject<<"_facet_der_projY_" << i <<".png";
       cPlots->SaveAs(fn_derY.str().c_str());

       // Make projection on X new YprojMin and YprojMax:
       // find XprojMin
       TLine *lineX = new TLine(-5,ThresholdX,5,ThresholdX);
       lineX -> SetLineStyle(kDotted);
       lineX -> SetLineColor(kRed);
       //TH1D * projhX = hfacet_derPhi[i]->ProjectionX();
       // find X  starting after 2 mm from YprojMin and scan 2mm
       // find int # of bins for 2 mm
       Int_t iBin = 1; 
       Double_t dBin = hfacet_derPhi[i]->GetXaxis()->GetBinWidth(1); // bin with in cm 
       Int_t numBinsX_derPhi = hfacet_derPhi[i]->GetNbinsX();
       if (dBin < 0) {cout << "Error: bin width = " << dBin << endl;}
       iBin = Int_t(0.2/dBin); // count bins in 2 mm
       iBin = max(iBin,1);
       cout << "iBin = " << iBin << endl;
       TH1D * projhX = hfacet_derPhi[i]->ProjectionX("",iYprojMin+iBin, iYprojMin+2*iBin); // start from 2 mm from edge and scan for 2mm
       //TH1D * projhX = hfacet_Phi[i]->ProjectionX();
       projhX->GetXaxis()->SetRangeUser(-0.5, 0.5);
       //TH1D * projhX = hfacet_der[i]->ProjectionX();
       //TH1D * projhX = hfacet[i]->ProjectionX();
       Int_t numBinsXproj = projhX->GetNbinsX();
       //cout << "i = " << i << " numBinsXproj = " << numBinsXproj << endl;
       Double_t XprojMin = -100.;
       Double_t XprojCut = -100.;
     
       for ( UInt_t ix = 1; ix <= UInt_t(numBinsXproj); ix++ ){
           Double_t binNum = projhX->GetBinContent( ix );
           Double_t binCenter = projhX->GetXaxis()->GetBinCenter(ix);
           if(fabs(binCenter) > 0.2) continue; //reject tails where derivety is not correct in edges bins
           //if (binNum >= ThresholdX && XprojCut < ThresholdX) {
           //    XprojMin = binCenter; 
           //    XprojCut = binNum;
           //}
           //if (binNum >= ThresholdX) XprojMax = binCenter; 
           if (binNum >= XprojCut) { // find a point with maximum value
              XprojMin = binCenter;
              XprojCut = binNum;
              if(i == 5) cout << "binCenter = " << binCenter << " binNum = " << binNum << endl;
           } 
       }
       //XprojMin = XprojMax;// the same
       //cout << "i = " << i << " XprojMin = " << XprojMin << " XprojMax = " << XprojMax << endl;
       projhX->Draw("e");
       //lineX -> Draw("same");
       cPlots->Update();
       std::ostringstream fn_derX;
       fn_derX.str("");
       fn_derX << "Plots/"<<FitObject<<"_facet_der_projX_" << i <<".png";
       cPlots->SaveAs(fn_derX.str().c_str());
       //
       // find XprojMax
       TH1D * projhXmax = hfacet_derPhi[i]->ProjectionX("",iYprojMax-2*iBin, iYprojMax-iBin); //start from 2 mm from edge and scan for 2mm
       projhXmax->GetXaxis()->SetRangeUser(-0.5, 0.5);
       Double_t XprojMax = -100.;
       XprojCut = -100.;

       for ( UInt_t ix = 1; ix <= UInt_t(numBinsXproj); ix++ ){
           Double_t binNum = projhXmax->GetBinContent( ix );
           Double_t binCenter = projhXmax->GetXaxis()->GetBinCenter(ix);
           if(fabs(binCenter) > 0.2) continue; //reject tails where derivety is not correct in edges bins
           if (binNum >= XprojCut) { // find a point with maximum value
              XprojMax = binCenter;
              XprojCut = binNum;
           }
       }
       cout << "i = " << i << " XprojMin = " << XprojMin << " XprojMax = " << XprojMax << endl;
       projhXmax->Draw("e");
       cPlots->Update();
       std::ostringstream fn_derXmax;
       fn_derXmax.str("");
       fn_derXmax << "Plots/"<<FitObject<<"_facet_der_projX_yMax" << i <<".png";
       cPlots->SaveAs(fn_derXmax.str().c_str());
       //
       //SetRangeUser should be set only after projection, othewise bug in Root.
       hfacet_derPhi[i]->GetXaxis()->SetRangeUser(-5., 5.);
       hfacet_derPhi[i]->GetYaxis()->SetRangeUser(-5., 5.);
       hfacet_derPhi[i]->Draw("COLZ");
       cPlots->Update();
       std::ostringstream fn_derPhi;
       fn_derPhi.str("");
       fn_derPhi << "Plots/"<<FitObject<<"_facet_derPhi_" << i <<".png";
       cPlots->SaveAs(fn_derPhi.str().c_str());



       // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
       // positions of the two halves so that the background subtraction is cleaner.
       Double_t x0ref = x0;
       Double_t y0ref = y0;
       if (i > 5) {x0ref = x0_Far; y0ref = y0_Far;} // for far side
       Double_t R_facetNear = 2.8;
       Double_t R_facetFar = 3.1;
       if (i == 5 || i == 11) R_facetFar = R_facetFar + 0.2;
       Double_t phi_facet = Pi/12. + Pi/6.*(i-2)-Pi/6.;
       //select Near facet (each even) and Far facet (odd):
       Double_t R_facet = R_facetFar;
       if (i == int(i/2)*2) R_facet = R_facetNear;
       //Rotate in phi R system of facet
       Double_t xf_0 = R_facet*cos(phi_facet);
       Double_t yf_0 = R_facet*sin(phi_facet);

       X1_facet[i] = XprojMin*cos(phi_facet) - YprojMin*sin(phi_facet) + x0ref + xf_0; 
       Y1_facet[i] = XprojMin*sin(phi_facet) + YprojMin*cos(phi_facet) + y0ref + yf_0; 
       X2_facet[i] = XprojMax*cos(phi_facet) - YprojMax*sin(phi_facet) + x0ref + xf_0; 
       Y2_facet[i] = XprojMax*sin(phi_facet) + YprojMax*cos(phi_facet) + y0ref + yf_0; 
       //if (sin(phi)*cos(phi) < 0) 
       //   {X1_facet = XprojMin; Y1_facet = YprojMin; X2_facet = XprojMax; Y2_facet = YprojMax;}
       //else
       //   {X1_facet = XprojMax; Y1_facet = YprojMin; X2_facet = XprojMin; Y2_facet = YprojMax;}
   

       // Draw facet in phi
       TLine *lineFacetPhi = new TLine(XprojMin,YprojMin,XprojMax,YprojMax);
       lineFacetPhi -> SetLineColor(kRed);
       lineFacetPhi -> SetLineWidth(3);

       hfacet_Phi[i]->GetXaxis()->SetRangeUser(-5., 5.);
       hfacet_Phi[i]->GetYaxis()->SetRangeUser(-5., 5.);
       hfacet_Phi[i]->Draw("COLZ");
       lineFacetPhi -> Draw("same");
       cPlots->Update();
       std::ostringstream fn_Phi;
       fn_Phi.str("");
       fn_Phi << "Plots/"<<FitObject<<"_facet_PhiPlot_" << i <<".png";
       cPlots->SaveAs(fn_Phi.str().c_str());

    }
    cPlots -> SetLogz();

    //////////////////////////
    //////////////////////////
    //Double_t X1_facet[12], Y1_facet[12], X2_facet[12], Y2_facet[12];
    Int_t N_Line = 3;
    Int_t N_ver = N_Line*(N_Line-1)/2;
    // Find vertex for Near pixel useing 1st layer
    Double_t X1[N_Line],Y1[N_Line],X2[N_Line],Y2[N_Line]; 
    for ( UInt_t i = 0; i < UInt_t(N_Line); i++ ){ // for for new side far facets # 1, 3 and 5
      X1[i] = X1_facet[2*i+1]; 
      X2[i] = X2_facet[2*i+1]; 
      Y1[i] = Y1_facet[2*i+1]; 
      Y2[i] = Y2_facet[2*i+1]; 
    } 
    Double_t X_verNear[N_ver], Y_verNear[N_ver];
    Double_t X_VerNear = 0., Y_VerNear = 0.;
    Int_t Ncount = 0; 
    for ( UInt_t i = 0; i < UInt_t(N_ver-1); i++ ){ // for for new side far facets # 1, 3 and 5
        for ( UInt_t j = i+1; j < UInt_t(N_ver); j++ ){
            Double_t par[2]; // x0, y0
            Double_t Line1[4]; // x1,y1,x2,y2
            Double_t Line2[4]; // x3,y3,x4,y4
            Line1[0] = X1[i]; Line1[1] = Y1[i];
            Line1[2] = X2[i]; Line1[3] = Y2[i];
            Line2[0] = X1[j]; Line2[1] = Y1[j];
            Line2[2] = X2[j]; Line2[3] = Y2[j];
            fun2Lines(Line1, Line2, par);
            X_verNear[Ncount] = par[0];
            Y_verNear[Ncount] = par[1];
            cout << "Vertex Near # = " << Ncount <<  " for (i,j) = (" << i << "," << j<< ") X_verNear = " << X_verNear[Ncount] << " Y_verNear = " << Y_verNear[Ncount] << endl;
            X_VerNear = X_VerNear + X_verNear[Ncount];
            Y_VerNear = Y_VerNear + Y_verNear[Ncount];
            Ncount = Ncount + 1;
    }}
    if (Ncount != N_ver) cout << " Error: Ncount != N_ver " << endl;
    X_VerNear = X_VerNear/Ncount;
    Y_VerNear = Y_VerNear/Ncount;
    Double_t dX_VerNear = 0., dY_VerNear = 0.;
    Double_t dX_VerNearCon = 0., dY_VerNearCon = 0.;
    for ( UInt_t i = 0; i < UInt_t(Ncount); i++ ){
        dX_VerNear = dX_VerNear + (X_verNear[i]-X_VerNear)*(X_verNear[i]-X_VerNear); 
        dY_VerNear = dY_VerNear + (Y_verNear[i]-Y_VerNear)*(Y_verNear[i]-Y_VerNear); 
        //dX_VerNearCon = max(dX_VerNearCon, fabs(X_verNear[i]-X_VerNear)); 
        //dY_VerNearCon = max(dY_VerNearCon, fabs(Y_verNear[i]-Y_VerNear)); 
        dX_VerNearCon = dX_VerNearCon + fabs(X_verNear[i]-X_VerNear); 
        dY_VerNearCon = dY_VerNearCon + fabs(Y_verNear[i]-Y_VerNear); 
    }
    dX_VerNear = sqrt(dX_VerNear)/Ncount;
    dY_VerNear = sqrt(dY_VerNear)/Ncount;
    dX_VerNearCon = dX_VerNearCon/Ncount;
    dY_VerNearCon = dY_VerNearCon/Ncount;
    cout << "X_VerNear      = " << X_VerNear     << " Y_VerNear     = " << Y_VerNear << endl; 
    cout << "dX_VerNear     = " << dX_VerNear    << " dY_VerNear    = " << dY_VerNear << endl; 
    cout << "dX_VerNearCon  = " << dX_VerNearCon << " dY_VerNearCon = " << dY_VerNearCon << endl; 
    //////////////////////////
    //////////////////////////
    // Find vertex for Near pixel useing 1st layer
    Double_t X1Far[N_Line],Y1Far[N_Line],X2Far[N_Line],Y2Far[N_Line];
    for ( UInt_t i = 0; i < UInt_t(N_Line); i++ ){ // for for new side far facets # 1, 3 and 5
      X1Far[i] = X1_facet[2*(i+3)+1];
      X2Far[i] = X2_facet[2*(i+3)+1];
      Y1Far[i] = Y1_facet[2*(i+3)+1];
      Y2Far[i] = Y2_facet[2*(i+3)+1];
    }
    Double_t X_verFar[N_ver], Y_verFar[N_ver];
    Double_t X_VerFar = 0., Y_VerFar = 0.;
    Ncount = 0;
    for ( UInt_t i = 0; i < UInt_t(N_ver-1); i++ ){ // for for new side far facets # 1, 3 and 5
        for ( UInt_t j = i+1; j < UInt_t(N_ver); j++ ){
            Double_t par[2]; // x0, y0
            Double_t Line1[4]; // x1,y1,x2,y2
            Double_t Line2[4]; // x3,y3,x4,y4
            Line1[0] = X1Far[i]; Line1[1] = Y1Far[i];
            Line1[2] = X2Far[i]; Line1[3] = Y2Far[i];
            Line2[0] = X1Far[j]; Line2[1] = Y1Far[j];
            Line2[2] = X2Far[j]; Line2[3] = Y2Far[j];
            fun2Lines(Line1, Line2, par);
            X_verFar[Ncount] = par[0];
            Y_verFar[Ncount] = par[1];
            cout << "Vertex Far # = " << Ncount <<  " for (i,j) = (" << i << "," << j<< ") X_verFar = " << X_verFar[Ncount] << " Y_verFar = " << Y_verFar[Ncount] << endl;
            //cout << "x1 = " << Line1[0] << " y1 = " << Line1[1] << " x2 = " << Line1[2] << " y2 = " << Line1[3] << endl;
            //cout << "x3 = " << Line2[0] << " y3 = " << Line2[1] << " x4 = " << Line2[2] << " y4 = " << Line2[3] << endl;
            //cout << endl;
            X_VerFar = X_VerFar + X_verFar[Ncount];
            Y_VerFar = Y_VerFar + Y_verFar[Ncount];
            Ncount = Ncount + 1;
    }}
    if (Ncount != N_ver) cout << " Error: Ncount != N_ver " << endl;
    X_VerFar = X_VerFar/Ncount;
    Y_VerFar = Y_VerFar/Ncount;
    Double_t dX_VerFar = 0., dY_VerFar = 0.;
    Double_t dX_VerFarCon = 0., dY_VerFarCon = 0.;
    for ( UInt_t i = 0; i < UInt_t(Ncount); i++ ){
        dX_VerFar = dX_VerFar + (X_verFar[i]-X_VerFar)*(X_verFar[i]-X_VerFar);
        dY_VerFar = dY_VerFar + (Y_verFar[i]-Y_VerFar)*(Y_verFar[i]-Y_VerFar);
        dX_VerFarCon = dX_VerFarCon + fabs(X_verFar[i]-X_VerFar);
        dY_VerFarCon = dY_VerFarCon + fabs(Y_verFar[i]-Y_VerFar);
    }
    dX_VerFar = sqrt(dX_VerFar)/Ncount;
    dY_VerFar = sqrt(dY_VerFar)/Ncount;
    dX_VerFarCon = dX_VerFarCon/Ncount;
    dY_VerFarCon = dY_VerFarCon/Ncount;
    cout << "X_VerFar      = " << X_VerFar     << " Y_VerFar     = " << Y_VerFar << endl;
    cout << "dX_VerFar     = " << dX_VerFar    << " dY_VerFar    = " << dY_VerFar << endl;
    cout << "dX_VerFarCon  = " << dX_VerFarCon << " dY_VerFarCon = " << dY_VerFarCon << endl;
    //////////////////////////
    //////////////////////////

    for(int i = 0; i < 12; i++){

       // Draw facet in (x,y)
       TLine *lineFacet = new TLine(X1_facet[i],Y1_facet[i],X2_facet[i],Y2_facet[i]);
       //lineFacet -> SetLineStyle(kDotted);
       lineFacet -> SetLineColor(kRed);
       lineFacet -> SetLineWidth(3);
       Double_t x1 = (X1_facet[i]+X2_facet[i])/2.;
       Double_t y1 = (Y1_facet[i]+Y2_facet[i])/2.;
       Double_t x2 = 0.;
       Double_t y2 = -100.;
       if( fabs(Y1_facet[i]-Y2_facet[i]) > 0.00001 ) y2 = (Y1_facet[i]+Y2_facet[i])/2. + (X1_facet[i]*X1_facet[i]-X2_facet[i]*X2_facet[i])/2./(Y1_facet[i]-Y2_facet[i]);
       TLine *lineFacetPerp = new TLine(x1,y1,x2,y2);
       lineFacetPerp -> SetLineColor(kBlue);
       lineFacetPerp -> SetLineWidth(3);
       TGraph* gr_arc;
       Double_t x_arc0[1], y_arc0[1];
       x_arc0[0] = 0.;
       y_arc0[0] = 0.;
       gr_arc = new TGraph(1,x_arc0,y_arc0);
      // put a cross at (0,0)
       gr_arc->SetMarkerStyle(33);
       gr_arc->SetMarkerSize(2.5);
       //gr_arc->SetMarkerColor(kBlue);
       gr_arc->SetMarkerColor(kBlack);
       TGraph* gr_VerNear = new TGraph(3,X_verNear,Y_verNear); 
       gr_VerNear->SetMarkerStyle(33);
       gr_VerNear->SetMarkerSize(2.5);
       gr_VerNear->SetMarkerColor(kRed);
       TGraph* gr_VerFar = new TGraph(3,X_verFar,Y_verFar); 
       gr_VerFar->SetMarkerStyle(33);
       gr_VerFar->SetMarkerSize(2.5);
       gr_VerFar->SetMarkerColor(kBlue);

       hfacet[i]->GetXaxis()->SetRangeUser(-5., 5.);
       hfacet[i]->GetYaxis()->SetRangeUser(-5., 5.);
       hfacet[i]->Draw("COLZ");
       lineFacet -> Draw("same");
       lineFacetPerp -> Draw("same");
       gr_arc -> Draw("P");
       gr_VerNear -> Draw("P");
       gr_VerFar -> Draw("P");
       cPlots->Update();
       std::ostringstream fn;
       fn.str("");
       fn << "Plots/"<<FitObject<<"_facet_Plot_" << i <<".png";
       cPlots->SaveAs(fn.str().c_str());



    } 
    //////////////////////////////////
    //////////////////////////////////
    continue; // don't need code below
    //////////////////////////////////
    //////////////////////////////////

    /// -------------- Step 1: find the background density as a function of phi and rho(x0, y0) ----------

    //estimate if we have any object inside of signal region except fitted object
    Int_t bgFitQuality[40];

    Double_t bgFit0[40];
    Double_t bgFit0Err[40];
    Double_t bgFit1[40];
    Double_t bgFit1Err[40];


    //divide 2D x-y plot into 40 sectors in phi as function of R
    for ( UInt_t phiSect = 0; phiSect < 40; phiSect ++ )
    {
      //Int_t numBinsX = h->GetNbinsX();
      //Int_t numBinsY = h->GetNbinsY();
      Double_t Xmax_h = h->GetXaxis()->GetBinCenter(numBinsX ) + h->GetXaxis()->GetBinWidth( numBinsX )/2;
      if(numBinsX != numBinsY) std::cout << "WARNING numBinsX = " << numBinsX << "is not equal to numBinsY = " << numBinsY << std::endl;
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      //std::cout << "Xmax_h = " << Xmax_h << endl;

      for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
      {
        for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
          // positions of the two halves so that the background subtraction is cleaner.
          Double_t x0ref = x0;
          Double_t y0ref = y0;
          if (FitObject == "PixelShieldMinus" && x >= 0) {x0ref = x0_PixelShieldPlus; y0ref = y0_PixelShieldPlus;}
          if (FitObject == "PixelSupportMinus" && x >= 0) {x0ref = x0_PixelSupportPlus; y0ref = y0_PixelSupportPlus;}

          if (FitObject == "PixelShield2Ellipses" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}
          if (FitObject == "PixelShield2Arcs" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}

          Double_t xc = x - x0ref;
          Double_t yc = y - y0ref;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Rmin || rc > Rmax ) continue;

          //Double_t pc = TMath::ATan2( yc, xc );
          Double_t pc = TMath::ATan2( y, x );
          if(pc < 0) pc = pc + 2*TMath::Pi();
          Int_t thisPhiSect = floor(  pc  / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != Int_t(phiSect) ) continue;
          //if(thisPhiSect == 0)std::cout << "thisPhiSect = " << thisPhiSect << " pc = " << pc << std::endl;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );

          hbgua0->Fill( rc, densityNum );

          //if ( ( rc > Rmin && rc < RSmin ) || ( rc > RSmax && rc < Rmax ) )
          if ( rc > RBGmin && rc < RBGmax )
          {
            hbgua1->Fill( rc, densityNum );
          }
          else if ( rc >= RSmin && rc <= RSmax )
          {
            hbgua2->Fill( rc, densityNum );
          }
        }
      }


      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2015}_{0},y^{2015}_{0}) (cm)");
      //hbgua0->GetXaxis()->SetRangeUser(PipeInf, FitSup+0.1);
      hbgua0->GetXaxis()->SetRangeUser(Rmin, Rmax);


      hbgua0->Draw();
      cPlots->Update();

      TPaveStats* sBg = (TPaveStats*)hbgua0->GetListOfFunctions()->FindObject("stats");
      x1L = sBg->GetX1NDC();
      x2L = sBg->GetX2NDC();
      y1L = sBg->GetY1NDC();
      y2L = sBg->GetY2NDC();

      hbgua0->SetStats(0);
      hbgua1->SetStats(0);
      hbgua2->SetStats(0);

      hbgua0->Draw();
      hbgua1->SetFillStyle(3004);
      hbgua1->SetFillColor(kRed);
      hbgua1->SetMarkerColor(kRed);
      hbgua1->SetLineColor(kRed);
      hbgua1->Draw("same");
      hbgua2->SetFillStyle(3005);
      hbgua2->SetFillColor(kGreen);
      hbgua2->SetMarkerColor(kGreen);
      hbgua2->SetLineColor(kGreen);
      hbgua2->Draw("same");

      //TF1 *fitBg = new TF1( "fitBg","[0] + x*[1]", RBGmin , RBGmax );
      //TF1 *fitBg = new TF1( "fitBg","[0]*[0]*TMath::Exp([1]*x)", RBGmin , RBGmax );
      TF1 *fitBg = new TF1( "fitBg",func_fitBg, RBGmin , RBGmax, 2 );
      fitBg->SetParameter(0, 10);
      fitBg->SetParameter(1, 0.01);
      fitBg->FixParameter(1,0);
      fitBg->SetParName(0, "N0");
      fitBg->SetParName(1, "k");
      //we  need set limits here to avoid negative values in fit (it will crash)
      //fitBg->SetParLimits(0, 0, 1E9);
      //fitBg->SetParLimits(1, -1E9, 0);
      fitBg->SetLineWidth(3);
      hbgua1->Fit("fitBg","MR0");
      fitBg->Draw("same");

      bgFit0[phiSect] = fitBg->GetParameter(0);
      bgFit0Err[phiSect] = fitBg->GetParError(0);
      if (bgFit0Err[phiSect] < 0) cout << "Erorr: bgFit0Err = " << bgFit0Err << endl;
      bgFit1[phiSect] = fitBg->GetParameter(1);
      bgFit1Err[phiSect] = fitBg->GetParError(1);
      if (bgFit1Err[phiSect] < 0) cout << "Erorr: bgFit1Err = " << bgFit1Err << endl;

      TLegend* legBg = new TLegend(x1L, 0.6, x2L, y2L, "");
      legBg->SetTextFont(42);
      legBg->SetTextSize(0.03*ScaleSize);
      legBg->SetFillColor(kWhite);
      legBg->SetTextColor(kBlack);
      legBg->AddEntry(hbgua0,"Data 2018","l");
      legBg->AddEntry(hbgua2,"Signal fit region","f");
      legBg->AddEntry(hbgua1,"Sideband fit region","f");
      legBg->AddEntry(fitBg,"Sideband fit function","l");
      legBg->Draw("same");

      gStyle->SetOptStat(1000111110);

// uncomment if you want fit only background plots in slices
/*
      std::ostringstream fn;
      fn << "Plots/"<<plotBg.c_str()<<"_BGUA" << "_" << phiSect<<".pdf";
      cPlots->SaveAs(fn.str().c_str());
      fn.str("");
      fn << "Plots/"<<plotBg.c_str()<<"_BGUA" << "_" << phiSect<<".png";
      cPlots->SaveAs(fn.str().c_str());
*/
      //delete to avoid memory leak:
      //cPlots->Delete();
      //if(cPlots)delete cPlots;
      delete hbgua0;
      delete hbgua1;
      delete hbgua2;

    } //end phi sector cycle

    /// -------------------------- Step 2: calculate background --------------------------------

    plot = plot + "_Bgk";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");
    cPlots->cd();

    //create empty 2d histo for backroung estimation in signal region
    TH2D* h0 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h0->GetXaxis()->SetTitle("x (cm)");
    h0->GetYaxis()->SetTitle("y (cm)");

    //Int_t numBinsX = h0->GetNbinsX();
    //Int_t numBinsY = h0->GetNbinsY();
    for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
    {
      for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
        //Double_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );

        // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
        // positions of the two halves so that the background subtraction is cleaner.
        Double_t x0ref = x0;
        Double_t y0ref = y0;
        if(FitObject == "PixelShieldMinus" && x >= 0) x0ref = x0_PixelShieldPlus, y0ref = y0_PixelShieldPlus;
        if(FitObject == "PixelSupportMinus" && x >= 0) x0ref = x0_PixelSupportPlus, y0ref = y0_PixelSupportPlus;

          if (FitObject == "PixelShield2Ellipses" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}
          if (FitObject == "PixelShield2Arcs" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}

        Double_t xc = x - x0ref;
        Double_t yc = y - y0ref;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

        if ( rc < Rmin || rc > Rmax ) continue;

        //Double_t pc = TMath::ATan2( yc, xc );
        Double_t pc = TMath::ATan2( y, x );
        if(pc < 0) pc = pc + 2*TMath::Pi();

        if ( rc > RSmin && rc < RSmax )
        {
          UInt_t phiSect = floor(  pc   / ( 2*TMath::Pi() ) * 40 );

          //Double_t par0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          //Double_t par1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );
          Double_t par0 =  bgFit0[phiSect];
          Double_t par1 =  bgFit1[phiSect];
          Double_t par0_p1 =  bgFit0[(41+phiSect)%40];
          Double_t par1_p1 =  bgFit1[(41+phiSect)%40];
          Double_t par0_m1 =  bgFit0[(39+phiSect)%40];
          Double_t par1_m1 =  bgFit1[(39+phiSect)%40];
          //cout << "par0_p1 =  " << par0_p1 << " par1_p1 =  " << par1_p1 << " par0_m1 =  " << par0_m1 << " par1_m1 =  " << par1_m1 << endl;

          Double_t x_rc[1];     x_rc[0]= rc;
          Double_t par_rc[2]; par_rc[0] = par0; par_rc[1] = par1;
          Double_t par_rc_p1[2]; par_rc_p1[0] = par0_p1; par_rc_p1[1] = par1_p1;
          Double_t par_rc_m1[2]; par_rc_m1[0] = par0_m1; par_rc_m1[1] = par1_m1;
          
          Double_t bgDensity = func_fitBg(x_rc,par_rc);
          /// Average over 3 adjacent sectors to smooth differences
          if (AverageBG == 1) bgDensity = (func_fitBg(x_rc,par_rc) + func_fitBg(x_rc,par_rc_p1) + func_fitBg(x_rc,par_rc_m1) )/3.;
          //cout << "bgDensity = " << bgDensity << endl;
          //cout << "func_fitBg(x_rc,par_rc) = " << func_fitBg(x_rc,par_rc) << endl;
          //cout << "func_fitBg(x_rc,par_rc_p1) = " << func_fitBg(x_rc,par_rc_p1) << endl;
          //cout << "func_fitBg(x_rc,par_rc_m1) = " << func_fitBg(x_rc,par_rc_m1) << endl;

          Double_t bgNum = h0->GetXaxis()->GetBinWidth( ix ) * h0->GetYaxis()->GetBinWidth( iy ) * bgDensity;

          if ( ( rc > RSmin && rc < RSmax ) )
            h0->Fill( x, y, bgNum );
        }
      }
    }

    h0->Draw("COL");

    // plot average estimated background in signal region from PipeInf to PipeSup
    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_DrawBG.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_DrawBG.png"));


    h0->Draw("LEGO");

    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_DrawBG_LEGO.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_DrawBG_LEGO.png"));
    //cPlots->Delete();
    //delete cPlots;

    /// ----------- Step 3: cross check background with original densities used for the fit -------------

    for ( UInt_t phiSect = 0; phiSect < 40; phiSect ++ )
    {
      //std::cout << "********MADE IT INTO LOOP********" << std::endl;
      //Int_t numBinsX = h->GetNbinsX();
      //Int_t numBinsY = h->GetNbinsY();
      Double_t Xmax_h = h->GetXaxis()->GetBinCenter(numBinsX ) + h->GetXaxis()->GetBinWidth( numBinsX )/2;

      //std::cout << "********ABOUT TO CREATE HISTOGRAMS********" << std::endl;
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua3 = new TH1D( (plotBg+"_BGUA3").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      //std::cout << "Int_t(numBinsX/2) = " << Int_t(numBinsX/2) << std::endl;
      //std::cout << "********FINISHED CREATING HISTOGRAMS********" << std::cout;
      for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
      {
        for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
          // positions of the two halves so that the background subtraction is cleaner.
          Double_t x0ref = x0;
          Double_t y0ref = y0;
          if(FitObject == "PixelShieldMinus" && x >= 0) x0ref = x0_PixelShieldPlus, y0ref = y0_PixelShieldPlus;
          if(FitObject == "PixelSupportMinus" && x >= 0) x0ref = x0_PixelSupportPlus, y0ref = y0_PixelSupportPlus;

          if (FitObject == "PixelShield2Ellipses" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}
          if (FitObject == "PixelShield2Arcs" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}

          Double_t xc = x - x0ref;
          Double_t yc = y - y0ref;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Rmin || rc > Rmax ) continue;

          //Double_t pc = TMath::ATan2( yc, xc );
          Double_t pc = TMath::ATan2( y, x );
          if(pc < 0) pc = pc + 2*TMath::Pi();

          Int_t thisPhiSect = floor(  pc / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != Int_t(phiSect) ) continue;

          //if (thisPhiSect == 0) std::cout << "thisPhiSect = " << thisPhiSect << " pc = " << pc << " x = " << x << " y = " << y << std::endl;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );

          hbgua0->Fill( rc, densityNum );

          //if ( ( rc > Rmin && rc < RSmin ) || ( rc > RSmax && rc < Rmax ) )
          if ( rc > RBGmin && rc < RBGmax )
          {
            hbgua1->Fill( rc, densityNum );
          }
          else if ( rc >= RSmin && rc <= RSmax )
          {
            hbgua2->Fill( rc, densityNum );
          }

          Double_t binNum0 = h0->GetBinContent( ix, iy );

          Double_t densityNum0 = binNum0 / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );
          if ( ( rc > RSmin && rc < RSmax ) )
          {
            hbgua3->Fill( rc, densityNum0 );
          }

        }
      } // end cycle by h

      // 
      // estimate if we have other objects in fit region with width = RangeEstimatorQuality
      Double_t SignalLowEdge = 0.; Double_t SignalUpperEdge = 0.; Double_t BgUpperEdge = 0.;
      //std::cout << " Int_t(numBinsX/2) = " << Int_t(numBinsX/2) << " hbgua0->GetNbinsX() = " << hbgua0->GetNbinsX() << std::endl;
      for ( UInt_t ix = 1; ix <= UInt_t(numBinsX/2); ix++ )
      { 
        Double_t x = hbgua0->GetXaxis()->GetBinCenter( ix );
        Double_t value = hbgua0->GetBinContent(ix);
        if( x > RSmin && x < (RSmin+RangeEstimatorQuality) ) SignalLowEdge = SignalLowEdge + value;
        if( (FitObject == "PixelSupport" || FitObject == "PixelSupportEllipse" || FitObject == "BeamPipe" || FitObject == "BeamPipeEllipse") 
             && x > RSmax && x < (RSmax+RangeEstimatorQuality)) SignalUpperEdge = SignalUpperEdge + value;
        if( (FitObject == "PixelShieldEllipse" || FitObject == "PixelShield2Ellipses" || FitObject == "PixelShield2Arcs"|| FitObject == "PixelShield" || FitObject == "PixelShieldPlus" || FitObject == "PixelShieldMinus") 
            && x > (RSmax-RangeEstimatorQuality) && x < RSmax) SignalUpperEdge = SignalUpperEdge + value;
        
        if( x > (RBGmax-RangeEstimatorQuality) && x < RBGmax) BgUpperEdge = BgUpperEdge + value;
      }
      bgFitQuality[phiSect] = 1; //good phi sector for fit      

      // Flag phi sectors to be excluded from the fit using bin contents in the signal and background region
      if( FitObject == "PixelSupportPlus" || FitObject == "PixelSupportMinus")
        {
         if (SignalLowEdge > 0.6*BgUpperEdge || SignalUpperEdge > 1.3*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        }
      if( FitObject == "PixelSupport" || FitObject == "PixelSupportEllipse")
        {
         //if (SignalLowEdge > 0.2*BgUpperEdge ) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
         if (BgUpperEdge > 2.0*SignalUpperEdge ) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
         std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << bgFitQuality[phiSect] << "   BgUpperEdge/SignalUpperEdge = "<< BgUpperEdge/SignalUpperEdge << std::endl;
         //cout << " BgUpperEdge = " << BgUpperEdge << " SignalUpperEdge = " << SignalUpperEdge << endl;
        }
      if(FitObject == "PixelShield")
        {
        if (SignalUpperEdge > 1.3*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
        std::cout << "********DONE CHECKING SLICE TO REMOVE STRUCTURES********" << std::endl;
        }
      if(FitObject == "PixelShieldPlus" )
        {
        if (SignalUpperEdge > 1.15*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
        }
      if(FitObject == "PixelShieldMinus")
        {
        if (SignalUpperEdge > 1.15*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
        }
      if(FitObject == "PixelShieldEllipse")
        {
        if (SignalUpperEdge > 1.2*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        std::cout << "Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
        }
      if(FitObject == "PixelShield2Ellipses" || (FitObject == "PixelShield2Arcs" && k == -6))
        {
        if (SignalUpperEdge > 1.2*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        cout << "BgUpperEdge =" << BgUpperEdge << endl;
        std::cout << "Phi Sector = " << phiSect << " hQuality fill = " << bgFitQuality[phiSect] << "   SignalUpperEdge/BgUpperEdge =" << SignalUpperEdge/BgUpperEdge << std::endl;
        }
      if(FitObject == "PixelShield2Arcs" && k != -6)
        {
        if (k == 4 && SignalUpperEdge > 1.25*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        //if (k == 4 && SignalUpperEdge > 2.*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        if (k == -5 && SignalUpperEdge > 1.4*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        if (k == -4 && SignalUpperEdge > 1.2*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        if (k == -2 && SignalUpperEdge > 1.*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        if (k == 0 && SignalUpperEdge > 0.85*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        if (k == 2 && SignalUpperEdge > 1.2*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        std::cout << "Phi Sector = " << phiSect << " hQuality fill = " << bgFitQuality[phiSect] << "   SignalUpperEdge/BgUpperEdge =" << SignalUpperEdge/BgUpperEdge << std::endl;
        }
      if(BgUpperEdge > 0.)hQuality->Fill( max(SignalLowEdge/BgUpperEdge, SignalUpperEdge/BgUpperEdge) );
      if(FitObject == "PixelShield")std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;

      cPlots->cd();
      hbgua0->SetMinimum(0);
      //hbgua0->GetXaxis()->SetTitle("#rho (x^{2017}_{0},y^{2017}_{0}) (cm)");
      hbgua0->GetXaxis()->SetTitleOffset(1.05);
      hbgua0->GetXaxis()->SetTitle("#rho (x_{0}, y_{0}) (cm)");
      hbgua0->GetYaxis()->SetTitle(Form("Events / %2.2f cm ",hbgua0->GetXaxis()->GetBinWidth(1)));
      hbgua0->GetXaxis()->SetRangeUser(Rmin, Rmax);
      hbgua0->Draw();
      cPlots->Update();

      // Format the plots of the phi sectors
      TPaveStats* sBg = (TPaveStats*)hbgua0->GetListOfFunctions()->FindObject("stats");
      x1L = sBg->GetX1NDC();
      x2L = sBg->GetX2NDC();
      y1L = sBg->GetY1NDC();
      y2L = sBg->GetY2NDC();

      hbgua0->SetStats(0);
      hbgua1->SetStats(0);
      hbgua2->SetStats(0);
 
      //gStyle->SetHatchesSpacing(2.0);
      //gStyle->SetHatchesLineWidth(2);
      hbgua0->SetLineWidth(3);
      hbgua1->SetLineWidth(3);
      hbgua2->SetLineWidth(3);
      hbgua3->SetLineWidth(3);
      hbgua0->Draw("histo");
      hbgua1->SetFillStyle(3004);
      //hbgua1->SetFillStyle(545);
      hbgua1->SetFillColor(kRed+1);
      hbgua1->SetMarkerColor(kRed+1);
      hbgua1->SetLineColor(kRed+1);
      hbgua1->Draw("samehisto");
      //hbgua2->SetFillStyle(3005);
      hbgua2->SetFillStyle(3013);
      hbgua2->SetFillColor(kGreen+2);
      hbgua2->SetMarkerColor(kGreen+2);
      hbgua2->SetLineColor(kGreen+2);
      hbgua2->Draw("samehisto");
      hbgua3->SetFillStyle(3005);
      //hbgua3->SetFillStyle(3335);
      hbgua3->SetFillColor(kBlue);
      hbgua3->SetMarkerColor(kBlue);
      hbgua3->SetLineColor(kBlue);
      hbgua3->Draw("samehisto");

      //TF1 *fitBg = new TF1( "fitBg","[0] + x*[1]", RBGmin, RBGmax );
      TF1 *fitBg = new TF1( "fitBg",func_fitBg, RBGmin , RBGmax, 2 );
      fitBg->SetParameter(0, bgFit0[phiSect]);
      fitBg->SetParameter(1, bgFit1[phiSect]);
      fitBg->SetParName(0, "N0");
      fitBg->SetParName(1, "k");
      fitBg->SetLineWidth(3);
      //fitBg->Draw("same");

      //TLegend* legBg = new TLegend(x1L, 0.52, x2L, y2L, "");
      //TLegend* legBg = new TLegend(0.45, 0.6, 0.8, 0.9, "");
      TLegend* legBg = new TLegend(0.5, 0.6, 0.7, 0.8, "");
      if(FitObject == "PixelSupportEllipse")legBg = new TLegend(0.2, 0.6, 0.4, 0.8, "");
      legBg->SetTextFont(42);
      legBg->SetTextSize(0.04*ScaleSize);
      legBg->SetFillColor(kWhite);
      legBg->SetTextColor(kBlack);
      if (bgFitQuality[phiSect] == 0) legBg->AddEntry(hbgua0,"EXCLUDED from FIT","");
      //legBg->AddEntry(hbgua0,Form("Data 2018, #phi sector = %d", phiSect),"");
      legBg->AddEntry(hbgua0,Form("Data 2018, #phi sector = %d", phiSect),"l");
      legBg->AddEntry(hbgua2,"Signal fit region","f");
      legBg->AddEntry(hbgua1,"Sideband fit region","f");
      //legBg->AddEntry(fitBg,"sideband fit function","l");
      legBg->AddEntry(hbgua3,"Estimated background","f");
      legBg->Draw("same");

      //gStyle->SetLineWidth(3);
      //hbgua0->SetAxisWidth(3);
      hbgua0->Draw("AXISsame");
      hbgua0->Draw("histosame");
      //gStyle->SetLineWidth(1);
      //TLine * lineTop = new TLine ( x1, y1, x2, y2 );
      TLine * lineX = new TLine ( Rmin, 0, Rmax , 0. );
      lineX->SetLineColor(kBlack);
      lineX->SetLineWidth(3);
      lineX->Draw("same");

      if (phiSect == 1 && FitObject == "BeamPipe" ) CMS_lumi( cPlots, iPeriod, iPos );
      gStyle->SetOptStat(1000111110);
      //gStyle->SetOptStat(0000000000);

      std::ostringstream fn;
      std::ostringstream fn_pdf;
      //fn << "Plots/"<<plotBg<<"_BGUA_XCk" << "_" << phiSect<<".pdf";
      fn_pdf << "Plots/"<<FitObject<<"_Slice_BGUA_XCk" << "_" << phiSect<<".pdf";
      //cPlots->SaveAs(fn.str().c_str());
      fn.str("");
      fn << "Plots/"<<FitObject<<"_Slice_BGUA_XCk" << "_" << phiSect<<".png";
      if (FitObject != "PixelSupportRails" && FitObject != "PixelSupportRailsPositive" && FitObject != "PixelSupportRailsNegative")cPlots->SaveAs(fn.str().c_str());
      if (phiSect == 1 && FitObject == "BeamPipe")cPlots->SaveAs(fn_pdf.str().c_str());
      //delete to avoid memory leak:
      //cPlots->Delete();
      //delete cPlots;
      delete hbgua0;
      delete hbgua1;
      delete hbgua2;
      delete hbgua3;
    } //end phi cicle


    cQuality = new TCanvas("");
    cQuality->cd();
    hQuality->Draw("e");
    //cQuality->Print("Plots/Quality.png");

    /// ----------------------- Step 4: subtract the background from the signal ---------------

    const std::string stBg = "_Bkg";
    if ( plot != stBg &&
         plot.size() > stBg.size() &&
         plot.substr(plot.size() - stBg.size()) == "_Bkg" )
    plot = plot.substr(0, plot.size() - stBg.size());

    plot = plot + "_Fit";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");
    cPlots->cd();

    //create empty histo for 2D signal (minus backroung minus 2 simgma of background)
    TH2D* h1 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h1->GetXaxis()->SetTitle("x (cm)");
    h1->GetYaxis()->SetTitle("y (cm)");
    h1->GetZaxis()->SetTitle(Form("Events/(%1.1f#times%1.1f mm^{2})", h1->GetXaxis()->GetBinWidth(1)*10,  h1->GetYaxis()->GetBinWidth(1)*10));
    h1->GetZaxis()->SetTitleOffset(1.4);
    //Int_t numBinsX = h->GetNbinsX();
    //Int_t numBinsY = h->GetNbinsY();

    Double_t Ymin_Deriv = h->GetYaxis()->GetBinCenter(1);
    Double_t Ymax_Deriv = h->GetYaxis()->GetBinCenter(numBinsY ) + h->GetYaxis()->GetBinWidth( numBinsY );
    std::cout << "Ymin_Deriv = " << Ymin_Deriv << " Ymax_Deriv = " << Ymax_Deriv << " bin width = " << h->GetYaxis()->GetBinWidth(1) << std::endl;
    hYderivative = new TH1D( "hYderivative", "x-integrated derivative as funct. of y", numBinsY, Ymin_Deriv, Ymax_Deriv );
    hYderivative2D = new TH2D( "hYderivative2D", "Y Derivative", h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    hXderivative2D = new TH2D( "hXderivative2D", "X Derivative", h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );

    //std::cout << "Number of X bins: " << h->GetNbinsX() << std::endl;
    //std::cout << "Number of Y bins: " << h->GetNbinsY() << std::endl;

    UInt_t yRailTop = 0.;
    UInt_t yRailBottom = 0.;
    Double_t yRailTopDer = 0.;
    Double_t yRailBottomDer = 0.;

    for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
    { 
      Double_t Xmin_int = 0.;
      Double_t Xmax_int = 0.;
      Double_t Ywidth = h->GetYaxis()->GetBinWidth( iy );
      if (Ywidth <= 0 ) std::cout << "Error Ywith = " << Ywidth << std::endl;
      if (Ywidth <= 0) continue;
      
      for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
      { 
        Double_t binNum = h->GetBinContent( ix, iy );
        
        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );
        
        // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
        // positions of the two halves so that the background subtraction is cleaner.
        Double_t x0ref = x0;
        Double_t y0ref = y0;
        if(FitObject == "PixelShieldMinus" && x >= 0) x0ref = x0_PixelShieldPlus, y0ref = y0_PixelShieldPlus;
        if(FitObject == "PixelSupportMinus" && x >= 0) x0ref = x0_PixelSupportPlus, y0ref = y0_PixelSupportPlus;

        if (FitObject == "PixelShield2Ellipses" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}
        if (FitObject == "PixelShield2Arcs" && x < 0) {x0ref = x0_Far; y0ref = y0_Far;}

        Double_t xc = x - x0ref;
        Double_t yc = y - y0ref;
        
        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );
        Double_t pc = TMath::ATan2( yc, xc );
        if(pc < 0) pc = pc + 2*TMath::Pi();
        
        //if ( rc > Rmin && rc < Rmax )
        if ( rc > RSmin && rc < RSmax )
        { 
          Xmin_int += binNum;
          if (Int_t(iy) < numBinsY) Xmax_int += h->GetBinContent( ix, iy+1 );
          
          UInt_t phiSect = floor(  pc / ( 2*TMath::Pi() ) * 40 );
          
          /// Remove Background
          //Double_t par0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          //Double_t par1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );
          Double_t par0 =  bgFit0[phiSect];
          Double_t par1 =  bgFit1[phiSect];
          Double_t par0_p1 =  bgFit0[(41+phiSect)%40];
          Double_t par1_p1 =  bgFit1[(41+phiSect)%40];
          Double_t par0_m1 =  bgFit0[(39+phiSect)%40];
          Double_t par1_m1 =  bgFit1[(39+phiSect)%40];
          
          Double_t x_rc[1];     x_rc[0]= rc;
          Double_t par_rc[2]; par_rc[0] = par0; par_rc[1] = par1;
          Double_t par_rc_p1[2]; par_rc_p1[0] = par0_p1; par_rc_p1[1] = par1_p1;
          Double_t par_rc_m1[2]; par_rc_m1[0] = par0_m1; par_rc_m1[1] = par1_m1;

          Double_t bgDensity = func_fitBg(x_rc,par_rc); 
          /// Average over 3 adjacent sectors to smooth differences
          if (AverageBG == 1) bgDensity = (func_fitBg(x_rc,par_rc) + func_fitBg(x_rc,par_rc_p1) + func_fitBg(x_rc,par_rc_m1) )/3.; 
          //cout << "bgDensity = " << bgDensity << endl;
          //cout << "1/3 = " << 1/3 << endl;
          //cout << "1./3. = " << 1./3. << endl;



          Double_t bgNum = h1->GetXaxis()->GetBinWidth( ix ) * h1->GetYaxis()->GetBinWidth( iy ) * bgDensity;
          
          if (k != -6 && bgNum < 1.) bgNum = 1.;
          //if (k == -3 && bgNum < 4.) bgNum = 4.;
          //if (k != -6 && bgNum < 2.) bgNum = 2.;
          //binNum -= bgNum; // subtrackt 1 BG only
          binNum -= (bgNum+2*sqrt(bgNum)); //sbutrackt BG+2sigmaBF
          //binNum -= (2*bgNum); // subtrackt 2 BG
          if (binNum < 0) binNum = 0;
          if (bgFitQuality[phiSect] == 1 || flag_ExcludeBadFitSector == 0) h1->Fill( x, y, binNum ); // fill only good phi sectors

           // calculate y Derivative in 2D, we use 2D histo without BG subtraction
           // formula is correct if all bins has the same width. If it is not true then you have to introduce bin width in this formula!
           if (ix>1 && Int_t(ix)<numBinsX && iy>1 && Int_t(iy)<numBinsY){
              Double_t u0 = h->GetBinContent( ix-1, iy-1 ) + 2*h->GetBinContent( ix, iy-1 ) + h->GetBinContent( ix+1, iy-1 );
              Double_t u2 = h->GetBinContent( ix-1, iy+1 ) + 2*h->GetBinContent( ix, iy+1 ) + h->GetBinContent( ix+1, iy+1 );
              Double_t fyDer2D = u2-u0;// calculate derivative at iy (y1) point
              // revert in negative y plain:
              if (y < 0) fyDer2D = -fyDer2D;
              // only fit the positive derivatives to measure the inner side of the pixel support rails
              if (FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRails")
                 {
                 if (fyDer2D < 0) fyDer2D = 0;
                 }
              // only fit the negative derivatives to measure the outer side of the pixel support rails
              if (FitObject == "PixelSupportRailsNegative")
                 {
                 if (fyDer2D > 0) fyDer2D = 0;
                 if (fyDer2D < 0) fyDer2D = -fyDer2D;
                 }

              hYderivative2D -> Fill (x, y, fyDer2D);

              Double_t u0x = h->GetBinContent( ix-1, iy-1 ) + 2*h->GetBinContent( ix-1, iy ) + h->GetBinContent( ix-1, iy+1 );
              Double_t u2x = h->GetBinContent( ix+1, iy-1 ) + 2*h->GetBinContent( ix+1, iy ) + h->GetBinContent( ix+1, iy+1 );
              Double_t fxDer2D = u2x-u0x;// calculate derivative at iy (y1) point
              // revert in negative y plain:
              if (x < 0) fxDer2D = -fxDer2D;
              hXderivative2D -> Fill (x, y, fxDer2D);
              }


        }//end rc cut in signal region
      } // end ix cycle
      //std::cout << "iy = " << iy << "   Xmax_int = " << Xmax_int << "   Xmin_int = " << Xmin_int << "   y Derivative = " << (Xmax_int-Xmin_int)/Ywidth << std::endl; 
      Double_t Der = (Xmax_int-Xmin_int)/Ywidth;
      if(yRailTopDer < Der) {yRailTopDer = Der; yRailTop = iy;}
      if(yRailBottomDer > Der) {yRailBottomDer = Der; yRailBottom = iy;}
      if(Int_t(iy) < numBinsY) hYderivative -> SetBinContent (iy, Der);
    } // end iy cycle
    std::cout << " yRailTop = " << hYderivative->GetXaxis()->GetBinCenter(yRailTop) << " +- " << hYderivative->GetXaxis()->GetBinWidth(yRailTop)/2. << std::endl;
    std::cout << " yRailBottom = " << hYderivative -> GetXaxis()->GetBinCenter(yRailBottom ) << " +- " << hYderivative->GetXaxis()->GetBinWidth(yRailBottom)/2. << std::endl;

    /// Step 5: fit the distribution

    //h1->SetMinimum(1);
    h1->SetStats(0);
    //h1->SetStats(1);
    h = h1;
    // don't plot "0" at z axis
    Double_t MaxZh = h->GetMaximum();
    cout << "******** Maximum Z value for h = " << MaxZh << endl;
    h->GetZaxis()->SetRangeUser(0.01, MaxZh);


    /// par[0] = R
    /// par[1] = x0
    /// par[2] = y0

    TVirtualFitter::SetDefaultFitter("Minuit");
    //TVirtualFitter::SetPrecision(1.E-9);

    // Here is where everything but the plus and minus sides of the pixel shield is fit with a circle
    // Create the Draw fitter
    TVirtualFitter* fitterDraw;
    fitterDraw = TVirtualFitter::Fitter( 0, 4 );
    // Create the general fitter
    //TVirtualFitter* fitter;
    //fitter = TVirtualFitter::Fitter( 0, 3 );
    if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport" || FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative")
    //if((FitObject != "PixelShieldPlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportPlus" && FitObject != "PixelSupportEllipse") && FitObject != "PixelSupportMinus")
      {
      //                                                  npar
      // Set the function that the fitter will use and set the parameters
      fitterDraw = TVirtualFitter::Fitter( 0, 3 );
      fitterDraw->SetFCN( chiSquareFunc );
      fitterDraw->SetParameter( 0,  "R",   r0, 0.01, RSmin, RSmax ); // in cm
      fitterDraw->SetParameter( 1, "x0",   x0, 0.01, -0.6, 0.6 ); // in cm
      fitterDraw->SetParameter( 2, "y0",   y0, 0.01, -0.6, 0.6 ); // in cm
      //   fitterDraw->FixParameter(1); fitterDraw->FixParameter(2); 


      //fitterDraw->SetParameter( 0,  "R", 2.932, 0.01, 2.6, 3.3 );
      //fitterDraw->FixParameter( 2 );
      //fitterDraw->FixParameter( 1 );
      //fitterDraw->FixParameter( 0 );
      Double_t arglist[10] = {0.};
      // Execute the fit

      //cout << "======    Start Fit of Inner Tracker with Circle" << endl;
      if(FitObject != "PixelSupportRails" && FitObject != "PixelSupportRailsPositive" && FitObject != "PixelSupportRailsNegative") fitterDraw->ExecuteCommand( "MIGRAD", arglist, 0 );
      //cout << "======    End Fit of Inner Tracker with Circle" << endl;
      }

    //if small slice, then rebin histo for better view
    //if(k > -6 && k < 5) h->Rebin2D(5,5);
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    //if ( FitObject == "PixelSupportEllipse" || FitObject == "PixelShield2Arcs" ){
       hEmpty -> Draw();
       h->Draw("COLZsame");
       //h->Draw("COLZ");
    //}
    //else {
    //   h->Draw("col");
    //}

    //TGraph* gr_arc;
    //Double_t x_arc0[1], y_arc0[1];
    x_arc0[0] = 0.;
    y_arc0[0] = 0.;
    gr_arc = new TGraph(1,x_arc0,y_arc0);
    gr_arc->SetMarkerStyle(22);
    gr_arc->SetMarkerSize(2);
    gr_arc->SetMarkerColor(kRed);

    // Fit the plus side of the pixel support with a semicircle
    //TVirtualFitter* fitterDraw;
    //fitterDraw = fitter;
    TGraph* gr_arcSupportPlus = gr_arc;
    if ( FitObject == "PixelSupportPlus")
       {
       fitterDraw = TVirtualFitter::Fitter( 0, 3 );
       fitterDraw->SetFCN(funPixelSupportPlus);
       // set the parameters
       fitterDraw->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, -0.6,  0.6 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.6,  0.6 ); // in cm

       Double_t arglistArcPlus[10] = {0.};
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );

       // Draw the arc of the fit
       TArc* arcSupportPlus = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), -90, 90);
       arcSupportPlus->SetFillStyle(0);
       arcSupportPlus->SetLineColor(kRed);
       arcSupportPlus->SetLineWidth(3);
       arcSupportPlus->Draw("same");
       Double_t x_arcSupportPlus[1], y_arcSupportPlus[1];
       x_arcSupportPlus[0] = fitterDraw->GetParameter(1);
       y_arcSupportPlus[0] = fitterDraw->GetParameter(2);
       gr_arcSupportPlus = new TGraph(1,x_arcSupportPlus,y_arcSupportPlus);
       gr_arcSupportPlus->SetMarkerStyle(22);
       gr_arcSupportPlus->SetMarkerSize(2);
       gr_arcSupportPlus->SetMarkerColor(kRed);
       gr_arcSupportPlus->Draw("P");
       fitterDraw = fitterDraw;
       }


    // Fit the minus side of the pixel support with a semicircle
    //TVirtualFitter* fitterSupportMinus;
    //fitterSupportMinus = fitter;
    TGraph* gr_arcSupportMinus = gr_arc;
    TGraph* gr_arcSupportMinusPlus = gr_arc;
    if ( FitObject == "PixelSupportMinus")
       {
       fitterDraw = TVirtualFitter::Fitter( 0, 3 );
       fitterDraw->SetFCN(funPixelSupportMinus);
       // set the parameters
       fitterDraw->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, -0.6,  0.6 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.6,  0.6 ); // in cm

       Double_t arglistArcPlus[10] = {0.};
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );

       // Draw the arc for the minus side.
       TArc* arcSupportMinus = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), 90, 270);
       arcSupportMinus->SetFillStyle(0);
       arcSupportMinus->SetLineColor(kBlack);
       arcSupportMinus->SetLineWidth(3);
       arcSupportMinus->Draw("same");
       Double_t x_arcSupportMinus[1], y_arcSupportMinus[1];
       x_arcSupportMinus[0] = fitterDraw->GetParameter(1);
       y_arcSupportMinus[0] = fitterDraw->GetParameter(2);
       gr_arcSupportMinus = new TGraph(1,x_arcSupportMinus,y_arcSupportMinus);
       gr_arcSupportMinus->SetMarkerStyle(20);
       gr_arcSupportMinus->SetMarkerSize(2);
       gr_arcSupportMinus->SetMarkerColor(kBlack);
       gr_arcSupportMinus->Draw("P");

       // Draw the arc for the plus side using predetermined values for the parameters
       TArc* arcSupportMinusPlus = new TArc( x0_PixelSupportPlus, y0_PixelSupportPlus, r0_PixelSupportPlus, -90, 90);
       arcSupportMinusPlus->SetFillStyle(0);
       arcSupportMinusPlus->SetLineColor(kRed);
       arcSupportMinusPlus->SetLineWidth(3);
       arcSupportMinusPlus->Draw("same");
       Double_t x_arcSupportPlus[1], y_arcSupportPlus[1];
       x_arcSupportPlus[0] = x0_PixelSupportPlus;
       y_arcSupportPlus[0] = y0_PixelSupportPlus;
       gr_arcSupportMinusPlus = new TGraph(1,x_arcSupportPlus,y_arcSupportPlus);
       gr_arcSupportMinusPlus->SetMarkerStyle(22);
       gr_arcSupportMinusPlus->SetMarkerSize(2);
       gr_arcSupportMinusPlus->SetMarkerColor(kRed);
       gr_arcSupportMinusPlus->Draw("P");
       fitterDraw = fitterDraw;
       }

    //TVirtualFitter* fitterShield2Ellipses;
    //fitterShield2Ellipses = fitter;
    TGraph* gr_ellipseShieldPlus = gr_arc;
    TGraph* gr_ellipseShieldFar = gr_arc;
    if (FitObject == "PixelShield2Ellipses")
       {
       fitterDraw = TVirtualFitter::Fitter(0,6);
       fitterDraw->SetFCN(funPixelShield2Ellipses);
       //std::cout << "**********Setting Parameters**********" << std::endl;
       fitterDraw->SetParameter( 0, "r0_x", r0, 0.01, RSmin+0.1, RSmax-0.16 ); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, -0.4, 0.5 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.4, 0.4 ); // in cm
       fitterDraw->SetParameter( 3, "r0_y", r0_y, 0.01, RSmin, RSmax ); // in cm
       //fitterDraw->SetParameter( 3, "r0_y", r0_y, 0.01, -0.05, 0.05 ); // in cm
       fitterDraw->SetParameter( 4, "x0_Far", x0_Far, 0.01, -0.4, 0.4 ); // in cm
       fitterDraw->SetParameter( 5, "y0_Far", y0_Far, 0.01, -0.4, 0.4 ); // in cm
       fitterDraw->FixParameter(0);
       //fitterDraw->FixParameter(3);
       //fitterDraw->FixParameter(4);
       //fitterDraw->FixParameter(5);
       Double_t arglistArcEllipse[10] = {0.};
       //std::cout << "**********About to Fit**********" << std::endl;
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );
       //std::cout << "*********Done Fitting**********" << std::endl;

       TEllipse* ellipseShieldPlus = new TEllipse( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), fitterDraw->GetParameter(3), -90, 90);
       ellipseShieldPlus->SetFillStyle(0);
       ellipseShieldPlus->SetLineColor(kRed);
       ellipseShieldPlus->SetLineWidth(3);
       ellipseShieldPlus->Draw("same");

       TEllipse* ellipseShieldFar = new TEllipse( fitterDraw->GetParameter(4), fitterDraw->GetParameter(5), fitterDraw->GetParameter(0), fitterDraw->GetParameter(3), 90, 270);
       ellipseShieldFar->SetFillStyle(0);
       ellipseShieldFar->SetLineColor(kBlack);
       ellipseShieldFar->SetLineWidth(3);
       ellipseShieldFar->Draw("same");

       Double_t x_ellipseShieldPlus[1], y_ellipseShieldPlus[1];
       x_ellipseShieldPlus[0] = fitterDraw->GetParameter(1);
       y_ellipseShieldPlus[0] = fitterDraw->GetParameter(2);

       gr_ellipseShieldPlus = new TGraph(1,x_ellipseShieldPlus,y_ellipseShieldPlus);
       gr_ellipseShieldPlus->SetMarkerStyle(22);
       gr_ellipseShieldPlus->SetMarkerSize(2);
       gr_ellipseShieldPlus->SetMarkerColor(kRed);
       gr_ellipseShieldPlus->Draw("P");

       Double_t x_ellipseShieldFar[1], y_ellipseShieldFar[1];
       x_ellipseShieldFar[0] = fitterDraw->GetParameter(4);
       y_ellipseShieldFar[0] = fitterDraw->GetParameter(5);
       gr_ellipseShieldFar = new TGraph(1,x_ellipseShieldFar,y_ellipseShieldFar);
       gr_ellipseShieldFar->SetMarkerStyle(20);
       gr_ellipseShieldFar->SetMarkerSize(2);
       gr_ellipseShieldFar->SetMarkerColor(kBlack);
       gr_ellipseShieldFar->Draw("P");

       }

    // fit the pixel shield with 2 semi-circles
    TGraph* gr_ArcShieldPlus = gr_arc;
    TGraph* gr_ArcShieldFar = gr_arc;
    TArc* ArcShieldFar =  new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), 90, 270);
    TArc* ArcShieldPlus = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), -90, 90);
    if (FitObject == "PixelShield2Arcs")
       {
       fitterDraw = TVirtualFitter::Fitter(0,5);
       fitterDraw->SetFCN(funPixelShield2Arcs);
       //std::cout << "**********Setting Parameters**********" << std::endl;
       //fitterDraw->SetParameter( 0, "r0", r0, 0.01, RSmin+0.1, RSmax-0.16 ); // in cm
       fitterDraw->SetParameter( 0, "r0", r0, 0.01, RSmin, RSmax); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, -0.3, 0.1 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.3, 0.1 ); // in cm
       fitterDraw->SetParameter( 3, "x0_Far", x0_Far, 0.01, -0.1, 0.3 ); // in cm
       if (k == 4)fitterDraw->SetParameter( 3, "x0_Far", x0_Far, 0.01, -0.3, 0.3 ); // in cm
       fitterDraw->SetParameter( 4, "y0_Far", y0_Far, 0.01, -0.3, 0.1 ); // in cm
       //fitterDraw->FixParameter(0);
       //fitterDraw->FixParameter(0);
       //fitterDraw->FixParameter(2);
       //fitterDraw->FixParameter(4);
       //if(k>-5 && k<6)fitterDraw->FixParameter(0);
       //if(k>-6 && k<6)fitterDraw->FixParameter(2);
       //if(k>-6 && k<6)fitterDraw->FixParameter(4);
       //if(k>-6 && k<6)fitterDraw->FixParameter(1);
       //if(k>-6 && k<6)fitterDraw->FixParameter(2);
       Double_t arglistArcEllipse[10] = {0.};
       //std::cout << "**********About to Fit**********" << std::endl;
       //fitterDraw->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );
       //fitterDraw->ExecuteCommand( "MIGRADImporved", arglistArcEllipse, 0 );
       //fitterDraw->ExecuteCommand( "Minimize", arglistArcEllipse, 0 );
       //fitterDraw->ExecuteCommand( "Seek", arglistArcEllipse, 0 );
       //fitterDraw->ExecuteCommand( "Simplex", arglistArcEllipse, 0 );
       //fitterDraw->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );
       //std::cout << "*********Done Fitting**********" << std::endl;

       ArcShieldPlus = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), -90, 90);
       ArcShieldPlus->SetFillStyle(0);
       ArcShieldPlus->SetLineColor(kRed);
       ArcShieldPlus->SetLineWidth(3);
       ArcShieldPlus->Draw("same");

       ArcShieldFar = new TArc( fitterDraw->GetParameter(3), fitterDraw->GetParameter(4), fitterDraw->GetParameter(0), 90, 270);
       ArcShieldFar->SetFillStyle(0);
       ArcShieldFar->SetLineColor(kBlack);
       ArcShieldFar->SetLineWidth(3);
       ArcShieldFar->Draw("same");

       Double_t x_ArcShieldPlus[1], y_ArcShieldPlus[1];
       x_ArcShieldPlus[0] = fitterDraw->GetParameter(1);
       y_ArcShieldPlus[0] = fitterDraw->GetParameter(2);

       gr_ArcShieldPlus = new TGraph(1,x_ArcShieldPlus,y_ArcShieldPlus);
       // set to triangle
       gr_ArcShieldPlus->SetMarkerStyle(22);
       gr_ArcShieldPlus->SetMarkerSize(2);
       gr_ArcShieldPlus->SetMarkerColor(kRed);
       gr_ArcShieldPlus->Draw("P");

       Double_t x_ArcShieldFar[1], y_ArcShieldFar[1];
       x_ArcShieldFar[0] = fitterDraw->GetParameter(3);
       y_ArcShieldFar[0] = fitterDraw->GetParameter(4);
       gr_ArcShieldFar = new TGraph(1,x_ArcShieldFar,y_ArcShieldFar);
       // set to upside down triangle
       gr_ArcShieldFar->SetMarkerStyle(23);
       gr_ArcShieldFar->SetMarkerSize(2);
       gr_ArcShieldFar->SetMarkerColor(kBlack);
       gr_ArcShieldFar->Draw("P");

       }
    cout << "======  TEST  1 seg. vio. " << endl;

    // fit the pixel support with an ellipse
    //TVirtualFitter* fitterSupportEllipse;
    //fitterSupportEllipse = fitter;
    TGraph* gr_ellipseSupport = gr_arc;
    if ( FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
       {
       fitterDraw = TVirtualFitter::Fitter( 0, 4 );
       fitterDraw->SetFCN(funPixelSupportEllipse);
       // set parameters for the pixel support ellipse fit
       std::cout << "********** Setting Parameters **********" << std::endl;
       fitterDraw->SetParameter( 0, "r0_x", r0, 0.01, RSmin, RSmax ); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, -0.3,  0.3 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.6,  0.6 ); // in cm
       fitterDraw->SetParameter( 3, "r0_y", r0_y, 0.01, RSmin, RSmax ); // in cm
       //fitterDraw->FixParameter(0);
       //fitterDraw->FixParameter(1);
       //fitterDraw->FixParameter(3); 
       //fitterDraw->FixParameter(2); 

       //std::cout << "Fitting Ellipse" << std::endl;
       Double_t arglistArcEllipse[10] = {0.};
       std::cout << "********** About to Fit **********" << std::endl;
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );

       std::cout << "********** Drawing Ellipse **********" << std::endl;
       // draw the ellipse
       TEllipse* ellipseSupport = new TEllipse( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0),(fitterDraw->GetParameter(3)));
       ellipseSupport->SetFillStyle(0);
       ellipseSupport->SetLineColor(kRed);
       ellipseSupport->SetLineWidth(3);
       ellipseSupport->Draw("same");
       Double_t x_ellipseSupport[1], y_ellipseSupport[1];
       x_ellipseSupport[0] = fitterDraw->GetParameter(1);
       y_ellipseSupport[0] = fitterDraw->GetParameter(2);

       gr_ellipseSupport = new TGraph(1,x_ellipseSupport,y_ellipseSupport);
       gr_ellipseSupport->SetMarkerStyle(22);
       gr_ellipseSupport->SetMarkerSize(1.5);
       gr_ellipseSupport->SetMarkerColor(kRed);
       gr_ellipseSupport->Draw("P");
       std::cout << "********** Done Drawing Ellipse **********" << std::endl;
       }

    cout << "======  TEST  2 seg. vio. " << endl;
    // Here is where the plus semicircle of the pixel shield is fit

 
    //TVirtualFitter* fitterArcPlus ;
    //fitterArcPlus = fitter ;
    TGraph* gr_arcPlus = gr_arc;
    if ( FitObject == "PixelShieldPlus")
       {
       // create the fitter, set the function that it will use,  and set the parameters
       fitterDraw = TVirtualFitter::Fitter( 0, 3 );
       fitterDraw->SetFCN(funArcPlus);
       fitterDraw->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, -0.3, 0.1 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.3,  0.1 ); // in cm

       Double_t arglistArcPlus[10] = {0.};
       // Execute the fit
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );

       // Draw an arc from -90 degrees to 90 degrees using the parameters of the fit
       TArc* arcPlus = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), -90, 90);
       arcPlus->SetFillStyle(0);
       arcPlus->SetLineColor(kRed);
       arcPlus->SetLineWidth(3);
       arcPlus->Draw("same");
       Double_t x_arcPlus[1], y_arcPlus[1];
       x_arcPlus[0] = fitterDraw->GetParameter(1);
       y_arcPlus[0] = fitterDraw->GetParameter(2);
       gr_arcPlus = new TGraph(1,x_arcPlus,y_arcPlus);
       gr_arcPlus->SetMarkerStyle(22);
       gr_arcPlus->SetMarkerSize(2);
       gr_arcPlus->SetMarkerColor(kRed);
       gr_arcPlus->Draw("P");
       }

    // Here is where the minus semicircle of the pixel shield is fit
    //TVirtualFitter* fitterArcMinus ;
    //fitterArcMinus = fitter ;
    TGraph* gr_arcMinus = gr_arc;
    TGraph* gr_arcMinusPlus = gr_arc;
    if (FitObject == "PixelShieldMinus")
       {
       fitterDraw = TVirtualFitter::Fitter( 0, 3 );
       fitterDraw->SetFCN(funArcMinus);
       // create the fitter, set the function that it will use, and set the parameters
       fitterDraw->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterDraw->SetParameter( 1, "x0", x0, 0.01, 0.,  0.1 ); // in cm
       fitterDraw->SetParameter( 2, "y0", y0, 0.01, -0.15,  -0.05 ); // in cm
       
       Double_t arglistArcPlus[10] = {0.};
       // Execute the fit
       fitterDraw->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );
       
       // Draw an arc from 90 degrees to 270 degrees using the parameters from the fit
       TArc* arcMinus = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0), 90, 270);
       arcMinus->SetFillStyle(0);
       arcMinus->SetLineColor(kBlack);
       arcMinus->SetLineWidth(3);
       arcMinus->Draw("same"); 
       Double_t x_arcMinus[1], y_arcMinus[1];
       x_arcMinus[0] = fitterDraw->GetParameter(1);
       y_arcMinus[0] = fitterDraw->GetParameter(2);
       gr_arcMinus = new TGraph(1,x_arcMinus,y_arcMinus);
       gr_arcMinus->SetMarkerStyle(20);
       gr_arcMinus->SetMarkerSize(2);
       gr_arcMinus->SetMarkerColor(kBlack);
       gr_arcMinus->Draw("P");
       
       // Draw an arc from -90 degrees to 90 degrees using previously determined values from the fit for the plus side of the pixel shield
       TArc* arcMinusPlus = new TArc( x0_PixelShieldPlus, y0_PixelShieldPlus, r0_PixelShieldPlus, -90, 90);
       arcMinusPlus->SetFillStyle(0);
       arcMinusPlus->SetLineColor(kRed);
       arcMinusPlus->SetLineWidth(3);
       arcMinusPlus->Draw("same"); 
       Double_t x_arcMinusPlus[1], y_arcMinusPlus[1];
       x_arcMinusPlus[0] = x0_PixelShieldPlus;
       y_arcMinusPlus[0] = y0_PixelShieldPlus;
       gr_arcMinusPlus = new TGraph(1,x_arcMinusPlus,y_arcMinusPlus);
       gr_arcMinusPlus->SetMarkerStyle(22);
       gr_arcMinusPlus->SetMarkerSize(2);
       gr_arcMinusPlus->SetMarkerColor(kRed);
       gr_arcMinusPlus->Draw("P");
       }

    cout << "======  TEST 3 seg. vio. " << endl;
    // If the object is not the plus or minus sides of the pixel shield, draw a circle using the parameters from the fit
     TArc* arc = new TArc( fitterDraw->GetParameter(1), fitterDraw->GetParameter(2), fitterDraw->GetParameter(0) );
      arc->SetFillStyle(0);
      arc->SetLineColor(kRed);
      arc->SetLineWidth(3);
    if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport" || FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative")
    //if ( (FitObject != "PixelShieldPlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportPlus") /*&& FitObject != "PixelSupportEllipse"*/ && FitObject != "PixelSupportMinus")
      {
      cout << "======    fitterDraw->GetParameter(1) = " << fitterDraw->GetParameter(1) << endl;
      arc->Draw("same");
      Double_t x_arc[1], y_arc[1];
      x_arc[0] = fitterDraw->GetParameter(1);
      y_arc[0] = fitterDraw->GetParameter(2);
      gr_arc = new TGraph(1,x_arc,y_arc);
      gr_arc->SetMarkerStyle(22);
      gr_arc->SetMarkerSize(2);
      gr_arc->SetMarkerColor(kRed);
      gr_arc->Draw("P");
      }

    TGraph* gr_arc0;
    x_arc0[0] = 0.;
    y_arc0[0] = 0.;
    gr_arc0 = new TGraph(1,x_arc0,y_arc0);
    gr_arc0->SetMarkerStyle(20);
    gr_arc0->SetMarkerSize(2);
    gr_arc0->SetMarkerColor(kBlue);
    if(FitObject !="BeamPipe" && FitObject != "PixelShield2Arcs" && FitObject != "PixelSupportEllipse")gr_arc0->Draw("P");
    // draw the (0,0) point for everything but the pixel support fit with an ellipse
    if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShield2Ellipses"  && FitObject != "PixelShield2Arcs" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
      {
      //plot circle with center at (0.0)
      TArc* arc0 = new TArc( 0., 0., fitterDraw->GetParameter(0) );
      arc0->SetFillStyle(0);
      arc0->SetLineColor(kBlue);
      arc0->SetLineWidth(3);
      //gr_arc0->Draw("P");
      //arc0->Draw("same");
      }

    //if(FitObject == "PixelShield2Ellipses")
    //  {
    //  // plot ellipse with center at (0,0)
    //  TArc* arc0 = new TArc( 0., 0., fitterDraw->GetParameter(0) );
    //  arc0->SetFillStyle(0);
    //  arc0->SetLineColor(kBlue);
    //  arc0->SetLineWidth(3);
    // gr_arc0->Draw("P");
    //  }

    // draw the (0,0) point for the pixel support fit with an ellipse
    if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
     {
      std::cout << "********** Drawing Center **********" << std::endl;
      //plot circle with center at (0.0)
      TArc* arc0 = new TArc( 0., 0., fitterDraw->GetParameter(0) );
      arc0->SetFillStyle(0);
      arc0->SetLineColor(kBlue);
      arc0->SetLineWidth(3);
      //arc0->Draw("same");
      //gr_arc0->Draw("P");
      std::cout << "********** Done Drawing Center **********" << std::endl;
     }

    std::cout << "About to update plots" << std::endl;
    cPlots->Update();
    std::cout << "Done updating plots" << std::endl;

    TPaveStats* s = (TPaveStats*)h0->GetListOfFunctions()->FindObject("stats");
    x1L = s->GetX1NDC();
    x2L = s->GetX2NDC();
    y1L = s->GetY1NDC();
    y2L = s->GetY2NDC();

    cout << "======  TEST 4 seg. vio. " << endl;
    // Create the stats box for everything that is not the minus side of the pixel shield,
    // the minus side of the pixel support, or the pixel support ellipse
    if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShield2Ellipses" && FitObject != "PixelShield2Arcs" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
      {
      //TPaveText* res = new TPaveText(x1L-0.01, y1L-0.22, x2L+0.02, y2L-0.40, "brNDC");
      //TPaveText* res = new TPaveText(/*x1L-*/0.0, /*y1L-*/0.0, /*x2L+*/0.2, /*y2L+*/0.40, "brNDC");
      //std::cout << "x1L = " << x1L << std::endl;
      //std::cout << "y1L = " << y1L << std::endl;
      //std::cout << "x2L = " << x2L << std::endl;
      //std::cout << "y2L = " << y2L << std::endl;

      std::ostringstream legRadius;
      if(fitterDraw->GetParError(0) >= ErrPrecision)legRadius << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legRadius << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys;

      std::ostringstream legCenter;
      if(fitterDraw->GetParError(1) >= ErrPrecision)legCenter << "#splitline{x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10 << "}";
      else legCenter << "#splitline{x_{0} (mm) \t = \t" << fixed << setprecision(2) <<  fitterDraw->GetParameter(1)*10 <<" #pm " << x_Sys*10 << "}";
      if(fitterDraw->GetParError(2) >= ErrPrecision)legCenter << "{y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10 << "}";
      else legCenter << "{y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10 << "}";

      latex_circle.DrawLatex(0.5, -2.9, legCenter.str().c_str());
      latex_circle.DrawLatex(-3.1, -2.7, legRadius.str().c_str());

      //latex_circle.DrawLatex(-8, -17, legCenter.str().c_str());
      //latex_circle.DrawLatex(-8, -13.7, legRadius.str().c_str());
      CMS_lumi( cPlots, iPeriod, iPos );
      //cout << " ======= cPlots->GetTopMargin() =  " << cPlots->GetTopMargin() << endl; 

      /*res->AddText(legCenter.str().c_str());
      res->AddText(legRadius.str().c_str());

      res->SetFillStyle(0);
      res->SetTextAlign(12);
      res->SetTextColor(kRed);
      res->SetLineColor(kRed);
      res->SetTextFont(42);
      res->Draw("same");*/
      }

    // Create the stats box for the pixel support ellipse fit
    if(FitObject == "PixelSupportEllipse" || FitObject == "BeamPipeEllipse" || FitObject == "PixelShieldEllipse")
      {

      std::ostringstream legRadius;
      if(fitterDraw->GetParError(0) >= ErrPrecision)legRadius << "#splitline{R_{x} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys << "}";
      else legRadius << "#splitline{R_{x} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys << "}";
      if(fitterDraw->GetParError(3) >= ErrPrecision)legRadius << "{R_{y} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(3) << " #pm " << fitterDraw->GetParError(3) << " #pm " << r_Sys << "}";
      else legRadius << "{R_{y} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(3) << " #pm " << r_Sys << "}";

      std::ostringstream legCenter;
      if(fitterDraw->GetParError(1) >= ErrPrecision)legCenter << "#splitline{x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10 << "}";
      else legCenter << "#splitline{x_{0} (mm) \t = \t" << fixed << setprecision(2) <<  fitterDraw->GetParameter(1)*10 <<" #pm " << x_Sys*10 << "}";
      if(fitterDraw->GetParError(2) >= ErrPrecision)legCenter << "{y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10 << "}";
      else legCenter << "{y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10 << "}";

      if(FitObject == "PixelSupportEllipse"){
         latex_circle.DrawLatex(4., -26., legCenter.str().c_str());
         latex_circle.DrawLatex(-27., -26., legRadius.str().c_str());
      }
      if(FitObject == "BeamPipeEllipse"){
         latex_circle.DrawLatex(0.5, -2.8, legCenter.str().c_str());
         latex_circle.DrawLatex(-3., -2.8, legRadius.str().c_str());
      }
      CMS_lumi( cPlots, iPeriod, iPos );

      }

    // Create the stats box for the pixel support ellipse fit
    if(FitObject == "PixelShield2Ellipses")
      {
      TPaveText* res = new TPaveText(x1L-0.01, y1L-0.32, x2L+0.02, y2L-0.40, "brNDC");
      std::ostringstream legEntry;

      legEntry.str("");
      if(fitterDraw->GetParError(0) >= ErrPrecision)legEntry << "r_{0}^{x} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legEntry << "r_{0}^{x} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(3) >= ErrPrecision)legEntry << "r_{0}^{y} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(3) << " #pm " << fitterDraw->GetParError(3) << " #pm " << r_Sys;
      //else legEntry << "r_{0}^{y} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) + fabs(fitterDraw->GetParameter(3)) << " #pm " << r_Sys;
      else legEntry << "r_{0}^{y} (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(3) << " #pm " << r_Sys;
      res->AddText( legEntry.str().c_str() );

      legEntry.str("");
      if(fitterDraw->GetParError(1) >= ErrPrecision) legEntry << "x_{0}^{near} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0}^{near} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(2) >= ErrPrecision) legEntry << "y_{0}^{near} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      else legEntry << "y_{0}^{near} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );

      legEntry.str("");
      if(fitterDraw->GetParError(4) >= ErrPrecision) legEntry << "x_{0}^{far} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(4)*10 << " #pm " << fitterDraw->GetParError(4)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0}^{far} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(4)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(5) >= ErrPrecision) legEntry << "y_{0}^{far} (mm) \t = \t" << fitterDraw->GetParameter(5)*10 << " #pm " << fitterDraw->GetParError(5)*10 << " #pm " << x_Sys*10;
      else legEntry << "y_{0}^{far} (mm) \t = \t" << fitterDraw->GetParameter(5)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );



      res->SetFillStyle(0);
      res->SetTextAlign(12);
      res->SetTextColor(kRed);
      res->SetLineColor(kRed);
      res->SetTextFont(42);
      res->Draw("same");
      }


    // Create the stats box for the pixel support ellipse fit
    if(FitObject == "PixelShield2Arcs")
      {

      std::ostringstream legRadius;
      if(fitterDraw->GetParError(0) >= r_Sys/3.)legRadius << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legRadius << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys;

      std::ostringstream legCenter;
      if(fitterDraw->GetParError(1) >= x_Sys/3.)legCenter << "#splitline{x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10 << "}";
      else legCenter << "#splitline{x_{0}^{near} (mm) \t = \t" << fixed << setprecision(2) <<  fitterDraw->GetParameter(1)*10 <<" #pm " << x_Sys*10 << "}";
      if(fitterDraw->GetParError(2) >= x_Sys/3.)legCenter << "{y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10 << "}";
      else legCenter << "{y_{0}^{near} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10 << "}";

      std::ostringstream legCenterFar;
      if(fitterDraw->GetParError(3) >= x_Sys/3.) legCenterFar << "#splitline{x_{0}^{far} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(3)*10 << " #pm " << fitterDraw->GetParError(3)*10 << " #pm " << x_Sys*10  << "}";
      else legCenterFar << "#splitline{x_{0}^{far} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(3)*10 << " #pm " << x_Sys*10  << "}";
      if(fitterDraw->GetParError(4) >= x_Sys/3.) legCenterFar << "{y_{0}^{far} (mm) \t = \t" << fitterDraw->GetParameter(4)*10 << " #pm " << fitterDraw->GetParError(4)*10 << " #pm " << x_Sys*10 << "}";
      else legCenterFar << "{y_{0}^{far} (mm) \t = \t" << fitterDraw->GetParameter(4)*10 << " #pm " << x_Sys*10 << "}";
      latex_circle.DrawLatex(0.5, -5.5, legCenter.str().c_str());
      latex_circle.DrawLatex(-5.5, -5.5, legCenterFar.str().c_str());
      latex_circle.DrawLatex(-2.5, -4.5, legRadius.str().c_str());
      if(k > -5 && k < 4) latex_circle.DrawLatex(2.5, 3.3,Form("%d<z<%d cm", k*5, (k+2)*5));
      if(k == -5 || k == 4) latex_circle.DrawLatex(2.5, 3.3,Form("%d < z < %d cm", k*5, (k+1)*5));
      CMS_lumi( cPlots, iPeriod, iPos );




      }



      // Format the 2D map for the pixel shield
      if(FitObject == "PixelShieldMinus")
      {
      // Create the stats box entries for the minus side
      TPaveText* resMinus = new TPaveText(x1L-0.01, y1L-0.32, x2L+0.02, y2L-0.50, "brNDC");
      std::ostringstream legEntry;
      legEntry.str("");
      if(fitterDraw->GetParError(0) >= ErrPrecision)legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys;
      resMinus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(1) >= ErrPrecision) legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << x_Sys*10;
      resMinus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(2) >= ErrPrecision) legEntry << "y_{0} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      else legEntry << "y_{0} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10;
      resMinus->AddText( legEntry.str().c_str() );
      resMinus->SetFillStyle(0);
      resMinus->SetTextAlign(12);
      resMinus->SetTextColor(kBlack);
      resMinus->SetLineColor(kBlack);
      resMinus->SetTextFont(42);
      resMinus->Draw("same");

      // Create the stats box entries for the plus side
      TPaveText* resPlus = new TPaveText(x1L-0.01, y1L-0.12, x2L+0.02, y2L-0.30, "brNDC");
      //std::ostringstream legEntry;
      legEntry.str("");
      if(fitterDraw->GetParError(0) >= ErrPrecision) legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << r0_PixelShieldPlus << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << r0_PixelShieldPlus << " #pm " << r_Sys;
      resPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(1) >= ErrPrecision) legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << x0_PixelShieldPlus*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << x0_PixelShieldPlus*10 << " #pm " << x_Sys*10;
      resPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(2) >= ErrPrecision) legEntry << "y_{0} (mm) \t = \t" << y0_PixelShieldPlus*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      else legEntry << "y_{0} (mm) \t = \t" << y0_PixelShieldPlus*10 << " #pm " << x_Sys*10;
      resPlus->AddText( legEntry.str().c_str() );
      resPlus->SetFillStyle(0);
      resPlus->SetTextAlign(12);
      resPlus->SetTextColor(kRed);
      resPlus->SetLineColor(kRed);
      resPlus->SetTextFont(42);
      resPlus->Draw("same");
      }
      if(FitObject == "PixelSupportMinus")
      {
      // Create the stats box entries for the minus side
      TPaveText* resSupportMinus = new TPaveText(x1L-0.01, y1L-0.32, x2L+0.02, y2L-0.50, "brNDC");
      std::ostringstream legEntry;
      legEntry.str("");
      legEntry << "R (cm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << x_Sys;
      resSupportMinus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      resSupportMinus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "y_{0} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      resSupportMinus->AddText( legEntry.str().c_str() );
      resSupportMinus->SetFillStyle(0);
      resSupportMinus->SetTextAlign(12);
      resSupportMinus->SetTextColor(kBlack);
      resSupportMinus->SetLineColor(kBlack);
      resSupportMinus->SetTextFont(42);
      resSupportMinus->Draw("same");

      // Create the stats box entries for the plus side
      TPaveText* resSupportPlus = new TPaveText(x1L-0.01, y1L-0.12, x2L+0.02, y2L-0.30, "brNDC");
      //std::ostringstream legEntry;
      legEntry.str("");
      legEntry << "R (cm) \t = \t" << fixed << setprecision(2) << r0_PixelSupportPlus << " #pm " << fitterDraw->GetParError(0) << " #pm " << x_Sys;
      resSupportPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << x0_PixelSupportPlus*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      resSupportPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "y_{0} (mm) \t = \t" << y0_PixelSupportPlus*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      resSupportPlus->AddText( legEntry.str().c_str() );
      resSupportPlus->SetFillStyle(0);
      resSupportPlus->SetTextAlign(12);
      resSupportPlus->SetTextColor(kRed);
      resSupportPlus->SetLineColor(kRed);
      resSupportPlus->SetTextFont(42);
      resSupportPlus->Draw("same");
      }

      // Create the legend for all 2D XY map plots, include (0,0) point
      //TLegend* legArc = new TLegend(0.75, 0.75, 0.95, 0.9, "");
      TLegend* legData = new TLegend(0.42, 0.70, 0.52, 0.82, "");
      TLegend* legArc = new TLegend(0.67, 0.69, 0.77, 0.81, "");
      if ( FitObject == "PixelSupportEllipse" || FitObject == "PixelShield2Arcs" ) legArc = new TLegend(0.65, 0.70, 0.75, 0.83, "");
      legArc->SetTextFont(42);
      legArc->SetTextSize(0.04*ScaleSize);
      legArc->SetFillColor(kWhite);
      legArc->SetTextColor(kBlack);
      legData->SetTextFont(42);
      legData->SetTextSize(0.04*ScaleSize);
      legData->SetFillColor(kWhite);
      legData->SetTextColor(kBlack);

      
      if(FitObject == "PixelShield2Arcs") {legData->AddEntry(arc,"Data 2018","");} 
      else {legArc->AddEntry(arc,"Data 2018","");}

      if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport") 
        {
        legArc->AddEntry(arc,"Circle fit","l");
        legArc->Draw("same");
        }
      if( FitObject == "PixelShield2Arcs"){ 
        legData->AddEntry(ArcShieldPlus,"Circle fit, near","l");
        legData->AddEntry(ArcShieldFar,"Circle fit, far","l");
        legData -> Draw("same");
      }

      if( FitObject == "PixelSupportEllipse") 
        legArc->AddEntry(arc,"Ellipse fit","l");

      if(FitObject !="BeamPipe" && FitObject != "PixelShield2Arcs" && FitObject != "PixelSupportEllipse")legArc->AddEntry(gr_arc0,"(0,0)","P");
      legArc->Draw("same");

      if( FitObject == "BeamPipe" || FitObject == "PixelShield2Arcs" || FitObject == "PixelSupportEllipse") {
         gr_BS->Draw("P");
         legArc->AddEntry(gr_BS,"Beam spot","P"); 
      }

      // Add entries according to the object that was fit
      if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport" || FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative")
        {
        legArc->AddEntry(gr_arc,"(x_{0}, y_{0})","P");
        legArc->Draw("same");
        //legArc->AddEntry(gr_arc,"(x_{0}, y_{0}) from fit","P");
        }

      if(FitObject == "PixelShieldPlus")
        {
        legArc->AddEntry(gr_arcPlus,"x_{0}, y_{0} from fit","P");
        }
      if(FitObject == "PixelShieldMinus")
        {
        // include entry for the plus side of the pixel shield since it will be superimposed on the same plot
        legArc->AddEntry(gr_arcMinus,"x_{0}, y_{0} for far","P");
        legArc->AddEntry(gr_arcMinusPlus,"x_{0}, y_{0} for near","P");
        }
      if(FitObject == "PixelSupportMinus")
        {
        legArc->AddEntry(gr_arcSupportMinus,"x_{0}, y_{0} for far","P");
        legArc->AddEntry(gr_arcSupportMinusPlus,"x_{0}, y_{0} for near","P");
        }
      if(FitObject == "PixelSupportEllipse")
        {
        legArc->AddEntry(gr_ellipseSupport,"(x_{0}, y_{0})","P");
        }
      if(FitObject == "PixelShield2Ellipses")
        {
        legArc->AddEntry(gr_ellipseShieldPlus,"(x_{0}^{near}, y_{0}^{near})", "P");
        legArc->AddEntry(gr_ellipseShieldFar,"(x_{0}^{far}, y_{0}^{far})", "P");
        }
      if(FitObject == "PixelShield2Arcs")
        {
        legArc->AddEntry(gr_ArcShieldPlus,"(x_{0}^{near}, y_{0}^{near})", "P");
        legArc->AddEntry(gr_ArcShieldFar,"(x_{0}^{far}, y_{0}^{far})", "P");
        }
      if(FitObject == "PixelShieldEllipse")
        {
        legArc->AddEntry(gr_ellipseSupport,"x_{0}, y_{0} from fit","P");
        }
      if(FitObject == "BeamPipeEllipse")
        {
        legArc->AddEntry(gr_ellipseSupport,"(x_{0}, y_{0})","P");
        }
    if ( k > -6 )
    {
      resZ[k+5] = 0.5*(k*5 + (k+1)*5);
      resR[k+5] = fitterDraw->GetParameter(0);
      errR[k+5] = fitterDraw->GetParError(0);
      resx0[k+5] = fitterDraw->GetParameter(1)*10;
      errx0[k+5] = fitterDraw->GetParError(1)*10;
      resy0[k+5] = fitterDraw->GetParameter(2)*10;
      errx0[k+5] = fitterDraw->GetParError(2)*10;
    }

    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Fit.pdf"));

      if(k> -6 && k < 6){
        if(k < 0)cPlots->SaveAs(Form("Plots/"+FitObject+"_Fit_m%d.png", -k));
        else cPlots->SaveAs(Form("Plots/"+FitObject+"_Fit_p%d.png", k));
      }
    else {
        cPlots->SaveAs(("Plots/"+FitObject+"_Fit.png"));
        cPlots->SaveAs(("Plots/"+FitObject+"_Fit.pdf"));
        cPlots->SaveAs(("Plots/"+FitObject+"_Fit.root"));
    }
    TFile* f = new TFile(("Plots/"+FitObject+"_Fit.root"), "UPDATE");

    h->Write("BEAM_PIPE");
    f->Close();
    //cPlots->Delete();
    //delete cPlots;

    // set the range for the rhophi plots
    if(FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse")
      {
      h_RhoPhi->GetYaxis()->SetRangeUser(Rmin, Rmax);
      }
    //if(FitObject == "PixelShield2Arcs") h_RhoPhi->GetYaxis()->SetRangeUser(3.4, Rmax);
    if(FitObject == "PixelSupportMinus" || FitObject == "PixelSupportEllipse")
      {
      h_RhoPhi->GetYaxis()->SetRangeUser(19, 23);
      }
    //h_RhoPhi->GetYaxis()->SetRangeUser(RSmin, RSmax);
    h_RhoPhi->Draw("colz");
    h_RhoPhi->GetYaxis()->SetTitleOffset(1.5);

    //TF1 *bpAlt = new TF1("bpAlt","sqrt((21.699*cos(x)-0.081)^2 + (21.699*sin(x)-0.345)^2)",-3.15,3.15);
    // Create function that will be plotted on the Rho-Phi plots, but not on the plots for the minus side of the pixel shield,
    // the minus side of the pixel support, and the ellipse fit for the pixel support
    TF1 *bpAlt = new TF1("bpAlt",func_ArcRhoPhi,-3.15,6.3,3);
    if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShield2Ellipses" && FitObject != "PixelShield2Arcs" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
      {
      // use parameters from the fitter
      bpAlt->SetParameter(0, fitterDraw->GetParameter(0));
      bpAlt->SetParameter(1, fitterDraw->GetParameter(1));
      bpAlt->SetParameter(2, fitterDraw->GetParameter(2));
      bpAlt->SetLineColor(kRed);
      bpAlt->SetLineWidth(3);
      bpAlt ->Draw("same");
      CMS_lumi( cPlots, iPeriod, 0 );

      TLegend* legArc_RhoPhi = new TLegend(0.65, 0.75, 0.82, 0.81, "");
      legArc_RhoPhi->SetTextFont(42);
      legArc_RhoPhi->SetTextSize(0.04*ScaleSize);
      legArc_RhoPhi->SetFillColor(kWhite);
      legArc_RhoPhi->SetTextColor(kBlack);
      if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport")
        {
        legArc_RhoPhi->AddEntry(arc,"Data 2018","");
        legArc_RhoPhi->AddEntry(arc,"Circle fit","l");
        }

      legArc_RhoPhi->Draw("same");



      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.pdf"));
      }

    // draw the ellipse in rhophi
    TF1 *bpEllipseAlt = new TF1("bpAlt",func_EllipseRhoPhi,-3.15,3.15,4);
    if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
      {
      // use parameters from the fitter
      bpEllipseAlt->SetParameter(0, fitterDraw->GetParameter(0));
      bpEllipseAlt->SetParameter(1, fitterDraw->GetParameter(1));
      bpEllipseAlt->SetParameter(2, fitterDraw->GetParameter(2));
      bpEllipseAlt->SetParameter(3, (fitterDraw->GetParameter(3)));
      bpEllipseAlt->SetLineColor(kRed);
      bpEllipseAlt->SetLineWidth(3);
      bpEllipseAlt ->Draw("same");
      CMS_lumi( cPlots, iPeriod, 0 );

      TLegend* legArc_RhoPhi = new TLegend(0.65, 0.75, 0.82, 0.81, "");
      legArc_RhoPhi->SetTextFont(42);
      legArc_RhoPhi->SetTextSize(0.04*ScaleSize);
      legArc_RhoPhi->SetFillColor(kWhite);
      legArc_RhoPhi->SetTextColor(kBlack);
      legArc_RhoPhi->AddEntry(arc,"Data 2018","");
      legArc_RhoPhi->AddEntry(arc,"Ellipse fit","l");

      legArc_RhoPhi->Draw("same");

      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.pdf"));
      }

    // Draw the ellipse in rhophi for the pixel shield plus
    TF1 *funShieldEllipseNear = new TF1("funShieldEllipseNear",func_EllipseRhoPhi,-1.575,1.575,4);
    TF1 *funShieldEllipseFar = new TF1("funShieldEllipseFar",func_EllipseRhoPhi,1.575,2*1.575,4);
    TF1 *funShieldEllipseFar2 = new TF1("funShieldEllipseFar2",func_EllipseRhoPhi,-2.*1.575,-1.575,4);
    if(FitObject == "PixelShield2Ellipses")
      {
      // use parameters from the fitter
      funShieldEllipseNear->SetParameter(0, fitterDraw->GetParameter(0));
      funShieldEllipseNear->SetParameter(1, fitterDraw->GetParameter(1));
      funShieldEllipseNear->SetParameter(2, fitterDraw->GetParameter(2));
      funShieldEllipseNear->SetParameter(3, fitterDraw->GetParameter(3));
      funShieldEllipseNear->SetLineColor(kRed);
      funShieldEllipseNear->SetLineWidth(3);
      funShieldEllipseNear->Draw("same");

      funShieldEllipseFar->SetParameter(0, fitterDraw->GetParameter(0));
      funShieldEllipseFar->SetParameter(1, fitterDraw->GetParameter(4));
      funShieldEllipseFar->SetParameter(2, fitterDraw->GetParameter(5));
      funShieldEllipseFar->SetParameter(3, fitterDraw->GetParameter(3));
      funShieldEllipseFar->SetLineColor(kBlack);
      funShieldEllipseFar->SetLineWidth(3);
      funShieldEllipseFar->Draw("same");

      funShieldEllipseFar2->SetParameter(0, fitterDraw->GetParameter(0));
      funShieldEllipseFar2->SetParameter(1, fitterDraw->GetParameter(4));
      funShieldEllipseFar2->SetParameter(2, fitterDraw->GetParameter(5));
      funShieldEllipseFar2->SetParameter(3, fitterDraw->GetParameter(3));
      funShieldEllipseFar2->SetLineColor(kBlack);
      funShieldEllipseFar2->SetLineWidth(3);
      funShieldEllipseFar2->Draw("same");


      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.pdf"));
      }

    // Draw the ellipse in rhophi for the pixel shield plus
    TF1 *funShieldArcNear = new TF1("funShieldArcNear",func_ArcRhoPhi,-1.575,1.575,4);
    TF1 *funShieldArcFar = new TF1("funShieldArcFar",func_ArcRhoPhi,1.575,2*1.575,4);
    TF1 *funShieldArcFar2 = new TF1("funShieldArcFar2",func_ArcRhoPhi,-2.*1.575,-1.575,4);
    if(FitObject == "PixelShield2Arcs")
    {
      // use parameters from the fitter
      funShieldArcNear->SetParameter(0, fitterDraw->GetParameter(0));
      funShieldArcNear->SetParameter(1, fitterDraw->GetParameter(1));
      funShieldArcNear->SetParameter(2, fitterDraw->GetParameter(2));
      funShieldArcNear->SetLineColor(kRed);
      funShieldArcNear->SetLineWidth(3);
      funShieldArcNear->Draw("same");

      funShieldArcFar->SetParameter(0, fitterDraw->GetParameter(0));
      funShieldArcFar->SetParameter(1, fitterDraw->GetParameter(3));
      funShieldArcFar->SetParameter(2, fitterDraw->GetParameter(4));
      funShieldArcFar->SetLineColor(kBlack);
      funShieldArcFar->SetLineWidth(3);
      funShieldArcFar->Draw("same");

      funShieldArcFar2->SetParameter(0, fitterDraw->GetParameter(0));
      funShieldArcFar2->SetParameter(1, fitterDraw->GetParameter(3));
      funShieldArcFar2->SetParameter(2, fitterDraw->GetParameter(4));
      funShieldArcFar2->SetLineColor(kBlack);
      funShieldArcFar2->SetLineWidth(3);
      funShieldArcFar2->Draw("same");

      CMS_lumi( cPlots, iPeriod, 0 );

      TLegend* legArc_RhoPhi = new TLegend(0.60, 0.75, 0.82, 0.84, "");
      if(k> -6 && k < 6) legArc_RhoPhi = new TLegend(0.58, 0.71, 0.82, 0.84, "");
      legArc_RhoPhi->SetTextFont(42);
      legArc_RhoPhi->SetTextSize(0.04*ScaleSize);
      legArc_RhoPhi->SetFillColor(kWhite);
      legArc_RhoPhi->SetTextColor(kBlack);
      legArc_RhoPhi->AddEntry(arc,"Data 2018","");
      if(k > -5 && k < 4) legArc_RhoPhi->AddEntry(arc,Form("%d<z<%d cm", k*5, (k+2)*5),""); 
      if(k == -5 || k == 4) legArc_RhoPhi->AddEntry(arc,Form("%d<z<%d cm", k*5, (k+1)*5),""); 
      legArc_RhoPhi->AddEntry(ArcShieldPlus,"Circle fit, near","l");
      legArc_RhoPhi->AddEntry(ArcShieldFar,"Circle fit, far","l");

      legArc_RhoPhi->Draw("same");

      cPlots->Update();
      if(k> -6 && k < 6){
        if(k < 0)cPlots->SaveAs(Form("Plots/"+FitObject+"_Fit_RhoPhi_m%d.png", -k));
        else cPlots->SaveAs(Form("Plots/"+FitObject+"_Fit_RhoPhi_p%d.png", k));
      }
      else {cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png")); cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.pdf"));}
    }





    // Create functions that will be plotted on the Rho-Phi plots for the minus side of the pixel shield
    // The functions for the minus side are split in two because the plot is centered on the plus side
    TF1 *bpAltMinus1 = new TF1("bpAlt",func_ArcRhoPhi,1.575, 3.15,3);
    TF1 *bpAltMinus2 = new TF1("bpAlt",func_ArcRhoPhi,-3.15, -1.575,3);
    TF1 *bpAltPlus = new TF1("bpAlt",func_ArcRhoPhi,-1.575, 1.575,3);
    if(FitObject == "PixelShieldMinus")
      {
      // set parameters for half of the minus side from the fitter
      bpAltMinus1->SetParameter(0, fitterDraw->GetParameter(0));
      bpAltMinus1->SetParameter(1, fitterDraw->GetParameter(1));
      bpAltMinus1->SetParameter(2, fitterDraw->GetParameter(2));
      bpAltMinus1->SetLineColor(kRed);
      bpAltMinus1->SetLineWidth(3);
      bpAltMinus1->Draw("same");
      
      // set parameters for the other half of the minus side from the fitter
      bpAltMinus2->SetParameter(0, fitterDraw->GetParameter(0));
      bpAltMinus2->SetParameter(1, fitterDraw->GetParameter(1));
      bpAltMinus2->SetParameter(2, fitterDraw->GetParameter(2));
      bpAltMinus2->SetLineColor(kRed);
      bpAltMinus2->SetLineWidth(3);
      bpAltMinus2->Draw("same");
      
      // set parameters for the plus side using stored values from the previous fit
      bpAltPlus->SetParameter(0, r0_PixelShieldPlus);
      bpAltPlus->SetParameter(1, x0_PixelShieldPlus);
      bpAltPlus->SetParameter(2, y0_PixelShieldPlus);
      bpAltPlus->SetLineColor(kRed);
      bpAltPlus->SetLineWidth(3);
      bpAltPlus->Draw("same");
      
      // save
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.pdf"));
      }

    // create the plots in rhophi for the pixel support minus side fit
    TF1 *bpAltSupportMinus1 = new TF1("bpAlt",func_ArcRhoPhi,1.575, 3.15,3);
    TF1 *bpAltSupportMinus2 = new TF1("bpAlt",func_ArcRhoPhi,-3.15, -1.575,3);
    TF1 *bpAltSupportPlus = new TF1("bpAlt",func_ArcRhoPhi,-1.575, 1.575,3);
    if(FitObject == "PixelSupportMinus")
      {
      // set parameters for half of the minus side from the fitter
      bpAltSupportMinus1->SetParameter(0, fitterDraw->GetParameter(0));
      bpAltSupportMinus1->SetParameter(1, fitterDraw->GetParameter(1));
      bpAltSupportMinus1->SetParameter(2, fitterDraw->GetParameter(2));
      bpAltSupportMinus1->SetLineColor(kRed);
      bpAltSupportMinus1->SetLineWidth(3);
      bpAltSupportMinus1->Draw("same");

      // set parameters for the other half of the minus side from the fitter
      bpAltSupportMinus2->SetParameter(0, fitterDraw->GetParameter(0));
      bpAltSupportMinus2->SetParameter(1, fitterDraw->GetParameter(1));
      bpAltSupportMinus2->SetParameter(2, fitterDraw->GetParameter(2));
      bpAltSupportMinus2->SetLineColor(kRed);
      bpAltSupportMinus2->SetLineWidth(3);
      bpAltSupportMinus2->Draw("same");

      // set parameters for the plus side using stored values from the previous fit
      bpAltSupportPlus->SetParameter(0, r0_PixelSupportPlus);
      bpAltSupportPlus->SetParameter(1, x0_PixelSupportPlus);
      bpAltSupportPlus->SetParameter(2, y0_PixelSupportPlus);
      bpAltSupportPlus->SetLineColor(kRed);
      bpAltSupportPlus->SetLineWidth(3);
      bpAltSupportPlus->Draw("same");

      // save
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.pdf"));
      }

   if (flag_Sys == 1)
       {
       // x variation
       // create the functions for the systematic variation of x, but not for the minus side of the pixel shield
       TF1 *bpAlt_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,6.3,3);
       TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,6.3,3);
       if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShield2Ellipses" && FitObject != "PixelShield2Arcs" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
         {
         // set parameters using values from the fitter
         bpAlt_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAlt_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpAlt_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAlt_xp->SetLineColor(kBlack);
         bpAlt_xp->SetLineWidth(3);
         bpAlt_xp ->Draw("same");

         //TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpAlt_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpAlt_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAlt_xm->SetLineColor(kBlack);
         bpAlt_xm->SetLineWidth(3);
         bpAlt_xm ->Draw("same");
         }

       // draw the x variation of the ellipse in rhophi
       TF1 *bpAltEllipse_xp = new TF1("bpAlt_xp",func_EllipseRhoPhi,-3.15,3.15,4);
       TF1 *bpAltEllipse_xm = new TF1("bpAlt_xm",func_EllipseRhoPhi,-3.15,3.15,4);
       if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
         {
         // set parameters using values from the fitter
         bpAltEllipse_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltEllipse_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpAltEllipse_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltEllipse_xp->SetParameter(3, (fitterDraw->GetParameter(3)));
         bpAltEllipse_xp->SetLineColor(kBlack);
         bpAltEllipse_xp->SetLineWidth(3);
         bpAltEllipse_xp->Draw("same");

         //TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,3.15,3);
         bpAltEllipse_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltEllipse_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpAltEllipse_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltEllipse_xm->SetParameter(3, (fitterDraw->GetParameter(3)));
         bpAltEllipse_xm->SetLineColor(kBlack);
         bpAltEllipse_xm->SetLineWidth(3);
         bpAltEllipse_xm->Draw("same");

         bpEllipseAlt->Draw("same");
         cPlots->Update();
         }

       TF1 *bpAltShieldEllipsePlus_xp = new TF1("bpAlt_xp",func_EllipseRhoPhi,-1.575,1.575,4);
       TF1 *bpAltShieldEllipsePlus_xm = new TF1("bpAlt_xm",func_EllipseRhoPhi,-1.575,1.575,4);
       if(FitObject == "PixelShield2Ellipses")
         {
         bpAltShieldEllipsePlus_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltShieldEllipsePlus_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpAltShieldEllipsePlus_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltShieldEllipsePlus_xp->SetParameter(3, fitterDraw->GetParameter(3));
         bpAltShieldEllipsePlus_xp->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_xp->SetLineWidth(3);
         bpAltShieldEllipsePlus_xp->Draw("same");

         bpAltShieldEllipsePlus_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltShieldEllipsePlus_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpAltShieldEllipsePlus_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltShieldEllipsePlus_xm->SetParameter(3, fitterDraw->GetParameter(3));
         bpAltShieldEllipsePlus_xm->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_xm->SetLineWidth(3);
         bpAltShieldEllipsePlus_xm->Draw("same");
         cPlots->Update();
         }

       // Create the functions for the x variation of the minus side of the pixel shield
       // The minus side is split in two because the plot centers on the plus side of the pixel shield
       TF1 *bpAltMinus1_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpAltMinus2_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpAltMinus1_xm = new TF1("bpAlt_xp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpAltMinus2_xm = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpAltPlus_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-1.575,1.575,3);
       TF1 *bpAltPlus_xm = new TF1("bpAlt_xp",func_ArcRhoPhi,-1.575,1.575,3);
       if(FitObject == "PixelShieldMinus")
         {
         // set the parameters for the positive deviation of half of the minus side
         bpAltMinus1_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus1_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpAltMinus1_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus1_xp->SetLineColor(kBlack);
         bpAltMinus1_xp->SetLineWidth(3);
         bpAltMinus1_xp ->Draw("same");

         // set the parameters for the positive deviation of the other half of the minus side
         bpAltMinus2_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus2_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpAltMinus2_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus2_xp->SetLineColor(kBlack);
         bpAltMinus2_xp->SetLineWidth(3);
         bpAltMinus2_xp ->Draw("same");

         // set the parameters for the negative deviation of the first half of the minus side
         bpAltMinus1_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus1_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpAltMinus1_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus1_xm->SetLineColor(kBlack);
         bpAltMinus1_xm->SetLineWidth(3);
         bpAltMinus1_xm ->Draw("same");

         // set the parameters for the negative deviation of the other half of the minus side
         bpAltMinus2_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus2_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpAltMinus2_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus2_xm->SetLineColor(kBlack);
         bpAltMinus2_xm->SetLineWidth(3);
         bpAltMinus2_xm ->Draw("same");

         // set the parameters for the positive deviation of the plus side
         bpAltPlus_xp->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_xp->SetParameter(1, x0_PixelShieldPlus+x_Sys);
         bpAltPlus_xp->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_xp->SetLineColor(kBlack);
         bpAltPlus_xp->SetLineWidth(3);
         bpAltPlus_xp ->Draw("same");

         // set the parameters for the negative deviation of the minus side
         bpAltPlus_xm->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_xm->SetParameter(1, x0_PixelShieldPlus-x_Sys);
         bpAltPlus_xm->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_xm->SetLineColor(kBlack);
         bpAltPlus_xm->SetLineWidth(3);
         bpAltPlus_xm->Draw("same");

         }

       // Create the functions for the x variation of the minus and plus side of the pixel support (semicircles)
       TF1 *bpSupportAltMinus1_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpSupportAltMinus2_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpSupportAltMinus1_xm = new TF1("bpAlt_xp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpSupportAltMinus2_xm = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpSupportAltPlus_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-1.575,1.575,3);
       TF1 *bpSupportAltPlus_xm = new TF1("bpAlt_xp",func_ArcRhoPhi,-1.575,1.575,3);
       if(FitObject == "PixelSupportMinus")
         {
         // set the parameters for the positive deviation of half of the minus side
         bpSupportAltMinus1_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus1_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpSupportAltMinus1_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus1_xp->SetLineColor(kBlack);
         bpSupportAltMinus1_xp->SetLineWidth(3);
         bpSupportAltMinus1_xp ->Draw("same");

         // set the parameters for the positive deviation of the other half of the minus side
         bpSupportAltMinus2_xp->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus2_xp->SetParameter(1, fitterDraw->GetParameter(1)+x_Sys);
         bpSupportAltMinus2_xp->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus2_xp->SetLineColor(kBlack);
         bpSupportAltMinus2_xp ->Draw("same");

         // set the parameters for the negative deviation of the first half of the minus side
         bpSupportAltMinus1_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus1_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpSupportAltMinus1_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus1_xm->SetLineColor(kBlack);
         bpSupportAltMinus1_xm->SetLineWidth(3);
         bpSupportAltMinus1_xm ->Draw("same");

         // set the parameters for the negative deviation of the other half of the minus side
         bpSupportAltMinus2_xm->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus2_xm->SetParameter(1, fitterDraw->GetParameter(1)-x_Sys);
         bpSupportAltMinus2_xm->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus2_xm->SetLineColor(kBlack);
         bpSupportAltMinus2_xm->SetLineWidth(3);
         bpSupportAltMinus2_xm ->Draw("same");

         // set the parameters for the positive deviation of the plus side
         bpSupportAltPlus_xp->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_xp->SetParameter(1, x0_PixelSupportPlus+x_Sys);
         bpSupportAltPlus_xp->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_xp->SetLineColor(kBlack);
         bpSupportAltPlus_xp->SetLineWidth(3);
         bpSupportAltPlus_xp ->Draw("same");

         // set the parameters for the negative deviation of the minus side
         bpSupportAltPlus_xm->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_xm->SetParameter(1, x0_PixelSupportPlus-x_Sys);
         bpSupportAltPlus_xm->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_xm->SetLineColor(kBlack);
         bpSupportAltPlus_xm->SetLineWidth(3);
         bpSupportAltPlus_xm->Draw("same");
         }

       // save plots
       cPlots->Update();
       cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi_sysX.png"));

       // y variation
       h_RhoPhi->Draw("colz");
       bpAlt ->Draw("same");

       // Create the functions for the systematic variation of y, but not for the minus side of the pixel shield 
       TF1 *bpAlt_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,-3.15,6.3,3);
       TF1 *bpAlt_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-3.15,6.3,3);
       if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShield2Ellipses" && FitObject != "PixelShield2Arcs"&& FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
         {
         // set parameters for the positive deviation
         bpAlt_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAlt_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAlt_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpAlt_yp->SetLineColor(kBlack);
         bpAlt_yp->SetLineWidth(3);
         bpAlt_yp ->Draw("same");
         
         // set parameters for the negative deviation
         //TF1 *bpAlt_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpAlt_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpAlt_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpAlt_ym->SetLineColor(kBlack);
         bpAlt_ym->SetLineWidth(3);
         bpAlt_ym ->Draw("same");
         }

       // draw the y variation of the pixel support ellipse in the rhophi plos
       TF1 *bpAltEllipse_yp = new TF1("bpAlt_yp",func_EllipseRhoPhi,-3.15,3.15,4);
       TF1 *bpAltEllipse_ym = new TF1("bpAlt_ym",func_EllipseRhoPhi,-3.15,3.15,4);
       if(FitObject == "PixelShieldEllipse" || FitObject == "PixelSupportEllipse" || FitObject == "BeamPipeEllipse")
         {
         // set parameters for the positive deviation
         bpAltEllipse_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltEllipse_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltEllipse_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpAltEllipse_yp->SetParameter(3, fitterDraw->GetParameter(3));
         bpAltEllipse_yp->SetLineColor(kBlack);
         bpAltEllipse_yp->SetLineWidth(3);
         bpAltEllipse_yp ->Draw("same");

         // set parameters for the negative deviation
         bpAltEllipse_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltEllipse_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltEllipse_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpAltEllipse_ym->SetParameter(3, fitterDraw->GetParameter(3));
         bpAltEllipse_ym->SetLineColor(kBlack);
         bpAltEllipse_ym->SetLineWidth(3);
         bpAltEllipse_ym ->Draw("same");

         bpEllipseAlt->Draw("same");
         cPlots->Update();
         }

       TF1 *bpAltShieldEllipsePlus_yp = new TF1("bpAlt_yp",func_EllipseRhoPhi,-1.575,1.575,4);
       TF1 *bpAltShieldEllipsePlus_ym = new TF1("bpAlt_ym",func_EllipseRhoPhi,-1.575,1.575,4);
       if(FitObject == "PixelShield2Ellipses")
         {
         // set parameters for the positive deviaiton
         bpAltShieldEllipsePlus_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltShieldEllipsePlus_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltShieldEllipsePlus_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpAltShieldEllipsePlus_yp->SetParameter(3, fitterDraw->GetParameter(3));
         bpAltShieldEllipsePlus_yp->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_yp->SetLineWidth(3);
         bpAltShieldEllipsePlus_yp->Draw("same");

         bpAltShieldEllipsePlus_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltShieldEllipsePlus_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltShieldEllipsePlus_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpAltShieldEllipsePlus_ym->SetParameter(3, fitterDraw->GetParameter(3));
         bpAltShieldEllipsePlus_ym->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_ym->SetLineWidth(3);
         bpAltShieldEllipsePlus_ym->Draw("same");

         funShieldEllipseNear->Draw("same");
         cPlots->Update();
         }

       // Create the functions for the systematic variation of y for the minus side of the pixel shield
       // The functions for the minus side are split in two because the plot centers on the plus side
       TF1 *bpAltMinus1_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpAltMinus2_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpAltMinus1_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpAltMinus2_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpAltPlus_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-1.575,1.575,3);
       TF1 *bpAltPlus_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,-1.575,1.575,3);
       if(FitObject == "PixelShieldMinus")
         {
         // set the parameters for the positive deviation of one of the halves of the minus side
         bpAltMinus1_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus1_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus1_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpAltMinus1_yp->SetLineColor(kBlack);
         bpAltMinus1_yp->SetLineWidth(3);
         bpAltMinus1_yp ->Draw("same");
         
         // set the parameters for the positive deviation of the other half of the minus side
         bpAltMinus2_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus2_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus2_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpAltMinus2_yp->SetLineColor(kBlack);
         bpAltMinus2_yp->SetLineWidth(3);
         bpAltMinus2_yp ->Draw("same");
         
         // set the parameters for the negative deviation of one of the halves of the minus side
         bpAltMinus1_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus1_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus1_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpAltMinus1_ym->SetLineColor(kBlack);
         bpAltMinus1_ym->SetLineWidth(3);
         bpAltMinus1_ym ->Draw("same");
         
         // set the parameters for the negative deviation of the other half of the minus side
         bpAltMinus2_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpAltMinus2_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus2_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpAltMinus2_ym->SetLineColor(kBlack);
         bpAltMinus2_ym->SetLineWidth(3);
         bpAltMinus2_ym ->Draw("same");
         
         // set the parameters for the positive deviation of the plus side
         bpAltPlus_yp->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_yp->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_yp->SetParameter(2, y0_PixelShieldPlus+x_Sys);
         bpAltPlus_yp->SetLineColor(kBlack);
         bpAltPlus_yp->SetLineWidth(3);
         bpAltPlus_yp ->Draw("same");
         
         // set the parameters for the negative deviation of the plus side
         bpAltPlus_ym->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_ym->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_ym->SetParameter(2, y0_PixelShieldPlus-x_Sys);
         bpAltPlus_ym->SetLineColor(kBlack);
         bpAltPlus_ym->SetLineWidth(3);
         bpAltPlus_ym ->Draw("same");
         
         // Draw the central functions
         bpAltMinus1->Draw("same");
         bpAltMinus2->Draw("same");
         bpAltPlus->Draw("same");
         }

       // Create the functions for the y deviation of the minus and plus side of the pixel support (semicircles)
       TF1 *bpSupportAltMinus1_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpSupportAltMinus2_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpSupportAltMinus1_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpSupportAltMinus2_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpSupportAltPlus_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-1.575,1.575,3);
       TF1 *bpSupportAltPlus_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,-1.575,1.575,3);
       if(FitObject == "PixelSupportMinus")
         {
         // set the parameters for the positive deviation of one of the halves of the minus side
         bpSupportAltMinus1_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus1_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus1_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpSupportAltMinus1_yp->SetLineColor(kBlack);
         bpSupportAltMinus1_yp->SetLineWidth(3);
         bpSupportAltMinus1_yp ->Draw("same");

         // set the parameters for the negative deviation of one of the halves of the minus side
         bpSupportAltMinus2_yp->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus2_yp->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus2_yp->SetParameter(2, fitterDraw->GetParameter(2)+x_Sys);
         bpSupportAltMinus2_yp->SetLineColor(kBlack);
         bpSupportAltMinus2_yp->SetLineWidth(3);
         bpSupportAltMinus2_yp ->Draw("same");

         // set the parameters for the negative deviation of one of the halves of the minus side
         bpSupportAltMinus1_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus1_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus1_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpSupportAltMinus1_ym->SetLineColor(kBlack);
         bpSupportAltMinus1_ym->SetLineWidth(3);
         bpSupportAltMinus1_ym ->Draw("same");

         // set the parameters for the negative deviation of the other half of the minus side
         bpSupportAltMinus2_ym->SetParameter(0, fitterDraw->GetParameter(0));
         bpSupportAltMinus2_ym->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus2_ym->SetParameter(2, fitterDraw->GetParameter(2)-x_Sys);
         bpSupportAltMinus2_ym->SetLineColor(kBlack);
         bpSupportAltMinus2_ym->SetLineWidth(3);
         bpSupportAltMinus2_ym ->Draw("same");
         // set the parameters for the positive deviation of the plus side
         bpSupportAltPlus_yp->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_yp->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_yp->SetParameter(2, y0_PixelSupportPlus+x_Sys);
         bpSupportAltPlus_yp->SetLineColor(kBlack);
         bpSupportAltPlus_yp->SetLineWidth(3);
         bpSupportAltPlus_yp ->Draw("same");

         // set the parameters for the negative deviation of the plus side
         bpSupportAltPlus_ym->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_ym->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_ym->SetParameter(2, y0_PixelSupportPlus-x_Sys);
         bpSupportAltPlus_ym->SetLineColor(kBlack);
         bpSupportAltPlus_ym->SetLineWidth(3);
         bpSupportAltPlus_ym ->Draw("same");

         // Draw the central functions
         bpAltSupportMinus1->Draw("same");
         bpAltSupportMinus2->Draw("same");
         bpAltSupportPlus->Draw("same");
         }

       // save
       cPlots->Update();
       cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi_sysY.png"));

       // R variation
       h_RhoPhi->Draw("colz");
       bpAlt ->Draw("same");

       // Create the functions for the systematic variation of rho, but not for the minus side of the pixel shield
       TF1 *bpAlt_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-3.15,6.3,3);
       TF1 *bpAlt_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-3.15,6.3,3);
       if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShield2Ellipses" && FitObject != "PixelShield2Arcs" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
         {
         // set the parameters for the positive deviation
         //TF1 *bpAlt_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpAlt_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAlt_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAlt_rp->SetLineColor(kBlack);
         bpAlt_rp->SetLineWidth(3);
         bpAlt_rp ->Draw("same");

         // set the parameters for the negative deviation
         //TF1 *bpAlt_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpAlt_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpAlt_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAlt_rm->SetLineColor(kBlack);
         bpAlt_rm->SetLineWidth(3);
         bpAlt_rm ->Draw("same");
         }

       // draw the radius variation for the pixel support ellipse on the rhophi plots
       // create the functions for the positive and negative deviation of the radius.
       TF1 *bpAltEllipse_rp = new TF1("bpAlt_rp",func_EllipseRhoPhi,-3.15,3.15,4);
       TF1 *bpAltEllipse_rm = new TF1("bpAlt_rm",func_EllipseRhoPhi,-3.15,3.15,4);
       if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
         {
         // set the parameters for the positive deviation
         bpAltEllipse_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpAltEllipse_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltEllipse_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltEllipse_rp->SetParameter(3, (fitterDraw->GetParameter(3))+r_Sys);
         bpAltEllipse_rp->SetLineColor(kBlack);
         bpAltEllipse_rp->SetLineWidth(3);
         bpAltEllipse_rp->Draw("same");

         // set the parameters for the negative deviation
         bpAltEllipse_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpAltEllipse_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltEllipse_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltEllipse_rm->SetParameter(3, (fitterDraw->GetParameter(3))-r_Sys);
         bpAltEllipse_rm->SetLineColor(kBlack);
         bpAltEllipse_rm->SetLineWidth(3);
         bpAltEllipse_rm->Draw("same");

         // draw the central function, update the plot
         bpEllipseAlt->Draw("same");
         cPlots->Update();
         }

       TF1 *bpAltShieldEllipsePlus_rp = new TF1("bpAlt_rp",func_EllipseRhoPhi,-1.575,1.575,4);
       TF1 *bpAltShieldEllipsePlus_rm = new TF1("bpAlt_rm",func_EllipseRhoPhi,-1.575,1.575,4);
       if(FitObject == "PixelShield2Ellipses")
         {
         bpAltShieldEllipsePlus_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpAltShieldEllipsePlus_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltShieldEllipsePlus_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltShieldEllipsePlus_rp->SetParameter(3, fitterDraw->GetParameter(3)+r_Sys);
         bpAltShieldEllipsePlus_rp->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_rp->SetLineWidth(3);
         bpAltShieldEllipsePlus_rp->Draw("same");

         bpAltShieldEllipsePlus_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpAltShieldEllipsePlus_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltShieldEllipsePlus_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltShieldEllipsePlus_rm->SetParameter(3, fitterDraw->GetParameter(3)-r_Sys);
         bpAltShieldEllipsePlus_rm->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_rm->SetLineWidth(3);
         bpAltShieldEllipsePlus_rm->Draw("same");

         funShieldEllipseNear->Draw("same");
         cPlots->Update();
         }

       // Create the functions for the systematic variation of rho for the minus side of the pixel shield
       // The minus side is split into two because the plot centers on the plus side
       TF1 *bpAltMinus1_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpAltMinus2_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpAltMinus1_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpAltMinus2_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpAltPlus_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-1.575,1.575,3);
       TF1 *bpAltPlus_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-1.575,1.575,3);
       if(FitObject == "PixelShieldMinus")
         {
         // Draw the central functoins
         bpAltMinus1->Draw("same");
         bpAltMinus2->Draw("same");
         bpAltPlus->Draw("same");

         // set the parameters for the positive deviation of rho for one of the halves of the minus side
         bpAltMinus1_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpAltMinus1_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus1_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus1_rp->SetLineColor(kBlack);
         bpAltMinus1_rp->SetLineWidth(3);
         bpAltMinus1_rp->Draw("same");

         // set the parameters for the positive deviation of rho for the other half of the minus side
         bpAltMinus2_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpAltMinus2_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus2_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus2_rp->SetLineColor(kBlack);
         bpAltMinus2_rp->SetLineWidth(3);
         bpAltMinus2_rp->Draw("same");

         // set the parameters for the negative deviation of rho for one of the halves of the minus side
         bpAltMinus1_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpAltMinus1_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus1_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus1_rm->SetLineColor(kBlack);
         bpAltMinus1_rm->SetLineWidth(3);
         bpAltMinus1_rm->Draw("same");

         // set the parameters for the negative deviation of rho for the other half of the minus side
         bpAltMinus2_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpAltMinus2_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpAltMinus2_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpAltMinus2_rm->SetLineColor(kBlack);
         bpAltMinus2_rm->SetLineWidth(3);
         bpAltMinus2_rm->Draw("same");

         // set the parameters for the positive deviation of rho for the plus side
         bpAltPlus_rp->SetParameter(0, r0_PixelShieldPlus+r_Sys);
         bpAltPlus_rp->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_rp->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_rp->SetLineColor(kBlack);
         bpAltPlus_rp->SetLineWidth(3);
         bpAltPlus_rp->Draw("same");

         // set the parameters for the negative deviation of rho for the plus side
         bpAltPlus_rm->SetParameter(0, r0_PixelShieldPlus-r_Sys);
         bpAltPlus_rm->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_rm->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_rm->SetLineColor(kBlack);
         bpAltPlus_rm->SetLineWidth(3);
         bpAltPlus_rm->Draw("same");

         }

       // create the functions for the radius variation of the minus and plus side of the pixel support
       TF1 *bpSupportAltMinus1_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpSupportAltMinus2_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpSupportAltMinus1_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,1.575,3.15,3);
       TF1 *bpSupportAltMinus2_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-3.15,-1.575,3);
       TF1 *bpSupportAltPlus_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-1.575,1.575,3);
       TF1 *bpSupportAltPlus_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-1.575,1.575,3);
       if(FitObject == "PixelSupportMinus")
         {
         // Draw the central functoins
         bpAltSupportMinus1->Draw("same");
         bpAltSupportMinus2->Draw("same");
         bpAltSupportPlus->Draw("same");

         // set the parameters for the positive deviation of rho for one of the halves of the minus side
         bpSupportAltMinus1_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpSupportAltMinus1_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus1_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus1_rp->SetLineColor(kBlack);
         bpSupportAltMinus1_rp->SetLineWidth(3);
         bpSupportAltMinus1_rp->Draw("same");

         // set the parameters for the positive deviation of rho for the other half of the minus side
         bpSupportAltMinus2_rp->SetParameter(0, fitterDraw->GetParameter(0)+r_Sys);
         bpSupportAltMinus2_rp->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus2_rp->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus2_rp->SetLineColor(kBlack);
         bpSupportAltMinus2_rp->SetLineWidth(3);
         bpSupportAltMinus2_rp->Draw("same");

         // set the parameters for the negative deviation of rho for one of the halves of the minus side
         bpSupportAltMinus1_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpSupportAltMinus1_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus1_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus1_rm->SetLineColor(kBlack);
         bpSupportAltMinus1_rm->SetLineWidth(3);
         bpSupportAltMinus1_rm->Draw("same");

         // set the parameters for the negative deviation of rho for the other half of the minus side
         bpSupportAltMinus2_rm->SetParameter(0, fitterDraw->GetParameter(0)-r_Sys);
         bpSupportAltMinus2_rm->SetParameter(1, fitterDraw->GetParameter(1));
         bpSupportAltMinus2_rm->SetParameter(2, fitterDraw->GetParameter(2));
         bpSupportAltMinus2_rm->SetLineColor(kBlack);
         bpSupportAltMinus2_rm->SetLineWidth(3);
         bpSupportAltMinus2_rm->Draw("same");

         // set the parameters for the positive deviation of rho for the plus side
         bpSupportAltPlus_rp->SetParameter(0, r0_PixelSupportPlus+r_Sys);
         bpSupportAltPlus_rp->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_rp->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_rp->SetLineColor(kBlack);
         bpSupportAltPlus_rp->SetLineWidth(3);
         bpSupportAltPlus_rp->Draw("same");

         // set the parameters for the negative deviation of rho for the plus side
         bpSupportAltPlus_rm->SetParameter(0, r0_PixelSupportPlus-r_Sys);
         bpSupportAltPlus_rm->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_rm->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_rm->SetLineColor(kBlack);
         bpSupportAltPlus_rm->SetLineWidth(3);
         bpSupportAltPlus_rm->Draw("same");
         }

       // update and save
       cPlots->Update();
       cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi_sysR.png"));
    }



    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);

    h->Draw("LEGO");
    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Fit_LEGO.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit_LEGO.png"));
    //cPlots->Delete();
    //delete cPlots;

    // Plot Derivative
    Double_t YRailTop = 0.;
    Double_t YRailBottom = 0.;
    if (FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative") {
       gStyle->SetOptStat(0);
       hYderivative->GetYaxis()->SetTitleOffset(1.5);
       hYderivative->GetXaxis()->SetTitle("y (cm)");
       hYderivative->GetYaxis()->SetTitle("y Derivative");
       hYderivative->SetLineWidth(3);

       hYderivative ->Draw("e");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivative.png");

       hYderivative ->GetXaxis()->SetRangeUser(-Rmax, -Rmin);
       hYderivative ->GetXaxis()->SetRangeUser(Rmin, Rmax);
       hYderivative ->Draw("e");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivativeTop.png");

       hYderivative ->GetXaxis()->SetRangeUser(-Rmax, -Rmin);
       hYderivative ->Draw("e");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivativeBottom.png");

       hYderivative2D->Draw("COLZ");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivative2D.png");

       // Draw and Fit Bottom
       std::cout<<"Fit for bottom rail"<<std::endl;
       TF1 *f2Bottom = new TF1("f2Bottom",fun2,-8,8,2);
       f2Bottom -> SetParameter(0, -19.7);
       f2Bottom -> SetParameter(1, 0.);
       f2Bottom->SetLineWidth(3);
       f2Bottom->SetLineColor(kRed);
       //hYderivative2D->GetXaxis()->SetRangeUser(-7., -7.);
       //hYderivative2D->GetYaxis()->SetRangeUser(-20., -19.5);
       hYderivative2D->GetXaxis()->SetRangeUser(-8., 8.);
       hYderivative2D->GetYaxis()->SetRangeUser(-19.9, -19.5);
       hYderivative2D->Fit("f2Bottom","R");//fit only this Range defind in function
       YRailBottom = f2Bottom->GetParameter(0);
       std::cout<<"End fit for bottom rail"<<std::endl;

       hYderivative2D ->GetYaxis()->SetRangeUser(-RSmax, -Rmin);
       hYderivative2D ->GetXaxis()->SetRangeUser(-15., 15.);
       hYderivative2D->Draw("COLZ");
       f2Bottom ->Draw("same");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivative2DBottom.png");

       std::cout<<"Fit for top rail"<<std::endl;
       f2Bottom -> SetParameter(0, 19.);
       f2Bottom -> SetParameter(1, 0.);
       hYderivative2D->GetXaxis()->SetRangeUser(-8., -8.);
       hYderivative2D->GetYaxis()->SetRangeUser(18.9, 19.3);
       //TBox *tbox = new TBox (-7., 18.8, 7., 19.4);
       //tbox ->SetFillColorAlpha(kRed,0.);
       hYderivative2D->Fit("f2Bottom","R");//fit only this Range defind in function
       YRailTop = f2Bottom->GetParameter(0);
       std::cout<<"End fit for top rail"<<std::endl;

       hYderivative2D ->GetYaxis()->SetRangeUser(Rmin, RSmax);
       hYderivative2D ->GetXaxis()->SetRangeUser(-15., 15.);
       hYderivative2D->Draw("COLZ");
       f2Bottom ->Draw("same");
       //tbox ->Draw("same");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivative2DTop.png");

       hXderivative2D->Draw("COLZ");
       cPlots->Update();
       cPlots->SaveAs("Plots/xDerivative2D.png");

       hXderivative2D ->GetYaxis()->SetRangeUser(-RSmax, -Rmin);
       hXderivative2D ->GetXaxis()->SetRangeUser(-15., 15.);
       hXderivative2D->Draw("COLZ");

       cPlots->Update();
       cPlots->SaveAs("Plots/xDerivative2DBottom.png");

       hXderivative2D ->GetYaxis()->SetRangeUser(Rmin, RSmax);
       hXderivative2D->Draw("COLZ");
       cPlots->Update();
       cPlots->SaveAs("Plots/xDerivative2DTop.png");

       gStyle->SetOptStat(1000111110);
    }
    // end Plot Derivative

    hEmpty -> Draw();
    h->Draw("COLZsame");
    //h->Draw("COLZ");
    if (FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative") {
       //std::cout << " yRailTop = " << hYderivative->GetXaxis()->GetBinCenter(yRailTop) << " +- " << hYderivative->GetXaxis()->GetBinWidth(yRailTop)/2. << std::endl;
       Double_t x1 = -RPlot;
       Double_t x2 = RPlot;
       Double_t yerr = hYderivative->GetXaxis()->GetBinWidth(yRailTop)/sqrt(12.);
       //Double_t y1 = hYderivative->GetXaxis()->GetBinCenter(yRailTop);//very rude estimation
       Double_t y1 = YRailTop;//more precize
       Double_t y2 = y1;
       TLine * lineTop = new TLine ( x1, y1, x2, y2 );
       lineTop->SetLineColor(kRed);
       lineTop->SetLineWidth(3);
       lineTop->Draw("same");

       //TText *t_top = new TText(.5,y1+2,Form("Top rail y = %3.3f #pm %3.3f",y1, yerr));
       TLatex *t_top = new TLatex(.5,y1+3.7,Form("Top rail y = %3.2f #pm %3.2f cm",y1, yerr));
       latex_circle.DrawLatex(-14., 23.5, Form("Top rail y = %3.2f #pm %3.2f cm",y1, yerr));
       t_top->SetTextAlign(22);
       t_top->SetTextColor(kRed);
       t_top->SetTextFont(43);
       t_top->SetTextSize(40);
       //t_top->SetTextAngle(45);
       //t_top->Draw();


       //y1 = hYderivative->GetXaxis()->GetBinCenter(yRailBottom);//very rude estimation
       y1 = YRailBottom;//more precize
       y2 = y1;
       TLine * lineBottom = new TLine ( x1, y1, x2, y2 );
       lineBottom->SetLineColor(kRed);
       lineBottom->SetLineWidth(3);
       lineBottom->Draw("same");

       latex_circle.DrawLatex(17., 27., "Data 2018");
       TLatex *t_bottom = new TLatex(.5,y1+3.7,Form("Bottom rail y = %3.2f #pm %3.2f cm",y1, yerr));
       latex_circle.DrawLatex(-15., -25., Form("Bottom rail y = %3.2f #pm %3.2f cm",y1, yerr));
       t_bottom->SetTextAlign(22);
       t_bottom->SetTextColor(kRed);
       t_bottom->SetTextFont(43);
       t_bottom->SetTextSize(40);
       //t_bottom->SetTextAngle(45);
       //t_bottom->Draw();

    }

    if(FitObject == "PixelSupportRails")     CMS_lumi( cPlots, iPeriod, 0 );
    // save
    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.png"));
    if(FitObject == "PixelSupportRails") cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.pdf"));

  }

}
//End Main Program

// Function Definition:


//create Fit function for background
Double_t func_fitBg(Double_t *x ,Double_t *par)
{
 //Double_t value = par[0]*par[0]*TMath::Exp(par[1]*x[0]);
 Double_t value = par[0]*par[0]*exp(par[1]*x[0]);
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}

Double_t fun2(Double_t *x ,Double_t *par)
{
  Double_t value = par[0]+par[1]*x[0];
  return value;
}

//create Circle/Arc function in phi,R plane:
Double_t func_ArcRhoPhi(Double_t *x ,Double_t *par)
{
 // x[0] is phi here
 Double_t value = sqrt( (par[0]*cos(x[0])+par[1])*(par[0]*cos(x[0])+par[1]) + (par[0]*sin(x[0])+par[2])*(par[0]*sin(x[0])+par[2]) );
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}

Double_t func_EllipseRhoPhi(Double_t *x, Double_t *par)
{
 // x[0] is phi here
 Double_t value = sqrt( (par[0]*cos(x[0])+par[1])*(par[0]*cos(x[0])+par[1]) + (par[3]*sin(x[0])+par[2])*(par[3]*sin(x[0])+par[2]) );
 return value;
}

//create function to fit beam pipe in 2D (circle)
void chiSquareFunc( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{ 
  Double_t resoNI = 0.01;
  //Double_t halfWidthPipe = 0.025;
  Int_t numBinsX = h->GetNbinsX();
  Int_t numBinsY = h->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  //Bool_t skip = h->Integral() > 500000;
  for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
  { 
    for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
    { 
      Double_t binNum = h->GetBinContent( ix, iy );
      
      /// Thresholds
      /// 2011A+B: 5 entries for inclusive
      ///          3 entries for 5 cm slices
      /// 2012A+B+C+D: 20 entries for inclusive
      ///              5 entries for 5 cm slices      
      //if ( !skip && binNum < 3 ) continue;
      
      // skip (??) negative values after background subtracktion: 
      if ( binNum < 0 ) continue;
      
      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      
      // fit only in singnal + BK subtraction region
      //Double_t Radius = TMath::Sqrt( x*x + y*y  );
      //if ( Radius > PipeInf && Radius < FitInf )
      Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );
      //if ( r > PipeInf && r < FitInf )
      if ( r > RSmin && r < RSmax )
      { 
        
        //Double_t PhaseSpaceFactor = (r0*r0)/(r*r);
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r*r);
        
        diff = par[0] - r;
        chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
      }
//      if (fabs(diff) > halfWidthPipe)  chiSquare += binNum*diff*diff / ( resoNI*resoNI);
     
    }
  } 
  f = chiSquare;
}
// create function to fit the plus side of the pixel support
void funPixelSupportPlus( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
Double_t resoNI = 0.01;
//Double_t halfWidthPipe = 0.025;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
   {
   for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0 ) continue;

      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );

     if ( r > RSmin && r < RSmax && x >= 0)
        {
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r*r);

        diff = par[0] - r;
        chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
        }
      }
   }
f  = chiSquare;
}

// create function to fit the minus side of the pixel support
void funPixelSupportMinus( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
Double_t resoNI = 0.01;
//Double_t halfWidthPipe = 0.025;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
   {
   for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0 ) continue;

      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );

     if ( r > RSmin && r < RSmax && x < 0)
        {
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r*r);

        diff = par[0] - r;
        chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
        }
      }
   }
f  = chiSquare;
}

// create function to fit the pixel support with an ellipse
void funPixelSupportEllipse( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
Double_t resoNI = 0.01;
//Double_t halfWidthPipe = 0.025;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
   {
   for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0 ) continue;
      
      // create the necessary variables for the ellipse
      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      Double_t a = par[0]; // x radius
      Double_t b = par[3]; // y radius
      Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) ); // define r
      Double_t cos_ellipse = (x-par[1])/r; // the cosine
      Double_t sin_ellipse = (y-par[2])/r; // the sine
      //Double_t x_ellipse = a*cos_ellipse - par[1];
      Double_t x_ellipse = a*cos_ellipse;
      //Double_t y_ellipse = b*sin_ellipse - par[2];
      Double_t y_ellipse = b*sin_ellipse;
      Double_t r_ellipse = TMath::Sqrt( (x_ellipse)*(x_ellipse) + (y_ellipse)*(y_ellipse) ); // define radius of the ellipse for the point
      //Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );
     
     if ( r > RSmin && r < RSmax)
        {
        Double_t PhaseSpaceFactor = (r_ellipse*r_ellipse)/(r*r);
        
        diff = r_ellipse - r;
        chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
        }
      }
   } 
f  = chiSquare;
}

// create funciton to fit the pixel shield with an ellipse
void funPixelShield2Ellipses( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
Double_t resoNI = 0.01;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++)
   {
   for (UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++)
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0) continue;

      Double_t x = h->GetXaxis()->GetBinCenter(ix);
      Double_t y = h->GetYaxis()->GetBinCenter(iy);
      Double_t a = par[0]; // x radius
      Double_t b = par[3]; // y radius
      //Double_t b = par[0]+ fabs(par[3]); // y radius

      //near side x > 0
      Double_t r = TMath::Sqrt( (x-par[1])*(x-par[1]) + (y-par[2])*(y-par[2]) ); // define r
      Double_t cos_ellipse = (x-par[1])/r; // the cosin
      Double_t sin_ellipse = (y-par[2])/r; // the sine
      Double_t x_ellipse = a*cos_ellipse;
      Double_t y_ellipse = b*sin_ellipse;
      Double_t r_ellipse = TMath::Sqrt( (x_ellipse)*(x_ellipse) + (y_ellipse)*(y_ellipse) );

      //far side x < 0
      Double_t r_far = TMath::Sqrt( (x-par[4])*(x-par[4]) + (y-par[5])*(y-par[5]) ); // define r
      Double_t cos_ellipse_far = (x-par[4])/r_far; // the cosin
      Double_t sin_ellipse_far = (y-par[5])/r_far; // the sine
      Double_t x_ellipse_far = a*cos_ellipse_far;
      Double_t y_ellipse_far = b*sin_ellipse_far;
      Double_t r_ellipse_far = TMath::Sqrt( (x_ellipse_far)*(x_ellipse_far) + (y_ellipse_far)*(y_ellipse_far) );

      if ( r > RSmin && r < RSmax && x >= 0)
        {
        Double_t PhaseSpaceFactor = (r_ellipse*r_ellipse)/(r*r);
        diff = r_ellipse -r;
        chiSquare += binNum*diff*diff / (resoNI*resoNI) * PhaseSpaceFactor;
        }

      if ( r > RSmin && r < RSmax && x < 0)
        {
        Double_t PhaseSpaceFactor = (r_ellipse_far*r_ellipse_far)/(r_far*r_far);
        diff = r_ellipse_far -r_far;
        chiSquare += binNum*diff*diff / (resoNI*resoNI) * PhaseSpaceFactor;
        }

      }
   }
   f = chiSquare;
}

// create funciton to fit the pixel shield with an ellipse
void funPixelShield2Arcs( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
{
Double_t resoNI = 0.01;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++)
   {
   for (UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++)
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0) continue;

      Double_t x = h->GetXaxis()->GetBinCenter(ix);
      Double_t y = h->GetYaxis()->GetBinCenter(iy);

      //near side x > 0
      Double_t r_near = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );

      //far side x < 0
      Double_t r_far = TMath::Sqrt( (x - par[3])*(x - par[3]) + (y - par[4])*(y - par[4]) );

      if ( r_near > RSmin && r_near < RSmax && x >= 0)
        {
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r_near*r_near);
        diff = par[0] -r_near;
        chiSquare += binNum*diff*diff / (resoNI*resoNI) * PhaseSpaceFactor;
        }

      //if ( r > RSmin && r < RSmax && x < 0)
      if ( r_far > RSmin && r_far < RSmax && x < 0)
        {
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r_far*r_far);
        diff = par[0] -r_far;
        chiSquare += binNum*diff*diff / (resoNI*resoNI) * PhaseSpaceFactor;
        }

      }
   }
   f = chiSquare;
}

// describe Layer 1
Double_t funPixelLayer1(Double_t *x, Double_t *par)
{
//Double_t Long_facets = 0.88; // in cm \pm from (x_R, y_R)
//Double_t Long_facets = 1.1; // in cm \pm from (x_R, y_R)
Double_t Long_facets =3.; // in cm \pm from (x_R, y_R)

Double_t R_L1 = par[0];
Double_t phi_L1 = par[1];
Double_t x0_L1 = par[2];
Double_t y0_L1 = par[3];
Double_t x_corr = x[0]-x0_L1;
Double_t y_corr = 0.0;

Double_t y_L1 = 0.0;
//if (fabs(sin(phi_L1)) > 0.0001) y_L1 = R_L1/sin(phi_L1)-cos(phi_L1)/sin(phi_L1)*x[0];
if (fabs(sin(phi_L1)) > 0.0001) y_corr = R_L1/sin(phi_L1)-cos(phi_L1)/sin(phi_L1)*x_corr;
Double_t x_R = R_L1*cos(phi_L1);
Double_t y_R = R_L1*sin(phi_L1);
Double_t L_facets = sqrt((x_R - x_corr)*(x_R - x_corr) + (y_R - y_corr)* (y_R - y_corr));
if (L_facets > Long_facets) {y_L1 = -100.0;}
else {y_L1 = y_corr + y0_L1;}

return y_L1;
}

// describe Layer 1
void fun2Lines(Double_t *Line1, Double_t *Line2, Double_t *par)
{
Double_t x1f = Line1[0];
Double_t y1f = Line1[1];
Double_t x2f = Line1[2];
Double_t y2f = Line1[3];
Double_t x3f = Line2[0];
Double_t y3f = Line2[1];
Double_t x4f = Line2[2];
Double_t y4f = Line2[3];

// perpendicular line to middle of facet
Double_t x1 = (x1f+x2f)/2.;
Double_t y1 = (y1f+y2f)/2.;
Double_t x2 = 0.; 
Double_t y2 = -100.;
if( fabs(y1f-y2f) > 0.00001 ) y2 = (y1f+y2f)/2. + (x1f*x1f-x2f*x2f)/2./(y1f-y2f);
Double_t x3 = (x3f+x4f)/2.;
Double_t y3 = (y3f+y4f)/2.;
Double_t x4 = 0.; 
Double_t y4 = -100.;
if( fabs(y3f-y4f) > 0.00001 ) y4 = (y3f+y4f)/2. + (x3f*x3f-x4f*x4f)/2./(y3f-y4f);

Double_t xVer = -100;
Double_t yVer = -100;

Double_t Divide = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
if (fabs(Divide) > 0.000001){ // not a zero
   xVer = ( (x1*y2-y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4) )/Divide;
   yVer = ( (x1*y2-y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4) )/Divide;
}

par[0] = xVer;
par[1] = yVer;
}


// create function to fit the plus semicircle of the pixel shield
void funArcPlus( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
Double_t resoNI = 0.01;
//Double_t halfWidthPipe = 0.025;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

//Bool_t skip = h->Integral() > 500000;
for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
   {
   for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0 ) continue;
      
      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      // fit only in singnal + BK subtraction region
      //Double_t Radius = TMath::Sqrt( x*x + y*y  );
      //if ( Radius > PipeInf && Radius < FitInf )
      Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );
     
     if ( r > RSmin && r < RSmax && x > 0)
        {
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r*r);
        
        diff = par[0] - r;
        chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
        }
      }
   } 
f  = chiSquare;
}// end funArcPlus

// create function to fit the minus semicircle of the pixel shield
void funArcMinus( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
Double_t resoNI = 0.01;
//Double_t halfWidthPipe = 0.025;
Int_t numBinsX = h->GetNbinsX();
Int_t numBinsY = h->GetNbinsY();
Double_t chiSquare = 0.0;
Double_t diff = 0.0;

//Bool_t skip = h->Integral() > 500000;
for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
   {
   for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
      {
      Double_t binNum = h->GetBinContent( ix, iy );
      if ( binNum < 0 ) continue;

      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      Double_t r = TMath::Sqrt( (x - par[1])*(x - par[1]) + (y - par[2])*(y - par[2]) );

     if ( r > RSmin && r < RSmax && x < 0)
        {
        Double_t PhaseSpaceFactor = (par[0]*par[0])/(r*r);

        diff = par[0] - r;
        chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
        }
      }
    }
f  = chiSquare;
} // end funArcMinus



