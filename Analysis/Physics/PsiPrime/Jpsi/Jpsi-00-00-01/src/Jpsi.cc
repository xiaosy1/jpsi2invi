// -*- C++ -*-
//
//
// Description: J/psi -> Invisible 
//
// Original Author:  SHI Xin <shixin@ihep.ac.cn>
//         Created:  [2016-03-23 Wed 09:12] 
//         Inspired by Zhu Kai and Zhang Chi's code 
//


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
#include "VertexFit/VertexFit.h"

#include "ParticleID/ParticleID.h"
#include "McTruth/McParticle.h"


#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

//
// class declaration
//

class Jpsi : public Algorithm {
  
public:
  Jpsi(const std::string&, ISvcLocator*);
  ~Jpsi(); 
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
  
  // define Trees
  TTree* m_tree;

  // common info 
  int m_run;
  int m_event;


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
  void book_tree(); 
  void clearVariables();
  bool buildJpsiToInvisible();
  void saveGenInfo(); 
  
}; 


//
// module declare
//

DECLARE_ALGORITHM_FACTORY( Jpsi )
DECLARE_FACTORY_ENTRIES( Jpsi ) {
  DECLARE_ALGORITHM(Jpsi);
}

LOAD_FACTORY_ENTRIES( Jpsi )

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
  
Jpsi::Jpsi(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
  m_tree(0)
{
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("IsMonteCarlo", m_isMonteCarlo);
}


StatusCode Jpsi::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;

  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd(); 

  // book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Jpsi::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
  
  // clear variables 
  clearVariables();
  
  // h_evtflw->Fill(0); // raw 
  SmartDataPtr<Event::EventHeader>eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();
  
  if (buildJpsiToInvisible()) {
    m_tree->Fill(); // only fill tree for the selected events 
  }

  return StatusCode::SUCCESS; 
}

StatusCode Jpsi::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  // h_evtflw->Write();
  m_fout->Close();
  
  return StatusCode::SUCCESS;
}


Jpsi::~Jpsi() {
}


void Jpsi::book_tree() {

  m_tree=new TTree("tree", "Jpsi");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");
	  
  // MC truth info
  if (!m_isMonteCarlo) return; 
  m_tree->Branch("indexmc", &m_indexmc, "indexmc/I");
  m_tree->Branch("pdgid", m_pdgid, "m_pdgid[100]/I");
  m_tree->Branch("trkidx", m_trkidx, "m_trkidx[100]/I");
  m_tree->Branch("motherpid", m_motherpid, "m_motherpid[100]/I");
  m_tree->Branch("motheridx", m_motheridx, "m_motheridx[100]/I");

  // m_tree->Branch("mc_mom_pip", &m_mc_mom_pip, "mc_mom_pip/D");
  // m_tree->Branch("mc_mom_pim", &m_mc_mom_pim, "mc_mom_pim/D");
  // m_tree->Branch("mc_mom_mup", &m_mc_mom_mup, "mc_mom_mup/D");
  // m_tree->Branch("mc_mom_mum", &m_mc_mom_mum, "mc_mom_mum/D");
  // m_tree->Branch("mc_mom_ep", &m_mc_mom_ep, "mc_mom_ep/D");
  // m_tree->Branch("mc_mom_em", &m_mc_mom_em, "mc_mom_em/D");
  // m_tree->Branch("mc_mom_p", &m_mc_mom_p, "mc_mom_p/D");
  // m_tree->Branch("mc_mom_pb", &m_mc_mom_pb, "mc_mom_pb/D");
  // m_tree->Branch("mc_mom_n", &m_mc_mom_n, "mc_mom_n/D");
  // m_tree->Branch("mc_mom_nb", &m_mc_mom_nb, "mc_mom_nb/D");
  
  // m_tree->Branch("mc_pt_pip", &m_mc_pt_pip, "mc_pt_pip/D");
  // m_tree->Branch("mc_pt_pim", &m_mc_pt_pim, "mc_pt_pim/D");
  // m_tree->Branch("mc_pt_mup", &m_mc_pt_mup, "mc_pt_mup/D");
  // m_tree->Branch("mc_pt_mum", &m_mc_pt_mum, "mc_pt_mum/D");
  // m_tree->Branch("mc_pt_ep", &m_mc_pt_ep, "mc_pt_ep/D");
  // m_tree->Branch("mc_pt_em", &m_mc_pt_em, "mc_pt_em/D");
  // m_tree->Branch("mc_pt_p", &m_mc_pt_p, "mc_pt_p/D");
  // m_tree->Branch("mc_pt_pb", &m_mc_pt_pb, "mc_pt_pb/D");
  // m_tree->Branch("mc_pt_n", &m_mc_pt_n, "mc_pt_n/D");
  // m_tree->Branch("mc_pt_nb", &m_mc_pt_nb, "mc_pt_nb/D");
  
  m_tree->Branch("mc_costhe_pip", &m_mc_costhe_pip, "mc_costhe_pip/D");
  m_tree->Branch("mc_costhe_pim", &m_mc_costhe_pim, "mc_costhe_pim/D");
  // m_tree->Branch("mc_costhe_mup", &m_mc_costhe_mup, "mc_costhe_mup/D");
  // m_tree->Branch("mc_costhe_mum", &m_mc_costhe_mum, "mc_costhe_mum/D");
  // m_tree->Branch("mc_costhe_ep", &m_mc_costhe_ep, "mc_costhe_ep/D");
  // m_tree->Branch("mc_costhe_em", &m_mc_costhe_em, "mc_costhe_em/D");
  // m_tree->Branch("mc_costhe_p", &m_mc_costhe_p, "mc_costhe_p/D");
  // m_tree->Branch("mc_costhe_pb", &m_mc_costhe_pb, "mc_costhe_pb/D");
  // m_tree->Branch("mc_costhe_n", &m_mc_costhe_n, "mc_costhe_n/D");
  // m_tree->Branch("mc_costhe_nb", &m_mc_costhe_nb, "mc_costhe_nb/D");
    
  // m_tree->Branch("mc_cospipi", &m_mc_cospipi, "mc_cospipi/D");
  // m_tree->Branch("mc_cos2pisys", &m_mc_cos2pisys, "mc_cos2pisys/D");
  
}

