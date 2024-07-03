void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval);

void set_marker(TGraphErrors *g, int style, int color) {
	g->SetMarkerStyle(style);
	g->SetMarkerColor(color);
	g->SetLineColor(color);
}

void set_line(TGraphErrors *g, int style, int color, double width) {
	g->SetLineStyle(style);
	g->SetLineColor(color);
	g->SetLineWidth(width);
}

void compare() {
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.01);
	gStyle->SetPadBottomMargin(0.11);
	gStyle->SetPadLeftMargin(0.07);

	gStyle->SetTitleBorderSize(0);
	
	gStyle->SetTitleFont(132);
	gStyle->SetTitleSize(0.05);
	gStyle->SetTitleOffset(1.2);
	
	gStyle->SetLabelSize(0.05,"XY");
	gStyle->SetLabelOffset(0.01,"XY");  
	
	gStyle->SetTitleSize(0.05,"XY");
	gStyle->SetTitleOffset(1.1,"X");
	
	//gStyle->SetMarkerStyle(8);
	gStyle->SetMarkerSize(2.0);

	TFile *inf[3];
	inf[0] = TFile::Open("../gluex1/sdme_bootstrap.root");
	inf[1] = TFile::Open("../kpkm/sdme.root");
	// inf[2] = TFile::Open("../sp20/sdme.root");
	inf[2] = TFile::Open("../jpac/jpac_model.root");

	TGraphErrors *g[3][9];
	vector<string> names = {"g_rho000", "g_rho100", "g_rho1m10", "g_rho111", "g_rho001", "g_rho101", "g_rho1m11", "g_rho102", "g_rho1m12"};

	double xlow = 0.01;
	double xhigh = 1.0;

	TCanvas *c = new TCanvas("c", "c", 420, 550);
	c->Divide(3,3);
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 9; j++) {
			g[i][j] = (TGraphErrors*)inf[i]->Get(names[j].c_str());

			if(i == 0)	set_marker(g[i][j], 1, 1);	// kskl channel
			if(i == 1)	set_marker(g[i][j], 1, 2);	// k+k- channel
			// if(i == 2)	set_marker(g[i][j], 1, 3);	// k+k- channel
			if(i == 2)	set_line(g[i][j], 2, 4, 3);	// jpac model
		}

	c->cd(1);
	draw_graph(g[0][0], "#rho_{00}^{0}",  xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][0]->Draw("SAME P");
	g[2][0]->Draw("SAME");

	c->cd(2);
	draw_graph(g[0][1], "Re(#rho_{10}^{0})",  xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][1]->Draw("SAME P");
	g[2][1]->Draw("SAME");

	c->cd(3);
	draw_graph(g[0][2], "#rho_{1-1}^{0}", xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][2]->Draw("SAME P");
	g[2][2]->Draw("SAME");

	c->cd(4);
	draw_graph(g[0][3], "#rho_{11}^{1}",  xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][3]->Draw("SAME P");
	g[2][3]->Draw("SAME");

	c->cd(5);
	draw_graph(g[0][4], "#rho_{00}^{1}",  xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][4]->Draw("SAME P");
	g[2][4]->Draw("SAME");

	c->cd(6);
	draw_graph(g[0][5], "Re(#rho_{10}^{1})",  xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][5]->Draw("SAME P");
	g[2][5]->Draw("SAME");

	c->cd(7);
	draw_graph(g[0][6], "#rho_{1-1}^{1}", xlow, xhigh, 0.25, 0.75, kTRUE, 0.50);
	// g[1][6]->Draw("SAME P");
	g[2][6]->Draw("SAME");


	c->cd(8);
	draw_graph(g[0][7], "Im(#rho_{10}^{2})",  xlow, xhigh, -0.15, 0.15, kTRUE, 0.00);
	// g[1][7]->Draw("SAME P");
	g[2][7]->Draw("SAME");

	c->cd(9);
	draw_graph(g[0][8], "Im(#rho_{1-1}^{2})", xlow, xhigh, -0.75, -0.25, kTRUE, -0.50);
	// g[1][8]->Draw("SAME P");
	g[2][8]->Draw("SAME");

	TLegend *lg = new TLegend(0.15, 0.17, 0.95, 0.37);
	lg->SetNColumns(4);
	lg->AddEntry(g[0][0], "K_{S}K_{L} GlueX-I", "lep");
	// lg->AddEntry(g[1][0], "K^{+}K^{-}", "lep");
	// lg->AddEntry(g[2][0], "K_{S}K_{L} 2020", "lep");
	lg->AddEntry(g[2][0], "JPAC Model", "lp");
	TLine *line = new TLine();
	lg->AddEntry(line, "SCHC", "l");

	c->cd(2);
	lg->Draw();

	c->SaveAs("sdme.png");
	c->SaveAs("sdme.pdf");
}

void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval) {
	TH1 *frame = gPad->DrawFrame(xmin,ymin,xmax,ymax);
	frame->GetXaxis()->SetTitle("Four Momentum Transfer (GeV^{2})");

	g->Draw( "P" );

	g->GetYaxis()->SetRangeUser(ymin, ymax);
	g->GetXaxis()->SetRangeUser(xmin,xmax);

	TLatex t;
	t.SetTextSize(0.12);
	//if(gtitle == "#rho_{1-1}^{1}")
	//	t.DrawLatex(0.45*xmax, 0.88*ymax, gtitle);
	//else if(ymax > 0)
	//	t.DrawLatex(0.45*xmax, 0.72*ymax, gtitle);
	//else
	//	t.DrawLatex(0.45*xmax, 1.26*ymax, gtitle);
	if(ymax < 0)
		t.DrawLatex(0.45*xmax, ymax + (1-0.83)*(ymin - ymax), gtitle);
	else
		t.DrawLatex(0.45*xmax, ymin + 0.83*(ymax - ymin), gtitle);

	if (hline) {
		TLine* l = new TLine(xmin, hval, xmax, hval);
		l->Draw();
	}
}
