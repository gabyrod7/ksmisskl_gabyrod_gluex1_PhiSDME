#include "helper_functions.h"

void mkskl() {
	// Change default parameters to make plots pretty
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.005);
	gStyle->SetPadBottomMargin(0.11);
	gStyle->SetPadLeftMargin(0.08);

	gStyle->SetTitleBorderSize(0);
	
	gStyle->SetTitleFont(132);
	gStyle->SetTitleSize(0.05);
	gStyle->SetTitleOffset(1.2);
	
	gStyle->SetLabelSize(0.05,"XY");
	gStyle->SetLabelOffset(0.01,"XY");  
	
	gStyle->SetTitleSize(0.05,"XY");
	gStyle->SetTitleOffset(1.1,"X");
	
	gStyle->SetMarkerStyle(8);
	gStyle->SetMarkerSize(2.0);

	TFile *inf[4];
	inf[0] = TFile::Open("../gluex1/sdme.root");
	inf[1] = TFile::Open("../mkskl1/sdme.root");
	inf[2] = TFile::Open("../mkskl2/sdme.root");
	inf[3] = TFile::Open("../mkskl3/sdme.root");

	TGraphErrors *g[4][9];
	TGraph *b[4][9];
	TLatex text;
	TLegend *lg;
	TCanvas *c;
	TLine *line;
	text.SetTextSize(0.12);
	vector<string> names = {"g_rho000", "g_rho100", "g_rho1m10", "g_rho111", "g_rho001", "g_rho101", "g_rho1m11", "g_rho102", "g_rho1m12"};
	std::map<string, string> SDMEs = { {"g_rho000", "#rho_{00}^{0}"}, {"g_rho100", "Re(#rho_{10}^{0})"}, {"g_rho1m10", "#rho_{1-1}^{0}"}, {"g_rho111", "#rho_{11}^{1}"}, 
			{"g_rho001", "#rho_{00}^{1}"}, {"g_rho101", "Re(#rho_{10}^{1})"}, {"g_rho1m11", "#rho_{1-1}^{1}"}, {"g_rho102", "Im(#rho_{10}^{2})"}, {"g_rho1m12", "Im(#rho_{1-1}^{2})"}};

	c = new TCanvas("c", "c", 960, 540);
	c->Divide(3,3);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 9; j++) {
			g[i][j] = (TGraphErrors*)inf[i]->Get(names[j].c_str());

			// Format graph to look pretty
			if(i == 0)	set_marker(g[i][j], 20, 4); 
			if(i == 1)	set_marker(g[i][j], 21, 1); 
			if(i == 2)	set_marker(g[i][j], 22, 2); 
			if(i == 3)	set_marker(g[i][j], 20, 3); 

			// If points overlap to much we can shift some points to make the results more readable
			// if(i == 1)	x_shift_graph(g[i][j], -0.025);
			// if(i == 2)	x_shift_graph(g[i][j], 0.025);
		}

	c->cd(1);
	draw_graph(g[0][0], "#rho_{00}^{0}",  0.01, 1.50, -0.17, 0.17, kTRUE, 0.00);
	g[1][0]->Draw("SAME P");
	g[2][0]->Draw("SAME P");
	g[3][0]->Draw("SAME P");

	c->cd(2);
	draw_graph(g[0][1], "Re(#rho_{10}^{0})",  0.01, 1.50, -0.17, 0.17, kTRUE, 0.00);
	g[1][1]->Draw("SAME P");
	g[2][1]->Draw("SAME P");
	g[3][1]->Draw("SAME P");

	c->cd(3);
	draw_graph(g[0][2], "#rho_{1-1}^{0}", 0.01, 1.50, -0.17, 0.17, kTRUE, 0.00);
	g[1][2]->Draw("SAME P");
	g[2][2]->Draw("SAME P");
	g[3][2]->Draw("SAME P");

	c->cd(4);
	draw_graph(g[0][3], "#rho_{11}^{1}",  0.01, 1.50, -0.17, 0.17, kTRUE, 0.00);
	g[1][3]->Draw("SAME P");
	g[2][3]->Draw("SAME P");
	g[3][3]->Draw("SAME P");

	c->cd(5);
	draw_graph(g[0][4], "#rho_{00}^{1}",  0.01, 1.50, -0.17, 0.17, kTRUE, 0.00);
	g[1][4]->Draw("SAME P");
	g[2][4]->Draw("SAME P");
	g[3][4]->Draw("SAME P");

	c->cd(6);
	draw_graph(g[0][5], "Re(#rho_{10}^{1})",  0.01, 1.50, -0.17, 0.17, kTRUE, 0.00);
	g[1][5]->Draw("SAME P");
	g[2][5]->Draw("SAME P");
	g[3][5]->Draw("SAME P");

	c->cd(7);
	draw_graph(g[0][6], "#rho_{1-1}^{1}", 0.01, 1.50, 0.25, 0.75, kTRUE, 0.50);
	g[1][6]->Draw("SAME P");
	g[2][6]->Draw("SAME P");
	g[3][6]->Draw("SAME P");


	c->cd(8);
	draw_graph(g[0][7], "Im(#rho_{10}^{2})",  0.01, 1.50, -0.16, 0.16, kTRUE, 0.00);
	g[1][7]->Draw("SAME P");
	g[2][7]->Draw("SAME P");
	g[3][7]->Draw("SAME P");

	c->cd(9);
	draw_graph(g[0][8], "Im(#rho_{1-1}^{2})", 0.01, 1.50, -0.75, -0.25, kTRUE, -0.50);
	g[1][8]->Draw("SAME P");
	g[2][8]->Draw("SAME P");
	g[3][8]->Draw("SAME P");

	// Set legend
	lg = new TLegend(0.13, 0.17, 0.98, 0.37);
	lg->SetNColumns(2);
	lg->AddEntry(g[0][0], "1.005 < M(K_{S}K_{L}) < 1.050 GeV", "f");
	lg->AddEntry(g[1][0], "1.010 < M(K_{S}K_{L}) < 1.030 GeV", "lep");
	lg->AddEntry(g[2][0], "1.005 < M(K_{S}K_{L}) < 1.040 GeV", "lep");
	lg->AddEntry(g[3][0], "1.000 < M(K_{S}K_{L}) < 1.060 GeV", "lep");

	c->cd(2);
	lg->Draw();

	// Save results as pictures and root files
	c->SaveAs("sdme_mkskl.png");
	c->SaveAs("sdme_mkskl.pdf");
	TFile *opf = TFile::Open("sdme_mkskl.root", "RECREATE");
	c->Write();

	c = new TCanvas("c2", "c2", 960, 540);
	c->Divide(3,3);
	line = new TLine();
	for(int i = 0; i < 9; i++) {
		// Calculate Barlow criteria
		b[1][i] = calc_barlow(g[0][i], g[1][i]);
		b[2][i] = calc_barlow(g[0][i], g[2][i]);
		b[3][i] = calc_barlow(g[0][i], g[3][i]);

		// Make graph pretty 
		set_marker(b[1][i], 21, 1); 
		set_marker(b[2][i], 22, 2); 
		set_marker(b[3][i], 20, 3); 

		// Draw results
		c->cd(i+1);
		b[1][i]->GetYaxis()->SetRangeUser(-20, 20);
		b[1][i]->Draw( "AP" );
		b[2][i]->Draw( "P SAME" );
		b[3][i]->Draw( "P SAME" );
		line->DrawLine(0.15, 4, 1.5, 4);
		line->DrawLine(0.15, -4, 1.5, -4);
	}

	c->cd(2);
	lg = new TLegend(0.13, 0.17, 0.98, 0.37);
	lg->SetNColumns(1);
	lg->AddEntry(g[1][0], "1.010 < M(K_{S}K_{L}) < 1.030 GeV", "lep");
	lg->AddEntry(g[2][0], "1.005 < M(K_{S}K_{L}) < 1.040 GeV", "lep");
	lg->AddEntry(g[3][0], "1.000 < M(K_{S}K_{L}) < 1.060 GeV", "lep");

	c->SaveAs("barlow_mkskl.pdf");
}

