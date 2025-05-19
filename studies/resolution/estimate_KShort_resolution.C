Double_t AsymmetricGaussian(Double_t *x, Double_t *par);
Double_t CrystalBall(Double_t *x, Double_t *par);

void estimate_KShort_resolution() {
    TFile *inf = TFile::Open("hist.root");
    TH1F *hist = (TH1F*)inf->Get("res_kshort_vertex");

    TF1 *fit1 = new TF1("fit1", "gausn", -4, 6);

    TF1 *fit2 = new TF1("fit2", "gausn(0) + gausn(3)", -4, 6);
    fit2->SetParameters(5e4, -0.01, 0.2, 4e4, 0.01, 0.2);

    TF1 *fit3 = new TF1("fit3", AsymmetricGaussian, -4, 6, 4);
    fit3->SetParameters(9e4, -0.01, 0.2, 0.3);

    TF1 *fit4 = new TF1("fit4", "[0]*TMath::Landau(x,[1],[2],0)", -4, 6);
    fit4->SetParameters(100, 0.2, 1.3);

    // TF1 *fit5 = new TF1("fit5", CrystalBall, -4, 6, 5);
    // fit5->SetParNames("N", "mean", "sigma", "alpha", "n");
    // fit5->SetParameters(100, 0.0, 0.2, -1.0, 2.0);  // Example parameters
    TF1 *fit5 = new TF1("fit5", "crystalball", -4, 6);
    fit5->SetParameters(4e4, 0.01, 0.8, -0.5, 1);

    TCanvas *c;
    TLatex t;
    
    c = new TCanvas();
    hist->Fit(fit1, "RE");
    hist->SetTitle("Fit model: Normalized Gaussian");
    t.DrawLatex(3, 0.8*hist->GetMaximum(), Form("N = %.0f", fit1->GetParameter(0)));
    t.DrawLatex(3, 0.7*hist->GetMaximum(), Form("#mu = %.3f", fit1->GetParameter(1)));
    t.DrawLatex(3, 0.6*hist->GetMaximum(), Form("#sigma = %.3f", fit1->GetParameter(2)));
    c->SaveAs("kshort_fit1.pdf");

    c = new TCanvas();
    hist->Fit(fit2, "RE");
    hist->SetTitle("Fit model: Double Normalized Gaussian");
    t.DrawLatex(3, 0.8*hist->GetMaximum(), Form("N = %.0f", fit2->GetParameter(0)));
    t.DrawLatex(3, 0.7*hist->GetMaximum(), Form("#mu = %.3f", fit2->GetParameter(1)));
    t.DrawLatex(3, 0.6*hist->GetMaximum(), Form("#sigma = %.3f", fit2->GetParameter(2)));
    t.DrawLatex(3, 0.5*hist->GetMaximum(), Form("N = %.0f", fit2->GetParameter(3)));
    t.DrawLatex(3, 0.4*hist->GetMaximum(), Form("#mu = %.3f", fit2->GetParameter(4)));
    t.DrawLatex(3, 0.3*hist->GetMaximum(), Form("#sigma = %.3f", fit2->GetParameter(5)));
    double weighted_sigma = (fit2->GetParameter(0)*fit2->GetParameter(2) + fit2->GetParameter(3)*fit2->GetParameter(5)) / (fit2->GetParameter(0) + fit2->GetParameter(3));
    t.DrawLatex(3, 0.2*hist->GetMaximum(), Form("#bar{#sigma} = %.3f", weighted_sigma));
    c->SaveAs("kshort_fit2.pdf");

    c = new TCanvas();
    hist->Fit(fit3, "RE");
    hist->SetTitle("Fit model: Asymmetric Normalized Gaussian");
    t.DrawLatex(3, 0.8*hist->GetMaximum(), Form("N = %.0f", fit3->GetParameter(0)));
    t.DrawLatex(3, 0.7*hist->GetMaximum(), Form("#mu = %.3f", fit3->GetParameter(1)));
    t.DrawLatex(3, 0.6*hist->GetMaximum(), Form("#sigma_{L} = %.3f", fit3->GetParameter(2)));
    t.DrawLatex(3, 0.5*hist->GetMaximum(), Form("#sigma_{R} = %.3f", fit3->GetParameter(2)));
    c->SaveAs("kshort_fit3.pdf");

    c = new TCanvas();
    hist->Fit(fit4, "RE");
    hist->SetTitle("Fit model: Landau");
    t.DrawLatex(3, 0.8*hist->GetMaximum(), Form("N = %.0f", fit4->GetParameter(0)));
    t.DrawLatex(3, 0.7*hist->GetMaximum(), Form("#mu = %.3f", fit4->GetParameter(1)));
    t.DrawLatex(3, 0.6*hist->GetMaximum(), Form("#sigma = %.3f", fit4->GetParameter(2)));
    c->SaveAs("kshort_fit4.pdf");

    c = new TCanvas();
    hist->Fit(fit5, "RE");
    // fit5->Draw();
    hist->SetTitle("Fit model: Crystal Ball");
    t.DrawLatex(3, 0.8*hist->GetMaximum(), Form("Constant = %.0f", fit5->GetParameter(0)));
    t.DrawLatex(3, 0.7*hist->GetMaximum(), Form("Mean = %.3f", fit5->GetParameter(1)));
    t.DrawLatex(3, 0.6*hist->GetMaximum(), Form("#sigma = %.3f", fit5->GetParameter(2)));
    t.DrawLatex(3, 0.5*hist->GetMaximum(), Form("#alpha = %.3f", fit5->GetParameter(3)));
    t.DrawLatex(3, 0.4*hist->GetMaximum(), Form("N = %.3f", fit5->GetParameter(4)));
    c->SaveAs("kshort_fit5.pdf");
}

// Asymmetric Normalized Gaussian
Double_t AsymmetricGaussian(Double_t *x, Double_t *par) {
    Double_t mu = par[1];      // mean
    Double_t sigmaL = par[2];  // std dev for x < mu
    Double_t sigmaR = par[3];  // std dev for x >= mu

    Double_t norm = par[0] * 2.0 / (TMath::Sqrt(2 * TMath::Pi()) * (sigmaL + sigmaR));

    if (x[0] < mu) {
        return norm * TMath::Exp(-0.5 * TMath::Power((x[0] - mu) / sigmaL, 2));
    } else {
        return norm * TMath::Exp(-0.5 * TMath::Power((x[0] - mu) / sigmaR, 2));
    }
}

// One-sided Crystal Ball function
Double_t CrystalBall(Double_t *x, Double_t *par) {
    Double_t m = x[0];
    Double_t N = par[0];
    Double_t mean = par[1];
    Double_t sigma = par[2];
    Double_t alpha = par[3];  // tail transition point (in sigma units)
    Double_t n = par[4];      // tail exponent

    Double_t t = (m - mean) / sigma;

    if (alpha < 0) t = -t;
    Double_t absAlpha = TMath::Abs(alpha);

    // Gaussian core
    if (t > -absAlpha) {
        return TMath::Exp(-0.5 * t * t);
    } else {
        Double_t A = TMath::Power(n / absAlpha, n) * TMath::Exp(-0.5 * absAlpha * absAlpha);
        Double_t B = n / absAlpha - absAlpha;
        return N * A * TMath::Power(B - t, -n);
    }
}