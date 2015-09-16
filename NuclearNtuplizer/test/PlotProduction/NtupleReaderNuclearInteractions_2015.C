#ifndef NtupleReaderNuclearInteractions_2015_cxx
#define NtupleReaderNuclearInteractions_2015_cxx

/* ****************************************** */
/*                                            */
/* Tracker Material with Nuclear Interactions */
/*                                            */
/*               Nicola Pozzobon              */
/*                    2013                    */
/*                                            */
/* ****************************************** */

#include "NtupleReaderNuclearInteractions_2015.h"

/* Constructor (file opening and tree loading) */
NtupleReaderNuclearInteractions_2015::NtupleReaderNuclearInteractions_2015( const std::string fileList, const Long64_t maxEvents )
{
  /// Initialize the chain
  inputChain = new TChain("MyNtupleMaking/NuclearInteractionsTree");
  std::cout << " declaring tchain MyNtupleMaking/NuclearInteractionsTree\n";

  /// Load the input files
  std::ifstream fileNames( fileList.c_str() );
  if ( !fileNames.good() )
  {
    std::cout << "E R R O R ! File list \"" << fileList << "\" does not exist!" << std::endl;
    std::cout << "            Exiting ..." << std::endl;
    return;
  }

  /// Load each single file and add its tree to the chain
  std::string fileName;
  while ( fileNames >> fileName )
  {
    std::cout << "I N F O : Adding file \"" << fileName << "\" to the chain." << std::endl;
    inputChain->Add( fileName.c_str() );
  }

  /// Store the maximum number of events to be processed
  maxEventsToProcess = ( maxEvents == -1 ) ? inputChain->GetEntries() : std::min( inputChain->GetEntries(), maxEvents );

  std::cout << " entries are "<<inputChain->GetEntries()<<std::endl;

  outputFile = new TFile( "prova.root", "RECREATE" );

}

/* Destructor (kill all pointers) */
NtupleReaderNuclearInteractions_2015::~NtupleReaderNuclearInteractions_2015()
{
  outputFile->Write();
  outputFile->Close();
  delete inputChain->GetCurrentFile();
}

