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

      //if ( ( y > 18.5 && y < 20.5 ) || (  y > -21.5 && y < -19.5 ) ) continue;

      Double_t xc = x + 0.079;
      Double_t yc = y + 0.325;

      Double_t rc = TMath::Sqrt( xc*xc + yc*yc );
      if ( rc > 21.1 && rc < 22.7 )
      {
        //0 a
        //1 b
        //2 x0
        //3 y0
        //4 phi0

        // Move to ellipse center
        Double_t u = x - par[2];
        Double_t v = y - par[3];

        /// Back-Rotate
        Double_t p =   u * TMath::Cos(par[4]) + v * TMath::Sin(par[4]);
        Double_t q = - u * TMath::Sin(par[4]) + v * TMath::Cos(par[4]);

        /// Now the ellipse is correctly centered
/*
        Double_t phi = TMath::ATan2(q, p);
        Double_t r = TMath::Sqrt(u*u* + v*v);
        Double_t rphi2 = (par[0]*par[0]*par[1]*par[1]) / (par[0]*par[0]*TMath::Sin(phi)*TMath::Sin(phi)
                                                        + par[1]*par[1]*TMath::Cos(phi)*TMath::Cos(phi) );
        diff = r - TMath::Sqrt(rphi2);
*/
        diff = TMath::Sqrt(par[0]*par[1]) - TMath::Power( p*p*par[1]*par[1] + q*q*par[0]*par[0], 0.25 );

        chiSquare += binNum*diff*diff / ( resoNI*resoNI + halfWidthBPixSupp*halfWidthBPixSupp );
      }
    }
  }
  f = chiSquare;
}

