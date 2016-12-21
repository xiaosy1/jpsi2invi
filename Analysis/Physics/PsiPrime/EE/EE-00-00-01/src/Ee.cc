// -*- C++ -*-
//
//
// Description: Psi' -> pi+pi-Jpsi,J/psi -> e+e- 
//
// Original Author:  Chen Qian <chenq@pku.edu.cn>
//         Created:  [2016-05-23 Mon 14:40] 
//         Inspired by Shi xin's code 
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

#include "EventModel/EventModel.h"
#include "EventModel/Event.h"
#include "McTruth/McParticle.h"
#include "DstEvent/TofHitStatus.h"


#include "CLHEP/Vector/ThreeVector.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/Helix.h"
#include "VertexFit/WTrackParameter.h"
#include "VertexFit/VertexFit.h"
#include "VertexFit/KinematicFit.h"
#include "VertexFit/KalmanKinematicFit.h"


#include "ParticleID/ParticleID.h"

#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>

//
// class declaration
//

class Ee : public Algorithm {
  
public:
  Ee(const std::string&, ISvcLocator*);
  ~Ee(); 
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:
  // declare r0, z0 cut for charged tracks
  double m_ecms; 
  double m_vr0cut, m_vz0cut;
  double m_distin_pionlep;
  double m_cha_costheta_cut; 
  double m_total_number_of_charged_max; 
  double m_min_emctime;
  double m_max_emctime;
  double m_costheta_barrel_max;
  double m_costheta_endcap_min;
  double m_costheta_endcap_max;
  double m_energy_barrel_min;
  double m_energy_endcap_min;
  double m_photon_iso_angle_min;
  double m_pion_polar_angle_max;
  double m_pion_momentum_max;
  double m_eon_momentum_min;
  double m_eon_momentum_max;
  double m_prob_pion_min;
  double m_dipion_mass_min; 
  double m_dipion_mass_max;
  double m_pipi_costheta_max;
  double m_pipisys_costheta_max; 
  double m_ee_mass_min; 
  double m_ee_mass_max;
  double m_ep_ratio;
  
  
  //setting cut criteria
  bool cut_pip_costhe;
  bool cut_pim_costhe;
  bool cut_ep_costhe;
  bool cut_em_costhe;  
  bool cut_pi_costhe;
  bool cut_PID;
  bool cut_cospipi;
  bool cut_cos2pisys;
  bool cut_mjpsi;
  bool cut_mjpsi_signal;
  bool cut_epratio;
  bool cut_mee;  

  // output file
  std::string m_output_filename;
  TFile* m_fout; 
  
  // define Histograms
  TH1F* h_evtflw; 

  TH1F* h_cos2pisys; 
  TH1F* h_cospipi;
  TH1F* h_pim_costhe;
  TH1F* h_pip_costhe;
  TH1F* h_em_costhe;
  TH1F* h_ep_costhe;  
  TH1F* h_mee;
  TH1F* h_mrecpipi;
  TH2D* h_epratio;
  
  // define Trees
  
  // signal 
  TTree* m_tree;
  TTree* TopoTree;

  // common info 
  int m_run;
  int m_event;
  
  
        int m_rec;
  		int m_idxmc;
		int m_drank[500];
		//int m_trkidx[500];
		int m_pdgid[500];
		int m_motheridx[500];
		int m_motherpid[500];


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

  
  double m_pip_costhe;
  double m_pim_costhe;
  double m_ep_costhe;
  double m_em_costhe;  
  
  // pion info
  double m_pip_px;
  double m_pip_py;
  double m_pip_pz;
  double m_pip_p;

  double m_pim_px;
  double m_pim_py;
  double m_pim_pz;
  double m_pim_p;
  
  double m_cos_theta_pi_p;
  double m_cos_theta_pi_m;
  
  // eon info
  double m_ep_px;
  double m_ep_py;
  double m_ep_pz;
  double m_ep_p;

  double m_em_px;
  double m_em_py;
  double m_em_pz;
  double m_em_p;
  
  double m_cos_theta_e_p;
  double m_cos_theta_e_m;

  // fitted info
  //pipi
  double m_vtx_pip_px; 
  double m_vtx_pip_py; 
  double m_vtx_pip_pz; 
  double m_vtx_pip_p;   
  double m_vtx_pip_e;
  double m_vtx_pim_px; 
  double m_vtx_pim_py; 
  double m_vtx_pim_pz;
  double m_vtx_pim_p;   
  double m_vtx_pim_e;

  double m_vtx_mpipi;
  double m_vtx_mrecpipi;
  double m_vtx_cospipi;
  double m_vtx_cos2pisys; 
  double m_vtx_cospip;
  double m_vtx_cospim;
  
  //Ee
  double m_vtx_ep_px; 
  double m_vtx_ep_py; 
  double m_vtx_ep_pz; 
  double m_vtx_ep_p;   
  double m_vtx_ep_e;
  double m_vtx_em_px; 
  double m_vtx_em_py; 
  double m_vtx_em_pz;
  double m_vtx_em_p;   
  double m_vtx_em_e;

