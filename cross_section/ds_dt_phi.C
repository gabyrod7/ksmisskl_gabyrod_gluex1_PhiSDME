void ds_dt(string inf_dat, string inf_acc, string inf_gen, string inf_flux, string outf);

void ds_dt_phi() {
	ds_dt("hist_dat_sp17.root", "hist_acc_sp17.root", "hist_gen_sp17.root", "../flux/flux_30274_31057.root", "xs_phi_kskl_sp17");
	ds_dt("hist_dat_sp18.root", "hist_acc_sp18.root", "hist_gen_sp18.root", "../flux/flux_40856_42559.root", "xs_phi_kskl_sp18");
	ds_dt("hist_dat_fa18.root", "hist_acc_fa18.root", "hist_gen_fa18.root", "../flux/flux_50685_51768.root", "xs_phi_kskl_fa18");
	ds_dt("hist_dat_gluex1.root", "hist_acc_gluex1.root", "hist_gen_gluex1.root", "../flux/flux_gluex1.root", "xs_phi_kskl_gluex1");
}

void ds_dt(string inf_dat, string inf_acc, string inf_gen, string inf_flux, string outf) {
	gStyle->SetOptStat(0);

	TFile *inf1 = TFile::Open(inf_dat.c_str());
	TFile *inf2 = TFile::Open(inf_acc.c_str());
	TFile *inf3 = TFile::Open(inf_gen.c_str());
	TFile *inf4 = TFile::Open(inf_flux.c_str());

	TFile *opf = TFile::Open((outf+".root").c_str(), "RECREATE");

	TH1F *dat = (TH1F*)inf1->Get("h1_t");
	TH1F *bkg = (TH1F*)inf1->Get("h1_t_sb");
	TH1F *acc = (TH1F*)inf2->Get("h1_t");
	TH1F *gen = (TH1F*)inf3->Get("h1_t");
	TH1F *hflux = (TH1F*)inf4->Get("tagged_flux");
	TH1F *eff = (TH1F*)acc->Clone("eff");

	double target = 1.22e-6; // target thickness
	double br = 0.34*0.69; // branching ration, phi->KsKl br = 0.34, Ks->pi+pi- br = 0.69
	double flux = hflux->Integral();
	double Delta_t = dat->GetBinWidth(1);
	char text[100];

	TLatex t;

	cout << "Flux is " << flux << endl;

	eff->Divide(gen);
	dat->Add(bkg, -1);
	dat->Divide( eff );
	dat->Scale( 1.0/flux );
	dat->Scale( 1.0/target );
	dat->Scale( 1.0/br );
	dat->Scale( 1.0/Delta_t );

	dat->GetXaxis()->SetRangeUser(0.1, 1.0);
	dat->GetYaxis()->SetRangeUser(0.0, 1.8);

	dat->GetYaxis()->SetTitle("#frac{d#sigma}{d(-t)} (#mub/GeV^{2})");

	TCanvas *c = new TCanvas();
	eff->Draw();
	// eff->Write("efficiency");
	c->SaveAs(("figs/"+outf+"_efficiency.pdf").c_str());

	c = new TCanvas();
	dat->Draw();

//	t.DrawLatex(0.13, 1.60, "#frac{d#sigma}{d(-t)} = #frac{N}{Flux * Target Thickness * Br(#phi) * Br(K_{S}) * #Deltat}");
//	t.DrawLatex(0.4, 1.3, "Flux = 1.69407*10^{12}");
//	t.DrawLatex(0.4, 1.2, "Target Thickness = 1.22 b");
//	t.DrawLatex(0.4, 1.1, "Br(#phi #rightarrow K_{S}K_{L}) = 0.34");
//	t.DrawLatex(0.4, 0.98, "Br(K_{S} #rightarrow #pi^{+}#pi^{-}) = 0.69");
//	sprintf(text, "#Deltat = %.2f", Delta_t);
//	t.DrawLatex(0.4, 0.85, text);

	// c->SaveAs("cross_section.png");

	dat->Write();
	dat->Fit("expo");

	cout << "Integrated cross section " << dat->Integral("width") << endl;
}
