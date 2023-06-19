#include "helper_functions.h"
//void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval);
//
//void set_marker(TGraphErrors *g, int style, int color) {
//	g->SetMarkerStyle(style);
//	g->SetLineColor(color);
//	g->SetMarkerColor(color);
//}
//
//void set_line(TGraphErrors *g, int style, int color, double width) {
//	g->SetLineStyle(style);
//	g->SetLineColor(0);
//	g->SetLineWidth(width);
//	g->SetFillColorAlpha(kBlue, 0.5);
//	g->SetFillStyle(3001);
//}
//void calc(TGraphErrors *nominal, TGraphErrors *variation) {
//	double Delta, sigma;
//
//	for(int i = 0; i < nominal->GetN(); i++) {
//		//cout << "nomina = " << nominal->GetPointY(i) << endl;
//		Delta = nominal->GetPointY(i) - variation->GetPointY(i);
//		sigma = TMath::Sqrt( abs( nominal->GetErrorY(i)*nominal->GetErrorY(i) + variation->GetErrorY(i)*variation->GetErrorY(i) ) );
//		//cout << i << "	" << Delta << "	" << sigma << "		" << Delta / sigma << endl;
//		variation->SetPointY( i, Delta/sigma );
//		variation->SetPointX( i, nominal->GetPointX(i) );
//	}
//}

void run_periods() {
	gStyle->SetPadTopMargin(0.03);
	gStyle->SetPadRightMargin(0.001);
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
	inf[1] = TFile::Open("../sp17/sdme.root");
	inf[2] = TFile::Open("../sp18/sdme.root");
	inf[3] = TFile::Open("../fa18/sdme.root");
	//inf[3] = TFile::Open("../april_4/sdme.root");

	TGraphErrors *g[4][9];
	TGraphErrors *b[4][9];
	TLatex text;
	text.SetTextSize(0.12);
	vector<string> names = {"g_rho000", "g_rho100", "g_rho1m10", "g_rho111", "g_rho001", "g_rho101", "g_rho1m11", "g_rho102", "g_rho1m12"};
	std::map<string, string> SDMEs = { {"g_rho000", "#rho_{00}^{0}"}, {"g_rho100", "Re(#rho_{10}^{0})"}, {"g_rho1m10", "#rho_{1-1}^{0}"}, {"g_rho111", "#rho_{11}^{1}"}, 
			{"g_rho001", "#rho_{00}^{1}"}, {"g_rho101", "Re(#rho_{10}^{1})"}, {"g_rho1m11", "#rho_{1-1}^{1}"}, {"g_rho102", "Im(#rho_{10}^{2})"}, {"g_rho1m12", "Im(#rho_{1-1}^{2})"}};

	TCanvas *c = new TCanvas("c", "c", 960, 540);
	c->Divide(3,3);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 9; j++) {
			g[i][j] = (TGraphErrors*)inf[i]->Get(names[j].c_str());

			if(i == 1)	set_marker(g[i][j], 20, 1);	// 
			if(i == 2)	set_marker(g[i][j], 21, 2);	// 
			if(i == 3)	set_marker(g[i][j], 22, 3);	// 
			if(i == 0)	set_line(g[i][j], 2, 4, 3);	// 
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

	TLegend *lg = new TLegend(0.15, 0.17, 0.95, 0.37);
	lg->SetNColumns(4);
	lg->AddEntry(g[0][0], "GlueX-I", "f");
	lg->AddEntry(g[1][0], "Spring 2017", "lep");
	lg->AddEntry(g[2][0], "Spring 2018", "lep");
	lg->AddEntry(g[3][0], "Fall 2018", "lep");

	c->cd(2);
	lg->Draw();

	c->SaveAs("sdme_RunPeriod.png");
	c->SaveAs("sdme_RunPeriod.pdf");

	double chisq_sp17 = 0;
	double chisq_sp18 = 0;
	double chisq_fa18 = 0;

	TLine *line = new TLine();
	for(int i = 0; i < 9; i++) {
		chisq_sp17 += calc_chisq(g[0][i], g[1][i]);
		chisq_sp18 += calc_chisq(g[0][i], g[2][i]);
		chisq_fa18 += calc_chisq(g[0][i], g[3][i]);
		cout << "Spring 2017 "+names[i] << "	" << calc_chisq(g[0][i], g[1][i])/9 << endl;
		cout << "Spring 2018 "+names[i] << "	" << calc_chisq(g[0][i], g[2][i])/9 << endl;
		cout << "Fall 2018 "+names[i] << "	" << calc_chisq(g[0][i], g[3][i])/9 << endl;

		//cout << names[i] << endl;
		calc_pull(g[0][i], g[1][i]);
		calc_pull(g[0][i], g[2][i]);
		calc_pull(g[0][i], g[3][i]);

		c->cd(i+1);
		g[1][i]->GetYaxis()->SetRangeUser(-6 , 6 );
		g[1][i]->Draw( "AP" );
		g[2][i]->Draw( "P SAME" );
		g[3][i]->Draw( "P SAME" );
		line->SetLineStyle(1);
		line->DrawLine(0.15, 2, 1.5, 2);
		line->DrawLine(0.15, -2, 1.5, -2);
		line->SetLineStyle(2);
		line->DrawLine(0.15, 3, 1.5, 3);
		line->DrawLine(0.15, -3, 1.5, -3);
		text.DrawLatex(0.45*1.5,  4 , SDMEs[names[i]].c_str());
		//text.DrawLatex(0.05*1.5,  4 , "Pull");
		//text.DrawLatex(0.80*1.5, -5 , "-t (GeV^{2})");
	}

	c->cd(2);
	lg = new TLegend(0.15, 0.17, 0.95, 0.30);
	lg->SetNColumns(3);
	lg->AddEntry(g[1][0], "Spring 2017", "lep");
	lg->AddEntry(g[2][0], "Spring 2018", "lep");
	lg->AddEntry(g[3][0], "Fall 2018", "lep");
	lg->Draw();

	c->SaveAs("pull_RunPeriod.pdf");

	cout << "Spring 2017 reduced chi^2 = " << chisq_sp17/81 << endl;
	cout << "Spring 2018 reduced chi^2 = " << chisq_sp18/81 << endl;
	cout << "Fall 2018 reduced chi^2 = " << chisq_fa18/81 << endl;
}

//void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval) {
//	TH1 *frame = gPad->DrawFrame(xmin,ymin,xmax,ymax);
//	frame->GetXaxis()->SetTitle("Four Momentum Transfer t (GeV^{2})");
//
//	g->Draw( "a3" );
//
//	g->GetYaxis()->SetRangeUser(ymin, ymax);
//	g->GetXaxis()->SetRangeUser(xmin,xmax);
//
//	TLatex t;
//	t.SetTextSize(0.12);
//	if(ymax < 0)
//		t.DrawLatex(0.45*xmax, ymax + (1-0.83)*(ymin - ymax), gtitle);
//	else
//		t.DrawLatex(0.45*xmax, ymin + 0.83*(ymax - ymin), gtitle);
//
//	if (hline) {
//		TLine* l = new TLine(xmin, hval, xmax, hval);
//		l->Draw();
//	}
//}
