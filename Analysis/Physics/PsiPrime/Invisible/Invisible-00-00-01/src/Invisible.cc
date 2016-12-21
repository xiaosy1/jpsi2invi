// -*- C++ -*-
//
//
// Description: Psi' -> pi+pi-Jpsi,J/psi -> invisible 
//
// Original Author:  Chen Qian <chenq@pku.edu.cn>
//         Created:  [2016-10-21 Fri 19:30] 
//         Inspired by Shi xin's code 
//


//
// system include files
//

#include <iostream>
#include <stdlib.h> 
#include <vector>

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

#include "TLorentzVector.h"

#include "ParticleID/ParticleID.h"

#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

//
// class declaration
//

class Invisible : public Algorithm {
  
public:
  Invisible(const std::string&, ISvcLocator*);
  ~Invisible(); 
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
  double m_ep_ratio;
  
  //setting cut criteria
  bool cut_pip_costhe;
  bool cut_pim_costhe;
  bool cut_pi_costhe;
  bool cut_pip_p;
  bool cut_pim_p;
  bool cut_PID;
  bool cut_cospipi;
  bool cut_cos2pisys;
  bool cut_mjpsi;
  bool cut_mjpsi_signal;
  bool cut_ngamma;
  
  // output file
  std::string m_output_filename;
  TFile* m_fout; 
  
  // define Histograms
  TH1F* h_evtflw; 

  TH1F* h_cos2pisys; 
  TH1F* h_cospipi;
  TH1F* h_ngamma;
  TH1F* h_pim_costhe;
  TH1F* h_pip_costhe;
  TH1F* h_pip_p;
  TH1F* h_pim_p;
  TH1F* h_mrecpipi;
  TH1F* h_mpipi;
  
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
  double m_mdcp_p;
  double m_mdcm_p;
  
  // neutral tracks
  int m_nshow;
  int m_ngam;
  std::vector<double> *m_raw_gpx; 
  std::vector<double> *m_raw_gpy; 
  std::vector<double> *m_raw_gpz; 
  std::vector<double> *m_raw_ge; 
  
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
  
  double m_cospipi;
  double m_cos2pisys;

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
  
  //jpsi
  double m_vtx_jpsi_p;
  // vertex 
  double m_vr0;
  double m_vz0;
  
    // PID info
  double m_prob_pip;
  double m_prob_pim;
  double m_prob_kp;
  double m_prob_km;

  //ncut
  //vector<int> counter;
  int ncounter[10];
  
  int Ncut0;
  int Ncut1;
  int Ncut2;
  int Ncut3;
  int Ncut4;
  int Ncut5;
  int Ncut6;
  int Ncut7;
  int Ncut8;
  int Ncut9;
  int Ncut10;
  int Ncut11;
  int Ncut12;
  
  int m_savetopo;
  int m_09data;
  
  // functions
  void book_histogram();
  void book_tree();
  void save_topo();  
  bool buildJpsiToInvisible();
  
  //void saveGenInfo(); 
  void saveTrkInfo(EvtRecTrackIterator,
		   EvtRecTrackIterator);
  void savePionInfo(RecMdcKalTrack *,
		    RecMdcKalTrack *);
  void savepipiVtxInfo(HepLorentzVector,
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
		    double& ,
		    double&);
  bool hasGoodPiPiVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *);
  int selectNeutralTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>);
  bool passVertexSelection(CLHEP::Hep3Vector,
			   RecMdcTrack* ); 
  CLHEP::Hep3Vector getOrigin();
}; 

//
// module declare 组件和加载声明
//

DECLARE_ALGORITHM_FACTORY( Invisible )
DECLARE_FACTORY_ENTRIES( Invisible ) {
  DECLARE_ALGORITHM(Invisible);
}

LOAD_FACTORY_ENTRIES( Invisible )

//
// constants
//

const double PION_MASS = 0.139570;
const double MU_MASS = 0.105658;


//
// member functions
//
  
