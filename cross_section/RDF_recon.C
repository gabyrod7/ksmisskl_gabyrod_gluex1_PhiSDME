void RDF_recon(Int_t n_threads,string inf_name, string opf_name, Bool_t show_cut_report) {
	cout<<" "<< endl;
	cout<<"Run RDataFrame Analysis on gp -> KsKlp data"<< endl;
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
	auto rdf_variables = rdf.Define("mkl_p4", "missing_mass");

	//3.2)Now apply cuts on the newly defined variables:
	
	//Check for energy and momentum balance:
	auto rdf_cut = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0");
	auto rdf_cut_sb = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && (mpipi > 0.42 && mpipi < 0.46) && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0");

	auto rdf_cut2 = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks <= 1");
	auto rdf_cut2_sb = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && (mpipi > 0.42 && mpipi < 0.46) && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks <= 1");

	auto rdf_cut3 = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 5 && num_unused_tracks == 0");
	auto rdf_cut3_sb = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && (mpipi > 0.42 && mpipi < 0.46) && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 5 && num_unused_tracks == 0");

	auto rdf_cut4 = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 3 && chisq_ndf < 4 && num_unused_tracks == 0");
	auto rdf_cut4_sb = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && (mpipi > 0.42 && mpipi < 0.46) && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 3 && chisq_ndf < 4 && num_unused_tracks == 0");

	auto rdf_cut5 = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.45 && missing_mass < 0.55 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0");
	auto rdf_cut5_sb = rdf_variables.Filter("mkskl > 1.01 && mkskl < 1.05 && (mpipi > 0.42 && mpipi < 0.46) && missing_mass > 0.45 && missing_mass < 0.55 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0");

	auto rdf_ShowerCut1 = rdf_cut.Filter("num_unused_showers < 1");
	auto rdf_ShowerCut1_sb = rdf_cut_sb.Filter("num_unused_showers < 1");

	auto rdf_ShowerCut2 = rdf_cut.Filter("num_unused_showers < 2");
	auto rdf_ShowerCut2_sb = rdf_cut_sb.Filter("num_unused_showers < 2");

	auto rdf_ShowerCut3 = rdf_cut.Filter("num_unused_showers < 3");
	auto rdf_ShowerCut3_sb = rdf_cut_sb.Filter("num_unused_showers < 3");

	auto rdf_ShowerCut4 = rdf_cut.Filter("num_unused_showers < 4");
	auto rdf_ShowerCut4_sb = rdf_cut_sb.Filter("num_unused_showers < 4");

	auto rdf_ShowerCut5 = rdf_cut.Filter("num_unused_showers < 5");
	auto rdf_ShowerCut5_sb = rdf_cut_sb.Filter("num_unused_showers < 5");

	auto rdf_ShowerCut6 = rdf_cut.Filter("num_unused_showers < 6");
	auto rdf_ShowerCut6_sb = rdf_cut_sb.Filter("num_unused_showers < 6");

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto h1_t = rdf_cut.Histo1D({"h1_t", ";-t (GeV^{2});Counts", 50, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_sb = rdf_cut_sb.Histo1D({"h1_t_sb", ";-t (GeV^{2});Counts", 50, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t2 = rdf_cut2.Histo1D({"h1_t2", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t2_sb = rdf_cut2_sb.Histo1D({"h1_t2_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t3 = rdf_cut3.Histo1D({"h1_t3", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t3_sb = rdf_cut3_sb.Histo1D({"h1_t3_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t4 = rdf_cut4.Histo1D({"h1_t4", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t4_sb = rdf_cut4_sb.Histo1D({"h1_t4_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t5 = rdf_cut5.Histo1D({"h1_t5", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t5_sb = rdf_cut5_sb.Histo1D({"h1_t5_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t_shower1 = rdf_ShowerCut1.Histo1D({"h1_t_shower1", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_shower1_sb = rdf_ShowerCut1_sb.Histo1D({"h1_t_shower1_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t_shower2 = rdf_ShowerCut2.Histo1D({"h1_t_shower2", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_shower2_sb = rdf_ShowerCut2_sb.Histo1D({"h1_t_shower2_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t_shower3 = rdf_ShowerCut3.Histo1D({"h1_t_shower3", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_shower3_sb = rdf_ShowerCut3_sb.Histo1D({"h1_t_shower3_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t_shower4 = rdf_ShowerCut4.Histo1D({"h1_t_shower4", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_shower4_sb = rdf_ShowerCut4_sb.Histo1D({"h1_t_shower4_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t_shower5 = rdf_ShowerCut5.Histo1D({"h1_t_shower5", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_shower5_sb = rdf_ShowerCut5_sb.Histo1D({"h1_t_shower5_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	auto h1_t_shower6 = rdf_ShowerCut6.Histo1D({"h1_t_shower6", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");
	auto h1_t_shower6_sb = rdf_ShowerCut6_sb.Histo1D({"h1_t_shower6_sb", ";-t (GeV^{2});Counts", 100, 0.00, 1.00}, "mandel_t", "accidental_weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: RDF_Ana_Results.root ..."<< endl;

	h1_t->Write();
	h1_t_sb->Write();

	h1_t2->Write();
	h1_t2_sb->Write();

	h1_t3->Write();
	h1_t3_sb->Write();

	h1_t4->Write();
	h1_t4_sb->Write();

	h1_t5->Write();
	h1_t5_sb->Write();

	h1_t_shower1->Write();
	h1_t_shower1_sb->Write();

	h1_t_shower2->Write();
	h1_t_shower2_sb->Write();

	h1_t_shower3->Write();
	h1_t_shower3_sb->Write();

	h1_t_shower4->Write();
	h1_t_shower4_sb->Write();

	h1_t_shower5->Write();
	h1_t_shower5_sb->Write();

	h1_t_shower6->Write();
	h1_t_shower6_sb->Write();

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
