void calc_recon_eff() {
    TFile *inf1 = TFile::Open("hist_acc.root");
    TH1F *hist1 = (TH1F*)inf1->Get("h1_chisqNdf");

    TFile *inf2 = TFile::Open("hist_gen.root");
    TH1F *hist2 = (TH1F*)inf2->Get("im_kskl");

    double uBin = hist1->FindBin(4.0)-1;
    double recon_integral = hist1->Integral(0, uBin);
    double thrown_integral = hist2->Integral();

    cout << "Reconstruction efficiency (%): " << recon_integral/thrown_integral*100 << endl;

    // int bin0 = hist->FindBin(0.0);
    // int bin2 = hist->FindBin(4.0)-1;



//     cout << bin0 << endl;
//     cout << bin2 << endl;


//     cout << Form("Integral1 = %.0f", hist->Integral(bin0, bin2)) << endl;
//     cout << Form("Integral2 = %.0f", hist->Integral(bin2, hist->GetNbinsX())) << endl;
}