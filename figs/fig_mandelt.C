void fig_mandelt() {
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.03);
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

	TFile *inf1 = TFile::Open("hist_dat_gluex1.root");
	TFile *inf2 = TFile::Open("hist_acc_gluex1.root");

	TH1F *h1 = (TH1F*)inf1->Get("h1_mandelt");
	TH1F *h1_sb = (TH1F*)inf1->Get("h1_mandelt_sb");
	TH1F *h2 = (TH1F*)inf2->Get("h1_mandelt");

	h1->Add(h1_sb, -1);

	h2->Scale(h1->GetMaximum()/h2->GetMaximum());

	h1->SetMarkerColor(kBlack);
	h2->SetMarkerColor(kRed);

	h1->SetMarkerStyle(8);
	h2->SetMarkerStyle(35);

	h1->GetYaxis()->SetRangeUser(10, 10*h1->GetMaximum());

	char title[100];
	sprintf(title, "Counts / %.2f (GeV^{2}/c^{2})", h1->GetBinWidth(1));
	h1->GetYaxis()->SetTitle(title);
	h1->GetXaxis()->SetTitle("Squared 4-Momentum Transfer -t (GeV^{2}/c^{2})");

	TCanvas *c = new TCanvas();
	c->SetLogy();
	h1->Draw();
	h2->Draw("SAME");

	// TLatex t;
	// t.SetTextSize(0.08);
	// t.DrawLatex(0.9, 0.85*h1->GetMaximum(), "GlueX-I Data");
	// t.SetTextColor(kRed);
	// t.DrawLatex(0.9, 0.73*h1->GetMaximum(), "Monte Carlo");

	TLegend *leg = new TLegend(0.63, 0.7, 0.97, 0.97);
	leg->SetTextSize(0.055);
	leg->AddEntry(h1, "GlueX-I Data", "lep");
	leg->AddEntry(h2, "Simulated Data", "lep");
	leg->Draw();

	c->SaveAs("figs/mandel_t.pdf");

	TLine *line = new TLine(0.15, 0, 0.15, h1->GetMaximum());
	line->SetLineWidth(2);
	line->Draw();

	// c = new TCanvas();
	// TRatioPlot *rp = new TRatioPlot(h1, h2);
	// rp->Draw();
	// rp->GetLowerRefYaxis()->SetNdivisions(509);
	// rp->GetLowerRefYaxis()->SetRangeUser(0.9, 1.49);
	// c->SaveAs("fig_mandelt.pdf");
}
