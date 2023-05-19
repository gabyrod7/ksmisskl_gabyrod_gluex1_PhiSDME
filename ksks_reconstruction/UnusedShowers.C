void UnusedShowers() {
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
	auto inf2 = TFile::Open("hist_kskl_acc_flat.root");

	auto h1 = (TH1F*)inf1->Get("NumUnusedShowers_charged");
	auto h2 = (TH1F*)inf2->Get("NumUnusedShowers");
	auto h3 = (TH1F*)inf1->Get("NumUnusedShowers_mixed");
	auto h4 = (TH1F*)inf1->Get("NumUnusedShowers_0");

	h1->Scale(1./20000000);
	h3->Scale(1./20000000);
	h4->Scale(1./20000000);
	h2->Scale(1./(2000000*0.69));

	h1->SetMarkerStyle(8);
	h2->SetMarkerStyle(8);
	h3->SetMarkerStyle(8);
	h4->SetMarkerStyle(8);

	h1->SetMarkerColor(kRed);
	h2->SetMarkerColor(kBlack);
	h3->SetMarkerColor(kBlue);
	h4->SetMarkerColor(kGreen-3);

	h1->SetMarkerSize(1.5);
	h2->SetMarkerSize(1.5);
	h3->SetMarkerSize(1.5);
	h4->SetMarkerSize(1.5);

	h1->GetYaxis()->SetRangeUser(0, 0.03);
	h1->GetYaxis()->SetTitle("Efficiency");

	TCanvas *c = new TCanvas();
	h1->Draw();
	h2->Draw("SAME");
	h3->Draw("SAME");
//	h4->Draw("SAME");

	TLatex t;
	t.SetTextSize(0.06);
	t.DrawLatex(3, 0.9*h1->GetMaximum(), "K_{S}K_{L}p #rightarrow #pi^{+}#pi^{-}(K_{L})p");
	t.SetTextColor(kRed);
	t.DrawLatex(3, 0.8*h1->GetMaximum(), "K_{S}K_{S}p #rightarrow #pi^{+}#pi^{-}#pi^{+}#pi^{-}p");
	t.SetTextColor(kBlue);
	t.DrawLatex(3, 0.7*h1->GetMaximum(), "K_{S}K_{S}p #rightarrow #pi^{+}#pi^{-}#pi^{0}#pi^{0}p");
//	t.SetTextColor(kGreen-3);
//	t.DrawLatex(3, 0.6*h1->GetMaximum(), "K_{S}K_{S}p #rightarrow other channels");

	c->SaveAs("unsued_showers_study.pdf");
}
