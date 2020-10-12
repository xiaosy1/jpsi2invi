// -*- C++ -*-
//
//
// Description: J/psi -> Invisible 
//
// Original Author:  SHI Xin <shixin@ihep.ac.cn>
//         Created:  [2016-03-23 Wed 09:12] 
//         Inspired by Zhu Kai and Zhang Chi's code 
//
// Modified to : Psip->pi+pi-J/psi, J/psi -> eta(->2gamma) + gamma  by R. Kiuchi

//
// system include files
//


#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/DeclareFactoryEntries.h"
#include "GaudiKernel/LoadFactoryEntries.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"

#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/ThreeVector.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/Helix.h"
#include "VertexFit/WTrackParameter.h"
//#include "VertexFit/VertexFit.h"
#include "VertexFit/KalmanKinematicFit.h"
#include "VertexFit/SecondVertexFit.h"
#include "VertexFit/KinematicFit.h"

#include "ParticleID/ParticleID.h"
#include "McTruth/McParticle.h"

#include "TrigEvent/TrigEvent.h"
#include "TrigEvent/TrigData.h"

#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

//
// class declaration
//

class Jpsi2geta : public Algorithm {
  
public:
  Jpsi2geta(const std::string&, ISvcLocator*);
  ~Jpsi2geta(); 
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:
  // declare r0, z0 cut for charged tracks
  double m_ecms; 
  double m_vr0cut, m_vz0cut;
  // double m_distin_pionlep;
  double m_cha_costheta_cut; 
  double m_total_number_of_charged_max; 
  double m_min_emctime;
  double m_max_emctime;
  double m_gammaCosCut; 
  double m_costheta_barrel_max;
  double m_costheta_endcap_min;
  double m_costheta_endcap_max;
  double m_energy_barrel_min;
  double m_energy_endcap_min;
  double m_photon_iso_angle_min;
  double m_pion_polar_angle_max;
  double m_pion_momentum_max;
  double m_prob_pion_min;
  double m_dipion_mass_min; 
  double m_dipion_mass_max;
  double m_pipi_costheta_max;
  double m_pipisys_costheta_max; 

  // output file
  std::string m_output_filename;
  bool m_isMonteCarlo; 
  bool m_isZCcondition;
  TFile* m_fout; 
  
  // define Histograms
  TH1F* h_evtflw; 
  
  // define Trees
  TTree* m_tree;

  // common info 
  int m_run;
  int m_event;

  // charged tracks
  int m_ncharged;
  int m_nptrk;
  int m_nmtrk;
  double m_trkp_p; 
  double m_trkp_px; 
  double m_trkp_py; 
  double m_trkp_pz; 
  double m_trkp_theta; 
  double m_trkp_phi; 
  double m_trkp_eraw; 
  
  double m_trkm_p; 
  double m_trkm_px; 
  double m_trkm_py; 
  double m_trkm_pz; 
  double m_trkm_theta; 
  double m_trkm_phi; 
  double m_trkm_eraw; 

  // neutral tracks
  int m_nshow;
  int m_ngam;
  std::vector<double> *m_raw_gpx; 
  std::vector<double> *m_raw_gpy; 
  std::vector<double> *m_raw_gpz; 
  std::vector<double> *m_raw_ge; 

  std::vector<double> *m_raw_phi;
  std::vector<double> *m_raw_theta;
  std::vector<double> *m_raw_costheta;
  std::vector<int> *m_raw_cstat;
  std::vector<int> *m_raw_nhit;       
  std::vector<int> *m_raw_module;
  std::vector<double> *m_raw_secmom;
  std::vector<double> *m_raw_time;       
  
  // vertex 
  double m_vr0;
  double m_vz0;

  // PID info
  double m_prob_pip;
  double m_prob_pim;
  double m_prob_kp;
  double m_prob_km;
  double m_prob_p; 
  double m_prob_pb; 

  // pion info
  double m_pip_px;
  double m_pip_py;
  double m_pip_pz;

  double m_pim_px;
  double m_pim_py;
  double m_pim_pz;

  // fitted info
  double m_vtx_pip_px; 
  double m_vtx_pip_py; 
  double m_vtx_pip_pz; 
  double m_vtx_pip_p; 
  double m_vtx_pip_e;
  double m_vtx_pip_costheta;
  double m_vtx_pip_phi;

  double m_vtx_pim_px; 
  double m_vtx_pim_py; 
  double m_vtx_pim_pz; 
  double m_vtx_pim_p; 
  double m_vtx_pim_e;
  double m_vtx_pim_costheta;
  double m_vtx_pim_phi;

  double m_vtx_mpipi;
  double m_vtx_mrecpipi;
  double m_vtx_cospipi;
  double m_vtx_cos2pisys; 

  WTrackParameter wpip;
  WTrackParameter wpim;
   
  // kinematic fit info
  double m_kmfit_chisq;
  double m_kmfit_g1g2dang;
  double m_kmfit_g1g3dang;
  double m_kmfit_g2g3dang;
  
  double m_kmfit_g1_gpx;
  double m_kmfit_g1_gpy;
  double m_kmfit_g1_gpz;
  double m_kmfit_g1_ge;
  
  double m_kmfit_g2_gpx;
  double m_kmfit_g2_gpy;
  double m_kmfit_g2_gpz;
  double m_kmfit_g2_ge;
  
  double m_kmfit_g3_gpx;
  double m_kmfit_g3_gpy;
  double m_kmfit_g3_gpz;
  double m_kmfit_g3_ge;
  
  double m_kmfit_m_g1g2;
  double m_kmfit_m_g1g3;
  double m_kmfit_m_g2g3;
  
  double m_kmfit_m_pipig1g2;
  double m_kmfit_m_pipig1g3;
  double m_kmfit_m_pipig2g3;
  
  double m_kmfit_mrecpipi;
  double m_kmfit_mpipi;
  double m_kmfit_cospipi;
  double m_kmfit_cos2pisys;

    
  // trigger info
  int m_trig_condition[48];
  int m_trig_channel[16];
  int m_trig_timewindow;
  int m_trig_timetype;

  
  // check MDC and EMC match
  long m_pion_matched;
  long m_lep_matched;

  // jpsi2invi
  int m_ntrk; 
  int m_npho;

  //  MC truth info
  int m_indexmc;
  int m_pdgid[100];
  int m_trkidx[100];
  int m_motheridx[100];
  int m_motherpid[100];

  double m_mc_mom_pip;
  double m_mc_mom_pim;
  double m_mc_mom_mup;
  double m_mc_mom_mum;
  double m_mc_mom_ep;
  double m_mc_mom_em;  
  double m_mc_mom_p;
  double m_mc_mom_pb;
  double m_mc_mom_n;
  double m_mc_mom_nb;
  
  double m_mc_pt_pip;
  double m_mc_pt_pim;
  double m_mc_pt_mup ; 
  double m_mc_pt_mum ; 
  double m_mc_pt_ep ; 
  double m_mc_pt_em ; 
  double m_mc_pt_p ; 
  double m_mc_pt_pb ; 
  double m_mc_pt_n ; 
  double m_mc_pt_nb ;
  
  double m_mc_costhe_mup ; 
  double m_mc_costhe_mum ; 
  double m_mc_costhe_ep ; 
  double m_mc_costhe_em ; 
  double m_mc_costhe_p ; 
  double m_mc_costhe_pb ; 
  double m_mc_costhe_n ; 
  double m_mc_costhe_nb ;
  double m_mc_costhe_pip ; 
  double m_mc_costhe_pim ;
  
  double m_mc_cospipi ; 
  double m_mc_cos2pisys ; 


