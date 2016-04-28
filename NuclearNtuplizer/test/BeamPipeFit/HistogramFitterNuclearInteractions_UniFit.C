/* ****************************************** */
/*                                            */
/* Tracker Material with Nuclear Interactions */
/*                                            */
/*               Nicola Pozzobon              */
/*                    2013                    */
/*                                            */
/* ****************************************** */

#include <memory>
#include <fstream>
#include <iostream>
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

TH2D* h;
TH2D* hrp;
TCanvas* cPlots;
TCanvas* cQuality;
TH1D* hQuality;
TH1D* hYderivative;
TH2D* hYderivative2D;
TH2D* hXderivative2D;

//*** sef parameters for Beam Pipe fit
//*** to fit is uncomment this block:
//TString FitObject = "BeamPipe";
//TString PlotObject = "hPFDV_XY_Map_Pipe";
//TString PlotObjectBg = "hPFDV_RhoPhi_Map_Pipe";
//double Rmin = 1.8, Rmax = 3.0, RBGmin = 2.4, RBGmax = 3., RSmin = 2.0, RSmax = 2.4, RPlot = 2.6;
//double RangeEstimatorQuality = 0.1; 
//int flag_ExcludeBadFitSector = 1; // = 1 exclude; = 0 not exclude;
//int flag_Sys = 1; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
//double x_Sys = 0.02; //size of systematics in cm
//double x0 = 0.124;// from 2015
//double y0 = 0.028; // from 2015
//double r0 = 2.211;  // from 2015
//*** end comments for Beam Pipe

//*** set parameters for Pixel Shield
//*** to fit is uncomment this block:
//TString FitObject = "PixelShield";
//TString PlotObject = "hPFDV_XY_Map_Pipe";
//TString PlotObjectBg = "hPFDV_RhoPhi_Map_Pipe";
//double Rmin = 3.0, Rmax = 4.1, RBGmin = 2.6, RBGmax = 3.5, RSmin = 3.5, RSmax = 3.9, RPlot = 4.1;
//double RangeEstimatorQuality = 0.1; 
//int flag_ExcludeBadFitSector = 1; // = 1 exclude; = 0 not exclude;
//int flag_Sys = 1; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
//double x_Sys = 0.03; //size of systematics in cm
//double x0 = -0.025;// from 2015
//double y0 = -0.083; // from 2015
//double r0 = 3.723;  // from 2015
//***  end comments for Pixel Shield
//*** with all phi sectors: 3.736, x0 = -0.02, y0 = -0.092

//*** set parameters for Pixel Support
//*** to fit is uncomment this block:
TString FitObject = "PixelSupport";
TString PlotObject = "hPFDV_XY_Map_BPix";
TString PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
double Rmin = 18.5, Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 20.5, RSmax = 22.5, RPlot = 24.5; 
double RangeEstimatorQuality = 0.5; 
int flag_ExcludeBadFitSector = 0; // = 1 exclude; = 0 not exclude;
//int flag_ExcludeBadFitSector = 1; // = 1 exclude; = 0 not exclude;
int flag_Sys = 1; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
double x_Sys = 0.1; //size of systematics in cm
double x0 = -0.08;// from 2015
double y0 = -0.34; // from 2015
double r0 = 21.70;  // from 2015
//***  end comments for Pixel Support


//*** set parameters for Pixel Support Rails
//*** to fit is uncomment this block:
//TString FitObject = "PixelSupportRails";
//TString PlotObject = "hPFDV_XY_Map_BPix";
//TString PlotObjectBg = "hPFDV_RhoPhi_Map_BPix";
//double Rmin = 18., Rmax = 24.5, RBGmin = 22.5, RBGmax = 24.5, RSmin = 18., RSmax = 22.5, RPlot = 24.5; 
//double RangeEstimatorQuality = 0.5; 
//int flag_ExcludeBadFitSector = 0; // = 1 exclude; = 0 not exclude, for Railse should be 0;
//int flag_Sys = 0; // = 0 - don't superimpose systematic variation, = 1 - superimpose systematics
//double x_Sys = 0.02; //size of systematics in cm
//double x0 = -0.08;// from 2015
//double y0 = -0.34; // from 2015
//double r0 = 21.70;  // from 2015
//***  end comments for Pixel Support




