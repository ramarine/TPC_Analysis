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
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooGaussian.h"
#include "RooArgusBG.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooPlot.h"

using namespace RooFit;

Double_t CrystalBall(Double_t *x, Double_t *par);


void PMT_SPE_Ana(){
  //gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(111111);// Observable:
  RooRealVar mes("mes","m_{ES} (GeV)",5.20,5.30);

  // Parameters:
  RooRealVar sigmean("sigmean","B^{#pm} mass",5.28,5.20,5.30);
  RooRealVar sigwidth("sigwidth","B^{#pm} width",0.0027,0.001,1.);

  // Build a Gaussian PDF:
  RooGaussian signalModel("signal","signal PDF",mes,sigmean,sigwidth);

  string NSigmas = "3.0";
  // TFile *fPEN800 = TFile::Open((path+"Graphs/GeneralPlots_5000_"+NSigmas+"RMS.root").c_str());
  // TFile *fPEN800 =  TFile::Open("/Users/robertamarinei/Desktop/Year1_PhD/TPC/Comissioning/TPC_Ana/LecroyPMT_Ana/backups/AnaResults/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650/GeneralPlots_5000_3.0RMS.root");//original used for the paper
  //  TFile *fPEN800 =  TFile::Open("/home/amarinei/Year1_PhD/TPC/Comissioning/TPC_Ana/LeCroyPMT_Ana/Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650/WF_output_2000_1.5RMS.root");//used to fit the expectation
  TFile *fPEN800 =  TFile::Open("/home/amarinei/Year1_PhD/TPC/Comissioning/TPC_Ana/LeCroyPMT_Ana/Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650/WF_output_2000_3.0RMS.root");//used to fit the expectation


  TH1D*  single = (TH1D*)fPEN800->Get("single");
  TH1D*  single_pos = (TH1D*)fPEN800->Get("single_pos");
  TH1D*  subtracted = new TH1D("subtracted",";Amplitude Sum (V);",100,-0.5,0.05);
  TH1D*  inv_subtracted = new TH1D(""," ;Amplitude Sum (V#upointns); Counts",100,-0.05,0.5);
  TH1D*  inv_single = new TH1D(""," ;Amplitude Sum (V#upointns); Counts",100,-0.05,0.5);
  inv_subtracted->GetYaxis()->SetTitleOffset(1.1);


  //
  //
  //
  // single->SetLineWidth(2);
  // single_pos->SetLineWidth(2);
  // subtracted->SetLineWidth(2);

  single->SetTitle("Single Peak with noise");
  single_pos->SetTitle("Electronic Noise");
  subtracted->SetTitle("Single Peak, noise subtracted");

  //  double scale_single =  single->GetEntries();
  //double scale_single_pos =  single_pos->GetEntries();

  double scale_single =  1;
  double scale_single_pos =  1;  
  // single_pos->SetLineColor(46);
  // single->SetLineColor(41);
  // subtracted->SetLineColor(30);
  
  
  
  

  for (int i(0); i < single->GetNbinsX(); i++){
    double dumm = single->GetBinContent(i)/scale_single - single_pos->GetBinContent(i)/scale_single_pos;
    subtracted->SetBinContent(i,dumm);
    inv_subtracted->SetBinContent(single->GetNbinsX() - i+1, dumm);
    inv_single->SetBinContent(single->GetNbinsX()-i+1, single->GetBinContent(i));
  }
  
  



  TF1 *fitFcn_2Gaus = new TF1("fitFcn_2Gaus","[0]*TMath::Exp(-(x-[1])*(x-[1])/(2*[2]*[2])) + [3]*TMath::Exp(-(x-[4])*(x-[4])/(2*[5]*[5])) ",0.04,0.2);
  
  
  fitFcn_2Gaus->SetParameters(1600,0.05,0.3, 200,.16, 0.01);
  
  // subtracted->Fit("fitFcn_2","V+","ep", -0.065, -0.024);
  //gStyle->SetOptFit(11111);
  // single->Draw();
  // single_pos->Draw("same");
  
  //uncomment for orginal plot in EL paper
  /*
  inv_subtracted->Draw();
  inv_subtracted->Fit("gaus", "","", 0.025, 0.05 );
  inv_subtracted->GetFunction("gaus")->SetLineColor(kRed);



  */


  //TF1 *doublegaussian2 = new TF1("doublegaussian2","[0]*exp(-.5*((x-[1])/[2])^2)+[3]+[4]*exp(-.5*((x-[5])/[6])^2)+[7]",0,1);
  
  //inv_single->Fit(fitFcn_2Gaus,"","",0.045, 0.07);
  
  inv_single->Fit("gaus","","",0.04, 0.07);
  inv_single->GetFunction("gaus")->SetLineColor(kRed);

  //fitFcn_2Gaus->Draw("same");
 
  inv_single->Draw("");

  gPad->Update();


  // inv_single->Fit("g2", "","", 0.14, 0.2 );
  // single->Fit("gaus", "","", -0.2, -0.15 );
  // inv_single->GetFunction("fitFcn_2Gaus")->SetLineColor(kRed);



  // gStyle->SetOptFit(1111111111);
  // fitFcn->Draw();
  // inv_subtracted->Draw();



  // TF1 *fitFunction = new TF1("fitFunction", CrystalBall,-0.5,0.1,4);
  // TF1 *fitFunction = new TF1("pdf","ROOT::Math::crystalball_pdf(x, 3, 1.01, 1, -0.04)",-5,5,4);
  // fitFunction->SetParameters(3, 1.01, 1, -0.04);
  //
  // subtracted->Fit("fitFunction", "","", -0.1, -0.025);
  // fitFunction->Draw("same");

  auto legend = new TLegend(0.1,0.7,0.48,0.9);
  // legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
  legend->AddEntry(single,"Single Peak with noise","l");
  legend->AddEntry(single_pos,"Noise","l");
  legend->AddEntry(subtracted,"Single  Peak without noise ","l");
  // legend->Draw();


}


Double_t CrystalBall(Double_t *x, Double_t *par) {
  return ROOT::Math::crystalball_function(x[0], par[0], par[1], par[2], par[3]);
}