  // functions
  void book_histogram();
  void book_tree(); 
  void clearVariables();
  bool buildJpsiToGammaEta();
  void saveGenInfo(); 
//   void saveTrkInfo(EvtRecTrackIterator,
// 		   EvtRecTrackIterator);
  void saveTrkInfopip(EvtRecTrackIterator);
  void saveTrkInfopim(EvtRecTrackIterator);
  void savePionInfopip(RecMdcKalTrack *);
  void savePionInfopim(RecMdcKalTrack *);
//   void savePionInfo(RecMdcKalTrack *,
// 		    RecMdcKalTrack *);
  void saveVtxInfo(HepLorentzVector,
		   HepLorentzVector);  
  void saveGamInfo(std::vector<int>,
		   SmartDataPtr<EvtRecTrackCol>);
  int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>,
			  std::vector<int> &,
			  std::vector<int> &); 
  int selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol>,
			      std::vector<int>,
			      std::vector<int>);
  void calcTrackPID(EvtRecTrackIterator,
		    double&,
		    double&,
		    double&);
  bool hasGoodPiPiVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *,
			 bool);
  int selectNeutralTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>,
			  std::vector<int> &);
  bool passVertexSelection(CLHEP::Hep3Vector,
			   RecMdcKalTrack* ); 
  CLHEP::Hep3Vector getOrigin();

  int kinematicFit(SmartDataPtr<EvtRecTrackCol>,
		   std::vector<int>);
  void saveKinematicFitInfo(double, 
			    HepLorentzVector, 
			    HepLorentzVector,
			    HepLorentzVector ,
			    HepLorentzVector, 
			    HepLorentzVector);
   void getTrigInfo();
}; 


//
// module declare
//

DECLARE_ALGORITHM_FACTORY( Jpsi2geta )
DECLARE_FACTORY_ENTRIES( Jpsi2geta ) {
  DECLARE_ALGORITHM(Jpsi2geta);
}

LOAD_FACTORY_ENTRIES( Jpsi2geta )

//
// constants
//

const double PION_MASS = 0.139570;

const int ELECTRON_PDG_ID = 11;
const int MUON_PDG_ID = 13;
const int PIONPLUS_PDG_ID = 211;

const int JPSI_PDG_ID = 443;
const int PSI2S_PDG_ID = 100443;
const int PROTON_PDG_ID = 2212; 
const int NEUTRON_PDG_ID = 2112; 

//
// member functions
//
  
Jpsi2geta::Jpsi2geta(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
  m_tree(0),
  m_raw_gpx(0), 
  m_raw_gpy(0), 
  m_raw_gpz(0), 
  m_raw_ge(0),  
  m_raw_phi(0),
  m_raw_theta(0),
  m_raw_costheta(0),
  m_raw_cstat(0),
  m_raw_nhit(0),
  m_raw_module(0),
  m_raw_secmom(0),
  m_raw_time(0)
{
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("IsMonteCarlo", m_isMonteCarlo);
  declareProperty("ZChi_AnaCondition", m_isZCcondition=false);
  //declareProperty("ZChi_AnaCondition", m_isZCcondition=true);
  declareProperty("Ecms", m_ecms = 3.686);
  declareProperty("Vr0cut", m_vr0cut=1.0);
  declareProperty("Vz0cut", m_vz0cut=10.0);
  declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.93);
  declareProperty("TotalNumberOfChargedMax", m_total_number_of_charged_max=50);
  declareProperty("MinEstCut", m_min_emctime=0.0);
  declareProperty("MaxEstCut", m_max_emctime=14.0);
  declareProperty("GammaCosCut",  m_gammaCosCut= 0.93); 
  declareProperty("CosthetaBarrelMax", m_costheta_barrel_max=0.8);
  declareProperty("CosthetaEndcapMin", m_costheta_endcap_min=0.86);
  declareProperty("CosthetaEndcapMax", m_costheta_endcap_max=0.92);
  declareProperty("EnergyBarrelMin", m_energy_barrel_min=0.025); 
  declareProperty("EnergyEndcapMin", m_energy_endcap_min=0.050); 
  declareProperty("PhotonIsoAngleMin", m_photon_iso_angle_min=10);
  declareProperty("PionPolarAngleMax", m_pion_polar_angle_max=0.99);
  declareProperty("PionMomentumMax", m_pion_momentum_max=1.9); 
  declareProperty("ProbPionMin", m_prob_pion_min=0.001);
  declareProperty("DipionMassMin", m_dipion_mass_min=3.0); 
  declareProperty("DipionMassMax", m_dipion_mass_max=3.2); 
  declareProperty("PiPiCosthetaMax", m_pipi_costheta_max=0.99);
  declareProperty("PiPiSysCosthetaMax", m_pipisys_costheta_max=0.99);
}


StatusCode Jpsi2geta::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;

  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd(); 

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Jpsi2geta::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
  
  // clear variables 
  clearVariables();
  
  h_evtflw->Fill(0); // raw 
  SmartDataPtr<Event::EventHeader>eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();
  
  if (buildJpsiToGammaEta()) {
    m_tree->Fill(); // only fill tree for the selected events 
  }

  return StatusCode::SUCCESS; 
}

StatusCode Jpsi2geta::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  h_evtflw->Write();
  m_fout->Close();
  
  return StatusCode::SUCCESS;
}


Jpsi2geta::~Jpsi2geta() {
}


void Jpsi2geta::book_histogram() {

  h_evtflw = new TH1F("hevtflw", "eventflow", 13, 0, 13);
  if (!h_evtflw) return;
  h_evtflw->GetXaxis()->SetBinLabel(1, "raw");
  h_evtflw->GetXaxis()->SetBinLabel(2, "N_{Good}=2");
  h_evtflw->GetXaxis()->SetBinLabel(3, "|cos#theta|<0.99");
  h_evtflw->GetXaxis()->SetBinLabel(4, "|p|<1.9");
  h_evtflw->GetXaxis()->SetBinLabel(5, "PID"); 
  h_evtflw->GetXaxis()->SetBinLabel(6, "cos#theta_{#pi^{+}#pi^{-}}<0.99");
  h_evtflw->GetXaxis()->SetBinLabel(7, "cos#theta_{#pi#pi sys}<0.99");
  h_evtflw->GetXaxis()->SetBinLabel(8, "3<M_{#pi#pi}^{rec}<3.2");
  h_evtflw->GetXaxis()->SetBinLabel(9, "N_{#gamma}<20");
  h_evtflw->GetXaxis()->SetBinLabel(10, "test");
}


