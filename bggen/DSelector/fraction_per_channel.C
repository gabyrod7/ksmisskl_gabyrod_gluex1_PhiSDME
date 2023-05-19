
void fraction_per_channel() {
    TFile *inf = TFile::Open("hist_bggen.root");

    TH1F *h = (TH1F*)inf->Get("hHistSelectThrownTopologies_nominalCuts");

    h->Scale(1.0/h->Integral());

    h->GetXaxis()->LabelsOption(">");
    h->GetYaxis()->SetTitle("Fraction of surviving events");
    h->Draw("hist text");
}
