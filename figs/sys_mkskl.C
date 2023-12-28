void sys_mkskl() {
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

	TH1F *h1 = (TH1F*)inf1->Get("im_kskl");
	TH1F *h1_sb = (TH1F*)inf1->Get("im_kskl_sb");

	h1->Add(h1_sb, -1);

	h1->SetMarkerColor(kBlack);
	h1->SetMarkerStyle(8);
	h1->GetYaxis()->SetRangeUser(0, 1.1*h1->GetMaximum());

	TCanvas *c = new TCanvas();
	h1->Draw();

	TLine *line1, *line2, *line3;
	
	// Nominal cut
	line1 = new TLine(1.005, 0, 1.005, h1->GetMaximum());
	line1->SetLineWidth(2);
	line1->Draw();
	line1->DrawLine(1.04, 0, 1.04, h1->GetMaximum());

	// Cut variation 1
	line2 = new TLine(1.002, 0, 1.002, h1->GetMaximum());
	line2->SetLineWidth(2); line2->SetLineStyle(2); 
	line2->Draw();

	line2 = new TLine(1.043, 0, 1.043, h1->GetMaximum());
	line2->SetLineWidth(2); line2->SetLineStyle(2); 
	line2->Draw();

	// Cut variation 2
	line3 = new TLine(1.007, 0, 1.007, h1->GetMaximum());
	line3->SetLineWidth(2); line3->SetLineStyle(2); 
	line3->Draw();
	line3->DrawLine(1.038, 0, 1.038, h1->GetMaximum());

	// Cut variation 3
	line3 = new TLine(1.006, 0, 1.006, h1->GetMaximum());
	line3->SetLineWidth(2); line3->SetLineStyle(2); 
	line3->Draw();
	line3->DrawLine(1.039, 0, 1.039, h1->GetMaximum());

	TLegend *lg = new TLegend(0.6, 0.7, 0.95, 0.95);
	lg->AddEntry(h1, "Data", "ep");
	lg->AddEntry(line1, "Nominal cut", "l");
	lg->AddEntry(line2, "Cut Variations", "l");
	// lg->AddEntry(line3, "Cut Variation 2", "l");
	lg->Draw();

	// Integrate histogram upto each line
	cout << h1->Integral(h1->GetXaxis()->FindBin(1.005), h1->GetXaxis()->FindBin(1.04))/h1->Integral(h1->GetXaxis()->FindBin(1.002), h1->GetXaxis()->FindBin(1.043)) << endl;
	cout << h1->Integral(h1->GetXaxis()->FindBin(1.005), h1->GetXaxis()->FindBin(1.04))/h1->Integral(h1->GetXaxis()->FindBin(1.007), h1->GetXaxis()->FindBin(1.038)) << endl;
	cout << h1->Integral(h1->GetXaxis()->FindBin(1.005), h1->GetXaxis()->FindBin(1.04))/h1->Integral(h1->GetXaxis()->FindBin(1.008), h1->GetXaxis()->FindBin(1.037)) << endl;

	c->SaveAs("systematics/mkskl.pdf");
}
