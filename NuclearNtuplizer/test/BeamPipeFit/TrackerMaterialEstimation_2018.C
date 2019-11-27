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
#include <TLatex.h>

#include "tdrstyle.C"
#include "CMS_lumi.C"

using namespace std;

TH2D* h;
TH1D* hSlicePhiBG_Fit;
TH2D* h_Extra;
Double_t Rmin, Rmax, RBGmin, RBGmax, RSmin, RSmax, RPlot;
vector<double> rcBGmin_Fit;
vector<double> rcBGmax_Fit;
TCanvas* cPlots;
float ScaleSize = 1. - 2.*0.16;  

// creat plot Data + MC:
void PlotMaker(TH1D*,TH1D*,TString);

// good fit values
// 21.70; -0.08; -0.34
// 21.68; -0.07; -0.28
//create function to fit objects in 2D with circle (Arc)
void chiSquareBG( Int_t&, Double_t*, Double_t&, Double_t*, Int_t );

//create Fit function for background
Double_t func_fitBg(Double_t*, Double_t* );
Double_t func_fitBgAll(Double_t*, Double_t* );
Double_t fun2(Double_t*, Double_t* );

//create Circle/Arc  or Ellipse function in phi,R plane:
Double_t func_ArcRhoPhi(Double_t*, Double_t* );
Double_t func_EllipseRhoPhi(Double_t*, Double_t*);



// Main Program to fit Inner Tracker: Beam Pipe, Pixel Shield, Pixel Support and Pixel Support Rails

