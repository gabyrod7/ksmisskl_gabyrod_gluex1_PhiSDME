void sys_FlightSignificance() {
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

	TH1F *h1 = (TH1F*)inf1->Get("h1_FS");
	TH1F *h1_sb = (TH1F*)inf1->Get("h1_FS_sb");

	h1->Add(h1_sb, -1);

	h1->SetMarkerColor(kBlack);
	h1->SetMarkerStyle(8);
	h1->GetYaxis()->SetRangeUser(0, 1.1*h1->GetMaximum());

	TCanvas *c = new TCanvas();
	h1->Draw();

	TLine *line1, *line2;
	
	line1 = new TLine(4, 0, 4, h1->GetMaximum());
	line1->SetLineWidth(2);
	line1->Draw();

	line2 = new TLine(3.5, 0, 3.5, h1->GetMaximum());
	line2->SetLineWidth(2);
	line2->SetLineStyle(2);
	line2->Draw();

	line2->DrawLine(4.5, 0, 4.5, h1->GetMaximum());
	line2->DrawLine(5.0, 0, 5.0, h1->GetMaximum());

	TLegend *lg = new TLegend(0.6, 0.7, 0.95, 0.95);
	lg->AddEntry(h1, "Data", "ep");
	lg->AddEntry(line1, "Nominal cut", "l");
	lg->AddEntry(line2, "Cut Variations", "l");
	lg->Draw();

	// Integrate histogram upto each line
	cout << h1->Integral(h1->GetXaxis()->FindBin(4.0), h1->GetXaxis()->FindBin(1000.0))/h1->Integral(h1->GetXaxis()->FindBin(3.5), h1->GetXaxis()->FindBin(1000.0)) << endl;
	cout << h1->Integral(h1->GetXaxis()->FindBin(4.0), h1->GetXaxis()->FindBin(1000.0))/h1->Integral(h1->GetXaxis()->FindBin(4.5), h1->GetXaxis()->FindBin(1000.0)) << endl;
	cout << h1->Integral(h1->GetXaxis()->FindBin(4.0), h1->GetXaxis()->FindBin(1000.0))/h1->Integral(h1->GetXaxis()->FindBin(5.0), h1->GetXaxis()->FindBin(1000.0)) << endl;

	c->SaveAs("systematics/flight_significance.pdf");
}
