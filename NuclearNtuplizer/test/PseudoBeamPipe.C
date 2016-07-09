
// all units are in cm
void PseudoBeamPipe(double R0, double x0, double y0, double width){

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

  TFile* file_out = new TFile(Form("PseudoBeamPipe_r%.2fcm_x0%.2fcm_y0%.2fcm_w%.2fcm.root", R0, x0, y0, width), "RECREATE");
  GenCircle->Write();
  GenCircleRPhi->Write();
  file_out->Close();


}
