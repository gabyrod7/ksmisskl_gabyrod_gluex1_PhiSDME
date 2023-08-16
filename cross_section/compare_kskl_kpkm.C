void compare_kskl_kpkm() {
	gStyle->SetOptStat(0);

	char text[100];

	TFile *inf1 = TFile::Open("xs_phi_kskl_sp17.root");
	TFile *inf2 = TFile::Open("xs_phi_kskl_sp18.root");
	TFile *inf3 = TFile::Open("xs_phi_kskl_fa18.root");
	TFile *inf4 = TFile::Open("xs_phi_kskl_gluex1.root");
	TFile *inf5 = TFile::Open("xs_phi_kpkm.root");

	TCanvas *c;

	TH1F *h1 = (TH1F*)inf1->Get("h1_t");
	TH1F *h2 = (TH1F*)inf2->Get("h1_t");
	TH1F *h3 = (TH1F*)inf3->Get("h1_t");
	TH1F *h4 = (TH1F*)inf4->Get("h1_t");
	TH1F *h5 = (TH1F*)inf5->Get("h_xs");
	// TH1F *h3 = (TH1F*)h1->Clone();

	h1->SetMarkerStyle(8);
	h2->SetMarkerStyle(8);
	h3->SetMarkerStyle(8);
	h4->SetMarkerStyle(8);
	h5->SetMarkerStyle(8);

	h1->SetMarkerColor(kRed);
	h2->SetMarkerColor(kBlue);
	h3->SetMarkerColor(kBlack);
	h4->SetMarkerColor(kOrange);
	h5->SetMarkerColor(kViolet);

	h1->GetYaxis()->SetRangeUser(0.01, 1.6);
	h2->GetYaxis()->SetRangeUser(0.01, 1.6);
	h3->GetYaxis()->SetRangeUser(0.01, 1.6);
	h4->GetYaxis()->SetRangeUser(0.01, 1.6);
	h5->GetYaxis()->SetRangeUser(0.01, 1.6);

	double low = 0.2, high = 1.0;
	h1->GetXaxis()->SetRangeUser(low, high);
	h2->GetXaxis()->SetRangeUser(low, high);
	h3->GetXaxis()->SetRangeUser(low, high);
	h4->GetXaxis()->SetRangeUser(low, high);
	h5->GetXaxis()->SetRangeUser(low, high);

	TF1 *fit = new TF1("expo", "expo", low, high);

	c = new TCanvas();
	gPad->SetLogy();
	h1->Draw();
	h2->Draw("SAME");
	h3->Draw("SAME");
	h5->Draw("SAME");

	TLegend *lg = new TLegend(0.1,0.10,0.65,0.4);

	double integral, error;

	h5->Fit(fit, "RQN");
	integral = h5->IntegralAndError(h5->FindBin(low), h5->FindBin(high), error, "width");
	sprintf(text, "#phi #rightarrow K^{+}K^{-}, slope = %.2f #pm %.2f, integral = %.1f #pm %.1f (nb)", fit->GetParameter(1), fit->GetParError(1), integral*1000, error*1000);
	lg->AddEntry(h5, text, "lep");

	h1->Fit(fit, "RQN");
	integral = h1->IntegralAndError(h1->FindBin(low), h1->FindBin(high), error, "width");
	sprintf(text, "Spring 2017, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f, integral = %.1f #pm %.1f (nb)", fit->GetParameter(1), fit->GetParError(1), integral*1000, error*1000);
	lg->AddEntry(h1, text, "lep");

	h2->Fit(fit, "RQN");
	integral = h2->IntegralAndError(h2->FindBin(low), h2->FindBin(high), error, "width");
	sprintf(text, "Spring 2018, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f, integral = %.1f #pm %.1f (nb)", fit->GetParameter(1), fit->GetParError(1), integral*1000, error*1000);
	lg->AddEntry(h2, text, "lep");

	h3->Fit(fit, "RQN");
	integral = h3->IntegralAndError(h3->FindBin(low), h3->FindBin(high), error, "width");
	sprintf(text, "Fall 2018, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f, integral = %.1f #pm %.1f (nb)", fit->GetParameter(1), fit->GetParError(1), integral*1000, error*1000);
	lg->AddEntry(h3, text, "lep");

	lg->Draw();

	// c->SaveAs("compare.png");
	c->SaveAs("figs/compare.pdf");

	c = new TCanvas();
	h2->Divide(h1);
	h3->Divide(h1);

	h2->GetYaxis()->SetRangeUser(0.8, 1.3);
	h2->Draw("");
	h3->Draw("SAME");

	lg = new TLegend(0.15,0.15,0.85,0.30);

	fit = new TF1("line", "pol1", low, high);
	fit->SetLineColor(kBlue);
	h2->Fit(fit, "R");
	sprintf(text, "Spring 2018/Spring 2017, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	lg->AddEntry(h2, text, "lep");

	fit = new TF1("line2", "pol1", low, high);
	fit->SetLineColor(kBlack);
	h3->Fit(fit, "R");
	sprintf(text, "Fall 2018/Spring 2017, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	lg->AddEntry(h3, text, "lep");

	lg->Draw();

	c->SaveAs("figs/compare_ratio.pdf");
}