  double m_vtx_mee;
  double m_vtx_cosee;
  double m_vtx_cosep;
  double m_vtx_cosem;
  
  double epratio_p;
  double epratio_m;


  // vertex 
  double m_vr0;
  double m_vz0;

  // check MDC and EMC match
  long m_pion_matched;
  long m_lep_matched;

  // jpsi2invi
  int m_ntrk; 
  int m_npho; 
  
    // PID info
  double m_prob_pip;
  double m_prob_pim;
  double m_prob_kp;
  double m_prob_km;
  //double m_prob_p; 
  //double m_prob_pb; 
  
  //4C
  double m_chi4C;
  double m_me0;
  
  int ncounter[10];

  int m_savetopo;
  int m_09data;
  
  // functions
  void book_histogram();
  void book_tree(); 
  bool buildJpsiToEe();
  
  //void saveGenInfo(); 
  void saveTrkInfo(EvtRecTrackIterator,
		   EvtRecTrackIterator);
  void savePionInfo(RecMdcKalTrack *,
		    RecMdcKalTrack *);
  void saveeonInfo(RecMdcKalTrack *,
		    RecMdcKalTrack *);
  void savepipiVtxInfo(HepLorentzVector,
		   HepLorentzVector);
  void saveEeVtxInfo(HepLorentzVector,
		   HepLorentzVector);
  
  int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>,
			  std::vector<int> &,
			  std::vector<int> &); 
  int selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol>,
			      std::vector<int>,
			      std::vector<int>);
  int selectePluseMinus(SmartDataPtr<EvtRecTrackCol>,
			      std::vector<int>,
			      std::vector<int>);
  void calcTrackPID(EvtRecTrackIterator,
		    double& ,
		    double&);
  bool hasGoodPiPiVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *);
  bool hasGoodEeVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *);
  bool passVertexSelection(CLHEP::Hep3Vector,
			   RecMdcTrack* ); 
  CLHEP::Hep3Vector getOrigin();
}; 


//
// module declare 组件和加载声明
//

DECLARE_ALGORITHM_FACTORY( Ee )
DECLARE_FACTORY_ENTRIES( Ee ) {
  DECLARE_ALGORITHM(Ee);
}

LOAD_FACTORY_ENTRIES( Ee )

//
// constants
//

const double PION_MASS = 0.139570;
const double ELECTRON_MASS = 0.000511;


//
// member functions
//
  
Ee::Ee(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("Ecms", m_ecms = 3.686);
  declareProperty("Vr0cut", m_vr0cut=1.0);
  declareProperty("Vz0cut", m_vz0cut=10.0);
  //declareProperty("DiffPionLep", m_distin_pionlep=0.8);
  declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.8);
  declareProperty("TotalNumberOfChargedMax", m_total_number_of_charged_max=50);
  declareProperty("MinEstCut", m_min_emctime=0.0);
  declareProperty("MaxEstCut", m_max_emctime=14.0);
  declareProperty("CosthetaBarrelMax", m_costheta_barrel_max=0.8);
  declareProperty("CosthetaEndcapMin", m_costheta_endcap_min=0.86);
  declareProperty("CosthetaEndcapMax", m_costheta_endcap_max=0.92);
  declareProperty("EnergyBarrelMin", m_energy_barrel_min=0.025); 
  declareProperty("EnergyEndcapMin", m_energy_endcap_min=0.050); 
  declareProperty("PhotonIsoAngleMin", m_photon_iso_angle_min=10);
  declareProperty("PionPolarAngleMax", m_pion_polar_angle_max=0.8);
  declareProperty("PionMomentumMax", m_pion_momentum_max=0.45); 
  declareProperty("eonMomentumMin", m_eon_momentum_min=0.45); 
  declareProperty("eonMomentumMax", m_eon_momentum_max=2.0); 
  declareProperty("ProbPionMin", m_prob_pion_min=0.001);
  declareProperty("DipionMassMin", m_dipion_mass_min=3.0); 
  declareProperty("DipionMassMax", m_dipion_mass_max=3.2); 
  declareProperty("PiPiCosthetaMax", m_pipi_costheta_max=0.95);
  declareProperty("PiPiSysCosthetaMax", m_pipisys_costheta_max=0.90);
  declareProperty("DipionMassMin", m_ee_mass_min=2.7); 
  declareProperty("DipionMassMax", m_ee_mass_max=3.2); 
  declareProperty("epratio", m_ep_ratio=0.8);
  declareProperty("savetopo", m_savetopo = 1);
  declareProperty("data09",m_09data = 0); 
  }


