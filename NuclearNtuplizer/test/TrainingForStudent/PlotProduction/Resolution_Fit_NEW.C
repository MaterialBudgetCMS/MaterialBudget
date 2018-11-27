#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1.h>
#include "TAxis.h"
#include <TMatrixD.h>
#include <iostream>     // std::cout
#include <algorithm>    // std::max
#include <TMath.h>
#include <math.h>
#include "Fit/BinData.h"
#include <TF1.h>
#include <TROOT.h>
#include <string>
#include <TMinuit.h>
#include <TLine.h>
#include <stdlib.h>
#include <TSystem.h>
#include <sstream>
#include <TPaveStats.h>
#include <TLegend.h>
#include <TKey.h>
#include <TFile.h>
#include <TClass.h>
#include <Math/Minimizer.h>

TH1D* res_TH1D_TF1(TH1D* hist, TF1* fit_func, char Option)
{
    bool redo = false;
    int Bins=hist->GetNbinsX();  
    string name = "res_";
    string histname = hist->GetName();
    name+=histname;
    TH1D* res_hist = new TH1D(name.c_str(),name.c_str(),Bins,hist->GetXaxis()->GetXmin(),hist->GetXaxis()->GetXmax());
    res_hist->SetEntries(hist->GetEntries());
    res_hist->Sumw2();
    res_hist->SetLineColor(kBlack);
    res_hist->SetBinContent(1,0.0); //underflow bin
    for(int i=1; i <= Bins; i++)
    { 
       if(Option == 'C')
       {
	double res_val = 1.0-((fit_func->Eval(hist->GetBinCenter(i)))-hist->GetBinContent(i));
	if(hist->GetBinError(i) != 0.0)
	{
	 res_val = res_val/hist->GetBinError(i);
	}
	else
	{
	 res_val = 0.0;
	}
        res_hist->SetBinContent(i,res_val);
       }
       else
       {
	if(fit_func->Eval(hist->GetBinCenter(i)) != 0.0)
	{
	 res_hist->SetBinContent(i,hist->GetBinContent(i)/fit_func->Eval(hist->GetBinCenter(i)));
	 res_hist->SetBinError(i,hist->GetBinError(i)/fit_func->Eval(hist->GetBinCenter(i)));
	}
	else
	{
	 res_hist->SetBinContent(i,0.0);
	}
       }
    }
    for(int i=0; i < Bins; i++)
    {
     if(res_hist->GetBinContent(i) == 0 && res_hist->GetBinContent(i) == 0)
     {
	double res_val = hist->GetBinContent(i);
	if(fit_func->Eval(hist->GetBinCenter(i)) != 0.0)
	{
	 res_val = res_val/fit_func->Eval(hist->GetBinCenter(i));
	}
	else
	{
	 res_val = 0.0;
	}
     }
    }
    //if the first, last, and middle bin are zero then likely that the whole histogram has zeros
    if(res_hist->GetBinContent(1) == 0.0 && res_hist->GetBinContent(Bins-1) == 0.0 && res_hist->GetBinContent(Bins/2) == 0.0)
     {
      redo = true;
     }
     if(redo)
     {
      //adjust parameter by some machine precision to avoid zeros again
      TF1* func_test = (TF1*) fit_func->Clone("test");
      func_test->SetParameter(2,fit_func->GetParameter(2)+1E8);
      for(int i=0; i < Bins; i++)
      {
	double res_val = hist->GetBinContent(i);
	if(func_test->Eval(hist->GetBinCenter(i)) != 0.0)
	{
	 res_val = res_val/func_test->Eval(hist->GetBinCenter(i));
	}
	else
	{
	 res_val = 0.0;
	}       
      }
     }    
    return res_hist;
}

int getPrecision(double num)
{
 string num_str = std::to_string(num);
 num_str.erase ( num_str.find_last_not_of('0') + 1, std::string::npos );
 int pre = 0;
 bool point = false;
 int num_str_length = num_str.length();
 for(int i=0; i<num_str_length; i++)
 {
  if(point)
  {
   pre++;
  }
  if(num_str.at(i) == '.')
  {
   point = true;
  }
 }
 return pre;
}

double toPrecision(double num, int n) 
{
    //https://stackoverflow.com/questions/202302/rounding-to-an-arbitrary-number-of-significant-digits

    if(num == 0) {
      return 0.0;
    }

    double d = std::ceil(std::log10(num < 0 ? -num : num));
    int power = n - (int)d;
    double magnitude = std::pow(10., power);
    long shifted = std::round(num*magnitude);

    std::ostringstream oss;
    oss << shifted/magnitude;
    string num_str = oss.str();
    return atof(num_str.c_str());
}

