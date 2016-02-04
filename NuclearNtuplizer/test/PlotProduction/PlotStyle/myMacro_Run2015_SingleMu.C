TString StyleCol = "BW"; // BW = balk/white, COL = color style
TString HigtoName = "hPFDV_ZR_Map"; // hPFDV_XY_Map_Pipe = beam pipe xy; hPFDV_RhoPhi_Map_Pipe = beam pipe rho-phi
//TString HigtoName = "hPFDV_XY_Map_Pipe"; // hPFDV_XY_Map_Pipe = beam pipe xy; hPFDV_RhoPhi_Map_Pipe = beam pipe rho-phi
//TString HigtoName = "hPFDV_RhoPhi_Map_Pipe"; // hPFDV_XY_Map_Pipe = beam pipe xy; hPFDV_RhoPhi_Map_Pipe = beam pipe rho-phi
int PlotBeamPipeAlternative = 0; //0 - don't plot, 1 - plot Alternative mesurement and (0,0)

void myMacro_Run2015_SingleMu()
{


  gROOT->LoadMacro("tdrstyle.C");
  setTDRStyle();

  gROOT->LoadMacro("CMS_lumi.C");

  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  extraText  = "Internal";  // default extra text is "Preliminary"
  lumi_8TeV  = "19.1 fb^{-1}"; // default is "19.7 fb^{-1}"
  lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
  //lumi_13TeV  = "7.3 pb^{-1}";  // default is "XXX"
  lumi_13TeV  = "Run2015 D";  // default is "XXX"
  //lumi_13TeV  = "Run2015 B";  // default is "XXX"
  //lumi_13TeV  = "Run2015 C";  // default is "XXX"

  int iPeriod = 13;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 13 = 13TeV 

  // second parameter in example_plot is iPos, which drives the position of the CMS logo in the plot
  // iPos=11 : top-left, left-aligned
  // iPos=33 : top-right, right-aligned
  // iPos=22 : center, centered
  // mode generally : 
  //   iPos = 10*(alignement 1/2/3) + position (1/2/3 = left/center/right)

  example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)
  //  example_plot( iPeriod, 11 );  // left-aligned
 //   example_plot( iPeriod, 33 );  // right-aligned

  //  writeExtraText = false;       // remove Preliminary
  
  //  example_plot( iPeriod, 0 );   // out of frame (in exceptional cases)

  //  example_plot( iPeriod, 11 );  // default: left-aligned
  //  example_plot( iPeriod, 22 );  // centered
  //  example_plot( iPeriod, 33 );  // right-aligned  
}