StatusCode Ee::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;
  
    //ncut
  for (int index=0;index<10;index++){
	  ncounter[index]=0;
  }
  


  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Ee::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
 
  ncounter[0]++;
  //cout<<ncounter[0]<<endl;
  h_evtflw->Fill(0);
  SmartDataPtr<Event::EventHeader> eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();
  m_rec = m_event;
  
  //saveTopoInfo();
  
  if(buildJpsiToEe())
  {
	 cut_pip_costhe = (fabs(m_pip_costhe) < m_pion_polar_angle_max);
     cut_pim_costhe = (fabs(m_pim_costhe) < m_pion_polar_angle_max);
	 cut_ep_costhe = (fabs(m_ep_costhe) < m_pion_polar_angle_max);
     cut_em_costhe = (fabs(m_em_costhe) < m_pion_polar_angle_max);	 
     cut_pi_costhe = cut_pip_costhe && cut_pim_costhe;
     cut_PID = (m_prob_pip > m_prob_kp && m_prob_pip > m_prob_pion_min && m_prob_pim > m_prob_km && m_prob_pim > m_prob_pion_min);
     cut_cospipi = (m_vtx_cospipi < m_pipi_costheta_max);
     cut_cos2pisys = (fabs(m_vtx_cos2pisys) < m_pipisys_costheta_max);
     cut_mjpsi = (m_vtx_mrecpipi >= m_dipion_mass_min && m_vtx_mrecpipi <= m_dipion_mass_max);
	 cut_mjpsi_signal = (m_vtx_mrecpipi > 3.081916 && m_vtx_mrecpipi < 3.111916);
	 cut_epratio = (epratio_p > m_ep_ratio || epratio_m > m_ep_ratio || sqrt((epratio_p-1)*(epratio_p-1)+(epratio_m-1)*(epratio_m-1))<0.4);
	 cut_mee = (m_vtx_mee > m_ee_mass_min && m_vtx_mee < m_ee_mass_max);
	 
//fill hist
  if(cut_pim_costhe && cut_ep_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_epratio && cut_mee)
	  h_pip_costhe->Fill(m_pip_costhe);
  
  if(cut_pip_costhe && cut_ep_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_epratio && cut_mee)
	  h_pim_costhe->Fill(m_pim_costhe);  

  if(cut_pip_costhe && cut_pim_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_epratio && cut_mee)
	  h_ep_costhe->Fill(m_ep_costhe);
  
  if(cut_pip_costhe && cut_pim_costhe && cut_ep_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_epratio && cut_mee)
	  h_em_costhe->Fill(m_em_costhe); 
  
  if(cut_pip_costhe && cut_pim_costhe && cut_ep_costhe && cut_em_costhe  && cut_PID && cut_cos2pisys && cut_mjpsi_signal && cut_epratio && cut_mee)
	  h_cospipi->Fill(m_vtx_cospipi);

  if(cut_pip_costhe && cut_pim_costhe && cut_ep_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_mjpsi_signal && cut_epratio && cut_mee)
	  h_cos2pisys->Fill(m_vtx_cos2pisys);
  
  if(cut_pip_costhe && cut_pim_costhe && cut_ep_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_epratio && cut_mjpsi_signal)
	  h_mee->Fill(m_vtx_mee); 
  
  if(cut_pip_costhe && cut_pim_costhe && cut_ep_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi && cut_epratio && cut_mee)
	  h_mrecpipi->Fill(m_vtx_mrecpipi);   
  
  if(cut_pip_costhe && cut_pim_costhe && cut_ep_costhe && cut_em_costhe && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_mee)
      h_epratio->Fill(epratio_p,epratio_m);
  

  //fill tree
  if(cut_pi_costhe && cut_ep_costhe && cut_em_costhe)
    {
      ncounter[1]++;
	  h_evtflw->Fill(1);
      if(cut_PID)
      {
        ncounter[2]++;
		h_evtflw->Fill(2);
            if(cut_cospipi)
            {
              ncounter[3]++;
			  h_evtflw->Fill(3);
              if(cut_cos2pisys)
              {
                ncounter[4]++;
				h_evtflw->Fill(4);
                if(cut_mjpsi)
                {
					ncounter[5]++;
					h_evtflw->Fill(5);
					if(cut_epratio)
					{
						ncounter[6]++;
						h_evtflw->Fill(6);
						if(cut_mee)
						{
							ncounter[7]++;
							h_evtflw->Fill(7);
                  m_tree->Fill();
				 
				 

	  //saveTopoInfo
	if(m_savetopo == 1&& cut_mjpsi_signal)
	{
	 if (eventHeader->runNumber()<0)
	 {
		SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");

		if (!mcParticleCol)
		{
			std::cout << "Could not retrieve McParticelCol" << std::endl;
			return StatusCode::FAILURE;
		}

		else
		{
			Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
			Event::McParticle temp;
			m_idxmc=0;

			bool jpsiDecay = false;
			int jpsiIndex = -1;
			bool strange = false;

			for (; iter_mc != mcParticleCol->end(); iter_mc++)
			{
				if((*iter_mc)->primaryParticle()&&(*iter_mc)->particleProperty()==11&&((*iter_mc)->mother()).particleProperty()==11) {strange = true;}
				if ((*iter_mc)->primaryParticle()) continue;
				if (!(*iter_mc)->decayFromGenerator()) continue;
				//if ( ((*iter_mc)->mother()).trackIndex()<3 ) continue;
				if ((*iter_mc)->particleProperty() == 443) 
				{
					jpsiDecay = true;
					jpsiIndex = (*iter_mc)->trackIndex();
				}
				if (!jpsiDecay) continue;

				//int trkidx = (*iter_mc)->trackIndex() - rootIndex;

				int mcidx = ((*iter_mc)->mother()).trackIndex() - jpsiIndex;
				int pdgid = (*iter_mc)->particleProperty();
				if(strange &&((*iter_mc)->mother()).particleProperty()!=443) mcidx--; 
				if(pdgid == -22) continue;
				m_pdgid[m_idxmc] = pdgid;
				m_motheridx[m_idxmc] = mcidx;
				temp=(*iter_mc)->mother();
				m_motherpid[m_idxmc] = temp.particleProperty();

				if(pdgid == 443) m_drank[m_idxmc]=0;
				else
				{
					for(int i=1;i<100;i++)
					{
						if(temp.particleProperty()==443)
						{
							m_drank[m_idxmc]=i;
							break;
						}
						temp = temp.mother();
					}
				}

				m_idxmc++;    
			}

		}
	}
	TopoTree->Fill();
	}
  }
                }
              }
            }
          }
        }
      }

  } 
  return StatusCode::SUCCESS; 
}

