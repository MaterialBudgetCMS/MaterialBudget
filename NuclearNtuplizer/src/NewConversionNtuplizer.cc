// -*- C++ -*-
//
// Package:    NewConversionNtuplizer
// Class:      NewConversionNtuplizer
// 
/**\class NewConversionNtuplizer NewConversionNtuplizer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Giuseppe Cerati
// reorganized by:   Domenico Giordano
//         Created:  Wed Aug 19 15:39:10 CEST 2009
// $Id: NewConversionNtuplizer.cc,v 1.13 2012/02/14 10:52:48 dinardo Exp $
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "FWCore/ParameterSet/interface/InputTag.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/BoundDisk.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"
#include "DataFormats/GeometrySurface/interface/SimpleDiskBounds.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GeomDetUnit.h"
#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "TrackingTools/MaterialEffects/interface/PropagatorWithMaterial.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/ColinearityKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"

#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruthFinder.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruthFinder.h"
#include "RecoEgamma/EgammaMCTools/interface/PhotonMCTruth.h"
#include "RecoEgamma/EgammaMCTools/interface/ElectronMCTruth.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimTracker/TrackAssociation/interface/TrackAssociatorBase.h"
#include "DataFormats/Common/interface/RefToBaseVector.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h" 
#include "TrackingTools/Records/interface/TrackingComponentsRecord.h" 
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateOnSurface.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"

#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "TrackingTools/PatternTools/interface/TwoTrackMinimumDistance.h"
#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"

#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TTree.h>


using namespace std;
using namespace edm;
using namespace reco;

//
// class declaration
//

typedef struct {
  int run, event;
  unsigned int lumi;

  //Track counters
  int nCkf, n1Tk, nGsf, nCkfInOut, nCkfOutIn, nRecoConv, nPrimVtx;

  void init(){
    run=0;
    event=0;
    lumi=0;
    nCkf=0;
    n1Tk=0;
    nGsf=0;
    nCkfInOut=0;
    nCkfOutIn=0;
    nRecoConv=0;
    nPrimVtx=0;
  }
} EVT;


typedef struct{
  int algo;  
  int q;
  float pt, phi, theta;
  float px, py, pz;
  float r;
  float chi2, d0, dz;
  float x, y, z;
  float mass;//photon invariant mass by conv->mass()

  void init(){
    q = -999;
    pt = -999,  phi = -999,  theta = -999;
    px = -999,  py = -999,  pz = -999;
    r = -999; //Not meangiful in particle
    chi2 = -999,  d0 = -999,  dz = -999;
    x = -999,  y = -999,  z = -999; //Not meaningful in particle
    algo = -999;
    mass = -999;//photon invariant mass by conv->mass()
  }
} PARTICLEDATA;

typedef struct{

  int nHits;
  int missHits;//missed hits
  int npHits;//pixel hits
  int nsHits;//strip stereo hits
  int beforeHits;//num of hits before vertex
  float lambdaError;

  void init(){
    nHits = -999;
    missHits = -999;//missed hits
    npHits = -999;//pixel hits
    nsHits = -999;//strip stereo hits
    beforeHits = -999;//num of hits before vertex
    lambdaError = -999;
  }
} PARTICLEEXTRA;

typedef struct { 
  int isAssoc, isDouble;
  float x, y, z;
  //float r, perp, theta, phi
  float deltapt, deltaphi, deltatheta, deltax, deltay, deltaz;
  float minapp, chi2;
  float chi2prob;
  int   refit;
  float tx, ty, tz;//track analytical X

  void init(){
    isAssoc=0;
    isDouble=0;
    x=-999; y=-999; z=-999; 
    //    deltapt=-999; deltaphi=-999; deltatheta=-999; deltax=-999; deltay=-999; deltaz=-999;
    deltapt=0.; deltaphi=0.; deltatheta=0.; deltax=0.; deltay=0.; deltaz=0.;
    minapp=-999; chi2=-999;
    chi2prob=-999;
    refit=-999;
    tx=-999; ty=-999; tz=-999;//track analytical X  
  }
} VERTEXDATA;

typedef struct { 
  int iGeneralTracksOnly; 
  int iArbitratedEcalSeeded; 
  int iArbitratedMerged;
  int iArbitratedMergedEcalGeneral;
  int iHighPurity;
  int iHighEfficiency;
  int iEcalMatched1Track;
  int iEcalMatched2Track;

  void init(){
    iGeneralTracksOnly=0; 
    iArbitratedEcalSeeded=0; 
    iArbitratedMerged=0;
    iArbitratedMergedEcalGeneral=0;
    iHighPurity=0;
    iHighEfficiency=0;
    iEcalMatched1Track=0;
    iEcalMatched2Track=0;            
    
  }
} VERTEXQUALITY;


typedef struct { 
  PARTICLEDATA mcLeg[2];
  PARTICLEDATA recoLeg[2];
  PARTICLEDATA refitLeg[2];
  PARTICLEDATA seedLeg[2];
  PARTICLEDATA inStateLeg[2];
  PARTICLEDATA outStateLeg[2];
  PARTICLEDATA stateAtVertexLeg[2];

  PARTICLEEXTRA extrasLeg[2];
  
  PARTICLEDATA mcPhoton;
  PARTICLEDATA recoPhoton;
  PARTICLEDATA refitPhoton;
  VERTEXDATA   convvtx;
  VERTEXQUALITY quality;

  void init(){
    for(size_t i=0;i<2;i++){
      mcLeg[i].init();
      recoLeg[i].init();
      refitLeg[i].init();
      seedLeg[i].init();
      inStateLeg[i].init();
      outStateLeg[i].init();
      stateAtVertexLeg[i].init();
      extrasLeg[i].init();
    }
    mcPhoton.init();
    recoPhoton.init();
    refitPhoton.init();
    convvtx.init();
    quality.init();
  }
} FULLDATA;



class NewConversionNtuplizer : public edm::EDAnalyzer {
public:
  explicit NewConversionNtuplizer(const edm::ParameterSet&);
  ~NewConversionNtuplizer();
    
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  const char* stringTochar(std::string s){return s.c_str();}
  void initStructs();
  
  void setEvent(const edm::Event& iEvent);
  void setPrimaryVertex(reco::Vertex& pvtx);
  void setBeamSpot(const reco::BeamSpot* bs);

  int getNTracksFromCollection(const edm::Event& iEvent, edm::InputTag tag);

  void getReconstructedData(const edm::Event& iEvent,const ConversionCollection* pIn,vector<PhotonMCTruth>& mcPhotons);
    
  void fillR2S(const Conversion& conv, const edm::RefToBase<reco::Track> *tk, bool valid_pvtx, reco::Vertex &the_pvtx, KinematicVertex& vtx );
  void fillR2S_refit(Track **tk, bool valid_pvtx, reco::Vertex &the_pvtx );
  void fillR2SHitPattern(const edm::RefToBase<reco::Track> *tk);
  void fillR2SCrossingPoint(const Conversion& conv);
  void fillR2SQuality(const Conversion& conv);
  void fillR2SAssociation(bool isDouble, float deltaPt=0,float deltaPhi=0,float deltaTheta=0,float deltaX=0,float deltaY=0,float deltaZ=0);
  int getBeforeHit(const edm::RefToBase<reco::Track> &tk, float recoPhoR, float vtx_z);

  void getSimulatedData(const edm::Event& iEvent, vector<PhotonMCTruth>& mcPhotons,const ConversionCollection* pIn);
  void fillMCinS2R(const PhotonMCTruth& Pho,std::vector<ElectronMCTruth>& electrons);
  void fillMatchedTrackingParticleCollection( RefVector<TrackingParticleCollection>& tpc, Handle<TrackingParticleCollection>& TPCollectionH,std::vector<ElectronMCTruth>& electrons);
  
  GlobalVector getStateAtVertex(const edm::RefToBase<reco::Track> &tk, float recoPhoR,float vtx_z,float& iphi);
  void getConversionVertexPairs(const ConversionCollection* convColl);
  void dumpDebugTable(const ConversionCollection* convColl);
  bool isConvQualityNotOk(ConversionCollection::const_iterator conv);
  bool getKinematicVertexFromConversion(vector<TransientTrack>& t_tks,ConversionCollection::const_iterator conv,KinematicVertex& kineVtx);
  void RefitVertex(vector<TransientTrack>& t_tks, KinematicVertex& kineVtx);
  void tryRefit(const Conversion& conv);
  
  void AssociateByKineConstraints(vector<PhotonMCTruth>& mcPhotons,KinematicVertex& vtx,const edm::RefToBase<reco::Track> *arrayTK);
  void AssociateByKineConstraintsImproved(vector<PhotonMCTruth>& mcPhotons,KinematicVertex& vtx,const edm::RefToBase<reco::Track> *arrayTK, vector<bool>& doubleCounterCheck);
  bool isSimVertexOutsideAssCut(KinematicVertex& vtx, const PhotonMCTruth& Pho);
  void AssociateByHit(const edm::Event& iEvent,const Conversion& conv);
  void SearchTrackingParticleConversionCandidates( RefVector<TrackingParticleCollection>& tpc);
  //TO BE FIXED
  bool checkSimToRecoAssociation(const edm::Event& iEvent,const Conversion& conv, RefVector<TrackingParticleCollection>& tpc,KinematicVertex& vtx,const PhotonMCTruth& Pho);
  void fillS2R(const Conversion& conv,KinematicVertex& vtx,const PhotonMCTruth& Pho);
  
  

  //Data Members

  const MagneticField* magField;
  const TrackerGeometry* trackerGeom;

  const TransientTrackBuilder *_TransientTrackBuilder;

  TrajectoryStateTransform transformer;
  KinematicConstrainedVertexFitter fitter;

  Handle<TrackingParticleCollection>  TPCollectionH;
  ESHandle<TrackAssociatorBase> theAssociator;

  reco::VertexCollection vertexCollection;
  reco::Vertex the_pvtx;

  typedef pair<unsigned int,KinematicVertex> conversionVertex;
  vector<conversionVertex> conversionVertices;

  //------------------------------------------------------------------------
  TFile * file;
  std::string outfile;
  edm::InputTag primaryVerticesTag;
  edm::InputTag ckfTrackCollectionTag;
  edm::InputTag singleLegTrackCollectionTag;
  edm::InputTag gsfTrackCollectionTag;
  edm::InputTag inOutTrackCollectionTag;
  edm::InputTag outInTrackCollectionTag;
  bool generalTkOnly;
  bool redovtx;
  bool hitassoc;
  bool retracking;
  double minPhoPtForEffic;
  double maxPhoEtaForEffic;
  double maxPhoZForEffic;
  double maxPhoRForEffic;
  double minPhoPtForPurity;
  double maxPhoEtaForPurity;
  double maxPhoZForPurity;
  double maxPhoRForPurity;
  bool simulation;
  std::string dataType;
  bool prints;

  int numberOfRecoConvInEvt;

  // ### Pileup information in MC ###
  std::vector<int>* bunchXingMC;
  std::vector<int>* nInteractionsMC;
  
  bool valid_pvtx;
  //------------------------------------------------------------------------
  
  EVT          evtbranch;
  VERTEXDATA   primaryvtx;
  VERTEXDATA   beamspot;
  FULLDATA     s2rbranch;
  FULLDATA     r2sbranch;
  TTree *ntupleEvt;
  TTree *ntupleS2R,*ntupleR2S;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
NewConversionNtuplizer::NewConversionNtuplizer(const edm::ParameterSet& iConfig) :
  outfile(iConfig.getParameter<std::string>("outfile")),
  primaryVerticesTag(iConfig.getParameter<edm::InputTag>("primaryVerticesTag")),
  generalTkOnly(iConfig.getParameter<bool>("generalTkOnly")),
  redovtx(iConfig.getParameter<bool>("redovtx")),
  hitassoc(iConfig.getParameter<bool>("hitassoc")),
  retracking(iConfig.getParameter<bool>("retracking")),
  minPhoPtForEffic(iConfig.getParameter<double>("minPhoPtForEffic")),
  maxPhoEtaForEffic(iConfig.getParameter<double>("maxPhoEtaForEffic")),
  maxPhoZForEffic(iConfig.getParameter<double>("maxPhoZForEffic")),
  maxPhoRForEffic(iConfig.getParameter<double>("maxPhoRForEffic")),
  minPhoPtForPurity(iConfig.getParameter<double>("minPhoPtForPurity")),
  maxPhoEtaForPurity(iConfig.getParameter<double>("maxPhoEtaForPurity")),
  maxPhoZForPurity(iConfig.getParameter<double>("maxPhoZForPurity")),
  maxPhoRForPurity(iConfig.getParameter<double>("maxPhoRForPurity")),
  simulation(iConfig.getParameter<bool>("simulation")), 
  dataType(iConfig.getUntrackedParameter<std::string>("dataType",std::string("MCRECO"))), // It can be:  "MCAOD, "MCRECO", "DATAAOD", "DATARECO"
  prints(iConfig.getParameter<bool>("prints")),
  ntupleEvt(0),
  ntupleS2R(0),ntupleR2S(0)
{ 

  //Track counters
  ckfTrackCollectionTag = (iConfig.exists("ckfTrackCollectionTag")) 
    ? iConfig.getParameter<InputTag>("ckfTrackCollectionTag") : edm::InputTag("generalTracks");
  singleLegTrackCollectionTag = (iConfig.exists("singleLegTrackCollectionTag")) 
    ? iConfig.getParameter<InputTag>("singleLegTrackCollectionTag") : edm::InputTag("conversionStepTracks");
  gsfTrackCollectionTag = (iConfig.exists("gsfTrackCollectionTag")) 
    ? iConfig.getParameter<InputTag>("gsfTrackCollectionTag") : edm::InputTag("electronGsfTracks");
  //? iConfig.getParameter<InputTag>("gsfTrackCollectionTag") : edm::InputTag("gsfConversionTrackProducer");
  inOutTrackCollectionTag = (iConfig.exists("inOutTrackCollectionTag")) 
    ? iConfig.getParameter<InputTag>("inOutTrackCollectionTag") : edm::InputTag("ckfInOutTracksFromConversions");
  outInTrackCollectionTag = (iConfig.exists("outInTrackCollectionTag")) 
    ? iConfig.getParameter<InputTag>("outInTrackCollectionTag") : edm::InputTag("ckfOutInTracksFromConversions");

}


NewConversionNtuplizer::~NewConversionNtuplizer() { }

void NewConversionNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  if (prints) cout << "new evt" << endl;

  initStructs();
  numberOfRecoConvInEvt=0;

  //-------------- Get ESHandles -----------//
  //get tracker geometry for hits positions
  edm::ESHandle<TrackerGeometry> tracker;
  iSetup.get<TrackerDigiGeometryRecord>().get(tracker);
  trackerGeom = tracker.product();

  edm::ESHandle<MagneticField> magFieldHandle;
  iSetup.get<IdealMagneticFieldRecord>().get( magFieldHandle );
  magField = magFieldHandle.product();;
  
  ESHandle<TransientTrackBuilder> theB;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);
  _TransientTrackBuilder = theB.product();

  if (simulation && hitassoc) {
    iSetup.get<TrackAssociatorRecord>().get("TrackAssociatorByHits",theAssociator);
    iEvent.getByLabel("mergedtruth","MergedTrackTruth",TPCollectionH);
  }

  //----------------------------------

  //record the beam spot
  edm::Handle<reco::BeamSpot> bs;
  iEvent.getByLabel(edm::InputTag("offlineBeamSpot"),bs);
  if(bs.isValid())    setBeamSpot(bs.product());

  valid_pvtx = false;  
  edm::Handle<reco::VertexCollection> vertexHandle;
  iEvent.getByLabel(primaryVerticesTag, vertexHandle);
  if (vertexHandle.isValid()){ 
    vertexCollection = *(vertexHandle.product());
    if (!vertexCollection.empty()){
      the_pvtx = *(vertexCollection.begin());
      //asking for one good vertex
      if (
	  the_pvtx.isValid() 
	  && 
	  fabs(the_pvtx.position().z())<=15 
	  && the_pvtx.position().Rho()<=2){

	setPrimaryVertex(the_pvtx);
	valid_pvtx = true;
      }
    }else{
      edm::LogError("TrackerOnlyConversionProducer") << "Error! Can't get the product primary Vertex Collection "<< "\n";
    } 
  }
  
  //make conversion vertices
  Handle<ConversionCollection> pIn;
  iEvent.getByLabel("allConversions",pIn);
   
  //make conversion-vertex pair vector
  getConversionVertexPairs(pIn.product());
  
  vector<PhotonMCTruth> mcPhotons;
  if (simulation) {
    getSimulatedData(iEvent,mcPhotons,pIn.product());
  }
  
  //compute purity and plot residues
  numberOfRecoConvInEvt=conversionVertices.size();
  if (prints) cout << "loop on reco, size=" << numberOfRecoConvInEvt << endl;
  getReconstructedData(iEvent,pIn.product(),mcPhotons);


  // ###################
  // # Fill Evt Branch #
  // ###################
  setEvent(iEvent);
}
 
void NewConversionNtuplizer::
getReconstructedData(const edm::Event& iEvent,const ConversionCollection* pIn,vector<PhotonMCTruth>& mcPhotons){

  vector<bool> doubleCounterCheck;
  doubleCounterCheck.assign(mcPhotons.size(),false);

  for (vector<conversionVertex>::iterator rcv=conversionVertices.begin();rcv!=conversionVertices.end();++rcv) {
    const Conversion& conv = (*pIn)[rcv->first];

    r2sbranch.init();

    KinematicVertex& vtx = rcv->second;
    if (prints) cout << "got vtx" << endl;
 
    //    TrackRef arrayTK[2]={conv.tracks().front() , conv.tracks().back()};     
    const edm::RefToBase<reco::Track> arrayTK[2]={conv.tracks().front() , conv.tracks().back()};
    
    //reco plots
    if (prints) cout << "fill reco plots" << endl;
    
    fillR2S(conv, arrayTK,valid_pvtx,the_pvtx,vtx);
    fillR2SHitPattern(arrayTK);   //count hits before vertex
    tryRefit(conv);
    fillR2SCrossingPoint(conv);
    fillR2SQuality(conv);


    if (simulation) {
      //double simPhoR(0), simPhoZ(0), simPhoEta(0), simPhoPt(0), simPhoPhi(0), simPhoTheta(0);
      if (prints) cout << "check assoc" << endl;
      if (hitassoc) {
	AssociateByHit(iEvent,conv);
      } else {
	//AssociateByKineConstraints(mcPhotons,vtx,arrayTK);
	AssociateByKineConstraintsImproved(mcPhotons,vtx,arrayTK,doubleCounterCheck);
      }    
      
    }
    ntupleR2S->Fill();    
    if (prints) cout << "end of loop" << endl;
  }  
  if (prints) cout << "end of event" << endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
NewConversionNtuplizer::beginJob()
{
  file = new TFile(outfile.c_str(),"recreate");

  bunchXingMC = new std::vector<int>;
  nInteractionsMC = new std::vector<int>;

  const bool oldAddDir = TH1::AddDirectoryStatus();
  TH1::AddDirectory(true);

  ntupleEvt = new TTree("ntupleEvt", "evt");
  ntupleEvt->Branch("run",              &(evtbranch.run),       "run/I");
  ntupleEvt->Branch("event",		&(evtbranch.event),     "event/I");
  ntupleEvt->Branch("lumi",		&(evtbranch.lumi),      "lumi/I");
  ntupleEvt->Branch("nCkf",             &(evtbranch.nCkf),      "nCkf/I");     
  ntupleEvt->Branch("n1Tk",             &(evtbranch.n1Tk),      "n1Tk/I");     
  ntupleEvt->Branch("nGsf",             &(evtbranch.nGsf),      "nGsf/I");     
  ntupleEvt->Branch("nCkfInOut",        &(evtbranch.nCkfInOut), "nCkfInOut/I");
  ntupleEvt->Branch("nCkfOutIn",        &(evtbranch.nCkfOutIn), "nCkfOutIn/I"); 
  ntupleEvt->Branch("nRecoConv",        &(evtbranch.nRecoConv), "nRecoConv/I"); 

  ntupleEvt->Branch("nPrimVtx",        &(evtbranch.nPrimVtx), "nPrimVtx/I"); 
  ntupleEvt->Branch("bunchXingMC",     &bunchXingMC); 
  ntupleEvt->Branch("nInteractionsMC", &nInteractionsMC); 

  ntupleS2R = new TTree("ntupleS2R","sim2reco");
  ntupleS2R->Branch("run",		&(evtbranch.run),"run/I");
  ntupleS2R->Branch("event",		&(evtbranch.event),"event/I");
  
  ntupleS2R->Branch("isAssoc",		&(s2rbranch.convvtx.isAssoc),"isAssoc/I");

  std::string c[2]={"1","2"};
  for(size_t i=0;i<2;i++){
    ntupleS2R->Branch(stringTochar("q"	          +c[i]),  &(s2rbranch.mcLeg[i].q),          	stringTochar("q"	 +c[i]+"/I"));
    ntupleS2R->Branch(stringTochar("pt"	          +c[i]),  &(s2rbranch.mcLeg[i].pt),	     	stringTochar("pt"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("phi"	  +c[i]),  &(s2rbranch.mcLeg[i].phi),	     	stringTochar("phi"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("theta"	  +c[i]),  &(s2rbranch.mcLeg[i].theta),	     	stringTochar("theta"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("qseed"	  +c[i]),  &(s2rbranch.seedLeg[i].q),	     	stringTochar("qseed"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("ptseed"	  +c[i]),  &(s2rbranch.seedLeg[i].pt),	     	stringTochar("ptseed"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("phiseed"	  +c[i]),  &(s2rbranch.seedLeg[i].phi),	     	stringTochar("phiseed"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("thetaseed"    +c[i]),  &(s2rbranch.seedLeg[i].theta),    	stringTochar("thetaseed" +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("rseed"	  +c[i]),  &(s2rbranch.seedLeg[i].r),	     	stringTochar("rseed"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("zseed"	  +c[i]),  &(s2rbranch.seedLeg[i].z),	     	stringTochar("zseed"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("r_algo"	  +c[i]),  &(s2rbranch.recoLeg[i].algo),     	stringTochar("r_algo"	 +c[i]+"/I"));
    ntupleS2R->Branch(stringTochar("r_pt"	  +c[i]),  &(s2rbranch.recoLeg[i].pt),	     	stringTochar("r_pt"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("r_d0"	  +c[i]),  &(s2rbranch.recoLeg[i].d0),	     	stringTochar("r_d0"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("r_theta"	  +c[i]),  &(s2rbranch.recoLeg[i].theta),    	stringTochar("r_theta"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("r_phi"	  +c[i]),  &(s2rbranch.recoLeg[i].phi),	     	stringTochar("r_phi"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("r_chi2"	  +c[i]),  &(s2rbranch.recoLeg[i].chi2),     	stringTochar("r_chi2"	 +c[i]+"/F"));
    ntupleS2R->Branch(stringTochar("r_hits"	  +c[i]),  &(s2rbranch.extrasLeg[i].nHits),  	stringTochar("r_hits"	 +c[i]+"/I"));
    ntupleS2R->Branch(stringTochar("r_before"     +c[i]),  &(s2rbranch.extrasLeg[i].beforeHits),stringTochar("r_before"	 +c[i]+"/I"));
    ntupleS2R->Branch(stringTochar("r_missHits"   +c[i]),  &(s2rbranch.extrasLeg[i].missHits),  stringTochar("r_missHits"+c[i]+"/I"));
  }

  
  ntupleS2R->Branch("pt",		&(s2rbranch.mcPhoton.pt),	       	"pt/F");
  ntupleS2R->Branch("phi",		&(s2rbranch.mcPhoton.phi),		"phi/F");
  ntupleS2R->Branch("theta",		&(s2rbranch.mcPhoton.theta),		"theta/F");
										
  ntupleS2R->Branch("deltapt",		&(s2rbranch.convvtx.deltapt),		"deltapt/F");
  ntupleS2R->Branch("deltaphi",		&(s2rbranch.convvtx.deltaphi),		"deltaphi/F");
  ntupleS2R->Branch("deltatheta",	&(s2rbranch.convvtx.deltatheta),       	"deltatheta/F");
  ntupleS2R->Branch("x",		&(s2rbranch.convvtx.x),	       	"x/F");
  ntupleS2R->Branch("y",		&(s2rbranch.convvtx.y),		"y/F");
  ntupleS2R->Branch("z",		&(s2rbranch.convvtx.z),		"z/F");
  ntupleS2R->Branch("deltax",		&(s2rbranch.convvtx.deltax),		"deltax/F");
  ntupleS2R->Branch("deltay",		&(s2rbranch.convvtx.deltay),		"deltay/F");
  ntupleS2R->Branch("deltaz",		&(s2rbranch.convvtx.deltaz),		"deltaz/F");
										
  ntupleS2R->Branch("r_minapp",		&(s2rbranch.convvtx.minapp),		"r_minapp/F");
  ntupleS2R->Branch("r_chi2prob",	&(s2rbranch.convvtx.chi2prob),		"r_chi2prob/F");

  ntupleS2R->Branch("q_gto",		&(s2rbranch.quality.iGeneralTracksOnly),          "q_gto/I");
  ntupleS2R->Branch("q_aes",		&(s2rbranch.quality.iArbitratedEcalSeeded),       "q_aes/I");
  ntupleS2R->Branch("q_am",		&(s2rbranch.quality.iArbitratedMerged),           "q_am/I");
  ntupleS2R->Branch("q_ameg",		&(s2rbranch.quality.iArbitratedMergedEcalGeneral),"q_ameg/I");
  ntupleS2R->Branch("q_hp",		&(s2rbranch.quality.iHighPurity),                 "q_hp/I");
  ntupleS2R->Branch("q_he",		&(s2rbranch.quality.iHighEfficiency),             "q_he/I");
  ntupleS2R->Branch("q_em1t",		&(s2rbranch.quality.iEcalMatched1Track),          "q_em1t/I");
  ntupleS2R->Branch("q_em2t",		&(s2rbranch.quality.iEcalMatched2Track),          "q_em2t/I");


  ntupleR2S = new TTree("ntupleR2S","reco2sim");
  ntupleR2S->Branch("run",		&(evtbranch.run),		"run/I");
  ntupleR2S->Branch("event",		&(evtbranch.event),		"event/I");

  ntupleR2S->Branch("isAssoc",		&(r2sbranch.convvtx.isAssoc),	"isAssoc/I");
  ntupleR2S->Branch("isDouble",		&(r2sbranch.convvtx.isDouble),	"isDouble/I");
  
  for(size_t i=0;i<2;i++){
    ntupleR2S->Branch(stringTochar(	"q"		+c[i])	,		&(r2sbranch.recoLeg[i].q),     	 	stringTochar(	"q"		+c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"algo"		+c[i])	,		&(r2sbranch.recoLeg[i].algo),	 	stringTochar(	"algo"		+c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"d0"		+c[i])	,		&(r2sbranch.recoLeg[i].d0),    	 	stringTochar(	"d0"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"dz"		+c[i])	,		&(r2sbranch.recoLeg[i].dz),    	 	stringTochar(	"dz"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"pt"		+c[i])	,		&(r2sbranch.recoLeg[i].pt),    	 	stringTochar(	"pt"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"phi"		+c[i])	,		&(r2sbranch.recoLeg[i].phi),	 	stringTochar(	"phi"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"iphi"		+c[i])	,		&(r2sbranch.stateAtVertexLeg[i].phi),   stringTochar(	"iphi"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"theta"		+c[i])	,		&(r2sbranch.recoLeg[i].theta),	 	stringTochar(	"theta"	        +c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"x"		+c[i])	,		&(r2sbranch.inStateLeg[i].x),     	stringTochar(	"x"		+c[i]+"/F")); //wrong assignment????
    ntupleR2S->Branch(stringTochar(	"y"		+c[i])	,		&(r2sbranch.inStateLeg[i].y),     	stringTochar(	"y"		+c[i]+"/F"));//
    ntupleR2S->Branch(stringTochar(	"z"		+c[i])	,		&(r2sbranch.inStateLeg[i].z),     	stringTochar(	"z"		+c[i]+"/F"));//
    ntupleR2S->Branch(stringTochar(	"chi2"		+c[i])	,		&(r2sbranch.recoLeg[i].chi2),	 	stringTochar(	"chi2"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"nHits"		+c[i])	,		&(r2sbranch.extrasLeg[i].nHits), 	stringTochar(	"nHits"	        +c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"beforeHits"	+c[i])	,		&(r2sbranch.extrasLeg[i].beforeHits),	stringTochar(	"beforeHits"	+c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"npHits"	+c[i])	,		&(r2sbranch.extrasLeg[i].npHits),	stringTochar(	"npHits"	+c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"nsHits"	+c[i])	,		&(r2sbranch.extrasLeg[i].nsHits),	stringTochar(	"nsHits"	+c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"missHits"	+c[i])	,		&(r2sbranch.extrasLeg[i].missHits),	stringTochar(	"missHits"	+c[i]+"/I"));
    ntupleR2S->Branch(stringTochar(	"lambdaError"	+c[i])	,		&(r2sbranch.extrasLeg[i].lambdaError),  stringTochar(	"lambdaError"	+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_pt"		+c[i])	,		&(r2sbranch.refitLeg[i].pt),	 	stringTochar(	"r_pt"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_d0"		+c[i])	,		&(r2sbranch.refitLeg[i].d0),	 	stringTochar(	"r_d0"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_phi"		+c[i])	,		&(r2sbranch.refitLeg[i].phi),	 	stringTochar(	"r_phi"	        +c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_theta"	+c[i])	,		&(r2sbranch.refitLeg[i].theta),	 	stringTochar(	"r_theta"	+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_px"		+c[i])	,		&(r2sbranch.refitLeg[i].px),	 	stringTochar(	"r_px"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_py"		+c[i])	,		&(r2sbranch.refitLeg[i].py),	 	stringTochar(	"r_py"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"r_pz"		+c[i])	,		&(r2sbranch.refitLeg[i].pz),	 	stringTochar(	"r_pz"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"ipx"		+c[i])	,		&(r2sbranch.inStateLeg[i].px),	 	stringTochar(	"ipx"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"ipy"		+c[i])	,		&(r2sbranch.inStateLeg[i].py),	 	stringTochar(	"ipy"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"ipz"		+c[i])	,		&(r2sbranch.inStateLeg[i].pz),	 	stringTochar(	"ipz"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"ix"		+c[i])	,		&(r2sbranch.inStateLeg[i].x),	 	stringTochar(	"ix"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"iy"		+c[i])	,		&(r2sbranch.inStateLeg[i].y),	 	stringTochar(	"iy"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"iz"		+c[i])	,		&(r2sbranch.inStateLeg[i].z),	 	stringTochar(	"iz"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"ox"		+c[i])	,		&(r2sbranch.outStateLeg[i].x),	 	stringTochar(	"ox"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"oy"		+c[i])	,		&(r2sbranch.outStateLeg[i].y),	 	stringTochar(	"oy"		+c[i]+"/F"));
    ntupleR2S->Branch(stringTochar(	"oz"		+c[i])	,		&(r2sbranch.outStateLeg[i].z),	 	stringTochar(	"oz"		+c[i]+"/F"));
  }  


  ntupleR2S->Branch("pt",		&(r2sbranch.recoPhoton.pt),		"pt/F");
  ntupleR2S->Branch("phi",		&(r2sbranch.recoPhoton.phi),		"phi/F");
  ntupleR2S->Branch("theta",		&(r2sbranch.recoPhoton.theta),		"theta/F");
  ntupleR2S->Branch("mass",		&(r2sbranch.recoPhoton.mass),		"mass/F");
  ntupleR2S->Branch("r_pt",		&(r2sbranch.refitPhoton.pt),		"r_pt/F");
  ntupleR2S->Branch("r_phi",		&(r2sbranch.refitPhoton.phi),		"r_phi/F");
  ntupleR2S->Branch("r_theta",		&(r2sbranch.refitPhoton.theta),	        "r_theta/F");
  ntupleR2S->Branch("r_mass",		&(r2sbranch.refitPhoton.mass),		"r_mass/F");

  ntupleR2S->Branch("chi2",		&(r2sbranch.convvtx.chi2),		"chi2/F");										
  ntupleR2S->Branch("deltapt",		&(r2sbranch.convvtx.deltapt),		"deltapt/F");
  ntupleR2S->Branch("deltaphi",		&(r2sbranch.convvtx.deltaphi),		"deltaphi/F");
  ntupleR2S->Branch("deltatheta",       &(r2sbranch.convvtx.deltatheta),	"deltatheta/F");
  ntupleR2S->Branch("x",		&(r2sbranch.convvtx.x),		"x/F");
  ntupleR2S->Branch("y",		&(r2sbranch.convvtx.y),		"y/F");
  ntupleR2S->Branch("z",		&(r2sbranch.convvtx.z),		"z/F");
  ntupleR2S->Branch("deltax",		&(r2sbranch.convvtx.deltax),		"deltax/F");
  ntupleR2S->Branch("deltay",		&(r2sbranch.convvtx.deltay),		"deltay/F");
  ntupleR2S->Branch("deltaz",		&(r2sbranch.convvtx.deltaz),		"deltaz/F");
  ntupleR2S->Branch("minapp",	        &(r2sbranch.convvtx.minapp),	        "minapp/F");
  ntupleR2S->Branch("refit",		&(r2sbranch.convvtx.refit),		"refit/I");
  ntupleR2S->Branch("vx",		&(primaryvtx.x),		"vx/F");
  ntupleR2S->Branch("vy",		&(primaryvtx.y),		"vy/F");
  ntupleR2S->Branch("vz",		&(primaryvtx.z),		"vz/F");
  ntupleR2S->Branch("tx",		&(r2sbranch.convvtx.tx),		"tx/F");
  ntupleR2S->Branch("ty",		&(r2sbranch.convvtx.ty),		"ty/F");
  ntupleR2S->Branch("tz",		&(r2sbranch.convvtx.tz),		"tz/F");
  ntupleR2S->Branch("bsx",		&(beamspot.x),		"bsx/F");
  ntupleR2S->Branch("bsy",		&(beamspot.y),		"bsy/F");
  ntupleR2S->Branch("bsz",		&(beamspot.z),		"bsz/F");
  ntupleR2S->Branch("chi2prob",		&(r2sbranch.convvtx.chi2prob),		"chi2prob/F");

  ntupleR2S->Branch("q_gto",		&(r2sbranch.quality.iGeneralTracksOnly),          "q_gto/I");
  ntupleR2S->Branch("q_aes",		&(r2sbranch.quality.iArbitratedEcalSeeded),       "q_aes/I");
  ntupleR2S->Branch("q_am",		&(r2sbranch.quality.iArbitratedMerged),           "q_am/I");
  ntupleR2S->Branch("q_ameg",		&(r2sbranch.quality.iArbitratedMergedEcalGeneral),"q_ameg/I");
  ntupleR2S->Branch("q_hp",		&(r2sbranch.quality.iHighPurity),                 "q_hp/I");
  ntupleR2S->Branch("q_he",		&(r2sbranch.quality.iHighEfficiency),             "q_he/I");
  ntupleR2S->Branch("q_em1t",		&(r2sbranch.quality.iEcalMatched1Track),          "q_em1t/I");
  ntupleR2S->Branch("q_em2t",		&(r2sbranch.quality.iEcalMatched2Track),          "q_em2t/I");

  TH1::AddDirectory(oldAddDir);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NewConversionNtuplizer::endJob() {
  file->Write();
  file->Close();
}



void NewConversionNtuplizer::fillR2S(const Conversion& conv, const edm::RefToBase<reco::Track> *tk, bool valid_pvtx, reco::Vertex &the_pvtx, KinematicVertex& vtx ){
  for(size_t i=0;i<2;i++){
    r2sbranch.recoLeg[i].q     =tk[i]->charge();
    r2sbranch.recoLeg[i].algo  =tk[i]->algo();
    r2sbranch.recoLeg[i].pt    =tk[i]->pt();
    r2sbranch.recoLeg[i].phi   =tk[i]->phi();
    r2sbranch.recoLeg[i].theta =tk[i]->theta();

    r2sbranch.recoLeg[i].chi2  =tk[i]->normalizedChi2();


    r2sbranch.extrasLeg[i].nHits =tk[i]->numberOfValidHits();

    if (valid_pvtx){
      r2sbranch.recoLeg[i].d0 = - tk[i]->dxy(the_pvtx.position());
      r2sbranch.recoLeg[i].dz = - tk[i]->dz(the_pvtx.position());
    } else {
      r2sbranch.recoLeg[i].d0 = tk[i]->d0();
      r2sbranch.recoLeg[i].dz = tk[i]->dz();
    }    

    if ((dataType == "MCRECO") || (dataType == "DATARECO"))
      {
	float iphi = -999.;
	getStateAtVertex(tk[i], vtx.position().perp(),vtx.position().z(),iphi);

	r2sbranch.stateAtVertexLeg[i].phi =iphi;

	r2sbranch.inStateLeg[i].x  =tk[i]->innerPosition().x();
	r2sbranch.inStateLeg[i].y  =tk[i]->innerPosition().y();
	r2sbranch.inStateLeg[i].z  =tk[i]->innerPosition().z();

	r2sbranch.inStateLeg[i].px = tk[i]->innerMomentum().x();
	r2sbranch.inStateLeg[i].py = tk[i]->innerMomentum().y();
	r2sbranch.inStateLeg[i].pz = tk[i]->innerMomentum().z();

        r2sbranch.outStateLeg[i].x = tk[i]->outerPosition().x();
	r2sbranch.outStateLeg[i].y = tk[i]->outerPosition().y();
	r2sbranch.outStateLeg[i].z = tk[i]->outerPosition().z();

	r2sbranch.extrasLeg[i].beforeHits  = getBeforeHit(tk[i],vtx.position().perp(),vtx.position().z());
	r2sbranch.extrasLeg[i].missHits    = tk[i]->lost();
	r2sbranch.extrasLeg[i].lambdaError = tk[i]->lambdaError();
      }
  }

  //  math::XYZVector photonMom = tk[0]->momentum()+tk[1]->momentum();
  math::XYZVectorF photonMom = conv.refittedPairMomentum();
  r2sbranch.recoPhoton.pt    = photonMom.rho();
  r2sbranch.recoPhoton.phi   = photonMom.phi();
  r2sbranch.recoPhoton.theta = photonMom.theta();

  //FIXME dovrebbe essere piuttosto assegnato al vertice
  r2sbranch.convvtx.x    =vtx.position().x(); 
  r2sbranch.convvtx.y    =vtx.position().y();
  r2sbranch.convvtx.z    =vtx.position().z();
  r2sbranch.convvtx.chi2 =vtx.chiSquared()/vtx.degreesOfFreedom();

  r2sbranch.convvtx.chi2prob = ChiSquaredProbability(vtx.chiSquared(), vtx.degreesOfFreedom());  //Fixme, altrove viene calcolata solo come rapporto. qui??

  if(prints) cout<<"converted photon with valid vertex at R="<<vtx.position().perp()<<" pt="<<photonMom.rho()
		 <<" tk1pT="<<tk[0]->pt()<<" tk2pT="<<tk[1]->pt()<<endl;
  
}

void NewConversionNtuplizer::fillR2S_refit(Track **tk, bool valid_pvtx, reco::Vertex &the_pvtx ){
  r2sbranch.convvtx.refit = 1;
  for(size_t i=0;i<2;i++){
    r2sbranch.refitLeg[i].pt    =tk[i]->pt();
    r2sbranch.refitLeg[i].phi   =tk[i]->phi();
    r2sbranch.refitLeg[i].theta =tk[i]->theta();
    r2sbranch.refitLeg[i].px  =tk[i]->px();
    r2sbranch.refitLeg[i].py  =tk[i]->py();
    r2sbranch.refitLeg[i].pz  =tk[i]->pz();
    //    r2sbranch.refitLeg[i].x  =tk[i]->innerPosition().x();
    //    r2sbranch.refitLeg[i].y  =tk[i]->innerPosition().y();
    //    r2sbranch.refitLeg[i].z  =tk[i]->innerPosition().z();
    
    if (valid_pvtx){
      r2sbranch.refitLeg[i].d0 = - tk[i]->dxy(the_pvtx.position());
      r2sbranch.refitLeg[i].dz = - tk[i]->dz(the_pvtx.position());
    } else {
      r2sbranch.refitLeg[i].d0 = tk[i]->d0();
      r2sbranch.refitLeg[i].dz = tk[i]->dz();
    }    
  }
  
  math::XYZVector refit_photonMom = tk[0]->momentum()+tk[1]->momentum();

  //  double refit_recoPhoPt = sqrt(refit_photonMom.perp2());
  
  r2sbranch.refitPhoton.pt = refit_photonMom.Rho();
  r2sbranch.refitPhoton.phi = refit_photonMom.phi();
  r2sbranch.refitPhoton.theta = refit_photonMom.theta();

}

void NewConversionNtuplizer:: 
fillR2SHitPattern(const edm::RefToBase<reco::Track> *tk){

  unsigned short PatternSize = 25;
  unsigned short HitSize = 11;
  
  for(size_t i=0;i<2;i++){
    const HitPattern & pattern = tk[i]->hitPattern();
    //valid pixel hits
    r2sbranch.extrasLeg[i].npHits = pattern.numberOfValidPixelHits();
    

    int ns_hit = 0; 
    for (int j=0; j<(PatternSize * 32) / HitSize; j++) {
      uint32_t kpattern = pattern.getHitPattern(j);
      if (kpattern != 0) {//valid strip stereo hit
	if (pattern.validHitFilter(kpattern)) {
	  if (pattern.stripHitFilter(kpattern)){
	    if (pattern.getSide(kpattern)==1){
	      ns_hit++;
	    }
	  }
	}
      }
    }
    r2sbranch.extrasLeg[i].nsHits =ns_hit;
  }
}


int NewConversionNtuplizer::getBeforeHit(const edm::RefToBase<reco::Track> &tk, float recoPhoR, float vtx_z){
  //count hits before vertex
  int before_hit = 0;
  for (trackingRecHit_iterator hit = tk->recHitsBegin(); hit != tk->recHitsEnd(); ++hit){
    if ((*hit)->isValid () && !(*hit)->geographicalId ().null ()){
      LocalPoint local_pos(0, 0, 0);//for 336, it needs refit
      GlobalPoint hit_pos = trackerGeom->idToDet((*hit)->geographicalId())->surface().toGlobal(local_pos);
      if ((hit_pos.perp()<recoPhoR) && fabs(hit_pos.z())<fabs(vtx_z)){
	before_hit ++;
      }
    }
  }
  return before_hit;
}

void NewConversionNtuplizer::
initStructs(){
  evtbranch.init();
  primaryvtx.init();
  beamspot.init();
  s2rbranch.init();
  r2sbranch.init();
}

void NewConversionNtuplizer::
setEvent(const edm::Event& iEvent){
  evtbranch.run=iEvent.run();
  evtbranch.event=iEvent.id().event();
  evtbranch.lumi  = iEvent.id().luminosityBlock();

  edm::Handle<reco::VertexCollection> vertexHandle;
  iEvent.getByLabel(primaryVerticesTag, vertexHandle);
  evtbranch.nPrimVtx = vertexHandle->size();

  bunchXingMC->clear();
  nInteractionsMC->clear();
  if ((dataType == "MCRECO") || (dataType == "MCAOD"))
    {
      edm::Handle< vector<PileupSummaryInfo> > PupInfo;
      iEvent.getByLabel(edm::InputTag("addPileupInfo"), PupInfo);
      for (vector<PileupSummaryInfo>::const_iterator PVI = PupInfo->begin(); PVI != PupInfo->end(); PVI++)
	{
	  bunchXingMC->push_back(PVI->getBunchCrossing());
	  nInteractionsMC->push_back(PVI->getPU_NumInteractions());
	}
    }

  //Count tracks from collections;
  evtbranch.nCkf = getNTracksFromCollection(iEvent, ckfTrackCollectionTag);
  evtbranch.n1Tk = getNTracksFromCollection(iEvent, singleLegTrackCollectionTag);
  evtbranch.nGsf = getNTracksFromCollection(iEvent, gsfTrackCollectionTag);
  evtbranch.nCkfInOut = getNTracksFromCollection(iEvent, inOutTrackCollectionTag);
  evtbranch.nCkfOutIn = getNTracksFromCollection(iEvent, outInTrackCollectionTag);

  evtbranch.nRecoConv = numberOfRecoConvInEvt;

  ntupleEvt->Fill();  
}

void NewConversionNtuplizer::
setBeamSpot(const reco::BeamSpot* bs){
  beamspot.x = bs->position().x();
  beamspot.y = bs->position().y();
  beamspot.y = bs->position().z();
}


void NewConversionNtuplizer::
setPrimaryVertex(reco::Vertex& pvtx){
  primaryvtx.x =pvtx.position().x();
  primaryvtx.y =pvtx.position().y();
  primaryvtx.z =pvtx.position().z();
}


int NewConversionNtuplizer::
getNTracksFromCollection(const edm::Event& iEvent, edm::InputTag tag)
{

  /*
  edm::Handle<reco::TrackCollection> tkCollection;
  //  iEvent.getByType(tkCollection);
  //  edm::Handle<edm::View<reco::Track> > tkRefCollection;
 
  iEvent.getByLabel(tag, tkCollection);
  if (!tkCollection.isValid()) {
    std::cout << "Error! Can't get the collection: " << tag << "\n";
    return -1;
  }

  std::cout << " Collection: " << tag << " Size: " << tkCollection->size() << "\n";
  return tkCollection->size();
  */
 
  edm::Handle<edm::View<reco::Track> > tkCollection;
 
  bool found = iEvent.getByLabel(tag, tkCollection);

  if ( ! found ) {
    std::cout << "Error! Can't get the collection: " << tag << "\n";
    return -1;
  }

  if (prints) std::cout << " Collection: " << tag << " Size: " << tkCollection->size() << "\n";
  return tkCollection->size();
 

}


