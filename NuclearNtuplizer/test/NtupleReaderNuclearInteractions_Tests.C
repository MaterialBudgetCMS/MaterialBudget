#ifndef NtupleReaderNuclearInteractions_MaterialBudget_cxx
#define NtupleReaderNuclearInteractions_MaterialBudget_cxx

/* ****************************************** */
/*                                            */
/* Tracker Material with Nuclear Interactions */
/*                                            */
/*               Nicola Pozzobon              */
/*                    2013                    */
/*                                            */
/* ****************************************** */

#include "NtupleReaderNuclearInteractions_MaterialBudget.h"

/* Constructor (file opening and tree loading) */
NtupleReaderNuclearInteractions_MaterialBudget::NtupleReaderNuclearInteractions_MaterialBudget( const std::string fileList, const Long64_t maxEvents )
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
NtupleReaderNuclearInteractions_MaterialBudget::~NtupleReaderNuclearInteractions_MaterialBudget()
{
  outputFile->Write();
  outputFile->Close();
  delete inputChain->GetCurrentFile();
}

/* Begin Job (tree initialization) */
void NtupleReaderNuclearInteractions_MaterialBudget::beginJob()
{
  /// Initialize all branches
  std::string warningString_Branches = "W A R N I N G! Variable is missing from the ntuple! Trying to use it will result in a crash!";

  /// General
  if ( inputChain->GetBranchStatus( "isRealData" ) )
    inputChain->SetBranchAddress( "isRealData", &isRealData, &b_isRealData );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "runNumber" ) )
    inputChain->SetBranchAddress( "runNumber", &runNumber, &b_runNumber );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "eventNumber" ) )
    inputChain->SetBranchAddress( "eventNumber", &eventNumber, &b_eventNumber );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "lumiSection" ) )
    inputChain->SetBranchAddress( "lumiSection", &lumiSection, &b_lumiSection );
  else std::cout << warningString_Branches.data() << std::endl;

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
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_x" ) )
    inputChain->SetBranchAddress( "PV_x", &PV_x, &b_PV_x );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_y" ) )
    inputChain->SetBranchAddress( "PV_y", &PV_y, &b_PV_y );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_z" ) )
    inputChain->SetBranchAddress( "PV_z", &PV_z, &b_PV_z );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_xError" ) )
    inputChain->SetBranchAddress( "PV_xError", &PV_xError, &b_PV_xError );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_yError" ) )
    inputChain->SetBranchAddress( "PV_yError", &PV_yError, &b_PV_yError );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_zError" ) )
    inputChain->SetBranchAddress( "PV_zError", &PV_zError, &b_PV_zError );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PV_isFake" ) )
    inputChain->SetBranchAddress( "PV_isFake", &PV_isFake, &b_PV_isFake );
  else std::cout << warningString_Branches.data() << std::endl;

  /// MC PileUp
  MC_PUInfo_bunchCrossing = new std::vector< unsigned int >();
  MC_PUInfo_numberOfInteractions = new std::vector< unsigned int >();

  if ( inputChain->GetBranchStatus( "numberOfMC_PUInfo" ) )
    inputChain->SetBranchAddress( "numberOfMC_PUInfo", &numberOfMC_PUInfo, &b_numberOfMC_PUInfo );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_PUInfo_bunchCrossing" ) )
    inputChain->SetBranchAddress( "MC_PUInfo_bunchCrossing", &MC_PUInfo_bunchCrossing, &b_MC_PUInfo_bunchCrossing );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_PUInfo_numberOfInteractions" ) )
    inputChain->SetBranchAddress( "MC_PUInfo_numberOfInteractions", &MC_PUInfo_numberOfInteractions, &b_MC_PUInfo_numberOfInteractions );
  else std::cout << warningString_Branches.data() << std::endl;

  /// BeamSpot
  if ( inputChain->GetBranchStatus( "BS_x" ) )
    inputChain->SetBranchAddress( "BS_x", &BS_x, &b_BS_x );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_y" ) )
    inputChain->SetBranchAddress( "BS_y", &BS_y, &b_BS_y );
  else std::cout << warningString_Branches.data() << std::endl;
    if ( inputChain->GetBranchStatus( "BS_z" ) )
    inputChain->SetBranchAddress( "BS_z", &BS_z, &b_BS_z );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_zSigma" ) )
    inputChain->SetBranchAddress( "BS_zSigma", &BS_zSigma, &b_BS_zSigma );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_dxdy" ) )
    inputChain->SetBranchAddress( "BS_dxdy", &BS_dxdy, &b_BS_dxdy );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_dydz" ) )
    inputChain->SetBranchAddress( "BS_dydz", &BS_dydz, &b_BS_dydz );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_xWidth" ) )
    inputChain->SetBranchAddress( "BS_xWidth", &BS_xWidth, &b_BS_xWidth );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "BS_yWidth" ) )
    inputChain->SetBranchAddress( "BS_yWidth", &BS_yWidth, &b_BS_yWidth );
  else std::cout << warningString_Branches.data() << std::endl;

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
  MC_TrkV_momentumOut_numberOfParticles = new std::vector< unsigned int >();
  MC_TrkV_isAssociatedPF = new std::vector< bool >();
  MC_TrkV_associationPFDVIdx = new std::vector< unsigned int >();

  if ( inputChain->GetBranchStatus( "numberOfMC_TrkV" ) )
    inputChain->SetBranchAddress( "numberOfMC_TrkV", &numberOfMC_TrkV, &b_numberOfMC_TrkV );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isNuclearInteraction" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isNuclearInteraction", &MC_TrkV_isNuclearInteraction, &b_MC_TrkV_isNuclearInteraction );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isKaonDecay" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isKaonDecay", &MC_TrkV_isKaonDecay, &b_MC_TrkV_isKaonDecay );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isConversion" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isConversion", &MC_TrkV_isConversion, &b_MC_TrkV_isConversion );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_x" ) )
    inputChain->SetBranchAddress( "MC_TrkV_x", &MC_TrkV_x, &b_MC_TrkV_x );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_y" ) )
    inputChain->SetBranchAddress( "MC_TrkV_y", &MC_TrkV_y, &b_MC_TrkV_y );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_z" ) )
    inputChain->SetBranchAddress( "MC_TrkV_z", &MC_TrkV_z, &b_MC_TrkV_z );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumInc_pt" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumInc_pt", &MC_TrkV_momentumInc_pt, &b_MC_TrkV_momentumInc_pt );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumInc_theta" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumInc_theta", &MC_TrkV_momentumInc_theta, &b_MC_TrkV_momentumInc_theta );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumInc_phi" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumInc_phi", &MC_TrkV_momentumInc_phi, &b_MC_TrkV_momentumInc_phi );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_pt" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_pt", &MC_TrkV_momentumOut_pt, &b_MC_TrkV_momentumOut_pt );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_phi" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_phi", &MC_TrkV_momentumOut_phi, &b_MC_TrkV_momentumOut_phi );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_theta" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_theta", &MC_TrkV_momentumOut_theta, &b_MC_TrkV_momentumOut_theta );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_mass" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_mass", &MC_TrkV_momentumOut_mass, &b_MC_TrkV_momentumOut_mass );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_momentumOut_numberOfParticles" ) )
    inputChain->SetBranchAddress( "MC_TrkV_momentumOut_numberOfParticles", &MC_TrkV_momentumOut_numberOfParticles, &b_MC_TrkV_momentumOut_numberOfParticles );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_isAssociatedPF" ) )
    inputChain->SetBranchAddress( "MC_TrkV_isAssociatedPF", &MC_TrkV_isAssociatedPF, &b_MC_TrkV_isAssociatedPF );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "MC_TrkV_associationPFDVIdx" ) )
    inputChain->SetBranchAddress( "MC_TrkV_associationPFDVIdx", &MC_TrkV_associationPFDVIdx, &b_MC_TrkV_associationPFDVIdx );
  else std::cout << warningString_Branches.data() << std::endl;

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
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_x" ) )
    inputChain->SetBranchAddress( "PFDV_x", &PFDV_x, &b_PFDV_x );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_y" ) )
    inputChain->SetBranchAddress( "PFDV_y", &PFDV_y, &b_PFDV_y );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_z" ) )
    inputChain->SetBranchAddress( "PFDV_z", &PFDV_z, &b_PFDV_z );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumInc_pt" ) )
    inputChain->SetBranchAddress( "PFDV_momentumInc_pt", &PFDV_momentumInc_pt, &b_PFDV_momentumInc_pt );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumInc_theta" ) )
    inputChain->SetBranchAddress( "PFDV_momentumInc_theta", &PFDV_momentumInc_theta, &b_PFDV_momentumInc_theta );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumInc_phi" ) )
    inputChain->SetBranchAddress( "PFDV_momentumInc_phi", &PFDV_momentumInc_phi, &b_PFDV_momentumInc_phi );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_pt" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_pt", &PFDV_momentumOut_pt, &b_PFDV_momentumOut_pt );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_phi" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_phi", &PFDV_momentumOut_phi, &b_PFDV_momentumOut_phi );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_theta" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_theta", &PFDV_momentumOut_theta, &b_PFDV_momentumOut_theta );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_mass" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_mass", &PFDV_momentumOut_mass, &b_PFDV_momentumOut_mass );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_momentumOut_numberOfTracks" ) )
    inputChain->SetBranchAddress( "PFDV_momentumOut_numberOfTracks", &PFDV_momentumOut_numberOfTracks, &b_PFDV_momentumOut_numberOfTracks );
  if ( inputChain->GetBranchStatus( "PFDV_isNuclear" ) )
    inputChain->SetBranchAddress( "PFDV_isNuclear", &PFDV_isNuclear, &b_PFDV_isNuclear );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isNuclearLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isNuclearLoose", &PFDV_isNuclearLoose, &b_PFDV_isNuclearLoose );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isNuclearKink" ) )
    inputChain->SetBranchAddress( "PFDV_isNuclearKink", &PFDV_isNuclearKink, &b_PFDV_isNuclearKink );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isK0" ) )
    inputChain->SetBranchAddress( "PFDV_isK0", &PFDV_isK0, &b_PFDV_isK0 );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isLambda" ) )
    inputChain->SetBranchAddress( "PFDV_isLambda", &PFDV_isLambda, &b_PFDV_isLambda );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isLambdaBar" ) )
    inputChain->SetBranchAddress( "PFDV_isLambdaBar", &PFDV_isLambdaBar, &b_PFDV_isLambdaBar );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isKPlusLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isKPlusLoose", &PFDV_isKPlusLoose, &b_PFDV_isKPlusLoose );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isKMinusLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isKMinusLoose", &PFDV_isKMinusLoose, &b_PFDV_isKMinusLoose );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isConversionLoose" ) )
    inputChain->SetBranchAddress( "PFDV_isConversionLoose", &PFDV_isConversionLoose, &b_PFDV_isConversionLoose );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isLooper" ) )
    inputChain->SetBranchAddress( "PFDV_isLooper", &PFDV_isLooper, &b_PFDV_isLooper );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isFake" ) )
    inputChain->SetBranchAddress( "PFDV_isFake", &PFDV_isFake, &b_PFDV_isFake );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isTherePrimaryTrack" ) )
    inputChain->SetBranchAddress( "PFDV_isTherePrimaryTrack", &PFDV_isTherePrimaryTrack, &b_PFDV_isTherePrimaryTrack );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isThereMergedTrack" ) )
    inputChain->SetBranchAddress( "PFDV_isThereMergedTrack", &PFDV_isThereMergedTrack, &b_PFDV_isThereMergedTrack );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_isAssociatedMC" ) )
    inputChain->SetBranchAddress( "PFDV_isAssociatedMC", &PFDV_isAssociatedMC, &b_PFDV_isAssociatedMC );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_associationMC_TrkVIdx" ) )
    inputChain->SetBranchAddress( "PFDV_associationMC_TrkVIdx", &PFDV_associationMC_TrkVIdx, &b_PFDV_associationMC_TrkVIdx );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_pt" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_pt", &PFDV_vTrack_pt, &b_PFDV_vTrack_pt );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_phi" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_phi", &PFDV_vTrack_phi, &b_PFDV_vTrack_phi );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_eta" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_eta", &PFDV_vTrack_eta, &b_PFDV_vTrack_eta );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_rho" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_rho", &PFDV_vTrack_rho, &b_PFDV_vTrack_rho );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_numberOfValidHits" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_numberOfValidHits", &PFDV_vTrack_numberOfValidHits, &b_PFDV_vTrack_numberOfValidHits );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_numberOfExpectedOuterHits" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_numberOfExpectedOuterHits", &PFDV_vTrack_numberOfExpectedOuterHits, &b_PFDV_vTrack_numberOfExpectedOuterHits );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDxyPVIdx" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDxyPVIdx", &PFDV_vTrack_closestDxyPVIdx, &b_PFDV_vTrack_closestDxyPVIdx );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDxyPVIdx_dxy" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDxyPVIdx_dxy", &PFDV_vTrack_closestDxyPVIdx_dxy, &b_PFDV_vTrack_closestDxyPVIdx_dxy );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDxyPVIdx_dz" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDxyPVIdx_dz", &PFDV_vTrack_closestDxyPVIdx_dz, &b_PFDV_vTrack_closestDxyPVIdx_dz );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDzPVIdx" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDzPVIdx", &PFDV_vTrack_closestDzPVIdx, &b_PFDV_vTrack_closestDzPVIdx );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDzPVIdx_dxy" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDzPVIdx_dxy", &PFDV_vTrack_closestDzPVIdx_dxy, &b_PFDV_vTrack_closestDzPVIdx_dxy );
  else std::cout << warningString_Branches.data() << std::endl;
  if ( inputChain->GetBranchStatus( "PFDV_vTrack_closestDzPVIdx_dz" ) )
    inputChain->SetBranchAddress( "PFDV_vTrack_closestDzPVIdx_dz", &PFDV_vTrack_closestDzPVIdx_dz, &b_PFDV_vTrack_closestDzPVIdx_dz );
  else std::cout << warningString_Branches.data() << std::endl;



  inputChain->SetBranchStatus("*",0);
  inputChain->SetBranchStatus( "numberOfPFDV",1);
  inputChain->SetBranchStatus( "PFDV_x",1);
  inputChain->SetBranchStatus( "PFDV_y",1);
  inputChain->SetBranchStatus( "PFDV_z",1);
  //inputChain->SetBranchStatus( "PFDV_momentumInc_pt",1);
  //inputChain->SetBranchStatus( "PFDV_momentumOut_pt",1);
  //inputChain->SetBranchStatus( "PFDV_momentumOut_phi",1);
  //inputChain->SetBranchStatus( "PFDV_momentumOut_theta",1);
  //inputChain->SetBranchStatus( "PFDV_momentumOut_mass",1);
  inputChain->SetBranchStatus( "PFDV_momentumOut_numberOfTracks",1);
  inputChain->SetBranchStatus( "PFDV_isNuclear",1);
  inputChain->SetBranchStatus( "PFDV_vTrack_closestDzPVIdx_dxy",1);
  inputChain->SetBranchStatus( "PFDV_vTrack_closestDzPVIdx_dz",1);
  inputChain->SetBranchStatus( "PFDV_vTrack_eta",1);
  inputChain->SetBranchStatus( "PFDV_vTrack_phi",1);


  /// Output histograms and graphs etc
