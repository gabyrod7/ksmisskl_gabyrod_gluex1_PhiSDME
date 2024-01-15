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
	std::map<std::string, std::string> cuts_list = {{"mkskl", "mkskl > 1.005 && mkskl < 1.04"},
													{"mmiss", "missing_mass > 0.3 && missing_mass < 0.7"},
													{"mandel_t", "mandel_t < 1.5"},
													{"flight_significance", "flight_significance > 4"},
													{"chisq", "chisq_ndf < 4"},
													{"ntracks", "num_unused_tracks == 0"},
													{"nshowers", "num_unused_showers < 3"},
													{"proton_z_vertex", "proton_z_vertex > 52 && proton_z_vertex < 78"},
													{"beam_energy", "beam_energy > 8.2 && beam_energy < 8.8"}};
	string cuts = "";
	string signal = "mpipi > 0.48 && mpipi < 0.52";
	string sideband = "mpipi > 0.42 && mpipi < 0.46";

	//3.3)Now apply cuts on the newly defined variables:
	cuts = set_cuts(cuts_list, {"mkskl", ""});
	auto rdf_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"mmiss", ""});
	auto rdfMissingMass_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"chisq", ""});
	auto rdfChiSqNdf_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"flight_significance", ""});
	auto rdfFlightSignificance_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"ntracks", ""});
	auto rdfUnusedTracks_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"nshowers", ""});
	auto rdfUnusedShowers_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list, {"proton_z_vertex", ""});
	auto rdfProtonZVertex_cut = rdf_variables.Filter(cuts);

	cuts = set_cuts(cuts_list);
	auto rdfMpipi_cut = rdf_variables.Filter(cuts);

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto im_kskl = rdf_cut.Filter(signal).Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts", 110, 0.99, 1.10}, "mkskl", "accidental_weight");
	auto im_kskl_sb = rdf_cut.Filter(sideband).Histo1D({"im_kskl_sb", ";M(K_{S}K_{L});Counts", 110, 0.99, 1.10}, "mkskl", "accidental_weight");

	auto im_ksp = rdf_cut.Filter(signal).Histo1D({"im_ksp", ";M(K_{S}p);Counts", 90, 2.50, 3.4}, "mksp", "accidental_weight");
	auto im_ksp_sb = rdf_cut.Filter(sideband).Histo1D({"im_ksp_sb", ";M(K_{S}p);Counts", 90, 2.50, 3.4}, "mksp", "accidental_weight");

	auto im_klp = rdf_cut.Filter(signal).Histo1D({"im_klp", ";M(K_{L}p);Counts", 90, 2.50, 3.4}, "mklp", "accidental_weight");
	auto im_klp_sb = rdf_cut.Filter(sideband).Histo1D({"im_klp_sb", ";M(K_{L}p);Counts", 90, 2.50, 3.4}, "mklp", "accidental_weight");

	auto im_pipp = rdf_cut.Filter(signal).Histo1D({"im_pipp", ";M(#pi^{+}p);Counts", 115, 1.10, 3.40}, "mpipp", "accidental_weight");
	auto im_pipp_sb = rdf_cut.Filter(sideband).Histo1D({"im_pipp_sb", ";M(#pi^{+}p);Counts", 115, 1.10, 3.40}, "mpipp", "accidental_weight");

	auto im_pimp = rdf_cut.Filter(signal).Histo1D({"im_pimp", ";M(#pi^{-}p);Counts", 115, 1.10, 3.40}, "mpimp", "accidental_weight");
	auto im_pimp_sb = rdf_cut.Filter(sideband).Histo1D({"im_pimp_sb", ";M(#pi^{-}p);Counts", 115, 1.10, 3.40}, "mpimp", "accidental_weight");

	auto h1_mandelt = rdf_cut.Filter(signal).Histo1D({"h1_mandelt", ";-t (GeV^{2});Counts", 75, 0, 1.5}, "mandel_t", "accidental_weight");
	auto h1_mandelt_sb = rdf_cut.Filter(sideband).Histo1D({"h1_mandelt_sb", ";-t (GeV^{2});Counts", 75, 0, 1.5}, "mandel_t", "accidental_weight");

	auto h1_MissingMass = rdfMissingMass_cut.Filter(signal).Histo1D({"h1_MissingMass", ";Missing Mass (GeV);Counts",  100, 0, 1}, "missing_mass", "accidental_weight");
	auto h1_MissingMass_sb = rdfMissingMass_cut.Filter(sideband).Histo1D({"h1_MissingMass_sb", ";Missing Mass (GeV);Counts",  100, 0, 1}, "missing_mass", "accidental_weight");

	auto h1_fs = rdfFlightSignificance_cut.Filter(signal).Histo1D({"h1_FS", ";Flight Significance (#sigma);Counts",  80, 2, 10}, "fs", "accidental_weight");
	auto h1_fs_sb = rdfFlightSignificance_cut.Filter(sideband).Histo1D({"h1_FS_sb", ";Flight Significance (#sigma);Counts",  80, 2, 10}, "fs", "accidental_weight");

	auto h1_ChisqNdf = rdfChiSqNdf_cut.Filter(signal).Histo1D({"h1_ChisqNdf", ";#chi^{2}/ndf;Counts",  60, 0, 6}, "chisq_ndf", "accidental_weight");
	auto h1_ChisqNdf_sb = rdfChiSqNdf_cut.Filter(sideband).Histo1D({"h1_ChisqNdf_sb", ";#chi^{2}/ndf;Counts",  60, 0, 6}, "chisq_ndf", "accidental_weight");

	auto h1_UnusedTracks = rdfUnusedTracks_cut.Filter(signal).Histo1D({"h1_UnusedTracks", ";Number of Unused Tracks;Counts",  4, 0, 4}, "num_unused_tracks", "accidental_weight");
	auto h1_UnusedTracks_sb = rdfUnusedTracks_cut.Filter(sideband).Histo1D({"h1_UnusedTracks_sb", ";Number of Unused Tracks;Counts",  4, 0, 4}, "num_unused_tracks", "accidental_weight");

	auto h1_UnusedShowers = rdfUnusedShowers_cut.Filter(signal).Histo1D({"h1_UnusedShowers", ";Number of Unused Showers;Counts",  10, 0, 10}, "num_unused_showers", "accidental_weight");
	auto h1_UnusedShowers_sb = rdfUnusedShowers_cut.Filter(sideband).Histo1D({"h1_UnusedShowers_sb", ";Number of Unused Showers;Counts",  10, 0, 10}, "num_unused_showers", "accidental_weight");

	auto h1_ProtonZVertex = rdfProtonZVertex_cut.Filter(signal).Histo1D({"h1_ProtonZVertex", ";Proton Z vertex (cm);Counts",  75, 40, 115}, "proton_z_vertex", "accidental_weight");
	auto h1_ProtonZVertex_sb = rdfProtonZVertex_cut.Filter(sideband).Histo1D({"h1_ProtonZVertex_sb", ";Proton Z-vertex (cm);Counts",  75, 40, 115}, "proton_z_vertex", "accidental_weight");

	auto h1_Mpipi = rdfMpipi_cut.Histo1D({"h1_Mpipi", ";M(#pi^{+}#pi^{-}) (GeV);Counts",  160, 0.4, 0.56}, "mpipi", "accidental_weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: " << opf_name << endl;

	im_kskl->Write();
	im_kskl_sb->Write();

	im_ksp->Write();
	im_ksp_sb->Write();

	im_klp->Write();
	im_klp_sb->Write();

	im_pipp->Write();
	im_pipp_sb->Write();

	im_pimp->Write();
	im_pimp_sb->Write();

	h1_mandelt->Write();
	h1_mandelt_sb->Write();

	h1_MissingMass->Write();
	h1_MissingMass_sb->Write();

	h1_fs->Write();
	h1_fs_sb->Write();

	h1_ChisqNdf->Write();
	h1_ChisqNdf_sb->Write();

	h1_UnusedTracks->Write();
	h1_UnusedTracks_sb->Write();

	h1_UnusedShowers->Write();
	h1_UnusedShowers_sb->Write();

	h1_ProtonZVertex->Write();
	h1_ProtonZVertex_sb->Write();

	h1_Mpipi->Write();

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