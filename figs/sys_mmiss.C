void sys_mmiss() {
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

	TH1F *h1 = (TH1F*)inf1->Get("h1_MissingMass");
	TH1F *h1_sb = (TH1F*)inf1->Get("h1_MissingMass_sb");

	h1->Add(h1_sb, -1);

	h1->SetMarkerColor(kBlack);
	h1->SetMarkerStyle(8);
	h1->GetYaxis()->SetRangeUser(0, 1.1*h1->GetMaximum());

	TCanvas *c = new TCanvas();
	h1->Draw();

	TLine *line1, *line2, *line3;
	
	line1 = new TLine(0.3, 0, 0.7, h1->GetMaximum());
	line1->SetLineWidth(2);
	line1->DrawLine(0.3, 0, 0.3, h1->GetMaximum());
	line1->DrawLine(0.7, 0, 0.7, h1->GetMaximum());

	line2 = new TLine(0.3, 0, 0.7, h1->GetMaximum());
	line2->SetLineWidth(2);
	line2->SetLineStyle(2);
	// line2->SetLineColor(kGray+1);

	line2->DrawLine(0.2, 0, 0.2, h1->GetMaximum());
	line2->DrawLine(0.8, 0, 0.8, h1->GetMaximum());
	line2->DrawLine(0.35, 0.0, 0.35, h1->GetMaximum());
	line2->DrawLine(0.65, 0.0, 0.65, h1->GetMaximum());
	line2->DrawLine(0.38, 0.0, 0.38, h1->GetMaximum());
	line2->DrawLine(0.62, 0.0, 0.62, h1->GetMaximum());

	TLegend *lg = new TLegend(0.72, 0.7, 0.97, 0.97);
	lg->AddEntry(h1, "Data", "ep");
	lg->AddEntry(line1, "Nominal cut", "l");
	lg->AddEntry(line2, "Cut Variation", "l");
	lg->Draw();

	// Integrate histogram upto each line
	cout << h1->Integral(h1->GetXaxis()->FindBin(0.3), h1->GetXaxis()->FindBin(0.7))/h1->Integral(h1->GetXaxis()->FindBin(0.20), h1->GetXaxis()->FindBin(0.80)) << endl;
	cout << h1->Integral(h1->GetXaxis()->FindBin(0.3), h1->GetXaxis()->FindBin(0.7))/h1->Integral(h1->GetXaxis()->FindBin(0.35), h1->GetXaxis()->FindBin(0.65)) << endl;
	cout << h1->Integral(h1->GetXaxis()->FindBin(0.3), h1->GetXaxis()->FindBin(0.7))/h1->Integral(h1->GetXaxis()->FindBin(0.37), h1->GetXaxis()->FindBin(0.63)) << endl;

	c->SaveAs("systematics/missing_mass.pdf");
}
