// this is where I analyse the TTree produced through the unpacking of the binary.
// this works with the inpout produced from GeneralAna_v6.

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

using namespace std;

double GetDivError(double nom, double denom, double nom_err, double denom_err){
  return TMath::Sqrt(((nom_err*nom_err) / (denom*denom) ) + (nom*nom * denom_err*denom_err)/(denom*denom*denom*denom));
}

double GetAddError(double err_x, double err_y){
  return TMath::Sqrt((err_x*err_x) + (err_y*err_y));
}

void Config18_Ana_v2(){

  double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1e7 for 1650V (Hamamtsu R6427)
  double con_fact = - dt /(R* gain *e_ch*qe*col_eff);

  std::vector<TString> path_store;
  //



  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650_a/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh200_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh300_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh400_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh500_ii_TPC1650_b/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh600_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh700_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh800_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh900_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1000_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1100_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1200_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1300_TPC1650/");
  path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1400_TPC1650/");

  // path_store.push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh1450_TPC1650/");




  int tot_evt = 10;
  TCanvas *time = new TCanvas("c1", "overlap", 0, 0, 800, 600);

  const char* histoname = "sc";
  double rebin_no  = 5000;




  TString NSigmas = "4.0";
  std::vector<TFile*> file_store;
  std::vector<TH1D*> hWFsumFlat_st;
  std::vector<TH1D*> hWFsumRaw_st;
  std::vector<TH1D*> hWFsum_Ratio_st;


  for (int i(0); i < path_store.size(); i++){

    file_store.push_back(TFile::Open(path_store.at(i)+"WF_output_5000_"+NSigmas+"RMS.root"));

  }




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
    std::vector<double> AbsEL_Only (file_store.size(),0);
    std::vector<double> Err_AbsEL_Only (file_store.size(),0);

    int ThGEM_comp = 0;





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



    THStack *hsWFsum = new THStack("hsWF", " WF Sum (amplitudes higher than treshold);  Time [s]; Number of Photons ");
    THStack *hsWFsumRaw = new THStack("hsWFraw", "WF Sum Raw;  Time [s]; Number of Photonss");
    //
    //
    //
    //
    std::vector<double> HowManySignalEvt;
    std::vector<double> HowManyEmptyEvt;
    std::vector<double> HowManySparkEvt;


    for (int i(0); i < file_store.size(); i++){
      auto tree = file_store.at(i)->Get<TTree>("T");
      hWFsumFlat_st.push_back((TH1D*)file_store.at(i)->Get("hWFsum_FlatNorm"));
      hWFsumRaw_st.push_back((TH1D*)file_store.at(i)->Get("hWFsumRaw"));
      hWFsumFlat_st.at(i)->SetLineColor(color_st.at(i));
      hWFsumRaw_st.at(i)->SetLineColor(color_st.at(i));
      hWFsumFlat_st.at(i)->SetLineWidth(1);
      hWFsumRaw_st.at(i)->SetLineWidth(1);
      // HowManySignalEvt.push_back(((TH1D*)file_store.at(i)->Get("hHowManySignalEvt"))->GetBinContent(((TH1D*)file_store.at(i)->Get("hHowManySignalEvt"))->GetMaximumBin()));
      // HowManyEmptyEvt.push_back(((TH1D*)file_store.at(i)->Get("hHowManyEmptyEvt"))->GetBinContent(((TH1D*)file_store.at(i)->Get("hHowManyEmptyEvt"))->GetMaximumBin()));
      // HowManySparkEvt.push_back(((TH1D*)file_store.at(i)->Get("hHowManySparkEvt"))->GetBinContent(((TH1D*)file_store.at(i)->Get("hHowManySparkEvt"))->GetMaximumBin()));
      HowManySignalEvt.push_back(tree->GetBranch("Signal")->GetEntries());
      HowManyEmptyEvt.push_back(tree->GetBranch("Empty")->GetEntries());
      HowManySparkEvt.push_back(tree->GetBranch("Spark")->GetEntries());


    }


    //-----------------------------------------------------------------
    //------------------------Normalising the WF sum histos------------
    // ----------------------------------------------------------------

    std::vector<double> norm_st;
    std::vector<double> WFsum_base_st( hWFsumFlat_st.size(),0);
    std::vector<double> WFsumRaw_base_st( hWFsumRaw_st.size(),0);



    for (int i(0); i < file_store.size(); i++){
      // norm_st.push_back(HowManyEmptyEvt.at(i)+HowManySignalEvt.at(i));
      norm_st.push_back(HowManySignalEvt.at(i));
    }


    cout << "debug debug debug debug " << endl;


    for (int i = 0; i <  hWFsumFlat_st.size(); i++){
      for (int j(0); j < hWFsumFlat_st.at(0)->GetNbinsX(); j++){

        hWFsumFlat_st.at(i)->SetBinContent(j,hWFsumFlat_st.at(i)->GetBinContent(j)/norm_st.at(i)*con_fact);
        hWFsumRaw_st.at(i)->SetBinContent(j,hWFsumRaw_st.at(i)->GetBinContent(j)/norm_st.at(i)*con_fact);
      }
    }

    //-----------------------------------------------------------------
    //------------------------Obtain the SUM OF THE WF SUM !!----------
    // ----------------------------------------------------------------


    std::vector <double> SumOfWFSum_a(file_store.size(), 0);
    std::vector <double> SumOfWFSum_ab(file_store.size(), 0);



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
      AbsEL_Only[i] = SumOfWFSum_a[i]-SumOfWFSum_a[ThGEM_comp];

    }




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

    // V_PEN[9] = 1450;

    // E_N = VPEN /0.43 *4*0.001;
    // V = 100; E_N = 0.93; ElGainTh =  0;
    // V = 200; E_N = 1.86; ElGainTh =  0;
    // V = 300; E_N = 2.79; ElGainTh =  0.005;
    // V = 400; E_N = 3.72; ElGainTh =  0.015;


    //E_N[9] = 13.49;





    // E_N.erase(E_N.begin()+norm_term);
    // RelElGainTh.erase(RelElGainTh.begin()+norm_term);
    // empty_4.erase(empty_4.begin()+norm_term);
    // RelElGainMeas_a.erase(RelElGainMeas_a.begin()+norm_term);
    // RelElGainMeas_ab.erase(RelElGainMeas_ab.begin()+norm_term);

    TCanvas * c_AbsYield = new TCanvas("Abs_Yield","", 800, 600);
    c_AbsYield->Divide(2,1);
    TGraphErrors *g_Abs = new TGraphErrors(SumOfWFSum_a.size(), &V_PEN[0], &SumOfWFSum_a[0], &empty_4[0],&err_IntgWFSum_a[0]);
    TGraphErrors *g_ElAbs = new TGraphErrors(AbsEL_Only.size(), &V_PEN[0], &AbsEL_Only[0], &empty_4[0],&Err_AbsEL_Only[0]);


    g_Abs ->SetLineColor(46);
    g_Abs ->SetLineWidth(2);
    g_Abs->SetFillColor(kBlack);
    g_Abs ->SetMarkerStyle(20);
    g_ElAbs -> SetLineColor(38);
    g_ElAbs ->SetLineWidth(2);


    TMultiGraph *mg_AbsYield = new TMultiGraph();
    mg_AbsYield->SetTitle("Absolute Number of Photons Detected; PEN Mesh Voltage [V]; Photon Number");
    mg_AbsYield->Add(g_Abs,"ALP");
    mg_AbsYield->Add(g_ElAbs,"ALP");
    mg_AbsYield->Draw("ALP");
    auto leg_AbsYield = new TLegend(0.1,0.7,0.48,0.9);
    leg_AbsYield->AddEntry(g_Abs,"ThGEM + EL ","l");//800
    leg_AbsYield->AddEntry(g_ElAbs,"EL Only ","l");//800
    leg_AbsYield->Draw();
    c_AbsYield->Write();


    TCanvas * c_Yield = new TCanvas("Yield","", 1200, 600);
    c_Yield->Divide(2,1);




    // TGraphErrors *g_Meas_a = new TGraphErrors(3, &E_N[0], &SumOfWFSum_a[0], &err_x[0], &err_IntgWFSum_a[0]);

    // TGraphErrors *g_Meas_a = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_a[0], &empty_4[0], &err_Ratio_a[0]);
    // TGraphErrors *g_Meas_a_ELcomp = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_a_ELcomp[0], &empty_4[0], &err_Ratio_a_ELcomp[0]);
    TGraphErrors *g_Meas_ab = new TGraphErrors(RelElGainTh.size(), &E_N[0], &RelElGainMeas_ab[0], &empty_3[0], &err_Ratio_ab[0]);

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
    leg_ELYield->AddEntry(g_Th,"MC EL Only","lep");//800
    leg_ELYield->AddEntry(g_Meas_a,"ThGEM+EL","lep");//800
    leg_ELYield->AddEntry(g_Meas_a_ELcomp,"EL Only","lep");
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
    mg->GetXaxis()->SetTitle("E/N [Td]");
    mg->GetYaxis()->SetTitle(Form("Relative Yield (to %.1f Td)",E_N[norm_term] ));
    c_Yield->cd(1);
    mg->Draw("ALP");


    leg_ELYield->Draw();
    TMultiGraph *mg_ab = new TMultiGraph();
    // mg_ab->GetYaxis()->SetRangeUser(1.4, 2.7);
    mg_ab->Add(g_Meas_ab,"ALP");
    mg_ab->Add(g_Th,"AC");
    // mg_ab->Add(g_Meas_ab_4);
    // mg_ab->Add(g_Meas_ab_4_5);
    // mg_ab->Add(g_Meas_ab_3_5);
    // g_Th->SetMar
    // g_Th->SetMar
    mg_ab->SetTitle(Form("Relative Integral of WF SUM (after drift period) (NSigmas = %s)", NSigmas.Data()));
    mg_ab->GetXaxis()->SetTitle("V PEN [V]");
    mg_ab->GetYaxis()->SetTitle(Form("Relative Yield (to %.1f Td)", E_N[norm_term]));
    c_Yield->cd(2);
    mg_ab->Draw("ALP");
    leg_ELYield->Draw();
    c_Yield->SaveAs("../../../../../Conferences/Troyes2022/Poster/MG_comp.pdf");
    c_Yield->Write();


    // g_Meas_a->Draw("apl");
    // g_Th->Draw("apl same");

    //-----------------------------------------------------------------
    //------------------------Plotting the WF Sums---------------------
    // ----------------------------------------------------------------

    // for (int i = 0; i <  hWFsumFlat_st.size(); i++){
    for (int i = 0; i <  2; i++){
      hWFsumFlat_st.at(i)->Rebin(rebin_no);
      hsWFsum->Add(hWFsumFlat_st.at(i));
      hWFsumRaw_st.at(i)->Rebin(rebin_no);
      hsWFsumRaw->Add(hWFsumRaw_st.at(i));
    }



    auto leg_WFsum = new TLegend(0.1,0.7,0.48,0.9);
    for (int i(V_PEN.size() -1); i >= 0; i--){
      char* title = Form("MESH %.0f V", V_PEN.at(i));
      leg_WFsum->AddEntry(hWFsumFlat_st.at(i),title,"l");//800
    }


    TCanvas *cWFsum = new TCanvas("cWFsum", " sum of waveform ", 1200, 600);
    cWFsum->Divide(2,1);
    cWFsum->cd(1);
    hsWFsumRaw->Draw("nostack");
    leg_WFsum->Draw("same");
    cWFsum->cd(2);
    hsWFsum->Draw("nostack");
    leg_WFsum->Draw("same");




    //-----------------------------------------------------------------
    //------------------------Making the WF Ratios---------------------
    // ----------------------------------------------------------------

    TH1D* hWFsum_Ratio800_1100 = (TH1D*)hWFsumFlat_st.at(0)->Clone();
    hWFsum_Ratio800_1100->SetTitle("Ratio of WaveForm Sums; Time [s]; Amplitude Ratio");
    TH1D* hWFsum_Ratio800_1200 =(TH1D*)hWFsumFlat_st.at(0)->Clone();
    TH1D* hWFsum_Ratio800_1400= (TH1D*)hWFsumFlat_st.at(0)->Clone();

    for (int j(0); j < hWFsumFlat_st.at(0)->GetNbinsX(); j++){
      hWFsum_Ratio800_1100->SetBinContent(j , hWFsumFlat_st.at(1)->GetBinContent(j)/hWFsumFlat_st.at(0)->GetBinContent(j));
      hWFsum_Ratio800_1200->SetBinContent(j , hWFsumFlat_st.at(2)->GetBinContent(j)/hWFsumFlat_st.at(0)->GetBinContent(j));
      hWFsum_Ratio800_1400->SetBinContent(j , hWFsumFlat_st.at(3)->GetBinContent(j)/hWFsumFlat_st.at(0)->GetBinContent(j));

    }

    hWFsum_Ratio_st.push_back(hWFsum_Ratio800_1100);
    hWFsum_Ratio_st.push_back(hWFsum_Ratio800_1200);
    hWFsum_Ratio_st.push_back(hWFsum_Ratio800_1400);



    //-----------------------------------------------------------------
    //------------------------Plotting the WF Ratios---------------------
    // ----------------------------------------------------------------


    TCanvas *cRatios = new TCanvas("cRatios","" ,800,600);

    for (int i(0); i< hWFsum_Ratio_st.size(); i++){
      hWFsum_Ratio_st.at(i)->SetLineColor(color_st.at(i));
      hWFsum_Ratio_st.at(i)->SetLineWidth(1);
      hWFsum_Ratio_st.at(i)->Draw("same");
      hWFsum_Ratio_st.at(i)->GetXaxis()->SetRangeUser(-0.035e-3,0.015e-3);
    }

    auto leg_Ratios = new TLegend(0.1,0.7,0.48,0.9);
    leg_Ratios->AddEntry(hWFsum_Ratio_st.at(0),"800/1100 V","l");//800
    leg_Ratios->AddEntry(hWFsum_Ratio_st.at(1),"800/1200 V","l");//1100
    leg_Ratios->AddEntry(hWFsum_Ratio_st.at(2),"800/1400 V","l");//1200
    leg_Ratios->Draw("same");



