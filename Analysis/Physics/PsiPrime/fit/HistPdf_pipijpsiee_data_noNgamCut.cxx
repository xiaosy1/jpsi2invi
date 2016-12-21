{
  gROOT->Reset();
  gSystem->Load("libRooFit");
  using namespace RooFit;

  //range of fit
  Double_t left_value = 3.03;
  Double_t right_value = 3.17;
  Int_t nbins = 50;
  Int_t nRebin = 2;

  //input data
	TFile *f1 = new TFile("ee_data09_all.root");
  
  //TH1D *h1_mrecpipi = new TH1D("h1_mrecpipi","h1_mrecpipi",1000,3.03,3.17);
  TH1D *h1_mrecpipi = new TH1D("h1_mrecpipi","h1_mrecpipi",280,3.03,3.17);
  TTree* t1 = (TTree*)f1->Get("signal");

  //TH1D *h1_mrecpipi = new TH1D("h1_mrecpipi","h1_mrecpipi",1000,3.0,3.2);
  
  t1->Project("h1_mrecpipi","vtx_mrecpipi");

  //h1_mrecpipi->Smooth();
  //TH1D *h1_mrecpipi = (TH1D*)f1->Get("h_mrecpipi_mu");
  //h1_mrecpipi->Rebin(nRebin);
  RooRealVar invm("vtx_mrecpipi", "M(recoil(#pi#pi))", left_value, right_value, "GeV/c^{2}");
  RooPlot *frame = invm.frame(Name("invmframe"),Bins(nbins));
	
  RooDataHist *data = new RooDataHist("data", "data mass", invm, h1_mrecpipi);

	RooHistPdf pipijpsiee_dataPdf("pipijpsiee_dataPdf","pipijpsiee_dataPdf",invm,*data,5);
	//RooHistPdf pipijpsiee_dataPdf("pipijpsiee_dataPdf","pipijpsiee_dataPdf",invm,*data);


  RooWorkspace *w = new RooWorkspace("w_pipijpsiee_dataPdf", "workspace");
  w->import(pipijpsiee_dataPdf);
  w->writeToFile("pipijpsiee_dataPdf_noNgamCut.root");

  //TFile *data_pdf = new TFile("pipijpsiee_dataPdf.root","recreate");
  //pipijpsiee_dataPdf.Write();
  //data_pdf->Close();


   
  pipijpsiee_dataPdf.plotOn(frame,LineStyle(7));
  data->plotOn(frame); 
  TCanvas* c1 = new TCanvas;
  c1->SetLogy();
  frame->Draw();
  
  //c1->SaveAs("HistPdf_pipijpsiee_data.eps");

}
