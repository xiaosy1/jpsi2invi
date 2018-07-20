#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooHistPdf.h"
#include "RooFFTConvPdf.h"
#include "RooBreitWigner.h"
#include "RooChebychev.h"
#include "RooExponential.h"
#include "RooAbsPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
#include "TH1.h"
#include "TH2.h"
#include "RooPlot.h"
#include "RooHist.h"

#include <fstream>
#include <string>
#include <sstream>


using namespace RooFit ;


void roohistpdf()
{
   // Setting :: 
   // 1. ROOT Files
   std::string signal_pdf_rootfile;
   std::string jpsi2incl_rootfile;
   std::string jpsi2invi_rootfile;
   
//	TCanvas* c = new TCanvas("","",900,300);
//	c->Divide(3);
    

   signal_pdf_rootfile =   "../run/jpsi2lplm/hist/jpsi2lplm_data_psip_data12_event_merged_1.root" ;
   jpsi2incl_rootfile =    "../run/jpsi2incl/hist/jpsi2incl_data_psip_data12_event_merged_1.root" ;
   jpsi2invi_rootfile =    "../run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_1.root" ;
  
//   signal_pdf_rootfile =   "../RooFit/rootfile/jpsi2lplm_data_psip_data12_event_merged_1.root" ;
//   jpsi2incl_rootfile =    "../RooFit/rootfile/jpsi2incl_data_psip_data12_merged_1.root" ;
//   jpsi2invi_rootfile =    "../RooFit/rootfile/jpsi2invi_data_psip_data12_merged_1.root" ;

   // 2. Select Fiiting Set
   int hist_id;  // hist_id = 1 (J/psi->inclusive), 2 (J/psi->invisible)
   hist_id = 2;

   int Fitting_Method; // Fitting_Method = 1 (Unbinned), or 2 (Binned) . %% For Jpsi->inclusive, only "Binned" can be used because of huge data size. 
   Fitting_Method=1;
   
   // 3. Output files for the fitting result
   std::string table, figname;
   if( hist_id == 1 ){
      if( Fitting_Method == 1 ){  
         table = "fitres_incl_unbinned.txt" ; 
         figname = "Jpsi2incl_fit_unbinned.eps" ;
      }
      else{ 
         table = "fitres_incl_binned.txt" ; 
         figname = "Jpsi2incl_fit_binned.eps" ;
      }
   }
   if( hist_id == 2 ){
      if( Fitting_Method == 1 ){  
         table = "fitres_invisible_unbinned.txt" ; 
         figname = "Jpsi2invible_fit_unbinned.eps" ;
      }
      else{ 
         table = "fitres_invisible_binned.txt" ; 
         figname = "Jpsi2invisible_fit_binned.eps" ;
      }
   }
      

  // Extract PDF function
  if(hist_id==1 || hist_id==2){
    // Extract PDF function from the recoil(dipion) mass distribution, Psip->pi+pi-J/psi, J/psi->e+e-
     TFile *f1 = new TFile(signal_pdf_rootfile.c_str());

    std::stringstream hist_title;
    hist_title << "h_mrecpipi_el_fit" ;
    
    TH1F* histll = dynamic_cast<TH1F*>(gDirectory->Get(hist_title.str().c_str()));
    
    RooRealVar x("vtx_mrecpipi","M(recoil(#pi^{+}#pi^{-}))",3.03,3.17) ;
    //RooRealVar x("vtx_mrecpipi","M(recoil(#pi^{+}#pi^{-}))",3.02,3.18) ;
    //RooRealVar x("vtx_mrecpipi","M(recoil(#pi^{+}#pi^{-}))",3.04,3.16) ;
    
    RooDataHist *data1 = new RooDataHist("data","data", x, histll); 
    
    // Smoothing 
    int g_conv_flag = 0;   // g_conv_flag==1 --> Gaussian convolution to the signal PDF
    if( g_conv_flag == 0 )
    {
       RooHistPdf signalpdf("SignalPDF", "Signal PDF", x, *data1, 4);
    }
    // For gaussian convolution
    if( g_conv_flag == 1 )
    {
       // Smoothing 
       RooHistPdf signalpdf1("SignalPDF", "Signal PDF", x, *data1, 4);

       RooRealVar mean("mean","mean of gaussian",0, -0.5, 0.5) ; 
       RooRealVar sigma("sigma","width of gaussian",0.01, 0.0001, 0.5) ; 
       RooGaussian gauss("gauss","gaussian PDF",x,mean,sigma) ;  

       //RooRealVar gmfrac("gmfrac", "fraction of gaussian", 0.5, 0.00001, 1.0);
       //RooAddModel gauss1("gauss1","gaus test", RooArgList(gauss, gauss2), gmfrac);
       x.setBins(10000, "fft");
    
       RooFFTConvPdf signalpdf("GConvSignal", "Gaussian covoluted signal PDF", x, signalpdf1, gauss);
    }

    // 2nd order polynomial function 
    RooRealVar c0("c0","coefficient #0", 0.0, -10.0, 10.0); 
    RooRealVar c1("c1","coefficient #1", 0.0, -10.0, 10.0); 
    RooChebychev bkg("bkg","background p.d.f.", x, RooArgList(c0,c1)); 
    
    // 3rd order polynomial function
   // RooRealVar c2("c2","coefficient #2",-0.1,-1.,1.) ; 
    //RooChebychev bkg("bkg","background p.d.f.",x,RooArgList(c0,c1,c2)) ; 
    
    if(hist_id==1){  // For Jpsi2Incl
      RooRealVar nsig("nsig","signal fraction",1000000, 0.0, 1000000000.0); 
      RooRealVar nbkg("nbkg","background fraction",100000, 0.0, 200000000.0); 
    }
    
    if(hist_id==2){ // For Jpsi2Invi
      RooRealVar nsig("nsig","signal fraction",1000000, 0.0, 1000000000.0); 
      RooRealVar nbkg("nbkg","background fraction",100000, 0.0, 20000000.0); 
    }
      
    RooAddPdf model("model", "model", RooArgList(signalpdf,bkg), RooArgList(nsig, nbkg));
  
    
    // Load data sample
    TFile *f2;
    if(hist_id==1){ // For Jpsi2Incl
       f2 = new TFile(jpsi2incl_rootfile.c_str());

    }
    if(hist_id==2){ // For Jpsi2Invi
       f2 = new TFile(jpsi2invi_rootfile.c_str());
    }
    
    RooPlot* xframe;
    RooFitResult* result;
    gStyle->SetCanvasColor(0);
    if(Fitting_Method==1)
    {
       TTree* tree = (TTree*) gDirectory->Get("signal");

       RooRealVar xtree("vtx_mrecpipi","M(recoil(#pi^{+}#pi^{-}))",3.03,3.17) ;
       //RooRealVar xtree("vtx_mrecpipi","M(recoil(#pi^{+}#pi^{-}))",3.02,3.18) ;
       //RooRealVar xtree("vtx_mrecpipi","M(recoil(#pi^{+}#pi^{-}))",3.04,3.16) ;
       RooDataSet data_tree("data", "data J/psi->invisible", tree, xtree);

       //model.fitTo(data_tree);
       result = model.fitTo(data_tree, Save(kTRUE));

       //RooPlot* xframe = xtree.frame();
       xframe = xtree.frame();
       data_tree.plotOn(xframe, Binning(140)); 
       //data_tree.plotOn(xframe, Binning(160)); 
       //data_tree.plotOn(xframe, Binning(120)); 
       model.plotOn(xframe); 
       //model.plotOn(xframe, Components(sig), LineStyle(kDotted), LineColor(kRed)); 
       model.plotOn(xframe, Components(bkg), LineStyle(kDashed), LineColor(kGreen)); 
      //  c->cd(1);
      //  gPad->SetLogy();
	     xframe->Draw(); 
       xframe->GetXaxis()->CenterTitle();
       xframe->GetYaxis()->CenterTitle();
       xframe->GetYaxis()->SetTitle("Events / ( 0.01 GeV/c^{2} )");
       xframe->GetXaxis()->SetTitle("M(recoil(#pi^{+}#pi^{-})) (GeV/c^{2})");

       xframe->GetXaxis()->SetNdivisions(505);
       xframe->GetYaxis()->SetNdivisions(505);

       xframe->GetXaxis()->SetTitleFont(132);
       xframe->GetYaxis()->SetTitleFont(132);
       xframe->GetXaxis()->SetLabelFont(132);
       xframe->GetYaxis()->SetLabelFont(132);
       xframe->GetXaxis()->SetTitleOffset(1.2);
       //htmp_mc->GetYaxis()->SetTitleOffset(1.6);
       xframe->GetYaxis()->SetTitleOffset(1.1);

       xframe->GetXaxis()->SetTitleSize(0.065);
       xframe->GetYaxis()->SetTitleSize(0.065);
       xframe->GetXaxis()->SetLabelOffset(0.02);
       xframe->GetYaxis()->SetLabelOffset(0.02);
  
       xframe->GetXaxis()->SetLabelSize(0.05);
       xframe->GetYaxis()->SetLabelSize(0.05);

       TGaxis::SetMaxDigits(3);
       gPad->SetTicks(1,1);
  
	 //  gPad->SetCanvasColor(0);
       gPad->SetBottomMargin(0.17);
       gPad->SetLeftMargin(0.16);

       xframe->SetName("");
       xframe->SetTitle("");
       xframe->SetName("");
       xframe->SetTitle("");
    }

    if(Fitting_Method==2)
    {
       std::stringstream hist_title_2;
       //hist_title_2  << "h_mrecpipi" ;
       hist_title_2  << "h_mrecpipi_fit" ;
       TH1F* histo = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_2.str().c_str()));

       histo->Rebin(7);    //1MeV
       //histo->Rebin(2);  //0.2MeV

       RooDataHist *data = new RooDataHist("data2","data2", x, histo); 

       //model.fitTo(*data);
       result = model.fitTo(*data, Save(kTRUE));

       //RooPlot* xframe = x.frame(); 
       xframe = x.frame(); 
       data->plotOn(xframe); 
       model.plotOn(xframe);
 
       //model.plotOn(xframe, Components(signalpdf), LineStyle(kDotted), LineColor(kRed)); 
       model.plotOn(xframe, Components(bkg), LineStyle(kDashed), LineColor(kGreen)); 
  //     c->cd(1);
  //     gPad->SetLogy();
	   xframe->Draw(); 
       xframe->GetXaxis()->CenterTitle();
       xframe->GetYaxis()->CenterTitle();
       
       xframe->GetYaxis()->SetTitle("Events / ( 0.01 GeV/c^{2} )");
       //xframe->GetYaxis()->SetTitle("Events / ( 0.0002 GeV/c^{2} )");
       xframe->GetXaxis()->SetTitle("M(recoil(#pi^{+}#pi^{-})) (GeV/c^{2})");

       xframe->GetXaxis()->SetNdivisions(505);
       xframe->GetYaxis()->SetNdivisions(505);

       xframe->GetXaxis()->SetTitleFont(132);
       xframe->GetYaxis()->SetTitleFont(132);
       xframe->GetXaxis()->SetLabelFont(132);
       xframe->GetYaxis()->SetLabelFont(132);
       xframe->GetXaxis()->SetTitleOffset(1.2);
       //htmp_mc->GetYaxis()->SetTitleOffset(1.6);
       xframe->GetYaxis()->SetTitleOffset(1.1);

       xframe->GetXaxis()->SetTitleSize(0.065);
       xframe->GetYaxis()->SetTitleSize(0.065);
       xframe->GetXaxis()->SetLabelOffset(0.02);
       xframe->GetYaxis()->SetLabelOffset(0.02);
  
       xframe->GetXaxis()->SetLabelSize(0.05);
       xframe->GetYaxis()->SetLabelSize(0.05);

       TGaxis::SetMaxDigits(3);
       gPad->SetTicks(1,1);
  
       gPad->SetBottomMargin(0.17);
       gPad->SetLeftMargin(0.16);

       xframe->SetName("");
       xframe->SetTitle("");
       xframe->SetName("");
       xframe->SetTitle("");
    }

    // Save to file (table)
    std::ofstream ofs;
    ofs.open(table.c_str());
    ofs << std::endl; 
    result->printArgs(ofs); 
    result->printMultiline(ofs, 1, kTRUE, "");
    result->printValue(ofs);
    ofs << std::endl; 
    ofs << std::endl;       
    ofs.close();

    std::cout<<"chi2/"<<result->floatParsFinal().getSize()<<" ="<<xframe->chiSquare("model_Norm[vtx_mrecpipi]", "h_data2" ,result->floatParsFinal().getSize())<<std::endl;

	// RooHist* hresid = xframe->residHist();
	// RooHist* hpull = xframe->pullHist();
	// RooPlot* frame2 = x.frame(Title("Residual Distribution"));
	// frame2->addPlotable(hresid, "P");
	// c->cd(2); frame2->Draw();
  //   gPad->SetLogy();
	// RooPlot* frame3 = x.frame(Title("Pull Distribution"));
	// frame3->addPlotable(hpull,"P");
	// frame3->SetMarkerSize(0.1);
	// c->cd(3); frame3->Draw();
    gPad->SetLogy();

    if(hist_id==1){ // For Jpsi2Incl
      xframe->SetMaximum(40000000);
      xframe->SetMinimum(100000);
    }
    
    if(hist_id==2){ //For Jpsi2Invi
      xframe->SetMaximum(4000000);
      xframe->SetMinimum(10);
    }
    
    // Print to eps file
    // c->Print(figname.c_str());
    gPad->Print(figname.c_str());
  }


}