void Jpsi::clearVariables() {

  // MC Topology
  m_indexmc = 0;
  for(int i=0;i<100;i++)
    {
      m_pdgid[i] = 0;
      m_trkidx[i] = 0;
      m_motheridx[i] = 0;
      m_motherpid[i] = 0;
    }

  m_run = 0;
  m_event = 0;
}

bool Jpsi::buildJpsiToInvisible() {

  if (m_isMonteCarlo) saveGenInfo(); 
  
  return true; 
}


void Jpsi::saveGenInfo() {
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

    // if ((*iter_mc)->mother().particleProperty() == JPSI_PDG_ID ) {
  //     if((*iter_mc)->particleProperty() == -MUON_PDG_ID )
	// mc_mup = (*iter_mc)->initialFourMomentum();

  //     if((*iter_mc)->particleProperty() == MUON_PDG_ID )
	// mc_mum = (*iter_mc)->initialFourMomentum();
      
  //     if((*iter_mc)->particleProperty() == -ELECTRON_PDG_ID )
	// mc_ep = (*iter_mc)->initialFourMomentum();

  //     if((*iter_mc)->particleProperty() == ELECTRON_PDG_ID )
	// mc_em = (*iter_mc)->initialFourMomentum();

  //     if((*iter_mc)->particleProperty() == PROTON_PDG_ID )
	// mc_p = (*iter_mc)->initialFourMomentum();

  //     if((*iter_mc)->particleProperty() == -PROTON_PDG_ID )
	// mc_pb = (*iter_mc)->initialFourMomentum();

  //     if((*iter_mc)->particleProperty() == NEUTRON_PDG_ID )
	// mc_n = (*iter_mc)->initialFourMomentum();

  //     if((*iter_mc)->particleProperty() == -NEUTRON_PDG_ID )
	// mc_nb = (*iter_mc)->initialFourMomentum();
    // }
  } 

  // m_mc_mom_pip = mc_pip.vect().mag();
  // m_mc_mom_pim = mc_pim.vect().mag();
  // m_mc_mom_mup = mc_mup.vect().mag();
  // m_mc_mom_mum = mc_mum.vect().mag();
  // m_mc_mom_ep = mc_ep.vect().mag();
  // m_mc_mom_em = mc_em.vect().mag();
  // m_mc_mom_p = mc_p.vect().mag();
  // m_mc_mom_pb = mc_pb.vect().mag();
  // m_mc_mom_n = mc_n.vect().mag();
  // m_mc_mom_nb = mc_nb.vect().mag();

  // m_mc_pt_pip = mc_pip.vect().perp(); 
  // m_mc_pt_pim = mc_pim.vect().perp(); 
  // m_mc_pt_mup = mc_mup.vect().perp(); 
  // m_mc_pt_mum = mc_mum.vect().perp(); 
  // m_mc_pt_ep = mc_ep.vect().perp(); 
  // m_mc_pt_em = mc_em.vect().perp();
  // m_mc_pt_p = mc_p.vect().perp(); 
  // m_mc_pt_pb = mc_pb.vect().perp();
  // m_mc_pt_n = mc_n.vect().perp(); 
  // m_mc_pt_nb = mc_nb.vect().perp();

  // m_mc_costhe_mup = mc_mup.vect().cosTheta();
  // m_mc_costhe_mum = mc_mum.vect().cosTheta();
  // m_mc_costhe_ep = mc_ep.vect().cosTheta();
  // m_mc_costhe_em = mc_em.vect().cosTheta();
  // m_mc_costhe_p = mc_p.vect().cosTheta();
  // m_mc_costhe_pb = mc_pb.vect().cosTheta();
  // m_mc_costhe_n = mc_n.vect().cosTheta();
  // m_mc_costhe_nb = mc_nb.vect().cosTheta();
  m_mc_costhe_pip = mc_pip.vect().cosTheta();
  m_mc_costhe_pim = mc_pim.vect().cosTheta();
      
  // m_mc_cospipi = mc_pip.vect().cosTheta(mc_pim.vect());
  // m_mc_cos2pisys = (mc_pip + mc_pim).vect().cosTheta();

}