void Rounding(double sigma68_abs_err, double sigma68_rel_err, double sigma68, TString& landau_sigma68_tstr, TString& landau_rel_err_tstr)
{
  string landau_sigma68_start = "Landau #sigma68% = ";
  char landau_sigma68_char[50];
  char landau_sigma68_err_char[50];
  string pm = " #pm ";
  string units = " #mum";
  string landau_rel_err = "Relative Error = ";
  string format_sprintf = "%.";
  format_sprintf+="lf";
  int scale = 1000.0;
 if(sigma68_abs_err > 0.001)
 {
  sigma68_abs_err = toPrecision(sigma68_abs_err,2);
  int precision =  getPrecision(sigma68_abs_err); //get number of places after decimal point
  sigma68 = toPrecision(sigma68,precision);
  sigma68=sigma68*scale;
  sigma68_abs_err=sigma68_abs_err*scale;
  precision = getPrecision(sigma68_abs_err);
  string precision_str = std::to_string(precision);
  format_sprintf+=precision_str;
 
  sprintf(landau_sigma68_char, format_sprintf.c_str(), sigma68);
 

  sprintf(landau_sigma68_err_char, format_sprintf.c_str(), sigma68_abs_err);

  landau_sigma68_start += landau_sigma68_char;
  landau_sigma68_start += pm;
  landau_sigma68_start += landau_sigma68_err_char; 
  landau_sigma68_start += units; 
  landau_sigma68_tstr = landau_sigma68_start;
 }
 else
 {
  sigma68_abs_err = toPrecision(sigma68_abs_err,1);
  int precision =  getPrecision(sigma68_abs_err); //get number of places after decimal point
  sigma68 = toPrecision(sigma68,precision);
  sigma68=sigma68*scale;
  sigma68_abs_err=sigma68_abs_err*scale;
  precision = getPrecision(sigma68_abs_err);
  string precision_str = std::to_string(precision);
  format_sprintf+=precision_str;
 
  sprintf(landau_sigma68_char, format_sprintf.c_str(), sigma68);
 
  sprintf(landau_sigma68_err_char, format_sprintf.c_str(), sigma68_abs_err);

  landau_sigma68_start += landau_sigma68_char;
  landau_sigma68_start += pm;
  landau_sigma68_start += landau_sigma68_err_char; 
  landau_sigma68_start += units; 
 }
  char landau_sigma68_rel_char[50];
  sprintf(landau_sigma68_rel_char, "%.1lf", sigma68_rel_err*100.0);
  landau_sigma68_start += " (";
  landau_sigma68_start += landau_sigma68_rel_char;
  landau_sigma68_start += "%)";
  landau_rel_err+=landau_sigma68_rel_char;
  string per = "%";
  landau_rel_err+=per;
  landau_sigma68_tstr = landau_sigma68_start; 
  landau_rel_err_tstr = landau_rel_err;
}

TString set_limit_tstr(string parameter, double lower, double upper)
{
 char lower_char[50];
 sprintf(lower_char,"%.5lf",lower);
 char upper_char[50];
 sprintf(upper_char,"%.5lf",upper);

 string limit_str = parameter;
 limit_str += " Limits = ";
 limit_str += lower_char;
 limit_str += " -> ";
 limit_str += upper_char;
 TString limit_tstr = limit_str;
 return limit_tstr;
}

Double_t Fit_Landau(Double_t *x,Double_t *par)
{
 double norm = par[0];
 double mean = par[1];
 double sigma = par[2];

 return norm*TMath::Landau(x[0]-mean,sigma,0);
}

Double_t Fit_Cauchy(Double_t *x,Double_t *par)
{
   Double_t pi = TMath::Pi();
   Double_t norm = par[0];
   Double_t x0 = par[1];
   Double_t b = par[2];
   return norm*(b/(pi * ((x[0]-x0)*(x[0]-x0) + b*b)));
}

double GammaCalc(TH1D* hist, TF1* func, double PerpendicularFactor)
{
 double widthTest=0.0;
 double width=0.0;
 double widthP=0.0; //Gamma
 double range=100.0;
 int counts=0;
 std::cout <<"Max Landau/histo Value/2 = " << hist->GetMaximum()/2.0 << std::endl;
 for(int i=0; i<hist->GetMaximum()*100000; i++)
 {
  //break;
  if(i%100000==0)
  {
   //std::cout << "Looped Through: " << i*0.00001 << std::endl;
  }
  widthTest=func->Eval((i)*0.00001);
  if(widthTest<=((hist->GetMaximum()/2.0)+1.0/range) && widthTest>=((hist->GetMaximum()/2.0)-1.0/range))
  {
   widthP=i*0.00001; //Gamma
   counts++;
  }
  if(counts>0) break;
 }
 width=func->Eval(widthP);
 std::cout << "Width Value Checker  = " << width << std::endl;
 double integral=func->Integral(0.,100.0/PerpendicularFactor);
 std::cout << "Integral(0->100.0)=" << integral << std::endl;
 return widthP;
}

