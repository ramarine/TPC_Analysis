

//read binary files to arrays

// single photon peak finder and analyser. Compared to the scriptto up to GeneralAna_v6/7 this takes the algorithm defined in SinglePhotonAlgorithm_RMSComp.pptx. 

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

#include <dirent.h>
#include <errno.h>

using namespace std::chrono;

using namespace std;


const float NSigmas = 3.0;
const float NSigmas_ped = NSigmas;
const int NPeds = 200;
const double spark_tresh = -5.2;//1.2
const double  spark_tresh_gl = -5.2;//1.2
const double  up_spark_tresh_gl = 5.2;//0.2

int two_samples = 0;
int four_samples = 0;
int five_samples = 0;
int three_samples = 0;


//define structure in order to store the values from the

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

double ConvertToPhot(double Amplitude, double dt);

std::tuple<std::vector<double>, std::vector<double>, double, int> ADC_Ped_Subtracted(  vector<double>& adc, const int NPeds = 200, double NSigmas = 4. , int evt = -1 , double spark_tresh_local = -1.2, double up_spark_tresh_local = 0.2, double t0 =0., double dt = 0.   );

void GetWFSum(std::vector<std::vector<double>> *ampl_TPC,  std::vector<std::vector<double>> &rmsv, std::vector<int>&sig_evt, int NSigmas = 4,   TFile *storeWF =NULL, const double t0 = 0, const double dt = 0);

int GeneralAna_v3_test(string path = "");

double ConvertToPhot(double Amplitude, double dt){
  double const R(50.), gain(1e7), e_ch(1.6e-19), qe(0.25), col_eff(0.8);//gain = 1e7 for 1650V (Hamamtsu R6427)
  return Amplitude * (-dt) /(R* gain *e_ch*qe*col_eff);
}





//------------------------********************--------------------
//                      Function to output the adc - ped in a vector of vectors
//-----------------------*********************---------------------

std::tuple<std::vector<double>, std::vector<double>, double, int> ADC_Ped_Subtracted(  vector<double>& adc, const int NPeds = 200, double NSigmas = 4. , int evt = -1 , double spark_tresh_local = -1.2, double up_spark_tresh_local = 0.2, double t0 =0., double dt = 0.   ){

  // cout << "t0 = " << t0 << " dt= " << dt << endl;

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


  double min = 500000;

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

    // if (isnan(adc[i]-ped) || isinf(adc[i]-ped)) cout << "here i filled a histo with infinity " << endl;
    //              if (isnan(adc[i]-ped) || isinf(adc[i]-ped)) cout << "do i crush when setting the bin content to WF_spark?" << endl;


  }

  std::vector<double> rmsv(threshv.size());
  for (int i(0); i < threshv.size(); i++){
    rmsv[i] = (threshv[i]/NSigmas);
  }





  if (*min_element(adc_subtracted.begin(), adc_subtracted.end()) < spark_tresh_local || *max_element(adc_subtracted.begin(), adc_subtracted.end()) > up_spark_tresh_local  ){
    //adc_subtracted[0] = -999;
    //return std::make_tuple(spark_adc,spark_rms, -999 , 2 );
    return std::make_tuple(adc_subtracted,spark_rms, -999 , 2 );
  }
  //if (evt ==5) cout << " min idx " << std::min_element(adc_subtracted.begin(),adc_subtracted.end()) - adc_subtracted.begin() << " min value " <<  adc_subtracted[std::min_element(adc_subtracted.begin(),adc_subtracted.end()) - adc_subtracted.begin()]<< endl;
  return std::make_tuple(std::move(adc_subtracted), std::move(rmsv), *min_element(adc_subtracted.begin(), adc_subtracted.end()) , std::min_element(adc_subtracted.begin(),adc_subtracted.end()) - adc_subtracted.begin());//adc, rmsv, min, min idx


}

//------------------------********************--------------------
//                      Function to read binary
//-----------------------*********************---------------------

