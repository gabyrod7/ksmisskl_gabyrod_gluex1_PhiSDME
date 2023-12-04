void sys_ProtonZVertex() {
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.065);
	gStyle->SetPadRightMargin(0.015);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.17);

	gStyle->SetTitleBorderSize(0);
		
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetLabelSize(0.06,"XY");
	gStyle->SetLabelOffset(0.02,"XY");  
	
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetTitleOffset(1.15,"X");
	gStyle->SetTitleOffset(1.5,"Y");
	
	// gStyle->SetMarkerSize(1.5);
	gROOT->ForceStyle();

	TFile *inf1 = TFile::Open("hist_dat_gluex1.root");

	TH1F *h1 = (TH1F*)inf1->Get("h1_ProtonZVertex");
	TH1F *h1_sb = (TH1F*)inf1->Get("h1_ProtonZVertex_sb");

	h1->Add(h1_sb, -1);

	h1->SetMarkerColor(kBlack);
	h1->SetMarkerStyle(8);
	h1->SetMarkerSize(1.5);
	h1->GetYaxis()->SetRangeUser(0, 1.1*h1->GetMaximum());
	h1->GetXaxis()->SetRangeUser(0, 9);

	TCanvas *c = new TCanvas();
	h1->Draw();

	TLine *line1, *line2;
	
	line1 = new TLine(52, 0, 52, h1->GetMaximum());
	line1->SetLineWidth(2);
	line1->Draw();
	line1->DrawLine(78, 0, 78, h1->GetMaximum());

	line2 = new TLine(79, 0, 79, h1->GetMaximum());
	line2->SetLineWidth(2);
	line2->SetLineStyle(2);
	line2->Draw();
	line2->DrawLine(77, 0, 77, h1->GetMaximum());
	line2->DrawLine(53, 0, 53, h1->GetMaximum());
	line2->DrawLine(51, 0, 51, h1->GetMaximum());

	// line2->DrawLine(3, 0, 3, h1->GetMaximum());

	TLegend *lg = new TLegend(0.63, 0.7, 0.98, 0.93);
	lg->AddEntry(h1, "Data", "ep");
	lg->AddEntry(line1, "Nominal cut", "l");
	lg->AddEntry(line2, "Cut Variations", "l");
	lg->Draw();

	c->SaveAs("systematics/proton_zvertex.pdf");
}