double sigma68calc(const TF1* fit, TH1D* hist, double PerpendicularFactor)
{
 TF1* fit_copy = new TF1();
 fit->Copy(*fit_copy);
 //calculate sigma at 68% for landau
 double integral=fit_copy->Integral(0.,100.0/PerpendicularFactor);
 double sigmaTest=0.0;
 double integralTest=0.0;
 double sigma68=0.0;
 int count=0;
 double sigma68value=integral*0.68;
 //std::cout << "68% of integral from 0->100.0 = " << sigma68value << std::endl;
 double ranges=1000.0;
 for(int i=0; i<hist->GetMaximum()*10000000; i++)
 { 
  //break;
  sigmaTest=i*0.000001;
  //if(sigmaTest>1.0/PerpendicularFactor) break;
  //if(sigmaTest<widthP) continue;
  integralTest=fit_copy->Integral(0.0,sigmaTest);
  /*if(i%10000 == 0 )
  {
   std::cout << "Looped Through sigma = " << sigmaTest << std::endl;
  }*/
  if(integralTest<=(sigma68value+1.0/ranges) && integralTest>=(sigma68value-1.0/ranges))
  {
   count++;
   sigma68=sigmaTest;
  }
  if(count>0) break;
  }
 sigma68 = abs(sigma68);
 return sigma68;
}

double sigma68errcalc(const TF1* fit,TH1D* hist,double sigma68,double PerpendicularFactor)
{
 TF1* fit_copy = new TF1();
 fit->Copy(*fit_copy);
 
 //cout << "sigma 68 orig: " << sigma68 << endl;
 double par0 = fit->GetParameter(0);
 double par1 = fit->GetParameter(1);
 double par2 = fit->GetParameter(2);
 
 double par0err = fit->GetParError(0);
 double par1err = fit->GetParError(1);
 double par2err = fit->GetParError(2);
 
 fit_copy->FixParameter(0,par0);
 fit_copy->FixParameter(1,par1);
 fit_copy->FixParameter(2,par2);
 //double sigma68_check = sigma68calc(fit_copy,hist,PerpendicularFactor);
 //cout << "sigma68 unchanged: " << sigma68_check << endl;

 fit_copy->FixParameter(1,par1+par1err);
 double sigma68_MPV_plus = sigma68calc(fit_copy,hist,PerpendicularFactor);
 //cout << "sigma68 MPV Plus: " << sigma68_MPV_plus << endl; 
 
 fit_copy->FixParameter(1,par1-par1err);
 double sigma68_MPV_minus = sigma68calc(fit_copy,hist,PerpendicularFactor);
 //cout << "sigma68 MPV Minus: " << sigma68_MPV_minus << endl; 

 fit_copy->FixParameter(1,par1);
 
 fit_copy->FixParameter(2,par2+par2err);
 double sigma68_sigma_plus = sigma68calc(fit_copy,hist,PerpendicularFactor);
 //cout << "sigma68 sigma Plus: " << sigma68_sigma_plus << endl; 

 fit_copy->FixParameter(2,par2-par2err);
 double sigma68_sigma_minus = sigma68calc(fit_copy,hist,PerpendicularFactor);
 //cout << "sigma68 Sigma Minus: " << sigma68_sigma_minus << endl; 
 
 double delta_sigma68_MPV_plus = abs(sigma68-sigma68_MPV_plus);
 //cout << "Delta Sigma68 MPV Plus: " << delta_sigma68_MPV_plus << endl;
 
 double delta_sigma68_MPV_minus = abs(sigma68-sigma68_MPV_minus);
 //cout << "Delta Sigma68 MPV Minus: " << delta_sigma68_MPV_minus << endl;
 
 double delta_sigma68_sigma_plus = abs(sigma68-sigma68_sigma_plus);
 //cout << "Delta Sigma68 sigma Plus: " << delta_sigma68_sigma_plus << endl;
 
 double delta_sigma68_sigma_minus = abs(sigma68-sigma68_sigma_minus);
 //cout << "Delta Sigma68 sigma Minus: " << delta_sigma68_sigma_minus << endl;
 
 double delta_MPV_max, delta_sigma_max, MPV_min, sigma_min;
 
 if(delta_sigma68_MPV_plus > delta_sigma68_MPV_minus)
 {
  delta_MPV_max = delta_sigma68_MPV_plus;
 }
 else
 {
  delta_MPV_max = delta_sigma68_MPV_minus;
 }

 if(delta_sigma68_sigma_plus > delta_sigma68_sigma_minus)
 {
  delta_sigma_max = delta_sigma68_sigma_plus;
 }
 else
 {
  delta_sigma_max = delta_sigma68_sigma_minus;
 }
 
 if(sigma68_MPV_plus < sigma68_MPV_minus)
 {
  MPV_min = sigma68_MPV_plus;
 }
 else
 {
  MPV_min = sigma68_MPV_minus;
 }
 if(MPV_min == 0.0 && MPV_min == sigma68_MPV_plus)
 {
  MPV_min = sigma68_MPV_minus;
 }
 else if(MPV_min == 0.0 && MPV_min == sigma68_MPV_minus)
 {
  MPV_min = sigma68_MPV_plus;
 }

 if(sigma68_sigma_plus < sigma68_sigma_minus)
 {
  sigma_min = sigma68_sigma_plus;
 }
 else
 {
  sigma_min = sigma68_sigma_minus;
 }
 if(sigma_min == 0.0 && sigma_min == sigma68_sigma_plus)
 {
  sigma_min = sigma68_sigma_minus;
 }
 else if(sigma_min == 0.0 && sigma_min == sigma68_sigma_minus)
 {
  sigma_min = sigma68_sigma_plus;
 }

 //cout << "delta_MPV_max: " << delta_MPV_max << endl;
 //cout << "delta_sigma_max: " << delta_sigma_max << endl;
 //cout << "MPV_min: " << MPV_min << endl;
 //cout << "sigma_min: " << sigma_min << endl;


 double sigma68_rel_err = sqrt((delta_MPV_max/MPV_min)*(delta_MPV_max/MPV_min)+(delta_sigma_max/sigma_min)*(delta_sigma_max/sigma_min)); //relative error 
 delete fit_copy;
 return sigma68_rel_err;
}
 
