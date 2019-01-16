#ifndef Resolution_h
#define Resolution_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TVector3.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Resolution {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TChain* inputChain;

   // Declaration of leaf types
   Bool_t          isRealData;
   UInt_t          eventNumber;
   UInt_t          runNumber;
   UInt_t          lumiSection;
   UInt_t          numberOfPV;
   vector<double>  *PV_x;
   vector<double>  *PV_y;
   vector<double>  *PV_z;
   vector<double>  *PV_xError;
   vector<double>  *PV_yError;
   vector<double>  *PV_zError;
   vector<bool>    *PV_isFake;
   UInt_t          numberOfMC_PUInfo;
   vector<unsigned int> *MC_PUInfo_bunchCrossing;
   vector<unsigned int> *MC_PUInfo_numberOfInteractions;
   Double_t        BS_x;
   Double_t        BS_y;
   Double_t        BS_z;
   Double_t        BS_zSigma;
   Double_t        BS_dxdy;
   Double_t        BS_dydz;
   Double_t        BS_xWidth;
   Double_t        BS_yWidth;
   UInt_t          numberOfMC_TrkV;
   vector<bool>    *MC_TrkV_isNuclearInteraction;
   vector<bool>    *MC_TrkV_isKaonDecay;
   vector<bool>    *MC_TrkV_isConversion;
   vector<double>  *MC_TrkV_x;
   vector<double>  *MC_TrkV_y;
   vector<double>  *MC_TrkV_z;
   vector<double>  *MC_TrkV_momentumInc_pt;
   vector<double>  *MC_TrkV_Inc_charge;
   vector<int>     *MC_TrkV_Inc_pdgId;
   vector<double>  *MC_TrkV_momentumInc_phi;
   vector<double>  *MC_TrkV_momentumInc_theta;
   vector<double>  *MC_TrkV_momentumOut_pt;
   vector<double>  *MC_TrkV_momentumOut_phi;
   vector<double>  *MC_TrkV_momentumOut_theta;
   vector<double>  *MC_TrkV_momentumOut_mass;
   vector<unsigned int> *MC_TrkV_numberOfChargedParticles_0p2;
   vector<unsigned int> *MC_TrkV_numberOfChargedParticles_0p5;
   vector<unsigned int> *MC_TrkV_numberOfChargedParticles_1p0;
   vector<unsigned int> *MC_TrkV_numberOfChargedParticles_Out0p2;
   vector<unsigned int> *MC_TrkV_numberOfChargedParticles_Out0p5;
   vector<unsigned int> *MC_TrkV_numberOfChargedParticles_Out1p0;
   vector<bool>    *MC_TrkV_isAssociatedPF;
   vector<unsigned int> *MC_TrkV_associationPFDVIdx;
   vector<double>  *MC_TrkV_associationPFDV_deltaR2d;
   vector<double>  *MC_TrkV_associationPFDV_deltaR3d;
   vector<double>  *MC_TrkV_associationPFDV_deltaR3dPerpendicular;
   vector<double>  *MC_TrkV_associationPFDV_deltaR3dParallel;
   UInt_t          numberOfPFDV;
   vector<double>  *PFDV_x;
   vector<double>  *PFDV_y;
   vector<double>  *PFDV_z;
   vector<double>  *PFDV_momentumInc_pt;
   vector<double>  *PFDV_Inc_charge;
   vector<double>  *PFDV_momentumInc_phi;
   vector<double>  *PFDV_momentumInc_theta;
   vector<double>  *PFDV_momentumOut_pt;
   vector<double>  *PFDV_momentumOut_phi;
   vector<double>  *PFDV_momentumOut_theta;
   vector<double>  *PFDV_momentumOut_mass;
   vector<unsigned int> *PFDV_momentumOut_numberOfTracks;
   vector<unsigned int> *PFDV_numberOfTracks_0p0;
   vector<unsigned int> *PFDV_numberOfTracks_0p2;
   vector<unsigned int> *PFDV_numberOfTracks_0p5;
   vector<unsigned int> *PFDV_numberOfTracks_1p0;
   vector<unsigned int> *PFDV_numberOfTracks_Out0p0;
   vector<unsigned int> *PFDV_numberOfTracks_Out0p2;
   vector<unsigned int> *PFDV_numberOfTracks_Out0p5;
   vector<unsigned int> *PFDV_numberOfTracks_Out1p0;
   vector<bool>    *PFDV_isNuclear;
   vector<bool>    *PFDV_isNuclearLoose;
   vector<bool>    *PFDV_isNuclearKink;
   vector<bool>    *PFDV_isK0;
   vector<bool>    *PFDV_isLambda;
   vector<bool>    *PFDV_isLambdaBar;
   vector<bool>    *PFDV_isKPlusLoose;
   vector<bool>    *PFDV_isKMinusLoose;
   vector<bool>    *PFDV_isConversionLoose;
   vector<bool>    *PFDV_isLooper;
   vector<bool>    *PFDV_isFake;
   vector<bool>    *PFDV_isTherePrimaryTrack;
   vector<bool>    *PFDV_isThereMergedTrack;
   vector<bool>    *PFDV_isAssociatedMC;
   vector<double>  *PFDV_deltaR3d_Associated;
   vector<double>  *PFDV_deltaR2d_Associated;
   vector<unsigned int> *PFDV_associationMC_TrkVIdx;
   vector<vector<double> > *PFDV_vTrack_pt;
   vector<vector<double> > *PFDV_vTrack_eta;
   vector<vector<double> > *PFDV_vTrack_phi;
   vector<vector<double> > *PFDV_vTrack_rho;
   vector<vector<unsigned int> > *PFDV_vTrack_numberOfValidHits;
   vector<vector<unsigned int> > *PFDV_vTrack_numberOfExpectedOuterHits;
   vector<vector<unsigned int> > *PFDV_vTrack_closestDxyPVIdx;
   vector<vector<double> > *PFDV_vTrack_closestDxyPVIdx_dxy;
   vector<vector<double> > *PFDV_vTrack_closestDxyPVIdx_dz;
   vector<vector<unsigned int> > *PFDV_vTrack_closestDzPVIdx;
   vector<vector<double> > *PFDV_vTrack_closestDzPVIdx_dxy;
   vector<vector<double> > *PFDV_vTrack_closestDzPVIdx_dz;

   // List of branches
   TBranch        *b_isRealData;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_lumiSection;   //!
   TBranch        *b_numberOfPV;   //!
   TBranch        *b_PV_x;   //!
   TBranch        *b_PV_y;   //!
   TBranch        *b_PV_z;   //!
   TBranch        *b_PV_xError;   //!
   TBranch        *b_PV_yError;   //!
   TBranch        *b_PV_zError;   //!
   TBranch        *b_PV_isFake;   //!
   TBranch        *b_numberOfMC_PUInfo;   //!
   TBranch        *b_MC_PUInfo_bunchCrossing;   //!
   TBranch        *b_MC_PUInfo_numberOfInteractions;   //!
   TBranch        *b_BS_x;   //!
   TBranch        *b_BS_y;   //!
   TBranch        *b_BS_z;   //!
   TBranch        *b_BS_zSigma;   //!
   TBranch        *b_BS_dxdy;   //!
   TBranch        *b_BS_dydz;   //!
   TBranch        *b_BS_xWidth;   //!
   TBranch        *b_BS_yWidth;   //!
   TBranch        *b_numberOfMC_TrkV;   //!
   TBranch        *b_MC_TrkV_isNuclearInteraction;   //!
   TBranch        *b_MC_TrkV_isKaonDecay;   //!
   TBranch        *b_MC_TrkV_isConversion;   //!
   TBranch        *b_MC_TrkV_x;   //!
   TBranch        *b_MC_TrkV_y;   //!
   TBranch        *b_MC_TrkV_z;   //!
   TBranch        *b_MC_TrkV_momentumInc_pt;   //!
   TBranch        *b_MC_TrkV_Inc_charge;   //!
   TBranch        *b_MC_TrkV_Inc_pdgId;   //!
   TBranch        *b_MC_TrkV_momentumInc_phi;   //!
   TBranch        *b_MC_TrkV_momentumInc_theta;   //!
   TBranch        *b_MC_TrkV_momentumOut_pt;   //!
   TBranch        *b_MC_TrkV_momentumOut_phi;   //!
   TBranch        *b_MC_TrkV_momentumOut_theta;   //!
   TBranch        *b_MC_TrkV_momentumOut_mass;   //!
   TBranch        *b_MC_TrkV_numberOfChargedParticles_0p2;   //!
   TBranch        *b_MC_TrkV_numberOfChargedParticles_0p5;   //!
   TBranch        *b_MC_TrkV_numberOfChargedParticles_1p0;   //!
   TBranch        *b_MC_TrkV_numberOfChargedParticles_Out0p2;   //!
   TBranch        *b_MC_TrkV_numberOfChargedParticles_Out0p5;   //!
   TBranch        *b_MC_TrkV_numberOfChargedParticles_Out1p0;   //!
   TBranch        *b_MC_TrkV_isAssociatedPF;   //!
   TBranch        *b_MC_TrkV_associationPFDVIdx;   //!
   TBranch        *b_MC_TrkV_associationPFDV_deltaR2d;   //!
   TBranch        *b_MC_TrkV_associationPFDV_deltaR3d;   //!
   TBranch        *b_MC_TrkV_associationPFDV_deltaR3dPerpendicular;   //!
   TBranch        *b_MC_TrkV_associationPFDV_deltaR3dParallel;   //!
   TBranch        *b_numberOfPFDV;   //!
   TBranch        *b_PFDV_x;   //!
   TBranch        *b_PFDV_y;   //!
   TBranch        *b_PFDV_z;   //!
   TBranch        *b_PFDV_momentumInc_pt;   //!
   TBranch        *b_PFDV_Inc_charge;   //!
   TBranch        *b_PFDV_momentumInc_phi;   //!
   TBranch        *b_PFDV_momentumInc_theta;   //!
   TBranch        *b_PFDV_momentumOut_pt;   //!
   TBranch        *b_PFDV_momentumOut_phi;   //!
   TBranch        *b_PFDV_momentumOut_theta;   //!
   TBranch        *b_PFDV_momentumOut_mass;   //!
   TBranch        *b_PFDV_momentumOut_numberOfTracks;   //!
   TBranch        *b_PFDV_numberOfTracks_0p0;   //!
   TBranch        *b_PFDV_numberOfTracks_0p2;   //!
   TBranch        *b_PFDV_numberOfTracks_0p5;   //!
   TBranch        *b_PFDV_numberOfTracks_1p0;   //!
   TBranch        *b_PFDV_numberOfTracks_Out0p0;   //!
   TBranch        *b_PFDV_numberOfTracks_Out0p2;   //!
   TBranch        *b_PFDV_numberOfTracks_Out0p5;   //!
   TBranch        *b_PFDV_numberOfTracks_Out1p0;   //!
   TBranch        *b_PFDV_isNuclear;   //!
   TBranch        *b_PFDV_isNuclearLoose;   //!
   TBranch        *b_PFDV_isNuclearKink;   //!
   TBranch        *b_PFDV_isK0;   //!
   TBranch        *b_PFDV_isLambda;   //!
   TBranch        *b_PFDV_isLambdaBar;   //!
   TBranch        *b_PFDV_isKPlusLoose;   //!
   TBranch        *b_PFDV_isKMinusLoose;   //!
   TBranch        *b_PFDV_isConversionLoose;   //!
   TBranch        *b_PFDV_isLooper;   //!
   TBranch        *b_PFDV_isFake;   //!
   TBranch        *b_PFDV_isTherePrimaryTrack;   //!
   TBranch        *b_PFDV_isThereMergedTrack;   //!
   TBranch        *b_PFDV_isAssociatedMC;   //!
   TBranch        *b_PFDV_deltaR3d_Associated;   //!
   TBranch        *b_PFDV_deltaR2d_Associated;   //!
   TBranch        *b_PFDV_associationMC_TrkVIdx;   //!
   TBranch        *b_PFDV_vTrack_pt;   //!
   TBranch        *b_PFDV_vTrack_eta;   //!
   TBranch        *b_PFDV_vTrack_phi;   //!
   TBranch        *b_PFDV_vTrack_rho;   //!
   TBranch        *b_PFDV_vTrack_numberOfValidHits;   //!
   TBranch        *b_PFDV_vTrack_numberOfExpectedOuterHits;   //!
   TBranch        *b_PFDV_vTrack_closestDxyPVIdx;   //!
   TBranch        *b_PFDV_vTrack_closestDxyPVIdx_dxy;   //!
   TBranch        *b_PFDV_vTrack_closestDxyPVIdx_dz;   //!
   TBranch        *b_PFDV_vTrack_closestDzPVIdx;   //!
   TBranch        *b_PFDV_vTrack_closestDzPVIdx_dxy;   //!
   TBranch        *b_PFDV_vTrack_closestDzPVIdx_dz;   //!

   Resolution(TTree *tree=0, TString FileNameRoot="");
   virtual ~Resolution();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(const char* filename, double dR_xfactor, double dR_binfactor);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};
