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

// I want a function which takes h1

using namespace std;

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



void MergeHistos(){

  
  //defining Stacks
  THStack *hsWFsum = new THStack("hsWF", " WF Sum (amplitudes higher than treshold);  Time (#mus); Equivalent Number of Photons ");
  

  double rebin_no = 5000;


  double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1e7 for 1650V (Hamamtsu R6427)
  double phot_to_volt =1/( - dt /(R* gain *e_ch*qe*col_eff));
  double con_fact = -0.045;
  TString NSigmas = "4.0";
  std::vector<std::vector<TString>> path_store;

  path_store.push_back({});
  path_store[0].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650_a/");
  //path_store[0].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650_b/");
  
  //
  path_store.push_back({});
  path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650/");
  //path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_ii_TPC1650_a/");
  //path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_ii_TPC1650_b/");
  //
  //
  path_store.push_back({});
  path_store[2].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh200_TPC1650/"); 
  // path_store[2].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh200_ii_TPC1650_a/"); 
  // path_store[2].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh200_ii_TPC1650_b/");


  path_store.push_back({});
  path_store[3].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh300_TPC1650/");
  // path_store[3].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh300_ii_TPC1650_a/");
  // path_store[3].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh300_ii_TPC1650_b/");

  path_store.push_back({});
  path_store[4].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_TPC1650/");
  // path_store[4].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_ii_TPC1650_a/");
  // path_store[4].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_ii_TPC1650_b/");



  path_store.push_back({});
  // path_store[5].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_TPC1650/");
  // path_store[5].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_ii_TPC1650_a/");
  path_store[5].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_ii_TPC1650_b/");

  path_store.push_back({});
  path_store[6].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh600_TPC1650/");
  //path_store[6].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh600_ii_TPC1650_a/");
  //path_store[6].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh600_ii_TPC1650_b/");

  path_store.push_back({});
  path_store[7].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh700_TPC1650/");
  //path_store[7].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh700_ii_TPC1650_a/");
  //path_store[7].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh700_ii_TPC1650_b/");
  
  path_store.push_back({});
  path_store[8].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh800_TPC1650/");
  // path_store[8].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh800_ii_TPC1650_a/");
  //path_store[8].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh800_ii_TPC1650_b/");

  path_store.push_back({});
  path_store[9].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh900_TPC1650/");
  //path_store[9].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh900_ii_TPC1650_a/");
  //path_store[9].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh900_ii_TPC1650_b/");

  path_store.push_back({});
  path_store[10].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1000_TPC1650/");
  //path_store[10].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1000_ii_TPC1650_a/");
  //path_store[10].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1000_ii_TPC1650_b/");


  path_store.push_back({});
  path_store[11].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1100_TPC1650/");
  // path_store[11].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1100_ii_TPC1650_a/");
  // path_store[11].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1100_ii_TPC1650_b/");
  
  path_store.push_back({});
  path_store[12].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1200_TPC1650/");
  // path_store[12].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1200_ii_TPC1650_a/");
  //path_store[12].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1200_ii_TPC1650_b/");

  path_store.push_back({});
  path_store[13].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1300_TPC1650/");
  //path_store[13].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1300_ii_TPC1650_a/");
  //path_store[13].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1300_ii_TPC1650_b/");


  path_store.push_back({});
  path_store[14].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1400_TPC1650/");
  //path_store[14].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1400_ii_TPC1650_a/");
  //path_store[14].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1400_ii_TPC1650_b/");


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




  for (int i(0); i < path_store.size(); i++){
    for (int j(0); j < path_store.at(i).size(); j++ ){

      file_store[i].push_back(TFile::Open(path_store.at(i).at(j)+"WF_output_5000_"+NSigmas+"RMS.root"));
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

      h1->SetBinContent(j,dummy/norm_dummy/con_fact);//norm_dummy*con_fact
      // norm_store.push_back(norm_dummy);
      
    }
    
    h1->SetLineColor(color_st.at(i));
    h1->SetLineWidth(3);
    hWFsumFlat_st.push_back(h1);
    cout <<"at file " << i << " signal of " <<  norm_dummy << endl;

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
      
      if (i<ThGEMContrCount){
	ThGemContribution_a += SumOfWFSum_a[i];
	ThGemContribution_ab += SumOfWFSum_ab[i];
      }
      

      //
    }
    ThGemContribution_a =ThGemContribution_a/ ThGEMContrCount;
    ThGemContribution_ab =ThGemContribution_ab/ ThGEMContrCount;

    
    for (int i(0); i <file_store.size(); i++){
      AbsEL_Only[i] = SumOfWFSum_a[i]-ThGemContribution_a;
      AbsEL_Only_ab[i] = SumOfWFSum_ab[i]-ThGemContribution_ab;
    }
    
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
  //determine error on the average count of the ThGEM only photons
  std::vector<double> ThGEM_Only_IntgWFSum;
  for (int i(0); i< ThGEMContrCount; i++){
    ThGEM_Only_IntgWFSum.push_back(err_IntgWFSum_a[i]);
  }
  double ErrorOnThGEMOnlyGain = GetAvgError(&ThGEM_Only_IntgWFSum);
  
  for (int i(0); i < SumOfWFSum_a.size(); i++){
    // if (i ==2 ) cotinue;
    err_Ratio_a.push_back(GetDivError(SumOfWFSum_a[i],SumOfWFSum_a[norm_term], err_IntgWFSum_a[i], err_IntgWFSum_a[norm_term]));
    err_Ratio_ab.push_back(GetDivError(SumOfWFSum_ab[i], SumOfWFSum_ab[norm_term], err_IntgWFSum_ab[i], err_IntgWFSum_ab[norm_term]));
    
    Err_AbsEL_Only[i] = GetAddError(err_IntgWFSum_a[i], ErrorOnThGEMOnlyGain);
    
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
    RelElGainMeas_ab_ELcomp[i] =AbsEL_Only_ab[i]/AbsEL_Only_ab[norm_term];
  

}
  std::vector<double>err_Ratio_a_ELcomp(SumOfWFSum_a.size(), 0);
  std::vector<double>err_Ratio_ab_ELcomp(SumOfWFSum_a.size(), 0);
  for (int i(0); i < SumOfWFSum_a.size(); i++){
    
    err_Ratio_a_ELcomp[i] =err_Ratio_a[i]+err_Ratio_a[ThGEM_comp];
    err_Ratio_ab_ELcomp[i] =err_Ratio_ab[i]+err_Ratio_ab[ThGEM_comp];

  }




  V_PEN = {0., 100, 200, 300, 400, 500,600,700,800,900,1000,1100,1200,1300,1400};




  //-----------------------------------------------------------------
  //-----------------------------------------------------------------
  //------------------------Plots and Figure---------------------
  // ----------------------------------------------------------------
  //-----------------------------------------------------------------



  //-----------------------------------------------------------------
  //------------------------Plotting the WF Sums---------------------
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
  for (int i(V_PEN.size() -1); i >= 0; i--){
    char* title = Form("MESH %.0f V", V_PEN.at(i));
    leg_WFsum->AddEntry(hWFsumFlat_st.at(i),title,"l");//800
  }


  TCanvas *cWFsum = new TCanvas("cWFsum", " sum of waveform ", 800, 600);
  
  hsWFsum->Draw("nostack");
  leg_WFsum->Draw("same");



  TCanvas * c_AbsYield = new TCanvas("Abs_Yield","", 800, 600);
  c_AbsYield->Divide(2,1);
  TGraphErrors *g_Abs = new TGraphErrors(SumOfWFSum_a.size(), &E_N[0], &SumOfWFSum_a[0], &empty_4[0],&err_IntgWFSum_a[0]);
  TGraphErrors *g_ElAbs = new TGraphErrors(AbsEL_Only.size(), &E_N[0], &AbsEL_Only[0], &empty_4[0],&Err_AbsEL_Only[0]);
  
  TF1  *f1 = new TF1("f1","(x-[0])*[1]",0,20);
  f1->SetParameters(4,1.2);
  g_ElAbs->Fit("f1","","", 3.6,13.1);
  g_ElAbs->GetFunction("f1")->SetLineColor(kRed);
  g_ElAbs->GetYaxis()->SetTitleOffset(0.6);
  g_Abs->GetYaxis()->SetTitleOffset(0.6);
  
  g_Abs ->SetLineColor(46);
  g_Abs ->SetLineWidth(2);
  g_Abs->SetFillColor(kBlack);
  g_Abs ->SetMarkerStyle(20);
  g_ElAbs -> SetLineColor(38);
  g_ElAbs ->SetLineWidth(2);
  gStyle->SetOptFit(11111);
  
  //Fit over the linear EL graph

  gPad->Update();
  
  TMultiGraph *mg_AbsYield = new TMultiGraph();
  mg_AbsYield->SetTitle("Absolute Number of Photons Detected; E/N (Td); Photon Number");
  mg_AbsYield->Add(g_Abs,"ALP");
  mg_AbsYield->Add(g_ElAbs,"ALP");
  mg_AbsYield->Draw("ALP");
  auto leg_AbsYield = new TLegend(0.1,0.7,0.48,0.9);
  leg_AbsYield->AddEntry(g_Abs,"ThGEM + EL ","l");//800
  leg_AbsYield->AddEntry(g_ElAbs,"EL Only ","l");//800
  leg_AbsYield->Draw();
  
  gPad->Update();
  
  TGaxis *axis1 = new TGaxis(0,1850,13,1850,0,1400,510,"-");
  axis1->SetTitle("Mesh Voltage [V]");
  axis1->SetLabelSize(0.03);
  axis1->SetTitleSize(0.03);
  axis1->SetTitleOffset(1.1);
  // axis1->Draw();
  
  c_AbsYield->Write();
  
  
  TCanvas * c_Yield = new TCanvas("Yield","", 1200, 600);
  c_Yield->Divide(2,1);
  
  
  
  
  // TGraphErrors *g_Meas_a = new TGraphErrors(3, &E_N[0], &SumOfWFSum_a[0], &err_x[0], &err_IntgWFSum_a[0]);

  // TGraphErrors *g_Meas_a = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_a[0], &empty_4[0], &err_Ratio_a[0]);
  // TGraphErrors *g_Meas_a_ELcomp = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_a_ELcomp[0], &empty_4[0], &err_Ratio_a_ELcomp[0]);
  TGraphErrors *g_Meas_ab = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_ab[0], &empty_3[0], &err_Ratio_ab[0]);
  TGraphErrors *g_Meas_ab_ELcomp = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_ab_ELcomp[0], &empty_4[0], &err_Ratio_ab_ELcomp[0]);
  cout << E_N.size() << " sizeiis "<<E_N_Monteiro.size() << endl;
  
  TGraphErrors *g_Meas_a = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_a[0], &empty_4[0], &err_Ratio_a[0]);
  TGraphErrors *g_Meas_a_ELcomp = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_a_ELcomp[0], &empty_4[0], &err_Ratio_a_ELcomp[0]);
  TGraph *g_Meas_Monteiro = new TGraph(ElGainMonteiroMeas.size(), &E_N_Monteiro[0], &RelElGainMonteiro_Meas[0]);
  TGraphErrors *g_Th = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainTh[0], &empty_4[0],&empty_4[0]);


  g_Meas_a ->SetLineColor(kRed);
  g_Meas_a ->SetLineWidth(1);
  g_Meas_a ->SetMarkerStyle(8);

  g_Meas_a_ELcomp ->SetLineColor(kBlue);
  g_Meas_a_ELcomp ->SetLineWidth(1);
  g_Meas_a_ELcomp ->SetMarkerStyle(8);
  
  g_Meas_ab_ELcomp ->SetLineColor(kBlue);
  g_Meas_ab_ELcomp ->SetLineWidth(1);
  g_Meas_ab_ELcomp ->SetMarkerStyle(8);

  g_Meas_ab ->SetLineColor(kRed);
  g_Meas_ab ->SetLineWidth(1);
  g_Meas_ab ->SetMarkerStyle(8);

  g_Meas_Monteiro ->SetLineColor(kBlack);
  g_Meas_Monteiro ->SetLineWidth(1);
  g_Meas_Monteiro ->SetMarkerStyle(kCircle);

  g_Th ->SetLineColor(kCyan);
  g_Th ->SetLineWidth(1);
  g_Th ->SetMarkerStyle(kPlus);



  auto leg_ELYield = new TLegend(0.1,0.7,0.48,0.9);
  leg_ELYield->AddEntry(g_Th,"MC EL Only","l");//800
  leg_ELYield->AddEntry(g_Meas_a,"ThGEM+EL","l");//800
  leg_ELYield->AddEntry(g_Meas_a_ELcomp,"EL Only","l");
  // leg_ELYield->AddEntry(g_Meas_Monteiro,"Coimbra EL Gain  ","lep");

  // leg_ELYield->AddEntry(g_Meas_a_3_5,"Measured EL Gain (NSig = 3.5) ","l");//800
  // leg_ELYield->AddEntry(g_Meas_a_4,"Measured EL Gain (NSig = 4)","l");//800
  // leg_ELYield->AddEntry(g_Meas_a_4_5,"Measured EL Gain (NSig = 4.5)","l");//800
  //leg_ELYield->Draw();



  TMultiGraph *mg = new TMultiGraph();

  mg->Add(g_Meas_a,"ALP");
  mg->Add(g_Meas_a_ELcomp,"ALP");
  // mg->Add(g_Meas_Monteiro,"ACP");
  mg->Add(g_Th,"AC");

  // mg->Add(g_Meas_a_4);
  // mg->Add(g_Meas_a_4_5);
  // mg->Add(g_Meas_a_3_5);
  // g_Th->SetMar
  // mg->SetTitle(Form("Integral of WF SUM (drift time) (NSigmas = %s)", NSigmas.c_str()));
  mg->SetTitle(Form("Relative Integral of WF SUM (drift period) (NSigmas = %s)", NSigmas.Data()));
  mg->GetXaxis()->SetTitle("E/N (Td)");
  mg->GetYaxis()->SetTitle(Form("Relative Yield (to %.1f Td)",E_N[norm_term] ));
  c_Yield->cd(1);
  mg->Draw("ALP");


  leg_ELYield->Draw();
  TMultiGraph *mg_ab = new TMultiGraph();
  // mg_ab->GetYaxis()->SetRangeUser(1.4, 2.7);
  mg_ab->Add(g_Meas_ab,"ALP");
  mg_ab->Add(g_Meas_ab_ELcomp,"ALP");
  mg_ab->Add(g_Th,"AC");
  // mg_ab->Add(g_Meas_ab_4);
  // mg_ab->Add(g_Meas_ab_4_5);
  // mg_ab->Add(g_Meas_ab_3_5);
  // g_Th->SetMar
  // g_Th->SetMar
  mg_ab->SetTitle(Form("Relative Integral of WF SUM (after drift period) (NSigmas = %s)", NSigmas.Data()));
  mg_ab->GetXaxis()->SetTitle(" E/N (Td)");
  mg_ab->GetYaxis()->SetTitle(Form("Relative Yield (to %.1f Td)", E_N[norm_term]));
  c_Yield->cd(2);
  mg_ab->Draw("ALP");
  leg_ELYield->Draw();
  // c_Yield->SaveAs("../../../../../Conferences/Troyes2022/Poster/MG_comp.pdf");
  // c_Yield->Write();

  

  //----------------------------------------------------------
  //---Plotting Data Taking Quality over PEN Voltages---------
  //----------------------------------------------------------
  
  TCanvas * c_DataTaking = new TCanvas("","", 1000,1000);
  c_DataTaking->Divide(2,2);
  c_DataTaking->cd(1);
  std::vector<double> HowManySparkEvt_PerDataSet(path_store.size(), 0);
  std::vector<double> HowManySignalEvt_PerDataSet(path_store.size(), 0);
  std::vector<double> HowManyBadPedEvt_PerDataSet(path_store.size(), 0);
  std::vector<double> HowManyEmptyEvt_PerDataSet(path_store.size(), 0); 
  
  for (int i(0); i < path_store.size(); i++){
    //    HowManySparkEvt_PerDataSet[i] = HowManySparkEvt[i]/path_store[i].size();
    HowManySparkEvt_PerDataSet[i] = HowManySparkEvt[i];
    HowManySignalEvt_PerDataSet[i] = HowManySignalEvt[i]/path_store[i].size();
    HowManyEmptyEvt_PerDataSet[i] = HowManyEmptyEvt[i]/path_store[i].size();    
  }


  TGraph *g_Spark_PENV = new TGraph(HowManySparkEvt.size(), &V_PEN[0], &HowManySparkEvt_PerDataSet[0]);
  g_Spark_PENV ->SetLineColor(30);
  g_Spark_PENV ->SetLineWidth(4);
  g_Spark_PENV ->SetMarkerStyle(kCircle);
  g_Spark_PENV ->SetTitle("Number of sparks per data set of 12 hours; PEN Voltage [V]; No. of Sparks");
  g_Spark_PENV ->Draw("ACP");
  gPad->SetGrid();
  c_DataTaking->cd(3);
  TGraph *g_Signal_PENV = new TGraph(HowManySparkEvt.size(), &V_PEN[0], &HowManySignalEvt_PerDataSet[0]);
  g_Signal_PENV ->SetLineColor(30);
  g_Signal_PENV ->SetLineWidth(4);
  g_Signal_PENV ->SetMarkerStyle(kCircle);
  g_Signal_PENV ->SetTitle("Number of signal events per data set of 12 hours; PEN Voltage [V]; No. of Signal Events");
  
  g_Signal_PENV->Draw("ACP");
  gPad->SetGrid();
  


  c_DataTaking->cd(2);
  TGraph *g_Empty_PENV = new TGraph(HowManySparkEvt.size(), &V_PEN[0], &HowManyEmptyEvt_PerDataSet[0]);
  g_Empty_PENV ->SetLineColor(30);
  g_Empty_PENV ->SetLineWidth(4);
  g_Empty_PENV ->SetMarkerStyle(kCircle);
  g_Empty_PENV ->SetTitle("Number of empty events per data set of 12 hours; PEN Voltage [V]; No. of Empty Events");
  g_Empty_PENV->Draw("APC");
  
  gPad->SetGrid();

  //----------------------------------//
  // Plots only made for the EL paper //
  //----------------------------------//

  TCanvas *cWFSum_0 = new TCanvas("cWFSum0","", 800,600);
  TH1D * h_test = new TH1D("","title;Time (#mus); Equivalent Number of Photons", hWFsumFlat_ind_st[0].at(0)->GetNbinsX(), -20,80);
  for (int i(0); i < hWFsumFlat_ind_st[0].at(0)->GetNbinsX(); i++){
    h_test->SetBinContent(i,hWFsumFlat_ind_st[0].at(0)->GetBinContent(i));

}
    
  auto leg_SingleWF = new TLegend(0.1,0.7,0.48,0.9);
  
  char* title_SingleWF = Form("MESH %.0f V", V_PEN.at(0));
  leg_SingleWF->AddEntry(h_test,title_SingleWF,"l");//800
  

  
  leg_SingleWF->Draw("same");
  
  h_test->Draw();
 
  gPad->Modified();
  gPad->Update();
  
  //----------------------------------//
  // Plots made to see the integral distribution//
  //----------------------------------//

  TCanvas * c_intg_a = new TCanvas("c_intg_a","c_intg_a", 800, 600); 
  
  //  auto tree = file_store.at(0).at(j0)->Get<TTree>("T");
  auto tree = file_store[0][0]->Get<TTree>("T");

  float intg_a(0);

  tree->SetBranchStatus("*",0);
  tree->SetBranchAddress("intg_a",&intg_a);
  tree->SetBranchStatus("intg_a",1);
  TH1D* h_intg_a = new TH1D ("h_intg_a","h_intg_a", 100, 0, 1000); 
  
  //  cout << "number of entries " << tree->GetEntries() << endl;

  for (int i(0);i< tree->GetEntries(); i++){
    //cout << i << endl;
    tree->GetEntry(i);
    h_intg_a->Fill(intg_a);
    cout << " intg_a " << intg_a << endl;
    
  }

  gStyle->SetOptStat(11111);
  h_intg_a->Draw();


}