double stat_error_calc(TH1* hist)
{
 double eff = 0.68;
 double N = hist->GetEntries();
 return sqrt((eff*(1.0-eff))/N);
 //return sqrt(N);
}

void ResolutionCalc(TH1* hist, double& sigma, double& sigmay, double& sigma_err)
{
 double entries68 = 0.68*hist->GetEntries();
 double count = 0.0;
 int NBins = hist->GetNbinsX();
 for(int i = 0; i < NBins; i++)
 {
  count += hist->GetBinContent(i+1);
  if(count >= entries68)
  {
   sigma = hist->GetBinCenter(i+1);
   sigmay = hist->GetBinContent(i+1);
   sigma_err = 0.5*hist->GetBinWidth(i+1);
   break;
  }
 }
}

TString LandauDrawing(TH1D* hist, double PerpendicularFactor, string filename, char Option)
{
 string histname = hist->GetName();

 string canvasname = histname;
 canvasname += "_canvas";
 if(Option == 'A')
 {
  canvasname+='A';
 }
 else if(Option == 'B')
 {
  canvasname+='B';
 }
 TCanvas* canvas = new TCanvas((canvasname).c_str(),(canvasname).c_str(),750,500);
 
 string padname = histname;
 padname += "_pad";
 if(Option == 'A')
 {
  padname+='A';
 }
 else if(Option == 'B')
 {
  padname+='B';
 }
 TPad* pad = new TPad((padname).c_str(),(padname).c_str(),0.0,0.3,1.0,1.0);
 pad->SetBottomMargin(0.95);
 //pad->SetLogy();
 pad->Draw();
 pad->cd(); 

 hist->Draw();

 TF1* landau_fit = new TF1("func_landau","landau");
 landau_fit->SetLineColor(kBlue);
 landau_fit->SetNpx(10000000); 
 double limit_factor = 2.0; //1.3
 double MPV_upper=limit_factor*hist->GetMean();
 double MPV_lower=-limit_factor*hist->GetMean();
 double sigma_upper=limit_factor*hist->GetRMS();
 double sigma_lower=0.0;
 
 if(Option == 'A')
 {
  filename+="A"; 
  landau_fit->SetParameter(0,5.0*hist->GetEntries());
  landau_fit->SetParameter(1,0.0);
  landau_fit->SetParameter(2,0.1*hist->GetRMS()); 
  hist->Fit(landau_fit,"EMR","SAMES",0.0,0.1*hist->GetXaxis()->GetXmax());
 } 
 else if(Option == 'B')
 {
  filename+="B";
  landau_fit->SetParameter(0,5.0*hist->GetNormFactor());
  landau_fit->SetParameter(1,0.0);
  landau_fit->SetParameter(2,0.1*hist->GetRMS());
  hist->Fit(landau_fit,"EMR","SAMES",0.1*hist->GetXaxis()->GetXmax(),hist->GetXaxis()->GetXmax());
 }
 else
 {
  //default
  /*
  landau_fit->SetParameter(0,5.0*hist->GetEntries());
  landau_fit->SetParameter(1,0.0);
  landau_fit->SetParameter(2,0.1*hist->GetRMS()); 
  */
  
  landau_fit->SetParameter(0,5.0*hist->GetEntries());
  landau_fit->SetParameter(1,0.0);
  landau_fit->SetParameter(2,0.1*hist->GetRMS()); 
  
  landau_fit->SetParLimits(1,MPV_lower,MPV_upper);
  landau_fit->SetParLimits(2,sigma_lower,sigma_upper);
  
  hist->Fit(landau_fit,"QEMR","SAMES",0.0,hist->GetXaxis()->GetXmax()); //add "W" to change "problems" to successful 
 }

 TString status = gMinuit->fCstatu;

 pad->Update();
 filename+=".png"; 

 TPaveStats *stats_landau = (TPaveStats*)hist->FindObject("stats");
 stats_landau->SetTextColor(kBlue);
 stats_landau->SetLineColor(kBlue);
 stats_landau->SetY1NDC(0.95);
 stats_landau->SetY2NDC(0.7);
 pad->Update(); 
 
 TString status_landau_leg = "Landau Status = ";
 status_landau_leg+=status;

 //double gamma = GammaCalc(hist, landau_fit, PerpendicularFactor);

 //std::cout << "Calculating Landau Sigma 68%" << std::endl;
 double sigma68 = sigma68calc(landau_fit, hist, PerpendicularFactor);

 if(sigma68 == 0.0)
 {
  cout << "\033[1;31mCheck Landau\033[0m\n" << endl;
 }
 //std::cout << "sigma68: " << sigma68 << endl;

 //std::cout << "Calculating Error on Landau Sigma 68%" << std::endl;

 double sigma68_rel_err = sigma68errcalc(landau_fit, hist, sigma68, PerpendicularFactor);
 double sigma68_abs_err = sigma68*sigma68_rel_err;

 TLine* landau_sigma_line = new TLine(sigma68,0.0,sigma68,landau_fit->Eval(sigma68));
 landau_sigma_line->SetLineColor(kBlue);
 landau_sigma_line->SetLineStyle(7);
 landau_sigma_line->SetLineWidth(2);
 landau_sigma_line->Draw("SAMES");
 pad->Update();


 //rounding sigma68 and errrors
 TString landau_sigma68_tstr="";
 TString landau_rel_err_tstr="";
 Rounding(sigma68_abs_err,sigma68_rel_err,sigma68,landau_sigma68_tstr,landau_rel_err_tstr);
 
 //limits text
 string par_name1 = landau_fit->GetParName(1);
 string par_name2 = landau_fit->GetParName(2);
 TString landau_limit_tstr1 = set_limit_tstr(par_name1, MPV_lower, MPV_upper); 
 TString landau_limit_tstr2 = set_limit_tstr(par_name2, sigma_lower, sigma_upper); 
 
 double sigma = 0.0;
 double sigmay = 0.0;
 double sigma_err_rel = 0.0;
 ResolutionCalc(hist,sigma,sigmay,sigma_err_rel);
 sigma_err_rel = stat_error_calc(hist);
 double sigma_err_abs = sigma_err_rel*sigma;
 TLine* sigma_line = new TLine(sigma,0.0,sigma,sigmay);
 sigma_line->SetLineColor(kRed);
 sigma_line->SetLineStyle(7);
 sigma_line->SetLineWidth(2);
 sigma_line->Draw("SAMES");
 canvas->Update();

 char sigma_char[50];
 sprintf(sigma_char,"%.0lf",10000.0*sigma);
 char sigma_err_abs_char[50];
 sprintf(sigma_err_abs_char,"%.0lf",10000.0*sigma_err_abs);
 char sigma_err_rel_char[50];
 sprintf(sigma_err_rel_char,"%.0lf",100.0*sigma_err_rel);
 string sigma_str = "Resolution (No Fit) = ";
 sigma_str += sigma_char;
 sigma_str += " ";
 sigma_str += "#pm ";
 sigma_str += sigma_err_abs_char;
 sigma_str += " #mum";
 sigma_str += " (";
 sigma_str += sigma_err_rel_char;
 sigma_str += "%)";

 TString sigma_tstr = sigma_str;

 pad->Update();
 TLegend* leg_landau = new TLegend(0.62,0.3,0.98,0.7,"");
 leg_landau->SetFillColor(kWhite);
 leg_landau->SetTextColor(kBlue);
 leg_landau->AddEntry((TObject*)0, status_landau_leg, "");
 leg_landau->AddEntry((TObject*)0, landau_sigma68_tstr, "");
 leg_landau->AddEntry((TObject*)0, landau_limit_tstr1, "");
 leg_landau->AddEntry((TObject*)0, landau_limit_tstr2, "");
 leg_landau->AddEntry((TObject*)0, sigma_tstr, "");
 leg_landau->Draw("SAMES");

 /* 
 pad->Update();
 TString filename_tstr = filename;
 TLegend* leg_landau_name = new TLegend(0.4,0.3,0.98,0.5,"");
 leg_landau_name->SetFillColor(kWhite);
 leg_landau_name->SetTextColor(kBlue);
 leg_landau_name->AddEntry((TObject*)0, filename_tstr, "");
 leg_landau_name->Draw("SAMES");
 */

 pad->Update(); 
 canvas->cd();
 string padname_res = histname;
 padname_res += "_pad_res";
 if(Option == 'A')
 {
  padname_res+='A';
 }
 else if(Option == 'B')
 {
  padname_res+='B';
 }
 TPad* pad_res = new TPad((padname_res).c_str(),(padname_res).c_str(),0.0,0.05,1.0,0.3);
 pad_res->Draw();
 pad_res->cd();
 pad_res->SetTopMargin(0.05);
 pad_res->Update();
 canvas->Update();
 TH1D* res_hist = res_TH1D_TF1(hist, landau_fit, Option);
 res_hist->GetXaxis()->SetLabelSize(0.1);
 res_hist->GetYaxis()->SetLabelSize(0.1);
 res_hist->Draw();
 pad_res->Update();
 TLine* res_hist_one_line = new TLine(res_hist->GetXaxis()->GetXmin(),1.0,res_hist->GetXaxis()->GetXmax(),1.0);
 res_hist_one_line->SetLineColor(kBlack);
 res_hist_one_line->SetLineStyle(7);
 res_hist_one_line->SetLineWidth(2);
 res_hist_one_line->Draw("SAMES");
 pad_res->Update();
 canvas->Update();
 canvas->SaveAs(filename.c_str());
 //delete everything
 delete landau_sigma_line;
 delete sigma_line;
 delete leg_landau;
 delete landau_fit;
 delete hist;
 delete pad;
 delete res_hist;
 delete res_hist_one_line;
 delete pad_res;
 delete canvas;
 return status;
}

