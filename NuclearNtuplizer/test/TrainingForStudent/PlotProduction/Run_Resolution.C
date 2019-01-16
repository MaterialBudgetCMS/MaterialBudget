#include "Resolution.hh"
#include "Resolution_Fit_NEW.C"

void Run_Resolution()
{
 Long64_t start = gSystem->Now();
 TString FileNameRoot1 = "/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/PionGun2018/CMSSW_10_1_6_Pion10GeV_Ntuple/MC_Pi10GeV_1016.root"; 
 TString FileNameRoot2 = "../../../../../../../../../Ntuple_Pi50GeV_1016.root";
 TString FileNameRoot3 = "../../../../../../../../../Ntuple_Pi100GeV_1016.root";
 TString FileNameRoot4 = "../../Ntuple_MC_10and100GeVpions.root";
 

 double val = 0.5;
 Resolution m1(0,FileNameRoot1); 
 m1.GetEntry(0);
 m1.Loop("ResolutionPlots_10GeV_2018.root",0.15,1.0);

 Resolution m2(0,FileNameRoot2);
 m2.GetEntry(0);
 m2.Loop("ResolutionPlots_50GeV_2018.root",0.15,1.0);
 
 Resolution m3(0,FileNameRoot3);
 m3.GetEntry(0);
 m3.Loop("ResolutionPlots_100GeV_2018.root",0.15,0.5);

 Resolution m4(0,FileNameRoot4);
 m4.GetEntry(0);
 m4.Loop("ResolutionPlots_2015_REPRO.root",0.15,0.5);
  
 /*
 double val = 0.63;
//for(int i = 0; i < 50; i++)
//{
 
 Resolution m1(0,FileNameRoot1); 
 m1.GetEntry(0);
 m1.Loop("ResolutionPlots_10GeV_2018.root",0.15,1.25);
 //m1.Loop("ResolutionPlots_10GeV_2018.root",0.15,0.67);

 Resolution m2(0,FileNameRoot2);
 m2.GetEntry(0);
 m2.Loop("ResolutionPlots_50GeV_2018.root",0.15,1.25);
 //m2.Loop("ResolutionPlots_50GeV_2018.root",0.15,0.67);
 
 Resolution m3(0,FileNameRoot3);
 m3.GetEntry(0);
 m3.Loop("ResolutionPlots_100GeV_2018.root",0.15,val);
 //m3.Loop("ResolutionPlots_100GeV_2018.root",0.15,0.75);

 Resolution m4(0,FileNameRoot4);
 m4.GetEntry(0);
 m4.Loop("ResolutionPlots_2015_REPRO.root",0.15,val);
 //m4.Loop("ResolutionPlots_2015_REPRO.root",0.15,0.75);
 
 //To Run Fitter:
 //Resolution_Fit_NEW();

 cout << "Bins: " << val*40 << ", Successful: " << Resolution_Fit_NEW() << endl; 
 //val = val-0.02;
//}
 */
 //cout << "Bins: " << val*50 << ", Successful: " << Resolution_Fit_NEW() << endl; 
 Resolution_Fit_NEW();
 Long64_t end = gSystem->Now();
 cout << "Time to process = " << (end-start)/1000.0 << " seconds" << endl;
}
