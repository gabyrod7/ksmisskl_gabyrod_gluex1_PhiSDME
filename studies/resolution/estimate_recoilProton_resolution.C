void estimate_recoilProton_resolution() {
    TFile *inf = TFile::Open("hist.root");
    TH1F *hist = (TH1F*)inf->Get("res_recoilp_vertex");

    TF1 *fit1 = new TF1("fit1", "gausn", -2, 2);

    TF1 *fit2 = new TF1("fit2", "gausn(0) + gausn(3)", -2, 2);
    fit2->SetParameters(5e4, -0.01, 0.2, 4e4, 0.01, 0.2);

    TCanvas *c;
    TLatex t;
    
    c = new TCanvas();
    hist->Fit(fit1, "RE");
    hist->SetTitle("Fit model: Normalized Gaussian");
    t.DrawLatex(1, 0.8*hist->GetMaximum(), Form("N = %.0f", fit1->GetParameter(0)));
    t.DrawLatex(1, 0.7*hist->GetMaximum(), Form("#mu = %.3f", fit1->GetParameter(1)));
    t.DrawLatex(1, 0.6*hist->GetMaximum(), Form("#sigma = %.3f", fit1->GetParameter(2)));
    c->SaveAs("recoilProton_fit1.pdf");

    c = new TCanvas();
    hist->Fit(fit2, "RE");
    hist->SetTitle("Fit model: Normalized Gaussian");
    t.DrawLatex(1, 0.8*hist->GetMaximum(), Form("N = %.0f", fit2->GetParameter(0)));
    t.DrawLatex(1, 0.7*hist->GetMaximum(), Form("#mu = %.3f", fit2->GetParameter(1)));
    t.DrawLatex(1, 0.6*hist->GetMaximum(), Form("#sigma = %.3f", fit2->GetParameter(2)));
    t.DrawLatex(1, 0.5*hist->GetMaximum(), Form("N = %.0f", fit2->GetParameter(3)));
    t.DrawLatex(1, 0.4*hist->GetMaximum(), Form("#mu = %.3f", fit2->GetParameter(4)));
    t.DrawLatex(1, 0.3*hist->GetMaximum(), Form("#sigma = %.3f", fit2->GetParameter(5)));
    double weighted_sigma = (fit2->GetParameter(0)*fit2->GetParameter(2) + fit2->GetParameter(3)*fit2->GetParameter(5)) / (fit2->GetParameter(0) + fit2->GetParameter(3));
    t.DrawLatex(1, 0.2*hist->GetMaximum(), Form("#bar{#sigma} = %.3f", weighted_sigma));
    c->SaveAs("recoilProton_fit2.pdf");
}