void NewConversionNtuplizer::
getSimulatedData(const edm::Event& iEvent, vector<PhotonMCTruth>& mcPhotons,const ConversionCollection* pIn){

  //compute efficiency
  if (prints) cout << "get sim stuff" << endl;
  //get sim info
  std::vector<SimTrack> theSimTracks;
  std::vector<SimVertex> theSimVertices;
  Handle<SimTrackContainer> SimTk;
  Handle<SimVertexContainer> SimVtx;
  iEvent.getByLabel("g4SimHits",SimTk);
  iEvent.getByLabel("g4SimHits",SimVtx);

  PhotonMCTruthFinder*  thePhotonMCTruthFinder_ = new PhotonMCTruthFinder();
  
  theSimTracks.insert(theSimTracks.end(),SimTk->begin(),SimTk->end());
  theSimVertices.insert(theSimVertices.end(),SimVtx->begin(),SimVtx->end());
  mcPhotons=thePhotonMCTruthFinder_->find(theSimTracks,  theSimVertices);
  
  if (prints) cout << "loop over sim, size=" << mcPhotons.size() << endl;
  for (vector<PhotonMCTruth>::const_iterator iPho=mcPhotons.begin(); iPho !=mcPhotons.end(); ++iPho ) {
    
    std::vector<ElectronMCTruth> electrons = (*iPho).electrons();
    
    if ( (!(*iPho).isAConversion()) || electrons.size()!=2 ) continue;
    if ((*iPho).fourMomentum().perp() < minPhoPtForEffic) continue;
    if (fabs((*iPho).fourMomentum().eta())>maxPhoEtaForEffic) continue;
    if (fabs((*iPho).vertex().z())>maxPhoZForEffic) continue;
    if ((*iPho).vertex().perp()>maxPhoRForEffic) continue;
    
    if (prints) cout << "fill mc plots" << endl;

    s2rbranch.init();
  
    fillMCinS2R(*iPho,electrons);


    //look for matching reco conversion
    if (prints) cout << "look for match" << endl;

    RefVector<TrackingParticleCollection> tpc;
    if (prints) cout << "look for match.. again" << endl;
    if (hitassoc) { 
      fillMatchedTrackingParticleCollection(tpc,TPCollectionH,electrons);
    }
    if (prints) cout << "conversionVertices.size()=" << conversionVertices.size() << endl;
    
    for (vector<conversionVertex>::iterator rcv=conversionVertices.begin();rcv!=conversionVertices.end();++rcv) {
      const Conversion& conv = (*pIn)[rcv->first];
      KinematicVertex& vtx = rcv->second;
      if (prints) cout << "got vtx" << endl;
      
      if(checkSimToRecoAssociation(iEvent,conv,tpc,vtx,*iPho)){
	fillS2R(conv,vtx,*iPho);
	break;
      }

    }
    ntupleS2R->Fill();     
  }
}

