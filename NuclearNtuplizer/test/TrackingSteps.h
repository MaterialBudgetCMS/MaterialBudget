//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jun 21 17:25:44 2010 by ROOT version 5.20/00
// from TTree TrackingSteps/reco2sim
// found on file: ntuple_nuclint_CMSSW358p3_goodcoll7TeV_2010-06-04.root
//////////////////////////////////////////////////////////

#ifndef TrackingSteps_h
#define TrackingSteps_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

class TrackingSteps {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Int_t           event;
   Int_t           isAssoc;
   Char_t          isNuclSim;
   Char_t          isKSim;
   Float_t         pt;
   Float_t         phi;
   Float_t         theta;
   Float_t         ptOut;
   Float_t         phiOut;
   Float_t         thetaOut;
   Float_t         mOut;
   Float_t         mK;
   Float_t         angle;
   Int_t           nOut;
   Int_t           nOutTkStep67Good;
   Int_t           nOutTkStep67Poor;
   Float_t         x;
   Float_t         y;
   Float_t         z;
   Float_t         deltapt;
   Float_t         deltaphi;
   Float_t         deltatheta;
   Float_t         deltapt_InSim_OutRec;
   Float_t         deltaphi_InSim_OutRec;
   Float_t         deltatheta_InSim_OutRec;
   Float_t         deltax;
   Float_t         deltay;
   Float_t         deltaz;
   Char_t          isTherePrimaryTrack;
   Char_t          isThereMergedTrack;
   Char_t          isNucl;
   Char_t          isNuclLoose;
   Char_t          isNuclKink;
   Char_t          isFake;
   Char_t          isK0;
   Char_t          isLambda;
   Char_t          isLambdaBar;
   Char_t          isKminusLoose;
   Char_t          isKplusLoose;
   Char_t          isLooper;
   Char_t          isConvLoose;
   vector<float>   *tkPt;
   vector<float>   *tkEta;
   vector<float>   *tkDxy;
   vector<float>   *tkDz;
   vector<float>   *tkRho;
   vector<int>     *tkHits;
   vector<int>     *tkAlgo;
   vector<int>     *tkOuter;
   vector<int>    *tkPrimary;
   vector<int>    *tkSecondary;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isAssoc;   //!
   TBranch        *b_isNuclSim;   //!
   TBranch        *b_isKSim;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_phi;   //!
   TBranch        *b_theta;   //!
   TBranch        *b_ptOut;   //!
   TBranch        *b_phiOut;   //!
   TBranch        *b_thetaOut;   //!
   TBranch        *b_mOut;   //!
   TBranch        *b_mK;   //!
   TBranch        *b_angle;   //!
   TBranch        *b_nOut;   //!
   TBranch        *b_nOutTkStep67Good;   //!
   TBranch        *b_nOutTkStep67Poor;   //!
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_deltapt;   //!
   TBranch        *b_deltaphi;   //!
   TBranch        *b_deltatheta;   //!
   TBranch        *b_deltapt_InSim_OutRec;   //!
   TBranch        *b_deltaphi_InSim_OutRec;   //!
   TBranch        *b_deltatheta_InSim_OutRec;   //!
   TBranch        *b_deltax;   //!
   TBranch        *b_deltay;   //!
   TBranch        *b_deltaz;   //!
   TBranch        *b_isTherePrimaryTrack;   //!
   TBranch        *b_isThereMergedTrack;   //!
   TBranch        *b_isNucl;   //!
   TBranch        *b_isNuclLoose;   //!
   TBranch        *b_isNuclKink;   //!
   TBranch        *b_isFake;   //!
   TBranch        *b_isK0;   //!
   TBranch        *b_isLambda;   //!
   TBranch        *b_isLambdaBar;   //!
   TBranch        *b_isKminusLoose;   //!
   TBranch        *b_isKplusLoose;   //!
   TBranch        *b_isLooper;   //!
   TBranch        *b_isConvLoose;   //!
   TBranch        *b_tkPt;   //!
   TBranch        *b_tkEta;   //!
   TBranch        *b_tkDxy;   //!
   TBranch        *b_tkDz;   //!
   TBranch        *b_tkRho;   //!
   TBranch        *b_tkHits;   //!
   TBranch        *b_tkAlgo;   //!
   TBranch        *b_tkOuter;   //!
   TBranch        *b_tkPrimary;   //!
   TBranch        *b_tkSecondary;   //!