void TrackerMaterialEstimation_2018()
{
  //  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();


  //  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  //extraText  = "";  // default extra text is "Preliminary"
  //extraText  = "Preliminary";  // default extra text is "Preliminary"
  extraText  = "work in progress";  // default extra text is "Preliminary"
  //lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  //lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  // BELOW IS ONE FOR 2015
  //lumi_13TeV  = "2.5 fb^{-1}";  // default is "5.1 fb^{-1}"
  //lumi_13TeV  = "4.3 fb^{-1}";  // for preliminary of 2018 RawToReco
  lumi_13TeV  = "~50 fb^{-1}";  // for 88% of 2018AOD
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
  
  TH2D* h_RhoPhi;
  TH2D* h_RhoPhi_Extra;
  TH2D* h_ZR;
  TH2D* h_XY;
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
  Double_t x0_PixelShieldPlus = -0.107;
  Double_t y0_PixelShieldPlus = -0.093;
  Double_t r0_PixelShieldPlus = 3.780;
  
  
  Double_t x0_PixelSupportPlus = -0.233;
  Double_t y0_PixelSupportPlus = -0.331;
  Double_t r0_PixelSupportPlus = 21.85;

  TString z25 = "|z| < 25 cm"; 
////Average over 3 adjacent sectors to smooth differences 
  Int_t AverageBG = 0; // 0 - Default, don't average BG; 1 - sytematics, average BG
  TString FitObject = "";
  //TString PlotObject = "hPFDV_XY_Map_Pipe";
  //TString PlotObjectBg = "hPFDV_RhoPhi_Map_Pipe";
  // for 0.04 cm bining -> fast proccess
  //TString PlotObject = "hPFDV_XY_PixelSupport";
  // for 0.01 cm bining -> long proccess
  TString PlotObject = "hPFDV_XY_Pixel";       // NI All
  //TString PlotObject = "hPFDV_XY_PixelMultNI";   // NI >= 1
  //TString PlotObject = "hPFDV_XY_PixelSingleNI";   // NI == 1
  TString PlotObjectBg = "hPFDV_RhoPhi_PixelSupport";
  //doesn't exits:
  //TString PlotObjectBg = "hPFDV_RhoPhi_Pixel";
  Double_t RangeEstimatorQuality, x_Sys = 0, r_Sys = 0, x0 = 0, y0 = 0, r0 = 1, r0_y =1, x0_Far = 0, y0_Far = 0;
  if (r0_y < 0.) cout << "Error: r0_y < 0" << endl;

  Double_t ErrPrecision = 0.0005;  
  //Double_t ErrPrecision = 0.00000005;  

  // Set flags for fit options:

  Int_t flag_ExcludeBadFitSector = 1; // = 1 exclude; = 0 not exclude;
  Int_t  flag_Sys = 1; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
  

  //*** to fit is uncomment line:

  FitObject = "BeamPipe"; // working well
  //FitObject = "PixelSupportEllipse"; //work well
  //FitObject = "PixelSupportRails"; // work well

  //FitObject = "PixelShield2Arcs"; // status failed
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
  
  Rmin = 1., Rmax = 25., RBGmin = 2.35/*2.4*/, RBGmax = 2.6/*3.*/, RSmin = 2./*1.9*/, RSmax = 2.35/*2.4*/, RPlot = 25.;
  RangeEstimatorQuality = 0.1;
  //                     BP       L1      L2     L3      L4      shield    tube    strip start
  vector<double> x0M = {0.171,    0.10,   0.10,   0.10,   0.10,   0.10,   -0.075,   0.};
  vector<double> y0M = {-0.176,  -0.10,  -0.10,  -0.10,  -0.10,  -0.10,    -0.315,   0.};
  vector<double> r0M = { 2.210,   2.94,   6.80,  10.9,   16.0,   18.7,    21.753,  23.5};

  Int_t sizeM = x0M.size();
  if ( x0M.size() != y0M.size()) cout << "ERROR: x0M.size() ! = y0M.size()" << endl;
  if ( x0M.size() != r0M.size()) cout << "ERROR: x0M.size() ! = r0M.size()" << endl;
  cout << "Number of material layers sizeM = " << sizeM << endl;
  Double_t R_facetNear = 2.781;//2.8 // Technical design
  Double_t R_facetFar = 3.1;//3.014; // Technical design
  Double_t R_facetNear_L2 = 6.616; // Technical design
  Double_t R_facetFar_L2  = 7.0;//6.898; // Technical design 
  // sqrt{(x-x0)**2+(y-y0)**2} approx sqrt{x**2+y**2} - (x0cos_phi+y0sin_phi)
 
  x0 = 0.171; // from previous fits using this program that were based on 2018
  y0 = -0.176; // from previous fits using this program that were based on 2018
  r0 = 2.210; // from previous fits using this program that were based on 2018
  //*** set parameters for Beam Pipe fit
  if(FitObject == "BeamPipe"){
     //Rmin = 1.8, Rmax = /*5.*/3.0, RBGmin = 2.35/*2.4*/, RBGmax = 2.6/*3.*/, RSmin = 2.0/*1.9*/, RSmax = 2.35/*2.4*/, RPlot = /*5.*/3.5;
     Rmin = 1.6, Rmax = 25., RBGmin = 2.35/*2.4*/, RBGmax = 2.6/*3.*/, RSmin = 2./*1.9*/, RSmax = 2.35/*2.4*/, RPlot = 25.;
     RangeEstimatorQuality = 0.1;
     x_Sys = 0.003; //size of systematics in cm
     r_Sys = 0.003; //size of systematics in cm
     //x_Sys = 0.02; //size of systematics in cm
     //r_Sys = 0.02; //size of systematics in cm
     //x0 = 0.; // from MC
     //y0 = 0.; // from MC
     x0 = 0.171; // from previous fits using this program that were based on 2018
     y0 = -0.176; // from previous fits using this program that were based on 2018
     r0 = 2.210; // from previous fits using this program that were based on 2018
     //x0 = 0.124; // for pseudo 2015 CMS
     //y0 = 0.027; // -||-
     //r0 = 2.211; // -||- 
     //x0 = 1.; // for extrim text
     //y0 = -0.5; // -||- 
     //r0 = 2.210; // -||-
     //Rmin = 1.8, Rmax = 3., RBGmin = 2.4, RBGmax = 3., RSmin = 2., RSmax = 2.4, RPlot = 3.5;
     //RangeEstimatorQuality = 0.1;  
     //x_Sys = 0.003; //size of systematics in cm
     //r_Sys = 0.003; //size of systematics in cm
     //x0 = 0.124; // from previous fits using this program that were based on 2015
     //y0 = 0.026; // from previous fits using this program that were based on 2015
     //r0 = 2.21; // from previous fits using this program that were based on 2015
  }
  
  TH2F *hEmpty = new TH2F("hEmpty","",40,-RPlot,RPlot,40,-RPlot,RPlot);
  hEmpty->GetXaxis()->SetTitle("x (cm)");
  hEmpty->GetYaxis()->SetTitle("y (cm)"); 
  hEmpty->SetStats(0);
  //End Initialization:

  //gROOT->SetBatch(1);
  //gROOT->ForceStyle();

  // 2018 data file
  TString NameInputFile = "";
  ///TFile* inputFile = TFile::Open("Run2015DreReco.root");//for test only
  //TFile* inputFile = TFile::Open("PlotProduced_2018.root");
  //TFile* inputFile = TFile::Open("PlotProduced_MC2018_Pi10GeV.root");
  //TFile* inputFile = TFile::Open("PlotProduced_2018D_RawToReco.root");
  //TFile* inputFile = TFile::Open("PlotProduced_2018BCD_RawToReco.root");
  TFile* inputFile = TFile::Open("PlotProduced_2018D_AODpart.root");
  TFile* inputFileMC = TFile::Open("MCplot_DYFall2017realisticPU.root");
  // for pseudo MC only:
  //TString NameInputFile = "../PseudoBeamPipe/PseudoBeamPipe";
  //TFile* inputFile = TFile::Open(NameInputFile+".root");
  //TFile* inputFile = TFile::Open(NameInputFile+"_2015CMS.root");
  //TFile* inputFile = TFile::Open(NameInputFile+"_extrim.root");

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
  //gStyle->SetPadTopMargin(0.1);
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


  //for ( int k = -7; k < 5; k++ )
  //for ( int k = -5; k < 5; k++ ) // slices in 5 cm at |z| < 25 cm
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
    cout << "Function used for R:PHI = " << plotBg << endl;
    cPlots = new TCanvas(("c_"+plot).c_str(),"");

    /// -------------- Step 1: find the background density as a function of phi and rho(x0, y0) ----------

    //estimate if we have any object inside of signal region except fitted object
    Int_t bgFitQuality[40];

    Double_t bgFit0[40];
    Double_t bgFit0Err[40];
    Double_t bgFit1[40];
    Double_t bgFit1Err[40];

    /// ----------- Step 3: cross check background with original densities used for the fit -------------

    TH1D* hSlicePhi_Tot = (TH1D*)inputFile->Get("hPFDV_PixelSlicePhi_0")->Clone("hSlicePhi_Tot");
    TH1D* hSlicePhiMC_Tot = (TH1D*)inputFileMC->Get("hPFDV_PixelSlicePhi_0")->Clone("hSlicePhiMC_Tot");
    TH1D* hSlicePhiSingleNI_Tot = (TH1D*)inputFile->Get("hPFDV_PixelSlicePhiSingleNI_0")->Clone("hSlicePhiSingleNI_Tot");
    TH1D* hSlicePhiMCSingleNI_Tot = (TH1D*)inputFileMC->Get("hPFDV_PixelSlicePhiSingleNI_0")->Clone("hSlicePhiMCSingleNI_Tot");
    TH1D* hSlicePhiMultNI_Tot = (TH1D*)inputFile->Get("hPFDV_PixelSlicePhiMultNI_0")->Clone("hSlicePhiMultNI_Tot");
    TH1D* hSlicePhiMCMultNI_Tot = (TH1D*)inputFileMC->Get("hPFDV_PixelSlicePhiMultNI_0")->Clone("hSlicePhiMCMultNI_Tot");
    //const int lenPhi = 40; 
    const int lenPhi = 3; //for Test only...
    const int lenStructure = 8;
    double NumNI[lenPhi][lenStructure];
    double NumNI_MC[lenPhi][lenStructure];
    for(int i = 0; i < lenPhi; i++){
	for(int j = 0; j < lenStructure; j++){
           NumNI[i][j] = 0;
           NumNI_MC[i][j] = 0;
	}
    }
    for ( UInt_t phiSect = 0; phiSect < lenPhi; phiSect ++ )
    {
      vector<double> rmin_BG = { 0, 0, 0, 0, 0, 0, 0, 0};
      vector<double> rmax_BG = { 0, 0, 0, 0, 0, 0, 0, 0};
      vector<double> rmin_BG_MC = { 0, 0, 0, 0, 0, 0, 0, 0};
      vector<double> rmax_BG_MC = { 0, 0, 0, 0, 0, 0, 0, 0};
     
      //std::cout << "********MADE IT INTO LOOP********" << std::endl;
      //Int_t numBinsX = h->GetNbinsX();
      //Int_t numBinsY = h->GetNbinsY();

      // Get histo
      //TH1D* hSlicePhi = (TH1D*)inputFile->Get(Form("hPFDV_PixelSlicePhi_%d", phiSect)); //PhiSlice
      //TH1D* hSlicePhi_MC = (TH1D*)inputFileMC->Get(Form("hPFDV_PixelSlicePhi_%d", phiSect)); //PhiSlice
      TH1D* hSlicePhi = (TH1D*)inputFile->Get(Form("hPFDV_PixelSlicePhiSingleNI_%d", phiSect)); //PhiSlice
      TH1D* hSlicePhi_MC = (TH1D*)inputFileMC->Get(Form("hPFDV_PixelSlicePhiSingleNI_%d", phiSect)); //PhiSlice
      if(phiSect > 0){
		hSlicePhi_Tot -> Add((TH1D*)inputFile->Get(Form("hPFDV_PixelSlicePhi_%d", phiSect))); 
		hSlicePhiMC_Tot -> Add((TH1D*)inputFileMC->Get(Form("hPFDV_PixelSlicePhi_%d", phiSect)));
		hSlicePhiSingleNI_Tot -> Add((TH1D*)inputFile->Get(Form("hPFDV_PixelSlicePhiSingleNI_%d", phiSect))); 
		hSlicePhiMCSingleNI_Tot -> Add((TH1D*)inputFileMC->Get(Form("hPFDV_PixelSlicePhiSingleNI_%d", phiSect)));
		hSlicePhiMultNI_Tot -> Add((TH1D*)inputFile->Get(Form("hPFDV_PixelSlicePhiMultNI_%d", phiSect))); 
		hSlicePhiMCMultNI_Tot -> Add((TH1D*)inputFileMC->Get(Form("hPFDV_PixelSlicePhiMultNI_%d", phiSect)));
      }
      hSlicePhi->Rebin(4);
      hSlicePhi_MC->Rebin(4);
      //TH1D* hSlicePhiNoInTrk = (TH1D*)inputFile->Get(Form("hPFDV_PixelSlicePhiNoInTrk_%d", phiSect)); //PhiSlice
      //hSlicePhiNoInTrk->Rebin(2);
      Int_t numBinsSliceX = hSlicePhi->GetNbinsX(); 
      Int_t numBinsSliceX_MC = hSlicePhi_MC->GetNbinsX(); 
      Double_t Xmax_h = hSlicePhi->GetXaxis()->GetBinCenter(numBinsSliceX) + hSlicePhi->GetXaxis()->GetBinWidth(numBinsSliceX)/2;

      //std::cout << "********ABOUT TO CREATE HISTOGRAMS********" << std::endl;
      //TH1D* hSlicePhi = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      //TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", numBinsSliceX, 0., Xmax_h );
      //TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", numBinsSliceX, 0., Xmax_h );
      //TH1D* hbgua3 = new TH1D( (plotBg+"_BGUA3").c_str(), "Counts per Unit Area in transverse plane", numBinsSliceX, 0., Xmax_h );
      TH1D* hSlicePhiBG = (TH1D*)hSlicePhi ->Clone("hSlicePhiBG");
      TH1D* hSlicePhiBG_MC = (TH1D*)hSlicePhi_MC ->Clone("hSlicePhiBG_MC");
      TH1D* hSlicePhiSignal = (TH1D*)hSlicePhi ->Clone("hSlicePhiSignal");
      hSlicePhiBG->Reset();
      hSlicePhiBG_MC->Reset();
      hSlicePhiSignal->Reset();
      //std::cout << "Int_t(numBinsX/2) = " << Int_t(numBinsX/2) << std::endl;
      //std::cout << "********FINISHED CREATING HISTOGRAMS********" << std::cout;
      vector<double> rcBGmin;
      vector<double> rcBGmax;
      vector<double> rcBGmin_MC;
      vector<double> rcBGmax_MC;
      rcBGmin_Fit ={0, 0, 0, 0, 0, 0, 0, 0}; 
      rcBGmax_Fit ={0, 0, 0, 0, 0, 0, 0, 0};
      rcBGmin =    {0, 0, 0, 0, 0, 0, 0, 0}; 
      rcBGmax =    {0, 0, 0, 0, 0, 0, 0, 0};
      rcBGmin_MC = {0, 0, 0, 0, 0, 0, 0, 0}; 
      rcBGmax_MC = {0, 0, 0, 0, 0, 0, 0, 0};
      if(numBinsSliceX != numBinsSliceX_MC) cout << "ERROR: #bins in Data is different from MC: code will not work properly!!!" << endl;
      for ( UInt_t ix = 1; ix <= UInt_t(numBinsSliceX); ix++ )
      {
          Double_t x = hSlicePhiBG->GetXaxis()->GetBinCenter( ix );

          // adjust the calculation of rho for the minus side of the pixel shield to accomodate the differing 
          // positions of the two halves so that the background subtraction is cleaner.
          Double_t x0ref = x0;
          Double_t y0ref = y0;

          //Double_t rc = TMath::Sqrt( xc*xc + yc*yc );
          //Double_t rc = TMath::Sqrt( x*x + y*y ); //without correction to material position
          Double_t rc = x; //without correction to material position from 1D histo

          if ( rc < Rmin || rc > Rmax ) continue; //radius without correction to material

          //Double_t pc = TMath::ATan2( y, x );
          //if(pc < 0) pc = pc + 2*TMath::Pi();

          //Int_t thisPhiSect = floor(  pc / ( 2*TMath::Pi() ) * 40 );

          //if ( thisPhiSect != Int_t(phiSect) ) continue;

          Double_t binNum = hSlicePhi->GetBinContent( ix );
          Double_t binNum_MC = hSlicePhi_MC->GetBinContent( ix );
        
          Double_t pc = ( 2*TMath::Pi() ) * Double_t(phiSect)/40; // approximate estimation angle for phi sector
          Int_t BG_flag = 0;
          Int_t BG_flag_MC = 0;
          for ( UInt_t iBG = 0; iBG <= UInt_t(sizeM); iBG++ ){

             // *****   For DATA
             // set up baground region
             Double_t rc_M_min = Rmin;
             if (iBG > 0 ) rc_M_min = r0M[iBG-1] + (x0M[iBG-1]*cos(pc) + y0M[iBG-1]*sin(pc)) + 1.0;
             if (iBG > 5 ) rc_M_min = r0M[iBG-1] + (x0M[iBG-1]*cos(pc) + y0M[iBG-1]*sin(pc)) + 0.5;
             Double_t rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.2;
             //if (iBG > 0 && iBG < UInt_t(sizeM) )rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.5;
             if (iBG > 0 && iBG < UInt_t(sizeM) )rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.7;
             // cut between beam pine and L1:
             if (iBG == 1 ) rc_M_min = r0M[iBG-1] + (x0M[iBG-1]*cos(pc) + y0M[iBG-1]*sin(pc)) + 0.07;
	     if (iBG == 1 )rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.53;
             if (iBG == 1 && (phiSect >= 9 && phiSect <= 16)){
                rc_M_min = r0M[iBG-1] + (x0M[iBG-1]*cos(pc) + y0M[iBG-1]*sin(pc)) + 0.35;
	        rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.38;
             }
             if (iBG == 1 && (phiSect == 8 && phiSect == 17)){
                rc_M_min = r0M[iBG-1] + (x0M[iBG-1]*cos(pc) + y0M[iBG-1]*sin(pc)) + 0.5;
	        rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.2;
             }
             if (iBG == 1 && (phiSect >= 32 && phiSect <= 34)){
                rc_M_min = r0M[iBG-1] + (x0M[iBG-1]*cos(pc) + y0M[iBG-1]*sin(pc)) + 0.17;
	        rc_M_max = r0M[iBG] + (x0M[iBG]*cos(pc) + y0M[iBG]*sin(pc)) - 0.4;
             }

             // for eadge of rails:
             if (iBG == 6 && (phiSect ==32 || phiSect == 27 )) rc_M_max = 20.5;
             if (iBG == 6 && (phiSect ==12 || phiSect == 7 )) rc_M_max = 20.;
             if (rc > rc_M_min && rc < rc_M_max){
                 BG_flag = 1;
		 rmin_BG[iBG] = rc_M_min;
		 rmax_BG[iBG] = rc_M_max;
                // remove BG region related to double outter shield structure:
                if (iBG == 5 && (phiSect == 1 || phiSect == 7 || phiSect == 8 || phiSect == 11 || phiSect == 18 || phiSect == 21 || phiSect == 22 || phiSect == 28 || phiSect == 31 || phiSect == 32 || phiSect == 37 || phiSect == 38) ) BG_flag = 0;            
                // remove BG region related to rails:
                if (iBG == 6 && ((phiSect >= 8 && phiSect <=11)|| (phiSect >= 28 && phiSect <=31) ) ) BG_flag = 0;            
                
                // Fill BG region:
                if (BG_flag == 1 && iBG < UInt_t(sizeM)){rcBGmin[iBG] = rc_M_min; rcBGmax[iBG] = rc_M_max;}
             }

             // *****   For MC (no shift from (0,0)):
             // set up baground region
             rc_M_min = Rmin;
             if (iBG > 0 ) rc_M_min = r0M[iBG-1] +  1.0;
             if (iBG > 5 ) rc_M_min = r0M[iBG-1] +  0.5;
             rc_M_max = r0M[iBG]  - 0.2;
             if (iBG > 0 && iBG < UInt_t(sizeM) )rc_M_max = r0M[iBG] - 0.7;
             // cut between beam pine and L1:
             if (iBG == 1 ) rc_M_min = r0M[iBG-1] + 0.07;
             if (iBG == 1 )rc_M_max = r0M[iBG] - 0.53;
             if (iBG == 1 && (phiSect >= 9 && phiSect <= 16)){
                rc_M_min = r0M[iBG-1]  + 0.35;
                rc_M_max = r0M[iBG] - 0.38;
             }
             if (iBG == 1 && (phiSect == 8 && phiSect == 17)){
                rc_M_min = r0M[iBG-1] + 0.5;
                rc_M_max = r0M[iBG] - 0.2;
             }
             if (iBG == 1 && (phiSect >= 32 && phiSect <= 34)){
                rc_M_min = r0M[iBG-1] + 0.17;
                rc_M_max = r0M[iBG] - 0.4;
             }

             // for eadge of rails:
             if (iBG == 6 && (phiSect ==32 || phiSect == 27 )) rc_M_max = 20.5;
             if (iBG == 6 && (phiSect ==12 || phiSect == 7 )) rc_M_max = 20.;
             if (rc > rc_M_min && rc < rc_M_max){
                 BG_flag_MC = 1;
                 rmin_BG_MC[iBG] = rc_M_min;
                 rmax_BG_MC[iBG] = rc_M_max;
		 // as for data
		 if (iBG == 5 && (phiSect == 1 || phiSect == 7 || phiSect == 8 || phiSect == 11 || phiSect == 18 || phiSect == 21 || phiSect == 22 || phiSect == 28 || phiSect == 31 || phiSect == 32 || phiSect == 37 || phiSect == 38) ) BG_flag_MC = 0;
                // remove BG region related to rails:
                if (iBG == 6 && ((phiSect >= 8 && phiSect <=11)|| (phiSect >= 28 && phiSect <=31) ) ) BG_flag_MC = 0;

                // Fill BG region (BG_flag_MC is calculated as for DATA):
                if (BG_flag_MC == 1 && iBG < UInt_t(sizeM)){rcBGmin_MC[iBG] = rc_M_min; rcBGmax_MC[iBG] = rc_M_max;}
             }
             // **** end MC


          } // end for iBG

          if ( BG_flag == 1 )
          {
            hSlicePhiBG->Fill( rc, binNum );
          }
          else if ( rc >= RSmin && rc <= RSmax )
          {
            hSlicePhiSignal->Fill( rc, binNum );
          }
          if ( BG_flag_MC == 1 )
          {
            hSlicePhiBG_MC->Fill( rc, binNum_MC );
          }

      } // end cycle by hSlicePhi histo

      //Double_t bgRegionFit0[sizeM];
      //Double_t bgRegionFit1[sizeM];
      //for ( UInt_t iBG = 0; iBG < UInt_t(sizeM); iBG++ ){
      //    // Make fit:
      //   if(fabs(rcBGmin[iBG]) < 0.001){rcBGmin[iBG] = 0; rcBGmax[iBG] = 0;} // if BG is not definded so skip fit
      //   else{
      //      TF1 *fitBg = new TF1( "fitBg",func_fitBg, rcBGmin[iBG], rcBGmax[iBG], 2 );
      //      fitBg->SetParameter(0, 10);
      //      fitBg->SetParameter(1, 0.01);
      //      fitBg->SetParName(0, "N0");
      //      fitBg->SetParName(1, "k");
      //      hSlicePhi->Fit("fitBg","MR0Q");
      //      bgRegionFit0[iBG] = fitBg->GetParameter(0);
      //      bgRegionFit1[iBG] = fitBg->GetParameter(1);
      //   }
      //}
      ////

      TVirtualFitter* fitterDraw;
      //fitterDraw = TVirtualFitter::Fitter( 0, 9 );
      fitterDraw = TVirtualFitter::Fitter( 0, 10 );
      for ( UInt_t iR = 0; iR < 8; iR++ ){
          rcBGmin_Fit[iR] = rcBGmin[iR]; 
          rcBGmax_Fit[iR] = rcBGmax[iR]; 
      }
      //                                                  npar
      // Set the function that the fitter will use and set the parameters
      hSlicePhiBG_Fit = (TH1D*)hSlicePhiBG ->Clone("hSlicePhiBG_Fit");
      fitterDraw->SetFCN( chiSquareBG );
      fitterDraw->SetParameter( 0,  "par0",   140., 0.01, 0., 500. ); 
      fitterDraw->SetParameter( 1, "par1",   -0.7, 0.01, -10., 10. ); 
      fitterDraw->SetParameter( 2,  "par2",   120, 0.01, 0., 500. ); 
      fitterDraw->SetParameter( 3, "par3",    -0.4, 0.01, -10., 10. ); 
      fitterDraw->SetParameter( 4, "par4",    100., 0.01, 0., 500. ); 
      fitterDraw->SetParameter( 5, "par5",    -0.3, 0.01, -10., 10. ); 
      fitterDraw->SetParameter( 6, "par6",     50., 0.01, 0., 200. ); 
      fitterDraw->SetParameter( 7, "par7",    -0.25, 0.01, -10., 10. ); 
      fitterDraw->SetParameter( 8, "par8",    50., 0.01, 0., 200. ); 
      fitterDraw->SetParameter( 9, "par9",    -0.2, 0.01, -10., 10. ); 
      //   fitterDraw->FixParameter(1); fitterDraw->FixParameter(2); 

      Double_t arglist[10] = {0.};
      fitterDraw->ExecuteCommand( "MIGRAD", arglist, 0 );
      Double_t parBG[10];
      for ( UInt_t iBG = 0; iBG < 10; iBG++ ){
         parBG[iBG] = fitterDraw->GetParameter(iBG);
         cout << "parBG[" << iBG << "] = " << parBG[iBG] << endl;
      }

     TF1 *fitBgAll = new TF1( "fitBgAll",func_fitBgAll, 1., 25., 10 );
     fitBgAll ->SetNpx(1000);
     for ( UInt_t iBG = 0; iBG < 10; iBG++ ){
         fitBgAll->SetParameter(iBG, parBG[iBG]);
     }
     fitBgAll->SetLineWidth(3);
     fitBgAll->SetLineColor(kRed+1);
     cout << "Test pass" << endl;

//      //stara MC
//      for ( UInt_t iR = 0; iR < 8; iR++ ){
//          rcBGmin_Fit[iR] = rcBGmin_MC[iR]; 
//          rcBGmax_Fit[iR] = rcBGmax_MC[iR]; 
//      }
//      cout << "Test pass 1 " << endl;
//      TVirtualFitter* fitterDraw_MC;
//      
//      //                                                  npar
//      // Set the function that the fitter will use and set the parameters
//       cout << "Test pass 2 " << endl;
//      fitterDraw_MC->SetFCN( chiSquareBG );
//       cout << "Test pass 3 " << endl;
//      fitterDraw_MC->SetParameter( 0,  "par0",   140., 0.01, 0., 500. );
//      fitterDraw_MC->SetParameter( 1, "par1",   -0.7, 0.01, -10., 10. );
//      fitterDraw_MC->SetParameter( 2,  "par2",   120, 0.01, 0., 500. );
//      fitterDraw_MC->SetParameter( 3, "par3",    -0.4, 0.01, -10., 10. );
//      fitterDraw_MC->SetParameter( 4, "par4",    100., 0.01, 0., 500. );
//      fitterDraw_MC->SetParameter( 5, "par5",    -0.3, 0.01, -10., 10. );
//      fitterDraw_MC->SetParameter( 6, "par6",     50., 0.01, 0., 200. );
//      fitterDraw_MC->SetParameter( 7, "par7",    -0.25, 0.01, -10., 10. );
//      fitterDraw_MC->SetParameter( 8, "par8",    50., 0.01, 0., 200. );
//      fitterDraw_MC->SetParameter( 9, "par9",    -0.2, 0.01, -10., 10. );
//      //   fitterDraw_MC->FixParameter(1); fitterDraw_MC->FixParameter(2); 
//
//      Double_t arglist_MC[10] = {0.};
//      fitterDraw_MC->ExecuteCommand( "MIGRAD", arglist_MC, 0 );
//      Double_t parBG_MC[10];
//      for ( UInt_t iBG = 0; iBG < 10; iBG++ ){
//         parBG_MC[iBG] = fitterDraw_MC->GetParameter(iBG);
//         cout << "parBG_MC[" << iBG << "] = " << parBG_MC[iBG] << endl;
//      }
//     TF1 *fitBgAll_MC = new TF1( "fitBgAll_MC",func_fitBgAll, 1., 25., 10 );
//     fitBgAll_MC ->SetNpx(1000);
//     for ( UInt_t iBG = 0; iBG < 10; iBG++ ){
//         fitBgAll_MC->SetParameter(iBG, parBG_MC[iBG]);
//     }
//     fitBgAll_MC->SetLineWidth(3);
//     fitBgAll_MC->SetLineColor(kRed+1);
//     fitBgAll_MC->Draw("same");
//      //end MC

      TCanvas* cPlotPhi = new TCanvas();
      // Inside this canvas, we create two pads
      TPad *pad1 = new TPad("pad1","This is pad1",0.01,0.51,0.99,0.99); // x1, y1, x2, y2 fraction
      TPad *pad2 = new TPad("pad2","This is pad2",0.01,0.02,0.99,0.49);
      //pad1->SetFillColor(11);
      //pad2->SetFillColor(11);
      pad1->Draw();
      pad2->Draw();
      pad1 -> SetLogy(1);
      pad2 -> SetLogy(1);
      pad1->SetTopMargin(0.);
      pad1->SetBottomMargin(0.1);
      pad2->SetTopMargin(0.);
      pad2->SetBottomMargin(0.1);

      pad1 ->cd();

      //cPlotPhi -> Divide(1,2);
      //cPlotPhi ->cd(1);
      //gPad -> SetLogy(1);
      //gPad -> SetTopMargin(0.);

      //hSlicePhi->SetMinimum(0);
      hSlicePhi->SetMinimum(10);
      //hSlicePhi->SetMinimum(1000);
      hSlicePhi->SetMaximum(40000);
      //hSlicePhi->SetMaximum(20000);
      //hSlicePhi->GetXaxis()->SetTitle("#rho (x^{2017}_{0},y^{2017}_{0}) (cm)");
      hSlicePhi->GetXaxis()->SetTitleOffset(1.05);
      //hSlicePhi->GetXaxis()->SetTitle("#rho (x_{0}, y_{0}) (cm)");
      hSlicePhi->GetXaxis()->SetTitle("r (cm)");
      hSlicePhi->GetYaxis()->SetTitle(Form("Events / %2.2f cm ",hSlicePhi->GetXaxis()->GetBinWidth(1)));
      hSlicePhi->GetXaxis()->SetRangeUser(Rmin, Rmax);
      //hSlicePhi->GetXaxis()->SetRangeUser(Rmin,8.);
      hSlicePhi->Draw();
      cPlotPhi ->Update();

      // Format the plots of the phi sectors
      TPaveStats* sBg = (TPaveStats*)hSlicePhi->GetListOfFunctions()->FindObject("stats");
      x1L = sBg->GetX1NDC();
      x2L = sBg->GetX2NDC();
      y1L = sBg->GetY1NDC();
      y2L = sBg->GetY2NDC();

      hSlicePhi->SetStats(0);
      hSlicePhiBG->SetStats(0);
      hSlicePhiSignal->SetStats(0);
 
      //gStyle->SetHatchesSpacing(2.0);
      //gStyle->SetHatchesLineWidth(2);
      hSlicePhi->SetLineWidth(3);
      hSlicePhi_MC->SetLineWidth(3);
      hSlicePhiBG->SetLineWidth(3);
      hSlicePhiSignal->SetLineWidth(3);
      hSlicePhi->Draw("histo");
      hSlicePhi_MC->SetLineColor(kGreen+2);
      Double_t Integral_MC = hSlicePhi_MC->Integral();
      if(Integral_MC > 0.)hSlicePhi_MC->Scale(hSlicePhi->Integral()/Integral_MC);
      hSlicePhi_MC->Draw("samehisto");

      //hSlicePhiNoInTrk->SetLineWidth(3);
      //hSlicePhiNoInTrk->SetLineColor(kGreen+1);
      //hSlicePhiNoInTrk->Draw("samehisto");

      hSlicePhiBG->SetFillStyle(3004);
      //hSlicePhiBG->SetFillStyle(545);
      hSlicePhiBG->SetFillColor(kRed+1);
      hSlicePhiBG->SetMarkerColor(kRed+1);
      hSlicePhiBG->SetLineColor(kRed+1);
      hSlicePhiBG->Draw("samehisto");
      fitBgAll->Draw("same");

      //for ( UInt_t iBG = 0; iBG < UInt_t(sizeM-1); iBG++ ){
      //   if (fabs(rcBGmin[iBG] < 0.001)) continue; // do nothing if it is not defined
      //   Double_t x_max = rcBGmin[iBG+1];
      //   if (fabs(rcBGmin[iBG+1] < 0.001 )) x_max = 25.; // if it is not defined
      //   if (iBG == 0 && fabs(rcBGmin[iBG+2] > 0.001 )) x_max = rcBGmin[iBG+2]; // if it is not defined
      //   TF1 *fitBg = new TF1( "fitBg",func_fitBg, rcBGmin[iBG], x_max, 2 );
      //   fitBg->SetParameter(0, bgRegionFit0[iBG]);
      //   fitBg->SetParameter(1, bgRegionFit1[iBG]);
      //   fitBg->SetParName(0, "N0");
      //   fitBg->SetParName(1, "k");
      //   fitBg->SetLineWidth(3);
      //   fitBg->SetLineColor(kRed+1);
      //   fitBg->Draw("same");
      //}
      

      //hSlicePhiSignal->SetFillStyle(3005);
      hSlicePhiSignal->SetFillStyle(3013);
      hSlicePhiSignal->SetFillColor(kGreen+2);
      hSlicePhiSignal->SetMarkerColor(kGreen+2);
      hSlicePhiSignal->SetLineColor(kGreen+2);
      //hSlicePhiSignal->Draw("samehisto");
      


      //TLegend* legBg = new TLegend(0.4, 0.65, 0.7, 0.8, "");
      TLegend* legBg = new TLegend(0.5, 0.75, 0.8, 0.95, "");
      legBg->SetTextFont(42);
      legBg->SetTextSize(0.05*ScaleSize);
      legBg->SetFillColor(kWhite);
      legBg->SetTextColor(kBlack);
      //if (bgFitQuality[phiSect] == 0) legBg->AddEntry(hSlicePhi,"EXCLUDED from FIT","");
      //legBg->AddEntry(hSlicePhi,Form("Data 2018, #phi sector = %d", phiSect),"");
      legBg->AddEntry(hSlicePhi,"|z| < 25 cm ","");
      legBg->AddEntry(hSlicePhi,Form("Data 2018, #phi sector = %d", phiSect),"l");
      legBg->AddEntry(hSlicePhi_MC,Form("MC DY Fall2017, #phi sector = %d", phiSect),"l");
      //legBg->AddEntry(hSlicePhiNoInTrk,"Data, no income/merged track","l");
      //legBg->AddEntry(hSlicePhiSignal,"Signal fit region","f");
      legBg->AddEntry(hSlicePhiBG,"Sideband fit region","f");
      //legBg->AddEntry(fitBg,"sideband fit function","l");
      legBg->Draw("same");

      //gStyle->SetLineWidth(3);
      //hSlicePhi->SetAxisWidth(3);
      hSlicePhi->Draw("AXISsame");
      hSlicePhi->Draw("histosame");
      //gStyle->SetLineWidth(1);
      //TLine * lineTop = new TLine ( x1, y1, x2, y2 );
      TLine * lineX = new TLine ( Rmin, 0, Rmax , 0. );
      //TLine * lineX = new TLine ( Rmin, 0, 8 , 0. );
      lineX->SetLineColor(kBlack);
      lineX->SetLineWidth(3);
      lineX->Draw("same");

      //cPlotPhi  -> cd(2);
      //gPad -> SetLogy(1);
      //gPad -> SetTopMargin(0.);
      pad2->cd();
      //pad2->SetBottomMargin(0.12);
      //TPad* pad = (TPad*)cPlotPhi->GetPad(2);
      //pad->SetLeftMargin(0.15);
      //pad->SetRightMargin(0.02);
      //pad->SetFillColor(0);
      //pad->SetBorderMode(1);
      gStyle->SetOptFit(0);
      gStyle->SetOptStat(0);
      hSlicePhi_MC->GetXaxis()->SetTitle("r (cm)");
      hSlicePhi_MC->GetYaxis()->SetTitle(Form("Events / %2.2f cm ",hSlicePhi_MC->GetXaxis()->GetBinWidth(1)));
      hSlicePhi_MC->Draw("histo"); 
      //if (phiSect == 1 && FitObject == "BeamPipe" ) CMS_lumi( cPlots, iPeriod, iPos );
      //gStyle->SetOptStat(1000111110);
      //gStyle->SetOptStat(0000000000);
      cPlotPhi->Update();
      std::ostringstream fn;
      std::ostringstream fn_pdf;
      fn.str("");
      fn << "Plots/MaterialPhiSector_" << phiSect<<".png";
      cPlotPhi->SaveAs(fn.str().c_str());
      //cPlots -> Divide(1,1);
      cPlots -> cd();
      TH1D* hSlicePhiNoBG = (TH1D*)hSlicePhi ->Clone("hSlicePhiNoBG");
      hSlicePhiNoBG->Reset();
      //hSlicePhiNoBG->Sumw2();
      hSlicePhiNoBG->FillRandom("fitBgAll",10000000);
      Double_t Integral_GEN = hSlicePhiNoBG->Integral();
      Double_t BinWidth = hSlicePhi->GetXaxis()->GetBinWidth(1);
      Double_t xmin_int = hSlicePhi->GetXaxis()->GetBinLowEdge(1);
      Double_t xmax_int = hSlicePhi->GetXaxis()->GetBinUpEdge(hSlicePhi->GetNbinsX());
      Double_t Integral_FUNC = fitBgAll->Integral(Rmin,Rmax)/BinWidth;
      if(Integral_GEN > 0.)hSlicePhiNoBG->Scale(Integral_FUNC/Integral_GEN);
      hSlicePhiNoBG -> Add (hSlicePhi, hSlicePhiNoBG, 1., -1.);

      cPlots->SetLogy(0);
      hSlicePhiNoBG->SetMinimum(0);
      hSlicePhiNoBG->SetMaximum(20000);

      hSlicePhiNoBG -> Draw("histo");
        TLegend* legNoBG = new TLegend(0.5, 0.70, 0.7, 0.8, "");
        legNoBG->SetTextFont(42);
        legNoBG->SetTextSize(0.04*ScaleSize);
        legNoBG->SetFillColor(kWhite);
        legNoBG->SetTextColor(kBlack);
        legNoBG->AddEntry(hSlicePhiNoBG,Form("Data 2018, #phi sector = %d", phiSect),"l");
        legNoBG->AddEntry(hSlicePhiNoBG,"|z| < 25 cm ","");
        legNoBG->Draw("same");

      for ( UInt_t i_cal = 0; i_cal < lenStructure ; i_cal++ ){
              Double_t xmin_cal = rmax_BG[i_cal];
              Double_t xmax_cal = Rmax;
              if (i_cal < (lenStructure-1))xmax_cal = rmin_BG[i_cal+1];
              Int_t xID_min = round((xmin_cal - xmin_int)/BinWidth);
              Int_t xID_max = round((xmax_cal - xmin_int)/BinWidth);
	      NumNI[phiSect][i_cal] = hSlicePhiNoBG -> Integral(xID_min,xID_max);
              TLine * lineSignal = new TLine ( xmin_cal, 0, xmax_cal , 0. );
              lineSignal->SetLineColor(kRed);
              lineSignal->SetLineWidth(5);
              lineSignal->Draw("same");
//cout << "For structure i = " << i_cal <<  " phiSect = " << phiSect << " xmin_cal = " << xmin_cal << " xmax_cal = " << xmax_cal << " NumNI = " << NumNI[phiSect][i_cal] << endl;
      }
      //fitBgAll->Draw("same");
      cPlots->SaveAs(Form("Plots/MaterialPhiSectorNoBG_%d.png", phiSect));
      
      //if (phiSect == 1 && FitObject == "BeamPipe")cPlots->SaveAs(fn_pdf.str().c_str());
      //delete to avoid memory leak:
      //cPlots->Delete();
      //delete cPlots;
      delete hSlicePhi;
      delete hSlicePhi_MC;
      delete hSlicePhiBG;
      delete hSlicePhiBG_MC;
      delete hSlicePhiSignal;
    } //end phi cicle

    double normNumNI[lenPhi][lenStructure];
    for(int i = 0; i < lenPhi; i++){
        for(int j = 0; j < lenStructure; j++){
           if(fabs(NumNI[i][j])< 0.001)cout << "Warning too small: NumNI[" << i << "][" << j << "] = " << NumNI[i][j] << endl;
           // normalize to L2 (j = 2)
           if (fabs(NumNI[i][2]) > 0.001) normNumNI[i][j] = NumNI[i][j]/NumNI[i][2];
           //cout << "Test phi = " << i << " ID Structure = " << j << "Rate to L2 = " << normNumNI[i][j] << endl; 
        }
    }
    for(int i = 0; i < lenPhi; i++){
        const char *Structure[lenStructure] = {"beam pipe", "L1", "L2", "L3", "L4", "OS", "PS", "TL1"};
        TH1F *hRate = new TH1F("hRate","Rate to L2",3,0,3);
        hRate->SetStats(0);
        hRate->SetFillColor(38);
        hRate->SetCanExtend(TH1::kAllAxes);
        for (Int_t j=0;j<lenStructure;j++) {
    	    hRate->Fill(Structure[j],normNumNI[i][j]);
	}
	hRate->LabelsDeflate();
        //hRate->SetMinimum(0);
        //hRate->SetMaximum(3.0);
	hRate->Draw("histo");
	TLegend* legRate = new TLegend(0.5, 0.70, 0.7, 0.8, "");
	legRate->SetTextFont(42);
	legRate->SetTextSize(0.04*ScaleSize);
	legRate->SetFillColor(kWhite);
	legRate->SetTextColor(kBlack);
	legRate->AddEntry(hRate,Form("Data 2018, #phi sector = %d", i),"f");
	legRate->AddEntry(hRate,"|z| < 25 cm ","");
	legRate->Draw("same");
	cPlots->SaveAs(Form("Plots/MaterialPhiSectorRate_%d.png", i));
        delete hRate;
   }

      hSlicePhi_Tot->Rebin(4);
      hSlicePhiMC_Tot->Rebin(4);
      TString PlotTitle = "Plots/Material_Tot.png";
      PlotMaker(hSlicePhi_Tot, hSlicePhiMC_Tot, PlotTitle);

      hSlicePhiSingleNI_Tot->Rebin(4);
      hSlicePhiMCSingleNI_Tot->Rebin(4);
      PlotTitle = "Plots/MaterialSingleNI_Tot.png";
      PlotMaker(hSlicePhiSingleNI_Tot, hSlicePhiMCSingleNI_Tot, PlotTitle);

      hSlicePhiMultNI_Tot->Rebin(4);
      hSlicePhiMCMultNI_Tot->Rebin(4);
      PlotTitle = "Plots/MaterialMultNI_Tot.png";
      PlotMaker(hSlicePhiMultNI_Tot, hSlicePhiMCMultNI_Tot, PlotTitle);


      //cPlots->cd();
      //cPlots->SetLogy(1);
      //hSlicePhi_Tot->SetMinimum(1.E3);
      //hSlicePhi_Tot->SetMaximum(1.E6);
      //hSlicePhi_Tot->GetXaxis()->SetTitleOffset(1.05);
      //hSlicePhi_Tot->GetXaxis()->SetTitle("r (cm)");
      //hSlicePhi_Tot->GetYaxis()->SetTitle(Form("Events / %2.2f cm ",hSlicePhi_Tot->GetXaxis()->GetBinWidth(1)));
      //hSlicePhi_Tot->GetXaxis()->SetRangeUser(Rmin,Rmax);
      //hSlicePhi_Tot->Draw();
      //cPlots->Update();

      //////// Format the plots of the phi sectors
      //////TPaveStats* sBg = (TPaveStats*)hSlicePhi->GetListOfFunctions()->FindObject("stats");
      //////x1L = sBg->GetX1NDC();
      //////x2L = sBg->GetX2NDC();
      //////y1L = sBg->GetY1NDC();
      //////y2L = sBg->GetY2NDC();

      //hSlicePhi_Tot->SetStats(0);

      //hSlicePhi_Tot->SetLineWidth(3);
      //hSlicePhiMC_Tot->SetLineWidth(3);
      //hSlicePhi_Tot->Draw("histo");
      //hSlicePhiMC_Tot->SetLineColor(kGreen+2);
      //Double_t Integral_MC_Tot = hSlicePhiMC_Tot->Integral();
      //if(Integral_MC_Tot > 0.)hSlicePhiMC_Tot->Scale(hSlicePhi_Tot->Integral()/Integral_MC_Tot);
      //hSlicePhiMC_Tot->Draw("samehisto");

      //TLegend* LegTot = new TLegend(0.5, 0.7, 0.7, 0.8, "");
      //if(FitObject == "PixelSupportEllipse")LegTot = new TLegend(0.2, 0.6, 0.4, 0.8, "");
      //LegTot->SetTextFont(42);
      //LegTot->SetTextSize(0.04*ScaleSize);
      //LegTot->SetFillColor(kWhite);
      //LegTot->SetTextColor(kBlack);
      //LegTot->AddEntry(hSlicePhi_Tot,"Data 2018","l");
      //LegTot->AddEntry(hSlicePhiMC_Tot,"MC DY Fall2017","l");
      //LegTot->AddEntry(hSlicePhi_Tot,"|z| < 25 cm ","");
      ////LegTot->AddEntry(hSlicePhiBG,"Sideband fit region","f");
      //LegTot->Draw("same");

      //hSlicePhi_Tot->Draw("AXISsame");
      //hSlicePhi_Tot->Draw("histosame");
      //TLine * lineX_Tot = new TLine ( Rmin, 0, Rmax , 0. );
      //lineX_Tot->SetLineColor(kBlack);
      //lineX_Tot->SetLineWidth(3);
      //lineX_Tot->Draw("same");

      //cPlots->SaveAs("Plots/Material_Tot.png");

    continue;// END for material estimation
   }
}
//End Main Program

