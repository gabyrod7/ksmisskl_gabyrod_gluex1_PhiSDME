
void jpac() {
	FILE *fin = fopen("jpac.txt","r");
	TFile *opf = TFile::Open("jpac_model.root", "RECREATE");
	
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

	int nBins = 21;
	TGraphErrors	*g_rho000  = new TGraphErrors(nBins), 
			*g_rho100  = new TGraphErrors(nBins), 
			*g_rho1m10 = new TGraphErrors(nBins), 
			*g_rho111  = new TGraphErrors(nBins), 
			*g_rho001  = new TGraphErrors(nBins), 
			*g_rho101  = new TGraphErrors(nBins), 
			*g_rho1m11 = new TGraphErrors(nBins), 
			*g_rho102  = new TGraphErrors(nBins),
			*g_rho1m12 = new TGraphErrors(nBins);

	for(int i = 1; i <= nBins; i++) {
		fscanf(fin,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf \n", &t, &rho000, &rho100,  &rho1m10,   &rho111,  &rho001 ,   &rho101 ,  &rho1m11,  &rho102 ,  &rho1m12);

		g_rho000->SetPoint(i, t, rho000);
		g_rho100->SetPoint(i, t, rho100);
		g_rho1m10->SetPoint(i, t, rho1m10);
		g_rho111->SetPoint(i, t, rho111);
		g_rho001->SetPoint(i, t, rho001);
		g_rho101->SetPoint(i, t, rho101);
		g_rho1m11->SetPoint(i, t, rho1m11);
		g_rho102->SetPoint(i, t, rho102);
		g_rho1m12->SetPoint(i, t, rho1m12);
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
}
