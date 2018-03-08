#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

int make_fig(TH1F* h1, TH1F* h2, TH1F* h3, double hmax, 
	     std::string &xtitle,std::string &ytitle, std::string &figname, int flag)
{
  TH1F *htmp_mc   = (TH1F*)h1->Clone();
  TH1F *htmp_data = (TH1F*)h2->Clone();
  TH1F *htmp_nonpipi = (TH1F*)h3->Clone();

  gStyle->SetAxisColor(1);

  
  TCanvas *MyC_tmp = new TCanvas("MyC_tmp","",500,375);
  htmp_mc->SetMaximum(hmax);
  
  htmp_mc->GetXaxis()->SetTitleFont(132);
  htmp_mc->GetYaxis()->SetTitleFont(132);
  htmp_mc->GetXaxis()->SetLabelFont(132);
  htmp_mc->GetYaxis()->SetLabelFont(132);
  htmp_mc->GetXaxis()->SetTitleOffset(1.2);
  htmp_mc->GetYaxis()->SetTitleOffset(1.1);
  htmp_mc->GetXaxis()->SetTitleSize(0.065);
  htmp_mc->GetYaxis()->SetTitleSize(0.065);
  htmp_mc->GetXaxis()->SetLabelOffset(0.02);
  htmp_mc->GetYaxis()->SetLabelOffset(0.02);
  
  htmp_mc->GetXaxis()->SetLabelSize(0.05);
  htmp_mc->GetYaxis()->SetLabelSize(0.05);
  
  
  htmp_mc->GetXaxis()->SetTitle(xtitle.c_str());
  htmp_mc->GetYaxis()->SetTitle(ytitle.c_str());
  
  htmp_mc->GetXaxis()->CenterTitle();
  htmp_mc->GetYaxis()->CenterTitle();
  
  htmp_mc->GetXaxis()->SetNdivisions(505);
  htmp_mc->GetYaxis()->SetNdivisions(505);

  TGaxis::SetMaxDigits(3);
  MyC_tmp->SetTicks(1,1);
  
  htmp_mc->Draw();
  gPad->SetBottomMargin(0.17);
  gPad->SetLeftMargin(0.16);
  
  //htmp_mc->SetFillColor(kGreen-8);
  htmp_mc->SetFillColor(29);
  htmp_mc->SetLineColor(29);
  htmp_mc->SetMinimum(0);

  htmp_data->Scale(400.0/341.0);
  htmp_data->Draw("same,P");
  htmp_data->Sumw2();
  htmp_data->SetMarkerStyle(20);
  htmp_data->SetMarkerSize(0.55);

  htmp_nonpipi->Draw("same");
  htmp_nonpipi->SetLineColor(6);

  htmp_mc->SetName("");
  htmp_mc->SetTitle("");
  htmp_data->SetName("");
  htmp_data->SetTitle("");
  htmp_nonpipi->SetName("");
  htmp_nonpipi->SetTitle("");

  

  

  //*********Drawing********//
  
  double tmp_xmax = htmp_mc->GetXaxis()->GetXmax();
  double tmp_xmin  = htmp_mc->GetXaxis()->GetXmin();
  
  double circ_x[1], circ_y[1];
  double box_x[1], box_y[1];
  circ_x[0] = (tmp_xmax - tmp_xmin)*0.08 + tmp_xmin;
  circ_y[0] = hmax * 0.94;
  box_x[0] =  (tmp_xmax - tmp_xmin)*0.08 + tmp_xmin;
  box_y[0] =  hmax * 0.87;
  
  TGraph *gr_circ = new TGraph(1, circ_x, circ_y);
  TGraph *gr_box  = new TGraph(1, box_x, box_y);
  gr_circ->SetMarkerStyle(20);   gr_box->SetMarkerStyle(21);
  gr_circ->SetMarkerColor(1);    gr_box->SetMarkerColor(29);
  gr_circ->SetMarkerSize(0.75);  gr_box->SetMarkerSize(1.5);
  gr_circ->Draw("SAME,P");       gr_box->Draw("SAME,P");
  
  double x1 = (tmp_xmax-tmp_xmin)*0.06 + tmp_xmin;
  double x2 = (tmp_xmax-tmp_xmin)*0.10 + tmp_xmin;
  TLine *t1 = new TLine(x1, hmax*0.94, x2, hmax*0.94);
  t1->Draw();

  TLatex t_circ, t_box;
  t_circ.SetTextSize(0.04);  t_box.SetTextSize(0.04);
  t_circ.SetTextFont(132);    t_box.SetTextFont(132);
  t_circ.SetTextAlign(12);    t_box.SetTextAlign(12);
  t_circ.DrawLatex((tmp_xmax-tmp_xmin)*0.11+tmp_xmin, hmax*0.94, "Data");
  t_box.DrawLatex((tmp_xmax-tmp_xmin)*0.11+tmp_xmin, hmax*0.87, "#psi(2S) inclusive MC");
  
  // For Non-pipiJpsi
  TLine *nont = new TLine(x1, hmax*0.80, x2, hmax*0.80);
  nont->SetLineColor(6);
  nont->Draw();
  TLatex t_nonpipiJpsi;
  t_nonpipiJpsi.SetTextSize(0.04);
  t_nonpipiJpsi.SetTextFont(132);
  t_nonpipiJpsi.SetTextAlign(12);
  t_nonpipiJpsi.DrawLatex( (tmp_xmax-tmp_xmin)*0.11+tmp_xmin, hmax*0.80, "Non-#pi#piJ/#psi");


  if(flag==3 || flag==4)
    {
      TLine *tp = new TLine(0.45, 0.0, 0.45, hmax);
      tp->Draw();
      tp->SetLineStyle(2);
      tp->SetLineColor(4);

      TArrow *ar1 = new TArrow(0.45, hmax*0.5, 0.42, hmax*0.5, 0.02, "|>");
      ar1->Draw();
      ar1->SetLineColor(4);
      ar1->SetLineWidth(1.5);
    }
  if(flag==7 || flag==8)
    {
      TArrow *ar1 = new TArrow(-0.80, hmax*0.7, -0.80, hmax*0.6, 0.02, "|>");
      ar1->Draw();
      ar1->SetLineColor(4);
      ar1->SetLineWidth(1.5);

      TArrow *ar2 = new TArrow(0.80, hmax*0.7, 0.80, hmax*0.6, 0.02, "|>");
      ar2->Draw();
      ar2->SetLineColor(4);
      ar2->SetLineWidth(1.5);
    }
  if(flag==5)
    {
      TLine *tp = new TLine(0.95, 0.0, 0.95, hmax);
      tp->Draw();
      tp->SetLineStyle(2);
      tp->SetLineColor(4);

      TArrow *ar1 = new TArrow(0.95, hmax*0.5, 0.85, hmax*0.5, 0.02, "|>");
      ar1->Draw();
      ar1->SetLineColor(4);
      ar1->SetLineWidth(1.5); 
    }
  if(flag==6)
    {
      TArrow *ar1 = new TArrow(-0.90, 0.9*1000000, -0.90, 0.8*1000000, 0.02, "|>");
      ar1->Draw();
      ar1->SetLineColor(4);
      ar1->SetLineWidth(1.5);

      TArrow *ar2 = new TArrow(0.90, 0.9*1000000, 0.90, 0.8*1000000, 0.02, "|>");
      ar2->Draw();
      ar2->SetLineColor(4);
      ar2->SetLineWidth(1.5);
    }
    
  
  //************************//
    
  MyC_tmp->Print(figname.c_str());
     

  return 0;
}

