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
// const double_t clusTmax = 160.;
const double_t clusTmax = 155.;
const double_t clusTmin = 150.;
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

void Pi0_mass_calculation(Double_t Targetname, int RunNo, int Sgemin, int Segmax, Double_t angle, Double_t beamEne, Double_t* result){
    TString FilePath_PS = "/volatile/hallc/nps/cmorean/REPORT_OUTPUT/COIN/SKIM/";
    TString Input_File_PS = FilePath_PS + Form("skim_NPS_HMS_report_%d_-1.report",RunNo);
    std::ifstream inputFile(Input_File_PS);
    if(!inputFile.is_open()){
        Input_File_PS = FilePath_PS + Form("skim_NPS_HMS_report_%d_0_1_-1.report",RunNo);
        inputFile.open(Input_File_PS);
    }
    if(!inputFile.is_open()){
        std::cout<<"Can't open the report file for run "<<RunNo<<std::endl;
        result[0] = -1.;
        return;
    } 
    else std::cout<<Input_File_PS<<" opened successfully!"<<std::endl;

    int Ps1_factor, Ps2_factor, Ps3_factor, Ps4_factor, Ps5_factor, Ps6_factor;
    Double_t NofCharge, Target_Type;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.find("Ps1_factor") != std::string::npos) {
            std::sscanf(line.c_str(), "Ps1_factor = %d", &Ps1_factor);
        } else if (line.find("Ps2_factor") != std::string::npos) {
            std::sscanf(line.c_str(), "Ps2_factor = %d", &Ps2_factor);
        } else if (line.find("Ps3_factor") != std::string::npos) {
            std::sscanf(line.c_str(), "Ps3_factor = %d", &Ps3_factor);
        } else if (line.find("Ps4_factor") != std::string::npos) {
            std::sscanf(line.c_str(), "Ps4_factor = %d", &Ps4_factor);
        } else if (line.find("Ps5_factor") != std::string::npos) {
            std::sscanf(line.c_str(), "Ps5_factor = %d", &Ps5_factor);
        } else if (line.find("Ps6_factor") != std::string::npos) {
            std::sscanf(line.c_str(), "Ps6_factor = %d", &Ps6_factor);
            break;
        }

        if (line.find("BCM4A Beam Cut Charge:") != std::string::npos) {
            std::sscanf(line.c_str(), "BCM4A Beam Cut Charge: %lf uC", &NofCharge);
        }

        if (line.find("Target AMU") != std::string::npos)
        {
            std::sscanf(line.c_str(), "Target AMU  : %lf", &Target_Type);
        }
    }
    int ps[6];
    Double_t Ps[6];
    ps[0] = Ps1_factor;
    ps[1] = Ps2_factor;
    ps[2] = Ps3_factor;
    ps[3] = Ps4_factor;
    ps[4] = Ps5_factor;
    ps[5] = Ps6_factor;

    for(int i=0;i<6;i++){
       if(ps[i]==-1) Ps[i] = -1.;
       else if(ps[i]==1) Ps[i] = 0.;
       else Ps[i] = log2((ps[i]-1)*1.)+1.;
    }

    // if(ps[5]==-1){
    //     result[0] = -1.;
    //     return;
    // }
    if (ps[5]!=-1 && ps[0]==-1 && ps[1]==-1 && ps[2]==-1 && ps[3]==-1 && ps[4]==-1){
        std::cout<<"Only ps6 was used for this run."<<std::endl;
    }
    else{
        result[0] = -1.;
        return;
    }

    if(Target_Type>1.&&Target_Type<3.) std::cout<<"Target type is LH2 or LD2."<<std::endl;
    else{
        result[0] = -1.;
        return;
    }
    

    inputFile.close();
    
    TChain	*ch1 = new TChain("T");
    // TString File_Path = "/lustre19/expphy/cache/hallc/c-nps/analysis/online/replays/";
    // for(int k=Sgemin;k<=Segmax;k++){
    //     TString FileName = File_Path + Form("nps_hms_coin_%d_%d_1_-1.root",RunNo,k);
    //     ch1->Add(FileName);
    //     std::cout<<"Processing "<<FileName<<"..."<<std::endl;
    // }
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
    Double_t clusX[40];
    Double_t clusY[40];
    Double_t clusZ[40];
    Double_t clusT[40];
    Double_t clusE[40];
    Double_t clusSize[40];

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
    Double_t T_hms_hEDTM_tdcTime, H_BCM4A_scalerCurrent, H_BCM4A_scalerRate, H_1MHz_scaler;

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

    ch1->GetEntry(0);

    Double_t NofPi0 = 0.;
    Double_t NofDVCS = 0.;

    TH1F* h_clust_E = new TH1F(Form("h_clust_E_%d",RunNo),Form("h_clust_E_%d",RunNo),100,0,10);

    Long64_t nentries = ch1->GetEntries();
    for(Long64_t evt=0; evt<nentries; evt++){
    // for(Long64_t evt= 0; evt < 1000; evt++){

        ch1->GetEntry(evt);

        if(abs(vtx_z)>4.) continue;

        if(vtx_ok < 1) continue;
        TVector3 v_vtx(vtx_x, vtx_y, vtx_z);

        if(gtr_dp < -10 || gtr_dp > 10) continue;

        if(etracknorm < 0.7 || etracknorm>1.3) continue;

        if(npesum < 2) continue;

        if(gtr_ok < 1) continue;

        TLorentzVector sele_vect;
        if(gtr_px > 1.e30) continue;

        if(nclust>0.5&&nclust<1.5&&clusSize[0]>MinClusSize&&clusT[0]>clusTmin&&clusT[0]<clusTmax){
            NofDVCS += 1.;
            h_clust_E->Fill(clusE[0]);
        }

        if(nclust<1.5) continue;

        sele_vect.SetXYZM(gtr_px,gtr_py,gtr_pz,electron_mass);

        // cout<<gtr_pz<<endl;

        for(int i=0; i<nclust;i++){
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

                TLorentzVector beam_vect;
                beam_vect.SetXYZM(0,0,beamEne,electron_mass);

                TLorentzVector target_vect;
                if(Target_Type>1.&&Target_Type<2.) target_vect.SetXYZM(0,0,0,LH2_10cm_target);
                if(Target_Type>2.&&Target_Type<3.) target_vect.SetXYZM(0,0,0,LD2_10cm_target);
                
                TLorentzVector X_vect;
                X_vect = (beam_vect + target_vect - sele_vect - Q1 - Q2);
                if (invmass < 0.1 || invmass > 0.13) continue;
                Double_t mm2 = X_vect.M2();
                NofPi0 += 1.;

                if( mm2<1.1 || mm2>1.8 ) continue;
                if(T_hms_hEDTM_tdcTime>1.) std::cout<<"!!!!!EDTM Event!!!!!!"<<std::endl;

            }
        }
    }
    result[0] = NofPi0*ps[5];
    result[1] = NofCharge/1000.; //mC
    result[2] = NofDVCS*ps[5];
    result[3] = Target_Type;
    // std::cout<<NofPi0<<"\t"<<NofCharge/1000.<<std::endl;
    // return NofPi0/(NofCharge/1000.);

    TCanvas* c_clust_E = new TCanvas(Form("c_clust_E_%d",RunNo),Form("c_clust_E_%d",RunNo),1200,800);
    h_clust_E->Draw();
    c_clust_E->SaveAs(Form("./pi0_charge/clust_E_%d.pdf",RunNo));
}

