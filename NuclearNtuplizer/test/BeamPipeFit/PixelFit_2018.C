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
TH1D* hProj;
TH1D* h_xPixelNear;
TH1D* h_yPixelNear;
TH1D* h_xPixelFar;
TH1D* h_yPixelFar;
TH2D* h_Extra;
Double_t Rmin, Rmax, RBGmin, RBGmax, RSmin, RSmax, RPlot;
Double_t Sigma_facet = 0.04;//bin width of histo in cm
Double_t Lenth_facet = 2.2;//cm

Double_t fit_facet(Double_t* ,Double_t*);

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
Double_t fun2LinesAngle(Double_t *Line1, Double_t *Line2);

// create function to fit the plus semicircle of the pixel shield
void funArcPlus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create function to fit the minus semicircle of the pixel shield
void funArcMinus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// good fit values
// 21.70; -0.08; -0.34
// 21.68; -0.07; -0.28
//create function to fit objects in 2D with circle (Arc)
void chiSquareFunc( Int_t&, Double_t*, Double_t&, Double_t*, Int_t );
void chiSquareFitFacet( Int_t&, Double_t*, Double_t&, Double_t*, Int_t );
void PixelVertexPlot(TH1D*,TString, TString, Double_t, Double_t);

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
     PlotObject = "hPFDV_XY_Pixel";
     //PlotObject = "hPFDV_XY_PixelSupport";
     PlotObjectBg = "hPFDV_RhoPhi_PixelSupport";
     Rmin = 2.28, Rmax = 8.0, RBGmin = 2.5, RBGmax = 2.55, RSmin = 2.55, RSmax = 2.6;
     RPlot = 8.0;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.02; // size of systematics in cm
     r_Sys = 0.02; // size of systematics in cm
     //**** for |z| < 25 cm
     x0 = 0.09;//0.10; // in cm
     y0 = -0.08;//-0.11; // in cm
     x0_Far = 0.08;//0.04; // in cm
     y0_Far = -0.12;//-0.18; // in cm
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
  //TFile* inputFile = TFile::Open("PlotProduced_MC2018_Pi10GeV.root");
  //TFile* inputFile = TFile::Open("PlotProduced_2018D_RawToReco.root");
  TFile* inputFile = TFile::Open("PlotProduced_2018CD_RawToReco.root");

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
  //for ( int k = -6; k < -5; k++ ) // deafault: |z| < 25 cm 
  //{
    int k = -6; // deafault: |z| < 25 cm 
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
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw.pdf"));
    
    cPlots -> SetLogz();
    h_ZR->Draw("COLZ");
    CMS_lumi( cPlots, iPeriod, 0 ); 
    latex_circle.DrawLatex(-33., 66., "Data 2018");
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_ZR_COLZ.png"));
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw_ZR_COLZ.pdf"));
    cPlots -> SetLogz(1);

    cPlots -> SetLogz();
    h_XY->Draw("COLZ");
    CMS_lumi( cPlots, iPeriod, 0 ); 
    latex_circle.DrawLatex(15., 22., "Data 2018");
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_XY_COLZ.png"));
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw_XY_COLZ.pdf"));
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
    Double_t R_facetNear = 2.781;//2.8 // Technical design
    Double_t R_facetFar = 3.1;//3.014; // Technical design
    Double_t R_facetNear_L2 = 6.616; // Technical design
    Double_t R_facetFar_L2  = 7.0;//6.898; // Technical design 
    Double_t R_PixelCut = 8.0; // incluse volue from 1st and 2nd layer only.
    //Double_t thikness_facet = 0.35; // in cm in phi-R facet plane
    Double_t thikness_facet = 0.5; // in cm in phi-R facet plane
    // 12 facets at layer 1 (0-11) and 28 facets at layer 2 (11-39)
    Int_t NumberFacets = 40; // 12 at layer 1 and 28 at layer 2
    TH2D* hfacet[NumberFacets];
    TH2D* hfacet_Phi[NumberFacets];
    TH2D* hfacet_der[NumberFacets];
    TH2D* hfacet_derPhi[NumberFacets];
    Double_t phi_facet[NumberFacets];
    Double_t dphi_facetPixelSystem[NumberFacets];
    Double_t R_facet[NumberFacets];
    Double_t L_facet[NumberFacets];
    for(int i = 0; i < NumberFacets; i++){

       // define phi_facet for facet #i
       Double_t phi_facet_L1 = Pi/12. + Pi/6.*(i-3) + 0.015; // last value from fit to calculate phi facet more precise
       Double_t phi_facet_L2 = Pi/20. + Pi/14.*(i-12-7) - 0.025; // last value from fit to calculate phi facet more precise 

       phi_facet[i] = phi_facet_L1;
       if (i > 11) phi_facet[i] = phi_facet_L2;

       // define Radius facet, Near facet (each even) and Far facet (odd):
       Double_t R_facetFarTemp = R_facetFar;
       Double_t R_facetNearTemp = R_facetNear;
       if (i > 11){
          R_facetFarTemp = R_facetFar_L2;
          R_facetNearTemp = R_facetNear_L2;
       }
       R_facet[i] = R_facetFarTemp;
       if (i == 5 || i == 11 || i == 25 || i == 39) R_facet[i] = R_facetFarTemp + 0.2;
       if (i == int(i/2)*2){
          R_facet[i] = R_facetNearTemp;
       }

       //hfacet[i] -> Sumw2();
       //hfacet_der[i] -> Sumw2();
       std::ostringstream fn;
       fn.str("");
       fn << "Plots/"<<FitObject<<"_facet_" << i;
       Double_t dBin = h->GetXaxis()->GetBinWidth(1); // bin width in cm
       Int_t NbinX = h->GetNbinsX();
       if (h->GetNbinsX() != h->GetNbinsY()) cout << "ERROR: different binning in X and Y, please modify the code" << endl;
       Double_t XY_cut = fabs(h->GetXaxis()->GetBinLowEdge(1)); 
       if(XY_cut > R_PixelCut) {
          XY_cut = R_PixelCut;
          if(dBin > 0.000000001)NbinX = Int_t(2*XY_cut/dBin);
          else cout << "Error: dBin = " << dBin << endl;
       }
       if (XY_cut < R_PixelCut) R_PixelCut = XY_cut;    
       //cout << "XY_cut = " << XY_cut << " NbinX = " << NbinX << endl;
   
       //hfacet[i] =  new TH2D( fn.str().c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
       //                                               h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );  
       hfacet[i] =  new TH2D( fn.str().c_str(), h->GetTitle(), NbinX, -XY_cut, XY_cut, NbinX, -XY_cut, XY_cut);
       hfacet[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet[i]->GetZaxis()->SetTitle(Form("facet %2i: Events/(%1.1f#times%1.1f mm^{2})", i, hfacet[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet[i]->SetStats(0);
       std::ostringstream fn_der;
       fn_der.str("");
       fn_der << "Plots/"<<FitObject<<"_facet_der_" << i;
       //hfacet_der[i] =  new TH2D( fn_der.str().c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
       //                                               h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );  
       hfacet_der[i] =  new TH2D( fn_der.str().c_str(), h->GetTitle(), NbinX, -XY_cut, XY_cut, NbinX, -XY_cut, XY_cut);
       hfacet_der[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet_der[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet_der[i]->GetZaxis()->SetTitle(Form("d^{2}Events/(%1.1f#times%1.1f mm^{2})", hfacet_der[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_der[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet_der[i]->SetStats(0);

       Int_t NbinX_phi = Int_t(NbinX/4.); // valid if x bin width = y bin width
       //if(i > 11) NbinX_phi = Int_t(NbinX/8.); // valid if x bin width = y bin width
       std::ostringstream fn_Phi;
       fn_Phi.str("");
       fn_Phi << "Plots/"<<FitObject<<"_facet_Phi_" << i;
       hfacet_Phi[i] =  new TH2D( fn_Phi.str().c_str(), h->GetTitle(), NbinX_phi,  -XY_cut, XY_cut, NbinX_phi, -XY_cut, XY_cut);
       hfacet_Phi[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet_Phi[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet_Phi[i]->SetStats(0);

       std::ostringstream fn_derPhi;
       fn_derPhi.str("");
       fn_derPhi << "Plots/"<<FitObject<<"_facet_derPhi_" << i;
       hfacet_derPhi[i] =  new TH2D( fn_derPhi.str().c_str(), h->GetTitle(), NbinX_phi,  -XY_cut, XY_cut, NbinX_phi, -XY_cut, XY_cut);
       hfacet_derPhi[i]->GetXaxis()->SetTitle("x (cm)");
       hfacet_derPhi[i]->GetYaxis()->SetTitle("y (cm)");
       hfacet_derPhi[i]->GetZaxis()->SetTitle(Form("Rotate in #phi facet %2i: d^{2}Events/(%1.1f#times%1.1f mm^{2})", i, hfacet_derPhi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_derPhi[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet_derPhi[i]->SetStats(0);
    }
    numBinsX = h->GetNbinsX();
    numBinsY = h->GetNbinsY();
    for(int i = 0; i < NumberFacets; i++){
       for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
       {
         for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
         {
           Double_t binNum = h->GetBinContent( ix, iy );
           //if(binNum < 1.) continue;
           Double_t x = h->GetXaxis()->GetBinCenter( ix );
           Double_t y = h->GetYaxis()->GetBinCenter( iy );
           if (fabs(x) > R_PixelCut || fabs(y) > R_PixelCut) continue; // don't fill h_facet above this value
           // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
           // positions of the two halves so that the background subtraction is cleaner.
           Double_t x0ref = x0;
           Double_t y0ref = y0;
           if ((i > 5 && i < 12) || (i > 25 && i < 40)) {x0ref = x0_Far; y0ref = y0_Far;} // for far side layer 1 and 2

           Double_t xc = x - x0ref;
           Double_t yc = y - y0ref;

           Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

           if ( rc < Rmin || rc > Rmax ) continue;

           // select facet "i"
           //Double_t x_facet[1];
          // x_facet[0] = xc;
 
           //Rotate in phi R system of facet
           Double_t xf_0 = R_facet[i]*cos(phi_facet[i]);
           Double_t yf_0 = R_facet[i]*sin(phi_facet[i]);
           Double_t xf_prime = xc - xf_0;
           Double_t yf_prime = yc - yf_0;
           // in phi, R system:
           Double_t xf = xf_prime*cos(phi_facet[i]) + yf_prime*sin(phi_facet[i]);
           Double_t yf = -xf_prime*sin(phi_facet[i]) + yf_prime*cos(phi_facet[i]);

           //Double_t par_facet[4];
           //par_facet[0] = R_facet[i];
           //par_facet[1] = phi_facet[i];
           //par_facet[2] = x0ref;
           //par_facet[3] = y0ref;
           //Double_t y_facet = funPixelLayer1(x_facet, par_facet);

           //if (fabs(yc - y_facet) < thikness_facet){// seelect region near facet 2*i
           //if (i == 13) cout << "i = " << i << " phi_facet = " << phi_facet[i] << " R_facet = " << R_facet[i] << " xf = " << xf << " yf = " << yf << endl; 
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
                 //if (y < 0) fyDer2D = -fyDer2D; // to observe start and end
                 //if(fyDer2D < 0) fyDer2D = 1.;// reset if negative

                 Double_t u0x = h->GetBinContent( ix-1, iy-1 ) + 2*h->GetBinContent( ix-1, iy ) + h->GetBinContent( ix-1, iy+1 );
                 Double_t u2x = h->GetBinContent( ix+1, iy-1 ) + 2*h->GetBinContent( ix+1, iy ) + h->GetBinContent( ix+1, iy+1 );
                 Double_t fxDer2D = u2x-u0x;// calculate derivative at iy (y1) point
                 // revert in negative y plain:
                 //if (x < 0) fxDer2D = -fxDer2D;
                 //Double_t fxyDer2D = fabs(fyDer2D*fxDer2D)/binNum/binNum;
                 Double_t fxyDer2D = fabs(fyDer2D*fxDer2D);
                 //if(fxyDer2D < 20000./fabs(sin(phi_facet[i])/cos(phi_facet[i]))) fxyDer2D = 0;
                 //if(fxyDer2D < 20000./fabs(sin(phi_facet[i])) || fxyDer2D < 20000./fabs(cos(phi_facet[i]))) fxyDer2D = 0;
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
                 if (fabs(x) < 0.4*thikness_facet)hfacet_derPhi[i] -> Fill (x, y, fxDer2D); // +- 2 mm don't fill close to edge of end of histo (will be spike)
                 //if (fabs(x) < 0.4*thikness_facet)hfacet_derPhi[i] -> Fill (x, y, fxyDer2D); // +- 2 mm don't fill close to edge of end of histo (will be spike)
                 //if (fabs(x) < 0.4*thikness_facet)hfacet_derPhi[i] -> Fill (x, y, fyDer2D); // +- 2 mm don't fill close to edge of end of histo (will be spike)
    }}}

} /// end hfacet


    Double_t X1_facet[NumberFacets], Y1_facet[NumberFacets], X2_facet[NumberFacets], Y2_facet[NumberFacets];
    for(int i = 0; i < NumberFacets; i++){

       //hfacet_der[i]->Draw("COLZ");
       //cPlots->Update();
       //std::ostringstream fn_der;
       //fn_der.str("");
       //fn_der << "Plots/"<<FitObject<<"_facet_der_" << i <<".png";
       //cPlots->SaveAs(fn_der.str().c_str());


       //TH1D * projhY = hfacet_der[i]->ProjectionY();
       //TH1D * projhY = hfacet_Phi[i]->ProjectionY();
       TH1D * projhY = hfacet_derPhi[i]->ProjectionY("",0, -1,"e");
       hProj = hfacet_derPhi[i]->ProjectionY("",0, -1,"e");

       projhY->GetXaxis()->SetRangeUser(-1.9, 1.9);
       //TH1D * projhY = hfacet[i]->ProjectionY();
       Double_t YprojMin = -100.;
       Double_t YprojMax = -100.;
       Int_t iYprojMin = -100;
       Int_t iYprojMax = -100;
       Double_t YprojCut = -100.;


       // Create the Draw fitter
       TVirtualFitter* fitterDraw;
       // Set the function that the fitter will use and set the parameters
       fitterDraw = TVirtualFitter::Fitter( 0, 3 );
       fitterDraw->SetFCN( chiSquareFitFacet );
       fitterDraw->SetParameter( 0,  "y1",  -1.02, 0.01, 0., 0.); // in cm
       fitterDraw->SetParameter( 1, "A1",   100, 1., 0., 250. ); // in cm
       fitterDraw->SetParameter( 2, "A2",   500, 1., 250., 800. ); // in cm
       //fitterDraw->FixParameter(1);
       //fitterDraw->FixParameter(2);
       Double_t arglist[10] = {0.};
       // Execute the fit
       arglist[0] = 5000; // number of function calls
       arglist[1] = 0.01; // tolerance
       //fitterDraw->ExecuteCommand( "MIGRAD", arglist, 0 );
       fitterDraw->ExecuteCommand( "MIGRAD", arglist, 2 );
       //fitterDraw->ExecuteCommand( "HESSE", arglist, 0 );
       Double_t YprojMinFit = fitterDraw->GetParameter(0)-Sigma_facet;
       Double_t YprojMaxFit = YprojMinFit+Lenth_facet;
       cout << "YprojMinFit = " << YprojMinFit << " YprojMaxFit = " << YprojMaxFit << endl;

       TF1* func_facet = new TF1("func_facet", fit_facet, -1.9,  1.9,  4);
       // set value for fit parametes par[0] and par[2]
       func_facet->SetParameters(fitterDraw->GetParameter(0), fitterDraw->GetParameter(1), fitterDraw->GetParameter(2));
       //func_facet->SetParameter(1, 1.14);
       //func_facet->SetParLimits(1, 1., 1.3);
       //// set name to par[1]
       //func_facet->SetParName(0,"Y1");
       //func_facet->SetParName(1,"Y1");
       //projhY->Fit(func_facet, "M", "", -1.5, 1.5);

       YprojMin = YprojMinFit;
       YprojMax = YprojMaxFit;

       Int_t numBinsYproj = projhY->GetNbinsX();
       Int_t numPhiTestY = hfacet_derPhi[i] -> GetNbinsX();
       if (numBinsYproj != numPhiTestY)cout << "Error: different binning for projection (check that there is no SetRangeUser for original histo) for i = " << i << " numBinsYproj = " << numBinsYproj << " numPhiTestY = " << numPhiTestY << endl;
       for ( UInt_t ix = 1; ix <= UInt_t(numBinsYproj); ix++ ){
           Double_t binNum = projhY->GetBinContent( ix );
           Double_t binCenter = projhY->GetXaxis()->GetBinCenter(ix);
           if(fabs(binCenter) > 1.9) continue; //reject tails where derivety is not correct in edges bins
           Double_t yLow = projhY->GetXaxis()->GetBinLowEdge(ix);
           Double_t yUp = projhY->GetXaxis()->GetBinUpEdge(ix);
           if (YprojMin >= yLow && YprojMin < yUp) iYprojMin = ix;
           if (YprojMax >= yLow && YprojMax < yUp) iYprojMax = ix;
       }
       cout << "i = " << i << " YprojMin = " << YprojMin << " YprojMax = " << YprojMax << endl;
       cout << "i = " << i << " iYprojMin = " << iYprojMin << " iYprojMax = " << iYprojMax << endl;


       TString FacetPixel = "Facet Near";
       if ((i > 5 && i < 12) || (i > 25 && i < 40)) FacetPixel = "Facet Far";
       Int_t iFacetVertex = Int_t((i-1)/2);
       if(i > 5 && i < 12) iFacetVertex = Int_t((i-7)/2);
       if(i > 11 && i < 26) iFacetVertex = Int_t((i-13)/2)+3;
       if (i > 25 && i < 40) iFacetVertex = Int_t((i-27)/2)+3;

       projhY->SetStats(0);
       projhY->GetYaxis()->SetTitle(Form("%s %d (id %d): Events/%1.2f cm", FacetPixel.Data(), i, iFacetVertex, projhY->GetXaxis()->GetBinWidth(1)));
       if (2*Int_t((i-1)/2) != (i-1) ) projhY->GetYaxis()->SetTitle(Form("%s %d: Events/%1.2f cm", FacetPixel.Data(), i, projhY->GetXaxis()->GetBinWidth(1)));
       projhY->GetXaxis()->SetTitle("y (cm)");
       projhY->GetYaxis()->SetTitleOffset(1.5);
       projhY->Draw("e");
       func_facet -> SetLineWidth(3);
       func_facet ->SetNpx(1000); 
       func_facet -> Draw("same");
       cPlots->Update();
       std::ostringstream fn_derY;
       fn_derY.str("");
       fn_derY << "Plots/"<<FitObject<<"_facet_der_projY_" << i <<".png";
       cPlots->SaveAs(fn_derY.str().c_str());

       // Make projection on X new YprojMin and YprojMax:
       // find XprojMin
       //TH1D * projhX = hfacet_derPhi[i]->ProjectionX();
       // find X  starting after 2 mm from YprojMin and scan 2mm
       // find int # of bins for 2 mm
       Double_t dBin = hfacet_derPhi[i]->GetXaxis()->GetBinWidth(1); // bin with in cm 
       Int_t numBinsX_derPhi = hfacet_derPhi[i]->GetNbinsX();
       Int_t iBin = 1; 
       if (dBin < 0) {cout << "Error: bin width = " << dBin << endl;}
       iBin = Int_t(0.2/dBin); // count bins in 2 mm
       iBin = max(iBin,1);
       cout << "iBin = " << iBin << endl;
       TH1D * projhX = hfacet_derPhi[i]->ProjectionX("",iYprojMin+iBin, iYprojMin+2*iBin,"e"); // start from 2 mm from edge and scan for 2mm
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
           if (binNum >= 0.8*XprojCut) { // find a point with maximum value <= here the laterst strong signal (at lease 80% then before)
              XprojMin = binCenter;
              XprojCut = binNum;
              //if(i == 5) cout << "binCenter = " << binCenter << " binNum = " << binNum << endl;
           } 
       }
       //XprojMin = XprojMax;// the same
       //cout << "i = " << i << " XprojMin = " << XprojMin << " XprojMax = " << XprojMax << endl;
       projhX->GetYaxis()->SetTitle(Form("%s %d (id %d): Events/%1.2f cm", FacetPixel.Data(), i, iFacetVertex, projhX->GetXaxis()->GetBinWidth(1)));
       if (2*Int_t((i-1)/2) != (i-1) ) projhX->GetYaxis()->SetTitle(Form("%s %d: Events/%1.2f cm", FacetPixel.Data(), i, projhX->GetXaxis()->GetBinWidth(1)));
       projhX->GetXaxis()->SetTitle("x_{min} (cm)");
       projhX->GetYaxis()->SetTitleOffset(1.5);
       projhX->Draw("e");
       cPlots->Update();
       std::ostringstream fn_derX;
       fn_derX.str("");
       fn_derX << "Plots/"<<FitObject<<"_facet_der_projX_" << i <<".png";
       cPlots->SaveAs(fn_derX.str().c_str());
       //
       // find XprojMax
       TH1D * projhXmax = hfacet_derPhi[i]->ProjectionX("",iYprojMax-2*iBin, iYprojMax-iBin,"e"); //start from 2 mm from edge and scan for 2mm
       projhXmax->GetXaxis()->SetRangeUser(-0.5, 0.5);
       Double_t XprojMax = -100.;
       XprojCut = -100.;

       for ( UInt_t ix = 1; ix <= UInt_t(numBinsXproj); ix++ ){
           Double_t binNum = projhXmax->GetBinContent( ix );
           Double_t binCenter = projhXmax->GetXaxis()->GetBinCenter(ix);
           if(fabs(binCenter) > 0.2) continue; //reject tails where derivety is not correct in edges bins
           if (binNum >= 0.8*XprojCut) { // find a point with maximum value <= here the laterst strong signal (at lease 80% then before)
              XprojMax = binCenter;
              XprojCut = binNum;
           }
       }
       cout << "i = " << i << " XprojMin = " << XprojMin << " XprojMax = " << XprojMax << endl;
       projhXmax->GetYaxis()->SetTitle(Form("%s %d (id %d): Events/%1.2f cm", FacetPixel.Data(), i, iFacetVertex, projhXmax->GetXaxis()->GetBinWidth(1)));
       if (2*Int_t((i-1)/2) != (i-1) ) projhXmax->GetYaxis()->SetTitle(Form("%s %d: Events/%1.2f cm", FacetPixel.Data(), i, projhXmax->GetXaxis()->GetBinWidth(1)));
       projhXmax->GetXaxis()->SetTitle("x_{max} (cm)");
       projhXmax->GetYaxis()->SetTitleOffset(1.5);
       projhXmax->Draw("e");
       cPlots->Update();
       std::ostringstream fn_derXmax;
       fn_derXmax.str("");
       fn_derXmax << "Plots/"<<FitObject<<"_facet_der_projX_yMax" << i <<".png";
       cPlots->SaveAs(fn_derXmax.str().c_str());
       //
       //SetRangeUser should be set only after projection, othewise bug in Root.
       hfacet_derPhi[i]->GetXaxis()->SetRangeUser(-R_PixelCut, R_PixelCut);
       hfacet_derPhi[i]->GetYaxis()->SetRangeUser(-R_PixelCut, R_PixelCut);
       hfacet_derPhi[i]->GetZaxis()->SetTitle(Form("In #phi Der. %s %d (id %d): Events/(%1.1f#times%1.1f mm^{2})", FacetPixel.Data(), i, iFacetVertex, hfacet_derPhi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_derPhi[i]->GetYaxis()->GetBinWidth(1)*10));
       if (2*Int_t((i-1)/2) != (i-1) )hfacet_derPhi[i]->GetZaxis()->SetTitle(Form("In #phi Der. %s %d: Events/(%1.1f#times%1.1f mm^{2})", FacetPixel.Data(), i, hfacet_derPhi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_derPhi[i]->GetYaxis()->GetBinWidth(1)*10));
       hfacet_derPhi[i]->GetZaxis()->SetTitleOffset(1.2);
       hfacet_derPhi[i]->Draw("COLZ");
       cPlots->Update();
       std::ostringstream fn_derPhi;
       fn_derPhi.str("");
       fn_derPhi << "Plots/"<<FitObject<<"_facet_derPhi_" << i <<".png";
       cPlots->SaveAs(fn_derPhi.str().c_str());


       dphi_facetPixelSystem[i] = -100.;
       if (fabs(YprojMin-YprojMax) > 0.0001){
          dphi_facetPixelSystem[i] = TMath::ATan2((XprojMax - XprojMin),(YprojMax-YprojMin)); // y, x coordinate, for us it is inverse (x, y)
       }

       // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
       // positions of the two halves so that the background subtraction is cleaner.
       Double_t x0ref = x0;
       Double_t y0ref = y0;
       if ((i > 5 && i < 12) || (i > 25 && i < 40)) {x0ref = x0_Far; y0ref = y0_Far;} // for far side
       //Rotate in phi R system of facet
       Double_t xf_0 = R_facet[i]*cos(phi_facet[i]);
       Double_t yf_0 = R_facet[i]*sin(phi_facet[i]);

       X1_facet[i] = XprojMin*cos(phi_facet[i]) - YprojMin*sin(phi_facet[i]) + x0ref + xf_0; 
       Y1_facet[i] = XprojMin*sin(phi_facet[i]) + YprojMin*cos(phi_facet[i]) + y0ref + yf_0; 
       X2_facet[i] = XprojMax*cos(phi_facet[i]) - YprojMax*sin(phi_facet[i]) + x0ref + xf_0; 
       Y2_facet[i] = XprojMax*sin(phi_facet[i]) + YprojMax*cos(phi_facet[i]) + y0ref + yf_0; 
       L_facet[i] = (X2_facet[i] - X1_facet[i])*(X2_facet[i] - X1_facet[i]) + (Y2_facet[i] - Y1_facet[i])*(Y2_facet[i] - Y1_facet[i]);
       L_facet[i] = sqrt(L_facet[i]);
       cout << "i = " << i << " L_facet = " << L_facet[i] << " dphi_facetPixelSystem = " << dphi_facetPixelSystem[i] << endl;
       //if (sin(phi)*cos(phi) < 0) 
       //   {X1_facet = XprojMin; Y1_facet = YprojMin; X2_facet = XprojMax; Y2_facet = YprojMax;}
       //else
       //   {X1_facet = XprojMax; Y1_facet = YprojMin; X2_facet = XprojMin; Y2_facet = YprojMax;}
   

       // Draw facet in phi
       TLine *lineFacetPhi = new TLine(XprojMin,YprojMin,XprojMax,YprojMax);
       lineFacetPhi -> SetLineColor(kRed);
       lineFacetPhi -> SetLineWidth(3);

       hfacet_Phi[i]->GetXaxis()->SetRangeUser(-R_PixelCut, R_PixelCut);
       hfacet_Phi[i]->GetYaxis()->SetRangeUser(-R_PixelCut, R_PixelCut);
       hfacet_Phi[i]->GetZaxis()->SetTitle(Form("In #phi %s %d (id %d): Events/(%1.1f#times%1.1f mm^{2})", FacetPixel.Data(), i, iFacetVertex, hfacet_Phi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_Phi[i]->GetYaxis()->GetBinWidth(1)*10));
       if (2*Int_t((i-1)/2) != (i-1) )hfacet_Phi[i]->GetZaxis()->SetTitle(Form("In #phi %s %d: Events/(%1.1f#times%1.1f mm^{2})", FacetPixel.Data(), i, hfacet_Phi[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet_Phi[i]->GetYaxis()->GetBinWidth(1)*10)); 
       hfacet_Phi[i]->GetZaxis()->SetTitleOffset(1.2);
       hfacet_Phi[i]->Draw("COLZ");
       lineFacetPhi -> Draw("same");
       cPlots->Update();
       std::ostringstream fn_Phi;
       fn_Phi.str("");
       fn_Phi << "Plots/"<<FitObject<<"_facet_PhiPlot_" << i <<".png";
       cPlots->SaveAs(fn_Phi.str().c_str());

    }
    cPlots -> SetLogz();
    Double_t dphi_facetL1 = 0.;
    Double_t dphi_facetL2 = 0.;
    Int_t Ndphi_facetL1 = 0;
    Int_t Ndphi_facetL2 = 0;
    for(int i = 0; i < NumberFacets; i++){
      if (Int_t(i/2.)*2 != i ){
        cout << "i = " << i << " L_facet = " << L_facet[i] << " dphi_facetPixelSystem = " << dphi_facetPixelSystem[i] << endl;
        if (i < 12) {dphi_facetL1 += dphi_facetPixelSystem[i]; Ndphi_facetL1 += 1;}
        if (i > 11 && i < 40) {dphi_facetL2 += dphi_facetPixelSystem[i]; Ndphi_facetL2 += 1;}
      } 
    }
    if( Ndphi_facetL1 > 0) dphi_facetL1 = dphi_facetL1/Ndphi_facetL1;
    if( Ndphi_facetL2 > 0) dphi_facetL2 = dphi_facetL2/Ndphi_facetL2;
    cout << "Average dphi_facetL1 = " << dphi_facetL1 << " dphi_facetL2 = " << dphi_facetL2 << endl;
    //////////////////////////
    //////////////////////////
    //Double_t X1_facet[12], Y1_facet[12], X2_facet[12], Y2_facet[12];
    //Int_t N_Line = 3;
    Int_t N_Line = Int_t(NumberFacets/4);
    Int_t N_ver = N_Line*(N_Line-1)/2;
    // Find vertex for Near pixel useing 1st layer
    Double_t X1[N_Line],Y1[N_Line],X2[N_Line],Y2[N_Line]; 
    Int_t N_LineNear = 0;
    for ( UInt_t i = 0; i < UInt_t(NumberFacets/2.); i++ ){ // for for new side far facets # 1, 3 and 5
    //for ( UInt_t i = 0; i < 3; i++ ){ // for for new side far facets # 1, 3 and 5
      if (i < 3 || (i > 5 && i < 13) ){ // list only Near Side
         X1[N_LineNear] = X1_facet[2*i+1]; 
         X2[N_LineNear] = X2_facet[2*i+1]; 
         Y1[N_LineNear] = Y1_facet[2*i+1]; 
         Y2[N_LineNear] = Y2_facet[2*i+1];
         N_LineNear = N_LineNear+1; 
      }
    } 
    if (N_LineNear != N_Line) cout << "ERROR not equal: N_LineNear = " << N_LineNear << " N_Line = " << N_Line << endl;

    Double_t X_verNear[N_ver], Y_verNear[N_ver];
    Double_t X_VerNear = 0., Y_VerNear = 0.;
    Int_t Ncount = 0; 
    h_xPixelNear = new TH1D( "h_xPixelNear", "x_{0}^{Near} Pixel", 100, -5.,5. );
    h_yPixelNear = new TH1D( "h_yPixelNear", "y_{0}^{Near} Pixel", 100, -5.,5. );
    h_xPixelFar = new TH1D( "h_xPixelFar", "x_{0}^{Far} Pixel", 100, -5.,5. );
    h_yPixelFar = new TH1D( "h_yPixelFar", "y_{0}^{Far} Pixel", 100, -5.,5. );
    cout << "Near pixel: reject buggy lines with current statistics Line = 6, 7 and 9, see code" <<endl;
    for ( UInt_t i = 0; i < UInt_t(N_LineNear-1); i++ ){ // for for new side far facets # 1, 3 and 5
        for ( UInt_t j = i+1; j < UInt_t(N_LineNear); j++ ){
            Double_t par[2]; // x0, y0
            Double_t Line1[4]; // x1,y1,x2,y2
            Double_t Line2[4]; // x3,y3,x4,y4
            Line1[0] = X1[i]; Line1[1] = Y1[i];
            Line1[2] = X2[i]; Line1[3] = Y2[i];
            Line2[0] = X1[j]; Line2[1] = Y1[j];
            Line2[2] = X2[j]; Line2[3] = Y2[j];
            // reject buggy lines with current statistics:
            //if(i == 6 || i == 7 || i == 9 || j == 6 || j == 7 || j == 9) continue;
            //if( i == 6 || i == 3 || i == 7 || j == 3 || j == 6 || j == 7 ) continue;
            fun2Lines(Line1, Line2, par);
            X_verNear[Ncount] = par[0];
            Y_verNear[Ncount] = par[1];
            Double_t Phi_lines = 0.; // reject if lines parallel
            Phi_lines = fun2LinesAngle(Line1, Line2); // find Angel between 2 lines
            if (Phi_lines < 0.8) continue; // reject if lines with angle less then ~45 degree (0.78)
            h_xPixelNear -> Fill(10.*X_verNear[Ncount]);//in mm
            h_yPixelNear -> Fill(10.*Y_verNear[Ncount]);//in mm
            cout << "Vertex Near # = " << Ncount <<  " for (i,j) = (" << i << "," << j<< ") X_verNear = " << fixed << setprecision(3) << X_verNear[Ncount] << " Y_verNear = " << Y_verNear[Ncount] << " Phi_lines = " << Phi_lines << endl;
            X_VerNear = X_VerNear + X_verNear[Ncount];
            Y_VerNear = Y_VerNear + Y_verNear[Ncount];
            Ncount = Ncount + 1;
    }}
    //if (Ncount != N_ver) cout << " Error: Ncount != N_ver " << endl;
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
    cout << "X_VerNear      = " << fixed << setprecision(3) << X_VerNear     << " Y_VerNear     = " << Y_VerNear << endl; 
    cout << "dX_VerNear     = " << fixed << setprecision(3) << dX_VerNear    << " dY_VerNear    = " << dY_VerNear << endl; 
    cout << "dX_VerNearCon  = " << fixed << setprecision(3) << dX_VerNearCon << " dY_VerNearCon = " << dY_VerNearCon << endl; 
    //////////////////////////
    //////////////////////////
    // Find vertex for Near pixel useing 1st layer
    Double_t X1Far[N_Line],Y1Far[N_Line],X2Far[N_Line],Y2Far[N_Line];
    Int_t N_LineFar = 0;
    for ( UInt_t i = 0; i < UInt_t(NumberFacets/2.); i++ ){ // for for new side far facets # 1, 3 and 5
    //for ( UInt_t i = 0; i < 6; i++ ){ // for for new side far facets # 1, 3 and 5
      if( (i>=3 && i < 6) || i > 12){
         X1Far[N_LineFar] = X1_facet[2*i+1];
         X2Far[N_LineFar] = X2_facet[2*i+1];
         Y1Far[N_LineFar] = Y1_facet[2*i+1];
         Y2Far[N_LineFar] = Y2_facet[2*i+1];
         N_LineFar = N_LineFar+1;
      }
    }
    if (N_LineFar != N_Line) cout << "ERROR not equal: N_LineFar = " << N_LineFar << " N_Line = " << N_Line << endl;
    Double_t X_verFar[N_ver], Y_verFar[N_ver];
    Double_t X_VerFar = 0., Y_VerFar = 0.;
    Ncount = 0;
    //for ( UInt_t i = 0; i < UInt_t(N_ver-1); i++ ){ // for for new side far facets # 1, 3 and 5
    //    for ( UInt_t j = i+1; j < UInt_t(N_ver); j++ ){
    cout << "Far pixel: reject buggy lines with current statistics Line = 4, 5, 7 and 8, see code" <<endl;
    for ( UInt_t i = 0; i < UInt_t(N_LineFar-1); i++ ){ // for for new side far facets # 1, 3 and 5
        for ( UInt_t j = i+1; j < UInt_t(N_LineFar); j++ ){
            Double_t par[2]; // x0, y0
            Double_t Line1[4]; // x1,y1,x2,y2
            Double_t Line2[4]; // x3,y3,x4,y4
            Line1[0] = X1Far[i]; Line1[1] = Y1Far[i];
            Line1[2] = X2Far[i]; Line1[3] = Y2Far[i];
            Line2[0] = X1Far[j]; Line2[1] = Y1Far[j];
            Line2[2] = X2Far[j]; Line2[3] = Y2Far[j];
            // reject buggy lines with current statistics:
            //if(i == 4 || i == 5 || i == 7 || i == 8 || j == 4 || j == 5 || j == 7 || j == 8) continue;
            fun2Lines(Line1, Line2, par);
            X_verFar[Ncount] = par[0];
            Y_verFar[Ncount] = par[1];
            Double_t Phi_lines = 0.; // reject if lines parallel
            Phi_lines = fun2LinesAngle(Line1, Line2); // find Angel between 2 lines
            if (Phi_lines < 0.8) continue; // reject if lines with angle less then ~45 degree (0.78)
            h_xPixelFar -> Fill(10.*X_verFar[Ncount]);// in mm
            h_yPixelFar -> Fill(10.*Y_verFar[Ncount]);//in mm
            cout << "Vertex Far # = " << Ncount <<  " for (i,j) = (" << i << "," << j<< ") X_verFar = " << fixed << setprecision(3) << X_verFar[Ncount] << " Y_verFar = " << Y_verFar[Ncount] << " Phi_lines = " << Phi_lines << endl;
            X_VerFar = X_VerFar + X_verFar[Ncount];
            Y_VerFar = Y_VerFar + Y_verFar[Ncount];
            Ncount = Ncount + 1;
    }}
    //if (Ncount != N_ver) cout << " Error: Ncount != N_ver " << endl;
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
    cout << "X_VerFar      = " << fixed << setprecision(3) << X_VerFar     << " Y_VerFar     = " << Y_VerFar << endl;
    cout << "dX_VerFar     = " << fixed << setprecision(3) << dX_VerFar    << " dY_VerFar    = " << dY_VerFar << endl;
    cout << "dX_VerFarCon  = " << fixed << setprecision(3) << dX_VerFarCon << " dY_VerFarCon = " << dY_VerFarCon << endl;
    //////////////////////////
    //////////////////////////

   // Draw (X,Y) pixel position for near and far sides
    PixelVertexPlot(h_xPixelNear,"x_{0}^{Near} (mm)", "Plots/PixelShield2Arcs_x0PixelNear.png",X_VerNear, dX_VerNearCon);
    PixelVertexPlot(h_yPixelNear,"y_{0}^{Near} (mm)", "Plots/PixelShield2Arcs_y0PixelNear.png",Y_VerNear, dY_VerNearCon);
    PixelVertexPlot(h_xPixelFar,"x_{0}^{Far} (mm)", "Plots/PixelShield2Arcs_x0PixelFar.png",X_VerFar, dX_VerFarCon);
    PixelVertexPlot(h_yPixelFar,"y_{0}^{Far} (mm)", "Plots/PixelShield2Arcs_y0PixelFar.png",Y_VerFar, dY_VerFarCon);


    for(int i = 0; i < NumberFacets; i++){

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

       TString FacetPixel = "Facet Near";
       if ((i > 5 && i < 12) || (i > 25 && i < 40)) FacetPixel = "Facet Far";
       Int_t iFacetVertex = Int_t((i-1)/2);
       if(i > 5 && i < 12) iFacetVertex = Int_t((i-7)/2);
       if(i > 11 && i < 26) iFacetVertex = Int_t((i-13)/2)+3;
       if (i > 25 && i < 40) iFacetVertex = Int_t((i-27)/2)+3;
       //hfacet[i]->GetXaxis()->SetRangeUser(-5., 5.);
       //hfacet[i]->GetYaxis()->SetRangeUser(-5., 5.);
       hfacet[i]->GetXaxis()->SetRangeUser(-R_PixelCut, R_PixelCut);
       hfacet[i]->GetYaxis()->SetRangeUser(-R_PixelCut, R_PixelCut);
       hfacet[i]->GetZaxis()->SetTitle(Form("%s %d (id %d): Events/(%1.1f#times%1.1f mm^{2})", FacetPixel.Data(), i, iFacetVertex, hfacet[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet[i]->GetYaxis()->GetBinWidth(1)*10));
       if (2*Int_t((i-1)/2) != (i-1) )hfacet[i]->GetZaxis()->SetTitle(Form("%s %d: Events/(%1.1f#times%1.1f mm^{2})", FacetPixel.Data(), i, hfacet[i]->GetXaxis()->GetBinWidth(1)*10,  hfacet[i]->GetYaxis()->GetBinWidth(1)*10)); 
       hfacet[i]->GetZaxis()->SetTitleOffset(1.2);
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
    //continue; // don't need code below
    //////////////////////////////////
    //////////////////////////////////

}
//End Main Program

// Function Definition:

Double_t fit_facet(Double_t *x ,Double_t *par)
{
 Double_t value= par[2];
 //Double_t Sigma_facet = 0.04;//bin width of histo in cm
 //Double_t Lenth_facet = 2.2;//cm
 Double_t lenth = Lenth_facet-2*Sigma_facet;//cm

if (x[0] < par[0]){
  Double_t temp = (x[0]-par[0]) * (x[0]-par[0]) /Sigma_facet/Sigma_facet ;
  value = par[1] + (par[2]-par[1]) * exp( -0.5 * temp );
}
if (x[0] > par[0]+lenth){
  Double_t temp = (x[0]-par[0]-lenth) * (x[0]-par[0]-lenth) /Sigma_facet/Sigma_facet ;
  value = par[1] + (par[2] - par[1])* exp( -0.5 * temp );

}
 return value;
}

// Draw (X,Y) pixel position for near and far sides
void PixelVertexPlot(TH1D*hPlot,TString Xaxis, TString PngTitle, Double_t VertexPos, Double_t dVertexPos){
    TCanvas* cVer = new TCanvas("cVer","");
    cVer->cd();

    hPlot->SetStats(0);
    hPlot->GetXaxis()->SetTitle(Xaxis);
    hPlot->GetYaxis()->SetTitle(Form("Events/%1.1f mm", hPlot->GetXaxis()->GetBinWidth(1)));
    hPlot->GetXaxis()->SetTitleOffset(1.2);
    hPlot-> SetLineWidth(3);
    Double_t MaxY = hPlot->GetMaximum();
    MaxY = MaxY + 1.1*sqrt(MaxY);
    //hPlot->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    //hPlot->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    TLine *lineX0PixelFar = new TLine(10.*VertexPos,0,10.*VertexPos,MaxY); // in mm
    lineX0PixelFar -> SetLineColor(kRed);
    lineX0PixelFar -> SetLineWidth(3);
    hPlot->Draw("e");
    lineX0PixelFar->Draw("same");
    //cVer->Update();
    cVer->SaveAs(PngTitle);
    cVer->Close();
}

//create function to fit beam pipe in 2D (circle)
//void chiSquareFitFacet( Int_t&, Double_t*, Double_t&, Double_t*, Int_t );
void chiSquareFitFacet( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Double_t resoNI = 0.01;
  //Double_t halfWidthPipe = 0.025;
  Int_t numBinsX = hProj->GetNbinsX();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  Int_t Npoints = 0;
  for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
  {
      Double_t binNum = hProj->GetBinContent( ix);

      Double_t x[1];
      x[0] = hProj->GetXaxis()->GetBinCenter( ix );
      if (fabs(x[0]) > 1.9) continue; // reject entries about 1.9
      if (binNum < 1) continue; // reject 0 bin
      Npoints = Npoints +1;

      Double_t value= 100.;
      value = fit_facet(x, par);


      Double_t PhaseSpaceFactor = 100.;
      //if (x < par[0] || x > par[1]) PhaseSpaceFactor = 1.;
      //else PhaseSpaceFactor = 100.;
      diff = fabs(binNum - value);
      //if (x > par[0] && x < par[1]) diff = min(diff, fabs(diff-50.)); // for high plot ignor errors withing 50.
      chiSquare += diff*diff/PhaseSpaceFactor;
      //cout << " x = " << x[0] << " binNum = " << binNum << " value = " << value << " diff = " << diff << endl;
  }
 
  //if (Npoints > 3) f = chiSquare/(Npoints-3); // 3 parameters
  //else f = 1000.;
  f = chiSquare;
  //cout << " y1 = " << par[0] << " A1 = " << par[1] << " A2 = " << par[2] << " f = " << f  << " Npoints = " << Npoints << endl;

}

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

Double_t fun2LinesAngle(Double_t *Line1, Double_t *Line2)
{
  Double_t Phi_lines = 0.; // reject if lines paralle
  Double_t L_Line1 = sqrt( (Line1[2]-Line1[0])*(Line1[2]-Line1[0]) + (Line1[3]-Line1[1])*(Line1[3]-Line1[1]) );
  Double_t L_Line2 = sqrt( (Line2[2]-Line2[0])*(Line2[2]-Line2[0]) + (Line2[3]-Line2[1])*(Line2[3]-Line2[1]) );
  if (L_Line1 > 0.0001 && L_Line2 > 0.0001){
     Phi_lines = (Line1[2]-Line1[0])*(Line2[2]-Line2[0])+(Line1[3]-Line1[1])*(Line2[3]-Line2[1]);
     Phi_lines = Phi_lines/L_Line1/L_Line2;
     Phi_lines = TMath::ACos(Phi_lines);
     Phi_lines = min(Phi_lines, (TMath::Pi()-Phi_lines));
  }
  return Phi_lines;
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



