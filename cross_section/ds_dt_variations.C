void ds_dt_variations() {
	gStyle->SetOptStat(0);

	char text[50];

	// TFile *inf1 = TFile::Open("hist_dat_sp17.root");
	// TFile *inf2 = TFile::Open("hist_acc_sp17.root");
	// TFile *inf3 = TFile::Open("hist_gen_sp17.root");
	// TFile *inf4 = TFile::Open("../flux/flux_30274_31057.root");

	TFile *inf1 = TFile::Open("hist_dat_sp18.root");
	TFile *inf2 = TFile::Open("hist_acc_sp18.root");
	TFile *inf3 = TFile::Open("hist_gen_sp18.root");
	TFile *inf4 = TFile::Open("../flux/flux_40856_42559.root");

	// TFile *inf1 = TFile::Open("hist_dat_fa18.root");
	// TFile *inf2 = TFile::Open("hist_acc_fa18.root");
	// TFile *inf3 = TFile::Open("hist_gen_fa18.root");
	// TFile *inf4 = TFile::Open("../flux/flux_50685_51768.root");

	//TFile *opf = TFile::Open("xs_phi_kskl.root", "UPDATE");
	TFile *opf = TFile::Open("xs_phi_kskl_variations.root", "RECREATE");

	TLegend *lg = new TLegend(0.25, 0.5, 0.9, 0.9);

	pair<string, string> hnames[] = {make_pair("h1_t", "No unused showers cut"), make_pair("h1_t_shower1", "unused shower < 1"), 
									make_pair("h1_t_shower2", "unused shower < 2"), make_pair("h1_t_shower3", "unused shower < 3"), 
									make_pair("h1_t_shower4", "unused shower < 4"), make_pair("h1_t_shower5", "unused shower < 5"), 
									make_pair("h1_t_shower6", "unused shower < 6")};

	int count = 1;
	TCanvas *c = new TCanvas("c", "c", 1800, 1000);
	for(auto hname : hnames) {
		TH1F *dat = (TH1F*)inf1->Get(hname.first.c_str());
		TH1F *bkg = (TH1F*)inf1->Get((hname.first+"_sb").c_str());
		TH1F *acc = (TH1F*)inf2->Get(hname.first.c_str());
		TH1F *gen = (TH1F*)inf3->Get("h1_t");
		TH1F *hflux = (TH1F*)inf4->Get("tagged_flux");
		TH1F *eff = (TH1F*)acc->Clone("eff");
	
		double target = 1.22e-6; // target thickness
		double br = 0.34*0.69; // branching ration, phi->KsKl br = 0.34, Ks->pi+pi- br = 0.69
		double flux = hflux->Integral();
		double Delta_t = dat->GetBinWidth(1);
		char text[100];
	
		eff->Divide(gen);
		dat->Add(bkg, -1);
		dat->Divide( eff );
		dat->Scale( 1.0/flux );
		dat->Scale( 1.0/target );
		dat->Scale( 1.0/br );
		dat->Scale( 1.0/Delta_t );
	
		dat->GetXaxis()->SetRangeUser(0.2, 1.00);
		dat->GetYaxis()->SetRangeUser(0.0, 1.2);
	
		dat->GetYaxis()->SetTitle("#frac{d#sigma}{d(-t)} (#mub/GeV^{2})");

		dat->SetLineColor(count);
		count++;

		if(hname.first == "h1_t")
			dat->Draw();
		else
			dat->Draw("same");

		// sprintf(text, "Unused Showers < %c", hname[11]);
		// lg->AddEntry(dat , text, "lep");

		TF1 *fit = new TF1("expo", "expo", 0.2, 1.0);
		dat->Fit(fit, "RQN");
		sprintf(text, "%s, integral = %.4f #pm %.4f, slope = %.2f #pm %.2f", hname.second.c_str(), fit->Integral(0.2, 1.0), fit->IntegralError(0.2, 1.0), fit->GetParameter(1), fit->GetParError(1));
		// sprintf(text, "%s, A = %.3f #pm %.3f, slope = %.2f #pm %.2f", hname.second.c_str(), fit->GetParameter(0), fit->GetParError(0), fit->GetParameter(1), fit->GetParError(1));
		lg->AddEntry(dat, text, "lep");
	
		dat->Write();
	
		cout << "Integrated cross section " << dat->Integral("width") << endl;
	}

	lg->Draw();

	c->SaveAs("sp18_xs_phi_kskl_variations.png");
}
