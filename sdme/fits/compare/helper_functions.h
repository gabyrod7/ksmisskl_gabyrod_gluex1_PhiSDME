#ifndef helper_functions // include guard
#define helper_functions

void set_marker(TGraphErrors *g, int style, int color) {
	g->SetMarkerStyle(style);
	g->SetMarkerColor(color);

	g->SetLineColor(color);

	g->SetFillColorAlpha(color, 0.5);
	g->SetFillStyle(3001);
}

void set_marker(TGraph *g, int style, int color) {
	g->SetMarkerStyle(style);
	g->SetMarkerColor(color);
	g->SetMarkerSize(1.0);

	g->SetLineColor(color);

	g->SetFillColorAlpha(color, 0.5);
	g->SetFillStyle(3001);

	g->SetTitle("");
}

void set_line(TGraphErrors *g, int style, int color, double width) {
	g->SetLineStyle(style);
	g->SetLineColor(0);
	g->SetLineWidth(width);
	g->SetFillColorAlpha(kBlue, 0.5);
	g->SetFillStyle(3001);
}

void draw_graph(TGraphErrors *g, const char* gtitle, float xmin, float xmax, float ymin, float ymax, bool hline, float hval) {
	TH1 *frame = gPad->DrawFrame(xmin,ymin,xmax,ymax);
	frame->GetXaxis()->SetTitle("Four Momentum Transfer t (GeV^{2})");

	g->SetLineColor(0);
	g->Draw( "a2" );

	g->GetYaxis()->SetRangeUser(ymin, ymax);
	g->GetXaxis()->SetRangeUser(xmin,xmax);

	TLatex t;
	t.SetTextSize(0.12);
	if(ymax < 0)
		t.DrawLatex(0.3*xmax, ymax + (1-0.83)*(ymin - ymax), gtitle);
		// t.DrawLatex(0.7*xmax, ymax + (1-0.83)*(ymin - ymax), gtitle);
	else
		t.DrawLatex(0.3*xmax, ymin + 0.83*(ymax - ymin), gtitle);
		// t.DrawLatex(0.7*xmax, ymin + 0.83*(ymax - ymin), gtitle);

	if (hline) {
		TLine* l = new TLine(xmin, hval, xmax, hval);
		l->Draw();
	}
}

void x_shift_graph(TGraphErrors *g, double shift) {
	for(int i = 0; i < g->GetN(); i++) {
		g->SetPointX(i, g->GetPointX(i) + shift);
		g->SetPointError(i, 0, g->GetErrorY(i));
	}
}


TGraphErrors* calc_barlow(TGraphErrors *nominal, TGraphErrors *variation) {
	TGraphErrors *graph = new TGraphErrors();
	double Delta, sigma;

	for(int i = 0; i < nominal->GetN(); i++) {
		Delta = nominal->GetPointY(i) - variation->GetPointY(i);
		sigma = TMath::Sqrt( abs( nominal->GetErrorY(i)*nominal->GetErrorY(i) - variation->GetErrorY(i)*variation->GetErrorY(i) ) );
		//cout << Delta << "	" << sigma << "		" << Delta / sigma << endl;

		if(sigma != 0.0)	graph->SetPointY( i, Delta/sigma );
		else				graph->SetPointY( i, 0.0 );
		graph->SetPointX( i, nominal->GetPointX(i) );
		graph->SetPointError( i, variation->GetErrorX(i), 0 );

		// cout << i << "	" << Delta / sigma << endl;
		// cout << "	"<< sigma << endl;
	}

	return graph;
}

TGraph* calc_diff(TGraphErrors *nominal, TGraphErrors *variation) {
	TGraph* graph = new TGraph(nominal->GetN());


	for(int i = 0; i < nominal->GetN(); i++) {
		graph->SetPoint( i, nominal->GetPointX(i), nominal->GetPointY(i) - variation->GetPointY(i) );
	}

	return graph;
}

TGraphErrors* calc_pull(TGraphErrors *nominal, TGraphErrors *variation) {
	double Delta, sigma;
	TGraphErrors* graph = new TGraphErrors(nominal->GetN());

	for(int i = 0; i < nominal->GetN(); i++) {
		Delta = nominal->GetPointY(i) - variation->GetPointY(i);
		sigma = variation->GetErrorY(i);
		graph->SetPoint( i, nominal->GetPointX(i), Delta/sigma );
		graph->SetPointError( i, nominal->GetErrorX(i), 0 );
	}

	return graph;
}

TGraphErrors* calc_percent_diff(TGraphErrors *nominal, TGraphErrors *variation) {
	double Delta, sigma;
	TGraphErrors* graph = new TGraphErrors(nominal->GetN());

	for(int i = 0; i < nominal->GetN(); i++) {
		Delta = 1 - variation->GetPointY(i)/nominal->GetPointY(i);
		graph->SetPoint( i, nominal->GetPointX(i), Delta );
		graph->SetPointError( i, nominal->GetErrorX(i), 0 );
	}

	return graph;
}

double calc_chisq(TGraphErrors *nominal, TGraphErrors *variation) {
	double Delta, sigma;
	double chisq = 0;
	int ndf = nominal->GetN();

	for(int i = 0; i < ndf; i++) {
		Delta = (nominal->GetPointY(i) - variation->GetPointY(i)) * (nominal->GetPointY(i) - variation->GetPointY(i));
		sigma = nominal->GetErrorY(i)*nominal->GetErrorY(i) + variation->GetErrorY(i)*variation->GetErrorY(i);

		chisq += Delta/sigma;
	}

	return chisq;
}

#endif