void NewConversionNtuplizer::
fillMCinS2R(const PhotonMCTruth& Pho,std::vector<ElectronMCTruth>& electrons){

  for(size_t i=0;i<2;i++){
    s2rbranch.mcLeg[i].q     = electrons[i].simTracks().charge();
    s2rbranch.mcLeg[i].pt    = electrons[i].fourMomentum().perp();
    s2rbranch.mcLeg[i].phi   = electrons[i].fourMomentum().phi();
    s2rbranch.mcLeg[i].theta = electrons[i].fourMomentum().theta();
  }

  s2rbranch.mcPhoton.pt    = Pho.fourMomentum().perp();
  s2rbranch.mcPhoton.phi   = Pho.fourMomentum().phi();
  s2rbranch.mcPhoton.theta = Pho.fourMomentum().theta();
  s2rbranch.convvtx.x     = Pho.vertex().x();
  s2rbranch.convvtx.y     = Pho.vertex().y();
  s2rbranch.convvtx.z     = Pho.vertex().z();
}



void NewConversionNtuplizer::
fillMatchedTrackingParticleCollection( RefVector<TrackingParticleCollection>& tpc, Handle<TrackingParticleCollection>& TPCollectionH,std::vector<ElectronMCTruth>& electrons){
  tpc = RefVector<TrackingParticleCollection>(TPCollectionH.id());
  for (unsigned int j=0; j<TPCollectionH->size();j++) {
    Ref<TrackingParticleCollection> tptest(TPCollectionH,j);
    if (
	( (fabs(tptest->p4().x()-electrons[0].fourMomentum().x())<0.0001) &&
	  (fabs(tptest->p4().y()-electrons[0].fourMomentum().y())<0.0001) &&
	  (fabs(tptest->p4().z()-electrons[0].fourMomentum().z())<0.0001) ) ||
	( (fabs(tptest->p4().x()-electrons[1].fourMomentum().x())<0.0001) &&
	  (fabs(tptest->p4().y()-electrons[1].fourMomentum().y())<0.0001) &&
	  (fabs(tptest->p4().z()-electrons[1].fourMomentum().z())<0.0001) )
	) {
      //cout << "pushing tp=" << tptest->p4() << " e0=" << electrons[0].fourMomentum() << " e1=" << electrons[1].fourMomentum() << endl;
      tpc.push_back(tptest);
    }
  }
}



