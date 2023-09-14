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
  
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_all_1562_300000.root");

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/hms_replay_production_all_1562_300000.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/hallc-online/ROOTfiles/hms_coin_replay_production_all_4716_300001.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/hallc-online/ROOTfiles/hms_coin_replay_production_all_4719_300000.root");
  // chain.Add("/net/cdaq/cdaql3data/cdaq/hallc-online/ROOTfiles/hms_coin_replay_production_all_4720_-1.root");
  // chain.Add("/net/cdaq/cdaql3data/cdaq/hallc-online/ROOTfiles/shms_coin_replay_production_all_4721_500004.root");

  chain.Add(" /home/cdaq/polhe3/production/hallc_replay/ROOTfiles/shms_replay_production_all_11473_200000.root");


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
  Double_t track_beta, notrack_beta, justw,pist, delta, elclean, elreal,prshadc_mult,legngcer_mult;
  Double_t h1x_fptime, h2x_fptime, h1y_fptime, h2y_fptime, ng_x_atcer, ztar, ytar, shadc_mult;
  Double_t prlo, prhi, shlo, ceramp, shadc, prshadc, edtm, legngcer,ello, certdc, ello, elhi, ellolo;


  chain.SetBranchAddress("T.shms.pPRLO_tdcTimeRaw", &prlo); 
  chain.SetBranchAddress("T.shms.pPRHI_tdcTimeRaw", &prhi); 

  chain.SetBranchAddress("T.shms.pPSHWR_adcPulseAmp", &prshadc); 
  chain.SetBranchAddress("T.shms.pPSHWR_adcMultiplicity", &prshadc_mult); 
  chain.SetBranchAddress("T.shms.pHGCER_adcPulseAmp", &legngcer); 
  chain.SetBranchAddress("T.shms.pHGCER_adcMultiplicity", &legngcer_mult); 
  

  chain.SetBranchAddress("T.shms.pEDTM_tdcTime", &edtm); 

  chain.SetBranchAddress("T.shms.pEL_CLEAN_tdcTimeRaw", &elclean); 
  chain.SetBranchAddress("T.shms.pEL_REAL_tdcTimeRaw", &elreal); 
  chain.SetBranchAddress("T.shms.pEL_LO_tdcTimeRaw", &ello); 
  chain.SetBranchAddress("T.shms.pEL_LO_LO_tdcTimeRaw", &ellolo); 
  chain.SetBranchAddress("T.shms.pEL_HI_tdcTimeRaw", &elhi); 
  chain.SetBranchAddress("T.shms.pHGCER_tdcTimeRaw", &certdc); 

  //  chain.SetBranchAddress("P.cer.goodAdcPulseAmp", &ceramp); 

  chain.SetBranchAddress("P.dc.ntrack", &track_nr);        
  chain.SetBranchAddress("P.hgcer.npeSum", &ng_npe);        
  chain.SetBranchAddress("P.hod.2x.nhits", &nhits_2x);        

  chain.SetBranchAddress("P.react.z", &ztar);        
  chain.SetBranchAddress("P.react.y", &ytar);        

  chain.SetBranchAddress("P.hod.2x.totNumGoodTdcHits", &goodtdchits_2x);        
  chain.SetBranchAddress("P.hod.2x.totNumGoodNegTdcHits", &goodnegtdchits_2x);        
  chain.SetBranchAddress("P.hod.2x.totNumGoodPosTdcHits", &goodpostdchits_2x);        
  chain.SetBranchAddress("P.hod.1x.totNumGoodNegTdcHits", &goodnegtdchits_1x);        
  chain.SetBranchAddress("P.hod.1x.totNumGoodPosTdcHits", &goodpostdchits_1x);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_1y);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_1y);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_2y);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_2y);        

  chain.SetBranchAddress("Ndata.P.dc.x", &nTracksx);
  chain.SetBranchAddress("Ndata.P.dc.y", &nTracksy);
  chain.SetBranchAddress("P.dc.x", track_x);        
  chain.SetBranchAddress("P.dc.y", track_y);    
  chain.SetBranchAddress("Ndata.P.dc.xp", &nTracksxp);
  chain.SetBranchAddress("Ndata.P.dc.yp", &nTracksyp);
  chain.SetBranchAddress("P.dc.xp", track_xp);      
  chain.SetBranchAddress("P.dc.yp", track_yp);    
  chain.SetBranchAddress("P.cal.etracknorm", &shtrk); 
  chain.SetBranchAddress("P.cal.eprtracknorm", &prshtrk); 
  chain.SetBranchAddress("P.cal.eprtrack", &nprshtrk); 
  chain.SetBranchAddress("P.cal.etottracknorm", &totshtrk); 
  chain.SetBranchAddress("P.hod.beta", &track_beta);  
  chain.SetBranchAddress("P.hod.betanotrack", &notrack_beta);  
  chain.SetBranchAddress("P.hod.1x.fptime", &h1x_fptime);  
  chain.SetBranchAddress("P.hod.2x.fptime", &h2x_fptime);  
  chain.SetBranchAddress("P.hod.1y.fptime", &h1y_fptime);  
  chain.SetBranchAddress("P.hod.2y.fptime", &h2y_fptime);  
  chain.SetBranchAddress("P.kin.W", &justw);  
  chain.SetBranchAddress("P.gtr.p", &pist); 

  
  chain.SetBranchAddress("P.gtr.dp", &delta);

  /*  chain.SetBranchAddress("P.cer.xAtCer", &ng_x_atcer);

  chain.SetBranchAddress("Ndata.P.cer.goodAdcPulseInt", &ndcer);
  chain.SetBranchAddress("P.cer.goodAdcPulseInt", cerpulseint);        

  chain.SetBranchAddress("Ndata.P.cer.goodAdcPulseAmp", &ndcer);
  chain.SetBranchAddress("P.cer.goodAdcPulseAmp", cerpulseamp);        

  chain.SetBranchAddress("Ndata.P.cer.goodAdcTdcDiffTime", &ndcerdifft);
  chain.SetBranchAddress("P.cer.goodAdcTdcDiffTime", cerdifft);        

  chain.SetBranchAddress("Ndata.P.cer.numTracksMatched", &ncertr);
  chain.SetBranchAddress("P.cer.numTracksMatched", certr);        */

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


  // histos to check the legs


  // preshower first

  TH1F* prsh_sum_mult_cut = new TH1F("", "", 210, -10., 200.);
  TH1F* prsh_sum_tdcprlo_cut = new TH1F("", "", 210, -10., 200.);
  TH1F* prsh_sum_tdcprhi_cut = new TH1F("", "", 210, -10., 200.);

  // 

  TH2F* prsh_sum_tdcprlo_cut_vsetot = new TH2F("", "", 210, -10., 200., 150, 0., 1.5);
  TH2F* prsh_sum_tdcprhi_cut_vsetot = new TH2F("", "", 210, -10., 200., 150, 0., 1.5);
  TH2F* prsh_sum_mult_vsetot = new TH2F("", "", 210, -10., 200., 150, 0., 1.5);


  // ///////


  TH1F* legcer_mult_cut = new TH1F("", "", 900, 0., 900.);
  TH1F* legcer_mult_tdc_cut = new TH1F("", "", 900, 0., 900.);


  ///////////

  TH2F* xp1 = new TH2F("", "", 100, -0.1., 0.1, 100, 0.01, 1.5);  
  TH2F* xp2 = new TH2F("", "", 100, -0.1., 0.1, 150, 0.1, 60);  

  TH2F* x_vs_y_strange = new TH2F("", "", 100, -40., 40., 100, -40., 40.);  

  TH2F* pr_vs_sh = new TH2F("", "", 150, 0.001, 1.5, 150, 0.001, 0.8);  
  TH2F* pr_vs_sh_elreal = new TH2F("", "", 150, 0.001, 1.5, 150, 0.001, 0.8);  
  TH2F* pr_vs_sh_prlo = new TH2F("", "", 150, 0.001, 1.5, 150, 0.001, 0.8);  
  TH2F* pr_vs_sh_prhi = new TH2F("", "", 150, 0.001, 1.5, 150, 0.001, 0.8);  
  TH2F* pr_vs_sh_shlo = new TH2F("", "", 150, 0.001, 1.5, 150, 0.001, 0.8);  

  TH1F* xfp = new TH1F("", "", 100, -40., 40.);  
  TH1F* x_at_ng = new TH1F("", "", 120, -40., 40.);
  TH1F* x_at_ng_del_cut = new TH1F("", "", 120, -40., 40.);
  TH1F* x_at_ng_low_del = new TH1F("", "", 120, -40., 40.);
  
  TH1F* xfp_del_cut = new TH1F("", "", 100, -70., 70.);  

  TH1F* npes = new TH1F("", "", 150, 0., 30.);
  TH1F* npes_cerleg = new TH1F("", "", 150, 0., 30.);
  TH1F* npes_cerleg_cutelec = new TH1F("", "", 150, 0., 30.);
  TH1F* npes_elecs = new TH1F("", "", 150, 0., 30.);

  TH1F* npes_low_del = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_del_cut = new TH1F("", "", 150, 0., 60.);
  
  TH1F *prshtrk_all = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_pion = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_elec = new TH1F("", "", 150, 0.0, 1.5);


  TH1F *prshtrk_all_elreal = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prshtrk_all_prlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prshtrk_all_prhi = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_elec_elreal = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_elec_prlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_elec_prhi = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_pion_elreal = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_pion_prlo = new TH1F("", "", 150, 0.0, 1.5);
  TH1F *prsh_pion_prhi = new TH1F("", "", 150, 0.0, 1.5);

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
    
    
    if (delta > -10. && delta < 22.){
      
      if (legngcer_mult>0) {
	
	legcer_mult_cut->Fill(legngcer);
	
	if (certdc>0.){
	  
	  legcer_mult_tdc_cut->Fill(legngcer);
	  
	  
	}
	
      }

      if (prshadc_mult>0){
	
	prsh_sum_mult_cut->Fill(prshadc);
	prsh_sum_mult_vsetot->Fill(prshadc,totshtrk);

	if(prlo>0.){

	  prsh_sum_tdcprlo_cut->Fill(prshadc);
	  prsh_sum_tdcprlo_cut_vsetot->Fill(prshadc,totshtrk);

	}

	if(prhi>0.){

	  prsh_sum_tdcprhi_cut->Fill(prshadc);
	  prsh_sum_tdcprhi_cut_vsetot->Fill(prshadc,totshtrk);

	}
	
      }


      if(shadc_mult>0.){
	
	sh_sum_mult_cut->Fill(shadc);
	sh_sum_mult_vsetot->Fill(shadc,totshtrk);

	if(shlo>0.){
	  
	  sh_sum_tdcshlo_cut->Fill(shadc);
	  sh_sum_tdcshlo_cut_vsetot->Fill(shadc,totshtrk);
	}
	
      }



      shtrk_all->Fill(totshtrk);
      prshtrk_all->Fill(prshtrk);
      npes->Fill(ng_npe);
      pr_vs_sh->Fill(totshtrk,prshtrk);
      
      // this is to see effect of PID legs on all totshtrk
      
      if (elreal>0.){
	shtrk_all_elreal->Fill(totshtrk);
	prshtrk_all_elreal->Fill(prshtrk);
	pr_vs_sh_elreal->Fill(totshtrk,prshtrk);
	
      }
      if (elclean>0.){
	shtrk_all_elclean->Fill(totshtrk);
      }
      if(prlo>0.){
	shtrk_all_prlo->Fill(totshtrk);
	prshtrk_all_prlo->Fill(prshtrk);
	pr_vs_sh_prlo->Fill(totshtrk,prshtrk);
	
      }
      if(prhi>0.){
	shtrk_all_prhi->Fill(totshtrk);
 	prshtrk_all_prhi->Fill(prshtrk);
	pr_vs_sh_prhi->Fill(totshtrk,prshtrk);
	
      }
      //      if(shlo>0.){
      //	shtrk_all_shlo->Fill(totshtrk);
      //	pr_vs_sh_shlo->Fill(totshtrk,prshtrk);
	
      //      }
      if(certdc>0.){
	shtrk_all_cerleg->Fill(totshtrk);
      }
      
      // this is to see effect of CER PID leg on pions

      if(totshtrk>0.7){
	npes_elecs->Fill(ng_npe);
      }
      
      if(certdc > 0.){
	npes_cerleg->Fill(ng_npe);
	
	if (totshtrk>0.7){
	  npes_cerleg_cutelec->Fill(ng_npe);
	}
      }
      
      // this is to see the effect of PID legs on electrons only (electrons selected with CER)
      
      if (ng_npe > 1.){
	
	sh_elec->Fill(totshtrk);
	prsh_elec->Fill(prshtrk);
	
	if(elclean > 0.){
	  sh_elec_elclean->Fill(totshtrk);
	}
	if(elreal > 0.){
	  sh_elec_elreal->Fill(totshtrk);
	  prsh_elec_elreal->Fill(prshtrk);
	}
	if(ello > 0.){
	  sh_elec_ello->Fill(totshtrk);
	}
	if(ellolo > 0.){
	  sh_elec_ellolo->Fill(totshtrk);
	}
	if(elhi > 0.){
	  sh_elec_elhi->Fill(totshtrk);
	}
	if(prlo > 0.){
	  sh_elec_prlo->Fill(totshtrk);
	  prsh_elec_prlo->Fill(prshtrk);
	}
	//	if(shlo > 0.){
	//	  sh_elec_shlo->Fill(totshtrk);
	//	}
	if(prhi > 0.){
	  sh_elec_prhi->Fill(totshtrk);
	  prsh_elec_prhi->Fill(prshtrk);
	}
	if(certdc > 0.){
	  sh_elec_ngcer->Fill(totshtrk);
	}
	
      }
      
      if (ng_npe == 0.){
	
	sh_pion->Fill(totshtrk);
	prsh_pion->Fill(prshtrk);
	
	if(elclean > 0.){
	  sh_pion_elclean->Fill(totshtrk);
	}
	if(elreal > 0.){
	  sh_pion_elreal->Fill(totshtrk);
	  prsh_pion_elreal->Fill(prshtrk);
	}
	if(prlo > 0.){
	  sh_pion_prlo->Fill(totshtrk);
	  prsh_pion_prlo->Fill(prshtrk);
	}
	//	if(shlo > 0.){
	//	  sh_pion_shlo->Fill(totshtrk);
	//	}
	if(prhi > 0.){
	  sh_pion_prhi->Fill(totshtrk);
	  prsh_pion_prhi->Fill(prshtrk);
	}
	if(certdc > 0.){
	  sh_pion_ngcer->Fill(totshtrk);
	}
	
      }
      
      
    }
    
    
  }
  

  Double_t int_elreal_elec_only = sh_elec_elreal->Integral(70,130);
  Double_t int_elreal_pion_only = sh_pion_elreal->Integral(2,70);
  
  Double_t int_elclean_elec_only = sh_elec_elclean->Integral(70,130);
  Double_t int_elclean_pion_only = sh_pion_elclean->Integral(2,70);
  
  Double_t int_ello_elec_only = sh_elec_ello->Integral(70,130);
  //  Double_t int_ello_pion_only = sh_pion_ello->Integral(2,70);
  
  Double_t int_elhi_elec_only = sh_elec_elhi->Integral(70,130);
  //  Double_t int_elhi_pion_only = sh_pion_elhi->Integral(2,70);
  
  Double_t int_ellolo_elec_only = sh_elec_ellolo->Integral(70,130);
  //  Double_t int_ellolo_pion_only = sh_pion_ellolo->Integral(2,70);
  
  Double_t int_prlo_elec_only = sh_elec_prlo->Integral(70,130);
  Double_t int_prlo_pion_only = sh_pion_prlo->Integral(2,70);
  
  Double_t int_prhi_elec_only = sh_elec_prhi->Integral(70,130);
  Double_t int_prhi_pion_only = sh_pion_prhi->Integral(2,70);
  
  //  Double_t int_shlo_elec_only = sh_elec_shlo->Integral(70,130);
  //  Double_t int_shlo_pion_only = sh_pion_shlo->Integral(2,70);
  
  Double_t int_elec_only = sh_elec->Integral(70,130);
  Double_t int_pion_only = sh_pion->Integral(2,70);
  
  
  
  cout << " elec eff. elreal: " << int_elreal_elec_only << " " << int_elec_only << " " << int_elreal_elec_only/int_elec_only << endl;
  cout << " pion rej. elreal: " << int_elreal_pion_only << " " << int_pion_only << " " << int_pion_only/int_elreal_pion_only << endl;
  
  
  /////////////////////////////////////////////////////////////////////////////////////////////
  
  cout << " elec eff. elclean: " << int_elclean_elec_only << " " << int_elec_only << " " << int_elclean_elec_only/int_elec_only << endl;
  cout << " pion rej. elclean: " << int_elclean_pion_only << " " << int_pion_only << " " << int_pion_only/(int_elclean_pion_only+1.) << endl;
  
  cout << " elec eff. ello: " << int_ello_elec_only << " " << int_elec_only << " " << int_ello_elec_only/int_elec_only << endl;
  //  cout << " pion rej. ello from 1562: " << int_ello_pion_only << " " << int_pion_only << " " << int_pion_onlyint_ello_pion_only << endl;

  cout << " elec eff. elhi: " << int_elhi_elec_only << " " << int_elec_only << " " << int_elhi_elec_only/int_elec_only << endl;
  //  cout << " pion rej. elhi from 1562: " << int_elhi_pion_only << " " << int_pion_only << " " << int_pion_only/int_elhi_pion_only << endl;

  cout << " elec eff. ellolo: " << int_ellolo_elec_only << " " << int_elec_only << " " << int_ellolo_elec_only/int_elec_only << endl;
  //  cout << " pion rej. ellolo from 1562: " << int_ellolo_pion_only << " " << int_pion_only << " " << int_pion_only/int_ellolo_pion_only << endl;

  cout << " elec eff. prlo: " << int_prlo_elec_only << " " << int_elec_only << " " << int_prlo_elec_only/int_elec_only << endl;
  cout << " pion rej. prlo: " << int_prlo_pion_only << " " << int_pion_only << " " << int_pion_only/int_prlo_pion_only << endl;

  cout << " elec eff. prhi: " << int_prhi_elec_only << " " << int_elec_only << " " << int_prhi_elec_only/int_elec_only << endl;
  cout << " pion rej. prhi: " << int_prhi_pion_only << " " << int_pion_only << " " << int_pion_only/int_prhi_pion_only << endl;

  //  cout << " elec eff. shlo: " << int_shlo_elec_only << " " << int_elec_only << " " << int_shlo_elec_only/int_elec_only << endl;
  //  cout << " pion rej. shlo: " << int_shlo_pion_only << " " << int_pion_only << " " << int_pion_only/int_shlo_pion_only << endl;

  gStyle->SetCanvasColor(10);
  gStyle->SetFrameFillColor(10);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetPalette(1,0);
  
  
  TCanvas *c3 = new TCanvas("c3","",900,900);
  
  c3->Divide(1,2);
  
  c3->cd(1);
  formatit(sh_elec, "3/4 - effect of PID legs on electrons only", "SHMS Shower","Events",0);
  formatit_diff3(sh_elec_elreal, "ELREAL TDC cut", "SHMS Shower","Events",0);
  formatit_diff5(sh_elec_elclean, "ELCLEAN TDC cut", "SHMS Shower","Events",0);
  //  formatit_diff7(sh_elec_shlo, "SHLO TDC cut", "SHMS Shower","Events",0);
  formatit_diff4(sh_elec_ngcer, "CER TDC cut", "SHMS Shower","Events",0);
  formatit_diff(sh_elec_prhi, "PRHI TDC cut", "SHMS Shower","Events",0);
  formatit_diff2(sh_elec_prlo, "PRLO TDC cut", "SHMS Shower","Events",0);
  
  c3->cd(2);
  formatit(sh_pion, "3/4 - effect of PID legs on pions only", "SHMS Shower","Events",0);
  formatit_diff3(sh_pion_elreal, "ELREAL TDC cut", "SHMS Shower","Events",1);
  formatit_diff5(sh_pion_elclean, "ELCLEAN TDC cut", "SHMS Shower","Events",1);
  formatit_diff4(sh_pion_ngcer, "CER TDC cut", "SHMS Shower","Events",1);
  formatit_diff(sh_pion_prhi, "PRHI TDC cut", "SHMS Shower","Events",1);
  formatit_diff2(sh_pion_prlo, "PRLO TDC cut", "SHMS Shower","Events",1);
  //  formatit_diff7(sh_pion_shlo, "SHLO TDC cut", "SHMS Shower","Events",1);
  
  
  c3->Print("effect_all_legs_on_elec_pions_hms.png"); 
  
  
  TCanvas *c4 = new TCanvas("c4","",900,900);
  
  c4->Divide(1,2);
  
  c4->cd(1);
  formatit(npes, "3/4, All", "SHMS CHER npe","Events",1);
  formatit_diff(npes_cerleg, "3/4, All - CHER TDC cut", "npe","Events",0);

  c4->cd(2);
  formatit(npes_elecs, "3/4, electrons", "SHMS CHER npe","Events",1);
  formatit_diff(npes_cerleg_cutelec, "3/4, Electrons - CHER TDC cut", "npe","Events",0);
  
  c4->Print("effect_of_cerleg_hms.png"); 
  
  TCanvas *c5 = new TCanvas("c5","",900,900);
  
  c5->Divide(1,1);
  
  c5->cd(1);
  formatit(shtrk_all, "3/4 - all", "SHMS Shower" , "Events", 1);
  formatit_diff(shtrk_all_elreal, "ELREAL", "SHMS Shower","Events",1);
  formatit_diff5(shtrk_all_elclean, "ELCLEAN", "SHMS Shower","Events",1);
  formatit_diff2(shtrk_all_prlo, "PRLO", "SHMS Shower","Events",1);
  formatit_diff3(shtrk_all_prhi, "PRHI", "SHMS Shower","Events",1);
  //  formatit_diff7(shtrk_all_shlo, "SHLO", "SHMS Shower","Events",1);
  formatit_diff4(shtrk_all_cerleg, "CERLEG", "SHMS Shower","Events",1);
  
  c5->Print("effect_all_legs_on_all_hms.png"); 
  

  // all important histos

  
  TCanvas *c57 = new TCanvas("c57","",900,900);
  
  c57->Divide(1,3);

  c57->cd(1);
  formatit(shtrk_all, "3/4 All", "SHMS Shower","Events",1);
  formatit_diff(shtrk_all_elreal, "3/4 - All after ELREAL cut", "SHMS Shower","Events",1);
  //  formatit_diff2(shtrk_all_shlo, "3/4 - All after SHLO cut", "SHMS Shower","Events",1);

  c57->cd(2);
  formatit(sh_elec, "3/4 - Electrons only", "SHMS Shower","Events",1);
  formatit_diff(sh_elec_elreal, "3/4 - Electrons after ELREAL cut", "SHMS Shower","Events",1);
  //  formatit_diff2(sh_elec_shlo, "3/4 - Electrons after SHLO cut", "SHMS Shower","Events",1);

  c57->cd(3);
  formatit(sh_pion, "3/4 - Pions only", "SHMS Shower","Events",1);
  formatit_diff(sh_pion_elreal, "3/4 - Pions after ELREAL cut", "SHMS Shower","Events",1);
  //  formatit_diff2(sh_pion_shlo, "3/4 - Pions after SHLO cut", "SHMS Shower","Events",1);

  c57->Print("sh_simple.png");


  TCanvas *c58 = new TCanvas("c58","",900,900);
  c58->Divide(1,3);

  c58->cd(1);
  formatit(prshtrk_all, "3/4 - All", "SHMS PrShower","Events",1);
  formatit_diff(prshtrk_all_elreal, "All after ELREAL cut", "SHMS PrShower","Events",1);
  formatit_diff3(prshtrk_all_prlo, "All after PRLO cut", "SHMS PrShower","Events",1);
  formatit_diff2(prshtrk_all_prhi, "All after PRHI cut", "SHMS PrShower","Events",1);

  c58->cd(2);
  formatit(prsh_elec, "3/4 - Electrons only", "SHMS PrShower","Events",1);
  formatit_diff(prsh_elec_elreal, "Electrons after ELREAL cut", "SHMS PrShower","Events",1);
  formatit_diff3(prsh_elec_prlo, "Electrons after PRLO cut", "SHMS PrShower","Events",1);
  formatit_diff2(prsh_elec_prhi, "Electrons after PRHI cut", "SHMS PrShower","Events",1);


  c58->cd(3);
  formatit(prsh_pion, "3/4 - Pions only", "SHMS PrShower","Events",1);
  formatit_diff(prsh_pion_elreal, "Pions after ELREAL cut", "SHMS PrShower","Events",1);
  formatit_diff3(prsh_pion_prlo, "Pions after PRLO cut", "SHMS PrShower","Events",1);
  formatit_diff2(prsh_pion_prhi, "Pions after PRHI cut", "SHMS PrShower","Events",1);

  c58->Print("prsh_all_elec_puions.png");


  // 2-D histos of shower vs preshower to show the PID thresholds cuts 


  TCanvas *c59 = new TCanvas("c59","",900,900);
  c59->Divide(2,2);
  c59->cd(1);
  formatit_2d(pr_vs_sh, "3/4 - All", "SHMS Shower","SHMS PrShower",1);
  c59->cd(2);
  formatit_2d(pr_vs_sh_elreal, "3/4, All - ELREAL cut", "SHMS Shower","SHMS PrShower",1);
  c59->cd(3);
  formatit_2d(pr_vs_sh_prlo, "3/4, All - PRLO cut", "SHMS Shower","SHMS PrShower",1);
  c59->cd(4);
  formatit_2d(pr_vs_sh_prhi, "3/4, All - PRHI cut", "SHMS Shower","SHMS PrShower",1);
  //  c59->cd(5);
  //  formatit_2d(pr_vs_sh_shlo, "3/4, All - SHLO cut", "SHMS Shower","SHMS PrShower",1);

  c59->Print("2d_sh_vs_pr.png");

  //

  TCanvas *c68 = new TCanvas("c68","",900,900);
  c68->Divide(1,1);
  c68->cd(1);
  formatit(prsh_sum_mult_cut, "3/4, PrShower Sum", "SHMS PrShower Sum","Events",1);
  formatit_diff(prsh_sum_tdcprlo_cut, "3/4, PrShower Sum, PRLO", "SHMS PrShower Sum (mV)","Events",1);
  formatit_diff2(prsh_sum_tdcprhi_cut, "3/4, PrShower Sum, PRHI", "SHMS PrShower Sum (mV)","Events",1);

  c68->Print("prsh_sum_adc.png");


  TCanvas *c699 = new TCanvas("c699","",900,900);
  c699->Divide(1,1);
  c699->cd(1);
  formatit(legcer_mult_cut, "3/4", "SHMS Cher Sum (mV)","Events",1);
  formatit_diff(legcer_mult_tdc_cut, "3/4, CHER cut", "SHMS Cher Sum (mV)","Events",1);

  c699->Print("cher_sum_adc.png");


  TCanvas *c99 = new TCanvas("c99","",900,900);
  c99->Divide(2,2);
  c99->cd(1);
  formatit_2d(prsh_sum_mult_vsetot, "3/4", "SHMS PrShower Sum (mV)","SHMS Shower EtotTrackNorm",1);
  c99->cd(2);
  formatit_2d(prsh_sum_tdcprlo_cut_vsetot, "3/4 - PRLO cut", "SHMS PrShower Sum (mV)","SHMS Shower EtotTrackNorm",1);
  c99->cd(3);
  formatit_2d(prsh_sum_tdcprhi_cut_vsetot, "3/4 - PRHI cut", "SHMS PrShower Sum (mV)","SHMS Shower EtotTrackNorm",1);

  c99->Print("2d_prsum_adc.png");




  return 0;
  
}
