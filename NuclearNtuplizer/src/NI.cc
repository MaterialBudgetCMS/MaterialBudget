// -*- C++ -*-

// Nuclear interaction finder on AOD

// Original Author:  Daniel Pitzl
//         Created:  Sun, 26 Feb 2017

// system include files:
#include <memory>
#include <cmath> // Pow

// ROOT:
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"

// CMS include files:
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

//------------------------------------------------------------------------------
// class declaration:
class NI : public edm::one::EDAnalyzer<edm::one::SharedResources> {

public:
  explicit NI(const edm::ParameterSet&);
  ~NI();

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

  static unsigned neve;
  static unsigned prevrun;
  static unsigned prevLB;

  edm::EDGetTokenT <reco::VertexCollection> tVertexCollection;
  edm::EDGetTokenT <reco::TrackCollection> tTrackCollection;

  TH1D * hnvx;
  TH1D *h010, *h011, *h012, *h013, *h014, *h015, *h016, *h017, *h018, *h019;
  TH1D *h020, *h021, *h022, *h023, *h024, *h025, *h026, *h027, *h028, *h029;

  TH1D *h100, *h101, *h102, *h103, *h104, *h105, *h106, *h107, *h108, *h109;
  TH1D * hds;
  TH1D * hdphi;
  TH1D * hdzi;
  TH1D * hdzic;
  TH1D * hdsc;
  TH1D * hdf;
  TH2D * hgxy;

  TH1D *h110, *h111, *h112, *h113, *h114, *h115, *h116, *h117, *h118, *h119;
  TH1D *h120, *h121, *h122, *h123, *h124, *h125, *h126, *h127, *h128, *h129;
  TH1D *h130, *h131, *h132, *h133;
  TH2D *h134;

}; // class

// constants, enums and typedefs

// static data member definitions

unsigned NI::neve = 0; // declared static above
unsigned NI::prevrun = 0;
unsigned NI::prevLB = 0;