void Jpsi2geta::book_tree() {

  m_tree=new TTree("tree", "jpsi2geta");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");
	  
  //charged tracks
  m_tree->Branch("ncharged", &m_ncharged, "ncharged/I");
  m_tree->Branch("nptrk", &m_nptrk, "nptrk/I");
  m_tree->Branch("nmtrk", &m_nmtrk, "nmtrk/I");
  m_tree->Branch("trkp_p", &m_trkp_p, "trkp_p/D"); 
  m_tree->Branch("trkp_px", &m_trkp_px, "trkp_px/D"); 
  m_tree->Branch("trkp_py", &m_trkp_py, "trkp_py/D"); 
  m_tree->Branch("trkp_pz", &m_trkp_pz, "trkp_pz/D"); 
  m_tree->Branch("trkp_theta", &m_trkp_theta, "trkp_theta/D"); 
  m_tree->Branch("trkp_phi", &m_trkp_phi, "trkp_phi/D"); 
  m_tree->Branch("trkp_eraw", &m_trkp_eraw, "trkp_eraw/D"); 

  m_tree->Branch("trkm_p", &m_trkm_p, "trkm_p/D"); 
  m_tree->Branch("trkm_px", &m_trkm_px, "trkm_px/D"); 
  m_tree->Branch("trkm_py", &m_trkm_py, "trkm_py/D"); 
  m_tree->Branch("trkm_pz", &m_trkm_pz, "trkm_pz/D"); 
  m_tree->Branch("trkm_theta", &m_trkm_theta, "trkm_theta/D"); 
  m_tree->Branch("trkm_phi", &m_trkm_phi, "trkm_phi/D"); 
  m_tree->Branch("trkm_eraw", &m_trkm_eraw, "trkm_eraw/D"); 
	  
  //vertex
  m_tree->Branch("vr0", &m_vr0, "vr0/D");
  m_tree->Branch("vz0", &m_vz0, "vz0/D");

	  
  //netual tracks
  m_tree->Branch("nshow", &m_nshow, "nshow/I");
  m_tree->Branch("ngam", &m_ngam, "ngam/I");
  m_tree->Branch("raw_gpx", &m_raw_gpx);
  m_tree->Branch("raw_gpy", &m_raw_gpy);
  m_tree->Branch("raw_gpz", &m_raw_gpz);
  m_tree->Branch("raw_ge", &m_raw_ge);
  
  m_tree->Branch("raw_phi", &m_raw_phi);
  m_tree->Branch("raw_theta", &m_raw_theta);
  m_tree->Branch("raw_costheta", &m_raw_costheta);
  m_tree->Branch("raw_cstat", &m_raw_cstat);
  m_tree->Branch("raw_nhit", &m_raw_nhit);
  m_tree->Branch("raw_module", &m_raw_module);
  m_tree->Branch("raw_secmom", &m_raw_secmom);
  m_tree->Branch("raw_time", &m_raw_time);

  // PID info
  m_tree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
  m_tree->Branch("prob_pim", &m_prob_pim, "prob_pim/D"); 
  m_tree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
  m_tree->Branch("prob_km", &m_prob_km, "prob_km/D"); 
  m_tree->Branch("prob_p", &m_prob_p, "prob_p/D"); 
  m_tree->Branch("prob_pb", &m_prob_pb, "prob_pb/D"); 

  // save pion info
  m_tree->Branch("pip_px", &m_pip_px, "pip_px/D");
  m_tree->Branch("pip_py", &m_pip_py, "pip_py/D");
  m_tree->Branch("pip_pz", &m_pip_pz, "pip_pz/D");

  m_tree->Branch("pim_px", &m_pim_px, "pim_px/D");
  m_tree->Branch("pim_py", &m_pim_py, "pim_py/D");
  m_tree->Branch("pim_pz", &m_pim_pz, "pim_pz/D");

  // fitted info
  m_tree->Branch("vtx_pip_px", &m_vtx_pip_px, "vtx_pip_px/D");
  m_tree->Branch("vtx_pip_py", &m_vtx_pip_py, "vtx_pip_py/D");
  m_tree->Branch("vtx_pip_pz", &m_vtx_pip_pz, "vtx_pip_pz/D");
  m_tree->Branch("vtx_pip_p", &m_vtx_pip_p, "vtx_pip_p/D");
  m_tree->Branch("vtx_pip_e", &m_vtx_pip_e, "vtx_pip_e/D");
  m_tree->Branch("vtx_pip_costheta", &m_vtx_pip_costheta, "vtx_pip_costheta/D");
  m_tree->Branch("vtx_pip_phi", &m_vtx_pip_phi, "vtx_pip_phi/D");

  m_tree->Branch("vtx_pim_px", &m_vtx_pim_px, "vtx_pim_px/D");
  m_tree->Branch("vtx_pim_py", &m_vtx_pim_py, "vtx_pim_py/D");
  m_tree->Branch("vtx_pim_pz", &m_vtx_pim_pz, "vtx_pim_pz/D");
  m_tree->Branch("vtx_pim_p", &m_vtx_pim_p, "vtx_pim_p/D");
  m_tree->Branch("vtx_pim_e", &m_vtx_pim_e, "vtx_pim_e/D");
  m_tree->Branch("vtx_pim_costheta", &m_vtx_pim_costheta, "vtx_pim_costheta/D");
  m_tree->Branch("vtx_pim_phi", &m_vtx_pim_phi, "vtx_pim_phi/D");

  m_tree->Branch("vtx_mpipi", &m_vtx_mpipi, "vtx_mpipi/D");
  m_tree->Branch("vtx_mrecpipi", &m_vtx_mrecpipi, "vtx_mrecpipi/D");
  m_tree->Branch("vtx_cospipi", &m_vtx_cospipi, "vtx_cospipi/D");
  m_tree->Branch("vtx_cos2pisys", &m_vtx_cos2pisys, "vtx_cos2pisys/D");

  // kinematic fitting info
  m_tree->Branch("kmfit_chisq", &m_kmfit_chisq, "kmfit_chisq/D");
  m_tree->Branch("kmfit_g1g2dang", &m_kmfit_g1g2dang, "kmfit_g1g2dang/D");
  m_tree->Branch("kmfit_g1g3dang", &m_kmfit_g1g3dang, "kmfit_g1g3dang/D");
  m_tree->Branch("kmfit_g2g3dang", &m_kmfit_g2g3dang, "kmfit_g2g3dang/D");
  
  m_tree->Branch("kmfit_g1_gpx", &m_kmfit_g1_gpx, "kmfit_g1_gpx/D");
  m_tree->Branch("kmfit_g1_gpy", &m_kmfit_g1_gpy, "kmfit_g1_gpy/D");
  m_tree->Branch("kmfit_g1_gpz", &m_kmfit_g1_gpz, "kmfit_g1_gpz/D");
  m_tree->Branch("kmfit_g1_ge", &m_kmfit_g1_ge, "kmfit_g1_ge/D");

  m_tree->Branch("kmfit_g2_gpx", &m_kmfit_g2_gpx, "kmfit_g2_gpx/D");
  m_tree->Branch("kmfit_g2_gpy", &m_kmfit_g2_gpy, "kmfit_g2_gpy/D");
  m_tree->Branch("kmfit_g2_gpz", &m_kmfit_g2_gpz, "kmfit_g2_gpz/D");
  m_tree->Branch("kmfit_g2_ge", &m_kmfit_g2_ge, "kmfit_g2_ge/D");

  m_tree->Branch("kmfit_g3_gpx", &m_kmfit_g3_gpx, "kmfit_g3_gpx/D");
  m_tree->Branch("kmfit_g3_gpy", &m_kmfit_g3_gpy, "kmfit_g3_gpy/D");
  m_tree->Branch("kmfit_g3_gpz", &m_kmfit_g3_gpz, "kmfit_g3_gpz/D");
  m_tree->Branch("kmfit_g3_ge", &m_kmfit_g3_ge, "kmfit_g3_ge/D");

  m_tree->Branch("kmfit_m_g1g2", &m_kmfit_m_g1g2, "kmfit_m_g1g2/D");
  m_tree->Branch("kmfit_m_g1g3", &m_kmfit_m_g1g3, "kmfit_m_g1g3/D");
  m_tree->Branch("kmfit_m_g2g3", &m_kmfit_m_g2g3, "kmfit_m_g2g3/D");

  m_tree->Branch("kmfit_m_pipig1g2", &m_kmfit_m_pipig1g2, "kmfit_m_pipig1g2/D");
  m_tree->Branch("kmfit_m_pipig1g3", &m_kmfit_m_pipig1g3, "kmfit_m_pipig1g3/D");
  m_tree->Branch("kmfit_m_pipig2g3", &m_kmfit_m_pipig2g3, "kmfit_m_pipig2g3/D");

  m_tree->Branch("kmfit_mrecpipi", &m_kmfit_mrecpipi, "kmfit_mrecpipi/D");
  m_tree->Branch("kmfit_mpipi", &m_kmfit_mpipi, "kmfit_mpipi/D");
  m_tree->Branch("kmfit_cospipi", &m_kmfit_cospipi, "kmfit_cospipi/D");
  m_tree->Branch("kmfit_cos2pisys", &m_kmfit_cos2pisys, "kmfit_cos2pisys/D");

  // trigger info
  m_tree->Branch("trig_condition", m_trig_condition, "m_trig_condition[48]/I");
  m_tree->Branch("trig_channel", m_trig_channel, "m_trig_channel[16]/I");
  m_tree->Branch("trig_timewindow", &m_trig_timewindow, "m_trig_timewindow/I");
  m_tree->Branch("trig_timetype", &m_trig_timetype, "m_trig_timetype/I");

  // MC truth info
  if (!m_isMonteCarlo) return; 
  m_tree->Branch("indexmc", &m_indexmc, "indexmc/I");
  m_tree->Branch("pdgid", m_pdgid, "m_pdgid[100]/I");
  m_tree->Branch("trkidx", m_trkidx, "m_trkidx[100]/I");
  m_tree->Branch("motherpid", m_motherpid, "m_motherpid[100]/I");
  m_tree->Branch("motheridx", m_motheridx, "m_motheridx[100]/I");

  m_tree->Branch("mc_mom_pip", &m_mc_mom_pip, "mc_mom_pip/D");
  m_tree->Branch("mc_mom_pim", &m_mc_mom_pim, "mc_mom_pim/D");
  m_tree->Branch("mc_mom_mup", &m_mc_mom_mup, "mc_mom_mup/D");
  m_tree->Branch("mc_mom_mum", &m_mc_mom_mum, "mc_mom_mum/D");
  m_tree->Branch("mc_mom_ep", &m_mc_mom_ep, "mc_mom_ep/D");
  m_tree->Branch("mc_mom_em", &m_mc_mom_em, "mc_mom_em/D");
  m_tree->Branch("mc_mom_p", &m_mc_mom_p, "mc_mom_p/D");
  m_tree->Branch("mc_mom_pb", &m_mc_mom_pb, "mc_mom_pb/D");
  m_tree->Branch("mc_mom_n", &m_mc_mom_n, "mc_mom_n/D");
  m_tree->Branch("mc_mom_nb", &m_mc_mom_nb, "mc_mom_nb/D");
  
  m_tree->Branch("mc_pt_pip", &m_mc_pt_pip, "mc_pt_pip/D");
  m_tree->Branch("mc_pt_pim", &m_mc_pt_pim, "mc_pt_pim/D");
  m_tree->Branch("mc_pt_mup", &m_mc_pt_mup, "mc_pt_mup/D");
  m_tree->Branch("mc_pt_mum", &m_mc_pt_mum, "mc_pt_mum/D");
  m_tree->Branch("mc_pt_ep", &m_mc_pt_ep, "mc_pt_ep/D");
  m_tree->Branch("mc_pt_em", &m_mc_pt_em, "mc_pt_em/D");
  m_tree->Branch("mc_pt_p", &m_mc_pt_p, "mc_pt_p/D");
  m_tree->Branch("mc_pt_pb", &m_mc_pt_pb, "mc_pt_pb/D");
  m_tree->Branch("mc_pt_n", &m_mc_pt_n, "mc_pt_n/D");
  m_tree->Branch("mc_pt_nb", &m_mc_pt_nb, "mc_pt_nb/D");
  
  m_tree->Branch("mc_costhe_pip", &m_mc_costhe_pip, "mc_costhe_pip/D");
  m_tree->Branch("mc_costhe_pim", &m_mc_costhe_pim, "mc_costhe_pim/D");
  m_tree->Branch("mc_costhe_mup", &m_mc_costhe_mup, "mc_costhe_mup/D");
  m_tree->Branch("mc_costhe_mum", &m_mc_costhe_mum, "mc_costhe_mum/D");
  m_tree->Branch("mc_costhe_ep", &m_mc_costhe_ep, "mc_costhe_ep/D");
  m_tree->Branch("mc_costhe_em", &m_mc_costhe_em, "mc_costhe_em/D");
  m_tree->Branch("mc_costhe_p", &m_mc_costhe_p, "mc_costhe_p/D");
  m_tree->Branch("mc_costhe_pb", &m_mc_costhe_pb, "mc_costhe_pb/D");
  m_tree->Branch("mc_costhe_n", &m_mc_costhe_n, "mc_costhe_n/D");
  m_tree->Branch("mc_costhe_nb", &m_mc_costhe_nb, "mc_costhe_nb/D");
    
  m_tree->Branch("mc_cospipi", &m_mc_cospipi, "mc_cospipi/D");
  m_tree->Branch("mc_cos2pisys", &m_mc_cos2pisys, "mc_cos2pisys/D");
  
}

