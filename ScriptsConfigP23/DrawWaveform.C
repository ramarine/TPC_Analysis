// This works with Configuration_17, 18
// Plots many figures investigating the time distributions of signals in events.

//updated at 14September2022
//this is a newer version than the one used in the SharedScripts Folder
#include "TRandom.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TMath.h"
#include <vector>
#include <math.h>       /* pow */
#include <iostream>

using namespace std::chrono;
using namespace std;


double GetDivError(double nom, double denom, double nom_err, double denom_err){
  return TMath::Sqrt(((nom_err*nom_err) / (denom*denom) ) + (nom*nom * denom_err*denom_err)/(denom*denom*denom*denom));
}


std::vector<double> AddWf(std::vector<double> *wf = NULL, std::vector<double> *rms = NULL,std::vector<double> wf_init = std::vector<double> (100000, 0), double NSigmas = 4.0 ){
  
  for (int i(0); i < wf->size(); i++){
    if (wf->at(i) < -NSigmas *rms->at(i))
      wf_init.at(i) += wf->at(i);
  }

  return wf_init;
} 


void PlotMultiWF(std::vector<int> idx,std::vector<TH1*> hist ,const char * file_name){

  TCanvas *c1 = new TCanvas("c1","sub data",200,10,700,500);

  const char * file_ = "h1.pdf";
  string first = std::string(file_)+std::string("(");
  string last =std::string(file_) +std::string(")");
  string mid = std::string(file_);
  

  
  for (int i(0); i < idx.size(); i++){
    //char first = file_name.c_str+"(";
    //char last = file_name.c_str+")";
    if (i==0){
      hist[i]->Draw();
      c1->Print(first.c_str(),"pdf0");
    }else if (i == idx.size() -1 ){
      hist[i]->Draw();
      c1->Print(last.c_str(),"pdf2");
    }else{
      hist[i]->Draw();
      c1->Print(file_name,"pdf1");
    }
  }




}