/*
  hPFDV_XY_Map = new TH2D( "hPFDV_XY_Map", "N.I. in Tracker", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map = new TH2D( "hPFDV_RhoPhi_Map", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map->Sumw2();
  hPFDV_RhoPhi_Map->Sumw2();

  hPFDV_XY_Map_BPix = new TH2D( "hPFDV_XY_Map_BPix", "N.I. in Tracker", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_BPix = new TH2D( "hPFDV_RhoPhi_Map_BPix", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_BPix->Sumw2();
  hPFDV_RhoPhi_Map_BPix->Sumw2();

  hPFDV_XY_Map_Pipe = new TH2D( "hPFDV_XY_Map_Pipe", "N.I. in Tracker", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe = new TH2D( "hPFDV_RhoPhi_Map_Pipe", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Pipe->Sumw2();
  hPFDV_RhoPhi_Map_Pipe->Sumw2();

  hPFDV_XY_Map_Corr = new TH2D( "hPFDV_XY_Map_Corr", "N.I. in Tracker, BS Corr", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_Corr = new TH2D( "hPFDV_RhoPhi_Map_Corr", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_Corr->Sumw2();
  hPFDV_RhoPhi_Map_Corr->Sumw2();

  hPFDV_XY_Map_Corr_BPix = new TH2D( "hPFDV_XY_Map_Corr_BPix", "N.I. in Tracker, BS Corr", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_Corr_BPix = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_Corr_BPix->Sumw2();
  hPFDV_RhoPhi_Map_Corr_BPix->Sumw2();

  hPFDV_XY_Map_Corr_Pipe = new TH2D( "hPFDV_XY_Map_Corr_Pipe", "N.I. in Tracker, BS Corr", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Corr_Pipe = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Corr_Pipe->Sumw2();
  hPFDV_RhoPhi_Map_Corr_Pipe->Sumw2();

  /// BPix length only
  hPFDV_XY_Map_AbsZ25 = new TH2D( "hPFDV_XY_Map_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_AbsZ25->Sumw2();
  hPFDV_RhoPhi_Map_AbsZ25->Sumw2();

  hPFDV_XY_Map_BPix_AbsZ25 = new TH2D( "hPFDV_XY_Map_BPix_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_BPix_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_BPix_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_BPix_AbsZ25->Sumw2();
  hPFDV_RhoPhi_Map_BPix_AbsZ25->Sumw2();

  hPFDV_XY_Map_Pipe_AbsZ25 = new TH2D( "hPFDV_XY_Map_Pipe_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Pipe_AbsZ25", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Pipe_AbsZ25->Sumw2();
  hPFDV_RhoPhi_Map_Pipe_AbsZ25->Sumw2();

  hPFDV_XY_Map_Corr_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_Corr_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_Corr_AbsZ25->Sumw2();
  hPFDV_RhoPhi_Map_Corr_AbsZ25->Sumw2();

  hPFDV_XY_Map_Corr_BPix_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_BPix_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_Corr_BPix_AbsZ25->Sumw2();
  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25->Sumw2();

  hPFDV_XY_Map_Corr_Pipe_AbsZ25 = new TH2D( "hPFDV_XY_Map_Corr_Pipe_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25 = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Corr_Pipe_AbsZ25->Sumw2();
  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25->Sumw2();

  /// Reweighted
  hPFDV_XY_Map_Weight = new TH2D( "hPFDV_XY_Map_Weight", "N.I. in Tracker", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_Weight = new TH2D( "hPFDV_RhoPhi_Map_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Weight->Sumw2();

  hPFDV_XY_Map_BPix_Weight = new TH2D( "hPFDV_XY_Map_BPix_Weight", "N.I. in Tracker", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_BPix_Weight = new TH2D( "hPFDV_RhoPhi_Map_BPix_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_BPix_Weight->Sumw2();
  hPFDV_RhoPhi_Map_BPix_Weight->Sumw2();

  hPFDV_XY_Map_Pipe_Weight = new TH2D( "hPFDV_XY_Map_Pipe_Weight", "N.I. in Tracker", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe_Weight = new TH2D( "hPFDV_RhoPhi_Map_Pipe_Weight", "N.I. in Tracker", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Pipe_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Pipe_Weight->Sumw2();

  hPFDV_XY_Map_Corr_Weight = new TH2D( "hPFDV_XY_Map_Corr_Weight", "N.I. in Tracker, BS Corr", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_Corr_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_Corr_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Corr_Weight->Sumw2();

  hPFDV_XY_Map_Corr_BPix_Weight = new TH2D( "hPFDV_XY_Map_Corr_BPix_Weight", "N.I. in Tracker, BS Corr", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_Corr_BPix_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_Corr_BPix_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Corr_BPix_Weight->Sumw2();

  hPFDV_XY_Map_Corr_Pipe_Weight = new TH2D( "hPFDV_XY_Map_Corr_Pipe_Weight", "N.I. in Tracker, BS Corr", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Corr_Pipe_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_Weight", "N.I. in Tracker, BS Corr", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Corr_Pipe_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Corr_Pipe_Weight->Sumw2();

  hPFDV_XY_Map_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_AbsZ25_Weight->Sumw2();
  hPFDV_RhoPhi_Map_AbsZ25_Weight->Sumw2();

  hPFDV_XY_Map_BPix_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_BPix_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_BPix_AbsZ25_Weight->Sumw2();
  hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight->Sumw2();

  hPFDV_XY_Map_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Pipe_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight", "N.I. in Tracker, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Pipe_AbsZ25_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight->Sumw2();

  hPFDV_XY_Map_Corr_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -100, 100, 1000, -100, 100 );
  hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
  hPFDV_XY_Map_Corr_AbsZ25_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight->Sumw2();

  hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -25, 25, 1000, -25, 25 );
  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
  hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight->Sumw2();

  hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 1000, -5, 5, 1000, -5, 5 );
  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight = new TH2D( "hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight", "N.I. in Tracker, BS Corr, |z| < 25 cm", 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
  hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight->Sumw2();
  hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight->Sumw2();

  std::ostringstream histoName;
  std::ostringstream histoTitle;

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
    h1->Sumw2();
    m_hPFDV_XY_Map.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
    m_hPFDV_RhoPhi_Map.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_BPix_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
    h1->Sumw2();
    m_hPFDV_XY_Map_BPix.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_BPix_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
    m_hPFDV_RhoPhi_Map_BPix.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Pipe_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Pipe.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Pipe_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
    m_hPFDV_RhoPhi_Map_Pipe.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Corr_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Corr.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Corr_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
    m_hPFDV_RhoPhi_Map_Corr.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Corr_BPix.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
    m_hPFDV_RhoPhi_Map_Corr_BPix.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5;
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Corr_Pipe.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5;
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
    m_hPFDV_RhoPhi_Map_Corr_Pipe.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  /// Reweighted
  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_" << k*5 << "_" << (k+1)*5 << "_Weight";
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_" << k*5 << "_" << (k+1)*5 << "_Weight";
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
    m_hPFDV_RhoPhi_Map_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
    h1->Sumw2();
    m_hPFDV_XY_Map_BPix_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
    m_hPFDV_RhoPhi_Map_BPix_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
    m_hPFDV_RhoPhi_Map_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Corr_" << k*5 << "_" << (k+1)*5 << "_Weight";
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -100, 100, 1000, -100, 100 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Corr_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Corr_" << k*5 << "_" << (k+1)*5 << "_Weight";
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 100 );
    m_hPFDV_RhoPhi_Map_Corr_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -25, 25, 1000, -25, 25 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Corr_BPix_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Corr_BPix_" << k*5 << "_" << (k+1)*5 << "_Weight";
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 25 );
    m_hPFDV_RhoPhi_Map_Corr_BPix_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
  }

  for ( int k = -5; k < 5; k++ )
  {
    histoName.str("");
    histoTitle.str("");
    histoName << "hPFDV_XY_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
    histoTitle << "N.I. in Tracker, " << k*5 << " (cm) <= z < " << (k+1)*5 << " (cm)";
    TH2D* h1 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 1000, -5, 5, 1000, -5, 5 );
    h1->Sumw2();
    m_hPFDV_XY_Map_Corr_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h1 ) );
    histoName.str("");
    histoName << "hPFDV_RhoPhi_Map_Corr_Pipe_" << k*5 << "_" << (k+1)*5 << "_Weight";
    TH2D* h2 = new TH2D( histoName.str().c_str(), histoTitle.str().c_str(), 400, -TMath::Pi(), TMath::Pi(), 500, 0, 5 );
    m_hPFDV_RhoPhi_Map_Corr_Pipe_Weight.insert( std::pair<int, TH2D*>( k, h2 ) );
  }
*/

  hPFDVTracks_dxy_PFDV_Rho = new TH2D( "hPFDVTracks_dxy_PFDV_Rho", "Track IP vs. NI #rho", 200, 0, 50, 200, 0, 10 );
  hPFDVTracks_dxy_PFDV_Rho->Sumw2();

  hPFDVTracks_DR_PFDV_Rho = new TH2D( "hPFDVTracks_DR_PFDV_Rho", "DeltaR between tracks vs. NI #rho", 200, 0, 50, 200, 0, 5 );
  hPFDVTracks_DR_PFDV_Rho->Sumw2();
}