StatusCode Ee::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  if(m_savetopo == 1)  TopoTree->Write();
  h_evtflw->Write();
  h_pip_costhe->Write();
  h_pim_costhe->Write();
  h_ep_costhe->Write();
  h_em_costhe->Write();  
  h_cospipi->Write();
  h_cos2pisys->Write();
  h_epratio->Write();
  h_mee->Write();
  h_mrecpipi->Write();
  m_fout->Close();
  
  cout<<"total number:            "<<ncounter[0]<<endl;
  cout<<"pi(e)_costhe<0.8:           "<<ncounter[1]<<endl;
  cout<<"Pass PID:                "<<ncounter[2]<<endl;
  cout<<"cut_cospipi:             "<<ncounter[3]<<endl;
  cout<<"cut_cos2pisys:           "<<ncounter[4]<<endl;
  cout<<"3.0<mrecpipi<3.2:        "<<ncounter[5]<<endl;
  cout<<"cut_epratio:             "<<ncounter[6]<<endl;
  cout<<"2.8<mee<3.2:           "<<ncounter[7]<<endl;

  
  return StatusCode::SUCCESS;
}


Ee::~Ee() {
}


void Ee::book_histogram() {
  h_cos2pisys = new TH1F("h_cos2pisys","h_cos2pisys",100,-1,1); 
  h_cospipi = new TH1F("h_cospipi","h_cospipi",100,-1,1);
  h_pim_costhe = new TH1F("h_pim_costhe","h_pim_costhe",100,-1,1);
  h_pip_costhe = new TH1F("h_pip_costhe","h_pip_costhe",100,-1,1);
  h_em_costhe = new TH1F("h_em_costhe","h_em_costhe",100,-1,1);
  h_ep_costhe = new TH1F("h_ep_costhe","h_ep_costhe",100,-1,1);
  h_mee = new TH1F("h_mee","h_mee",100,2.6,3.4);
  h_mrecpipi = new TH1F("h_mrecpipi","h_mrecpipi",100,3,3.2);
  h_epratio = new TH2D("h_epratio","h_epratio",1000,0,1.5,1000,0,1.5);
	
  h_evtflw = new TH1F("hevtflw", "eventflow", 9, 0, 9);
  if (!h_evtflw) return;
  h_evtflw->GetXaxis()->SetBinLabel(1, "raw");
  h_evtflw->GetXaxis()->SetBinLabel(2, "pi_costhe<0.8");
  h_evtflw->GetXaxis()->SetBinLabel(3, "Pass pi PID");
  h_evtflw->GetXaxis()->SetBinLabel(4, "cut_cospipi");
  h_evtflw->GetXaxis()->SetBinLabel(5, "cut_cos2pisys"); 
  h_evtflw->GetXaxis()->SetBinLabel(6, "3.0<mrecpipi<3.2");
  h_evtflw->GetXaxis()->SetBinLabel(7, "cut_epratio");
  h_evtflw->GetXaxis()->SetBinLabel(8, "3.0<mee<3.2");
}


