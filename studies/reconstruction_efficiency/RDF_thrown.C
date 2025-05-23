void RDF_thrown(Int_t n_threads,string inf_name, string opf_name, Bool_t show_cut_report) {
	cout<<" "<< endl;
	cout<<"Run RDataFrame Analysis on subset of gp -> KsKlp Spring 2017 data"<< endl;
	cout<<" "<< endl;
    
	if(n_threads > 0.0)	ROOT::EnableImplicitMT(n_threads);
	
	TStopwatch watch;
	
	watch.Reset();
	watch.Start();
	
	cout <<"Load data and set ROOT DataFrame..."<< endl;
	
	//1.) Define the chain:
	TChain my_chain("kskl");
	my_chain.Add(inf_name.c_str());
	Int_t nEvents = my_chain.GetEntries();
   	cout << nEvents << endl; 

	TFile *out_file = new TFile(opf_name.c_str(),"RECREATE");

	// bool dIsMC = (my_chain.GetBranch("dIsMC") != NULL);

	//2.) Set the RDataFrame:
	ROOT::RDataFrame rdf(my_chain);
	
	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	cout <<"Define variables and cuts..."<< endl;
	
	//3.) Define important variables and analysis conditions
	
	//3.1) Define some variables first:
	auto rdf_variables = rdf.Define("target", "TLorentzVector(0,0,0,0.938)");

	//3.2)Now apply cuts on the newly defined variables:
	
	//Check for energy and momentum balance:
	auto rdf_cut = rdf_variables.Filter("true");
	//auto rdf_cut = rdf_variables.Filter("mandel_t > 0.1 && mandel_t < 0.5");

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto im_kskl = rdf_cut.Filter("mandel_t > 0.1 && mandel_t < 1.0 && mkskl > 1.005 && mkskl < 1.04").Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts / 1 MeV",  75, 0.98, 2.48}, "mkskl");
	// auto im_kskl2 = rdf_cut.Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts / 1 MeV",  75, 0.98, 2.48}, "mkskl");

	// auto h1_t = rdf_cut.Histo1D({"h1_t", ";M(K_{S}K_{L});Counts / 1 MeV", 50, 0.00, 1.00}, "mandel_t");
	// auto h1_t2 = rdf_cut.Histo1D({"h1_t2", ";M(K_{S}K_{L});Counts / 1 MeV", 85, 0.15, 1.00}, "mandel_t");
	//auto h1_t = rdf_cut.Filter("mkskl > 1.01 && mkskl < 1.05").Histo1D({"h1_t", ";M(K_{S}K_{L});Counts / 1 MeV", 100, 0.00, 1.00}, "mandel_t");
	//auto h1_t2 = rdf_cut.Filter("mkskl < 1.05").Histo1D({"h1_t2", ";M(K_{S}K_{L});Counts / 1 MeV", 100, 0.00, 1.00}, "mandel_t");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: RDF_Ana_Results.root ..."<< endl;

	im_kskl->Write();
	// im_kskl2->Write();

	// h1_t->Write();
	// h1_t2->Write();

	out_file->Write();
	out_file->Close();
	
	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	watch.Stop();
	Double_t ana_time = watch.RealTime();

	if(n_threads > 0 && show_cut_report)
		cout << "Most set n_threads to 0 to view cut report" << endl;

	if(n_threads == 0 && show_cut_report){
		cout <<"  "<< endl;
		cout <<"Cut Report:"<< endl;
		auto allCutsReport = rdf_cut.Report();
		allCutsReport->Print();
		cout <<"  "<< endl;
	}

	Double_t report_time = 0.0;
	TString ana_time_unit = "s";
	//----------------------------------------------
	if(ana_time < 60.0){
	    report_time = ana_time;
	}else if(ana_time >= 60.0 && ana_time < 3600.0){
	    report_time = ana_time / 60.0;
	    ana_time_unit = "min";
	}else if(ana_time >= 3600.0){
	    report_time = ana_time / 3600.0;
	    ana_time_unit = "h";
	}
	//----------------------------------------------
	
	cout <<"Processed "<<nEvents<<" events in: "<<report_time<<ana_time_unit<< endl;
	cout <<"Have a great day!"<< endl;
	cout <<" "<< endl;
}
