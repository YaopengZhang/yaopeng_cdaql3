#include <TGraph.h>
#include <TCanvas.h>

TGraph* ReadDataAndCreateGraph(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return nullptr;
    }

    std::vector<double> xData, yData;
    double x;
    int pointCounter = 0;

    while (file >> x) {
        xData.push_back(pointCounter);
        yData.push_back(x);
        pointCounter++;
    }

    TGraph* graph = new TGraph(xData.size(), &xData[0], &yData[0]);
    graph->SetTitle("DC Current Pedestals for channel 0");
    graph->GetXaxis()->SetTitle("Index / 10 s");
    graph->GetYaxis()->SetTitle("I / mA");

    return graph;
}

void PlotGraphFromTxtFile() {
    const char* filename = "Pedestals_channel_0.txt";
    TGraph* graph = ReadDataAndCreateGraph(filename);

    if (graph) {
        TCanvas* canvas = new TCanvas("canvas", "Graph for DC current Pedestals", 1200, 800);
        graph->GetYaxis()->SetTitleOffset(1.3);
        graph->Draw("APL");
        canvas->Update();
        canvas->SaveAs("Pedestals_channel_0.pdf");
    }
}

void Plot_Pedestals() {
    PlotGraphFromTxtFile();
}