void Ee::book_tree() {
  m_tree=new TTree("signal", "signal");
  TopoTree = new TTree("topoall","topoall");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");
  
  //topo info
  		TopoTree->Branch("run", &m_run, "run/I");
		TopoTree->Branch("rec", &m_rec, "rec/I");
		TopoTree->Branch("indexmc", &m_idxmc, "indexmc/I");

		//		TopoTree->Branch("trkidx", m_trkidx, "trkidx[indexmc]/I");
		TopoTree->Branch("pdgid", m_pdgid, "pdgid[indexmc]/I");
		TopoTree->Branch("drank", m_drank, "drank[indexmc]/I");
		TopoTree->Branch("motheridx", m_motheridx, "motheridx[indexmc]/I");
		TopoTree->Branch("motherpid", m_motherpid, "motherpid[indexmc]/I");

  
  
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
  m_tree->Branch("vr0",&m_vr0,"vr0/D");
  m_tree->Branch("vz0",&m_vz0,"vz0/D");
  
  
   // PID info
  m_tree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
  m_tree->Branch("prob_pim", &m_prob_pim, "prob_pim/D"); 
  m_tree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
  m_tree->Branch("prob_km", &m_prob_km, "prob_km/D"); 
  //m_tree->Branch("prob_p", &m_prob_p, "prob_p/D"); 
  //m_tree->Branch("prob_pb", &m_prob_pb, "prob_pb/D"); 

  // save pion info
  m_tree->Branch("pip_px", &m_pip_px, "pip_px/D");
  m_tree->Branch("pip_py", &m_pip_py, "pip_py/D");
  m_tree->Branch("pip_pz", &m_pip_pz, "pip_pz/D");
  m_tree->Branch("pip_p", &m_pip_p, "pip_p/D");

  m_tree->Branch("pim_px", &m_pim_px, "pim_px/D");
  m_tree->Branch("pim_py", &m_pim_py, "pim_py/D");
  m_tree->Branch("pim_pz", &m_pim_pz, "pim_pz/D");
  m_tree->Branch("pim_p", &m_pim_p, "pim_p/D");
  
  m_tree->Branch("cos#theta_pi_p", &m_cos_theta_pi_p, "cos#theta_pi_p/D");
  m_tree->Branch("cos#theta_pi_m", &m_cos_theta_pi_m, "cos#theta_pi_m/D");

  // save eon info
  m_tree->Branch("ep_px", &m_ep_px, "ep_px/D");
  m_tree->Branch("ep_py", &m_ep_py, "ep_py/D");
  m_tree->Branch("ep_pz", &m_ep_pz, "ep_pz/D");
  m_tree->Branch("ep_p", &m_ep_p, "ep_p/D");

  m_tree->Branch("em_px", &m_em_px, "em_px/D");
  m_tree->Branch("em_py", &m_em_py, "em_py/D");
  m_tree->Branch("em_pz", &m_em_pz, "em_pz/D");
  m_tree->Branch("em_p", &m_em_p, "em_p/D");
  
  m_tree->Branch("cos#theta_e_p", &m_cos_theta_e_p, "cos#theta_e_p/D");
  m_tree->Branch("cos#theta_e_m", &m_cos_theta_e_m, "cos#theta_e_m/D");


  // fitted info
  //pipi
  m_tree->Branch("vtx_pip_px", &m_vtx_pip_px, "vtx_pip_px/D");
  m_tree->Branch("vtx_pip_py", &m_vtx_pip_py, "vtx_pip_py/D");
  m_tree->Branch("vtx_pip_pz", &m_vtx_pip_pz, "vtx_pip_pz/D");
  m_tree->Branch("vtx_pip_p", &m_vtx_pip_p, "vtx_pip_p/D");
  m_tree->Branch("vtx_pip_e", &m_vtx_pip_e, "vtx_pip_e/D");
  m_tree->Branch("vtx_pim_px", &m_vtx_pim_px, "vtx_pim_px/D");
  m_tree->Branch("vtx_pim_py", &m_vtx_pim_py, "vtx_pim_py/D");
  m_tree->Branch("vtx_pim_p", &m_vtx_pim_p, "vtx_pim_p/D");  
  m_tree->Branch("vtx_pim_e", &m_vtx_pim_e, "vtx_pim_e/D");

  m_tree->Branch("vtx_mpipi", &m_vtx_mpipi, "vtx_mpipi/D");
  m_tree->Branch("vtx_mrecpipi", &m_vtx_mrecpipi, "vtx_mrecpipi/D");
  m_tree->Branch("vtx_cospipi", &m_vtx_cospipi, "vtx_cospipi/D");
  m_tree->Branch("vtx_cos2pisys", &m_vtx_cos2pisys, "vtx_cos2pisys/D");  
  m_tree->Branch("vtx_cospip", &m_vtx_cospip, "vtx_cospip/D");
  m_tree->Branch("vtx_cospim", &m_vtx_cospim, "vtx_cospim/D");

  //Ee
  m_tree->Branch("vtx_ep_px", &m_vtx_ep_px, "vtx_ep_px/D");
  m_tree->Branch("vtx_ep_py", &m_vtx_ep_py, "vtx_ep_py/D");
  m_tree->Branch("vtx_ep_pz", &m_vtx_ep_pz, "vtx_ep_pz/D");
  m_tree->Branch("vtx_ep_p", &m_vtx_ep_p, "vtx_ep_p/D");
  m_tree->Branch("vtx_ep_e", &m_vtx_ep_e, "vtx_ep_e/D");
  m_tree->Branch("vtx_em_px", &m_vtx_em_px, "vtx_em_px/D");
  m_tree->Branch("vtx_em_py", &m_vtx_em_py, "vtx_em_py/D");
  m_tree->Branch("vtx_em_p", &m_vtx_em_p, "vtx_em_p/D");  
  m_tree->Branch("vtx_em_e", &m_vtx_em_e, "vtx_em_e/D");

  m_tree->Branch("vtx_mee", &m_vtx_mee, "vtx_mee/D");
  m_tree->Branch("vtx_cosee", &m_vtx_cosee, "vtx_cosee/D");
  m_tree->Branch("vtx_cosep", &m_vtx_cosep, "vtx_cosep/D");
  m_tree->Branch("vtx_cosem", &m_vtx_cosem, "vtx_cosem/D");  
 
  //for 4C
  m_tree->Branch("chi4C", &m_chi4C, "chi4C/D");
  m_tree->Branch("me0", &m_me0, "me0/D");

}