vector<TH1*> list_histos(const char *fname)
{
 std::vector<TH1*> vect_hist;
 TKey *key;
 TFile *f = TFile::Open(fname,"READ");
 string skip = "Inner_EndCap"; //default skip
 string skip_new1 = "Parallel_Inner_Barrel";
 string skip_new2 = "Perpendicular_Inner_Barrel";
 string skip_new3 = "Parallel_Outer_Barrel";
 string skip_new4 = "Perpendicular_Outer_Barrel";
 string skip_new5 = "Parallel_Outer_EndCap";
 string skip_new6 = "Perpendicular_Outer_EndCap";
 bool pass = false;
 if(!f || f->IsZombie())
 {
  cout << "Unable to open " << fname << " for reading..." << endl;
  return vect_hist;
 }
 TIter next((TList *)f->GetListOfKeys());
 while((key = (TKey *)next()))
 {
  TClass *cl = gROOT->GetClass(key->GetClassName());
  if(cl->InheritsFrom("TH1"))
  {
   TH1 *h = (TH1*)key->ReadObj();
   string name = h->GetName();
   //if(name.find(skip) != std::string::npos) continue;
   if(name.find(skip_new1) != std::string::npos) {pass = true;}
   else if(name.find(skip_new2) != std::string::npos) {pass = true;}
   else if(name.find(skip_new3) != std::string::npos) {pass = true;}
   else if(name.find(skip_new4) != std::string::npos) {pass = true;}
   else if(name.find(skip_new5) != std::string::npos) {pass = true;}
   else if(name.find(skip_new6) != std::string::npos) {pass = true;}
   if(pass)
   {
    vect_hist.push_back(h);
    pass = false;
   }
    pass = false;
   }
 }
 return vect_hist;
}

