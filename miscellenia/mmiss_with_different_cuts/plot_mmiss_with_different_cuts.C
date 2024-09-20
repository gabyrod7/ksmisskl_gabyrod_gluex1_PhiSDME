
void plot_mmiss_with_different_cuts() {
	gStyle->SetOptStat(0);
	gStyle->SetPadTopMargin(0.07);
	gStyle->SetPadRightMargin(0.03);
	gStyle->SetPadBottomMargin(0.15);
	gStyle->SetPadLeftMargin(0.15);

	gStyle->SetTitleBorderSize(0);
		
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetLabelSize(0.06,"XY");
	gStyle->SetLabelOffset(0.02,"XY");  
	
	gStyle->SetTitleSize(0.06,"XY");
	gStyle->SetTitleOffset(1.15,"X");
	gStyle->SetTitleOffset(1.35,"Y");
	
	gStyle->SetMarkerSize(1.5);
	gROOT->ForceStyle();

    TFile *inf = TFile::Open("hist_dat_gluex1.root");

    vector<string> hNames = {"h1_mmiss", "h1_mmiss_noFScut", "h1_mmiss_noChisqcut", "h1_mmiss_noNtrackscut", "h1_mmiss_noNshowerscut", "h1_mmiss_noMpipicut"};
    map<string, TH1F*> hMap;
    map<string, TH1F*> hMap_norm;
    for(int i = 0; i < hNames.size(); i++) {
        hMap[hNames[i]] = (TH1F*)inf->Get(hNames[i].c_str());
    }

    hMap["h1_mmiss"]->SetLineColor(kBlack);
    hMap["h1_mmiss_noFScut"]->SetLineColor(kRed);
    hMap["h1_mmiss_noChisqcut"]->SetLineColor(kGreen);
    hMap["h1_mmiss_noNtrackscut"]->SetLineColor(kBlue);
    hMap["h1_mmiss_noNshowerscut"]->SetLineColor(kMagenta);
    hMap["h1_mmiss_noMpipicut"]->SetLineColor(kCyan);

    for(int i = 0; i < hNames.size(); i++) {
        hMap_norm[hNames[i]] = (TH1F*)hMap[hNames[i]]->Clone();
        hMap_norm[hNames[i]]->Scale(1.0/hMap_norm[hNames[i]]->Integral());
    }

    hMap["h1_mmiss"]->GetYaxis()->SetRangeUser(0, 1.1*hMap["h1_mmiss_noNshowerscut"]->GetMaximum());
    char text[100];
    sprintf(text, "Counts / %.0f MeV", 1000*hMap["h1_mmiss"]->GetBinWidth(1));
    hMap["h1_mmiss"]->GetYaxis()->SetTitle(text);
    hMap_norm["h1_mmiss"]->GetYaxis()->SetTitle("Intensity (a. u.)");

    TCanvas *c = new TCanvas("c", "c", 800, 500);

    // TPad *pad1 = new TPad("pad1","",0,0,1,1);
	// pad1->SetTopMargin(0.03);
	// pad1->SetRightMargin(0.02);
	// pad1->SetBottomMargin(0.15);
	// pad1->SetLeftMargin(0.17);
	// pad1->SetTopMargin(0.07);
	// pad1->SetRightMargin(0.03);
	// pad1->SetBottomMargin(0.15);
	// pad1->SetLeftMargin(0.15);
    // TGaxis::SetMaxDigits(3);

    // TPad *pad2 = new TPad("pad2","",0.62, 0.57, 0.96, 0.92);
	// pad2->SetTopMargin(0.07);
	// pad2->SetRightMargin(0.03);
	// pad2->SetBottomMargin(0.15);
	// pad2->SetLeftMargin(0.18);

    // pad1->Draw();
    // pad1->cd();
    hMap["h1_mmiss"]->Draw("hist");
    for(int i = 1; i < hNames.size(); i++) {
        hMap[hNames[i]]->Draw("hist same");
    }

    TLegend *leg = new TLegend(0.20, 0.6, 0.45, 0.9);
    leg->AddEntry(hMap["h1_mmiss"], "All cuts", "l");
    leg->AddEntry(hMap["h1_mmiss_noFScut"], "Flight Significance > 2#sigma", "l");
    leg->AddEntry(hMap["h1_mmiss_noChisqcut"], "#chi^{2}/ndf < 6", "l");
    leg->AddEntry(hMap["h1_mmiss_noNtrackscut"], "N_{tracks} #leq 4", "l");
    leg->AddEntry(hMap["h1_mmiss_noNshowerscut"], "N_{showers} #leq 10", "l");
    leg->AddEntry(hMap["h1_mmiss_noMpipicut"], "0.3 < M(#pi^{+}#pi^{-}) < 0.7 GeV", "l");
    leg->Draw();

    // pad2->Draw();
    // pad2->cd();
    // hMap_norm["h1_mmiss"]->Draw("hist");
    // for(int i = 1; i < hNames.size(); i++) {
    //     hMap_norm[hNames[i]]->Draw("hist same");
    // }

    c->SaveAs("mmiss_with_different_cuts.pdf");
}
