#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TMatrixD.h>
#include <TROOT.h>
#include <TMatrixDBase.h>
#include <TMath.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>
#include <cstdlib>
#include "TColor.h"

using namespace std;

static const double degtorad = 3.141592653589793/180.;

void formatit(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kAzure-2);
  histo->SetLineWidth(3);
  histo->SetLineStyle(1);
  histo->Draw("");  

  leg = new TLegend(0.15,0.9,0.35,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kAzure-2);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_diff(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kOrange+1);
  histo->SetLineWidth(3);
  histo->SetLineStyle(2);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.85,0.35,0.9);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kOrange+1);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_diff2(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kTeal-5);
  histo->SetLineWidth(3);
  histo->SetLineStyle(8);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.8,0.35,0.85);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kTeal-5);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_diff3(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kViolet-5);
  histo->SetLineWidth(3);
  histo->SetLineStyle(7);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.75,0.35,0.8);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kViolet-5);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_diff4(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kBlue+2);
  histo->SetLineWidth(3);
  histo->SetLineStyle(6);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.7,0.35,0.75);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kBlue+2);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}


void formatit_diff5(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kRed-4);
  histo->SetLineWidth(3);
  histo->SetLineStyle(10);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.65,0.35,0.7);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kRed-4);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}
void formatit_diff6(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kOrange+3);
  histo->SetLineWidth(3);
  histo->SetLineStyle(4);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.6,0.35,0.65);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kOrange+3);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}
void formatit_diff7(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kMagenta-8);
  histo->SetLineWidth(3);
  histo->SetLineStyle(5);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.55,0.35,0.6);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kMagenta-8);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_diff8(TH1F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.15);
  gPad->SetRightMargin(0.03);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  //  gPad->SetLiny(1);
  if (flag == 1){
    gPad->SetLogy(1);

  }

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->SetLineColor(kCyan-10);
  histo->SetLineWidth(3);
  histo->SetLineStyle(9);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.5,0.35,0.55);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kCyan-10);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

}

void formatit_2d(TH2F *histo, TString bar, TString xax, TString yax, Int_t flag){

  gPad->SetTicks(1,1);
  gPad->SetLeftMargin(0.21);
  gPad->SetRightMargin(0.11);
  gPad->SetTopMargin(0.03);
  gPad->SetBottomMargin(0.13);
  

  histo->SetLabelSize(0.045, "x");
  histo->SetLabelSize(0.045, "y");
  histo->GetXaxis()->SetTitleSize(0.055);
  histo->GetYaxis()->SetTitleSize(0.055);
  histo->GetXaxis()->CenterTitle(1);
  histo->GetYaxis()->CenterTitle(1);
  histo->GetXaxis()->SetTitleOffset(1.1);
  histo->GetYaxis()->SetTitleOffset(1.3);
  histo->GetYaxis()->SetTitle(yax);
  histo->GetXaxis()->SetTitle(xax);
  histo->Draw("colz");  

  leg = new TLegend(0.25,0.85,0.45,0.95);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.055);
  leg->SetTextColor(kRed-4);
  leg->SetBorderSize(0);
  leg->AddEntry(histo,bar,"");
  leg->Draw("same"); 

  if (flag == 0){

    TLine *linex = new TLine(30.,0.,30.,600.);
    TLine *liney = new TLine(0.,30.,600.,30.);
    linex->SetLineColor(kOrange+7);
    liney->SetLineColor(kOrange+7);
    //    linex->Draw("same");
    //    liney->Draw("same");

  }

}



