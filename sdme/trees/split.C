#include "TFile.h"
#include "TROOT.h"
#include "ROOT/RDF/RFilter.hxx"
#include "ROOT/RDataFrame.hxx"

#include <vector>
#include <string>
#include <iostream>

void Split(std::string inf_name, std::string data, std::string dir, int n_threads = 4, std::string run = "", std::string filter = "", bool verbose = false);
void runSplit(std::vector<std::string> inf_names, std::string dir, int n_threads = 4, std::string run = "", std::string cuts = "", std::string gen_cuts = "", bool verbose = false);
std::string set_cuts(std::map<std::string, std::string> cuts_list, std::pair<std::string, std::string> change_cut = {"", ""});

void split() {
	std::vector<std::string> inf_names;
	std::string dir = "";
	int n_threads = 16;
	std::string run = "";
	std::string cuts = "";
	std::string gen_cuts = "";

	std::map<std::string, std::string> cuts_list = {
		{"mkskl", "mkskl > 1.005 && mkskl < 1.04"},
		{"mmiss", "missing_mass > 0.3 && missing_mass < 0.7"},
		{"mpipi" , "mpipi > 0.48 && mpipi < 0.52"},
		{"mandel_t", "mandel_t < 1.0"},
		{"fs", "flight_significance > 4"},
		{"chisq", "chisq_ndf < 4"},
		{"ntracks", "num_unused_tracks == 0"},
		{"nshowers", "num_unused_showers <= 2"},
		{"proton_z_vertex", "proton_z_vertex > 52 && proton_z_vertex < 78"},
		{"beam_energy", "beam_energy > 8.2 && beam_energy < 8.8"}
	};

	// Set nominal cuts
	cuts = set_cuts(cuts_list);
	gen_cuts = "mandel_t > 0.15 && mandel_t < 1.0";

	// Spring 2017 data for SDME
	inf_names = {"DSelector/ftree_dat_sp17.root", "DSelector/ftree_acc_sp17.root", "DSelector/ftree_gen_sp17.root"};
	dir = "sp17";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// Spring 2018 data for SDME
	inf_names = {"DSelector/ftree_dat_sp18.root", "DSelector/ftree_acc_sp18.root", "DSelector/ftree_gen_sp18.root"};	
	dir = "sp18";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// Fall 2018 data for SDME
	inf_names = {"DSelector/ftree_dat_fa18.root", "DSelector/ftree_acc_fa18.root", "DSelector/ftree_gen_fa18.root"};	
	dir = "fa18";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-I data for SDME
	inf_names = {"DSelector/ftree_dat_gluex1.root", "DSelector/ftree_acc_gluex1.root", "DSelector/ftree_gen_gluex1.root"};	
	dir = "gluex1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-I data for SDME
	inf_names = {"DSelector/ftree_dat_gluex1.root", "DSelector/ftree_acc_gluex1.root", "DSelector/ftree_gen_gluex1.root"};	
	dir = "gluex1_test";
	run = "gluex1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// Spring 2020 data for SDME
	inf_names = {"DSelector/ftree_dat_sp20.root", "DSelector/ftree_acc_sp20.root", "DSelector/ftree_gen_sp20.root"};	
	dir = "sp20";
	cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.0 && beam_energy < 8.6"});
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// MC I/O test
	inf_names = {"DSelector/ftree_acc_sdme_test.root", "DSelector/ftree_acc_sp17_Weight1.root", "DSelector/ftree_gen_sp17.root"};
	dir = "sdme_mc_test";
	run = "sp17";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	inf_names = {"DSelector/ftree_acc_sdme_test_thrown4vector.root", "DSelector/ftree_acc_sp17_Weight1.root", "DSelector/ftree_gen_sp17.root"};
	dir = "sdme_mc_test_thrown4vector";
	run = "sp17";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	inf_names = {"DSelector/ftree_acc_sdme_test_noAccidentals.root", "DSelector/ftree_acc_noAccidentals.root", "DSelector/ftree_gen_sp17.root"};
	dir = "sdme_mc_test_noAccidentals";
	run = "sp17";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	inf_names = {"DSelector/ftree_acc_sdme_test_wL1TriggerCondition.root", "DSelector/ftree_acc_sp17_Weight1_wL1TriggerCondition.root", "DSelector/ftree_gen_sp17.root"};
	dir = "sdme_mc_test_wL1TriggerCondition";
	run = "sp17";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);


	inf_names = {"DSelector/ftree_dat_gluex1.root", "DSelector/ftree_acc_gluex1_Weight1_wL1TriggerCondition.root", "DSelector/ftree_gen_gluex1.root"};
	dir = "gluex1_wL1TriggerCondition";
	run = "gluex1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// MC I/O test with background term in generated model
	inf_names = {"DSelector/ftree_acc_sdme_uniform.root", "DSelector/ftree_acc_sp17_Weight1.root", "DSelector/ftree_gen_sp17.root"};
	dir = "sdme_uniform_mc";
	run = "sp17";
	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// // GlueX-I data for SDME
	// inf_names = {"DSelector/ftree_dat_gluex1.root", "DSelector/tmp/ftree_acc_gluex1.root", "DSelector/ftree_gen_gluex1.root"};	
	// dir = "gluex1_noWeight";
	// run = "gluex1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	inf_names = {"DSelector/ftree_dat_gluex1.root", "DSelector/ftree_acc_gluex1.root", "DSelector/ftree_gen_gluex1.root"};	
	run = "gluex1";

	// GlueX-1 data for SDME measurement. Beam energy bins
	// cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.2 && beam_energy < 8.4"});
	// dir = "beam_energy_bin1";
	// // runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.4 && beam_energy < 8.6"});
	// dir = "beam_energy_bin2";
	// // runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.6 && beam_energy < 8.8"});
	// dir = "beam_energy_bin3";
	// // runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.4 && beam_energy < 8.8"});
	// dir = "beam_energy_bin4";
	// // runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.2 && beam_energy < 8.5"});
	dir = "beam_energy_bin1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"beam_energy", "beam_energy > 8.5 && beam_energy < 8.8"});
	dir = "beam_energy_bin2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-1 data for SDME measurement. KsKl invariant mass variation
	cuts = set_cuts(cuts_list, {"mkskl", "mkskl > 1.003 && mkskl < 1.042"});
	dir = "mkskl1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mkskl", "mkskl > 1.008 && mkskl < 1.039"});
	dir = "mkskl2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mkskl", "mkskl > 1.007 && mkskl < 1.038"});
	dir = "mkskl3";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-1 data for SDME measurement. missing mass variation
	cuts = set_cuts(cuts_list, {"mmiss", "missing_mass > 0.20 && missing_mass < 0.80"});
	dir = "mmiss1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mmiss", "missing_mass > 0.35 && missing_mass < 0.65"});
	dir = "mmiss2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mmiss", "missing_mass > 0.37 && missing_mass < 0.63"});
	dir = "mmiss3";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-1 data for SDME measurement. mpipi variation
	cuts = set_cuts(cuts_list, {"mpipi", "mpipi > 0.475 && mpipi < 0.525"});
	dir = "mpipi1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mpipi", "mpipi > 0.482 && mpipi < 0.518"});
	dir = "mpipi2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mpipi", "mpipi > 0.484 && mpipi < 0.516"});
	dir = "mpipi3";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-1 data for SDME measurement. KsKl invariant mass variation
	cuts = set_cuts(cuts_list, {"mkskl", "mkskl > 1.005 && mkskl < 1.02"});
	dir = "mkskl_low";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"mkskl", "mkskl > 1.02 && mkskl < 1.04"});
	dir = "mkskl_high";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-1 data for SDME measurement. flight significance variation
	cuts = set_cuts(cuts_list, {"fs", "flight_significance > 3.5"});
	dir = "fs1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"fs", "flight_significance > 4.5"});
	dir = "fs2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"fs", "flight_significance > 5.0"});
	dir = "fs3";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-I data for SDME measurement. chisq variation
	cuts = set_cuts(cuts_list, {"chisq", "chisq_ndf < 3"});
	dir = "chisq1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"chisq", "chisq_ndf < 3.5"});
	dir = "chisq2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"chisq", "chisq_ndf < 4.5"});
	dir = "chisq3";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-I data for SDME measurement. unused tracks variation
	cuts = set_cuts(cuts_list, {"ntracks", "num_unused_tracks <= 1"});
	dir = "ntracks1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"ntracks", "num_unused_tracks <= 2"});
	dir = "ntracks2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-I data for SDME measurement. unused showers variation
	cuts = set_cuts(cuts_list, {"nshowers", "num_unused_showers <= 3"});
	dir = "nshowers1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"nshowers", "num_unused_showers <= 1"});
	dir = "nshowers2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-I data for SDME measurement. proton z-vertex variation
	cuts = set_cuts(cuts_list, {"proton_z_vertex", "proton_z_vertex > 51 && proton_z_vertex < 79"});
	dir = "proton_z_vertex1";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	cuts = set_cuts(cuts_list, {"proton_z_vertex", "proton_z_vertex > 53 && proton_z_vertex < 77"});
	dir = "proton_z_vertex2";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// For Partial Wave Analysis
	inf_names = {"ftree_dat_gluex1.root", "ftree_acc_gluex1.root", "ftree_gen_gluex1.root"};	
	dir = "pwa_t_0.15_0.25_v2";
	run = "gluex1";
	cuts = "missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t > 0.15 && mandel_t < 0.25 && mkskl > 1.00 && mkskl < 1.10";
	gen_cuts = "mandel_t > 0.15 && mandel_t < 0.25";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// Spring 2017 data for SDME
	inf_names = {"ftree_dat_fa18.root", 
			"/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/DSelector/ftrees/ftree_acc_fa18_shifted_v2.root", 
			"/d/grid15/gabyrod7/analysis/ksmisskl_gabyrod_gluex1_PhiSDME/DSelector/ftrees/ftree_gen_fa18_shifted_v2.root"};
	dir = "fa18_shifted_test";
	cuts = set_cuts(cuts_list);
	run = "fa18";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
}

