
void jpac() {
	gStyle->SetLineStyle(2);
	gStyle->SetLineWidth(2);
	gStyle->SetLineColor(kBlue);
	gStyle->SetMarkerStyle(0);
	gStyle->SetMarkerSize(0.0);

	FILE *fin = fopen("jpac.txt","r");
	TFile *opf = TFile::Open("phi_sdme_jpac_model.root", "RECREATE");
	
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

	int nBins = 21;
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


	for(int i = 1; i <= nBins; i++) {
		fscanf(fin,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf \n", &t, &rho000, &rho100,  &rho1m10,   &rho111,  &rho001 ,   &rho101 ,  &rho1m11,  &rho102 ,  &rho1m12);

		rho110 = 0.5*(1-rho000);

		rho11N = 0.5*(rho110 + rho1m11);
		rho00N = 0.5*(rho000 - rho001);
		rho10N = 0.5*(rho100 - rho101);
		rho1m1N = 0.5*(rho1m10 + rho111);

		rho11U = 0.5*(rho110 - rho1m11);
		rho00U = 0.5*(rho000 + rho001);
		rho10U = 0.5*(rho100 + rho101);
		rho1m1U = 0.5*(rho1m10 - rho111);

		Psigma = 2*rho1m11 - rho001;

		delta1 = rho1m11 + rho1m12;
		delta2 = rho101 + rho102;
		delta3 = rho100 + rho101;
		delta4 = rho1m10 - rho111;

		g_rho000->SetPoint(i, t, rho000);
		g_rho100->SetPoint(i, t, rho100);
		g_rho1m10->SetPoint(i, t, rho1m10);
		g_rho111->SetPoint(i, t, rho111);
		g_rho001->SetPoint(i, t, rho001);
		g_rho101->SetPoint(i, t, rho101);
		g_rho1m11->SetPoint(i, t, rho1m11);
		g_rho102->SetPoint(i, t, rho102);
		g_rho1m12->SetPoint(i, t, rho1m12);

		g_Psigma->SetPoint(i, t, Psigma);

		g_rho11N->SetPoint(i, t, rho11N);
		g_rho00N->SetPoint(i, t, rho00N);
		g_rho10N->SetPoint(i, t, rho10N);
		g_rho1m1N->SetPoint(i, t, rho1m1N);

		g_rho11U->SetPoint(i, t, rho11U);
		g_rho00U->SetPoint(i, t, rho00U);
		g_rho10U->SetPoint(i, t, rho10U);
		g_rho1m1U->SetPoint(i, t, rho1m1U);

		g_delta1->SetPoint(i, t, delta1);
		g_delta2->SetPoint(i, t, delta2);
		g_delta3->SetPoint(i, t, delta3);
		g_delta4->SetPoint(i, t, delta4);
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
