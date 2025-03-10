#include <TROOT.h>
#include <TH2D.h>
#include <TMath.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <stdio.h>      /* printf */
#include <math.h>       /* pow */
#include <iostream>

// Evolved version of MergeHisto in which the scan voltage between 400 and 500 Mesh voltage is taken into account

using namespace std;

double GetDivError(double nom, double denom, double nom_err, double denom_err){
  return TMath::Sqrt(((nom_err*nom_err) / (denom*denom) ) + (nom*nom * denom_err*denom_err)/(denom*denom*denom*denom));
}

double GetAddError(double err_x, double err_y){
  return TMath::Sqrt((err_x*err_x) + (err_y*err_y));
}




void MergeHistos_Scan(){

  //defining Stacks
  THStack *hsWFsum = new THStack("hsWF", " WF Sum (amplitudes higher than treshold);  Time [s]; Number of Photons ");
  double rebin_no = 5000;

  double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1e7 for 1650V (Hamamtsu R6427)
  double con_fact = - dt /(R* gain *e_ch*qe*col_eff);

  TString NSigmas = "4.0";
  std::vector<std::vector<TString>> path_store;

  path_store.push_back({});
  path_store[0].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh300_TPC1650/");  
  //
  path_store.push_back({});
  path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_TPC1650/");
  path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_ii_TPC1650_a/");
  path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_ii_TPC1650_b/");
  //
  //
  path_store.push_back({});
  // path_store[2].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh420_TPC1650/"); 
  path_store[2].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh420_TPC1650_a/"); 
  path_store[2].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh420_TPC1650_b/");


  path_store.push_back({});
  path_store[3].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh440_TPC1650_a/");
  
  path_store[3].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh440_TPC1650_b/");

  path_store.push_back({});
  
  path_store[4].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh460_TPC1650_a/");
  path_store[4].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh460_TPC1650_b/");



  path_store.push_back({});
  
  path_store[5].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh480_TPC1650_a/");
  path_store[5].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh480_TPC1650_b/");

  path_store.push_back({});
  path_store[6].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_TPC1650/");
  path_store[6].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_ii_TPC1650_a/");
  path_store[6].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_ii_TPC1650_b/");


  std::vector<std::vector<TFile*> > file_store (path_store.size(),std::vector<TFile*>(0));
  
  std::vector<std::vector<double> > HowManySignalEvt_ind(path_store.size(),std::vector<double>(0));
  std::vector<std::vector<double> > HowManyEmptyEvt_ind(path_store.size(),std::vector<double>(0));
  std::vector<std::vector<double> > HowManySparkEvt_ind(path_store.size(),std::vector<double>(0));

  std::vector<double> HowManySignalEvt(path_store.size(),0);
  std::vector<double> HowManyEmptyEvt(path_store.size(),0);
  std::vector<double> HowManySparkEvt(path_store.size(),0);



  std::vector<std::vector<TH1D*> > hWFsumFlat_ind_st(path_store.size(),std::vector<TH1D*>(0));
  std::vector<std::vector<TH1D*> > hWFsumRaw_st(path_store.size(),std::vector<TH1D*>(0));
  std::vector<std::vector<TH1D*> > hWFsum_Ratio_st(path_store.size(),std::vector<TH1D*>(0));


  std::vector<int> color_st;
  color_st.push_back(30);// 4 = blue
  color_st.push_back(12);// 4 = blue
  color_st.push_back(17);// 4 = blue
  color_st.push_back(4);// 4 = blue
  color_st.push_back(2);// 2 = red
  color_st.push_back(1); // 1 = black
  color_st.push_back(7);// 7 = cyan
  color_st.push_back(6); //6 = magenta
  color_st.push_back(48);// 48 = rose
  color_st.push_back(12);// 48 = rose
  color_st.push_back(52);// 48 = rose
  color_st.push_back(14);// 48 = rose
  color_st.push_back(21);// 48 = rose
  color_st.push_back(27);// 48 = rose
  color_st.push_back(38);// 48 = rose
  color_st.push_back(39);// 48 = rose


  for (int i(0); i < path_store.size(); i++){
    for (int j(0); j < path_store.at(i).size(); j++ ){

      file_store[i].push_back(TFile::Open(path_store.at(i).at(j)+"WF_output_5000_"+NSigmas+"RMS.root"));
      auto tree = file_store.at(i).at(j)->Get<TTree>("T");
      hWFsumFlat_ind_st[i].push_back((TH1D*)file_store.at(i).at(j)->Get("hWFsum_FlatNorm"));
      hWFsumRaw_st[i].push_back((TH1D*)file_store.at(i).at(j)->Get("hWFsumRaw"));

      HowManySignalEvt_ind[i].push_back(tree->GetBranch("Signal")->GetEntries());
      HowManyEmptyEvt_ind[i].push_back(tree->GetBranch("Empty")->GetEntries());
      HowManySparkEvt_ind[i].push_back(tree->GetBranch("Spark")->GetEntries());


    }
  }

  for (int i(0); i<HowManySignalEvt_ind.size(); i++){
    for (int j(0); j<HowManySignalEvt_ind.at(i).size(); j++){
      HowManySignalEvt[i]+=HowManySignalEvt_ind.at(i).at(j);
      HowManyEmptyEvt[i]+=HowManyEmptyEvt_ind.at(i).at(j);
      HowManySparkEvt[i]+=HowManySparkEvt_ind.at(i).at(j);
    }
  }


  //------------------------------------------------------
  //--------Produce WF SUM--------------------------------
  //------------------------------------------------------



  std::vector<double> norm_st;

  std::vector<TH1D*> hWFsumFlat_st;

  for (int i(0); i< path_store.size(); i++){
    // TH1D* h1 = new TH1D("","",100000, -0.8e-3,0.2e-3);
    TH1D* h1 = hWFsumFlat_ind_st.at(i).at(0);
    double norm_dummy(0);

    for (int j(0); j< hWFsumFlat_ind_st.at(i).at(0)->GetNbinsX(); j++){
      double dummy =0;

      for (int z(0); z < path_store.at(i).size(); z++){

        dummy +=  hWFsumFlat_ind_st.at(i).at(z)->GetBinContent(j);
        if (j == 0) norm_dummy +=HowManySignalEvt_ind.at(i).at(z);

      }

      h1->SetBinContent(j,dummy/(HowManySignalEvt.at(i)) * (1/-0.049));//norm_dummy*con_fact


    }
    h1->SetLineColor(color_st.at(i));
    h1->SetLineWidth(3);
    hWFsumFlat_st.push_back(h1);


  }

  cout << "con fact " << 1/con_fact << endl;

  //-----------------------------------------------------------------
  //------------------------Obtain the SUM OF THE WF SUM !!----------
  // ----------------------------------------------------------------


  std::vector<double> ElGainTh(file_store.size(),0);
  std::vector<double> ElGainMonteiroMeas;
  std::vector<double> E_N_Monteiro;
  std::vector<double> RelElGainMonteiro_Meas;
  std::vector<double> E_N(file_store.size(),0);
  std::vector<double> V_PEN(file_store.size(),0);
  std::vector<double> V_PEN_Scan;
  std::vector<double> E_N_PEN_Scan;
  std::vector<double> RelElGainTh (file_store.size(),0);
  std::vector<double> RelElGainMeas_a (file_store.size(),0);
  std::vector<double> RelElGainMeas_a_ELcomp (file_store.size(),0);
  std::vector<double> RelElGainMeas_ab (file_store.size(),0);
  std::vector<double> AbsEL_Only (file_store.size(),0);
  std::vector<double> Err_AbsEL_Only (file_store.size(),0);

  int ThGEM_comp = 0;
  double ThGEM_avg_abs_yield = 0;

  std::vector <double> SumOfWFSum_a(file_store.size(), 0);
  std::vector <double> SumOfWFSum_ab(file_store.size(), 0);
  //
  //
  //

  //do the sum of the waveform sum

  for (int i(0); i < file_store.size(); i++){
    // cout << "size " <<  hWFsumFlat_st.at(i)->GetNbinsX()<< endl;
    for (int j(0); j < hWFsumFlat_st.at(i)->GetNbinsX(); j++){
      if ( -0.06e-3 < hWFsumFlat_st.at(i)->GetBinCenter(j) && hWFsumFlat_st.at(i)->GetBinCenter(j) <-0.02e-3  ) {
        SumOfWFSum_a.at(i) += hWFsumFlat_st.at(i)->GetBinContent(j);
      }

      if ( -0.02e-3 < hWFsumFlat_st.at(i)->GetBinCenter(j) && hWFsumFlat_st.at(i)->GetBinCenter(j) <0.02e-3  ){
        SumOfWFSum_ab.at(i) += hWFsumFlat_st.at(i)->GetBinContent(j);
      }
    }
    if (i < 5)   ThGEM_avg_abs_yield += SumOfWFSum_a[i];
    //
  }
  ThGEM_avg_abs_yield /=5;


  for (int i(0); i < file_store.size(); i++){
    AbsEL_Only[i] = SumOfWFSum_a[i]-ThGEM_avg_abs_yield;
  }

  cout << "The average photon yield for the ThGEM alone is: " << ThGEM_avg_abs_yield << endl;


  //-----------------------------------------------------------------
  //------------------------Treating Errors--------------------------
  // ----------------------------------------------------------------


  std::vector<double>err_IntgWFSum_a(file_store.size(),0);
  std::vector<double>err_IntgWFSum_ab(file_store.size(),0);
  std::vector<double>err_Ratio_a;
  std::vector<double>err_Ratio_ab;
  std::vector<double>empty_4(file_store.size(),0);
  std::vector<double>empty_3(file_store.size(),0);

  for (int i(0); i < SumOfWFSum_a.size(); i++){
    err_IntgWFSum_a[i] = TMath::Sqrt(SumOfWFSum_a[i]);
    err_IntgWFSum_ab[i] = TMath::Sqrt(SumOfWFSum_ab[i]);
  }
  int norm_term_monteiro = 8;
  int norm_term = 13;

  for (int i(0); i < SumOfWFSum_a.size(); i++){
    // if (i ==2 ) cotinue;
    err_Ratio_a.push_back(GetDivError(SumOfWFSum_a[i],SumOfWFSum_a[norm_term], err_IntgWFSum_a[i], err_IntgWFSum_a[norm_term]));
    err_Ratio_ab.push_back(GetDivError(SumOfWFSum_ab[i], SumOfWFSum_ab[norm_term], err_IntgWFSum_ab[i], err_IntgWFSum_ab[norm_term]));
    Err_AbsEL_Only[i] = GetAddError(err_IntgWFSum_a[i],err_IntgWFSum_a[ThGEM_comp]);

    // cout << "asdads " << GetDivError(SumOfWFSum_a[i],SumOfWFSum_a[norm_term], err_IntgWFSum_a[i], err_IntgWFSum_a[norm_term]) << "  ab " <<  GetDivError(SumOfWFSum_ab[i], SumOfWFSum_ab[0], err_IntgWFSum_ab[i], err_IntgWFSum_ab[0]) << endl;
  }



  cout << SumOfWFSum_a[0] <<  "  " << SumOfWFSum_a[1]<< " " << SumOfWFSum_a[2] << " " << SumOfWFSum_a[3] << endl;
  cout << SumOfWFSum_ab[0] <<  "  " << SumOfWFSum_ab[1]<< " " << SumOfWFSum_ab[2] << " " << SumOfWFSum_ab[3] << endl;
  cout << "Relative EL gain for drift period: "  << endl;
  cout << SumOfWFSum_a[0]/SumOfWFSum_a[norm_term] <<  "  " << SumOfWFSum_a[1]/SumOfWFSum_a[norm_term]<< " " << SumOfWFSum_a[norm_term]/SumOfWFSum_a[norm_term] << endl;
  cout << "Relative EL gain for ab period: "  << endl;
  cout << SumOfWFSum_ab[0]/SumOfWFSum_ab[norm_term] <<  "  " << SumOfWFSum_ab[1]/SumOfWFSum_ab[norm_term]<< " " << SumOfWFSum_ab[norm_term]/SumOfWFSum_ab[norm_term] << endl;



  //-----------------------------------------------------------------
  //----Plotting the relative SUM of the WF sum ---------------------
  // ----------------------------------------------------------------




  ElGainTh =  {0., 0., 0., 0.005,0.015,0.05,0.13,0.24,0.35,0.45,0.57,0.65,0.74,0.82,0.94};
  E_N = {0., 0.93,1.86, 2.79, 3.72,4.65,5.58,6.51,7.45,8.37,9.30,10.23,11.16,12.09,13.0};
  ElGainMonteiroMeas= {0.222,0.267,0.319,0.377,0.429,0.551, 0.680,0.745,0.822,0.996,1.074,1.170,1.261,1.364,1.474};
  E_N_Monteiro = {4.857,5.477,6.099,6.875,7.599,9.152,10.653,11.430,12.207,13.711,14.488,15.215,15.993,16.771,17.550};





  for (int i(0); i < ElGainMonteiroMeas.size(); i++){

    RelElGainMonteiro_Meas.push_back(ElGainMonteiroMeas.at(i)/ElGainMonteiroMeas.at(norm_term_monteiro));


  }





  //ElGainTh[11] = 0.99;//1450


  for (int i(0); i<file_store.size(); i++){
    RelElGainTh[i]= ElGainTh[i]/ ElGainTh[norm_term];
    RelElGainMeas_a[i] =SumOfWFSum_a[i]/SumOfWFSum_a[norm_term];

    RelElGainMeas_a_ELcomp[i] = AbsEL_Only[i]/AbsEL_Only[norm_term] ;
    RelElGainMeas_ab[i] =SumOfWFSum_ab[i]/SumOfWFSum_ab[norm_term];
  }
  std::vector<double>err_Ratio_a_ELcomp(SumOfWFSum_a.size(), 0);
  for (int i(0); i < SumOfWFSum_a.size(); i++){
    // if (i ==2 ) cotinue;
    err_Ratio_a_ELcomp[i] =err_Ratio_a[i]+err_Ratio_a[ThGEM_comp];

  }





  V_PEN = {0., 100, 200, 300, 400, 500,600,700,800,900,1000,1100,1200,1300,1400};
  V_PEN_Scan = { 300, 400, 420, 440, 460, 480, 500};
  double conv_e_n = 0.93;// 100 V on the pen mesh = 0.93 Td.
  E_N_PEN_Scan = { 3*conv_e_n, 4*conv_e_n, 4.2*conv_e_n, 4.4*conv_e_n, 4.60*conv_e_n, 4.80*conv_e_n, 5.00*conv_e_n};




  //-----------------------------------------------------------------
  //-----------------------------------------------------------------
  //------------------------Plots and Figure---------------------
  // ----------------------------------------------------------------
  //-----------------------------------------------------------------



  //-----------------------------------------------------------------
  //------------------------Plotting the WF Sums---------------------
  // ----------------------------------------------------------------
  cout << "hereasdasdadsasdakadskkasd" << endl;


  TCanvas * c_AbsYield = new TCanvas("Abs_Yield","", 800, 600);
  c_AbsYield->Divide(2,1);


  TGraphErrors *g_Abs_VPEN = new TGraphErrors(SumOfWFSum_a.size(), &V_PEN[0], &SumOfWFSum_a[0], &empty_4[0],&err_IntgWFSum_a[0]);
  TGraphErrors *g_ElAbs_VPEN = new TGraphErrors(AbsEL_Only.size(), &V_PEN[0], &AbsEL_Only[0], &empty_4[0],&Err_AbsEL_Only[0]);
  TGraphErrors *g_Abs = new TGraphErrors(SumOfWFSum_a.size(), &E_N[0], &SumOfWFSum_a[0], &empty_4[0],&err_IntgWFSum_a[0]);
  TGraphErrors *g_ElAbs = new TGraphErrors(AbsEL_Only.size(), &E_N[0], &AbsEL_Only[0], &empty_4[0],&Err_AbsEL_Only[0]);

  g_Abs ->SetLineColor(46);
  g_Abs ->SetLineWidth(2);
  g_Abs->SetFillColor(kBlack);
  g_Abs ->SetMarkerStyle(20);
  g_ElAbs -> SetLineColor(38);
  g_ElAbs ->SetLineWidth(2);


  g_Abs_VPEN ->SetLineColor(46);
  g_Abs_VPEN ->SetLineWidth(2);
  g_Abs_VPEN->SetFillColor(kBlack);
  g_Abs_VPEN ->SetMarkerStyle(20);
  g_ElAbs_VPEN -> SetLineColor(38);
  g_ElAbs_VPEN ->SetLineWidth(2);





  gStyle->SetOptFit(11111);
  TMultiGraph *mg_AbsYield = new TMultiGraph();
  mg_AbsYield->SetTitle(" ; Reduced Electric Field [E/N]; Photon Number");
  mg_AbsYield->Add(g_Abs,"ALP");
  mg_AbsYield->Add(g_ElAbs,"ALP");
  mg_AbsYield->Draw("ALP");


  TGaxis *axis1 = new TGaxis(0,1467,13,1467,0,1400,510,"-");
  axis1->SetTitle("Mesh Voltage [V]");
  axis1->SetLabelSize(0.03);
  axis1->SetTitleSize(0.03);
  axis1->SetTitleOffset(1.1);
    // gPad->DrawFrame(0.,1940.,1400.,1940);



  TMultiGraph *mg_AbsYield_VPEN = new TMultiGraph();
  mg_AbsYield_VPEN->SetTitle("; Mesh Voltage [V]; Photon Number");
  mg_AbsYield_VPEN->Add(g_Abs_VPEN,"ALP");
  mg_AbsYield_VPEN->Add(g_ElAbs_VPEN,"ALP");
  // mg_AbsYield_VPEN->Draw("ALP");
  // TF1  *f1 = new TF1("f1","(x-[0])[1]",0,10);
  TF1  *f1 = new TF1("f1","(x-[0])*[1]",0,2000);

  f1->SetParameters(400,1.2);
  g_ElAbs->Fit("f1","","", 3.8,14);

  axis1->Draw("same");
  gPad->SetGrid();



  auto leg_AbsYield = new TLegend(0.1,0.7,0.48,0.9);
  leg_AbsYield->AddEntry(g_Abs,"ThGEM + EL ","l");//800
  leg_AbsYield->AddEntry(g_ElAbs,"EL Only ","l");//800
  leg_AbsYield->Draw();
  c_AbsYield->Write();


  TCanvas * c_Yield = new TCanvas("Yield","", 1200, 600);
  c_Yield->Divide(2,1);







}