   TH1 * h4;
   TH1 * h5;
   TH1 * h6;
   TH1 * h7;
   TH1 * h8;
   TH1 * h9;
   TH1 * h10;
   TH1 * h11;
   TH1 * h12;
   TFile* out;

   TrackingSteps(TTree *tree=0);
   virtual ~TrackingSteps();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TrackingSteps_cxx
TrackingSteps::TrackingSteps(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//   if (tree == 0) {
//  TFile *f = TFile::Open("/afs/cern.ch/user/m/mgouzevi/scratch0/CMSSW_4_1_2_patch1/src/Tests/MaterialNtuplizer/ntuple_wDomenicoStep.root");
  TFile *f = TFile::Open("/tmp/mgouzevi/ntuple_Total_wDomenicoStep.root");

     //("rfio:/castor/cern.ch/user/m/mgouzevi/CMSSW_358p3/NuclearSkim_CMSSW358p3_minbias7TeV_R2S_20100604_HighPurity.root");
     //if (!f) {
     //    f = new TFile("ntuple_nuclint_CMSSW358p3_goodcoll7TeV_2010-06-04.root");
     // }
     // }
  tree = (TTree*)gDirectory->Get("TrackingSteps");
   Init(tree);
}

TrackingSteps::~TrackingSteps()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TrackingSteps::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TrackingSteps::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TrackingSteps::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   tkPt = 0;
   tkEta = 0;
   tkDxy = 0;
   tkDz = 0;
   tkRho = 0;
   tkHits = 0;
   tkAlgo = 0;
   tkOuter = 0;
   tkPrimary = 0;
   tkSecondary = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("isAssoc", &isAssoc, &b_isAssoc);
   fChain->SetBranchAddress("isNuclSim", &isNuclSim, &b_isNuclSim);
   fChain->SetBranchAddress("isKSim", &isKSim, &b_isKSim);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("phi", &phi, &b_phi);
   fChain->SetBranchAddress("theta", &theta, &b_theta);
   fChain->SetBranchAddress("ptOut", &ptOut, &b_ptOut);
   fChain->SetBranchAddress("phiOut", &phiOut, &b_phiOut);
   fChain->SetBranchAddress("thetaOut", &thetaOut, &b_thetaOut);
   fChain->SetBranchAddress("mOut", &mOut, &b_mOut);
   fChain->SetBranchAddress("mK", &mK, &b_mK);
   fChain->SetBranchAddress("angle", &angle, &b_angle);
   fChain->SetBranchAddress("nOut", &nOut, &b_nOut);
   fChain->SetBranchAddress("nOutTkStep67Good", &nOutTkStep67Good, &b_nOutTkStep67Good);
   fChain->SetBranchAddress("nOutTkStep67Poor", &nOutTkStep67Poor, &b_nOutTkStep67Poor);
   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("deltapt", &deltapt, &b_deltapt);
   fChain->SetBranchAddress("deltaphi", &deltaphi, &b_deltaphi);
   fChain->SetBranchAddress("deltatheta", &deltatheta, &b_deltatheta);
   fChain->SetBranchAddress("deltapt_InSim_OutRec", &deltapt_InSim_OutRec, &b_deltapt_InSim_OutRec);
   fChain->SetBranchAddress("deltaphi_InSim_OutRec", &deltaphi_InSim_OutRec, &b_deltaphi_InSim_OutRec);
   fChain->SetBranchAddress("deltatheta_InSim_OutRec", &deltatheta_InSim_OutRec, &b_deltatheta_InSim_OutRec);
   fChain->SetBranchAddress("deltax", &deltax, &b_deltax);
   fChain->SetBranchAddress("deltay", &deltay, &b_deltay);
   fChain->SetBranchAddress("deltaz", &deltaz, &b_deltaz);
   fChain->SetBranchAddress("isTherePrimaryTrack", &isTherePrimaryTrack, &b_isTherePrimaryTrack);
   fChain->SetBranchAddress("isThereMergedTrack", &isThereMergedTrack, &b_isThereMergedTrack);
   fChain->SetBranchAddress("isNucl", &isNucl, &b_isNucl);
   fChain->SetBranchAddress("isNuclLoose", &isNuclLoose, &b_isNuclLoose);
   fChain->SetBranchAddress("isNuclKink", &isNuclKink, &b_isNuclKink);
   fChain->SetBranchAddress("isFake", &isFake, &b_isFake);
   fChain->SetBranchAddress("isK0", &isK0, &b_isK0);
   fChain->SetBranchAddress("isLambda", &isLambda, &b_isLambda);
   fChain->SetBranchAddress("isLambdaBar", &isLambdaBar, &b_isLambdaBar);
   fChain->SetBranchAddress("isKminusLoose", &isKminusLoose, &b_isKminusLoose);
   fChain->SetBranchAddress("isKplusLoose", &isKplusLoose, &b_isKplusLoose);
   fChain->SetBranchAddress("isLooper", &isLooper, &b_isLooper);
   fChain->SetBranchAddress("isConvLoose", &isConvLoose, &b_isConvLoose);
   fChain->SetBranchAddress("tkPt", &tkPt, &b_tkPt);
   fChain->SetBranchAddress("tkEta", &tkEta, &b_tkEta);
   fChain->SetBranchAddress("tkDxy", &tkDxy, &b_tkDxy);
   fChain->SetBranchAddress("tkDz", &tkDz, &b_tkDz);
   fChain->SetBranchAddress("tkRho", &tkRho, &b_tkRho);
   fChain->SetBranchAddress("tkHits", &tkHits, &b_tkHits);
   fChain->SetBranchAddress("tkAlgo", &tkAlgo, &b_tkAlgo);
   fChain->SetBranchAddress("tkOuter", &tkOuter, &b_tkOuter);
   fChain->SetBranchAddress("tkPrimary", &tkPrimary, &b_tkPrimary);
   fChain->SetBranchAddress("tkSecondary", &tkSecondary, &b_tkSecondary);
   Notify();

   
   h4 = new TH1F("r4","r4",80,0,80);
   h5 = new TH1F("r5","r5",80,0,80);
   h6 = new TH1F("r6","r6",80,0,80);
   h7 = new TH1F("r7","r7",80,0,80);
   h8 = new TH1F("r8","r8",80,0,80);
   h9 = new TH1F("r9","r9",80,0,80);
   h10 = new TH1F("r10","r10",80,0,80);
   h11 = new TH1F("r11","r11",80,0,80);
   h12 = new TH1F("r12","r12",80,0,80);
   
   /*
   h4 = new TH1F("r4","r4",60,-3,3);
   h5 = new TH1F("r5","r5",60,-3,3);
   h6 = new TH1F("r6","r6",60,-3,3);
   h7 = new TH1F("r7","r7",60,-3,3);
   h8 = new TH1F("r8","r8",60,-3,3);
   h9 = new TH1F("r9","r9",60,-3,3);
   h10 = new TH1F("r10","r10",60,-3,3);
   h11 = new TH1F("r11","r11",60,-3,3);
   */

   out = new TFile("out_eta.root","recreate");

}

Bool_t TrackingSteps::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TrackingSteps::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TrackingSteps::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TrackingSteps_cxx