void Jpsi2geta::clearVariables() {

  // EMC Info
  m_raw_gpx->clear();
  m_raw_gpy->clear();
  m_raw_gpz->clear();
  m_raw_ge->clear();

  m_raw_phi->clear();
  m_raw_theta->clear();
  m_raw_costheta->clear();
  m_raw_cstat->clear();
  m_raw_nhit->clear();
  m_raw_module->clear();
  m_raw_secmom->clear();
  m_raw_time->clear();

  // MC Topology
  m_indexmc = 0;
  for(int i=0;i<100;i++)
    {
      m_pdgid[i] = 0;
      m_trkidx[i] = 0;
      m_motheridx[i] = 0;
      m_motherpid[i] = 0;
    }

  // Trigger Info
  for(int i=0; i<48; i++){ m_trig_condition[i] = 0; }
  for(int i=0; i<16; i++){ m_trig_channel[i] = 0; }
    
  m_run = 0;
  m_event = 0;
}

bool Jpsi2geta::buildJpsiToGammaEta() {

  if (m_isMonteCarlo) saveGenInfo(); 
  
  SmartDataPtr<EvtRecEvent>evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");
  if(!evtRecEvent) return false;

  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
  if(!evtRecTrkCol) return false;

  h_evtflw->Fill(9);

  std::vector<int> iPGood, iMGood; 
  selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

  // if (m_ncharged != 1) return false;
  if (m_ncharged < 1) return false;
  h_evtflw->Fill(1); // N_{Good} = 2 

  if( selectPionPlusPionMinus(evtRecTrkCol, iPGood, iMGood)!=1 ) return false;  

  std::vector<int> iGam;
  selectNeutralTracks(evtRecEvent, evtRecTrkCol, iGam);
  if (m_ngam >= 20) return false;
  //if (m_ngam >= 20 || m_ngam<3) return false;
  h_evtflw->Fill(8); // N_{#gamma} < 20 

  // if( kinematicFit(evtRecTrkCol, iGam)==0 ) return false; // no chisq fitting success combination 

  if (!m_isMonteCarlo) getTrigInfo(); 
  return true; 
}


