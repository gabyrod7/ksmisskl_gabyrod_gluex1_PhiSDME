void UnusedShowers2() {
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.03);
	gStyle->SetPadBottomMargin(0.13);
	gStyle->SetPadLeftMargin(0.15);

	gStyle->SetTitleBorderSize(0);
	
	gStyle->SetTitleFont(132);
	gStyle->SetTitleSize(0.05);
	gStyle->SetTitleOffset(1.2);
	
	gStyle->SetLabelSize(0.05,"XY");
	gStyle->SetLabelOffset(0.01,"XY");  
	
	gStyle->SetTitleSize(0.05,"XY");
	gStyle->SetTitleOffset(1.1,"X");
	
	gStyle->SetMarkerStyle(8);
	gStyle->SetMarkerSize(2.0);

	gROOT->ForceStyle();

	auto inf1 = TFile::Open("hist_ksks_miss_recon.root");
	auto inf2 = TFile::Open("hist_kskl.root");

	auto h_kskl = (TH1F*)inf2->Get("NumUnusedShowers_trackscut");
	auto h_ksks_pippimpippim = (TH1F*)inf1->Get("NumUnusedShowers_charged_trackscut");
	auto h_ksks_pippimpi0pi0 = (TH1F*)inf1->Get("NumUnusedShowers_mixed_trackscut");

	h_ksks_pippimpippim->Scale(1./(20000000*0.48));
	h_ksks_pippimpi0pi0->Scale(1./(20000000*0.41));
	h_kskl->Scale(1./(18000000*0.69));

	h_ksks_pippimpippim->SetMarkerStyle(8);
	h_kskl->SetMarkerStyle(8);
	h_ksks_pippimpi0pi0->SetMarkerStyle(8);

	h_ksks_pippimpippim->SetLineColor(kRed);
	h_kskl->SetLineColor(kBlack);
	h_ksks_pippimpi0pi0->SetLineColor(kBlue);

	h_ksks_pippimpippim->SetMarkerSize(1.5);
	h_kskl->SetMarkerSize(1.5);
	h_ksks_pippimpi0pi0->SetMarkerSize(1.5);

	h_ksks_pippimpippim->GetYaxis()->SetRangeUser(0, 0.08);
	h_ksks_pippimpippim->GetYaxis()->SetTitle("Efficiency");

	TCanvas *c = new TCanvas();
	h_ksks_pippimpippim->Draw("HIST");
	h_kskl->Draw("HIST SAME");
	h_ksks_pippimpi0pi0->Draw("HIST SAME");

	TLatex t;
	t.SetTextSize(0.06);
	t.DrawLatex(5, 0.9*h_ksks_pippimpippim->GetMaximum(), "K_{S}K_{L}p #rightarrow #pi^{+}#pi^{-}(K_{L})p");
	t.SetTextColor(kRed);
	t.DrawLatex(5, 0.8*h_ksks_pippimpippim->GetMaximum(), "K_{S}K_{S}p #rightarrow #pi^{+}#pi^{-}#pi^{+}#pi^{-}p");
	t.SetTextColor(kBlue);
	t.DrawLatex(5, 0.7*h_ksks_pippimpippim->GetMaximum(), "K_{S}K_{S}p #rightarrow #pi^{+}#pi^{-}#pi^{0}#pi^{0}p");
//	t.SetTextColor(kGreen);
//	t.DrawLatex(3, 0.6*h_ksks_pippimpippim->GetMaximum(), "K_{S}K_{S}p #rightarrow other channels");

	c->SaveAs("unsued_showers_study2.pdf");

	cout << "efficiency " << h_ksks_pippimpi0pi0->Integral(1, 3, "width") << endl;
}
