#include "TCanvas.h"
#include <TLatex.h>
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TMath.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void plot(){
    Double_t ratio_pi0, ratio_dvcs, fitParameter, chiSquare, ndf, gmax, gmin;
    TLatex latex;
    latex.SetTextSize(0.03);
    latex.SetTextAlign(12);
    std::vector<double> runs_array_D, R_pi0_D, R_pi0_err_D, R_dvcs_D, R_dvcs_err_D, x_err_D;
    std::vector<double> runs_array_H, R_pi0_H, R_pi0_err_H, R_dvcs_H, R_dvcs_err_H, x_err_H;

    // Kin_x50_2 LD2_15uA LH2_30uA
    // Int_t RunBegin = 1572;
    // Int_t RunEnd = 1752;

    // Kin_x60_3 LD2_20uA LH2_30uA ----------
    // Int_t RunBegin = 1703; // 1800
    // Int_t RunEnd = 2019;
    // Int_t Min = 1800;
    // Int_t Max = 2000;

    // Kin_x36_3 LD2_15uA LH2_15uA
    // Int_t RunBegin = 2020;
    // Int_t RunEnd = 2183;
    
    // Kin_x36_5 LD2_15uA LH2_25uA ----------
    Int_t RunBegin = 2188;
    Int_t RunEnd = 2324;
    // Int_t Min = 1800;
    // Int_t Max = 2000;
    
    // Kin_x50_4 LD2_15uA LH2_35uA
    // Int_t RunBegin = 2325;
    // Int_t RunEnd = 2450;
    

    Int_t Min = 1;
    Int_t Max = 10000;
    std::ifstream inputFile(Form("./pi0_charge/%d_%d.txt",RunBegin,RunEnd));
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int RunNo;
        Double_t result[4];
        if (iss >> RunNo >> result[0] >> result[1] >> result[2] >> result[3]) {
            if(result[0]<100.||result[2]<100.) continue;
            if ( RunNo<Min || RunNo>Max ) continue;
            // std::cout<<RunNo<<"\t"<<result[0]<<"\t"<<result[1]<<"\t"<<result[2]<<"\t"<<result[3]<<std::endl;
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
    c_ratio_pi0_D->SaveAs("./plots/ratio_pi0_D.pdf");

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
    c_ratio_dvcs_D->SaveAs("./plots/ratio_dvcs_D.pdf");

    // /*
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
    c_ratio_pi0_H->SaveAs("./plots/ratio_pi0_H.pdf");

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
    c_ratio_dvcs_H->SaveAs("./plots/ratio_dvcs_H.pdf");
    // */
}

