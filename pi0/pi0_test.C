#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include "TChain.h"
#include "TTree.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TFile.h"
#include "TLine.h"
#include "TLatex.h"
#include "TMatrixD.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <TString.h>

const double_t convdeg = TMath::Pi()/180.;
const double_t MinClusSize = 3;
const double_t clusTmax = 160.;
const double_t clusTmin = 148.;
const double_t LH2_10cm_target = 1.00794*931.5/1000.;
const double_t LD2_10cm_target = 2.014*931.5/1000./2.;
const double_t electron_mass = 0.51099895e-3;


void GetPvect(double_t clx, double_t cly,double_t clz, double_t cle, TVector3 &vtx, TVector3 &pvect, double_t angle){

	double nps_angle = angle * convdeg;
    
	double cth = cos(nps_angle);
	double sth = sin(nps_angle);

	double xlab = clx*cth + clz*sth - vtx.X();
	double ylab = cly - vtx.Y();
	double zlab = -clx*sth + clz*cth - vtx.Z();

	TVector3 rvect(xlab, ylab, zlab);
	double th = rvect.Theta();
	double ph = rvect.Phi();   

	pvect.SetXYZ(cle * cos(ph) * sin(th),
	cle * sin(ph) * sin(th),
	cle * cos(th));

	return;
}