GlobalVector NewConversionNtuplizer::
getStateAtVertex(const edm::RefToBase<reco::Track> &tk, float recoPhoR,float vtx_z,float& iphi){
  PropagatorWithMaterial propag( anyDirection, 0.000511, magField );
  GlobalVector ip(tk->innerMomentum().x(), tk->innerMomentum().y(), tk->innerMomentum().z());
  iphi = tk->innerMomentum().phi();
  if (prints) std::cout << " getStateAtVertex check tk " << tk->innerMomentum() << std::endl; 
  //take the phi from the vertex if it can propagate back to that position
  Surface::RotationType rot;
  ReferenceCountingPointer<BoundCylinder>  theBarrel_(new BoundCylinder( Surface::PositionType(0,0,0), rot,
									 SimpleCylinderBounds( recoPhoR-0.001,
											       recoPhoR+0.001, 
											       -fabs(vtx_z), 
											       fabs(vtx_z)
											       )
									 )
						      );
  ReferenceCountingPointer<BoundDisk>      theDisk_(
						    new BoundDisk( Surface::PositionType( 0, 0, vtx_z), rot,
								   SimpleDiskBounds( 0, recoPhoR, -0.001, 0.001)
								   )
						    );

  //New/sguazz
  const TrajectoryStateOnSurface myTSOS(trajectoryStateTransform::innerStateOnSurface(*tk, *trackerGeom, magField));

  //Old/sguazz
  //const TrajectoryStateOnSurface myTSOS = transformer.innerStateOnSurface(*tk, *trackerGeom, magField);

  TrajectoryStateOnSurface  stateAtVtx;
  if (prints) std::cout << " getStateAtVertex check  TSOS " << myTSOS.globalMomentum() << std::endl; 
  stateAtVtx = propag.propagate(myTSOS, *theBarrel_);
  if (!stateAtVtx.isValid() ) {
    stateAtVtx = propag.propagate(myTSOS, *theDisk_);
  }
  if (stateAtVtx.isValid()){
      iphi = stateAtVtx.globalDirection().phi();
      ip   = stateAtVtx.globalMomentum();
  }
  if (prints)
    std::cout<<" state validity "<<stateAtVtx.isValid()<<std::endl;
  return ip;
}