void pi0_charge_fast(){
    // "/lustre19/expphy/cache/hallc/c-nps/analysis/online/replays/"

    Double_t ratio_pi0, ratio_dvcs, fitParameter, chiSquare, ndf, gmax, gmin;
    Double_t result[4];
    TLatex latex;
    latex.SetTextSize(0.03);
    latex.SetTextAlign(12);

    // int runs_array_0[] = {1817,1818,1819,1820,1821,1822}; 

    Int_t RunBegin = 1817;
    Int_t RunEnd = 1823;
    std::vector<double> runs_array_D, R_pi0_D, R_pi0_err_D, R_dvcs_D, R_dvcs_err_D, x_err_D;
    std::vector<double> runs_array_H, R_pi0_H, R_pi0_err_H, R_dvcs_H, R_dvcs_err_H, x_err_H;
    for(int RunNo=RunBegin;RunNo<=RunEnd;RunNo++){
        Pi0_mass_calculation(1.,RunNo,0,0,0.,10.538,result);
        // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<result[2]<<"\t"<<result[3]<<std::endl;
        if(result[0]<1.) continue;
        ratio_pi0 = result[0]/result[1];
        ratio_dvcs = result[2]/result[1];
        if(result[3]>1.&&result[3]<2.){
            runs_array_H.push_back(RunNo);
            x_err_H.push_back(0.);
            R_pi0_H.push_back(ratio_pi0);
            R_pi0_err_H.push_back(ratio_pi0/sqrt(result[0]));
            R_dvcs_H.push_back(ratio_dvcs);
            R_dvcs_err_H.push_back(ratio_dvcs/sqrt(result[2]));
        }
        if(result[3]>2.&&result[3]<3.){
            runs_array_D.push_back(RunNo);
            x_err_D.push_back(0.);
            R_pi0_D.push_back(ratio_pi0);
            R_pi0_err_D.push_back(ratio_pi0/sqrt(result[0]));
            R_dvcs_D.push_back(ratio_dvcs);
            R_dvcs_err_D.push_back(ratio_dvcs/sqrt(result[2]));
        }
    }

    // Plot LD2 charge normalized event counts
    TGraphErrors* g_ratio_pi0_D = new TGraphErrors(runs_array_D.size(),&runs_array_D[0],&R_pi0_D[0],&x_err_D[0],&R_pi0_err_D[0]);
    g_ratio_pi0_D->SetTitle("Charge normalized #pi_{0} events(LD2);Run Number;counts/mC^{-1}");
    TGraphErrors* g_ratio_dvcs_D = new TGraphErrors(runs_array_D.size(),&runs_array_D[0],&R_dvcs_D[0],&x_err_D[0],&R_dvcs_err_D[0]);
    g_ratio_dvcs_D->SetTitle("Charge normalized DVCS events(LD2);Run Number;counts/mC^{-1}");

    TCanvas* c_ratio_pi0_D = new TCanvas("c_ratio_pi0_D","c_ratio_pi0_D",1200,800);
    g_ratio_pi0_D->SetMarkerStyle(29);
    g_ratio_pi0_D->GetXaxis()->SetNdivisions(505);
    g_ratio_pi0_D->Fit("pol0");
    fitParameter = g_ratio_pi0_D->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_pi0_D->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_pi0_D->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_pi0_D->GetYaxis()->GetXmax();
    gmin = g_ratio_pi0_D->GetYaxis()->GetXmin();
    g_ratio_pi0_D->Draw("AP");
    latex.DrawLatex(runs_array_D[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_D[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_pi0_D->SaveAs("./pi0_charge/ratio_pi0_D.pdf");

    TCanvas* c_ratio_dvcs_D = new TCanvas("c_ratio_dvcs_D","c_ratio_dvcs_D",1200,800);
    g_ratio_dvcs_D->SetMarkerStyle(29);
    g_ratio_dvcs_D->GetXaxis()->SetNdivisions(505);
    g_ratio_dvcs_D->Fit("pol0");
    fitParameter = g_ratio_dvcs_D->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_dvcs_D->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_dvcs_D->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_dvcs_D->GetYaxis()->GetXmax();
    gmin = g_ratio_dvcs_D->GetYaxis()->GetXmin();
    g_ratio_dvcs_D->Draw("AP");
    latex.DrawLatex(runs_array_D[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_D[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_dvcs_D->SaveAs("./pi0_charge/ratio_dvcs_D.pdf");

    /*
    // Plot LH2 charge normalized event counts
    TGraphErrors* g_ratio_pi0_H = new TGraphErrors(runs_array_H.size(),&runs_array_H[0],&R_pi0_H[0],&x_err_H[0],&R_pi0_err_H[0]);
    g_ratio_pi0_H->SetTitle("Charge normalized #pi_{0} events(LH2);Run Number;counts/mC^{-1}");
    TGraphErrors* g_ratio_dvcs_H = new TGraphErrors(runs_array_H.size(),&runs_array_H[0],&R_dvcs_H[0],&x_err_H[0],&R_dvcs_err_H[0]);
    g_ratio_dvcs_H->SetTitle("Charge normalized DVCS events(LH2);Run Number;counts/mC^{-1}");

    TCanvas* c_ratio_pi0_H = new TCanvas("c_ratio_pi0_H","c_ratio_pi0_H",1200,800);
    g_ratio_pi0_H->SetMarkerStyle(29);
    g_ratio_pi0_H->GetXaxis()->SetNdivisions(505);
    g_ratio_pi0_H->Fit("pol0");
    fitParameter = g_ratio_pi0_H->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_pi0_H->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_pi0_H->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_pi0_H->GetYaxis()->GetXmax();
    gmin = g_ratio_pi0_H->GetYaxis()->GetXmin();
    g_ratio_pi0_H->Draw("AP");
    latex.DrawLatex(runs_array_H[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_H[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_pi0_H->SaveAs("./pi0_charge/ratio_pi0_H.pdf");

    TCanvas* c_ratio_dvcs_H = new TCanvas("c_ratio_dvcs_H","c_ratio_dvcs_H",1200,800);
    g_ratio_dvcs_H->SetMarkerStyle(29);
    g_ratio_dvcs_H->GetXaxis()->SetNdivisions(505);
    g_ratio_dvcs_H->Fit("pol0");
    fitParameter = g_ratio_dvcs_H->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_dvcs_H->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_dvcs_H->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_dvcs_H->GetYaxis()->GetXmax();
    gmin = g_ratio_dvcs_H->GetYaxis()->GetXmin();
    g_ratio_dvcs_H->Draw("AP");
    latex.DrawLatex(runs_array_H[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_H[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_dvcs_H->SaveAs("./pi0_charge/ratio_dvcs_H.pdf");
    */



    // Pi0_mass_calculation(LH2_10cm_target,1849,0,0,18.72,10.538,result);
    // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<result[2]<<std::endl;
    // Pi0_mass_calculation(LH2_10cm_target,1849,0,0,0.,10.538,result);
    // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<result[2]<<"\t"<<result[3]<<std::endl;

    // Pi0_mass_calculation(LH2_10cm_target,1727,0,3,20.58,10.538,result);
    // Pi0_mass_calculation(LH2_10cm_target,1727,0,3,0.,10.538,result);
    // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<result[2]<<std::endl;
    // Pi0_mass_calculation(LH2_10cm_target,1727,1,1,20.58,10.538,result);
    // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<ratio_pi0<<std::endl;
    // Pi0_mass_calculation(LH2_10cm_target,1727,2,2,20.58,10.538,result);
    // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<ratio_pi0<<std::endl;
    // Pi0_mass_calculation(LH2_10cm_target,1727,3,3,20.58,10.538,result);
    // std::cout<<result[0]<<"\t"<<result[1]<<"\t"<<ratio_pi0<<std::endl;

    /*
    // KinC_x60_3 18.72 Clust pair thresh = 750MeV, clust read thresh = 400MeV
    // LD2 coin_sparse 20uA
    int runs_array_0[] = {1817,1818,1819,1820,1821,1822};
    int Segmax_0[] = {5,3,6,4,4,4};
    int Length_0 = sizeof(runs_array_0)/sizeof(runs_array_0[0]);

    // KinC_x60_3 18.72 Clust pair thresh = 750MeV, clust read thresh = 400MeV
    // LH2 coin_sparse 30 uA
    int runs_array_1[] = {1826,1827,1828,1829,1848,1849,1851};
    int Segmax_1[] = {1,1,1,1,1,0,1};
    int Length_1 = sizeof(runs_array_1)/sizeof(runs_array_1[0]);

    TGraphErrors* g_ratio_pi0_0 = new TGraphErrors();
    TGraphErrors* g_ratio_dvcs_0 = new TGraphErrors();
    g_ratio_pi0_0->SetTitle("Charge normalized #pi_{0} events(LD2 20uA);Run Number;counts/mC^{-1}");
    g_ratio_dvcs_0->SetTitle("Charge normalized DVCS events(LD2 20uA);Run Number;counts/mC^{-1}");
    for(int i=0;i<Length_0;i++){
        Pi0_mass_calculation(LD2_10cm_target,runs_array_0[i],0,Segmax_0[i],18.72,10.538,result);
        ratio_pi0 = result[0]/result[1];
        ratio_dvcs = result[2]/result[1];
        g_ratio_pi0_0->SetPoint(i,runs_array_0[i],ratio_pi0);
        g_ratio_pi0_0->SetPointError(i,0.,ratio_pi0/sqrt(result[0]));
        g_ratio_dvcs_0->SetPoint(i,runs_array_0[i],ratio_dvcs);
        g_ratio_dvcs_0->SetPointError(i,0.,ratio_dvcs/sqrt(result[2]));
    }

    TCanvas* c_ratio_pi0_0 = new TCanvas("c_ratio_pi0_0","c_ratio_pi0_0",1200,800);
    g_ratio_pi0_0->SetMarkerStyle(29);
    g_ratio_pi0_0->GetXaxis()->SetNdivisions(505);
    g_ratio_pi0_0->Fit("pol0");
    fitParameter = g_ratio_pi0_0->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_pi0_0->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_pi0_0->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_pi0_0->GetYaxis()->GetXmax();
    gmin = g_ratio_pi0_0->GetYaxis()->GetXmin();
    g_ratio_pi0_0->Draw("AP");
    latex.DrawLatex(runs_array_0[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_0[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_pi0_0->SaveAs("./pi0_charge/ratio_pi0_0.pdf");

    TCanvas* c_ratio_dvcs_0 = new TCanvas("c_ratio_dvcs_0","c_ratio_dvcs_0",1200,800);
    g_ratio_dvcs_0->SetMarkerStyle(29);
    g_ratio_dvcs_0->GetXaxis()->SetNdivisions(505);
    g_ratio_dvcs_0->Fit("pol0");
    fitParameter = g_ratio_dvcs_0->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_dvcs_0->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_dvcs_0->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_dvcs_0->GetYaxis()->GetXmax();
    gmin = g_ratio_dvcs_0->GetYaxis()->GetXmin();
    g_ratio_dvcs_0->Draw("AP");
    latex.DrawLatex(runs_array_0[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_0[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_dvcs_0->SaveAs("./pi0_charge/ratio_dvcs_0.pdf");






    TGraphErrors* g_ratio_pi0_1 = new TGraphErrors();
    TGraphErrors* g_ratio_dvcs_1 = new TGraphErrors();
    g_ratio_pi0_1->SetTitle("Charge normalized #pi_{0} events(LH2 30uA);Run Number;counts/mC^{-1}");
    g_ratio_dvcs_1->SetTitle("Charge normalized DVCS events(LH2 30uA);Run Number;counts/mC^{-1}");
    for(int i=0;i<Length_1;i++){
        Pi0_mass_calculation(LH2_10cm_target,runs_array_1[i],0,Segmax_1[i],18.72,10.538,result);
        ratio_pi0 = result[0]/result[1];
        ratio_dvcs = result[2]/result[1];
        g_ratio_pi0_1->SetPoint(i,runs_array_1[i],ratio_pi0);
        g_ratio_pi0_1->SetPointError(i,0.,ratio_pi0/sqrt(result[0]));
        g_ratio_dvcs_1->SetPoint(i,runs_array_1[i],ratio_dvcs);
        g_ratio_dvcs_1->SetPointError(i,0.,ratio_dvcs/sqrt(result[2]));
    }

    TCanvas* c_ratio_pi0_1 = new TCanvas("c_ratio_pi0_1","c_ratio_pi0_1",1200,800);
    g_ratio_pi0_1->SetMarkerStyle(29);
    g_ratio_pi0_1->GetXaxis()->SetNdivisions(505);
    g_ratio_pi0_1->Fit("pol0");
    fitParameter = g_ratio_pi0_1->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_pi0_1->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_pi0_1->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_pi0_1->GetYaxis()->GetXmax();
    gmin = g_ratio_pi0_1->GetYaxis()->GetXmin();
    g_ratio_pi0_1->Draw("AP");
    latex.DrawLatex(runs_array_1[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_1[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_pi0_1->SaveAs("./pi0_charge/ratio_pi0_1.pdf");

    TCanvas* c_ratio_dvcs_1 = new TCanvas("c_ratio_dvcs_1","c_ratio_dvcs_1",1200,800);
    g_ratio_dvcs_1->SetMarkerStyle(29);
    g_ratio_dvcs_1->GetXaxis()->SetNdivisions(505);
    g_ratio_dvcs_1->Fit("pol0");
    fitParameter = g_ratio_dvcs_1->GetFunction("pol0")->GetParameter(0);
    chiSquare = g_ratio_dvcs_1->GetFunction("pol0")->GetChisquare();
    ndf = g_ratio_dvcs_1->GetFunction("pol0")->GetNDF();
    gmax = g_ratio_dvcs_1->GetYaxis()->GetXmax();
    gmin = g_ratio_dvcs_1->GetYaxis()->GetXmin();
    g_ratio_dvcs_1->Draw("AP");
    latex.DrawLatex(runs_array_1[0], gmin+(gmax-gmin)*0.15, Form("Fit result: y = %.3f",fitParameter));
    latex.DrawLatex(runs_array_1[0], gmin+(gmax-gmin)*0.10, Form("#chi^{2} / NDf = %.3f / %.0f", chiSquare, ndf));
    c_ratio_dvcs_1->SaveAs("./pi0_charge/ratio_dvcs_1.pdf");
    */

    std::cout<<"Process done!"<<std::endl;

}