void DrawWaveform(){

  bool PlotSparks = false;

  TH1F *hWF_sum = new TH1F ("hWF_sum"," The sum of ", 100000, -20,80); 
  //  double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1e7 for 1650V (Hamamtsu R6427)
  //double con_fact = - dt /(R* gain *e_ch*qe*col_eff);
  double con_fact = -0.05;
  std::vector<double> key_idx;
  std::vector<double> key_Intg;
  std::vector<double> key_min_a;

  // double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8), dt(1e-9);//gain = 1e7 for 1650V (Hamamtsu R6427)
  // double con_fact = - dt /(R* gain *e_ch*qe*col_eff);

  auto start = high_resolution_clock::now();

  std::vector<TString> path_store;


  path_store.push_back("../../../Swan_TTrees/Configuration_P23/C3800_LSF1780_ThGUp1400_ThGDnGND_PMesh0_TPC1650/");


  TString NSigmas_st = "4.0";
  double NSigmas = 6.0;
  std::vector<int> sig_evt;

  std::unique_ptr<TFile> myFile(TFile::Open(path_store.at(0)+"WF_output_1000_"+NSigmas_st+"RMS.root"));
  auto tree = myFile->Get<TTree>("T");
  std::vector<int> Spark_idx;
  std::vector<int> BadPed_idx;
  std::vector<int> Signal_idx;
  std::vector<int> Empty_idx;
  std::vector<double> intg_bef;
  std::vector<double> intg_aft;
  std::vector<double> intg_a;
  std::vector<double> intg_b;
  std::vector<double> dummy_intg(4,0);



  // std::vector<std::vector<double>> wf_store;
  // std::vector<std::vector<double>> rms_store;

  std::vector<double> *wf = new std::vector<double>;
  std::vector<double> *rms = new std::vector<double>;
  std::vector<int> MinIdxPerEvt;
  std::vector<int> signal_evt_idx;
  std::vector<int> spark_evt_idx;

  int trig_idx, nentries;
  Double_t dt, t0;
  Int_t  Signal, Spark;

  tree->SetBranchAddress("WF", &wf);
  tree->SetBranchAddress("RMS", &rms);
  tree->SetBranchAddress("dt", &dt);
  tree->SetBranchAddress("t0", &t0);
  tree->SetBranchAddress("trig_idx", &trig_idx);
  tree->SetBranchAddress("nentries", &nentries);
  tree->SetBranchAddress("Signal", &Signal);
  tree->SetBranchAddress("Spark", &Spark);

  tree->GetEntry(0);
  TH1F *hWF = new TH1F ("hWF","", nentries, -20,80); 

  std::vector<double> wf_sum(nentries, 0);

  

  TBranch *BSignal = tree->GetBranch("Signal"); 
  TBranch *BSpark = tree->GetBranch("Spark"); 

  std::vector<std::vector<int>> integral_500_signal_a;// this is a container keeping all the entries higher than the treshold
  std::vector<std::vector<int>> integral_500_signal_b;

  int tot_evt = 0;
  if (PlotSparks == true)  tot_evt = tree->GetBranch("Spark")->GetEntries();
  else tot_evt = tree->GetBranch("Signal")->GetEntries();
  //  cout << TrigTimeIdx << " " << a_idx << " " << ab_idx << endl;
  TCanvas *cEventDisplay = new TCanvas("event_display","dum_display",0,0,800,600);
  const char * file_name = "h1.pdf";
  int wf_count =0;
  
  string first = std::string(file_name)+std::string("(");
  string last =std::string(file_name) +std::string(")");
  string mid = std::string(file_name);
  cout << "There are " << tot_evt << " sparks " << endl;

  for (int i(0); i < tot_evt; i++){       
    tree -> GetEntry(i);
    signal_evt_idx.push_back(Signal);
    spark_evt_idx.push_back(Spark);
    //cout << "Get Entry " << Signal<< endl;
  } 

  int HowManyWfToDraw= 0;
  if (PlotSparks == true)  HowManyWfToDraw = spark_evt_idx.size();
  else  HowManyWfToDraw = signal_evt_idx.size();
  

  TFile *outPlots =  TFile::Open(Form("Spark_WFs_EVT%d.root",HowManyWfToDraw ), "recreate");  

  for (int i(0); i < HowManyWfToDraw; i++ ){
    int incr_a = 0;
    int incr_b = 0;
    if (PlotSparks == true) tree->GetEntry(spark_evt_idx.at(i));
    else tree->GetEntry( signal_evt_idx.at(i) );
    
    for (int j(0); j< wf->size(); j++){
      hWF->SetBinContent(j+1,wf->at(j));
    }
    hWF->Write();
    hWF->Reset("ICESCM");
    // bool print == true; 
    
  }

  
  


  
  std::vector<double> time;
  cout << " nentries " << nentries << " t0 " << t0 << " dt " << dt <<endl; 
  for (int i(t0); i < nentries; i++){
    time.push_back(-20e-6 + i*dt);
    //cout << "time " << time.at(i)<<endl;
  }
  
  
  cout << "debug " << endl;
  
  

  
  // for (int i(0); i < tot_evt; i++){
    
  //   tree->GetEntry(i);
  //   cout << "signal " << Signal << endl;
  //   tree->GetEntry(Signal);
  //   wf_sum =  AddWf(wf,rms,wf_sum,NSigmas);
  //   bool print =  false;
  //   int No_waveforms = 3;
    
    //if (print == true && wf_count< No_waveforms){
      
    // 	tree->GetEntry(i);
    // 	cout << "signal " << Signal << endl;
    // 	tree->GetEntry(Signal);
    // 	for (int j(0); j< wf->size(); j++){
    // 	  hWF->SetBinContent(j+1,wf->at(j));
    // 	}
    // 	hWF->Draw();
    // 	wf_count++;
    
    
    // 	//if (wf_count == 0)    cEventDisplay->Print(first.c_str(),"pdf0");
    // 	//else if (wf_count == No_waveforms -1)    cEventDisplay->Print(last.c_str(),"pdf2");
    // 	//else cEventDisplay->Print(mid.c_str(),"pdf1");
    // }
    
      
    
    


  //} 



  

  
  
  
  
  outPlots->Close();

    

}