void runSplit(std::vector<std::string> inf_names, std::string dir, int n_threads = 4, std::string run = "", std::string cuts = "", std::string gen_cuts = "", bool verbose = false) {
	if(gSystem->AccessPathName(dir.c_str())) {
		std::cout << "Making directory called "+dir << std::endl;
		gSystem->Exec( ("mkdir "+dir+"/").c_str() );
	}

	if((dir == "sp17" || dir == "sp18" || dir == "fa18" || dir == "gluex1" || dir == "sp20") && run == "")	run = dir;

	Split(inf_names[0], "dat", dir, n_threads, run, cuts);
	Split(inf_names[1], "acc", dir, n_threads, run, cuts);
	Split(inf_names[2], "gen", dir, n_threads, run, gen_cuts);
}

void Split(std::string inf_name, std::string data, std::string dir, int n_threads = 4, std::string run = "", std::string filter = "", bool verbose = false) {
	// Parallelize with n threads
	if(n_threads > 0.0)	ROOT::EnableImplicitMT(n_threads);

	// Branches you want to save get
	std::vector<std::string> branches = {"Weight", "pol_angle", "E_Beam", "Px_Beam", "Py_Beam", "Pz_Beam", 
				"NumFinalState", "E_FinalState", "Px_FinalState", "Py_FinalState", "Pz_FinalState", "mandel_t"};

	// make data frame
	// format : tree name, file name, branches to open
	auto df = ROOT::RDataFrame("kin", inf_name.c_str()).Filter(filter);

	std::cout << std::endl;
	std::cout << "We will now separate the file "+inf_name+" base on polarization angle" << std::endl;
	std::cout << "Number of entries to proccess " << *df.Count() << std::endl;

	if(verbose) {
		std::cout << n_threads << " threads used" << std::endl;
		std::cout << "Branches to save" << std::endl;
		for(auto branch : branches)	std::cout << "- " << branch << std::endl;
	}
	
	// make new data frame with cuts
	// auto dat000 = df.Filter( "amptools_dat == 1 && pol_angle == 0" );
	// auto dat045 = df.Filter( "amptools_dat == 1 && pol_angle == 45" );
	// auto dat090 = df.Filter( "amptools_dat == 1 && pol_angle == 90" );
	// auto dat135 = df.Filter( "amptools_dat == 1 && pol_angle == 135" );
	auto dat000 = df.Filter( "is_in_time && pol_angle == 0" );
	auto dat045 = df.Filter( "is_in_time && pol_angle == 45" );
	auto dat090 = df.Filter( "is_in_time && pol_angle == 90" );
	auto dat135 = df.Filter( "is_in_time && pol_angle == 135" );

	std::cout << std::endl << "Filters have been defines next we take a Snapshot" << std::endl;

	// save falt tree with specific branches
	dat000.Snapshot("kin", (dir+"/"+data+"_"+run+"_000.root").c_str(), branches);
	dat045.Snapshot("kin", (dir+"/"+data+"_"+run+"_045.root").c_str(), branches);
	dat090.Snapshot("kin", (dir+"/"+data+"_"+run+"_090.root").c_str(), branches);
	dat135.Snapshot("kin", (dir+"/"+data+"_"+run+"_135.root").c_str(), branches);

	std::cout << std::endl << "Snapshots have completed" << std::endl;
	std::cout << "Number of entries saved " << *dat000.Count() + *dat045.Count() + *dat090.Count() + *dat135.Count() << std::endl;

	if(data == "dat") {
		std::cout << std::endl << "Proccesing background files" << std::endl;

		// auto bkg000 = df.Filter("pol_angle == 0 && amptools_bkg == 1");
		// auto bkg045 = df.Filter("pol_angle == 45 && amptools_bkg == 1");
		// auto bkg090 = df.Filter("pol_angle == 90 && amptools_bkg == 1");
		// auto bkg135 = df.Filter("pol_angle == 135 && amptools_bkg == 1");
		auto bkg000 = df.Filter("pol_angle == 0 && !is_in_time");
		auto bkg045 = df.Filter("pol_angle == 45 && !is_in_time");
		auto bkg090 = df.Filter("pol_angle == 90 && !is_in_time");
		auto bkg135 = df.Filter("pol_angle == 135 && !is_in_time");

		bkg000.Snapshot("kin", (dir+"/bkg_"+run+"_000.root").c_str(), branches);
		bkg045.Snapshot("kin", (dir+"/bkg_"+run+"_045.root").c_str(), branches);
		bkg090.Snapshot("kin", (dir+"/bkg_"+run+"_090.root").c_str(), branches);
		bkg135.Snapshot("kin", (dir+"/bkg_"+run+"_135.root").c_str(), branches);

		std::cout << std::endl << "Snapshot of background files has been taken" << std::endl;
	}
}

std::string set_cuts(std::map<std::string, std::string> cuts_list, std::pair<std::string, std::string> change_cut = {"", ""}) {
	std::string cuts = "";

	for(auto it = cuts_list.begin(); it != cuts_list.end(); ++it) {
		if(it->first == change_cut.first)	cuts += change_cut.second + " && ";
		else								cuts += it->second + " && ";
	}
	cuts.erase(cuts.size()-4, 4); // remove last " && "

	return cuts;
}
