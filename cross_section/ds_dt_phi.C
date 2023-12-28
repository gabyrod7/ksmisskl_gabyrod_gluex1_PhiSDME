void ds_dt(string inf_dat, string inf_acc, string inf_gen, string inf_flux, string outf);

void ds_dt_phi() {
	ds_dt("hist_dat_sp17.root", "hist_acc_sp17.root", "hist_gen_sp17.root", "../flux/flux_30274_31057.root", "xs_phi_kskl_sp17");
	ds_dt("hist_dat_sp18.root", "hist_acc_sp18.root", "hist_gen_sp18.root", "../flux/flux_40856_42559.root", "xs_phi_kskl_sp18");
	ds_dt("hist_dat_fa18.root", "hist_acc_fa18.root", "hist_gen_fa18.root", "../flux/flux_50685_51768.root", "xs_phi_kskl_fa18");
	ds_dt("hist_dat_gluex1.root", "hist_acc_gluex1.root", "hist_gen_gluex1.root", "../flux/flux_gluex1.root", "xs_phi_kskl_gluex1");
}

void ds_dt(string inf_dat, string inf_acc, string inf_gen, string inf_flux, string outf) {
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadBottomMargin(0.11);
	gStyle->SetPadLeftMargin(0.11);

	gStyle->SetTitleBorderSize(0);
	
	gStyle->SetTitleFont(132);
	gStyle->SetTitleSize(0.05);
	gStyle->SetTitleOffset(1.2);
	
	gStyle->SetLabelSize(0.05,"XY");
	gStyle->SetLabelOffset(0.01,"XY");  
	
	gStyle->SetTitleSize(0.05,"XY");
	gStyle->SetTitleOffset(1.1,"X");
	
	gStyle->SetMarkerStyle(8);
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

	double target = 1.22e-9; // target thickness
	double br = 0.34*0.69; // branching ration, phi->KsKl br = 0.34, Ks->pi+pi- br = 0.69
	double flux = hflux->Integral();
	double Delta_t = dat->GetBinWidth(1);
	char text[100];

	TLatex t;

	cout << "Flux is " << flux << endl;
	cout << "yield " << dat->Integral() << endl;

	eff->Divide(gen);
	dat->Add(bkg, -1);
	dat->Divide( eff );
	dat->Scale( 1.0/flux );
	dat->Scale( 1.0/target );
	dat->Scale( 1.0/br );
	dat->Scale( 1.0/Delta_t );

	eff->GetYaxis()->SetTitle("Efiiciency");
	eff->GetXaxis()->SetRangeUser(0.15, 1.0);
	eff->GetYaxis()->SetRangeUser(0, 1.2*eff->GetMaximum());
	eff->SetMarkerStyle(8);

	dat->GetXaxis()->SetRangeUser(0.15, 1.0);
	dat->GetYaxis()->SetRangeUser(0.0, 1500);
	dat->SetMarkerStyle(8);

	dat->GetYaxis()->SetTitle("#frac{d#sigma}{d(-t)} (nb/GeV^{2})");

	TCanvas *c = new TCanvas();
	eff->Draw();
	// eff->Write("efficiency");
	c->SaveAs(("figs/"+outf+"_efficiency.pdf").c_str());

	c = new TCanvas();
	dat->Draw();

	// t.DrawLatex(0.17, 1.60, "#frac{d#sigma}{d(-t)} = #frac{N}{Flux * Target Thickness * Br(#phi) * Br(K_{S}) * #Deltat}");
	// t.DrawLatex(0.4, 1.3, "Flux = 1.69407*10^{12}");
	// t.DrawLatex(0.4, 1.2, "Target Thickness = 1.22 b");
	// t.DrawLatex(0.4, 1.1, "Br(#phi #rightarrow K_{S}K_{L}) = 0.34");
	// t.DrawLatex(0.4, 0.98, "Br(K_{S} #rightarrow #pi^{+}#pi^{-}) = 0.69");

	dat->Write();
	// dat->Fit("expo");

	double integral, error;

	integral = dat->IntegralAndError(dat->GetXaxis()->FindBin(0.2), dat->GetXaxis()->FindBin(0.8), error, "width");
	cout << integral << " +/- " << error << endl;
	integral = dat->IntegralAndError(dat->GetXaxis()->FindBin(0.15), dat->GetXaxis()->FindBin(1.0), error, "width");
	cout << integral << " +/- " << error << endl;

	sprintf(text, "#int#frac{d#sigma}{d(-t)} d(-t) = %.1f #pm %.1f nb", integral, error);
	t.DrawLatex(0.5, 1200, text);
	// sprintf(text, "#int#frac{d#sigma}{d(-t)} d(-t) = %.1f #pm %.1f nb", dat->GetFunction("expo")->Integral(0.15, 1.0), dat->GetFunction("expo")->IntegralError(0.15, 1.0));
	// t.DrawLatex(0.5, 1200, text);
	// sprintf(text, "#chi^{2}/ndf = %.1f/%d = %.1f", dat->GetFunction("expo")->GetChisquare(), dat->GetFunction("expo")->GetNDF(), dat->GetFunction("expo")->GetChisquare()/dat->GetFunction("expo")->GetNDF());
	// t.DrawLatex(0.5, 1000, text);

	c->SaveAs(("figs/"+outf+".pdf").c_str());

}