// Function Definition:

void PlotMaker(TH1D* hData,TH1D* hMC, TString PlotTitle)
{
      cPlots->cd();
      cPlots->SetLogy(1);
      hData->SetMinimum(0.5E3);
      hData->SetMaximum(1.E6);
      hData->GetXaxis()->SetTitleOffset(1.05);
      hData->GetXaxis()->SetTitle("r (cm)");
      hData->GetYaxis()->SetTitle(Form("Events / %2.2f cm ",hData->GetXaxis()->GetBinWidth(1)));
      hData->GetXaxis()->SetRangeUser(Rmin,Rmax);
      hData->Draw();
      cPlots->Update();

      ////// Format the plots of the phi sectors
      ////TPaveStats* sBg = (TPaveStats*)hSlicePhi->GetListOfFunctions()->FindObject("stats");
      ////x1L = sBg->GetX1NDC();
      ////x2L = sBg->GetX2NDC();
      ////y1L = sBg->GetY1NDC();
      ////y2L = sBg->GetY2NDC();

      hData->SetStats(0);

      hData->SetLineWidth(3);
      hMC->SetLineWidth(3);
      hData->Draw("histo");
      hMC->SetLineColor(kGreen+2);
      Double_t Integral_MC_Tot = hMC->Integral();
      if(Integral_MC_Tot > 0.)hMC->Scale(hData->Integral()/Integral_MC_Tot);
      hMC->Draw("samehisto");

      TLegend* LegTot = new TLegend(0.5, 0.7, 0.7, 0.8, "");
      LegTot->SetTextFont(42);
      LegTot->SetTextSize(0.04*ScaleSize);
      LegTot->SetFillColor(kWhite);
      LegTot->SetTextColor(kBlack);
      LegTot->AddEntry(hData,"Data 2018","l");
      LegTot->AddEntry(hMC,"MC DY Fall2017","l");
      LegTot->AddEntry(hData,"|z| < 25 cm ","");
      //LegTot->AddEntry(hSlicePhiBG,"Sideband fit region","f");
      LegTot->Draw("same");

      hData->Draw("AXISsame");
      hData->Draw("histosame");
      TLine * lineX_Tot = new TLine ( Rmin, 0, Rmax , 0. );
      lineX_Tot->SetLineColor(kBlack);
      lineX_Tot->SetLineWidth(3);
      //lineX_Tot->Draw("same");

      cPlots->SaveAs(PlotTitle);
}