void Pi0_mass_calculation(int fileoption, int fileNo, Double_t Targetname, int RunNo, Double_t angle, Double_t beamEne){
    TChain	*ch1 = new TChain("T");
    // TString File_Path = "/lustre19/expphy/cache/hallc/c-nps/analysis/online/replays/";
    // TString FileName = File_Path + Form("nps_hms_coin_%d_0_1_-1.root",RunNo);
    TString File_Path = "/net/cdaq/cdaql4data/cdaq/hallc-online-nps2023/ROOTfiles/COIN/SKIM/";
    TString FileName = File_Path + Form("nps_hms_skim_%d_0_1_-1.root",RunNo);
    ch1->Add(FileName);
    std::cout<<"Processing "<<FileName<<"..."<<std::endl;

    ch1->SetBranchStatus("*",false);
    
    ch1->SetBranchStatus("NPS.cal.clusE", true);
    ch1->SetBranchStatus("NPS.cal.clusT", true);
    ch1->SetBranchStatus("NPS.cal.clusX", true);
    ch1->SetBranchStatus("NPS.cal.clusY", true);
    ch1->SetBranchStatus("NPS.cal.clusZ", true);
    ch1->SetBranchStatus("NPS.cal.clusSize", true);
    ch1->SetBranchStatus("NPS.cal.nclust", true);

    ch1->SetBranchStatus("H.react.ok", true);
    ch1->SetBranchStatus("H.react.x", true);
    ch1->SetBranchStatus("H.react.y", true);
    ch1->SetBranchStatus("H.react.z", true);

    ch1->SetBranchStatus("NPS.cal.trk.px", true);
    ch1->SetBranchStatus("NPS.cal.trk.py", true);
    ch1->SetBranchStatus("NPS.cal.trk.pz", true);

    ch1->SetBranchStatus("H.gtr.px", true);
    ch1->SetBranchStatus("H.gtr.py", true);
    ch1->SetBranchStatus("H.gtr.pz", true);
    ch1->SetBranchStatus("H.gtr.ok", true);
    ch1->SetBranchStatus("H.gtr.dp", true);

    ch1->SetBranchStatus("H.cal.etracknorm", true);
    ch1->SetBranchStatus("H.cer.npeSum", true);

    ch1->SetBranchStatus("T.helicity.nqrt", true);
    ch1->SetBranchStatus("T.helicity.hel", true);
    ch1->SetBranchStatus("T.helicity.helpred", true);
    ch1->SetBranchStatus("T.helicity.helrep", true);

    //Cluster info
    Double_t nclust;
    Double_t clusX[20];
    Double_t clusY[20];
    Double_t clusZ[20];
    Double_t clusT[20];
    Double_t clusE[20];
    Double_t clusSize[20];

    // Vertex Position
    Double_t vtx_ok;
    Double_t vtx_x;
    Double_t vtx_y;
    Double_t vtx_z;

    // HMS golden track
    Double_t gtr_px;
    Double_t gtr_py;
    Double_t gtr_pz;
    Double_t gtr_ok;
    Double_t gtr_dp;
    Double_t etracknorm;
    Double_t npesum;

    Double_t T_helicity_nqrt, T_helicity_hel, T_helicity_helpred, T_helicity_helrep;

    ch1->SetBranchAddress("NPS.cal.clusE", clusE);
    ch1->SetBranchAddress("NPS.cal.clusT", clusT);
    ch1->SetBranchAddress("NPS.cal.clusX", clusX);
    ch1->SetBranchAddress("NPS.cal.clusY", clusY);
    ch1->SetBranchAddress("NPS.cal.clusZ", clusZ);
    ch1->SetBranchAddress("NPS.cal.clusSize", clusSize);
    ch1->SetBranchAddress("NPS.cal.nclust", &nclust);

    ch1->SetBranchAddress("H.react.ok", &vtx_ok);
    ch1->SetBranchAddress("H.react.x", &vtx_x);
    ch1->SetBranchAddress("H.react.y", &vtx_y);
    ch1->SetBranchAddress("H.react.z", &vtx_z);

    ch1->SetBranchAddress("H.gtr.px",&gtr_px);
    ch1->SetBranchAddress("H.gtr.py",&gtr_py);
    ch1->SetBranchAddress("H.gtr.pz",&gtr_pz);
    ch1->SetBranchAddress("H.gtr.ok",&gtr_ok);
    ch1->SetBranchAddress("H.gtr.dp", &gtr_dp);

    ch1->SetBranchAddress("H.cal.etracknorm", &etracknorm);
    ch1->SetBranchAddress("H.cer.npeSum", &npesum);

    ch1->SetBranchAddress("T.helicity.nqrt", &T_helicity_nqrt);
    ch1->SetBranchAddress("T.helicity.hel", &T_helicity_hel); // actualHelicity
    ch1->SetBranchAddress("T.helicity.helpred", &T_helicity_helpred);
    ch1->SetBranchAddress("T.helicity.helrep", &T_helicity_helrep);

    TFile* f1;
    if(fileoption==1) f1 = new TFile(Form("./pi0/pi0_multiruns_%d.root",fileNo),"recreate");
    else f1 = new TFile(Form("./pi0/pi0_multiruns_%d.root",fileNo),"update");
    TTree *tree = new TTree(Form("Run_%d",RunNo),Form("Run_%d",RunNo));
    Double_t phi, hel;
    TBranch* b_phi = tree->Branch("phi",&phi,"phi/D");
    TBranch* b_hel = tree->Branch("hel",&hel,"hel/D");

    TH1F* inv_mass = new TH1F(Form("invmass_%d",RunNo),"Invariant mass",70,0,0.3);
    inv_mass->GetXaxis()->SetTitle("Energy(GeV)");
    inv_mass->SetLineColor(4);

    TH1F* miss_mass = new TH1F(Form("missingmass2_%d",RunNo),"Missing mass square",200,0,5);
    miss_mass->GetXaxis()->SetTitle("Energy(GeV)");
    miss_mass->SetLineColor(2);

    Int_t NofBins_phi = 20;
    Double_t Bin_length = 2.*TMath::Pi()/(NofBins_phi*1.);
    TH1F* h_phi = new TH1F(Form("h_phi_%d",RunNo),"#phi distribution;#phi;counts",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_phi_0 = new TH1F(Form("h_phi_0_%d",RunNo),"#phi distribution (helicity 0);#phi;counts",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_phi_pos = new TH1F(Form("h_phi_pos_%d",RunNo),"#phi distribution (helicity +);#phi;counts",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_phi_neg = new TH1F(Form("h_phi_neg_%d",RunNo),"#phi distribution (helicity -);#phi;counts",NofBins_phi,0,2.*TMath::Pi());

    Double_t Asymmetry_up[NofBins_phi], Asymmetry_down[NofBins_phi], Asymmetry[NofBins_phi];
    memset(Asymmetry_up,0,sizeof(Asymmetry_up));
    memset(Asymmetry_down,0,sizeof(Asymmetry_down));
    TH1F* h_asymmetry = new TH1F(Form("h_asymmetry_%d",RunNo),"#pi^{0} asymmetry;#phi;asymmetry",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_asymmetry_diff = new TH1F(Form("h_asymmetry_diff_%d",RunNo),"#pi^{0} N_{ +} - N_{ -};#phi;N_{+} - N_{-}",NofBins_phi,0,2.*TMath::Pi());

    TH1F* h_clust_T = new TH1F(Form("h_clust_T_%d",RunNo),"clust_T",100,0,500);

    Long64_t nentries = ch1->GetEntries();
    for(Long64_t evt=0; evt<nentries; evt++){
    // for(Long64_t evt= 0; evt < 1000; evt++){

        ch1->GetEntry(evt);

        if(abs(vtx_z)>4.) continue;

        if(nclust<1.5) continue;

        if(vtx_ok < 1) continue;
        TVector3 v_vtx(vtx_x, vtx_y, vtx_z);

        if(gtr_dp < -10 || gtr_dp > 10) continue;

        if(etracknorm < 0.7 || etracknorm>1.3) continue;

        if(npesum < 2) continue;

        if(gtr_ok < 1) continue;

        TLorentzVector sele_vect;
        if(gtr_px > 1.e30) continue;
        sele_vect.SetXYZM(gtr_px,gtr_py,gtr_pz,electron_mass);

        // cout<<gtr_pz<<endl;

        for(int i=0; i<nclust;i++){
            h_clust_T->Fill(clusT[i]);
            for(int j=i+1; j<nclust;j++){

                if(clusSize[i] < MinClusSize || clusSize[j] <MinClusSize) continue;

                if(clusT[i] < clusTmin || clusT[i] > clusTmax) continue;
                if(clusT[j] <= clusTmin || clusT[j] >= clusTmax) continue;

                if(clusE[i]<0.5||clusE[j]<0.5) continue;

                TVector3 v_Q1, v_Q2;
                GetPvect(clusX[i], clusY[i],clusZ[i],clusE[i], v_vtx, v_Q1, angle);
                GetPvect(clusX[j], clusY[j],clusZ[j],clusE[j], v_vtx, v_Q2, angle);

                TLorentzVector Q1;
                TLorentzVector Q2;
                TLorentzVector Q3;

                Q1.SetPxPyPzE(v_Q1[0], v_Q1[1], v_Q1[2], clusE[i]);
                Q2.SetPxPyPzE(v_Q2[0], v_Q2[1], v_Q2[2], clusE[j]);
                Q3=Q1+Q2;

                Double_t im2 = Q3.M2();
                Double_t invmass = sqrt(im2);
                inv_mass->Fill(invmass);

                TLorentzVector beam_vect;
                beam_vect.SetXYZM(0,0,beamEne,electron_mass);

                TLorentzVector target_vect;
                target_vect.SetXYZM(0,0,0,Targetname);

                TLorentzVector X_vect;
                X_vect = (beam_vect + target_vect - sele_vect - Q1 - Q2);
                if (invmass < 0.1 || invmass > 0.13) continue;
                Double_t mm2 = X_vect.M2();
                // if( mm2<1.1 || mm2>1.7 ) continue;
                miss_mass->Fill(mm2);


                if( mm2<1.1 || mm2>1.8 ) continue;

                // kp is a TVector3 of the scattered electron;
                // qp is the TVector3 of the photon (or pi0=photon1+photon2)
                TVector3 k, kp, qp;
                k.SetXYZ(0,0,beamEne);
                kp.SetXYZ(gtr_px,gtr_py,gtr_pz);
                qp.SetXYZ(Q3.X(),Q3.Y(),Q3.Z());
                TVector3 q=k-kp;
                TVector3 v1=q.Cross(kp);
                TVector3 v2=q.Cross(qp);
                Double_t fphi=v1.Angle(v2);
                if(q.Dot(v1.Cross(v2))<0) fphi=2.*TMath::Pi()-fphi;
                h_phi->Fill(fphi);
                if(T_helicity_hel>0.) h_phi_pos->Fill(fphi);
                if(T_helicity_hel<0.) h_phi_neg->Fill(fphi);
                if(T_helicity_hel==0.) h_phi_0->Fill(fphi);

                phi = fphi;
                hel = T_helicity_hel;

                Int_t BinNo = int(ceil(fphi/Bin_length));
                Asymmetry_up[BinNo-1] += T_helicity_hel;
                Asymmetry_down[BinNo-1] += 1.;

                // cout<<evt<<"\t"<<T_helicity_nqrt<<"\t"<<T_helicity_hel<<endl;

                tree->Fill();

            }
        }
    }

    for(int i=0;i<NofBins_phi;i++){
        Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
        h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
        h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));

        h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
    }

    /*
    TCanvas *c_phi = new TCanvas("c_phi","c_phi",1200,800);
    h_phi->Draw();
    c_phi->SaveAs("./pi0/phi_distribution.pdf");

    TCanvas *c_phi_0 = new TCanvas("c_phi_0","c_phi_0",1200,800);
    h_phi_0->Draw();
    c_phi_0->SaveAs("./pi0/phi_0_distribution.pdf");

    TCanvas *c_phi_pos = new TCanvas("c_phi_pos","c_phi_pos",1200,800);
    h_phi_pos->Draw();
    c_phi_pos->SaveAs("./pi0/phi_pos_distribution.pdf");

    TCanvas *c_phi_neg = new TCanvas("c_phi_neg","c_phi_neg",1200,800);
    h_phi_neg->Draw();
    c_phi_neg->SaveAs("./pi0/phi_neg_distribution.pdf");

    TCanvas *c_asymmetry = new TCanvas("c_asymmetry","c_asymmetry",1200,800);
    h_asymmetry->SetStats(0);
    h_asymmetry->Draw("E1");
    c_asymmetry->SaveAs("./pi0/phi_asymmetry.pdf");

    TCanvas *c_asymmetry_diff = new TCanvas("c_asymmetry_diff","c_asymmetry_diff",1200,800);
    h_asymmetry_diff->SetStats(0);
    h_asymmetry_diff->Draw();
    c_asymmetry_diff->SaveAs("./pi0/phi_asymmetry_diff.pdf");

    TCanvas *c1 = new TCanvas("c1","invmass",1200,800);
    c1->SetLineWidth(4);
    inv_mass->Draw();
    c1->SaveAs("./pi0/invmass.pdf");

    TCanvas *c2 = new TCanvas("c2","missingmass2",1200,800);
    c2->SetLineWidth(4);
    miss_mass->Draw();
    c2->SaveAs("./pi0/missingmass2.pdf");
    */

    f1->cd();
    miss_mass->Write();
    inv_mass->Write();
    h_phi->Write();
    h_phi_0->Write();
    h_phi_pos->Write();
    h_phi_neg->Write();
    h_asymmetry->Write();
    h_asymmetry_diff->Write();
    h_clust_T->Write();
    tree->Write();
    f1->Close();
}

void pi0_test(){
    // "/lustre19/expphy/cache/hallc/c-nps/analysis/online/replays/"

    // OUT  LD2  20.58
    // Pi0_mass_calculation(1,0,LD2_10cm_target,1723,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,0,LD2_10cm_target,1724,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,0,LD2_10cm_target,1725,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,0,LD2_10cm_target,1726,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,0,LD2_10cm_target,1735,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,0,LD2_10cm_target,1737,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,0,LD2_10cm_target,1738,20.58,10.538); // 1 "recreate"; 0 "update"

    int All_runs_0[] = {1723,1724,1725,1726,1735,1737,1738};
    int arrayLength_0 = sizeof(All_runs_0)/sizeof(All_runs_0[0]);

    // OUT  LD2  18.72
    // Pi0_mass_calculation(1,1,LD2_10cm_target,1757,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1758,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1759,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1945,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1946,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1947,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1948,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1949,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1950,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1952,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,1,LD2_10cm_target,1953,18.72,10.538); // 1 "recreate"; 0 "update"


    int All_runs_1[] = {1757,1758,1759,1945,1946,1947,1948,1949,1950,1952,1953};
    int arrayLength_1 = sizeof(All_runs_1)/sizeof(All_runs_1[0]);

    // OUT  LH2  20.58
    // Pi0_mass_calculation(1,2,LH2_10cm_target,1727,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,2,LH2_10cm_target,1728,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,2,LH2_10cm_target,1729,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,2,LH2_10cm_target,1730,20.58,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,2,LH2_10cm_target,1731,20.58,10.538); // 1 "recreate"; 0 "update"

    int All_runs_2[] = {1727,1728,1729,1730,1731};
    int arrayLength_2 = sizeof(All_runs_2)/sizeof(All_runs_2[0]);

    // OUT  LH2  18.72
    // Pi0_mass_calculation(1,5,LH2_10cm_target,1954,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,5,LH2_10cm_target,1955,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,5,LH2_10cm_target,1956,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,5,LH2_10cm_target,1957,18.72,10.538); // 1 "recreate"; 0 "update"

    int All_runs_5[] = {1954,1955,1956,1957};
    int arrayLength_5 = sizeof(All_runs_5)/sizeof(All_runs_5[0]);

    // IN  LD2  18.72
    // Pi0_mass_calculation(1,3,LD2_10cm_target,1820,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1821,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1822,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1824,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1825,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1834,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1835,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1837,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1839,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1840,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1859,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1863,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1864,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1865,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1866,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1867,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1874,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1875,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1876,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1891,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1904,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1905,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1906,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1907,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1908,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1910,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1911,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1913,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1914,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1926,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1927,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1929,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1930,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,3,LD2_10cm_target,1931,18.72,10.538); // 1 "recreate"; 0 "update"

    int All_runs_3[] = {1820,1821,1822,1824,1825,1834,1835,1837,1839,1840,1859,1863,1864,1865,1866,1867,1874,1875,1876,1891,1904,1905,1906,1907,1908,1910,1911,1913,1914,1926,1927,1929,1930,1931};
    int arrayLength_3 = sizeof(All_runs_3)/sizeof(All_runs_3[0]);

    // IN  LH2  18.72
    // Pi0_mass_calculation(1,4,LH2_10cm_target,1826,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1827,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1828,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1829,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1830,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1831,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1848,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1849,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1851,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1877,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1878,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1879,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1880,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1881,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1882,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1883,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1884,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1885,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1886,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1887,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1896,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1897,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1898,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1899,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1916,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1917,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1918,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1919,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1920,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1921,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1922,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1934,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1935,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1936,18.72,10.538); // 1 "recreate"; 0 "update"
    // Pi0_mass_calculation(0,4,LH2_10cm_target,1937,18.72,10.538); // 1 "recreate"; 0 "update"

    int All_runs_4[] = {1826,1827,1828,1829,1830,1831,1848,1849,1851,1877,1878,1879,1880,1881,1882,1883,1884,1885,1886,1887,1896,1897,1898,1899,1916,1917,1918,1919,1920,1921,1922,1934,1935,1936,1937};
    int arrayLength_4 = sizeof(All_runs_4)/sizeof(All_runs_4[0]);

    std::cout<<"Process done!"<<std::endl;



    Int_t NofBins_phi = 20;
    Double_t Bin_length = 2.*TMath::Pi()/(NofBins_phi*1.);
    TH1F* h_phi = new TH1F("h_phi","#phi distribution;#phi;counts",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_phi_0 = new TH1F("h_phi_0","#phi distribution (helicity 0);#phi;counts",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_phi_pos = new TH1F("h_phi_pos","#phi distribution (helicity +);#phi;counts",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_phi_neg = new TH1F("h_phi_neg","#phi distribution (helicity -);#phi;counts",NofBins_phi,0,2.*TMath::Pi());

    Double_t Asymmetry_up[NofBins_phi], Asymmetry_down[NofBins_phi], Asymmetry[NofBins_phi];
    memset(Asymmetry_up,0,sizeof(Asymmetry_up));
    memset(Asymmetry_down,0,sizeof(Asymmetry_down));
    TH1F* h_asymmetry = new TH1F("h_asymmetry","#pi^{0} asymmetry;#phi;asymmetry",NofBins_phi,0,2.*TMath::Pi());
    TH1F* h_asymmetry_diff = new TH1F("h_asymmetry_diff","#pi^{0} N_{ +} - N_{ -};#phi;N_{+} - N_{-}",NofBins_phi,0,2.*TMath::Pi());

    // /*
    // OUT  LD2  20.58
    TFile* file_0 = TFile::Open("./pi0/pi0_multiruns_0.root", "READ");
    for(int i=0;i<arrayLength_0;i++){

        TTree* tree = (TTree*)file_0->Get(Form("Run_%d",All_runs_0[i]));

        Double_t phi, hel;
        tree->SetBranchAddress("phi", &phi);
        tree->SetBranchAddress("hel", &hel);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            h_phi->Fill(phi);
            if(hel>0.) h_phi_pos->Fill(phi);
            if(hel<0.) h_phi_neg->Fill(phi);
            if(hel==0.) h_phi_0->Fill(phi);

            Int_t BinNo = int(ceil(phi/Bin_length));
            Asymmetry_up[BinNo-1] += hel;
            Asymmetry_down[BinNo-1] += 1.;

        }

        for(int i=0;i<NofBins_phi;i++){
            Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
            h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
            h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));
            h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
        }

    }

    // OUT  LD2  18.72
    TFile* file_1 = TFile::Open("./pi0/pi0_multiruns_1.root", "READ");
    for(int i=0;i<arrayLength_1;i++){

        TTree* tree = (TTree*)file_1->Get(Form("Run_%d",All_runs_1[i]));

        Double_t phi, hel;
        tree->SetBranchAddress("phi", &phi);
        tree->SetBranchAddress("hel", &hel);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            h_phi->Fill(phi);
            if(hel>0.) h_phi_pos->Fill(phi);
            if(hel<0.) h_phi_neg->Fill(phi);
            if(hel==0.) h_phi_0->Fill(phi);

            Int_t BinNo = int(ceil(phi/Bin_length));
            Asymmetry_up[BinNo-1] += hel;
            Asymmetry_down[BinNo-1] += 1.;

        }

        for(int i=0;i<NofBins_phi;i++){
            Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
            h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
            h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));
            h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
        }

    }

    // OUT  LH2  20.58
    TFile* file_2 = TFile::Open("./pi0/pi0_multiruns_2.root", "READ");
    for(int i=0;i<arrayLength_2;i++){

        TTree* tree = (TTree*)file_2->Get(Form("Run_%d",All_runs_2[i]));

        Double_t phi, hel;
        tree->SetBranchAddress("phi", &phi);
        tree->SetBranchAddress("hel", &hel);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            h_phi->Fill(phi);
            if(hel>0.) h_phi_pos->Fill(phi);
            if(hel<0.) h_phi_neg->Fill(phi);
            if(hel==0.) h_phi_0->Fill(phi);

            Int_t BinNo = int(ceil(phi/Bin_length));
            Asymmetry_up[BinNo-1] += hel;
            Asymmetry_down[BinNo-1] += 1.;

        }

        for(int i=0;i<NofBins_phi;i++){
            Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
            h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
            h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));
            h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
        }

    }

    // OUT  LH2  18.72
    TFile* file_5 = TFile::Open("./pi0/pi0_multiruns_5.root", "READ");
    for(int i=0;i<arrayLength_5;i++){

        TTree* tree = (TTree*)file_5->Get(Form("Run_%d",All_runs_5[i]));

        Double_t phi, hel;
        tree->SetBranchAddress("phi", &phi);
        tree->SetBranchAddress("hel", &hel);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            h_phi->Fill(phi);
            if(hel>0.) h_phi_pos->Fill(phi);
            if(hel<0.) h_phi_neg->Fill(phi);
            if(hel==0.) h_phi_0->Fill(phi);

            Int_t BinNo = int(ceil(phi/Bin_length));
            Asymmetry_up[BinNo-1] += hel;
            Asymmetry_down[BinNo-1] += 1.;

        }

        for(int i=0;i<NofBins_phi;i++){
            Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
            h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
            h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));
            h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
        }

    }
    // */

    /*
    // IN  LD2  18.72
    TFile* file_3 = TFile::Open("./pi0/pi0_multiruns_3.root", "READ");
    for(int i=0;i<arrayLength_3;i++){

        TTree* tree = (TTree*)file_3->Get(Form("Run_%d",All_runs_3[i]));

        Double_t phi, hel;
        tree->SetBranchAddress("phi", &phi);
        tree->SetBranchAddress("hel", &hel);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            h_phi->Fill(phi);
            if(hel>0.) h_phi_pos->Fill(phi);
            if(hel<0.) h_phi_neg->Fill(phi);
            if(hel==0.) h_phi_0->Fill(phi);

            Int_t BinNo = int(ceil(phi/Bin_length));
            Asymmetry_up[BinNo-1] += hel;
            Asymmetry_down[BinNo-1] += 1.;

        }

        for(int i=0;i<NofBins_phi;i++){
            Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
            h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
            h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));
            h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
        }

    }

    // IN  LH2  18.72
    TFile* file_4 = TFile::Open("./pi0/pi0_multiruns_4.root", "READ");
    for(int i=0;i<arrayLength_4;i++){

        TTree* tree = (TTree*)file_4->Get(Form("Run_%d",All_runs_4[i]));

        Double_t phi, hel;
        tree->SetBranchAddress("phi", &phi);
        tree->SetBranchAddress("hel", &hel);

        Long64_t nEntries = tree->GetEntries();
        for (Long64_t i = 0; i < nEntries; i++) {
            tree->GetEntry(i);

            h_phi->Fill(phi);
            if(hel>0.) h_phi_pos->Fill(phi);
            if(hel<0.) h_phi_neg->Fill(phi);
            if(hel==0.) h_phi_0->Fill(phi);

            Int_t BinNo = int(ceil(phi/Bin_length));
            Asymmetry_up[BinNo-1] += hel;
            Asymmetry_down[BinNo-1] += 1.;

        }

        for(int i=0;i<NofBins_phi;i++){
            Asymmetry[i] = Asymmetry_up[i]/Asymmetry_down[i];
            h_asymmetry->SetBinContent(i+1,Asymmetry[i]);
            h_asymmetry->SetBinError(i+1,sqrt((1-pow(Asymmetry[i],2))/Asymmetry_down[i]));
            h_asymmetry_diff->SetBinContent(i+1,Asymmetry_up[i]);
        }

    }
    */

    TCanvas *c_phi = new TCanvas("c_phi","c_phi",1200,800);
    h_phi->Draw();
    c_phi->SaveAs("./pi0/phi_distribution.pdf");

    TCanvas *c_phi_0 = new TCanvas("c_phi_0","c_phi_0",1200,800);
    h_phi_0->Draw();
    c_phi_0->SaveAs("./pi0/phi_0_distribution.pdf");

    TCanvas *c_phi_pos = new TCanvas("c_phi_pos","c_phi_pos",1200,800);
    h_phi_pos->Draw();
    c_phi_pos->SaveAs("./pi0/phi_pos_distribution.pdf");

    TCanvas *c_phi_neg = new TCanvas("c_phi_neg","c_phi_neg",1200,800);
    h_phi_neg->Draw();
    c_phi_neg->SaveAs("./pi0/phi_neg_distribution.pdf");

    TCanvas *c_asymmetry = new TCanvas("c_asymmetry","c_asymmetry",1200,800);
    h_asymmetry->SetStats(0);
    h_asymmetry->Draw("E1");
    c_asymmetry->SaveAs("./pi0/phi_asymmetry.pdf");

    TCanvas *c_asymmetry_diff = new TCanvas("c_asymmetry_diff","c_asymmetry_diff",1200,800);
    h_asymmetry_diff->SetStats(0);
    h_asymmetry_diff->Draw();
    c_asymmetry_diff->SaveAs("./pi0/phi_asymmetry_diff.pdf");

    file_0->Close();
    file_1->Close();
    file_2->Close();
    file_5->Close();
    delete file_0;
    delete file_1;
    delete file_2;
    delete file_5;
    // file_3->Close();
    // file_4->Close();
    // delete file_3;
    // delete file_4;
}


