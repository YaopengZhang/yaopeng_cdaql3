#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLegend.h>
#include <TH2F.h>
#include <TText.h>
#include <TF1.h>

using namespace std;

void readCSV(const std::string& fileName, int* Date, std::vector<double>& time, std::vector<double>& value){

    ifstream file;
    file.open(fileName);

    time.clear();
    value.clear();

    Int_t First_Flag = 1;
    int year_first, month_first, date_first;
    double hour_offset;
    string s;
    double val;
    getline(file,s);

    while(getline(file,s)){
        istringstream iss(s);
        string part1, part2, part3;
        iss >> part1;
        iss >> part2;
        iss >> part3;
        val = stod(part3);
        // cout<<part1<<"\t"<<part2<<"\t"<<part3<<endl;
        // cout<<part1<<"\t"<<part2<<"\t"<<val<<endl;

        double year, month, date, hour, min, sec;
        string token;
        stringstream ss(part1);
        vector<std::string> tokens;
        while(getline(ss, token, '-')) {
            tokens.push_back(token);
        }
        year = stod(tokens[0]);
        month = stod(tokens[1]);
        date = stod(tokens[2]);
        // cout<<tokens[0]<<"\t"<<tokens[1]<<"\t"<<tokens[2]<<endl;
        // cout<<tokens[0]<<"\t"<<tokens[1]<<"\t"<<date<<endl;

        stringstream ss_1(part2);
        vector<std::string> tokens_1;
        while(getline(ss_1, token, ':')) {
            tokens_1.push_back(token);
        }
        hour = stod(tokens_1[0]);
        min = stod(tokens_1[1]);
        sec = stod(tokens_1[2]);
        // cout<<hour<<"\t"<<min<<"\t"<<sec<<endl;

        if(First_Flag==1){
            year_first = int(year);
            month_first = int(month);
            date_first = int(date);
            hour_offset = hour;
            First_Flag = 0;
        }

        if(date>date_first) hour_offset = 0.;
        double timeValue;
        timeValue=(date-date_first)*24+(hour-hour_offset)+min/60.+sec/60./60.;

        time.push_back(timeValue);
        value.push_back(val);
    }
    Date[0] = year_first;
    Date[1] = month_first;
    Date[2] = date_first;

    file.close();
}

