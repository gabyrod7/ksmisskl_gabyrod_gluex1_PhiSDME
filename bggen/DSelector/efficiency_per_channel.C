
void efficiency_per_channel() {
    TFile *inf = TFile::Open("hist_bggen.root");

    TH1F *h1 = (TH1F*)inf->Get("im_kskl");
    TH1F *h2 = (TH1F*)inf->Get("im_kskl_sig");
    TH1F *h3 = (TH1F*)inf->Get("im_kskl_bkg");

    h2->Add(h3, -1);

    h1->Draw();
    h2->Draw("SAME HIST");

    TH1F *h4 = (TH1F*)inf->Get("hHistSelectThrownTopologies_noCuts");
    TH1F *h5 = (TH1F*)inf->Get("hHistSelectThrownTopologies_nominalCuts");
    h4->GetXaxis()->LabelsOption("a");
    h5->GetXaxis()->LabelsOption("a");

    h5->Divide(h4);
    h5->GetXaxis()->LabelsOption(">");
    h5->GetYaxis()->SetTitle("Fraction of surviving events after cuts");
    h5->Draw("hist text");
}
