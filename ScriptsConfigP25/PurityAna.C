//This is a code very similar to the MergeHisto code series in which the yield of several line is plotted on the same graph.
// This code is intended to study the only 3 mesh point per line: -100, 0 and 100V. 
// Each line set is taken at a very constant gas purity level. first set is taken at 10 ppm O2, 50 ppm P2. 
// Second data set is taken a????

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


//I want a function which takes h1

using namespace std;


double GetE_N(double potential, double dist, double p){  
  //   // gas parameteres
  double n(0.);
  //  double p(100000); //pressure in Pa
  double N0(6.022e23);
  double R(8.3145);//J/mol/K
  double T(293.);//K
  
  //Geometry
  //double dist = 0.1;// in cm (distance between the electrodes)
  //  double potential  = 1400; // in Volts.
  
  //conversion factor
  double cm_unit = 1e-6;
  double toTd = 1e-17;
  n = p*N0/(R*T)*cm_unit;
  

  //    std::cout << " The number density is " << n << " atom/cm3"<<  std::endl;
  // std::cout << " This is the number which appears in the excel formula" <<1/ (n*toTd) << " atom/cm3"<<  std::endl;

//   std::cout << " The reduced electric field is " << potential/dist/n/toTd << "Td" << std::endl;
  
//   std::cout << " ---------------------------------- " << std::endl;
  
  return potential/dist/n/toTd;

  }

std::vector<double> GetMean_STD_NEntries(std::vector<double> & intg_a_values){
    
    auto v = intg_a_values;
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    double mean = sum / v.size(); 
    
    std::vector<double> diff(v.size());
    std::transform(v.begin(), v.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
    double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / v.size());
    
    std::vector<double> dummy(3,0);
    dummy[0] = mean;
    dummy[1] = stdev;
    dummy[2] = v.size();
    
    return dummy;

  }

  

double GetDivError(double nom, double denom, double nom_err, double denom_err){
  return TMath::Sqrt(((nom_err*nom_err) / (denom*denom) ) + (nom*nom * denom_err*denom_err)/(denom*denom*denom*denom));
}

double GetAddError(double err_x, double err_y){
  return TMath::Sqrt((err_x*err_x) + (err_y*err_y));
}


double GetAvgError(std::vector<double> *error_vect = NULL){
  double dummy(0);
  for (int i(0); i < error_vect->size(); i++){
    dummy+= error_vect->at(i)* error_vect->at(i);
  }


  return TMath::Sqrt(dummy)/error_vect->size();
}