void NewConversionNtuplizer::
getConversionVertexPairs(const ConversionCollection* convColl){
  if (prints) cout << "loop 1, conversion size=" << convColl->size() << endl;
  
  conversionVertices.clear();
  for (ConversionCollection::const_iterator conv = convColl->begin();conv!=convColl->end();++conv) {
    
    if ( isConvQualityNotOk(conv) ) continue;

    const edm::RefToBase<reco::Track> tk1 = conv->tracks().front();
    const edm::RefToBase<reco::Track> tk2 = conv->tracks().back();
    
    if (tk1->charge()*tk2->charge()!=-1) continue;
    //if (prints) cout << "tk1 q=" << tk1->charge() << " pt=" << tk1->pt() << " dxy=" << tk1->dxy() << endl;
    //if (prints) cout << "tk2 q=" << tk2->charge() << " pt=" << tk2->pt() << " dxy=" << tk2->dxy() << endl;
    
    vector< reco::TransientTrack > t_tks;
    t_tks.push_back(_TransientTrackBuilder->build(*tk1));
    t_tks.push_back(_TransientTrackBuilder->build(*tk2));
    
    KinematicVertex _kinematicVertex;
    
    bool validVtx=false;
    if (redovtx) {
      if (prints) cout << "make vtx" << endl;
      RefitVertex(t_tks,_kinematicVertex);
      validVtx = _kinematicVertex.vertexIsValid();
    } else {
      validVtx=getKinematicVertexFromConversion(t_tks,conv, _kinematicVertex);
      validVtx = true;
    }
    
    if (validVtx){
      if (prints) cout << "pushing vtx" << endl;
      conversionVertices.push_back(std::make_pair((int)(conv-convColl->begin()),_kinematicVertex));
      //if (prints) cout << "converted photon with valid vertex at R=" << tv.position().perp() 
      //<< " pt=" << sqrt(photonMom.perp2())
      //<< endl;
    }
  }
}

