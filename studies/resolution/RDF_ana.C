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
				.Define("mksp2", "(ks_p4 + p_p4_kin).M2()").Define("mklp2", "(kl_p4 + p_p4_kin).M2()")
				.Define("ks_phi", "ks_p4_cm.Phi()").Define("p_z", "p_x4_kin.Z()")
				.Define("ksphi", "ks_p4.Phi()*180/3.14159265359")
				.Define("mpipp", "(pip_p4_kin + p_p4_kin).M()").Define("mpimp", "(pim_p4_kin + p_p4_kin).M()");

	// 3.2) Make list of nominal cuts
	std::map<std::string, std::string> cuts_list = {
		{"mkskl", "mkskl > 1.005 && mkskl < 1.04"},
		{"mmiss", "missing_mass > 0.3 && missing_mass < 0.7"},
		{"mandel_t", "mandel_t < 1.5"},
		{"flight_significance", "flight_significance > 4"},
		{"chisq", "chisq_ndf < 4"},
		{"ntracks", "num_unused_tracks == 0"},
		{"nshowers", "num_unused_showers < 3"},
		{"proton_z_vertex", "proton_z_vertex > 52 && proton_z_vertex < 78"},
		{"beam_energy", "beam_energy > 8.2 && beam_energy < 8.8"}
	};

	string cuts = "";
	string signal = "mpipi > 0.48 && mpipi < 0.52";
	string sideband = "mpipi > 0.42 && mpipi < 0.46";

	//3.3)Now apply cuts on the newly defined variables:
	cuts = set_cuts(cuts_list, {"mkskl", ""});
	auto rdf_cut = rdf_variables.Filter(cuts);

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	// auto im_kskl = rdf_cut.Filter(signal).Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts", 110, 0.99, 1.10}, "mkskl", "accidental_weight");
	// auto im_kskl_sb = rdf_cut.Filter(sideband).Histo1D({"im_kskl_sb", ";M(K_{S}K_{L});Counts", 110, 0.99, 1.10}, "mkskl", "accidental_weight");
	auto im_kskl = rdf_cut.Filter(signal).Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts", 130, 0.97, 1.10}, "mkskl", "accidental_weight");
	auto im_kskl_sb = rdf_cut.Filter(sideband).Histo1D({"im_kskl_sb", ";M(K_{S}K_{L});Counts", 130, 0.97, 1.10}, "mkskl", "accidental_weight");

	auto res_pippim_vertex = rdf_cut.Filter(signal).Histo1D({"res_kshort_vertex", ";K_{S} Vertex [Recon - Thrown] (cm);Counts", 200, -10, 10}, "pippim_res", "accidental_weight");
	auto res_recoilp_vertex = rdf_cut.Filter(signal).Histo1D({"res_recoilp_vertex", ";Recoil Proton Vertex [Recon - Thrown] (cm);Counts", 80, -4, 4}, "recoilp_res", "accidental_weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: " << opf_name << endl;

	im_kskl->Write();
	im_kskl_sb->Write();

	res_pippim_vertex->Write();
	res_recoilp_vertex->Write();

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