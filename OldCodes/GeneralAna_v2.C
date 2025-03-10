//read binary files to arrays

//compared to GeneralAna, here I am going to output struct instead of tuples.

#include <TROOT.h>
#include <TH2D.h>
#include <TH1D.h>
#include <TMath.h>
#include <TRandom.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <TFile.h>
#include <cmath>
#include <chrono>
using namespace std::chrono;

using namespace std;



const float NSigmas = 3.0;
const int NPeds = 200;
TH1* hADC_dump = new TH1F("ADC_dump"," ADC ; ADC amplitude [V];", 200, -1.5, 0.5 );
const double spark_tresh = -1.2;
const double  spark_tresh_gl = -1.2;
const double  up_spark_tresh_gl = 0.2;


//define structure in order to store the values from the 
struct BinaryComponents{
    std::vector<std::vector<double>> Ampl_TPC;
    std::vector<std::vector<double>> Rms_TPC;
    std::vector<int> Min_idx;
    double T0;
    double Dt;
    int Trig_idx;
    int Nentries;
   
    

};

 double ConvertToPhot(double Amplitude, double dt){
     double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8);//gain = 1e7 for 1650V (Hamamtsu R6427)
     return Amplitude * (-dt) /(R* gain *e_ch*qe*col_eff);
 }    
//------------------------********************--------------------
//                      Function to output the adc - ped in a vector of vectors
//-----------------------*********************---------------------


//input the event path and it outputs a vector with the values (adc - ped)