void NewConversionNtuplizer::
dumpDebugTable(const ConversionCollection* convColl){
  if (prints) cout << "loop 1, conversion size=" << convColl->size() << endl;
  
  conversionVertices.clear();
  for (ConversionCollection::const_iterator conv = convColl->begin();conv!=convColl->end();++conv) {
    
    //    if ( isConvQualityNotOk(conv) ) continue;

    const edm::RefToBase<reco::Track> tk1 = conv->tracks().front();
    const edm::RefToBase<reco::Track> tk2 = conv->tracks().back();
    
    vector< reco::TransientTrack > t_tks;
    t_tks.push_back(_TransientTrackBuilder->build(*tk1));
    t_tks.push_back(_TransientTrackBuilder->build(*tk2));
    
    cout << ">>>>>>>>>>>>>>> New reco conversion found >>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << ">>>vtx "
	 << " x=" << conv->conversionVertex().position().x() 
	 << " y=" << conv->conversionVertex().position().y() 
	 << " z=" << conv->conversionVertex().position().z() 
	 << endl; 

    int iGeneralTracksOnly = 0;		 
    int iArbitratedEcalSeeded = 0;	 
    int iArbitratedMerged = 0;		 
    int iArbitratedMergedEcalGeneral = 0; 
    int iHighPurity = 0;			 
    int iHighEfficiency = 0;		 
    int iEcalMatched1Track = 0;		 
    int iEcalMatched2Track = 0;           

    if ( conv->quality(reco::Conversion::generalTracksOnly) )           iGeneralTracksOnly = 1;
    if ( conv->quality(reco::Conversion::arbitratedEcalSeeded) )        iArbitratedEcalSeeded = 1;
    if ( conv->quality(reco::Conversion::arbitratedMerged) )            iArbitratedMerged = 1;
    if ( conv->quality(reco::Conversion::arbitratedMergedEcalGeneral) ) iArbitratedMergedEcalGeneral = 1;
    if ( conv->quality(reco::Conversion::highPurity) )                  iHighPurity = 1;
    if ( conv->quality(reco::Conversion::highEfficiency) )              iHighEfficiency = 1;
    if ( conv->quality(reco::Conversion::ecalMatched1Track) )           iEcalMatched1Track = 1;
    if ( conv->quality(reco::Conversion::ecalMatched2Track) )           iEcalMatched2Track = 1;           
    cout << ">>>vtx flags"
	 << " gto =" << iGeneralTracksOnly		  
	 << " aes =" << iArbitratedEcalSeeded	 
	 << " am  =" << iArbitratedMerged		 
	 << " ameg=" << iArbitratedMergedEcalGeneral 
	 << " hp  =" << iHighPurity			 
	 << " he  =" << iHighEfficiency		 
	 << " em1t=" << iEcalMatched1Track		 
	 << " em2t=" << iEcalMatched2Track            
	 << endl; 

    cout << ">>>track 1"
	 << " p="  << tk1->outerP() 
	 << " pt=" << tk1->outerPt() 
	 << " th=" << tk1->outerTheta() 
	 << " ph=" << tk1->outerPhi() 
	 << endl; 

    cout << ">>>track 2"
	 << " p="  << tk2->outerP() 
	 << " pt=" << tk2->outerPt() 
	 << " th=" << tk2->outerTheta() 
	 << " ph=" << tk2->outerPhi() 
	 << endl; 

  }
}

bool NewConversionNtuplizer::      
getKinematicVertexFromConversion(vector<TransientTrack>& t_tks,ConversionCollection::const_iterator conv,KinematicVertex& kineVtx){
  if ( !conv->conversionVertex().isValid() ) 
    return false;

  GlobalPoint point(conv->conversionVertex().position().x(),conv->conversionVertex().position().y(),conv->conversionVertex().position().z());
  GlobalError error(conv->conversionVertex().error()(0,0),conv->conversionVertex().error()(1,0),conv->conversionVertex().error()(1,1),
		    conv->conversionVertex().error()(2,2),conv->conversionVertex().error()(2,1),
		    conv->conversionVertex().error()(2,2));
  TransientVertex tv2(point, error, t_tks, conv->conversionVertex().chi2(),conv->conversionVertex().ndof());
  kineVtx = KinematicVertex(tv2.vertexState(),tv2.totalChiSquared(),tv2.degreesOfFreedom());
  return true;
}

void NewConversionNtuplizer::
RefitVertex(vector<TransientTrack>& t_tks, KinematicVertex& kineVtx){
  vector<RefCountedKinematicParticle> allParticles;
  KinematicParticleFactoryFromTransientTrack pFactory;
  const ParticleMass elecMass = 0.000000511;
  float sigma = 0.00000000001;
  allParticles.push_back(pFactory.particle (t_tks[0],elecMass,0.,0.,sigma));
  allParticles.push_back(pFactory.particle (t_tks[1],elecMass,0.,0.,sigma));

  MultiTrackKinematicConstraint * colinearConstr = new  ColinearityKinematicConstraint(ColinearityKinematicConstraint::PhiTheta);
  RefCountedKinematicTree myTree = fitter.fit(allParticles, colinearConstr);
  if (myTree->isEmpty()) 
    return;
  
  myTree->movePointerToTheTop();
  kineVtx= *(myTree->currentDecayVertex());
}


void NewConversionNtuplizer::
tryRefit(const Conversion& conv){
  reco::Vertex the_vtx = conv.conversionVertex();  //Perche riaccede al conversionVertex se prima si era fatto rifare il refit del vertice??? FIXME, Verificare
  vector<Track> refit_tracks;
  if (the_vtx.isValid()){
    refit_tracks = the_vtx.refittedTracks();
    if (refit_tracks.size()==2){
      Track *rtk[2] ={&(refit_tracks.front()),&(refit_tracks.back())};
      fillR2S_refit(rtk, valid_pvtx, the_pvtx);
    }
  }
}

