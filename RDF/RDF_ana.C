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
	auto rdf_variables = rdf.Define("fs", "flight_significance").Define("mmiss", "missing_mass").Define("misse", "missing_p4_meas.E()")
				.Define("mksp", "(ks_p4 + p_p4_kin).M()").Define("mklp", "(kl_p4 + p_p4_kin).M()")
				.Define("ks_phi", "ks_p4_cm.Phi()")
				.Define("ksphi", "ks_p4.Phi()*180/3.14159265359")
				// .Define("p_z_thrown", "p_x4_thrown.Z()")
				.Define("p_z", "p_x4_kin.Z()")
				// .Define("p_z_res", "p_x4_kin.Z() - p_x4_thrown.Z()")
				.Define("mpipp", "(pip_p4_kin + p_p4_kin).M()").Define("mpimp", "(pim_p4_kin + p_p4_kin).M()");

	//3.2)Now apply cuts on the newly defined variables:
	auto rdf_cut = rdf_variables.Filter("mpipi > 0.48 && mpipi < 0.52 && mmiss > 0.3 && mmiss < 0.7 && fs > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && p_z > 52 && p_z < 78 && mandel_t > 0.15 && mandel_t < 1.0");
	auto rdf_cut_sb = rdf_variables.Filter("((mpipi > 0.44 && mpipi < 0.46) || (mpipi > 0.54 && mpipi < 0.56)) && mmiss > 0.3 && mmiss < 0.7 && fs > 4 && chisq_ndf < 4 && mandel_t > 0.15 && mandel_t < 1.5 && num_unused_tracks == 0 && num_unused_showers < 3&& p_z > 52 && p_z < 78");
	auto rdf_cut_mmiss = rdf_variables.Filter("p_z > 52 && p_z < 78 && mpipi > 0.48 && mpipi < 0.52 && fs > 4 && chisq_ndf < 4 && mandel_t > 0.15&& mandel_t < 1.5 && num_unused_tracks == 0 && num_unused_showers < 3");
	auto rdf_cut_mmiss_sb = rdf_variables.Filter("p_z > 52 && p_z < 78 && ((mpipi > 0.44 && mpipi < 0.46) || (mpipi > 0.54 && mpipi < 0.56)) && fs > 4 && chisq_ndf < 4 && mandel_t > 0.15&& mandel_t < 1.5 && num_unused_tracks == 0 && num_unused_showers < 3");
	//auto rdf_cut = rdf_variables.Filter("(p_z > 83 && p_z < 86) && mpipi > 0.48 && mpipi < 0.52 && mmiss > 0.3 && mmiss < 0.7 && fs > 4 && chisq_ndf < 4 && mandel_t > 0.15&& mandel_t < 1.5 && num_unused_tracks == 0 && num_unused_showers < 3");
	//auto rdf_cut_sb = rdf_variables.Filter("(p_z > 83 && p_z < 86) && ((mpipi > 0.44 && mpipi < 0.46) || (mpipi > 0.54 && mpipi < 0.56)) && mmiss > 0.3 && mmiss < 0.7 && fs > 4 && chisq_ndf < 4 && mandel_t > 0.15&& mandel_t < 1.5 && num_unused_tracks == 0 && num_unused_showers < 3");
	auto rdf_cut2 = rdf_variables.Filter("mpipi > 0.48 && mpipi < 0.52 && mmiss > 0.4 && mmiss < 0.6 && fs > 6 && chisq_ndf < 2 && num_unused_tracks == 0 && num_unused_showers < 3");
	auto rdf_cut2_sb = rdf_variables.Filter("((mpipi > 0.44 && mpipi < 0.46) || (mpipi > 0.54 && mpipi < 0.56)) && mmiss > 0.4 && mmiss < 0.6 && fs > 6 && chisq_ndf < 2 && num_unused_tracks == 0 && num_unused_showers < 3");
	auto rdf_cut3 = rdf_variables.Filter("mmiss > 0.3 && mmiss < 0.7 && fs > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t > 0.15 && mandel_t < 1.5");
	auto rdfChiSqNdf_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && fs > 3 && mandel_t > 0.1 && mandel_t < 0.5 && num_unused_tracks == 0");
	auto rdfFlightSignificance_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && chisq_ndf < 4 && mandel_t > 0.1 && mandel_t < 0.5 && num_unused_tracks == 0");
	auto rdfNumUnusedTracks_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && chisq_ndf < 2 && fs > 6 && mandel_t > 0.1 && mandel_t < 0.5");
	auto rdfNumUnusedShowers_cut = rdf_variables.Filter("mmiss > 0.4 && mmiss < 0.6 && chisq_ndf < 2 && fs > 6 && mandel_t > 0.1 && mandel_t < 0.5 && num_unused_tracks == 0");
	auto rdfProtonZ_cut = rdf_variables.Filter("mpipi > 0.48 && mpipi < 0.52 && mmiss > 0.3 && mmiss < 0.7 && fs > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t > 0.15 && mandel_t < 1.5");

	cout <<"...done!"<< endl;
	cout <<" "<< endl;
	
	//4.) Define Histograms:
	
	cout <<"Set up histograms..."<< endl;
	
	//4.1) Histograms
	auto im_kskl = rdf_cut.Histo1D({"im_kskl", ";M(K_{S}K_{L});Counts", 110, 0.99, 1.10}, "mkskl", "accidental_weight");
	auto im_ksp = rdf_cut.Histo1D({"im_ksp", ";M(K_{S}p);Counts", 110, 2.50, 3.40}, "mksp", "accidental_weight");
	auto im_klp = rdf_cut.Histo1D({"im_klp", ";M(K_{L}p);Counts", 110, 2.50, 3.40}, "mklp", "accidental_weight");
	auto im_pipp = rdf_cut.Histo1D({"im_pipp", ";M(#pi^{+}p);Counts", 100, 1.00, 4.00}, "mpipp", "accidental_weight");
	auto im_pimp = rdf_cut.Histo1D({"im_pimp", ";M(#pi^{-}p);Counts", 100, 1.00, 4.00}, "mpimp", "accidental_weight");
	auto im_miss = rdf_cut_mmiss.Histo1D({"im_miss", ";Missing Mass (GeV);Counts", 100, 0.00, 1.00}, "mmiss", "accidental_weight");
	auto im_pipi = rdf_cut3.Filter("mkskl > 1.005 & mkskl < 1.05").Histo1D({"im_pipi", ";M(#pi#pi) (GeV);Counts", 150, 0.40, 0.55}, "mpipi", "accidental_weight");

	auto im_kskl_sb = rdf_cut_sb.Histo1D({"im_kskl_sb", ";M(K_{S}K_{L});Counts", 110, 0.99, 1.10}, "mkskl", "accidental_weight");
	auto im_ksp_sb = rdf_cut_sb.Histo1D({"im_ksp_sb", ";M(K_{S}p);Counts", 110, 2.50, 3.40}, "mksp", "accidental_weight");
	auto im_klp_sb = rdf_cut_sb.Histo1D({"im_klp_sb", ";M(K_{L}p);Counts", 110, 2.50, 3.40}, "mklp", "accidental_weight");
	auto im_pipp_sb = rdf_cut_sb.Histo1D({"im_pipp_sb", ";M(#pi^{+}p);Counts", 100, 1.00, 4.00}, "mpipp", "accidental_weight");
	auto im_pimp_sb = rdf_cut_sb.Histo1D({"im_pimp_sb", ";M(#pi^{-}p);Counts", 100, 1.00, 4.00}, "mpimp", "accidental_weight");
	auto im_miss_sb = rdf_cut_mmiss_sb.Histo1D({"im_miss_sb", ";Missing Mass (GeV);Counts", 100, 0.00, 1.00}, "mmiss", "accidental_weight");

	auto h1_p_z = rdf_cut.Histo1D({"h1_p_z", ";recoil proton Z (cm);Counts", 100, 0.00, 100.00}, "p_z", "accidental_weight");
	auto h1_p_z_sb = rdf_cut_sb.Histo1D({"h1_p_z_sb", ";recoil proton Z (cm);Counts", 100, 0.00, 100.00}, "p_z", "accidental_weight");

	auto h1_t = rdf_cut2.Histo1D({"h1_t", ";-t;Counts",  100, 0, 1}, "mandel_t", "accidental_weight");
	auto h1_t_sb = rdf_cut2_sb.Histo1D({"h1_t_sb", ";-t;Counts",  100, 0, 1}, "mandel_t", "accidental_weight");

	auto h1_t2 = rdf_variables.Filter("missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.5 && mkskl > 1.005 && mkskl < 1.05 && amptools_dat == 1").Histo1D({"h1_t2", ";-t;Counts",  100, 0, 1}, "mandel_t", "Weight");
	auto h1_t_sb2 = rdf_variables.Filter("missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.5 && mkskl > 1.005 && mkskl < 1.05 && amptools_bkg == 1").Histo1D({"h1_t_sb2", ";-t;Counts",  100, 0, 1}, "mandel_t", "Weight");

	auto h2_mpipi_t = rdf_cut3.Histo2D({"h2_mpipi_t", ";M(#pi#pi);-t;Counts",  100, 0.4, 0.6, 150, 0, 1.5}, "mpipi", "mandel_t", "accidental_weight");

	auto h1_path_length = rdf_cut2.Histo1D({"h1_path_length", ";Path Length;Counts",  100, 0, 100}, "path_length", "accidental_weight");
	auto h1_path_length_sb = rdf_cut2_sb.Histo1D({"h1_path_length", ";Path Length;Counts",  100, 0, 100}, "path_length", "accidental_weight");

	auto h1_ksphi = rdf_cut2.Histo1D({"h1_ksphi", ";-t;Counts",  180, -3.14, 3.14}, "ks_phi", "accidental_weight");
	auto h1_ksphi_sb = rdf_cut2_sb.Histo1D({"h1_ksphi_sb", ";-t;Counts",  180, -3.14, 3.14}, "ks_phi", "accidental_weight");

	auto h1_protonZ = rdfProtonZ_cut.Histo1D({"h1_protonZ", ";Recoil proton Z (cm);Counts", 100, 0, 100}, "p_z", "accidental_weight");
	// auto h1_protonZthrown = rdfProtonZ_cut.Histo1D({"h1_protonZthrown", ";Recoil proton Z (cm);Counts", 100, 0, 100}, "p_z_thrown", "accidental_weight");
	// auto h1_protonZres = rdfProtonZ_cut.Histo1D({"h1_protonZres", ";Recoil proton Z (cm);Counts", 100, -1, 1}, "p_z_res", "accidental_weight");

	auto h2_mpipi_ChiSqNdf = rdfChiSqNdf_cut.Histo2D({"h2_mpipi_ChiSqNdf", ";M(#pi^{+}#pi^{-});#chi^{2]/ndf", 100, 0.30, 0.70, 500, 0.0, 5.0}, "mpipi", "chisq_ndf", "accidental_weight");
	auto h2_mpipi_FlightSignificance = rdfFlightSignificance_cut.Histo2D({"h2_mpipi_FlightSignificance", ";M(#pi^{+}#pi^{-});Flight Significance", 100, 0.30, 0.70, 180, 2.0, 20.0}, "mpipi", "fs", "accidental_weight");
	auto h2_mpipi_NumUnusedTracks = rdfNumUnusedTracks_cut.Histo2D({"h2_mpipi_NumUnusedTracks", ";M(#pi^{+}#pi^{-});Flight Significance", 100, 0.30, 0.70, 4, 0.0, 4.0}, "mpipi", "num_unused_tracks", "accidental_weight");
	auto h2_mpipi_NumUnusedShowers = rdfNumUnusedShowers_cut.Histo2D({"h2_mpipi_NumUnusedShowers", ";M(#pi^{+}#pi^{-});Flight Significance", 100, 0.30, 0.70, 10, 0.0, 10.0}, "mpipi", "num_unused_showers", "accidental_weight");

	auto h2_mkskl_mksp = rdf_cut.Histo2D({"h2_mkskl_mksp", ";M(K_{S}K_{L});M(K_{S}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mksp", "accidental_weight");
	auto h2_mkskl_mklp = rdf_cut.Histo2D({"h2_mkskl_mklp", ";M(K_{S}K_{L});M(K_{L}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mklp", "accidental_weight");
	auto h2_mkskl_mpipp = rdf_cut.Histo2D({"h2_mkskl_mpipp", ";M(K_{S}K_{L});M(#pi^{+}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mpipp", "accidental_weight");
	auto h2_mkskl_mpimp = rdf_cut.Histo2D({"h2_mkskl_mpimp", ";M(K_{S}K_{L});M(#pi^{-}p)", 200, 0.98, 2.98, 100, 1.0, 4.0}, "mkskl", "mpimp", "accidental_weight");

	auto h2_mkskl_coshx = rdf_cut.Histo2D({"h2_mkskl_coshx", ";M(K_{S}K_{L});cos(#theta_{hel})", 120, 0.98, 1.10, 100, -1.0, 1.0}, "mkskl", "cos_hel_ks", "accidental_weight");
	auto h2_mkskl_mandelt = rdf_cut.Histo2D({"h2_mkskl_mandelt", ";M(K_{S}K_{L});-t (GeV^{2})", 60, 0.98, 1.10, 50, 0.15, 1.5}, "mkskl", "mandel_t", "accidental_weight");

	auto h2_ksmass_ksphi = rdf_cut3.Histo2D({"h2_ksmass_ksphi", ";M(#pi#pi);#phi", 100, 0.4, 0.6, 90, -180, 180}, "mpipi", "ksphi", "accidental_weight");
	auto h2_ksmass_ksphi1 = rdf_cut3.Filter("pol_angle == 0").Histo2D({"h2_ksmass_ksphi1", ";M(#pi#pi);#phi", 100, 0.4, 0.6, 90, -180, 180}, "mpipi", "ksphi", "accidental_weight");
	auto h2_ksmass_ksphi2 = rdf_cut3.Filter("pol_angle == 45").Histo2D({"h2_ksmass_ksphi2", ";M(#pi#pi);#phi", 100, 0.4, 0.6, 90, -180, 180}, "mpipi", "ksphi", "accidental_weight");
	auto h2_ksmass_ksphi3 = rdf_cut3.Filter("pol_angle == 90").Histo2D({"h2_ksmass_ksphi3", ";M(#pi#pi);#phi", 100, 0.4, 0.6, 90, -180, 180}, "mpipi", "ksphi", "accidental_weight");
	auto h2_ksmass_ksphi4 = rdf_cut3.Filter("pol_angle == 135").Histo2D({"h2_ksmass_ksphi4", ";M(#pi#pi);#phi", 100, 0.4, 0.6, 90, -180, 180}, "mpipi", "ksphi", "accidental_weight");
	auto h2_mkskl_ksphi = rdf_cut.Histo2D({"h2_mkskl_ksphi", ";M(K_{S}K_{L});#phi", 100, 0.98, 1.10, 40, -180, 180}, "mkskl", "ksphi", "accidental_weight");

	cout <<" "<< endl;
	
	//5.) Write everything to a file:
	cout <<"Write results to file: " << opf_name << endl;

	im_kskl->Write();
	im_ksp->Write();
	im_klp->Write();
	im_pipp->Write();
	im_pimp->Write();
	im_miss->Write();
	im_pipi->Write();

	im_kskl_sb->Write();
	im_ksp_sb->Write();
	im_klp_sb->Write();
	im_pipp_sb->Write();
	im_pimp_sb->Write();
	im_miss_sb->Write();

	h1_p_z->Write();
	h1_p_z_sb->Write();

	h1_t->Write();
	h1_t_sb->Write();

	h1_t2->Write();
	h1_t_sb2->Write();

	h2_mpipi_t->Write();

	h1_path_length->Write();
	h1_path_length_sb->Write();

	h1_ksphi->Write();
	h1_ksphi_sb->Write();

	h1_protonZ->Write();
	// h1_protonZthrown->Write();
	// h1_protonZres->Write();

	h2_mpipi_ChiSqNdf->Write();
	h2_mpipi_FlightSignificance->Write();
	h2_mpipi_NumUnusedTracks->Write();
	h2_mpipi_NumUnusedShowers->Write();
	
	h2_mkskl_mksp->Write();
	h2_mkskl_mklp->Write();
	h2_mkskl_mpipp->Write();
	h2_mkskl_mpimp->Write();

	h2_mkskl_coshx->Write();
	h2_mkskl_mandelt->Write();

	h2_ksmass_ksphi->Write();
	h2_ksmass_ksphi1->Write();
	h2_ksmass_ksphi2->Write();
	h2_ksmass_ksphi3->Write();
	h2_ksmass_ksphi4->Write();
	h2_mkskl_ksphi->Write();

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