void Jpsi2geta::saveGenInfo() {
  SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
  HepLorentzVector mc_psip,mc_pip,mc_pim,mc_ep,mc_em,mc_mup,mc_mum,mc_p,mc_pb,mc_n,mc_nb,mc_jpsi;

  // MC Topology 
  {
    int m_numParticle = 0;
    bool Decay = false;
    int rootIndex = -1;
    Event::McParticleCol::iterator iter_mc_topo = mcParticleCol->begin();
    for (; iter_mc_topo != mcParticleCol->end(); iter_mc_topo++) {
      if ((*iter_mc_topo)->primaryParticle() && Decay) { rootIndex++; continue; }
      if ((*iter_mc_topo)->primaryParticle()) continue;
      if (!(*iter_mc_topo)->decayFromGenerator()) continue;
      if ((*iter_mc_topo)->particleProperty() == PSI2S_PDG_ID) {
        Decay = true;
        rootIndex = (*iter_mc_topo)->trackIndex();
      }
      if (!Decay) continue;
      int mpdgid = ((*iter_mc_topo)->mother()).particleProperty();
      int mcidx = (((*iter_mc_topo)->mother()).particleProperty() == PSI2S_PDG_ID) ? 0 : ((*iter_mc_topo)->mother()).trackIndex() - rootIndex;
      //int mcidx = ((*iter_mc_topo)->mother()).trackIndex() - rootIndex;
      int pdgid = (*iter_mc_topo)->particleProperty();
      int trkidx = (*iter_mc_topo)->trackIndex() - rootIndex;
      m_pdgid[m_numParticle] = pdgid;
      m_trkidx[m_numParticle] = trkidx;
      m_motheridx[m_numParticle] = mcidx;
      m_motherpid[m_numParticle] = mpdgid;
      m_numParticle++;
    }
    m_indexmc = m_numParticle;
  }


  Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
  for (; iter_mc != mcParticleCol->end(); iter_mc++){
    if ((*iter_mc)->primaryParticle()) continue;
    if (!(*iter_mc)->decayFromGenerator()) continue;

    if( (*iter_mc)->mother().particleProperty() == PSI2S_PDG_ID) {
      if ( (*iter_mc)->particleProperty() == PIONPLUS_PDG_ID)
	mc_pip = (*iter_mc)->initialFourMomentum();

      if ( (*iter_mc)->particleProperty() == -PIONPLUS_PDG_ID)
	mc_pim = (*iter_mc)->initialFourMomentum();
    }

    if ((*iter_mc)->mother().particleProperty() == JPSI_PDG_ID ) {
      if((*iter_mc)->particleProperty() == -MUON_PDG_ID )
	mc_mup = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == MUON_PDG_ID )
	mc_mum = (*iter_mc)->initialFourMomentum();
      
      if((*iter_mc)->particleProperty() == -ELECTRON_PDG_ID )
	mc_ep = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == ELECTRON_PDG_ID )
	mc_em = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == PROTON_PDG_ID )
	mc_p = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == -PROTON_PDG_ID )
	mc_pb = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == NEUTRON_PDG_ID )
	mc_n = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == -NEUTRON_PDG_ID )
	mc_nb = (*iter_mc)->initialFourMomentum();
    }
  } 

  m_mc_mom_pip = mc_pip.vect().mag();
  m_mc_mom_pim = mc_pim.vect().mag();
  m_mc_mom_mup = mc_mup.vect().mag();
  m_mc_mom_mum = mc_mum.vect().mag();
  m_mc_mom_ep = mc_ep.vect().mag();
  m_mc_mom_em = mc_em.vect().mag();
  m_mc_mom_p = mc_p.vect().mag();
  m_mc_mom_pb = mc_pb.vect().mag();
  m_mc_mom_n = mc_n.vect().mag();
  m_mc_mom_nb = mc_nb.vect().mag();

  m_mc_pt_pip = mc_pip.vect().perp(); 
  m_mc_pt_pim = mc_pim.vect().perp(); 
  m_mc_pt_mup = mc_mup.vect().perp(); 
  m_mc_pt_mum = mc_mum.vect().perp(); 
  m_mc_pt_ep = mc_ep.vect().perp(); 
  m_mc_pt_em = mc_em.vect().perp();
  m_mc_pt_p = mc_p.vect().perp(); 
  m_mc_pt_pb = mc_pb.vect().perp();
  m_mc_pt_n = mc_n.vect().perp(); 
  m_mc_pt_nb = mc_nb.vect().perp();

  m_mc_costhe_mup = mc_mup.vect().cosTheta();
  m_mc_costhe_mum = mc_mum.vect().cosTheta();
  m_mc_costhe_ep = mc_ep.vect().cosTheta();
  m_mc_costhe_em = mc_em.vect().cosTheta();
  m_mc_costhe_p = mc_p.vect().cosTheta();
  m_mc_costhe_pb = mc_pb.vect().cosTheta();
  m_mc_costhe_n = mc_n.vect().cosTheta();
  m_mc_costhe_nb = mc_nb.vect().cosTheta();
  m_mc_costhe_pip = mc_pip.vect().cosTheta();
  m_mc_costhe_pim = mc_pim.vect().cosTheta();
      
  m_mc_cospipi = mc_pip.vect().cosTheta(mc_pim.vect());
  m_mc_cos2pisys = (mc_pip + mc_pim).vect().cosTheta();

}

CLHEP::Hep3Vector Jpsi2geta::getOrigin() {
  CLHEP::Hep3Vector xorigin(0,0,0);
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
  if(vtxsvc->isVertexValid()){
    double *dbv = vtxsvc->PrimaryVertex(); 
    xorigin.setX(dbv[0]);
    xorigin.setY(dbv[1]);
    xorigin.setZ(dbv[2]);
  }
  return xorigin; 
}


bool Jpsi2geta::passVertexSelection(CLHEP::Hep3Vector xorigin,
				    RecMdcKalTrack* mdcTrk ) {
  HepVector a = mdcTrk->helix();
  HepSymMatrix Ea = mdcTrk->err();
  HepPoint3D point0(0.,0.,0.);
  VFHelix helixip(point0,a,Ea);
  HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
  helixip.pivot(IP);
  HepVector vecipa = helixip.a();
  
  m_vz0 = vecipa[3];
  m_vr0 = vecipa[0];
  
  if(fabs(m_vz0) >= m_vz0cut) return false;
  if(fabs(m_vr0) >= m_vr0cut) return false;
  
  return true;
}


int Jpsi2geta::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				   std::vector<int> & iPGood,
				   std::vector<int> & iMGood) {

  CLHEP::Hep3Vector xorigin = getOrigin(); 

  std::vector<int> iGood;
  iGood.clear();
  iPGood.clear();
  iMGood.clear();
  
  // loop through charged tracks 
  for(int i = 0; i < evtRecEvent->totalCharged(); i++){
    // get mdcTrk 
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;

    // Good Kalman Track 
    if(!(*itTrk)->isMdcKalTrackValid()) continue;

    if(!(*itTrk)->isMdcTrackValid()) continue;
    RecMdcKalTrack* mdcTrk = (*itTrk)->mdcKalTrack();

    // Good Vertex 
    if (!passVertexSelection(xorigin, mdcTrk) ) continue; 

    // Polar angle cut
    if(fabs(cos(mdcTrk->theta())) > m_cha_costheta_cut) continue;
    
    // if (! ( (evtRecEvent)->totalCharged()==2 ) ) continue;
    if (! ( (evtRecEvent)->totalCharged()==1 || (evtRecEvent)->totalCharged()==2 ) ) continue;
    iGood.push_back((*itTrk)->trackId());
    if(mdcTrk->charge()>0) iPGood.push_back((*itTrk)->trackId());
    if(mdcTrk->charge()<0) iMGood.push_back((*itTrk)->trackId());

  } // end charged tracks
 
  m_ncharged = iGood.size();
  m_nptrk = iPGood.size();
  m_nmtrk = iMGood.size(); 

  if (m_nptrk > 0 && m_nmtrk == 0) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[0];
    saveTrkInfopip(itTrk_p);
  }
  if (m_nptrk == 0 && m_nmtrk > 0) {
    EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[0];
    saveTrkInfopim( itTrk_m);
  }
  return iGood.size(); 
}

