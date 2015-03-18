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

void chiSquareFunc0( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Double_t resoNI = 0.01;
  Double_t halfWidthBPixSupp = 0.5;

  Int_t numBinsX = h->GetNbinsX();
  Int_t numBinsY = h->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;

  for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
  {
    for ( UInt_t iy = 1; iy <= numBinsY; iy++ ) 
    {
      Int_t binNum = h->GetBinContent( ix, iy );

      Double_t x = h->GetXaxis()->GetBinCenter( ix );
      Double_t y = h->GetYaxis()->GetBinCenter( iy );

      if ( y < 18.9 || y > 19.3 ) continue;
      if ( x < -9 || x > 9 || ( x > -4.6 && x < -2.2 ) || ( x > 2.2 && x < 4.6 ) ) continue;

      diff = y - ( par[0] + x*par[1] );
      chiSquare += binNum*diff*diff / ( resoNI*resoNI + halfWidthBPixSupp*halfWidthBPixSupp );
    }
  }
  f = chiSquare;
}

void chiSquareFunc1( Int_t &, Double_t *, Double_t &f, Double_t *par, Int_t )
{
  Double_t resoNI = 0.01;
  Double_t halfWidthBPixSupp = 0.5;

  Int_t numBinsX = h->GetNbinsX();
  Int_t numBinsY = h->GetNbinsY();
  Double_t chiSquare = 0.0;
  Double_t diff = 0.0;

  for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
  {
    for ( UInt_t iy = 1; iy <= numBinsY; iy++ ) 
    {
      Int_t binNum = h->GetBinContent( ix, iy );

      Double_t x = h->GetXaxis()->GetBinCenter( ix );
      Double_t y = h->GetYaxis()->GetBinCenter( iy );

      if ( y < -20 || y > -19.6 ) continue;
      if ( x < -9 || x > 9 || ( x > -4.6 && x < -2.2 ) || ( x > 2.2 && x < 4.6 ) ) continue;

      diff = y - ( par[0] + x*par[1] );
      chiSquare += binNum*diff*diff / ( resoNI*resoNI + halfWidthBPixSupp*halfWidthBPixSupp );
    }
  }
  f = chiSquare;
}

void HistogramFitterNuclearInteractions_BPixSuppRails2012ABCD()
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

  Double_t resa[10];
  Double_t erra[10];
  Double_t resb[10];
  Double_t errb[10];
