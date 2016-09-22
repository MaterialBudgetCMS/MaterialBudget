/* ************************************************* */
/*                                                   */
/* Tracker Material with Nuclear Interactions        */
/*                                                   */
/* Current Developer: Anna Kropivnitskaya,           */
/*                    Eilish Gibson                  */
/*              2013: Nicola Pozzobon for Beam Pipe  */
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

using namespace std;

TH2D* h;
Double_t Rmin, Rmax, RBGmin, RBGmax, RSmin, RSmax, RPlot;

// create function to fit the plus side of the pixel support
void funPixelSupportPlus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create function to fit the minus side of the pixel support
void funPixelSupportMinus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create function to fit the pixel support with an ellipse
void funPixelSupportEllipse( Int_t &, Double_t *, Double_t &, Double_t *, Int_t );

// create funciton to fit the pixel shield with an ellipse
void funPixelShieldEllipsePlus( Int_t &, Double_t *, Double_t &, Double_t *, Int_t);

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

void InnerTrackerFit()
{

  //Start Initialization:
  
  TH2D* h_RhoPhi;
  TCanvas* cPlots;
  TCanvas* cQuality;
  TH1D* hQuality;
  TH1D* hYderivative;
  TH2D* hYderivative2D;
  TH2D* hXderivative2D;
  
  // fit mesurements:
  Double_t x0_PixelShieldPlus = -0.112;
  Double_t y0_PixelShieldPlus = -0.093;
  Double_t r0_PixelShieldPlus = 3.782;
  
  
  Double_t x0_PixelSupportPlus = -0.233;
  Double_t y0_PixelSupportPlus = -0.331;
  Double_t r0_PixelSupportPlus = 21.85;
  
  
  TString FitObject = "";
  TString PlotObject = "hPFDV_XY_Map_Pipe";
  TString PlotObjectBg = "hPFDV_RhoPhi_Map_Pipe";
  Double_t RangeEstimatorQuality, x_Sys = 0, r_Sys = 0, x0 = 0, y0 = 0, r0 = 1, r0_y =1 ;
  if (r0_y < 0.) cout << "Error: r0_y < 0" << endl;

  Double_t ErrPrecision = 0.0005;  
  //Double_t ErrPrecision = 0.00000005;  

  // Set flags for fit options:

  Int_t flag_ExcludeBadFitSector = 1; // = 1 exclude; = 0 not exclude;
  Int_t  flag_Sys = 1; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
  

  //*** to fit is uncomment line:

  FitObject = "BeamPipe"; // working well
  //FitObject = "BeamPipeEllipse"; //work well
  //FitObject = "PixelShield"; // work well
  //FitObject = "PixelShieldPlus"; // work well
  //FitObject = "PixelShieldMinus"; // work well 
  //FitObject = "PixelShieldEllipse"; //work well
  //FitObject = "PixelShieldEllipsePlus"; // status failed
  //FitObject = "PixelSupport"; // work well
  //FitObject = "PixelSupportPlus"; // work well, don't use it
  //FitObject = "PixelSupportMinus"; // work well, don't use it
  //FitObject = "PixelSupportEllipse"; //work well
  //FitObject = "PixelSupportRails"; // work well
  //FitObject = "PixelSupportRailsPositive"; // work well
  //FitObject = "PixelSupportRailsNegative"; // work wel
  
  //*** set parameters for Beam Pipe fit
  if(FitObject == "BeamPipe"){
     Rmin = 1.8, Rmax = 3.0, RBGmin = 2.4, RBGmax = 3., RSmin = 2.0, RSmax = 2.4, RPlot = 2.6;
     RangeEstimatorQuality = 0.1;  
     x_Sys = 0.002; //size of systematics in cm
     r_Sys = 0.002; //size of systematics in cm
     x0 = 0.124; // from previous fits using this program that were based on 2015
     y0 = 0.026; // from previous fits using this program that were based on 2015
     r0 = 2.21; // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Beam Pipe Ellipse fit
  if(FitObject == "BeamPipeEllipse") {
     Rmin = 1.8, Rmax = 3.0, RBGmin = 2.4, RBGmax = 3., RSmin = 2.0, RSmax = 2.4, RPlot = 2.6;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.002; //size of systematics in cm
     r_Sys = 0.002; //size of systematics in cm
     x0 = 0.124; // from previous fits using this program that were based on 2015
     y0 = 0.026; // from previous fits using this program that were based on 2015
     r0 = 2.211; // initial x radiu, from previous fits using this program that were based on 2015
     r0_y = 2.211; // in cm, initial y radius
  }
  
  //*** set parameters for Pixel Shield
  if(FitObject == "PixelShield"){
     Rmin = 3.0, Rmax = 4.1, RBGmin = 2.6, RBGmax = 3.5, RSmin = 3.5, RSmax = 3.9, RPlot = 4.1;
     RangeEstimatorQuality = 0.1;  
     x_Sys = 0.03; //size of systematics in cm
     r_Sys = 0.03; //size of systematics in cm
     // Values for fit with a circle
     x0 = -0.029; // from previous fits using this program that were based on 2015
     y0 = -0.079; // from previous fits using this program that were based on 2015
     r0 = 3.72;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Shield Plus
  if(FitObject == "PixelShieldPlus"){
     Rmin = 3.0, Rmax = 4.1, RBGmin = 2.6, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 4.1;
     RangeEstimatorQuality = 0.1; 
     x_Sys = 0.006; // size of systematics in cm
     r_Sys = 0.006; // size of systematics in cm
     x0 = -0.106; // in cm
     y0 = -0.096; // in cm
     r0 = 3.783; // in cm
  }
  //*** with all phi sectors: 3.736, x0 = -0.02, y0 = -0.092
  
  //*** set parameters for Pixel Shield Minus
  //*** to superimpose the fits for the Pxiel Shield Plus and Minus sides run this
  if(FitObject == "PixelShieldMinus"){
     Rmin = 3.0, Rmax = 4.1, RBGmin = 2.6, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 4.1;
     RangeEstimatorQuality = 0.1; 
     x_Sys = 0.006; // size of systematics in cm
     r_Sys = 0.006; // size of systematics in cm
     x0 = 0.052; // in cm
     y0 = -0.095; // in cm
     r0 = 3.777; // in cm
  }
  
  //*** set parameters for Pixel Shield Ellipse
  if(FitObject == "PixelShieldEllipse"){
     Rmin = 3.0, Rmax = 4.1, RBGmin = 2.6, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 4.1;
     RangeEstimatorQuality = 0.1; 
     x_Sys = 0.03; // size of systematics in cm
     r_Sys = 0.03; // size of systematics in cm
     x0 = -0.029; // in cm
     y0 = -0.086; // in cm
     r0 = 3.71; // in cm, initial x radius
     r0_y = 3.75; // in cm, initial y radius
  }
  
  //*** set parameters for Pixel Shield Ellipse Plus
  if(FitObject == "PixelShieldEllipsePlus"){
     Rmin = 3.0, Rmax = 4.1, RBGmin = 2.6, RBGmax = 3.6, RSmin = 3.6, RSmax = 4.0, RPlot = 4.1;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.006; // size of systematics in cm
     r_Sys = 0.006; // size of systematics in cm
     x0 = -0.115; // in cm
     y0 = -0.097; // in cm
     r0 = 3.792; // in cm, the initial x radius
     r0_y = 3.783; // in cm, initial y radius
  }
  
  //*** set parameters for Pixel Support
  if(FitObject == "PixelSupport"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;  
     x_Sys = 0.1; //size of systematics in cm
     r_Sys = 0.1; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Plus
  if(FitObject == "PixelSupportPlus"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;  
     x_Sys = 0.1; //size of systematics in cm
     r_Sys = 0.1; //size of systematics in cm
     x0 = -0.232; // from previous fits using this program that were based on 2015
     y0 = -0.331; // from previous fits using this program that were based on 2015
     r0 = 21.85;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Minus
  if(FitObject == "PixelSupportMinus"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;  
     x_Sys = 0.1; //size of systematics in cm
     r_Sys = 0.1; //size of systematics in cm
     x0 = 0.023;// from previous fits using this program that were based on 2015
     y0 = -0.317; // from previous fits using this program that were based on 2015
     r0 = 21.81; // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Ellipse
  if(FitObject == "PixelSupportEllipse"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18.5, Rmax = 24.5, RBGmin = 22.3, RBGmax = 24.5, RSmin = 21.1, RSmax = 22.3, RPlot = 24.5; 
     RangeEstimatorQuality = 0.2;  
     x_Sys = 0.006; //size of systematics in cm
     r_Sys = 0.05; //size of systematics in cm
     x0 = -0.081;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.70;  // initial x radius, from previous fits using this program that were based on 2015
     r0_y = 21.78; // initial y radius, from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Rails
  if(FitObject == "PixelSupportRails"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5; 
     x_Sys = 0.02; //size of systematics in cm
     r_Sys = 0.02; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Rails Positive
  if(FitObject == "PixelSupportRailsPositive"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5; 
     x_Sys = 0.02; //size of systematics in cm
     r_Sys = 0.02; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
  
  //*** set parameters for Pixel Support Rails Negative
  if(FitObject == "PixelSupportRailsNegative"){
     PlotObject = "hPFDV_XY_Map_BPix";
     PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
     Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 24.5; 
     RangeEstimatorQuality = 0.5;
     x_Sys = 0.02; //size of systematics in cm
     r_Sys = 0.02; //size of systematics in cm
     x0 = -0.083;// from previous fits using this program that were based on 2015
     y0 = -0.324; // from previous fits using this program that were based on 2015
     r0 = 21.73;  // from previous fits using this program that were based on 2015
  }
  
  //End Initialization:

  //gROOT->SetBatch(1);
  gROOT->ForceStyle();

  TFile* inputFile = TFile::Open("Run2015DreReco.root");

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
  gStyle->SetPalette(1);
  gStyle->SetOptStat(1000111110);
  gStyle->SetCanvasDefW(980);
  gStyle->SetCanvasDefH(800);
  gStyle->SetPadRightMargin(0.2725);
  gStyle->SetStatX(0.98);
  gStyle->SetStatY(0.90);
  gStyle->SetStatW(0.24);
  gStyle->SetTitleW(0.585);
  gStyle->SetTitleX(0.434);

  gStyle->SetOptFit(0011);

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
  for ( int k = -6; k < -5; k++ )
  //for ( int k = -5; k < -4; k++ ) //for for list of histograms to fit
  {
    std::string  plot = std::string(PlotObject);
    std::string  plotBg = std::string(PlotObjectBg);
    //if (FitObject == "PixelSupport")TString plot = PlotObject;
    //if (FitObject == "PixelSupport")TString plotBg = PlotObjectBg;
    //TString plot = "hPFDV_XY_Map_Pipe";
    //TString plotBg = "hPFDV_RhoPhi_Map_Pipe";
    std::ostringstream plotName;
    std::ostringstream plotNameBg;

    plotName.str("");
    plotName << plot.c_str();
    plotNameBg.str("");
    plotNameBg << plotBg.c_str();

    /// k = -7 is the inclusive one
    /// k = -6 is only BPiz (|z| < 25 cm)
    if ( FitObject == "PixelShield" || FitObject == "BeamPipe" || FitObject == "PixelShieldPlus" || FitObject == "PixelShieldMinus" ||
         FitObject == "BeamPipeEllipse" || FitObject == "PixelShieldEllipse" ||
         FitObject == "PixelShieldEllipsePlus" || FitObject == "PixelShieldEllipseMinus"  ) {
       if ( k == -6 )
       {
         plotName << "_AbsZ25";
         plotNameBg << "_AbsZ25";
       }
       else if ( k != -7 )
      {
        plotName << "_" << k*5 << "_" << (k+1)*5;
        plotNameBg << "_" << k*5 << "_" << (k+1)*5;
      }
    }

    plot = TString( plotName.str().c_str() );
    plotBg = TString( plotNameBg.str().c_str() );
    //printf(plot.c_str());
    //printf("\n");

    cout << "Function used for X:Y   = " << plot << endl;
    cout << "Function used for R:PHI = " << plot << endl;

    h_RhoPhi = new TH2D();
    h_RhoPhi = (TH2D*)inputFile->Get( plotBg.c_str() );
    h_RhoPhi->Sumw2();
    if(FitObject == "PixelSupport")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelSupportEllipse")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShield") h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldEllipsePlus") h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldEllipse")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldPlus")h_RhoPhi->Rebin2D(2,2);
    if(FitObject == "PixelShieldMinus")h_RhoPhi->Rebin2D(2,2);
    //if(FitObject == "BeamPipe")    h_RhoPhi->Rebin2D(5,5);
    h_RhoPhi->SetStats(0);
    h_RhoPhi->GetXaxis()->SetTitle("#phi");
    h_RhoPhi->GetYaxis()->SetTitle("R [cm]");
    //h_RhoPhi->GetXaxis()->SetRangeUser(-RPlot, RPlot);


    cPlots = new TCanvas(("c_"+plot).c_str(),"");

    cPlots->cd();


    h = new TH2D();
    h = (TH2D*)inputFile->Get( plot.c_str() );
    h->Sumw2();
    if(FitObject == "PixelSupport" || FitObject == "PixelSupportPlus" || FitObject == "PixelSupportMinus")h->Rebin2D(3,3);
    if(FitObject == "PixelSupportEllipse")h->Rebin2D(3,3);
    if(FitObject == "PixelShield") h->Rebin2D(5,5);
    if(FitObject == "PixelShieldEllipsePlus") h->Rebin2D(5,5);
    if(FitObject == "PixelShieldEllipse")h->Rebin2D(5,5);
    if(FitObject == "PixelShieldPlus") h->Rebin2D(5,5);
    if(FitObject == "PixelShieldMinus")h->Rebin2D(5,5);
    if(FitObject == "BeamPipe")    h->Rebin2D(5,5);
    if(FitObject == "BeamPipeEllipse")h->Rebin2D(5,5);
    if(FitObject == "PixelSupportRails")h->Rebin2D(3,3);
    //if(FitObject == "PixelSupportRailsPositive")h->Rebin2D(2,2);
    //if(FitObject == "PixelSupportRailsNegative")h->Rebin2D(2,2);
    h->SetStats(0);
    h->GetXaxis()->SetTitle("x [cm]");
    h->GetYaxis()->SetTitle("y [cm]");
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    h->Draw("col");

    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw.png"));

    h->Draw("LEGO");
    //cPlots->SaveAs(("Plots/"+FitObject+"_Draw_LEGO.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Draw_LEGO.png"));


   //create quality Histogram
   hQuality = new TH1D( "hQuality", "BG Quality", 100, 0., 5. );
   hQuality->Sumw2();


    /// Step 0: apply flux factor



    Int_t numBinsX = h->GetNbinsX();
    Int_t numBinsY = h->GetNbinsY();

    for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
      {
        for ( UInt_t iy = 1; iy <= UInt_t(numBinsY); iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x;
          Double_t yc = y;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          //          if ( rc < Inf || rc > Sup ) continue;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum * rc*rc / (r0*r0);

          h->SetBinContent(ix, iy, densityNum);

        }
      }
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    h->Draw("LEGO");
    //cPlots->SaveAs(("Plots/"+FitObject+"_FluxCorrection_LEGO.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_FluxCorrection_LEGO.png"));


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
          if (FitObject == "PixelShieldMinus" && x >= 0) x0ref = x0_PixelShieldPlus, y0ref = y0_PixelShieldPlus;
          if (FitObject == "PixelSupportMinus" && x >= 0) x0ref = x0_PixelSupportPlus, y0ref = y0_PixelSupportPlus;
          Double_t xc = x - x0ref;
          Double_t yc = y - y0ref;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Rmin || rc > Rmax ) continue;

          Double_t pc = TMath::ATan2( yc, xc );
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
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2015}_{0},y^{2015}_{0}) [cm]");
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
      fitBg->SetParName(0, "N0");
      fitBg->SetParName(1, "k");
      //we  need set limits here to avoid negative values in fit (it will crash)
      //fitBg->SetParLimits(0, 0, 1E9);
      //fitBg->SetParLimits(1, -1E9, 0);
      fitBg->SetLineWidth(2);
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
      legBg->SetTextSize(0.03);
      legBg->SetFillColor(kWhite);
      legBg->SetTextColor(kBlack);
      legBg->AddEntry(hbgua0,"inclusive data","l");
      legBg->AddEntry(hbgua2,"signal fit region","f");
      legBg->AddEntry(hbgua1,"sideband fit region","f");
      legBg->AddEntry(fitBg,"sideband fit function","l");
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
    }

    /// -------------------------- Step 2: calculate background --------------------------------

    plot = plot + "_Bgk";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");
    cPlots->cd();

    //create empty 2d histo for backroung estimation in signal region
    TH2D* h0 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h0->GetXaxis()->SetTitle("x [cm]");
    h0->GetYaxis()->SetTitle("y [cm]");

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
        Double_t xc = x - x0ref;
        Double_t yc = y - y0ref;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

        if ( rc < Rmin || rc > Rmax ) continue;

        Double_t pc = TMath::ATan2( yc, xc );
        if(pc < 0) pc = pc + 2*TMath::Pi();

        if ( rc > RSmin && rc < RSmax )
        {
          UInt_t phiSect = floor(  pc   / ( 2*TMath::Pi() ) * 40 );

          /// Average over 3 adjacent sectors to smooth differences
          //Double_t avg0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          //Double_t avg1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );
          Double_t avg0 =  bgFit0[phiSect];
          Double_t avg1 =  bgFit1[phiSect];

          //Double_t bgDensity = avg0 + avg1*rc;
          Double_t x_rc[1];     x_rc[0]= rc;
          Double_t par_rc[2]; par_rc[0] = avg0; par_rc[1] = avg1;

          Double_t bgDensity = func_fitBg(x_rc,par_rc);
          Double_t bgNum = h0->GetXaxis()->GetBinWidth( ix ) * h0->GetYaxis()->GetBinWidth( iy ) * bgDensity;

          if ( ( rc > RSmin && rc < RSmax ) )
            h0->Fill( x, y, bgNum );
        }
      }
    }

    h0->Draw("col");

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
          Double_t xc = x - x0ref;
          Double_t yc = y - y0ref;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Rmin || rc > Rmax ) continue;

          Double_t pc = TMath::ATan2( yc, xc );
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
        if( (FitObject == "PixelSupport" || FitObject == "PixelSupportEllipse" || FitObject == "BeamPipe" || FitObject == "BeamPipeEllipse") && x > RSmax && x < (RSmax+RangeEstimatorQuality)) SignalUpperEdge = SignalUpperEdge + value;
        if( (FitObject == "PixelShieldEllipse" || FitObject == "PixelShieldEllipsePlus" || FitObject == "PixelShield" || FitObject == "PixelShieldPlus" || FitObject == "PixelShieldMinus") && x > (RSmax-RangeEstimatorQuality) && x < RSmax) SignalUpperEdge = SignalUpperEdge + value;
        
        if( x > (RBGmax-RangeEstimatorQuality) && x < RBGmax) BgUpperEdge = BgUpperEdge + value;
      }
      bgFitQuality[phiSect] = 1; //good phi sector for fit      

      // Flag phi sectors to be excluded from the fit using bin contents in the signal and background region
      if(FitObject == "PixelSupport" || FitObject == "PixelSupportPlus" || FitObject == "PixelSupportMinus")
        {
         if (SignalLowEdge > 0.6*BgUpperEdge || SignalUpperEdge > 1.3*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        }
      if(FitObject == "PixelSupportEllipse")
        {
         if (SignalLowEdge > 0.2*BgUpperEdge ) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        }
      if(FitObject == "PixelShield")
        {
        if (SignalUpperEdge > 1.3*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
        std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
        std::cout << "********DONE CHECKING SLICE TO REMOVE STRUCTURES********" << std::endl;
        }
      if(FitObject == "PixelShieldPlus")
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
      if(FitObject == "PixelShieldEllipsePlus")
        {
        if (SignalUpperEdge > 1.3*BgUpperEdge) bgFitQuality[phiSect] = 0; // bad phi sector for fit
        std::cout << "Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
        }
      if(BgUpperEdge > 0.)hQuality->Fill( max(SignalLowEdge/BgUpperEdge, SignalUpperEdge/BgUpperEdge) );
      if(FitObject == "PixelShield")std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalUpperEdge/BgUpperEdge << std::endl;
      if( FitObject == "PixelSupport" || FitObject == "PixelSupportEllipse")std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << SignalLowEdge/BgUpperEdge << std::endl;

      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2015}_{0},y^{2015}_{0}) [cm]");
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

      hbgua0->Draw("histo");
      hbgua1->SetFillStyle(3004);
      hbgua1->SetFillColor(kRed);
      hbgua1->SetMarkerColor(kRed);
      hbgua1->SetLineColor(kRed);
      hbgua1->Draw("samehisto");
      hbgua2->SetFillStyle(3005);
      hbgua2->SetFillColor(kGreen);
      hbgua2->SetMarkerColor(kGreen);
      hbgua2->SetLineColor(kGreen);
      hbgua2->Draw("samehisto");
      hbgua3->SetFillStyle(3005);
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
      fitBg->SetLineWidth(2);
      fitBg->Draw("same");

      //TLegend* legBg = new TLegend(x1L, 0.52, x2L, y2L, "");
      //TLegend* legBg = new TLegend(0.45, 0.6, 0.8, 0.9, "");
      TLegend* legBg = new TLegend(0.65, 0.6, 1.0, 0.9, "");
      legBg->SetTextFont(42);
      legBg->SetTextSize(0.03);
      legBg->SetFillColor(kWhite);
      legBg->SetTextColor(kBlack);
      if (bgFitQuality[phiSect] == 0) legBg->AddEntry(hbgua0,"EXCLUDED from FIT","");
      legBg->AddEntry(hbgua0,"inclusive data","l");
      legBg->AddEntry(hbgua2,"signal fit region","f");
      legBg->AddEntry(hbgua1,"sideband fit region","f");
      legBg->AddEntry(fitBg,"sideband fit function","l");
      legBg->AddEntry(hbgua3,"estimated background","f");
      legBg->Draw("same");

      gStyle->SetOptStat(1000111110);

      std::ostringstream fn;
      //fn << "Plots/"<<plotBg<<"_BGUA_XCk" << "_" << phiSect<<".pdf";
      fn << "Plots/"<<FitObject<<"_Slice_BGUA_XCk" << "_" << phiSect<<".pdf";
      //cPlots->SaveAs(fn.str().c_str());
      fn.str("");
      fn << "Plots/"<<FitObject<<"_Slice_BGUA_XCk" << "_" << phiSect<<".png";
      cPlots->SaveAs(fn.str().c_str());
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
    cQuality->Print("Plots/Quality.png");

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
    h1->GetXaxis()->SetTitle("x [cm]");
    h1->GetYaxis()->SetTitle("y [cm]");

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
          /// Average over 3 adjacent sectors to smooth differences
          //Double_t avg0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          //Double_t avg1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );
          Double_t avg0 =  bgFit0[phiSect];
          Double_t avg1 =  bgFit1[phiSect];
          
          Double_t x_rc[1];     x_rc[0]= rc;
          Double_t par_rc[2]; par_rc[0] = avg0; par_rc[1] = avg1;
          //Double_t bgDensity = avg0 + avg1*rc;
          Double_t bgDensity = func_fitBg(x_rc,par_rc); 
          Double_t bgNum = h1->GetXaxis()->GetBinWidth( ix ) * h1->GetYaxis()->GetBinWidth( iy ) * bgDensity;
          
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
              if (FitObject == "PixelSupportRailsPositive")
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

    h1->SetMinimum(1);
    h1->SetStats(0);
    h = h1;


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
    TVirtualFitter* fitter;
    fitter = TVirtualFitter::Fitter( 0, 3 );
    if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport" || FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative")
    //if((FitObject != "PixelShieldPlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportPlus" && FitObject != "PixelSupportEllipse") && FitObject != "PixelSupportMinus")
      {
      //                                                  npar
      // Set the function that the fitter will use and set the parameters
      fitter->SetFCN( chiSquareFunc );
      fitter->SetParameter( 0,  "R",   r0, 0.01, RSmin, RSmax ); // in cm
      fitter->SetParameter( 1, "x0",   x0, 0.01, -0.6, 0.6 ); // in cm
      fitter->SetParameter( 2, "y0",   y0, 0.01, -0.6, 0.6 ); // in cm
      //   fitter->FixParameter(1); fitter->FixParameter(2); 


      //fitter->SetParameter( 0,  "R", 2.932, 0.01, 2.6, 3.3 );
      //fitter->FixParameter( 2 );
      //fitter->FixParameter( 1 );
      //fitter->FixParameter( 0 );
      Double_t arglist[10] = {0.};
      // Execute the fit

      //cout << "======    Start Fit of Inner Tracker with Circle" << endl;
      if(FitObject != "PixelSupportRails" && FitObject != "PixelSupportRailsPositive" && FitObject != "PixelSupportRailsNegative") fitter->ExecuteCommand( "MIGRAD", arglist, 0 );
      //cout << "======    End Fit of Inner Tracker with Circle" << endl;
      fitterDraw = fitter;
      }

    //if small slice, then rebin histo for better view
    //if(k > -6 && k < 5) h->Rebin2D(5,5);
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    h->Draw("col");

    TGraph* gr_arc;
    Double_t x_arc0[1], y_arc0[1];
    x_arc0[0] = 0.;
    y_arc0[0] = 0.;
    gr_arc = new TGraph(1,x_arc0,y_arc0);
    gr_arc->SetMarkerStyle(20);
    gr_arc->SetMarkerSize(0.5);
    gr_arc->SetMarkerColor(kRed);

    // Fit the plus side of the pixel support with a semicircle
    TVirtualFitter* fitterSupportPlus;
    fitterSupportPlus = fitter;
    TGraph* gr_arcSupportPlus = gr_arc;
    if ( FitObject == "PixelSupportPlus")
       {
       fitterSupportPlus = TVirtualFitter::Fitter( 0, 3 );
       fitterSupportPlus->SetFCN(funPixelSupportPlus);
       // set the parameters
       fitterSupportPlus->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterSupportPlus->SetParameter( 1, "x0", x0, 0.01, -0.6,  0.6 ); // in cm
       fitterSupportPlus->SetParameter( 2, "y0", y0, 0.01, -0.6,  0.6 ); // in cm

       Double_t arglistArcPlus[10] = {0.};
       fitterSupportPlus->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );

       // Draw the arc of the fit
       TArc* arcSupportPlus = new TArc( fitterSupportPlus->GetParameter(1), fitterSupportPlus->GetParameter(2), fitterSupportPlus->GetParameter(0), -90, 90);
       arcSupportPlus->SetFillStyle(0);
       arcSupportPlus->SetLineColor(kRed);
       arcSupportPlus->SetLineWidth(2);
       arcSupportPlus->Draw("same");
       Double_t x_arcSupportPlus[1], y_arcSupportPlus[1];
       x_arcSupportPlus[0] = fitterSupportPlus->GetParameter(1);
       y_arcSupportPlus[0] = fitterSupportPlus->GetParameter(2);
       gr_arcSupportPlus = new TGraph(1,x_arcSupportPlus,y_arcSupportPlus);
       gr_arcSupportPlus->SetMarkerStyle(20);
       gr_arcSupportPlus->SetMarkerSize(0.5);
       gr_arcSupportPlus->SetMarkerColor(kRed);
       gr_arcSupportPlus->Draw("P");
       fitterDraw = fitterSupportPlus;
       }


    // Fit the minus side of the pixel support with a semicircle
    TVirtualFitter* fitterSupportMinus;
    fitterSupportMinus = fitter;
    TGraph* gr_arcSupportMinus = gr_arc;
    TGraph* gr_arcSupportMinusPlus = gr_arc;
    if ( FitObject == "PixelSupportMinus")
       {
       fitterSupportMinus = TVirtualFitter::Fitter( 0, 3 );
       fitterSupportMinus->SetFCN(funPixelSupportMinus);
       // set the parameters
       fitterSupportMinus->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterSupportMinus->SetParameter( 1, "x0", x0, 0.01, -0.6,  0.6 ); // in cm
       fitterSupportMinus->SetParameter( 2, "y0", y0, 0.01, -0.6,  0.6 ); // in cm

       Double_t arglistArcPlus[10] = {0.};
       fitterSupportMinus->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );

       // Draw the arc for the minus side.
       TArc* arcSupportMinus = new TArc( fitterSupportMinus->GetParameter(1), fitterSupportMinus->GetParameter(2), fitterSupportMinus->GetParameter(0), 90, 270);
       arcSupportMinus->SetFillStyle(0);
       arcSupportMinus->SetLineColor(kBlack);
       arcSupportMinus->SetLineWidth(2);
       arcSupportMinus->Draw("same");
       Double_t x_arcSupportMinus[1], y_arcSupportMinus[1];
       x_arcSupportMinus[0] = fitterSupportMinus->GetParameter(1);
       y_arcSupportMinus[0] = fitterSupportMinus->GetParameter(2);
       gr_arcSupportMinus = new TGraph(1,x_arcSupportMinus,y_arcSupportMinus);
       gr_arcSupportMinus->SetMarkerStyle(20);
       gr_arcSupportMinus->SetMarkerSize(0.5);
       gr_arcSupportMinus->SetMarkerColor(kBlack);
       gr_arcSupportMinus->Draw("P");

       // Draw the arc for the plus side using predetermined values for the parameters
       TArc* arcSupportMinusPlus = new TArc( x0_PixelSupportPlus, y0_PixelSupportPlus, r0_PixelSupportPlus, -90, 90);
       arcSupportMinusPlus->SetFillStyle(0);
       arcSupportMinusPlus->SetLineColor(kRed);
       arcSupportMinusPlus->SetLineWidth(2);
       arcSupportMinusPlus->Draw("same");
       Double_t x_arcSupportPlus[1], y_arcSupportPlus[1];
       x_arcSupportPlus[0] = x0_PixelSupportPlus;
       y_arcSupportPlus[0] = y0_PixelSupportPlus;
       gr_arcSupportMinusPlus = new TGraph(1,x_arcSupportPlus,y_arcSupportPlus);
       gr_arcSupportMinusPlus->SetMarkerStyle(20);
       gr_arcSupportMinusPlus->SetMarkerSize(0.5);
       gr_arcSupportMinusPlus->SetMarkerColor(kRed);
       gr_arcSupportMinusPlus->Draw("P");
       fitterDraw = fitterSupportMinus;
       }

    TVirtualFitter* fitterShieldEllipsePlus;
    fitterShieldEllipsePlus = fitter;
    TGraph* gr_ellipseShieldPlus = gr_arc;
    if (FitObject == "PixelShieldEllipsePlus")
       {
       fitterShieldEllipsePlus = TVirtualFitter::Fitter(0,4);
       fitterShieldEllipsePlus->SetFCN(funPixelShieldEllipsePlus);
       //std::cout << "**********Setting Parameters**********" << std::endl;
       fitterShieldEllipsePlus->SetParameter( 0, "r0_x", r0, 0.01, RSmin, RSmax ); // in cm
       fitterShieldEllipsePlus->SetParameter( 1, "x0", x0, 0.01, -0.4, 0.4 ); // in cm
       fitterShieldEllipsePlus->SetParameter( 2, "y0", y0, 0.01, -0.4, 0.4 ); // in cm
       fitterShieldEllipsePlus->SetParameter( 3, "r0_y", r0_y, 0.01, RSmin, RSmax ); // in cm
       Double_t arglistArcEllipse[10] = {0.};
       //std::cout << "**********About to Fit**********" << std::endl;
       fitterShieldEllipsePlus->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );
       //std::cout << "*********Done Fitting**********" << std::endl;

       TEllipse* ellipseShieldPlus = new TEllipse( fitterShieldEllipsePlus->GetParameter(1), fitterShieldEllipsePlus->GetParameter(2), fitterShieldEllipsePlus->GetParameter(0), fitterShieldEllipsePlus->GetParameter(3));
       ellipseShieldPlus->SetFillStyle(0);
       ellipseShieldPlus->SetLineColor(kRed);
       ellipseShieldPlus->SetLineWidth(2);
       ellipseShieldPlus->Draw("same");
       Double_t x_ellipseShieldPlus[1], y_ellipseShieldPlus[1];
       x_ellipseShieldPlus[0] = fitterShieldEllipsePlus->GetParameter(1);
       y_ellipseShieldPlus[0] = fitterShieldEllipsePlus->GetParameter(2);

       gr_ellipseShieldPlus = new TGraph(1,x_ellipseShieldPlus,y_ellipseShieldPlus);
       gr_ellipseShieldPlus->SetMarkerStyle(20);
       gr_ellipseShieldPlus->SetMarkerSize(0.5);
       gr_ellipseShieldPlus->SetMarkerColor(kRed);
       gr_ellipseShieldPlus->Draw("P");
       fitterDraw = fitterShieldEllipsePlus;
       }
    // fit the pixel support with an ellipse

    TVirtualFitter* fitterSupportEllipse;
    fitterSupportEllipse = fitter;
    TGraph* gr_ellipseSupport = gr_arc;
    if ( FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
       {
       fitterSupportEllipse = TVirtualFitter::Fitter( 0, 4 );
       fitterSupportEllipse->SetFCN(funPixelSupportEllipse);
       // set parameters for the pixel support ellipse fit
       std::cout << "********** Setting Parameters **********" << std::endl;
       fitterSupportEllipse->SetParameter( 0, "r0_x", r0, 0.01, RSmin, RSmax ); // in cm
       fitterSupportEllipse->SetParameter( 1, "x0", x0, 0.01, -0.3,  0.3 ); // in cm
       fitterSupportEllipse->SetParameter( 2, "y0", y0, 0.01, -0.6,  0.6 ); // in cm
       fitterSupportEllipse->SetParameter( 3, "r0_y", r0_y, 0.01, RSmin, RSmax ); // in cm
       //fitterSupportEllipse->FixParameter(0);
       //fitterSupportEllipse->FixParameter(1);
       //fitterSupportEllipse->FixParameter(3); 
       //fitterSupportEllipse->FixParameter(2); 

       //std::cout << "Fitting Ellipse" << std::endl;
       Double_t arglistArcEllipse[10] = {0.};
       std::cout << "********** About to Fit **********" << std::endl;
       fitterSupportEllipse->ExecuteCommand( "MIGRAD", arglistArcEllipse, 0 );

       std::cout << "********** Drawing Ellipse **********" << std::endl;
       // draw the ellipse
       TEllipse* ellipseSupport = new TEllipse( fitterSupportEllipse->GetParameter(1), fitterSupportEllipse->GetParameter(2), fitterSupportEllipse->GetParameter(0),(fitterSupportEllipse->GetParameter(3)));
       ellipseSupport->SetFillStyle(0);
       ellipseSupport->SetLineColor(kRed);
       ellipseSupport->SetLineWidth(2);
       ellipseSupport->Draw("same");
       Double_t x_ellipseSupport[1], y_ellipseSupport[1];
       x_ellipseSupport[0] = fitterSupportEllipse->GetParameter(1);
       y_ellipseSupport[0] = fitterSupportEllipse->GetParameter(2);

       gr_ellipseSupport = new TGraph(1,x_ellipseSupport,y_ellipseSupport);
       gr_ellipseSupport->SetMarkerStyle(20);
       gr_ellipseSupport->SetMarkerSize(0.5);
       gr_ellipseSupport->SetMarkerColor(kRed);
       gr_ellipseSupport->Draw("P");
       std::cout << "********** Done Drawing Ellipse **********" << std::endl;
       fitterDraw = fitterSupportEllipse;
       }

    // Here is where the plus semicircle of the pixel shield is fit

 
    TVirtualFitter* fitterArcPlus ;
    fitterArcPlus = fitter ;
    TGraph* gr_arcPlus = gr_arc;
    if ( FitObject == "PixelShieldPlus")
       {
       // create the fitter, set the function that it will use,  and set the parameters
       fitterArcPlus = TVirtualFitter::Fitter( 0, 3 );
       fitterArcPlus->SetFCN(funArcPlus);
       fitterArcPlus->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterArcPlus->SetParameter( 1, "x0", x0, 0.01, -0.3, 0.1 ); // in cm
       fitterArcPlus->SetParameter( 2, "y0", y0, 0.01, -0.3,  0.1 ); // in cm

       Double_t arglistArcPlus[10] = {0.};
       // Execute the fit
       fitterArcPlus->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );

       // Draw an arc from -90 degrees to 90 degrees using the parameters of the fit
       TArc* arcPlus = new TArc( fitterArcPlus->GetParameter(1), fitterArcPlus->GetParameter(2), fitterArcPlus->GetParameter(0), -90, 90);
       arcPlus->SetFillStyle(0);
       arcPlus->SetLineColor(kRed);
       arcPlus->SetLineWidth(2);
       arcPlus->Draw("same");
       Double_t x_arcPlus[1], y_arcPlus[1];
       x_arcPlus[0] = fitterArcPlus->GetParameter(1);
       y_arcPlus[0] = fitterArcPlus->GetParameter(2);
       gr_arcPlus = new TGraph(1,x_arcPlus,y_arcPlus);
       gr_arcPlus->SetMarkerStyle(20);
       gr_arcPlus->SetMarkerSize(0.5);
       gr_arcPlus->SetMarkerColor(kRed);
       gr_arcPlus->Draw("P");
       fitterDraw = fitterArcPlus;
       }

    // Here is where the minus semicircle of the pixel shield is fit
    TVirtualFitter* fitterArcMinus ;
    fitterArcMinus = fitter ;
    TGraph* gr_arcMinus = gr_arc;
    TGraph* gr_arcMinusPlus = gr_arc;
    if (FitObject == "PixelShieldMinus")
       {
       fitterArcMinus = TVirtualFitter::Fitter( 0, 3 );
       fitterArcMinus->SetFCN(funArcMinus);
       // create the fitter, set the function that it will use, and set the parameters
       fitterArcMinus->SetParameter( 0, "R",  r0, 0.01, RSmin, RSmax ); // in cm
       fitterArcMinus->SetParameter( 1, "x0", x0, 0.01, 0.,  0.1 ); // in cm
       fitterArcMinus->SetParameter( 2, "y0", y0, 0.01, -0.15,  -0.05 ); // in cm
       
       Double_t arglistArcPlus[10] = {0.};
       // Execute the fit
       fitterArcMinus->ExecuteCommand( "MIGRAD", arglistArcPlus, 0 );
       
       // Draw an arc from 90 degrees to 270 degrees using the parameters from the fit
       TArc* arcMinus = new TArc( fitterArcMinus->GetParameter(1), fitterArcMinus->GetParameter(2), fitterArcMinus->GetParameter(0), 90, 270);
       arcMinus->SetFillStyle(0);
       arcMinus->SetLineColor(kBlack);
       arcMinus->SetLineWidth(2);
       arcMinus->Draw("same"); 
       Double_t x_arcMinus[1], y_arcMinus[1];
       x_arcMinus[0] = fitterArcMinus->GetParameter(1);
       y_arcMinus[0] = fitterArcMinus->GetParameter(2);
       gr_arcMinus = new TGraph(1,x_arcMinus,y_arcMinus);
       gr_arcMinus->SetMarkerStyle(20);
       gr_arcMinus->SetMarkerSize(0.5);
       gr_arcMinus->SetMarkerColor(kBlack);
       gr_arcMinus->Draw("P");
       
       // Draw an arc from -90 degrees to 90 degrees using previously determined values from the fit for the plus side of the pixel shield
       TArc* arcMinusPlus = new TArc( x0_PixelShieldPlus, y0_PixelShieldPlus, r0_PixelShieldPlus, -90, 90);
       arcMinusPlus->SetFillStyle(0);
       arcMinusPlus->SetLineColor(kRed);
       arcMinusPlus->SetLineWidth(2);
       arcMinusPlus->Draw("same"); 
       Double_t x_arcMinusPlus[1], y_arcMinusPlus[1];
       x_arcMinusPlus[0] = x0_PixelShieldPlus;
       y_arcMinusPlus[0] = y0_PixelShieldPlus;
       gr_arcMinusPlus = new TGraph(1,x_arcMinusPlus,y_arcMinusPlus);
       gr_arcMinusPlus->SetMarkerStyle(20);
       gr_arcMinusPlus->SetMarkerSize(0.5);
       gr_arcMinusPlus->SetMarkerColor(kRed);
       gr_arcMinusPlus->Draw("P");
       fitterDraw = fitterArcMinus;
       }

    // If the object is not the plus or minus sides of the pixel shield, draw a circle using the parameters from the fit
    if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport" || FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative")
    //if ( (FitObject != "PixelShieldPlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportPlus") /*&& FitObject != "PixelSupportEllipse"*/ && FitObject != "PixelSupportMinus")
      {
      cout << "======    fitter->GetParameter(1) = " << fitter->GetParameter(1) << endl;
      TArc* arc = new TArc( fitter->GetParameter(1), fitter->GetParameter(2), fitter->GetParameter(0) );
      arc->SetFillStyle(0);
      arc->SetLineColor(kRed);
      arc->SetLineWidth(2);
      arc->Draw("same");
      Double_t x_arc[1], y_arc[1];
      x_arc[0] = fitter->GetParameter(1);
      y_arc[0] = fitter->GetParameter(2);
      gr_arc = new TGraph(1,x_arc,y_arc);
      gr_arc->SetMarkerStyle(20);
      gr_arc->SetMarkerSize(0.5);
      gr_arc->SetMarkerColor(kRed);
      gr_arc->Draw("P");
      }

    TGraph* gr_arc0;
    x_arc0[0] = 0.;
    y_arc0[0] = 0.;
    gr_arc0 = new TGraph(1,x_arc0,y_arc0);
    gr_arc0->SetMarkerStyle(20);
    gr_arc0->SetMarkerSize(0.5);
    gr_arc0->SetMarkerColor(kBlue);
    // draw the (0,0) point for everything but the pixel support fit with an ellipse
    if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShieldEllipsePlus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
      {
      //plot circle with center at (0.0)
      TArc* arc0 = new TArc( 0., 0., fitter->GetParameter(0) );
      arc0->SetFillStyle(0);
      arc0->SetLineColor(kBlue);
      arc0->SetLineWidth(2);
      //arc0->Draw("same");
      gr_arc0->Draw("P");
      }

    if(FitObject == "PixelShieldEllipsePlus")
      {
      // plot ellipse with center at (0,0)
      TArc* arc0 = new TArc( 0., 0., fitterShieldEllipsePlus->GetParameter(0) );
      arc0->SetFillStyle(0);
      arc0->SetLineColor(kBlue);
      arc0->SetLineWidth(2);
      gr_arc0->Draw("P");
      }

    // draw the (0,0) point for the pixel support fit with an ellipse
    if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
     {
      std::cout << "********** Drawing Center **********" << std::endl;
      //plot circle with center at (0.0)
      TArc* arc0 = new TArc( 0., 0., fitterSupportEllipse->GetParameter(0) );
      arc0->SetFillStyle(0);
      arc0->SetLineColor(kBlue);
      arc0->SetLineWidth(2);
      //arc0->Draw("same");
      gr_arc0->Draw("P");
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

    // Create the stats box for everything that is not the minus side of the pixel shield,
    // the minus side of the pixel support, or the pixel support ellipse
    if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShieldEllipsePlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
      {
      TPaveText* res = new TPaveText(x1L-0.01, y1L-0.22, x2L+0.02, y2L-0.40, "brNDC");
      std::ostringstream legEntry;
      legEntry.str("");
      if(fitterDraw->GetParError(0) >= ErrPrecision)legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(1) >= ErrPrecision)legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) <<  fitterDraw->GetParameter(1)*10 <<" #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(2) >= ErrPrecision)legEntry << "y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      else legEntry << "y_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );
      res->SetFillStyle(0);
      res->SetTextAlign(12);
      res->SetTextColor(kRed);
      res->SetLineColor(kRed);
      res->SetTextFont(42);
      res->Draw("same");
      }

    // Create the stats box for the pixel support ellipse fit
    if(FitObject == "PixelSupportEllipse" || FitObject == "BeamPipeEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "PixelShieldEllipsePlus")
      {
      TPaveText* res = new TPaveText(x1L-0.01, y1L-0.22, x2L+0.02, y2L-0.40, "brNDC");
      std::ostringstream legEntry;
      legEntry.str("");
      if(fitterDraw->GetParError(0) >= ErrPrecision)legEntry << "r0_x (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << fitterDraw->GetParError(0) << " #pm " << r_Sys;
      else legEntry << "r0_x (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(0) << " #pm " << r_Sys;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(3) >= ErrPrecision)legEntry << "r0_y (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(3) << " #pm " << fitterDraw->GetParError(3) << " #pm " << r_Sys;
      else legEntry << "r0_y (cm) \t = \t" << fixed << setprecision(3) << fitterDraw->GetParameter(3) << " #pm " << r_Sys;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(1) >= ErrPrecision) legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << fitterDraw->GetParError(1)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterDraw->GetParameter(1)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(2) >= ErrPrecision) legEntry << "y_{0} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << fitterDraw->GetParError(2)*10 << " #pm " << x_Sys*10;
      else legEntry << "y_{0} (mm) \t = \t" << fitterDraw->GetParameter(2)*10 << " #pm " << x_Sys*10;
      res->AddText( legEntry.str().c_str() );
      res->SetFillStyle(0);
      res->SetTextAlign(12);
      res->SetTextColor(kRed);
      res->SetLineColor(kRed);
      res->SetTextFont(42);
      res->Draw("same");
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
      if(fitterDraw->GetParError(0) >= ErrPrecision) legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << r0_PixelShieldPlus << " #pm " << fitter->GetParError(0) << " #pm " << r_Sys;
      else legEntry << "R (cm) \t = \t" << fixed << setprecision(3) << r0_PixelShieldPlus << " #pm " << r_Sys;
      resPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(1) >= ErrPrecision) legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << x0_PixelShieldPlus*10 << " #pm " << fitter->GetParError(1)*10 << " #pm " << x_Sys*10;
      else legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << x0_PixelShieldPlus*10 << " #pm " << x_Sys*10;
      resPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      if(fitterDraw->GetParError(2) >= ErrPrecision) legEntry << "y_{0} (mm) \t = \t" << y0_PixelShieldPlus*10 << " #pm " << fitter->GetParError(2)*10 << " #pm " << x_Sys*10;
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
      legEntry << "R (cm) \t = \t" << fixed << setprecision(2) << fitterSupportMinus->GetParameter(0) << " #pm " << fitterSupportMinus->GetParError(0) << " #pm " << x_Sys;
      resSupportMinus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitterSupportMinus->GetParameter(1)*10 << " #pm " << fitterSupportMinus->GetParError(1)*10 << " #pm " << x_Sys*10;
      resSupportMinus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "y_{0} (mm) \t = \t" << fitterSupportMinus->GetParameter(2)*10 << " #pm " << fitterSupportMinus->GetParError(2)*10 << " #pm " << x_Sys*10;
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
      legEntry << "R (cm) \t = \t" << fixed << setprecision(2) << r0_PixelSupportPlus << " #pm " << fitter->GetParError(0) << " #pm " << x_Sys;
      resSupportPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << x0_PixelSupportPlus*10 << " #pm " << fitter->GetParError(1)*10 << " #pm " << x_Sys*10;
      resSupportPlus->AddText( legEntry.str().c_str() );
      legEntry.str("");
      legEntry << "y_{0} (mm) \t = \t" << y0_PixelSupportPlus*10 << " #pm " << fitter->GetParError(2)*10 << " #pm " << x_Sys*10;
      resSupportPlus->AddText( legEntry.str().c_str() );
      resSupportPlus->SetFillStyle(0);
      resSupportPlus->SetTextAlign(12);
      resSupportPlus->SetTextColor(kRed);
      resSupportPlus->SetLineColor(kRed);
      resSupportPlus->SetTextFont(42);
      resSupportPlus->Draw("same");
      }

      // Create the legend for all 2D XY map plots, include (0,0) point
      TLegend* legArc = new TLegend(0.75, 0.75, 0.95, 0.9, "");
      legArc->SetTextFont(42);
      legArc->SetTextSize(0.03);
      legArc->SetFillColor(kWhite);
      legArc->SetTextColor(kBlack);
      //legArc->AddEntry(gr_arc,"(x_{0}, y_{0}) from fit","P");
      legArc->AddEntry(gr_arc0,"(0,0)","P");
      legArc->Draw("same");

      // Add entries according to the object that was fit
      if( FitObject == "BeamPipe" || FitObject == "PixelShield" || FitObject == "PixelSupport" || FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative")
      //if((FitObject != "PixelShieldPlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportPlus" && FitObject != "PixelSupportEllipse") && FitObject != PixelSupportMinus)
        {
        legArc->AddEntry(gr_arc,"(x_{0}, y_{0}) from fit","P");
        }
      if(FitObject == "PixelShieldPlus")
        {
        legArc->AddEntry(gr_arcPlus,"x_{0}, y_{0} from fit","P");
        }
      if(FitObject == "PixelShieldMinus")
        {
        // include entry for the plus side of the pixel shield since it will be superimposed on the same plot
        legArc->AddEntry(gr_arcMinus,"x_{0}, y_{0} for Minus","P");
        legArc->AddEntry(gr_arcMinusPlus,"x_{0}, y_{0} for Plus","P");
        }
      if(FitObject == "PixelSupportMinus")
        {
        legArc->AddEntry(gr_arcSupportMinus,"x_{0}, y_{0} for Minus","P");
        legArc->AddEntry(gr_arcSupportMinusPlus,"x_{0}, y_{0} for Plus","P");
        }
      if(FitObject == "PixelSupportEllipse")
        {
        legArc->AddEntry(gr_ellipseSupport,"x_{0}, y_{0} from fit","P");
        }
      if(FitObject == "PixelShieldEllipsePlus")
        {
        legArc->AddEntry(gr_ellipseShieldPlus,"x_{0}, y_{0} from fit", "P");
        }
      if(FitObject == "PixelShieldEllipse")
        {
        legArc->AddEntry(gr_ellipseSupport,"x_{0}, y_{0} from fit","P");
        }
      if(FitObject == "BeamPipeEllipse")
        {
        legArc->AddEntry(gr_ellipseSupport,"x_{0}, y_{0} form fit","P");
        }
    if ( k > -6 )
    {
      resZ[k+5] = 0.5*(k*5 + (k+1)*5);
      resR[k+5] = fitter->GetParameter(0);
      errR[k+5] = fitter->GetParError(0);
      resx0[k+5] = fitter->GetParameter(1)*10;
      errx0[k+5] = fitter->GetParError(1)*10;
      resy0[k+5] = fitter->GetParameter(2)*10;
      errx0[k+5] = fitter->GetParError(2)*10;
    }

    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Fit.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit.png"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit.root"));

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
    if(FitObject == "PixelSupportMinus" || FitObject == "PixelSupportEllipse")
      {
      h_RhoPhi->GetYaxis()->SetRangeUser(19, 23);
      }
    //h_RhoPhi->GetYaxis()->SetRangeUser(RSmin, RSmax);
    h_RhoPhi->Draw("colz");

    //TF1 *bpAlt = new TF1("bpAlt","sqrt((21.699*cos(x)-0.081)^2 + (21.699*sin(x)-0.345)^2)",-3.15,3.15);
    // Create function that will be plotted on the Rho-Phi plots, but not on the plots for the minus side of the pixel shield,
    // the minus side of the pixel support, and the ellipse fit for the pixel support
    TF1 *bpAlt = new TF1("bpAlt",func_ArcRhoPhi,-3.15,6.3,3);
    if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShieldEllipsePlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
      {
      // use parameters from the fitter
      bpAlt->SetParameter(0, fitter->GetParameter(0));
      bpAlt->SetParameter(1, fitter->GetParameter(1));
      bpAlt->SetParameter(2, fitter->GetParameter(2));
      bpAlt->SetLineColor(kRed);
      bpAlt->SetLineWidth(2);
      bpAlt ->Draw("same");
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      }

    // draw the ellipse in rhophi
    TF1 *bpEllipseAlt = new TF1("bpAlt",func_EllipseRhoPhi,-3.15,3.15,4);
    if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
      {
      // use parameters from the fitter
      bpEllipseAlt->SetParameter(0, fitterSupportEllipse->GetParameter(0));
      bpEllipseAlt->SetParameter(1, fitterSupportEllipse->GetParameter(1));
      bpEllipseAlt->SetParameter(2, fitterSupportEllipse->GetParameter(2));
      bpEllipseAlt->SetParameter(3, (fitterSupportEllipse->GetParameter(3)));
      bpEllipseAlt->SetLineColor(kRed);
      bpEllipseAlt->SetLineWidth(2);
      bpEllipseAlt ->Draw("same");
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      }

    // Draw the ellipse in rhophi for the pixel shield plus
    TF1 *bpShieldEllipsePlusAlt = new TF1("bpAlt",func_EllipseRhoPhi,-1.575,1.575,4);
    if(FitObject == "PixelShieldEllipsePlus")
      {
      // use parameters from the fitter
      bpShieldEllipsePlusAlt->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0));
      bpShieldEllipsePlusAlt->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1));
      bpShieldEllipsePlusAlt->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2));
      bpShieldEllipsePlusAlt->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3));

      bpShieldEllipsePlusAlt->SetLineColor(kRed);
      bpShieldEllipsePlusAlt->SetLineWidth(2);
      bpShieldEllipsePlusAlt->Draw("same");
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      }

    // Create functions that will be plotted on the Rho-Phi plots for the minus side of the pixel shield
    // The functions for the minus side are split in two because the plot is centered on the plus side
    TF1 *bpAltMinus1 = new TF1("bpAlt",func_ArcRhoPhi,1.575, 3.15,3);
    TF1 *bpAltMinus2 = new TF1("bpAlt",func_ArcRhoPhi,-3.15, -1.575,3);
    TF1 *bpAltPlus = new TF1("bpAlt",func_ArcRhoPhi,-1.575, 1.575,3);
    if(FitObject == "PixelShieldMinus")
      {
      // set parameters for half of the minus side from the fitter
      bpAltMinus1->SetParameter(0, fitterArcMinus->GetParameter(0));
      bpAltMinus1->SetParameter(1, fitterArcMinus->GetParameter(1));
      bpAltMinus1->SetParameter(2, fitterArcMinus->GetParameter(2));
      bpAltMinus1->SetLineColor(kRed);
      bpAltMinus1->SetLineWidth(2);
      bpAltMinus1->Draw("same");
      
      // set parameters for the other half of the minus side from the fitter
      bpAltMinus2->SetParameter(0, fitterArcMinus->GetParameter(0));
      bpAltMinus2->SetParameter(1, fitterArcMinus->GetParameter(1));
      bpAltMinus2->SetParameter(2, fitterArcMinus->GetParameter(2));
      bpAltMinus2->SetLineColor(kRed);
      bpAltMinus2->SetLineWidth(2);
      bpAltMinus2->Draw("same");
      
      // set parameters for the plus side using stored values from the previous fit
      bpAltPlus->SetParameter(0, r0_PixelShieldPlus);
      bpAltPlus->SetParameter(1, x0_PixelShieldPlus);
      bpAltPlus->SetParameter(2, y0_PixelShieldPlus);
      bpAltPlus->SetLineColor(kRed);
      bpAltPlus->SetLineWidth(2);
      bpAltPlus->Draw("same");
      
      // save
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      }

    // create the plots in rhophi for the pixel support minus side fit
    TF1 *bpAltSupportMinus1 = new TF1("bpAlt",func_ArcRhoPhi,1.575, 3.15,3);
    TF1 *bpAltSupportMinus2 = new TF1("bpAlt",func_ArcRhoPhi,-3.15, -1.575,3);
    TF1 *bpAltSupportPlus = new TF1("bpAlt",func_ArcRhoPhi,-1.575, 1.575,3);
    if(FitObject == "PixelSupportMinus")
      {
      // set parameters for half of the minus side from the fitter
      bpAltSupportMinus1->SetParameter(0, fitterSupportMinus->GetParameter(0));
      bpAltSupportMinus1->SetParameter(1, fitterSupportMinus->GetParameter(1));
      bpAltSupportMinus1->SetParameter(2, fitterSupportMinus->GetParameter(2));
      bpAltSupportMinus1->SetLineColor(kRed);
      bpAltSupportMinus1->SetLineWidth(2);
      bpAltSupportMinus1->Draw("same");

      // set parameters for the other half of the minus side from the fitter
      bpAltSupportMinus2->SetParameter(0, fitterSupportMinus->GetParameter(0));
      bpAltSupportMinus2->SetParameter(1, fitterSupportMinus->GetParameter(1));
      bpAltSupportMinus2->SetParameter(2, fitterSupportMinus->GetParameter(2));
      bpAltSupportMinus2->SetLineColor(kRed);
      bpAltSupportMinus2->SetLineWidth(2);
      bpAltSupportMinus2->Draw("same");

      // set parameters for the plus side using stored values from the previous fit
      bpAltSupportPlus->SetParameter(0, r0_PixelSupportPlus);
      bpAltSupportPlus->SetParameter(1, x0_PixelSupportPlus);
      bpAltSupportPlus->SetParameter(2, y0_PixelSupportPlus);
      bpAltSupportPlus->SetLineColor(kRed);
      bpAltSupportPlus->SetLineWidth(2);
      bpAltSupportPlus->Draw("same");

      // save
      cPlots->Update();
      cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));
      }

   if (flag_Sys == 1)
       {
       // x variation
       // create the functions for the systematic variation of x, but not for the minus side of the pixel shield
       TF1 *bpAlt_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,6.3,3);
       TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,6.3,3);
       if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShieldEllipsePlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
         {
         // set parameters using values from the fitter
         bpAlt_xp->SetParameter(0, fitter->GetParameter(0));
         bpAlt_xp->SetParameter(1, fitter->GetParameter(1)+x_Sys);
         bpAlt_xp->SetParameter(2, fitter->GetParameter(2));
         bpAlt_xp->SetLineColor(kBlack);
         bpAlt_xp->SetLineWidth(2);
         bpAlt_xp ->Draw("same");

         //TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_xm->SetParameter(0, fitter->GetParameter(0));
         bpAlt_xm->SetParameter(1, fitter->GetParameter(1)-x_Sys);
         bpAlt_xm->SetParameter(2, fitter->GetParameter(2));
         bpAlt_xm->SetLineColor(kBlack);
         bpAlt_xm->SetLineWidth(2);
         bpAlt_xm ->Draw("same");
         }

       // draw the x variation of the ellipse in rhophi
       TF1 *bpAltEllipse_xp = new TF1("bpAlt_xp",func_EllipseRhoPhi,-3.15,3.15,4);
       TF1 *bpAltEllipse_xm = new TF1("bpAlt_xm",func_EllipseRhoPhi,-3.15,3.15,4);
       if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
         {
         // set parameters using values from the fitter
         bpAltEllipse_xp->SetParameter(0, fitterSupportEllipse->GetParameter(0));
         bpAltEllipse_xp->SetParameter(1, fitterSupportEllipse->GetParameter(1)+x_Sys);
         bpAltEllipse_xp->SetParameter(2, fitterSupportEllipse->GetParameter(2));
         bpAltEllipse_xp->SetParameter(3, (fitterSupportEllipse->GetParameter(3)));
         bpAltEllipse_xp->SetLineColor(kBlack);
         bpAltEllipse_xp->SetLineWidth(2);
         bpAltEllipse_xp->Draw("same");

         //TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,3.15,3);
         bpAltEllipse_xm->SetParameter(0, fitterSupportEllipse->GetParameter(0));
         bpAltEllipse_xm->SetParameter(1, fitterSupportEllipse->GetParameter(1)-x_Sys);
         bpAltEllipse_xm->SetParameter(2, fitterSupportEllipse->GetParameter(2));
         bpAltEllipse_xm->SetParameter(3, (fitterSupportEllipse->GetParameter(3)));
         bpAltEllipse_xm->SetLineColor(kBlack);
         bpAltEllipse_xm->SetLineWidth(2);
         bpAltEllipse_xm->Draw("same");

         bpEllipseAlt->Draw("same");
         cPlots->Update();
         }

       TF1 *bpAltShieldEllipsePlus_xp = new TF1("bpAlt_xp",func_EllipseRhoPhi,-1.575,1.575,4);
       TF1 *bpAltShieldEllipsePlus_xm = new TF1("bpAlt_xm",func_EllipseRhoPhi,-1.575,1.575,4);
       if(FitObject == "PixelShieldEllipsePlus")
         {
         bpAltShieldEllipsePlus_xp->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0));
         bpAltShieldEllipsePlus_xp->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1)+x_Sys);
         bpAltShieldEllipsePlus_xp->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2));
         bpAltShieldEllipsePlus_xp->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3));
         bpAltShieldEllipsePlus_xp->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_xp->SetLineWidth(2);
         bpAltShieldEllipsePlus_xp->Draw("same");

         bpAltShieldEllipsePlus_xm->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0));
         bpAltShieldEllipsePlus_xm->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1)-x_Sys);
         bpAltShieldEllipsePlus_xm->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2));
         bpAltShieldEllipsePlus_xm->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3));
         bpAltShieldEllipsePlus_xm->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_xm->SetLineWidth(2);
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
         bpAltMinus1_xp->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus1_xp->SetParameter(1, fitterArcMinus->GetParameter(1)+x_Sys);
         bpAltMinus1_xp->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus1_xp->SetLineColor(kBlack);
         bpAltMinus1_xp->SetLineWidth(2);
         bpAltMinus1_xp ->Draw("same");

         // set the parameters for the positive deviation of the other half of the minus side
         bpAltMinus2_xp->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus2_xp->SetParameter(1, fitterArcMinus->GetParameter(1)+x_Sys);
         bpAltMinus2_xp->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus2_xp->SetLineColor(kBlack);
         bpAltMinus2_xp->SetLineWidth(2);
         bpAltMinus2_xp ->Draw("same");

         // set the parameters for the negative deviation of the first half of the minus side
         bpAltMinus1_xm->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus1_xm->SetParameter(1, fitterArcMinus->GetParameter(1)-x_Sys);
         bpAltMinus1_xm->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus1_xm->SetLineColor(kBlack);
         bpAltMinus1_xm->SetLineWidth(2);
         bpAltMinus1_xm ->Draw("same");

         // set the parameters for the negative deviation of the other half of the minus side
         bpAltMinus2_xm->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus2_xm->SetParameter(1, fitterArcMinus->GetParameter(1)-x_Sys);
         bpAltMinus2_xm->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus2_xm->SetLineColor(kBlack);
         bpAltMinus2_xm->SetLineWidth(2);
         bpAltMinus2_xm ->Draw("same");

         // set the parameters for the positive deviation of the plus side
         bpAltPlus_xp->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_xp->SetParameter(1, x0_PixelShieldPlus+x_Sys);
         bpAltPlus_xp->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_xp->SetLineColor(kBlack);
         bpAltPlus_xp->SetLineWidth(2);
         bpAltPlus_xp ->Draw("same");

         // set the parameters for the negative deviation of the minus side
         bpAltPlus_xm->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_xm->SetParameter(1, x0_PixelShieldPlus-x_Sys);
         bpAltPlus_xm->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_xm->SetLineColor(kBlack);
         bpAltPlus_xm->SetLineWidth(2);
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
         bpSupportAltMinus1_xp->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus1_xp->SetParameter(1, fitterSupportMinus->GetParameter(1)+x_Sys);
         bpSupportAltMinus1_xp->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus1_xp->SetLineColor(kBlack);
         bpSupportAltMinus1_xp->SetLineWidth(2);
         bpSupportAltMinus1_xp ->Draw("same");

         // set the parameters for the positive deviation of the other half of the minus side
         bpSupportAltMinus2_xp->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus2_xp->SetParameter(1, fitterSupportMinus->GetParameter(1)+x_Sys);
         bpSupportAltMinus2_xp->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus2_xp->SetLineColor(kBlack);
         bpSupportAltMinus2_xp ->Draw("same");

         // set the parameters for the negative deviation of the first half of the minus side
         bpSupportAltMinus1_xm->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus1_xm->SetParameter(1, fitterSupportMinus->GetParameter(1)-x_Sys);
         bpSupportAltMinus1_xm->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus1_xm->SetLineColor(kBlack);
         bpSupportAltMinus1_xm->SetLineWidth(2);
         bpSupportAltMinus1_xm ->Draw("same");

         // set the parameters for the negative deviation of the other half of the minus side
         bpSupportAltMinus2_xm->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus2_xm->SetParameter(1, fitterSupportMinus->GetParameter(1)-x_Sys);
         bpSupportAltMinus2_xm->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus2_xm->SetLineColor(kBlack);
         bpSupportAltMinus2_xm->SetLineWidth(2);
         bpSupportAltMinus2_xm ->Draw("same");

         // set the parameters for the positive deviation of the plus side
         bpSupportAltPlus_xp->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_xp->SetParameter(1, x0_PixelSupportPlus+x_Sys);
         bpSupportAltPlus_xp->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_xp->SetLineColor(kBlack);
         bpSupportAltPlus_xp->SetLineWidth(2);
         bpSupportAltPlus_xp ->Draw("same");

         // set the parameters for the negative deviation of the minus side
         bpSupportAltPlus_xm->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_xm->SetParameter(1, x0_PixelSupportPlus-x_Sys);
         bpSupportAltPlus_xm->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_xm->SetLineColor(kBlack);
         bpSupportAltPlus_xm->SetLineWidth(2);
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
       if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShieldEllipsePlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
         {
         // set parameters for the positive deviation
         bpAlt_yp->SetParameter(0, fitter->GetParameter(0));
         bpAlt_yp->SetParameter(1, fitter->GetParameter(1));
         bpAlt_yp->SetParameter(2, fitter->GetParameter(2)+x_Sys);
         bpAlt_yp->SetLineColor(kBlack);
         bpAlt_yp->SetLineWidth(2);
         bpAlt_yp ->Draw("same");
         
         // set parameters for the negative deviation
         //TF1 *bpAlt_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_ym->SetParameter(0, fitter->GetParameter(0));
         bpAlt_ym->SetParameter(1, fitter->GetParameter(1));
         bpAlt_ym->SetParameter(2, fitter->GetParameter(2)-x_Sys);
         bpAlt_ym->SetLineColor(kBlack);
         bpAlt_ym->SetLineWidth(2);
         bpAlt_ym ->Draw("same");
         }

       // draw the y variation of the pixel support ellipse in the rhophi plos
       TF1 *bpAltEllipse_yp = new TF1("bpAlt_yp",func_EllipseRhoPhi,-3.15,3.15,4);
       TF1 *bpAltEllipse_ym = new TF1("bpAlt_ym",func_EllipseRhoPhi,-3.15,3.15,4);
       if(FitObject == "PixelShieldEllipse" || FitObject == "PixelSupportEllipse" || FitObject == "BeamPipeEllipse")
         {
         // set parameters for the positive deviation
         bpAltEllipse_yp->SetParameter(0, fitterSupportEllipse->GetParameter(0));
         bpAltEllipse_yp->SetParameter(1, fitterSupportEllipse->GetParameter(1));
         bpAltEllipse_yp->SetParameter(2, fitterSupportEllipse->GetParameter(2)+x_Sys);
         bpAltEllipse_yp->SetParameter(3, fitterSupportEllipse->GetParameter(3));
         bpAltEllipse_yp->SetLineColor(kBlack);
         bpAltEllipse_yp->SetLineWidth(2);
         bpAltEllipse_yp ->Draw("same");

         // set parameters for the negative deviation
         bpAltEllipse_ym->SetParameter(0, fitterSupportEllipse->GetParameter(0));
         bpAltEllipse_ym->SetParameter(1, fitterSupportEllipse->GetParameter(1));
         bpAltEllipse_ym->SetParameter(2, fitterSupportEllipse->GetParameter(2)-x_Sys);
         bpAltEllipse_ym->SetParameter(3, fitterSupportEllipse->GetParameter(3));
         bpAltEllipse_ym->SetLineColor(kBlack);
         bpAltEllipse_ym->SetLineWidth(2);
         bpAltEllipse_ym ->Draw("same");

         bpEllipseAlt->Draw("same");
         cPlots->Update();
         }

       TF1 *bpAltShieldEllipsePlus_yp = new TF1("bpAlt_yp",func_EllipseRhoPhi,-1.575,1.575,4);
       TF1 *bpAltShieldEllipsePlus_ym = new TF1("bpAlt_ym",func_EllipseRhoPhi,-1.575,1.575,4);
       if(FitObject == "PixelShieldEllipsePlus")
         {
         // set parameters for the positive deviaiton
         bpAltShieldEllipsePlus_yp->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0));
         bpAltShieldEllipsePlus_yp->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1));
         bpAltShieldEllipsePlus_yp->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2)+x_Sys);
         bpAltShieldEllipsePlus_yp->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3));
         bpAltShieldEllipsePlus_yp->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_yp->SetLineWidth(2);
         bpAltShieldEllipsePlus_yp->Draw("same");

         bpAltShieldEllipsePlus_ym->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0));
         bpAltShieldEllipsePlus_ym->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1));
         bpAltShieldEllipsePlus_ym->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2)-x_Sys);
         bpAltShieldEllipsePlus_ym->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3));
         bpAltShieldEllipsePlus_ym->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_ym->SetLineWidth(2);
         bpAltShieldEllipsePlus_ym->Draw("same");

         bpShieldEllipsePlusAlt->Draw("same");
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
         bpAltMinus1_yp->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus1_yp->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus1_yp->SetParameter(2, fitterArcMinus->GetParameter(2)+x_Sys);
         bpAltMinus1_yp->SetLineColor(kBlack);
         bpAltMinus1_yp->SetLineWidth(2);
         bpAltMinus1_yp ->Draw("same");
         
         // set the parameters for the positive deviation of the other half of the minus side
         bpAltMinus2_yp->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus2_yp->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus2_yp->SetParameter(2, fitterArcMinus->GetParameter(2)+x_Sys);
         bpAltMinus2_yp->SetLineColor(kBlack);
         bpAltMinus2_yp->SetLineWidth(2);
         bpAltMinus2_yp ->Draw("same");
         
         // set the parameters for the negative deviation of one of the halves of the minus side
         bpAltMinus1_ym->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus1_ym->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus1_ym->SetParameter(2, fitterArcMinus->GetParameter(2)-x_Sys);
         bpAltMinus1_ym->SetLineColor(kBlack);
         bpAltMinus1_ym->SetLineWidth(2);
         bpAltMinus1_ym ->Draw("same");
         
         // set the parameters for the negative deviation of the other half of the minus side
         bpAltMinus2_ym->SetParameter(0, fitterArcMinus->GetParameter(0));
         bpAltMinus2_ym->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus2_ym->SetParameter(2, fitterArcMinus->GetParameter(2)-x_Sys);
         bpAltMinus2_ym->SetLineColor(kBlack);
         bpAltMinus2_ym->SetLineWidth(2);
         bpAltMinus2_ym ->Draw("same");
         
         // set the parameters for the positive deviation of the plus side
         bpAltPlus_yp->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_yp->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_yp->SetParameter(2, y0_PixelShieldPlus+x_Sys);
         bpAltPlus_yp->SetLineColor(kBlack);
         bpAltPlus_yp->SetLineWidth(2);
         bpAltPlus_yp ->Draw("same");
         
         // set the parameters for the negative deviation of the plus side
         bpAltPlus_ym->SetParameter(0, r0_PixelShieldPlus);
         bpAltPlus_ym->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_ym->SetParameter(2, y0_PixelShieldPlus-x_Sys);
         bpAltPlus_ym->SetLineColor(kBlack);
         bpAltPlus_ym->SetLineWidth(2);
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
         bpSupportAltMinus1_yp->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus1_yp->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus1_yp->SetParameter(2, fitterSupportMinus->GetParameter(2)+x_Sys);
         bpSupportAltMinus1_yp->SetLineColor(kBlack);
         bpSupportAltMinus1_yp->SetLineWidth(2);
         bpSupportAltMinus1_yp ->Draw("same");

         // set the parameters for the negative deviation of one of the halves of the minus side
         bpSupportAltMinus2_yp->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus2_yp->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus2_yp->SetParameter(2, fitterSupportMinus->GetParameter(2)+x_Sys);
         bpSupportAltMinus2_yp->SetLineColor(kBlack);
         bpSupportAltMinus2_yp->SetLineWidth(2);
         bpSupportAltMinus2_yp ->Draw("same");

         // set the parameters for the negative deviation of one of the halves of the minus side
         bpSupportAltMinus1_ym->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus1_ym->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus1_ym->SetParameter(2, fitterSupportMinus->GetParameter(2)-x_Sys);
         bpSupportAltMinus1_ym->SetLineColor(kBlack);
         bpSupportAltMinus1_ym->SetLineWidth(2);
         bpSupportAltMinus1_ym ->Draw("same");

         // set the parameters for the negative deviation of the other half of the minus side
         bpSupportAltMinus2_ym->SetParameter(0, fitterSupportMinus->GetParameter(0));
         bpSupportAltMinus2_ym->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus2_ym->SetParameter(2, fitterSupportMinus->GetParameter(2)-x_Sys);
         bpSupportAltMinus2_ym->SetLineColor(kBlack);
         bpSupportAltMinus2_ym->SetLineWidth(2);
         bpSupportAltMinus2_ym ->Draw("same");
         // set the parameters for the positive deviation of the plus side
         bpSupportAltPlus_yp->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_yp->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_yp->SetParameter(2, y0_PixelSupportPlus+x_Sys);
         bpSupportAltPlus_yp->SetLineColor(kBlack);
         bpSupportAltPlus_yp->SetLineWidth(2);
         bpSupportAltPlus_yp ->Draw("same");

         // set the parameters for the negative deviation of the plus side
         bpSupportAltPlus_ym->SetParameter(0, r0_PixelSupportPlus);
         bpSupportAltPlus_ym->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_ym->SetParameter(2, y0_PixelSupportPlus-x_Sys);
         bpSupportAltPlus_ym->SetLineColor(kBlack);
         bpSupportAltPlus_ym->SetLineWidth(2);
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
       if(FitObject != "PixelShieldEllipse" && FitObject != "PixelShieldEllipsePlus" && FitObject != "PixelShieldMinus" && FitObject != "PixelSupportMinus" && FitObject != "PixelSupportEllipse" && FitObject != "BeamPipeEllipse")
         {
         // set the parameters for the positive deviation
         //TF1 *bpAlt_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_rp->SetParameter(0, fitter->GetParameter(0)+r_Sys);
         bpAlt_rp->SetParameter(1, fitter->GetParameter(1));
         bpAlt_rp->SetParameter(2, fitter->GetParameter(2));
         bpAlt_rp->SetLineColor(kBlack);
         bpAlt_rp->SetLineWidth(2);
         bpAlt_rp ->Draw("same");

         // set the parameters for the negative deviation
         //TF1 *bpAlt_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-3.15,3.15,3);
         bpAlt_rm->SetParameter(0, fitter->GetParameter(0)-r_Sys);
         bpAlt_rm->SetParameter(1, fitter->GetParameter(1));
         bpAlt_rm->SetParameter(2, fitter->GetParameter(2));
         bpAlt_rm->SetLineColor(kBlack);
         bpAlt_rm->SetLineWidth(2);
         bpAlt_rm ->Draw("same");
         }

       // draw the radius variation for the pixel support ellipse on the rhophi plots
       // create the functions for the positive and negative deviation of the radius.
       TF1 *bpAltEllipse_rp = new TF1("bpAlt_rp",func_EllipseRhoPhi,-3.15,3.15,4);
       TF1 *bpAltEllipse_rm = new TF1("bpAlt_rm",func_EllipseRhoPhi,-3.15,3.15,4);
       if(FitObject == "PixelSupportEllipse" || FitObject == "PixelShieldEllipse" || FitObject == "BeamPipeEllipse")
         {
         // set the parameters for the positive deviation
         bpAltEllipse_rp->SetParameter(0, fitterSupportEllipse->GetParameter(0)+r_Sys);
         bpAltEllipse_rp->SetParameter(1, fitterSupportEllipse->GetParameter(1));
         bpAltEllipse_rp->SetParameter(2, fitterSupportEllipse->GetParameter(2));
         bpAltEllipse_rp->SetParameter(3, (fitterSupportEllipse->GetParameter(3))+r_Sys);
         bpAltEllipse_rp->SetLineColor(kBlack);
         bpAltEllipse_rp->SetLineWidth(2);
         bpAltEllipse_rp->Draw("same");

         // set the parameters for the negative deviation
         bpAltEllipse_rm->SetParameter(0, fitterSupportEllipse->GetParameter(0)-r_Sys);
         bpAltEllipse_rm->SetParameter(1, fitterSupportEllipse->GetParameter(1));
         bpAltEllipse_rm->SetParameter(2, fitterSupportEllipse->GetParameter(2));
         bpAltEllipse_rm->SetParameter(3, (fitterSupportEllipse->GetParameter(3))-r_Sys);
         bpAltEllipse_rm->SetLineColor(kBlack);
         bpAltEllipse_rm->SetLineWidth(2);
         bpAltEllipse_rm->Draw("same");

         // draw the central function, update the plot
         bpEllipseAlt->Draw("same");
         cPlots->Update();
         }

       TF1 *bpAltShieldEllipsePlus_rp = new TF1("bpAlt_rp",func_EllipseRhoPhi,-1.575,1.575,4);
       TF1 *bpAltShieldEllipsePlus_rm = new TF1("bpAlt_rm",func_EllipseRhoPhi,-1.575,1.575,4);
       if(FitObject == "PixelShieldEllipsePlus")
         {
         bpAltShieldEllipsePlus_rp->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0)+r_Sys);
         bpAltShieldEllipsePlus_rp->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1));
         bpAltShieldEllipsePlus_rp->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2));
         bpAltShieldEllipsePlus_rp->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3)+r_Sys);
         bpAltShieldEllipsePlus_rp->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_rp->SetLineWidth(2);
         bpAltShieldEllipsePlus_rp->Draw("same");

         bpAltShieldEllipsePlus_rm->SetParameter(0, fitterShieldEllipsePlus->GetParameter(0)-r_Sys);
         bpAltShieldEllipsePlus_rm->SetParameter(1, fitterShieldEllipsePlus->GetParameter(1));
         bpAltShieldEllipsePlus_rm->SetParameter(2, fitterShieldEllipsePlus->GetParameter(2));
         bpAltShieldEllipsePlus_rm->SetParameter(3, fitterShieldEllipsePlus->GetParameter(3)-r_Sys);
         bpAltShieldEllipsePlus_rm->SetLineColor(kBlack);
         bpAltShieldEllipsePlus_rm->SetLineWidth(2);
         bpAltShieldEllipsePlus_rm->Draw("same");

         bpShieldEllipsePlusAlt->Draw("same");
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
         bpAltMinus1_rp->SetParameter(0, fitterArcMinus->GetParameter(0)+r_Sys);
         bpAltMinus1_rp->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus1_rp->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus1_rp->SetLineColor(kBlack);
         bpAltMinus1_rp->SetLineWidth(2);
         bpAltMinus1_rp->Draw("same");

         // set the parameters for the positive deviation of rho for the other half of the minus side
         bpAltMinus2_rp->SetParameter(0, fitterArcMinus->GetParameter(0)+r_Sys);
         bpAltMinus2_rp->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus2_rp->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus2_rp->SetLineColor(kBlack);
         bpAltMinus2_rp->SetLineWidth(2);
         bpAltMinus2_rp->Draw("same");

         // set the parameters for the negative deviation of rho for one of the halves of the minus side
         bpAltMinus1_rm->SetParameter(0, fitterArcMinus->GetParameter(0)-r_Sys);
         bpAltMinus1_rm->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus1_rm->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus1_rm->SetLineColor(kBlack);
         bpAltMinus1_rm->SetLineWidth(2);
         bpAltMinus1_rm->Draw("same");

         // set the parameters for the negative deviation of rho for the other half of the minus side
         bpAltMinus2_rm->SetParameter(0, fitterArcMinus->GetParameter(0)-r_Sys);
         bpAltMinus2_rm->SetParameter(1, fitterArcMinus->GetParameter(1));
         bpAltMinus2_rm->SetParameter(2, fitterArcMinus->GetParameter(2));
         bpAltMinus2_rm->SetLineColor(kBlack);
         bpAltMinus2_rm->SetLineWidth(2);
         bpAltMinus2_rm->Draw("same");

         // set the parameters for the positive deviation of rho for the plus side
         bpAltPlus_rp->SetParameter(0, r0_PixelShieldPlus+r_Sys);
         bpAltPlus_rp->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_rp->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_rp->SetLineColor(kBlack);
         bpAltPlus_rp->SetLineWidth(2);
         bpAltPlus_rp->Draw("same");

         // set the parameters for the negative deviation of rho for the plus side
         bpAltPlus_rm->SetParameter(0, r0_PixelShieldPlus-r_Sys);
         bpAltPlus_rm->SetParameter(1, x0_PixelShieldPlus);
         bpAltPlus_rm->SetParameter(2, y0_PixelShieldPlus);
         bpAltPlus_rm->SetLineColor(kBlack);
         bpAltPlus_rm->SetLineWidth(2);
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
         bpSupportAltMinus1_rp->SetParameter(0, fitterSupportMinus->GetParameter(0)+r_Sys);
         bpSupportAltMinus1_rp->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus1_rp->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus1_rp->SetLineColor(kBlack);
         bpSupportAltMinus1_rp->SetLineWidth(2);
         bpSupportAltMinus1_rp->Draw("same");

         // set the parameters for the positive deviation of rho for the other half of the minus side
         bpSupportAltMinus2_rp->SetParameter(0, fitterSupportMinus->GetParameter(0)+r_Sys);
         bpSupportAltMinus2_rp->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus2_rp->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus2_rp->SetLineColor(kBlack);
         bpSupportAltMinus2_rp->SetLineWidth(2);
         bpSupportAltMinus2_rp->Draw("same");

         // set the parameters for the negative deviation of rho for one of the halves of the minus side
         bpSupportAltMinus1_rm->SetParameter(0, fitterSupportMinus->GetParameter(0)-r_Sys);
         bpSupportAltMinus1_rm->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus1_rm->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus1_rm->SetLineColor(kBlack);
         bpSupportAltMinus1_rm->SetLineWidth(2);
         bpSupportAltMinus1_rm->Draw("same");

         // set the parameters for the negative deviation of rho for the other half of the minus side
         bpSupportAltMinus2_rm->SetParameter(0, fitterSupportMinus->GetParameter(0)-r_Sys);
         bpSupportAltMinus2_rm->SetParameter(1, fitterSupportMinus->GetParameter(1));
         bpSupportAltMinus2_rm->SetParameter(2, fitterSupportMinus->GetParameter(2));
         bpSupportAltMinus2_rm->SetLineColor(kBlack);
         bpSupportAltMinus2_rm->SetLineWidth(2);
         bpSupportAltMinus2_rm->Draw("same");

         // set the parameters for the positive deviation of rho for the plus side
         bpSupportAltPlus_rp->SetParameter(0, r0_PixelSupportPlus+r_Sys);
         bpSupportAltPlus_rp->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_rp->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_rp->SetLineColor(kBlack);
         bpSupportAltPlus_rp->SetLineWidth(2);
         bpSupportAltPlus_rp->Draw("same");

         // set the parameters for the negative deviation of rho for the plus side
         bpSupportAltPlus_rm->SetParameter(0, r0_PixelSupportPlus-r_Sys);
         bpSupportAltPlus_rm->SetParameter(1, x0_PixelSupportPlus);
         bpSupportAltPlus_rm->SetParameter(2, y0_PixelSupportPlus);
         bpSupportAltPlus_rm->SetLineColor(kBlack);
         bpSupportAltPlus_rm->SetLineWidth(2);
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
       hYderivative->GetXaxis()->SetTitle("y [cm]");
       hYderivative->GetYaxis()->SetTitle("y Derivative");
       hYderivative->SetLineWidth(2);

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
       std::cout<<"Fit for Bottom Rail"<<std::endl;
       TF1 *f2Bottom = new TF1("f2Bottom",fun2,-7,7,2);
       f2Bottom -> SetParameter(0, -19.7);
       f2Bottom -> SetParameter(1, 0.);
       f2Bottom->SetLineWidth(2);
       f2Bottom->SetLineColor(kRed);
       hYderivative2D->GetXaxis()->SetRangeUser(-7., -7.);
       hYderivative2D->GetYaxis()->SetRangeUser(-20., -19.5);
       hYderivative2D->Fit("f2Bottom","R");//fit only this Range defind in function
       YRailBottom = f2Bottom->GetParameter(0);
       std::cout<<"End Fit for Bottom Rail"<<std::endl;

       hYderivative2D ->GetYaxis()->SetRangeUser(-RSmax, -Rmin);
       hYderivative2D ->GetXaxis()->SetRangeUser(-15., 15.);
       hYderivative2D->Draw("COLZ");
       f2Bottom ->Draw("same");
       cPlots->Update();
       cPlots->SaveAs("Plots/yDerivative2DBottom.png");

       std::cout<<"Fit for Top Rail"<<std::endl;
       f2Bottom -> SetParameter(0, 19.);
       f2Bottom -> SetParameter(1, 0.);
       hYderivative2D->GetXaxis()->SetRangeUser(-7., -7.);
       hYderivative2D->GetYaxis()->SetRangeUser(18.8, 19.4);
       //TBox *tbox = new TBox (-7., 18.8, 7., 19.4);
       //tbox ->SetFillColorAlpha(kRed,0.);
       hYderivative2D->Fit("f2Bottom","R");//fit only this Range defind in function
       YRailTop = f2Bottom->GetParameter(0);
       std::cout<<"End Fit for Top Rail"<<std::endl;

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

    h->Draw("COLZ");
    if (FitObject == "PixelSupportRails" || FitObject == "PixelSupportRailsPositive" || FitObject == "PixelSupportRailsNegative") {
       //std::cout << " yRailTop = " << hYderivative->GetXaxis()->GetBinCenter(yRailTop) << " +- " << hYderivative->GetXaxis()->GetBinWidth(yRailTop)/2. << std::endl;
       Double_t x1 = -RPlot;
       Double_t x2 = RPlot;
       Double_t yerr = hYderivative->GetXaxis()->GetBinWidth(yRailTop)/2.;
       //Double_t y1 = hYderivative->GetXaxis()->GetBinCenter(yRailTop);//very rude estimation
       Double_t y1 = YRailTop;//more precize
       Double_t y2 = y1;
       TLine * lineTop = new TLine ( x1, y1, x2, y2 );
       lineTop->SetLineColor(kRed);
       lineTop->SetLineWidth(2);
       lineTop->Draw("same");

       //TText *t_top = new TText(.5,y1+2,Form("Top Rail y = %3.3f #pm %3.3f",y1, yerr));
       TLatex *t_top = new TLatex(.5,y1+3.7,Form("Top Rail y = %3.2f #pm %3.2f cm",y1, yerr));
       t_top->SetTextAlign(22);
       t_top->SetTextColor(kRed);
       t_top->SetTextFont(43);
       t_top->SetTextSize(40);
       //t_top->SetTextAngle(45);
       t_top->Draw();


       //y1 = hYderivative->GetXaxis()->GetBinCenter(yRailBottom);//very rude estimation
       y1 = YRailBottom;//more precize
       y2 = y1;
       TLine * lineBottom = new TLine ( x1, y1, x2, y2 );
       lineBottom->SetLineColor(kRed);
       lineBottom->SetLineWidth(2);
       lineBottom->Draw("same");

       TLatex *t_bottom = new TLatex(.5,y1+3.7,Form("Bottom Rail y = %3.2f #pm %3.2f cm",y1, yerr));
       t_bottom->SetTextAlign(22);
       t_bottom->SetTextColor(kRed);
       t_bottom->SetTextFont(43);
       t_bottom->SetTextSize(40);
       //t_bottom->SetTextAngle(45);
       t_bottom->Draw();

    }

    // save
    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.png"));



  }
  cout << "======    Pass Fit and Plots" << endl;

  /// Summary TGraph
  cPlots = new TCanvas("results","");
  cPlots->cd();
  TGraphErrors* gRfit = new TGraphErrors( 10, resZ, resR, errZ, errR );
  gRfit->GetXaxis()->SetTitle("z [cm]");
  gRfit->GetYaxis()->SetTitle("R [cm]");
  gRfit->SetTitle("fit results");
  gRfit->SetMarkerStyle(20);
  gRfit->SetMarkerSize(1.2);
  gRfit->SetMarkerColor(kBlack);
  gRfit->SetDrawOption("ap");
  TF1* fRfit = new TF1("fRfit","[0]+[1]*x",-25,25);
  fRfit->SetParNames("R_{s} (cm)","k_{R} (cm/cm)");
  fRfit->SetLineColor(kBlack);
  fRfit->SetMarkerColor(kBlack);
  gRfit->Fit("fRfit","RWEMS");
  gRfit->Draw("ap");
  cPlots->Update();

  TGraphErrors* gx0fit = new TGraphErrors( 10, resZ, resx0, errZ, errx0 );
  gx0fit->GetXaxis()->SetTitle("z [cm]");
  gx0fit->GetYaxis()->SetTitle("x_{0} [mm]");
  gx0fit->SetTitle("fit results");
  gx0fit->SetMarkerStyle(20);
  gx0fit->SetMarkerSize(1.2);
  gx0fit->SetMarkerColor(kRed);
  gx0fit->SetLineColor(kRed);
  gx0fit->SetDrawOption("ap");
  TF1* fx0fit = new TF1("fx0fit","[0]+[1]*x",-25,25);
  fx0fit->SetParNames("x_{0s} (mm)","k_{x0} (mm/cm)");
  fx0fit->SetLineColor(kRed);
  fx0fit->SetMarkerColor(kRed);
  gx0fit->Fit("fx0fit","RWEMS");
  gx0fit->Draw("ap");
  cPlots->Update();

  TGraphErrors* gy0fit = new TGraphErrors( 10, resZ, resy0, errZ, erry0 );
  gy0fit->GetXaxis()->SetTitle("z [cm]");
  gy0fit->GetYaxis()->SetTitle("y_{0} [mm]");
  gy0fit->SetTitle("fit results");
  gy0fit->SetMarkerStyle(20);
  gy0fit->SetMarkerSize(1.2);
  gy0fit->SetMarkerColor(kBlue);
  gy0fit->SetLineColor(kBlue);
  gy0fit->SetDrawOption("ap");
  TF1* fy0fit = new TF1("fy0fit","[0]+[1]*x",-25,25);
  fy0fit->SetParNames("y_{0s} (mm)","k_{y0} (mm/cm)");
  fy0fit->SetLineColor(kBlue);
  fy0fit->SetMarkerColor(kBlue);
  gy0fit->Fit("fy0fit","RWEMS");
  gy0fit->Draw("ap");
  //cout << "======    Check Error 1" << endl;
  cPlots->Update();
  //cout << "======    Check Error 2" << endl;

  cPlots->cd();

  TPad* pad1 = new TPad("pad1", "", 0, 0.64, 1, 1.00, 0, 0, 0);
  TPad* pad2 = new TPad("pad2", "", 0, 0.38, 1, 0.64, 0, 0, 0);
  TPad* pad3 = new TPad("pad3", "", 0, 0.00, 1, 0.38, 0, 0, 0);

  pad3->SetTopMargin(0.000);
  pad3->SetBottomMargin(pad3->GetBottomMargin()*2.6);
  pad2->SetBottomMargin(0.000);
  pad2->SetTopMargin(0.000);
  pad1->SetTopMargin(pad1->GetTopMargin()*2.6);
  pad1->SetBottomMargin(0.000);

  //gRfit->SetTitle("");

  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  double labelSizeFactor1 = (pad1->GetHNDC()+pad2->GetHNDC()+pad3->GetHNDC()) / pad1->GetHNDC();
  double labelSizeFactor2 = (pad1->GetHNDC()+pad2->GetHNDC()+pad3->GetHNDC()) / pad2->GetHNDC();
  double labelSizeFactor3 = (pad1->GetHNDC()+pad2->GetHNDC()+pad3->GetHNDC()) / pad3->GetHNDC();

  pad1->cd();
  //gRfit->SetTitle("fit results");
  //gRfit->GetYaxis()->SetTitle("a, b (cm)");
  gRfit->GetYaxis()->SetRangeUser(RSmin, RSmax);
  gRfit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor1);
  gRfit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor1);
  gRfit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor1);
  gRfit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor1);
  gRfit->GetYaxis()->SetTitleOffset(gRfit->GetYaxis()->GetTitleOffset()/labelSizeFactor1);
  gRfit->Draw("ap");
  pad1->Update();
  TPaveStats *statsRfit = (TPaveStats*)gRfit->GetListOfFunctions()->FindObject("stats");
  statsRfit->SetTextColor(kBlack);
  statsRfit->SetLineColor(kBlack);
  statsRfit->SetX1NDC(x1L);
  statsRfit->SetX2NDC(x2L);
  statsRfit->SetY1NDC(0.371);
  statsRfit->SetY2NDC(0.665);
  pad1->Update();
  TPaveText *title = (TPaveText*)pad1->GetPrimitive("title");
  title->SetY1NDC( 0.78 );
  title->SetY2NDC( 0.94 );

  //gbfit->Draw("p same");
  //gbfit->GetListOfFunctions()->FindObject("stats")->Delete();

  pad1->Modified();

  pad2->cd();
  gx0fit->SetTitle("");
  gx0fit->GetYaxis()->SetRangeUser(-1.5, 1.5);
  gx0fit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor2);
  gx0fit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor2);
  gx0fit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor2);
  gx0fit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor2);
  gx0fit->GetYaxis()->SetTitleOffset(gx0fit->GetYaxis()->GetTitleOffset()/labelSizeFactor2);
  gx0fit->Draw("ap");
  pad2->Update();
  TPaveStats *statsx0fit = (TPaveStats*)gx0fit->GetListOfFunctions()->FindObject("stats");
  statsx0fit->SetTextColor(kRed);
  statsx0fit->SetLineColor(kRed);
  statsx0fit->SetX1NDC(x1L);
  statsx0fit->SetX2NDC(x2L);
  statsx0fit->SetY1NDC(0.5);
  statsx0fit->SetY2NDC(0.9);
  pad2->Update();


  pad3->cd();
  gy0fit->SetTitle("");
  gy0fit->GetYaxis()->SetRangeUser(-1.5, 1.5);
  gy0fit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor3);
  gy0fit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor3);
  gy0fit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor3);
  gy0fit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor3);
  gy0fit->GetYaxis()->SetTitleOffset(gy0fit->GetYaxis()->GetTitleOffset()/labelSizeFactor3);
  gy0fit->Draw("ap");
  pad3->Update();
  TPaveStats *statsy0fit = (TPaveStats*)gy0fit->GetListOfFunctions()->FindObject("stats");
  statsy0fit->SetTextColor(kBlue);
  statsy0fit->SetLineColor(kBlue);
  statsy0fit->SetX1NDC(x1L);
  statsy0fit->SetX2NDC(x2L);
  statsy0fit->SetY1NDC(0.657);
  statsy0fit->SetY2NDC(0.932);
  //gphi21fit->Draw("p same");
  //gphi21fit->GetListOfFunctions()->FindObject("stats")->Delete();

  pad3->Update();
  //cPlots->SaveAs("Plots/FitResults.pdf");
  cPlots->SaveAs("Plots/FitResults.png");

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
void funPixelShieldEllipsePlus( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t)
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
      Double_t r = TMath::Sqrt( (x-par[1])*(x-par[1]) + (y-par[2])*(y-par[2]) ); // define r
      Double_t cos_ellipse = (x-par[1])/r; // the cosin
      Double_t sin_ellipse = (y-par[2])/r; // the sine
      Double_t x_ellipse = a*cos_ellipse;
      Double_t y_ellipse = b*sin_ellipse;
      Double_t r_ellipse = TMath::Sqrt( (x_ellipse)*(x_ellipse) + (y_ellipse)*(y_ellipse) );

      if ( r > RSmin && r < RSmax && x >0)
        {
        Double_t PhaseSpaceFactor = (r_ellipse*r_ellipse)/(r*r);
        diff = r_ellipse -r;
        chiSquare += binNum*diff*diff / (resoNI*resoNI) * PhaseSpaceFactor;
        }
      }
   }
   f = chiSquare;
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



