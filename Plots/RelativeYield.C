void RelativeYield()
{
//=========Macro generated from canvas: Yield/
//=========  (Thu Sep 22 20:23:06 2022) by ROOT version 6.24/06
   TCanvas *Yield = new TCanvas("Yield", "",207,74,1200,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   Yield->Range(0,0,1,1);
   Yield->SetFillColor(0);
   Yield->SetBorderMode(0);
   Yield->SetBorderSize(2);
   Yield->SetTickx(1);
   Yield->SetTicky(1);
   Yield->SetLeftMargin(0.13);
   Yield->SetRightMargin(0.13);
   Yield->SetTopMargin(0.05);
   Yield->SetBottomMargin(0.16);
   Yield->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: Yield_1
   TPad *Yield_1 = new TPad("Yield_1", "Yield_1",0.01,0.01,0.49,0.99);
   Yield_1->Draw();
   Yield_1->cd();
   Yield_1->Range(-3.162162,-0.4249179,16.16216,1.294013);
   Yield_1->SetFillColor(0);
   Yield_1->SetBorderMode(0);
   Yield_1->SetBorderSize(2);
   Yield_1->SetTickx(1);
   Yield_1->SetTicky(1);
   Yield_1->SetLeftMargin(0.13);
   Yield_1->SetRightMargin(0.13);
   Yield_1->SetTopMargin(0.05);
   Yield_1->SetBottomMargin(0.16);
   Yield_1->SetFrameBorderMode(0);
   Yield_1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("Relative Integral of WF SUM (drift period) (NSigmas = 4.0)");
   
   Double_t Graph_fx1001[15] = {
   0,
   0.93,
   1.86,
   2.79,
   3.72,
   4.65,
   5.58,
   6.51,
   7.45,
   8.37,
   9.3,
   10.23,
   11.16,
   12.09,
   13};
   Double_t Graph_fy1001[15] = {
   0.3274194,
   0.3493586,
   0.3311923,
   0.2995414,
   0.3166723,
   0.3986499,
   0.4291627,
   0.4820774,
   0.5387724,
   0.6748754,
   0.753077,
   0.8650013,
   0.926671,
   1,
   1.029504};
   Double_t Graph_fex1001[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1001[15] = {
   0.01615482,
   0.01682462,
   0.01627071,
   0.01528866,
   0.01582303,
   0.01829769,
   0.01919101,
   0.02071284,
   0.02231186,
   0.02605247,
   0.02815569,
   0.03112389,
   0.03274255,
   0.0346546,
   0.03542051};
   TGraphErrors *gre = new TGraphErrors(15,Graph_fx1001,Graph_fy1001,Graph_fex1001,Graph_fey1001);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(8);
   
   TH1F *Graph_Graph1001 = new TH1F("Graph_Graph1001","Graph",100,0,14.3);
   Graph_Graph1001->SetMinimum(0.2061856);
   Graph_Graph1001->SetMaximum(1.142991);
   Graph_Graph1001->SetDirectory(0);
   Graph_Graph1001->SetStats(0);
   Graph_Graph1001->SetMarkerStyle(20);
   Graph_Graph1001->GetXaxis()->SetLabelFont(132);
   Graph_Graph1001->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1001->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1001->GetXaxis()->SetTitleFont(132);
   Graph_Graph1001->GetYaxis()->SetLabelFont(132);
   Graph_Graph1001->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1001->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1001->GetYaxis()->SetTitleFont(132);
   Graph_Graph1001->GetZaxis()->SetLabelFont(132);
   Graph_Graph1001->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1001->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1001->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1001);
   
   multigraph->Add(gre,"ALP");
   
   Double_t Graph_fx1002[15] = {
   0,
   0.93,
   1.86,
   2.79,
   3.72,
   4.65,
   5.58,
   6.51,
   7.45,
   8.37,
   9.3,
   10.23,
   11.16,
   12.09,
   13};
   Double_t Graph_fy1002[15] = {
   -0.01466305,
   0.01843472,
   -0.008971224,
   -0.05672015,
   -0.03087634,
   0.09279604,
   0.1388281,
   0.2186558,
   0.3041866,
   0.5095132,
   0.6274891,
   0.7963394,
   0.889375,
   1,
   1.044509};
   Double_t Graph_fex1002[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1002[15] = {
   0.03230965,
   0.03297945,
   0.03242553,
   0.03144348,
   0.03197786,
   0.03445251,
   0.03534583,
   0.03686767,
   0.03846668,
   0.0422073,
   0.04431051,
   0.04727871,
   0.04889737,
   0.05080943,
   0.05157533};
   gre = new TGraphErrors(15,Graph_fx1002,Graph_fy1002,Graph_fex1002,Graph_fey1002);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(8);
   
   TH1F *Graph_Graph1002 = new TH1F("Graph_Graph1002","Graph",100,0,14.3);
   Graph_Graph1002->SetMinimum(-0.2065885);
   Graph_Graph1002->SetMaximum(1.21451);
   Graph_Graph1002->SetDirectory(0);
   Graph_Graph1002->SetStats(0);
   Graph_Graph1002->SetMarkerStyle(20);
   Graph_Graph1002->GetXaxis()->SetLabelFont(132);
   Graph_Graph1002->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1002->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1002->GetXaxis()->SetTitleFont(132);
   Graph_Graph1002->GetYaxis()->SetLabelFont(132);
   Graph_Graph1002->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1002->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1002->GetYaxis()->SetTitleFont(132);
   Graph_Graph1002->GetZaxis()->SetLabelFont(132);
   Graph_Graph1002->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1002->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1002->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1002);
   
   multigraph->Add(gre,"ALP");
   
   Double_t Graph_fx1003[15] = {
   0,
   0.93,
   1.86,
   2.79,
   3.72,
   4.65,
   5.58,
   6.51,
   7.45,
   8.37,
   9.3,
   10.23,
   11.16,
   12.09,
   13};
   Double_t Graph_fy1003[15] = {
   0,
   0,
   0,
   0.006097561,
   0.01829268,
   0.06097561,
   0.1585366,
   0.2926829,
   0.4268293,
   0.5487805,
   0.695122,
   0.7926829,
   0.902439,
   1,
   1.146341};
   Double_t Graph_fex1003[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1003[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(15,Graph_fx1003,Graph_fy1003,Graph_fex1003,Graph_fey1003);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ffff");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(2);
   
   TH1F *Graph_Graph1003 = new TH1F("Graph_Graph1003","Graph",100,0,14.3);
   Graph_Graph1003->SetMinimum(0);
   Graph_Graph1003->SetMaximum(1.260976);
   Graph_Graph1003->SetDirectory(0);
   Graph_Graph1003->SetStats(0);
   Graph_Graph1003->SetMarkerStyle(20);
   Graph_Graph1003->GetXaxis()->SetLabelFont(132);
   Graph_Graph1003->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1003->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1003->GetXaxis()->SetTitleFont(132);
   Graph_Graph1003->GetYaxis()->SetLabelFont(132);
   Graph_Graph1003->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1003->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1003->GetYaxis()->SetTitleFont(132);
   Graph_Graph1003->GetZaxis()->SetLabelFont(132);
   Graph_Graph1003->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1003->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1003->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1003);
   
   multigraph->Add(gre,"AC");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetLimits(-0.65, 13.65);
   multigraph->GetXaxis()->SetTitle("E/N (Td)");
   multigraph->GetXaxis()->SetLabelFont(132);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(132);
   multigraph->GetYaxis()->SetTitle("Relative Yield (to 12.1 Td)");
   multigraph->GetYaxis()->SetLabelFont(132);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1);
   multigraph->GetYaxis()->SetTitleFont(132);
   
   TLegend *leg = new TLegend(0.2104549,0.7599823,0.5460838,0.9108252,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","MC EL Only","l");

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph","ThGEM+EL","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph","EL Only","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   Yield_1->Modified();
   Yield->cd();
  
// ------------>Primitives in pad: Yield_2
   TPad *Yield_2 = new TPad("Yield_2", "Yield_2",0.51,0.01,0.99,0.99);
   Yield_2->Draw();
   Yield_2->cd();
   Yield_2->Range(-3.162162,-0.5125834,16.16216,1.302252);
   Yield_2->SetFillColor(0);
   Yield_2->SetBorderMode(0);
   Yield_2->SetBorderSize(2);
   Yield_2->SetTickx(1);
   Yield_2->SetTicky(1);
   Yield_2->SetLeftMargin(0.13);
   Yield_2->SetRightMargin(0.13);
   Yield_2->SetTopMargin(0.05);
   Yield_2->SetBottomMargin(0.16);
   Yield_2->SetFrameBorderMode(0);
   Yield_2->SetFrameBorderMode(0);
   
   multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("Relative Integral of WF SUM (after drift period) (NSigmas = 4.0)");
   
   Double_t Graph_fx1004[15] = {
   0,
   0.93,
   1.86,
   2.79,
   3.72,
   4.65,
   5.58,
   6.51,
   7.45,
   8.37,
   9.3,
   10.23,
   11.16,
   12.09,
   13};
   Double_t Graph_fy1004[15] = {
   0.1893444,
   0.303852,
   0.2176196,
   0.1689175,
   0.1235114,
   0.2505571,
   0.2350614,
   0.249623,
   0.2847912,
   0.6036264,
   0.6976166,
   0.7824371,
   0.8824684,
   1,
   0.8991999};
   Double_t Graph_fex1004[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1004[15] = {
   0.0274569,
   0.03641804,
   0.02978353,
   0.02570992,
   0.02155329,
   0.03238743,
   0.03117499,
   0.03231493,
   0.03499862,
   0.05692553,
   0.06296506,
   0.06832871,
   0.07457355,
   0.08182507,
   0.07561098};
   gre = new TGraphErrors(15,Graph_fx1004,Graph_fy1004,Graph_fex1004,Graph_fey1004);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(8);
   
   TH1F *Graph_Graph1004 = new TH1F("Graph_Graph1004","Graph",100,0,14.3);
   Graph_Graph1004->SetMinimum(0.003971412);
   Graph_Graph1004->SetMaximum(1.179812);
   Graph_Graph1004->SetDirectory(0);
   Graph_Graph1004->SetStats(0);
   Graph_Graph1004->SetMarkerStyle(20);
   Graph_Graph1004->GetXaxis()->SetLabelFont(132);
   Graph_Graph1004->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1004->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1004->GetXaxis()->SetTitleFont(132);
   Graph_Graph1004->GetYaxis()->SetLabelFont(132);
   Graph_Graph1004->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1004->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1004->GetYaxis()->SetTitleFont(132);
   Graph_Graph1004->GetZaxis()->SetLabelFont(132);
   Graph_Graph1004->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1004->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1004->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1004);
   
   multigraph->Add(gre,"ALP");
   
   Double_t Graph_fx1005[15] = {
   0,
   0.93,
   1.86,
   2.79,
   3.72,
   4.65,
   5.58,
   6.51,
   7.45,
   8.37,
   9.3,
   10.23,
   11.16,
   12.09,
   13};
   Double_t Graph_fy1005[15] = {
   -0.0248063,
   0.1199508,
   0.01093833,
   -0.05062937,
   -0.1080304,
   0.05257697,
   0.03298778,
   0.05139603,
   0.09585467,
   0.4989165,
   0.617736,
   0.7249635,
   0.8514201,
   1,
   0.8725716};
   Double_t Graph_fex1005[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1005[15] = {
   0.0549138,
   0.06387494,
   0.05724043,
   0.05316681,
   0.04901019,
   0.05984433,
   0.05863189,
   0.05977182,
   0.06245552,
   0.08438243,
   0.09042195,
   0.09578561,
   0.1020304,
   0.109282,
   0.1030679};
   gre = new TGraphErrors(15,Graph_fx1005,Graph_fy1005,Graph_fex1005,Graph_fey1005);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(8);
   
   TH1F *Graph_Graph1005 = new TH1F("Graph_Graph1005","Graph",100,0,14.3);
   Graph_Graph1005->SetMinimum(-0.2836729);
   Graph_Graph1005->SetMaximum(1.235914);
   Graph_Graph1005->SetDirectory(0);
   Graph_Graph1005->SetStats(0);
   Graph_Graph1005->SetMarkerStyle(20);
   Graph_Graph1005->GetXaxis()->SetLabelFont(132);
   Graph_Graph1005->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1005->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1005->GetXaxis()->SetTitleFont(132);
   Graph_Graph1005->GetYaxis()->SetLabelFont(132);
   Graph_Graph1005->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1005->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1005->GetYaxis()->SetTitleFont(132);
   Graph_Graph1005->GetZaxis()->SetLabelFont(132);
   Graph_Graph1005->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1005->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1005->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1005);
   
   multigraph->Add(gre,"ALP");
   
   Double_t Graph_fx1006[15] = {
   0,
   0.93,
   1.86,
   2.79,
   3.72,
   4.65,
   5.58,
   6.51,
   7.45,
   8.37,
   9.3,
   10.23,
   11.16,
   12.09,
   13};
   Double_t Graph_fy1006[15] = {
   0,
   0,
   0,
   0.006097561,
   0.01829268,
   0.06097561,
   0.1585366,
   0.2926829,
   0.4268293,
   0.5487805,
   0.695122,
   0.7926829,
   0.902439,
   1,
   1.146341};
   Double_t Graph_fex1006[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   Double_t Graph_fey1006[15] = {
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(15,Graph_fx1006,Graph_fy1006,Graph_fex1006,Graph_fey1006);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#00ffff");
   gre->SetLineColor(ci);
   gre->SetMarkerStyle(2);
   
   TH1F *Graph_Graph_Graph10031006 = new TH1F("Graph_Graph_Graph10031006","Graph",100,0,14.3);
   Graph_Graph_Graph10031006->SetMinimum(0);
   Graph_Graph_Graph10031006->SetMaximum(1.260976);
   Graph_Graph_Graph10031006->SetDirectory(0);
   Graph_Graph_Graph10031006->SetStats(0);
   Graph_Graph_Graph10031006->SetMarkerStyle(20);
   Graph_Graph_Graph10031006->GetXaxis()->SetLabelFont(132);
   Graph_Graph_Graph10031006->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph10031006->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph10031006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph10031006->GetXaxis()->SetTitleFont(132);
   Graph_Graph_Graph10031006->GetYaxis()->SetLabelFont(132);
   Graph_Graph_Graph10031006->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph10031006->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph10031006->GetYaxis()->SetTitleFont(132);
   Graph_Graph_Graph10031006->GetZaxis()->SetLabelFont(132);
   Graph_Graph_Graph10031006->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph_Graph10031006->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph_Graph10031006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph10031006->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph_Graph10031006);
   
   multigraph->Add(gre,"AC");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetLimits(-0.65, 13.65);
   multigraph->GetXaxis()->SetTitle(" E/N (Td)");
   multigraph->GetXaxis()->SetLabelFont(132);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(132);
   multigraph->GetYaxis()->SetTitle("Relative Yield (to 12.1 Td)");
   multigraph->GetYaxis()->SetLabelFont(132);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1);
   multigraph->GetYaxis()->SetTitleFont(132);
   
   leg = new TLegend(0.2104549,0.7599823,0.5460838,0.9108252,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph","MC EL Only","l");

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph","ThGEM+EL","l");

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph","EL Only","l");

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   Yield_2->Modified();
   Yield->cd();
   Yield->Modified();
   Yield->cd();
   Yield->SetSelected(Yield);
}
