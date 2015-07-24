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
#include <TMath.h>
#include <TVirtualFitter.h>
#include <TFitter.h>

#include <TCanvas.h>
#include "TPaveStats.h"
#include "TColor.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArc.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TROOT.h"

TH2D* h;
TH2D* hrp;
TCanvas* cPlots;

void chiSquareFunc( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Double_t resoNI = 0.01;
  Double_t halfWidthPipe = 0.025;
  Int_t numBinsX = h->GetNbinsX();
  Int_t numBinsY = h->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  //Bool_t skip = h->Integral() > 500000;
  for ( int ix = 1; ix <= numBinsX; ix++ )
  {
    for ( int iy = 1; iy <= numBinsY; iy++ ) 
    {
      Double_t binNum = h->GetBinContent( ix, iy );

      /// Thresholds
      /// 2011A+B: 5 entries for inclusive
      ///          3 entries for 5 cm slices
      /// 2012A+B+C+D: 20 entries for inclusive
      ///              5 entries for 5 cm slices      
      //if ( skip && binNum < 5 ) continue;
      //if ( !skip && binNum < 3 ) continue;

      Double_t x = h->GetXaxis()->GetBinCenter( ix );// - 0.087;
      Double_t y = h->GetYaxis()->GetBinCenter( iy );// + 0.197;
      //Double_t r = TMath::Sqrt( x*x + y*y );
//      if ( r > 2.8 && r < 3.04 )
//      {
        Double_t u = x - par[1];
        Double_t v = y - par[2];
        diff = par[0] - TMath::Sqrt(u*u + v*v);
        chiSquare += binNum*diff*diff / ( resoNI*resoNI + halfWidthPipe*halfWidthPipe );
//      }
    }
  }
  f = chiSquare;
}


/*
void chiSquareBackground( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Int_t numBinsPhi = hrp->GetNbinsX();
  Int_t numBinsRho = hrp->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  for ( UInt_t iphi = 1; iphi <= numBinsPhi; iphi++ )
  {
    for ( UInt_t irho = 1; irho <= numBinsRho; irho++ )
    {
      Int_t binNum = hrp->GetBinContent( iphi, irho );

      Double_t rho = hrp->GetYaxis()->GetBinCenter( irho );
      Double_t phi = hrp->GetXaxis()->GetBinCenter( iphi );
      Double_t x = rho * TMath::Cos( phi ) - 0.087;
      Double_t y = rho * TMath::Sin( phi ) + 0.197;
      Double_t r = TMath::Sqrt( x*x + y*y );
      if ( ( r > 2.2 && r < 2.5 ) || r > 3.3 && r < 3.6 )
      {
        /// Number per unit area!
        Double_t diff = binNum/( rho*hrp->GetYaxis()->GetBinWidth( iphi )*hrp->GetXaxis()->GetBinWidth( irho ) ) - ( par[0] + rho*par[1] );
        chiSquare += diff*diff;
      }
    }    
  }
  f = chiSquare;
}
*/