void Analyze(){
    vector<double> time, value;
    int Date[3];
    // readCSV(Form("./data/chart-%d.txt",1),Date,time,value);
    // for(int k=0;k<value.size();k++){
    //     cout<<time[k]<<"\t"<<value[k]<<endl;
    // }
    // cout<<Date[0]<<"\t"<<Date[1]<<"\t"<<Date[2]<<endl;

    // /*
    int Calibration_Flag = 0;
    double xMin, xMax, yMin, yMax;

    TCanvas* c[4];
    TH2F* h2[4];
    
    TCanvas* c_g_1D[112];
    TCanvas* c_g[12];
    TGraph* g[112];
    TGraph* g_1D[112];
    TText* text_ave[112];
    TText* text_std[112];
    double T_ave[112], T_std[112];

    TCanvas* c_multi_g[2];
    double YMin[2], YMax[2];

    double temp_average = 0.;
    double temp_STD = 0.;
    double ave_max, ave_min, std_max, std_min;
    ave_max = 0.;
    ave_min = 1000.;
    std_max = 0.;
    std_min = 1000.;

    double temp_calibration = 0.;
    double temp_cali_factor = 21.4122; // fit 8 corner 1D plots for data_6, x range(15,28)

    // 2D TGraphs
    // back
    YMin[0] = 1000.;
    YMax[0] = 0.;
    for(int j=1;j<=56;j++){
        readCSV(Form("/home/cdaq/yaopeng/Temperature_plots/data/chart-%d.txt",j), Date, time, value);
        // if(j==21){
            vector<double> time_new, value_new;
            double p0, p;
            for(int k=1;k<value.size();k++){
                p0 = value[k-1];
                p = value[k];
                if(fabs(p-p0)<1.&&p<35){
                    time_new.push_back(time[k]);
                    value_new.push_back(value[k]);
                }
            }
            time = time_new;
            value = value_new;
        // }
        for(int k=0;k<value.size();k++){
            value[k] = temp_cali_factor+20.-value[k];
        }
        g[j-1] = new TGraph(time.size(), &time[0], &value[0]);
        g_1D[j-1] = new TGraph(time.size(), &time[0], &value[0]);
        for(int k=1;k<value.size();k++){
            if(value[k]<YMin[0]) YMin[0] = value[k];
            if(value[k]>YMax[0]) YMax[0] = value[k];
        }
        temp_average = 0.;
        temp_STD = 0.;
        for(int k=0;k<value.size();k++){
            temp_average += value[k];
        }
        temp_average = temp_average/(value.size()*1.);
        for(int k=0;k<value.size();k++){
            temp_STD += pow(value[k]-temp_average,2);
        }
        temp_STD = sqrt(temp_STD/value.size());

        if(temp_average>ave_max) ave_max = temp_average;
        if(temp_average<ave_min) ave_min = temp_average;

        if(temp_STD>std_max) std_max = temp_STD;
        if(temp_STD<std_min) std_min = temp_STD;

        T_ave[j-1] = temp_average;
        T_std[j-1] = temp_STD;
    }

    // front
    YMin[1] = 1000.;
    YMax[1] = 0.;
    for(int j=1;j<=56;j++){
        readCSV(Form("/home/cdaq/yaopeng/Temperature_plots/data/chart-%d.txt",j+56), Date, time, value);
        // if(j==21){
            vector<double> time_new, value_new;
            double p0, p;
            for(int k=1;k<value.size();k++){
                p0 = value[k-1];
                p = value[k];
                if(fabs(p-p0)<1.&&p<35){
                    time_new.push_back(time[k]);
                    value_new.push_back(value[k]);
                }
            }
            time = time_new;
            value = value_new;
        // }
        for(int k=0;k<value.size();k++){
            value[k] = temp_cali_factor+20.-value[k];
        }
        g[j+56-1] = new TGraph(time.size(), &time[0], &value[0]);
        g_1D[j+56-1] = new TGraph(time.size(), &time[0], &value[0]);
        for(int k=1;k<value.size();k++){
            if(value[k]<YMin[1]) YMin[1] = value[k];
            if(value[k]>YMax[1]) YMax[1] = value[k];
        }
        temp_average = 0.;
        temp_STD = 0.;
        for(int k=0;k<value.size();k++){
            temp_average += value[k];
        }
        temp_average = temp_average/(value.size()*1.);
        for(int k=0;k<value.size();k++){
            temp_STD += pow(value[k]-temp_average,2);
        }
        temp_STD = sqrt(temp_STD/value.size());

        if(temp_average>ave_max) ave_max = temp_average;
        if(temp_average<ave_min) ave_min = temp_average;

        if(temp_STD>std_max) std_max = temp_STD;
        if(temp_STD<std_min) std_min = temp_STD;

        T_ave[j+56-1] = temp_average;
        T_std[j+56-1] = temp_STD;
    }

    c[0] = new TCanvas("c_ave_back","c_ave_back",1200,800);
    h2[0] = new TH2F("h2_ave_back",Form("NPS Sensor Temperature Average -- Back (%d-%d-%d)",Date[0],Date[1],Date[2]),7,0,7,8,0,8);
    for(int m=0;m<7;m++){
        for(int n=0;n<8;n++){
            int FillNo = n+m*8;
            if(FillNo==24) FillNo = 28;
            else if(FillNo==25) FillNo = 24;
            else if(FillNo==26) FillNo = 29;
            else if(FillNo==27) FillNo = 25;
            else if(FillNo==28) FillNo = 30;
            else if(FillNo==29) FillNo = 26;
            else if(FillNo==30) FillNo = 31;
            else if(FillNo==31) FillNo = 27;
            h2[0]->Fill(m,n,T_ave[FillNo]);
        }
    }
    h2[0]->SetMaximum(ave_max);
    h2[0]->SetMinimum(ave_min);
    h2[0]->SetContour(99);
    h2[0]->Draw("COLZTEXT");
    h2[0]->SetStats(0);
    c[0]->Update();
    c[0]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_2D/temp_back_ave_2D.pdf");
    // c[0]->SaveAs("./plots_hclog/temp_back_ave_2D.pdf");

    c[1] = new TCanvas("c_std_back","c_std_back",1200,800);
    h2[1] = new TH2F("h2_std_back",Form("NPS Sensor Temperature STD -- Back (%d-%d-%d)",Date[0],Date[1],Date[2]),7,0,7,8,0,8);
    for(int m=0;m<7;m++){
        for(int n=0;n<8;n++){
            int FillNo = n+m*8;
            if(FillNo==24) FillNo = 28;
            else if(FillNo==25) FillNo = 24;
            else if(FillNo==26) FillNo = 29;
            else if(FillNo==27) FillNo = 25;
            else if(FillNo==28) FillNo = 30;
            else if(FillNo==29) FillNo = 26;
            else if(FillNo==30) FillNo = 31;
            else if(FillNo==31) FillNo = 27;
            h2[1]->Fill(m,n,T_std[FillNo]);
        }
    }
    h2[1]->SetMaximum(std_max);
    h2[1]->SetMinimum(std_min);
    h2[1]->SetContour(99);
    h2[1]->Draw("COLZTEXT");
    h2[1]->SetStats(0);
    c[1]->Update();
    c[1]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_2D/temp_back_std_2D.pdf");
    // c[1]->SaveAs("./plots_hclog/temp_back_std_2D.pdf");

    c[2] = new TCanvas("c_ave_front","c_ave_front",1200,800);
    h2[2] = new TH2F("h2_ave_front",Form("NPS Sensor Temperature Average -- Front (%d-%d-%d)",Date[0],Date[1],Date[2]),7,0,7,8,0,8);
    for(int m=0;m<7;m++){
        for(int n=0;n<8;n++){
            int FillNo = n+m*8;
            h2[2]->Fill(m,n,T_ave[FillNo+56]);
        }
    }
    h2[2]->SetMaximum(ave_max);
    h2[2]->SetMinimum(ave_min);
    h2[2]->SetContour(99);
    h2[2]->Draw("COLZTEXT");
    h2[2]->SetStats(0);
    c[2]->Update();
    c[2]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_2D/temp_front_ave_2D.pdf");
    // c[2]->SaveAs("./plots_hclog/temp_front_ave_2D.pdf");

    c[3] = new TCanvas("c_std_front","c_std_front",1200,800);
    h2[3] = new TH2F("h2_std_front",Form("NPS Sensor Temperature STD -- Front (%d-%d-%d)",Date[0],Date[1],Date[2]),7,0,7,8,0,8);
    for(int m=0;m<7;m++){
        for(int n=0;n<8;n++){
            int FillNo = n+m*8;
            h2[3]->Fill(m,n,T_std[FillNo+56]);
        }
    }
    h2[3]->SetMaximum(std_max);
    h2[3]->SetMinimum(std_min);
    h2[3]->SetContour(99);
    h2[3]->Draw("COLZTEXT");
    h2[3]->SetStats(0);
    c[3]->Update();
    c[3]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_2D/temp_front_std_2D.pdf");
    // c[3]->SaveAs("./plots_hclog/temp_front_std_2D.pdf");

    TCanvas *c_ave = new TCanvas("c_ave","c_ave",1200,1600);
    c_ave->Divide(1,2);
    c_ave->cd(1);
    c[0]->DrawClonePad();
    c_ave->cd(2);
    c[2]->DrawClonePad();
    c_ave->Update();
    c_ave->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_average_2D.pdf");

    TCanvas *c_std = new TCanvas("c_std","c_std",1200,1600);
    c_std->Divide(1,2);
    c_std->cd(1);
    c[1]->DrawClonePad();
    c_std->cd(2);
    c[3]->DrawClonePad();
    c_std->Update();
    c_std->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_std_2D.pdf");

    // 1D plots array
    c_multi_g[0] = new TCanvas("c_multi_g_0","c_multi_g_0",3200,4000);
    c_multi_g[0]->Divide(7,8);
    for(int m=0;m<7;m++){
        for(int n=0;n<8;n++){
            c_multi_g[0]->cd((7-n)*7+m+1);
            int FillNo = n+m*8;
            if(FillNo==24) FillNo = 28;
            else if(FillNo==25) FillNo = 24;
            else if(FillNo==26) FillNo = 29;
            else if(FillNo==27) FillNo = 25;
            else if(FillNo==28) FillNo = 30;
            else if(FillNo==29) FillNo = 26;
            else if(FillNo==30) FillNo = 31;
            else if(FillNo==31) FillNo = 27;
            g[FillNo]->GetHistogram()->SetMaximum(YMax[0]);
            g[FillNo]->GetHistogram()->SetMinimum(YMin[0]);
            g[FillNo]->SetTitle(Form("NPS Sensor %d Back Temperature(%d-%d-%d);Time / hour;Temperature / degree",FillNo+1,Date[0],Date[1],Date[2]));
            if(Calibration_Flag==1){
                TF1 *fitFunc = new TF1("fitFunc", "pol1");
                g[FillNo]->Fit(fitFunc,"","",15,28);
                double slope = fitFunc->GetParameter(1);
                double intercept = fitFunc->GetParameter(0);
                // cout<<i<<"\t"<<m<<"\t"<<n<<"\t"<<intercept<<"\t"<<slope<<endl;
                temp_calibration+=intercept;
            }
            g[FillNo]->Draw();
        }
    }
    c_multi_g[0]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_1D/2D/temp_back_1D_array.pdf");
    c_multi_g[0]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_back_1D_array.pdf");
    // c_multi_g[0]->SaveAs("./plots_1D/2D/temp_back.png");

    c_multi_g[1] = new TCanvas("c_multi_g_1","c_multi_g_1",3200,4000);
    c_multi_g[1]->Divide(7,8);
    for(int m=0;m<7;m++){
        for(int n=0;n<8;n++){
            c_multi_g[1]->cd((7-n)*7+m+1);
            int FillNo = n+m*8;
            g[FillNo+56]->GetHistogram()->SetMaximum(YMax[1]);
            g[FillNo+56]->GetHistogram()->SetMinimum(YMin[1]);
            g[FillNo+56]->SetTitle(Form("NPS Sensor %d Front Temperature(%d-%d-%d);Time / hour;Temperature / degree",FillNo+1,Date[0],Date[1],Date[2]));
            if(Calibration_Flag==1){
                TF1 *fitFunc = new TF1("fitFunc", "pol1");
                g[FillNo+56]->Fit(fitFunc,"","",15,28);
                double slope = fitFunc->GetParameter(1);
                double intercept = fitFunc->GetParameter(0);
                // cout<<i<<"\t"<<m<<"\t"<<n<<"\t"<<intercept<<"\t"<<slope<<endl;
                temp_calibration+=intercept;
            }
            g[FillNo+56]->Draw();
        }
    }
    c_multi_g[1]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_1D/2D/temp_front_1D_array.pdf");
    c_multi_g[1]->SaveAs("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_front_1D_array.pdf");
    // c_multi_g[1]->SaveAs("./plots_1D/2D/temp_front.png");
    // */

    // 1D TGraphs
    for(int i=0;i<56;i++){
        c_g_1D[i] = new TCanvas(Form("c_g_1D_%d",i),Form("c_g_1D_%d",i),1200,600);
        c_g_1D[i]->SetGrid(1);
        g_1D[i]->SetTitle(Form("NPS Sensor %d Back Temperature(%d-%d-%d);Time / hour;Temperature / degree",i+1,Date[0],Date[1],Date[2]));
        g_1D[i]->Draw();
        xMin = g_1D[i]->GetHistogram()->GetXaxis()->GetXmin();
        xMax = g_1D[i]->GetHistogram()->GetXaxis()->GetXmax();
        yMin = g_1D[i]->GetHistogram()->GetYaxis()->GetXmin();
        yMax = g_1D[i]->GetHistogram()->GetYaxis()->GetXmax();
        text_ave[i] = new TText(xMin+(xMax-xMin)*0.7, yMin+(yMax-yMin)*0.2,Form("Average = %6.4f",T_ave[i]));
        text_ave[i]->SetTextSize(0.04);
        text_ave[i]->Draw();
        text_std[i] = new TText(xMin+(xMax-xMin)*0.7, yMin+(yMax-yMin)*0.1,Form("STD = %6.4f",T_std[i]));
        text_std[i]->SetTextSize(0.04);
        text_std[i]->Draw();
        c_g_1D[i]->SaveAs(Form("/home/cdaq/yaopeng/Temperature_plots/plots_1D/1D/temp_1D_back_%d.png",i+1));

        c_g_1D[i+56] = new TCanvas(Form("c_g_1D_%d",i+56),Form("c_g_1D_%d",i+56),1200,600);
        c_g_1D[i+56]->SetGrid(1);
        g_1D[i+56]->SetTitle(Form("NPS Sensor %d Front Temperature(%d-%d-%d);Time / hour;Temperature / degree",i+1,Date[0],Date[1],Date[2]));
        g_1D[i+56]->Draw();
        xMin = g_1D[i+56]->GetHistogram()->GetXaxis()->GetXmin();
        xMax = g_1D[i+56]->GetHistogram()->GetXaxis()->GetXmax();
        yMin = g_1D[i+56]->GetHistogram()->GetYaxis()->GetXmin();
        yMax = g_1D[i+56]->GetHistogram()->GetYaxis()->GetXmax();
        text_ave[i+56] = new TText(xMin+(xMax-xMin)*0.7, yMin+(yMax-yMin)*0.2,Form("Average = %6.4f",T_ave[i+56]));
        text_ave[i+56]->SetTextSize(0.04);
        text_ave[i+56]->Draw();
        text_std[i+56] = new TText(xMin+(xMax-xMin)*0.7, yMin+(yMax-yMin)*0.1,Form("STD = %6.4f",T_std[i+56]));
        text_std[i+56]->SetTextSize(0.04);
        text_std[i+56]->Draw();
        c_g_1D[i+56]->SaveAs(Form("/home/cdaq/yaopeng/Temperature_plots/plots_1D/1D/temp_1D_front_%d.png",i+1));
    }

    for(int k=0;k<6;k++){
        c_g[k] = new TCanvas(Form("c_g_%d",k),Form("c_g_%d",k),3200,4000);
        c_g[k]->Divide(2,5);
        for(int i=0;i<10;i++){
            if(k==5 && i>5) continue;
            c_g[k]->cd(i+1);
            g_1D[i+10*k]->Draw();
            text_ave[i+10*k]->Draw();
            text_std[i+10*k]->Draw();
        }
        // c_g[k]->SaveAs(Form("./plots_1D/temp_back_%d.pdf",k+1));
    }
    c_g[0]->Print("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_back_1D.pdf(");
    for(int i=1;i<5;i++){
        c_g[i]->Print("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_back_1D.pdf");
    }
    c_g[5]->Print("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_back_1D.pdf)");

    for(int k=0;k<6;k++){
        c_g[k+6] = new TCanvas(Form("c_g_%d",k+6),Form("c_g_%d",k+6),3200,4000);
        c_g[k+6]->Divide(2,5);
        for(int i=0;i<10;i++){
            if(k==5 && i>5) continue;
            c_g[k+6]->cd(i+1);
            g_1D[i+10*k+56]->Draw();
            text_ave[i+10*k+56]->Draw();
            text_std[i+10*k+56]->Draw();
        }
        // c_g[k+6]->SaveAs(Form("./plots_1D/temp_front_%d.pdf",k+1));
    }
    c_g[6]->Print("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_front_1D.pdf(");
    for(int i=1;i<5;i++){
        c_g[i+6]->Print("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_front_1D.pdf");
    }
    c_g[11]->Print("/home/cdaq/yaopeng/Temperature_plots/plots_hclog/temp_front_1D.pdf)");

}