void fig_mksp() {
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.03);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.17);

	gStyle->SetTitleBorderSize(0);
		
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetLabelSize(0.06,"XY");
	gStyle->SetLabelOffset(0.02,"XY");  
	
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetTitleOffset(1.15,"X");
	gStyle->SetTitleOffset(1.5,"Y");
	
	gStyle->SetMarkerSize(1.5);
	gROOT->ForceStyle();

	TFile *inf1 = TFile::Open("hist_dat_gluex1.root");
	TFile *inf2 = TFile::Open("hist_acc_gluex1.root");

	TH1F *h1 = (TH1F*)inf1->Get("im_ksp");
	TH1F *h1_sb = (TH1F*)inf1->Get("im_ksp_sb");
	TH1F *h2 = (TH1F*)inf2->Get("im_ksp");

	h1->Add(h1_sb, -1);
	TH1F *h3 = (TH1F*)h1->Clone();

	h2->Scale(h1->GetMaximum()/h2->GetMaximum());

	h1->SetMarkerColor(kBlack);
	h2->SetMarkerColor(kRed);

	h1->SetMarkerStyle(8);
	h2->SetMarkerStyle(35);

	h1->GetYaxis()->SetRangeUser(0, 1.1*h1->GetMaximum());

	TCanvas *c = new TCanvas();
	h1->Draw();

	c->SaveAs("figs/mksp.pdf");
}
