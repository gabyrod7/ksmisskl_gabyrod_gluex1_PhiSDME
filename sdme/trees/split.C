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
	int n_threads = 20;
	std::string run = "";
	std::string cuts = "";
	std::string gen_cuts = "";

	std::map<std::string, std::string> cuts_list = {{"mkskl", "mkskl > 1.005 && mkskl < 1.04"},
													{"mmiss", "missing_mass > 0.3 && missing_mass < 0.7"},
													{"mandel_t", "mandel_t < 1.5"},
													{"fs", "flight_significance > 4"},
													{"chisq", "chisq_ndf < 4"},
													{"ntracks", "num_unused_tracks == 0"},
													{"nshowers", "num_unused_showers < 3"},
													{"proton_z_vertex", "proton_z_vertex > 52 && proton_z_vertex < 78"},
													{"beam_energy", "beam_energy > 8.2 && beam_energy < 8.8"}};

	// Set nominal cuts
	cuts = set_cuts(cuts_list);
	gen_cuts = "mandel_t > 0.15 && mandel_t < 1.5";

	// Spring 2017 data for SDME
	inf_names = {"ftree_dat_sp17.root", "ftree_acc_sp17.root", "ftree_gen_sp17.root"};
	dir = "sp17";
	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// Spring 2018 data for SDME
	inf_names = {"ftree_dat_sp18.root", "ftree_acc_sp18.root", "ftree_gen_sp18.root"};	
	dir = "sp18";
	//runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// Fall 2018 data for SDME
	inf_names = {"ftree_dat_fa18.root", "ftree_acc_fa18.root", "ftree_gen_fa18.root"};	
	dir = "fa18";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	dir = "fa18_weighted";
	run = "fa18";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// GlueX-I data for SDME
	inf_names = {"ftree_dat_gluex1.root", "ftree_acc_gluex1.root", "ftree_gen_gluex1.root"};	
	dir = "gluex1";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

//	// GlueX-1 data for SDME measurement. Beam energy 8.2-8.4
//	inf_names = {"ftree_dat_gluex1.root", "ftree_acc_phi_gluex1.root", "ftree_gen_phi_gluex1.root"};	
//	dir = "sdme_gluex1_be1";
//	cuts = "&& beam_energy > 8.2 && beam_energy < 8.4 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.4 && missing_mass < 0.6 && flight_significance > 6 && chisq_ndf < 2 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// GlueX-1 data for SDME measurement. Beam energy 8.4-8.6
//	dir = "sdme_gluex1_be2";
//	cuts = "&& beam_energy > 8.4 && beam_energy < 8.6 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.4 && missing_mass < 0.6 && flight_significance > 6 && chisq_ndf < 2 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// GlueX-1 data for SDME measurement. Beam energy 8.6-8.8
//	dir = "sdme_gluex1_be3";
//	cuts = "&& beam_energy > 8.6 && beam_energy < 8.8 && mpipi > 0.48 && mpipi < 0.52 && missing_mass > 0.4 && missing_mass < 0.6 && flight_significance > 6 && chisq_ndf < 2 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

//	// GlueX-1 data for SDME measurement. mpipi 1 sigma
//	inf_names = {"ftree_dat_sp18.root", "ftree_acc_phi_gluex1.root", "ftree_gen_phi_gluex1.root"};	
//	dir = "sdme_gluex1_mpipi1sig";
//	cuts = "&& mpipi > 0.487 && mpipi < 0.507 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	gen_cuts = "";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// mpipi 3 sigma 
//	dir = "sdme_gluex1_mpipi3sig";
//	cuts = "&& mpipi > 0.467 && mpipi < 0.527 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// mpipi 4 sigma
//	dir = "sdme_gluex1_mpipi4sig";
//	cuts = "&& mpipi > 0.457 && mpipi < 0.537 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	Split("ftree_dat_sp17.root", "dat", "phi_KK", 20, "", "&& missing_mass > 0.4 && missing_mass < 0.6 && flight_significance > 6 && chisq_ndf < 2 && mandel_t > 0.20 && mandel_t < 0.50 && mkskl < 1.10");