int main(){

TFile *myfile;


  TChain chain("T");


  // H2 25.035 Ep = 1.4 GeV

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1841_-1.root");

  // H2 25.035 Ep = 3. GeV

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1844_-1.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_coin_replay_production_1864_-1.root");
  
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_coin_replay_production_1913_-1.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1966_-1.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1967_-1.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1968_-1.root");

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_all_1558_300000.root");
  
  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_all_1562_300000.root");
  
  Int_t nTracksx;
  Int_t nTracksy, nTracksxp, nTracksyp;
  Int_t ndcer, ncertr, ndcerdifft;
  Double_t track_nr;
  Double_t ng_npe;
  Double_t shtrk;
  Double_t prshtrk, nprshtrk;
  Double_t totshtrk;

  Double_t track_x[1000];
  Double_t track_y[1000];
  Double_t track_xp[1000];
  Double_t track_yp[1000];
  Double_t cerpulseint[4];
  Double_t cerpulseamp[4];
  Double_t certr[4];
  Double_t cerdifft[4];
  Double_t nhits_2x;
  Double_t goodtdchits_2x;
  Double_t goodpostdchits_2x;
  Double_t goodnegtdchits_2x;
  Double_t goodpostdchits_1x;
  Double_t goodnegtdchits_1x;
  Double_t goodpostdchits_1y;
  Double_t goodnegtdchits_1y;
  Double_t goodpostdchits_2y;
  Double_t goodnegtdchits_2y;
  Double_t track_beta, notrack_beta, justw,pist, delta, elclean, elreal;
  Double_t h1x_fptime, h2x_fptime, h1y_fptime, h2y_fptime, ng_x_atcer, ztar, ytar;
  Double_t prlo, prhi, shlo, ceramp, shadc, prshadc, edtm, legngcer,ello, certdc, ello, elhi, ellolo;


  chain.SetBranchAddress("T.hms.hPRLO_tdcTimeRaw", &prlo); 
  chain.SetBranchAddress("T.hms.hPRHI_tdcTimeRaw", &prhi); 
  chain.SetBranchAddress("T.hms.hSHWR_tdcTimeRaw", &shlo); 

  chain.SetBranchAddress("T.hms.hSHWR_adcPulseAmp", &shadc); 
  chain.SetBranchAddress("T.hms.hPSHWR_adcPulseAmp", &prshadc); 

  chain.SetBranchAddress("T.hms.hCER_adcPulseAmp", &legngcer); 

  chain.SetBranchAddress("T.hms.hEDTM_tdcTime", &edtm); 

  chain.SetBranchAddress("T.hms.hEL_CLEAN_tdcTimeRaw", &elclean); 
  chain.SetBranchAddress("T.hms.hEL_REAL_tdcTimeRaw", &elreal); 
  chain.SetBranchAddress("T.hms.hEL_LO_tdcTimeRaw", &ello); 
  chain.SetBranchAddress("T.hms.hEL_LO_LO_tdcTimeRaw", &ellolo); 
  chain.SetBranchAddress("T.hms.hEL_HI_tdcTimeRaw", &elhi); 
  chain.SetBranchAddress("T.hms.hCER_tdcTimeRaw", &certdc); 

  //  chain.SetBranchAddress("H.cer.goodAdcPulseAmp", &ceramp); 

  chain.SetBranchAddress("H.dc.ntrack", &track_nr);        
  chain.SetBranchAddress("H.cer.npeSum", &ng_npe);        
  chain.SetBranchAddress("H.hod.2x.nhits", &nhits_2x);        

  chain.SetBranchAddress("H.react.z", &ztar);        
  chain.SetBranchAddress("H.react.y", &ytar);        

  chain.SetBranchAddress("H.hod.2x.totNumGoodTdcHits", &goodtdchits_2x);        
  chain.SetBranchAddress("H.hod.2x.totNumGoodNegTdcHits", &goodnegtdchits_2x);        
  chain.SetBranchAddress("H.hod.2x.totNumGoodPosTdcHits", &goodpostdchits_2x);        
  chain.SetBranchAddress("H.hod.1x.totNumGoodNegTdcHits", &goodnegtdchits_1x);        
  chain.SetBranchAddress("H.hod.1x.totNumGoodPosTdcHits", &goodpostdchits_1x);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_1y);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_1y);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_2y);        
  chain.SetBranchAddress("H.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_2y);        

  chain.SetBranchAddress("Ndata.H.dc.x", &nTracksx);
  chain.SetBranchAddress("Ndata.H.dc.y", &nTracksy);
  chain.SetBranchAddress("H.dc.x", track_x);        
  chain.SetBranchAddress("H.dc.y", track_y);    
  chain.SetBranchAddress("Ndata.H.dc.xp", &nTracksxp);
  chain.SetBranchAddress("Ndata.H.dc.yp", &nTracksyp);
  chain.SetBranchAddress("H.dc.xp", track_xp);      
  chain.SetBranchAddress("H.dc.yp", track_yp);    
  chain.SetBranchAddress("H.cal.etracknorm", &shtrk); 
  chain.SetBranchAddress("H.cal.eprtracknorm", &prshtrk); 
  chain.SetBranchAddress("H.cal.eprtrack", &nprshtrk); 
  chain.SetBranchAddress("H.cal.etottracknorm", &totshtrk); 
  chain.SetBranchAddress("H.hod.beta", &track_beta);  
  chain.SetBranchAddress("H.hod.betanotrack", &notrack_beta);  
  chain.SetBranchAddress("H.hod.1x.fptime", &h1x_fptime);  
  chain.SetBranchAddress("H.hod.2x.fptime", &h2x_fptime);  
  chain.SetBranchAddress("H.hod.1y.fptime", &h1y_fptime);  
  chain.SetBranchAddress("H.hod.2y.fptime", &h2y_fptime);  
  chain.SetBranchAddress("H.kin.W", &justw);  
  chain.SetBranchAddress("H.gtr.p", &pist); 

  
  chain.SetBranchAddress("H.gtr.dp", &delta);

  chain.SetBranchAddress("H.cer.xAtCer", &ng_x_atcer);

  chain.SetBranchAddress("Ndata.H.cer.goodAdcPulseInt", &ndcer);
  chain.SetBranchAddress("H.cer.goodAdcPulseInt", cerpulseint);        

  chain.SetBranchAddress("Ndata.H.cer.goodAdcPulseAmp", &ndcer);
  chain.SetBranchAddress("H.cer.goodAdcPulseAmp", cerpulseamp);        

  chain.SetBranchAddress("Ndata.H.cer.goodAdcTdcDiffTime", &ndcerdifft);
  chain.SetBranchAddress("H.cer.goodAdcTdcDiffTime", cerdifft);        

  chain.SetBranchAddress("Ndata.H.cer.numTracksMatched", &ncertr);
  chain.SetBranchAddress("H.cer.numTracksMatched", certr);        

  //  Int_t nentries = (Int_t)this_tree->GetEntries();
  Int_t nentries = chain.GetEntries();
  
  TH1F* pmt[10]; 
  TH1F* pmtc[10]; 
  TH1F* pmtca[10]; 
  
  for(Int_t mm = 0; mm < 10; mm++){
    
    pmt[mm] = new TH1F("","",400,0.,300.);
    pmtc[mm] = new TH1F("","",400,0.,300.);
    pmtca[mm] = new TH1F("","",500,0.,700.);
  }

  
  TH2F* xp1 = new TH2F("", "", 100, -0.1., 0.1, 100, 0.01, 1.5);  
  TH2F* xp2 = new TH2F("", "", 100, -0.1., 0.1, 150, 0.1, 60);  

  TH2F* x_vs_y_strange = new TH2F("", "", 100, -40., 40., 100, -40., 40.);  

  TH1F* xfp = new TH1F("", "", 100, -40., 40.);  
  TH1F* x_at_ng = new TH1F("", "", 120, -40., 40.);
  TH1F* x_at_ng_del_cut = new TH1F("", "", 120, -40., 40.);
  TH1F* x_at_ng_low_del = new TH1F("", "", 120, -40., 40.);
  
  TH1F* xfp_del_cut = new TH1F("", "", 100, -70., 70.);  

  TH1F* npes = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_cerleg = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_cerleg_timing = new TH1F("", "", 150, 0., 60.);

  TH1F* npes_low_del = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_del_cut = new TH1F("", "", 150, 0., 60.);
  
  TH1F *prsh = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_pion = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_elec = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_strange = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_low_del = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_del_cut = new TH1F("", "", 100, 0.0, 1.5); 

  TH1F *shtrk_all = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *shtrk_all_elreal = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *shtrk_all_elclean = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *shtrk_all_prlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *shtrk_all_shlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *shtrk_all_prhi = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *shtrk_all_cerleg = new TH1F("", "", 150, 0.0, 1.5);


  TH1F *sh_elec = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_elclean = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_elreal = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_ello = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_ellolo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_elhi = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_prlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_shlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_prhi = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_ngcer = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_elec_cer = new TH1F("", "", 150, 0.0, 1.5);

  TH1F *sh_pion = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_elclean = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_elreal = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_prlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_shlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_prhi = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_ngcer = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *sh_pion_cer = new TH1F("", "", 150, 0.0, 1.5);
  


  for(Int_t i=0; i < nentries; i++){
  //  for(Int_t i=0; i < 20000; i++){
    
    chain.GetEntry(i);
    

    if (edtm == 0. && delta > -9. && delta < 9.){
      
      
      shtrk_all->Fill(shtrk);
      npes->Fill(ng_npe);


      if (elreal>0.){
      shtrk_all_elreal->Fill(shtrk);
      }
      if (elclean>0.){
      shtrk_all_elclean->Fill(shtrk);
      }
      if(prlo>0.){
	shtrk_all_prlo->Fill(shtrk);
      }
      if(prhi>0){
	shtrk_all_prhi->Fill(shtrk);
      }
      if(shlo>0){
	shtrk_all_shlo->Fill(shtrk);
      }
      if(certdc>0.){
	shtrk_all_cerleg->Fill(shtrk);
      }



      if(certdc > 0.){
	npes_cerleg->Fill(ng_npe);
	
	if ((cerdifft[0] > -40. && cerdifft[0] < 40.) || (cerdifft[1] > -40. && cerdifft[1] < 40.) || (cerdifft[2] > -40. && cerdifft[2] < 40.) || (cerdifft[3] > -40. && cerdifft[3] < 40.) ){
	  npes_cerleg_timing->Fill(ng_npe);
	}
      }
      
      if (ng_npe > 5.){

	sh_elec->Fill(shtrk);

	if(elclean > 0.){
	sh_elec_elclean->Fill(shtrk);
	}
	if(elreal > 0.){
	sh_elec_elreal->Fill(shtrk);
	}
	if(ello > 0.){
	sh_elec_ello->Fill(shtrk);
	}
	if(ellolo > 0.){
	sh_elec_ellolo->Fill(shtrk);
	}
	if(elhi > 0.){
	sh_elec_elhi->Fill(shtrk);
	}
	if(prlo > 0.){
	sh_elec_prlo->Fill(shtrk);
	}
	if(shlo > 0.){
	sh_elec_shlo->Fill(shtrk);
	}
	if(prhi > 0.){
	sh_elec_prhi->Fill(shtrk);
	}
	if(certdc > 0.){
	sh_elec_ngcer->Fill(shtrk);
	}

      }
      
      if (ng_npe == 0.){

	sh_pion->Fill(shtrk);

	if(elclean > 0.){
	sh_pion_elclean->Fill(shtrk);
	}
	if(elreal > 0.){
	sh_pion_elreal->Fill(shtrk);
	}
	if(prlo > 0.){
	sh_pion_prlo->Fill(shtrk);
	}
	if(shlo > 0.){
	sh_pion_shlo->Fill(shtrk);
	}
	if(prhi > 0.){
	sh_pion_prhi->Fill(shtrk);
	}
	if(certdc > 0.){
	sh_pion_ngcer->Fill(shtrk);
	}

      }

      
    }
    
    
  }
  

  Double_t int_elreal_elec_only = sh_elec_elreal->Integral(70,130);
  Double_t int_elclean_elec_only = sh_elec_elclean->Integral(70,130);
  Double_t int_ello_elec_only = sh_elec_ello->Integral(70,130);
  Double_t int_elhi_elec_only = sh_elec_elhi->Integral(70,130);
  Double_t int_ellolo_elec_only = sh_elec_ellolo->Integral(70,130);
  Double_t int_prlo_elec_only = sh_elec_prlo->Integral(70,130);
  Double_t int_prhi_elec_only = sh_elec_prhi->Integral(70,130);
  Double_t int_shlo_elec_only = sh_elec_shlo->Integral(70,130);
  Double_t int_elec_only = sh_elec->Integral(70,130);

  cout << " elecs elreal from 1562: " << int_elreal_elec_only << " " << int_elec_only << " " << int_elreal_elec_only/int_elec_only << endl;
  cout << " elecs elclean from 1562: " << int_elclean_elec_only << " " << int_elec_only << " " << int_elclean_elec_only/int_elec_only << endl;
  cout << " elecs ello from 1562: " << int_ello_elec_only << " " << int_elec_only << " " << int_ello_elec_only/int_elec_only << endl;
  cout << " elecs elhi from 1562: " << int_elhi_elec_only << " " << int_elec_only << " " << int_elhi_elec_only/int_elec_only << endl;
  cout << " elecs ellolo from 1562: " << int_ellolo_elec_only << " " << int_elec_only << " " << int_ellolo_elec_only/int_elec_only << endl;
  cout << " elecs prlo from 1562: " << int_prlo_elec_only << " " << int_elec_only << " " << int_prlo_elec_only/int_elec_only << endl;
  cout << " elecs prhi from 1562: " << int_prhi_elec_only << " " << int_elec_only << " " << int_prhi_elec_only/int_elec_only << endl;
  cout << " elecs shlo from 1562: " << int_shlo_elec_only << " " << int_elec_only << " " << int_shlo_elec_only/int_elec_only << endl;

    gStyle->SetCanvasColor(10);
    gStyle->SetFrameFillColor(10);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPalette(1,0);
    
    
    TCanvas *c3 = new TCanvas("c3","",900,900);
    
    c3->Divide(1,2);
    
    c3->cd(1);
    formatit(sh_elec, "5.9 GeV/c , th = 21 deg, 3/4 - PID THRS. at prod. values", "SHMS Shower","Events",0);
    formatit_diff3(sh_elec_elreal, "ELREAL TDC cut", "SHMS Shower","Events",0);
    formatit_diff5(sh_elec_elclean, "ELCLEAN TDC cut", "SHMS Shower","Events",0);
    formatit_diff6(sh_elec_ello, "ELLO TDC cut", "SHMS Shower","Events",0);
    formatit_diff7(sh_elec_ellolo, "ELLOLO TDC cut", "SHMS Shower","Events",0);
    formatit_diff8(sh_elec_elhi, "ELHI TDC cut", "SHMS Shower","Events",0);
    formatit_diff4(sh_elec_ngcer, "CER TDC cut", "SHMS Shower","Events",0);
    formatit_diff(sh_elec_prhi, "PRHI TDC cut", "SHMS Shower","Events",0);
    formatit_diff2(sh_elec_prlo, "PRLO TDC cut", "SHMS Shower","Events",0);

    c3->cd(2);
    formatit(sh_pion, "5.9 GeV/c , th = 21 deg, 3/4 - PID THRS. at prod. values", "SHMS Shower","Events",0);
    formatit_diff3(sh_pion_elreal, "ELREAL TDC cut", "SHMS Shower","Events",1);
    formatit_diff5(sh_pion_elclean, "ELCLEAN TDC cut", "SHMS Shower","Events",1);
    formatit_diff4(sh_pion_ngcer, "CER TDC cut", "SHMS Shower","Events",1);
    formatit_diff(sh_pion_prhi, "PRHI TDC cut", "SHMS Shower","Events",1);
    formatit_diff2(sh_pion_prlo, "PRLO TDC cut", "SHMS Shower","Events",1);
    formatit_diff7(sh_pion_shlo, "PRLO TDC cut", "SHMS Shower","Events",1);

    
    c3->Print("test1_bits_1562_hms.png"); 


    TCanvas *c4 = new TCanvas("c4","",900,900);
    
    c4->Divide(1,1);
    
    c4->cd(1);
    formatit(npes, "5.9 GeV/c , th = 21 deg, 3/4 - PID THRS. at prod. values", "NGC npe","Events",1);
    formatit_diff(npes_cerleg, "CERLEG TDC cut", "npe","Events",0);
    //    formatit_diff2(npes_cerleg_timing, "CERLEG TDC cut + timing", "NGC npe","Events",0);
    
    c4->Print("test2_bits_1562_hms.png"); 
    
    TCanvas *c5 = new TCanvas("c5","",900,900);
    
    c5->Divide(1,1);
    
    c5->cd(1);
    formatit(shtrk_all, "5.9 GeV/c , th = 21 deg, 3/4 - PID THRS. at prod. values", "SHMS Shower","Events",1);
    formatit_diff(shtrk_all_elreal, "ELREAL", "SHMS Shower","Events",1);
    formatit_diff5(shtrk_all_elclean, "ELCLEAN", "SHMS Shower","Events",1);
    formatit_diff2(shtrk_all_prlo, "PRLO", "SHMS Shower","Events",1);
    formatit_diff3(shtrk_all_prhi, "PRHI", "SHMS Shower","Events",1);
    formatit_diff7(shtrk_all_shlo, "SHLO", "SHMS Shower","Events",1);
    formatit_diff4(shtrk_all_cerleg, "CERLEG", "SHMS Shower","Events",1);
    
    c5->Print("test3_bits_1562_hms.png"); 
    

    return 0;
    
}
