void Sphere(TH2D* hFIT, double Rmin, double Rmax, double Rexp, int xsplit)  {
  double rx0, ry0, rR02;
  double xg = 0, yg = 0, zg = 0, p2g = 0;



  double N = 0;
  double Rexp2 = Rexp*Rexp;

  TMatrix M(1,3);
  TMatrix Mg(1,3);
  TMatrix A(3,3);

  

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){
 
      double Nbin = hFIT->GetBinContent(i, j);
 

      if (Nbin < 1e-5) continue;

      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double R2 = ybin*ybin + xbin*xbin;
      double R = sqrt(R2);
      double p = (1+R2);

      // ----------- Phase space correction -----------

      double Ncorr = Nbin*R2/(Rexp2);
      hFIT->SetBinContent(i, j, Ncorr);
      Nbin = hFIT->GetBinContent(i, j);

 

      //if (xbin > 0) cout <<  "xbin before  =  " << xbin << endl; 
      //     if (xbin < 0) cout <<  "xsplit =  " << xsplit*xbin << endl;
      if (R < Rmin || R > Rmax || xsplit*xbin < -1e-6){
	hFIT->SetBinContent(i, j, 0);
	continue;
      }
      //    cout <<  "xbin =  " << xbin << endl; 

      double cosPhi = xbin/R;
      double sinPhi = ybin/R;
      double x = R*cosPhi/p;
      double y = R*sinPhi/p;
      double z = R2/p;

      Mg[0][0] += x*Nbin;
      Mg[0][1] += y*Nbin;
      Mg[0][2] += z*Nbin;
      N += Nbin;

    }

  }

  Mg *= 1./N;

  for (int i = 1; i< hFIT->GetXaxis()->GetNbins()+1; i++){
    double xbin = hFIT->GetXaxis()->GetBinCenter(i);

    for (int j = 1; j< hFIT->GetYaxis()->GetNbins()+1; j++){

      double Nbin = hFIT->GetBinContent(i, j);

      if (Nbin < 1e-5) continue;

      double ybin = hFIT->GetYaxis()->GetBinCenter(j);
      double R2 = ybin*ybin + xbin*xbin;
      double R = sqrt(R2);
      double p = (1+R2);

      if (R < Rmin || R > Rmax  || xsplit*xbin < -1e-8) continue;

      double cosPhi = xbin/R;
      double sinPhi = ybin/R;
      double x = R*cosPhi/p;
      double y = R*sinPhi/p;
      double z = R2/p;


      TMatrix Diff(1,3);

      Diff[0][0] = (x-Mg[0][0]);
      Diff[0][1] = (y-Mg[0][1]);
      Diff[0][2] = (z-Mg[0][2]);
      
      TMatrix ntDiff = Diff;
      TMatrix tDiff = Diff.Transpose(Diff);

      TMatrix mDiff = tDiff*ntDiff;

      A += Nbin*mDiff;

    }

  }

  //  cout << "N = " << N << endl;
  
  A *= (1.0/N);
  /*
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++)
      cout << " " << A[i][j];
    cout << ""<<endl;
  }
  */
  TVectorF eigVal;

  TMatrix Egenv = A.EigenVectors(eigVal);
  /*
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++)
    cout << " " << Egenv[i][j];
    cout << " is Eigenv"<<endl;
      }
  */


  /*
  for(int i = 0; i < 3; i++){
  cout << " " << eigVal[i];
  }
  */
  //  cout << "" << endl;

  TMatrix n(3,1);
  n[0][0] = Egenv[0][2];
  n[1][0] = Egenv[1][2]; 
  n[2][0] = Egenv[2][2];
  


  TMatrix zero = A*n - eigVal[2]*n;

  /*
  for(int i = 0; i < 3; i++){
    //     cout << " " << n[i][0];
    //    cout << " is n "<<endl;
  }

  for(int i = 0; i < 3; i++){
    cout << " " << zero[i][0];
    cout << " is An - lbda*n "<<endl;
  }
  */
  /*
    cout << "Norm = " << n[0][0]*n[0][0] + n[1][0]*n[1][0] + n[2][0]*n[2][0] << endl;

    for(int i = 0; i < 3; i++){
    cout << " " << Mg[0][i];
    }
    cout << " is Mg" << endl; 
  */

  double xg = Mg[0][0], yg = Mg[0][1], zg = Mg[0][2];
  double n0 = n[0][0], n1 = n[1][0], n2 = n[2][0];

  double c = -1*( xg*n0 + yg*n1 + zg*n2);

  //  cout << "c = " << c << endl;



  rx0 = -1.0/2 * n0/(c+n2);
  ry0 = -1* n[1][0]/(2*(c+n[2][0]));
  rR02 = ( n[0][0]*n[0][0] + n[1][0]*n[1][0] - 4*c*(c+n[2][0]) )/(4*(c+n[2][0]) * (c+n[2][0]));
  double rr0 = sqrt(rR02);
  cout << "x0 = " << 10*rx0 << " mm,  y0 = " << 10*ry0 << " mm,  r0 = " << rr0 << " cm"<< endl;
 
  string sRes = Form("x0 = %.3f mm, y0 = %.3f, r0 = %.3f cm", 10*rx0, 10*ry0, rr0);

  TH2D* PLOTTER = new TH2D("PLOTTER", "PLOTTER", 1, -1.3*rr0, 1.3*rr0, 1, -1.3*rr0, 1.3*rr0);
  PLOTTER->SetStats(0);
  PLOTTER->SetTitle(hFIT->GetTitle());
  PLOTTER->SetXTitle("x (cm)");
  PLOTTER->SetYTitle("x (cm)");

  PLOTTER->Draw("COLZ");
  hFIT->Draw("COLZSAME");


  TEllipse* Circle = new TEllipse(rx0, ry0, rr0);
  Circle->SetFillStyle(0);
  Circle->Draw();

  TEllipse* CircleFit = new TEllipse(rx0, ry0, rr0*0.02);
  CircleFit->SetFillColor(kRed);
  CircleFit->SetLineColor(kRed);
  CircleFit->Draw();

  TEllipse* Circle0 = new TEllipse(0, 0, rr0*0.02);
  Circle0->SetFillColor(kBlack);
  Circle0->Draw();

  TLatex latex;
  latex.SetTextSize(0.035);
  latex.DrawLatex(-rr0*1.0, -rr0*1.2, sRes.c_str());


 
}