//------------------------------------------------------------------------------
// constructor:
NI::NI(const edm::ParameterSet& iConfig)
{
  std::cout << "NI constructed" << std::endl;

  tVertexCollection = consumes<reco::VertexCollection>( edm::InputTag( "offlinePrimaryVertices" ) );
  //tVertexCollection = consumes<reco::VertexCollection>( edm::InputTag( "offlinePrimaryVerticesWithBS" ) );

  tTrackCollection = consumes<reco::TrackCollection>( edm::InputTag( "generalTracks" ) );

  usesResource( "TFileService" );
  edm::Service <TFileService> fs;

  hnvx = fs->make<TH1D>( "nvx", "primary vertices;primary vertices;events", 51, -0.5, 50.5 );

  h011 = fs->make<TH1D>( "h011", "invalid z-vertex;z [mm]", 100, -500, 500 );
  h012 = fs->make<TH1D>( "h012", "fake z-vertex;z [mm]", 100, -500, 500 );
  h013 = fs->make<TH1D>( "h013", "non-fake z-vertex;z [mm]", 100, -500, 500 );
  h014 = fs->make<TH1D>( "h014", "vertex x;x [mm]", 100, -5, 5 );
  h015 = fs->make<TH1D>( "h015", "vertex y;y [mm]", 100, -5, 5 );
  h016 = fs->make<TH1D>( "h016", "tracks per vertex;tracks;vertices", 51, -0.5, 50.5 );
  h017 = fs->make<TH1D>( "h017", "tracks per vertex;tracks;vertices", 100, 0, 500 );

  h021 = fs->make<TH1D>( "h021", "vertex sum pt;sum pt [GeV]", 100, 0, 100 );
  h022 = fs->make<TH1D>( "h022", "vertex max sum pt;max sum pt [GeV]", 100, 0, 100 );

  h023 = fs->make<TH1D>( "h023", "best vertex x;x [mm]", 100, -2.5, 2.5 );
  h024 = fs->make<TH1D>( "h024", "best vertex y;y [mm]", 100, -2.5, 2.5 );
  h025 = fs->make<TH1D>( "h025", "best vertex z;z [mm]", 100, -250, 250 );

  // intersects

  h100 = fs->make<TH1D>( "h100", "track dcap;dca(PV) [mm];tracks", 100, -50, 50 );
  h101 = fs->make<TH1D>( "h101", "track edcap;error dca [mm];tracks", 100, 0, 1 );
  h102 = fs->make<TH1D>( "h102", "track sdcap;dca(PV)/error;tracks", 100, -10, 10 );

  hds   = fs->make<TH1D>( "ds", "track distance;track distance [mm];track pairs", 100, -50, 50 );
  hdphi = fs->make<TH1D>( "dphi", "difference track direction;#Delta phi [mrad];track pairs", 100, -1, 1 );
  hdzi  = fs->make<TH1D>( "dzi", "intersect dz;dz [mm];track pairs", 100, -5, 5 );
  hdzic = fs->make<TH1D>( "dzic", "intersect dz, cut ds;dz [mm];track pairs", 100, -5, 5 );
  hdsc  = fs->make<TH1D>( "dsc", "track distance, cut dz;track distance [mm];track pairs", 100, -10, 10 );
  hdf   = fs->make<TH1D>( "df", "flight direction - momentum direction;#alpha [deg];track pairs", 100, -5, 5 );
  hgxy  = fs->make<TH2D>( "gxy", "Conv x-y, z < 260 mm;-x [mm];y [mm];Conversions",
			  340, -85, 85, 340, -85, 85 );

  h111 = fs->make<TH1D>( "h111", "r(NI);intersect radius [mm];combinations", 200, 0, 200 );
  h112 = fs->make<TH1D>( "h112", "turn angle to SV;turn angle to SV [mrad];candidates", 100, -50, 50 );
  h113 = fs->make<TH1D>( "h113", "NI dz(SV);dz(SV) [mm];candidates", 100, -5, 5 );
  h114 = fs->make<TH1D>( "h114", "NI sdz(SV);dz(SV)/edz;candidates", 100, -10, 10 );
  h115 = fs->make<TH1D>( "h115", "opening angle;intersect opening angle [rad];combinations", 200, -1, 1 );
  h116 = fs->make<TH1D>( "h116", "r(NI), dz/edz < 3;intersect radius [mm];combinations", 200, 0, 200 );

  h121 = fs->make<TH1D>( "h121", "dca3(SV);dca(SV) [mm];3rd track", 100, -5, 5 );
  h122 = fs->make<TH1D>( "h122", "dz3(SV);dz(SV) [mm];3rd track", 100, -5, 5 );
  h123 = fs->make<TH1D>( "h123", "sdz3(SV);dz(SV)/edz;3rd track", 100, -10, 10 );
  h124 = fs->make<TH1D>( "h124", "dca3(SV), sdz3 < 3;dca(SV) [mm];3rd track", 100, -5, 5 );

  h125 = fs->make<TH1D>( "h125", "z(NI3), dca3 < 0.5 mm;NI z [mm];NI3", 300, -300, 300 );

  h126 = fs->make<TH1D>( "h126", "pt NI;pt [GeV];NI tracks", 100, 0, 5 );
  h127 = fs->make<TH1D>( "h127", "dca NI;dca [cm];NI tracks", 120, -3, 3 );

  h130 = fs->make<TH1D>( "h130", "r(NI3), dca3 < 0.5 mm, z < 260 mm;NI radius [mm];NI3", 400, 0, 200 );
  h131 = fs->make<TH1D>( "h131", "r(NI3), all pt > 0.5;NI radius [mm];NI3", 400, 0, 200 );
  h132 = fs->make<TH1D>( "h132", "r(NI3), one pt < 0.5;NI radius [mm];NI3", 400, 0, 200 );
  h133 = fs->make<TH1D>( "h133", "phi(NI3), BPix 1, Z < 260 mm;NI phi [deg];NI3", 180, -180, 180 );
  h134 = fs->make<TH2D>( "h134", "NI x-y, z < 260 mm;NI -x [mm];NI y [mm];NI3", 200, -50, 50, 200, -50, 50 );

} // constructor

//------------------------------------------------------------------------------
// destructor:
NI::~NI()
{
}

//------------------------------------------------------------------------------
// method called once each job just before starting event loop:
void NI::beginJob()
{
  std::cout << "NI beginJob" << std::endl;
}