int plot()
{
   gStyle->SetOptStat(000);
   
   std::stringstream hist_title_1, hist_title_2, hist_title_3;
   std::stringstream hist_title_4, hist_title_5, hist_title_6;
   std::stringstream hist_title_7, hist_title_8, hist_title_9;

   
   // difference is only [3.03-3.17] (mrecpipi) <--> [3.04-3.16] (mrecpipi_org for past root files)
   // Need to change "h_mrecpipi" !! from next time. 
   hist_title_1  << "h_mrecpipi" ;  

   hist_title_2  << "h_mpipi" ;
   hist_title_3  << "h_pip_p" ;
   hist_title_4  << "h_pim_p" ;
   hist_title_5  << "h_cospipi" ;
   hist_title_6  << "h_cos2pisys" ;
   hist_title_7  << "h_pip_costhe" ;
   hist_title_8  << "h_pim_costhe" ;


   std::string histname_mc1, histname_mc2, histname_mc3, histname_mc4;
   std::string histname_mc5, histname_mc6, histname_mc7, histname_mc8;
   std::string histname_data1, histname_data2, histname_data3, histname_data4; 
   std::string histname_data5, histname_data6, histname_data7, histname_data8; 
   std::string xtitle1, xtitle2, xtitle3, xtitle4;
   std::string xtitle5, xtitle6, xtitle7, xtitle8;
   std::string ytitle1, ytitle2, ytitle3, ytitle4;
   std::string ytitle5, ytitle6, ytitle7, ytitle8;
   std::string figname1, figname2, figname3, figname4;
   std::string figname5, figname6, figname7, figname8;
   

   TFile *f1 = new TFile("./run/jpsi2incl/hist_mc12/jpsi2incl_psip_mc12_event_merged_1.root");
   TH1F* htmp_1_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_1.str().c_str()));
   TH1F* htmp_2_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_2.str().c_str()));
   TH1F* htmp_3_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_3.str().c_str()));
   TH1F* htmp_4_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_4.str().c_str()));
   TH1F* htmp_5_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_5.str().c_str()));
   TH1F* htmp_6_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_6.str().c_str()));
   TH1F* htmp_7_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_7.str().c_str()));
   TH1F* htmp_8_new_mc = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_8.str().c_str()));


   TFile *f2 = new TFile("./run/jpsi2incl/hist/jpsi2incl_data_psip_data12_event_merged_incl.root");
   TH1F* htmp_1_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_1.str().c_str()));
   TH1F* htmp_2_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_2.str().c_str()));
   TH1F* htmp_3_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_3.str().c_str()));
   TH1F* htmp_4_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_4.str().c_str()));
   TH1F* htmp_5_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_5.str().c_str()));
   TH1F* htmp_6_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_6.str().c_str()));
   TH1F* htmp_7_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_7.str().c_str()));
   TH1F* htmp_8_new_data = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_8.str().c_str()));


   TFile *f3 = new TFile("./run/jpsi2incl/hist_mc12/jpsi2incl_psip_mc12_event_merged_nonpipi.root");
   TH1F* htmp_1_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_1.str().c_str()));
   TH1F* htmp_2_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_2.str().c_str()));
   TH1F* htmp_3_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_3.str().c_str()));
   TH1F* htmp_4_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_4.str().c_str()));
   TH1F* htmp_5_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_5.str().c_str()));
   TH1F* htmp_6_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_6.str().c_str()));
   TH1F* htmp_7_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_7.str().c_str()));
   TH1F* htmp_8_nonpipiJpsi = dynamic_cast<TH1F*>(gDirectory->Get(hist_title_8.str().c_str()));



   //#####################################################################
   double hmax1, hmax2, hmax3, hmax4,hmax5;
   double hmax6, hmax7, hmax8, hmax9, hmax10;

   int xmin1 = htmp_1_new_mc->GetXaxis()->FindBin(3.04);
   int xmax1 = htmp_1_new_mc->GetXaxis()->FindBin(3.16);
   
   htmp_1_new_mc->GetXaxis()->SetRange(xmin1,xmax1);
   htmp_1_new_data->GetXaxis()->SetRange(xmin1,xmax1);

   hmax1 = 30000000;
   xtitle1 = "M(recoil(#pi^{+}#pi^{-})) (GeV/c^{2})";
   ytitle1 = "Events/(0.0012 GeV/c^{2})";
   figname1 = "./psfile/incl_mrecpipi.eps";
   make_fig(htmp_1_new_mc, htmp_1_new_data, htmp_1_nonpipiJpsi, hmax1, xtitle1, ytitle1, figname1, 1);

   hmax2 = 4500000;
   xtitle2 = "M(#pi^{+}#pi^{-}) (GeV/c^{2})";
   ytitle2 = "Events/(0.005 GeV/c^{2})";
   figname2 = "./psfile/incl_mpipi.eps";
   make_fig(htmp_2_new_mc, htmp_2_new_data, htmp_2_nonpipiJpsi, hmax2, xtitle2, ytitle2, figname2, 2);

   hmax3 = 3000000;
   xtitle3 = "P(#pi^{+}) (GeV/c)";
   ytitle3 = "Events/(0.005 GeV/c)";
   figname3 = "./psfile/incl_pip_p.eps";
   make_fig(htmp_3_new_mc, htmp_3_new_data, htmp_3_nonpipiJpsi, hmax3, xtitle3, ytitle3, figname3, 3);

   hmax4 = 3000000;
   xtitle4 = "P(#pi^{-}) (GeV/c)";
   ytitle4 = "Events/(0.005 GeV/c)";
   figname4 = "./psfile/incl_pim_p.eps";
   make_fig(htmp_4_new_mc, htmp_4_new_data, htmp_4_nonpipiJpsi, hmax4, xtitle4, ytitle4, figname4, 4);

   hmax5 = 2000000;
   xtitle5 = "Cos#theta_{#pi^{+}#pi^{-}}";
   ytitle5 = "Events/0.01";
   figname5 = "./psfile/incl_cospipi.eps";
   make_fig(htmp_5_new_mc, htmp_5_new_data, htmp_5_nonpipiJpsi, hmax5, xtitle5, ytitle5, figname5, 5);

   hmax6 = 1500000;
   xtitle6 = "Cos#theta_{#pi#pi sys.}";
   ytitle6 = "Events/0.02";
   figname6 = "./psfile/incl_cos2pisys.eps";
   make_fig(htmp_6_new_mc, htmp_6_new_data, htmp_6_nonpipiJpsi, hmax6, xtitle6, ytitle6, figname6, 6);

   hmax7 = 2000000;
   xtitle7 = "Cos#theta_{#pi^{+}}";
   ytitle7 = "Events/0.02";
   figname7 = "./psfile/incl_pip_costhe.eps";
   make_fig(htmp_7_new_mc, htmp_7_new_data, htmp_7_nonpipiJpsi, hmax7, xtitle7, ytitle7, figname7, 7);

   hmax8 = 2000000;
   xtitle8 = "Cos#theta_{#pi^{-}}";
   ytitle8 = "Events/0.02";
   figname8 = "./psfile/incl_pim_costhe.eps";
   make_fig(htmp_8_new_mc, htmp_8_new_data, htmp_8_nonpipiJpsi, hmax8, xtitle8, ytitle8, figname8, 8);

   //#######################################################################





   return 0;
}