void HistogramFitterNuclearInteractions_BeamPipe2012ABCD()
{
  //gROOT->SetBatch(1);
  gROOT->ForceStyle();

  //TFile* inputFile = TFile::Open("prova.root");
  TFile* inputFile = TFile::Open("/afs/cern.ch/work/k/kropiv/Tracker/Run2015B_GoodMuons.root");

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
  gStyle->SetOptStat(1000111110);
  gStyle->SetCanvasDefW(800);
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

  for ( int k = -7; k < 5; k++ )
  {
    std::string plot = "hPFDV_XY_Map_Pipe";
    std::string plotBg = "hPFDV_RhoPhi_Map_Pipe";
    std::ostringstream plotName;
    std::ostringstream plotNameBg;

    plotName.str("");
    plotName << plot.c_str();
    plotNameBg.str("");
    plotNameBg << plotBg.c_str();

    /// k = -7 is the inclusive one
    /// k = -6 is only BPiz (|z| < 25 cm)
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

    plot = std::string( plotName.str().c_str() );
    plotBg = std::string( plotNameBg.str().c_str() );

    //printf(plot.c_str());
    //printf("\n");

    cPlots = new TCanvas(("c_"+plot).c_str(),"");
    
    cPlots->cd();

    h = new TH2D();
    h = (TH2D*)inputFile->Get( plot.c_str() );
    h->Sumw2();
    h->GetXaxis()->SetTitle("x [cm]");
    h->GetYaxis()->SetTitle("y [cm]");
    h->Draw("col");

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());

    /// Step 1: find the background density as a function of phi and rho(x0, y0)

    Double_t bgFit0[40];
    Double_t bgFit0Err[40];
    Double_t bgFit1[40];
    Double_t bgFit1Err[40];

    for ( int phiSect = 0; phiSect < 40; phiSect ++ )
    {
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );

      Int_t numBinsX = h->GetNbinsX();
      Int_t numBinsY = h->GetNbinsY();

      for ( int ix = 1; ix <= numBinsX; ix++ )
      {
        for ( int iy = 1; iy <= numBinsY; iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x - 0.087;
          Double_t yc = y + 0.197;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < 2 || rc > 4 ) continue;

          Double_t pc = TMath::ATan2( yc, xc );

          Int_t thisPhiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != phiSect ) continue;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );

          hbgua0->Fill( rc, densityNum );

          if ( ( rc > 2.5 && rc < 2.7 ) || ( rc > 3.1 && rc < 3.3 ) )
          {
            hbgua1->Fill( rc, densityNum );
          }
          else if ( rc > 2.7 && rc < 3.1 )
          {
            hbgua2->Fill( rc, densityNum );
          }
        }
      }

      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2011}_{0},y^{2011}_{0}) [cm]");
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

      TF1 *fitBg = new TF1( "fitBg","[0] + x*[1]", 2.45, 3.35 );
      fitBg->SetParameter(0, 100);
      fitBg->SetParameter(1, -0.9);
      fitBg->SetParName(0, "N0");
      fitBg->SetParName(1, "k");
      fitBg->SetParLimits(0, 0, 1E9);
      fitBg->SetParLimits(1, -1E9, 0);
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

      std::ostringstream fn;
      fn << "Plots/"<<plotBg.c_str()<<"_BGUA" << "_" << phiSect<<".pdf";
      cPlots->SaveAs(fn.str().c_str());
      fn.str("");
      fn << "Plots/"<<plotBg.c_str()<<"_BGUA" << "_" << phiSect<<".png";
      cPlots->SaveAs(fn.str().c_str());
    }

    cPlots->Delete();

    /// Step 2: calculate background

    plot = plot + "_Bgk";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");
    cPlots->cd();

    TH2D* h0 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h0->GetXaxis()->SetTitle("x [cm]");
    h0->GetYaxis()->SetTitle("y [cm]");

    Int_t numBinsX = h0->GetNbinsX();
    Int_t numBinsY = h0->GetNbinsY();
    for ( int ix = 1; ix <= numBinsX; ix++ )
    {
      for ( int iy = 1; iy <= numBinsY; iy++ )
      {
        Double_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );

        Double_t xc = x - 0.087;
        Double_t yc = y + 0.197;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

        if ( rc < 2 || rc > 4 ) continue;

        Double_t pc = TMath::ATan2( yc, xc );

        if ( rc > 2.5 && rc < 3.3 )
        {
          int phiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          /// Average over 3 adjacent sectors to smooth differences
          Double_t avg0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          Double_t avg1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );

          Double_t bgDensity = avg0 + avg1*rc;
          Double_t bgNum = h0->GetXaxis()->GetBinWidth( ix ) * h0->GetYaxis()->GetBinWidth( iy ) * bgDensity;

          if ( ( rc > 2.5 && rc < 3.3 ) )
            h0->Fill( x, y, bgNum );
        }
      }
    }

    h0->Draw("col");

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());
    cPlots->Delete();

    /// Step 3: cross check background with original densities used for the fit

    for ( int phiSect = 0; phiSect < 40; phiSect ++ )
    {
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua3 = new TH1D( (plotBg+"_BGUA3").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );

      Int_t numBinsX = h->GetNbinsX();
      Int_t numBinsY = h->GetNbinsY();

      for ( int ix = 1; ix <= numBinsX; ix++ )
      {
        for ( int iy = 1; iy <= numBinsY; iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x - 0.087;
          Double_t yc = y + 0.197;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < 2 || rc > 4 ) continue;

          Double_t pc = TMath::ATan2( yc, xc );

          Int_t thisPhiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != phiSect ) continue;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );

          hbgua0->Fill( rc, densityNum );

          if ( ( rc > 2.5 && rc < 2.7 ) || ( rc > 3.1 && rc < 3.3 ) )
          {
            hbgua1->Fill( rc, densityNum );
          }
          else if ( rc > 2.7 && rc < 3.1 )
          {
            hbgua2->Fill( rc, densityNum );
          }

          Double_t binNum0 = h0->GetBinContent( ix, iy );

          Double_t densityNum0 = binNum0 / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );
          if ( ( rc > 2.5 && rc < 3.3 ) )
          {
            hbgua3->Fill( rc, densityNum0 );
          }

        }
      }

      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2011}_{0},y^{2011}_{0}) [cm]");
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

      TF1 *fitBg = new TF1( "fitBg","[0] + x*[1]", 2.45, 3.35 );
      fitBg->SetParameter(0, bgFit0[phiSect]);
      fitBg->SetParameter(1, bgFit1[phiSect]);
      fitBg->SetParName(0, "N0");
      fitBg->SetParName(1, "k");
      fitBg->SetLineWidth(2);
      fitBg->Draw("same");

      TLegend* legBg = new TLegend(x1L, 0.52, x2L, y2L, "");
      legBg->SetTextFont(42);
      legBg->SetTextSize(0.03);
      legBg->SetFillColor(TColor::kWhite);
      legBg->SetTextColor(TColor::kBlack);
      legBg->AddEntry(hbgua0,"inclusive data","l");
      legBg->AddEntry(hbgua2,"signal fit region","f");
      legBg->AddEntry(hbgua1,"sideband fit region","f");
      legBg->AddEntry(fitBg,"sideband fit function","l");
      legBg->AddEntry(hbgua3,"estimated background","f");
      legBg->Draw("same");

      gStyle->SetOptStat(1000111110);

      std::ostringstream fn;
      fn << "Plots/"<<plotBg.c_str()<<"_BGUA_XCk" << "_" << phiSect<<".pdf";
      cPlots->SaveAs(fn.str().c_str());
      fn.str("");
      fn << "Plots/"<<plotBg.c_str()<<"_BGUA_XCk" << "_" << phiSect<<".png";
      cPlots->SaveAs(fn.str().c_str());
    }

    /// Step 4: subtract the background from the signal

    const std::string stBg = "_Bkg";
    if ( plot != stBg &&
         plot.size() > stBg.size() &&
         plot.substr(plot.size() - stBg.size()) == "_Bkg" )
    plot = plot.substr(0, plot.size() - stBg.size());

    plot = plot + "_Fit";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");
    cPlots->cd();

    TH2D* h1 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h1->GetXaxis()->SetTitle("x [cm]");
    h1->GetYaxis()->SetTitle("y [cm]");

    Int_t numBinsX = h->GetNbinsX();
    Int_t numBinsY = h->GetNbinsY();
    for ( int ix = 1; ix <= numBinsX; ix++ )
    {
      for ( int iy = 1; iy <= numBinsY; iy++ )
      {
        Double_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );

        Double_t xc = x - 0.087;
        Double_t yc = y + 0.197;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );
        Double_t pc = TMath::ATan2( yc, xc );

        if ( rc > 2.5 && rc < 3.3 )