TH2D* GenerateCircle(double R0, double x0, double y0, double width){

  TRandom3* rnd = new TRandom3(1000);

  TH2D* GenCircle = new TH2D("GenCircle", " Generated Circle; x (cm); y (cm)", 100, -5, 5, 100, -5, 5);
  TH2D* GenCircleRPhi = new TH2D("GenCircleRPhi", " Generated Circle; phi (cm); y (cm)", 100, 0, 2.*TMath::Pi(), 100, 0, 5);
  for (int i = 0; i < 1e6; i++){

    if (i%200000 == 0) cout << i << endl;
    double phi = rnd->Uniform()*2*TMath::Pi();
    double R = rnd->Gaus(R0, 0.01) + rnd->Uniform(-width/2, width/2);
    double x = R*cos(phi), y = R*sin(phi);
    double w = R0*R0/(R*R);
    GenCircle->Fill(x+x0, y+y0, w);

    double pseudoPhi = atan((y+y0)/(x+x0));
    double pseudoR = sqrt((y+y0)*(y+y0)+(x+x0)*(x+x0));

    if (x+x0 < 0) pseudoPhi += TMath::Pi();
    if (x+x0>0 && y+y0<0) pseudoPhi += 2*TMath::Pi();

    GenCircleRPhi->Fill(pseudoPhi, pseudoR, w);
    

  }



  GenCircleRPhi->SetStats(0);
  GenCircleRPhi->Draw("COLZ");

  TFile* file_out = new TFile("PseudoBeamPipe_r22p2mm_x01mm_y0m1mm_w0p8mm.root", "RECREATE");
  GenCircle->Write();
  GenCircleRPhi->Write();
  file_out->Close();

  return GenCircle;

}