bool NewConversionNtuplizer::
isConvQualityNotOk(ConversionCollection::const_iterator conv){

  /*
  if ( generalTkOnly ) {//only check with general tracks. High purity flag always ON (suggested by Nancy)
    if (! (conv->quality(reco::Conversion::generalTracksOnly) && conv->quality(reco::Conversion::highPurity)) ) return true;
  } else {
    if (! (conv->quality(reco::Conversion::arbitratedMerged)  && conv->quality(reco::Conversion::highPurity)) ) return true;
  }
  */

  if (conv->nTracks()!=2) return true;
  
  return false;

}


void NewConversionNtuplizer::
fillR2SCrossingPoint(const Conversion& conv){
    
  const TransientTrack ttk_l(*(conv.tracks().front()), magField);
  const TransientTrack ttk_r(*(conv.tracks().back() ), magField);
  
  r2sbranch.convvtx.minapp =conv.distOfMinimumApproach();
      
  TwoTrackMinimumDistance md;
  md.calculate  (  ttk_l.initialFreeState(),  ttk_r.initialFreeState() );
  GlobalPoint thecross = md.crossingPoint();
  
  r2sbranch.convvtx.tx = thecross.x();
  r2sbranch.convvtx.ty = thecross.y();
  r2sbranch.convvtx.tz = thecross.z();

  //FIXME, forse metterlo altrove
  r2sbranch.recoPhoton.mass = conv.pairInvariantMass();
}

void NewConversionNtuplizer::
fillR2SQuality(const Conversion& conv){
    
  if ( conv.quality(reco::Conversion::generalTracksOnly) ) r2sbranch.quality.iGeneralTracksOnly = 1;
  if ( conv.quality(reco::Conversion::arbitratedEcalSeeded) ) r2sbranch.quality.iArbitratedEcalSeeded = 1;
  if ( conv.quality(reco::Conversion::arbitratedMerged) ) r2sbranch.quality.iArbitratedMerged = 1;
  if ( conv.quality(reco::Conversion::arbitratedMergedEcalGeneral) ) r2sbranch.quality.iArbitratedMergedEcalGeneral = 1;
  if ( conv.quality(reco::Conversion::highPurity) ) r2sbranch.quality.iHighPurity = 1;
  if ( conv.quality(reco::Conversion::highEfficiency) ) r2sbranch.quality.iHighEfficiency = 1;
  if ( conv.quality(reco::Conversion::ecalMatched1Track) ) r2sbranch.quality.iEcalMatched1Track = 1;
  if ( conv.quality(reco::Conversion::ecalMatched2Track) ) r2sbranch.quality.iEcalMatched2Track = 1;

}

void NewConversionNtuplizer::
fillR2SAssociation(bool isDouble, float deltaPt,float deltaPhi,float deltaTheta,float deltaX,float deltaY,float deltaZ){
  if (prints) cout << "associated" << endl;
  //residue
  r2sbranch.convvtx.isAssoc  =true;
  r2sbranch.convvtx.isDouble =isDouble;
  r2sbranch.convvtx.deltapt  =deltaPt;
  r2sbranch.convvtx.deltaphi =deltaPhi;
  r2sbranch.convvtx.deltatheta =deltaTheta;
  r2sbranch.convvtx.deltax = deltaX;
  r2sbranch.convvtx.deltay = deltaY;
  r2sbranch.convvtx.deltaz = deltaZ;
}
    
void NewConversionNtuplizer::
AssociateByKineConstraints(vector<PhotonMCTruth>& mcPhotons,KinematicVertex& vtx, const edm::RefToBase<reco::Track> *arrayTK){
  double simPhoR(0), simPhoZ(0), simPhoEta(0), simPhoPt(0), simPhoPhi(0), simPhoTheta(0);
  vector<PhotonMCTruth>::const_iterator iPho;
  for (iPho=mcPhotons.begin(); iPho !=mcPhotons.end(); ++iPho ) {
    if (prints) cout << "in loop over mc photons" << endl;
    simPhoR     = (*iPho).vertex().perp();
    simPhoZ     = (*iPho).vertex().z();
    simPhoEta   = (*iPho).fourMomentum().eta();
    simPhoPt    = (*iPho).fourMomentum().perp();
    simPhoPhi   = (*iPho).fourMomentum().phi();
    simPhoTheta = (*iPho).fourMomentum().theta();
    if ( 
	((*iPho).isAConversion()) 
	&& 
	simPhoPt>minPhoPtForPurity 
	&& 
	fabs(simPhoEta)<maxPhoEtaForPurity 
	&& 
	simPhoR<maxPhoRForPurity 
	&& 
	fabs(simPhoZ)<maxPhoZForPurity 
	 ) {
      if (
	  fabs((*iPho).vertex().x()-vtx.position().x())<5. 
	  &&   
	  fabs((*iPho).vertex().y()-vtx.position().y())<5. 
	  &&
	  fabs((*iPho).vertex().z()-vtx.position().z())<5.
	  ) {
	math::XYZVector photonMom = arrayTK[0]->momentum()+arrayTK[1]->momentum();
	fillR2SAssociation(true,
			   photonMom.rho()-simPhoPt,
			   photonMom.phi()-simPhoPhi,
			   photonMom.theta()-simPhoTheta,
			   (*iPho).vertex().x()-vtx.position().x(),
			   (*iPho).vertex().y()-vtx.position().y(),
			   (*iPho).vertex().z()-vtx.position().z()
			   );
	break;
      }
    }
  }
}

void NewConversionNtuplizer::
AssociateByKineConstraintsImproved(vector<PhotonMCTruth>& mcPhotons,KinematicVertex& vtx, const edm::RefToBase<reco::Track> *arrayTK,
vector<bool>& doubleCounterCheck){
  double simPhoR(0), simPhoZ(0), simPhoEta(0), simPhoPt(0), simPhoPhi(0), simPhoTheta(0);

  math::XYZVector photonMom = arrayTK[0]->momentum()+arrayTK[1]->momentum();
  //To store associated values
  double oldDistance3D=10000.; //Start with a big value
  double deltaRho = 0.;
  double deltaPhi = 0.;
  double deltaTheta = 0.;
  double deltax = 0.;
  double deltay = 0.;
  double deltaz = 0.;
  bool iMatch = false;
  int iDCOfLastAssociated=-1;

  vector<PhotonMCTruth>::const_iterator iPho;

  int iDC=-1;

  for (iPho=mcPhotons.begin(); iPho !=mcPhotons.end(); ++iPho ) {
    if (prints) cout << "in loop over mc photons" << endl;
    simPhoR     = (*iPho).vertex().perp();
    simPhoZ     = (*iPho).vertex().z();
    simPhoEta   = (*iPho).fourMomentum().eta();
    simPhoPt    = (*iPho).fourMomentum().perp();
    simPhoPhi   = (*iPho).fourMomentum().phi();
    simPhoTheta = (*iPho).fourMomentum().theta();

    iDC++;
    
    //Is the sim photon is not valid? Yes: skip to next.
    if ( 
	! (((*iPho).isAConversion()) 
	   && 
	   simPhoPt>minPhoPtForPurity 
	   && 
	   fabs(simPhoEta)<maxPhoEtaForPurity 
	   && 
	   simPhoR<maxPhoRForPurity 
	   && 
	   fabs(simPhoZ)<maxPhoZForPurity) 
	) continue;
    
    //Is the sim photon vertex outside the Association cut? Yes: skip to next.
    if ( isSimVertexOutsideAssCut(vtx, *iPho) ) continue;
    
    double tmpDeltax = (*iPho).vertex().x()-vtx.position().x();
    double tmpDeltay = (*iPho).vertex().y()-vtx.position().y();
    double tmpDeltaz = (*iPho).vertex().z()-vtx.position().z();
    double distance3D = sqrt(tmpDeltax*tmpDeltax+tmpDeltay*tmpDeltay+tmpDeltaz*tmpDeltaz);

    //Is the current sim photon vertex farther? Yes: skip to next.
    if ( distance3D > oldDistance3D ) continue;
    oldDistance3D = distance3D;

    //Match is found
    iMatch = true;
    iDCOfLastAssociated = iDC;

    //Store relevant information for later
    deltax = tmpDeltax;
    deltay = tmpDeltay;
    deltaz = tmpDeltaz;
    deltaRho = photonMom.rho()-simPhoPt;
    deltaPhi = photonMom.phi()-simPhoPhi;
    deltaTheta = photonMom.theta()-simPhoTheta;
   
    
  }
  
  if ( iMatch ){ 
      fillR2SAssociation(doubleCounterCheck[iDCOfLastAssociated], deltaRho, deltaPhi, deltaTheta,
				   deltax, deltay, deltaz);
      doubleCounterCheck[iDCOfLastAssociated]=true;
  }
  
}


bool NewConversionNtuplizer::
isSimVertexOutsideAssCut(KinematicVertex& vtx, const PhotonMCTruth& iPho){

  bool myPrints = false;

  /*  double xSim = (*iPho).vertex().x();
  double ySim = (*iPho).vertex().y();
  double zSim = (*iPho).vertex().z();
  double x = vtx.position().x();
  double y = vtx.position().y();
  double z = vtx.position().z();
  */

  //Cut on Delta r
  double r = vtx.position().perp();
  double rSim = iPho.vertex().perp();
  double dr = r - rSim;

  if (myPrints) cout<< ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> New acc test" << endl;
  if (myPrints) cout<< " dr=" << dr << " eta=" << vtx.position().eta() << endl;

  if ( 
      (fabs(vtx.position().eta())<1.2 && (dr<-1.0 || dr>3.0))
      ||
      (fabs(vtx.position().eta())>1.2 && (dr<-2.0 || dr>6.0))
      ) return true; 
  
  //Cut on Delta theta
  double t = vtx.position().theta();
  double tSim = iPho.vertex().theta();
  double fabsDt = fabs(t - tSim);

  if (myPrints) cout<< " |dTheta|=" << fabsDt << " eta=" << vtx.position().eta() << endl;

  if ( 
      (fabs(vtx.position().eta())<1.4 && fabsDt>0.2)
      ||
      (fabs(vtx.position().eta())>1.4 && fabsDt>0.1)
      ) return true; 

//Cut on Delta phi
   double p = vtx.position().phi();
   double pSim = iPho.vertex().phi();
   double fabsDp = fabs(reco::deltaPhi(p, pSim));

   if (myPrints) cout<< " |dPhi|=" << fabsDp << " eta=" << vtx.position().eta() << endl;

   if ( 
      (fabs(vtx.position().eta())<1.2 && fabsDp>0.04)
      ||
      (fabs(vtx.position().eta())>1.2 && fabsDp>0.08)
      ) return true; 

if (myPrints) cout<< " Within acc cuts..." << endl;

return false;

}

