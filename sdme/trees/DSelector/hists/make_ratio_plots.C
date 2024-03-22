void make_ratio_plots() {
    TFile *inf1, *inf2, *opf;

    vector<string> runs = {"sp17", "sp18", "fa18", "gluex1"};

    opf = TFile::Open("ratio.root", "recreate");
    for(auto run : runs) {
        inf1 = TFile::Open( ("hist_dat_"+run+".root").c_str() );
        inf2 = TFile::Open( ("hist_acc_"+run+".root").c_str() );

        TH1F *hist1 = (TH1F*)inf1->Get("im_kskl");
        TH1F *hist2 = (TH1F*)inf2->Get("im_kskl");

        hist2->Scale(hist1->Integral() / hist2->Integral());
        hist1->Divide(hist2);

        opf->cd();
        hist1->Write(run.c_str());

        inf1->Close();
        inf2->Close();

        // TCanvas *c = new TCanvas();
        // hist1->Draw("COLZ");
        // gStyle->SetOptStat(0);

        // hist1->GetXaxis()->SetRangeUser(1.00, 1.05);
        // c->SaveAs( ("ratio_"+run+".pdf").c_str() );
    }
}