//create Fit function for background
Double_t func_fitBg(Double_t *x ,Double_t *par)
{
 //Double_t value = par[0]*par[0]*TMath::Exp(par[1]*x[0]);
 Double_t value = par[0]*par[0]*exp(par[1]*x[0]);
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}
//
Double_t func_fitBgAll(Double_t *x ,Double_t *par)
{
 Double_t value=0;
 if (x[0] < rcBGmax_Fit[1]) value = par[0]*par[0]*exp(par[1]*x[0]);
 // between beam pipe and L1
 if (x[0] > rcBGmax_Fit[1]&& x[0] < rcBGmin_Fit[2]){
    Double_t x1 = rcBGmax_Fit[1];
    Double_t x2 = rcBGmin_Fit[2];
    Double_t y1 = par[0]*par[0]*exp(par[1]*x1);
    Double_t y2 = par[2]*par[2]*exp(par[3]*x2);
    Double_t b = (y1-y2)/(x1-x2);
    Double_t a = (y2*x1-y1*x2)/(x1-x2);
    value = a + b*x[0];
 }
 // after L1
 if (x[0] > rcBGmin_Fit[2])value = par[2]*par[2]*exp(par[3]*x[0]);
 // after L2
 if (x[0] > (rcBGmin_Fit[3]-0.4))value =par[4]*par[4]*exp(par[5]*x[0]);
 // after L3
 if (x[0] > (rcBGmin_Fit[4]-0.4))value =par[6]*par[6]*exp(par[7]*x[0]);
 // after L4
 Double_t xminL4 = rcBGmin_Fit[5];
 if (rcBGmin_Fit[5] < 15) xminL4 = 17.;
 if (x[0] > xminL4){
   value =par[8]*par[8]*exp(par[9]*x[0]);
 }
 Double_t xminST = rcBGmin_Fit[7];
 if (xminST < 20) xminST = 22.;
 if (x[0] > xminST){ // plateau after support tube
   value = par[8]*par[8]*exp(par[9]*xminST); 
 }
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
 // x[0] is phi in CMS coordiante
 Double_t Rf  = par[0]; // R
 Double_t x0f = par[1]; // x0
 Double_t y0f = par[2]; // y0
 Double_t phiPrime = -1000.;// phi in (x0,y0) frame
 Double_t phi = x[0];
 // find phiPrime in x0, y0 coordiante
 UInt_t Nbin = 1000;
 for ( UInt_t i = 0; i <=Nbin; i++ ){
     Double_t phiPrime_i = - TMath::Pi() + 2.*TMath::Pi()*Double_t(i)/Double_t(Nbin);
     Double_t phi_i = atan2((Rf*sin(phiPrime_i) + y0f),(Rf*cos(phiPrime_i) + x0f));
     if (fabs(phi_i-phi) <= 2.*TMath::Pi()/Double_t(Nbin)) phiPrime = phiPrime_i; 
 } 
 if (phiPrime < -100.) cout << "Error: phiPrime is not calculated for Circle phi = " << phi << endl;
 Double_t value = sqrt( (Rf*cos(phiPrime)+x0f)*(Rf*cos(phiPrime)+x0f) + (Rf*sin(phiPrime)+y0f)*(Rf*sin(phiPrime)+y0f) );
// Double_t value = sqrt( (par[0]*cos(x[0])+par[1])*(par[0]*cos(x[0])+par[1]) + (par[0]*sin(x[0])+par[2])*(par[0]*sin(x[0])+par[2]) ); // bugy version phi should be phiPrime
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}

