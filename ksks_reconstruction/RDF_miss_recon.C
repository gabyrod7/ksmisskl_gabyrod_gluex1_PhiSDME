void RDF_miss_recon(Int_t n_threads,string inf_name, string opf_name, Bool_t show_cut_report) {	
	cout<<" "<< endl;
	cout<<"Run RDataFrame Analysis"<< endl;
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
   	cout << "Events to process " << nEvents << endl; 

	TFile *out_file = new TFile(opf_name.c_str(),"RECREATE");

	//2.) Set the RDataFrame:
	ROOT::RDataFrame rdf(my_chain);
	
	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	cout <<"Define variables and cuts..."<< endl;
	
	//3.) Define important variables and analysis conditions
	
	//3.1) Define some variables first:
	auto rdf_variables = rdf.Define("fs", "flight_significance").Define("mmiss", "missing_mass")
				.Define("mksp", "(ks_p4 + p_p4_kin).M()").Define("mklp", "(kl_p4 + p_p4_kin).M()")
				.Define("mpipp", "(pip_p4_kin + p_p4_kin).M()").Define("mpimp", "(pim_p4_kin + p_p4_kin).M()");

	//3.2)Now apply cuts on the newly defined variables:
	
	auto rdf_cut = rdf_variables.Filter("mpipi > 0.48 && mpipi < 0.52 && mmiss > 0.4 && mmiss < 0.6 && fs > 6 && chisq_ndf < 2 && mandel_t > 0.2 && mandel_t < 1.0");
	auto rdf_pippimpippim = rdf_cut.Filter("topology == 1");
	auto rdf_pippimpi0pi0 = rdf_cut.Filter("topology == 2");
	auto rdf_0 = rdf_cut.Filter("topology == 0");

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto im_kskl = rdf_cut.Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts", 50, 1.00, 2.00}, "mkskl", "Weight");
	auto im_kskl2 = rdf_cut.Filter("num_unused_tracks == 0 && num_unused_showers < 3").Histo1D({"im_kskl_all_cuts", ";M(K_{S}K_{L});Counts", 50, 1.00, 2.00}, "mkskl", "accidental_weight");

	auto NumUnusedTracks =  rdf_cut.Histo1D({"NumUnusedTracks", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");
	auto NumUnusedShowers = rdf_cut.Histo1D({"NumUnusedShowers", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");

	auto NumUnusedTracks_charged =  rdf_pippimpippim.Histo1D({"NumUnusedTracks_charged", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");
	auto NumUnusedTracks_mixed =  rdf_pippimpi0pi0.Histo1D({"NumUnusedTracks_mixed", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");
	auto NumUnusedTracks_0 =  rdf_0.Histo1D({"NumUnusedTracks_0", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");

	auto NumUnusedShowers_charged = rdf_pippimpippim.Histo1D({"NumUnusedShowers_charged", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");
	auto NumUnusedShowers_mixed = rdf_pippimpi0pi0.Histo1D({"NumUnusedShowers_mixed", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");
	auto NumUnusedShowers_0 = rdf_0.Histo1D({"NumUnusedShowers_0", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");

	auto NumUnusedTracks_charged_showercut =  rdf_pippimpippim.Filter("num_unused_showers < 3").Histo1D({"NumUnusedTracks_charged_showercut", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");
	auto NumUnusedTracks_mixed_showercut =  rdf_pippimpi0pi0.Filter("num_unused_showers < 3").Histo1D({"NumUnusedTracks_mixed_showercut", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");
	auto NumUnusedTracks_0_showercut =  rdf_0.Filter("num_unused_showers < 3").Histo1D({"NumUnusedTracks_0_showercut", ";Number of Unused Tracks;Counts", 4, 0, 4}, "num_unused_tracks", "Weight");

	auto NumUnusedShowers_charged_trackcut = rdf_pippimpippim.Filter("num_unused_tracks == 0").Histo1D({"NumUnusedShowers_charged_trackscut", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");
	auto NumUnusedShowers_mixed_trackcut = rdf_pippimpi0pi0.Filter("num_unused_tracks == 0").Histo1D({"NumUnusedShowers_mixed_trackscut", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");
	auto NumUnusedShowers_0_trackcut = rdf_0.Filter("num_unused_tracks == 0").Histo1D({"NumUnusedShowers_0_trackscut", ";Number of Unused Showers;Counts", 10, 0, 10}, "num_unused_showers", "Weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: " << opf_name << endl;

	im_kskl->Write();
	im_kskl2->Write();

	NumUnusedTracks->Write();
	NumUnusedShowers->Write();

	NumUnusedTracks_charged->Write();
	NumUnusedTracks_mixed->Write();
	NumUnusedTracks_0->Write();

	NumUnusedShowers_charged->Write();
	NumUnusedShowers_mixed->Write();
	NumUnusedShowers_0->Write();

	NumUnusedTracks_charged_showercut->Write();
	NumUnusedTracks_mixed_showercut->Write();
	NumUnusedTracks_0_showercut->Write();

	NumUnusedShowers_charged_trackcut->Write();
	NumUnusedShowers_mixed_trackcut->Write();
	NumUnusedShowers_0_trackcut->Write();

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