/* Begin Job (tree initialization) */
void NtupleReaderNuclearInteractions_2015::beginJob()
{
  /// Initialize all branches
  std::string warningString_Branches = "W A R N I N G! Variable is missing from the ntuple! Trying to use it will result in a crash!";

  /// General
  if ( inputChain->GetBranchStatus( "isRealData" ) )
    inputChain->SetBranchAddress( "isRealData", &isRealData, &b_isRealData );
  else std::cout << "isRealData " << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "runNumber" ) )
    inputChain->SetBranchAddress( "runNumber", &runNumber, &b_runNumber );
  else std::cout << "runNumber "  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "eventNumber" ) )
    inputChain->SetBranchAddress( "eventNumber", &eventNumber, &b_eventNumber );
  else std::cout << "eventNumber " << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "lumiSection" ) )
    inputChain->SetBranchAddress( "lumiSection", &lumiSection, &b_lumiSection );
  else std::cout<< "lumiSection " << warningString_Branches.data() << std::endl;

  /// Primary Vertices
  PV_x = new std::vector< double >();
  PV_y = new std::vector< double >();
  PV_z = new std::vector< double >();
  PV_xError = new std::vector< double >();
  PV_yError = new std::vector< double >();
  PV_zError = new std::vector< double >();
  PV_isFake = new std::vector< bool >();

  if ( inputChain->GetBranchStatus( "numberOfPV" ) )
    inputChain->SetBranchAddress( "numberOfPV", &numberOfPV, &b_numberOfPV );
  else std::cout << "numberOfPV " << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_x" ) )
    inputChain->SetBranchAddress( "PV_x", &PV_x, &b_PV_x );
  else std::cout << "PV_x "  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_y" ) )
    inputChain->SetBranchAddress( "PV_y", &PV_y, &b_PV_y );
  else std::cout << "PV_y " << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_z" ) )
    inputChain->SetBranchAddress( "PV_z", &PV_z, &b_PV_z );
  else std::cout << "PV_z " << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_xError" ) )
    inputChain->SetBranchAddress( "PV_xError", &PV_xError, &b_PV_xError );
  else std::cout  << "PV_xError "<< warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_yError" ) )
    inputChain->SetBranchAddress( "PV_yError", &PV_yError, &b_PV_yError );
  else std::cout  << "PV_yError "<< warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_zError" ) )
    inputChain->SetBranchAddress( "PV_zError", &PV_zError, &b_PV_zError );
  else std::cout  << "PV_zError "<< warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_isFake" ) )
    inputChain->SetBranchAddress( "PV_isFake", &PV_isFake, &b_PV_isFake );
  else std::cout  << "PV_isFake "<< warningString_Branches.data() << std::endl;

  /// MC PileUp
  MC_PUInfo_bunchCrossing = new std::vector< unsigned int >();
  MC_PUInfo_numberOfInteractions = new std::vector< unsigned int >();

  if ( inputChain->GetBranchStatus( "numberOfMC_PUInfo" ) )
    inputChain->SetBranchAddress( "numberOfMC_PUInfo", &numberOfMC_PUInfo, &b_numberOfMC_PUInfo );
  else std::cout  << "numberOfMC_PUInfo "<< warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_PUInfo_bunchCrossing" ) )
    inputChain->SetBranchAddress( "MC_PUInfo_bunchCrossing", &MC_PUInfo_bunchCrossing, &b_MC_PUInfo_bunchCrossing );
  else std::cout << "MC_PUInfo_bunchCrossing "<< warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_PUInfo_numberOfInteractions" ) )
    inputChain->SetBranchAddress( "MC_PUInfo_numberOfInteractions", &MC_PUInfo_numberOfInteractions, &b_MC_PUInfo_numberOfInteractions );
  else std::cout << "MC_PUInfo_numberOfInteractions "<< warningString_Branches.data() << std::endl;

  /// BeamSpot
  if ( inputChain->GetBranchStatus( "BS_x" ) )
    inputChain->SetBranchAddress( "BS_x", &BS_x, &b_BS_x );
  else std::cout <<  "BS_x " << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_y" ) )
    inputChain->SetBranchAddress( "BS_y", &BS_y, &b_BS_y );
  else std::cout << "BS_y"  << warningString_Branches.data() << std::endl;
    if ( inputChain->GetBranchStatus( "BS_z" ) )
    inputChain->SetBranchAddress( "BS_z", &BS_z, &b_BS_z );
  else std::cout <<  "BS_z" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_zSigma" ) )
    inputChain->SetBranchAddress( "BS_zSigma", &BS_zSigma, &b_BS_zSigma );
  else std::cout << "BS_zSigma" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_dxdy" ) )
    inputChain->SetBranchAddress( "BS_dxdy", &BS_dxdy, &b_BS_dxdy );
  else std::cout <<"BS_dxdy"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_dydz" ) )
    inputChain->SetBranchAddress( "BS_dydz", &BS_dydz, &b_BS_dydz );
  else std::cout << "BS_dydz" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_xWidth" ) )
    inputChain->SetBranchAddress( "BS_xWidth", &BS_xWidth, &b_BS_xWidth );
  else std::cout << "BS_xWidth" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_yWidth" ) )
    inputChain->SetBranchAddress( "BS_yWidth", &BS_yWidth, &b_BS_yWidth );
  else std::cout << "BS_yWidth" << warningString_Branches.data() << std::endl;

  /// Tracking Vertices
  MC_TrkV_isNuclearInteraction = new std::vector< bool >();
  MC_TrkV_isKaonDecay = new std::vector< bool >();
  MC_TrkV_isConversion = new std::vector< bool >();
  MC_TrkV_x = new std::vector< double >();
  MC_TrkV_y = new std::vector< double >();
  MC_TrkV_z = new std::vector< double >();
  MC_TrkV_momentumInc_pt = new std::vector< double >();
  MC_TrkV_momentumInc_phi = new std::vector< double >();
  MC_TrkV_momentumInc_theta = new std::vector< double >();
  MC_TrkV_momentumOut_pt = new std::vector< double >();
  MC_TrkV_momentumOut_phi = new std::vector< double >();
  MC_TrkV_momentumOut_theta = new std::vector< double >();
  MC_TrkV_momentumOut_mass = new std::vector< double >();
  MC_TrkV_numberOfChargedParticles_0p2 = new std::vector< unsigned int >();
  MC_TrkV_numberOfChargedParticles_0p5 = new std::vector< unsigned int >();
  MC_TrkV_numberOfChargedParticles_1p0 = new std::vector< unsigned int >();
  MC_TrkV_isAssociatedPF = new std::vector< bool >();
  MC_TrkV_associationPFDVIdx = new std::vector< unsigned int >();
  MC_TrkV_associationPFDV_deltaR2d = new std::vector< double >();
  MC_TrkV_associationPFDV_deltaR3d = new std::vector< double >();
  MC_TrkV_associationPFDV_deltaR3dPerpendicular = new std::vector< double >();
  MC_TrkV_associationPFDV_deltaR3dParallel = new std::vector< double >();

  if ( inputChain->GetBranchStatus( "numberOfMC_TrkV" ) )
    inputChain->SetBranchAddress( "numberOfMC_TrkV", &numberOfMC_TrkV, &b_numberOfMC_TrkV );
  else std::cout << "numberOfMC_TrkV"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isNuclearInteraction" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isNuclearInteraction", &MC_TrkV_isNuclearInteraction, &b_MC_TrkV_isNuclearInteraction );
  else std::cout << "MC_TrkV_isNuclearInteraction" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isKaonDecay" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isKaonDecay", &MC_TrkV_isKaonDecay, &b_MC_TrkV_isKaonDecay );
  else std::cout <<"MC_TrkV_isKaonDecay"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isConversion" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isConversion", &MC_TrkV_isConversion, &b_MC_TrkV_isConversion );
  else std::cout <<"MC_TrkV_isConversion"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_x" ) )
    inputChain->SetBranchAddress( "MC_TrkV_x", &MC_TrkV_x, &b_MC_TrkV_x );
  else std::cout << "MC_TrkV_x" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_y" ) )
    inputChain->SetBranchAddress( "MC_TrkV_y", &MC_TrkV_y, &b_MC_TrkV_y );
  else std::cout << "MC_TrkV_y" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_z" ) )
    inputChain->SetBranchAddress( "MC_TrkV_z", &MC_TrkV_z, &b_MC_TrkV_z );
  else std::cout << "MC_TrkV_z" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumInc_pt" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumInc_pt", &MC_TrkV_momentumInc_pt, &b_MC_TrkV_momentumInc_pt );
  else std::cout << "MC_TrkV_momentumInc_pt" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumInc_theta" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumInc_theta", &MC_TrkV_momentumInc_theta, &b_MC_TrkV_momentumInc_theta );
  else std::cout <<"MC_TrkV_momentumInc_theta"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumInc_phi" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumInc_phi", &MC_TrkV_momentumInc_phi, &b_MC_TrkV_momentumInc_phi );
  else std::cout << "MC_TrkV_momentumInc_phi" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_pt" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_pt", &MC_TrkV_momentumOut_pt, &b_MC_TrkV_momentumOut_pt );
  else std::cout <<"MC_TrkV_momentumOut_pt"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_phi" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_phi", &MC_TrkV_momentumOut_phi, &b_MC_TrkV_momentumOut_phi );
  else std::cout << "MC_TrkV_momentumOut_phi" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_theta" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_theta", &MC_TrkV_momentumOut_theta, &b_MC_TrkV_momentumOut_theta );
  else std::cout <<"MC_TrkV_momentumOut_theta"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_mass" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_mass", &MC_TrkV_momentumOut_mass, &b_MC_TrkV_momentumOut_mass );
  else std::cout << "MC_TrkV_momentumOut_mass" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_numberOfChargedParticles_0p2" ) )
    inputChain->SetBranchAddress( "MC_TrkV_numberOfChargedParticles_0p2", &MC_TrkV_numberOfChargedParticles_0p2, &b_MC_TrkV_numberOfChargedParticles_0p2 );
  else std::cout <<"MC_TrkV_numberOfChargedParticles_0p2"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_numberOfChargedParticles_0p5" ) )
    inputChain->SetBranchAddress( "MC_TrkV_numberOfChargedParticles_0p5", &MC_TrkV_numberOfChargedParticles_0p5, &b_MC_TrkV_numberOfChargedParticles_0p5 );
  else std::cout <<"MC_TrkV_numberOfChargedParticles_0p5"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_numberOfChargedParticles_1p0" ) )
    inputChain->SetBranchAddress( "MC_TrkV_numberOfChargedParticles_1p0", &MC_TrkV_numberOfChargedParticles_1p0, &b_MC_TrkV_numberOfChargedParticles_1p0 );
  else std::cout <<"MC_TrkV_numberOfChargedParticles_1p0"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isAssociatedPF" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isAssociatedPF", &MC_TrkV_isAssociatedPF, &b_MC_TrkV_isAssociatedPF );
  else std::cout << "MC_TrkV_isAssociatedPF" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_associationPFDVIdx" ) )
    inputChain->SetBranchAddress( "MC_TrkV_associationPFDVIdx", &MC_TrkV_associationPFDVIdx, &b_MC_TrkV_associationPFDVIdx );
  else std::cout << "MC_TrkV_associationPFDVIdx" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_associationPFDV_deltaR2d" ) )
    inputChain->SetBranchAddress( "MC_TrkV_associationPFDV_deltaR2d", &MC_TrkV_associationPFDV_deltaR2d, &b_MC_TrkV_associationPFDV_deltaR2d );
  else std::cout << "MC_TrkV_associationPFDV_deltaR2d" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_associationPFDV_deltaR3d" ) )
    inputChain->SetBranchAddress( "MC_TrkV_associationPFDV_deltaR3d", &MC_TrkV_associationPFDV_deltaR3d, &b_MC_TrkV_associationPFDV_deltaR3d );
  else std::cout << "MC_TrkV_associationPFDV_deltaR3d" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_associationPFDV_deltaR3dPerpendicular" ) )
    inputChain->SetBranchAddress( "MC_TrkV_associationPFDV_deltaR3dPerpendicular", &MC_TrkV_associationPFDV_deltaR3dPerpendicular, &b_MC_TrkV_associationPFDV_deltaR3dPerpendicular );
  else std::cout << "MC_TrkV_associationPFDV_deltaR3dPerpendicular" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_associationPFDV_deltaR3dParallel" ) )
    inputChain->SetBranchAddress( "MC_TrkV_associationPFDV_deltaR3dParallel", &MC_TrkV_associationPFDV_deltaR3dParallel, &b_MC_TrkV_associationPFDV_deltaR3dParallel );
  else std::cout << "MC_TrkV_associationPFDV_deltaR3dParallel" << warningString_Branches.data() << std::endl;

  /// Displaced Vertices
  PFDV_x = new std::vector< double >();
  PFDV_y = new std::vector< double >();
  PFDV_z = new std::vector< double >();
  PFDV_momentumInc_pt = new std::vector< double >();
  PFDV_momentumInc_phi = new std::vector< double >();
  PFDV_momentumInc_theta = new std::vector< double >();
  PFDV_momentumOut_pt = new std::vector< double >();
  PFDV_momentumOut_phi = new std::vector< double >();
  PFDV_momentumOut_theta = new std::vector< double >();
  PFDV_momentumOut_mass = new std::vector< double >();
  PFDV_momentumOut_numberOfTracks = new std::vector< unsigned int >();
  PFDV_numberOfTracks_0p0 = new std::vector< unsigned int >();
  PFDV_numberOfTracks_0p2 = new std::vector< unsigned int >();
  PFDV_numberOfTracks_0p5 = new std::vector< unsigned int >();
  PFDV_numberOfTracks_1p0 = new std::vector< unsigned int >();
  PFDV_isNuclear = new std::vector< bool >();
  PFDV_isNuclearLoose = new std::vector< bool >();
  PFDV_isNuclearKink = new std::vector< bool >();
  PFDV_isK0 = new std::vector< bool >();
  PFDV_isLambda = new std::vector< bool >();
  PFDV_isLambdaBar = new std::vector< bool >();
  PFDV_isKPlusLoose = new std::vector< bool >();
  PFDV_isKMinusLoose = new std::vector< bool >();
  PFDV_isConversionLoose = new std::vector< bool >();
  PFDV_isLooper = new std::vector< bool >();
  PFDV_isFake = new std::vector< bool >();
  PFDV_isTherePrimaryTrack = new std::vector< bool >();
  PFDV_isThereMergedTrack = new std::vector< bool >();
  PFDV_isAssociatedMC = new std::vector< bool >();
  PFDV_deltaR3d_Associated = new std::vector< double >();
  PFDV_deltaR2d_Associated = new std::vector< double >();
  PFDV_associationMC_TrkVIdx = new std::vector< unsigned int >();
  PFDV_vTrack_pt = new std::vector< std::vector< double > >();
  PFDV_vTrack_eta = new std::vector< std::vector< double > >();
  PFDV_vTrack_phi = new std::vector< std::vector< double > >();
  PFDV_vTrack_rho = new std::vector< std::vector< double > >();
  PFDV_vTrack_numberOfValidHits = new std::vector< std::vector< unsigned int > >();
  PFDV_vTrack_numberOfExpectedOuterHits = new std::vector< std::vector< unsigned int > >();
  PFDV_vTrack_closestDxyPVIdx = new std::vector< std::vector< unsigned int > >();
  PFDV_vTrack_closestDxyPVIdx_dxy = new std::vector< std::vector< double > >();
  PFDV_vTrack_closestDxyPVIdx_dz = new std::vector< std::vector< double > >();
  PFDV_vTrack_closestDzPVIdx = new std::vector< std::vector< unsigned int > >();
  PFDV_vTrack_closestDzPVIdx_dxy = new std::vector< std::vector< double > >();
  PFDV_vTrack_closestDzPVIdx_dz = new std::vector< std::vector< double > >();

  if ( inputChain->GetBranchStatus( "numberOfPFDV" ) )
    inputChain->SetBranchAddress( "numberOfPFDV", &numberOfPFDV, &b_numberOfPFDV );
  else std::cout <<"numberOfPFDV"  <<  warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_x" ) )
    inputChain->SetBranchAddress( "PFDV_x", &PFDV_x, &b_PFDV_x );
  else std::cout << "PFDV_x" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_y" ) )
    inputChain->SetBranchAddress( "PFDV_y", &PFDV_y, &b_PFDV_y );
  else std::cout <<  "PFDV_y" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_z" ) )
    inputChain->SetBranchAddress( "PFDV_z", &PFDV_z, &b_PFDV_z );
  else std::cout << "PFDV_z"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumInc_pt" ) )
    inputChain->SetBranchAddress( "PFDV_momentumInc_pt", &PFDV_momentumInc_pt, &b_PFDV_momentumInc_pt );
  else std::cout <<"PFDV_momentumInc_pt"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumInc_theta" ) )
    inputChain->SetBranchAddress( "PFDV_momentumInc_theta", &PFDV_momentumInc_theta, &b_PFDV_momentumInc_theta );
  else std::cout << "PFDV_momentumInc_theta" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumInc_phi" ) )
    inputChain->SetBranchAddress( "PFDV_momentumInc_phi", &PFDV_momentumInc_phi, &b_PFDV_momentumInc_phi );
  else std::cout << "PFDV_momentumInc_phi" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_pt" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_pt", &PFDV_momentumOut_pt, &b_PFDV_momentumOut_pt );
  else std::cout <<"PFDV_momentumOut_pt"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_phi" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_phi", &PFDV_momentumOut_phi, &b_PFDV_momentumOut_phi );
  else std::cout << "PFDV_momentumOut_phi" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_theta" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_theta", &PFDV_momentumOut_theta, &b_PFDV_momentumOut_theta );
  else std::cout << "PFDV_momentumOut_theta" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_mass" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_mass", &PFDV_momentumOut_mass, &b_PFDV_momentumOut_mass );
  else std::cout << "PFDV_momentumOut_mass" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_numberOfTracks" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_numberOfTracks", &PFDV_momentumOut_numberOfTracks, &b_PFDV_momentumOut_numberOfTracks );
  else std::cout << "PFDV_momentumOut_numberOfTracks" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_numberOfTracks_0p0" ) )
    inputChain->SetBranchAddress( "PFDV_numberOfTracks_0p0", &PFDV_numberOfTracks_0p0, &b_PFDV_numberOfTracks_0p0 );
  else std::cout << "PFDV_numberOfTracks_0p0" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_numberOfTracks_0p2" ) )
    inputChain->SetBranchAddress( "PFDV_numberOfTracks_0p2", &PFDV_numberOfTracks_0p2, &b_PFDV_numberOfTracks_0p2 );
  else std::cout << "PFDV_numberOfTracks_0p2" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_numberOfTracks_0p5" ) )
    inputChain->SetBranchAddress( "PFDV_numberOfTracks_0p5", &PFDV_numberOfTracks_0p5, &b_PFDV_numberOfTracks_0p5 );
  else std::cout << "PFDV_numberOfTracks_0p5" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_numberOfTracks_1p0" ) )
    inputChain->SetBranchAddress( "PFDV_numberOfTracks_1p0", &PFDV_numberOfTracks_1p0, &b_PFDV_numberOfTracks_1p0 );
  else std::cout << "PFDV_numberOfTracks_1p0" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isNuclear" ) )
    inputChain->SetBranchAddress( "PFDV_isNuclear", &PFDV_isNuclear, &b_PFDV_isNuclear );
  else std::cout << "PFDV_isNuclear" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isNuclearLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isNuclearLoose", &PFDV_isNuclearLoose, &b_PFDV_isNuclearLoose );
  else std::cout << "PFDV_isNuclearLoose" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isNuclearKink" ) )
    inputChain->SetBranchAddress( "PFDV_isNuclearKink", &PFDV_isNuclearKink, &b_PFDV_isNuclearKink );
  else std::cout << "PFDV_isNuclearKink" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isK0" ) )
    inputChain->SetBranchAddress( "PFDV_isK0", &PFDV_isK0, &b_PFDV_isK0 );
  else std::cout << "PFDV_isK0"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isLambda" ) )
    inputChain->SetBranchAddress( "PFDV_isLambda", &PFDV_isLambda, &b_PFDV_isLambda );
  else std::cout << "PFDV_isLambda"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isLambdaBar" ) )
    inputChain->SetBranchAddress( "PFDV_isLambdaBar", &PFDV_isLambdaBar, &b_PFDV_isLambdaBar );
  else std::cout <<"PFDV_isLambdaBar" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isKPlusLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isKPlusLoose", &PFDV_isKPlusLoose, &b_PFDV_isKPlusLoose );
  else std::cout <<"PFDV_isKPlusLoose" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isKMinusLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isKMinusLoose", &PFDV_isKMinusLoose, &b_PFDV_isKMinusLoose );
  else std::cout <<"PFDV_isKMinusLoose" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isConversionLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isConversionLoose", &PFDV_isConversionLoose, &b_PFDV_isConversionLoose );
  else std::cout << "PFDV_isConversionLoose" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isLooper" ) )
    inputChain->SetBranchAddress( "PFDV_isLooper", &PFDV_isLooper, &b_PFDV_isLooper );
  else std::cout << "PFDV_isLooper"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isFake" ) )
    inputChain->SetBranchAddress( "PFDV_isFake", &PFDV_isFake, &b_PFDV_isFake );
  else std::cout << "PFDV_isFake" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isTherePrimaryTrack" ) )
    inputChain->SetBranchAddress( "PFDV_isTherePrimaryTrack", &PFDV_isTherePrimaryTrack, &b_PFDV_isTherePrimaryTrack );
  else std::cout << "PFDV_isTherePrimaryTrack" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isThereMergedTrack" ) )
    inputChain->SetBranchAddress( "PFDV_isThereMergedTrack", &PFDV_isThereMergedTrack, &b_PFDV_isThereMergedTrack );
  else std::cout <<"PFDV_isThereMergedTrack"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isAssociatedMC" ) )
    inputChain->SetBranchAddress( "PFDV_isAssociatedMC", &PFDV_isAssociatedMC, &b_PFDV_isAssociatedMC );
  else std::cout << "PFDV_isAssociatedMC" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_deltaR3d_Associated" ) )
    inputChain->SetBranchAddress( "PFDV_deltaR3d_Associated", &PFDV_deltaR3d_Associated, &b_PFDV_deltaR3d_Associated );
  else std::cout << "PFDV_deltaR3d_Associated" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_deltaR2d_Associated" ) )
    inputChain->SetBranchAddress( "PFDV_deltaR2d_Associated", &PFDV_deltaR2d_Associated, &b_PFDV_deltaR2d_Associated );
  else std::cout << "PFDV_deltaR2d_Associated" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_associationMC_TrkVIdx" ) )
    inputChain->SetBranchAddress( "PFDV_associationMC_TrkVIdx", &PFDV_associationMC_TrkVIdx, &b_PFDV_associationMC_TrkVIdx );
  else std::cout << "PFDV_associationMC_TrkVIdx" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_pt" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_pt", &PFDV_vTrack_pt, &b_PFDV_vTrack_pt );
  else std::cout << "PFDV_vTrack_pt" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_phi" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_phi", &PFDV_vTrack_phi, &b_PFDV_vTrack_phi );
  else std::cout << "PFDV_vTrack_phi" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_eta" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_eta", &PFDV_vTrack_eta, &b_PFDV_vTrack_eta );
  else std::cout << "PFDV_vTrack_eta" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_rho" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_rho", &PFDV_vTrack_rho, &b_PFDV_vTrack_rho );
  else std::cout << "PFDV_vTrack_rho" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_numberOfValidHits" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_numberOfValidHits", &PFDV_vTrack_numberOfValidHits, &b_PFDV_vTrack_numberOfValidHits );
  else std::cout << "PFDV_vTrack_numberOfValidHits" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_numberOfExpectedOuterHits" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_numberOfExpectedOuterHits", &PFDV_vTrack_numberOfExpectedOuterHits, &b_PFDV_vTrack_numberOfExpectedOuterHits );
  else std::cout <<"PFDV_vTrack_numberOfExpectedOuterHits"  << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDxyPVIdx" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDxyPVIdx", &PFDV_vTrack_closestDxyPVIdx, &b_PFDV_vTrack_closestDxyPVIdx );
  else std::cout << "PFDV_vTrack_closestDxyPVIdx" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDxyPVIdx_dxy" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDxyPVIdx_dxy", &PFDV_vTrack_closestDxyPVIdx_dxy, &b_PFDV_vTrack_closestDxyPVIdx_dxy );
  else std::cout << "PFDV_vTrack_closestDxyPVIdx_dxy" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDxyPVIdx_dz" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDxyPVIdx_dz", &PFDV_vTrack_closestDxyPVIdx_dz, &b_PFDV_vTrack_closestDxyPVIdx_dz );
  else std::cout << "PFDV_vTrack_closestDxyPVIdx_dz" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDzPVIdx" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDzPVIdx", &PFDV_vTrack_closestDzPVIdx, &b_PFDV_vTrack_closestDzPVIdx );
  else std::cout << "PFDV_vTrack_closestDzPVIdx" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDzPVIdx_dxy" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDzPVIdx_dxy", &PFDV_vTrack_closestDzPVIdx_dxy, &b_PFDV_vTrack_closestDzPVIdx_dxy );
  else std::cout << "PFDV_vTrack_closestDzPVIdx_dxy" << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDzPVIdx_dz" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDzPVIdx_dz", &PFDV_vTrack_closestDzPVIdx_dz, &b_PFDV_vTrack_closestDzPVIdx_dz );
  else std::cout << "PFDV_vTrack_closestDzPVIdx_dz" << warningString_Branches.data() << std::endl;


   //TRACKER MATERIAL bints : 1 bin by big structure.
   Bins[0]=     0.;
   Bins[1]=     1.9;
   Bins[2]=     2.5;
   Bins[3]=     3.5;
   Bins[4]=     6.;
   Bins[5]=     9.;
   Bins[6]=     11.5;
   Bins[7]=     22.;
   Bins[8]=     30.;
   Bins[9]=     38.;
   Bins[10]=     45.5;
   Bins[11]=    53.5;
   Bins[12]=    57.;
   Bins[13]=    65.;
 
  //histo MC_TrkV
  hMC_TrkV_isNuclearInteraction = new TH1D( "hMC_TrkV_isNuclearInteraction", "N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isNuclearInteraction->Sumw2();

  hMC_TrkV_isAssociatedPF = new TH1D( "hMC_TrkV_isAssociatedPF","N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isAssociatedPF->Sumw2();

  hMC_TrkV_associationPFDVIdx = new TH1D( "hMC_TrkV_associationPFDVIdx", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_associationPFDVIdx->Sumw2();
 
  hMC_TrkV_associationPFDV_deltaR2d = new TH1D( "hMC_TrkV_associationPFDV_deltaR2d", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR2d->Sumw2();

  hMC_TrkV_associationPFDV_deltaR2d_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR2d_Barrel", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR2d_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3d = new TH1D( "hMC_TrkV_associationPFDV_deltaR3d", "N.I. in Tracker", 100, 0, 5.);
  hMC_TrkV_associationPFDV_deltaR3d->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3d_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3d_Barrel", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR3d_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3d_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaR3d_Forward", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR3d_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicular = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicular", "N.I. in Tracker", 100, 0, 5.);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel", "N.I. in Tracker", 200, 0, 0.5);
  hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel", "N.I. in Tracker", 100, 0, 5.);
  hMC_TrkV_associationPFDV_deltaR3dParallel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallel_Forward = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallel_Forward", "N.I. in Tracker", 100, 0, 5. );
  hMC_TrkV_associationPFDV_deltaR3dParallel_Forward->Sumw2();

  hMC_TrkV_associationPFDV_deltaR3dParallelRel = new TH1D( "hMC_TrkV_associationPFDV_deltaR3dParallelRel", "N.I. in Tracker", 200, 0, 0.5);
  hMC_TrkV_associationPFDV_deltaR3dParallelRel->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR3d = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3d", "N.I. in Tracker", 100, 0, 0.20 );
  hMC_TrkV_associationPFDV_DuplicateR3d->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular", "N.I. in Tracker", 100, 0, 0.20 );
  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs", "N.I. in Tracker", 100, 0, 10. );
  hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR3dParallel = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR3dParallel", "N.I. in Tracker", 100, 0, 0.20 );
  hMC_TrkV_associationPFDV_DuplicateR3dParallel->Sumw2();

  hMC_TrkV_associationPFDV_DuplicateR = new TH1D( "hMC_TrkV_associationPFDV_DuplicateR", "N.I. in Tracker", 100, 0, 0.20 );
  hMC_TrkV_associationPFDV_DuplicateR->Sumw2();

  hMC_TrkV_isNuclearInteraction_Barrel = new TH1D( "hMC_TrkV_isNuclearInteraction_Barrel", "N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isNuclearInteraction_Barrel->Sumw2();

  hMC_TrkV_isAssociatedPF_Barrel = new TH1D( "hMC_TrkV_isAssociatedPF_Barrel","N.I. in Tracker", 10, -5, 5 );
  hMC_TrkV_isAssociatedPF_Barrel->Sumw2();

  hMC_TrkV_associationPFDVIdx_Barrel = new TH1D( "hMC_TrkV_associationPFDVIdx_Barrel", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_associationPFDVIdx_Barrel->Sumw2();


  hMC_TrkV_R_isNuclearInteraction = new TH1D( "hMC_TrkV_R_isNuclearInteraction", "N.I. in Tracker",500, 0, 60 );
  hMC_TrkV_R_isNuclearInteraction->Sumw2();

  hMC_TrkV_R_isNuclearInteraction_Barrel = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Barrel", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_isNuclearInteraction_Barrel->Sumw2();

  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel", "N.I. in Tracker", 13, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel->Sumw2();


  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2", "N.I. in Tracker", 13, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5", "N.I. in Tracker", 13, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5->Sumw2();
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0 = new TH1D( "hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0", "N.I. in Tracker", 13, Bins );
  hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0->Sumw2();

  hMC_TrkV_R_isAssociatedPF = new TH1D( "hMC_TrkV_R_isAssociatedPF", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_isAssociatedPF->Sumw2();

  hMC_TrkV_R_isAssociatedPF_Barrel = new TH1D( "hMC_TrkV_R_isAssociatedPF_Barrel","N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_isAssociatedPF_Barrel->Sumw2();

  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel","N.I. in Tracker", 13, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel->Sumw2();


  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2","N.I. in Tracker", 13, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5","N.I. in Tracker", 13, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5->Sumw2();
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0 = new TH1D( "hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0","N.I. in Tracker", 13, Bins);
  hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0->Sumw2();

  hMC_TrkV_R_associationPFDVIdx = new TH1D( "hMC_TrkV_R_associationPFDVIdx", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_associationPFDVIdx->Sumw2();

  hMC_TrkV_R_associationPFDVIdx_Barrel = new TH1D( "hMC_TrkV_R_associationPFDVIdx_Barrel", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_associationPFDVIdx_Barrel->Sumw2();

  hMC_TrkV_R = new TH1D( "hMC_TrkV_R", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R->Sumw2();

  hMC_TrkV_R_Barrel = new TH1D( "hMC_TrkV_R_Barrel", "N.I. in Tracker", 500, 0, 60 );
  hMC_TrkV_R_Barrel->Sumw2();


  hMC_TrkV_numberOftracks_0p2 = new TH1D( "hMC_TrkV_numberOftracks_0p2", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_0p2->Sumw2();

  hMC_TrkV_numberOftracks_0p5 = new TH1D( "hMC_TrkV_numberOftracks_0p5", "N.I. in Tracker", 20, 0, 20 );
  hMC_TrkV_numberOftracks_0p5->Sumw2();

  hMC_TrkV_numberOftracks_1p0 = new TH1D( "hMC_TrkV_numberOftracks_1p0", "N.I. in Tracker", 10, 0, 10 );
  hMC_TrkV_numberOftracks_1p0->Sumw2();


  /// Output histograms and graphs etc
  hPFDV_CountEventsWithNI = new TH1D( "hPFDV_CountEventsWithNI", "N.I. in Tracker", 3, 0, 2 );
  hPFDV_CountEventsWithNI->Sumw2();

  hPFDV_isAssociatedMC = new TH1D( "hPFDV_isAssociatedMC", "CMS work in progress", 10, -5, 5 );
  hPFDV_isAssociatedMC->Sumw2();

  hPFDV_deltaR3d_Associated = new TH1D( "hPFDV_deltaR3d_Associated", "CMS work in progress", 100, 0, 2 );
  hPFDV_deltaR3d_Associated->Sumw2();

  hPFDV_deltaR3d_Associated_Barrel = new TH1D( "hPFDV_deltaR3d_Associated_Barrel", "CMS work in progress", 100, 0, 2 );
  hPFDV_deltaR3d_Associated_Barrel->Sumw2();

  hPFDV_deltaR3d_Associated_Forward = new TH1D( "hPFDV_deltaR3d_Associated_Forward", "CMS work in progress", 100, 0, 6 );
  hPFDV_deltaR3d_Associated_Forward->Sumw2();

  hPFDV_deltaR3d_Associated_Rebin = new TH1D( "hPFDV_deltaR3d_Associated_Rebin", "CMS work in progress", 100, 0, 20 );
  hPFDV_deltaR3d_Associated_Rebin->Sumw2();

  hPFDV_deltaR3d_Associated_Barrel_Rebin = new TH1D( "hPFDV_deltaR3d_Associated_Barrel_Rebin", "CMS work in progress", 100, 0, 20 );
  hPFDV_deltaR3d_Associated_Barrel_Rebin->Sumw2();

  hPFDV_deltaR3d_Associated_Forward_Rebin = new TH1D( "hPFDV_deltaR3d_Associated_Forward_Rebin", "CMS work in progress", 100, 0, 20 );
  hPFDV_deltaR3d_Associated_Forward_Rebin->Sumw2();

  hPFDV_deltaR2d_Associated = new TH1D( "hPFDV_deltaR2d_Associated", "CMS work in progress", 100, -2, 2 );
  hPFDV_deltaR2d_Associated->Sumw2();

  hPFDV_deltaR2d_Associated_Barrel = new TH1D( "hPFDV_deltaR2d_Associated_Barrel", "CMS work in progress", 100, -2, 2 );
  hPFDV_deltaR2d_Associated_Barrel->Sumw2();


  hPFDV_isAssociatedMC_Barrel = new TH1D( "hPFDV_isAssociatedMC_Barrel", "CMS work in progress", 10, -5, 5 );
  hPFDV_isAssociatedMC_Barrel->Sumw2();

  hPFDV_isAssociatedMC_isNuclear_Barrel = new TH1D( "hPFDV_isAssociatedMC_isNuclear_Barrel", "CMS work in progress", 10, -5, 5 );
  hPFDV_isAssociatedMC_isNuclear_Barrel->Sumw2();

  hPFDV_associationMC_TrkVIdx = new TH1D( "hPFDV_associationMC_TrkVIdx", "CMS work in progress", 100, 0, 100 );
  hPFDV_associationMC_TrkVIdx->Sumw2();

  hPFDV_associationMC_TrkVIdx_Barrel = new TH1D( "hPFDV_associationMC_TrkVIdx_Barrel", "CMS work in progress", 100, 0, 100 );
  hPFDV_associationMC_TrkVIdx_Barrel->Sumw2();

  hPFDV_R_isAssociatedMC = new TH1D( "hPFDV_R_isAssociatedMC", "CMS work in progress", 500, 0, 60 );
  hPFDV_R_isAssociatedMC->Sumw2();

  hPFDV_R_isAssociatedMC_Barrel = new TH1D( "hPFDV_R_isAssociatedMC_Barrel", "CMS work in progress", 500, 0, 60 );
  hPFDV_R_isAssociatedMC_Barrel->Sumw2();

  hPFDV_numberOftracks_0p0 = new TH1D( "hPFDV_numberOftracks_0p0", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p0->Sumw2();

  hPFDV_numberOftracks_0p2 = new TH1D( "hPFDV_numberOftracks_0p2", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p2->Sumw2();

  hPFDV_numberOftracks_0p5 = new TH1D( "hPFDV_numberOftracks_0p5", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_0p5->Sumw2();

  hPFDV_numberOftracks_1p0 = new TH1D( "hPFDV_numberOftracks_1p0", "N.I. in Tracker", 20, 0, 20 );
  hPFDV_numberOftracks_1p0->Sumw2();

  hPFDV_vTrack_pt = new TH1D( "hPFDV_vTrack_pt", "CMS work in progress", 500, 0, 60 );
  hPFDV_vTrack_pt->Sumw2();

  hPFDV_R = new TH1D( "hPFDV_R", "CMS work in progress", 500, 0, 60 );
  hPFDV_R->Sumw2();

  hPFDV_R_BPix = new TH1D( "hPFDV_R_BPix", "CMS work in progress", 500, 0, 60 );
  hPFDV_R_BPix->Sumw2();

  hPFDV_R_Pipe = new TH1D( "hPFDV_R_Pipe", "CMS work in progress", 50, 2, 2.5 );
  hPFDV_R_Pipe->Sumw2();

  hPFDV_ZR_Map = new TH2D( "hPFDV_ZR_Map", "CMS work in progress", 800, -200, 200, 140, 0, 70 );
  hPFDV_ZR_Map->Sumw2();

  hPFDV_XY_Map = new TH2D( "hPFDV_XY_Map", "CMS work in progress", 280, -70, 70, 280, -70, 70 );
  hPFDV_RhoPhi_Map = new TH2D( "hPFDV_RhoPhi_Map", "CMS work in progress", 200, -TMath::Pi(), TMath::Pi(), 280, 0, 70 );
  hPFDV_XY_Map->Sumw2();
  hPFDV_RhoPhi_Map->Sumw2();

  hPFDV_XY_Map_BPix = new TH2D( "hPFDV_XY_Map_BPix", "CMS work in progress", 200, -25, 25, 200, -25, 25 );
  hPFDV_RhoPhi_Map_BPix = new TH2D( "hPFDV_RhoPhi_Map_BPix", "CMS work in progress", 200, -TMath::Pi(), TMath::Pi(), 200, 0, 25 );
  hPFDV_XY_Map_BPix->Sumw2();
  hPFDV_RhoPhi_Map_BPix->Sumw2();

  hPFDV_XY_Map_Pipe = new TH2D( "hPFDV_XY_Map_Pipe", "CMS work in progress", 200, -5, 5, 200, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe = new TH2D( "hPFDV_RhoPhi_Map_Pipe", "CMS work in progress", 200, -TMath::Pi(), TMath::Pi(), 200, 0, 5 );
  hPFDV_XY_Map_Pipe->Sumw2();
  hPFDV_RhoPhi_Map_Pipe->Sumw2();

//  hPFDV_XY_Map_Corr = new TH2D( "hPFDV_XY_Map_Corr", "N.I. in Tracker, BS Corr", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr = new TH2D( "hPFDV_RhoPhi_Map_Corr", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr->Sumw2();
//  hPFDV_RhoPhi_Map_Corr->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix = new TH2D( "hPFDV_XY_Map_Corr_BPix", "N.I. in Tracker, BS Corr", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe = new TH2D( "hPFDV_XY_Map_Corr_Pipe", "N.I. in Tracker, BS Corr", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe->Sumw2();
//
//  /// BPix length only
//  hPFDV_XY_Map_AbsZ25 = new TH2D( "hPFDV_XY_Map_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_BPix_AbsZ25 = new TH2D( "hPFDV_XY_Map_BPix_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_BPix_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_BPix_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_BPix_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_BPix_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Pipe_AbsZ25 = new TH2D( "hPFDV_XY_Map_Pipe_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Pipe_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Pipe_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Pipe_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Pipe_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Corr_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_BPix_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_Pipe_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25->Sumw2();
//
//  /// Reweighted
//  hPFDV_XY_Map_Weight = new TH2D( "hPFDV_XY_Map_Weight", "N.I. in Tracker", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Weight = new TH2D( "hPFDV_RhoPhi_Map_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Weight->Sumw2();
//
//  hPFDV_XY_Map_BPix_Weight = new TH2D( "hPFDV_XY_Map_BPix_Weight", "N.I. in Tracker", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_BPix_Weight = new TH2D( "hPFDV_RhoPhi_Map_BPix_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_BPix_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_BPix_Weight->Sumw2();
//
//  hPFDV_XY_Map_Pipe_Weight = new TH2D( "hPFDV_XY_Map_Pipe_Weight", "N.I. in Tracker", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Pipe_Weight = new TH2D( "hPFDV_RhoPhi_Map_Pipe_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Pipe_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Pipe_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_Weight = new TH2D( "hPFDV_XY_Map_Corr_Weight", "N.I. in Tracker, BS Corr", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix_Weight = new TH2D( "hPFDV_XY_Map_Corr_BPix_Weight", "N.I. in Tracker, BS Corr", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe_Weight = new TH2D( "hPFDV_XY_Map_Corr_Pipe_Weight", "N.I. in Tracker, BS Corr", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe_Weight->Sumw2();
//
//  hPFDV_XY_Map_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_BPix_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_BPix_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_BPix_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Pipe_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Pipe_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
//  hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//  hPFDV_XY_Map_Corr_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//  hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight->Sumw2();
//
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//  hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight->Sumw2();
//  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight->Sumw2();
//
//  std::ostringstream histoName;
//  std::ostringstream histoTitle;
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_" << k*5 << "_" << (k+1)*5;
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_" << k*5 << "_" << (k+1)*5;
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//    m_hPFDV_RhoPhi_Map.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_BPix_" << k*5 << "_" << (k+1)*5;
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_BPix.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_BPix_" << k*5 << "_" << (k+1)*5;
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//    m_hPFDV_RhoPhi_Map_BPix.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Pipe_" << k*5 << "_" << (k+1)*5;
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Pipe.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Pipe_" << k*5 << "_" << (k+1)*5;
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//    m_hPFDV_RhoPhi_Map_Pipe.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Corr_" << k*5 << "_" << (k+1)*5;
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Corr.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Corr_" << k*5 << "_" << (k+1)*5;
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//    m_hPFDV_RhoPhi_Map_Corr.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5;
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Corr_BPix.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5;
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//    m_hPFDV_RhoPhi_Map_Corr_BPix.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5;
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Corr_Pipe.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5;
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//    m_hPFDV_RhoPhi_Map_Corr_Pipe.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  /// Reweighted
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//    m_hPFDV_RhoPhi_Map_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_BPix_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//    m_hPFDV_RhoPhi_Map_BPix_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//    m_hPFDV_RhoPhi_Map_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Corr_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Corr_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Corr_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
//    m_hPFDV_RhoPhi_Map_Corr_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Corr_BPix_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
//    m_hPFDV_RhoPhi_Map_Corr_BPix_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }
//
//  for ( int k = -5; k < 5; k++ )
//  {
//    histoName.str("");
//    histoTitle.str("");
//    histoName << "hPFDV_XY_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
//    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
//    h1->Sumw2();
//    m_hPFDV_XY_Map_Corr_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
//    histoName.str("");
//    histoName << "hPFDV_RhoPhi_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
//    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
//    m_hPFDV_RhoPhi_Map_Corr_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
//  }




}



/* Analyze (loop over tree entries) */
void NtupleReaderNuclearInteractions_2015::analyze()
{
  /// Loop over events
  for ( Long64_t jentry = 0; jentry < maxEventsToProcess; jentry++ )
  {
    if( jentry%100000 == 0 )
      std::cout << "Loop over entry " << jentry << "/" << maxEventsToProcess << "." << std::endl;

    /// Set the environment to read one entry
    inputChain->LoadTree( jentry );
    inputChain->GetEntry( jentry );

    /// Here all the branches are available
    double ni_x, ni_y, ni_z, ni_rho, ni_phi;
    double ni_x_c, ni_y_c, ni_rho_c, ni_phi_c;
    int ni_z_i;

    double ni_MC_x, ni_MC_y, ni_MC_z, ni_MC_rho;
 
    int N_MCassociatePF = 0;
    double deltaR3dPerpendicular_Previouse = -1.;
    double deltaR3dParallel_Previouse = -1.;

    //for matching Duplicates
    std::vector< double > MatchingDuplicates_dR3;                               
    MatchingDuplicates_dR3.clear();
    std::vector< double > MatchingDuplicates_R;                               
    MatchingDuplicates_R.clear();

    for ( unsigned int i = 0; i < numberOfMC_TrkV; i++ )
    {
      ni_MC_x = MC_TrkV_x->at(i);
      ni_MC_y = MC_TrkV_y->at(i);
      ni_MC_z = MC_TrkV_z->at(i);
      ni_MC_rho = TMath::Sqrt( ni_MC_x*ni_MC_x + ni_MC_y*ni_MC_y );

      //check for assosiation MC_TrkV_isAssociatedPF->at(i) is dR3 < 20 is very big, need to do our serlf dR3 < 1 cm
      //bool isMC_assosiated_PF = MC_TrkV_isAssociatedPF->at(i);
      bool isMC_assosiated_PF = false;
      //if (MC_TrkV_isAssociatedPF->at(i) && MC_TrkV_associationPFDV_deltaR3d->at(i) < 1) isMC_assosiated_PF = true;  
      if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 2. && MC_TrkV_associationPFDV_deltaR3dParallel->at(i)< 20. ) isMC_assosiated_PF = true;  
      //if ( MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20. && MC_TrkV_associationPFDV_deltaR3dParallel->at(i)< 20. ) isMC_assosiated_PF = true;  

      // remove very soft vertex:
      if (MC_TrkV_numberOfChargedParticles_0p2->at(i) < 3 ) continue;

      ///////////     
      // test for assosiation
      double deltaMatchingDuplicates = -100;
      double deltaMatchingDuplicatesR = -100;
      double MatchDuplicatesCut_dR3 = 0.02;
      double MatchDuplicatesCut_R = 0.05; MatchDuplicatesCut_R = MatchDuplicatesCut_R;

      //if(isMC_assosiated_PF){
          //std::cout << "MC_TrkV_associationPFDV_deltaR3d = " << MC_TrkV_associationPFDV_deltaR3d->at(i) << std::endl; 
          //std::cout << "Radius of MC NI ni_MC_rho = " << ni_MC_rho << std::endl;
          //std::cout << "MC_TrkV_associationPFDV_deltaR3dPerpendicular = " << MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) << std::endl; 
          //std::cout << "MC_TrkV_associationPFDV_deltaR3dParallel = " << MC_TrkV_associationPFDV_deltaR3dParallel->at(i) << std::endl; 

          // DeltaR3d matching
          if (MC_TrkV_associationPFDV_deltaR3d->at(i) > 0) {
               if (i == 0) MatchingDuplicates_dR3.push_back( MC_TrkV_associationPFDV_deltaR3d->at(i) );
               double deltaMatching = 100.;
               if (MatchingDuplicates_dR3.size() > 1){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_dR3.size(); imatch++ )
                  {
                      double deltaMatching_imatch = fabs(MC_TrkV_associationPFDV_deltaR3d->at(i) - MatchingDuplicates_dR3.at(imatch))/(MC_TrkV_associationPFDV_deltaR3d->at(i) > 0);  
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                  } 
               }
               if (deltaMatching < 0.2)hMC_TrkV_associationPFDV_DuplicateR3d ->Fill(deltaMatching);//check that previouse value exist
               if (deltaMatching >= 0.2 && deltaMatching < 100.)hMC_TrkV_associationPFDV_DuplicateR3d ->Fill(0.1999999);//check that previouse value exist
               deltaMatchingDuplicates = deltaMatching;
               if (i != 0 && deltaMatchingDuplicates >= MatchDuplicatesCut_dR3) MatchingDuplicates_dR3.push_back( MC_TrkV_associationPFDV_deltaR3d->at(i) ); //next non Duplicate vertex
          }

          // Radius matching
          if ( ni_MC_rho > 0) {
               if (i == 0) MatchingDuplicates_R.push_back( ni_MC_rho );
               double deltaMatching = 100.;
               if (MatchingDuplicates_R.size() > 1){
                  for ( unsigned int imatch = 0; imatch < MatchingDuplicates_R.size(); imatch++ )
                  {
                      double deltaMatching_imatch = fabs(ni_MC_rho - MatchingDuplicates_R.at(imatch))/ni_MC_rho;
                      if (deltaMatching_imatch < deltaMatching) deltaMatching = deltaMatching_imatch;
                  }
               }
               if (deltaMatching < 0.2)hMC_TrkV_associationPFDV_DuplicateR ->Fill(deltaMatching);//check that previouse value exist
               if (deltaMatching >= 0.2 && deltaMatching < 100.)hMC_TrkV_associationPFDV_DuplicateR ->Fill(0.1999999);//check that previouse value exist
               deltaMatchingDuplicatesR = deltaMatching;
               if (i != 0 && deltaMatchingDuplicatesR >= MatchDuplicatesCut_R) MatchingDuplicates_R.push_back( ni_MC_rho ); //next non Duplicate vertex
          } 
 
          if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) > 0) {
               double deltaMatching = fabs(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) - deltaR3dPerpendicular_Previouse)/(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) > 0);
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatching < 0.2)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular ->Fill(deltaMatching);//check that previouse value exist
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatching >= 0.2)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicular ->Fill(0.1999999);//check that previouse value exist

               double deltaMatchingAbs = fabs(MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) - deltaR3dPerpendicular_Previouse);
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatchingAbs < 10.)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs ->Fill(deltaMatchingAbs);//check that previouse value exist
               if (deltaR3dPerpendicular_Previouse > 0 && deltaMatchingAbs >= 10.)hMC_TrkV_associationPFDV_DuplicateR3dPerpendicularAbs ->Fill(9.999999);//check that previouse value exist

               deltaR3dPerpendicular_Previouse = MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i);
          } 
          if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) > 0) {
               double deltaMatching = fabs(MC_TrkV_associationPFDV_deltaR3dParallel->at(i) - deltaR3dParallel_Previouse)/(MC_TrkV_associationPFDV_deltaR3dParallel->at(i) > 0);
               if (deltaR3dParallel_Previouse > 0 && deltaMatching < 0.2)hMC_TrkV_associationPFDV_DuplicateR3dParallel ->Fill(deltaMatching);//check that previouse value exist
               if (deltaR3dParallel_Previouse > 0 && deltaMatching >= 0.2)hMC_TrkV_associationPFDV_DuplicateR3dParallel ->Fill(0.1999999);//check that previouse value exist
               deltaR3dParallel_Previouse = MC_TrkV_associationPFDV_deltaR3dParallel->at(i);
          } 
      //} 

      //reject Duplicates:
      //if ( fabs(deltaMatchingDuplicates) < MatchDuplicatesCut_dR3) continue;
      if ( fabs(deltaMatchingDuplicates) < MatchDuplicatesCut_dR3 || fabs(deltaMatchingDuplicatesR) < MatchDuplicatesCut_R) continue;

      if(isMC_assosiated_PF) N_MCassociatePF++;
      if(N_MCassociatePF > 1){
          //std::cout << "MC_TrkV_associationPFDV_deltaR3d = " << MC_TrkV_associationPFDV_deltaR3d->at(i) << std::endl; 
          std::cout << "Radius of MC NI ni_MC_rho = " << ni_MC_rho << std::endl;
          //std::cout << "MC_TrkV_associationPFDV_deltaR3dPerpendicular = " << MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) << std::endl; 
          //std::cout << "MC_TrkV_associationPFDV_deltaR3dParallel = " << MC_TrkV_associationPFDV_deltaR3dParallel->at(i) << std::endl; 
      }
      ///////////
      
      hMC_TrkV_R->Fill( ni_MC_rho );
 
      hMC_TrkV_numberOftracks_0p2->Fill(MC_TrkV_numberOfChargedParticles_0p2->at(i));
      hMC_TrkV_numberOftracks_0p5->Fill(MC_TrkV_numberOfChargedParticles_0p5->at(i));
      hMC_TrkV_numberOftracks_1p0->Fill(MC_TrkV_numberOfChargedParticles_1p0->at(i));

      if ( MC_TrkV_isNuclearInteraction->at(i)){
      hMC_TrkV_isNuclearInteraction -> Fill (1.);
      hMC_TrkV_R_isNuclearInteraction->Fill( ni_MC_rho );
        if ( isMC_assosiated_PF ){
        hMC_TrkV_R_isAssociatedPF -> Fill ( ni_MC_rho );
        }
      }
      else{
      hMC_TrkV_isNuclearInteraction -> Fill (0.); 
      }

      
      if ( isMC_assosiated_PF ){
      hMC_TrkV_isAssociatedPF -> Fill (1.);
      }
      else{
      hMC_TrkV_isAssociatedPF -> Fill (0.);
      }
      
      if (MC_TrkV_associationPFDV_deltaR2d->at(i) < 5.)hMC_TrkV_associationPFDV_deltaR2d -> Fill (MC_TrkV_associationPFDV_deltaR2d->at(i));
      else if (MC_TrkV_associationPFDV_deltaR2d->at(i) < 20.)hMC_TrkV_associationPFDV_deltaR2d -> Fill (4.999);

      if (MC_TrkV_associationPFDV_deltaR3d->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3d -> Fill (MC_TrkV_associationPFDV_deltaR3d->at(i));
      else if (MC_TrkV_associationPFDV_deltaR3d->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3d -> Fill(4.999);

      if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dPerpendicular -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i));
      else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dPerpendicular -> Fill(4.999);

      if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dParallel -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
      else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallel -> Fill(4.999);

      double Rel_deltaR3dPerp = -1.;
      if (ni_MC_rho > 0.) Rel_deltaR3dPerp = MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i)/ni_MC_rho;
      if (Rel_deltaR3dPerp < 0.5 && Rel_deltaR3dPerp > 0.) hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel -> Fill (Rel_deltaR3dPerp);
      if (Rel_deltaR3dPerp >= 0.5 && MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dPerpendicularRel -> Fill(0.4999);

      double Rel_deltaR3dPar = -1.;
      if (ni_MC_rho > 0.) Rel_deltaR3dPar = MC_TrkV_associationPFDV_deltaR3dParallel->at(i)/ni_MC_rho;
      if (Rel_deltaR3dPar < 0.5 && Rel_deltaR3dPar > 0.) hMC_TrkV_associationPFDV_deltaR3dParallelRel -> Fill (Rel_deltaR3dPar);
      if (Rel_deltaR3dPar >= 0.5 && MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallelRel -> Fill(0.4999);

      hMC_TrkV_associationPFDVIdx -> Fill (MC_TrkV_associationPFDVIdx->at(i));


      if(fabs(ni_MC_z) <20)
      {
        if (MC_TrkV_associationPFDV_deltaR2d->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR2d_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR2d->at(i));
        else if (MC_TrkV_associationPFDV_deltaR2d->at(i) < 20.)hMC_TrkV_associationPFDV_deltaR2d_Barrel -> Fill (4.999);

        if (MC_TrkV_associationPFDV_deltaR3d->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3d_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3d->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3d->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3d_Barrel -> Fill(4.999);

        if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Barrel -> Fill(4.999);

        if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallel_Barrel -> Fill(4.999);


      }

      if(fabs(ni_MC_z) >20)
      {
        if (MC_TrkV_associationPFDV_deltaR3d->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3d_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3d->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3d->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3d_Forward -> Fill(4.999);

        if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3dPerpendicular->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dPerpendicular_Forward -> Fill(4.999);

        if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 5.) hMC_TrkV_associationPFDV_deltaR3dParallel_Forward -> Fill (MC_TrkV_associationPFDV_deltaR3dParallel->at(i));
        else if (MC_TrkV_associationPFDV_deltaR3dParallel->at(i) < 20.) hMC_TrkV_associationPFDV_deltaR3dParallel_Forward -> Fill(4.999);

      }
      
      //PIXEL region only 
      if(fabs(ni_MC_z) <20)
      {
        hMC_TrkV_R_Barrel->Fill( ni_MC_rho );
        if ( isMC_assosiated_PF ){
        hMC_TrkV_isAssociatedPF_Barrel -> Fill (1.);
        }
        else{
        hMC_TrkV_isAssociatedPF_Barrel -> Fill (0.);
        }
        
        hMC_TrkV_associationPFDVIdx_Barrel -> Fill (MC_TrkV_associationPFDVIdx->at(i));

        if ( MC_TrkV_isNuclearInteraction->at(i)){
        hMC_TrkV_isNuclearInteraction_Barrel -> Fill (1.);
        hMC_TrkV_R_isNuclearInteraction_Barrel->Fill( ni_MC_rho );
        hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel->Fill( ni_MC_rho );
          if ( isMC_assosiated_PF ){
            hMC_TrkV_R_isAssociatedPF_Barrel -> Fill ( ni_MC_rho );
            hMC_TrkV_R_isAssociatedPF_Rebin_Barrel -> Fill ( ni_MC_rho );
          }
        }
        else{
        hMC_TrkV_isNuclearInteraction_Barrel -> Fill (0.);
        }
        
        if ( MC_TrkV_numberOfChargedParticles_0p2->at(i) > 2){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p2->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p2 -> Fill ( ni_MC_rho );
            }
          }
        }
        if ( MC_TrkV_numberOfChargedParticles_0p5->at(i) > 2){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr0p5->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr0p5 -> Fill ( ni_MC_rho );
            }
          }
        }
        if ( MC_TrkV_numberOfChargedParticles_1p0->at(i) > 2){
          if ( MC_TrkV_isNuclearInteraction->at(i)){
          hMC_TrkV_R_isNuclearInteraction_Rebin_Barrel_3Tr1p0->Fill( ni_MC_rho );
            if ( isMC_assosiated_PF ){
               hMC_TrkV_R_isAssociatedPF_Rebin_Barrel_3Tr1p0 -> Fill ( ni_MC_rho );
            }
          }
        }


      }



    }
    //test for assosiation
    if(N_MCassociatePF > 1){ 
       std::cout << "size of MC_TrkV_associationPFDV_deltaR3dPerpendicular = " << MC_TrkV_associationPFDV_deltaR3dPerpendicular->size() << std::endl; 
       std::cout << "N_MCassociatePF per event = " << N_MCassociatePF << endl;
    }  
// end MC part

// start RECO part

    if (numberOfPV <= 0) continue; // reject events with 0 reco primary vertices
    if (numberOfPFDV >= 1){
    hPFDV_CountEventsWithNI->Fill(1.);
    }

    for ( unsigned int i = 0; i < numberOfPFDV; i++ )
    {
      
      ni_x = PFDV_x->at(i);
      ni_y = PFDV_y->at(i);
      ni_z = PFDV_z->at(i);
      ni_phi = TMath::ATan2( ni_y, ni_x );
      ni_rho = TMath::Sqrt( ni_x*ni_x + ni_y*ni_y );

      ni_z_i = floor( ni_z/5.0 );

    //  if(MC_TrkV_numberOfChargedParticles_0p2->at(i) > 1){
    //  hPFDV_vTrack_pt->Fill(PFDV_vTrack_pt->at(i));
    //  }

      hPFDV_numberOftracks_0p0->Fill(PFDV_numberOfTracks_0p0->at(i));
      hPFDV_numberOftracks_0p2->Fill(PFDV_numberOfTracks_0p2->at(i));
      hPFDV_numberOftracks_0p5->Fill(PFDV_numberOfTracks_0p5->at(i));
      hPFDV_numberOftracks_1p0->Fill(PFDV_numberOfTracks_1p0->at(i));

      hPFDV_R->Fill( ni_rho );

      hPFDV_R_Pipe->Fill( ni_rho );
      
      if ( fabs(ni_z) < 20 ) {
      hPFDV_R_BPix->Fill( ni_rho );
      }

      hPFDV_XY_Map->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map->Fill( ni_phi, ni_rho );

      hPFDV_XY_Map_BPix->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map_BPix->Fill( ni_phi, ni_rho );

      hPFDV_XY_Map_Pipe->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map_Pipe->Fill( ni_phi, ni_rho );

      hPFDV_ZR_Map->Fill( ni_z, ni_rho );

      hPFDV_deltaR2d_Associated->Fill(PFDV_deltaR2d_Associated->at(i));
      hPFDV_deltaR3d_Associated->Fill(PFDV_deltaR3d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Rebin->Fill(PFDV_deltaR3d_Associated->at(i));


      if ( fabs(ni_z) <20)
      {
      hPFDV_deltaR2d_Associated_Barrel->Fill(PFDV_deltaR2d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Barrel->Fill(PFDV_deltaR3d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Barrel_Rebin->Fill(PFDV_deltaR3d_Associated->at(i));
      }

      if ( fabs(ni_z) >20)
      {
      hPFDV_deltaR3d_Associated_Forward->Fill(PFDV_deltaR3d_Associated->at(i));
      hPFDV_deltaR3d_Associated_Forward_Rebin->Fill(PFDV_deltaR3d_Associated->at(i));
      }


      if ( PFDV_isAssociatedMC->at(i)){
      hPFDV_isAssociatedMC -> Fill (1.); 
      hPFDV_R_isAssociatedMC->Fill( ni_rho );
      }
      else{ 
      hPFDV_isAssociatedMC -> Fill (0.); 
      }

      if ( fabs(ni_z) <20)
      {
        hPFDV_associationMC_TrkVIdx_Barrel->Fill(PFDV_associationMC_TrkVIdx->at(i));
        if ( PFDV_isAssociatedMC->at(i)){
          if( PFDV_isNuclear->at(i)){
          hPFDV_isAssociatedMC_isNuclear_Barrel -> Fill (1.); 
          }
          else{
          hPFDV_isAssociatedMC_isNuclear_Barrel -> Fill (0.); 
          }
        hPFDV_isAssociatedMC_Barrel -> Fill (1.); 
        hPFDV_R_isAssociatedMC_Barrel->Fill( ni_rho );
        }
        else{
        hPFDV_isAssociatedMC_Barrel -> Fill (0.); 
        }
      }




//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_AbsZ25->Fill( ni_x, ni_y );
//        hPFDV_RhoPhi_Map_AbsZ25->Fill( ni_phi, ni_rho );
//
//        hPFDV_XY_Map_BPix_AbsZ25->Fill( ni_x, ni_y );
//        hPFDV_RhoPhi_Map_BPix_AbsZ25->Fill( ni_phi, ni_rho );
//
//        hPFDV_XY_Map_Pipe_AbsZ25->Fill( ni_x, ni_y );
//        hPFDV_RhoPhi_Map_Pipe_AbsZ25->Fill( ni_phi, ni_rho );
//
//        m_hPFDV_XY_Map.find( ni_z_i )->second->Fill( ni_x, ni_y );
//        m_hPFDV_RhoPhi_Map.find( ni_z_i )->second->Fill( ni_phi, ni_rho );
//
//        m_hPFDV_XY_Map_BPix.find( ni_z_i )->second->Fill( ni_x, ni_y );
//        m_hPFDV_RhoPhi_Map_BPix.find( ni_z_i )->second->Fill( ni_phi, ni_rho );
//
//        m_hPFDV_XY_Map_Pipe.find( ni_z_i )->second->Fill( ni_x, ni_y );
//        m_hPFDV_RhoPhi_Map_Pipe.find( ni_z_i )->second->Fill( ni_phi, ni_rho );
//      }
//
//      /// Correct for Beamspot Position
//      ni_x_c = ni_x - BS_x;
//      ni_y_c = ni_y - BS_y;
//      ni_phi_c = TMath::ATan2( ni_y_c, ni_x_c );
//      ni_rho_c = TMath::Sqrt( ni_x_c*ni_x_c + ni_y_c*ni_y_c );
//
//      hPFDV_XY_Map_Corr->Fill( ni_x_c, ni_y_c );
//      hPFDV_RhoPhi_Map_Corr->Fill( ni_phi_c, ni_rho_c );
//
//      hPFDV_XY_Map_Corr_BPix->Fill( ni_x_c, ni_y_c );
//      hPFDV_RhoPhi_Map_Corr_BPix->Fill( ni_phi_c, ni_rho_c );
//
//      hPFDV_XY_Map_Corr_Pipe->Fill( ni_x_c, ni_y_c );
//      hPFDV_RhoPhi_Map_Corr_Pipe->Fill( ni_phi_c, ni_rho_c );
//
//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_Corr_AbsZ25->Fill( ni_x_c, ni_y_c );
//        hPFDV_RhoPhi_Map_Corr_AbsZ25->Fill( ni_phi_c, ni_rho_c );
//
//        hPFDV_XY_Map_Corr_BPix_AbsZ25->Fill( ni_x_c, ni_y_c );
//        hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25->Fill( ni_phi_c, ni_rho_c );
//
//        hPFDV_XY_Map_Corr_Pipe_AbsZ25->Fill( ni_x_c, ni_y_c );
//        hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25->Fill( ni_phi_c, ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
//        m_hPFDV_RhoPhi_Map_Corr.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_BPix.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
//        m_hPFDV_RhoPhi_Map_Corr_BPix.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_Pipe.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
//        m_hPFDV_RhoPhi_Map_Corr_Pipe.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
//      }
//
//      /// Reweighted
//
//      hPFDV_XY_Map_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_BPix_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_BPix_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_Pipe_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Pipe_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_BPix_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_Pipe_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_BPix_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_BPix_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Pipe_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Pipe_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
//      }
//
//      hPFDV_XY_Map_Corr_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Corr_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_Corr_BPix_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Corr_BPix_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//      hPFDV_XY_Map_Corr_Pipe_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//      hPFDV_RhoPhi_Map_Corr_Pipe_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//      if ( fabs(ni_z) < 25 )
//      {
//        hPFDV_XY_Map_Corr_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Corr_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_BPix_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Corr_BPix_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//
//        m_hPFDV_XY_Map_Corr_Pipe_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
//        m_hPFDV_RhoPhi_Map_Corr_Pipe_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
//      }

    }

  } /// End of loop over events
      cout<<"number of events with NI = "<<hPFDV_CountEventsWithNI->Integral()<<endl;
      cout<<"number of NI events = "<<hPFDV_XY_Map->Integral()<<endl;

}



/* End Job (close output files) */
void NtupleReaderNuclearInteractions_2015::endJob()
{
//  outputFile->Close();





}

#endif

