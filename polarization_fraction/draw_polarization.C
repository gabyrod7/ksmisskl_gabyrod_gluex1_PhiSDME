void draw_polarization() {
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadBottomMargin(0.13);
	gStyle->SetPadLeftMargin(0.11);

	gStyle->SetTitleBorderSize(0);
	
	gStyle->SetTitleFont(132);
	gStyle->SetTitleSize(0.05);
	// gStyle->SetTitleOffset(1.2);
	
	gStyle->SetLabelSize(0.05,"XY");
	gStyle->SetLabelOffset(0.01,"XY");  
	
	gStyle->SetTitleSize(0.05,"XY");
	gStyle->SetTitleOffset(1.1,"X");
	
	gStyle->SetMarkerStyle(8);
	gStyle->SetMarkerSize(0.0);

    TFile *inf = new TFile("gluex1Tpol.root");

    TH1F *h, *h2;
    TLine *line1, *line2;
    
    vector<string> hnames = {"hPol0", "hPol45", "hPol90", "hPol135"};
    map<string, string> htitles = {
        {"hPol0", "Polarization at 0#circ"},
        {"hPol45", "Polarization at 45#circ"},
        {"hPol90", "Polarization at 90#circ"},
        {"hPol135", "Polarization at -45#circ"}
    };
    TLegend *lg = new TLegend(0.6, 0.6, 0.9, 0.9);

    TCanvas *c = new TCanvas();
    for(int i = 0; i < hnames.size(); i++) {
        h = (TH1F*)inf->Get(hnames[i].c_str());

        h->SetMarkerStyle(20);
        h->SetMarkerColor(i+1);
        h->SetMarkerSize(1.5);

        if(i == 0)  {
            h->GetXaxis()->SetRangeUser(7, 11.4);
            h->GetYaxis()->SetRangeUser(0, 0.5);

            h->GetXaxis()->SetTitle("E_{#gamma} (GeV)");
            h->GetYaxis()->SetTitle("Polarization Fraction");
            h->GetYaxis()->SetTitleOffset(0.8);

            h->Draw();

            line1 = new TLine(8.2, 0, 8.2, h->GetMaximum());
            line2 = new TLine(8.8, 0, 8.8, h->GetMaximum());
            line1->Draw();
            line2->Draw();
        }
        else    
            h->Draw("same");


        lg->AddEntry(h, htitles[hnames[i]].c_str(), "lep");
    }
    lg->Draw();

    c->SaveAs("polarization.pdf");
}