void Riemann(){

  TCanvas* cnv = new TCanvas("cnv", "", 800, 800);
  gPad->SetRightMargin(0.12);
  cnv->cd();
  //
  /*
  cout << " ================= Beam Pipe ============== " << endl;

  TFile *_file0 = TFile::Open("BeamPipe_Fit.root");
  TH2D* hFIT = (TH2D*) _file0->Get("BEAM_PIPE;1");
  hFIT->SetTitle("BEAM PIPE; x (cm); y(cm)");
  

  double Rmin = 2.0, Rmax = 2.4, Rexp = 2.21; int xsplit = 0;
  Sphere(hFIT, Rmin, Rmax, Rexp, xsplit);
  
  cnv->Update();
  cnv->SaveAs("BeamPipe_2015.png");
  cnv->SaveAs("BeamPipe_2015.pdf");
  cnv->Clear();
  _file0->Close();
 
  cout << " ================= Pixel Support ============== " << endl;

  TFile *_file0 = TFile::Open("PixelSupport_Fit.root");
  TH2D* hFIT = (TH2D*)  _file0->Get("BEAM_PIPE;1");
  hFIT->SetTitle("Pixel Support; x (cm); y(cm)");

  double Rmin = 21.0, Rmax = 22.0, Rexp = 21.7; int xsplit = 0;
  Sphere(hFIT, Rmin, Rmax, Rexp, xsplit);
  
  cnv->Update();
  cnv->SaveAs("PixelSupport_2015.png");
  cnv->SaveAs("PixelSupport_2015.pdf");
  cnv->Clear();
  _file0->Close();
  
  cout << " ================= Pixel Shield ============== " << endl;

  TFile *_file0 = TFile::Open("PixelShield_Fit.root");
  TH2D* hFIT = (TH2D*)  _file0->Get("BEAM_PIPE;1");
  hFIT->SetTitle("Pixel Shield Plus; x (cm); y(cm)");

  cout << " === Positive side ====" << endl;

  double Rmin = 3.5, Rmax = 3.9, Rexp = 3.78; int xsplit = 1;
  Sphere(hFIT, Rmin, Rmax, Rexp, xsplit);

  cnv->Update();
  cnv->SaveAs("PixelShieldPlus_2015.png");
  cnv->SaveAs("PixelShieldPlus_2015.pdf");
  cnv->Clear();
  _file0->Close();

  cout << " === Negative side ====" << endl;

  TFile *_file0 = TFile::Open("PixelShield_Fit.root");
  TH2D* hFIT = (TH2D*)  _file0->Get("BEAM_PIPE;1");
  hFIT->SetTitle("Pixel Shield Minus; x (cm); y(cm)");
  double Rmin = 3.5, Rmax = 3.9, Rexp = 3.78; int xsplit = -1;
  Sphere(hFIT, Rmin, Rmax, Rexp, xsplit);

  cnv->Update();
  cnv->SaveAs("PixelShieldMinus_2015.png");
  cnv->SaveAs("PixelShieldMinus_2015.pdf");
  cnv->Clear();
  _file0->Close();
  
  */
 
  cout << " ================= Random Cicrle with Radius 2p22 cm ============== " << endl;

  TH2D* hFIT = GenerateCircle(2.22, 0.1,-0.1, 0.08);
  cnv->SaveAs("RPhi_2p22cm.png");
  cnv->SaveAs("RPhi_2p22cm.pdf");

  double Rmin = 2.0, Rmax = 2.4, Rexp = 2.22; int xsplit = 0;
  Sphere(hFIT, Rmin, Rmax, Rexp, xsplit);
  
  cnv->Update();
  cnv->SaveAs("GenCircle_2p22cm.png");
  cnv->SaveAs("GenCircle_2p22cm.pdf");
  cnv->Clear();
 
}
