bool Ee::buildJpsiToEe() {

  SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");    //重建后的事例
  if(!evtRecEvent) return false;


  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");    //重建事例的所有径迹信息
  if(!evtRecTrkCol) return false;

  std::vector<int> iPGood, iMGood; 
  selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

  if (!(m_nptrk == 2 && m_nmtrk == 2)) return false;


  if(selectPionPlusPionMinus(evtRecTrkCol, iPGood, iMGood)!=1) return false;
    
  if(selectePluseMinus(evtRecTrkCol, iPGood, iMGood)!=1) return false;
  return true;
}


CLHEP::Hep3Vector Ee::getOrigin() {
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


bool Ee::passVertexSelection(CLHEP::Hep3Vector xorigin,
				    RecMdcTrack* mdcTrk ) {
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


int Ee::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				   std::vector<int> & iPGood,
				   std::vector<int> & iMGood) {

  CLHEP::Hep3Vector xorigin = getOrigin(); 

  std::vector<int> iGood;
  iGood.clear();
  iPGood.clear();
  iMGood.clear();
  
  
  // loop through charged tracks 
  for(int i = 0; i < evtRecEvent->totalCharged(); i++){        //evtRecTrkCol先放的是带电，然后是中性径迹，所以只用循环到totalcharged而不是totaltracks
    // get mdcTrk 
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;

    // Good Kalman Track 
    if(!(*itTrk)->isMdcKalTrackValid()) continue;

    if(!(*itTrk)->isMdcTrackValid()) continue;
    RecMdcTrack* mdcTrk = (*itTrk)->mdcTrack();

    // Good Vertex 
    if (!passVertexSelection(xorigin, mdcTrk) ) continue; 

    // Polar angle cut
    if(fabs(cos(mdcTrk->theta())) > 0.93) continue;

    iGood.push_back((*itTrk)->trackId());
    if(mdcTrk->charge()>0) iPGood.push_back((*itTrk)->trackId());
    if(mdcTrk->charge()<0) iMGood.push_back((*itTrk)->trackId());

  } // end charged tracks

  m_ncharged = iGood.size();
  m_nptrk = iPGood.size();
  m_nmtrk = iMGood.size(); 
  
  if (m_nptrk > 0 && m_nmtrk > 0) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[0];
    EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[0];
    saveTrkInfo(itTrk_p, itTrk_m);
  }
  
  return iGood.size(); 
}

int Ee::selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood,
				       std::vector<int> iMGood) {
  int npipi = 0;
  RecMdcTrack* m_mdcTrk_p;
  RecMdcTrack* m_mdcTrk_m;
  EvtRecTrackIterator m_itTrk_p,m_itTrk_m;
  
  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
    RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
    if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

    for(unsigned int i2 = 0; i2 < iMGood.size(); i2++) {
      EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[i2];
      RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
      if (mdcTrk_m->charge() > 0) continue; // only negative charged tracks
	  
	        // pion momentum
      if ( mdcTrk_p->p() < m_pion_momentum_max  &&
      	       mdcTrk_m->p() < m_pion_momentum_max )
	  {
	  m_mdcTrk_m = (*itTrk_m)->mdcTrack();
	  m_mdcTrk_p = (*itTrk_p)->mdcTrack();
	  m_itTrk_p = itTrk_p;
	  m_itTrk_m = itTrk_m;
	
      // polar angle for both pions
      m_pip_costhe = cos(mdcTrk_p->theta());
	  m_pim_costhe = cos(mdcTrk_m->theta());

      // track PID
      double prob_pip, prob_kp, prob_pim, prob_km; 
      calcTrackPID(itTrk_p, prob_pip, prob_kp);  
      calcTrackPID(itTrk_m, prob_pim, prob_km);
      // printf(">>> %f, %f, %f, %f \n", prob_pip, prob_kp, prob_pim, prob_km);
	  
	  m_prob_pip = prob_pip;
      m_prob_kp = prob_kp;
      //m_prob_p = prob_p;
      m_prob_pim = prob_pim;
      m_prob_km = prob_km;
      //m_prob_pb = prob_pb;

      //pass PID
	  
	  
      // apply vertex fit
      RecMdcKalTrack *pipTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+iMGood[i2]))->mdcKalTrack();

      savePionInfo(pipTrk, pimTrk); 
	 
      if (! hasGoodPiPiVertex(pipTrk, pimTrk) )continue;
              npipi++;
	}}}
  return npipi; 
}