BinaryComponents read_binary_3(TTree *tree, string path ="/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650_test", string path_prefix_data = "../../Swan_Data",string path_prefix_AnaResults = "../../Swan_TTrees" , const int tot_evt = 1 , TFile * WF_output = NULL){

  //return ampl_tpc, rms_tpc, min_idx ,t0, dt, trig_idx, nentries

  string binfilepath = path_prefix_data+path+"/binary_dat";
  FILE *readfile;

  readfile = fopen(binfilepath.c_str(), "r");

  const int sd = sizeof(double); //we define this to save a bit of time by not having to fetch it each time we read


  double t0, tf, dt, t_evt;
  int nentries;
  int trig_idx;
  char name[100];
  const int nevents = 1000;
  //first, read the header.
  //name
  fread(&name, sizeof(char), 100, readfile);
  //cout << "Name of file is " << name << endl;
  //t0
  fread(&t0, sd, 1, readfile);
  //cout << "t0 = "<< t0 << endl;
  fread(&tf, sd, 1, readfile);
  //dt
  fread(&dt, sd, 1, readfile);
  //cout << "dt = " << dt << endl;
  fread(&t_evt, sd, 1, readfile);
  //n_entries_per_file
  fread(&nentries, sizeof(int), 1, readfile);
  cout << "Number of entries per file = " << nentries << endl;
  //trigger index
  fread(&trig_idx, sizeof(int), 1, readfile);
  cout << "Index of scintillator minimum = " << trig_idx << endl;


  std::vector<vector<double>> ampl_TPC(tot_evt, (vector<double>(100000)));
  std::vector<vector<double>> rms_TPC(tot_evt, (vector<double>(100000)));

  //      BinaryComponents bin;
  //     bin.Ampl_TPC = std::move(ampl_TPC);
  //     bin.Rms_TPC = std::move(rms_TPC);
  //     bin.Min_idx = std::move(min_idx);
  //     bin.T0 = t0;
  //     bin.Dt = dt;
  //     bin.Trig_idx = trig_idx;
  //     bin.Nentries = nentries;

  std::vector<int> min_idx(nentries, 0);

  std::vector<double> ampl_evt(nentries,0);
  std::vector<double> rms_evt(nentries,0);

  TBranch* B_wf = tree->Branch("WF", &ampl_evt);
  TBranch* B_rms_wf = tree->Branch("RMS", &rms_evt);




  for (int evt = 0; evt<tot_evt; evt++){
    // cout << "evt " << evt << endl;
    for (int entry = 0; entry<nentries; entry++){
      fread(&(ampl_TPC[evt][entry]), sd, 1, readfile);

      //if (entry < 5)  cout << "ampl_tpc[evt][entry] " << ampl_TPC[evt][entry] << endl;
      //if (entry < 5)  cout << "ampl_tpc[evt][entry] " << ampl_TPC[evt][entry] << endl;

    }
    auto adc_and_tresh = ADC_Ped_Subtracted(ampl_TPC[evt], NPeds ,  NSigmas_ped , evt , spark_tresh, up_spark_tresh_gl , t0 ,  dt  );
    ampl_TPC[evt] = std::move(get<0>(adc_and_tresh));
    rms_TPC[evt] = std::move(get<1>(adc_and_tresh));
    rms_evt = rms_TPC[evt];
    ampl_evt = ampl_TPC[evt];
    //double min = get<2>(adc_and_tresh);
    min_idx[evt] = std::move(get<3>(adc_and_tresh));
    //Put your code which does the per-event analysis here.
    tree->Fill();

  }

  //Put your code to do the analysis of the full dataset here.
  
  BinaryComponents bin;
  bin.Ampl_TPC = std::move(ampl_TPC);
  
  bin.Rms_TPC = std::move(rms_TPC);
  bin.Min_idx = std::move(min_idx);
  bin.T0 = t0;
  bin.Dt = dt;
  bin.Trig_idx = trig_idx;
  bin.Nentries = nentries;

  TBranch* B_min_idx = tree->Branch("MinIdxPerEvt", &min_idx);
  TBranch *B_t0 =  tree->Branch("t0", &t0);
  TBranch *B_dt =  tree->Branch("dt", &dt);

  TBranch *B_trig_idx =  tree->Branch("trig_idx", &trig_idx);
  TBranch *B_nentries = tree->Branch("nentries", &nentries);



  B_min_idx->Fill();
  B_t0->Fill();
  B_dt->Fill();
  B_trig_idx->Fill();
  B_nentries->Fill();


  return bin;
}