// good fit values
// 21.70; -0.08; -0.34
// 21.68; -0.07; -0.28
//create function to fit beam pipe in 2D (circle)
void chiSquareFunc( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Double_t resoNI = 0.01;
  Double_t halfWidthPipe = 0.025;
  Int_t numBinsX = h->GetNbinsX();
  Int_t numBinsY = h->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  //Bool_t skip = h->Integral() > 500000;
  for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
  {
    for ( UInt_t iy = 1; iy <= numBinsY; iy++ ) 
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
//	if (fabs(diff) > halfWidthPipe)  chiSquare += binNum*diff*diff / ( resoNI*resoNI);
	
    }
  }
  f = chiSquare;
}

//create Fit function for background
Double_t func_fitBg(Double_t*, Double_t* );
Double_t func_fitBg(Double_t *x ,Double_t *par)
{
 //Double_t value = par[0]*par[0]*TMath::Exp(par[1]*x[0]);
 Double_t value = par[0]*par[0]*exp(par[1]*x[0]);
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}

Double_t fun2(Double_t*, Double_t* );
Double_t fun2(Double_t *x ,Double_t *par)
{
  Double_t value = par[0]+par[1]*x[0];
  return value;
}


//create Circle/Arc function in phi,R plane:
Double_t func_ArcRhoPhi(Double_t*, Double_t* );
Double_t func_ArcRhoPhi(Double_t *x ,Double_t *par)
{
 // x[0] is phi here
 Double_t value = sqrt( (par[0]*cos(x[0])+par[1])**2 + (par[0]*sin(x[0])+par[2])**2 );
 //std::cout << "x[0] = " << x[0] << " value = " << value <<std::endl;
 return value;
}





