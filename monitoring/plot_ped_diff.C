#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// source /u/apps/root/6.08.00/setroot_CUE.csh
// root -l -b -q 'plot_ped_diff.C("Nov",20)'

void plot_ped_diff(TString month, Int_t date){
    std::ifstream inputFile("Pedestals_LV_ON.txt");
    std::vector<double> pedestals_now, pedestals_before;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        double number;
        while (iss >> number) {
            pedestals_now.push_back(number);
        }
    }
    inputFile.close();
    // cout<<pedestals_now[5]<<endl;
    std::ifstream inputFile_before(Form("Pedestals_LV_ON_%s%02d.txt",month.Data(),date));
    while (std::getline(inputFile_before, line)) {
        std::istringstream iss(line);
        double number;
        while (iss >> number) {
            pedestals_before.push_back(number);
        }
    }
    inputFile_before.close();
    // cout<<pedestals_before[5]<<endl;

    TH2F* h2 = new TH2F("h2",Form("Pedestal change in #muA (Now - %s%2d)",month.Data(),date),30,0,30,36,0,36);
    for(int i=0;i<30;i++){
        for(int j=0;j<36;j++){
            int Num = i + j*30;
            h2->SetBinContent(30-i,j+1,(pedestals_now[Num]-pedestals_before[Num])/12.*1000.);
            TString labelx = Form("%2d",30-i-1);
            TString labely = Form("%2d",j);;
            h2->GetXaxis()->SetBinLabel(i+1, labelx.Data());
            h2->GetYaxis()->SetBinLabel(j+1, labely.Data());
        }
    }
    TCanvas* c1 = new TCanvas("c1","c1",2000,1000);
    gStyle->SetPaintTextFormat(".1f");
    gStyle->SetGridStyle(0);
    gPad->SetGrid();
    gPad->SetGridx();
    gPad->SetGridy();
    gPad->SetRightMargin(0.15);
    h2->SetStats(0);
    h2->Draw("COLZ TEXT");

    c1->Update();
    c1->Modified();
    c1->SaveAs(Form("./Pedestal_diff/%s%2d.pdf",month.Data(),date));


}