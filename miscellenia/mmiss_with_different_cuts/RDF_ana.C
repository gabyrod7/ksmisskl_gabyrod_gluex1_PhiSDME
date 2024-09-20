std::string set_cuts(std::map<std::string, std::string> cuts_list, std::pair<std::string, std::string> change_cut = {"", ""});

void RDF_ana(Int_t n_threads,string inf_name, string opf_name, Bool_t show_cut_report) {	
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
	auto rdf_variables = rdf.Define("fs", "flight_significance").Define("misse", "missing_p4_meas.E()").Define("mmiss", "missing_mass")
				.Define("mksp", "(ks_p4 + p_p4_kin).M()").Define("mklp", "(kl_p4 + p_p4_kin).M()")
				.Define("ks_phi", "ks_p4_cm.Phi()").Define("p_z", "p_x4_kin.Z()")
				.Define("ksphi", "ks_p4.Phi()*180/3.14159265359")
				.Define("mpipp", "(pip_p4_kin + p_p4_kin).M()").Define("mpimp", "(pim_p4_kin + p_p4_kin).M()");

	// 3.2) Make list of nominal cuts
	std::map<std::string, std::string> cuts_list = {
		{"mkskl", "mkskl > 1.005 && mkskl < 1.04"},
		// {"mmiss", "missing_mass > 0.3 && missing_mass < 0.7"},
		{"mandel_t", "mandel_t > 0.15 && mandel_t < 1.0"},
		{"flight_significance", "flight_significance > 4"},
		{"chisq", "chisq_ndf < 4"},
		{"ntracks", "num_unused_tracks == 0"},
		{"nshowers", "num_unused_showers < 3"},
		{"proton_z_vertex", "proton_z_vertex > 52 && proton_z_vertex < 78"},
		{"beam_energy", "beam_energy > 8.2 && beam_energy < 8.8"}
	};

	string cuts = "";
	string signal = "mpipi > 0.48 && mpipi < 0.52";

	//3.3)Now apply cuts on the newly defined variables:
	cuts = set_cuts(cuts_list, {"", ""});
	auto rdf_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"mmiss", "mmiss > 0.3 && mmiss < 0.7"});
	auto rdf_cut_mmiss = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"flight_significance", ""});
	auto rdf_cut_fs = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"chisq", ""});
	auto rdf_cut_chisq = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"ntracks", ""});
	auto rdf_cut_ntracks = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"nshowers", ""});
	auto rdf_cut_nshowers = rdf_variables.Filter(cuts);

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto h1_mmiss = rdf_cut.Filter(signal).Histo1D({"h1_mmiss", ";Missing Mass (GeV)", 100, 0.00, 1.00}, "mmiss", "accidental_weight");
	auto h1_mmiss_noFScut = rdf_cut_fs.Filter(signal).Histo1D({"h1_mmiss_noFScut", ";Missing Mass (GeV)", 100, 0.00, 1.00}, "mmiss", "accidental_weight");
	auto h1_mmiss_noChisqcut = rdf_cut_chisq.Filter(signal).Histo1D({"h1_mmiss_noChisqcut", ";Missing Mass (GeV)", 100, 0.00, 1.00}, "mmiss", "accidental_weight");
	auto h1_mmiss_noNtrackscut = rdf_cut_ntracks.Filter(signal).Histo1D({"h1_mmiss_noNtrackscut", ";Missing Mass (GeV)", 100, 0.00, 1.00}, "mmiss", "accidental_weight");
	auto h1_mmiss_noNshowerscut = rdf_cut_nshowers.Filter(signal).Histo1D({"h1_mmiss_noNshowerscut", ";Missing Mass (GeV)", 100, 0.00, 1.00}, "mmiss", "accidental_weight");
	auto h1_mmiss_noMpipicut = rdf_cut.Histo1D({"h1_mmiss_noMpipicut", ";Missing Mass (GeV)", 100, 0.00, 1.00}, "mmiss", "accidental_weight");

	auto h1_fs = rdf_cut_fs.Histo1D({"h1_fs", ";Flight Significance", 100, 0.0, 20.0}, "fs", "accidental_weight");
	auto h1_chisq = rdf_cut_chisq.Histo1D({"h1_chisq", ";#chi^{2}/ndf", 100, 0.0, 10.0}, "chisq_ndf", "accidental_weight");
	auto h1_ntracks = rdf_cut_ntracks.Histo1D({"h1_ntracks", ";N_{tracks}", 4, 0.0, 4.0}, "num_unused_tracks", "accidental_weight");
	auto h1_nshowers = rdf_cut_nshowers.Histo1D({"h1_nshowers", ";N_{showers}", 10, 0.0, 10.0}, "num_unused_showers", "accidental_weight");
	auto h1_mpipi = rdf_cut.Histo1D({"h1_mpipi", ";M(#pi^{+}#pi^{-}) (GeV)", 100, 0.3, 0.7}, "mpipi", "accidental_weight");

	// auto h1_fs = rdf_cut.Histo1D({"h1_fs", ";Flight Significance", 100, 0.0, 20.0}, "fs", "accidental_weight");
	// auto h1_fs_noChisqcut = rdf_cut_chisq.Histo1D({"h1_fs_noChisqcut", ";Flight Significance", 100, 0.0, 20.0}, "fs", "accidental_weight");
	// auto h1_fs_noNtrackscut = rdf_cut_ntracks.Histo1D({"h1_fs_noNtrackscut", ";Flight Significance", 100, 0.0, 20.0}, "fs", "accidental_weight");
	// auto h1_fs_noNshowerscut = rdf_cut_nshowers.Histo1D({"h1_fs_noNshowerscut", ";Flight Significance", 100, 0.0, 20.0}, "fs", "accidental_weight");
	// auto h1_fs_noMpipicut = rdf_cut.Histo1D({"h1_fs_noMpipicut", ";Flight Significance", 100, 0.0, 20.0}, "fs", "accidental_weight");


	auto h2_mpipi_mandelt = rdf_cut.Filter("missing_mass > 0.3 && missing_mass < 0.7").Histo2D({"h2_mpipi_mandelt", ";M(#pi^{+}#pi^{-}) (GeV);-t (GeV^{2})", 100, 0.40, 0.60, 17, 0.15, 1.0}, "mpipi", "mandel_t", "accidental_weight");
	auto h2_mmiss_mandelt = rdf_cut_mmiss.Filter(signal).Histo2D({"h2_mmiss_mandelt", ";Missing Mass (GeV);-t (GeV^{2})", 100, 0.00, 1.00, 17, 0.15, 1.0}, "mmiss", "mandel_t", "accidental_weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: " << opf_name << endl;

	h1_mmiss->Write();
	h1_mmiss_noFScut->Write();
	h1_mmiss_noChisqcut->Write();
	h1_mmiss_noNtrackscut->Write();
	h1_mmiss_noNshowerscut->Write();
	h1_mmiss_noMpipicut->Write();

	h1_fs->Write();
	h1_chisq->Write();
	h1_ntracks->Write();
	h1_nshowers->Write();
	h1_mpipi->Write();

	h2_mpipi_mandelt->Write();
	h2_mmiss_mandelt->Write();

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

std::string set_cuts(std::map<std::string, std::string> cuts_list, std::pair<std::string, std::string> change_cut = {"", ""}) {
	std::string cuts = "";

	for(auto it = cuts_list.begin(); it != cuts_list.end(); ++it) {
		if(it->first == change_cut.first)	{
			if(change_cut.second != "")
				cuts += change_cut.second + " && ";
			else // if change to cut is an empty string, then remove cut
				continue;
		}
		else								cuts += it->second + " && ";
	}
	cuts.erase(cuts.size()-4, 4); // remove last " && "

	return cuts;
}