int Jpsi2geta::selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood,
				       std::vector<int> iMGood) {
  int npipi = 0;
  bool evtflw_filled = false;
  // track PID
  double prob_pip, prob_kp, prob_pim, prob_km, prob_p, prob_pb; 
  if ( iPGood.size() > 0 ){
	  EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[0];
	  RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
      if ( ! ( fabs(cos(mdcTrk_p->theta())) < m_pion_polar_angle_max)) ;
      if ( !evtflw_filled ) h_evtflw->Fill(2); // |cos#theta| cut 
      if ( ! ( fabs(mdcTrk_p->p()) < m_pion_momentum_max )) ;

      if ( !evtflw_filled ) h_evtflw->Fill(3); //|p| cut 
  calcTrackPID(itTrk_p, prob_pip, prob_kp, prob_p);  
      m_prob_pip = prob_pip;
      m_prob_kp = prob_kp;
      m_prob_p = prob_p;
      if ( !evtflw_filled ) h_evtflw->Fill(4); //PID
      RecMdcKalTrack *pipTrk = (*(evtRecTrkCol->begin()+iPGood[0]))->mdcKalTrack(); 
      savePionInfopip(pipTrk);
      // if (! hasGoodPiPiVertex(pipTrk, pimTrk, evtflw_filled) ) continue; 
      npipi++;
      evtflw_filled = true;

	  }

  if ( iMGood.size() > 0 ){
	  EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[0];
	  RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
      if ( ! (  fabs(cos(mdcTrk_m->theta())) < m_pion_polar_angle_max )) ;
      if ( !evtflw_filled ) h_evtflw->Fill(2); // |cos#theta| cut 
      if ( ! (  fabs(mdcTrk_m->p()) < m_pion_momentum_max )) ;

      if ( !evtflw_filled ) h_evtflw->Fill(3); //|p| cut 
  calcTrackPID(itTrk_m, prob_pim, prob_km, prob_pb);
      m_prob_pim = prob_pim;
      m_prob_km = prob_km;
      m_prob_pb = prob_pb;
      if ( !evtflw_filled ) h_evtflw->Fill(4); //PID
      RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+iMGood[0]))->mdcKalTrack(); 
      savePionInfopim(pimTrk);
      // if (! hasGoodPiPiVertex(pipTrk, pimTrk, evtflw_filled) ) continue; 
      npipi++;
      evtflw_filled = true;
      
	 }
      
  return npipi; 
}


void Jpsi2geta::calcTrackPID(EvtRecTrackIterator itTrk_p,
			     double& prob_pip,
			     double& prob_kp,
			     double& prob_p) {
  prob_pip = 999.; 
  prob_kp = 999.; 
  prob_p = 999.; 
  ParticleID * pidp = ParticleID::instance();
  pidp->init();
  pidp->setMethod(pidp->methodProbability());
  pidp->setChiMinCut(4);
  pidp->setRecTrack(*itTrk_p);
  // use PID sub-system
  pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
  pidp->identify(pidp->onlyPionKaonProton());
  pidp->calculate();
  if(pidp->IsPidInfoValid()) {
    prob_pip = pidp->probPion();
    prob_kp  = pidp->probKaon();
    prob_p   = pidp->probProton();
  }
}

bool Jpsi2geta::hasGoodPiPiVertex(RecMdcKalTrack *pipTrk,
				  RecMdcKalTrack *pimTrk,
				  bool evtflw_filled) {

  HepLorentzVector pcms;
  if (!m_isZCcondition){
    pcms = HepLorentzVector(0.011*m_ecms, 0., 0., m_ecms);
  }
  else{ pcms = HepLorentzVector(0.011*m_ecms, -0.001, 0.005, m_ecms); }

  HepLorentzVector p4_vtx_pip, p4_vtx_pim, p4_vtx_pipi, p4_vtx_recpipi;
  WTrackParameter wvpipTrk, wvpimTrk;
  pipTrk->setPidType(RecMdcKalTrack::pion);
  wvpipTrk = WTrackParameter(PION_MASS, pipTrk->getZHelix(), pipTrk->getZError());

  pimTrk->setPidType(RecMdcKalTrack::pion);
  wvpimTrk = WTrackParameter(PION_MASS, pimTrk->getZHelix(), pimTrk->getZError());
  
  HepPoint3D vx(0., 0., 0.);
  HepSymMatrix Evx(3, 0);

  double bx = 1E+6;
  double by = 1E+6;
  double bz = 1E+6;
  Evx[0][0] = bx*bx;
  Evx[1][1] = by*by;
  Evx[2][2] = bz*bz;
  
  VertexParameter vxpar;
  vxpar.setVx(vx);
  vxpar.setEvx(Evx);
  
  VertexFit* vtxfit = VertexFit::instance();
  vtxfit->init();
  vtxfit->AddTrack(0,  wvpipTrk);
  vtxfit->AddTrack(1,  wvpimTrk);
  vtxfit->AddVertex(0, vxpar,0,1);

  if(!vtxfit->Fit(0)) return false;

  vtxfit->Swim(0);
      
  // WTrackParameter wpip = vtxfit->wtrk(0);
  // WTrackParameter wpim = vtxfit->wtrk(1);
  wpip = vtxfit->wtrk(0);  // wpip/wpim is now private variable to use in 4C kinematic fit 
  wpim = vtxfit->wtrk(1);

  p4_vtx_pip = vtxfit->pfit(0) ;
  p4_vtx_pim = vtxfit->pfit(1) ;
  p4_vtx_recpipi = pcms - p4_vtx_pip - p4_vtx_pim;
  p4_vtx_pipi = p4_vtx_pip + p4_vtx_pim;

  double cospipi = cos(p4_vtx_pip.vect().angle(p4_vtx_pim.vect()));
  double cos2pisys = (p4_vtx_pip + p4_vtx_pim).cosTheta();

  //if( ! (cospipi < m_pipi_costheta_max) ) return false;
  if( !evtflw_filled ) h_evtflw->Fill(5); // "cos#theta_{#pi^{+}#pi^{-}}<0.99"

  //if( ! (fabs(cos2pisys) < m_pipisys_costheta_max ) ) return false;
  if( !evtflw_filled ) h_evtflw->Fill(6); // cos#theta_{#pi#pi sys}<0.99 

  if( ! ( p4_vtx_recpipi.m() >= m_dipion_mass_min &&
	  p4_vtx_recpipi.m() <= m_dipion_mass_max) ) return false;
  if( !evtflw_filled ) h_evtflw->Fill(7); // 3<M_{#pi#pi}^{rec}<3.2

  saveVtxInfo(p4_vtx_pip, p4_vtx_pim); 
  m_vtx_mrecpipi = p4_vtx_recpipi.m();
  m_vtx_mpipi = p4_vtx_pipi.m();
  m_vtx_cospipi = cospipi;
  m_vtx_cos2pisys = cos2pisys; 
  
  return true;
}