Invisible::Invisible(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator) {
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("Ecms", m_ecms = 3.686);
  declareProperty("Vr0cut", m_vr0cut=1.0);
  declareProperty("Vz0cut", m_vz0cut=10.0);
  //declareProperty("DiffPionLep", m_distin_pionlep=0.8);
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
  declareProperty("PionPolarAngleMax", m_pion_polar_angle_max=0.8);
  declareProperty("PionMomentumMax", m_pion_momentum_max=0.45); 
  declareProperty("ProbPionMin", m_prob_pion_min=0.001);
  declareProperty("DipionMassMin", m_dipion_mass_min=3.0); 
  declareProperty("DipionMassMax", m_dipion_mass_max=3.2); 
  declareProperty("PiPiCosthetaMax", m_pipi_costheta_max=0.95);
  declareProperty("PiPiSysCosthetaMax", m_pipisys_costheta_max=0.90);
  declareProperty("epratio", m_ep_ratio=0.26);
  declareProperty("savetopo", m_savetopo=1);
  declareProperty("data09",m_09data = 0); 

}


StatusCode Invisible::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;
  
  //ncut  
  Ncut0=0;
  Ncut1=0;
  Ncut2=0;
  Ncut3=0;
  Ncut4=0;
  Ncut5=0;
  Ncut6=0;
  Ncut7=0;
  Ncut8=0;
  Ncut9=0;
  Ncut10=0;
  Ncut11=0;
  Ncut12=0;
  for (int index=0;index<10;index++){
	  ncounter[index]=0;
  }


  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Invisible::execute() {
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
    
  //counter.clear();	
  if(buildJpsiToInvisible())
  {
	  //saveTopoInfo
  cut_pip_costhe = (fabs(m_pip_costhe) < m_pion_polar_angle_max);
  cut_pim_costhe = (fabs(m_pim_costhe) < m_pion_polar_angle_max);
  cut_pi_costhe = cut_pip_costhe && cut_pim_costhe;
  cut_pip_p = (0 < m_mdcp_p && m_mdcp_p < m_pion_momentum_max);
  cut_pim_p = (0 < m_mdcm_p && m_mdcm_p < m_pion_momentum_max);
  cut_PID = (m_prob_pip > m_prob_kp && m_prob_pip > m_prob_pion_min && m_prob_pim > m_prob_km && m_prob_pim > m_prob_pion_min);
  cut_cospipi = (m_vtx_cospipi < m_pipi_costheta_max);
  cut_cos2pisys = (fabs(m_vtx_cos2pisys) < m_pipisys_costheta_max);
  cut_mjpsi = (m_vtx_mrecpipi >= m_dipion_mass_min && m_vtx_mrecpipi <= m_dipion_mass_max);
  cut_mjpsi_signal = (m_vtx_mrecpipi > 3.081916 && m_vtx_mrecpipi < 3.111916);
  cut_ngamma = (m_ngam == 0);  
  
  //fill hist
  if(cut_pi_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi && cut_ngamma)
	  h_mrecpipi->Fill(m_vtx_mrecpipi);
  
  if(cut_pi_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_ngamma)
      h_mpipi->Fill(m_vtx_mpipi);	  
  
  if(cut_pi_costhe && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_ngamma)
	  h_pip_p->Fill(m_mdcp_p);
  
  if(cut_pi_costhe && cut_pip_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_ngamma)
	  h_pim_p->Fill(m_mdcm_p);

  if(cut_pi_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cos2pisys && cut_mjpsi_signal && cut_ngamma)
	  h_cospipi->Fill(m_vtx_cospipi);

  if(cut_pi_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_mjpsi_signal && cut_ngamma)
	  h_cos2pisys->Fill(m_vtx_cos2pisys);

  if(cut_pim_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_ngamma)
	  h_pip_costhe->Fill(m_pip_costhe);

  if(cut_pip_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal && cut_ngamma)
	  h_pim_costhe->Fill(m_pim_costhe);

  if(cut_pi_costhe && cut_pip_p && cut_pim_p && cut_PID && cut_cospipi && cut_cos2pisys && cut_mjpsi_signal)
	  h_ngamma->Fill(m_ngam);
  
  //fill tree
  if(cut_pi_costhe)
    {
      ncounter[1]++;
	  h_evtflw->Fill(1);
      if(cut_PID)
      {
        ncounter[2]++;
        h_evtflw->Fill(2);
        if(cut_pip_p && cut_pim_p)
        {
          ncounter[3]++;
		  h_evtflw->Fill(3);
          if(cut_ngamma)
          {
            ncounter[4]++;
			h_evtflw->Fill(4);
            if(cut_cospipi)
            {
              ncounter[5]++;
			  h_evtflw->Fill(5);
              if(cut_cos2pisys)
              {
                ncounter[6]++;
				h_evtflw->Fill(6);
                if(cut_mjpsi)
                {
                  ncounter[7]++;
				  h_evtflw->Fill(7);
                  m_tree->Fill();
				  
				  //saveTopoInfo
		if(m_savetopo == 1 && cut_mjpsi_signal)
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
			bool psiprimeDecay = true;
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

StatusCode Invisible::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  if(m_savetopo==1) TopoTree->Write();
  h_evtflw->Write();
  h_pim_p->Write();
  h_pip_p->Write();
  h_pip_costhe->Write();
  h_pim_costhe->Write();
  h_ngamma->Write();
  h_cospipi->Write();
  h_cos2pisys->Write();
  h_mpipi->Write();
  h_mrecpipi->Write();  
  m_fout->Close();
  
  cout<<"total number:            "<<ncounter[0]<<endl;
  cout<<"pi_costhe<0.8:           "<<ncounter[1]<<endl;
  cout<<"Pass pi PID:             "<<ncounter[2]<<endl;
  cout<<"cut_pip_p&&cut_pim_p:    "<<ncounter[3]<<endl;
  cout<<"cut_ngam:                "<<ncounter[4]<<endl;
  cout<<"cut_cospipi:             "<<ncounter[5]<<endl;
  cout<<"cut_cos2pisys:           "<<ncounter[6]<<endl;
  cout<<"3.0<mrecpipi<3.2:        "<<ncounter[7]<<endl;
    
  return StatusCode::SUCCESS;
}


Invisible::~Invisible() {
}


void Invisible::book_histogram() {
  h_evtflw = new TH1F("hevtflw", "eventflow", 9, 0, 9);
  if (!h_evtflw) return;  
  h_evtflw->GetXaxis()->SetBinLabel(1, "raw");
  h_evtflw->GetXaxis()->SetBinLabel(2, "pi_costhe<0.8");
  h_evtflw->GetXaxis()->SetBinLabel(3, "Pass pi PID");
  h_evtflw->GetXaxis()->SetBinLabel(4, "cut_pip_p&&cut_pim_p:");
  h_evtflw->GetXaxis()->SetBinLabel(5, "cut_ngam"); 
  h_evtflw->GetXaxis()->SetBinLabel(6, "cut_cospipi");
  h_evtflw->GetXaxis()->SetBinLabel(7, "cut_cos2pisys");
  h_evtflw->GetXaxis()->SetBinLabel(8, "3.0<mrecpipi<3.2");	
	
  h_cos2pisys = new TH1F("h_cos2pisys","h_cos2pisys",100,-1,1); 
  h_cospipi = new TH1F("h_cospipi","h_cospipi",100,-1,1);
  h_ngamma = new TH1F("h_ngamma","h_ngamma",100,0,20);
  h_pim_costhe = new TH1F("h_pim_costhe","h_pim_costhe",100,-1,1);
  h_pip_costhe = new TH1F("h_pip_costhe","h_pip_costhe",100,-1,1);
  h_pip_p = new TH1F("h_pip_p","h_pip_p",100,0,0.5);
  h_pim_p = new TH1F("h_pim_p","h_pim_p",100,0,0.5);
  h_mpipi = new TH1F("h_mpipi","h_mpipi",100,0.2,0.7);
  h_mrecpipi = new TH1F("h_mrecpipi","h_mrecpipi",100,3,3.2);
}


void Invisible::book_tree() {
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
  
  m_tree->Branch("ngam", &m_ngam, "ngam/I");  
  /*//netual tracks
  m_tree->Branch("nshow", &m_nshow, "nshow/I");
  m_tree->Branch("ngam", &m_ngam, "ngam/I");
  //m_tree->Branch("raw_gpx", &m_raw_gpx);
  //m_tree->Branch("raw_gpy", &m_raw_gpy);
  //m_tree->Branch("raw_gpz", &m_raw_gpz);
  //m_tree->Branch("raw_ge", &m_raw_ge);*/
  
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

  //jpsi
  m_tree->Branch("vtx_jpsi_p", &m_vtx_jpsi_p, "vtx_jpsi_p/D");

}


void save_topo(){

}

bool Invisible::buildJpsiToInvisible() {

  SmartDataPtr<EvtRecEvent> evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");    //重建后的事例
  if(!evtRecEvent) return false;


  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");    //重建事例的所有径迹信息
  if(!evtRecTrkCol) return false;

  std::vector<int> iPGood, iMGood; 
  selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

  if (!(m_nptrk == 1 && m_nmtrk == 1)) return false;

  selectNeutralTracks(evtRecEvent, evtRecTrkCol);   //if (m_ngam != 0) return;  

  if(selectPionPlusPionMinus(evtRecTrkCol, iPGood, iMGood)!=1) return false;

  return true;
}


CLHEP::Hep3Vector Invisible::getOrigin() {
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


bool Invisible::passVertexSelection(CLHEP::Hep3Vector xorigin,
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


int Invisible::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
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
    if(fabs(cos(mdcTrk->theta())) > m_cha_costheta_cut) continue;

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

int Invisible::selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood,
				       std::vector<int> iMGood) {
  int npipi = 0;
  
  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
    RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
    if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

    for(unsigned int i2 = 0; i2 < iMGood.size(); i2++) {
      EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[i2];
      RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
      if (mdcTrk_m->charge() > 0) continue; // only negative charged tracks

      // polar angle for both pions
      m_pip_costhe = cos(mdcTrk_p->theta());
	  m_pim_costhe = cos(mdcTrk_m->theta());

      // pion momentum
      m_mdcp_p = mdcTrk_p->p();
      m_mdcm_p = mdcTrk_m->p();
	  
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
	 
      if (! hasGoodPiPiVertex(pipTrk, pimTrk) ) continue; 
      
      npipi++;
    }
  } 

  return npipi; 
}


void Invisible::calcTrackPID(EvtRecTrackIterator itTrk_p,
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

bool Invisible::hasGoodPiPiVertex(RecMdcKalTrack *pipTrk,RecMdcKalTrack *pimTrk) {

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
      
  WTrackParameter wpip = vtxfit->wtrk(0);
  WTrackParameter wpim = vtxfit->wtrk(1);
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
  
  m_vtx_jpsi_p = sqrt(p4_vtx_recpipi.px()*p4_vtx_recpipi.px()+p4_vtx_recpipi.py()*p4_vtx_recpipi.py()+p4_vtx_recpipi.pz()*p4_vtx_recpipi.pz());

  
  return true;
}



int Invisible::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol) {
  
  std::vector<int> iGam;
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
    double abs_costheta = fabs(cos(emcTrk->theta()));
    bool barrel = (abs_costheta < m_costheta_barrel_max); 
    bool endcap = (abs_costheta > m_costheta_endcap_min
		   && abs_costheta < m_costheta_endcap_max);
    double eraw = emcTrk->energy();
    
   // if ( !( (barrel && eraw > m_energy_barrel_min)
	//    || (endcap && eraw > m_energy_endcap_min))||eraw > 2.00)  continue;

     int    module = emcTrk->module();
    double CutEnergyThreshold;
    if ( module == 1 ) CutEnergyThreshold  = m_energy_barrel_min;
    else               CutEnergyThreshold  = m_energy_endcap_min;
    if ( eraw < CutEnergyThreshold || eraw > 2.00 )             continue;

	
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

  //saveGamInfo(iGam, evtRecTrkCol);   
  
  
  return iGam.size(); 
}


void Invisible::saveTrkInfo(EvtRecTrackIterator itTrk_p,
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

void Invisible::saveGamInfo(std::vector<int> iGam,
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
  }
}

void Invisible::savePionInfo(RecMdcKalTrack *pipTrk,
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


void Invisible::savepipiVtxInfo(HepLorentzVector p4_vtx_pip,
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