TCanvas* example_plot( int iPeriod, int iPos )
{ 
  //  if( iPos==0 ) relPosX = 0.12;

  int W = 800;
  //int H = 600;
  int H = 800;

  // 
  // Simple example of macro: plot with CMS name and lumi text
  //  (this script does not pretend to work in all configurations)
  // iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
  // For instance: 
  //               iPeriod = 3 means: 7 TeV + 8 TeV
  //               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
  // Initiated by: Gautier Hamel de Monchenault (Saclay)
  //
  int H_ref = 600; 
  int W_ref = 800; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;

  TString canvName = "FigBeamPipe_";
  canvName += W;
  canvName += "-";
  canvName += H;
  canvName += "_";  
  canvName += iPeriod;
  if(HigtoName == "hPFDV_RhoPhi_Map_Pipe") canvName += "_BeamPipe_RhoPhi";
  if(HigtoName == "hPFDV_ZR_Map") canvName += "__ZR";
  if(HigtoName == "hPFDV_XY_Map_Pipe") canvName += "_BeamPipe_XY";
  if(PlotBeamPipeAlternative == 1) canvName += "_AlternativeBP";

  if( writeExtraText ) canvName += "-prelim";
  if( iPos%10==0 ) canvName += "-out";
  else if( iPos%10==1 ) canvName += "-left";
  else if( iPos%10==2 )  canvName += "-center";
  else if( iPos%10==3 )  canvName += "-right";

  TCanvas* canv = new TCanvas(canvName,canvName,50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);

  TH1* h = new TH1F("h","h",40,70,110);
  h->GetXaxis()->SetNdivisions(6,5,0);
  h->GetXaxis()->SetTitle("m_{e^{+}e^{-}} (GeV)");  
  h->GetYaxis()->SetNdivisions(6,5,0);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetTitle("Events / 0.5 GeV");  

  h->SetMaximum( 260 );
  if( iPos==1 ) h->SetMaximum( 300 );
  //h->Draw();

  int histLineColor = kOrange+7;
  int histFillColor = kOrange-2;
  float markerSize  = 1.0;

  {
    TLatex latex;
				
    int n_ = 2;

    float x1_l = 0.92;
    float y1_l = 0.60;

    float dx_l = 0.30;
    float dy_l = 0.18;
    float x0_l = x1_l-dx_l;
    float y0_l = y1_l-dy_l;

    TPad* legend = new TPad("legend_0","legend_0",x0_l,y0_l,x1_l, y1_l );
    //    legend->SetFillColor( kGray );
    legend->Draw();
    legend->cd();
		
    float ar_l = dy_l/dx_l;
		
    float x_l[1];
    float ex_l[1];
    float y_l[1];
    float ey_l[1];
		
    //    float gap_ = 0.09/ar_l;
    float gap_ = 1./(n_+1);
		
    float bwx_ = 0.12;
    float bwy_ = gap_/1.5;
		
    x_l[0] = 1.2*bwx_;
    //    y_l[0] = 1-(1-0.10)/ar_l;
    y_l[0] = 1-gap_;
    ex_l[0] = 0;
    ey_l[0] = 0.04/ar_l;
		
    TGraph* gr_l = new TGraphErrors(1, x_l, y_l, ex_l, ey_l );
		
    gStyle->SetEndErrorSize(0);
    gr_l->SetMarkerSize(0.9);
    gr_l->Draw("0P");
		
    latex.SetTextFont(42);
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    latex.SetTextSize(0.25);    
    latex.SetTextAlign(12); 
		
    TLine line_;
    TBox  box_;
    float xx_ = x_l[0];
    float yy_ = y_l[0];
    latex.DrawLatex(xx_+1.*bwx_,yy_,"Data");
		
    yy_ -= gap_;
    box_.SetLineStyle( kSolid );
    box_.SetLineWidth( 1 );
    //		box_.SetLineColor( kBlack );
    box_.SetLineColor( histLineColor );
    box_.SetFillColor( histFillColor );
    box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );
    box_.SetFillStyle(0);
    box_.DrawBox( xx_-bwx_/2, yy_-bwy_/2, xx_+bwx_/2, yy_+bwy_/2 );
    latex.DrawLatex(xx_+1.*bwx_,yy_,"Z #rightarrow e^{+}e^{-} (MC)");

    canv->cd();
  }

  {
        gROOT->Clear();
        gStyle->SetOptStat(0);
        gStyle->SetPalette(1,0); //// blue to red false color palette. Use 9 for b/w
        gStyle->SetOptTitle(0);


    // Observed data
    //TFile file_("histo.root","READ");
    //TFile file_("../MCplot_Run2015D.root","READ");
    //TFile file_("../MCplot_Run2015B.root","READ");
    TFile file_("../MCplot_Run2015C.root","READ");

    TH2D *data = (TH1*) (file_.Get(HigtoName)->Clone());
    data->SetDirectory(0);
    //data->SetMarkerStyle(20);
    data->SetMarkerSize(markerSize);
    //data->SetMarkerSize(0.15);
    data->GetYaxis()->SetTitleOffset(1.1);
    data->GetYaxis()->SetTitleSize(0.045);
    data->GetXaxis()->SetTitleSize(0.045);
    data->SetTitle(" ");
    data->SetStats(0);

    if(StyleCol == "COL"){ 
      canv->SetRightMargin(0.1);
      canv->SetBottomMargin(0.15);
    }

    if(HigtoName == "hPFDV_XY_Map_Pipe" || HigtoName == "hPFDV_ZR_Map"){ 
      data->GetXaxis()->SetTitle("x (cm)");
      data->GetYaxis()->SetTitle("y (cm)");
    }
    if(HigtoName == "hPFDV_ZR_Map"){ 
      data->GetXaxis()->SetTitle("z (cm)");
      data->GetYaxis()->SetTitle("R (cm)");
    }
    if(HigtoName == "hPFDV_RhoPhi_Map_Pipe"){ 
      data->GetXaxis()->SetTitle("#phi");
      data->GetYaxis()->SetTitle("Radius (cm)");
    }
    //TH1F *MC   = (TH1*) (file_.Get("MC")->Clone());
    //MC->SetDirectory(0);
    //MC->SetLineColor(histLineColor);
    //MC->SetFillColor(histFillColor);

    //MC->Draw("histsame");
    //data->Draw("esamex0");
    //data->Draw("COL"); //without scale for Z axis
    //data->SetMinimum(20.); 
    //TH2D* h2 = new TH2D("h2", "h2", 10, -200., 200., 10, 20., 70.);
    //h2 ->Draw();
    if(StyleCol == "COL")data->Draw("9COLZ");
    if(StyleCol == "BW")data->Draw();
    if(HigtoName == "hPFDV_ZR_Map"){ 

      TF1 *fa = new TF1("fa"," x*tan( 2*atan(exp(-[0])) )",0,200);
      fa->SetParameter(0,2.5);
      fa->SetLineColor(kRed);
      fa->SetLineWidth(2);
      fa->Draw("same"); 

      TF1 *fa1 = new TF1("fa1"," x*tan( 2*atan(exp(-[0])) )",0,200);
      fa1->SetParameter(0,1.4);
      fa1->SetLineColor(kRed);
      fa1->SetLineWidth(2);
      fa1->Draw("same"); 

      TF1 *fa2 = new TF1("fa2"," x*tan( 2*atan(exp(-[0])) )",0,200);
      fa2->SetParameter(0,1.);
      fa2->SetLineColor(kRed);
      fa2->SetLineWidth(2);
      fa2->Draw("same"); 

      TF1 *fa3 = new TF1("fa3"," x*tan( 2*atan(exp(-[0])) )",0,200);
      fa3->SetParameter(0,0.4);
      fa3->SetLineColor(kRed);
      fa3->SetLineWidth(2);
      fa3->Draw("same"); 

      TF1 *fa4 = new TF1("fa4"," x*tan( 2*atan(exp(-[0])) )",-200,0);
      fa4->SetParameter(0,-0.4);
      fa4->SetLineColor(kRed);
      fa4->SetLineWidth(2);
      fa4->Draw("same"); 

      TF1 *fa5 = new TF1("fa5"," x*tan( 2*atan(exp(-[0])) )",-200,0);
      fa5->SetParameter(0,-1.);
      fa5->SetLineColor(kRed);
      fa5->SetLineWidth(2);
      fa5->Draw("same"); 

      TF1 *fa6 = new TF1("fa6"," x*tan( 2*atan(exp(-[0])) )",-200,0);
      fa6->SetParameter(0,-1.4);
      fa6->SetLineColor(kRed);
      fa6->SetLineWidth(2);
      fa6->Draw("same"); 

      TF1 *fa7 = new TF1("fa7"," x*tan( 2*atan(exp(-[0])) )",-200,0);
      fa7->SetParameter(0,-2.5);
      fa7->SetLineColor(kRed);
      fa7->SetLineWidth(2);
      fa7->Draw("same"); 

    }  

    if(HigtoName == "hPFDV_XY_Map_Pipe" && PlotBeamPipeAlternative == 1){
       TArc* arc = new TArc( 0.075, 0.015, 2.25);
       arc->SetFillStyle(0);
       arc->SetLineColor(TColor::kRed);
       arc->SetLineWidth(2);
       arc->Draw("same");

       Double_t x[1], y[1];
       x[0] = 0.075;
       y[0] = 0.015;
       gr = new TGraph(1,x,y);
       gr->SetMarkerStyle(20);
       gr->SetMarkerSize(0.5);
       gr->SetMarkerColor(TColor::kRed);
       gr->Draw("P");

       TArc* arc00 = new TArc( 0.0, 0.0, 2.25);
       arc00->SetFillStyle(0);
       arc00->SetLineColor(TColor::kBlue);
       arc00->SetLineWidth(2);
       arc00->Draw("same");

       x[0] = 0.0;
       y[0] = 0.0;
       gr00 = new TGraph(1,x,y);
       gr00->SetMarkerStyle(20);
       gr00->SetMarkerSize(0.5);
       gr00->SetMarkerColor(TColor::kBlue);
       gr00->Draw("P");
    }

    if(HigtoName == "hPFDV_RhoPhi_Map_Pipe" && PlotBeamPipeAlternative == 1){
       TF1 *bpAlt = new TF1("bpAlt","sqrt((2.25*cos(x)+0.075)^2 + (2.25*sin(x)+0.015)^2)",-3.15,3.15);
       bpAlt->SetLineColor(TColor::kRed);
       bpAlt->SetLineWidth(2);
       bpAlt ->Draw("same");

       TF1 *bp00 = new TF1("bp00","sqrt((2.25*cos(x)+0.0)^2 + (2.25*sin(x)+0.0)^2)",-3.15,3.15);
       bp00->SetLineColor(TColor::kBlue);
       bp00->SetLineWidth(2);
       bp00 ->Draw("same");

    }
    file_.Close();
  }

  // writing the lumi information and the CMS "logo"
  CMS_lumi( canv, iPeriod, iPos );

  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();

  //canv->Print("Plots_BeamPipe/"+canvName+"_test.pdf",".pdf");
  //canv->Print("Plots_BeamPipe/"+canvName+"_test.root",".root");
  canv->Print("Plots_BeamPipe/"+canvName+"_test.png",".png");

  return canv;
}
