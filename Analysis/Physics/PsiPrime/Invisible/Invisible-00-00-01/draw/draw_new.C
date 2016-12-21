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

void draw_new()
{
  double scale_con = 11.22;//509.4/44.5*(3.65/3.686)**2
  double scale_psip = 0.875;

  TGaxis::SetMaxDigits(3);

  TLegend* myLegd = new TLegend(0.2, 0.71, 0.50, 0.88);
  myLegd->SetTextSize(0.04);
  myLegd->SetFillColor(0);
  myLegd->SetFillStyle(0);
  myLegd->SetLineColor(0);
  myLegd->SetShadowColor(0);
  myLegd->SetTextFont(132);

  TFile *f_sig = new TFile("../signal/invisible_signal_50w.root");
  TFile *f_dat = new TFile("../data09/invisible_data09_all.root");
  TFile *f_con = new TFile("../con3650/invisible_con3650_all.root");
  TFile *f_inc = new TFile("../09mc/invisible_09mc_all.root");
  
  
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
  h_cospipi_dat->GetYaxis()->SetRangeUser(0,11000);  
  h_cospipi_dat->SetXTitle("cos#theta_{#pi^{+}#pi^{-}}");
  h_cospipi_dat->SetYTitle("Events/0.02");
  h_cospipi_dat->GetXaxis()->CenterTitle();
  h_cospipi_dat->GetYaxis()->CenterTitle();
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
  TLine* cutline2_h_cospipi = new TLine(0.95,11000,0.95,0); 
  cutline2_h_cospipi->SetLineColor(kBlue);
  cutline2_h_cospipi->SetLineWidth(3);
  cutline2_h_cospipi->SetLineStyle(kDashed);
  cutline2_h_cospipi->Draw();	

  TArrow *arrow2_h_cospipi = new TArrow(0.95,5500,0.87,5500,0.02,"|>");
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
  h_cos2pisys_dat->GetYaxis()->SetRangeUser(0,11000);  
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
  TLine* cutline1_h_cos2pisys = new TLine(-0.90,11000,-0.90,0); 
  cutline1_h_cos2pisys->SetLineColor(kBlue);
  cutline1_h_cos2pisys->SetLineWidth(3);
  cutline1_h_cos2pisys->SetLineStyle(kDashed);
  cutline1_h_cos2pisys->Draw();	

  TArrow *arrow1_h_cos2pisys = new TArrow(-0.90,5500,-0.82,5500,0.02,"|>");
  arrow1_h_cos2pisys->SetLineWidth(3);
  arrow1_h_cos2pisys->SetFillColor(kBlue);
  arrow1_h_cos2pisys->SetLineColor(kBlue);
  arrow1_h_cos2pisys->Draw();  
  
  TLine* cutline2_h_cos2pisys = new TLine(0.90,11000,0.90,0); 
  cutline2_h_cos2pisys->SetLineColor(kBlue);
  cutline2_h_cos2pisys->SetLineWidth(3);
  cutline2_h_cos2pisys->SetLineStyle(kDashed);
  cutline2_h_cos2pisys->Draw();	

  TArrow *arrow2_h_cos2pisys = new TArrow(0.90,5500,0.82,5500,0.02,"|>");
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
//                            		h_pip_p                                    //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_pip_p_sig = (TH1F*)f_sig->Get("h_pip_p");
  TH1F *h_pip_p_dat = (TH1F*)f_dat->Get("h_pip_p");
  TH1F *h_pip_p_con = (TH1F*)f_con->Get("h_pip_p");
  TH1F *h_pip_p_inc = (TH1F*)f_inc->Get("h_pip_p");
  
  h_pip_p_con->Scale(scale_con);
  h_pip_p_inc->Scale(scale_psip);
  h_pip_p_sig->Scale(0.5*h_pip_p_dat->GetMaximum()/h_pip_p_sig->GetMaximum());

  h_pip_p_dat->SetTitle("");
  h_pip_p_dat->SetStats(0);
  h_pip_p_dat->Sumw2();
  h_pip_p_dat->SetMarkerStyle(20);
  h_pip_p_dat->SetMarkerSize(0.8);
  h_pip_p_dat->SetLineWidth(2);
  h_pip_p_inc->SetLineColor(29);
  h_pip_p_inc->SetFillColor(29);
  h_pip_p_inc->SetMarkerColor(29);
  h_pip_p_con->SetLineColor(kOrange);
  h_pip_p_con->SetFillColor(kOrange);
  h_pip_p_con->SetMarkerColor(kOrange);
  h_pip_p_sig->SetLineColor(2);
  h_pip_p_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_pip_p_dat->GetYaxis()->SetRangeUser(0,6000);  
  h_pip_p_dat->SetXTitle("P(#pi^{+})(GeV/c)");
  h_pip_p_dat->SetYTitle("Events/(0.005 GeV/c)");
  h_pip_p_dat->GetXaxis()->CenterTitle();
  h_pip_p_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_pip_p = new THStack("h_pip_p","");
  h_pip_p->Add(h_pip_p_con);
  h_pip_p->Add(h_pip_p_inc);
  
  TCanvas *c1_h_pip_p = new TCanvas();	
  c1_h_pip_p->SetFillColor(0);
  c1_h_pip_p->SetFrameFillColor(0); 
  h_pip_p_dat->Draw();
  h_pip_p->Draw("same");
  h_pip_p_sig->Draw("same");
  h_pip_p_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline2_h_pip_p = new TLine(0.45,6000,0.45,0); 
  cutline2_h_pip_p->SetLineColor(kBlue);
  cutline2_h_pip_p->SetLineWidth(3);
  cutline2_h_pip_p->SetLineStyle(kDashed);
  cutline2_h_pip_p->Draw();	

  TArrow *arrow2_h_pip_p = new TArrow(0.45,3000,0.43,3000,0.02,"|>");
  arrow2_h_pip_p->SetLineWidth(3);
  arrow2_h_pip_p->SetFillColor(kBlue);
  arrow2_h_pip_p->SetLineColor(kBlue);
  arrow2_h_pip_p->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_pip_p_dat,"Data","lp");
  myLegd->AddEntry(h_pip_p_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_pip_p_con,"Cont.");
  myLegd->AddEntry(h_pip_p_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_pip_p->SaveAs("pic/h_pip_p.pdf");  
  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_pim_p                                        //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_pim_p_sig = (TH1F*)f_sig->Get("h_pim_p");
  TH1F *h_pim_p_dat = (TH1F*)f_dat->Get("h_pim_p");
  TH1F *h_pim_p_con = (TH1F*)f_con->Get("h_pim_p");
  TH1F *h_pim_p_inc = (TH1F*)f_inc->Get("h_pim_p");
  
  h_pim_p_con->Scale(scale_con);
  h_pim_p_inc->Scale(scale_psip);
  h_pim_p_sig->Scale(0.5*h_pim_p_dat->GetMaximum()/h_pim_p_sig->GetMaximum());

  h_pim_p_dat->SetTitle("");
  h_pim_p_dat->SetStats(0);
  h_pim_p_dat->Sumw2();
  h_pim_p_dat->SetMarkerStyle(20);
  h_pim_p_dat->SetMarkerSize(0.8);
  h_pim_p_dat->SetLineWidth(2);
  h_pim_p_inc->SetLineColor(29);
  h_pim_p_inc->SetFillColor(29);
  h_pim_p_inc->SetMarkerColor(29);
  h_pim_p_con->SetLineColor(kOrange);
  h_pim_p_con->SetFillColor(kOrange);
  h_pim_p_con->SetMarkerColor(kOrange);
  h_pim_p_sig->SetLineColor(2);
  h_pim_p_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_pim_p_dat->GetYaxis()->SetRangeUser(0,6000);  
  h_pim_p_dat->SetXTitle("P(#pi^{-})(GeV/c)");
  h_pim_p_dat->SetYTitle("Events/(0.005 GeV/c)");
  h_pim_p_dat->GetXaxis()->CenterTitle();
  h_pim_p_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_pim_p = new THStack("h_pim_p","");
  h_pim_p->Add(h_pim_p_con);
  h_pim_p->Add(h_pim_p_inc);
  
  TCanvas *c1_h_pim_p = new TCanvas();	
  c1_h_pim_p->SetFillColor(0);
  c1_h_pim_p->SetFrameFillColor(0);
  h_pim_p_dat->Draw();
  h_pim_p->Draw("same");
  h_pim_p_sig->Draw("same");
  h_pim_p_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  TLine* cutline2_h_pim_p = new TLine(0.45,6000,0.45,0); 
  cutline2_h_pim_p->SetLineColor(kBlue);
  cutline2_h_pim_p->SetLineWidth(3);
  cutline2_h_pim_p->SetLineStyle(kDashed);
  cutline2_h_pim_p->Draw();	

  TArrow *arrow2_h_pim_p = new TArrow(0.45,3000,0.43,3000,0.02,"|>");
  arrow2_h_pim_p->SetLineWidth(3);
  arrow2_h_pim_p->SetFillColor(kBlue);
  arrow2_h_pim_p->SetLineColor(kBlue);
  arrow2_h_pim_p->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_pim_p_dat,"Data","lp");
  myLegd->AddEntry(h_pim_p_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_pim_p_con,"Cont.");
  myLegd->AddEntry(h_pim_p_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_pim_p->SaveAs("pic/h_pim_p.pdf");  

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
  h_pim_costhe_dat->GetYaxis()->SetRangeUser(0,3000);  
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
  TLine* cutline1_h_pim_costhe = new TLine(-0.80,3000,-0.80,0); 
  cutline1_h_pim_costhe->SetLineColor(kBlue);
  cutline1_h_pim_costhe->SetLineWidth(3);
  cutline1_h_pim_costhe->SetLineStyle(kDashed);
  cutline1_h_pim_costhe->Draw();	

  TArrow *arrow1_h_pim_costhe = new TArrow(-0.80,1500,-0.72,1500,0.02,"|>");
  arrow1_h_pim_costhe->SetLineWidth(3);
  arrow1_h_pim_costhe->SetFillColor(kBlue);
  arrow1_h_pim_costhe->SetLineColor(kBlue);
  arrow1_h_pim_costhe->Draw();  
  
  TLine* cutline2_h_pim_costhe = new TLine(0.80,3000,0.80,0); 
  cutline2_h_pim_costhe->SetLineColor(kBlue);
  cutline2_h_pim_costhe->SetLineWidth(3);
  cutline2_h_pim_costhe->SetLineStyle(kDashed);
  cutline2_h_pim_costhe->Draw();	

  TArrow *arrow2_h_pim_costhe = new TArrow(0.80,1500,0.72,1500,0.02,"|>");
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
  h_pip_costhe_dat->GetYaxis()->SetRangeUser(0,3000);  
  h_pip_costhe_dat->SetXTitle("cos#theta_{#pi^{-}}");
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
  TLine* cutline1_h_pip_costhe = new TLine(-0.80,3000,-0.80,0); 
  cutline1_h_pip_costhe->SetLineColor(kBlue);
  cutline1_h_pip_costhe->SetLineWidth(3);
  cutline1_h_pip_costhe->SetLineStyle(kDashed);
  cutline1_h_pip_costhe->Draw();	

  TArrow *arrow1_h_pip_costhe = new TArrow(-0.80,1500,-0.72,1500,0.02,"|>");
  arrow1_h_pip_costhe->SetLineWidth(3);
  arrow1_h_pip_costhe->SetFillColor(kBlue);
  arrow1_h_pip_costhe->SetLineColor(kBlue);
  arrow1_h_pip_costhe->Draw();  
  
  TLine* cutline2_h_pip_costhe = new TLine(0.80,3000,0.80,0); 
  cutline2_h_pip_costhe->SetLineColor(kBlue);
  cutline2_h_pip_costhe->SetLineWidth(3);
  cutline2_h_pip_costhe->SetLineStyle(kDashed);
  cutline2_h_pip_costhe->Draw();	

  TArrow *arrow2_h_pip_costhe = new TArrow(0.80,1500,0.72,1500,0.02,"|>");
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
//                            		h_ngamma                                    //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_ngamma_sig = (TH1F*)f_sig->Get("h_ngamma");
  TH1F *h_ngamma_dat = (TH1F*)f_dat->Get("h_ngamma");
  TH1F *h_ngamma_con = (TH1F*)f_con->Get("h_ngamma");
  TH1F *h_ngamma_inc = (TH1F*)f_inc->Get("h_ngamma");
  
  h_ngamma_con->Scale(scale_con);
  h_ngamma_inc->Scale(scale_psip);
  h_ngamma_sig->Scale(0.5*h_ngamma_dat->GetMaximum()/h_ngamma_sig->GetMaximum());

  h_ngamma_dat->SetTitle("");
  h_ngamma_dat->SetStats(0);
  h_ngamma_dat->Sumw2();
  h_ngamma_dat->SetMarkerStyle(20);
  h_ngamma_dat->SetMarkerSize(0.8);
  h_ngamma_dat->SetLineWidth(2);
  h_ngamma_inc->SetLineColor(29);
  h_ngamma_inc->SetFillColor(29);
  h_ngamma_inc->SetMarkerColor(29);
  h_ngamma_con->SetLineColor(kOrange);
  h_ngamma_con->SetFillColor(kOrange);
  h_ngamma_con->SetMarkerColor(kOrange);
  h_ngamma_sig->SetLineColor(2);
  h_ngamma_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_ngamma_dat->GetYaxis()->SetRangeUser(0,200000);  
  h_ngamma_dat->SetXTitle("N_{#gamma}");
  h_ngamma_dat->SetYTitle("Events");
  h_ngamma_dat->GetXaxis()->CenterTitle();
  h_ngamma_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_ngamma = new THStack("h_ngamma","");
  h_ngamma->Add(h_ngamma_con);
  h_ngamma->Add(h_ngamma_inc);
  
  TCanvas *c1_h_ngamma = new TCanvas();	
  c1_h_ngamma->SetFillColor(0);
  c1_h_ngamma->SetFrameFillColor(0);
  h_ngamma_dat->Draw();
  h_ngamma->Draw("same");
  h_ngamma_sig->Draw("same");
  h_ngamma_dat->Draw("same");
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////  
  TLine* cutline2_h_ngamma = new TLine(1.0,200000,1.0,0); 
  cutline2_h_ngamma->SetLineColor(kBlue);
  cutline2_h_ngamma->SetLineWidth(3);
  cutline2_h_ngamma->SetLineStyle(kDashed);
  cutline2_h_ngamma->Draw();	

  TArrow *arrow2_h_ngamma = new TArrow(1.00,100000,0.0,100000,0.02,"|>");
  arrow2_h_ngamma->SetLineWidth(3);
  arrow2_h_ngamma->SetFillColor(kBlue);
  arrow2_h_ngamma->SetLineColor(kBlue);
  arrow2_h_ngamma->Draw();

  /////////////////////////////////////////////////////////////////////
  
  myLegd->Clear();
  myLegd->AddEntry(h_ngamma_dat,"Data","lp");
  myLegd->AddEntry(h_ngamma_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_ngamma_con,"Cont.");
  myLegd->AddEntry(h_ngamma_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_ngamma->SaveAs("pic/h_ngamma.pdf");
  
  
/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_mpipi                                        //
//																				   //
/////////////////////////////////////////////////////////////////////////////////////
  TH1F *h_mpipi_sig = (TH1F*)f_sig->Get("h_mpipi");
  TH1F *h_mpipi_dat = (TH1F*)f_dat->Get("h_mpipi");
  TH1F *h_mpipi_con = (TH1F*)f_con->Get("h_mpipi");
  TH1F *h_mpipi_inc = (TH1F*)f_inc->Get("h_mpipi");
  
  h_mpipi_con->Scale(scale_con);
  h_mpipi_inc->Scale(scale_psip);
  h_mpipi_sig->Scale(0.5*h_mpipi_dat->GetMaximum()/h_mpipi_sig->GetMaximum());

  h_mpipi_dat->SetTitle("");
  h_mpipi_dat->SetStats(0);
  h_mpipi_dat->Sumw2();
  h_mpipi_dat->SetMarkerStyle(20);
  h_mpipi_dat->SetMarkerSize(0.8);
  h_mpipi_dat->SetLineWidth(2);
  h_mpipi_inc->SetLineColor(29);
  h_mpipi_inc->SetFillColor(29);
  h_mpipi_inc->SetMarkerColor(29);
  h_mpipi_con->SetLineColor(kOrange);
  h_mpipi_con->SetFillColor(kOrange);
  h_mpipi_con->SetMarkerColor(kOrange);
  h_mpipi_sig->SetLineColor(2);
  h_mpipi_sig->SetLineWidth(2);
  
  /////////////////////////////////////////////////////////////////////////////
  //																		 //	
  //                              modify								     //
  //																	     //
  /////////////////////////////////////////////////////////////////////////////
  h_mpipi_dat->GetYaxis()->SetRangeUser(0,7000);  
  h_mpipi_dat->SetXTitle("M_{#pi^{+}#pi^{-}}(GeV/c^{2})");
  h_mpipi_dat->SetYTitle("Events/(0.005Gev/c^{2})");
  h_mpipi_dat->GetXaxis()->CenterTitle();
  h_mpipi_dat->GetYaxis()->CenterTitle();
  /////////////////////////////////////////////////////////////////////

  THStack *h_mpipi = new THStack("h_mpipi","");
  h_mpipi->Add(h_mpipi_con);
  h_mpipi->Add(h_mpipi_inc);
  
  TCanvas *c1_h_mpipi = new TCanvas();	
  c1_h_mpipi->SetFillColor(0);
  c1_h_mpipi->SetFrameFillColor(0);
  h_mpipi_dat->Draw();
  h_mpipi->Draw("same");
  h_mpipi_sig->Draw("same");
  h_mpipi_dat->Draw("same");

  
  myLegd->Clear();
  myLegd->AddEntry(h_mpipi_dat,"Data","lp");
  myLegd->AddEntry(h_mpipi_inc,"#psi(2S) inclusive MC");
  myLegd->AddEntry(h_mpipi_con,"Cont.");
  myLegd->AddEntry(h_mpipi_sig,"Signal MC","l");
  myLegd->Draw();
  
  c1_h_mpipi->SaveAs("pic/h_mpipi.pdf");  



/////////////////////////////////////////////////////////////////////////////////////
//																				   //
//                            		h_mrecpipi                                        //
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
  h_mrecpipi_dat->GetYaxis()->SetRangeUser(0,60000);  
  h_mrecpipi_dat->SetXTitle("M(recoil(#pi^{+}#pi^{-}))(GeV/c^{2})");
  h_mrecpipi_dat->SetYTitle("Events/(0.002Gev/c^{2})");
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
  
}
