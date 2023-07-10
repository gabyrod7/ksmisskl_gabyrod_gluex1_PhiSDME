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

	double low = 0.15, high = 1.0;
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
	// h4->Draw("SAME");
	h5->Draw("SAME");

	TLegend *lg = new TLegend(0.1,0.10,0.6,0.4);

	h5->Fit(fit, "RQN");
	sprintf(text, "#phi #rightarrow K^{+}K^{-}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	lg->AddEntry(h5, text, "lep");

	h1->Fit(fit, "RQN");
	sprintf(text, "Spring 2017, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	lg->AddEntry(h1, text, "lep");

	h2->Fit(fit, "RQN");
	sprintf(text, "Spring 2018, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	lg->AddEntry(h2, text, "lep");

	h3->Fit(fit, "RQN");
	sprintf(text, "Fall 2018, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	lg->AddEntry(h3, text, "lep");

	// h4->Fit(fit, "QN");
	// sprintf(text, "GlueX-I, #phi #rightarrow K_{S}K_{L}, slope = %.2f #pm %.2f", fit->GetParameter(1), fit->GetParError(1));
	// lg->AddEntry(h4, text, "lep");

	lg->Draw();

	c->SaveAs("compare.png");

	c = new TCanvas();
	// h1->Divide(h5);
	h2->Divide(h1);
	h3->Divide(h1);
	// h4->Divide(h5);

	// h1->GetYaxis()->SetRangeUser(0, 2.0);

	// h1->Draw();
	h2->Draw("");
	h3->Draw("SAME");
	// h4->Draw("SAME");

	lg = new TLegend(0.40,0.75,0.85,0.90);

	fit = new TF1("line", "pol1", low, high);
	fit->SetLineColor(kBlue);
	h2->Fit(fit, "R");
	lg->AddEntry(h2, "Spring 2018, #phi #rightarrow K_{S}K_{L}", "lep");

	fit = new TF1("line2", "pol1", low, high);
	fit->SetLineColor(kBlack);
	h3->Fit(fit, "R");
	lg->AddEntry(h3, "Fall 2018, #phi #rightarrow K_{S}K_{L}", "lep");

	lg->Draw();

	c->SaveAs("compare_ratio.png");

	// c = new TCanvas();
	// h3->Divide(h2);
	// h3->GetYaxis()->SetTitle("#phi #rightarrow K_{S}K_{L}/#phi #rightarrow K^{+}K^{-}");
	// h3->Draw();
	// h3->GetYaxis()->SetRangeUser(0.5, 1.1);
}