/*
  Double_t resx0[10];
  Double_t errx0[10];
  Double_t resy0[10];
  Double_t erry0[10];
  Double_t resp0[10];
  Double_t errp0[10];
*/
  Double_t resZ[10];
  Double_t errZ[10] = {2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5, 2.5};

  Double_t x1L, x2L, y1L, y2L;

  for ( int k = -7; k < 5; k++ )
  {
    std::string plot = "hPFDV_XY_Map_BPix";
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

    cPlots->SetLogz();

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());

    cPlots->SetLogz(0);

    for ( Int_t minBin = 1; minBin < 11; minBin+=1 )
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

    plot = plot + "_Fit";
    cPlots = new TCanvas(("c_"+plot).c_str(),"");

    TH2D* h0 = new TH2D( plot.c_str(), h->GetTitle(), h->GetNbinsX(), h->GetXaxis()->GetBinLowEdge(1), h->GetXaxis()->GetBinUpEdge(h->GetNbinsX()),
                                                      h->GetNbinsY(), h->GetYaxis()->GetBinLowEdge(1), h->GetYaxis()->GetBinUpEdge(h->GetNbinsY()) );
    h0->GetXaxis()->SetTitle("x [cm]");
    h0->GetYaxis()->SetTitle("y [cm]");

    //Bool_t skip = h->Integral() > 500000;

    Int_t numBinsX = h0->GetNbinsX();
    Int_t numBinsY = h0->GetNbinsY();
    for ( UInt_t ix = 1; ix <= numBinsX; ix++ )
    {
      for ( UInt_t iy = 1; iy <= numBinsY; iy++ )
      {
        Int_t binNum = h->GetBinContent( ix, iy );

        Double_t x = h->GetXaxis()->GetBinCenter( ix );
        Double_t y = h->GetYaxis()->GetBinCenter( iy );

        if ( y > 19.3 || y < -20 || ( y > -19.6 && y < 18.9 ) ) continue;
        if ( x < -9 || x > 9 || ( x > -4.6 && x < -2.2 ) || ( x > 2.2 && x < 4.6 ) ) continue;

        h0->Fill( x, y, binNum );
      }
    }

    h = h0;

    TVirtualFitter::SetDefaultFitter("Minuit");
    TVirtualFitter* fitter = TVirtualFitter::Fitter( 0, 2 );

    Double_t arglist[10] = {0.};

    //h0->Draw("col");
    h0->SetMarkerStyle(6);
    //h0->SetMinimum( skip ? 4 : 2 );
    //if (k<-5)
      h0->Draw("col");
    //else
      //h0->Draw();

    fitter->SetFCN( chiSquareFunc0 );
    fitter->SetParameter( 0,  "y_{0,1}", 19, 0.01, 15, 22.5 );
    fitter->SetParameter( 1,  "k_{1}",    0, 0.01, -1,    1 );
    fitter->ExecuteCommand( "MIGRAD", arglist, 0 );

    Double_t x1 = -10; 
    Double_t x2 = 10; 
    Double_t y11 = fitter->GetParameter(0) + x1 * fitter->GetParameter(1);
    Double_t y12 = fitter->GetParameter(0) + x2 * fitter->GetParameter(1);

    TLine * line1 = new TLine ( x1, y11, x2, y12 );
    line1->SetLineColor(TColor::kRed);
    line1->SetLineWidth(2);
    line1->Draw("same");

    cPlots->Update();

    TPaveStats* s = (TPaveStats*)h0->GetListOfFunctions()->FindObject("stats");
    x1L = s->GetX1NDC();
    x2L = s->GetX2NDC();
    y1L = s->GetY1NDC();
    y2L = s->GetY2NDC();

    TPaveText* res = new TPaveText(x1L, y1L-0.17, x2L, y2L-0.42, "brNDC");
    std::ostringstream legEntry;
    legEntry.str("");
    legEntry << "y_{1} (cm) \t = \t" << fitter->GetParameter(0) << " +/- " << fitter->GetParError(0);
    res->AddText( legEntry.str().c_str() );

    if ( k > -6 )
    {
      resZ[k+5] = 0.5*(k*5 + (k+1)*5);
      resa[k+5] = fitter->GetParameter(0);
      erra[k+5] = fitter->GetParError(0);
    }

    fitter->SetFCN( chiSquareFunc1 );
    fitter->SetParameter( 0,  "y_{0,2}", -19.8, 0.01, -23.5, -18 );
    fitter->SetParameter( 1,  "k_{2}",       0, 0.01, -1,      1 );
    fitter->ExecuteCommand( "MIGRAD", arglist, 0 );

    Double_t y21 = fitter->GetParameter(0) + x1 * fitter->GetParameter(1);
    Double_t y22 = fitter->GetParameter(0) + x2 * fitter->GetParameter(1);

    TLine * line2 = new TLine ( x1, y21, x2, y22 );
    line2->SetLineColor(TColor::kBlue);
    line2->SetLineWidth(2);
    line2->Draw("same");

    cPlots->Update();

    legEntry.str("");
    legEntry << "y_{2} (cm) \t = \t" << fitter->GetParameter(0) << " +/- " << fitter->GetParError(0);
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");

    res->SetFillStyle(0);
    res->SetTextAlign(12);
    res->SetTextColor(TColot::kRed);
    res->SetLineColor(TColot::kRed);
    res->SetTextFont(42);
    res->Draw("same");


    if ( k > -6 )
    {
      resZ[k+5] = 0.5*(k*5 + (k+1)*5);
      resb[k+5] = fitter->GetParameter(0);
      errb[k+5] = fitter->GetParError(0);
    }

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());
    cPlots->Delete();
  }



  /// Summary TGraph
  TGraphErrors* gx0fit = new TGraphErrors( 10, resZ, resa, errZ, erra );
  gx0fit->GetXaxis()->SetTitle("z [cm]");
  gx0fit->GetYaxis()->SetTitle("y_{1} [cm]");
  gx0fit->SetTitle("fit results");
  gx0fit->SetMarkerStyle(20);
  gx0fit->SetMarkerSize(1.2);
  gx0fit->SetMarkerColor(TColor::kRed);
  gx0fit->SetLineColor(TColor::kRed);
  gx0fit->SetDrawOption("ap");
  TF1* fx0fit = new TF1("fx0fit","[0]+[1]*x",-25,25);
  fx0fit->SetParNames("y_{1s} (cm)","k_{y1} (cm/cm)");
  fx0fit->SetLineColor(TColor::kRed);
  fx0fit->SetMarkerColor(TColor::kRed);
  gx0fit->Fit("fx0fit","RWEMS");
  gx0fit->Draw("ap");
  cPlots->Update();

  TGraphErrors* gy0fit = new TGraphErrors( 10, resZ, resb, errZ, errb );
  gy0fit->GetXaxis()->SetTitle("z [cm]");
  gy0fit->GetYaxis()->SetTitle("y_{2} [cm]");
  gy0fit->SetTitle("fit results");
  gy0fit->SetMarkerStyle(20);
  gy0fit->SetMarkerSize(1.2);
  gy0fit->SetMarkerColor(TColor::kBlue);
  gy0fit->SetLineColor(TColor::kBlue);
  gy0fit->SetDrawOption("ap");
  TF1* fy0fit = new TF1("fy0fit","[0]+[1]*x",-25,25);
  fy0fit->SetParNames("y_{2s} (cm)","k_{y2} (cm/cm)");
  fy0fit->SetLineColor(TColor::kBlue);
  fy0fit->SetMarkerColor(TColor::kBlue);
  gy0fit->Fit("fy0fit","RWEMS");
  gy0fit->Draw("ap");
  cPlots->Update();

  cPlots->cd();

  TPad* pad1 = new TPad("pad1", "", 0, 0.50, 1, 1.00, 0, 0, 0);
  TPad* pad2 = new TPad("pad2", "", 0, 0.00, 1, 0.50, 0, 0, 0);

  pad2->SetTopMargin(0.000);
  pad2->SetBottomMargin(pad2->GetBottomMargin()*2.6);
  pad1->SetTopMargin(pad1->GetTopMargin()*2.6);
  pad1->SetBottomMargin(0.000);

  //gafit->SetTitle("");

  pad1->Draw();
  pad2->Draw();

  double labelSizeFactor1 = (pad1->GetHNDC()+pad2->GetHNDC()) / pad1->GetHNDC();
  double labelSizeFactor2 = (pad1->GetHNDC()+pad2->GetHNDC()) / pad2->GetHNDC();

  pad1->cd();
  //gafit->SetTitle("fit results");
  //gafit->GetYaxis()->SetTitle("a, b (cm)");
  gx0fit->GetYaxis()->SetRangeUser(18.5, 19.5);
  gx0fit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor1);
  gx0fit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor1);
  gx0fit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor1);
  gx0fit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor1);
  gx0fit->GetYaxis()->SetTitleOffset(gx0fit->GetYaxis()->GetTitleOffset()/labelSizeFactor1);
  gx0fit->Draw("ap");
  pad1->Update();
  TPaveStats *statsx0fit = (TPaveStats*)gx0fit->GetListOfFunctions()->FindObject("stats");
  statsx0fit->SetTextColor(TColor::kRed);
  statsx0fit->SetLineColor(TColor::kRed);
  statsx0fit->SetX1NDC(x1L);
  statsx0fit->SetX2NDC(x2L);
  statsx0fit->SetY1NDC(0.371);
  statsx0fit->SetY2NDC(0.665);
  pad1->Update();

  TPaveText *title = (TPaveText*)pad1->GetPrimitive("title");
  title->SetY1NDC( 0.78 );
  title->SetY2NDC( 0.94 );

  //gbfit->Draw("p same");
  //gbfit->GetListOfFunctions()->FindObject("stats")->Delete();

  pad1->Modified();

  pad2->cd();
  gy0fit->SetTitle("");
  gy0fit->GetYaxis()->SetRangeUser(-20.3, -19.3);
  gy0fit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor2);
  gy0fit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor2);
  gy0fit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor2);
  gy0fit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor2);
  gy0fit->GetYaxis()->SetTitleOffset(gy0fit->GetYaxis()->GetTitleOffset()/labelSizeFactor2);
  gy0fit->Draw("ap");
  pad2->Update();
  TPaveStats *statsy0fit = (TPaveStats*)gy0fit->GetListOfFunctions()->FindObject("stats");
  statsy0fit->SetTextColor(TColor::kBlue);
  statsy0fit->SetLineColor(TColor::kBlue);
  statsy0fit->SetX1NDC(x1L);
  statsy0fit->SetX2NDC(x2L);
  statsy0fit->SetY1NDC(0.657);
  statsy0fit->SetY2NDC(0.932);
  pad2->Update();

  cPlots->SaveAs("Plots/FitResults.pdf");
  cPlots->SaveAs("Plots/FitResults.png");

}