Double_t func_EllipseRhoPhi(Double_t *x, Double_t *par)
{
 // x[0] is phi here
 Double_t Rxf  = par[0]; // Rx
 Double_t Ryf  = par[3]; // Ry
 Double_t x0f = par[1]; // x0
 Double_t y0f = par[2]; // y0
 Double_t phiPrime = -1000.;// phi in (x0,y0) frame
 Double_t phi = x[0];
 // find phiPrime in x0, y0 coordiante
 UInt_t Nbin = 1000;
 for ( UInt_t i = 0; i <=Nbin; i++ ){
     Double_t phiPrime_i = - TMath::Pi() + 2.*TMath::Pi()*Double_t(i)/Double_t(Nbin);
     Double_t phi_i = atan2((Ryf*sin(phiPrime_i) + y0f),(Rxf*cos(phiPrime_i) + x0f));
     if (fabs(phi_i-phi) <= 2.*TMath::Pi()/Double_t(Nbin) ||fabs(fabs(phi_i-phi)-2.*TMath::Pi()) <= 2.*TMath::Pi()/Double_t(Nbin) ) phiPrime = phiPrime_i;
     //cout << "phi_i = " << phi_i << " phi = " << phi << endl;
 }
 if (phiPrime < -100.) cout << "Error: phiPrime is not calculated for Ellispse phi = " << phi << endl;
 Double_t value = sqrt( (Rxf*cos(phiPrime)+x0f)*(Rxf*cos(phiPrime)+x0f) + (Ryf*sin(phiPrime)+y0f)*(Ryf*sin(phiPrime)+y0f) );
 //Double_t value = sqrt( (par[0]*cos(x[0])+par[1])*(par[0]*cos(x[0])+par[1]) + (par[3]*sin(x[0])+par[2])*(par[3]*sin(x[0])+par[2]) );  // bugy version phi should be phiPrime
 return value;
}

