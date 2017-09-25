#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>



int plot()
{
  gStyle->SetOptStat(000);
  
  double x0 = -2.66/1000.0;      // number in memo
  double sigma = 3.00/1000.0; // number in memo

  double mu_t[30000],Prob[30000];

  TH1F *h_gaus = new TH1F("hgaus", "hgaus", 23000, -0.006, 0.017);

  
  // Plot & Integral
  double sum=0.0;
  for(int i=0;i<23000;i++)
    {
      mu_t[i] = (-6.0+i*0.001)/1000.0;
      double c1 = 1/sqrt(2*3.141592*sigma*sigma);
      Prob[i] = c1*exp(-(x0-mu_t[i])*(x0-mu_t[i])/2/sigma/sigma);
      
      h_gaus->SetBinContent(i+1,Prob[i]);
      
      // For Integral
      if(mu_t[i]>=0.0)
	{
	  sum += Prob[i];
	}
    }

  // Draw
  TCanvas *MyC_tmp = new TCanvas("MyC_tmp","",500,350);
  h_gaus->Draw();
  
  
  // Calculation of integral
  double ratio = 0.90; // 90% confidencial level
  double tmp_sum=0.0;
  double hmax=0.0;
  double CL_mu;
  int i_CL;
  for(int i=0;i<23000;i++)
    {
      if(Prob[i]>hmax)
	{
	  hmax = Prob[i];
	}

      if(mu_t[i]>=0.0)
	{
	  tmp_sum += Prob[i];
	}
      if(tmp_sum>=sum*ratio)
	{
	  i_CL=i;
	  CL_mu = mu_t[i];
	  break;
	}
    }

  std::cout << "90% CL limit = " << CL_mu << std::endl;

  h_gaus->SetMaximum(hmax*1.1);
  h_gaus->SetMinimum(0);

  TLine *tl = new TLine(CL_mu, 0, CL_mu, hmax*1.1);
  tl->SetLineColor(4);
  tl->SetLineStyle(2);
  tl->Draw();
  
  gPad->SetBottomMargin(0.17);
  gPad->SetLeftMargin(0.12);

  h_gaus->SetName("");
  h_gaus->SetTitle("");

  h_gaus->GetXaxis()->SetTitleFont(22);
  h_gaus->GetYaxis()->SetTitleFont(22);
  h_gaus->GetXaxis()->SetTitleOffset(1.2);
  h_gaus->GetYaxis()->SetTitleOffset(0.9);
  h_gaus->GetXaxis()->SetTitleSize(0.06);
  h_gaus->GetYaxis()->SetTitleSize(0.06);
  
  h_gaus->GetXaxis()->SetLabelSize(0.05);
  h_gaus->GetYaxis()->SetLabelSize(0.05);
  
  h_gaus->GetXaxis()->SetTitle("Br(J/#psi#rightarrow invisible)/Br(J/#psi#rightarrow#mu^{+}#mu^{-})");
  h_gaus->GetYaxis()->SetTitle("Likelihood(arbitrary unit)");
  
  h_gaus->GetXaxis()->CenterTitle();
  h_gaus->GetYaxis()->CenterTitle();
  
  h_gaus->GetXaxis()->SetNdivisions(505);
  h_gaus->GetYaxis()->SetNdivisions(505);

  
  // For drawing
  TH1F *h_gaus_shaded = new TH1F("hgaus_shaded", "hgaus_shaded", 23000, -0.006, 0.017);
  for(int i=0;i<23000;i++)
    { 
      // For Integral
      if(mu_t[i]>=0.0 && CL_mu > mu_t[i])
	{
	  h_gaus_shaded->SetBinContent(i+1,Prob[i]);
	}
      else
	{
	  h_gaus_shaded->SetBinContent(i+1,0.0);
	}
    }
  h_gaus_shaded->Draw("same");
  h_gaus_shaded->SetFillColor(kGreen-8);
  h_gaus->Draw("same");
  h_gaus->SetLineColor(1);
  h_gaus_shaded->SetLineColor(1);

  std::stringstream cl_mu_num;
  cl_mu_num << "C.L.(90%) = " <<  CL_mu;
  
  TLatex t_ul;
  t_ul.SetTextSize(0.05);
  t_ul.SetTextFont(20);  
  t_ul.SetTextAlign(12);   
  t_ul.DrawLatex(0.004, hmax*0.9, cl_mu_num.str().c_str());

  MyC_tmp->Print("UL.eps");
  
  return 0;
}
