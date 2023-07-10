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

	TLegend *lg = new TLegend(0.6, 0.6, 0.9, 0.9);

	vector<string> hnames = {"h1_t", "h1_t2", "h1_t3", "h1_t4", "h1_t5"};
	map<string, string> legend = {{"h1_t", "nominal"}, {"h1_t2", "unused tracks < 2"}, {"h1_t3", "#chi^{2}/ndf < 5"}, {"h1_t4", "FS > 3"}, {"h1_t5", "0.45 < MM < 0.55"}};
	// vector<string> hnames = {"h1_t_shower1", "h1_t_shower2", "h1_t_shower3", "h1_t_shower4", "h1_t_shower5", "h1_t_shower6"};
	// // map<string, string> legend = {{"h1_t_shower1", "unused shower < "}, {"h1_t_shower", "unused tracks < 2"}};

	int count = 1;
	TCanvas *c = new TCanvas();
	for(auto hname : hnames) {

		TH1F *dat = (TH1F*)inf1->Get(hname.c_str());
		TH1F *bkg = (TH1F*)inf1->Get((hname+"_sb").c_str());
		TH1F *acc = (TH1F*)inf2->Get(hname.c_str());
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
	
		dat->GetXaxis()->SetRangeUser(0.1, 0.70);
		dat->GetYaxis()->SetRangeUser(0.0, 1.8);
	
		dat->GetYaxis()->SetTitle("#frac{d#sigma}{d(-t)} (#mub/GeV^{2})");

		dat->SetLineColor(count);
		count++;

		// TCanvas *c = new TCanvas();
		// eff->Draw();
		// c->SaveAs("efficiency.pdf");
	
		// c = new TCanvas();
		if(hname == "h1_t_shower1")
			dat->Draw();
		else
			dat->Draw("same");

		// sprintf(text, "Unused Showers < %c", hname[11]);
		// lg->AddEntry(dat , text, "lep");
		lg->AddEntry(dat, legend[hname].c_str(), "lep");
	
		dat->Write();
	
		cout << "Integrated cross section " << dat->Integral() << endl;
	}

	lg->Draw();

	c->SaveAs("sp18_xs_phi_kskl_variations.png");
}