//create function to fit BG in phi slice
void chiSquareBG( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Int_t numBinsX = hSlicePhiBG_Fit->GetNbinsX();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  for ( UInt_t ix = 1; ix <= UInt_t(numBinsX); ix++ )
  {
      Double_t binNum = hSlicePhiBG_Fit->GetBinContent( ix);

      if ( binNum <= 0 ) continue; // fit only where BG is not zero

      Double_t x[1];
      x[0] = hSlicePhiBG_Fit->GetXaxis()->GetBinCenter( ix );
      //if (x < 11. || x > 22.) continue; // fit after 3d BPIX layer
      //if (x < 7.|| x > 22.) continue; // fit after 2d BPIX layer
      //if (x < 3.|| x > 22.) continue; // fit after 1st BPIX layer
      if (x[0] > 23.) continue; // fit after 1st BPIX layer
      //cout << "binNum = " << binNum << endl;
      Double_t value = func_fitBgAll(x, par);
      //Double_t value = par[0]*par[0]*exp(par[1]*x) + par[2]*par[2]*exp(par[3]*x) + par[4]*par[4]*exp(par[5]*x);
      diff = binNum - value;
      chiSquare += diff*diff /binNum;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );

  }
  //cout << "chiSquare = " << chiSquare << endl; 
  f = chiSquare;
}