int Jpsi2geta::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				   std::vector<int> & iGam) {

  //std::vector<int> iGam;
  iGam.clear();
  std::vector<int> iShow;
  iShow.clear();

  // loop through neutral tracks
  for(int i=evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
    if (i > m_total_number_of_charged_max) break;

    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i ;
    if(!(*itTrk)->isEmcShowerValid()) continue;
    RecEmcShower *emcTrk = (*itTrk)->emcShower();
    iShow.push_back((*itTrk)->trackId());
    
    // TDC window
    if ( !(emcTrk->time() >= m_min_emctime && emcTrk->time() <= m_max_emctime) )
      continue; 

    // Energy threshold
    double abs_costheta(fabs(cos(emcTrk->theta())));
    bool barrel = (abs_costheta < m_costheta_barrel_max); 
    bool endcap = (abs_costheta > m_costheta_endcap_min
		   && abs_costheta < m_costheta_endcap_max);
    double eraw = emcTrk->energy();
    
    if (!m_isZCcondition){     // Cut by "costheta"
      if ( !( (barrel && eraw > m_energy_barrel_min)
	      || (endcap && eraw > m_energy_endcap_min)))  continue; 
    }
    else{                      // Cut by "module"
      int module = emcTrk->module();
      if( module == 1 ){  if( !(eraw > m_energy_barrel_min) ) continue; }
      else{ if( !(eraw > m_energy_endcap_min) ) continue; }
    }

    // photon isolation: the opening angle between a candidate shower
    // and the closest charged track should be larger than 10 degree 
    CLHEP::Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

    // EMC costheta cut 
    double costhe = cos(emcpos.theta());
    if ( fabs(costhe) >= m_gammaCosCut) continue;
    
    // find the nearest charged track
    double dthe = 200.;
    double dphi = 200.;
    double dang = 200.; 
    for(int j = 0; j < evtRecEvent->totalCharged(); j++) {
      EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
      if(!(*jtTrk)->isExtTrackValid()) continue;
      RecExtTrack *extTrk = (*jtTrk)->extTrack();
      if(extTrk->emcVolumeNumber() == -1) continue;
      CLHEP::Hep3Vector extpos = extTrk->emcPosition();
      double angd = extpos.angle(emcpos);
      double thed = extpos.theta() - emcpos.theta();
      double phid = extpos.deltaPhi(emcpos);
      thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
      phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;

      if(fabs(thed) < fabs(dthe)) dthe = thed;
      if(fabs(phid) < fabs(dphi)) dphi = phid;
      if(angd < dang) dang = angd;	    
    }

    if(dang>=200) continue;
    dthe = dthe * 180 / (CLHEP::pi);
    dphi = dphi * 180 / (CLHEP::pi);
    dang = dang * 180 / (CLHEP::pi);
    if (dang < m_photon_iso_angle_min ) continue; 

    iGam.push_back((*itTrk)->trackId());
  } // end loop neutral tracks     

  m_ngam = iGam.size();
  m_nshow = iShow.size();

  saveGamInfo(iGam, evtRecTrkCol);   
  
  return iGam.size(); 
}


int Jpsi2geta::kinematicFit(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
			    std::vector<int> iGam){

  HepLorentzVector pcms;
  if (!m_isZCcondition){
    pcms = HepLorentzVector(0.011*m_ecms, 0., 0., m_ecms);
  }
  else{ pcms = HepLorentzVector(0.011*m_ecms, -0.001, 0.005, m_ecms); }

  int nGam = iGam.size();

  KalmanKinematicFit * kmfit = KalmanKinematicFit::instance();
  double chisq_4c = 9999.;
  int ig[3] = {-1,-1,-1};
  HepLorentzVector p4_gamma1, p4_gamma2, p4_gamma3;
  HepLorentzVector p4_pip,p4_pim;

  p4_gamma1 = HepLorentzVector(0, 0, 0, 0);
  p4_gamma2 = HepLorentzVector(0, 0, 0, 0);
  p4_gamma3 = HepLorentzVector(0, 0, 0, 0);
  p4_pip = HepLorentzVector(0, 0, 0, 0);
  p4_pim = HepLorentzVector(0, 0, 0, 0);
  
  int count=0;
  for(int i1=0;i1<nGam;i1++){
    for(int i2=0;i2<nGam;i2++){
      if(i2<=i1)continue;
      for(int i3=0;i3<nGam;i3++){
	if(i3<=i2)continue;
        
	RecEmcShower* itTrk1 = (*(evtRecTrkCol->begin() + iGam[i1]))->emcShower();
	RecEmcShower* itTrk2 = (*(evtRecTrkCol->begin() + iGam[i2]))->emcShower();
	RecEmcShower* itTrk3 = (*(evtRecTrkCol->begin() + iGam[i3]))->emcShower();

	// kmfit->init();
	// kmfit->AddTrack(0, wpip);
	// kmfit->AddTrack(1, wpim);
	// kmfit->AddTrack(2, 0.0, itTrk1);
	// kmfit->AddTrack(3, 0.0, itTrk2);
	// kmfit->AddTrack(4, 0.0, itTrk3);
	// kmfit->AddFourMomentum(0, pcms);
	// //if(!kmfit->Fit(0)) continue;
	// //if(!kmfit->Fit(1)) continue;
	// bool oksq = kmfit->Fit();
	// if(oksq){
	//   double chisq = kmfit->chisq(); 
	//   //std::cout << "Chi Square = " << chisq << std::endl;
	//   count++;
	//   if(chisq<chisq_4c){
	//     chisq_4c=chisq;
	//     ig[0] = i1;
	//     ig[1] = i2;
	//     ig[2] = i3;
	//     p4_pip = kmfit->pfit(0) ;
	//     p4_pim = kmfit->pfit(1) ;
	//     p4_gamma1 = kmfit->pfit(2) ;
	//     p4_gamma2 = kmfit->pfit(3) ;
	//     p4_gamma3 = kmfit->pfit(4) ;
	//   }
	// }
      }  
    }
  }
 
  // saveKinematicFitInfo(chisq_4c, p4_pip, p4_pim, p4_gamma1, p4_gamma2, p4_gamma3);  

  return count;
}


void Jpsi2geta::saveKinematicFitInfo(double chisq, HepLorentzVector p4_kmfit_pip, 
                            HepLorentzVector p4_kmfit_pim, 
                            HepLorentzVector p4_kmfit_gamma1, 
                            HepLorentzVector p4_kmfit_gamma2,
                            HepLorentzVector p4_kmfit_gamma3 ){
 
  HepLorentzVector pcms;
  if (!m_isZCcondition){
    pcms = HepLorentzVector(0.011*m_ecms, 0., 0., m_ecms);
  }
  else{ pcms = HepLorentzVector(0.011*m_ecms, -0.001, 0.005, m_ecms); }

  double angle_g1g2 = p4_kmfit_gamma1.vect().angle( p4_kmfit_gamma2.vect() );
  double angle_g1g3 = p4_kmfit_gamma1.vect().angle( p4_kmfit_gamma3.vect() );
  double angle_g2g3 = p4_kmfit_gamma2.vect().angle( p4_kmfit_gamma3.vect() );
  
  double dangle_g1g2 = angle_g1g2*180.0/(CLHEP::pi);
  double dangle_g1g3 = angle_g1g3*180.0/(CLHEP::pi);
  double dangle_g2g3 = angle_g2g3*180.0/(CLHEP::pi);
  
  HepLorentzVector p4_kmfit_g1g2 = p4_kmfit_gamma1 + p4_kmfit_gamma2;
  HepLorentzVector p4_kmfit_g1g3 = p4_kmfit_gamma1 + p4_kmfit_gamma3;
  HepLorentzVector p4_kmfit_g2g3 = p4_kmfit_gamma2 + p4_kmfit_gamma3;
  
  // HepLorentzVector p4_kmfit_recpipi = pcms - p4_kmfit_pip - p4_kmfit_pim;
  // HepLorentzVector p4_kmfit_pipi = p4_kmfit_pip + p4_kmfit_pim;
  
  // HepLorentzVector p4_kmfit_pipi_g1g2 = p4_kmfit_pipi + p4_kmfit_g1g2;
  // HepLorentzVector p4_kmfit_pipi_g1g3 = p4_kmfit_pipi + p4_kmfit_g1g3;
  // HepLorentzVector p4_kmfit_pipi_g2g3 = p4_kmfit_pipi + p4_kmfit_g2g3;
  
  
  m_kmfit_chisq = chisq;
  m_kmfit_g1g2dang = dangle_g1g2;
  m_kmfit_g1g3dang = dangle_g1g3;
  m_kmfit_g2g3dang = dangle_g2g3;
  
  
  m_kmfit_g1_gpx = p4_kmfit_gamma1.px();
  m_kmfit_g1_gpy = p4_kmfit_gamma1.py();
  m_kmfit_g1_gpz = p4_kmfit_gamma1.pz();
  m_kmfit_g1_ge = p4_kmfit_gamma1.e();
  
  m_kmfit_g2_gpx = p4_kmfit_gamma2.px();
  m_kmfit_g2_gpy = p4_kmfit_gamma2.py();
  m_kmfit_g2_gpz = p4_kmfit_gamma2.pz();
  m_kmfit_g2_ge = p4_kmfit_gamma2.e();
  
  m_kmfit_g3_gpx = p4_kmfit_gamma3.px();
  m_kmfit_g3_gpy = p4_kmfit_gamma3.py();
  m_kmfit_g3_gpz = p4_kmfit_gamma3.pz();
  m_kmfit_g3_ge = p4_kmfit_gamma3.e();
  
  
  m_kmfit_m_g1g2 = p4_kmfit_g1g2.m();
  m_kmfit_m_g1g3 = p4_kmfit_g1g3.m();
  m_kmfit_m_g2g3 = p4_kmfit_g2g3.m();
  
  // m_kmfit_m_pipig1g2 = p4_kmfit_pipi_g1g2.m(); 
  // m_kmfit_m_pipig1g3 = p4_kmfit_pipi_g1g3.m(); 
  // m_kmfit_m_pipig2g3 = p4_kmfit_pipi_g2g3.m(); 
  
  // m_kmfit_mrecpipi = p4_kmfit_recpipi.m();
  // m_kmfit_mpipi = p4_kmfit_pipi.m();
  // m_kmfit_cospipi = cos( p4_kmfit_pip.vect().angle( p4_kmfit_pim.vect() ) );
  // m_kmfit_cos2pisys = p4_kmfit_pipi.cosTheta();
}