int Ee::selectePluseMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood,
				       std::vector<int> iMGood) {
  int nEe = 0;
  RecMdcTrack* m_mdcTrk_p;
  RecMdcTrack* m_mdcTrk_m;
  RecEmcShower *m_emcTrk_p;
  RecEmcShower *m_emcTrk_m;
    EvtRecTrackIterator m_itTrk_p,m_itTrk_m;


  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
    RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();

	RecEmcShower *emcTrk_p = (*itTrk_p)->emcShower();
   
   if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

    for(unsigned int i2 = 0; i2 < iMGood.size(); i2++) {
      EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[i2];

      RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
	if(!((*itTrk_m)->isEmcShowerValid())||!((*itTrk_p)->isEmcShowerValid())) continue; 
   	  RecEmcShower *emcTrk_m = (*itTrk_m)->emcShower();
    if (mdcTrk_m->charge() > 0) continue; // only negative charged tracks
	  
	  
	if ( mdcTrk_p->p() > m_eon_momentum_min  &&    mdcTrk_p->p() < m_eon_momentum_max  &&
      	       mdcTrk_m->p() > m_eon_momentum_min && mdcTrk_m->p() < m_eon_momentum_max )
	{
	m_mdcTrk_m = (*itTrk_m)->mdcTrack();
	m_mdcTrk_p = (*itTrk_p)->mdcTrack();
	m_emcTrk_m = (*itTrk_m)->emcShower();
	m_emcTrk_p = (*itTrk_p)->emcShower();
	  m_itTrk_p = itTrk_p;
	  m_itTrk_m = itTrk_m;
	  
      // polar angle for both pions
      m_ep_costhe = cos(mdcTrk_p->theta());
	  m_em_costhe = cos(mdcTrk_m->theta());	  

	  // ratio cut
	  double emcenergy_p = emcTrk_p->energy(); 	  
	  double emcenergy_m = emcTrk_m->energy(); 
	  double pemc_p=fabs(mdcTrk_p->p());
	  double pemc_m=fabs(mdcTrk_m->p());
	  epratio_p = emcenergy_p/pemc_p;
	  epratio_m = emcenergy_m/pemc_m;

      // apply vertex fit
      RecMdcKalTrack *epTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      RecMdcKalTrack *emTrk = (*(evtRecTrkCol->begin()+iMGood[i2]))->mdcKalTrack();
	    
	  saveeonInfo(epTrk,emTrk);
		
      if (! hasGoodEeVertex(epTrk, emTrk) ) continue;	
	  	  nEe++;
	}}
  }
  return nEe; 
}

void Ee::calcTrackPID(EvtRecTrackIterator itTrk_p,
			     double& prob_pip,
			     double& prob_kp) {
  prob_pip = 999.; 
  prob_kp = 999.; 
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
  }
}

bool Ee::hasGoodPiPiVertex(RecMdcKalTrack *pipTrk,
				  RecMdcKalTrack *pimTrk) {

  HepLorentzVector pcms;
  if(m_09data==1)
    pcms = HepLorentzVector(0.011*m_ecms, -0.001, 0.005, m_ecms);
  else 
	pcms = HepLorentzVector(0.011*m_ecms, 0., 0., m_ecms);

  HepLorentzVector p4_vtx_pip, p4_vtx_pim,p4_vtx_pipi,p4_vtx_recpipi;
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
      
  p4_vtx_pip = vtxfit->pfit(0) ;
  p4_vtx_pim = vtxfit->pfit(1) ;
  p4_vtx_recpipi = pcms - p4_vtx_pip - p4_vtx_pim;
  p4_vtx_pipi = p4_vtx_pip + p4_vtx_pim;


  double cospipi = cos(p4_vtx_pip.vect().angle(p4_vtx_pim.vect()));
  double cos2pisys = (p4_vtx_pip + p4_vtx_pim).cosTheta();
  double cospip = p4_vtx_pip.cosTheta();
  double cospim = p4_vtx_pim.cosTheta();  

  //cospipi

  //cos2pisys

  //mrecpipi  

  savepipiVtxInfo(p4_vtx_pip, p4_vtx_pim); 
  m_vtx_mrecpipi = p4_vtx_recpipi.m();
  m_vtx_mpipi = p4_vtx_pipi.m();
  m_vtx_cospipi = cospipi;
  m_vtx_cos2pisys = cos2pisys;
  m_vtx_cospip = cospip;
  m_vtx_cospim = cospim;
  
  
  return true;
}