std::tuple<std::vector<double>, std::vector<double>, double, int> ADC_Ped_Subtracted(  vector<double>& adc, const int NPeds = 200, double NSigmas = 4. , int evt = -1 , double spark_tresh_local = -1.2, double up_spark_tresh_local = 0.2,  TFile *WF_output = NULL, double t0 =0., double dt = 0.   ){
   // cout << "t0 = " << t0 << " dt= " << dt << endl; 
  // amplitude vector, tresh vector, min, index where minimum occurs. Here minumum means the biggest signal
  std::vector<double> adc_subtracted;
  std::tuple<std::vector<double>, std::vector<double>, double, int> dum_vec;// amplitude vector, tresh vector, min, index where minimum occurs. Here minumum means the biggest signal.

  std::vector<double> spark_adc(1,-999);
  std::vector<double> bad_PedSub_adc(1, -888);
  std::vector<double> spark_rms(1,-999);
    

 

  //dum_vec.push_back(-1e6);

  // filename = path+"C4Test0006.txt";


  double n,t;
//  std::vector<float> adc;
  //std::vector<float> time;
  std::vector<double> pedv;
  std::vector<double> threshv;

  string ch;
  int nv;
  double a1,a2,sampling;
  string line;




  Long64_t nentries = adc.size();

  //  std::cout << "Trig Time " << time.at(TrigTimeIdx) << " at " << TrigTimeIdx << endl;
  //  std::cout << "Drift Time " << time.at(a_idx) << " extended_drift_time " << time.at(ab_idx) << endl;


  if( nentries < NPeds ) return dum_vec;

  double ped = 0;
  double ped2 = 0;

  //*********
  //calculate simple baseline for
  //*********
  for( int i = 0; i < NPeds; i++ ) {
    //  cout << "adc[i]= " << adc[i] << endl;
    ped += adc[i]/NPeds;
    ped2 += adc[i]*adc[i]/NPeds;
  }

  double rms = TMath::Sqrt(ped2-ped*ped); // determine rms
  double thres = NSigmas*rms;

  double pedsaved = ped;
  ped = ped2 = 0;
  double iped = 0;


  double min = 100000;

  //************************
  //calculate pedestal for the first 200 entries, only for adc smaller than NSigmas* rms
  //************************

  for( int i = 0; i < NPeds; i++ ) {
    if( TMath::Abs(adc[i]-pedsaved) < thres ) {
      ped += adc[i];
      ped2 += adc[i]*adc[i];
      iped++;
    }
    if( TMath::Abs(adc[i]-adc[i+1]) < min && TMath::Abs(adc[i]-adc[i+1])  > 0   ) min = TMath::Abs( adc[i]-adc[i+1] );
  }

  ped /= iped;
  ped2 /= iped;

  rms = TMath::Sqrt(ped2-ped*ped);
  thres = NSigmas*rms;

  pedsaved = ped;
  double thressaved = thres;

  //*********************
  // Now compute the pedestals for 200, 201, 202, 203 etc.. and save them to pedv. each
  //*******************

  for(int i = 0; i < nentries; i++ ) {
    if( TMath::Abs(adc[i]-adc[i+1]) < min && TMath::Abs(adc[i]-adc[i+1]) > 0 ) min = TMath::Abs( adc[i]-adc[i+1] );
    double pp = ped*iped;
    double pp2 = ped2*iped;
    if( i >= NPeds ) {
      if( TMath::Abs(adc[i]-ped) < thres ) {pp += adc[i]; pp2+=adc[i]*adc[i]; iped++;}
      if( TMath::Abs(adc[i-NPeds]-pedv[i-NPeds]) < threshv[i-NPeds] ) {pp -= adc[i-NPeds]; pp2-=adc[i-NPeds]*adc[i-NPeds]; iped--;} // Remove it if it was used.
    }

    //if( iped > NPeds ) std::cout << " Error " << iped << "  > " <<  NPeds  << std::endl;
    //    std::cout << iped << std::endl;

    pedv.push_back(pp/iped); // Same pedestal used in this sample calculation
    threshv.push_back(thres);

    ped = pp/iped;
    ped2 = pp2/iped;

    thres = NSigmas*TMath::Sqrt(ped2-ped*ped);

    if( thres < min ) thres = NSigmas*min;

    if( ped2 < ped*ped ) {thres = NSigmas* min;}

  }



  double cadc = 0.;

  int iaccum = 0;
  double accum = 0;
  static TH1F *WF_spark = NULL;
  if( WF_spark )
  WF_spark->Reset();
  else
  WF_spark = new TH1F("WF_spark","  ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));



  for(int i = 0; i < nentries; i++ ) {
    ped = pedv[i];
    cadc += adc[i]-ped;  
    
    if (isnan(adc[i]-ped) || isinf(adc[i]-ped)){
      adc_subtracted.push_back(0.);        
      return  std::make_tuple(bad_PedSub_adc,spark_rms, -999 , 2 );
    }
    else adc_subtracted.push_back(adc[i]-ped);
   
      
  //  if (adc[i]-ped > 1.5) cout<<  "adc - iped " << adc[i]-ped << endl;
   // if (isnan(adc[i]-ped) || isinf(adc[i]-ped)) cout << "here i am with infinity " << endl;
      hADC_dump->Fill(adc[i]-ped);
         // if (isnan(adc[i]-ped) || isinf(adc[i]-ped)) cout << "here i filled a histo with infinity " << endl;
//              if (isnan(adc[i]-ped) || isinf(adc[i]-ped)) cout << "do i crush when setting the bin content to WF_spark?" << endl;

    WF_spark->SetBinContent(i+1,adc[i]);
  }

  std::vector<double> rmsv(threshv.size());
  for (int i(0); i < threshv.size(); i++){
    rmsv[i] = (threshv[i]/NSigmas);
  }

  if (WF_spark->GetBinContent(WF_spark-> GetMinimumBin()) < spark_tresh_local || WF_spark->GetBinContent(WF_spark-> GetMaximumBin()) > up_spark_tresh_local  ){
    WF_spark->SetName(Form("evt_%d", evt));
    WF_output->cd("Sparks");
    WF_spark->Write();
    //WF_output->Close();
    return std::make_tuple(spark_adc,spark_rms, -999 , 2 );
  }

  return std::make_tuple(std::move(adc_subtracted), std::move(rmsv), WF_spark->GetBinContent(WF_spark-> GetMinimumBin()), WF_spark-> GetMinimumBin() );

}



//-------------------------------------------********************--------------------------------------------------------
//                                         Define Integral function
//------------------------------------------*********************--------------------------------------------------------


std::vector <double> Integral(std::vector<double> &adc, std::vector<double> &rmsv, std::vector<double> &time,   double NSigmas = 4, TH1D *single = NULL, TH1D * single_pos = NULL, int evt = -1, TFile *WF_output = NULL, double t0 = 0, double dt = 0, const int TrigTimeIdx = 0, const int a_idx = 0,const int ab_idx = 0. ) {


   bool plotfig = false;


  // cout << " Trig Time Index " << TrigTimeIdx << endl;
  // cout << " Index at end of drift " << a_idx << endl;
  // cout << " Index at end of extended drift " << ab_idx << endl;
  //std::cout << "Calculate (Integral)s " << endl;


  std::vector <double> dum_vec(1,-1000000);


  double n,t;


  std::vector<double> pedv;

  string ch;
  int nv;
  double a1,a2,sampling;
  string line;




  Long64_t nentries = adc.size();

        




  static TH1F *WF = NULL;
  if( WF )
  WF->Reset();
  else
  WF = new TH1F("WF","  ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));

  static TH1F *Cum = NULL;
  if( Cum )
  Cum->Reset();
  else
  Cum = new TH1F("Cum","  ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));

  static TH1F *Thr = NULL;
  if( Thr )
  Thr->Reset();
  else
  Thr = new TH1F("Thr","  ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));





  double cadc = 0.;
  int iaccum = 0;
  double accum = 0;
  int iaccum_pos = 0;
  double accum_pos = 0;

  for(int i = 0; i < nentries; i++ ) {
    hADC_dump->Fill(adc[i]);

    if (adc[i] < - rmsv[i]*NSigmas) cadc += adc[i];// variable being passed to the Cum  TH1. Basicaly each entry in this histogram represents the integral up to that point.
    if (single){
      if(adc[i] < -rmsv[i]*NSigmas){
        accum += (adc[i]);
        iaccum++;
      }
      else{
        if(  iaccum == 2 || iaccum == 3 ) single->Fill(accum);
        iaccum = 0;
        accum = 0;
      }
    }

    if (single_pos){
      if(adc[i] > rmsv[i]*NSigmas){
        accum_pos += (-adc[i]);
        iaccum_pos++;
      }
      else{
        if(  iaccum_pos == 2 || iaccum_pos == 3 ) single_pos->Fill(accum_pos);
        iaccum_pos = 0;
        accum_pos = 0;
      }

    }




    WF->SetBinContent(i+1,adc[i]);
    Cum->SetBinContent(i+1,cadc);
    Thr->SetBinContent(i+1,rmsv[i]);





    if( plotfig ) {

      TCanvas *c =  new TCanvas("c"," ",800,800);
      c->Divide(1,4);

      c->cd(2);
      WF->Draw("Hist");
      c->cd(3);
      Cum->Draw("Hist"); Cum->SetLineColor(2);
      c->Update();
    }
  }



  std::vector<double> intg_vect;  
  double IntgNormBef = (time[TrigTimeIdx]-t0);    
  double IntgNormAft = (time[nentries]-time[TrigTimeIdx]);    
  double IntgNormA = (time[a_idx]-time[TrigTimeIdx]);    
  double IntgNormAB = (time[ab_idx]-time[TrigTimeIdx]);
    
  // cout << " Intg Bef " <<IntgNormBef << "  Intg Aft " << IntgNormAft << " Intg A " <<  IntgNormA << "  Intg AB " << IntgNormAB<< "  " <<endl;
  intg_vect.push_back(Cum->GetBinContent(TrigTimeIdx) /(IntgNormBef/IntgNormA));
  intg_vect.push_back((Cum->GetBinContent(nentries) - Cum->GetBinContent(TrigTimeIdx))/(IntgNormAft/IntgNormA));
  intg_vect.push_back((Cum->GetBinContent(a_idx) - Cum->GetBinContent(TrigTimeIdx))/(IntgNormA/IntgNormA));
  //intg_vect.push_back(Cum->GetBinContent(a_idx) - Cum->GetBinContent(TrigTimeIdx));
  intg_vect.push_back((Cum->GetBinContent(ab_idx) - Cum->GetBinContent(TrigTimeIdx))/(IntgNormAB/IntgNormA));

  double int_a_store = ConvertToPhot(intg_vect[2],dt); 
  if (WF_output){

    //      WF->SetTitle(Form("Number of Photons In the Drift Period %f", -  dt /(R* gain *e_ch*qe*col_eff)*(IntgNormA/IntgNormA)));
    WF->SetTitle(Form("Number of Photons In the Drift Period %f", int_a_store ));
    WF->SetName(Form("evt_%d", evt));
    if   (int_a_store <100)    {
      WF_output->cd("integral_0_100");
      WF->Write();
    } else if(100 < int_a_store && int_a_store  < 500 ){
      WF_output->cd("integral_100_500");
      WF->Write();
    }else{
      WF_output->cd("integral_500");
      WF->Write();
    }


  }

  return intg_vect;

}


//------------------------********************------------------------------------------------------------------------------
//                       ReadBinary then to subtract pedestal and then to output a tuple with everything
//-----------------------*********************------------------------------------------------------------------------------



BinaryComponents read_binary_3( string path ="/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650_test", string path_prefix_data = "../../Swan_Data",string path_prefix_AnaResults = "../../Swan_TTrees" , const int tot_evt = 1 , TFile * WF_output = NULL){
 //return ampl_tpc, rms_tpc, min_idx ,t0, dt, trig_idx, nentries
 
  std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<double>>, std::vector<int> , double,const int, int> dum_tup;

  
 
 string binfilepath = path_prefix_data+path+"/binary_dat";
 FILE *readfile;

 readfile = fopen(binfilepath.c_str(), "r");

 const int sd = sizeof(double); //we define this to save a bit of time by not having to fetch it each time we read

 double t0;
 double dt;
 int nentries;
 int trig_idx;
 char name[100];

 //first, read the header.
 //name
 fread(&name, sizeof(char), 100, readfile);
 //cout << "Name of file is " << name << endl;
// cout << " 1 " << endl;
 //t0
 fread(&t0, sd, 1, readfile);
 //cout << "t0 = "<< t0 << endl;
// cout << " 2 " << endl;
 //dt
 fread(&dt, sd, 1, readfile);
 //cout << "dt = " << dt << endl;
// cout << " 3 " << endl;
 //n_entries_per_file
 fread(&nentries, sizeof(int), 1, readfile);
 //cout << "Number of entries per file = " << nentries << endl;
// cout << " 4 " << endl;
 //trigger index
 fread(&trig_idx, sizeof(int), 1, readfile);
 //cout << "Index of scintillator minimum = " << trig_idx << endl;
//cout << " 5 " << endl;
 vector<vector<double>> ampl_TPC(tot_evt, (vector<double>(nentries)));
 vector<vector<double>> rms_TPC(tot_evt, (vector<double>(nentries)));
//  vector<vector<double>> ampl_TPC;
//  vector<vector<double>> rms_TPC;

    std::vector<int> min_idx(nentries, 0);

    for (int evt = 0; evt<tot_evt; evt++){
       // cout << "evt " << evt << endl;
     for (int entry = 0; entry<nentries; entry++){
        fread(&(ampl_TPC[evt][entry]), sd, 1, readfile);
        //if (entry < 5)  cout << "ampl_tpc[evt][entry] " << ampl_TPC[evt][entry] << endl; 
     }
        auto adc_and_tresh = ADC_Ped_Subtracted(  ampl_TPC[evt], NPeds ,  NSigmas , evt , spark_tresh, up_spark_tresh_gl ,  WF_output,  t0 ,  dt  );
        ampl_TPC[evt] = std::move(get<0>(adc_and_tresh));
        rms_TPC[evt] = std::move(get<1>(adc_and_tresh));
        //double min = get<2>(adc_and_tresh);
        min_idx[evt] = get<3>(adc_and_tresh);
        //Put your code which does the per-event analysis here.

    }

    //Put your code to do the analysis of the full dataset here.


//    BinaryComponents bin(&ampl_TPC, &rms_TPC,&min_idx, t0, dt, trig_idx, nentries);
    BinaryComponents bin;
    bin.Ampl_TPC = std::move(ampl_TPC);
    bin.Rms_TPC = std::move(rms_TPC);
    bin.Min_idx = std::move(min_idx);
    bin.T0 = t0;
    bin.Dt = dt;
    bin.Trig_idx = trig_idx;
    bin.Nentries = nentries;
    
    
   return bin;
}

// struct BinaryComponents{
//     std::vector<std::vector<double>> Ampl_TPC;
//     std::vector<std::vector<double>> Rms_TPC;
//     std::vector<int> Min_idx;
//     double T0;
//     double Dt;
//     const int Trig_idx;
//     const int Nentries;
        

// };


// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------Draws the WaveForm sum--------------------------------------------
// ---------------------------------------------------------------------------------------------------------

void GetWFSum(std::vector<std::vector<double>> &ampl_TPC,  std::vector<std::vector<double>> &rmsv, std::vector<int>&sig_evt, int NSigmas = 4,   TFile *storeWF =NULL, const double t0 = 0, const double dt = 0){
  // int nentries = ampl_TPC[0].size();
  // std::vector <int> clean_evt;
  // std::vector <float> WF_sum_raw(ampl_TPC[0].size());
  // std::vector <float> WF_sum( ampl_TPC[0].size());
  // std::vector <float> bin_count( ampl_TPC[0].size(),0);

  int nentries = 100e3;
  std::vector <int> clean_evt;
  std::vector <double> WF_sum_raw(nentries);
  std::vector <double> WF_sum(nentries);
  std::vector <double> bin_count(nentries,0);

  // sig_evt = GetCleanEvents(ampl_TPC, spark_tresh_gl, up_spark_tresh_gl);

  TH1F * hWF_sum_raw = new TH1F("hWFsumRaw"," Raw Sum Of Waveforms; Time [s]; Amplitude [V] ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));
  TH1F * hWF_sum_flat = new TH1F("hWFsum_FlatNorm"," Sum Of Waveforms with flat normalisation; Time [s]; Amplitude [V] ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));
  TH1F * hWF_sum = new TH1F("hWFsum"," Sum Of Waveforms; Time [s]; Amplitude [V] ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));
  TH1F * hBin_count = new TH1F("hBin_count"," entries in each WF bin; Time [s]; Amplitude [V]  ",nentries, t0-0.5e-9,((t0 + dt * nentries)-0.5e-9));

  cout << "nentries " << nentries << endl;
  cout << "WF_sum_raw size " << WF_sum_raw.size() << endl;
  cout << "ampl_TPC size " << ampl_TPC.size() << endl;
  cout << "ampl_TPC[0] size " << ampl_TPC[0].size() << endl;
  for (int i(0); i < sig_evt.size(); i++){
    for(int j(0); j < ampl_TPC[sig_evt[i]].size(); j++){

      WF_sum_raw[j] += ampl_TPC[sig_evt[i]][j];

      if (ampl_TPC[sig_evt[i]][j] < -NSigmas * rmsv[sig_evt[i]][j]){
        WF_sum[j] += ampl_TPC[sig_evt[i]][j];

        bin_count[j] +=1;
      }

    }
  }


  for (int i(0); i<ampl_TPC[sig_evt[0]].size(); i++){
    hWF_sum_raw->SetBinContent(i,WF_sum_raw[i]);
    hWF_sum_flat-> SetBinContent(i,WF_sum[i]);
    if(bin_count[i]==0) hWF_sum->SetBinContent(i,WF_sum[i]);
    else hWF_sum->SetBinContent(i,WF_sum[i]/bin_count[i]);
    hBin_count->SetBinContent(i,bin_count[i]);
  }

  //
  // TCanvas  *cWF_sum = new TCanvas("cWF_sum", "Wave Form Sums", 1200,800);
  // cWF_sum->Divide(2,2);
  // cWF_sum->cd(1);
  // hWF_sum_raw -> Draw();
  // cWF_sum->cd(2);
  // hWF_sum_raw -> Draw();
  // cWF_sum->cd(3);
  // hWF_sum -> Draw();
  // cWF_sum->cd(4);
  // hBin_count->Draw();

  if (storeWF){
    hWF_sum->SetTitle(Form("%lu Signal Events Added in This Plot", sig_evt.size()));
    hWF_sum_raw->SetTitle(Form("%lu Signal Events Added in This Plot", sig_evt.size()));
    hWF_sum_raw->Write();
    hWF_sum->Write();
    hWF_sum_flat->Write();
    hBin_count->Write();
  }


}







int GeneralAna_v2(){
    //Configuration_18
    auto start = high_resolution_clock::now();
    std::vector<int>signal_evt_idx;
    std::vector<int>EmptyTrigger_evt_idx;
    std::vector<int>spark_evt_idx;
    std::vector<int> badPedestal_evt_idx; 
    
//     string path = "Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh800_ii_TPC1650/";  const int tot_evt = 8000;
        string path = "Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650/";  const int tot_evt = 5000;
    string prefix_path_data = "../../Swan_Data/";
    string path_prefix_AnaResults = "../../Swan_TTrees/";
       
    TFile *WF_output = TFile::Open((path_prefix_AnaResults + path+Form("WF_output_%d_%.1fRMS.root",tot_evt,         NSigmas)).c_str(),"RECREATE");
    WF_output->mkdir("integral_0_100");
    WF_output->mkdir("integral_100_500");
    WF_output->mkdir("integral_500");
    WF_output->mkdir("Sparks");
    
    TH1D *single = new TH1D("single","single",100,-0.5,0.05);
    TH1D *single_pos = new TH1D("single_pos","Positive ADC plotted in the negative",100,-0.5,0.05);
    TH1D *integral_bef = new TH1D("integral_bef","",1000, -0.1e2,100e3);
    TH1D *integral_aft = new TH1D("integral_aft","",1000, -0.1e2,100e3);
    TH1D *integral_a = new TH1D("integral_a","",1000, -0.1e2,100e3);
    TH1D *integral_ab = new TH1D("integral_ab","",1000, -0.1e2,100e3);
    TH2D *integral_a_ab = new TH2D("integral_a_ab","b vs a; a; b",tot_evt, -0.5,tot_evt-0.5,100, -10,1.2e3);


  double max = 0;
  double imax;
    
//    std::tuple <vector<vector<double>>, double, double, int, int> tup;
    //auto tup = read_binary_3(path, prefix_path_data, prefix_path_AnaResults, tot_evt);
    auto bin1 = read_binary_3(path,prefix_path_data,path_prefix_AnaResults, tot_evt ,WF_output );//return ampl_tpc, rms_tpc, min_idx vector, t0, dt, trig_idx, nentries
    
     std::vector<std::vector<double>> ampl_TPC= bin1.Ampl_TPC;
     std::vector<std::vector<double>> rms= bin1.Rms_TPC;
     std::vector<int> min_idx =  bin1.Min_idx;
     const double  t0 = bin1.T0;
     const double  dt = bin1.Dt;
     int const  nentries = bin1.Nentries;
    
    std::vector<double>  time(nentries, 0);
    for (int i(0); i < nentries; i++){
        time[i] = t0 + i*dt;
        
    }
    
    const double drift_time = 40e-6;
    const double extended_drift_time = 80e-6;
    
    int const TrigTimeIdx = bin1.Trig_idx;
    int const a_idx = TrigTimeIdx + int(drift_time/dt);
    int const ab_idx = TrigTimeIdx + int(extended_drift_time/dt);
    
    
//    cout << " Size of adc " << ampl_TPC.size()<< " of rms " << rms.size() << " of time " << time.size() << endl;
    
//     ************//************
//     here the big chunk of analysis starts
//     ************//************
    
    for (int evt(0); evt < ampl_TPC.size(); evt++ ){
       // cout<< "Starting Event " << evt << endl;
         if(ampl_TPC[evt][0] == -999 ){
              cout << "Spark file: " << evt << endl;
              spark_evt_idx.push_back(evt);
              continue;
         }else if (ampl_TPC[evt][0] == -888) {
             cout << "Bad Pedestal subtraction file: " << evt << endl;
              badPedestal_evt_idx.push_back(evt);
              continue;
         }
         else if (ampl_TPC.at(evt).size() == 0) continue;

         if ( ampl_TPC[evt][min_idx[evt]] > - NSigmas * rms[evt][min_idx[evt]]) {

      EmptyTrigger_evt_idx.push_back(evt);
      continue;}
      // cout << "evt: " << i <<" min is  " << min << " happening at " <<time[min_idx] << endl;



      signal_evt_idx.push_back(evt);

        
        
      auto Intg_Tup = Integral(ampl_TPC[evt], rms[evt], time,NSigmas, single , single_pos , evt , WF_output, t0 , dt,  TrigTimeIdx , a_idx , ab_idx  ); 
      integral_bef->Fill(ConvertToPhot(Intg_Tup[0], dt));
      integral_aft->Fill(ConvertToPhot(Intg_Tup[1], dt)); 
      integral_a->Fill(ConvertToPhot(Intg_Tup[2], dt));
      integral_ab->Fill(ConvertToPhot(Intg_Tup[3], dt));
      // integral_a_ab->Fill(-v[2]*  dt /(R* gain *e_ch*qe*col_eff), -v[3]*  dt /(R* gain *e_ch*qe*col_eff) );
      integral_a_ab->Fill( evt,ConvertToPhot(Intg_Tup[2], dt));
//       if (-v[2]*   dt /(R* gain *e_ch*qe*col_eff) > 5000) cout << " A lot of photons: " << -v[2]*   dt /(R* gain *e_ch*qe*col_eff) << " at event " << i << endl;
      if( -Intg_Tup[0] > max ) {max = -Intg_Tup[0]; imax = evt;}
    
    
    }

          
       ofstream DataSetQuality_;

    DataSetQuality_.open((path_prefix_AnaResults+path+Form("DataSetQuality_%d_%.1fRMS.txt", tot_evt, NSigmas)).c_str());

    cout << "The number of total events is " << tot_evt << endl;
    cout << "The number of empty triggers is " << EmptyTrigger_evt_idx.size() << endl;
    cout << "The number of signal events is " << signal_evt_idx.size() << endl;
    cout << "The number of spark events is " << spark_evt_idx.size() << endl;
    cout << " total " << EmptyTrigger_evt_idx.size() +signal_evt_idx.size() + spark_evt_idx.size() << endl;

    DataSetQuality_ << (path_prefix_AnaResults+path+Form("DataSetQuality_%d_%.1fRMS.txt", tot_evt, NSigmas)).c_str() << endl;
    DataSetQuality_ << " " << endl;
    DataSetQuality_ << " " << endl;
    DataSetQuality_ << "The number of total events is " << tot_evt << endl;
    DataSetQuality_ << "\t The number of empty triggers is " << EmptyTrigger_evt_idx.size() << endl;
    DataSetQuality_ << "\t The number of signal events is " << signal_evt_idx.size() << endl;
    DataSetQuality_ << "\t The number of spark events is " << spark_evt_idx.size() << endl;
    DataSetQuality_ << "\t The number of failed pedestal subtraction events is " << badPedestal_evt_idx.size() << endl;
    
    DataSetQuality_ << " ---------------------------- Ratios ---------------------------- " << endl;
    DataSetQuality_ << " " << endl;
    DataSetQuality_ << " \t Signal / All Clean Trigger " << double(signal_evt_idx.size())/ (tot_evt -spark_evt_idx.size() ) << endl;
    DataSetQuality_ << " \t Empty  / All Clean Trigger " << double(EmptyTrigger_evt_idx.size())/ (tot_evt -spark_evt_idx.size() ) << endl;
    DataSetQuality_ << " " << endl;
    DataSetQuality_ << " ---------------------------- More Info ---------------------------- " << endl;
    DataSetQuality_ << " " << endl;
    DataSetQuality_ << "Signal = Event with at least one amplitude bigger than treshold " << endl;
    DataSetQuality_ << "Empty = Event with no amplitude bigger than treshold (fake trigger)" << endl;
    DataSetQuality_ << "All clean trigger mean any event which does not contain sparks. " << endl;
    DataSetQuality_.close();

    TFile *GeneralPlots_output = TFile::Open((path_prefix_AnaResults+path+Form("GeneralPlots_%d_%.1fRMS.root", tot_evt, NSigmas)).c_str(),"RECREATE");
    GetWFSum(ampl_TPC, rms, signal_evt_idx, NSigmas, GeneralPlots_output, t0, dt);
    single->Write();
    single_pos->Write();
    integral_bef->Write();
    integral_aft->Write();
    integral_a->Write();
    integral_ab->Write();
    integral_a_ab->Write();

    TH1D* hHowManySignalEvt = new TH1D("hHowManySignalEvt","", 1,0,1);
    hHowManySignalEvt->SetBinContent(1,signal_evt_idx.size());
    hHowManySignalEvt->Write();
    TH1D* hHowManyEmptyEvt = new TH1D("hHowManyEmptyEvt","", 1,0,1);
    hHowManyEmptyEvt->SetBinContent(1,EmptyTrigger_evt_idx.size());
    hHowManyEmptyEvt->Write();
    TH1D* hHowManySparkEvt = new TH1D("hHowManySparkEvt","", 1,0,1);
    hHowManySparkEvt->SetBinContent(1,spark_evt_idx.size());
    hHowManySparkEvt->Write();
    GeneralPlots_output->Close();
    

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
   
 
// To get the value of duration use the count()
// member function on the duration object
    cout << "" << endl;
    cout << " -------------------------------"<< endl;
    cout << " It Took " <<duration.count()/60. << " minutes to run the code " << endl;
    
    return 0;
}