/*
void pi0_test(){

    // Pi0_mass_calculation("recreate", "T1721", LD2_10cm_target, 1721, 0, 0, 18.75, 10.5387);
    // Pi0_mass_calculation("recreate", "T1725", LD2_10cm_target, 1725, 0, 0, 20.61, 10.5384);

    // Pi0_mass_calculation("recreate", "T1723", LD2_10cm_target, 1723, 0, 9, 20.61, 10.5386);
    // Pi0_mass_calculation("recreate", "T1724", LD2_10cm_target, 1724, 1, 1, 20.61, 10.5387);
    // Pi0_mass_calculation("recreate", "T1725", LD2_10cm_target, 1725, 0, 0, 20.61, 10.5384);
    // Pi0_mass_calculation("recreate", "T1726", LD2_10cm_target, 1726, 0, 1, 20.61, 10.5385);
    // Pi0_mass_calculation("recreate", "T1735", LD2_10cm_target, 1735, 0, 8, 20.61, 10.5391);
    // Pi0_mass_calculation("recreate", "T1736", LD2_10cm_target, 1736, 0, 10, 20.61, 10.5391);
    // Pi0_mass_calculation("recreate", "T1738", LD2_10cm_target, 1738, 0, 10, 20.61, 10.5391);
    // Pi0_mass_calculation("recreate", "T1740", LD2_10cm_target, 1740, 0, 1, 20.61, 10.5389);
    // Pi0_mass_calculation("recreate", "T1741", LD2_10cm_target, 1741, 0, 4, 20.61, 10.5389);

    // std::vector<double> myVector;
    // double maxSizeAsDouble = static_cast<double>(myVector.max_size());
    // std::cout << "Max size of myVector: " << maxSizeAsDouble << std::endl;

    
    // Half-wave Plate Status -- OUT
    // const int NofRuns = 9;
    // int RunNo[NofRuns] = {1723,1724,1725,1726,1735,1736,1738,1740,1741};
    // int Segmin[NofRuns] = {0,0,0,0,0,0,0,0,0};
    // int Segmax[NofRuns] = {9,3,0,1,8,10,10,1,4}; // 55 segments
    // const int NofRuns = 1;
    // int RunNo[NofRuns] = {1724};
    // int Segmin[NofRuns] = {0};
    // int Segmax[NofRuns] = {3}; // 1 segments
    // const int NofRuns = 9;
    // int RunNo[NofRuns] = {1723,1724,1725,1726,1735,1736,1738,1740,1741};
    // int Segmin[NofRuns] = {0,0,0,0,0,0,0,0,0};
    // int Segmax[NofRuns] = {0,0,0,0,0,0,0,0,0}; // 55 segments
    // Pi0_mass_calculation_MuliRuns(NofRuns,LD2_10cm_target,RunNo,Segmin,Segmax,20.61,10.5389);
    

    
    // Half-wave Plate Status -- IN 1865
    // const int NofRuns = 9;
    // int RunNo[NofRuns] = {1859,1862,1863,1864,1866,1867,1874,1875,1876};
    // int Segmin[NofRuns] = {0,0,0,0,0,0,0,0,0};
    // int Segmax[NofRuns] = {0,4,4,2,4,5,0,1,0}; // 29 segments
    // const int NofRuns = 9;
    // int RunNo[NofRuns] = {1859,1862,1863,1864,1866,1867,1874,1875,1876};
    // int Segmin[NofRuns] = {0,0,0,0,0,0,0,0,0};
    // int Segmax[NofRuns] = {0,0,0,0,0,0,0,0,0}; // 29 segments
    // Pi0_mass_calculation_MuliRuns(NofRuns,LD2_10cm_target,RunNo,Segmin,Segmax,18.75,10.5382);
    


    // Pi0_mass_calculation("recreate", "T1722", LD2_10cm_target, 1722, 0, 0, 18.75, 10.5387);
    // Pi0_mass_calculation("recreate", "T1662", LD2_10cm_target, 1662, 0, 0, 20.63, 10.5389);

	// Chain("recreate","T1717","1717_run_minv","run1717_invmass","1717_run_mmiss","run1717_mmass",0,1,18.75);
	// Chain("update","T1718","1718_run_minv","run1718_invmass","1718_run_mmiss","run1718_mmiss",1,1,18.75);
    // Chain("update","T1719","1719_run_minv","run1719_invmass","1719_run_mmiss","run1719_mmiss",2,1,18.75);
    // Chain("update","T1720","1720_run_minv","run1720_invmass","1720_run_mmiss","run1720_mmiss",3,1,18.75);
    // Chain("recreate","T1721","1721_run_minv","run1721_invmass","1721_run_mm2","run1721_mm2",LD2_10cm_target,4,1,18.75,10.5387);
    // Chain("update","T1722","1722_run_minv","run1722_invmass","1722_run_mm2","run1722_mm2",LD2_10cm_target,5,6,18.75,10.5386);
    // Chain("update","T1723","1723_run_minv","run1723_invmass","1723_run_mm2","run1723_mm2",LD2_10cm_target,6,10,20.61,10.5386);
	// Chain("update","T1724","1724_run_minv","run1724_invmass","1724_run_mm2","run1724_mm2",LD2_10cm_target,7,4,20.61,10.5387);
    // Chain("update","T1725","1725_run_minv","run1725_invmass","1725_run_mm2","run1725_mm2",LD2_10cm_target,8,1,20.61,10.5384);
    // Chain("update","T1726","1726_run_minv","run1726_invmass","1726_run_mm2","run1726_mm2",LD2_10cm_target,9,2,20.61,10.5385);
    // Chain("update","T1727","1727_run_minv","run1727_invmass","1727_run_mm2","run1727_mm2",LH2_10cm_target,10,4,20.61,10.5384);
    // Chain("update","T1728","1728_run_minv","run1728_invmass","1728_run_mm2","run1728_mm2",LH2_10cm_target,11,1,20.61,10.5384);
    // Chain("update","T1729","1729_run_minv","run1729_invmass","1729_run_mm2","run1729_mm2",LH2_10cm_target,12,1,20.61,10.5384);
    // Chain("update","T1731","1731_run_minv","run1731_invmass","1731_run_mm2","run1731_mm2",LH2_10cm_target,13,1,20.61,10.5386);
    // Chain("update","T1732","1732_run_minv","run1732_invmass","1732_run_mm2","run1732_mm2",LH2_10cm_target,14,2,20.61,10.5386);
    // Chain("update","T1733","1733_run_minv","run1733_invmass","1733_run_mm2","run1733_mm2",LH2_10cm_target,15,1,20.61,10.5384);
    // //Chain("update","T1734","1734_run_minv","run1734_invmass","1734_run_mmiss","run1734_mmiss",16,2,20.61);
    // Chain("update","T1735","1735_run_minv","run1735_invmass","1735_run_mm2","run1735_mm2",LD2_10cm_target,17,9,20.61,10.5391);
    // Chain("update","T1736","1736_run_minv","run1736_invmass","1736_run_mm2","run1736_mm2",LD2_10cm_target,18,11,20.61,10.5391);
    // Chain("update","T1737","1737_run_minv","run1737_invmass","1737_run_mm2","run1737_mm2",LD2_10cm_target,19,11,20.61,10.5391);
    // Chain("update","T1738","1738_run_minv","run1738_invmass","1738_run_mm2","run1738_mm2",LD2_10cm_target,20,11,20.61,10.5391);
    // Chain("update","T1739","1739_run_minv","run1739_invmass","1739_run_mm2","run1739_mm2",LD2_10cm_target,21,2,20.61,10.5391);
    // Chain("update","T1740","1740_run_minv","run1740_invmass","1740_run_mm2","run1740_mm2",LD2_10cm_target,22,2,20.61,10.5389);
    // Chain("update","T1741","1741_run_minv","run1741_invmass","1741_run_mm2","run1741_mm2",LD2_10cm_target,23,5,20.61,10.5389);
    // Chain("update","T1742","1742_run_minv","run1742_invmass","1742_run_mm2","run1742_mm2",LH2_10cm_target,24,3,20.61,10.5387);
    // Chain("update","T1744","1744_run_minv","run1744_invmass","1744_run_mm2","run1744_mm2",LH2_10cm_target,25,4,20.61,10.5389);
    // Chain("update","T1745","1745_run_minv","run1745_invmass","1745_run_mm2","run1745_mm2",LH2_10cm_target,26,1,20.61,10.5389);
    // Chain("update","T1746","1746_run_minv","run1746_invmass","1746_run_mm2","run1746_mm2",LH2_10cm_target,27,1,20.61,10.5391);
    // Chain("update","T1747","1747_run_minv","run1747_invmass","1747_run_mm2","run1747_mm2",LH2_10cm_target,28,1,20.61,10.539);
    // Chain("update","T1748","1748_run_minv","run1748_invmass","1748_run_mm2","run1748_mm2",LH2_10cm_target,29,1,20.61,10.54);
    // Chain("update","T1750","1750_run_minv","run1750_invmass","1750_run_mm2","run1750_mm2",LH2_10cm_target,30,1,20.61,10.5389);
    // Chain("update","T1752","1752_run_minv","run1752_invmass","1752_run_mm2","run1752_mm2",LH2_10cm_target,31,4,20.61,10.5391);
    // Chain("update","T1753","1753_run_minv","run1753_invmass","1753_run_mm2","run1753_mm2",LD2_10cm_target,32,6,18.77,10.5392);
    // Chain("update","T1754","1754_run_minv","run1754_invmass","1754_run_mm2","run1754_mm2",LH2_10cm_target,33,1,18.77,10.5392);        
}
*/

