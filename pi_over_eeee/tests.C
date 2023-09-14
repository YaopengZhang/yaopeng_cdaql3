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
  histo->SetLineColor(kPink-2);
  histo->SetLineWidth(3);
  histo->SetLineStyle(2);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.85,0.35,0.9);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kPink-2);
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
  histo->SetLineColor(kGreen+3);
  histo->SetLineWidth(3);
  histo->SetLineStyle(10);
  histo->Draw("same");  

  leg = new TLegend(0.15,0.8,0.35,0.85);
  leg->SetFillColor(-1);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.045);
  leg->SetTextColor(kGreen+3);
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

  leg = new TLegend(0.15,0.85,0.35,0.95);
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
    linex->Draw("same");
    liney->Draw("same");

  }

}



int main(){

TFile *myfile;


  TChain chain("T");


  // H2 25.035 

  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1840_-1.root");
  //  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1840_300001.root");
  chain.Add("/net/cdaq/cdaql3data/cdaq/simona/ROOTfiles2/shms_replay_production_1842_-1.root");


  Int_t nTracksx;
  Int_t nTracksy;
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
  Double_t track_beta, notrack_beta, justw,pist, delta;
  Double_t h1x_fptime, h2x_fptime, h1y_fptime, h2y_fptime, ng_x_atcer;
  Double_t prlo, prhi, shlo, ceramp, shadc, prshadc, edtm, legngcer,ello, hg_npe;


  chain.SetBranchAddress("T.shms.pPRLO_tdcTimeRaw", &prlo); 
  chain.SetBranchAddress("T.shms.pPRHI_tdcTimeRaw", &prhi); 

  chain.SetBranchAddress("T.shms.pSHWR_adcPulseAmp", &shadc); 
  chain.SetBranchAddress("T.shms.pPSHWR_adcPulseAmp", &prshadc); 

  chain.SetBranchAddress("T.shms.pNGCER_adcPulseAmp", &legngcer); 

  chain.SetBranchAddress("T.shms.pEDTM_tdcTime", &edtm); 

  chain.SetBranchAddress("T.shms.hEL_LO_tdcTime", &ello); 

  //  chain.SetBranchAddress("P.cer.goodAdcPulseAmp", &ceramp); 

  chain.SetBranchAddress("Ndata.P.dc.x", &nTracksx);
  chain.SetBranchAddress("Ndata.P.dc.y", &nTracksy);
  chain.SetBranchAddress("P.dc.ntrack", &track_nr);        
  chain.SetBranchAddress("P.ngcer.npeSum", &ng_npe);        
  chain.SetBranchAddress("P.hgcer.npeSum", &hg_npe);        
  chain.SetBranchAddress("P.hod.2x.nhits", &nhits_2x);        

  chain.SetBranchAddress("P.hod.2x.totNumGoodTdcHits", &goodtdchits_2x);        
  chain.SetBranchAddress("P.hod.2x.totNumGoodNegTdcHits", &goodnegtdchits_2x);        
  chain.SetBranchAddress("P.hod.2x.totNumGoodPosTdcHits", &goodpostdchits_2x);        
  chain.SetBranchAddress("P.hod.1x.totNumGoodNegTdcHits", &goodnegtdchits_1x);        
  chain.SetBranchAddress("P.hod.1x.totNumGoodPosTdcHits", &goodpostdchits_1x);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_1y);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_1y);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodNegTdcHits", &goodnegtdchits_2y);        
  chain.SetBranchAddress("P.hod.1y.totNumGoodPosTdcHits", &goodpostdchits_2y);        

  chain.SetBranchAddress("P.dc.x", track_x);        
  chain.SetBranchAddress("P.dc.y", track_y);        
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

  chain.SetBranchAddress("P.ngcer.xAtCer", &ng_x_atcer);

  chain.SetBranchAddress("Ndata.P.ngcer.goodAdcPulseInt", &ndcer);
  chain.SetBranchAddress("P.ngcer.goodAdcPulseInt", cerpulseint);        

  chain.SetBranchAddress("Ndata.P.ngcer.goodAdcPulseAmp", &ndcer);
  chain.SetBranchAddress("P.ngcer.goodAdcPulseAmp", cerpulseamp);        

  chain.SetBranchAddress("Ndata.P.ngcer.goodAdcTdcDiffTime", &ndcerdifft);
  chain.SetBranchAddress("P.ngcer.goodAdcTdcDiffTime", cerdifft);        

  chain.SetBranchAddress("Ndata.P.ngcer.numTracksMatched", &ncertr);
  chain.SetBranchAddress("P.ngcer.numTracksMatched", certr);        

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

  
  TH1F* xfp = new TH1F("", "", 100, -40., 40.);  
  TH1F* x_at_ng = new TH1F("", "", 120, -40., 40.);
  TH1F* x_at_ng_del_cut = new TH1F("", "", 120, -40., 40.);
  TH1F* x_at_ng_low_del = new TH1F("", "", 120, -40., 40.);
  
  TH1F* xfp_del_cut = new TH1F("", "", 100, -70., 70.);  
  TH1F* npes = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_hg = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_low_del = new TH1F("", "", 150, 0., 60.);
  TH1F* npes_del_cut = new TH1F("", "", 150, 0., 60.);
  
  TH1F *prsh = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_low_del = new TH1F("", "", 100, 0.0, 1.5); 
  TH1F *prsh_del_cut = new TH1F("", "", 100, 0.0, 1.5); 

  TH1F *shtrk_all = new TH1F("", "", 150, 0.01, 1.5);
  TH1F *shtrk_del_cut = new TH1F("", "", 150, 0.01, 1.5);
  TH1F *shtrk_low_del = new TH1F("", "", 150, 0.01, 1.5);

  //  for(Int_t i=0; i < nentries; i++){
  for(Int_t i=0; i < 20000; i++){
    
    chain.GetEntry(i);
    
    if (track_nr == 1 && edtm == 0.){
      
      xfp->Fill(track_x[0]);
      x_at_ng->Fill(ng_x_atcer);

      if(delta > -10. && delta < 22.){
	
	xfp_del_cut->Fill(track_x[0]);
	x_at_ng_del_cut->Fill(ng_x_atcer);
	prsh_del_cut->Fill(nprshtrk);
	npes_del_cut->Fill(ng_npe);
	shtrk_del_cut->Fill(shtrk);
      }

      prsh->Fill(nprshtrk);
      shtrk_all->Fill(shtrk);
      npes->Fill(ng_npe);

      if (delta < -10.){

	prsh_low_del->Fill(nprshtrk);
	npes_low_del->Fill(ng_npe);
	x_at_ng_low_del->Fill(ng_x_atcer);
	shtrk_low_del->Fill(shtrk);

      }

    }
    
    
  }
  

    gStyle->SetCanvasColor(10);
    gStyle->SetFrameFillColor(10);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetPadBorderMode(0);
    gStyle->SetPalette(1,0);
    
    
    TCanvas *c3 = new TCanvas("c3","",900,900);
    
    c3->Divide(2,2);
    
    c3->cd(1);
    formatit(xfp, "1.4 GeV/c , th = 25 deg, ELREAL", "P.dc.x[0]","Events",0);
    formatit_diff(xfp_del_cut, "delta: -10 to +22", "P.dc.x[0]","Events",1);

    c3->cd(2);
    formatit(prsh, "1.4 GeV/c , th = 25 deg, ELREAL", "","Events",0);
    formatit_diff(prsh_low_del, "delta > -10", "SHMS PreShower","Events",1);
    formatit_diff2(prsh_del_cut, "delta: -10 to +22", "SHMS PreShower","Events",1);


    c3->cd(3);
    formatit(npes, "1.4 GeV/c , th = 25 deg, ELREAL", "NGC NPEs", "Events",0);
    formatit_diff(npes_low_del, "delta > -10", "NGC NPEs","Events",1);
    formatit_diff2(npes_del_cut, "delta: -10 to +22", "NGC NPEs","Events",1);

    c3->cd(4);
    formatit(x_at_ng, "1.4 GeV/c , th = 25 deg, ELREAL", "P.ngcer.xAtCer","Events",0);
    formatit_diff(x_at_ng_low_del, "delta > -10", "P.ngcer.xAtCer","Events",1);
    formatit_diff2(x_at_ng_del_cut, "delta: -10 to +22", "P.ngcer.xAtCer","Events",1);
   

    
    c3->Print("test1_1841.png"); 
    

   TCanvas *c4 = new TCanvas("c4","",900,900);
    
    c4->Divide(2,2);

    formatit(shtrk_all, "1.4 GeV/c , th = 25 deg, ELREAL", "","Events",0);
    formatit_diff(shtrk_low_del, "delta > -10", "SHMS Shower","Events",0);
    formatit_diff2(shtrk_del_cut, "delta: -10 to +22", "SHMS Shower","Events",0);

    c4->Print("test2_1841.png"); 

    return 0;
    
}
