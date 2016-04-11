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

TH2D* h;
TH2D* hrp;
TCanvas* cPlots;

double FitSup = 3.0, FitInf = 2.4, PipeInf = 2.0, PipeSup = 2.4, Inf = 1.8, Sup = 3.0, PlotSup = 2.6; 
double x0 =  0.128;//1.69759e-01;
double y0 = 0.028;//3.86970e-02;
double r0 = 2.22;

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
      if ( r > PipeInf && r < FitInf )
      {

	Double_t PhaseSpaceFactor = (r0*r0)/(r*r);

        diff = par[0] - r;
	chiSquare += binNum*diff*diff / ( resoNI*resoNI) *PhaseSpaceFactor;//  + halfWidthPipe*halfWidthPipe );// + halfWidthPipe*halfWidthPipe );
      }
//	if (fabs(diff) > halfWidthPipe)  chiSquare += binNum*diff*diff / ( resoNI*resoNI);
	
    }
  }
  f = chiSquare;
}




void HistogramFitterNuclearInteractions_BeamPipe()
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
    h->SetStats(0);
    h->GetXaxis()->SetTitle("x [cm]");
    h->GetYaxis()->SetTitle("y [cm]");
    h->GetXaxis()->SetRangeUser(-PlotSup, PlotSup);
    h->GetYaxis()->SetRangeUser(-PlotSup, PlotSup);
    h->Draw("col");

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());

    h->Draw("LEGO");
    cPlots->SaveAs(("Plots/"+plot+"_LEGO.pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+"_LEGO.png").c_str()); 


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

          Double_t densityNum = binNum * rc*rc / (2.2*2.2);

	  h->SetBinContent(ix, iy, densityNum);

        }
      }
    h->GetXaxis()->SetRangeUser(-PlotSup, PlotSup);
    h->GetYaxis()->SetRangeUser(-PlotSup, PlotSup);
    h->Draw("LEGO");
    cPlots->SaveAs(("Plots/"+plot+"_FluxCorrection_LEGO.pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+"_FluxCorrection_LEGO.png").c_str()); 


    /// -------------- Step 1: find the background density as a function of phi and rho(x0, y0) ----------


    Double_t bgFit0[40];
    Double_t bgFit0Err[40];
    Double_t bgFit1[40];
    Double_t bgFit1Err[40];

    //divide 2D x-y plot into 40 sectors in phi as function of R
    for ( UInt_t phiSect = 0; phiSect < 40; phiSect ++ )
    {
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );

      Int_t numBinsX = h->GetNbinsX();
      Int_t numBinsY = h->GetNbinsY();

      for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x - x0;
          Double_t yc = y - y0;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Inf || rc > Sup ) continue;

          Double_t pc = TMath::ATan2( yc, xc );

          Int_t thisPhiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != phiSect ) continue;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );

          hbgua0->Fill( rc, densityNum );

          if ( ( rc > Inf && rc < PipeInf ) || ( rc > PipeSup && rc < FitSup ) )
          {
            hbgua1->Fill( rc, densityNum );
          }
          else if ( rc >= PipeInf && rc <= PipeSup )
          {
            hbgua2->Fill( rc, densityNum );
          }
        }
      }

      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2015}_{0},y^{2015}_{0}) [cm]");
      hbgua0->GetXaxis()->SetRangeUser(PipeInf, FitSup+0.1);


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

      TF1 *fitBg = new TF1( "fitBg","[0] + x*[1]", FitInf, FitSup );
      fitBg->SetParameter(0, 100);
      fitBg->SetParameter(1, -0.9);
      fitBg->SetParName(0, "N0");
      fitBg->SetParName(1, "k");
      //we  need set limits here to avoid negative values in fit (it will crash)
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

        if ( rc < Inf || rc > Sup ) continue;

        Double_t pc = TMath::ATan2( yc, xc );

        if ( rc > PipeInf && rc < PipeSup )
        {
          UInt_t phiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          /// Average over 3 adjacent sectors to smooth differences
          Double_t avg0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          Double_t avg1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );
          //Double_t avg0 =  bgFit0[phiSect];
          //Double_t avg1 =  bgFit1[phiSect];

          Double_t bgDensity = avg0 + avg1*rc;
          Double_t bgNum = h0->GetXaxis()->GetBinWidth( ix ) * h0->GetYaxis()->GetBinWidth( iy ) * bgDensity;

          if ( ( rc > PipeInf && rc < PipeSup ) )
            h0->Fill( x, y, bgNum );
        }
      }
    }

    h0->Draw("col");

    // plot average estimated background in signal region from PipeInf to PipeSup
    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());


    h0->Draw("LEGO");

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+"_LEGO.pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+"_LEGO.png").c_str());
    //cPlots->Delete();
    //delete cPlots;

    /// ----------- Step 3: cross check background with original densities used for the fit -------------

    for ( UInt_t phiSect = 0; phiSect < 40; phiSect ++ )
    {
      TH1D* hbgua0 = new TH1D( (plotBg+"_BGUA0").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua1 = new TH1D( (plotBg+"_BGUA1").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua2 = new TH1D( (plotBg+"_BGUA2").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );
      TH1D* hbgua3 = new TH1D( (plotBg+"_BGUA3").c_str(), "Counts per Unit Area in transverse plane", 40, 2, 4 );

      Int_t numBinsX = h->GetNbinsX();
      Int_t numBinsY = h->GetNbinsY();

      for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
      {
        for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
        {
          Double_t x = h->GetXaxis()->GetBinCenter( ix );
          Double_t y = h->GetYaxis()->GetBinCenter( iy );

          Double_t xc = x - x0;
          Double_t yc = y - y0;

          Double_t rc = TMath::Sqrt( xc*xc + yc*yc );

          if ( rc < Inf || rc > Sup ) continue;

          Double_t pc = TMath::ATan2( yc, xc );

          Int_t thisPhiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          if ( thisPhiSect != phiSect ) continue;

          Double_t binNum = h->GetBinContent( ix, iy );

          Double_t densityNum = binNum / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );

          hbgua0->Fill( rc, densityNum );

          if ( ( rc > Inf && rc < PipeInf ) || ( rc > PipeSup && rc < FitSup ) )
          {
            hbgua1->Fill( rc, densityNum );
          }
          else if ( rc >= PipeInf && rc <= PipeSup )
          {
            hbgua2->Fill( rc, densityNum );
          }

          Double_t binNum0 = h0->GetBinContent( ix, iy );

          Double_t densityNum0 = binNum0 / ( rc * (TMath::Pi()/20) * hbgua0->GetXaxis()->GetBinWidth(1) );
          if ( ( rc > PipeInf && rc < PipeSup ) )
          {
            hbgua3->Fill( rc, densityNum0 );
          }

        }
      }

      cPlots->cd();
      hbgua0->SetMinimum(0);
      hbgua0->GetXaxis()->SetTitle("#rho (x^{2015}_{0},y^{2015}_{0}) [cm]");
      hbgua0->GetXaxis()->SetRangeUser(PipeInf, FitSup+0.1);
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

      TF1 *fitBg = new TF1( "fitBg","[0] + x*[1]", FitInf, FitSup );
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
      //delete to avoid memory leak:
      //cPlots->Delete();
      //delete cPlots;
      delete hbgua0;
      delete hbgua1;
      delete hbgua2;
      delete hbgua3;
    }

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
        Double_t pc = TMath::ATan2( yc, xc );

        if ( rc > Inf && rc < Sup )
//        if ( rc > 2.7 && rc < 3.1 )
        {
          UInt_t phiSect = floor( ( pc + TMath::Pi() ) / ( 2*TMath::Pi() ) * 40 );

          /// Remove Background
          /// Average over 3 adjacent sectors to smooth differences
          Double_t avg0 = 1/3. * ( bgFit0[phiSect] + bgFit0[(41+phiSect)%40] + bgFit0[(39+phiSect)%40] );
          Double_t avg1 = 1/3. * ( bgFit1[phiSect] + bgFit1[(41+phiSect)%40] + bgFit1[(39+phiSect)%40] );
          //Double_t avg0 =  bgFit0[phiSect];
          //Double_t avg1 =  bgFit1[phiSect];

          Double_t bgDensity = avg0 + avg1*rc;
          Double_t bgNum = h1->GetXaxis()->GetBinWidth( ix ) * h1->GetYaxis()->GetBinWidth( iy ) * bgDensity;

          //binNum -= bgNum; // subtrackt 1 BG only
          binNum -= (bgNum+2*sqrt(bgNum)); //sbutrackt BG+2sigmaBF
          //binNum -= (2*bgNum); // subtrackt 2 BG
          if (binNum < 0) binNum = 0;
	  h1->Fill( x, y, binNum );
        }
      }
    }

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
    fitter->SetParameter( 0,  "R",   r0, 0.01, 2.10, 2.5 ); // in cm
    fitter->SetParameter( 1, "x0",   x0, 0.001, -0.3, 0.3 ); // in cm
    fitter->SetParameter( 2, "y0",   y0, 0.001, -0.1, 0.1 ); // in cm
    //   fitter->FixParameter(1); fitter->FixParameter(2); 


    //fitter->SetParameter( 0,  "R", 2.932, 0.01, 2.6, 3.3 );
    //fitter->FixParameter( 0 );
    Double_t arglist[10] = {0.};
    fitter->ExecuteCommand( "MIGRAD", arglist, 0 );

    //if small slice, then rebin histo for better view
    if(k > -6 && k < 5) h->Rebin2D(5,5);
    h->GetXaxis()->SetRangeUser(-PlotSup, PlotSup);
    h->GetYaxis()->SetRangeUser(-PlotSup, PlotSup);
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
    cPlots->SaveAs(("Plots/"+plot+".root").c_str());

    TFile* f = new TFile(("Plots/"+plot+".root").c_str(), "UPDATE");
    
    h->Write("BEAM_PIPE");
    f->Close();
    //cPlots->Delete();
    //delete cPlots;

    h->GetXaxis()->SetRangeUser(-PlotSup, PlotSup);
    h->GetYaxis()->SetRangeUser(-PlotSup, PlotSup);

    h->Draw("LEGO");
    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+"_LEGO.pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+"_LEGO.png").c_str());
    //cPlots->Delete();
    //delete cPlots;

    h->Draw("COLZ");
    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+"_COLZ.pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+"_COLZ.png").c_str());
    //cPlots->Delete();
    //delete cPlots;
    //plot->Delete();
    //plotBg->Delete();

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
  gRfit->GetYaxis()->SetRangeUser(2.0, 2.4);
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
  cPlots->SaveAs("Plots/FitResults.pdf");
  cPlots->SaveAs("Plots/FitResults.png");

}
