    TCanvas *c_std = new TCanvas("c_std","c_std",1200,1600);
    c_std->Divide(1,2);
    c_std->cd(1);
    c[0]->DrawClonePad();
    c_std->cd(2);
    c[2]->DrawClonePad();
    c_std->Update();
    c_std->SstdAs("./plots_hclog/temp_std_2D.pdf");