void PurityAna(){

  gROOT->SetStyle("Plain");
  //defining Stacks
  THStack *hsWFsum = new THStack("hsWF", " WF Sum (amplitudes higher than treshold);  Time (#mus); Equivalent Number of Photons ");

  double rebin_no = 5000;
  double const R(50.),gain_1650(1e7) , gain(2.9e6), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1.21e7 for 1650V (Hamamtsu R6427), gain = 2.9e6 for 1370V
  //double phot_to_volt =1/( - dt /(R* gain *e_ch*qe*col_eff));// formula from my point of view
  double phot_to_volt =1/( - dt /(R* gain *e_ch));// formula from Federico's point of view
  double con_fact_P24 = phot_to_volt;// -0.05;
  //double con_fact_P25 = 1/( - dt /(R* gain_1650 *e_ch));
  double con_fact_P25 = -0.037;



  TString NSigmas = "4.0";
  std::vector<std::vector<TString>> path_store;

  
  
  std::vector<double> abs_gain_10ppm;
  std::vector<double> pen_mesh_10ppm = {-100, 0., 50};
  std::vector<double> temp_mesh_10ppm = {17.83, 16.91, 17.};
  std::vector<double> h2o_mesh_10ppm = { 50.7, 49.5, 50.5};
  std::vector<double> o2_mesh_10ppm = {9.6, 9.2, 9.1};
  
  std::vector<double> E_N_mesh_10ppm;
  
  std::vector<double> abs_gain_24ppm;
  std::vector<double> pen_mesh_24ppm = {-100., 0., 50.} ;
  std::vector<double> E_N_mesh_24ppm;  


  std::vector<double> abs_gain_44ppm;
  std::vector<double> pen_mesh_44ppm = {-100., 0., 50.} ;
  std::vector<double> E_N_mesh_44ppm;    
  
  
  
  cout << " asdasasd " << endl;
  std::vector<TString> evt_num;
  
  int ds_10ppm = pen_mesh_10ppm.size(); // number of data sets taken at p1 
  int ds_24ppm = pen_mesh_24ppm.size(); // number of data sets taken at p2_0
  int ds_44ppm = pen_mesh_44ppm.size(); // number of data sets taken at p2_0


  // 24 ppm files  
  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMeshNeg100_TPC1650_p2_0_iv/");
  evt_num.push_back("3938");

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMesh0_TPC1650_p2_0_vi/");
  evt_num.push_back("5000");

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMesh050_TPC1650_p2_0_iv/");
  evt_num.push_back("3045");
  



  // 10 ppm files

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMeshNeg100_TPC1650_p2_0_iii/");
  evt_num.push_back("5000");
  

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMesh0_TPC1650_p2_0_v/");
  evt_num.push_back("5000");

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMesh050_TPC1650_p2_0_iii/");
  evt_num.push_back("5000");




  // 44 ppm files

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMeshNeg100_TPC1650_p2_0_v/");
  evt_num.push_back("5000");
  

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMesh0_TPC1650_p2_0_vii/");
  evt_num.push_back("5000");

  path_store.push_back({});
  path_store.back().push_back("/srv/beegfs/scratch/users/a/amarinei/Swan_TTrees/Configuration_P25/Batch_2/C4600_LSF2550_ThGUp2250_ThGDnGND_PMesh050_TPC1650_p2_0_vi/");
  evt_num.push_back("5000");

  
  
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
  
  gStyle->SetPalette(kCividis);
  gStyle->SetPalette(kAlpine);
  gStyle->SetPalette(kBlueRedYellow);
  //gStyle->SetPalette(kGistEarth);
  //gStyle->SetPalette(kBrownCyan);
  //gStyle->SetPalette(kAtlantic);
  //gStyle->SetPalette(kLightTemperature);
  auto cols = TColor::GetPalette();
  //cout << "cols size: " << cols.size() << endl;
  //for (int i(0); i < path_store.size(); i++){
  // color_st.push_back(cols.At(i*17));
  // // cout << cols.At(i) << endl;
  //}
  color_st.push_back(30);// 4 = blue
  color_st.push_back(12);// 4 = blue
  color_st.push_back(17);// 4 = blue
  color_st.push_back(4); // 4 = blue
  color_st.push_back(2); // 2 = red

  color_st.push_back(1); // 1 = black
  color_st.push_back(7); // 7 = cyan
  color_st.push_back(6); //6 = magenta
  color_st.push_back(48);// 48 = rose
  color_st.push_back(12);// 48 = rose
  color_st.push_back(52);// 48 = rose
  color_st.push_back(14);// 48 = rose
  color_st.push_back(21);// 48 = rose
  color_st.push_back(27);// 48 = rose
  color_st.push_back(38);// 48 = rose
  color_st.push_back(39);// 48 = rose
  color_st.push_back(40);// 48 = rose
  color_st.push_back(41);// 48 = rose
  color_st.push_back(42);// 48 = rose
  color_st.push_back(1); // 1 = black
  color_st.push_back(7); // 7 = cyan
  color_st.push_back(6); //6 = magenta
  color_st.push_back(48);// 48 = rose
  color_st.push_back(12);// 48 = rose
  color_st.push_back(52);// 48 = rose
  color_st.push_back(14);// 48 = rose
  color_st.push_back(21);// 48 = rose
  color_st.push_back(27);// 48 = rose
  color_st.push_back(38);// 48 = rose
  color_st.push_back(39);// 48 = rose
  color_st.push_back(40);// 48 = rose
  color_st.push_back(41);// 48 = rose
  color_st.push_back(42);// 48 = rose
  color_st.push_back(1); // 1 = black
  color_st.push_back(7); // 7 = cyan
  color_st.push_back(6); //6 = magenta
  color_st.push_back(48);// 48 = rose
  color_st.push_back(12);// 48 = rose
  color_st.push_back(52);// 48 = rose
  color_st.push_back(14);// 48 = rose
  color_st.push_back(21);// 48 = rose
  color_st.push_back(27);// 48 = rose
  color_st.push_back(38);// 48 = rose
  

  cout << " p1 " << ds_10ppm << endl;
  cout << " p2_0 " << ds_24ppm << endl;
  

   
  for (int i(0); i < path_store.size(); i++){
    for (int j(0); j < path_store.at(i).size(); j++ ){
      
      file_store[i].push_back(TFile::Open(path_store.at(i).at(j)+"WF_output_" +evt_num.at(i) + "_"+NSigmas+"RMS.root"));      
     
      auto tree = file_store.at(i).at(j)->Get<TTree>("T");
      hWFsumFlat_ind_st[i].push_back((TH1D*)file_store.at(i).at(j)->Get("hWFsum_FlatNorm"));
      hWFsumRaw_st[i].push_back((TH1D*)file_store.at(i).at(j)->Get("hWFsumRaw"));

      HowManySignalEvt_ind[i].push_back(tree->GetBranch("Signal")->GetEntries());
      HowManyEmptyEvt_ind[i].push_back(tree->GetBranch("Empty")->GetEntries());
      HowManySparkEvt_ind[i].push_back(tree->GetBranch("Spark")->GetEntries());
      
      if (i == 0 && j ==0) cout << "number of signal " <<tree->GetBranch("Signal")->GetEntries() << endl;
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
  //--------Obtain WF SUM --------------
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
	//if (j == 0) norm_dummy +=HowManySignalEvt_ind.at(i).at(z) + HowManyEmptyEvt_ind.at(i).at(z);
	if (j == 0) norm_dummy += HowManySignalEvt_ind.at(i).at(z) ;
      }
      //cout << " norm_dummy " << norm_dummy << endl;
      h1->SetBinContent(j,dummy/norm_dummy/con_fact_P25);//norm_dummy*con_fact_P24
      // norm_store.push_back(norm_dummy);
      
    }
    
    h1->SetLineColor(color_st.at(i));
    h1->SetLineWidth(3);
    hWFsumFlat_st.push_back(h1);
    

  }


  //-----------------------------------------------------------------
  //------------------------!! Obtain the SUM OF THE WF SUM !!----------
  // ----------------------------------------------------------------


  std::vector<double> ElGainTh(file_store.size(),0);
  std::vector<double> ElGainMonteiroMeas;
  std::vector<double> E_N_Monteiro;
  std::vector<double> RelElGainMonteiro_Meas;
  std::vector<double> E_N(file_store.size(),0);
  std::vector<double> V_PEN(file_store.size(),0);
  std::vector<double> RelElGainTh (file_store.size(),0);
  std::vector<double> RelElGainMeas_a (file_store.size(),0);
  std::vector<double> RelElGainMeas_a_ELcomp (file_store.size(),0);
  std::vector<double> RelElGainMeas_ab (file_store.size(),0);
  std::vector<double> RelElGainMeas_ab_ELcomp (file_store.size(),0);
  std::vector<double> AbsEL_Only (file_store.size(),0);
  std::vector<double> AbsEL_Only_ab (file_store.size(),0);
  std::vector<double> Err_AbsEL_Only (file_store.size(),0);

  int ThGEM_comp = 0;


  std::vector <double> SumOfWFSum_a(file_store.size(), 0);
  std::vector <double> SumOfWFSum_ab(file_store.size(), 0);
  //
  //
  //
  double ThGemContribution_a(0), ThGemContribution_ab(0);
  int ThGEMContrCount = 6;
 
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
    



    //
  }
  

   


  
  //-----------------------------------------------------------------
  //-----------------------------------------------------------------
  //------------------------Plots and Figure---------------------
  //----------------------------------------------------------------
  //-----------------------------------------------------------------
  
  
  
  //-----------------------------------------------------------------
  //-------------------Preparing data for the WF Sums----------------
  // ----------------------------------------------------------------

  // Re drawing the waveform sum histograms with x axis from -20 to 80

  

  for (int i = 0; i <  hWFsumFlat_st.size(); i++){
    hWFsumFlat_st.at(i)->Rebin(rebin_no);
    TH1D * h_dummy = new TH1D("","", hWFsumFlat_st.at(i)->GetNbinsX(), -20,80);
    for (int j(0); j < hWFsumFlat_st.at(i)->GetNbinsX(); j++ ){
      h_dummy->SetBinContent(j,hWFsumFlat_st.at(i)->GetBinContent(j));
    }
    h_dummy->GetYaxis()->SetTitleOffset(-.1);
    h_dummy->SetLineColor(color_st.at(i));
    h_dummy->SetLineWidth(3);
    hsWFsum->Add(h_dummy);
  }
  
  auto leg_WFsum = new TLegend(0.1,0.7,0.48,0.9);
  for (int i(0); i < hWFsumFlat_st.size() ; i++){
    string bla = Form("set %d", i+1);
    leg_WFsum->AddEntry(hWFsumFlat_st.at(i), bla.c_str() ,"l");//800
}


  //-----------
  //Drawing waveform sums
  //-----------
  
  
  TCanvas *cWFsum = new TCanvas("cWFsum", " sum of waveform ", 800, 600);  
  hsWFsum->Draw("nostack");
  leg_WFsum->Draw("same");  
  std::vector<double>empty_4(file_store.size(),0);


  //----------------------------------
  //----Preparing data for abs gain---
  //----------------------------------
 
  for (int i(0); i < ds_10ppm; i++){
    abs_gain_10ppm.push_back(SumOfWFSum_a.at(i)); 
    E_N_mesh_10ppm.push_back(GetE_N(pen_mesh_10ppm.at(i), 0.26, 2e5));
    cout << " at file " << i << " the number of signal: " << HowManySignalEvt[i] << ", mesh voltage " << pen_mesh_10ppm.at(i)  << " , reduced field: " << E_N_mesh_10ppm[i]<< endl; 
  }
  

  
  for (int i = 0; i < ds_24ppm; i++){
    abs_gain_24ppm.push_back(SumOfWFSum_a.at(i +ds_10ppm));
    E_N_mesh_24ppm.push_back(GetE_N(pen_mesh_24ppm.at(i), 0.26, 2e5));
    cout << " at file " << i + ds_10ppm  << " the number of signal: " << HowManySignalEvt[i + ds_10ppm ] << ", mesh voltage " << pen_mesh_24ppm.at(i)  << " , red voltage: " << E_N_mesh_24ppm[i] << endl;   
  }

  for (int i = 0; i < ds_44ppm; i++){
    abs_gain_44ppm.push_back(SumOfWFSum_a.at(i +ds_10ppm+ds_24ppm));
    E_N_mesh_44ppm.push_back(GetE_N(pen_mesh_44ppm.at(i), 0.26, 2e5));
    cout << " at file " << i + ds_10ppm+ds_24ppm  << " the number of signal: " << HowManySignalEvt[i + ds_10ppm+ds_24ppm ] << ", mesh voltage " << pen_mesh_44ppm.at(i)  << " , red voltage: " << E_N_mesh_44ppm[i] << endl;   
  }
  

  //-- couting some general info about the number os signal ------

  


  //----------------
  //Plotting the absolute gain vs E/N
  //----------------

  TGraph *gr_24ppm = new TGraph(abs_gain_10ppm.size(), &E_N_mesh_10ppm[0], &abs_gain_10ppm[0]);
  TGraph *gr_10ppm = new TGraph(abs_gain_24ppm.size(), &E_N_mesh_24ppm[0], &abs_gain_24ppm[0]);
  TGraph *gr_44ppm = new TGraph(abs_gain_44ppm.size(), &E_N_mesh_44ppm[0], &abs_gain_44ppm[0]);

  
   

  gr_24ppm ->GetYaxis()->SetTitleOffset(0.6);
  gr_24ppm ->SetLineColor(kTeal -7);
  gr_24ppm ->SetLineWidth(2);
  gr_24ppm ->SetFillColor(kBlack);
  gr_24ppm ->SetMarkerStyle(20);






  gr_10ppm ->GetYaxis()->SetTitleOffset(0.6);
  gr_10ppm ->SetLineColor(kBlue -3);
  gr_10ppm ->SetLineWidth(2);
  gr_10ppm ->SetFillColor(kBlack);
  gr_10ppm ->SetMarkerStyle(20);

  gr_44ppm ->GetYaxis()->SetTitleOffset(0.6);
  gr_44ppm ->SetLineColor(kMagenta - 2);
  gr_44ppm ->SetLineWidth(2);
  gr_44ppm ->SetFillColor(kBlack);
  gr_44ppm ->SetMarkerStyle(20);

  TF1  *f1 = new TF1("f1","(x-[0])*[1]",0,20);
  f1->SetParameters(4,1.2);
  gr_24ppm->Fit("f1","","", 3.4,12);
  gStyle->SetOptFit(1111);
  TMultiGraph *mgr = new TMultiGraph();
  mgr->SetTitle("; E/N (Td); Equivalent Number of Photons ");
  mgr-> Add(gr_24ppm, "ALP");
  //mgr-> Add(gr_p1_2,"ALP");
  mgr-> Add(gr_10ppm,"ALP");
  mgr->Add(gr_44ppm ,"ALP");
