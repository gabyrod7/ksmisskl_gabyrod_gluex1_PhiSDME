
void plot_mandelt() {
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
	gStyle->SetTitleOffset(1.15,"Y");
	
	gStyle->SetMarkerSize(1.5);
	gROOT->ForceStyle();

    TFile *inf = TFile::Open("hist_dat_gluex1.root");

    TH1F *h1 = (TH1F*)inf->Get("h1_mandelt");
    TH1F *h1_sb = (TH1F*)inf->Get("h1_mandelt_sb");

    h1_sb->SetFillColor(kRed);

    h1->GetYaxis()->SetRangeUser(1, 10*h1->GetMaximum());

    TCanvas *c = new TCanvas("c", "c", 800, 500);
    c->SetLogy();
    h1->Draw();
    h1_sb->Draw("hist same");

    c->SaveAs("mandelt.pdf");

    c->SetLogy(0);
    h1_sb->GetYaxis()->SetTitle("Background [%]");
    h1_sb->Divide(h1);
    h1_sb->Scale(100);
    h1_sb->GetYaxis()->SetRangeUser(0, 1);
    h1_sb->Draw();
    c->SaveAs("mandelt_ratio.pdf");
}
