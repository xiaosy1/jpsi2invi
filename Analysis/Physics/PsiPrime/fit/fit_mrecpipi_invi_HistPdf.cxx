{
  gROOT->Reset();
  gROOT->ForceStyle(kTRUE);
  gSystem->Load("libRooFit") ;
  using namespace RooFit;
  //range of fit
  Double_t left_value = 3.03;
  Double_t right_value = 3.17;
  Int_t nbins = 50;
 
  //Observable
  RooRealVar invm( "vtx_mrecpipi", "M(recoil(#pi^{+}#pi^{-}))", left_value, right_value, "GeV/c^{2}" );

 
  //TFile *f1 = new TFile("/besfs/users/zhangc/664p01/PipiInclu/scripts/fit_file/pipijpsimumu_dataPdf.root");
  TFile *f1 = new TFile("pipijpsiee_dataPdf_noNgamCut.root");
  //TFile *f1 = new TFile("$HOME/test/pipijpsiee_dataPdf_noNgamCut.root");
  
  //RooWorkspace *w = (RooWorkspace*)f1->Get("w_pipijpsimumu_dataPdf");
  //RooAbsPdf *sig = w->pdf("pipijpsimumu_dataPdf");
  RooWorkspace *w = (RooWorkspace*)f1->Get("w_pipijpsiee_dataPdf");
  RooAbsPdf *sig = w->pdf("pipijpsiee_dataPdf");
  sig->SetName("sig");

  
  RooRealVar a( "a", "a", 0.0, -10.0, 10.0 );
  RooRealVar b( "b", "b", 0.0, -10.0, 10.0 );
  RooChebychev bg( "bg", "bg", invm, RooArgList( a,b ) );
  //RooChebychev bg( "bg", "bg", invm, RooArgList( a ) );

  RooRealVar nsig("nsig","signal number",800000,0,900000) ;
  RooRealVar nbg("nbg","bg number",100000,0,900000) ;

  RooAddPdf model( "model", "model", RooArgList( *sig, bg ), RooArgList( nsig, nbg ) );


  TFile* f = new TFile("../../data09/invisible_data09_all.root");
  TTree* signal = (TTree*)f->Get( "signal" );
  
  RooDataSet data( "data", "dataset with invm", signal, invm );

  //model.fitTo( data,Extended(),Minos(kTRUE));
  //model.fitTo( data,Extended(),Minos(kFALSE));
  //model.fitTo( data,Extended());
  // ------ fitting
  RooFitResult *m_fitres = model.fitTo(data, Save(kTRUE), Extended(kTRUE));

  m_fitres->Print("v");
  cout << "edm: " << m_fitres->edm() <<  "   minNll: " << m_fitres->minNll() << "   " << endl;

  RooArgSet *paramList = model.getParameters(data);
  paramList->Print("v");

  // ----- draw


  RooPlot *xframe = invm.frame( );
  data.plotOn( xframe, Binning(140) );
  //data.plotOn( xframe );
  model.plotOn( xframe );
  model.plotOn( xframe, Components(bg), LineStyle(kDashed), LineColor(kGreen) );
  model.plotOn( xframe, Components(*sig), LineStyle(7), LineColor(kBlue) );
  //bxg.plotOn( xframe );

  //model.paramOn(xframe,Parameters(RooArgSet(meanb,widthb)),Layout(0.15,0.5,0.85)) ;
  //model.paramOn(xframe,Parameters(RooArgSet(meanb,widthb,nsig,nbg)),Layout(0.6,0.95,0.85));
  //model.paramOn(xframe,Layout(0.1,0.4,0.85));
  //model.paramOn(xframe,Layout(0.6,0.95,0.95));

  //goodness of fit
  cout<<"chi2/"<<m_fitres->floatParsFinal().getSize()<<" ="<<xframe->chiSquare("model_Norm[vtx_mrecpipi]", "h_data" , m_fitres->floatParsFinal().getSize())<<endl;
  
  TCanvas* c1 = new TCanvas;
  TGaxis::SetMaxDigits(3);

  xframe->GetXaxis()->CenterTitle();
  xframe->GetYaxis()->CenterTitle();
  xframe->GetXaxis()->SetNdivisions(505,kTRUE);
  xframe->GetYaxis()->SetRangeUser(55,190000);

  c1->SetLogy();

  xframe->Draw();
  c1->SaveAs( "fit_mrecpipi_invi_HistPdf_log.eps" );
}