//	// GlueX-1 data for SDME measurement. missing mass 0.45-0.55
//	inf_names = {"ftree_dat_gluex1.root", "ftree_acc_phi_gluex1.root", "ftree_gen_phi_gluex1.root"};	
//	dir = "sdme_gluex1_mmiss1";
//	cuts = "&& mpipi > 0.480 && mpipi < 0.520 && missing_mass > 0.45 && missing_mass < 0.55 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	gen_cuts = "";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// missing mass 0.3-0.7
//	dir = "sdme_gluex1_mmiss2";
//	cuts = "&& mpipi > 0.480 && mpipi < 0.520 && missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// missing mass 0.2-0.8
//	dir = "sdme_gluex1_mmiss3";
//	cuts = "&& mpipi > 0.480 && mpipi < 0.520 && missing_mass > 0.2 && missing_mass < 0.8 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 2.00 && mkskl > 1.01 && mkskl < 1.03 && Weight > 0.0";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

	// GlueX-1 data for SDME measurement. mkskl 1.010-1.030
	inf_names = {"ftree_dat_gluex1.root", "ftree_acc_gluex1.root", "ftree_gen_gluex1.root"};	
	dir = "mkskl1";
	cuts = "mkskl > 1.010 && mkskl < 1.030 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
	// gen_cuts = "";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// mkskl 1.005-1.04
	dir = "mkskl2";
	cuts = "mkskl > 1.005 && mkskl < 1.040 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// mkskl 1-1.06
	dir = "mkskl3";
	cuts = "mkskl > 1.000 && mkskl < 1.060 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// // mkskl 1.005-1.020
	// dir = "mkskl_low";
	// cuts = "&& mkskl > 1.000 && mkskl < 1.020 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
	// // mkskl 1.020-1.050
	// dir = "mkskl_high";
	// cuts = "&& mkskl > 1.020 && mkskl < 1.050 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
	// runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

//	// Spring 2017 data for SDME
//	inf_names = {"../../DSelector/ftree_acc_sdme1.root", "ftree_acc_sp17.root", "ftree_gen_sp17.root"};	
//	dir = "mc_sdme1";
//	cuts = "&& missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.5 && mkskl > 1.005 && mkskl < 1.05";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);


//	// mkskl 1.005-1.020
//	dir = "mkskl_bin1";
//	cuts = "&& mkskl > 1.000 && mkskl < 1.020 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// mkskl 1.020-1.030
//	dir = "mkskl_bin2";
//	cuts = "&& mkskl > 1.020 && mkskl < 1.030 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);
//	// mkskl 1.030-1.050
//	dir = "mkskl_bin3";
//	cuts = "&& mkskl > 1.020 && mkskl < 1.050 && missing_mass > 0.30 && missing_mass < 0.70 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.50";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

//	// GlueX-I no pipi-sideband 
//	inf_names = {"ftree_dat_gluex1.root", "ftree_acc_gluex1.root", "ftree_gen_gluex1.root"};	
//	dir = "no_sideband";
//	cuts = "&& missing_mass > 0.3 && missing_mass < 0.7 && flight_significance > 4 && chisq_ndf < 4 && num_unused_tracks == 0 && num_unused_showers < 3 && mandel_t < 1.5 && mkskl > 1.005 && mkskl < 1.05 && mpipi > 0.48 && mpipi < 0.52";
//	runSplit(inf_names, dir, n_threads, run, cuts, gen_cuts);

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

	if((dir == "sp17" || dir == "sp18" || dir == "fa18" || dir == "gluex1") && run == "")	run = dir;

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
	auto df = ROOT::RDataFrame("kskl", inf_name.c_str()).Filter(filter);

	std::cout << std::endl;
	std::cout << "We will now separate the file "+inf_name+" base on polarization angle" << std::endl;
	std::cout << "Number of entries to proccess " << *df.Count() << std::endl;

	if(verbose) {
		std::cout << n_threads << " threads used" << std::endl;
		std::cout << "Branches to save" << std::endl;
		for(auto branch : branches)	std::cout << "- " << branch << std::endl;
	}
	
	// make new data frame with cuts
	auto dat000 = df.Filter( "amptools_dat == 1 && pol_angle == 0" );
	auto dat045 = df.Filter( "amptools_dat == 1 && pol_angle == 45" );
	auto dat090 = df.Filter( "amptools_dat == 1 && pol_angle == 90" );
	auto dat135 = df.Filter( "amptools_dat == 1 && pol_angle == 135" );

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

		auto bkg000 = df.Filter("pol_angle == 0 && amptools_bkg == 1");
		auto bkg045 = df.Filter("pol_angle == 45 && amptools_bkg == 1");
		auto bkg090 = df.Filter("pol_angle == 90 && amptools_bkg == 1");
		auto bkg135 = df.Filter("pol_angle == 135 && amptools_bkg == 1");

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