#endif

#define Resolution_cxx
inline Resolution::Resolution(TTree *tree, TString FileNameRoot) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/dpg_tracker_strip/tracker/MaterialBudget/NI/reReco2015D/reReco2015D_SingleMu.root");
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(FileNameRoot);
      if (!f || !f->IsOpen()) {
         f = new TFile(FileNameRoot);
      }
      TDirectory * dir = (TDirectory*)f->Get(FileNameRoot+":/MyNtupleMaking");
      /*TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("../Ntuple_MC_923.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("../Ntuple_MC_923.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("../Ntuple_MC_923.root:/MyNtupleMaking");
      */dir->GetObject("NuclearInteractionsTree",tree);

   }
   Init(tree);
}

inline Resolution::~Resolution()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

inline Int_t Resolution::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

inline Long64_t Resolution::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

inline void Resolution::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   PV_x = 0;
   PV_y = 0;
   PV_z = 0;
   PV_xError = 0;
   PV_yError = 0;
   PV_zError = 0;
   PV_isFake = 0;
   MC_PUInfo_bunchCrossing = 0;
   MC_PUInfo_numberOfInteractions = 0;
   MC_TrkV_isNuclearInteraction = 0;
   MC_TrkV_isKaonDecay = 0;
   MC_TrkV_isConversion = 0;
   MC_TrkV_x = 0;
   MC_TrkV_y = 0;
   MC_TrkV_z = 0;
   MC_TrkV_momentumInc_pt = 0;
   MC_TrkV_Inc_charge = 0;
   MC_TrkV_Inc_pdgId = 0;
   MC_TrkV_momentumInc_phi = 0;
   MC_TrkV_momentumInc_theta = 0;
   MC_TrkV_momentumOut_pt = 0;
   MC_TrkV_momentumOut_phi = 0;
   MC_TrkV_momentumOut_theta = 0;
   MC_TrkV_momentumOut_mass = 0;
   MC_TrkV_numberOfChargedParticles_0p2 = 0;
   MC_TrkV_numberOfChargedParticles_0p5 = 0;
   MC_TrkV_numberOfChargedParticles_1p0 = 0;
   MC_TrkV_numberOfChargedParticles_Out0p2 = 0;
   MC_TrkV_numberOfChargedParticles_Out0p5 = 0;
   MC_TrkV_numberOfChargedParticles_Out1p0 = 0;
   MC_TrkV_isAssociatedPF = 0;
   MC_TrkV_associationPFDVIdx = 0;
   MC_TrkV_associationPFDV_deltaR2d = 0;
   MC_TrkV_associationPFDV_deltaR3d = 0;
   MC_TrkV_associationPFDV_deltaR3dPerpendicular = 0;
   MC_TrkV_associationPFDV_deltaR3dParallel = 0;
   PFDV_x = 0;
   PFDV_y = 0;
   PFDV_z = 0;
   PFDV_momentumInc_pt = 0;
   PFDV_Inc_charge = 0;
   PFDV_momentumInc_phi = 0;
   PFDV_momentumInc_theta = 0;
   PFDV_momentumOut_pt = 0;
   PFDV_momentumOut_phi = 0;
   PFDV_momentumOut_theta = 0;
   PFDV_momentumOut_mass = 0;
   PFDV_momentumOut_numberOfTracks = 0;
   PFDV_numberOfTracks_0p0 = 0;
   PFDV_numberOfTracks_0p2 = 0;
   PFDV_numberOfTracks_0p5 = 0;
   PFDV_numberOfTracks_1p0 = 0;
   PFDV_numberOfTracks_Out0p0 = 0;
   PFDV_numberOfTracks_Out0p2 = 0;
   PFDV_numberOfTracks_Out0p5 = 0;
   PFDV_numberOfTracks_Out1p0 = 0;
   PFDV_isNuclear = 0;
   PFDV_isNuclearLoose = 0;
   PFDV_isNuclearKink = 0;
   PFDV_isK0 = 0;
   PFDV_isLambda = 0;
   PFDV_isLambdaBar = 0;
   PFDV_isKPlusLoose = 0;
   PFDV_isKMinusLoose = 0;
   PFDV_isConversionLoose = 0;
   PFDV_isLooper = 0;
   PFDV_isFake = 0;
   PFDV_isTherePrimaryTrack = 0;
   PFDV_isThereMergedTrack = 0;
   PFDV_isAssociatedMC = 0;
   PFDV_deltaR3d_Associated = 0;
   PFDV_deltaR2d_Associated = 0;
   PFDV_associationMC_TrkVIdx = 0;
   PFDV_vTrack_pt = 0;
   PFDV_vTrack_eta = 0;
   PFDV_vTrack_phi = 0;
   PFDV_vTrack_rho = 0;
   PFDV_vTrack_numberOfValidHits = 0;
   PFDV_vTrack_numberOfExpectedOuterHits = 0;
   PFDV_vTrack_closestDxyPVIdx = 0;
   PFDV_vTrack_closestDxyPVIdx_dxy = 0;
   PFDV_vTrack_closestDxyPVIdx_dz = 0;
   PFDV_vTrack_closestDzPVIdx = 0;
   PFDV_vTrack_closestDzPVIdx_dxy = 0;
   PFDV_vTrack_closestDzPVIdx_dz = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("isRealData", &isRealData, &b_isRealData);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("lumiSection", &lumiSection, &b_lumiSection);
   fChain->SetBranchAddress("numberOfPV", &numberOfPV, &b_numberOfPV);
   fChain->SetBranchAddress("PV_x", &PV_x, &b_PV_x);
   fChain->SetBranchAddress("PV_y", &PV_y, &b_PV_y);
   fChain->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
   fChain->SetBranchAddress("PV_xError", &PV_xError, &b_PV_xError);
   fChain->SetBranchAddress("PV_yError", &PV_yError, &b_PV_yError);
   fChain->SetBranchAddress("PV_zError", &PV_zError, &b_PV_zError);
   fChain->SetBranchAddress("PV_isFake", &PV_isFake, &b_PV_isFake);
   fChain->SetBranchAddress("numberOfMC_PUInfo", &numberOfMC_PUInfo, &b_numberOfMC_PUInfo);
   fChain->SetBranchAddress("MC_PUInfo_bunchCrossing", &MC_PUInfo_bunchCrossing, &b_MC_PUInfo_bunchCrossing);
   fChain->SetBranchAddress("MC_PUInfo_numberOfInteractions", &MC_PUInfo_numberOfInteractions, &b_MC_PUInfo_numberOfInteractions);
   fChain->SetBranchAddress("BS_x", &BS_x, &b_BS_x);
   fChain->SetBranchAddress("BS_y", &BS_y, &b_BS_y);
   fChain->SetBranchAddress("BS_z", &BS_z, &b_BS_z);
   fChain->SetBranchAddress("BS_zSigma", &BS_zSigma, &b_BS_zSigma);
   fChain->SetBranchAddress("BS_dxdy", &BS_dxdy, &b_BS_dxdy);
   fChain->SetBranchAddress("BS_dydz", &BS_dydz, &b_BS_dydz);
   fChain->SetBranchAddress("BS_xWidth", &BS_xWidth, &b_BS_xWidth);
   fChain->SetBranchAddress("BS_yWidth", &BS_yWidth, &b_BS_yWidth);
   fChain->SetBranchAddress("numberOfMC_TrkV", &numberOfMC_TrkV, &b_numberOfMC_TrkV);
   fChain->SetBranchAddress("MC_TrkV_isNuclearInteraction", &MC_TrkV_isNuclearInteraction, &b_MC_TrkV_isNuclearInteraction);
   fChain->SetBranchAddress("MC_TrkV_isKaonDecay", &MC_TrkV_isKaonDecay, &b_MC_TrkV_isKaonDecay);
   fChain->SetBranchAddress("MC_TrkV_isConversion", &MC_TrkV_isConversion, &b_MC_TrkV_isConversion);
   fChain->SetBranchAddress("MC_TrkV_x", &MC_TrkV_x, &b_MC_TrkV_x);
   fChain->SetBranchAddress("MC_TrkV_y", &MC_TrkV_y, &b_MC_TrkV_y);
   fChain->SetBranchAddress("MC_TrkV_z", &MC_TrkV_z, &b_MC_TrkV_z);
   fChain->SetBranchAddress("MC_TrkV_momentumInc_pt", &MC_TrkV_momentumInc_pt, &b_MC_TrkV_momentumInc_pt);
   fChain->SetBranchAddress("MC_TrkV_Inc_charge", &MC_TrkV_Inc_charge, &b_MC_TrkV_Inc_charge);
   fChain->SetBranchAddress("MC_TrkV_Inc_pdgId", &MC_TrkV_Inc_pdgId, &b_MC_TrkV_Inc_pdgId);
   fChain->SetBranchAddress("MC_TrkV_momentumInc_phi", &MC_TrkV_momentumInc_phi, &b_MC_TrkV_momentumInc_phi);
   fChain->SetBranchAddress("MC_TrkV_momentumInc_theta", &MC_TrkV_momentumInc_theta, &b_MC_TrkV_momentumInc_theta);
   fChain->SetBranchAddress("MC_TrkV_momentumOut_pt", &MC_TrkV_momentumOut_pt, &b_MC_TrkV_momentumOut_pt);
   fChain->SetBranchAddress("MC_TrkV_momentumOut_phi", &MC_TrkV_momentumOut_phi, &b_MC_TrkV_momentumOut_phi);
   fChain->SetBranchAddress("MC_TrkV_momentumOut_theta", &MC_TrkV_momentumOut_theta, &b_MC_TrkV_momentumOut_theta);
   fChain->SetBranchAddress("MC_TrkV_momentumOut_mass", &MC_TrkV_momentumOut_mass, &b_MC_TrkV_momentumOut_mass);
   fChain->SetBranchAddress("MC_TrkV_numberOfChargedParticles_0p2", &MC_TrkV_numberOfChargedParticles_0p2, &b_MC_TrkV_numberOfChargedParticles_0p2);
   fChain->SetBranchAddress("MC_TrkV_numberOfChargedParticles_0p5", &MC_TrkV_numberOfChargedParticles_0p5, &b_MC_TrkV_numberOfChargedParticles_0p5);
   fChain->SetBranchAddress("MC_TrkV_numberOfChargedParticles_1p0", &MC_TrkV_numberOfChargedParticles_1p0, &b_MC_TrkV_numberOfChargedParticles_1p0);
   fChain->SetBranchAddress("MC_TrkV_numberOfChargedParticles_Out0p2", &MC_TrkV_numberOfChargedParticles_Out0p2, &b_MC_TrkV_numberOfChargedParticles_Out0p2);
   fChain->SetBranchAddress("MC_TrkV_numberOfChargedParticles_Out0p5", &MC_TrkV_numberOfChargedParticles_Out0p5, &b_MC_TrkV_numberOfChargedParticles_Out0p5);
   fChain->SetBranchAddress("MC_TrkV_numberOfChargedParticles_Out1p0", &MC_TrkV_numberOfChargedParticles_Out1p0, &b_MC_TrkV_numberOfChargedParticles_Out1p0);
   fChain->SetBranchAddress("MC_TrkV_isAssociatedPF", &MC_TrkV_isAssociatedPF, &b_MC_TrkV_isAssociatedPF);
   fChain->SetBranchAddress("MC_TrkV_associationPFDVIdx", &MC_TrkV_associationPFDVIdx, &b_MC_TrkV_associationPFDVIdx);
   fChain->SetBranchAddress("MC_TrkV_associationPFDV_deltaR2d", &MC_TrkV_associationPFDV_deltaR2d, &b_MC_TrkV_associationPFDV_deltaR2d);
   fChain->SetBranchAddress("MC_TrkV_associationPFDV_deltaR3d", &MC_TrkV_associationPFDV_deltaR3d, &b_MC_TrkV_associationPFDV_deltaR3d);
   fChain->SetBranchAddress("MC_TrkV_associationPFDV_deltaR3dPerpendicular", &MC_TrkV_associationPFDV_deltaR3dPerpendicular, &b_MC_TrkV_associationPFDV_deltaR3dPerpendicular);
   fChain->SetBranchAddress("MC_TrkV_associationPFDV_deltaR3dParallel", &MC_TrkV_associationPFDV_deltaR3dParallel, &b_MC_TrkV_associationPFDV_deltaR3dParallel);
   fChain->SetBranchAddress("numberOfPFDV", &numberOfPFDV, &b_numberOfPFDV);
   fChain->SetBranchAddress("PFDV_x", &PFDV_x, &b_PFDV_x);
   fChain->SetBranchAddress("PFDV_y", &PFDV_y, &b_PFDV_y);
   fChain->SetBranchAddress("PFDV_z", &PFDV_z, &b_PFDV_z);
   fChain->SetBranchAddress("PFDV_momentumInc_pt", &PFDV_momentumInc_pt, &b_PFDV_momentumInc_pt);
   fChain->SetBranchAddress("PFDV_Inc_charge", &PFDV_Inc_charge, &b_PFDV_Inc_charge);
   fChain->SetBranchAddress("PFDV_momentumInc_phi", &PFDV_momentumInc_phi, &b_PFDV_momentumInc_phi);
   fChain->SetBranchAddress("PFDV_momentumInc_theta", &PFDV_momentumInc_theta, &b_PFDV_momentumInc_theta);
   fChain->SetBranchAddress("PFDV_momentumOut_pt", &PFDV_momentumOut_pt, &b_PFDV_momentumOut_pt);
   fChain->SetBranchAddress("PFDV_momentumOut_phi", &PFDV_momentumOut_phi, &b_PFDV_momentumOut_phi);
   fChain->SetBranchAddress("PFDV_momentumOut_theta", &PFDV_momentumOut_theta, &b_PFDV_momentumOut_theta);
   fChain->SetBranchAddress("PFDV_momentumOut_mass", &PFDV_momentumOut_mass, &b_PFDV_momentumOut_mass);
   fChain->SetBranchAddress("PFDV_momentumOut_numberOfTracks", &PFDV_momentumOut_numberOfTracks, &b_PFDV_momentumOut_numberOfTracks);
   fChain->SetBranchAddress("PFDV_numberOfTracks_0p0", &PFDV_numberOfTracks_0p0, &b_PFDV_numberOfTracks_0p0);
   fChain->SetBranchAddress("PFDV_numberOfTracks_0p2", &PFDV_numberOfTracks_0p2, &b_PFDV_numberOfTracks_0p2);
   fChain->SetBranchAddress("PFDV_numberOfTracks_0p5", &PFDV_numberOfTracks_0p5, &b_PFDV_numberOfTracks_0p5);
   fChain->SetBranchAddress("PFDV_numberOfTracks_1p0", &PFDV_numberOfTracks_1p0, &b_PFDV_numberOfTracks_1p0);
   fChain->SetBranchAddress("PFDV_numberOfTracks_Out0p0", &PFDV_numberOfTracks_Out0p0, &b_PFDV_numberOfTracks_Out0p0);
   fChain->SetBranchAddress("PFDV_numberOfTracks_Out0p2", &PFDV_numberOfTracks_Out0p2, &b_PFDV_numberOfTracks_Out0p2);
   fChain->SetBranchAddress("PFDV_numberOfTracks_Out0p5", &PFDV_numberOfTracks_Out0p5, &b_PFDV_numberOfTracks_Out0p5);
   fChain->SetBranchAddress("PFDV_numberOfTracks_Out1p0", &PFDV_numberOfTracks_Out1p0, &b_PFDV_numberOfTracks_Out1p0);
   fChain->SetBranchAddress("PFDV_isNuclear", &PFDV_isNuclear, &b_PFDV_isNuclear);
   fChain->SetBranchAddress("PFDV_isNuclearLoose", &PFDV_isNuclearLoose, &b_PFDV_isNuclearLoose);
   fChain->SetBranchAddress("PFDV_isNuclearKink", &PFDV_isNuclearKink, &b_PFDV_isNuclearKink);
   fChain->SetBranchAddress("PFDV_isK0", &PFDV_isK0, &b_PFDV_isK0);
   fChain->SetBranchAddress("PFDV_isLambda", &PFDV_isLambda, &b_PFDV_isLambda);
   fChain->SetBranchAddress("PFDV_isLambdaBar", &PFDV_isLambdaBar, &b_PFDV_isLambdaBar);
   fChain->SetBranchAddress("PFDV_isKPlusLoose", &PFDV_isKPlusLoose, &b_PFDV_isKPlusLoose);
   fChain->SetBranchAddress("PFDV_isKMinusLoose", &PFDV_isKMinusLoose, &b_PFDV_isKMinusLoose);
   fChain->SetBranchAddress("PFDV_isConversionLoose", &PFDV_isConversionLoose, &b_PFDV_isConversionLoose);
   fChain->SetBranchAddress("PFDV_isLooper", &PFDV_isLooper, &b_PFDV_isLooper);
   fChain->SetBranchAddress("PFDV_isFake", &PFDV_isFake, &b_PFDV_isFake);
   fChain->SetBranchAddress("PFDV_isTherePrimaryTrack", &PFDV_isTherePrimaryTrack, &b_PFDV_isTherePrimaryTrack);
   fChain->SetBranchAddress("PFDV_isThereMergedTrack", &PFDV_isThereMergedTrack, &b_PFDV_isThereMergedTrack);
   fChain->SetBranchAddress("PFDV_isAssociatedMC", &PFDV_isAssociatedMC, &b_PFDV_isAssociatedMC);
   fChain->SetBranchAddress("PFDV_deltaR3d_Associated", &PFDV_deltaR3d_Associated, &b_PFDV_deltaR3d_Associated);
   fChain->SetBranchAddress("PFDV_deltaR2d_Associated", &PFDV_deltaR2d_Associated, &b_PFDV_deltaR2d_Associated);
   fChain->SetBranchAddress("PFDV_associationMC_TrkVIdx", &PFDV_associationMC_TrkVIdx, &b_PFDV_associationMC_TrkVIdx);
   fChain->SetBranchAddress("PFDV_vTrack_pt", &PFDV_vTrack_pt, &b_PFDV_vTrack_pt);
   fChain->SetBranchAddress("PFDV_vTrack_eta", &PFDV_vTrack_eta, &b_PFDV_vTrack_eta);
   fChain->SetBranchAddress("PFDV_vTrack_phi", &PFDV_vTrack_phi, &b_PFDV_vTrack_phi);
   fChain->SetBranchAddress("PFDV_vTrack_rho", &PFDV_vTrack_rho, &b_PFDV_vTrack_rho);
   fChain->SetBranchAddress("PFDV_vTrack_numberOfValidHits", &PFDV_vTrack_numberOfValidHits, &b_PFDV_vTrack_numberOfValidHits);
   fChain->SetBranchAddress("PFDV_vTrack_numberOfExpectedOuterHits", &PFDV_vTrack_numberOfExpectedOuterHits, &b_PFDV_vTrack_numberOfExpectedOuterHits);
   fChain->SetBranchAddress("PFDV_vTrack_closestDxyPVIdx", &PFDV_vTrack_closestDxyPVIdx, &b_PFDV_vTrack_closestDxyPVIdx);
   fChain->SetBranchAddress("PFDV_vTrack_closestDxyPVIdx_dxy", &PFDV_vTrack_closestDxyPVIdx_dxy, &b_PFDV_vTrack_closestDxyPVIdx_dxy);
   fChain->SetBranchAddress("PFDV_vTrack_closestDxyPVIdx_dz", &PFDV_vTrack_closestDxyPVIdx_dz, &b_PFDV_vTrack_closestDxyPVIdx_dz);
   fChain->SetBranchAddress("PFDV_vTrack_closestDzPVIdx", &PFDV_vTrack_closestDzPVIdx, &b_PFDV_vTrack_closestDzPVIdx);
   fChain->SetBranchAddress("PFDV_vTrack_closestDzPVIdx_dxy", &PFDV_vTrack_closestDzPVIdx_dxy, &b_PFDV_vTrack_closestDzPVIdx_dxy);
   fChain->SetBranchAddress("PFDV_vTrack_closestDzPVIdx_dz", &PFDV_vTrack_closestDzPVIdx_dz, &b_PFDV_vTrack_closestDzPVIdx_dz);
   Notify();
}

