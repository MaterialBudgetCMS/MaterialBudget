
// all units are in cm
//void PseudoBeamPipe(double R0, double x0, double y0, double width, int Nmax){
void PseudoBeamPipe(double R0 = 2.211, double x0 = 0.124, double y0 = 0.027, double width = 0.05, int Nmax = 150000){ // 2015 CMS
//void PseudoBeamPipe(double R0 = 2.210, double x0 = 0.171, double y0 = -0.176, double width = 0.05, int Nmax = 150000){ // 2018 preliminary
//void PseudoBeamPipe(double R0 = 2.210, double x0 = 1.000, double y0 = -0.5, double width = 0.05, int Nmax = 150000){ // super extrim

  TRandom3* rnd = new TRandom3(1000);

  TH2D* hPFDV_XY_Map_Pipe_AbsZ25 = new TH2D("hPFDV_XY_Map_Pipe_AbsZ25", " Generated Circle; x (cm); y (cm)", 1000, -5, 5, 1000, -5, 5);
  hPFDV_XY_Map_Pipe_AbsZ25->Sumw2();
  TH2D* hPFDV_RhoPhi_Map_Pipe_AbsZ25 = new TH2D("hPFDV_RhoPhi_Map_Pipe_AbsZ25", " Generated Circle; #phi (rad); r (cm)", 400,  -TMath::Pi(), TMath::Pi(), 500, 0, 5);
  hPFDV_RhoPhi_Map_Pipe_AbsZ25->Sumw2();
  for (int i = 0; i < Nmax; i++){

    if (i%200000 == 0) cout << i << endl;
    double phi = rnd->Uniform()*2*TMath::Pi();
    double R = rnd->Gaus(R0, 0.01) + rnd->Uniform(-width/2, width/2);
    double x = R*cos(phi), y = R*sin(phi);
    double w = R0*R0/(R*R);
    hPFDV_XY_Map_Pipe_AbsZ25->Fill(x+x0, y+y0, w);

    //double pseudoPhi = atan((y+y0)/(x+x0));
    double pseudoPhi = atan2((y+y0),(x+x0));
    double pseudoR = sqrt((y+y0)*(y+y0)+(x+x0)*(x+x0));

    //if (x+x0 < 0) pseudoPhi += TMath::Pi();
    //if (x+x0>0 && y+y0<0) pseudoPhi += 2*TMath::Pi();

    hPFDV_RhoPhi_Map_Pipe_AbsZ25->Fill(pseudoPhi, pseudoR, w);
    

  }



  hPFDV_RhoPhi_Map_Pipe_AbsZ25->SetStats(0);
  hPFDV_RhoPhi_Map_Pipe_AbsZ25->Draw("COLZ");

  TFile* file_out = new TFile(Form("PseudoBeamPipe_r%.2fcm_x0%.2fcm_y0%.2fcm_w%.2fcm_Nevt%d.root", R0, x0, y0, width, Nmax), "RECREATE");
  hPFDV_XY_Map_Pipe_AbsZ25->Write();
  hPFDV_RhoPhi_Map_Pipe_AbsZ25->Write();
  file_out->Close();


}