//------------------------------------------------------------------------------
// method called for each event:
void NI::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup )
{
  const double pihalf = 2*atan(1);
  const double pi = 2*pihalf;
  const double twopi = 2*pi;
  const double wt = 180/pi;

  const double Bfac = 0.2998E-2 * 3.8112; // pt = cq R[cm] B[T] CMS

  const double xBP = 0.13; // [cm] 2017
  const double yBP =-0.20; // [cm] 2017

  neve++;
  if( prevrun != iEvent.run() ) {
    std::cout << "run " << iEvent.run() << std::endl;
    prevrun = iEvent.run();
  }
  if( prevLB != iEvent.luminosityBlock() ) {
    std::cout << " LB " << iEvent.luminosityBlock() << std::endl;
    prevLB = iEvent.luminosityBlock();
  }

  //----------------------------------------------------------------------------
  // primary vertices:

  edm::Handle <reco::VertexCollection> hvc;

  iEvent.getByToken( tVertexCollection, hvc );

  if( hvc.failedToGet() ) return;
  if( !hvc.isValid() ) return;

  const reco::VertexCollection * vertices = hvc.product();

  hnvx->Fill( vertices->size() );

  math::XYZPoint vtxP( 0, 0, 0 );
  double maxSumPt = 0;

  for( reco::VertexCollection::const_iterator iVertex = vertices->begin();
      iVertex != vertices->end(); ++iVertex ) {

    if( ! iVertex->isValid() ) {
      h011->Fill( iVertex->z()*10 );
      continue;
    }

    if( iVertex->isFake() ) {
      h012->Fill( iVertex->z()*10 );
      continue;
    }

    // valid non-fake:

    h013->Fill( iVertex->z()*10 );
    h014->Fill( iVertex->x()*10 );
    h015->Fill( iVertex->y()*10 );
    h016->Fill( iVertex->ndof() );
    h017->Fill( iVertex->ndof() );

    h021->Fill( iVertex->p4().pt() );

    if( iVertex->p4().pt() > maxSumPt ) {
      maxSumPt = iVertex->p4().pt();
      vtxP = math::XYZPoint( iVertex->x(), iVertex->y(), iVertex->z() );
    }

  } // vertices

  h022->Fill( maxSumPt );

  if( maxSumPt < 1 ) return;

  h023->Fill( vtxP.x()*10 );
  h024->Fill( vtxP.y()*10 );
  h025->Fill( vtxP.z()*10 );

  double xP = vtxP.x();
  double yP = vtxP.y();
  //double zP = vtxP.z();

  math::XYZPoint O( 0, 0, 0 ); // origin

  //----------------------------------------------------------------------------
  // tracks:

  edm::Handle <reco::TrackCollection> htc;
  iEvent.getByToken( tTrackCollection, htc );
  if( htc.failedToGet() ) return;
  if( !htc.isValid() ) return;
  const reco::TrackCollection * tracks = htc.product();

  for( reco::TrackCollection::const_iterator kTrack = tracks->begin();
       kTrack != tracks->end(); ++kTrack ) {

    double sdxy3 = kTrack->dxy(vtxP) / kTrack->dxyError();

    h100->Fill( kTrack->dxy(vtxP)*10 ); // cut at +- 15 mm
    h101->Fill( kTrack->dxyError()*10 );
    h102->Fill( sdxy3 );

    if( fabs( sdxy3 ) < 3 ) continue; // don't want primary tracks

    double px3 = kTrack->px();
    double py3 = kTrack->py();
    double pt3 = kTrack->pt();

    double rho3 =-kTrack->charge()*pt3/Bfac; // signed track radius [cm]
    double phi3 = kTrack->phi();
    //double eta3 = kTrack->eta();
    double dca3 = kTrack->d0(); // [cm] w.r.t. O
    //double dca3 =-kTrack->dxy(O); // [cm] w.r.t. O, Blobel sign
    double xc3 = ( dca3 - rho3 ) * sin( phi3 ); // circle center from O
    double yc3 = ( rho3 - dca3 ) * cos( phi3 );
    double z03 = kTrack->dz(O); // [cm] w.r.t. O
    double tet3 = kTrack->theta();
    double ez03 = kTrack->dzError();

    // 2nd track:

    for( reco::TrackCollection::const_iterator lTrack = kTrack + 1; // upper triangle loop
	 lTrack != tracks->end(); ++lTrack ) {

      if( lTrack->charge() == kTrack->charge() ) continue; // want opposite charges

      double sdxy4 = lTrack->dxy(vtxP) / lTrack->dxyError();

      if( fabs( sdxy4 ) < 3 ) continue; // don't want primary tracks

      double px4 = lTrack->px();
      double py4 = lTrack->py();
      double pt4 = lTrack->pt();

      double rho4 =-lTrack->charge()*pt4/Bfac; // signed track radius [cm]
      double phi4 = lTrack->phi();
      //double eta4 = lTrack->eta();
      double dca4 = lTrack->d0(); // [cm] w.r.t. O
      //double dca4 =-lTrack->dxy(O); // [cm] w.r.t. O, Blobel sign
      double xc4 = ( dca4 - rho4 ) * sin( phi4 ); // circle center from O
      double yc4 = ( rho4 - dca4 ) * cos( phi4 );

      double z04 = lTrack->dz(O); // [cm] w.r.t. O
      double tet4 = lTrack->theta();
      double ez04 = lTrack->dzError();

      // Intersecting circles: (trsec.f from O. Behnke)

      double dx = xc3 - xc4; // x distance of circle centers
      double dy = yc3 - yc4;
      double dd = sqrt( dx*dx + dy*dy ); // distance of circle centers
      double sr = fabs(rho3) + fabs(rho4); // sum of circle radii, abs in CMSSW truncates to int
      double dr = fabs(rho3) - fabs(rho4); // difference of circle radii

      if( dd < dr ) continue; // enclosed circles

      double x0, y0; // from O

      // conversions = touching cicles

      double ds = dd - sr;
      hds->Fill( ds*10 );

      if( fabs(ds)*10 < 10 ) {
	
	double aa = 0.5 * ( dd + fabs(rho4)-fabs(rho3) ) / dd; // Karin Daum 2008

	double xx = xc4 + aa*dx;
	double yy = yc4 + aa*dy; // mid point between circles
	double rr = sqrt( xx*xx + yy*yy );
	//double ff = atan2( yy, xx );

	if( rr*10 > 10 ) {

	  double lx = xx-xP;
	  double ly = yy-yP;
	  double lf = atan2( ly, lx ); // flight direction from beam

	  // arc length:

	  double a03 = atan2(  0-yc3,  0-xc3 ); // from center to O
	  double a13 = atan2( yy-yc3, xx-xc3 ); // from center to intersect
	  double da3 = a13-a03;
	  if( da3 > pi )
	    da3 -= twopi;
	  else if( da3 < -pi )
	    da3 += twopi;
	  double zi3 = z03 + rho3 * da3 * tan(pihalf-tet3);
	  phi3 = kTrack->phi() + da3; // don't accumulate corrections

	  if( fabs(zi3)*10 < 270 ) {

	    double a04 = atan2(  0-yc4,  0-xc4 ); // from center to O
	    double a14 = atan2( yy-yc4, xx-xc4 ); // from center to intersect
	    double da4 = a14-a04;
	    if( da4 > pi )
	      da4 -= twopi;
	    else if( da4 < -pi )
	      da4 += twopi;
	    double zi4 = z04 + rho4 * da4 * tan(pihalf-tet4);
	    phi4 = lTrack->phi() + da4;

	    hdphi->Fill( (phi4-phi3)*1E3 ); // zero by construction

	    double df = phi4 - lf; // momenum direction - flight direction
	    if( df > pi )
	      df -= twopi;
	    else if( df < -pi )
	      df += twopi;

	    double dzi = zi4 - zi3;
	    hdzi->Fill( dzi*10 ); // [mm]

	    if( fabs(ds)*10 < 0.5 )
	      hdzic->Fill( dzi*10 ); // [mm]

	    if( fabs(dzi)*10 < 0.2 ) { // was 0.5

	      hdsc->Fill( ds*10 );

	      if( fabs(ds)*10 < 0.5 ) {

		hdf->Fill( df*wt );

		if( fabs(df)*wt < 0.7 ) { // was 1

		  hgxy->Fill( -xx*10, yy*10 );

		} // df

	      } // ds

	    } // dz

	  } // z

	} // rr

      } // ds

      if( dd > sr + 0.5 ) continue; // separated circles too far apart

      if( dd > sr ) { // Separated circles, put intersect in middle of gap
	double aa = 0.5 * ( dd + fabs(rho4)-fabs(rho3) ) / dd; // Karin Daum 2008
	x0 = xc4 + aa*dx;
	y0 = yc4 + aa*dy;
      }
      else {
	// The line joining the 2 intersects is perpendicular
	// to the line joining the circle centers and divides it into
	// D1 + D2 = DD
	// The Gegenkathete of the triangle R2-D2 is cc
	// The Gegenkathete of the triangle R1-D1 is also cc
	// Apply Pythagoras to both and solve for cc:

	double bb = 0.5 * ( dd*dd - rho3*rho3 + rho4*rho4 ) / dd;
	double c2 = rho4*rho4 - bb*bb;
	if( c2 < 0 ) continue; // should not happen
	double cc = sqrt(c2);

	// 2 intersect solutions:

	double px0 = px3 + px4;
	double py0 = py3 + py4;

	double xi1 = xc4 + ( bb*dx + cc*dy ) / dd; // from O
	double yi1 = yc4 + ( bb*dy - cc*dx ) / dd;
	double ri1 = sqrt( xi1*xi1 + yi1*yi1 ); // from O
	//double fi1 = atan2( yi1, xi1 ); // position anmgle from O
	double sprod1 = (xi1-xP) * px0 + (yi1-yP) * py0; // from PV

	double xi2 = xc4 + ( bb*dx - cc*dy ) / dd;
	double yi2 = yc4 + ( bb*dy + cc*dx ) / dd;
	double ri2 = sqrt( xi2*xi2 + yi2*yi2 );
	//double fi2 = atan2( yi2, xi2 );
	double sprod2 = (xi2-xP) * px0 + (yi2-yP) * py0; // from PV

	// take the inner intersect if it is forward decay:

	// better: take the closer in z

	if( ri1 < ri2 ) {
	  if( sprod1 > 0 || sprod2 < 0 ) {
	    x0 = xi1; // from O
	    y0 = yi1;
	  }
	  else {
	    x0 = xi2;
	    y0 = yi2;
	  }
	}
	else {
	  if( sprod2 > 0 || sprod1 < 0 ) {
	    x0 = xi2;
	    y0 = yi2;
	  }
	  else {
	    x0 = xi1;
	    y0 = yi1;
	  }
	}

      } // circle cases

      // SV: x0, y0

      double r0 = sqrt( x0*x0 + y0*y0 ); // from origin
      h111->Fill( r0*10 );

      if( r0*10 < 15 ) continue; // don't want inside beam pipe

      // arc length:

      double a03 = atan2(  0-yc3,  0-xc3 ); // from center to O
      double a13 = atan2( y0-yc3, x0-xc3 ); // from center to intersect
      double da3 = a13-a03;
      if( da3 > pi )
	da3 = da3 - twopi;
      else if( da3 < -pi )
	da3 = da3 + twopi;
      h112->Fill( da3*1E3 ); // [mrad]
      double zi3 = z03 + rho3 * da3 * tan(pihalf-tet3);

      double a04 = atan2(  0-yc4,  0-xc4 ); // from center to O
      double a14 = atan2( y0-yc4, x0-xc4 ); // from center to intersect
      double da4 = a14-a04;
      if( da4 > pi )
	da4 = da4 - twopi;
      else if( da4 < -pi )
	da4 = da4 + twopi;
      h112->Fill( da4*1E3 ); // [mrad]
      double zi4 = z04 + rho4 * da4 * tan(pihalf-tet4);

      double dz34 = zi4 - zi3;
      h113->Fill( dz34*10 ); // [mm], peak

      double edz34 = sqrt( ez03*ez03 + ez04*ez04 );
      h114->Fill( dz34/edz34 ); // washed out

      if( fabs(dz34/edz34) > 3 ) continue;
      if( fabs(dz34)*10 > 0.3 ) continue; // [mm]

      phi3 = kTrack->phi() + da3; // don't accumulate corrections
      phi4 = lTrack->phi() + da4;

      double dphi = phi3 - phi4;
      if( dphi > pi )
	dphi = dphi - twopi;
      else if( dphi < -pi )
	dphi = dphi + twopi;

      h115->Fill( dphi ); // [rad], spike at zero ?
      if( fabs( dphi ) < 0.050 ) continue; // opening angle = intersect resolution
      if( fabs( dphi ) < 0.100 ) continue; // opening angle = intersect resolution

      h116->Fill( r0*10 );

      double z0 = 0.5*(zi3+zi4);

      //math::XYZPoint NIvx( x0, y0, z0 ); // from origin

      //double f0 = atan2( y0, x0 ); // azimuth from origin
      double fBP = atan2( y0-yBP, x0-xBP ); // azimuth from BP center
      double rBP = sqrt( pow( x0-xBP, 2 ) + pow( y0-yBP, 2 ) ); // from BP center

      // 3rd track:

      for( reco::TrackCollection::const_iterator mTrack = tracks->begin();
	   mTrack != tracks->end(); ++mTrack ) {

	if( mTrack == kTrack ) continue;
	if( mTrack == lTrack ) continue;

	double sdxy5 = mTrack->dxy(vtxP) / mTrack->dxyError();

	if( fabs( sdxy5 ) < 3 ) continue; // don't want primary tracks

	double pt5 = mTrack->pt();
	double rho5 =-mTrack->charge()*pt5/Bfac; // signed track radius [cm]
	double phi5 = mTrack->phi(); // at origin
	double dca5 = mTrack->d0(); // [cm] w.r.t. O
	double xc5 = ( dca5 - rho5 ) * sin( phi5 ); // circle center from O
	double yc5 = ( rho5 - dca5 ) * cos( phi5 );

	double dx5 = xc5 - x0; // center to SV
	double dy5 = yc5 - y0;
	double dca5sv = sqrt( dx5*dx5 + dy5*dy5 ) - fabs(rho5); // random sign

	h121->Fill( dca5sv*10 ); // [mm]

	double z05 = mTrack->dz(O); // [cm] w.r.t. O
	double tet5 = mTrack->theta();
	double ez05 = mTrack->dzError();

	// Move track 5 to intersect:

	double a05 = atan2(  0-yc5,  0-xc5 ); // from center to O
	double a15 = atan2( y0-yc5, x0-xc5 ); // from center to intersect
	double da5 = a15-a05;
	if( da5 > pi )
	  da5 = da5 - twopi;
	else if( da5 < -pi )
	  da5 = da5 + twopi;
	double zi5 = z05 + rho5 * da5 * tan(pihalf-tet5);
	phi5 += da5; // at intersect

	double dz05 = zi5 - z0;
	double edz05 = sqrt( ez03*ez03 + ez04*ez04 + ez05*ez05 );

	if( fabs( dca5sv )*10 < 0.25 ) {
	  h122->Fill( dz05*10 ); // [mm]
	  h123->Fill( dz05/edz05 ); // [mm]
	}

	if( fabs( dz05*10 ) > 0.3 ) continue; // [mm]

	h124->Fill( dca5sv*10 ); // [mm]

	if( fabs( dca5sv*10 ) > 0.25 ) continue; // [mm]

	double zni = ( zi3 + zi4 + zi5 ) / 3;

	h125->Fill( zni*10 );

	if( fabs(zni)*10 < 260 ) {

	  h126->Fill( pt3 );
	  h126->Fill( pt4 );
	  h126->Fill( pt5 );
	  h127->Fill( dca3 );
	  h127->Fill( dca4 );
	  h127->Fill( dca5 );

	  h130->Fill( rBP*10 );

	  if( pt3 > 0.5 && pt4 > 0.5 && pt5 > 0.5 )
	    h131->Fill( rBP*10 ); // not better
	  else
	    h132->Fill( rBP*10 );

	  //if( rBP*10 > 39 && rBP*10 < 48 ) // old BPix L1
	  if( rBP*10 < 40 ) // phase I BPix L1
	    h133->Fill( fBP*wt );

	  h134->Fill( -x0*10, y0*10 );

	} // zni

	// task: 3-track vertex fit

      } // mtrack 3

    } // ltrack 2

  } // ktrack 1

} // analyze

//------------------------------------------------------------------------------
void NI::endJob() 
{
  std::cout << "events " << neve << std::endl;
}

//------------------------------------------------------------------------------
void NI::fillDescriptions( edm::ConfigurationDescriptions& descriptions )
{
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(NI);