void HistogramFitterNuclearInteractions_BPixSuppEllipse2012ABCD()
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
  Double_t resx0[10];
  Double_t errx0[10];
  Double_t resy0[10];
  Double_t erry0[10];
  Double_t resp0[10];
  Double_t errp0[10];
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

        //if ( ( y > 18.5 && y < 20.5 ) || (  y > -21.5 && y < -19.5 ) ) continue;

        Double_t xc = x + 0.079;
        Double_t yc = y + 0.325;

        Double_t rc = TMath::Sqrt( xc*xc + yc*yc );
        if ( rc > 21.1 && rc < 22.7 )
        {
          h0->Fill( x, y, binNum );
        }
      }
    }

    h = h0;

    //0 a
    //1 b
    //2 x0
    //3 y0
    //4 phi0

    TVirtualFitter::SetDefaultFitter("Minuit");
    TVirtualFitter* fitter = TVirtualFitter::Fitter( 0, 5 );
    fitter->SetFCN( chiSquareFunc );
    fitter->SetParameter( 0,  "a",    22.3, 0.01, 21,    22.5 );
    fitter->SetParameter( 1,  "b",    21.2, 0.01, 21,    22.5 );
    fitter->SetParameter( 2, "x0",   -0.10, 0.01, -0.7,  0.7 );
    fitter->SetParameter( 3, "y0",   -0.50, 0.01, -0.7,  0.7 );
    fitter->SetParameter( 4, "phi0",   0.0, 0.01, 0.35*TMath::Pi(), 0.65*TMath::Pi() );

    //fitter->SetParameter( 0,  "R", 2.932, 0.01, 2.6, 3.3 );
    //fitter->FixParameter( 0 );

    Double_t arglist[10] = {0.};
    fitter->ExecuteCommand( "MIGRAD", arglist, 0 );

    //h0->Draw("col");
    h0->SetMarkerStyle(6);
    //h0->SetMinimum( skip ? 4 : 2 );
    //if (k<-5)
      h0->Draw("col");
    //else
      //h0->Draw();


    TEllipse *arc = new TEllipse( fitter->GetParameter(2), fitter->GetParameter(3),
                                  fitter->GetParameter(0), fitter->GetParameter(1),
                                  0, 360, TMath::RadToDeg()*fitter->GetParameter(4) );
    arc->SetFillStyle(0);
    arc->SetLineColor(TColor::kRed);
    //arc->SetLineWidth(2);
    arc->Draw("same");

    cPlots->Update();

    TPaveStats* s = (TPaveStats*)h0->GetListOfFunctions()->FindObject("stats");
    x1L = s->GetX1NDC();
    x2L = s->GetX2NDC();
    y1L = s->GetY1NDC();
    y2L = s->GetY2NDC();

    TPaveText* res = new TPaveText(x1L, y1L-0.32, x2L, y2L-0.42, "brNDC");
    std::ostringstream legEntry;
    legEntry.str("");
    legEntry << "a (cm) \t = \t" << fitter->GetParameter(0) << " +/- " << fitter->GetParError(0);
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "b (cm) \t = \t" << fitter->GetParameter(1) << " +/- " << fitter->GetParError(1);
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "x_{0} (mm) \t = \t" << fitter->GetParameter(2)*10 << " +/- " << fitter->GetParError(2)*10;
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "y_{0} (mm) \t = \t" << fitter->GetParameter(3)*10 << " +/- " << fitter->GetParError(3)*10;
    res->AddText( legEntry.str().c_str() );
    legEntry.str("");
    legEntry << "#phi_{0} (deg)\t = \t" << TMath::RadToDeg()*fitter->GetParameter(4) << " +/- " << TMath::RadToDeg()*fitter->GetParError(4);
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
      resa[k+5] = fitter->GetParameter(0);
      erra[k+5] = fitter->GetParError(0);
      resb[k+5] = fitter->GetParameter(1);
      errb[k+5] = fitter->GetParError(1);
      resx0[k+5] = fitter->GetParameter(2)*10;
      errx0[k+5] = fitter->GetParError(2)*10;
      resy0[k+5] = fitter->GetParameter(3)*10;
      errx0[k+5] = fitter->GetParError(3)*10;
      resp0[k+5] = fitter->GetParameter(4)*TMath::RadToDeg();
      errp0[k+5] = fitter->GetParError(4)*TMath::RadToDeg();
    }

    cPlots->Update();
    cPlots->SaveAs(("Plots/"+plot+".pdf").c_str());
    cPlots->SaveAs(("Plots/"+plot+".png").c_str());
    cPlots->Delete();
  }

  /// Summary TGraph
  cPlots = new TCanvas("results","");
  TGraphErrors* gafit = new TGraphErrors( 10, resZ, resa, errZ, erra );
  gafit->GetXaxis()->SetTitle("z [cm]");
  gafit->GetYaxis()->SetTitle("a,b [cm]");
  gafit->SetTitle("fit results");
  gafit->SetMarkerStyle(20);
  gafit->SetMarkerSize(1.2);
  gafit->SetMarkerColor(TColor::kBlack);
  gafit->SetDrawOption("ap");
  TF1* fafit = new TF1("fafit","[0]+[1]*x",-25,25);
  fafit->SetParNames("a_{s} (cm)","k_{a} (cm/cm)");
  fafit->SetLineColor(TColor::kBlack);
  fafit->SetMarkerColor(TColor::kBlack);
  gafit->Fit("fafit","RWEMS");
  gafit->Draw("ap");
  cPlots->Update();

  TGraphErrors* gbfit = new TGraphErrors( 10, resZ, resb, errZ, errb );
  gbfit->GetXaxis()->SetTitle("z [cm]");
  gbfit->GetYaxis()->SetTitle("b [cm]");
  gbfit->SetTitle("fit results");
  gbfit->SetMarkerStyle(24);
  gbfit->SetMarkerSize(1.2);
  gbfit->SetMarkerColor(TColor::kBlack);
  gbfit->SetDrawOption("ap");
  TF1* fbfit = new TF1("fbfit","[0]+[1]*x",-25,25);
  fbfit->SetParNames("b_{s} (cm)","k_{b} (cm/cm)");
  fbfit->SetLineColor(TColor::kBlack);
  fbfit->SetMarkerColor(TColor::kBlack);
  gbfit->Fit("fbfit","RWEMS");
  gbfit->Draw("psame");
  cPlots->Update();

  TGraphErrors* gx0fit = new TGraphErrors( 10, resZ, resx0, errZ, errx0 );
  gx0fit->GetXaxis()->SetTitle("z [cm]");
  gx0fit->GetYaxis()->SetTitle("x_{0}, y_{0} [mm]");
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

  TGraphErrors* gp0fit = new TGraphErrors( 10, resZ, resp0, errZ, errp0 );
  gp0fit->GetXaxis()->SetTitle("z [cm]");
  gp0fit->GetYaxis()->SetTitle("#phi_{0} [deg]");
  gp0fit->SetTitle("fit results");
  gp0fit->SetMarkerStyle(20);
  gp0fit->SetMarkerSize(1.2);
  gp0fit->SetMarkerColor(TColor::kGreen);
  gp0fit->SetLineColor(TColor::kGreen);
  gp0fit->SetDrawOption("ap");
  TF1* fp0fit = new TF1("fp0fit","[0]+[1]*x",-25,25);
  fp0fit->SetParNames("#phi_{0s} (deg)","k_{#phi0} (deg/cm)");
  fp0fit->SetLineColor(TColor::kGreen);
  fp0fit->SetMarkerColor(TColor::kGreen);
  gp0fit->Fit("fp0fit","RWEMS");
  gp0fit->Draw("ap");
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

  //gafit->SetTitle("");

  pad1->Draw();
  pad2->Draw();
  pad3->Draw();

  double labelSizeFactor1 = (pad1->GetHNDC()+pad2->GetHNDC()+pad3->GetHNDC()) / pad1->GetHNDC();
  double labelSizeFactor2 = (pad1->GetHNDC()+pad2->GetHNDC()+pad3->GetHNDC()) / pad2->GetHNDC();
  double labelSizeFactor3 = (pad1->GetHNDC()+pad2->GetHNDC()+pad3->GetHNDC()) / pad3->GetHNDC();

  pad1->cd();
  //gafit->SetTitle("fit results");
  //gafit->GetYaxis()->SetTitle("a, b (cm)");
  gafit->GetYaxis()->SetRangeUser(21.5, 22);
  gafit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor1);
  gafit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor1);
  gafit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor1);
  gafit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor1);
  gafit->GetYaxis()->SetTitleOffset(gafit->GetYaxis()->GetTitleOffset()/labelSizeFactor1);
  gafit->Draw("ap");
  gbfit->Draw("psames");
  pad1->Update();
  TPaveStats *statsafit = (TPaveStats*)gafit->GetListOfFunctions()->FindObject("stats");
  statsafit->SetTextColor(TColor::kBlack);
  statsafit->SetLineColor(TColor::kBlack);
  statsafit->SetX1NDC(x1L);
  statsafit->SetX2NDC(x2L);
  statsafit->SetY1NDC(0.371);
  statsafit->SetY2NDC(0.665);
  pad1->Update();
  TPaveStats *statsbfit = (TPaveStats*)gbfit->GetListOfFunctions()->FindObject("stats");
  statsbfit->SetFillColor(TColor::kBlack);
  statsbfit->SetTextColor(TColor::kWhite);
  statsbfit->SetLineColor(TColor::kWhite);
  statsbfit->SetX1NDC(x1L);
  statsbfit->SetX2NDC(x2L);
  statsbfit->SetY2NDC(0.371);
  statsbfit->SetY1NDC(0.077);
  pad1->Update();

  TPaveText *title = (TPaveText*)pad1->GetPrimitive("title");
  title->SetY1NDC( 0.78 );
  title->SetY2NDC( 0.94 );

  //gbfit->Draw("p same");
  //gbfit->GetListOfFunctions()->FindObject("stats")->Delete();

  pad1->Modified();

  pad2->cd();
  gx0fit->SetTitle("");
  gx0fit->GetYaxis()->SetRangeUser(-3.9, -0.1);
  gx0fit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor2);
  gx0fit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor2);
  gx0fit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor2);
  gx0fit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor2);
  gx0fit->GetYaxis()->SetTitleOffset(gx0fit->GetYaxis()->GetTitleOffset()/labelSizeFactor2);
  gx0fit->Draw("ap");
  gy0fit->Draw("psames");
  pad2->Update();
  TPaveStats *statsx0fit = (TPaveStats*)gx0fit->GetListOfFunctions()->FindObject("stats");
  statsx0fit->SetTextColor(TColor::kRed);
  statsx0fit->SetLineColor(TColor::kRed);
  statsx0fit->SetX1NDC(x1L);
  statsx0fit->SetX2NDC(x2L);
  statsx0fit->SetY1NDC(0.5);
  statsx0fit->SetY2NDC(0.9);
  pad2->Update();
  TPaveStats *statsy0fit = (TPaveStats*)gy0fit->GetListOfFunctions()->FindObject("stats");
  statsy0fit->SetTextColor(TColor::kBlue);
  statsy0fit->SetLineColor(TColor::kBlue);
  statsy0fit->SetX1NDC(x1L);
  statsy0fit->SetX2NDC(x2L);
  statsy0fit->SetY1NDC(0.1);
  statsy0fit->SetY2NDC(0.5);
  pad2->Update();

  pad3->cd();
  gp0fit->SetTitle("");
  gp0fit->GetYaxis()->SetRangeUser(50, 130);
  gp0fit->GetXaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor3);
  gp0fit->GetYaxis()->SetLabelSize(gStyle->GetLabelSize()*labelSizeFactor3);
  gp0fit->GetXaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor3);
  gp0fit->GetYaxis()->SetTitleSize(gStyle->GetTitleSize()*labelSizeFactor3);
  gp0fit->GetYaxis()->SetTitleOffset(gp0fit->GetYaxis()->GetTitleOffset()/labelSizeFactor3);
  gp0fit->Draw("ap");
  pad3->Update();
  TPaveStats *statsp0fit = (TPaveStats*)gp0fit->GetListOfFunctions()->FindObject("stats");
  statsp0fit->SetTextColor(TColor::kGreen);
  statsp0fit->SetLineColor(TColor::kGreen);
  statsp0fit->SetX1NDC(x1L);
  statsp0fit->SetX2NDC(x2L);
  statsp0fit->SetY1NDC(0.657);
  statsp0fit->SetY2NDC(0.932);
  //gphi21fit->Draw("p same");
  //gphi21fit->GetListOfFunctions()->FindObject("stats")->Delete();

  pad3->Update();
  cPlots->SaveAs("Plots/FitResults.pdf");
  cPlots->SaveAs("Plots/FitResults.png");


}