void Results (std::vector<TString> vect_status_landau)//, std::vector<TString> vect_status_cauchy)
{
/*
cout << endl << "FIT RESULTS Cauchy" << endl;
int success_cauchy = 0;
int problems_cauchy = 0;
int failed_cauchy = 0;
int failure_cauchy = 0;
int call_limit_cauchy = 0;

for(int i=0; i<vect_status_cauchy.size(); i++)
{
 if(vect_status_cauchy[i] == "SUCCESSFUL")
 {
  success_cauchy++;
 }
 if(vect_status_cauchy[i] == "PROBLEMS  ")
 {
  problems_cauchy++;
 }
 if(vect_status_cauchy[i] == "FAILED    ")
 {
  failed_cauchy++;
 }
 if(vect_status_cauchy[i] == "FAILURE   ")
 {
  failure_cauchy++;
 }
 if(vect_status_cauchy[i] == "CALL LIMIT")
 {
  call_limit_cauchy++;
 }
}
 
 cout << "Total Successful fits = " << success_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*success_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Problems fits = " << problems_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*problems_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Failed fits = " << failed_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*failed_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Failure fits = " << failure_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*failure_cauchy/vect_status_cauchy.size()) << "%" << endl; 
 cout << "Total Call Limit fits = " << call_limit_cauchy << "/" << vect_status_cauchy.size() << " or " << 100.0*(1.0*call_limit_cauchy/vect_status_cauchy.size()) << "%" << endl;
 cout << "Total Fits = " << success_cauchy+problems_cauchy+failed_cauchy+failure_cauchy+call_limit_cauchy << "/" << vect_status_cauchy.size() << endl;
 */

cout << endl << "FIT RESULTS Landau" << endl;
int success_landau = 0;
int problems_landau = 0;
int failed_landau = 0;
int failure_landau = 0;
int call_limit_landau = 0;
int ok_landau = 0;
int not_posdef_landau = 0;
int converged_landau = 0;

int vect_status_landau_size = vect_status_landau.size();
for(int i=0; i<vect_status_landau_size; i++)
{
 if(vect_status_landau[i] == "NOT POSDEF")
 {
  not_posdef_landau++;
 }
 else if(vect_status_landau[i] == "OK        ")
 {
  ok_landau++;
 }
 else if(vect_status_landau[i] == "SUCCESSFUL")
 {
  success_landau++;
 }
 else if(vect_status_landau[i] == "PROBLEMS  ")
 {
  problems_landau++;
 }
 else if(vect_status_landau[i] == "FAILED    ")
 {
  failed_landau++;
 }
 else if(vect_status_landau[i] == "FAILURE   ")
 {
  failure_landau++;
 }
 else if(vect_status_landau[i] == "CALL LIMIT")
 {
  call_limit_landau++;
 }
 else if(vect_status_landau[i] == "CONVERGED ")
 {
  converged_landau++;
 }
}
 cout << "Total Successful fits = " << success_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*success_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total Problems fits = " << problems_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*problems_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total Failed fits = " << failed_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*failed_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total Failure fits = " << failure_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*failure_landau/vect_status_landau.size()) << "%" << endl; 
 cout << "Total Call Limit fits = " << call_limit_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*call_limit_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total OK fits = " << ok_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*ok_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total NOT POSDEF fits = " << not_posdef_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*not_posdef_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total Converged fits = " << converged_landau << "/" << vect_status_landau.size() << " or " << 100.0*(1.0*converged_landau/vect_status_landau.size()) << "%" << endl;
 cout << "Total Acceptable Fits = " << success_landau+ok_landau+converged_landau << "/" << vect_status_landau.size() << endl; 
 cout << "Total Number of Fits = " << success_landau+problems_landau+failed_landau+failure_landau+call_limit_landau+ok_landau+not_posdef_landau+converged_landau << "/" << vect_status_landau.size() << endl; 

 cout << endl;

}