/* Analyze (loop over tree entries) */
void NtupleReaderNuclearInteractions_MaterialBudget::analyze()
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
    double tk_dxy;

    for ( unsigned int i = 0; i < numberOfPFDV; i++ )
    {

      if ( PFDV_isNuclear->at(i) == false ) continue;

      ni_x = PFDV_x->at(i);
      ni_y = PFDV_y->at(i);
      ni_z = PFDV_z->at(i);
      ni_phi = TMath::ATan2( ni_y, ni_x );
      ni_rho = TMath::Sqrt( ni_x*ni_x + ni_y*ni_y );

      ni_z_i = floor( ni_z/5.0 );

      for ( unsigned int j = 0; j < PFDV_vTrack_closestDzPVIdx_dxy->at(i).size(); j++ )
      {
        tk_dxy = PFDV_vTrack_closestDzPVIdx_dxy->at(i).at(j);

        hPFDVTracks_dxy_PFDV_Rho->Fill( ni_rho, tk_dxy );

        for ( unsigned int k = j+1; k < PFDV_vTrack_closestDzPVIdx_dxy->at(i).size(); k++ )
        {
          double deltaPhi = PFDV_vTrack_phi->at(i).at(j) - PFDV_vTrack_phi->at(i).at(k);
          if ( fabs(deltaPhi) >= M_PI )
          {
            if ( deltaPhi>0 )
              deltaPhi = deltaPhi - 2*M_PI;
            else
              deltaPhi = 2*M_PI + deltaPhi;
          }
          deltaPhi = fabs( deltaPhi );
          double deltaEta = fabs( PFDV_vTrack_eta->at(i).at(j) - PFDV_vTrack_eta->at(i).at(k) );
          double deltaR = sqrt( deltaPhi*deltaPhi + deltaEta*deltaEta );

          hPFDVTracks_DR_PFDV_Rho->Fill( ni_rho, deltaR );
        }

      }




/*
      hPFDV_XY_Map->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map->Fill( ni_phi, ni_rho );

      hPFDV_XY_Map_BPix->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map_BPix->Fill( ni_phi, ni_rho );

      hPFDV_XY_Map_Pipe->Fill( ni_x, ni_y );
      hPFDV_RhoPhi_Map_Pipe->Fill( ni_phi, ni_rho );

      if ( fabs(ni_z) < 25 )
      {
        hPFDV_XY_Map_AbsZ25->Fill( ni_x, ni_y );
        hPFDV_RhoPhi_Map_AbsZ25->Fill( ni_phi, ni_rho );

        hPFDV_XY_Map_BPix_AbsZ25->Fill( ni_x, ni_y );
        hPFDV_RhoPhi_Map_BPix_AbsZ25->Fill( ni_phi, ni_rho );

        hPFDV_XY_Map_Pipe_AbsZ25->Fill( ni_x, ni_y );
        hPFDV_RhoPhi_Map_Pipe_AbsZ25->Fill( ni_phi, ni_rho );

        m_hPFDV_XY_Map.find( ni_z_i )->second->Fill( ni_x, ni_y );
        m_hPFDV_RhoPhi_Map.find( ni_z_i )->second->Fill( ni_phi, ni_rho );

        m_hPFDV_XY_Map_BPix.find( ni_z_i )->second->Fill( ni_x, ni_y );
        m_hPFDV_RhoPhi_Map_BPix.find( ni_z_i )->second->Fill( ni_phi, ni_rho );

        m_hPFDV_XY_Map_Pipe.find( ni_z_i )->second->Fill( ni_x, ni_y );
        m_hPFDV_RhoPhi_Map_Pipe.find( ni_z_i )->second->Fill( ni_phi, ni_rho );
      }

      /// Correct for Beamspot Position
      ni_x_c = ni_x - BS_x;
      ni_y_c = ni_y - BS_y;
      ni_phi_c = TMath::ATan2( ni_y_c, ni_x_c );
      ni_rho_c = TMath::Sqrt( ni_x_c*ni_x_c + ni_y_c*ni_y_c );

      hPFDV_XY_Map_Corr->Fill( ni_x_c, ni_y_c );
      hPFDV_RhoPhi_Map_Corr->Fill( ni_phi_c, ni_rho_c );

      hPFDV_XY_Map_Corr_BPix->Fill( ni_x_c, ni_y_c );
      hPFDV_RhoPhi_Map_Corr_BPix->Fill( ni_phi_c, ni_rho_c );

      hPFDV_XY_Map_Corr_Pipe->Fill( ni_x_c, ni_y_c );
      hPFDV_RhoPhi_Map_Corr_Pipe->Fill( ni_phi_c, ni_rho_c );

      if ( fabs(ni_z) < 25 )
      {
        hPFDV_XY_Map_Corr_AbsZ25->Fill( ni_x_c, ni_y_c );
        hPFDV_RhoPhi_Map_Corr_AbsZ25->Fill( ni_phi_c, ni_rho_c );

        hPFDV_XY_Map_Corr_BPix_AbsZ25->Fill( ni_x_c, ni_y_c );
        hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25->Fill( ni_phi_c, ni_rho_c );

        hPFDV_XY_Map_Corr_Pipe_AbsZ25->Fill( ni_x_c, ni_y_c );
        hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25->Fill( ni_phi_c, ni_rho_c );

        m_hPFDV_XY_Map_Corr.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
        m_hPFDV_RhoPhi_Map_Corr.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );

        m_hPFDV_XY_Map_Corr_BPix.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
        m_hPFDV_RhoPhi_Map_Corr_BPix.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );

        m_hPFDV_XY_Map_Corr_Pipe.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c );
        m_hPFDV_RhoPhi_Map_Corr_Pipe.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c );
      }

      /// Reweighted

      hPFDV_XY_Map_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
      hPFDV_RhoPhi_Map_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

      hPFDV_XY_Map_BPix_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
      hPFDV_RhoPhi_Map_BPix_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

      hPFDV_XY_Map_Pipe_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
      hPFDV_RhoPhi_Map_Pipe_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

      if ( fabs(ni_z) < 25 )
      {
        hPFDV_XY_Map_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
        hPFDV_RhoPhi_Map_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

        hPFDV_XY_Map_BPix_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
        hPFDV_RhoPhi_Map_BPix_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

        hPFDV_XY_Map_Pipe_AbsZ25_Weight->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
        hPFDV_RhoPhi_Map_Pipe_AbsZ25_Weight->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

        m_hPFDV_XY_Map_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
        m_hPFDV_RhoPhi_Map_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

        m_hPFDV_XY_Map_BPix_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
        m_hPFDV_RhoPhi_Map_BPix_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );

        m_hPFDV_XY_Map_Pipe_Weight.find( ni_z_i )->second->Fill( ni_x, ni_y, ni_rho_c*ni_rho_c );
        m_hPFDV_RhoPhi_Map_Pipe_Weight.find( ni_z_i )->second->Fill( ni_phi, ni_rho, ni_rho_c*ni_rho_c );
      }

      hPFDV_XY_Map_Corr_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
      hPFDV_RhoPhi_Map_Corr_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

      hPFDV_XY_Map_Corr_BPix_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
      hPFDV_RhoPhi_Map_Corr_BPix_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

      hPFDV_XY_Map_Corr_Pipe_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
      hPFDV_RhoPhi_Map_Corr_Pipe_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

      if ( fabs(ni_z) < 25 )
      {
        hPFDV_XY_Map_Corr_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
        hPFDV_RhoPhi_Map_Corr_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

        hPFDV_XY_Map_Corr_BPix_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
        hPFDV_RhoPhi_Map_Corr_BPix_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

        hPFDV_XY_Map_Corr_Pipe_AbsZ25_Weight->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
        hPFDV_RhoPhi_Map_Corr_Pipe_AbsZ25_Weight->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

        m_hPFDV_XY_Map_Corr_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
        m_hPFDV_RhoPhi_Map_Corr_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

        m_hPFDV_XY_Map_Corr_BPix_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
        m_hPFDV_RhoPhi_Map_Corr_BPix_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );

        m_hPFDV_XY_Map_Corr_Pipe_Weight.find( ni_z_i )->second->Fill( ni_x_c, ni_y_c, ni_rho_c*ni_rho_c );
        m_hPFDV_RhoPhi_Map_Corr_Pipe_Weight.find( ni_z_i )->second->Fill( ni_phi_c, ni_rho_c, ni_rho_c*ni_rho_c );
      }
*/

    }

  } /// End of loop over events

}

/* End Job (close output files) */
void NtupleReaderNuclearInteractions_MaterialBudget::endJob()
{
//  outputFile->Close();


}

#endif