void NewConversionNtuplizer::
AssociateByHit(const edm::Event& iEvent,const Conversion& conv){

  RefToBaseVector<Track> tc1, tc2;
  RefToBase<Track> tfrb1(conv.tracks().front());
  RefToBase<Track> tfrb2(conv.tracks().back());
  tc1.push_back(tfrb1);
  tc2.push_back(tfrb2);
  
  RefVector<TrackingParticleCollection> tpc(TPCollectionH.id());
  SearchTrackingParticleConversionCandidates(tpc);

  if (tpc.size()==0) return;
  
  RecoToSimCollection p1 = theAssociator->associateRecoToSim(tc1,tpc,&iEvent);
  RecoToSimCollection p2 = theAssociator->associateRecoToSim(tc2,tpc,&iEvent);
  std::vector<std::pair<TrackingParticleRef, double> > tp1, tp2;
  //std::vector<std::pair<TrackingParticleRef, double> > tp2 = p2[tfrb2];
  if (p1.find(tfrb1) != p1.end()){
    tp1 = p1[tfrb1];
  }
  if (p2.find(tfrb2) != p2.end()){
    tp2 = p2[tfrb2];
  }

  if ( tp1.size()  &&  tp2.size() ) {
    TrackingParticleRef tpr1 = tp1.front().first;
    TrackingParticleRef tpr2 = tp2.front().first;
    if (abs(tpr1->pdgId())==11   &&  abs(tpr2->pdgId())==11) {
      if ( 
	  (tpr1->parentVertex()->sourceTracks_end()-tpr1->parentVertex()->sourceTracks_begin()==1) 
	  && 
	  (tpr2->parentVertex()->sourceTracks_end()-tpr2->parentVertex()->sourceTracks_begin()==1)
	  ){
	if (
	    tpr1->parentVertex().key()==tpr2->parentVertex().key() 
	    && 
	    ((*tpr1->parentVertex()->sourceTracks_begin())->pdgId()==22)
	    ) {
	  /*
	    float simPhoR     = tpr1->parentVertex()->position().rho();
	    float simPhoZ     = tpr1->parentVertex()->position().z();
	    float simPhoEta   = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().eta();
	    float simPhoPt    = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().rho();
	    float simPhoPhi   = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().Phi();
	    float simPhoTheta = (*tpr1->parentVertex()->sourceTracks_begin())->momentum().Theta();
	  */
	  fillR2SAssociation(true);
	}
      }
    }
  }
} 



void NewConversionNtuplizer::
SearchTrackingParticleConversionCandidates( RefVector<TrackingParticleCollection>& tpc){
  for (unsigned int j=0; j<TPCollectionH->size();j++) {
    Ref<TrackingParticleCollection> tptest(TPCollectionH,j);
    if (
	abs(tptest->pdgId())==11 
	&& 
	(tptest->parentVertex()->sourceTracks_end()-tptest->parentVertex()->sourceTracks_begin()==1) 
	&& 
	(*tptest->parentVertex()->sourceTracks_begin())->pdgId()==22 ) {
      
      double tmpSimPhoR   = tptest->parentVertex()->position().rho();
      double tmpSimPhoZ   = tptest->parentVertex()->position().z();
      double tmpSimPhoEta = (*tptest->parentVertex()->sourceTracks_begin())->momentum().eta();
      double tmpSimPhoPt  = (*tptest->parentVertex()->sourceTracks_begin())->momentum().rho();
      //double tmpSimPhoPhi = (*tptest->parentVertex()->sourceTracks_begin())->momentum().Phi();
      //double tmpSimPhoTheta = (*tptest->parentVertex()->sourceTracks_begin())->momentum().Theta();
      if (
	  tmpSimPhoPt>minPhoPtForPurity 
	   && 
	  fabs(tmpSimPhoEta)<maxPhoEtaForPurity 
	  &&
	  tmpSimPhoR<maxPhoRForPurity 
	  && 
	  fabs(tmpSimPhoZ)<maxPhoZForPurity ) {
	tpc.push_back(tptest);
      }
    }
  }
}

//TO BE FIXED
bool NewConversionNtuplizer::checkSimToRecoAssociation(const edm::Event& iEvent, const Conversion& conv, RefVector<TrackingParticleCollection>& tpc,KinematicVertex& vtx,const PhotonMCTruth& Pho){
  if (hitassoc) {

    RefToBaseVector<Track> tc1, tc2;
    tc1.push_back(RefToBase<Track>(conv.tracks().front()));
    tc2.push_back(RefToBase<Track>(conv.tracks().back ()));

    if (prints) cout << "associating tc1.size()=" << tc1.size() << " tpc.size()=" << tpc.size() << endl;
    if (prints) cout << "associating tc2.size()=" << tc2.size() << " tpc.size()=" << tpc.size() << endl;

    SimToRecoCollection q1 = theAssociator->associateSimToReco(tc1,tpc,&iEvent);
    SimToRecoCollection q2 = theAssociator->associateSimToReco(tc2,tpc,&iEvent);
    std::vector<std::pair<RefToBase<reco::Track>, double> > trackV1, trackV2;

    if (q1.find(tpc[0])!=q1.end()){
      trackV1 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q1[tpc[0]];
    } else if (q1.find(tpc[1])!=q1.end()){
      trackV1 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q1[tpc[1]];
    }
    if (q2.find(tpc[1])!=q2.end()){
      trackV2 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q2[tpc[1]];
    } else if (q2.find(tpc[0])!=q2.end()){
      trackV2 = (std::vector<std::pair<RefToBase<reco::Track>, double> >) q2[tpc[0]];
    }
    if (!(trackV1.size()&&trackV2.size())) return false;

    if (prints) {
      RefToBase<Track> tr1 = trackV1.front().first;
      RefToBase<Track> tr2 = trackV2.front().first;
      std::cout << "sim converted photon with p=" << (Pho).fourMomentum() << " (pt=" << (Pho).fourMomentum().perp()
			  << ") associated to reco conversion with p=" << tr1->momentum()+tr2->momentum() << endl;
    }

    return true;

  } else {


    float deltaX = Pho.vertex().x()-vtx.position().x();
    float deltaY = Pho.vertex().y()-vtx.position().y();
    float deltaZ = Pho.vertex().z()-vtx.position().z();

    if (fabs(deltaX)>5. || fabs(deltaY)>5. || fabs(deltaZ)>5.) return false;
    return true;



  }
}


void NewConversionNtuplizer::fillS2R(const Conversion& conv,KinematicVertex& vtx,const PhotonMCTruth& Pho){ 
  
  const edm::RefToBase<reco::Track> tk[2] = {conv.tracks().front(),conv.tracks().back()};
  math::XYZVector photonMom = tk[0]->momentum()+tk[1]->momentum();
  
  for(size_t i=0;i<2;i++){

    if (retracking){//if re-doing the tracking to test the dedicated tracking step. 
      //NOTE retracking should be set to False if reading conversions out of box because trajectory is not stored in RECO
      PTrajectoryStateOnDet state = tk[i]->seedRef()->startingState();
      DetId detId(state.detId());
      TrajectoryStateOnSurface tsos(trajectoryStateTransform::transientState( state, &(trackerGeom->idToDet(detId)->surface()), magField));

      s2rbranch.seedLeg[i].q     = state.parameters().charge();	  
      s2rbranch.seedLeg[i].pt    = tsos.globalMomentum().perp();	  
      s2rbranch.seedLeg[i].phi   = tsos.globalMomentum().phi();	  
      s2rbranch.seedLeg[i].theta = tsos.globalMomentum().theta();	  
      s2rbranch.seedLeg[i].r     = tsos.globalPosition().perp();	  
      s2rbranch.seedLeg[i].z     = tsos.globalPosition().z();	  
    }  
    
    s2rbranch.recoLeg[i].algo     = tk[i]->algo();                       
    s2rbranch.recoLeg[i].pt       = tk[i]->pt();
    s2rbranch.recoLeg[i].theta    = tk[i]->theta();
    s2rbranch.recoLeg[i].chi2     = tk[i]->normalizedChi2();
   
    s2rbranch.extrasLeg[i].nHits     = tk[i]->numberOfValidHits();
    s2rbranch.extrasLeg[i].missHits     = tk[i]->lost();
    s2rbranch.extrasLeg[i].beforeHits   = getBeforeHit(tk[i], vtx.position().perp(), vtx.position().z());

    if ((dataType == "MCRECO") || (dataType == "DATARECO"))
      {
	float iphi = -999.;
	//	GlobalVector ip = getStateAtVertex(tk[i],vtx.position().perp(),vtx.position().z(),iphi);
	s2rbranch.stateAtVertexLeg[i].phi = iphi;
	
	if (valid_pvtx) s2rbranch.recoLeg[i].d0 = - tk[i]->dxy(the_pvtx.position());
	else s2rbranch.recoLeg[i].d0 = tk[i]->d0();
      }
  }   
  
  s2rbranch.convvtx.isAssoc   =1;
  	    
  s2rbranch.convvtx.deltax    = Pho.vertex().x()-vtx.position().x(); 
  s2rbranch.convvtx.deltay    = Pho.vertex().y()-vtx.position().y();
  s2rbranch.convvtx.deltaz    = Pho.vertex().z()-vtx.position().z();
      	    
  s2rbranch.convvtx.deltapt     = photonMom.rho()   -  Pho.fourMomentum().perp();
  s2rbranch.convvtx.deltaphi    = photonMom.phi()   -  Pho.fourMomentum().phi();
  s2rbranch.convvtx.deltatheta  = photonMom.theta() -  Pho.fourMomentum().theta();
  	    
  s2rbranch.convvtx.chi2prob = ChiSquaredProbability(vtx.chiSquared(), vtx.degreesOfFreedom());
  s2rbranch.convvtx.minapp = conv.distOfMinimumApproach();
}
//define this as a plug-in
DEFINE_FWK_MODULE(NewConversionNtuplizer);