//        if ( rc > 2.7 && rc < 3.1 )
        {
          int phiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          /// Remove Background
          /// Average over 3 adjacent sectors to smooth differences
          Double_t avg0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          Double_t avg1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );

          Double_t bgDensity = avg0 + avg1*rc;
          Double_t bgNum = h1->GetXaxis()->GetBinWidth( ix ) * h1->GetYaxis()->GetBinWidth( iy ) * bgDensity;

          binNum -= bgNum;
//          if (binNum > 0)
            h1->Fill( x, y, binNum );
        }
      }
    }

    /// Step 5: fit the distribution

    h1->SetMinimum(1);
    h = h1;

    /// par[0] = R
    /// par[1] = x0
    /// par[2] = y0

    TVirtualFitter::SetDefaultFitter("Minuit");
    TVirtualFitter* fitter = TVirtualFitter::Fitter( 0, 3 );
    fitter->SetFCN( chiSquareFunc );
    fitter->SetParameter( 0,  "R",     3, 0.01, 2.6, 3.3 );
    fitter->SetParameter( 1, "x0",  0.06, 0.01, -0.3, 0.3 );
    fitter->SetParameter( 2, "y0", -0.18, 0.01, -0.3, 0.3 );

    //fitter->SetParameter( 0,  "R", 2.932, 0.01, 2.6, 3.3 );
    //fitter->FixParameter( 0 );
    Double_t arglist[10] = {0.};
    fitter->ExecuteCommand( "MIGRAD", arglist, 0 );

    h->Draw("col");

    TArc* arc = new TArc( fitter->GetParameter(1), fitter->GetParameter(2), fitter->GetParameter(0) );
    arc->SetFillStyle(0);
    arc->SetLineColor(TColor::kRed);
    arc->SetLineWidth(2);
    arc->Draw("same");

    cPlots->Update();

    TPaveStats* s = (TPaveStats*)h0->GetListOfFunctions()->FindObject("stats");
    x1L = s->GetX1NDC();
    x2L = s->GetX2NDC();
    y1L = s->GetY1NDC();
    y2L = s->GetY2NDC();

    TPaveText* res = new TPaveText(x1L, y1L-0.22, x2L, y2L-0.42, "brNDC");
    std::ostringstream legEntry;
    legEntry.str("");
    legEntry << "R (cm) \t = \t" << fitter->GetParameter(0) << " +/- " << fitter->GetParError(0);
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "x_{0} (mm) \t = \t" << fitter->GetParameter(1)*10 << " +/- " << fitter->GetParError(1)*10;
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "y_{0} (mm) \t = \t" << fitter->GetParameter(2)*10 << " +/- " << fitter->GetParError(2)*10;
    res->AddText( legEntry.str().c_str() );
    res->SetFillStyle(0);
    res->SetTextAlign(12);
    res->SetTextColor(TColot::kRed);
    res->SetLineColor(TColot::kRed);
    res->SetTextFont(42);
    res->Draw("same");

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
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());
    cPlots->Delete();
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
  gRfit->GetYaxis()->SetRangeUser(2.7, 3.2);
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
  gx0fit->GetYaxis()->SetRangeUser(0.3, 1.3);
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
  gy0fit->GetYaxis()->SetRangeUser(-2.3, -1.3);
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
  cPlots->SaveAs("Plots/FitResults.pdf");
  cPlots->SaveAs("Plots/FitResults.png");

}
