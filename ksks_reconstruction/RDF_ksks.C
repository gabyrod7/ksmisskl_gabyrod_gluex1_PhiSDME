void RDF_ksks(Int_t n_threads,string inf_name, string opf_name, Bool_t show_cut_report) {	
	cout<<" "<< endl;
	cout<<"Run RDataFrame Analysis"<< endl;
	cout<<" "<< endl;
    
	if(n_threads > 0.0)	ROOT::EnableImplicitMT(n_threads);
	
	TStopwatch watch;
	
	watch.Reset();
	watch.Start();
	
	cout <<"Load data and set ROOT DataFrame..."<< endl;
	
	//1.) Define the chain:
	TChain my_chain("ksks");
	my_chain.Add(inf_name.c_str());
	Int_t nEvents = my_chain.GetEntries();
   	cout << "Events to process " << nEvents << endl; 

	TFile *out_file = new TFile(opf_name.c_str(),"RECREATE");

	//2.) Set the RDataFrame:
	ROOT::RDataFrame rdf(my_chain);
	
	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	cout <<"Define variables and cuts..."<< endl;
	
	//3.) Define important variables and analysis conditions
	
	//3.1) Define some variables first:
	auto rdf_variables = rdf.Define("be", "beam_energy");

//	//3.2)Now apply cuts on the newly defined variables:
//	
//	auto rdf_cut = rdf_variables.Filter("true");
//	auto rdfChiSqNdf_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && fs > 3 && mandel_t > 0.1 && mandel_t < 0.5 && num_unused_tracks == 0");
//	auto rdfFlightSignificance_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && chisq_ndf < 4 && mandel_t > 0.1 && mandel_t < 0.5 && num_unused_tracks == 0");
//	auto rdfNumUnusedTracks_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && chisq_ndf < 2 && fs > 6 && mandel_t > 0.1 && mandel_t < 0.5");
//	auto rdfNumUnusedShowers_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && chisq_ndf < 2 && fs > 6 && mandel_t > 0.1 && mandel_t < 0.5 && num_unused_tracks == 0");

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto im_ksks = rdf_variables.Filter("t > 0.1 && t < 0.5").Histo1D({"im_ksks1", ";M(K_{S}p);Counts", 100, 1.00, 2.00}, "mksks");
//	auto im_ksks = rdf_cut.Histo1D({"im_ksks", ";M(K_{S}p);Counts", 100, 1.00, 2.00}, "mksks", "Weight");
//	auto im_ksp = rdf_cut.Histo1D({"im_ksp", ";M(K_{S}p);Counts", 100, 1.00, 4.00}, "mksp", "Weight");
//	auto im_klp = rdf_cut.Histo1D({"im_klp", ";M(K_{L}p);Counts", 100, 1.00, 4.00}, "mklp", "Weight");
//	auto im_pipp = rdf_cut.Histo1D({"im_pipp", ";M(#pi^{+}p);Counts", 100, 1.00, 4.00}, "mpipp", "Weight");
//	auto im_pimp = rdf_cut.Histo1D({"im_pimp", ";M(#pi^{-}p);Counts", 100, 1.00, 4.00}, "mpimp", "Weight");
//
//	auto h2_mpipi_ChiSqNdf = rdfChiSqNdf_cut.Histo2D({"h2_mpipi_ChiSqNdf", ";M(#pi^{+}#pi^{-});#chi^{2]/ndf", 100, 0.30, 0.70, 500, 0.0, 5.0}, "mpipi", "chisq_ndf", "Weight");
//	auto h2_mpipi_FlightSignificance = rdfFlightSignificance_cut.Histo2D({"h2_mpipi_FlightSignificance", ";M(#pi^{+}#pi^{-});Flight Significance", 100, 0.30, 0.70, 180, 2.0, 20.0}, "mpipi", "fs", "Weight");
//	auto h2_mpipi_NumUnusedTracks = rdfNumUnusedTracks_cut.Histo2D({"h2_mpipi_NumUnusedTracks", ";M(#pi^{+}#pi^{-});Flight Significance", 100, 0.30, 0.70, 4, 0.0, 4.0}, "mpipi", "num_unused_tracks", "Weight");
//	auto h2_mpipi_NumUnusedShowers = rdfNumUnusedShowers_cut.Histo2D({"h2_mpipi_NumUnusedShowers", ";M(#pi^{+}#pi^{-});Flight Significance", 100, 0.30, 0.70, 10, 0.0, 10.0}, "mpipi", "num_unused_showers", "Weight");
//
//	auto h2_mkskl_mksp = rdf_cut.Histo2D({"h2_mkskl_mksp", ";M(K_{S}K_{L});M(K_{S}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mksp", "Weight");
//	auto h2_mkskl_mklp = rdf_cut.Histo2D({"h2_mkskl_mklp", ";M(K_{S}K_{L});M(K_{L}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mklp", "Weight");
//	auto h2_mkskl_mpipp = rdf_cut.Histo2D({"h2_mkskl_mpipp", ";M(K_{S}K_{L});M(#pi^{+}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mpipp", "Weight");
//	auto h2_mkskl_mpimp = rdf_cut.Histo2D({"h2_mkskl_mpimp", ";M(K_{S}K_{L});M(#pi^{-}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mpimp", "Weight");
//
//	auto h2_mkskl_coshx = rdf_cut.Histo2D({"h2_mkskl_coshx", ";M(K_{S}K_{L});cos(#theta_{hel})", 200, 0.98, 2.98, 100, -1.0, 1.0}, "mkskl", "cos_hel_ks", "Weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: " << opf_name << endl;

	im_ksks->Write();
//	im_ksp->Write();
//	im_klp->Write();
//	im_pipp->Write();
//	im_pimp->Write();
//
//	h2_mpipi_ChiSqNdf->Write();
//	h2_mpipi_FlightSignificance->Write();
//	h2_mpipi_NumUnusedTracks->Write();
//	h2_mpipi_NumUnusedShowers->Write();
//	
//	h2_mkskl_mksp->Write();
//	h2_mkskl_mklp->Write();
//	h2_mkskl_mpipp->Write();
//	h2_mkskl_mpimp->Write();
//
//	h2_mkskl_coshx->Write();

	out_file->Write();
	out_file->Close();
	
	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	watch.Stop();
	Double_t ana_time = watch.RealTime();

	if(n_threads > 0 && show_cut_report)
		cout << "Most set n_threads to 0 to view cut report" << endl;

//	if(n_threads == 0 && show_cut_report){
//		cout <<"  "<< endl;
//		cout <<"Cut Report:"<< endl;
//		auto allCutsReport = rdf_cut.Report();
//		allCutsReport->Print();
//		cout <<"  "<< endl;
//	}

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