void Resolution_Fit_NEW(){

Long64_t start = gSystem->Now();
cout << endl << endl << endl << endl;

//ROOT::Math::MinimizerOptions::SetDefaultTolerance(1);
//int numcalls = 10000;
//ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(numcalls); //change "call limit" to "failure"


std::vector<TString> vect_status_landau;
std::vector<TString> vect_status_landauA;
std::vector<TString> vect_status_landauB;
//std::vector<TString> vect_status_cauchy;

gROOT->Clear();
gStyle->SetOptStat(0);
gStyle->SetOptFit(1111);
gStyle->SetPalette(1);
gStyle->SetOptTitle(0);
string fname;

for(int k = 0; k < 6; k++) //k < 6 to run over all files
{
 if(k==0)
 {
  fname = "ResolutionPlots_10GeV_2018.root";
 }
 if(k==1)
 {
  fname = "ResolutionPlots_50GeV_2018.root";
 }
 if(k==2)
 {
  fname = "ResolutionPlots_100GeV_2018.root";
 }
 if(k==3)
 {
  fname = "ResolutionPlots_2015_REPRO.root";
 }
 if(k==4)
 {
  fname = "ResolutionPlots_10GeV_2015.root";
 }
 if(k==5)
 {
  fname = "ResolutionPlots_100GeV_2015.root";
 }
// open file:
std::vector<TH1*> vect_hist = list_histos(fname.c_str());
std::vector<string> vect_filename;

int vect_hist_size = vect_hist.size();
for (int i = 0; i < vect_hist_size; i++)
{
 string dir = "Resolution/";
 if(k == 0)
 { 
  dir += "10GeV_2018_Results/";
 }
 if(k == 1)
 { 
  dir += "50GeV_2018_Results/";
 }
 if(k == 2)
 { 
  dir += "100GeV_2018_Results/";
 }
 if(k == 3)
 {
  dir += "2015_Results/";
 }
 if(k == 4)
 {
  dir += "10GeV_2015_Results/";
 }
 if(k == 5)
 {
  dir += "100GeV_2015_Results/";
 }
 string filename = vect_hist[i]->GetName();
 dir += filename;
 vect_filename.push_back(dir);
}

for (int i = 0; i < vect_hist_size; i++)
{
 vect_hist[i]->GetXaxis()->SetTitle("DeltaR [cm]");
 vect_hist[i]->GetYaxis()->SetTitle("Number Of Events");
 vect_hist[i]->SetLineColor(kBlack);
 cout << endl << "Fitting " << vect_hist[i]->GetName() << "   (" << (i+1) << "/" << vect_hist.size() << ")" << endl;
 string histname = vect_hist[i]->GetName();
 string perp = "Perpendicular";
 double PerpendicularFactor;
 if(histname.find(perp) != std::string::npos)
 {
  PerpendicularFactor=10.0;
 }
 else
 {
  PerpendicularFactor=1.0;
 }

 //Landau
 //cout << endl << "Fit Landau" << endl;
 TH1D* vect_hist_clone = (TH1D*)(vect_hist[i]->Clone());
 TH1D* vect_hist_cloneA = (TH1D*)(vect_hist[i]->Clone());
 TH1D* vect_hist_cloneB = (TH1D*)(vect_hist[i]->Clone());
 string histnameA = histname + "A"; 
 string histnameB = histname + "B"; 
 vect_hist_cloneA->SetName(histnameA.c_str());
 vect_hist_cloneB->SetName(histnameB.c_str());

 char FitOption = '.'; //Default
 char FitOptionA = 'A';
 char FitOptionB = 'B';

 TString status_landau = LandauDrawing(vect_hist_clone,PerpendicularFactor,vect_filename[i],FitOption);
 vect_status_landau.push_back(status_landau);
 
 /*
 cout << "Redoing Fit with Option A" << endl; 
 TString optionA = LandauDrawing(vect_hist_cloneA,PerpendicularFactor,vect_filename[i],FitOptionA);
 vect_status_landauA.push_back(optionA);
 
 cout << "Redoing Fit with Option B" << endl; 
 TString optionB = LandauDrawing(vect_hist_cloneB,PerpendicularFactor,vect_filename[i],FitOptionB);
 vect_status_landauB.push_back(optionB);
 */
 //Cauchy
 /*
 TF1 *func = new TF1("func", Fit_Cauchy, 0.0, 0.95*vect_hist[i]->GetXaxis()->GetXmax(), 3);
 
 func->SetParameter(0,0.5*vect_hist[i]->GetNormFactor());
 func->SetParameter(1,0.0);
 func->SetParameter(2,0.07*vect_hist[i]->GetRMS());

 //func->SetParLimits(0,0.0,10000.0);
 //func->SetParLimits(1,-1.0,0.5/PerpendicularFactor);
 func->SetParLimits(2,0.0,10.0);

 func->SetParName(0,"norm");
 func->SetParName(1,"mean");
 func->SetParName(2,"gamma");

 vect_hist[i]->SetLineColor(kBlack);

 //cout << endl << "Fit Cauchy" << endl;

 //func->SetLineColor(kRed); 
 //func->SetLineColorAlpha(kRed,0.0); 
 //vect_hist[i]->Fit(func,"QEMR");

 //TString status_cauchy = gMinuit->fCstatu;
 //vect_status_cauchy.push_back(status_cauchy);

 //func->Draw("SAMES");

 vect_canvas[i]->Update();

 TPaveStats *stats_cauchy = (TPaveStats*)vect_hist[i]->GetListOfFunctions()->FindObject("stats");
 stats_cauchy->SetTextColor(kRed);
 stats_cauchy->SetLineColor(kRed);
 stats_cauchy->SetY1NDC(0.9);
 stats_cauchy->SetY2NDC(0.7);
 //stats_cauchy->Draw("SAMES");
 vect_canvas[i]->Update(); 
*/
 //TString status_cauchy_leg = "Cauchy Status = ";
 //status_cauchy_leg+=status_cauchy;

/* double cauchy_sigma68 = abs(func->GetParameter(2)*TMath::Tan(0.34*TMath::Pi())+func->GetParameter(1));
//if(cauchy_sigma68 > (1.0/PerpendicularFactor))
if(cauchy_sigma68 == 0.0)
{
 cout << "\033[1;31mCheck Cauchy\033[0m\n " << cauchy_sigma68 << endl;
}

//cout << "Cauchy Sigma68 = " << cauchy_sigma68 << endl;

TLine* cauchy_sigma_line = new TLine(cauchy_sigma68,0.0,cauchy_sigma68,func->Eval(cauchy_sigma68));
cauchy_sigma_line->SetLineColor(kRed);
cauchy_sigma_line->SetLineStyle(2);
cauchy_sigma_line->SetLineWidth(2);
//cauchy_sigma_line->Draw("SAMES");
vect_canvas[i]->Update();

TLine* cauchy_gamma_line = new TLine(func->GetParameter(2),0.0,func->GetParameter(2),func->Eval(func->GetParameter(2)));
cauchy_gamma_line->SetLineColor(kGreen+2);
cauchy_gamma_line->SetLineStyle(5);
cauchy_gamma_line->SetLineWidth(2);
cauchy_gamma_line->Draw("SAMES");
vect_canvas[i]->Update();
*/
 //string cauchy_sigma68_start = "Cauchy #sigma68% = ";

 //char cauchy_sigma68_char[50];
 //sprintf(cauchy_sigma68_char, "%.0lf", cauchy_sigma68*10000.0);
/*
  cauchy_sigma68_start += cauchy_sigma68_char;
  cauchy_sigma68_start += units; 
  TString cauchy_sigma68_tstr = cauchy_sigma68_start;
 */
/*
  TLegend* leg_cauchy = new TLegend(0.55,0.3,0.98,0.4,"");
  leg_cauchy->SetTextFont(42);
  leg_cauchy->SetTextSize(0.04);
  leg_cauchy->SetFillColor(kWhite);
  leg_cauchy->SetTextColor(kRed);
  leg_cauchy->AddEntry((TObject*)0, status_cauchy_leg, "");
  leg_cauchy->AddEntry((TObject*)0, cauchy_sigma68_tstr, "");
  leg_cauchy->Draw("SAMES");
 */
 }
}
 cout << "Default Fit Results" << endl;
 Results(vect_status_landau);//, vect_status_cauchy);
 //cout << "Option A Results" << endl;
 //Results(vect_status_landauA);
 //cout << "Option B Results" << endl;
 //Results(vect_status_landauB);
 Long64_t end = gSystem->Now();
 cout << "Time to process = " << (end-start)/1000.0 << " seconds" << endl;
}