//mgr-> Add(gr_p1_5,"ALP");

  auto leg = new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(gr_10ppm, " 10 ppm O_{2}", "l");
  leg->AddEntry(gr_24ppm, " 24 ppm O_{2}", "l");
  //  leg->AddEntry(gr_44ppm, " 44 ppm O_{2}", "l");

 
  TCanvas * c_AbsGain = new TCanvas("c_AbsGain","", 800,600);
  
  //  gr_24ppm->Draw("ALP*");
  mgr->Draw("ALP");
  leg->Draw();
  cout << "The reduced electric field " << GetE_N(200, 0.26, 1e5) << endl;   

  TGraph *gr_10ppm_V = new TGraph(abs_gain_10ppm.size(), &pen_mesh_10ppm[0], &abs_gain_10ppm[0]);
  TGraph *gr_24ppm_V = new TGraph(abs_gain_24ppm.size(), &pen_mesh_24ppm[0], &abs_gain_24ppm[0]);

  TGraph *gr_10ppm_temp = new TGraph(temp_mesh_10ppm.size(), &pen_mesh_24ppm[0], &temp_mesh_10ppm[0]);
  TGraph *gr_10ppm_h2o = new TGraph(h2o_mesh_10ppm.size(), &pen_mesh_24ppm[0], &h2o_mesh_10ppm[0]);
  TGraph *gr_10ppm_o2 = new TGraph(h2o_mesh_10ppm.size(), &pen_mesh_24ppm[0], &o2_mesh_10ppm[0]);
 
   

  gr_10ppm_temp ->GetYaxis()->SetTitleOffset(0.6);
  gr_10ppm_temp ->SetLineColor(1);
  gr_10ppm_temp ->SetLineWidth(2);
  gr_10ppm_temp ->SetFillColor(kBlack);
  gr_10ppm_temp ->SetMarkerStyle(20);


  gr_10ppm_h2o ->GetYaxis()->SetTitleOffset(0.6);
  gr_10ppm_h2o ->SetLineColor(2);
  gr_10ppm_h2o ->SetLineWidth(2);
  gr_10ppm_h2o ->SetFillColor(kBlack);
  gr_10ppm_h2o ->SetMarkerStyle(20);

  gr_10ppm_o2 ->GetYaxis()->SetTitleOffset(0.6);
  gr_10ppm_o2 ->SetLineColor(3);
  gr_10ppm_o2 ->SetLineWidth(2);
  gr_10ppm_o2 ->SetFillColor(kBlack);
  gr_10ppm_o2 ->SetMarkerStyle(20);
  
  gr_24ppm_V ->GetYaxis()->SetTitleOffset(0.6);
  gr_24ppm_V ->SetLineColor(46);
  gr_24ppm_V ->SetLineWidth(2);
  gr_24ppm_V ->SetFillColor(kBlack);
  gr_24ppm_V ->SetMarkerStyle(20);

  gr_10ppm_V ->GetYaxis()->SetTitleOffset(0.6);
  gr_10ppm_V ->SetLineColor(42);
  gr_10ppm_V ->SetLineWidth(2);
  gr_10ppm_V ->SetFillColor(kBlack);
  gr_10ppm_V ->SetMarkerStyle(20);


  


  /*  
  TMultiGraph *mgr_V = new TMultiGraph();
  mgr_V->SetTitle("; Mesh voltage (V); Equivalent Number of Photons ");
  mgr_V-> Add(gr_24ppm_V, "ALP");
  //mgr-> Add(gr_p1_2,"ALP");
  mgr_V-> Add(gr_10ppm_V,"ALP");
  //mgr-> Add(gr_p1_5,"ALP");
 
  TCanvas * c_AbsGain_V = new TCanvas("c_AbsGain_V","", 800,600);
  
  //  gr_24ppm->Draw("ALP*");
  mgr_V->Draw("ALP");
  leg->Draw();
  */

  
  TMultiGraph *mgr_all_10ppm = new TMultiGraph();
  mgr_all_10ppm->SetTitle("; Mesh voltage (V);  ");
  mgr_all_10ppm-> Add(gr_10ppm_V, "ALP");
  //mgr-> Add(gr_p1_2,"ALP");
  mgr_all_10ppm-> Add(gr_10ppm_temp, "ALP");
  mgr_all_10ppm-> Add(gr_10ppm_h2o, "ALP");
  mgr_all_10ppm-> Add(gr_10ppm_o2, "ALP");
  
  auto leg_all_10ppm = new TLegend(0.1,0.7,0.48,0.9);
  leg_all_10ppm->AddEntry(gr_10ppm_V, " Photon Eq.", "l");
  leg_all_10ppm->AddEntry(gr_10ppm_temp, " Temp (C#circ)", "l");
  leg_all_10ppm->AddEntry(gr_10ppm_h2o, " H_{2}O (ppm)", "l");
  leg_all_10ppm->AddEntry(gr_10ppm_o2, "O_{2} (ppm)", "l");
  

  //mgr-> Add(gr_p1_5,"ALP");
  TCanvas *c_10ppm = new TCanvas();
  mgr_all_10ppm->Draw("ALP");
  leg_all_10ppm->Draw();

 

   

  // fill the relative yields
  // for (int i(0); i < ds_10_11_12.size(); i++){
  //   rel_10_11_12.push_back(ds_10_11_12.at(i)/ds_10_11_12.at(norm_term));
  //   rel_13_14_15.push_back(ds_13_14_15.at(i)/ds_13_14_15.at(norm_term));
  //   rel_Config_18.push_back(ds_Config_18.at(i)/ds_Config_18.at(norm_term));
  // }
  

  

 
  // g_Abs->GetYaxis()->SetTitleOffset(0.6);
  // g_Abs ->SetLineColor(46);
  // g_Abs ->SetLineWidth(2);
  // g_Abs->SetFillColor(kBlack);
  // g_Abs ->SetMarkerStyle(20);

  // g_Abs_2->GetYaxis()->SetTitleOffset(0.6);
  // g_Abs_2 ->SetLineColor(30);
  // g_Abs_2 ->SetLineWidth(2);
  // g_Abs_2->SetFillColor(kBlack);
  // g_Abs_2 ->SetMarkerStyle(20);


 

   


   cout << "Pressure 1 bar:"<<endl;
   for (int i(0); i< pen_mesh_10ppm.size(); i++){
     cout << "  voltage = " << pen_mesh_10ppm.at(i) <<" V, E/N = "<< E_N_mesh_10ppm.at(i) << " Td" << endl;
   }

   cout << "Pressure 2 bar:"<<endl;
   for (int i(0); i< pen_mesh_24ppm.size(); i++){
     cout << "  voltage = " << pen_mesh_24ppm.at(i) <<" V, E/N = "<< E_N_mesh_24ppm.at(i) << " Td" << endl;
   }

  
  
   cout << "  debug 1 " << endl;
   gPad->Modified();
   gPad->Update();
   
  
}