void GetWFSum(std::vector<std::vector<double>> *ampl_TPC,  std::vector<std::vector<double>> *rmsv, std::vector<int>&sig_evt, int NSigmas = 4,   TFile *storeWF =NULL, const double t0 = 0, const double dt = 0){
  //   int nentries = ampl_TPC[0].size();
  //   // std::vector <int> clean_evt;
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
  cout << "ampl_TPC size " << ampl_TPC->size() << endl;
  cout << "ampl_TPC[0] size " << ampl_TPC->at(0).size() << endl;
  for (int i(0); i < sig_evt.size(); i++){
    for(int j(0); j < ampl_TPC->at(sig_evt[i]).size(); j++){

      WF_sum_raw[j] += ampl_TPC->at(sig_evt[i]).at(j);

      if (ampl_TPC->at(sig_evt[i])[j] < -NSigmas * rmsv->at(sig_evt[i]).at(j)){
        WF_sum[j] += ampl_TPC->at(sig_evt[i]).at(j);

        bin_count[j] +=1;
      }
    }
  }


  for (int i(0); i<ampl_TPC->at(sig_evt[0]).size(); i++){
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


//-------------------------------------------********************--------------------------------------------------------
//                                         Define Integral function
//------------------------------------------*********************--------------------------------------------------------
std::tuple<double, double, double, double, std::vector<int>, int, std::string> Integral(std::vector<double> &adc, std::vector<double> &rmsv, std::vector<double> &time,   double NSigmas = 4, TH1D *single = NULL, TH1D * single_pos = NULL,TH1D *left = NULL, TH1D *right = NULL, TH1D *test_wf = NULL,  int evt = 1,TTree* tree = NULL ,TFile *WF_output = NULL, double t0 = 0, double dt = 0, const int TrigTimeIdx = 0, const int a_idx = 0, const int ab_idx = 0.) {//28 arguments, evt the 7th

  int debug = 856;
  double key_min = 10000.;
  int key_min_idx = 100000;
  Long64_t nentries = adc.size();
  std::vector<double>vect_cum(nentries,0);
  bool plotfig = false;
  std::vector<int> min_a;



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



  if (evt == 856 ) cout << " 1 " << endl ;

  double cadc = 0.;
  int iaccum = 0;
  double accum = 0;
  int iaccum_pos = 0;
  double accum_pos = 0;
 

  for(int i = 0; i < nentries; i++ ) {
    
    if (adc[i] < key_min){
      key_min = adc[i];
      key_min_idx = i;
    }
    if (adc[i] < - rmsv[i]*NSigmas) {
      cadc += adc[i];// variable being passed to the Cum  TH1. Basicaly each entry in this histogram represents the integral up to that point.
      if (TrigTimeIdx < i && i < a_idx ) min_a.push_back(i);
      //if (a_idx < i && i < ab_idx ) min_a.push_back(i);
      
    }
    if (single){
      if (evt == 491) test_wf->SetBinContent(i+1,adc[i] );    
      if(adc[i] < -rmsv[i]*NSigmas){
	iaccum++;
	if (evt == 1 && iaccum == 2) cout <<"Bef Evt: "<< evt << " Found a 2 sample peak at: " << time[i-2] <<" or index "<< i-2 <<". NSigmas*RMS = "<< NSigmas * rmsv[i-2] << ". NSigmas " << NSigmas << "rmsv[i-2] = " << rmsv[i-2]  << endl;
        accum += (adc[i]);
        
      }else{
	
        //if(  iaccum == 2 || iaccum == 3 || iaccum ==4 ||  iaccum == 5) {
	// if(   iaccum == 3 || iaccum ==4 ||  iaccum == 5) {
	if(   iaccum == 3) {
	//if(   iaccum ==2 ||  iaccum == 3) {
	  //double dum_right = adc[i];//1 points	  
	  double dum_right = adc[i];//2 points	  
	  //double dum_right = adc[i]+adc[i+1]+adc[i+2];//3 points	  
	  //double dum_right = adc[i]+adc[i+1]+adc[i+2]+adc[i+4];//4 points	  
	  //double dum_right = adc[i]+adc[i+1]+adc[i+2]+adc[i+4]+adc[i+5];//5 points	  	  
	  //double dum_right = adc[i]+adc[i+1]+adc[i+2]+adc[i+4]+adc[i+5]+adc[i+6]+adc[i+7]+adc[i+8]+adc[i+9]+adc[i+10];// 10 points	  
	  
       
	  if (iaccum ==1){
	    
	    double dum_left = adc[i-2];//1 points
	    left->Fill(dum_left);
	    single->Fill(dum_left + accum +dum_right);// 3 points
	    right->Fill(dum_right);//3 points after
	    two_samples++;
	  }
	  else  if (iaccum ==2 ){
	    // if (evt == 0) cout << "adc[i-2] = " << adc[i-2] << ", adc[i-1] =" <<adc[i-1]<< endl;	
	    double dum_left = adc[i-3]; //1 points
	    cout <<"Evt: "<< evt << " Found a 2 sample peak at: " << time[i-2] <<" or index "<< i-2 <<". NSigmas*RMS = "<< NSigmas * rmsv[i-2] << ". NSigmas " << NSigmas << "rmsv[i-2] = " << rmsv[i-2]  << endl;
	    //double dum_left = adc[i-4] + adc[i-3];//2 points
	    //double dum_left = adc[i-5]+adc[i-4]+adc[i-3];//3 points
	    //double dum_left = adc[i-6]+adc[i-5]+adc[i-4]+adc[i-3];//4 points
	    //double dum_left = adc[i-7]+adc[i-6]+adc[i-5]+adc[i-4]+adc[i-3];//5 points
	    //double dum_left = adc[i-9]+adc[i-8]+adc[i-7]+adc[i-6]+adc[i-5]+adc[i-4]+adc[i-3];//7 point	    
	    //double dum_left =adc[i-12]+adc[i-11]+adc[i-10]+ adc[i-9]+adc[i-8]+adc[i-7]+adc[i-6]+adc[i-5]+adc[i-4]+adc[i-3];//7 point	    
	    
	    left->Fill(dum_left);
	    single->Fill(dum_left + accum +dum_right);// 3 points
	    right->Fill(dum_right);//3 points after
	    two_samples++;
	  }
	  else if (iaccum ==3 ) {
	    double dum_left = adc[i-4];//1 points
	    //double dum_left = adc[i-5]+adc[i-4];//2 points
	    //double dum_left = adc[i-6]+adc[i-5]+adc[i-4];//3 points
	    //double dum_left = adc[i-7]+adc[i-6]+adc[i-5]+adc[i-4];//4 points
	    //double dum_left = adc[i-8]+adc[i-7]+adc[i-6]+adc[i-5]+adc[i-4];//5 points
	    //double dum_left = adc[i-13]+adc[i-12]+adc[i-11]+adc[i-10] + adc[i-9]+adc[i-8]+adc[i-7]+adc[i-6]+adc[i-5]+adc[i-4];//7 points

	    cout <<"Evt: "<< evt << " Found a 3 sample peak at: " << time[i-3] <<" or index "<< i-3 <<". NSigmas*RMS = "<< NSigmas * rmsv[i-2] << ". NSigmas " << NSigmas << "rmsv[i-2] = " << rmsv[i-2]  << endl;
	    left->Fill(dum_left);
	    three_samples++;
	    single->Fill(dum_left+ accum +dum_right);// 3 points
	    right->Fill(dum_right);

	  }
	  else  if (iaccum ==4  ){
	    if (four_samples < 2670)single->Fill(accum);
	    four_samples++;
	  }
	  else  if (iaccum ==5 ) {
	    five_samples++;
	    single->Fill(accum);
	  }
	}
        
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
      
      Cum->SetBinContent(i+1,cadc);
      Thr->SetBinContent(i+1,rmsv[i]);
      
      if (i>0) vect_cum[i] = cadc;
  }
    

 


  double IntgNormBef = (time[TrigTimeIdx]-t0);
  double IntgNormAft = (time.back()-time[TrigTimeIdx]);
  double IntgNormA = (time[a_idx]-time[TrigTimeIdx]);
  double IntgNormAB = (time[ab_idx]-time[a_idx]);


  double intg_a_store = ConvertToPhot((Cum->GetBinContent(a_idx) - Cum ->GetBinContent(TrigTimeIdx))/(IntgNormA/IntgNormA),dt);
  double intg_b_store = ConvertToPhot((Cum->GetBinContent(nentries)-Cum->GetBinContent(a_idx))/(IntgNormAft/IntgNormA),dt);
  double intg_bef_store = ConvertToPhot(Cum->GetBinContent(TrigTimeIdx) /(IntgNormBef/IntgNormA),dt);
  double intg_aft_store = ConvertToPhot((Cum->GetBinContent(ab_idx) -Cum->GetBinContent(TrigTimeIdx)) / (IntgNormAB / IntgNormA),dt);



  std::string evt_tag;

  if (evt == debug){
    cout << "rms size "<<rmsv.size() << endl;
    cout <<  "key "<<key_min_idx << endl;
    cout << "1"<< endl;
  }
  if (key_min < -NSigmas*rmsv.at(key_min_idx) && intg_b_store >10 && min_a.size() > 7) {
    evt_tag = "signal";
  }
  else evt_tag = "empty";
  if(evt == debug) cout << "w"<< endl;
  
  
  
  

  //                                      if (evt == 36 ) cout << " 11 " << endl;
  cout << "The count of 2: "<< two_samples <<"The count of 3:  " << three_samples << ", 4 " << four_samples << ", 5samples " << five_samples << endl;   
  return std::make_tuple(intg_a_store, intg_b_store, intg_bef_store, intg_aft_store, min_a, key_min_idx, evt_tag);


  }


// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------General Ana--------------------------------------------
// ---------------------------------------------------------------------------------------------------------




int SinglePhotonPeakAna(string path = ""){
  // path has to be of the form: C3500_..._TPC1650
  //i.e. wihtout any /
  gROOT->SetStyle("Plain");
  const int tot_evt =500;
  auto start = high_resolution_clock::now();
  std::vector<int>signal_evt_idx;
  std::vector<int>EmptyTrigger_evt_idx;
  std::vector<int>spark_evt_idx;
  std::vector<int> badPedestal_evt_idx;


  //path = " C3800_LSF1780_ThGUp1400_ThGDnGND_PMesh0_TPC1650"; cout << " path re-defined within code " << " !!! the file put in the argument of the function will not work " << endl; 

  
  // dummy_intg = std::move(get<0>(intg_out));
  // path = "C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650_a/";


  // string path = "Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh800_ii_TPC1650/";  const int tot_evt = 8000;

  // string prefix_path_data = "../../Swan_Data/Configuration_18/";
  //string path_prefix_AnaResults = "../../Swan_TTrees/Configuration_18/";

  string prefix_path_data = "../../Swan_Data/Configuration_18/";
  string path_prefix_AnaResults = "../../Swan_TTrees/Configuration_18/";
  

  TH1D *single = new TH1D("single","single; Waveform sum (V ns); ",100,-0.5,0.05);
  TH1D *left = new TH1D("left","left; Waveform sum (V ns); ",100,-0.5,0.05);
  TH1D *test_wf = new TH1D("test_wf","; Time (us); ",100000,0,100000);
  TH1D *right = new TH1D("right","right; Waveform sum (V ns); ",100,-0.5,0.05);
  TH1D *single_pos = new TH1D("single_pos","Positive ADC plotted in the negative",100,-0.5,0.05);
  TH1D *integral_bef = new TH1D("integral_bef","",1000, -0.1e2,100e3);
  TH1D *integral_aft = new TH1D("integral_aft","",1000, -0.1e2,100e3);
  TH1D *integral_a = new TH1D("integral_a","",1000, -0.1e2,100e3);
  TH1D *integral_ab = new TH1D("integral_ab","",1000, -0.1e2,100e3);
  TH2D *integral_a_ab = new TH2D("integral_a_ab","b vs a; a; b",tot_evt, -0.5,tot_evt-0.5,100, -10,1.2e3);


  double max = 0;
  double imax;


  DIR* dir = opendir((path_prefix_AnaResults+path).c_str());

  if (dir) {
    /* Directory exists. */
    closedir(dir);
    std::cout<< " Directory exists " << endl;
  } else if (ENOENT == errno) {
    gSystem->MakeDirectory((path_prefix_AnaResults+path).c_str());
  } else {

  }


  TFile *WF_output = TFile::Open((path_prefix_AnaResults + path+"/"+Form("WF_output_%d_%.1fRMS.root",tot_evt,     NSigmas)).c_str(),"RECREATE");
  TTree* tree = new TTree("T","Waveforms");
  auto bin1 = read_binary_3(tree, path, prefix_path_data, path_prefix_AnaResults, tot_evt ,WF_output);//return ampl_tpc, rms_tpc, min_idx vector, t0, dt, trig_idx, nentries

  
  std::vector<std::vector<double>> *ampl_TPC= &bin1.Ampl_TPC;
  std::vector<std::vector<double>> *rms_TPC= &bin1.Rms_TPC;
  std::vector<int> *min_idx =  &bin1.Min_idx;
  

  // const double  t0 = bin1.T0;
  const double  t0 = -20;
  cout  << "The time 0  is " << t0 << endl;
  const double  dt = bin1.Dt;
  int const  nentries = bin1.Nentries;



  std::vector<double>  time(nentries, 0);
  
  for (int i(0); i < nentries; i++){
    time[i] = t0 + i*dt*1e6;
  }

  const double drift_time = 40e-6;
  const double extended_drift_time = 80e-6;

  int const TrigTimeIdx = bin1.Trig_idx;
  cout << "Trig Time IDx " << TrigTimeIdx << endl;
  int const a_idx = TrigTimeIdx + int(drift_time/dt);
  int const ab_idx = TrigTimeIdx + int(extended_drift_time/dt);



  //    cout << " Size of adc " << ampl_TPC.size()<< " of rms " << rms.size() << " of time " << time.size() << endl;
  
  // //    ************//************
  //   //  here the big chunk of analysis starts
  //    // ************//************
  //             int evt = 0;

  std::vector<double> dum_vect_double(0,1);
  std::vector<int> dum_vect_int;
  double rand_doub = -100000.02;
  int  br_evt = -1;
  
  double intg_a(0), intg_b(0), intg_bef(0), intg_aft(0);
  std::vector<int> min_a;
  int key_min_idx(-1);
  std::string evt_tag;
  
  TBranch* B_BadPed = tree->Branch("BadPed", &br_evt);
  TBranch* B_Spark = tree->Branch("Spark", &br_evt);


  TBranch *B_intg_b = tree->Branch("intg_b", &intg_b);
  TBranch *B_intg_a = tree->Branch("intg_a", &intg_a);
  TBranch *B_intg_bef = tree->Branch("intg_bef", &intg_bef);
  TBranch *B_intg_aft = tree->Branch("intg_aft", &intg_aft);

  TBranch *B_signal = tree->Branch("Signal", &br_evt);
  TBranch *B_empty = tree->Branch("Empty", &br_evt);
  TBranch *B_vect_cum = tree->Branch("cum_vect", &dum_vect_double);
  TBranch *B_min_counts_inDrift = tree->Branch("min_counts_inDrift", &min_a);
  //             TBranch* min_counts_inDrift = tree->Branch("min_counts_inDrift", &rand_doub);


  //TBranch *intg_a =NULL, TBranch *intg_b =NULL, TBranch *intg_bef =NULL;
  //TBranch *intg_a = tree->Branch("intg_a", &int_a_store);



  for (int evt = 0; evt < ampl_TPC->size(); evt++ ){
    br_evt = evt;
    // cout<< "Starting Event " << evt << endl;
    if(ampl_TPC->at(evt).at(0)== -999){
      cout << "Spark file: " << evt << endl;
      B_Spark->Fill();
      spark_evt_idx.push_back(evt);
      continue;
    }else if (ampl_TPC->at(evt).at(0) == -888) {
      cout << "Bad Pedestal subtraction file: " << evt << endl;
      badPedestal_evt_idx.push_back(evt);
      B_BadPed->Fill();
      continue;
    }
    else if (ampl_TPC->at(evt).size() == 0) continue;
    

    // cout << "evt: " << i <<" min is  " << min << " happening at " <<time[min_idx] << endl;
    
    
    
    
    
    cout << " Doing the Integral of evt: " << evt << endl;
    
    
    auto intg_tuple   =  Integral(ampl_TPC->at(evt), rms_TPC->at(evt), time, NSigmas, single , single_pos,left,right, test_wf , evt ,tree, WF_output, t0 , dt,  TrigTimeIdx , a_idx , ab_idx);
    intg_a = std::move(get<0>(intg_tuple));
    intg_b = std::move(get<1>(intg_tuple));
    intg_bef= std::move(get<2>(intg_tuple));
    intg_aft = std::move(get<3>(intg_tuple));
    min_a = std::move(get<4>(intg_tuple));
    key_min_idx = std::move(get<5>(intg_tuple));
    evt_tag =   std::move(get<6>(intg_tuple));


    //    B_intg_b->Fill();
    // B_intg_a->Fill();
    // B_intg_bef->Fill();
    // B_intg_aft->Fill();
    if (evt_tag == "signal") {
      B_intg_b->Fill();
      B_intg_a->Fill();
      B_intg_bef->Fill();
      B_intg_aft->Fill();
      B_signal->Fill();
      signal_evt_idx.push_back(evt);
      //      cout <<" br_evt " << br_evt <<" intg a " << intg_a << endl; 
    }
    else {
      B_empty->Fill();
      B_min_counts_inDrift->Fill();
      EmptyTrigger_evt_idx.push_back(evt);
    }

  }


  //        ofstream DataSetQuality_;

  //     DataSetQuality_.open((path_prefix_AnaResults+path+Form("DataSetQuality_%d_%.1fRMS.txt", tot_evt, NSigmas)).c_str());

  cout << "The number of total events is " << tot_evt << endl;
  cout << "The number of empty triggers is " << EmptyTrigger_evt_idx.size() << endl;
  cout << "The number of signal events is " << signal_evt_idx.size() << endl;
  cout << "The number of spark events is " << spark_evt_idx.size() << endl;
  cout << "The number of bad pedestal events is " <<  badPedestal_evt_idx.size() << endl;
  cout << " A total of " << EmptyTrigger_evt_idx.size() +signal_evt_idx.size() + spark_evt_idx.size() + badPedestal_evt_idx.size()<< " events have been written to the following file " << path_prefix_AnaResults + path   << endl;

  //     DataSetQuality_ << (path_prefix_AnaResults+path+Form("DataSetQuality_%d_%.1fRMS.txt", tot_evt, NSigmas)).c_str() << endl;
  //     DataSetQuality_ << " " << endl;
  //     DataSetQuality_ << " " << endl;
  //     DataSetQuality_ << "The number of total events is " << tot_evt << endl;
  //     DataSetQuality_ << "\t The number of empty triggers is " << EmptyTrigger_evt_idx.size() << endl;
  //     DataSetQuality_ << "\t The number of signal events is " << signal_evt_idx.size() << endl;
  //     DataSetQuality_ << "\t The number of spark events is " << spark_evt_idx.size() << endl;
  //     DataSetQuality_ << "\t The number of failed pedestal subtraction events is " << badPedestal_evt_idx.size() << endl;

  //     DataSetQuality_ << " ---------------------------- Ratios ---------------------------- " << endl;
  //     DataSetQuality_ << " " << endl;
  //     DataSetQuality_ << " \t Signal / All Clean Trigger " << double(signal_evt_idx.size())/ (tot_evt -spark_evt_idx.size() ) << endl;
  //     DataSetQuality_ << " \t Empty  / All Clean Trigger " << double(EmptyTrigger_evt_idx.size())/ (tot_evt -spark_evt_idx.size() ) << endl;
  //     DataSetQuality_ << " " << endl;
  //     DataSetQuality_ << " ---------------------------- More Info ---------------------------- " << endl;
  //     DataSetQuality_ << " " << endl;
  //     DataSetQuality_ << "Signal = Event with at least one amplitude bigger than treshold " << endl;
  //     DataSetQuality_ << "Empty = Event with no amplitude bigger than treshold (fake trigger)" << endl;
  //     DataSetQuality_ << "All clean trigger mean any event which does not contain sparks. " << endl;
  //     DataSetQuality_.close();

  //     TFile *GeneralPlots_output = TFile::Open((path_prefix_AnaResults+path+Form("GeneralPlots_%d_%.1fRMS.root", tot_evt, NSigmas)).c_str(),"RECREATE");

  //  GetWFSum(ampl_TPC, rms_TPC, signal_evt_idx, NSigmas, WF_output, t0, dt);
  single->Write();
  single_pos->Write();
  left->Write();
  test_wf->Write();
  right->Write();
  //     integral_bef->Write();
  //     integral_aft->Write();
  //     integral_a->Write();
  //     integral_ab->Write();
  //     integral_a_ab->Write();

  TH1D* hHowManySignalEvt = new TH1D("hHowManySignalEvt","", 1,0,1);
  hHowManySignalEvt->SetBinContent(1,signal_evt_idx.size());
  hHowManySignalEvt->Write();
  TH1D* hHowManyEmptyEvt = new TH1D("hHowManyEmptyEvt","", 1,0,1);
  hHowManyEmptyEvt->SetBinContent(1,EmptyTrigger_evt_idx.size());
  hHowManyEmptyEvt->Write();
  TH1D* hHowManySparkEvt = new TH1D("hHowManySparkEvt","", 1,0,1);
  hHowManySparkEvt->SetBinContent(1,spark_evt_idx.size());
  hHowManySparkEvt->Write();
  TH1D* hHowManyBadPedEvt = new TH1D("hHowManyBadPedEvt","", 1,0,1);
  hHowManyBadPedEvt->SetBinContent(1,badPedestal_evt_idx.size());
  hHowManyBadPedEvt->Write();


  tree->Write("", TObject::kOverwrite);
  delete (tree);

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop - start);



  // To get the value of duration use the count()
  // member function on the duration object
  cout << "" << endl;
  cout << " -------------------------------"<< endl;
  cout << " It Took " <<duration.count()/60. << " minutes to run the code " << endl;


  WF_output->Close();

  return 1;


}
