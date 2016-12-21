#include "TMath.h"
#include "TF1.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1.h"
#include "TArrow.h"
#include "TLine.h"

void draw_new_mumu()
{
  double scale_con = 34.5;
  double scale_psip = 1.0;

  TGaxis::SetMaxDigits(3);

  TLegend* myLegd = new TLegend(0.2, 0.71, 0.50, 0.88);
  myLegd->SetTextSize(0.05);
  myLegd->SetFillColor(0);
  myLegd->SetFillStyle(0);
  myLegd->SetLineColor(0);
  myLegd->SetShadowColor(0);
  myLegd->SetTextFont(132);

  TFile *f_sig = new TFile("../signal_new/mumu_signal_all.root");
  TFile *f_dat = new TFile("../09data/mumu_data09_all.root");
  TFile *f_con = new TFile("../con3650/mumu_con3650_all.root");
  TFile *f_inc = new TFile("../09mc_new/mumu_09mc_all.root");
  
  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_cospipi                                      //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_cospipi_sig = (TH1F*)f_sig->Get("h_cospipi");
  TH1F *h_cospipi_dat = (TH1F*)f_dat->Get("h_cospipi");
  TH1F *h_cospipi_con = (TH1F*)f_con->Get("h_cospipi");
  TH1F *h_cospipi_inc = (TH1F*)f_inc->Get("h_cospipi");
  
  h_cospipi_con->Scale(scale_con);
  h_cospipi_inc->Scale(scale_psip);
  h_cospipi_sig->Scale(0.5*h_cospipi_dat->GetMaximum()/h_cospipi_sig->GetMaximum());

  h_cospipi_dat->SetTitle("");
  h_cospipi_dat->SetStats(0);
  h_cospipi_dat->Sumw2();
  h_cospipi_dat->SetMarkerStyle(20);
  h_cospipi_dat->SetMarkerSize(0.8);
  h_cospipi_dat->SetLineWidth(2);
  h_cospipi_inc->SetLineColor(29);
  h_cospipi_inc->SetFillColor(29);
  h_cospipi_inc->SetMarkerColor(29);
  h_cospipi_con->SetLineColor(kOrange);
  h_cospipi_con->SetFillColor(kOrange);
  h_cospipi_con->SetMarkerColor(kOrange);
  h_cospipi_sig->SetLineColor(2);
  h_cospipi_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_cospipi_dat->GetYaxis()->SetRangeUser(0,40000);  
  h_cospipi_dat->SetXTitle("cos#theta_{#pi^{+}#pi^{-}}");
  h_cospipi_dat->SetYTitle("Events/0.02");
  h_cospipi_dat->GetXaxis()->CenterTitle();
  h_cospipi_dat->GetYaxis()->CenterTitle();
  h_cospipi_dat->GetXaxis()->SetTitleSize(0.08);
  h_cospipi_dat->GetYaxis()->SetTitleSize(0.08);
  
  /////////////////////////////////////////////////////////////////////

  THStack *h_cospipi = new THStack("h_cospipi","");
  h_cospipi->Add(h_cospipi_con);
  h_cospipi->Add(h_cospipi_inc);
  
  TCanvas *c1_h_cospipi = new TCanvas();
  c1_h_cospipi->SetFillColor(0);
  c1_h_cospipi->SetFrameFillColor(0);
  h_cospipi_dat->Draw();
  h_cospipi->Draw("same");
  h_cospipi_sig->Draw("same");
  h_cospipi_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline2_h_cospipi = new TLine(0.95,40000,0.95,0); 
  cutline2_h_cospipi->SetLineColor(kBlue);
  cutline2_h_cospipi->SetLineWidth(3);
  cutline2_h_cospipi->SetLineStyle(kDashed);
  cutline2_h_cospipi->Draw();	

  TArrow *arrow2_h_cospipi = new TArrow(0.95,20000,0.87,20000,0.02,"|>");
  arrow2_h_cospipi->SetLineWidth(3);
  arrow2_h_cospipi->SetFillColor(kBlue);
  arrow2_h_cospipi->SetLineColor(kBlue);
  arrow2_h_cospipi->Draw();

  /////////////////////////////////////////////////////////////////////



  myLegd->Clear();
  myLegd->AddEntry(h_cospipi_dat,"Data","lp");
  myLegd->AddEntry(h_cospipi_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_cospipi_con,"Cont.");
  myLegd->AddEntry(h_cospipi_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_cospipi->SaveAs("pic/h_cospipi.pdf");
  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_cos2pisys                                    //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_cos2pisys_sig = (TH1F*)f_sig->Get("h_cos2pisys");
  TH1F *h_cos2pisys_dat = (TH1F*)f_dat->Get("h_cos2pisys");
  TH1F *h_cos2pisys_con = (TH1F*)f_con->Get("h_cos2pisys");
  TH1F *h_cos2pisys_inc = (TH1F*)f_inc->Get("h_cos2pisys");
  
  h_cos2pisys_con->Scale(scale_con);
  h_cos2pisys_inc->Scale(scale_psip);
  h_cos2pisys_sig->Scale(0.5*h_cos2pisys_dat->GetMaximum()/h_cos2pisys_sig->GetMaximum());

  h_cos2pisys_dat->SetTitle("");
  h_cos2pisys_dat->SetStats(0);
  h_cos2pisys_dat->Sumw2();
  h_cos2pisys_dat->SetMarkerStyle(20);
  h_cos2pisys_dat->SetMarkerSize(0.8);
  h_cos2pisys_dat->SetLineWidth(2);
  h_cos2pisys_inc->SetLineColor(29);
  h_cos2pisys_inc->SetFillColor(29);
  h_cos2pisys_inc->SetMarkerColor(29);
  h_cos2pisys_con->SetLineColor(kOrange);
  h_cos2pisys_con->SetFillColor(kOrange);
  h_cos2pisys_con->SetMarkerColor(kOrange);
  h_cos2pisys_sig->SetLineColor(2);
  h_cos2pisys_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_cos2pisys_dat->GetYaxis()->SetRangeUser(0,13000);  
  h_cos2pisys_dat->SetXTitle("cos#theta_{#pi#pi sys.}");
  h_cos2pisys_dat->SetYTitle("Events/0.02");
  h_cos2pisys_dat->GetXaxis()->CenterTitle();
  h_cos2pisys_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_cos2pisys = new THStack("h_cos2pisys","");
  h_cos2pisys->Add(h_cos2pisys_con);
  h_cos2pisys->Add(h_cos2pisys_inc);
  
  TCanvas *c1_h_cos2pisys = new TCanvas();	
  c1_h_cos2pisys->SetFillColor(0);
  c1_h_cos2pisys->SetFrameFillColor(0);
  h_cos2pisys_dat->Draw();
  h_cos2pisys->Draw("same");
  h_cos2pisys_sig->Draw("same");
  h_cos2pisys_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline1_h_cos2pisys = new TLine(-0.90,13000,-0.90,0); 
  cutline1_h_cos2pisys->SetLineColor(kBlue);
  cutline1_h_cos2pisys->SetLineWidth(3);
  cutline1_h_cos2pisys->SetLineStyle(kDashed);
  cutline1_h_cos2pisys->Draw();	

  TArrow *arrow1_h_cos2pisys = new TArrow(-0.90,6500,-0.82,6500,0.02,"|>");
  arrow1_h_cos2pisys->SetLineWidth(3);
  arrow1_h_cos2pisys->SetFillColor(kBlue);
  arrow1_h_cos2pisys->SetLineColor(kBlue);
  arrow1_h_cos2pisys->Draw();  
  
  TLine* cutline2_h_cos2pisys = new TLine(0.90,13000,0.90,0); 
  cutline2_h_cos2pisys->SetLineColor(kBlue);
  cutline2_h_cos2pisys->SetLineWidth(3);
  cutline2_h_cos2pisys->SetLineStyle(kDashed);
  cutline2_h_cos2pisys->Draw();	

  TArrow *arrow2_h_cos2pisys = new TArrow(0.90,6500,0.82,6500,0.02,"|>");
  arrow2_h_cos2pisys->SetLineWidth(3);
  arrow2_h_cos2pisys->SetFillColor(kBlue);
  arrow2_h_cos2pisys->SetLineColor(kBlue);
  arrow2_h_cos2pisys->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_cos2pisys_dat,"Data","lp");
  myLegd->AddEntry(h_cos2pisys_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_cos2pisys_con,"Cont.");
  myLegd->AddEntry(h_cos2pisys_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_cos2pisys->SaveAs("pic/h_cos2pisys.pdf");



/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_pim_costhe                                    //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_pim_costhe_sig = (TH1F*)f_sig->Get("h_pim_costhe");
  TH1F *h_pim_costhe_dat = (TH1F*)f_dat->Get("h_pim_costhe");
  TH1F *h_pim_costhe_con = (TH1F*)f_con->Get("h_pim_costhe");
  TH1F *h_pim_costhe_inc = (TH1F*)f_inc->Get("h_pim_costhe");
  
  h_pim_costhe_con->Scale(scale_con);
  h_pim_costhe_inc->Scale(scale_psip);
  h_pim_costhe_sig->Scale(0.5*h_pim_costhe_dat->GetMaximum()/h_pim_costhe_sig->GetMaximum());

  h_pim_costhe_dat->SetTitle("");
  h_pim_costhe_dat->SetStats(0);
  h_pim_costhe_dat->Sumw2();
  h_pim_costhe_dat->SetMarkerStyle(20);
  h_pim_costhe_dat->SetMarkerSize(0.8);
  h_pim_costhe_dat->SetLineWidth(2);
  h_pim_costhe_inc->SetLineColor(29);
  h_pim_costhe_inc->SetFillColor(29);
  h_pim_costhe_inc->SetMarkerColor(29);
  h_pim_costhe_con->SetLineColor(kOrange);
  h_pim_costhe_con->SetFillColor(kOrange);
  h_pim_costhe_con->SetMarkerColor(kOrange);
  h_pim_costhe_sig->SetLineColor(2);
  h_pim_costhe_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_pim_costhe_dat->GetYaxis()->SetRangeUser(0,15000);  
  h_pim_costhe_dat->SetXTitle("cos#theta_{#pi^{-}}");
  h_pim_costhe_dat->SetYTitle("Events/0.02");
  h_pim_costhe_dat->GetXaxis()->CenterTitle();
  h_pim_costhe_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_pim_costhe = new THStack("h_pim_costhe","");
  h_pim_costhe->Add(h_pim_costhe_con);
  h_pim_costhe->Add(h_pim_costhe_inc);
  
  TCanvas *c1_h_pim_costhe = new TCanvas();	
  c1_h_pim_costhe->SetFillColor(0);
  c1_h_pim_costhe->SetFrameFillColor(0);
  h_pim_costhe_dat->Draw();
  h_pim_costhe->Draw("same");
  h_pim_costhe_sig->Draw("same");
  h_pim_costhe_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline1_h_pim_costhe = new TLine(-0.80,15000,-0.80,0); 
  cutline1_h_pim_costhe->SetLineColor(kBlue);
  cutline1_h_pim_costhe->SetLineWidth(3);
  cutline1_h_pim_costhe->SetLineStyle(kDashed);
  cutline1_h_pim_costhe->Draw();	

  TArrow *arrow1_h_pim_costhe = new TArrow(-0.80,7500,-0.72,7500,0.02,"|>");
  arrow1_h_pim_costhe->SetLineWidth(3);
  arrow1_h_pim_costhe->SetFillColor(kBlue);
  arrow1_h_pim_costhe->SetLineColor(kBlue);
  arrow1_h_pim_costhe->Draw();  
  
  TLine* cutline2_h_pim_costhe = new TLine(0.80,15000,0.80,0); 
  cutline2_h_pim_costhe->SetLineColor(kBlue);
  cutline2_h_pim_costhe->SetLineWidth(3);
  cutline2_h_pim_costhe->SetLineStyle(kDashed);
  cutline2_h_pim_costhe->Draw();	

  TArrow *arrow2_h_pim_costhe = new TArrow(0.80,7500,0.72,7500,0.02,"|>");
  arrow2_h_pim_costhe->SetLineWidth(3);
  arrow2_h_pim_costhe->SetFillColor(kBlue);
  arrow2_h_pim_costhe->SetLineColor(kBlue);
  arrow2_h_pim_costhe->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_pim_costhe_dat,"Data","lp");
  myLegd->AddEntry(h_pim_costhe_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_pim_costhe_con,"Cont.");
  myLegd->AddEntry(h_pim_costhe_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_pim_costhe->SaveAs("pic/h_pim_costhe.pdf");

/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_pip_costhe                                    //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_pip_costhe_sig = (TH1F*)f_sig->Get("h_pip_costhe");
  TH1F *h_pip_costhe_dat = (TH1F*)f_dat->Get("h_pip_costhe");
  TH1F *h_pip_costhe_con = (TH1F*)f_con->Get("h_pip_costhe");
  TH1F *h_pip_costhe_inc = (TH1F*)f_inc->Get("h_pip_costhe");
  
  h_pip_costhe_con->Scale(scale_con);
  h_pip_costhe_inc->Scale(scale_psip);
  h_pip_costhe_sig->Scale(0.5*h_pip_costhe_dat->GetMaximum()/h_pip_costhe_sig->GetMaximum());

  h_pip_costhe_dat->SetTitle("");
  h_pip_costhe_dat->SetStats(0);
  h_pip_costhe_dat->Sumw2();
  h_pip_costhe_dat->SetMarkerStyle(20);
  h_pip_costhe_dat->SetMarkerSize(0.8);
  h_pip_costhe_dat->SetLineWidth(2);
  h_pip_costhe_inc->SetLineColor(29);
  h_pip_costhe_inc->SetFillColor(29);
  h_pip_costhe_inc->SetMarkerColor(29);
  h_pip_costhe_con->SetLineColor(kOrange);
  h_pip_costhe_con->SetFillColor(kOrange);
  h_pip_costhe_con->SetMarkerColor(kOrange);
  h_pip_costhe_sig->SetLineColor(2);
  h_pip_costhe_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_pip_costhe_dat->GetYaxis()->SetRangeUser(0,15000);  
  h_pip_costhe_dat->SetXTitle("cos#theta_{#pi^{+}}");
  h_pip_costhe_dat->SetYTitle("Events/0.02");
  h_pip_costhe_dat->GetXaxis()->CenterTitle();
  h_pip_costhe_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_pip_costhe = new THStack("h_pip_costhe","");
  h_pip_costhe->Add(h_pip_costhe_con);
  h_pip_costhe->Add(h_pip_costhe_inc);
  
  TCanvas *c1_h_pip_costhe = new TCanvas();	
  c1_h_pip_costhe->SetFillColor(0);
  c1_h_pip_costhe->SetFrameFillColor(0);  
  h_pip_costhe_dat->Draw();
  h_pip_costhe->Draw("same");
  h_pip_costhe_sig->Draw("same");
  h_pip_costhe_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline1_h_pip_costhe = new TLine(-0.80,15000,-0.80,0); 
  cutline1_h_pip_costhe->SetLineColor(kBlue);
  cutline1_h_pip_costhe->SetLineWidth(3);
  cutline1_h_pip_costhe->SetLineStyle(kDashed);
  cutline1_h_pip_costhe->Draw();	

  TArrow *arrow1_h_pip_costhe = new TArrow(-0.80,7500,-0.72,7500,0.02,"|>");
  arrow1_h_pip_costhe->SetLineWidth(3);
  arrow1_h_pip_costhe->SetFillColor(kBlue);
  arrow1_h_pip_costhe->SetLineColor(kBlue);
  arrow1_h_pip_costhe->Draw();  
  
  TLine* cutline2_h_pip_costhe = new TLine(0.80,15000,0.80,0); 
  cutline2_h_pip_costhe->SetLineColor(kBlue);
  cutline2_h_pip_costhe->SetLineWidth(3);
  cutline2_h_pip_costhe->SetLineStyle(kDashed);
  cutline2_h_pip_costhe->Draw();	

  TArrow *arrow2_h_pip_costhe = new TArrow(0.80,7500,0.72,7500,0.02,"|>");
  arrow2_h_pip_costhe->SetLineWidth(3);
  arrow2_h_pip_costhe->SetFillColor(kBlue);
  arrow2_h_pip_costhe->SetLineColor(kBlue);
  arrow2_h_pip_costhe->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_pip_costhe_dat,"Data","lp");
  myLegd->AddEntry(h_pip_costhe_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_pip_costhe_con,"Cont.");
  myLegd->AddEntry(h_pip_costhe_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_pip_costhe->SaveAs("pic/h_pip_costhe.pdf");

  

/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_mmumu                                    //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_mmumu_sig = (TH1F*)f_sig->Get("h_mmumu");
  TH1F *h_mmumu_dat = (TH1F*)f_dat->Get("h_mmumu");
  TH1F *h_mmumu_con = (TH1F*)f_con->Get("h_mmumu");
  TH1F *h_mmumu_inc = (TH1F*)f_inc->Get("h_mmumu");
  
  h_mmumu_con->Scale(scale_con);
  h_mmumu_inc->Scale(scale_psip);
  h_mmumu_sig->Scale(0.5*h_mmumu_dat->GetMaximum()/h_mmumu_sig->GetMaximum());

  h_mmumu_dat->SetTitle("");
  h_mmumu_dat->SetStats(0);
  h_mmumu_dat->Sumw2();
  h_mmumu_dat->SetMarkerStyle(20);
  h_mmumu_dat->SetMarkerSize(0.8);
  h_mmumu_dat->SetLineWidth(2);
  h_mmumu_inc->SetLineColor(29);
  h_mmumu_inc->SetFillColor(29);
  h_mmumu_inc->SetMarkerColor(29);
  h_mmumu_con->SetLineColor(kOrange);
  h_mmumu_con->SetFillColor(kOrange);
  h_mmumu_con->SetMarkerColor(kOrange);
  h_mmumu_sig->SetLineColor(2);
  h_mmumu_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_mmumu_dat->GetYaxis()->SetRangeUser(0,120000);  
  h_mmumu_dat->SetXTitle("M(#mu^{+}#mu^{-})(GeV/c^{2})");
  h_mmumu_dat->SetYTitle("Events/(0.006GeV/c^{2})");
  h_mmumu_dat->GetXaxis()->CenterTitle();
  h_mmumu_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_mmumu = new THStack("h_mmumu","");
  h_mmumu->Add(h_mmumu_con);
  h_mmumu->Add(h_mmumu_inc);
  
  TCanvas *c1_h_mmumu = new TCanvas();	
  c1_h_mmumu->SetFillColor(0);
  c1_h_mmumu->SetFrameFillColor(0);
  h_mmumu_dat->Draw();
  h_mmumu->Draw("same");
  h_mmumu_sig->Draw("same");
  h_mmumu_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline1_h_mmumu = new TLine(3.0,120000,3.0,0); 
  cutline1_h_mmumu->SetLineColor(kBlue);
  cutline1_h_mmumu->SetLineWidth(3);
  cutline1_h_mmumu->SetLineStyle(kDashed);
  cutline1_h_mmumu->Draw();	

  TArrow *arrow1_h_mmumu = new TArrow(3.0,60000,3.03,60000,0.02,"|>");
  arrow1_h_mmumu->SetLineWidth(3);
  arrow1_h_mmumu->SetFillColor(kBlue);
  arrow1_h_mmumu->SetLineColor(kBlue);
  arrow1_h_mmumu->Draw();  
  
  TLine* cutline2_h_mmumu = new TLine(3.2,120000,3.2,0); 
  cutline2_h_mmumu->SetLineColor(kBlue);
  cutline2_h_mmumu->SetLineWidth(3);
  cutline2_h_mmumu->SetLineStyle(kDashed);
  cutline2_h_mmumu->Draw();	

  TArrow *arrow2_h_mmumu = new TArrow(3.2,60000,3.17,60000,0.02,"|>");
  arrow2_h_mmumu->SetLineWidth(3);
  arrow2_h_mmumu->SetFillColor(kBlue);
  arrow2_h_mmumu->SetLineColor(kBlue);
  arrow2_h_mmumu->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_mmumu_dat,"Data","lp");
  myLegd->AddEntry(h_mmumu_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_mmumu_con,"Cont.");
  myLegd->AddEntry(h_mmumu_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_mmumu->SaveAs("pic/h_mmumu.pdf");




  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_vtx_mrecpipi                                 //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_mrecpipi_sig = (TH1F*)f_sig->Get("h_mrecpipi");
  TH1F *h_mrecpipi_dat = (TH1F*)f_dat->Get("h_mrecpipi");
  TH1F *h_mrecpipi_con = (TH1F*)f_con->Get("h_mrecpipi");
  TH1F *h_mrecpipi_inc = (TH1F*)f_inc->Get("h_mrecpipi");
  
  h_mrecpipi_con->Scale(scale_con);
  h_mrecpipi_inc->Scale(scale_psip);
  h_mrecpipi_sig->Scale(0.5*h_mrecpipi_dat->GetMaximum()/h_mrecpipi_sig->GetMaximum());

  h_mrecpipi_dat->SetTitle("");
  h_mrecpipi_dat->SetStats(0);
  h_mrecpipi_dat->Sumw2();
  h_mrecpipi_dat->SetMarkerStyle(20);
  h_mrecpipi_dat->SetMarkerSize(0.8);
  h_mrecpipi_dat->SetLineWidth(2);
  h_mrecpipi_inc->SetLineColor(29);
  h_mrecpipi_inc->SetFillColor(29);
  h_mrecpipi_inc->SetMarkerColor(29);
  h_mrecpipi_con->SetLineColor(kOrange);
  h_mrecpipi_con->SetFillColor(kOrange);
  h_mrecpipi_con->SetMarkerColor(kOrange);
  h_mrecpipi_sig->SetLineColor(2);
  h_mrecpipi_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_mrecpipi_dat->GetYaxis()->SetRangeUser(0,360000);  
  h_mrecpipi_dat->SetXTitle("M(recoil(#pi^{+}#pi^{-}))(GeV/c^{2})");
  h_mrecpipi_dat->SetYTitle("Events/(0.002GeV/c^{2})");
  h_mrecpipi_dat->GetXaxis()->CenterTitle();
  h_mrecpipi_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_mrecpipi = new THStack("h_mrecpipi","");
  h_mrecpipi->Add(h_mrecpipi_con);
  h_mrecpipi->Add(h_mrecpipi_inc);
  
  TCanvas *c1_h_mrecpipi = new TCanvas();	
  c1_h_mrecpipi->SetFillColor(0);
  c1_h_mrecpipi->SetFrameFillColor(0);
  h_mrecpipi_dat->Draw();
  h_mrecpipi->Draw("same");
  h_mrecpipi_sig->Draw("same");
  h_mrecpipi_dat->Draw("same");
  
  
  myLegd->Clear();
  myLegd->AddEntry(h_mrecpipi_dat,"Data","lp");
  myLegd->AddEntry(h_mrecpipi_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_mrecpipi_con,"Cont.");
  myLegd->AddEntry(h_mrecpipi_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_mrecpipi->SaveAs("pic/h_mrecpipi.pdf");

  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_vtx_mpipi                                 //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  Double_t vtx_mpipi;

  TTree *tree_vtx_mpipi_inc =(TTree *)f_inc->Get("signal");
  TTree *tree_vtx_mpipi_sig =(TTree *)f_sig->Get("signal");
  TTree *tree_vtx_mpipi_dat =(TTree *)f_dat->Get("signal");
  TTree *tree_vtx_mpipi_con =(TTree *)f_con->Get("signal");

  TH1F *h_vtx_mpipi_sig = new TH1F("h_vtx_mpipi_sig","",100,0.2,0.7);
  TH1F *h_vtx_mpipi_dat = new TH1F("h_vtx_mpipi_dat","",100,0.2,0.7);
  TH1F *h_vtx_mpipi_con = new TH1F("h_vtx_mpipi_con","",100,0.2,0.7);
  TH1F *h_vtx_mpipi_inc = new TH1F("h_vtx_mpipi_inc","",100,0.2,0.7);

  tree_vtx_mpipi_inc->SetBranchAddress("vtx_mpipi",&vtx_mpipi);
  for(Int_t i =0;i<tree_vtx_mpipi_inc->GetEntries();i++)
  {
    tree_vtx_mpipi_inc->GetEntry(i);
    h_vtx_mpipi_inc->Fill(vtx_mpipi);
  }
  
  tree_vtx_mpipi_sig->SetBranchAddress("vtx_mpipi",&vtx_mpipi);
  for(Int_t i =0;i<tree_vtx_mpipi_sig->GetEntries();i++)
  {
    tree_vtx_mpipi_sig->GetEntry(i);
    h_vtx_mpipi_sig->Fill(vtx_mpipi);
  }
  
  tree_vtx_mpipi_dat->SetBranchAddress("vtx_mpipi",&vtx_mpipi);
  for(Int_t i =0;i<tree_vtx_mpipi_dat->GetEntries();i++)
  {
    tree_vtx_mpipi_dat->GetEntry(i);
    h_vtx_mpipi_dat->Fill(vtx_mpipi);
  }
  
  tree_vtx_mpipi_con->SetBranchAddress("vtx_mpipi",&vtx_mpipi);
  for(Int_t i =0;i<tree_vtx_mpipi_con->GetEntries();i++)
  {
    tree_vtx_mpipi_con->GetEntry(i);
    h_vtx_mpipi_con->Fill(vtx_mpipi);
  }

  h_vtx_mpipi_con->Scale(scale_con);
  h_vtx_mpipi_inc->Scale(scale_psip);
  h_vtx_mpipi_sig->Scale(0.5*h_vtx_mpipi_dat->GetMaximum()/h_vtx_mpipi_sig->GetMaximum());

  h_vtx_mpipi_dat->SetTitle("");
  h_vtx_mpipi_dat->SetStats(0);
  h_vtx_mpipi_dat->Sumw2();
  h_vtx_mpipi_dat->SetMarkerStyle(20);
  h_vtx_mpipi_dat->SetMarkerSize(0.8);
  h_vtx_mpipi_dat->SetLineWidth(2);
  h_vtx_mpipi_inc->SetLineColor(29);
  h_vtx_mpipi_inc->SetFillColor(29);
  h_vtx_mpipi_inc->SetMarkerColor(29);
  h_vtx_mpipi_con->SetLineColor(kOrange);
  h_vtx_mpipi_con->SetFillColor(kOrange);
  h_vtx_mpipi_con->SetMarkerColor(kOrange);
  h_vtx_mpipi_sig->SetLineColor(2);
  h_vtx_mpipi_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_vtx_mpipi_dat->GetYaxis()->SetRangeUser(0,35000);  
  h_vtx_mpipi_dat->SetXTitle("M(#pi^{+}#pi^{-})(GeV/c^{2})");
  h_vtx_mpipi_dat->SetYTitle("Events/(0.002GeV/c^{2})");
  h_vtx_mpipi_dat->GetXaxis()->CenterTitle();
  h_vtx_mpipi_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_vtx_mpipi = new THStack("h_vtx_mpipi","");
  h_vtx_mpipi->Add(h_vtx_mpipi_con);
  h_vtx_mpipi->Add(h_vtx_mpipi_inc);
  
  TCanvas *c1_h_vtx_mpipi = new TCanvas();	
  c1_h_vtx_mpipi->SetFillColor(0);
  c1_h_vtx_mpipi->SetFrameFillColor(0);
  h_vtx_mpipi_dat->Draw();
  h_vtx_mpipi->Draw("same");
  h_vtx_mpipi_sig->Draw("same");
  h_vtx_mpipi_dat->Draw("same");
    
  myLegd->Clear();
  myLegd->AddEntry(h_vtx_mpipi_dat,"Data","lp");
  myLegd->AddEntry(h_vtx_mpipi_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_vtx_mpipi_con,"Cont.");
  myLegd->AddEntry(h_vtx_mpipi_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_vtx_mpipi->SaveAs("pic/h_vtx_mpipi.pdf");



/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_vtx_pip_p                                 //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  Double_t vtx_pip_p;

  TTree *tree_vtx_pip_p_inc =(TTree *)f_inc->Get("signal");
  TTree *tree_vtx_pip_p_sig =(TTree *)f_sig->Get("signal");
  TTree *tree_vtx_pip_p_dat =(TTree *)f_dat->Get("signal");
  TTree *tree_vtx_pip_p_con =(TTree *)f_con->Get("signal");

  TH1F *h_vtx_pip_p_sig = new TH1F("h_vtx_pip_p_sig","",100,0,0.5);
  TH1F *h_vtx_pip_p_dat = new TH1F("h_vtx_pip_p_dat","",100,0,0.5);
  TH1F *h_vtx_pip_p_con = new TH1F("h_vtx_pip_p_con","",100,0,0.5);
  TH1F *h_vtx_pip_p_inc = new TH1F("h_vtx_pip_p_inc","",100,0,0.5);

  tree_vtx_pip_p_inc->SetBranchAddress("vtx_pip_p",&vtx_pip_p);
  for(Int_t i =0;i<tree_vtx_pip_p_inc->GetEntries();i++)
  {
    tree_vtx_pip_p_inc->GetEntry(i);
    h_vtx_pip_p_inc->Fill(vtx_pip_p);
  }
  
  tree_vtx_pip_p_sig->SetBranchAddress("vtx_pip_p",&vtx_pip_p);
  for(Int_t i =0;i<tree_vtx_pip_p_sig->GetEntries();i++)
  {
    tree_vtx_pip_p_sig->GetEntry(i);
    h_vtx_pip_p_sig->Fill(vtx_pip_p);
  }
  
  tree_vtx_pip_p_dat->SetBranchAddress("vtx_pip_p",&vtx_pip_p);
  for(Int_t i =0;i<tree_vtx_pip_p_dat->GetEntries();i++)
  {
    tree_vtx_pip_p_dat->GetEntry(i);
    h_vtx_pip_p_dat->Fill(vtx_pip_p);
  }
  
  tree_vtx_pip_p_con->SetBranchAddress("vtx_pip_p",&vtx_pip_p);
  for(Int_t i =0;i<tree_vtx_pip_p_con->GetEntries();i++)
  {
    tree_vtx_pip_p_con->GetEntry(i);
    h_vtx_pip_p_con->Fill(vtx_pip_p);
  }

  h_vtx_pip_p_con->Scale(scale_con);
  h_vtx_pip_p_inc->Scale(scale_psip);
  h_vtx_pip_p_sig->Scale(0.5*h_vtx_pip_p_dat->GetMaximum()/h_vtx_pip_p_sig->GetMaximum());

  h_vtx_pip_p_dat->SetTitle("");
  h_vtx_pip_p_dat->SetStats(0);
  h_vtx_pip_p_dat->Sumw2();
  h_vtx_pip_p_dat->SetMarkerStyle(20);
  h_vtx_pip_p_dat->SetMarkerSize(0.8);
  h_vtx_pip_p_dat->SetLineWidth(2);
  h_vtx_pip_p_inc->SetLineColor(29);
  h_vtx_pip_p_inc->SetFillColor(29);
  h_vtx_pip_p_inc->SetMarkerColor(29);
  h_vtx_pip_p_con->SetLineColor(kOrange);
  h_vtx_pip_p_con->SetFillColor(kOrange);
  h_vtx_pip_p_con->SetMarkerColor(kOrange);
  h_vtx_pip_p_sig->SetLineColor(2);
  h_vtx_pip_p_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_vtx_pip_p_dat->GetYaxis()->SetRangeUser(0,22000);  
  h_vtx_pip_p_dat->SetXTitle("P(#pi^{+})(GeV/c)");
  h_vtx_pip_p_dat->SetYTitle("Events/(0.005GeV/c)");
  h_vtx_pip_p_dat->GetXaxis()->CenterTitle();
  h_vtx_pip_p_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_vtx_pip_p = new THStack("h_vtx_pip_p","");
  h_vtx_pip_p->Add(h_vtx_pip_p_con);
  h_vtx_pip_p->Add(h_vtx_pip_p_inc);
  
  TCanvas *c1_h_vtx_pip_p = new TCanvas();	
  c1_h_vtx_pip_p->SetFillColor(0);
  c1_h_vtx_pip_p->SetFrameFillColor(0);
  h_vtx_pip_p_dat->Draw();
  h_vtx_pip_p->Draw("same");
  h_vtx_pip_p_sig->Draw("same");
  h_vtx_pip_p_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  
  TLine* cutline2_h_vtx_pip_p = new TLine(0.45,22000,0.45,0); 
  cutline2_h_vtx_pip_p->SetLineColor(kBlue);
  cutline2_h_vtx_pip_p->SetLineWidth(3);
  cutline2_h_vtx_pip_p->SetLineStyle(kDashed);
  cutline2_h_vtx_pip_p->Draw();	

  TArrow *arrow2_h_vtx_pip_p = new TArrow(0.45,11000,0.43,11000,0.02,"|>");
  arrow2_h_vtx_pip_p->SetLineWidth(3);
  arrow2_h_vtx_pip_p->SetFillColor(kBlue);
  arrow2_h_vtx_pip_p->SetLineColor(kBlue);
  arrow2_h_vtx_pip_p->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_vtx_pip_p_dat,"Data","lp");
  myLegd->AddEntry(h_vtx_pip_p_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_vtx_pip_p_con,"Cont.");
  myLegd->AddEntry(h_vtx_pip_p_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_vtx_pip_p->SaveAs("pic/h_vtx_pip_p.pdf");


/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_vtx_pim_p                                 //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  Double_t vtx_pim_p;

  TTree *tree_vtx_pim_p_inc =(TTree *)f_inc->Get("signal");
  TTree *tree_vtx_pim_p_sig =(TTree *)f_sig->Get("signal");
  TTree *tree_vtx_pim_p_dat =(TTree *)f_dat->Get("signal");
  TTree *tree_vtx_pim_p_con =(TTree *)f_con->Get("signal");

  TH1F *h_vtx_pim_p_sig = new TH1F("h_vtx_pim_p_sig","",100,0,0.5);
  TH1F *h_vtx_pim_p_dat = new TH1F("h_vtx_pim_p_dat","",100,0,0.5);
  TH1F *h_vtx_pim_p_con = new TH1F("h_vtx_pim_p_con","",100,0,0.5);
  TH1F *h_vtx_pim_p_inc = new TH1F("h_vtx_pim_p_inc","",100,0,0.5);

  tree_vtx_pim_p_inc->SetBranchAddress("vtx_pim_p",&vtx_pim_p);
  for(Int_t i =0;i<tree_vtx_pim_p_inc->GetEntries();i++)
  {
    tree_vtx_pim_p_inc->GetEntry(i);
    h_vtx_pim_p_inc->Fill(vtx_pim_p);
  }
  
  tree_vtx_pim_p_sig->SetBranchAddress("vtx_pim_p",&vtx_pim_p);
  for(Int_t i =0;i<tree_vtx_pim_p_sig->GetEntries();i++)
  {
    tree_vtx_pim_p_sig->GetEntry(i);
    h_vtx_pim_p_sig->Fill(vtx_pim_p);
  }
  
  tree_vtx_pim_p_dat->SetBranchAddress("vtx_pim_p",&vtx_pim_p);
  for(Int_t i =0;i<tree_vtx_pim_p_dat->GetEntries();i++)
  {
    tree_vtx_pim_p_dat->GetEntry(i);
    h_vtx_pim_p_dat->Fill(vtx_pim_p);
  }
  
  tree_vtx_pim_p_con->SetBranchAddress("vtx_pim_p",&vtx_pim_p);
  for(Int_t i =0;i<tree_vtx_pim_p_con->GetEntries();i++)
  {
    tree_vtx_pim_p_con->GetEntry(i);
    h_vtx_pim_p_con->Fill(vtx_pim_p);
  }

  h_vtx_pim_p_con->Scale(scale_con);
  h_vtx_pim_p_inc->Scale(scale_psip);
  h_vtx_pim_p_sig->Scale(0.5*h_vtx_pim_p_dat->GetMaximum()/h_vtx_pim_p_sig->GetMaximum());

  h_vtx_pim_p_dat->SetTitle("");
  h_vtx_pim_p_dat->SetStats(0);
  h_vtx_pim_p_dat->Sumw2();
  h_vtx_pim_p_dat->SetMarkerStyle(20);
  h_vtx_pim_p_dat->SetMarkerSize(0.8);
  h_vtx_pim_p_dat->SetLineWidth(2);
  h_vtx_pim_p_inc->SetLineColor(29);
  h_vtx_pim_p_inc->SetFillColor(29);
  h_vtx_pim_p_inc->SetMarkerColor(29);
  h_vtx_pim_p_con->SetLineColor(kOrange);
  h_vtx_pim_p_con->SetFillColor(kOrange);
  h_vtx_pim_p_con->SetMarkerColor(kOrange);
  h_vtx_pim_p_sig->SetLineColor(2);
  h_vtx_pim_p_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_vtx_pim_p_dat->GetYaxis()->SetRangeUser(0,22000);  
  h_vtx_pim_p_dat->SetXTitle("P(#pi^{-})(GeV/c)");
  h_vtx_pim_p_dat->SetYTitle("Events/(0.005GeV/c)");
  h_vtx_pim_p_dat->GetXaxis()->CenterTitle();
  h_vtx_pim_p_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_vtx_pim_p = new THStack("h_vtx_pim_p","");
  h_vtx_pim_p->Add(h_vtx_pim_p_con);
  h_vtx_pim_p->Add(h_vtx_pim_p_inc);
  
  TCanvas *c1_h_vtx_pim_p = new TCanvas();	
  c1_h_vtx_pim_p->SetFillColor(0);
  c1_h_vtx_pim_p->SetFrameFillColor(0);
  h_vtx_pim_p_dat->Draw();
  h_vtx_pim_p->Draw("same");
  h_vtx_pim_p_sig->Draw("same");
  h_vtx_pim_p_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////  
  TLine* cutline2_h_vtx_pim_p = new TLine(0.45,22000,0.45,0); 
  cutline2_h_vtx_pim_p->SetLineColor(kBlue);
  cutline2_h_vtx_pim_p->SetLineWidth(3);
  cutline2_h_vtx_pim_p->SetLineStyle(kDashed);
  cutline2_h_vtx_pim_p->Draw();	

  TArrow *arrow2_h_vtx_pim_p = new TArrow(0.45,11000,0.42,11000,0.02,"|>");
  arrow2_h_vtx_pim_p->SetLineWidth(3);
  arrow2_h_vtx_pim_p->SetFillColor(kBlue);
  arrow2_h_vtx_pim_p->SetLineColor(kBlue);
  arrow2_h_vtx_pim_p->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_vtx_pim_p_dat,"Data","lp");
  myLegd->AddEntry(h_vtx_pim_p_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_vtx_pim_p_con,"Cont.");
  myLegd->AddEntry(h_vtx_pim_p_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_vtx_pim_p->SaveAs("pic/h_vtx_pim_p.pdf");





/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_vtx_cosmumu                                 //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  Double_t vtx_cosmumu;
  
  TTree *tree_vtx_cosmumu_inc =(TTree *)f_inc->Get("signal");
  TTree *tree_vtx_cosmumu_sig =(TTree *)f_sig->Get("signal");
  TTree *tree_vtx_cosmumu_dat =(TTree *)f_dat->Get("signal");
  TTree *tree_vtx_cosmumu_con =(TTree *)f_con->Get("signal");

  TH1F *h_vtx_cosmumu_sig = new TH1F("h_vtx_cosmumu_sig","",100,-1,-0.8);
  TH1F *h_vtx_cosmumu_dat = new TH1F("h_vtx_cosmumu_dat","",100,-1,-0.8);
  TH1F *h_vtx_cosmumu_con = new TH1F("h_vtx_cosmumu_con","",100,-1,-0.8);
  TH1F *h_vtx_cosmumu_inc = new TH1F("h_vtx_cosmumu_inc","",100,-1,-0.8);

  tree_vtx_cosmumu_inc->SetBranchAddress("vtx_cosmumu",&vtx_cosmumu);
  for(Int_t i =0;i<tree_vtx_cosmumu_inc->GetEntries();i++)
  {
    tree_vtx_cosmumu_inc->GetEntry(i);
    h_vtx_cosmumu_inc->Fill(vtx_cosmumu);
  }
  
  tree_vtx_cosmumu_sig->SetBranchAddress("vtx_cosmumu",&vtx_cosmumu);
  for(Int_t i =0;i<tree_vtx_cosmumu_sig->GetEntries();i++)
  {
    tree_vtx_cosmumu_sig->GetEntry(i);
    h_vtx_cosmumu_sig->Fill(vtx_cosmumu);
  }
  
  tree_vtx_cosmumu_dat->SetBranchAddress("vtx_cosmumu",&vtx_cosmumu);
  for(Int_t i =0;i<tree_vtx_cosmumu_dat->GetEntries();i++)
  {
    tree_vtx_cosmumu_dat->GetEntry(i);
    h_vtx_cosmumu_dat->Fill(vtx_cosmumu);
  }
  
  tree_vtx_cosmumu_con->SetBranchAddress("vtx_cosmumu",&vtx_cosmumu);
  for(Int_t i =0;i<tree_vtx_cosmumu_con->GetEntries();i++)
  {
    tree_vtx_cosmumu_con->GetEntry(i);
    h_vtx_cosmumu_con->Fill(vtx_cosmumu);
  }

  
  h_vtx_cosmumu_con->Scale(scale_con);
  h_vtx_cosmumu_inc->Scale(scale_psip);
  h_vtx_cosmumu_sig->Scale(0.5*h_vtx_cosmumu_dat->GetMaximum()/h_vtx_cosmumu_sig->GetMaximum());

  h_vtx_cosmumu_dat->SetTitle("");
  h_vtx_cosmumu_dat->SetStats(0);
  h_vtx_cosmumu_dat->Sumw2();
  h_vtx_cosmumu_dat->SetMarkerStyle(20);
  h_vtx_cosmumu_dat->SetMarkerSize(0.8);
  h_vtx_cosmumu_dat->SetLineWidth(2);
  h_vtx_cosmumu_inc->SetLineColor(29);
  h_vtx_cosmumu_inc->SetFillColor(29);
  h_vtx_cosmumu_inc->SetMarkerColor(29);
  h_vtx_cosmumu_con->SetLineColor(kOrange);
  h_vtx_cosmumu_con->SetFillColor(kOrange);
  h_vtx_cosmumu_con->SetMarkerColor(kOrange);
  h_vtx_cosmumu_sig->SetLineColor(2);
  h_vtx_cosmumu_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_vtx_cosmumu_dat->GetYaxis()->SetRangeUser(0,150000);  
  h_vtx_cosmumu_dat->SetXTitle("cos#theta_{#mu^{+}#mu^{-}}");
  h_vtx_cosmumu_dat->SetYTitle("Events/0.002");
  h_vtx_cosmumu_dat->GetXaxis()->CenterTitle();
  h_vtx_cosmumu_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_vtx_cosmumu = new THStack("h_vtx_cosmumu","");
  h_vtx_cosmumu->Add(h_vtx_cosmumu_con);
  h_vtx_cosmumu->Add(h_vtx_cosmumu_inc);
  
  TCanvas *c1_h_vtx_cosmumu = new TCanvas();	
  c1_h_vtx_cosmumu->SetFillColor(0);
  c1_h_vtx_cosmumu->SetFrameFillColor(0);
  h_vtx_cosmumu_dat->Draw();
  h_vtx_cosmumu->Draw("same");
  h_vtx_cosmumu_sig->Draw("same");
  h_vtx_cosmumu_dat->Draw("same");
  
  myLegd->Clear();
  myLegd->AddEntry(h_vtx_cosmumu_dat,"Data","lp");
  myLegd->AddEntry(h_vtx_cosmumu_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_vtx_cosmumu_con,"Cont.");
  myLegd->AddEntry(h_vtx_cosmumu_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_vtx_cosmumu->SaveAs("pic/h_vtx_cosmumu.pdf");
  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		epeatio                                 //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////  
  TFile *f_sig_e = new TFile("../../PipiEe/signal/ee_signal_all.root");
  TFile *f_dat_e = new TFile("../../PipiEe/09data/ee_data09_all.root");
  TFile *f_con_e = new TFile("../../PipiEe/con3650/ee_con3650_all.root");
  TFile *f_inc_e = new TFile("../../PipiEe/09mc/ee_09mc_all.root");
  
  TH2F *h_epratio_sig = (TH2F*)f_sig_e->Get("h_epratio");
  TH2F *h_epratio_dat = (TH2F*)f_dat_e->Get("h_epratio");
  TH2F *h_epratio_con = (TH2F*)f_con_e->Get("h_epratio");
  TH2F *h_epratio_inc = (TH2F*)f_inc_e->Get("h_epratio");
  
  
  //TF1 *line1 = new TF1("fa1","0.26",0.,0.26);
  TF1 *line1 = new TF1("fa1","1-sqrt(0.16-(x-1)**2)",1-sqrt(0.12),0.8);
  TF1 *line2 = new TF1("fa2","0.8",0.,1-sqrt(0.12));
  TF1 *line3 = new TF1("fa3","0.26",0.,0.26);
  
  TLine* line4 = new TLine(0.26,0.26,0.26,0); 
  TLine* line5 = new TLine(0.8,1-sqrt(0.12),0.8,0); 
  line1->SetLineColor(kBlue);
  line1->SetLineWidth(3);
  line1->SetLineStyle(kDashed);

  line2->SetLineColor(kBlue);
  line2->SetLineWidth(3);
  line2->SetLineStyle(kDashed);

  line3->SetLineColor(kBlue);
  line3->SetLineWidth(3);
  line3->SetLineStyle(kDashed);

  line4->SetLineColor(kBlue);
  line4->SetLineWidth(3);
  line4->SetLineStyle(kDashed);

  line5->SetLineColor(kBlue);
  line5->SetLineWidth(3);
  line5->SetLineStyle(kDashed);
  
  h_epratio_dat->SetMarkerStyle(1);
  h_epratio_dat->SetXTitle("E/P of l^{+}");
  h_epratio_dat->SetYTitle("E/P of l^{-}");
  h_epratio_dat->GetXaxis()->CenterTitle();
  h_epratio_dat->GetYaxis()->CenterTitle();
  
  TCanvas *c1_h_epratio_dat = new TCanvas();
  c1_h_epratio_dat->SetFillColor(0);
  c1_h_epratio_dat->SetFrameFillColor(0);

  h_epratio_dat->Draw();
  line1->Draw("same");
  line2->Draw("same");
  line3->Draw("same");
  line4->Draw("same");
  line5->Draw("same");
  c1_h_epratio_dat->SaveAs("pic/epratio_data.pdf");

  h_epratio_inc->Add(h_epratio_con);
  h_epratio_inc->SetMarkerStyle(1);
  h_epratio_inc->SetXTitle("E/P of l^{+}");
  h_epratio_inc->SetYTitle("E/P of l^{-}");
  h_epratio_inc->GetXaxis()->CenterTitle();
  h_epratio_inc->GetYaxis()->CenterTitle();
  
  TCanvas *c1_h_epratio_inc_con = new TCanvas();    
  c1_h_epratio_inc_con->SetFillColor(0);
  c1_h_epratio_inc_con->SetFrameFillColor(0);
  
  h_epratio_inc->Draw();
  line1->Draw("same");
  line2->Draw("same");
  line3->Draw("same");
  line4->Draw("same");
  line5->Draw("same");
  c1_h_epratio_inc_con->SaveAs("pic/epratio_inclu_mc_coti.pdf");
  
}