bool Ee::hasGoodEeVertex(RecMdcKalTrack *epTrk,
				  RecMdcKalTrack *emTrk) {

  HepLorentzVector p4_vtx_ep, p4_vtx_em,p4_vtx_Ee;
  WTrackParameter wvepTrk, wvemTrk;
  epTrk->setPidType(RecMdcKalTrack::electron);

  wvepTrk = WTrackParameter(ELECTRON_MASS, epTrk->getZHelixE(), epTrk->getZErrorE());

  emTrk->setPidType(RecMdcKalTrack::electron);
  wvemTrk = WTrackParameter(ELECTRON_MASS, emTrk->getZHelixE(), emTrk->getZErrorE());
  
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
  vtxfit->AddTrack(0,  wvepTrk);
  vtxfit->AddTrack(1,  wvemTrk);
  vtxfit->AddVertex(0, vxpar,0,1);

  if(!vtxfit->Fit(0)) return false;

  vtxfit->Swim(0);

  p4_vtx_ep = vtxfit->pfit(0) ;
  p4_vtx_em = vtxfit->pfit(1) ;
  p4_vtx_Ee = p4_vtx_ep + p4_vtx_em;
  
  double cosee = cos(p4_vtx_ep.vect().angle(p4_vtx_em.vect()));
  double cosep = p4_vtx_ep.cosTheta();
  double cosem = p4_vtx_em.cosTheta();  
  
  saveEeVtxInfo(p4_vtx_ep, p4_vtx_em); 
  m_vtx_mee = p4_vtx_Ee.m();
  m_vtx_cosee = cosee;
  m_vtx_cosep = cosep;
  m_vtx_cosem = cosem;
  return true;
}


void Ee::saveTrkInfo(EvtRecTrackIterator itTrk_p,
			    EvtRecTrackIterator itTrk_m) {

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


void Ee::savePionInfo(RecMdcKalTrack *pipTrk,
			     RecMdcKalTrack *pimTrk){

  m_pip_px = pipTrk->px();
  m_pip_py = pipTrk->py();
  m_pip_pz = pipTrk->pz();
  m_pip_p = pipTrk->p();
  
  m_pim_px = pimTrk->px();
  m_pim_py = pimTrk->py();
  m_pim_pz = pimTrk->pz();
  m_pim_p = pimTrk->p(); 
  
  m_cos_theta_pi_p=cos(pipTrk->theta());
  m_cos_theta_pi_m=cos(pimTrk->theta());
}

void Ee::saveeonInfo(RecMdcKalTrack *epTrk,
			     RecMdcKalTrack *emTrk){

  m_ep_px = epTrk->px();
  m_ep_py = epTrk->py();
  m_ep_pz = epTrk->pz();
  m_ep_p = epTrk->p();
  
  m_em_px = emTrk->px();
  m_em_py = emTrk->py();
  m_em_pz = emTrk->pz();
  m_em_p = emTrk->p(); 
  
  m_cos_theta_e_p=cos(epTrk->theta());
  m_cos_theta_e_m=cos(emTrk->theta());
}

void Ee::savepipiVtxInfo(HepLorentzVector p4_vtx_pip,
			    HepLorentzVector p4_vtx_pim){

  m_vtx_pip_px = p4_vtx_pip.px();
  m_vtx_pip_py = p4_vtx_pip.py();
  m_vtx_pip_pz = p4_vtx_pip.pz();
  m_vtx_pip_p = sqrt(p4_vtx_pip.px()*p4_vtx_pip.px()+p4_vtx_pip.py()*p4_vtx_pip.py()+p4_vtx_pip.pz()*p4_vtx_pip.pz());
  m_vtx_pip_e = p4_vtx_pip.e();

  m_vtx_pim_px = p4_vtx_pim.px();
  m_vtx_pim_py = p4_vtx_pim.py();
  m_vtx_pim_pz = p4_vtx_pim.pz();
  m_vtx_pim_p = sqrt(p4_vtx_pim.px()*p4_vtx_pim.px()+p4_vtx_pim.py()*p4_vtx_pim.py()+p4_vtx_pim.pz()*p4_vtx_pim.pz());
  m_vtx_pim_e = p4_vtx_pim.e();

}

void Ee::saveEeVtxInfo(HepLorentzVector p4_vtx_ep,
			    HepLorentzVector p4_vtx_em){

  m_vtx_ep_px = p4_vtx_ep.px();
  m_vtx_ep_py = p4_vtx_ep.py();
  m_vtx_ep_pz = p4_vtx_ep.pz();
  m_vtx_ep_p = sqrt(p4_vtx_ep.px()*p4_vtx_ep.px()+p4_vtx_ep.py()*p4_vtx_ep.py()+p4_vtx_ep.pz()*p4_vtx_ep.pz());
  m_vtx_ep_e = p4_vtx_ep.e();

  m_vtx_em_px = p4_vtx_em.px();
  m_vtx_em_py = p4_vtx_em.py();
  m_vtx_em_pz = p4_vtx_em.pz();
  m_vtx_em_p = sqrt(p4_vtx_em.px()*p4_vtx_em.px()+p4_vtx_em.py()*p4_vtx_em.py()+p4_vtx_em.pz()*p4_vtx_em.pz());
  m_vtx_em_e = p4_vtx_em.e();

}