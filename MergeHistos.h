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
std::vector<std::vector<TString>> path_store;
path_store.push_back{};
path_store[0].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh0_TPC1650_a/");
path_store[0].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh100_TPC1650/");

path_store.push_back{};
path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh200_TPC1650/");
path_store[1].push_back("../../Swan_TTrees/Configuration_18/C3500_LSF1480_ThGUp1400_ThGDnGND_PMesh300_TPC1650/");




void MergeHistos(, TTree *tree1, TH1* h1, TFile * file2, TTree *tree2, TH1 *h2,  ){






}