void HistogramFitterNuclearInteractions_UniFit()
{
  //gROOT->SetBatch(1);
  gROOT->ForceStyle();

  TFile* inputFile = TFile::Open("MCplot_Run2015D.root");

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
    std::string plot = PlotObject;
    std::string plotBg = PlotObjectBg;
    //if (FitObject == "PixelSupport")std::string plot = PlotObject;
    //if (FitObject == "PixelSupport")std::string plotBg = PlotObjectBg;
    //std::string plot = "hPFDV_XY_Map_Pipe";
    //std::string plotBg = "hPFDV_RhoPhi_Map_Pipe";
    std::ostringstream plotName;
    std::ostringstream plotNameBg;

    plotName.str("");
    plotName << plot.c_str();
    plotNameBg.str("");
    plotNameBg << plotBg.c_str();

    /// k = -7 is the inclusive one
    /// k = -6 is only BPiz (|z| < 25 cm)
    if ( FitObject == "PixelShield" || FitObject == "BeamPipe"  ) {
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

    plot = std::string( plotName.str().c_str() );
    plotBg = std::string( plotNameBg.str().c_str() );

    //printf(plot.c_str());
    //printf("\n");

    h_RhoPhi = new TH2D();
    h_RhoPhi = (TH2D*)inputFile->Get( plotBg.c_str() );
    h_RhoPhi->Sumw2();
    if(FitObject == "PixelSupport")h_RhoPhi->Rebin2D(1,1);
    if(FitObject == "PixelShield") h_RhoPhi->Rebin2D(2,2);
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
    if(FitObject == "PixelSupport")h->Rebin2D(1,1);
    if(FitObject == "PixelShield") h->Rebin2D(5,5);
    if(FitObject == "BeamPipe")    h->Rebin2D(5,5);
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

    for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
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
      Int_t numBinsX = h->GetNbinsX();
      Int_t numBinsY = h->GetNbinsY();
      Double_t Xmax_h = h->GetXaxis()->GetBinCenter(numBinsX ) + h->GetXaxis()->GetBinWidth( numBinsX )/2; 
      if(numBinsX != numBinsY) std::cout << "WARNING numBinsX = " << numBinsX << "is not equal to numBinsY = " << numBinsY << std::endl;
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      //std::cout << "Xmax_h = " << Xmax_h << endl;

      for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x - x0;
          Double_t yc = y - y0;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Rmin || rc > Rmax ) continue;

          Double_t pc = TMath::ATan2( yc, xc );

          Int_t thisPhiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != phiSect ) continue;

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
      hbgua1->SetFillColor(TColor::kRed);
      hbgua1->SetMarkerColor(TColor::kRed);
      hbgua1->SetLineColor(TColor::kRed);
      hbgua1->Draw("same");
      hbgua2->SetFillStyle(3005);
      hbgua2->SetFillColor(TColor::kGreen);
      hbgua2->SetMarkerColor(TColor::kGreen);
      hbgua2->SetLineColor(TColor::kGreen);
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
      bgFit1[phiSect] = fitBg->GetParameter(1);
      bgFit1Err[phiSect] = fitBg->GetParError(1);

      TLegend* legBg = new TLegend(x1L, 0.6, x2L, y2L, "");
      legBg->SetTextFont(42);
      legBg->SetTextSize(0.03);
      legBg->SetFillColor(TColor::kWhite);
      legBg->SetTextColor(TColor::kBlack);
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

    Int_t numBinsX = h0->GetNbinsX();
    Int_t numBinsY = h0->GetNbinsY();
    for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
    {
      for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
      {
        Double_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );

        Double_t xc = x - x0;
        Double_t yc = y - y0;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

        if ( rc < Rmin || rc > Rmax ) continue;

        Double_t pc = TMath::ATan2( yc, xc );

        if ( rc > RSmin && rc < RSmax )
        {
          UInt_t phiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

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

      Int_t numBinsX = h->GetNbinsX();
      Int_t numBinsY = h->GetNbinsY();
      Double_t Xmax_h = h->GetXaxis()->GetBinCenter(numBinsX ) + h->GetXaxis()->GetBinWidth( numBinsX )/2;

      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      TH1D* hbgua3 = new TH1D( (plotBg+"_BGUA3").c_str(), "Counts per Unit Area in transverse plane", Int_t(numBinsX/2), 0., Xmax_h );
      //std::cout << "Int_t(numBinsX/2) = " << Int_t(numBinsX/2) << std::endl;

      for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x - x0;
          Double_t yc = y - y0;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Rmin || rc > Rmax ) continue;

          Double_t pc = TMath::ATan2( yc, xc );

          Int_t thisPhiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != phiSect ) continue;

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
      }
     
      // 
      // estimate if we have other objects in fit region with width = RangeEstimatorQuality
      Double_t SignalLowEdge = 0.; Double_t SignalUpperEdge = 0.; Double_t BgUpperEdge =0.;
      for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        Double_t x = hbgua0->GetXaxis()->GetBinCenter( ix );
        Double_t value = hbgua0->GetBinContent(ix);
        if( x > RSmin && x < (RSmin+RangeEstimatorQuality) ) SignalLowEdge+ = value;
        if( (FitObject == "PixelSupport" || FitObject == "BeamPipe") && x > RSmax && x < (RSmax+RangeEstimatorQuality)) SignalUpperEdge+ = value;
        if( FitObject == "PixelShield" && x > (RSmax-RangeEstimatorQuality) && x < RSmax) SignalUpperEdge+ = value;
        if( x > (RBGmax-RangeEstimatorQuality) && x < RBGmax) BgUpperEdge+ = value;
      }
      bgFitQuality[phiSect] = 1; //good phi sector for fit      

      //if(FitObject == "PixelSupport")
      if (SignalLowEdge > 1.5*BgUpperEdge || SignalUpperEdge > 1.5*BgUpperEdge) bgFitQuality[phiSect] = 0; //bad phi sector for fit 
      if(BgUpperEdge > 0.)hQuality->Fill( max(SignalLowEdge/BgUpperEdge, SignalUpperEdge/BgUpperEdge) );
      //std::cout <<"Phi Sector = " << phiSect << " hQuality fill = " << max(SignalLowEdge/BgUpperEdge, SignalUpperEdge/BgUpperEdge) << std::endl;

      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2015}_{0},y^{2015}_{0}) [cm]");
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
      hbgua1->SetFillColor(TColor::kRed);
      hbgua1->SetMarkerColor(TColor::kRed);
      hbgua1->SetLineColor(TColor::kRed);
      hbgua1->Draw("same");
      hbgua2->SetFillStyle(3005);
      hbgua2->SetFillColor(TColor::kGreen);
      hbgua2->SetMarkerColor(TColor::kGreen);
      hbgua2->SetLineColor(TColor::kGreen);
      hbgua2->Draw("same");
      hbgua3->SetFillStyle(3005);
      hbgua3->SetFillColor(TColor::kBlue);
      hbgua3->SetMarkerColor(TColor::kBlue);
      hbgua3->SetLineColor(TColor::kBlue);
      hbgua3->Draw("same");

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
      legBg->SetFillColor(TColor::kWhite);
      legBg->SetTextColor(TColor::kBlack);
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

    Int_t numBinsX = h->GetNbinsX();
    Int_t numBinsY = h->GetNbinsY();

    Double_t Ymin_Deriv = h->GetYaxis()->GetBinCenter(1); 
    Double_t Ymax_Deriv = h->GetYaxis()->GetBinCenter(numBinsY ) + h->GetYaxis()->GetBinWidth( numBinsY );
    std::cout << "Ymin_Deriv = " << Ymin_Deriv << " Ymax_Deriv = " << Ymax_Deriv << " bin width = " << h->GetYaxis()->GetBinWidth(1) << std::endl; 
    hYderivative = new TH1D( "hYderivative", "x-integrated derivative as funct. of y", numBinsY, Ymin_Deriv, Ymax_Deriv );
    TH2D* hYderivative2D = new TH2D( "hYderivative2D", "Y Derivative", h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    TH2D* hXderivative2D = new TH2D( "hXderivative2D", "X Derivative", h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );

    UInt_t yRailTop = 0.;
    UInt_t yRailBottom = 0.;
    Double_t yRailTopDer = 0.;
    Double_t yRailBottomDer = 0.;

    for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
    {
      Double_t Xmin_int = 0.;
      Double_t Xmax_int = 0.;
      Double_t Ywidth = h->GetYaxis()->GetBinWidth( iy );
      if (Ywidth <= 0 ) std::cout << "Error Ywith = " << Ywidth << std::endl;
      if (Ywidth <= 0) continue; 
  
      for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        Double_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );

        Double_t xc = x - x0;
        Double_t yc = y - y0;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );
        Double_t pc = TMath::ATan2( yc, xc );

        //if ( rc > Rmin && rc < Rmax )
        if ( rc > RSmin && rc < RSmax )
        {
          Xmin_int += binNum;
          if (iy < numBinsY) Xmax_int += h->GetBinContent( ix, iy+1 );

          UInt_t phiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

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
          // formula is corrent if all bins has the same width. If it is not true then you have to introduce bin width in this formula!
          if (ix>1 && ix<numBinsX && iy>1 && iy<numBinsY){
             Double_t u0 = h->GetBinContent( ix-1, iy-1 ) + 2*h->GetBinContent( ix, iy-1 ) + h->GetBinContent( ix+1, iy-1 ); 
             Double_t u2 = h->GetBinContent( ix-1, iy+1 ) + 2*h->GetBinContent( ix, iy+1 ) + h->GetBinContent( ix+1, iy+1 );
             Double_t fyDer2D = u2-u0;// calculate derivative at iy (y1) point
             // revert in negative y plain:
             if (y < 0) fyDer2D = -fyDer2D;
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
      if(iy < numBinsY) hYderivative -> SetBinContent (iy, Der);
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
    //                                                  npar
    TVirtualFitter* fitter = TVirtualFitter::Fitter( 0, 3 );
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
    if(FitObject != "PixelSupportRails") fitter->ExecuteCommand( "MIGRAD", arglist, 0 );

    //if small slice, then rebin histo for better view
    //if(k > -6 && k < 5) h->Rebin2D(5,5);
    h->GetXaxis()->SetRangeUser(-RPlot, RPlot);
    h->GetYaxis()->SetRangeUser(-RPlot, RPlot);
    h->Draw("col");

    TArc* arc = new TArc( fitter->GetParameter(1), fitter->GetParameter(2), fitter->GetParameter(0) );
    arc->SetFillStyle(0);
    arc->SetLineColor(TColor::kRed);
    arc->SetLineWidth(2);
    arc->Draw("same");
    Double_t x_arc[1], y_arc[1];
    x_arc[0] = fitter->GetParameter(1);
    y_arc[0] = fitter->GetParameter(2);
    TGraph* gr_arc = new TGraph(1,x_arc,y_arc);
    gr_arc->SetMarkerStyle(20);
    gr_arc->SetMarkerSize(0.5);
    gr_arc->SetMarkerColor(TColor::kRed);
    gr_arc->Draw("P");

    //plot circle with center at (0.0)
    TArc* arc0 = new TArc( 0., 0., fitter->GetParameter(0) );
    arc0->SetFillStyle(0);
    arc0->SetLineColor(TColor::kBlue);
    arc0->SetLineWidth(2);
    //arc0->Draw("same");
    Double_t x_arc0[1], y_arc0[1];
    x_arc0[0] = 0.;
    y_arc0[0] = 0.;
    TGraph* gr_arc0 = new TGraph(1,x_arc0,y_arc0);
    gr_arc0->SetMarkerStyle(20);
    gr_arc0->SetMarkerSize(0.5);
    gr_arc0->SetMarkerColor(TColor::kBlue);
    gr_arc0->Draw("P");


    cPlots->Update();

    TPaveStats* s = (TPaveStats*)h0->GetListOfFunctions()->FindObject("stats");
    x1L = s->GetX1NDC();
    x2L = s->GetX2NDC();
    y1L = s->GetY1NDC();
    y2L = s->GetY2NDC();

    TPaveText* res = new TPaveText(x1L-0.01, y1L-0.22, x2L+0.02, y2L-0.40, "brNDC");
    std::ostringstream legEntry;
    legEntry.str("");
    legEntry << "R (cm) \t = \t" << fixed << setprecision(2) << fitter->GetParameter(0) << " #pm " << fitter->GetParError(0) << " #pm " << x_Sys;
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "x_{0} (mm) \t = \t" << fixed << setprecision(2) << fitter->GetParameter(1)*10 << " #pm " << fitter->GetParError(1)*10 << " #pm " << x_Sys*10;
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "y_{0} (mm) \t = \t" << fitter->GetParameter(2)*10 << " #pm " << fitter->GetParError(2)*10 << " #pm " << x_Sys*10;
    res->AddText( legEntry.str().c_str() );
    res->SetFillStyle(0);
    res->SetTextAlign(12);
    res->SetTextColor(TColot::kRed);
    res->SetLineColor(TColot::kRed);
    res->SetTextFont(42);
    res->Draw("same");

      TLegend* legArc = new TLegend(0.75, 0.75, 0.95, 0.9, "");
      legArc->SetTextFont(42);
      legArc->SetTextSize(0.03);
      legArc->SetFillColor(TColor::kWhite);
      legArc->SetTextColor(TColor::kBlack);
      legArc->AddEntry(gr_arc,"(x_{0}, y_{0}) from fit","P");
      legArc->AddEntry(gr_arc0,"(0,0)","P");
      legArc->Draw("same");

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

    h_RhoPhi->GetYaxis()->SetRangeUser(Rmin, Rmax);
    //h_RhoPhi->GetYaxis()->SetRangeUser(RSmin, RSmax);
    h_RhoPhi->Draw("colz");
    //TF1 *bpAlt = new TF1("bpAlt","sqrt((21.699*cos(x)-0.081)^2 + (21.699*sin(x)-0.345)^2)",-3.15,3.15);
    TF1 *bpAlt = new TF1("bpAlt",func_ArcRhoPhi,-3.15,3.15,3);
    bpAlt->SetParameter(0, fitter->GetParameter(0));
    bpAlt->SetParameter(1, fitter->GetParameter(1));
    bpAlt->SetParameter(2, fitter->GetParameter(2));
    bpAlt->SetLineColor(TColor::kRed);
    bpAlt->SetLineWidth(2);
    bpAlt ->Draw("same");
    cPlots->Update();
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi.png"));

    if (flag_Sys == 1){

       // x variation
       TF1 *bpAlt_xp = new TF1("bpAlt_xp",func_ArcRhoPhi,-3.15,3.15,3);
       bpAlt_xp->SetParameter(0, fitter->GetParameter(0));
       bpAlt_xp->SetParameter(1, fitter->GetParameter(1)+x_Sys);
       bpAlt_xp->SetParameter(2, fitter->GetParameter(2));
       bpAlt_xp->SetLineColor(TColor::kBlack);
       bpAlt_xp->SetLineWidth(2);
       bpAlt_xp ->Draw("same");

       TF1 *bpAlt_xm = new TF1("bpAlt_xm",func_ArcRhoPhi,-3.15,3.15,3);
       bpAlt_xm->SetParameter(0, fitter->GetParameter(0));
       bpAlt_xm->SetParameter(1, fitter->GetParameter(1)-x_Sys);
       bpAlt_xm->SetParameter(2, fitter->GetParameter(2));
       bpAlt_xm->SetLineColor(TColor::kBlack);
       bpAlt_xm->SetLineWidth(2);
       bpAlt_xm ->Draw("same");

       cPlots->Update();
       cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi_sysX.png"));

       // y variation
       h_RhoPhi->Draw("colz");
       bpAlt ->Draw("same");

       TF1 *bpAlt_yp = new TF1("bpAlt_yp",func_ArcRhoPhi,-3.15,3.15,3);
       bpAlt_yp->SetParameter(0, fitter->GetParameter(0));
       bpAlt_yp->SetParameter(1, fitter->GetParameter(1));
       bpAlt_yp->SetParameter(2, fitter->GetParameter(2)+x_Sys);
       bpAlt_yp->SetLineColor(TColor::kBlack);
       bpAlt_yp->SetLineWidth(2);
       bpAlt_yp ->Draw("same");

       TF1 *bpAlt_ym = new TF1("bpAlt_ym",func_ArcRhoPhi,-3.15,3.15,3);
       bpAlt_ym->SetParameter(0, fitter->GetParameter(0));
       bpAlt_ym->SetParameter(1, fitter->GetParameter(1));
       bpAlt_ym->SetParameter(2, fitter->GetParameter(2)-x_Sys);
       bpAlt_ym->SetLineColor(TColor::kBlack);
       bpAlt_ym->SetLineWidth(2);
       bpAlt_ym ->Draw("same");

       cPlots->Update();
       cPlots->SaveAs(("Plots/"+FitObject+"_Fit_RhoPhi_sysY.png"));

       // R variation
       h_RhoPhi->Draw("colz");
       bpAlt ->Draw("same");

       TF1 *bpAlt_rp = new TF1("bpAlt_rp",func_ArcRhoPhi,-3.15,3.15,3);
       bpAlt_rp->SetParameter(0, fitter->GetParameter(0)+x_Sys);
       bpAlt_rp->SetParameter(1, fitter->GetParameter(1));
       bpAlt_rp->SetParameter(2, fitter->GetParameter(2));
       bpAlt_rp->SetLineColor(TColor::kBlack);
       bpAlt_rp->SetLineWidth(2);
       bpAlt_rp ->Draw("same");

       TF1 *bpAlt_rm = new TF1("bpAlt_rm",func_ArcRhoPhi,-3.15,3.15,3);
       bpAlt_rm->SetParameter(0, fitter->GetParameter(0)-x_Sys);
       bpAlt_rm->SetParameter(1, fitter->GetParameter(1));
       bpAlt_rm->SetParameter(2, fitter->GetParameter(2));
       bpAlt_rm->SetLineColor(TColor::kBlack);
       bpAlt_rm->SetLineWidth(2);
       bpAlt_rm ->Draw("same");

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
    if (FitObject == "PixelSupportRails") {
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
       f2Bottom->SetLineColor(TColor::kRed);
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
    if (FitObject == "PixelSupportRails") {
       //std::cout << " yRailTop = " << hYderivative->GetXaxis()->GetBinCenter(yRailTop) << " +- " << hYderivative->GetXaxis()->GetBinWidth(yRailTop)/2. << std::endl;
       Double_t x1 = -RPlot;
       Double_t x2 = RPlot;
       Double_t yerr = hYderivative->GetXaxis()->GetBinWidth(yRailTop)/2.;
       //Double_t y1 = hYderivative->GetXaxis()->GetBinCenter(yRailTop);//very rude estimation
       Double_t y1 = YRailTop;//more precize
       Double_t y2 = y1;
       TLine * lineTop = new TLine ( x1, y1, x2, y2 );
       lineTop->SetLineColor(TColor::kRed);
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
       lineBottom->SetLineColor(TColor::kRed);
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

    cPlots->Update();
    //cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.pdf"));
    cPlots->SaveAs(("Plots/"+FitObject+"_Fit_COLZ.png"));
      


  }

  /// Summary TGraph
  cPlots = new TCanvas("results","");
  cPlots->cd();
  TGraphErrors* gRfit = new TGraphErrors( 10, resZ, resR, errZ, errR );
  gRfit->GetXaxis()->SetTitle("z [cm]");
  gRfit->GetYaxis()->SetTitle("R [cm]");
  gRfit->SetTitle("fit results");
  gRfit->SetMarkerStyle(20);
  gRfit->SetMarkerSize(1.2);
  gRfit->SetMarkerColor(TColor::kBlack);
  gRfit->SetDrawOption("ap");
  TF1* fRfit = new TF1("fRfit","[0]+[1]*x",-25,25);
  fRfit->SetParNames("R_{s} (cm)","k_{R} (cm/cm)");
  fRfit->SetLineColor(TColor::kBlack);
  fRfit->SetMarkerColor(TColor::kBlack);
  gRfit->Fit("fRfit","RWEMS");
  gRfit->Draw("ap");
  cPlots->Update();

  TGraphErrors* gx0fit = new TGraphErrors( 10, resZ, resx0, errZ, errx0 );
  gx0fit->GetXaxis()->SetTitle("z [cm]");
  gx0fit->GetYaxis()->SetTitle("x_{0} [mm]");
  gx0fit->SetTitle("fit results");
  gx0fit->SetMarkerStyle(20);
  gx0fit->SetMarkerSize(1.2);
  gx0fit->SetMarkerColor(TColor::kRed);
  gx0fit->SetLineColor(TColor::kRed);
  gx0fit->SetDrawOption("ap");
  TF1* fx0fit = new TF1("fx0fit","[0]+[1]*x",-25,25);
  fx0fit->SetParNames("x_{0s} (mm)","k_{x0} (mm/cm)");
  fx0fit->SetLineColor(TColor::kRed);
  fx0fit->SetMarkerColor(TColor::kRed);
  gx0fit->Fit("fx0fit","RWEMS");
  gx0fit->Draw("ap");
  cPlots->Update();

  TGraphErrors* gy0fit = new TGraphErrors( 10, resZ, resy0, errZ, erry0 );
  gy0fit->GetXaxis()->SetTitle("z [cm]");
  gy0fit->GetYaxis()->SetTitle("y_{0} [mm]");
  gy0fit->SetTitle("fit results");
  gy0fit->SetMarkerStyle(20);
  gy0fit->SetMarkerSize(1.2);
  gy0fit->SetMarkerColor(TColor::kBlue);
  gy0fit->SetLineColor(TColor::kBlue);
  gy0fit->SetDrawOption("ap");
  TF1* fy0fit = new TF1("fy0fit","[0]+[1]*x",-25,25);
  fy0fit->SetParNames("y_{0s} (mm)","k_{y0} (mm/cm)");
  fy0fit->SetLineColor(TColor::kBlue);
  fy0fit->SetMarkerColor(TColor::kBlue);
  gy0fit->Fit("fy0fit","RWEMS");
  gy0fit->Draw("ap");
  cPlots->Update();

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
  statsRfit->SetTextColor(TColor::kBlack);
  statsRfit->SetLineColor(TColor::kBlack);
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
  statsx0fit->SetTextColor(TColor::kRed);
  statsx0fit->SetLineColor(TColor::kRed);
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
  statsy0fit->SetTextColor(TColor::kBlue);
  statsy0fit->SetLineColor(TColor::kBlue);
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
