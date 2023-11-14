// #include "helper_functions.h"
void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval);

void set_marker(TGraphErrors *g, int style, int color) {
//	g->SetMarkerStyle(style);
	g->SetMarkerColor(color);
	g->SetLineColor(color);
	g->SetMarkerSize(0);
}

void set_line(TGraphErrors *g, int style, int color, double width) {
	g->SetLineStyle(style);
	g->SetLineColor(color);
	g->SetLineWidth(width);
	g->SetFillColor(4);
	g->SetFillStyle(3001);
}

void nominal_bootstrap() {
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
	
//	gStyle->SetMarkerStyle(8);
	gStyle->SetMarkerSize(0.01);

	TFile *inf[2];
	inf[0] = TFile::Open("../gluex1/sdme_bootstrap.root");
	inf[1] = TFile::Open("../gluex1/sdme_nominal.root");

	TGraphErrors *g[4][9];
	vector<string> names = {"g_rho000", "g_rho100", "g_rho1m10", "g_rho111", "g_rho001", "g_rho101", "g_rho1m11", "g_rho102", "g_rho1m12"};

	TCanvas *c = new TCanvas();
	c->Divide(3,3);
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 9; j++) {
			g[i][j] = (TGraphErrors*)inf[i]->Get(names[j].c_str());

//			c->cd(j+1);
//			if(i == 0)	g[i][j]->Draw("AP");
//			else		g[i][j]->Draw("P SAME");

			if(i == 0)	set_marker(g[i][j], 20, 1);	// 
			if(i == 1)	set_marker(g[i][j], 21, 2);	// 
		}

	c->cd(1);
	draw_graph(g[0][0], "#rho_{00}^{0}",  0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][0]->Draw("SAME P");

	c->cd(2);
	draw_graph(g[0][1], "Re(#rho_{10}^{0})",  0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][1]->Draw("SAME P");

	c->cd(3);
	draw_graph(g[0][2], "#rho_{1-1}^{0}", 0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][2]->Draw("SAME P");

	c->cd(4);
	draw_graph(g[0][3], "#rho_{11}^{1}",  0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][3]->Draw("SAME P");

	c->cd(5);
	draw_graph(g[0][4], "#rho_{00}^{1}",  0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][4]->Draw("SAME P");

	c->cd(6);
	draw_graph(g[0][5], "Re(#rho_{10}^{1})",  0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][5]->Draw("SAME P");

	c->cd(7);
	draw_graph(g[0][6], "#rho_{1-1}^{1}", 0.1, 1.00, 0.35, 0.65, kTRUE, 0.50);
	g[1][6]->Draw("SAME P");


	c->cd(8);
	draw_graph(g[0][7], "Im(#rho_{10}^{2})",  0.1, 1.00, -0.10, 0.10, kTRUE, 0.00);
	g[1][7]->Draw("SAME P");

	c->cd(9);
	draw_graph(g[0][8], "Im(#rho_{1-1}^{2})", 0.1, 1.00, -0.65, -0.35, kTRUE, -0.50);
	g[1][8]->Draw("SAME ");

	TLegend *lg = new TLegend(0.15, 0.17, 0.95, 0.37);
	lg->SetNColumns(4);
	lg->AddEntry(g[0][0], "Bootstrap", "lep");
	lg->AddEntry(g[1][0], "Nominal", "lep");
	//TLine *line = new TLine();
	//lg->AddEntry(line, "SCHC", "l");

	c->cd(2);
	lg->Draw();

	c->SaveAs("pngs/sdme_bootstrap.png");
	c->SaveAs("pdfs/sdme_bootstrap.pdf");
}

void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval) {
	TH1 *frame = gPad->DrawFrame(xmin,ymin,xmax,ymax);
	frame->GetXaxis()->SetTitle("Four Momentum Transfer t (GeV^{2})");

	g->Draw( "P" );

	g->GetYaxis()->SetRangeUser(ymin, ymax);
	g->GetXaxis()->SetRangeUser(xmin,xmax);

	TLatex t;
	t.SetTextSize(0.12);
	if(ymax < 0)
		t.DrawLatex(0.3*xmax, ymax + (1-0.83)*(ymin - ymax), gtitle);
	else
		t.DrawLatex(0.3*xmax, ymin + 0.83*(ymax - ymin), gtitle);


	if (hline) {
		TLine* l = new TLine(xmin, hval, xmax, hval);
		l->Draw();
	}
}


// void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval) {
// 	TH1 *frame = gPad->DrawFrame(xmin,ymin,xmax,ymax);
// 	frame->GetXaxis()->SetTitle("Four Momentum Transfer t (GeV^{2})");

// 	g->SetLineColor(0);
// 	g->Draw( "P" );

// 	g->GetYaxis()->SetRangeUser(ymin, ymax);
// 	g->GetXaxis()->SetRangeUser(xmin,xmax);

// 	TLatex t;
// 	t.SetTextSize(0.12);
// 	if(ymax < 0)
// 		t.DrawLatex(0.7*xmax, ymax + (1-0.83)*(ymin - ymax), gtitle);
// 	else
// 		t.DrawLatex(0.7*xmax, ymin + 0.83*(ymax - ymin), gtitle);

// 	if (hline) {
// 		TLine* l = new TLine(xmin, hval, xmax, hval);
// 		l->Draw();
// 	}
// }