cRatios->Write();

    //----------------------------------------------------------
    //---Plotting Data Taking Quality over PEN Voltages---------
    //----------------------------------------------------------

    TCanvas * c_DataTaking = new TCanvas("","", 1000,1000);
    c_DataTaking->Divide(2,2);
    c_DataTaking->cd(1);
    TGraph *g_Spark_PENV = new TGraph(HowManySparkEvt.size(), &V_PEN[0], &HowManySparkEvt[0]);
    g_Spark_PENV ->SetLineColor(30);
    g_Spark_PENV ->SetLineWidth(4);
    g_Spark_PENV ->SetMarkerStyle(kCircle);
    g_Spark_PENV ->SetTitle("Number of sparks per data set of 12 hours; PEN Voltage [V]; No. of Sparks");
    g_Spark_PENV ->Draw("ACP");
    gPad->SetGrid();
    c_DataTaking->cd(3);
    TGraph *g_Signal_PENV = new TGraph(HowManySparkEvt.size(), &V_PEN[0], &HowManySignalEvt[0]);
    g_Signal_PENV ->SetLineColor(30);
    g_Signal_PENV ->SetLineWidth(4);
    g_Signal_PENV ->SetMarkerStyle(kCircle);
    g_Signal_PENV ->SetTitle("Number of signal events per data set of 12 hours; PEN Voltage [V]; No. of Signal Events");

