void abs_gain()
{
//=========Macro generated from canvas: Abs_Yield/
//=========  (Thu Sep 22 20:25:30 2022) by ROOT version 6.24/06
   TCanvas *Abs_Yield = new TCanvas("Abs_Yield", "",367,38,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   Abs_Yield->Range(-3.154315,-594.6495,16.15431,1978.203);
   Abs_Yield->SetFillColor(0);
   Abs_Yield->SetBorderMode(0);
   Abs_Yield->SetBorderSize(2);
   Abs_Yield->SetTickx(1);
   Abs_Yield->SetTicky(1);
   Abs_Yield->SetLeftMargin(0.1296992);
   Abs_Yield->SetRightMargin(0.1296992);
   Abs_Yield->SetTopMargin(0.05043478);
   Abs_Yield->SetBottomMargin(0.1582609);
   Abs_Yield->SetFrameBorderMode(0);
   Abs_Yield->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("Absolute Number of Photons Detected; Mesh Voltage (V); Photon Number");
   
   Double_t Graph_fx1007[15] = {
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
   Double_t Graph_fy1007[15] = {
   545.2712,
   581.8079,
   551.5544,
   498.8443,
   527.3733,
   663.8956,
   714.7104,
   802.8324,
   897.2501,
   1123.911,
   1254.144,
   1440.539,
   1543.241,
   1665.36,
   1714.494};
   Double_t Graph_fex1007[15] = {
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
   Double_t Graph_fey1007[15] = {
   23.35104,
   24.1207,
   23.4852,
   22.33482,
   22.96461,
   25.76617,
   26.73407,
   28.3343,
   29.95413,
   33.52478,
   35.4139,
   37.95443,
   39.28411,
   40.80882,
   41.40645};
   TGraphErrors *gre = new TGraphErrors(15,Graph_fx1007,Graph_fy1007,Graph_fex1007,Graph_fey1007);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetFillStyle(1000);
   gre->SetLineColor(46);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1007 = new TH1F("Graph_Graph1007","Graph",100,0,14.3);
   Graph_Graph1007->SetMinimum(348.5704);
   Graph_Graph1007->SetMaximum(1883.84);
   Graph_Graph1007->SetDirectory(0);
   Graph_Graph1007->SetStats(0);
   Graph_Graph1007->SetMarkerStyle(20);
   Graph_Graph1007->GetXaxis()->SetLabelFont(132);
   Graph_Graph1007->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1007->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1007->GetXaxis()->SetTitleFont(132);
   Graph_Graph1007->GetYaxis()->SetLabelFont(132);
   Graph_Graph1007->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1007->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1007->GetYaxis()->SetTitleOffset(0.6);
   Graph_Graph1007->GetYaxis()->SetTitleFont(132);
   Graph_Graph1007->GetZaxis()->SetLabelFont(132);
   Graph_Graph1007->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1007->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1007->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1007);
   
   multigraph->Add(gre,"ALP");
   
   Double_t Graph_fx1008[15] = {
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
   Double_t Graph_fy1008[15] = {
   -16.18657,
   20.35013,
   -9.903355,
   -62.6135,
   -34.08446,
   102.4378,
   153.2526,
   241.3746,
   335.7923,
   562.4528,
   692.6867,
   879.0809,
   981.7831,
   1103.902,
   1153.036};
   Double_t Graph_fex1008[15] = {
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
   Double_t Graph_fey1008[15] = {
   33.02336,
   33.572,
   33.11836,
   32.31278,
   32.75125,
   34.77308,
   35.49622,
   36.71653,
   37.98054,
   40.85562,
   42.41952,
   44.56243,
   45.70024,
   47.01735,
   47.53699};
   gre = new TGraphErrors(15,Graph_fx1008,Graph_fy1008,Graph_fex1008,Graph_fey1008);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(38);
   gre->SetLineWidth(2);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph1008 = new TH1F("Graph_Graph1008","Graph",100,0,14.3);
   Graph_Graph1008->SetMinimum(-224.4762);
   Graph_Graph1008->SetMaximum(1330.123);
   Graph_Graph1008->SetDirectory(0);
   Graph_Graph1008->SetStats(0);
   Graph_Graph1008->SetMarkerStyle(20);
   Graph_Graph1008->GetXaxis()->SetLabelFont(132);
   Graph_Graph1008->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph1008->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph1008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1008->GetXaxis()->SetTitleFont(132);
   Graph_Graph1008->GetYaxis()->SetLabelFont(132);
   Graph_Graph1008->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph1008->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph1008->GetYaxis()->SetTitleOffset(0.6);
   Graph_Graph1008->GetYaxis()->SetTitleFont(132);
   Graph_Graph1008->GetZaxis()->SetLabelFont(132);
   Graph_Graph1008->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph1008->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph1008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1008->GetZaxis()->SetTitleFont(132);
   gre->SetHistogram(Graph_Graph1008);
   
   
   TF1 *f11009 = new TF1("f1","(x-[0])*[1]",3.6,13.1, TF1::EAddToList::kNo);
   f11009->SetFillColor(19);
   f11009->SetFillStyle(0);
   f11009->SetMarkerStyle(20);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   f11009->SetLineColor(ci);
   f11009->SetLineWidth(3);
   f11009->SetChisquare(18.22823);
   f11009->SetNDF(9);
   f11009->GetXaxis()->SetLabelFont(132);
   f11009->GetXaxis()->SetLabelSize(0.05);
   f11009->GetXaxis()->SetTitleSize(0.06);
   f11009->GetXaxis()->SetTitleOffset(1);
   f11009->GetXaxis()->SetTitleFont(132);
   f11009->GetYaxis()->SetLabelFont(132);
   f11009->GetYaxis()->SetLabelSize(0.05);
   f11009->GetYaxis()->SetTitleSize(0.06);
   f11009->GetYaxis()->SetTitleFont(132);
   f11009->SetParameter(0,4.259438);
   f11009->SetParError(0,0.1347679);
   f11009->SetParLimits(0,0,0);
   f11009->SetParameter(1,136.1206);
   f11009->SetParError(1,4.120628);
   f11009->SetParLimits(1,0,0);
   f11009->SetParent(gre);
   gre->GetListOfFunctions()->Add(f11009);
   
   TPaveStats *ptstats = new TPaveStats(0.1578947,0.5826087,0.5137845,0.733913,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(2);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   TText *ptstats_LaTex = ptstats->AddText("#chi^{2} / ndf = 18.23 / 9");
   ptstats_LaTex = ptstats->AddText("Prob  = 0.03262");
   ptstats_LaTex = ptstats->AddText("p0       = 4.259 #pm 0.1348 ");
   ptstats_LaTex = ptstats->AddText("p1       = 136.1 #pm 4.121 ");
   ptstats->SetOptStat(0);
   ptstats->SetOptFit(11111);
   ptstats->Draw();
   gre->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(gre->GetListOfFunctions());
   multigraph->Add(gre,"ALP");
   multigraph->Draw("ALP");
   multigraph->GetXaxis()->SetLimits(-0.65, 13.65);
   multigraph->GetXaxis()->SetTitle(" Mesh Voltage (V)");
   multigraph->GetXaxis()->SetLabelFont(132);
   multigraph->GetXaxis()->SetLabelSize(0.05);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(1);
   multigraph->GetXaxis()->SetTitleFont(132);
   multigraph->GetYaxis()->SetTitle(" Photon Number");
   multigraph->GetYaxis()->SetLabelFont(132);
   multigraph->GetYaxis()->SetLabelSize(0.05);
   multigraph->GetYaxis()->SetTitleSize(0.06);
   multigraph->GetYaxis()->SetTitleOffset(1);
   multigraph->GetYaxis()->SetTitleFont(132);
   
   TLegend *leg = new TLegend(0.1616541,0.7791304,0.5075188,0.9026087,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","ThGEM + EL ","l");
   entry->SetLineColor(46);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("Graph","EL Only ","l");
   entry->SetLineColor(38);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   Abs_Yield->Modified();
   Abs_Yield->cd();
   Abs_Yield->SetSelected(Abs_Yield);
}