inline Bool_t Resolution::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

inline void Resolution::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
inline Int_t Resolution::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

inline void Resolution::Loop(const char* filename, double dR_xfactor, double dR_binfactor)
{
  if (fChain == 0) return;
  Float_t dR_xmin = 0.;
  Float_t dR_xmax = 1.0;
  Int_t  dR_Nbin = 50*dR_binfactor;
   TFile* outputFile = new TFile(filename, "RECREATE");

   //initialize histograms 
   TH1D* hMC_deltaR3d;
   TH1D* hMC_deltaR3d_Parallel;
   TH1D* hMC_deltaR3d_Perpendicular;
   TH1D* hMC_deltaR3d_EndCap;
   TH1D* hMC_deltaR3d_Parallel_EndCap;
   TH1D* hMC_deltaR3d_Perpendicular_EndCap;
   TH1D* hMC_deltaR3d_Barrel;
   TH1D* hMC_deltaR3d_Parallel_Barrel;
   TH1D* hMC_deltaR3d_Perpendicular_Barrel;
   TH1D* hMC_deltaR3d_Inner;
   TH1D* hMC_deltaR3d_Parallel_Inner;
   TH1D* hMC_deltaR3d_Perpendicular_Inner;
   TH1D* hMC_deltaR3d_Inner_EndCap;
   TH1D* hMC_deltaR3d_Parallel_Inner_EndCap;
   TH1D* hMC_deltaR3d_Perpendicular_Inner_EndCap;
   TH1D* hMC_deltaR3d_Inner_Barrel;
   TH1D* hMC_deltaR3d_Parallel_Inner_Barrel;
   TH1D* hMC_deltaR3d_Perpendicular_Inner_Barrel;
   TH1D* hMC_deltaR3d_Outer;
   TH1D* hMC_deltaR3d_Parallel_Outer;
   TH1D* hMC_deltaR3d_Perpendicular_Outer;
   TH1D* hMC_deltaR3d_Outer_EndCap;
   TH1D* hMC_deltaR3d_Parallel_Outer_EndCap;
   TH1D* hMC_deltaR3d_Perpendicular_Outer_EndCap;
   TH1D* hMC_deltaR3d_Outer_Barrel;
   TH1D* hMC_deltaR3d_Parallel_Outer_Barrel;
   TH1D* hMC_deltaR3d_Perpendicular_Outer_Barrel;

   //create histograms
   hMC_deltaR3d = new TH1D("hMC_deltaR3d", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d->Sumw2();
   hMC_deltaR3d_Parallel = new TH1D("hMC_deltaR3d_Parallel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel->Sumw2();
   hMC_deltaR3d_Perpendicular = new TH1D("hMC_deltaR3d_Perpendicular", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular->Sumw2();
   hMC_deltaR3d_EndCap = new TH1D("hMC_deltaR3d_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_EndCap->Sumw2();
   hMC_deltaR3d_Parallel_EndCap = new TH1D("hMC_deltaR3d_Parallel_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_EndCap->Sumw2();
   hMC_deltaR3d_Perpendicular_EndCap = new TH1D("hMC_deltaR3d_Perpendicular_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_EndCap->Sumw2();
   hMC_deltaR3d_Barrel = new TH1D("hMC_deltaR3d_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Barrel->Sumw2();
   hMC_deltaR3d_Parallel_Barrel = new TH1D("hMC_deltaR3d_Parallel_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Barrel->Sumw2();
   hMC_deltaR3d_Perpendicular_Barrel = new TH1D("hMC_deltaR3d_Perpendicular_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Barrel->Sumw2();
   hMC_deltaR3d_Outer = new TH1D("hMC_deltaR3d_Outer", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Outer->Sumw2();
   hMC_deltaR3d_Parallel_Outer = new TH1D("hMC_deltaR3d_Parallel_Outer", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Outer->Sumw2();
   hMC_deltaR3d_Perpendicular_Outer = new TH1D("hMC_deltaR3d_Perpendicular_Outer", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Outer->Sumw2();
   hMC_deltaR3d_Outer_EndCap = new TH1D("hMC_deltaR3d_Outer_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Outer_EndCap->Sumw2();
   hMC_deltaR3d_Parallel_Outer_EndCap = new TH1D("hMC_deltaR3d_Parallel_Outer_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Outer_EndCap->Sumw2();
   hMC_deltaR3d_Perpendicular_Outer_EndCap = new TH1D("hMC_deltaR3d_Perpendicular_Outer_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Outer_EndCap->Sumw2();
   hMC_deltaR3d_Outer_Barrel = new TH1D("hMC_deltaR3d_Outer_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Outer_Barrel->Sumw2();
   hMC_deltaR3d_Parallel_Outer_Barrel = new TH1D("hMC_deltaR3d_Parallel_Outer_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Outer_Barrel->Sumw2();
   hMC_deltaR3d_Perpendicular_Outer_Barrel = new TH1D("hMC_deltaR3d_Perpendicular_Outer_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Outer_Barrel->Sumw2();
   hMC_deltaR3d_Inner = new TH1D("hMC_deltaR3d_Inner", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xfactor*dR_xmax);
   hMC_deltaR3d_Inner->Sumw2();
   hMC_deltaR3d_Parallel_Inner = new TH1D("hMC_deltaR3d_Parallel_Inner", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xfactor*dR_xmax);
   hMC_deltaR3d_Parallel_Inner->Sumw2();
   hMC_deltaR3d_Perpendicular_Inner = new TH1D("hMC_deltaR3d_Perpendicular_Inner", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xfactor*dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Inner->Sumw2();
   hMC_deltaR3d_Inner_EndCap = new TH1D("hMC_deltaR3d_Inner_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Inner_EndCap->Sumw2();
   hMC_deltaR3d_Parallel_Inner_EndCap = new TH1D("hMC_deltaR3d_Parallel_Inner_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax);
   hMC_deltaR3d_Parallel_Inner_EndCap->Sumw2();
   hMC_deltaR3d_Perpendicular_Inner_EndCap = new TH1D("hMC_deltaR3d_Perpendicular_Inner_EndCap", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Inner_EndCap->Sumw2();
   hMC_deltaR3d_Inner_Barrel = new TH1D("hMC_deltaR3d_Inner_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xfactor*dR_xmax);
   hMC_deltaR3d_Inner_Barrel->Sumw2();
   hMC_deltaR3d_Parallel_Inner_Barrel = new TH1D("hMC_deltaR3d_Parallel_Inner_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xfactor*dR_xmax);
   hMC_deltaR3d_Parallel_Inner_Barrel->Sumw2();
   hMC_deltaR3d_Perpendicular_Inner_Barrel = new TH1D("hMC_deltaR3d_Perpendicular_Inner_Barrel", "CMS work in Progress", dR_Nbin, dR_xmin, dR_xfactor*dR_xmax/10.0);
   hMC_deltaR3d_Perpendicular_Inner_Barrel->Sumw2();

   Long64_t nentries = fChain->GetEntriesFast();

   double ni_MC_x, ni_MC_y, ni_MC_z, ni_MC_rho;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
       if (Cut(ientry) < 0) continue;
      //Get Branch addresses for cuts
      b_MC_TrkV_numberOfChargedParticles_0p2->GetEntry(ientry);
      b_MC_TrkV_momentumOut_pt->GetEntry(ientry);
      // print how many events are done:
      //if( jentry%100000 == 0 )
           //std::cout << "Loop over entry " << jentry << "/" << nentries << "." << std::endl;
      int NumberNI=0;
      for ( int i = 0; i < numberOfMC_TrkV; i++ )
      {
       //get values of x, y, and z of MC tracks
       ni_MC_x = MC_TrkV_x->at(i);
       ni_MC_y = MC_TrkV_y->at(i);
       ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );
       //default cuts
       //if (MC_TrkV_numberOfChargedParticles_0p2->at(i) < 3 ) continue;
       if (MC_TrkV_momentumOut_pt->at(i) < 0.5 ) continue;
       if (ni_MC_rho < 1.7) continue;
       if (ni_MC_rho > 65) continue;
       NumberNI++;
      }
         if ( (NumberNI != 1) || numberOfPFDV != 1) continue;
      
      for ( int j = 0; j < numberOfMC_TrkV; j++ )
      {
         ni_MC_x = MC_TrkV_x->at(j);
         ni_MC_y = MC_TrkV_y->at(j);
         ni_MC_z = MC_TrkV_z->at(j);
         ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );
         double DeltaR3d_Min_Val=1000.;
         double DeltaR3dParallel_Min_Val=0.0;
         double DeltaR3dPerpendicular_Min_Val=0.0;
          //default cuts
          if (ni_MC_rho < 1.7) continue;
	  //if (MC_TrkV_numberOfChargedParticles_0p2->at(j) < 3 ) continue;
          if (MC_TrkV_momentumOut_pt->at(j) < 0.5 ) continue;
          if (ni_MC_rho > 22) continue;
          //find the minimum deltaR
          if(DeltaR3d_Min_Val>(MC_TrkV_associationPFDV_deltaR3d->at(j)))
           {
	    DeltaR3d_Min_Val=(MC_TrkV_associationPFDV_deltaR3d->at(j));
            DeltaR3dParallel_Min_Val=(MC_TrkV_associationPFDV_deltaR3dParallel->at(j));
            DeltaR3dPerpendicular_Min_Val=(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(j));
           }
   	  //fill histograms based on each region
          hMC_deltaR3d->Fill(DeltaR3d_Min_Val);
          hMC_deltaR3d_Parallel->Fill(DeltaR3dParallel_Min_Val);
          hMC_deltaR3d_Perpendicular->Fill(DeltaR3dPerpendicular_Min_Val);
          if(ni_MC_z > 25)
          {
           hMC_deltaR3d_EndCap->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_EndCap->Fill(DeltaR3dParallel_Min_Val);
           hMC_deltaR3d_Perpendicular_EndCap->Fill(DeltaR3dPerpendicular_Min_Val);
          }
          if(ni_MC_z < 25)
	  {
	   hMC_deltaR3d_Barrel->Fill(DeltaR3d_Min_Val);
 	   hMC_deltaR3d_Parallel_Barrel->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Barrel->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho > 19)
  	  {
	   hMC_deltaR3d_Outer->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Outer->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Outer->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho > 19 && ni_MC_z > 25)
	  {
	   hMC_deltaR3d_Outer_EndCap->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Outer_EndCap->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Outer_EndCap->Fill(DeltaR3dPerpendicular_Min_Val);
 	  }
	  if(ni_MC_rho > 19 && ni_MC_z < 25)
	  {
	   hMC_deltaR3d_Outer_Barrel->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Outer_Barrel->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Outer_Barrel->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho < 5)
	  {
	   hMC_deltaR3d_Inner->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Inner->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Inner->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho < 5 && ni_MC_z > 25)
	  {
	   hMC_deltaR3d_Inner_EndCap->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Inner_EndCap->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Inner_EndCap->Fill(DeltaR3dPerpendicular_Min_Val);
	  }
	  if(ni_MC_rho < 5 && ni_MC_z < 25)
	  {
	   hMC_deltaR3d_Inner_Barrel->Fill(DeltaR3d_Min_Val);
	   hMC_deltaR3d_Parallel_Inner_Barrel->Fill(DeltaR3dParallel_Min_Val);
	   hMC_deltaR3d_Perpendicular_Inner_Barrel->Fill(DeltaR3dPerpendicular_Min_Val);
 	  }
       }
   } 
   outputFile->Write();
   outputFile->Close();
   delete outputFile;
}
