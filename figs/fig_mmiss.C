void fig_mmiss() {
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.07);
	gStyle->SetPadRightMargin(0.03);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);

	gStyle->SetTitleBorderSize(0);
		
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetLabelSize(0.06,"XY");
	gStyle->SetLabelOffset(0.02,"XY");  
	
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetTitleOffset(1.15,"X");
	gStyle->SetTitleOffset(1.2,"Y");
	
	gStyle->SetMarkerSize(1.5);
	gROOT->ForceStyle();

	TGaxis::SetMaxDigits(3);

	TFile *inf1 = TFile::Open("hist_dat_gluex1.root");
	TFile *inf2 = TFile::Open("hist_acc_gluex1.root");

	TH1F *h1 = (TH1F*)inf1->Get("h1_MissingMass");
	TH1F *h1_sb = (TH1F*)inf1->Get("h1_MissingMass_sb");
	TH1F *h2 = (TH1F*)inf2->Get("h1_MissingMass");

	h1->Add(h1_sb, -1);
	TH1F *h3 = (TH1F*)h1->Clone();

	h2->Scale(h1->GetMaximum()/h2->GetMaximum());
	h3->GetXaxis()->SetRangeUser(0.30, 0.70);

	h1->SetMarkerColor(kBlack);
	h2->SetMarkerColor(kRed);
	h3->SetFillColorAlpha(kGreen, 0.2);

	h1->SetMarkerStyle(8);
	h2->SetMarkerStyle(35);

	h1->GetYaxis()->SetRangeUser(0, 1.1*h1->GetMaximum());

	char title[100];
	sprintf(title, "Counts / %.1f (MeV/c^{2})", h1->GetBinWidth(1)*1000);
	h1->GetYaxis()->SetTitle(title);
	h1->GetXaxis()->SetTitle("Missing Mass (GeV/c^{2})");

	TCanvas *c = new TCanvas();
	h1->Draw();
	h3->Draw("SAME HIST");
	h1->Draw("SAME");
	h2->Draw("SAME");

	// TLatex t;
	// t.SetTextSize(0.08);
	// t.DrawLatex(0.6, 0.85*h1->GetMaximum(), "GlueX-I Data");
	// t.SetTextColor(kRed);
	// t.DrawLatex(0.6, 0.73*h1->GetMaximum(), "Monte Carlo");

	TLine *line = new TLine(0.3, 0, 0.7, 0.5*h1->GetMaximum());
	line->SetLineWidth(2);
	line->DrawLine(0.3, 0, 0.3, 0.5*h1->GetMaximum());
	line->DrawLine(0.7, 0, 0.7, 0.5*h1->GetMaximum());

	// TLegend *leg = new TLegend(0.63, 0.7, 0.97, 0.97);
	TLegend *leg = new TLegend(0.63, 0.66, 0.97, 0.93);
	leg->SetTextSize(0.055);
	leg->AddEntry(h1, "GlueX-I Data", "lep");
	leg->AddEntry(h2, "Simulated Data", "lep");
	leg->AddEntry(line, "Signal Region", "l");
	leg->Draw();

	c->SaveAs("figs/missing_mass.pdf");

	cout << h3->Integral()/h1->Integral() << endl;
}
