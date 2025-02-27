void set_graph_point(TGraphErrors *g, int n, double x, double ex, double y, double ey);

void plot_slac_results(string filename = "slac_9.3GeV.csv") {
	gStyle->SetMarkerStyle(0);
	gStyle->SetMarkerSize(0.0);
	gStyle->SetLineColor(kGreen+2);
	gStyle->SetMarkerColor(kGreen+2);

	FILE *fin = fopen(filename.c_str(),"r");
	TFile *opf = TFile::Open("sdme_slac_9.3GeV.root", "RECREATE");
	
	double t;
	double te;
	double rho000;
	double rho000e;
	double rho100;
	double rho100e;
	double rho1m10;
	double rho1m10e;
	double rho111;
	double rho111e;
	double rho001;
	double rho001e;
	double rho101;
	double rho101e;
	double rho1m11;
	double rho1m11e;
	double rho102;
	double rho102e;
	double rho1m12;
	double rho1m12e;
	double rho110; // = 0.5*(1-rho000) because trace of rho^0 matrix is 1
	double rho110e;
	double Psigma;
	double Psigmae;
	double rho11N;
	double rho00N;
	double rho10N;
	double rho1m1N;
	double rho11U;
	double rho00U;
	double rho10U;
	double rho1m1U;
	double delta1;
	double delta2;
	double delta3;
	double delta4;

	int nBins = 1;
	TGraphErrors	*g_rho000  = new TGraphErrors(nBins), 
			*g_rho100  = new TGraphErrors(nBins), 
			*g_rho1m10 = new TGraphErrors(nBins), 
			*g_rho111  = new TGraphErrors(nBins), 
			*g_rho001  = new TGraphErrors(nBins), 
			*g_rho101  = new TGraphErrors(nBins), 
			*g_rho1m11 = new TGraphErrors(nBins), 
			*g_rho102  = new TGraphErrors(nBins),
			*g_rho1m12 = new TGraphErrors(nBins),
			*g_Psigma  = new TGraphErrors(nBins),
			*g_rho11N = new TGraphErrors(nBins),
			*g_rho00N = new TGraphErrors(nBins),
			*g_rho10N = new TGraphErrors(nBins),
			*g_rho1m1N = new TGraphErrors(nBins),
			*g_rho11U = new TGraphErrors(nBins),
			*g_rho00U = new TGraphErrors(nBins),
			*g_rho10U = new TGraphErrors(nBins),
			*g_rho1m1U = new TGraphErrors(nBins),
			*g_delta1 = new TGraphErrors(nBins),
			*g_delta2 = new TGraphErrors(nBins),
			*g_delta3 = new TGraphErrors(nBins),
			*g_delta4 = new TGraphErrors(nBins);


	for(int i = 0; i < nBins; i++) {
		fscanf(fin,"%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf \n", &t, &te, &rho000, &rho000e, &rho100,  &rho100e,  &rho1m10,  &rho1m10e, &rho001 ,  &rho001e, &rho111,  &rho111e,  &rho101 ,  &rho101e, &rho1m11 ,  &rho1m11e ,  &rho102 ,  &rho102e ,  &rho1m12 ,  &rho1m12e, &Psigma, &Psigmae);
		cout << t << "	" << te << endl;
		cout << rho000 << "	" << rho000e << endl;
		cout << rho100 << "	" << rho100e << endl;
		cout << rho1m10 << "	" << rho1m10e << endl;
		cout << rho111 << "	" << rho111e << endl;
		cout << rho001 << "	" << rho001e << endl;
		cout << rho101 << "	" << rho101e << endl;
		cout << rho1m11 << "	" << rho1m11e << endl;
		cout << rho102 << "	" << rho102e << endl;
		cout << rho1m12 << "	" << rho1m12e << endl;
		cout << Psigma << "	" << Psigmae << endl;

		rho110 = 0.5*(1-rho000);

		rho11N = 0.5*(rho110 + rho1m11);
		rho00N = 0.5*(rho000 - rho001);
		rho10N = 0.5*(rho100 - rho101);
		rho1m1N = 0.5*(rho1m10 + rho111);

		rho11U = 0.5*(rho110 - rho1m11);
		rho00U = 0.5*(rho000 + rho001);
		rho10U = 0.5*(rho100 + rho101);
		rho1m1U = 0.5*(rho1m10 - rho111);

		// Psigma = 2*rho1m11 - rho001;

		delta1 = rho1m11 + rho1m12;
		delta2 = rho101 + rho102;
		delta3 = rho100 + rho101;
		delta4 = rho1m10 - rho111;

		// g_rho000->SetPoint(i, t, rho000);
		// g_rho000->SetPointError(i, te, rho000e);
		// g_rho100->SetPoint(i, t, rho100);
		// g_rho100->SetPointError(i, te, rho100e);
		// g_rho1m10->SetPoint(i, t, rho1m10);
		// g_rho1m10->SetPointError(i, te, rho1m10e);
		// g_rho111->SetPoint(i, t, rho111);
		// g_rho111->SetPointError(i, te, rho111e);
		// g_rho001->SetPoint(i, t, rho001);
		// g_rho001->SetPointError(i, te, rho001e);
		// g_rho101->SetPoint(i, t, rho101);
		// g_rho101->SetPointError(i, te, rho101e);
		// g_rho1m11->SetPoint(i, t, rho1m11);
		// g_rho1m11->SetPointError(i, te, rho1m11e);
		// g_rho102->SetPoint(i, t, rho102);
		// g_rho102->SetPointError(i, te, rho102e);
		// g_rho1m12->SetPoint(i, t, rho1m12);
		// g_rho1m12->SetPointError(i, te, rho1m12e);

		// g_Psigma->SetPoint(i, t, Psigma);
		// g_Psigma->SetPointError(i, te, Psigmae);

		// g_rho11N->SetPoint(i, t, rho11N);
		// g_rho00N->SetPoint(i, t, rho00N);
		// g_rho10N->SetPoint(i, t, rho10N);
		// g_rho1m1N->SetPoint(i, t, rho1m1N);

		// g_rho11U->SetPoint(i, t, rho11U);
		// g_rho00U->SetPoint(i, t, rho00U);
		// g_rho10U->SetPoint(i, t, rho10U);
		// g_rho1m1U->SetPoint(i, t, rho1m1U);

		// g_delta1->SetPoint(i, t, delta1);
		// g_delta2->SetPoint(i, t, delta2);
		// g_delta3->SetPoint(i, t, delta3);
		// g_delta4->SetPoint(i, t, delta4);

		set_graph_point(g_rho000, i, t, te, rho000, rho000e);
		set_graph_point(g_rho100, i, t, te, rho100, rho100e);
		set_graph_point(g_rho1m10, i, t, te, rho1m10, rho1m10e);
		set_graph_point(g_rho111, i, t, te, rho111, rho111e);
		set_graph_point(g_rho001, i, t, te, rho001, rho001e);
		set_graph_point(g_rho101, i, t, te, rho101, rho101e);
		set_graph_point(g_rho1m11, i, t, te, rho1m11, rho1m11e);
		set_graph_point(g_rho102, i, t, te, rho102, rho102e);
		set_graph_point(g_rho1m12, i, t, te, rho1m12, rho1m12e);

        set_graph_point(g_Psigma, i, t, te, 2*rho1m11 - rho001, sqrt(4*rho1m11e*rho1m11e + rho001e*rho001e));

        set_graph_point(g_rho00N, i, t, te, 0.5*(rho000 - rho001), sqrt(rho000e*rho000e + rho001e*rho001e));
        set_graph_point(g_rho10N, i, t, te, 0.5*(rho100 - rho101), sqrt(rho100e*rho100e + rho101e*rho101e));
        set_graph_point(g_rho1m1N, i, t, te, 0.5*(rho1m10 + rho111), sqrt(rho1m10e*rho1m10e + rho111e*rho111e));
        set_graph_point(g_rho11N, i, t, te, 0.5*(0.5*(1-rho000) + rho1m11), sqrt(0.25*rho000e*rho000e + rho1m11e*rho1m11e));

        set_graph_point(g_rho00U, i, t, te, 0.5*(rho000 + rho001), sqrt(rho000e*rho000e + rho001e*rho001e));
        set_graph_point(g_rho10U, i, t, te, 0.5*(rho100 + rho101), sqrt(rho100e*rho100e + rho101e*rho101e));
        set_graph_point(g_rho1m1U, i, t, te, 0.5*(rho1m10 - rho111), sqrt(rho1m10e*rho1m10e + rho111e*rho111e));
        set_graph_point(g_rho11U, i, t, te, 0.5*(0.5*(1-rho000) - rho1m11), sqrt(0.25*rho000e*rho000e + rho1m11e*rho1m11e));

        set_graph_point(g_delta1, i, t, te, rho1m11 + rho1m12, sqrt(rho1m11e*rho1m11e + rho1m12e*rho1m12e));
        set_graph_point(g_delta2, i, t, te, rho101 + rho102, sqrt(rho101e*rho101e + rho102e*rho102e));
        set_graph_point(g_delta3, i, t, te, rho100 + rho101, sqrt(rho100e*rho100e + rho101e*rho101e));
        set_graph_point(g_delta4, i, t, te, rho1m10 - rho111, sqrt(rho1m10e*rho1m10e + rho111e*rho111e));

	}

	g_rho000->Write("g_rho000");
	g_rho100->Write("g_rho100");
	g_rho1m10->Write("g_rho1m10");
	g_rho111->Write("g_rho111");
	g_rho001->Write("g_rho001");
	g_rho101->Write("g_rho101");
	g_rho1m11->Write("g_rho1m11");
	g_rho102->Write("g_rho102");
	g_rho1m12->Write("g_rho1m12");

	g_Psigma->Write("g_Psigma");

	g_rho11N->Write("g_rho11N");
	g_rho00N->Write("g_rho00N");
	g_rho10N->Write("g_rho10N");
	g_rho1m1N->Write("g_rho1m1N");

	g_rho11U->Write("g_rho11U");
	g_rho00U->Write("g_rho00U");
	g_rho10U->Write("g_rho10U");
	g_rho1m1U->Write("g_rho1m1U");

	g_delta1->Write("g_delta1");
	g_delta2->Write("g_delta2");
	g_delta3->Write("g_delta3");
	g_delta4->Write("g_delta4");
}

void set_graph_point(TGraphErrors *g, int n, double x, double ex, double y, double ey) {
	g->SetPoint(n, x, y);
	g->SetPointError(n, ex, ey);
}