g_Signal_PENV->Draw("ACP");
gPad->SetGrid();



    // TMultiGraph *mg_DataTaking = new TMultiGraph();
    // mg_DataTaking->Add(g_Spark_PENV);
    // mg_DataTaking->Add(g_Signal_PENV);
    // mg_DataTaking->Draw("ACP");

    c_DataTaking->cd(2);
    TGraph *g_Empty_PENV = new TGraph(HowManySparkEvt.size(), &V_PEN[0], &HowManyEmptyEvt[0]);
    g_Empty_PENV ->SetLineColor(30);
    g_Empty_PENV ->SetLineWidth(4);
    g_Empty_PENV ->SetMarkerStyle(kCircle);
    g_Empty_PENV ->SetTitle("Number of empty events per data set of 12 hours; PEN Voltage [V]; No. of Empty Events");
    g_Empty_PENV->Draw("APC");

    gPad->SetGrid();

c_DataTaking->Write();
    //-----------------------------------------------------------------
    //-------------------Starting the Integral Analysis----------------
    // ----------------------------------------------------------------
    // TH1D*  hIntgA_800 = (TH1D*)fPEN800->Get("integral_a");
    // TH1D*  hIntgAft_800 = (TH1D*)fPEN800->Get("integral_aft");
    // //
    // TH1D*  hIntgA_1100 = (TH1D*)fPEN1100->Get("integral_a");
    // TH1D*  hIntgAft_1100 = (TH1D*)fPEN1100->Get("integral_aft");
    // //
    // TH1D*  hIntgA_1200 = (TH1D*)fPEN1200->Get("integral_a");
    // TH1D*  hIntgAft_1200 = (TH1D*)fPEN1200->Get("integral_aft");
    // //
    // //   // TH1D*  hIntgA_1300 = (TH1D*)fPEN1300->Get("integral_a");
    // //   // TH1D*  hIntgAft_1300 = (TH1D*)fPEN1300->Get("integral_aft");
    // //
    // TH1D*  hIntgA_1400 = (TH1D*)fPEN1400->Get("integral_a");
    // TH1D*  hIntgAft_1400 = (TH1D*)fPEN1400->Get("integral_aft");

    // TH1D*  hIntgA_1500 = (TH1D*)fPEN1500->Get("integral_a");
    // TH1D*  hIntgAft_1500 = (TH1D*)fPEN1500->Get("integral_aft");



    //   TH1D*  hIntgBef_800 = (TH1D*)fPEN800->Get("integral_bef");
    //   TH1D*  hIntgBef_1100 = (TH1D*)fPEN1100->Get("integral_bef");
    //   TH1D*  hIntgBef_1200 = (TH1D*)fPEN1200->Get("integral_bef");
    //   // TH1D*  hIntgBef_1300 = (TH1D*)fPEN1200->Get("integral_bef");
    //   TH1D*  hIntgBef_1400 = (TH1D*)fPEN1400->Get("integral_bef");
    //   // TH1D*  hIntgBef_1500 = (TH1D*)fPEN1500->Get("integral_bef");
    //
    //   TH1D* hIntgBkgSub_800 = (TH1D*)hIntgA_800->Clone();
    //   TH1D* hIntgBkgSub_1100 = (TH1D*)hIntgA_1100->Clone();
    //   TH1D* hIntgBkgSub_1200 = (TH1D*)hIntgA_1200->Clone();
    //   // TH1D* hIntgBkgSub_1300 = (TH1D*)hIntgA_1300->Clone();
    //   TH1D* hIntgBkgSub_1400 = (TH1D*)hIntgA_1400->Clone();
    //   // TH1D* hIntgBkgSub_1500 = (TH1D*)hIntgA_1500->Clone();
    //
    //   hIntgBkgSub_800  ->SetTitle("PMESH 800; Number of Photons ");
    //   hIntgBkgSub_1100  ->SetTitle("PMESH 1000; Number of Photons ");
    //   hIntgBkgSub_1200  ->SetTitle("PMESH 1200; Number of Photons ");
    //   // hIntgBkgSub_1300  ->SetTitle("PMESH 1300; Number of Photons ");
    //   hIntgBkgSub_1400  ->SetTitle("PMESH 1400; Number of Photons ");
    //   // hIntgBkgSub_1500  ->SetTitle("PMESH 1500; Number of Photons ");
    //
    //
    //
    //   for (int i(0); i < hIntgA_800->GetNbinsX(); i++){
    //     hIntgBkgSub_800->SetBinContent(i, hIntgA_800->GetBinContent(i) - hIntgBef_800->GetBinContent(i));
    //     hIntgBkgSub_1100->SetBinContent(i, hIntgA_1100->GetBinContent(i) - hIntgBef_1100->GetBinContent(i));
    //     hIntgBkgSub_1200->SetBinContent(i, hIntgA_1200->GetBinContent(i) - hIntgBef_1200->GetBinContent(i));
    //     // hIntgBkgSub_1300->SetBinContent(i, hIntgA_1300->GetBinContent(i) - hIntgBef_1300->GetBinContent(i));
    //     hIntgBkgSub_1400->SetBinContent(i, hIntgA_1400->GetBinContent(i) - hIntgBef_1400->GetBinContent(i));
    //     // hIntgBkgSub_1500->SetBinContent(i, hIntgA_1500->GetBinContent(i) - hIntgBef_1500->GetBinContent(i));
    //   }
    //
    //   hIntgA_800->SetLineColor(kBlue);
    //   hIntgA_1100->SetLineColor(kRed);
    //   hIntgA_1200->SetLineColor(kBlack);
    //   // hIntgA_1300->SetLineColor(kCyan);
    //   hIntgA_1400->SetLineColor(kMagenta);
    //   // hIntgA_1500->SetLineColor(kMagenta);
    //
    //   hIntgBkgSub_800->SetLineColor(kBlue);
    //   hIntgBkgSub_1100->SetLineColor(kRed);
    //   hIntgBkgSub_1200->SetLineColor(kBlack);
    //   // hIntgBkgSub_1300->SetLineColor(kCyan);
    //   hIntgBkgSub_1400->SetLineColor(kMagenta);
    //   // hIntgBkgSub_1500->SetLineColor(kRose);
    //
    //   hIntgBkgSub_800->SetLineWidth(1);
    //   hIntgBkgSub_1100->SetLineWidth(1);
    //   hIntgBkgSub_1200->SetLineWidth(1);
    //   // hIntgBkgSub_1300->SetLineWidth(1);
    //   hIntgBkgSub_1400->SetLineWidth(1);
    //   // hIntgBkgSub_1500->SetLineWidth(1);
    //
    //   hIntgA_800->SetLineWidth(1);
    //   hIntgA_1100->SetLineWidth(1);
    //   hIntgA_1200->SetLineWidth(1);
    //   // hIntgA_1300->SetLineWidth(1);
    //   hIntgA_1400->SetLineWidth(1);
    //   // hIntgA_1500->SetLineWidth(1);
    //
    //
    //   //
    //   //
    //   // hIntgA_800->Rebin(rebin_no);
    //   // hIntgA_1100->Rebin(rebin_no);
    //   // hIntgA_1200->Rebin(rebin_no);
    //   // hIntgA_1300->Rebin(rebin_no);
    //   // hIntgA_1400->Rebin(rebin_no);
    //
    //   // hIntgBef_800->Rebin(rebin_no);
    //   // hIntgBef_1100->Rebin(rebin_no);
    //   // hIntgBef_1200->Rebin(rebin_no);
    //   // hIntgBef_1300->Rebin(rebin_no);
    //   // hIntgBef_1400->Rebin(rebin_no);
    //
    //   THStack *hs = new THStack("hs", "");
    //   TCanvas * cIntg_all =  new TCanvas("hIntegral_all" ,"Integrals_all", 800,600);
    //
    //   // hs -> Add(hIntgA_1100);
    //   // hs -> Add(hIntgA_1200);
    //   // hs -> Add(hIntgA_800);
    //   // hs-> Draw("nostack");
    //   auto legend_2 = new TLegend(0.1,0.7,0.48,0.9);
    //   legend_2->AddEntry(hIntgA_800,"PEN MESH 800 V","l");
    //   legend_2->AddEntry(hIntgA_1100,"PEN MESH 1000 V","l");
    //   legend_2->AddEntry(hIntgA_1200,"PEN MESH 1200 V","l");
    //   // legend_2->AddEntry(hIntgA_1300,"PEN MESH 1300 V","l");
    //   legend_2->AddEntry(hIntgA_1400,"PEN MESH 1400 V","l");
    //   // legend_2->AddEntry(hIntgA_1500,"PEN MESH 1500 V","l");
    //
    //
    //
    //
    //   hIntgA_800->Draw();
    //   // hIntgA_1100->Draw("same");
    //   hIntgA_1200->Draw("same");
    //   // hIntgA_1300->Draw("same");
    //   hIntgA_1400->Draw("same");
    //   legend_2->Draw();
    //   hIntgA_800->GetXaxis()->SetRangeUser(0,15e3);
    //   hIntgA_1100->GetXaxis()->SetRangeUser(0,15e3);
    //   hIntgA_1200->GetXaxis()->SetRangeUser(0,15e3);
    //   // hIntgA_1300->GetXaxis()->SetRangeUser(0,15e3);
    //   hIntgA_1400->GetXaxis()->SetRangeUser(0,15e3);
    //   gPad->SetLogy();
    //
    //
    //
    //
    //
    //   TCanvas * cIntg =  new TCanvas("hIntegral","Integrals", 800,1200);
    //   cIntg->Divide(2,3);
    //
    //   cIntg->cd(1);
    //   gPad->SetLogy();
    //   hIntgA_800->SetTitle("PMESH 800; Number of Photons ");
    //   // hIntgA_800->Fit(f1);
    //   // hIntgA_800->Fit(exp_);
    //   hIntgA_800->Draw();
    //
    //   cIntg->cd(2);
    //   gPad->SetLogy();
    //   hIntgBef_800->Draw();
    //   hIntgBef_800->SetTitle("PMESH 800; Number of Photons ");
    //
    //   cIntg->cd(3);
    //   gPad->SetLogy();
    //   // hIntgA_1100->Fit(f1);
    //   hIntgA_1100->Draw();
    //   hIntgA_1100->SetTitle("PMESH 1000; Number of Photons ");
    //
    //   cIntg->cd(4);
    //   gPad->SetLogy();
    //   hIntgBef_1100->SetTitle("PMESH 1000; Number of Photons ");
    //   hIntgBef_1100->Draw();
    //
    //
    //   cIntg->cd(5);
    //   gPad->SetLogy();
    //   hIntgA_1200->SetTitle("PMESH 1200; Number of Photons ");
    //   // hIntgA_1200->Fit(f1);
    //   hIntgA_1200->Draw();
    //
    //   cIntg->cd(6);
    //   hIntgBef_1200->SetTitle("PMESH 1200; Number of Photons ");
    //   hIntgBef_1200->Draw();
    //   gPad->SetLogy();
    //
    //
    //
    //
    //
    //
    //   auto legend_3 = new TLegend(0.1,0.7,0.48,0.9);
    //   legend_3->AddEntry(hIntgBkgSub_1400,"PEN MESH 3.24 kV/cm","l");
    //   // legend_3->AddEntry(hIntgBkgSub_1300,"PEN MESH 3.0 kV/cm","l");
    //   legend_3->AddEntry(hIntgBkgSub_1200,"PEN MESH 2.79 kV/cm","l");
    //   legend_3->AddEntry(hIntgBkgSub_1100,"PEN MESH 2.32 kV/cm","l");
    //   legend_3->AddEntry(hIntgBkgSub_800,"PEN MESH 1.86 kV/cm","l");
    //
    //   TCanvas *cBkgSub = new TCanvas ("cBkgSub", "Bkg Sub", 800,600);
    //   cBkgSub->Divide(2,1);
    //   hIntgBkgSub_800->Rebin(rebin_no);
    //   hIntgBkgSub_1100->Rebin(rebin_no);
    //   hIntgBkgSub_1200->Rebin(rebin_no);
    //   // hIntgBkgSub_1300->Rebin(rebin_no);
    //   hIntgBkgSub_1400->Rebin(rebin_no);
    //   // hIntgBkgSub_1500->Rebin(rebin_no);
    //
    //
    //
    //
    //
    // //  hIntgBkgSub_800->Draw();
    // cBkgSub->cd(1);
    //   hIntgBkgSub_1100->Draw();
    //   //hIntgBkgSub_1200->Draw("same");
    //   gPad->SetLogy();
    //   cBkgSub->cd(2);
    //   // hIntgBkgSub_1500->Draw();
    //   // hIntgBkgSub_1300->Draw("same");
    //   hIntgBkgSub_1400->Draw("same");
    //
    //
    //   // double norm800  =  hIntgBkgSub_1100->GetEntries() / hIntgBkgSub_800->GetEntries();
    //   // double norm1000 = hIntgBkgSub_1100->GetEntries() / hIntgBkgSub_1100->GetEntries();
    //   // double norm1200 = hIntgBkgSub_1100->GetEntries() / hIntgBkgSub_1200->GetEntries();
    //   // double norm1300 = hIntgBkgSub_1100->GetEntries() / hIntgBkgSub_1300->GetEntries();
    //   // double norm1400 = hIntgBkgSub_1100->GetEntries() / hIntgBkgSub_1400->GetEntries();
    //
    //
    //   // double norm800 =   hIntgBkgSub_800 ->GetBinContent(hIntgBkgSub_800-> GetMaximumBin());
    //   // double norm1000 =   hIntgBkgSub_1100 ->GetBinContent(hIntgBkgSub_1100-> GetMaximumBin());
    //   // double norm1200 =   hIntgBkgSub_1200 ->GetBinContent(hIntgBkgSub_1200-> GetMaximumBin());
    //   // double norm1300 =   hIntgBkgSub_1300 ->GetBinContent(hIntgBkgSub_1300-> GetMaximumBin());
    //   // double norm1400 =   hIntgBkgSub_1400 ->GetBinContent(hIntgBkgSub_1400-> GetMaximumBin());
    //
    //   double norm800 =   hIntgBkgSub_800 ->GetEntries();
    //   double norm1000 =   hIntgBkgSub_1100 ->GetEntries();
    //   double norm1200 =   hIntgBkgSub_1200 ->GetEntries();
    //   // double norm1300 =   hIntgBkgSub_1300 ->GetEntries();
    //   double norm1400 =   hIntgBkgSub_1400 ->GetEntries();
    //   // double norm1500 =   hIntgBkgSub_1500 ->GetEntries();
    //
    //
    //
    //
    //   hIntgBkgSub_800->Scale(1./norm800);
    //   hIntgBkgSub_1100->Scale(1./norm1000);
    //   hIntgBkgSub_1200->Scale(1./norm1200);
    //   // hIntgBkgSub_1300->Scale(1./norm1300);
    //   hIntgBkgSub_1400->Scale(1./norm1400);
    //   // hIntgBkgSub_1500->Scale(1./norm1500);
    //
    //
    //
    //   hIntgBkgSub_800->GetXaxis()->SetRangeUser(0,15e3);
    //   hIntgBkgSub_1100->GetXaxis()->SetRangeUser(0,15e3);
    //   hIntgBkgSub_1200->GetXaxis()->SetRangeUser(0,15e3);
    //   // hIntgBkgSub_1300->GetXaxis()->SetRangeUser(0,15e3);
    //   hIntgBkgSub_1400->GetXaxis()->SetRangeUser(0,15e3);
    //   // hIntgBkgSub_1500->GetXaxis()->SetRangeUser(0,15e3);
    //
    //
    // cout <<" PEN MESH 800 signal events: " << hIntgA_800->GetEntries() << endl;
    // cout <<" PEN MESH 1000 signal events: " << hIntgA_1100->GetEntries() << endl;
    // cout <<" PEN MESH 1200 signal events: " << hIntgA_1200->GetEntries() << endl;
    // // cout <<" PEN MESH 1300 signal events: " << hIntgA_1300->GetEntries() << endl;
    // cout <<" PEN MESH 1400 signal events: " << hIntgA_1400->GetEntries() << endl;
    // // cout <<" PEN MESH 1500 signal events: " << hIntgA_1500->GetEntries() << endl;
    //
    //
    //   legend_3->Draw("same");
    //   gPad->SetLogy();

  }