void Jpsi2geta::saveTrkInfopip(EvtRecTrackIterator itTrk_p) {

  RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack(); 
  m_trkp_p = mdcTrk_p->p();
  m_trkp_px = mdcTrk_p->px();
  m_trkp_py = mdcTrk_p->py();
  m_trkp_pz = mdcTrk_p->pz();
  m_trkp_theta = mdcTrk_p->theta();
  m_trkp_phi = mdcTrk_p->phi();
  
  if((*itTrk_p)->isEmcShowerValid()){
    RecEmcShower *emcTrk_p = (*itTrk_p)->emcShower();
    m_trkp_eraw = emcTrk_p->energy();
  }

}

void Jpsi2geta::saveTrkInfopim(EvtRecTrackIterator itTrk_m) {

  RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
  m_trkm_p = mdcTrk_m->p();
  m_trkm_px = mdcTrk_m->px();
  m_trkm_py = mdcTrk_m->py();
  m_trkm_pz = mdcTrk_m->pz();
  m_trkm_theta = mdcTrk_m->theta();
  m_trkm_phi = mdcTrk_m->phi();
  
  if((*itTrk_m)->isEmcShowerValid()){
    RecEmcShower *emcTrk_m = (*itTrk_m)->emcShower();
    m_trkm_eraw = emcTrk_m->energy();
  }

}

void Jpsi2geta::saveGamInfo(std::vector<int> iGam,
			    SmartDataPtr<EvtRecTrackCol> evtRecTrkCol){

  for(vector<int>::size_type i=0; i<iGam.size(); i++)  {
    
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGam[i];
    RecEmcShower* emcTrk = (*itTrk)->emcShower();
    double eraw = emcTrk->energy();
    double phi = emcTrk->phi();
    double theta = emcTrk->theta();

    HepLorentzVector p4 = HepLorentzVector(eraw * sin(theta) * cos(phi),
					   eraw * sin(theta) * sin(phi),
					   eraw * cos(theta),
					   eraw );
    m_raw_gpx->push_back(p4.px());
    m_raw_gpy->push_back(p4.py());
    m_raw_gpz->push_back(p4.pz());
    m_raw_ge->push_back(p4.e());


    int cstat = emcTrk->status();
    int nhit = emcTrk->numHits();
    int module = emcTrk->module();      
    double secmom = emcTrk->secondMoment();      
    double time = emcTrk->time();

    m_raw_phi->push_back(phi);
    m_raw_theta->push_back(theta);
    m_raw_costheta->push_back(cos(theta));
    m_raw_cstat->push_back(cstat);
    m_raw_nhit->push_back(nhit);
    m_raw_module->push_back(module);
    m_raw_secmom->push_back(secmom);
    m_raw_time->push_back(time);
  }
}

void Jpsi2geta::savePionInfopip(RecMdcKalTrack *pipTrk){
  m_pip_px = pipTrk->px();
  m_pip_py = pipTrk->py();
  m_pip_pz = pipTrk->pz();
}
void Jpsi2geta::savePionInfopim(RecMdcKalTrack *pimTrk){
  m_pim_px = pimTrk->px();
  m_pim_py = pimTrk->py();
  m_pim_pz = pimTrk->pz();
}

void Jpsi2geta::saveVtxInfo(HepLorentzVector p4_vtx_pip,
			    HepLorentzVector p4_vtx_pim){

  m_vtx_pip_px = p4_vtx_pip.px();
  m_vtx_pip_py = p4_vtx_pip.py();
  m_vtx_pip_pz = p4_vtx_pip.pz();
  m_vtx_pip_p = p4_vtx_pip.rho();
  m_vtx_pip_e = p4_vtx_pip.e();
  m_vtx_pip_costheta = p4_vtx_pip.cosTheta();
  m_vtx_pip_phi = p4_vtx_pip.phi();

  m_vtx_pim_px = p4_vtx_pim.px();
  m_vtx_pim_py = p4_vtx_pim.py();
  m_vtx_pim_pz = p4_vtx_pim.pz();
  m_vtx_pim_p = p4_vtx_pim.rho();
  m_vtx_pim_e = p4_vtx_pim.e();
  m_vtx_pim_costheta = p4_vtx_pim.cosTheta();
  m_vtx_pim_phi = p4_vtx_pim.phi();

}


void Jpsi2geta::getTrigInfo(){
  // std::cout<<"enter trig"<<std::endl;

   SmartDataPtr<TrigData> trigData(eventSvc(),EventModel::Trig::TrigData);
   if (!trigData) {
    //  std::cout << "Could not find Trigger Data for physics analysis" << std::endl;
      //      return StatusCode::FAILURE;
   }

   //std::cout << "Trigger conditions: " << std::endl ;
   for(int trig_index=0; trig_index < 48; trig_index++){
        //  std::cout << "i=" << trig_index << ": " ; 
     //     std::cout << "name:" << trigData->getTrigCondName(trig_index) << "    "   ;
     //     std::cout << "condition: " << trigData->getTrigCondition(trig_index) << std::endl;
     m_trig_condition[trig_index] = trigData->getTrigCondition(trig_index);
   }
   
   for(int trig_index=0; trig_index < 16; trig_index++){
        //  std::cout << "channel: " << trig_index << ": " << trigData->getTrigChannel(trig_index) << std::endl;
     m_trig_channel[trig_index] = trigData->getTrigChannel(trig_index);
   }

   m_trig_timewindow = trigData->getTimeWindow();
   m_trig_timetype = trigData->getTimingType();
}
