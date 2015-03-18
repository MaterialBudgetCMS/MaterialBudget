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
TCanvas* cPlots;

void chiSquareFunc( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Double_t resoNI = 0.01;
  Double_t halfWidthPipe = 0.025;
  Int_t numBinsX = h->GetNbinsX();
  Int_t numBinsY = h->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;
  Bool_t skip = h->Integral() > 500000;
  for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
  {
    for ( UInt_t iy = 1; iy <= numBinsY; iy++ ) 
    {
      Int_t binNum = h->GetBinContent( ix, iy );

      /// Thresholds
      /// 2011A+B: 5 entries for inclusive
      ///          3 entries for 5 cm slices
      /// 2012A+B+C+D: 20 entries for inclusive
      ///              5 entries for 5 cm slices      
      if ( skip && binNum < 5 ) continue;
      if ( !skip && binNum < 3 ) continue;

      Double_t x = h->GetXaxis()->GetBinCenter( ix );
      Double_t y = h->GetYaxis()->GetBinCenter( iy );
      Double_t r = TMath::Sqrt( x*x + y*y );
      if ( r > 2.5 && r < 3.2 )
      {
        Double_t u = x - par[1];
        Double_t v = y - par[2];
        diff = par[0] - TMath::Sqrt(u*u + v*v);
        chiSquare += binNum*diff*diff / ( resoNI*resoNI + halfWidthPipe*halfWidthPipe );
      }
    }
  }
  f = chiSquare;
}

void HistogramFitterNuclearInteractions_BeamPipe2011AB()
{
  //gROOT->SetBatch(1);
  gROOT->ForceStyle();

  TFile* inputFile = TFile::Open("prova.root");

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
    std::ostringstream plotName;

    plotName.str("");
    plotName << plot.c_str();

    /// k = -7 is the inclusive one
    /// k = -6 is only BPiz (|z| < 25 cm)
    if ( k == -6 )
      plotName << "_AbsZ25";
    else if ( k != -7 )
      plotName << "_" << k*5 << "_" << (k+1)*5;

    plot = std::string( plotName.str().c_str() );

    printf(plot.c_str());
    printf("\n");

    cPlots = new TCanvas(("c_"+plot).c_str(),"");

    h = new TH2D();
    h = (TH2D*)inputFile->Get( plot.c_str() );
    h->GetXaxis()->SetTitle("x [cm]");
    h->GetYaxis()->SetTitle("y [cm]");
    h->Draw("col");

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());

    for ( Int_t minBin = 1; minBin < 31; minBin+=1 )
    {
      h->SetMinimum( minBin );
      std::ostringstream minBinStr;
      minBinStr.str("");
      minBinStr << "_Min" << minBin;

      cPlots->Update();
      cPlots->SaveAs(("Plots/"+plot+minBinStr.str()+".pdf").c_str());
      cPlots->SaveAs(("Plots/"+plot+minBinStr.str()+".png").c_str());
    }
    h->SetMinimum( 0 );

    cPlots->Delete();

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

    plot = plot + "_Fit";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");

    TH2D* h0 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h0->GetXaxis()->SetTitle("x [cm]");
    h0->GetYaxis()->SetTitle("y [cm]");

    Bool_t skip = h->Integral() > 500000;

    Int_t numBinsX = h0->GetNbinsX();
    Int_t numBinsY = h0->GetNbinsY();
    for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
    {
      for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
      {
        Int_t binNum = h->GetBinContent( ix, iy );
        if ( skip && binNum < 5 ) continue;
        if ( !skip && binNum < 3 ) continue;

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );
        Double_t r = TMath::Sqrt( x*x + y*y );
        if ( r > 2.5 && r < 3.2 )
        {
          h0->Fill( x, y, binNum );
        }
      }
    }

    //h0->Draw("col");
    h0->SetMarkerStyle(6);
    h0->SetMinimum( skip ? 4 : 2 );
    h0->Draw();

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
  /*
  TLegend* legRfit = new TLegend(0.16,0.72,0.41,0.78);
  legRfit->SetTextSize(0.03);
  legRfit->SetFillColor(TColor::kWhite);
  legRfit->SetTextColor(TColor::kBlack);
  legRfit->AddEntry(gRfit,"R (cm)","p");
  legRfit->Draw();
  */
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
  /*
  TLegend* legx0fit = new TLegend(0.16,0.72,0.41,0.78);
  legx0fit->SetTextSize(0.03);
  legx0fit->SetFillColor(TColor::kWhite);
  legx0fit->SetTextColor(TColor::kBlack);
  legx0fit->AddEntry(gx0fit,"x_{0} (mm)","p");
  legx0fit->Draw();
  */
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
  /*
  TLegend* legy0fit = new TLegend(0.16,0.72,0.41,0.78);
  legy0fit->SetTextSize(0.03);
  legy0fit->SetFillColor(TColor::kWhite);
  legy0fit->SetTextColor(TColor::kBlack);
  legy0fit->AddEntry(gy0fit,"y_{0} (mm)","p");
  legy0fit->Draw();
  */


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
