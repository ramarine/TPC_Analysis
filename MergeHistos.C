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


// I want a function which takes h1.


using namespace std;


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



void MergeHistos(){

  gROOT->SetStyle("Plain");

  //defining Stacks
  THStack *hsWFsum = new THStack("hsWF", " WF Sum (amplitudes higher than treshold);  Time (#mus); Equivalent Number of Photons ");


  double rebin_no = 5000;


  double const R(50.), gain(1.21e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1.21e7 for 1650V (Hamamtsu R6427)
  double phot_to_volt =1/( - dt /(R* gain *e_ch*qe*col_eff));
  double con_fact = -0.037;
  //con_fact = phot_to_volt;
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


  gStyle->SetPalette(kCividis);
  gStyle->SetPalette(kAlpine);
  gStyle->SetPalette(kBlueRedYellow);
  // gStyle->SetPalette(kGistEarth);
  //gStyle->SetPalette(kBrownCyan);
  //gStyle->SetPalette(kAtlantic);
  //  gStyle->SetPalette(kLightTemperature);
  auto cols = TColor::GetPalette();
  //cout << "cols size: " << cols.size() << endl;
  for (int i(0); i < path_store.size(); i++){
    color_st.push_back(cols.At(i*17));
    // cout << cols.At(i) << endl;
  }
  // color_st.push_back(30);// 4 = blue
  // color_st.push_back(12);// 4 = blue
  // color_st.push_back(17);// 4 = blue
  // color_st.push_back(4); // 4 = blue
  // color_st.push_back(2); // 2 = red
  // color_st.push_back(1); // 1 = black
  // color_st.push_back(7); // 7 = cyan
  // color_st.push_back(6); //6 = magenta
  // color_st.push_back(48);// 48 = rose
  // color_st.push_back(12);// 48 = rose
  // color_st.push_back(52);// 48 = rose
  // color_st.push_back(14);// 48 = rose
  // color_st.push_back(21);// 48 = rose
  // color_st.push_back(27);// 48 = rose
  // color_st.push_back(38);// 48 = rose
  // color_st.push_back(39);// 48 = rose




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
	  //if (hWFsumFlat_st.at(i)->GetBinContent(j) != 0) cout << " non 0 bro " << endl;
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


    std::cout << " The ThGEM contribution in photon yield is: " << ThGemContribution_a << " ( average of first "  << ThGEMContrCount << " points ) " << endl;

    for (int i(0); i <file_store.size(); i++){
      AbsEL_Only[i] = SumOfWFSum_a[i]-ThGemContribution_a;
      AbsEL_Only_ab[i] = SumOfWFSum_ab[i]-ThGemContribution_ab;
    }

   





    //-----------------------------------------------------------------
    //------------------------Treating Errors--------------------------
    // ----------------------------------------------------------------
    
    
    //producing errors for the abs gain: the mean of the exponential distribution/ sqrt(NEntries)
    
    std::vector<std::vector<double>> intg_a_store;
    std::vector<int> ct(path_store.size(), 0);
    for (int i(0); i < path_store.size(); i++){//number of voltages on the mesh
      intg_a_store.push_back({});
      for (int j(0); j < path_store.at(i).size(); j++ ){// number of datasets per each mesh voltage
	Double_t intg_a(0);
	int Signal(0);
	file_store[i].push_back(TFile::Open(path_store.at(i).at(j)+"WF_output_5000_"+NSigmas+"RMS.root"));
	auto tree = file_store.at(i).at(j)->Get<TTree>("T");
	tree->SetBranchAddress("Signal",&Signal);
	tree->SetBranchAddress("intg_a",&intg_a);
	tree->SetBranchStatus("*",0);
	tree->SetBranchStatus("intg_a",1);
	tree->SetBranchStatus("Signal",1);
	
	for (int z(0);  z< tree->GetBranch("Signal")->GetEntries(); z++){
	  tree->GetEntry(z);
	  tree->GetEntry(Signal);
	  intg_a_store.at(i).push_back(intg_a*phot_to_volt/(-con_fact));
	  ct.at(i) +=1;
	}
      }
    }
    
    std::vector<double> mean;
    std::vector<double> STD;
    std::vector<double> NEntries;
    
    
    for (int i (0); i < intg_a_store.size(); i++){
      auto stats =   GetMean_STD_NEntries(intg_a_store.at(0));
      mean.push_back(stats.at(0));
      STD.push_back(stats.at(1));
      NEntries.push_back(stats.at(2));
    }
    
    std::vector<double>err_IntgWFSum_a(file_store.size(),0);
    std::vector<double>err_IntgWFSum_ab(file_store.size(),0);
    std::vector<double>err_Ratio_a;
    std::vector<double>err_Ratio_ab;
    std::vector<double>empty_4(file_store.size(),0);
    std::vector<double>empty_3(file_store.size(),0);
    
    for (int i(0); i < SumOfWFSum_a.size(); i++){
      err_IntgWFSum_a[i] = STD.at(i)/TMath::Sqrt(NEntries.at(i));
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

      Err_AbsEL_Only[i] = GetAddError(err_IntgWFSum_a[i], ErrorOnThGEMOnlyGain);

      err_Ratio_a.push_back(GetDivError(SumOfWFSum_a[i],SumOfWFSum_a[norm_term], err_IntgWFSum_a[i], err_IntgWFSum_a[norm_term]));
      err_Ratio_ab.push_back(GetDivError(SumOfWFSum_ab[i], SumOfWFSum_ab[norm_term], err_IntgWFSum_ab[i], err_IntgWFSum_ab[norm_term]));


      
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


  for (int i(0); i<SumOfWFSum_a.size(); i++){
    cout << "Abs Yield: "<<SumOfWFSum_a.at(i)<< "  " << E_N.at(i) << endl;
    
  }

  cout << " The number of photons at " << E_N.back() << " is " << SumOfWFSum_a.back() << " pm " << err_IntgWFSum_a.back() << endl;

  TF1  *f1 = new TF1("f1","(x-[0])*[1]",0,20);
  f1->SetParameters(4,1.2);
  g_ElAbs->Fit("f1","","", 3.6,13.1);
  g_ElAbs->GetFunction("f1")->SetLineColor(kBlack);
  g_ElAbs->GetYaxis()->SetTitleOffset(0.6);
  g_Abs->GetYaxis()->SetTitleOffset(0.6);

  g_Abs ->SetLineColor(kTeal-7);
  g_Abs ->SetLineWidth(2);
  g_Abs->SetFillColor(kBlack);
  g_Abs ->SetMarkerStyle(8);
  g_ElAbs -> SetLineColor(kMagenta-2);
  g_ElAbs ->SetLineWidth(2);
  g_ElAbs ->SetMarkerStyle(21);//21, 8, 34
  gStyle->SetOptFit(11111);

  //Fit over the linear EL graph

  gPad->Update();

  TMultiGraph *mg_AbsYield = new TMultiGraph();
  mg_AbsYield->SetTitle("Absolute number of photons detected; E/N (Td); Photon number per event");
  mg_AbsYield->Add(g_Abs,"ALP");
  mg_AbsYield->Add(g_ElAbs,"ALP");
  mg_AbsYield->GetYaxis()->SetTitleOffset(0.95);
  mg_AbsYield->Draw("ALP");
  auto leg_AbsYield = new TLegend(0.1,0.7,0.48,0.9);
  leg_AbsYield->AddEntry(g_Abs,"ThGEM + EL ","lp");//800
  leg_AbsYield->AddEntry(g_ElAbs,"EL only ","lp");//800
  leg_AbsYield->Draw();

  gPad->Update();

  TGaxis *axis1 = new TGaxis(0,1850,13,1850,0,1400,510,"-");
  axis1->SetTitle("Mesh Voltage [V]");
  axis1->SetLabelSize(0.03);
  axis1->SetTitleSize(0.03);
  axis1->SetTitleOffset(1.1);
  // axis1->Draw();

  c_AbsYield->Write();


  TCanvas * c_Yield = new TCanvas("Yield","", 1600, 600);
  c_Yield->Divide(2,1);


  err_Ratio_a[norm_term] = 0;
  err_Ratio_a_ELcomp[norm_term] = 0;
  err_Ratio_ab[norm_term] = 0;
  err_Ratio_ab_ELcomp[norm_term] = 0;


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


  g_Meas_a ->SetLineColor(kTeal-7);
  g_Meas_a ->SetLineWidth(1);
  g_Meas_a ->SetMarkerStyle(8);// 8, 21 , 34

  g_Meas_a_ELcomp ->SetLineColor(kMagenta-2);
  g_Meas_a_ELcomp ->SetLineWidth(1);
  g_Meas_a_ELcomp ->SetMarkerStyle(21);

  
  g_Th ->SetLineColor(kOrange-3);
  g_Th ->SetLineWidth(1);
  g_Th ->SetMarkerStyle(kPlus);


  g_Meas_ab ->SetLineColor(kTeal-7);
  g_Meas_ab ->SetLineWidth(1);
  g_Meas_ab ->SetMarkerStyle(8);

  g_Meas_ab_ELcomp ->SetLineColor(kMagenta-2);
  g_Meas_ab_ELcomp ->SetLineWidth(1);
  g_Meas_ab_ELcomp ->SetMarkerStyle(21);

  g_Meas_Monteiro ->SetLineColor(kOrange-3);
  g_Meas_Monteiro ->SetLineWidth(1);
  g_Meas_Monteiro ->SetMarkerStyle(kCircle);



  auto leg_ELYield = new TLegend(0.1,0.7,0.48,0.9);
  leg_ELYield->AddEntry(g_Th,"MC EL only","l");//800
  leg_ELYield->AddEntry(g_Meas_a,"ThGEM+EL","lp");//800
  leg_ELYield->AddEntry(g_Meas_a_ELcomp,"EL only","lp");
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
  mg->GetYaxis()->SetTitle(Form("Relative yield (to %.1f Td)",E_N[norm_term] ));
  c_Yield->cd(1);
  mg->GetYaxis()->SetTitleOffset(0.95);
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
  mg_ab->GetYaxis()->SetTitleOffset(0.95);
  mg_ab->Draw("ALP");
  leg_ELYield->Draw();
  // c_Yield->SaveAs("../../../../../Conferences/Troyes2022/Poster/MG_comp.pdf");
  // c_Yield->Write();



  //----------------------------------------------------------
  //---Plotting Data Taking Quality over PEN Voltages---------
  //----------------------------------------------------------
  


  std::vector<double> HowManySparkEvt_PerDataSet(path_store.size(), 0);
  std::vector<double> HowManySignalEvt_PerDataSet(path_store.size(), 0);
  std::vector<double> HowManyBadPedEvt_PerDataSet(path_store.size(), 0);
  std::vector<double> HowManyEmptyEvt_PerDataSet(path_store.size(), 0);

  std::vector<double> HowManySparkEvt_Per5000(path_store.size(), 0);
  std::vector<double> HowManySignalEvt_Per5000(path_store.size(), 0);
  std::vector<double> HowManyEmptyEvt_Per5000(path_store.size(), 0);

  std::vector<double> err_spark_x(path_store.size(),0);
  std::vector<double> err_spark_y(path_store.size(),0);
  std::vector<double> HowManySignalEvt_PerDataSet_err(path_store.size(),0);
  std::vector<double> HowManyEmptyEvt_PerDataSet_err(path_store.size(),0);
  std::vector<double> err_spark_y_div(path_store.size(),0);
  std::vector<double> HowManySignalEvt_PerDataSet_err_div(path_store.size(),0);
  std::vector<double> HowManyEmptyEvt_PerDataSet_err_div(path_store.size(),0);

  for (int i(0); i < path_store.size(); i++){
    //    HowManySparkEvt_PerDataSet[i] = HowManySparkEvt[i]/path_store[i].size();
    HowManySparkEvt_PerDataSet[i] = HowManySparkEvt[i];
    HowManySignalEvt_PerDataSet[i] = HowManySignalEvt[i]/path_store[i].size();
    HowManyEmptyEvt_PerDataSet[i] = HowManyEmptyEvt[i]/path_store[i].size();
    
    HowManySparkEvt_Per5000[i] = HowManySparkEvt[i]/5000;
    HowManySignalEvt_Per5000[i] = HowManySignalEvt[i]/5000;
    HowManyEmptyEvt_Per5000[i] = HowManyEmptyEvt[i]/5000;
    
    err_spark_y[i] = TMath::Sqrt( HowManySparkEvt[i]);
    HowManySignalEvt_PerDataSet_err[i] = TMath::Sqrt(HowManySignalEvt_PerDataSet[i]);
    HowManyEmptyEvt_PerDataSet_err[i] = TMath::Sqrt(HowManyEmptyEvt_PerDataSet[i]);
    err_spark_y_div[i]= GetDivError(HowManySparkEvt_Per5000[i],5000,err_spark_y[i],0);
    HowManySignalEvt_PerDataSet_err_div[i]=GetDivError(HowManySignalEvt_Per5000[i],5000,HowManySignalEvt_PerDataSet_err[i],0);
    HowManyEmptyEvt_PerDataSet_err_div[i]=GetDivError(HowManyEmptyEvt_Per5000[i],5000,HowManyEmptyEvt_PerDataSet_err[i],0);
}

  //  double GetDivError(double nom, double denom, double nom_err, double denom_err){
  TCanvas * c_DataTaking_2 = new TCanvas("","", 800,600);
  
  TGraphErrors *g_Spark_div = new TGraphErrors(HowManySparkEvt.size(), &V_PEN[0], &HowManySparkEvt_Per5000[0], &err_spark_x[0], &err_spark_y_div[0]);
  TGraphErrors *g_Sig_div = new TGraphErrors(HowManySparkEvt.size(), &V_PEN[0], &HowManySignalEvt_Per5000[0], &err_spark_x[0], &HowManySignalEvt_PerDataSet_err_div[0]);
  TGraphErrors *g_Empty_div = new TGraphErrors(HowManySparkEvt.size(), &V_PEN[0], &HowManyEmptyEvt_Per5000[0], &err_spark_x[0], &HowManyEmptyEvt_PerDataSet_err_div[0]);
  

  // Int_t ci = TColor::GetFreeColorIndex();
  //Color_t color = Color_t(ci, 255, 31., 91.);
  

  //  g_Empty_div->SetLineColor();// kRed -9, kGreen -8, kBlue// kBlue, kGreen+3, kRed-9//kAzure+1, kGreen+3, kMagenta -2.



  //  TColor *color = new TColor(ci, 30, 119, 180);
  TColor *blue = new TColor(3000, 0, 0, 255);//blue
  TColor *orange = new TColor(3001, 255, 140, 0);//blue
  TColor *green = new TColor(3002, 0, 128, 0);//green
  
   
  
  g_Empty_div->SetLineColor(kMagenta-2);
  g_Empty_div->SetLineWidth(2);
  g_Spark_div->SetLineColor(kTeal-7);
  g_Spark_div->SetLineWidth(2);
  g_Sig_div->SetLineColor(kOrange -3);  
  g_Sig_div->SetLineWidth(2);
 

  TMultiGraph *mgr_c = new TMultiGraph();
  mgr_c->SetTitle(";Mesh voltage (V); Event fraction");   
  mgr_c->Add(g_Spark_div);
  mgr_c->Add(g_Empty_div);
  mgr_c->Add(g_Sig_div);
  mgr_c->Draw("ALP");

  auto leg_c = new TLegend(0.1,0.7,0.48,0.9);
  //legend->SetHeader("Quarter ThGEM hole","C"); // option "C" allows to center the header
  leg_c->AddEntry(g_Spark_div,"Spark ","l");
  leg_c->AddEntry(g_Sig_div,"Signal ","l");
  leg_c->AddEntry(g_Empty_div,"Empty ","l");
  leg_c->Draw();


  TCanvas * c_DataTaking = new TCanvas("","", 1600,1200);
  c_DataTaking->Divide(2,2);
  c_DataTaking->cd(1);
  TGraphErrors *g_Spark_PENV = new TGraphErrors(HowManySparkEvt.size(), &V_PEN[0], &HowManySparkEvt_PerDataSet[0], &err_spark_x[0], &err_spark_y[0]);
  g_Spark_PENV ->SetLineColor(kBlack);
  g_Spark_PENV ->SetLineWidth(1);
  g_Spark_PENV ->SetMarkerStyle(8);
  g_Spark_PENV ->SetTitle("Number of sparks per data set of 12 hours; Mesh voltage (V); Spark number");
  g_Spark_PENV ->Draw("AP");
  gPad->SetGrid();
  c_DataTaking->cd(3);
  TGraphErrors *g_Signal_PENV = new TGraphErrors(HowManySparkEvt.size(), &V_PEN[0], &HowManySignalEvt_PerDataSet[0], &err_spark_x[0], &HowManySignalEvt_PerDataSet_err[0]);
  g_Signal_PENV ->SetLineColor(kBlack);
  g_Signal_PENV ->SetLineWidth(1);
  g_Signal_PENV ->SetMarkerStyle(8);
  g_Signal_PENV ->SetTitle("Number of signal events per data set of 12 hours; Mesh voltage (V);Number of signal events");

  g_Signal_PENV->Draw("AP");
  gPad->SetGrid();



  c_DataTaking->cd(2);
  
  TGraphErrors *g_Empty_PENV = new TGraphErrors(HowManySparkEvt.size(), &V_PEN[0], &HowManyEmptyEvt_PerDataSet[0], &err_spark_x[0], &HowManyEmptyEvt_PerDataSet_err[0]);
  g_Empty_PENV ->SetLineColor(kBlack);
  g_Empty_PENV ->SetLineWidth(1);
  g_Empty_PENV ->SetMarkerStyle(8);
  g_Empty_PENV ->SetTitle("Number of empty events per data set of 12 hours; Mesh voltage (V);Number of empty events");
  g_Empty_PENV->Draw("AP");
  gPad->SetGrid();

  //----------------------------------//
  // Plots only made for the EL paper //
  //----------------------------------//

  TCanvas *cWFSum_0 = new TCanvas("cWFSum0","", 800,600);
  TH1D * h_test = new TH1D("","title;Time (#mus); Equivalent number of photons", hWFsumFlat_ind_st[0].at(0)->GetNbinsX(), -20,80);
  TH1D * h_WFSum_raw = new TH1D("","title;Time (#mus); Equivalent number of photons",hWFsumRaw_st[0].at(0)->GetNbinsX(), -20,80);
  TH1D * h_WFSum_raw_neg = new TH1D("","title;Time (#mus); A.U.",hWFsumRaw_st[0].at(0)->GetNbinsX(), -20,80);

  //  hWFsumRaw_st[i].push_back();
  h_WFSum_raw = (TH1D*)file_store.at(0).at(0)->Get("hWFsumRaw");

  for (int i(0); i < hWFsumFlat_ind_st[0].at(0)->GetNbinsX(); i++){
    h_test->SetBinContent(i,hWFsumFlat_ind_st[0].at(0)->GetBinContent(i)); 
    
  }
  for (int i(0); i < hWFsumRaw_st[0].at(0)->GetNbinsX(); i++){
    h_WFSum_raw_neg->SetBinContent(i,(-1)* h_WFSum_raw->GetBinContent(i)); 
  }
  auto leg_SingleWF = new TLegend(0.1,0.7,0.48,0.9);

  char* title_SingleWF = Form("MESH %.0f V", V_PEN.at(0));
  leg_SingleWF->AddEntry(h_test,title_SingleWF,"l");//800

  leg_SingleWF->Draw("same");
  h_test->Draw();
  gPad->Modified();
  gPad->Update();

  TCanvas *cWFSum_Raw = new TCanvas("cWFSumRaw","", 800,600);
  h_WFSum_raw_neg->Draw();
  gPad->Modified();
  gPad->Update();  


  // ----------------------------------//
  // Plots made to see the integral distribution//
  // ----------------------------------//

  // TCanvas * c_intg_a = new TCanvas("c_intg_a","c_intg_a", 800, 600);
  //
  // //  auto tree = file_store.at(0).at(j0)->Get<TTree>("T");
  // TFile * file = TFile::Open(path_store.at(0).at(0)+"WF_output_5000_"+NSigmas+"RMS.root");
  // auto tree = file->Get<TTree>("T");
  //
  // Double_t intg_a;
  //
  //
  // tree->SetBranchAddress("intg_a",&intg_a);
  // tree->SetBranchStatus("*",0);
  // tree->SetBranchStatus("intg_a",1);
  // TH1D* h_intg_a = new TH1D ("h_intg_a","h_intg_a", 100, 0, 10000);
  //
  // //  cout << "number of entries " << tree->GetEntries() << endl;
  // double ct(0);
  // for (int i(0);i< tree->GetBranch("intg_a")->GetEntries(); i++){
  //   tree->GetEntry(i);
  //   if (intg_a >10){
  //     h_intg_a->Fill(intg_a*phot_to_volt/(-con_fact));
  //     ct++;
  //   }
  //
  //
  // }
  // cout << "mean " << h_intg_a->GetMean() << " RMS: " << h_intg_a->GetRMS() << "rms/sqrt(N)"<< h_intg_a->GetRMS()/ct<<  endl;
  // gStyle->SetOptStat(111111);
  // h_intg_a->Draw();


  
  
  TCanvas * c_intg_a = new TCanvas("c_intg_a","c_intg_a", 800, 600);
  TH1D* h_intg_a = new TH1D ("h_intg_a","h_intg_a", 100, 0, 10000);
  for (int i(0); i < intg_a_store.at(0).size(); i++){
    h_intg_a->Fill(intg_a_store[0][i]);
  }
  gStyle->SetOptStat(111111);
  h_intg_a->Draw();
  

  cout << "evts at 0 " << ct.at(0) << endl;
  

  
  
  

  
}
