#include "DSelector_kskl_M16.h"
//
TVector3 calc_helicity_angles(TLorentzVector beam, TLorentzVector recoil, TLorentzVector p1, TLorentzVector p2) {
	TLorentzVector resonance = p1 + p2;
	
	TLorentzRotation resRestBoost( -resonance.BoostVector() );
	
	TLorentzVector beam_res   = resRestBoost * beam;
	TLorentzVector recoil_res = resRestBoost * recoil;
	TLorentzVector p1_res = resRestBoost * p1;

	// Helicity frame
	TVector3 z = -1. * recoil_res.Vect().Unit();
	
	// normal to the production plane
	TVector3 y = (beam.Vect().Unit().Cross(-recoil.Vect().Unit())).Unit();
	
	TVector3 x = y.Cross(z);
	
	TVector3 angles( (p1_res.Vect()).Dot(x),
	(p1_res.Vect()).Dot(y),
	(p1_res.Vect()).Dot(z) );
	

	return angles;
}

TVector3 calc_GJ_angles(TLorentzVector beam, TLorentzVector recoil, TLorentzVector p1, TLorentzVector p2) {
	TLorentzVector resonance = p1 + p2;
	
	TLorentzRotation resRestBoost( -resonance.BoostVector() );
	
	TLorentzVector beam_res   = resRestBoost * beam;
	TLorentzVector recoil_res = resRestBoost * recoil;
	TLorentzVector p1_res = resRestBoost * p1;

	// GJ frame
	TVector3 z = beam_res.Vect().Unit();
	
	// normal to the production plane
	TVector3 y = (beam.Vect().Unit().Cross(-recoil.Vect().Unit())).Unit();
	
	TVector3 x = y.Cross(z);
	
	TVector3 angles( (p1_res.Vect()).Dot(x),
	(p1_res.Vect()).Dot(y),
	(p1_res.Vect()).Dot(z) );
	
	return angles;
}

double calc_vanHove_X(double p1, double p2, double p3) {
	double q = TMath::Sqrt(p1*p1 + p2*p2 + p3*p3);
	double omega = TMath::ATan2( -1*TMath::Sqrt(3.)*p3, 2*p1 + p3) + TMath::Pi();

	return q*TMath::Cos(omega);
}

double calc_vanHove_Y(double p1, double p2, double p3) {
	double q = TMath::Sqrt(p1*p1 + p2*p2 + p3*p3);
	double omega = TMath::ATan2( -1*TMath::Sqrt(3.)*p3, 2*p1 + p3) + TMath::Pi();

	return q*TMath::Sin(omega);

}

void DSelector_kskl_M16::Init(TTree *locTree)
{
	// USERS: IN THIS FUNCTION, ONLY MODIFY SECTIONS WITH A "USER" OR "EXAMPLE" LABEL. LEAVE THE REST ALONE.

	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//USERS: SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "kskl_M16.root"; //"" for none
	dOutputTreeFileName = ""; //"" for none
	dFlatTreeFileName = "flat_tree_M16.root"; //output flat tree (one combo per tree entry), "" for none
	dFlatTreeName = "kskl"; //if blank, default name will be chosen
	//dSaveDefaultFlatBranches = true; // False: don't save default branches, reduce disk footprint.

	//Because this function gets called for each TTree in the TChain, we must be careful:
		//We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	Get_ComboWrappers();
	dPreviousRunNumber = 0;

	/*********************************** EXAMPLE USER INITIALIZATION: ANALYSIS ACTIONS **********************************/

	// EXAMPLE: Create deque for histogramming particle masses:
	// // For histogramming the phi mass in phi -> K+ K-
	// // Be sure to change this and dAnalyzeCutActions to match reaction
	std::deque<Particle_t> MyPhi;
	MyPhi.push_back(KPlus); MyPhi.push_back(KMinus);

	//ANALYSIS ACTIONS: //Executed in order if added to dAnalysisActions
	//false/true below: use measured/kinfit data

	//PID
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false));
	//below: value: +/- N ns, Unknown: All PIDs, SYS_NULL: all timing systems
	//dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.5, KPlus, SYS_BCAL));

	//PIDFOM (for charged tracks)
	dAnalysisActions.push_back(new DHistogramAction_PIDFOM(dComboWrapper));
	//dAnalysisActions.push_back(new DCutAction_PIDFOM(dComboWrapper, KPlus, 0.1));
	//dAnalysisActions.push_back(new DCutAction_EachPIDFOM(dComboWrapper, 0.1));

	//MASSES
	//dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, false, Lambda, 1000, 1.0, 1.2, "Lambda"));
	//dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 1000, -0.1, 0.1));

	//KINFIT RESULTS
	dAnalysisActions.push_back(new DHistogramAction_KinFitResults(dComboWrapper));

	//CUT MISSING MASS
	//dAnalysisActions.push_back(new DCutAction_MissingMassSquared(dComboWrapper, false, -0.03, 0.02));

	//CUT ON SHOWER QUALITY
	//dAnalysisActions.push_back(new DCutAction_ShowerQuality(dComboWrapper, SYS_FCAL, 0.5));

	//BEAM ENERGY
	dAnalysisActions.push_back(new DHistogramAction_BeamEnergy(dComboWrapper, false));
	//dAnalysisActions.push_back(new DCutAction_BeamEnergy(dComboWrapper, false, 8.2, 8.8));  // Coherent peak for runs in the range 30000-59999

	//KINEMATICS
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, false));

	// ANALYZE CUT ACTIONS
	// // Change MyPhi to match reaction
	dAnalyzeCutActions = new DHistogramAction_AnalyzeCutActions( dAnalysisActions, dComboWrapper, false, 0, MyPhi, 1000, 0.9, 2.4, "CutActionEffect" );

	//INITIALIZE ACTIONS
	//If you create any actions that you want to run manually (i.e. don't add to dAnalysisActions), be sure to initialize them here as well
	Initialize_Actions();
	dAnalyzeCutActions->Initialize(); // manual action, must call Initialize()

	/******************************** EXAMPLE USER INITIALIZATION: STAND-ALONE HISTOGRAMS *******************************/

//	//EXAMPLE MANUAL HISTOGRAMS:
//	dHist_MissingMassSquared = new TH1F("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 600, -0.06, 0.06);
//	dHist_BeamEnergy = new TH1F("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);
//
//	dHist_RFTime = new TH1F("RFTime", "; RF Time (ns)", 500, -20.0, 20.0);
//	dHist_RFTimeMeasured = new TH1F("RFTime_Measured", "; RF Time (ns)", 500, -20.0, 20.0);

	/************************** EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - MAIN TREE *************************/

	//EXAMPLE MAIN TREE CUSTOM BRANCHES (OUTPUT ROOT FILE NAME MUST FIRST BE GIVEN!!!! (ABOVE: TOP)):
	//The type for the branch must be included in the brackets
	//1st function argument is the name of the branch
	//2nd function argument is the name of the branch that contains the size of the array (for fundamentals only)
	/*
	dTreeInterface->Create_Branch_Fundamental<Int_t>("my_int"); //fundamental = char, int, float, double, etc.
	dTreeInterface->Create_Branch_FundamentalArray<Int_t>("my_int_array", "my_int");
	dTreeInterface->Create_Branch_FundamentalArray<Float_t>("my_combo_array", "NumCombos");
	dTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("my_p4");
	dTreeInterface->Create_Branch_ClonesArray<TLorentzVector>("my_p4_array");
	*/

	/************************** EXAMPLE USER INITIALIZATION: CUSTOM OUTPUT BRANCHES - FLAT TREE *************************/

	//EXAMPLE FLAT TREE CUSTOM BRANCHES (OUTPUT ROOT FILE NAME MUST FIRST BE GIVEN!!!! (ABOVE: TOP)):
	//The type for the branch must be included in the brackets
	//1st function argument is the name of the branch
	//2nd function argument is the name of the branch that contains the size of the array (for fundamentals only)
	/*
	dFlatTreeInterface->Create_Branch_Fundamental<Int_t>("flat_my_int"); //fundamental = char, int, float, double, etc.
	dFlatTreeInterface->Create_Branch_FundamentalArray<Int_t>("flat_my_int_array", "flat_my_int");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("flat_my_p4");
	dFlatTreeInterface->Create_Branch_ClonesArray<TLorentzVector>("flat_my_p4_array");
	*/

	dIsMC = (dTreeInterface->Get_Branch("MCWeight") != NULL);
	if(dIsMC)	dFlatTreeInterface->Create_Branch_Fundamental<bool>("dIsMC");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("event_weight");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("accidental_weight");

//	dFlatTreeInterface->Create_Branch_Fundamental<int>("num_charged_hypo");
	dFlatTreeInterface->Create_Branch_Fundamental<int>("num_unused_tracks");
	dFlatTreeInterface->Create_Branch_Fundamental<int>("num_unused_showers");
	dFlatTreeInterface->Create_Branch_Fundamental<int>("num_combos");

	dFlatTreeInterface->Create_Branch_Fundamental<int>("topology");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("mpipi");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("missing_mass");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("mkskl");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("beam_energy");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("mandel_t");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("ks_proper_time");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("flight_significance");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("chisq_ndf");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("cos_hel_ks");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("phi_hel_ks");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("cos_gj_ks");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("phi_gj_ks");

	dFlatTreeInterface->Create_Branch_Fundamental<double>("vanHove_x");
	dFlatTreeInterface->Create_Branch_Fundamental<double>("vanHove_y");

//	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pip_p4");
//	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pim_p4");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("ks_p4");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("kl_p4");

//	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pip_p4_meas");
//	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pim_p4_meas");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("ks_p4_meas");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("missing_p4_meas");

	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pip_p4_cm");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pim_p4_cm");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("ks_p4_cm");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("kl_p4_cm");
	dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("recoil_p4_cm");

	// For AmpTools
	dFlatTreeInterface->Create_Branch_Fundamental<bool>("amptools_dat");
	dFlatTreeInterface->Create_Branch_Fundamental<bool>("amptools_bkg");
	SetupAmpTools_FlatTree();

	dFlatTreeInterface->Create_Branch_Fundamental<Float_t>("Target_Mass"); // necesary for divideData.pl (I think)
	dFlatTreeInterface->Create_Branch_FundamentalArray<Int_t>("PID_FinalState","NumFinalState");
	dFlatTreeInterface->Create_Branch_Fundamental<int>("pol_angle");

	/************************************* ADVANCED EXAMPLE: CHOOSE BRANCHES TO READ ************************************/

	//TO SAVE PROCESSING TIME
		//If you know you don't need all of the branches/data, but just a subset of it, you can speed things up
		//By default, for each event, the data is retrieved for all branches
		//If you know you only need data for some branches, you can skip grabbing data from the branches you don't need
		//Do this by doing something similar to the commented code below

//	dTreeInterface->Clear_GetEntryBranches(); //now get none
//	dTreeInterface->Register_GetEntryBranch("RunNumber"); 
//	dTreeInterface->Register_GetEntryBranch("EventNumber"); 
//	dTreeInterface->Register_GetEntryBranch("NumCombos"); 
//	dTreeInterface->Register_GetEntryBranch("RFTime_Measured");
//	dTreeInterface->Register_GetEntryBranch("IsComboCut"); 
//	dTreeInterface->Register_GetEntryBranch("Proton__P4_KinFit"); 
//	dTreeInterface->Register_GetEntryBranch("Proton__X4_KinFit"); 
//	dTreeInterface->Register_GetEntryBranch("MissingKLong__P4_KinFit");
//	dTreeInterface->Register_GetEntryBranch("DecayingKShort_X4"); 
//	dTreeInterface->Register_GetEntryBranch("DecayingKShort_PathLengthSigma");
//	dTreeInterface->Register_GetEntryBranch("PiMinus__P4_KinFit");  
//	dTreeInterface->Register_GetEntryBranch("PiMinus__X4_KinFit");  
//	dTreeInterface->Register_GetEntryBranch("PiPlus__P4_KinFit");
//	dTreeInterface->Register_GetEntryBranch("PiPlus__X4_KinFit");

	/************************************** DETERMINE IF ANALYZING SIMULATED DATA *************************************/

//	dIsMC = (dTreeInterface->Get_Branch("MCWeight") != NULL);

}

Bool_t DSelector_kskl_M16::Process(Long64_t locEntry)
{
	// The Process() function is called for each entry in the tree. The entry argument
	// specifies which entry in the currently loaded tree is to be processed.
	//
	// This function should contain the "body" of the analysis. It can contain
	// simple or elaborate selection criteria, run algorithms on the data
	// of the event and typically fill histograms.
	//
	// The processing can be stopped by calling Abort().
	// Use fStatus to set the return value of TTree::Process().
	// The return value is currently not used.

	//CALL THIS FIRST
	DSelector::Process(locEntry); //Gets the data from the tree for the entry
	//cout << "RUN " << Get_RunNumber() << ", EVENT " << Get_EventNumber() << endl;
	//TLorentzVector locProductionX4 = Get_X4_Production();

	/******************************************** GET POLARIZATION ORIENTATION ******************************************/

	//Only if the run number changes
	//RCDB environment must be setup in order for this to work! (Will return false otherwise)
	UInt_t locRunNumber = Get_RunNumber();
	if(locRunNumber != dPreviousRunNumber)
	{
		hasPolarizationAngle = dAnalysisUtilities.Get_PolarizationAngle(locRunNumber, locPolarizationAngle);

		dIsPolarizedFlag = dAnalysisUtilities.Get_IsPolarizedBeam(locRunNumber, dIsPARAFlag);
		dPreviousRunNumber = locRunNumber;
	}

	/********************************************* SETUP UNIQUENESS TRACKING ********************************************/

	//ANALYSIS ACTIONS: Reset uniqueness tracking for each action
	//For any actions that you are executing manually, be sure to call Reset_NewEvent() on them here
	Reset_Actions_NewEvent();
	dAnalyzeCutActions->Reset_NewEvent(); // manual action, must call Reset_NewEvent()

	//PREVENT-DOUBLE COUNTING WHEN HISTOGRAMMING
		//Sometimes, some content is the exact same between one combo and the next
			//e.g. maybe two combos have different beam particles, but the same data for the final-state
		//When histogramming, you don't want to double-count when this happens: artificially inflates your signal (or background)
		//So, for each quantity you histogram, keep track of what particles you used (for a given combo)
		//Then for each combo, just compare to what you used before, and make sure it's unique

	//EXAMPLE 1: Particle-specific info:
	set<Int_t> locUsedSoFar_BeamEnergy; //Int_t: Unique ID for beam particles. set: easy to use, fast to search

	//EXAMPLE 2: Combo-specific info:
		//In general: Could have multiple particles with the same PID: Use a set of Int_t's
		//In general: Multiple PIDs, so multiple sets: Contain within a map
		//Multiple combos: Contain maps within a set (easier, faster to search)
	set<map<Particle_t, set<Int_t> > > locUsedSoFar_MissingMass;

	//INSERT USER ANALYSIS UNIQUENESS TRACKING HERE

	/**************************************** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES **************************************/

	/*
	Int_t locMyInt = 7;
	dTreeInterface->Fill_Fundamental<Int_t>("my_int", locMyInt);

	TLorentzVector locMyP4(4.0, 3.0, 2.0, 1.0);
	dTreeInterface->Fill_TObject<TLorentzVector>("my_p4", locMyP4);

	for(int loc_i = 0; loc_i < locMyInt; ++loc_i)
		dTreeInterface->Fill_Fundamental<Int_t>("my_int_array", 3*loc_i, loc_i); //2nd argument = value, 3rd = array index
	*/

	/************************************************* LOOP OVER COMBOS *************************************************/

	//Loop over combos
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);

		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut()) // Is false when tree originally created
			continue; // Combo has been cut previously

		/********************************************** GET PARTICLE INDICES *********************************************/

		//Used for tracking uniqueness when filling histograms, and for determining unused particles

		//Step 0
		Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
		Int_t locProtonTrackID = dProtonWrapper->Get_TrackID();

		//Step 1
		Int_t locPiMinusTrackID = dPiMinusWrapper->Get_TrackID();
		Int_t locPiPlusTrackID = dPiPlusWrapper->Get_TrackID();

		/*********************************************** GET FOUR-MOMENTUM **********************************************/

		// Get P4's: //is kinfit if kinfit performed, else is measured
		//dTargetP4 is target p4
		//Step 0
		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locProtonP4 = dProtonWrapper->Get_P4();
		TLorentzVector locMissingKLongP4 = dMissingKLongWrapper->Get_P4();
		//Step 1
		TLorentzVector locPiMinusP4 = dPiMinusWrapper->Get_P4();
		TLorentzVector locPiPlusP4 = dPiPlusWrapper->Get_P4();

		// Get Measured P4's:
		//Step 0
		TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
		TLorentzVector locProtonP4_Measured = dProtonWrapper->Get_P4_Measured();
		//Step 1
		TLorentzVector locPiMinusP4_Measured = dPiMinusWrapper->Get_P4_Measured();
		TLorentzVector locPiPlusP4_Measured = dPiPlusWrapper->Get_P4_Measured();

		/********************************************* GET COMBO RF TIMING INFO *****************************************/

		TLorentzVector locBeamX4_Measured = dComboBeamWrapper->Get_X4_Measured();
		Double_t locBunchPeriod = dAnalysisUtilities.Get_BeamBunchPeriod(Get_RunNumber());
		Double_t locDeltaT_RF = dAnalysisUtilities.Get_DeltaT_RF(Get_RunNumber(), locBeamX4_Measured, dComboWrapper);
		Int_t locRelBeamBucket = dAnalysisUtilities.Get_RelativeBeamBucket(Get_RunNumber(), locBeamX4_Measured, dComboWrapper); // 0 for in-time events, non-zero integer for out-of-time photons
		Int_t locNumOutOfTimeBunchesInTree = 4; //YOU need to specify this number
			// Number of out-of-time beam bunches in tree (on a single side, so that total number out-of-time bunches accepted is 2 times this number for left + right bunches) 

		Bool_t locSkipNearestOutOfTimeBunch = false; // True: skip events from nearest out-of-time bunch on either side (recommended).
		Int_t locNumOutOfTimeBunchesToUse = locSkipNearestOutOfTimeBunch ? locNumOutOfTimeBunchesInTree-1:locNumOutOfTimeBunchesInTree; 
		Double_t locAccidentalScalingFactor = dAnalysisUtilities.Get_AccidentalScalingFactor(Get_RunNumber(), locBeamP4.E(), dIsMC); // Ideal value would be 1, but deviations require added factor, which is different for data and MC.
		Double_t locAccidentalScalingFactorError = dAnalysisUtilities.Get_AccidentalScalingFactorError(Get_RunNumber(), locBeamP4.E()); // Ideal value would be 1, but deviations observed, need added factor.
		Double_t locHistAccidWeightFactor = locRelBeamBucket==0 ? 1 : -locAccidentalScalingFactor/(2*locNumOutOfTimeBunchesToUse) ; // Weight by 1 for in-time events, ScalingFactor*(1/NBunches) for out-of-time
		if(locSkipNearestOutOfTimeBunch && abs(locRelBeamBucket)==1) { // Skip nearest out-of-time bunch: tails of in-time distribution also leak in
			dComboWrapper->Set_IsComboCut(true); 
			continue; 
		} 

      	/********************************************* COMBINE FOUR-MOMENTUM ********************************************/

      	// DO YOUR STUFF HERE

		// Combine 4-vectors
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locProtonP4_Measured + locPiMinusP4_Measured + locPiPlusP4_Measured;

		TLorentzVector loc2PiP4 = locPiPlusP4 + locPiMinusP4;
		TLorentzVector locDecayingKShortP4 = locPiPlusP4 + locPiMinusP4;
		TLorentzVector loc2PiP4_Measured = locPiPlusP4_Measured + locPiMinusP4_Measured;

		TLorentzVector locKSKL_P4 = locMissingKLongP4 + loc2PiP4;
		TLorentzVector locKSKL_Measured_P4 = loc2PiP4_Measured + locMissingP4_Measured;
		TLorentzVector locPrecoil_P4 = locBeamP4_Measured + dTargetP4 - locProtonP4;
		TLorentzVector locPrecoil_P4_Measured = locBeamP4_Measured + dTargetP4 - locProtonP4_Measured;

		// do some boosting
		//TLorentzRotation resRestBoost( -locKSKL_P4.BoostVector() );
		TLorentzRotation resRestBoost( -(locBeamP4_Measured + dTargetP4).BoostVector() );
		TLorentzVector pip_res = resRestBoost * locPiPlusP4;
		TLorentzVector pim_res = resRestBoost * locPiMinusP4;
		TLorentzVector ks_res  = resRestBoost * locDecayingKShortP4;
		TLorentzVector kl_res  = resRestBoost * locMissingKLongP4;
		TLorentzVector recoil_res = resRestBoost * locProtonP4;
		TLorentzVector kskl_res= resRestBoost * locKSKL_P4;

		// Get Helicity angles
		TVector3 angles_hel = calc_helicity_angles(locBeamP4, locProtonP4, locDecayingKShortP4, locMissingKLongP4);
		double cos_hel_ks = angles_hel.CosTheta();
		double phi_hel_ks = angles_hel.Phi();

		// Get Helicity angles
		TVector3 angles_gj = calc_GJ_angles(locBeamP4, locProtonP4, locDecayingKShortP4, locMissingKLongP4);
		double cos_gj_ks = angles_gj.CosTheta();
		double phi_gj_ks = angles_gj.Phi();

		// Get van Hove x and y
		double vanHove_x = calc_vanHove_X(ks_res.Pz(), kl_res.Pz(), recoil_res.Pz());
		double vanHove_y = calc_vanHove_Y(ks_res.Pz(), kl_res.Pz(), recoil_res.Pz());

		double t = -(locProtonP4 - dTargetP4).M2();

		double mkskl = locKSKL_P4.M();
		double mkl = locMissingP4_Measured.M();
		
		// flight significance cuts
		TLorentzVector locKShort_X4;
		locKShort_X4 = dTreeInterface->Get_TObject<TLorentzVector>("DecayingKShort__X4", loc_i);

		TLorentzVector locFromSpacetimeVertex = locKShort_X4;  //Kshort vertex
		TLorentzVector locStepSpacetimeVertex = dComboBeamWrapper->Get_X4();  //Get production vertex
		TLorentzVector locDeltaSpacetime = locStepSpacetimeVertex - locFromSpacetimeVertex;  //vertex difference
		double locPathLength = locDeltaSpacetime.Vect().Mag(); //pathlength is just the magnitude

		float locPathLengthSigma = Get_Fundamental<Float_t>("DecayingKShort__PathLengthSigma", loc_i);  //Get Sigma from analysis tree
		double locPathLengthSignificance = locPathLength/locPathLengthSigma;  //Calculate significance
		double locDetachedLifeTime = locDeltaSpacetime.T();  //Easy to get lifetime!

		double ks_proper_time = -(1./locDecayingKShortP4.Gamma())*locDetachedLifeTime;

		double event_weight = 0;
		double sideband_w = -0.5;
		float Weight = 0; // This weight is for AmpTools fits

		double chisq = dComboWrapper->Get_ChiSq_KinFit("");
		double chisq_ndf = chisq / dComboWrapper->Get_NDF_KinFit("");

		bool Ks_Criteria = locDecayingKShortP4.M() > 0.48 && locDecayingKShortP4.M() < 0.52;
		bool Ks_Sideband = (locDecayingKShortP4.M() > 0.42 && locDecayingKShortP4.M() < 0.46) || (locDecayingKShortP4.M() > 0.54 && locDecayingKShortP4.M() < 0.58);

		if(Ks_Criteria && fabs(locDeltaT_RF) < 2)	event_weight = 1;
		else if(Ks_Criteria && (locDeltaT_RF) > 2)	event_weight = locHistAccidWeightFactor;
		else if(Ks_Sideband && (locDeltaT_RF) < 2)	event_weight = sideband_w;
		else if(Ks_Sideband && (locDeltaT_RF) > 2)	event_weight = sideband_w*locHistAccidWeightFactor;
		else						event_weight = locHistAccidWeightFactor;

		if(Ks_Criteria && fabs(locDeltaT_RF) < 2)	Weight = 1;
		else if(Ks_Criteria && (locDeltaT_RF) > 2)	Weight = -locHistAccidWeightFactor;
		else if(Ks_Sideband && (locDeltaT_RF) < 2)	Weight = -sideband_w;
		else if(Ks_Sideband && (locDeltaT_RF) > 2)	Weight = -sideband_w*locHistAccidWeightFactor;
		else						Weight = 0;

		if(dIsMC)	dFlatTreeInterface->Fill_Fundamental<bool>("dIsMC", dIsMC);
		dFlatTreeInterface->Fill_Fundamental<double>("event_weight", event_weight);
		dFlatTreeInterface->Fill_Fundamental<double>("accidental_weight", locHistAccidWeightFactor);

//		dFlatTreeInterface->Fill_Fundamental<int>("num_charged_hypo", Get_NumChargedHypos());
		dFlatTreeInterface->Fill_Fundamental<int>("num_unused_tracks", dComboWrapper->Get_NumUnusedTracks());
		dFlatTreeInterface->Fill_Fundamental<int>("num_unused_showers", dComboWrapper->Get_NumUnusedShowers());
		dFlatTreeInterface->Fill_Fundamental<int>("num_combos", Get_NumCombos());

		dFlatTreeInterface->Fill_Fundamental<double>("mpipi", locDecayingKShortP4.M());
		dFlatTreeInterface->Fill_Fundamental<double>("missing_mass", locMissingP4_Measured.M());
		dFlatTreeInterface->Fill_Fundamental<double>("mkskl", locKSKL_P4.M());

		dFlatTreeInterface->Fill_Fundamental<double>("beam_energy", locBeamP4.E());
		dFlatTreeInterface->Fill_Fundamental<double>("mandel_t", t);
		dFlatTreeInterface->Fill_Fundamental<double>("ks_proper_time", ks_proper_time);

		dFlatTreeInterface->Fill_Fundamental<double>("flight_significance", locPathLengthSignificance);
		dFlatTreeInterface->Fill_Fundamental<double>("chisq_ndf", chisq_ndf);

		dFlatTreeInterface->Fill_Fundamental<double>("cos_hel_ks", cos_hel_ks);
		dFlatTreeInterface->Fill_Fundamental<double>("phi_hel_ks", phi_hel_ks);

		dFlatTreeInterface->Fill_Fundamental<double>("cos_gj_ks", cos_gj_ks);
		dFlatTreeInterface->Fill_Fundamental<double>("phi_gj_ks", phi_gj_ks);

		dFlatTreeInterface->Fill_Fundamental<double>("vanHove_x", vanHove_x);
		dFlatTreeInterface->Fill_Fundamental<double>("vanHove_y", vanHove_y);

//		dFlatTreeInterface->Fill_TObject<TLorentzVector>("pip_p4", locPiPlusP4);
//		dFlatTreeInterface->Fill_TObject<TLorentzVector>("pim_p4", locPiMinusP4);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("ks_p4", locDecayingKShortP4);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("kl_p4", locMissingKLongP4);

//		dFlatTreeInterface->Fill_TObject<TLorentzVector>("pip_p4_meas", locPiPlusP4_Measured);
//		dFlatTreeInterface->Fill_TObject<TLorentzVector>("pim_p4_meas", locPiMinusP4_Measured);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("ks_p4_meas", loc2PiP4_Measured);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("missing_p4_meas", locMissingP4_Measured);

		dFlatTreeInterface->Fill_TObject<TLorentzVector>("pip_p4_cm", pip_res);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("pim_p4_cm", pim_res);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("ks_p4_cm", ks_res);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("kl_p4_cm", kl_res);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("recoil_p4_cm", recoil_res);

		vector<TLorentzVector> locFinalStateP4;
		locFinalStateP4.push_back(locProtonP4);
		locFinalStateP4.push_back(locDecayingKShortP4);
		locFinalStateP4.push_back(locMissingKLongP4);

		if(Ks_Criteria && fabs(locDeltaT_RF) < 2)
			dFlatTreeInterface->Fill_Fundamental<bool>("amptools_dat", true);
		else
			dFlatTreeInterface->Fill_Fundamental<bool>("amptools_dat", false);

		if((Ks_Criteria && (locDeltaT_RF) > 2) || (Ks_Criteria && (locDeltaT_RF) > 2) || (Ks_Sideband && (locDeltaT_RF) < 2))
			dFlatTreeInterface->Fill_Fundamental<bool>("amptools_bkg", true);
		else
			dFlatTreeInterface->Fill_Fundamental<bool>("amptools_bkg", false);

		dFlatTreeInterface->Fill_Fundamental<float>("Weight", Weight);
		dFlatTreeInterface->Fill_Fundamental<int>("pol_angle", locPolarizationAngle);
		dFlatTreeInterface->Fill_Fundamental<double>("Target_Mass", 0.9382720); // Necesary for divideData.pl not for AmpTools itself (I think)
		dFlatTreeInterface->Fill_Fundamental<int>("PID_FinalState", 2212, 0); // proton
		dFlatTreeInterface->Fill_Fundamental<int>("PID_FinalState", 310, 1);  // KShort
		dFlatTreeInterface->Fill_Fundamental<int>("PID_FinalState", 130, 2);  // KShort
		FillAmpTools_FlatTree(locBeamP4, locFinalStateP4);

		//FILL FLAT TREE
		//if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8 && locKSKL_P4.M() < 3) // there are a handful of events above 3 GeV in KsKl mass (not sure why)
		if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8 && locPathLengthSignificance > 2 && chisq_ndf < 5 && locMissingP4_Measured.M() > 0 && locMissingP4_Measured.M() < 1.0)
			Fill_FlatTree(); //for the active combo

		//Loop over throwns
		vector<int> thrown_index= {};
		vector<vector<int>> topologies = { {14, 9, 8, 9, 8, 16, 16}, {14, 1, 1, 1, 1, 9, 8, 16, 7, 7, 16}, {14, 9, 8, 1, 1, 1, 1, 16, 16, 7, 7} };

		for(UInt_t loc_i = 0; loc_i < Get_NumThrown(); ++loc_i)
		{
			//Set branch array indices corresponding to this particle
			dThrownWrapper->Set_ArrayIndex(loc_i);

			//Do stuff with the wrapper here ...
			Particle_t locPID = dThrownWrapper->Get_PID();
			thrown_index.push_back(locPID);
		}

		if(thrown_index == topologies[0]) 
			dFlatTreeInterface->Fill_Fundamental<int>("topology", 1);
		else if(thrown_index == topologies[1] || thrown_index == topologies[2]) 
			dFlatTreeInterface->Fill_Fundamental<int>("topology", 2);
		//else if(thrown_index == topologies[1]) 
		//	dFlatTreeInterface->Fill_Fundamental<int>("topology", 2);
		//else if(thrown_index == topologies[2]) 
		//	dFlatTreeInterface->Fill_Fundamental<int>("topology", 3);
		else
			dFlatTreeInterface->Fill_Fundamental<int>("topology", 0);

		for(auto i : thrown_index) {
			cout << " " << i << " ";
		}
		cout << endl;

//		if( !(mkskl > 1.1 && locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8) )	continue;

      	/******************************************** EXECUTE ANALYSIS ACTIONS *******************************************/

      	// Loop through the analysis actions, executing them in order for the active particle combo
      	dAnalyzeCutActions->Perform_Action(); // Must be executed before Execute_Actions()
      	if(!Execute_Actions()) //if the active combo fails a cut, IsComboCutFlag automatically set
      		continue;

      	//if you manually execute any actions, and it fails a cut, be sure to call:
      		//dComboWrapper->Set_IsComboCut(true);

      	/**************************************** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES **************************************/

      	/*
      	TLorentzVector locMyComboP4(8.0, 7.0, 6.0, 5.0);
      	//for arrays below: 2nd argument is value, 3rd is array index
      	//NOTE: By filling here, AFTER the cuts above, some indices won't be updated (and will be whatever they were from the last event)
      		//So, when you draw the branch, be sure to cut on "IsComboCut" to avoid these.
      	dTreeInterface->Fill_Fundamental<Float_t>("my_combo_array", -2*loc_i, loc_i);
      	dTreeInterface->Fill_TObject<TLorentzVector>("my_p4_array", locMyComboP4, loc_i);
      	*/

      	/**************************************** EXAMPLE: HISTOGRAM BEAM ENERGY *****************************************/

//      	//Histogram beam energy (if haven't already)
//		if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
//		{
//			dHist_BeamEnergy->Fill(locBeamP4.E()); // Fills in-time and out-of-time beam photon combos
//			//dHist_BeamEnergy->Fill(locBeamP4.E(),locHistAccidWeightFactor); // Alternate version with accidental subtraction
//
//			locUsedSoFar_BeamEnergy.insert(locBeamID);
//		}
//
//      	/************************************ EXAMPLE: HISTOGRAM MISSING MASS SQUARED ************************************/
//
//      	//Missing Mass Squared
//		double locMissingMassSquared = locMissingP4_Measured.M2();
//
//      	//Uniqueness tracking: Build the map of particles used for the missing mass
//      		//For beam: Don't want to group with final-state photons. Instead use "Unknown" PID (not ideal, but it's easy).
//		map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
//		locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
//		locUsedThisCombo_MissingMass[Proton].insert(locProtonTrackID);
//		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinusTrackID);
//		locUsedThisCombo_MissingMass[PiPlus].insert(locPiPlusTrackID);
//
//      	//compare to what's been used so far
//		if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
//		{
//			//unique missing mass combo: histogram it, and register this combo of particles
//			dHist_MissingMassSquared->Fill(locMissingMassSquared); // Fills in-time and out-of-time beam photon combos
//			//dHist_MissingMassSquared->Fill(locMissingMassSquared,locHistAccidWeightFactor); // Alternate version with accidental subtraction
//
//			locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
//		}
//
////		if( locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8 && locMissingP4_Measured.M()>0.4 && locMissingP4_Measured.M()<0.6 && loc2PiP4_Measured.M()>0.48 && loc2PiP4_Measured.M()<0.52 && locPathLengthSignificance > 5)
////			h2_mkskl_chisqndf->Fill(mkskl, dComboWrapper->Get_ChiSq_KinFit("")/dComboWrapper->Get_NDF_KinFit(""), locHistAccidWeightFactor);
//
//      	// kinematic fit
//		dHist_KinFitCL->Fill(dComboWrapper->Get_ConfidenceLevel_KinFit(""), locHistAccidWeightFactor);
//		dHist_KinFitChiSq->Fill(dComboWrapper->Get_ChiSq_KinFit("")/dComboWrapper->Get_NDF_KinFit(""), locHistAccidWeightFactor);
//
//		if(dComboWrapper->Get_ChiSq_KinFit("") < 0. || dComboWrapper->Get_ChiSq_KinFit("")/dComboWrapper->Get_NDF_KinFit("") > 4.) { 
//			dComboWrapper->Set_IsComboCut(true);
//			continue;
//		}
//      	
//      	
//      	// flight significance cuts
//		dHist_KSFlightSignificance->Fill(locPathLengthSignificance, locHistAccidWeightFactor);
//
//      	// KS flt. sig. sigma cut
//		if(locPathLengthSignificance < 5.) {
//		 	dComboWrapper->Set_IsComboCut(true);
//			continue;
//		}
//
//      
//      	
//		// RF times
//		dHist_RFTime->Fill(locDeltaT_RF);
//		
//		// let's plot some masses
//		dHist_MKs->Fill(locDecayingKShortP4.M(), locHistAccidWeightFactor);
//		dHist_MPiPi->Fill(loc2PiP4.M(), locHistAccidWeightFactor);
//		dHist_MPiPi_Measured->Fill(loc2PiP4_Measured.M(), locHistAccidWeightFactor);
//
////		h2_mks_mklmiss->Fill(loc2PiP4_Measured.M(), mkl, locHistAccidWeightFactor);
//
//		if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8 && t > 0.1 && t < 0.5 && locPathLengthSignificance > 5 && chisq_ndf < 3) {
//			if(locMissingP4_Measured.M()>0.4 && locMissingP4_Measured.M()<0.6 && loc2PiP4.M() > 1.1)
//				h2_mpipi_NumUnusedShowers->Fill(loc2PiP4.M(), locHistAccidWeightFactor);
//			if(loc2PiP4.M() > 0.48 && loc2PiP4.M() < 0.52 && loc2PiP4.M() > 1.1)
//				h2_mmiss_NumUnusedShowers->Fill(locMissingP4_Measured.M(), locHistAccidWeightFactor);
//			if(locMissingP4_Measured.M()>0.4 && locMissingP4_Measured.M()<0.6 && loc2PiP4.M() > 0.48 && loc2PiP4.M() < 0.52)
//				h2_mkskl_NumUnusedShowers->Fill(locKSKL_P4.M(), locHistAccidWeightFactor);
//		}
//
//		if( loc2PiP4_Measured.M()>0.48 && loc2PiP4_Measured.M()<0.52) {
//
//			if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8)
//
//			dHist_MKL_Miss->Fill(locMissingKLongP4.M(), locHistAccidWeightFactor);
//			h1_missingmass->Fill(locMissingP4_Measured.M(), locHistAccidWeightFactor);
//			h1_ks_proper_time->Fill(ks_proper_time, locHistAccidWeightFactor);
//			
//			//if( locMissingP4_Measured.M()>0.45 && locMissingP4_Measured.M()<0.55) {
//			if( locMissingP4_Measured.M()>0.4 && locMissingP4_Measured.M()<0.6) {
//				im_ksklmiss->Fill( (locMissingP4_Measured + locDecayingKShortP4).M(), locHistAccidWeightFactor);
//				im_ksklkin->Fill( (locMissingKLongP4 + locDecayingKShortP4).M(), locHistAccidWeightFactor);
//				dHist_MKsKL->Fill(locKSKL_P4.M(), locHistAccidWeightFactor);
//				im_ksp->Fill((locDecayingKShortP4 + locProtonP4).M(), locHistAccidWeightFactor);
//				im_pimp->Fill((locPiMinusP4 + locProtonP4).M(), locHistAccidWeightFactor);
//				im_pipp->Fill((locPiPlusP4 + locProtonP4).M(), locHistAccidWeightFactor);
//
//
//				if(t < 0.5) {
//					if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8) {
//						im_kskl_cp_lowt->Fill( (locMissingKLongP4 + locDecayingKShortP4).M(), locHistAccidWeightFactor);
//					}
//				}
//
//				if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8) {
//					h1_mandel_t->Fill(t, locHistAccidWeightFactor);
//					cm_precoil_cos->Fill(recoil_res.CosTheta(), locHistAccidWeightFactor);
//					cm_kskl_cos->Fill(kskl_res.CosTheta(), locHistAccidWeightFactor);
//					im_kskl_cp->Fill( (locMissingKLongP4+ locDecayingKShortP4).M(), locHistAccidWeightFactor);
//				}
//
//				dHist_MKsKL->Fill(locKSKL_P4.M(), locHistAccidWeightFactor);
//				dHist_MKsKL_Measured->Fill(locKSKL_Measured_P4.M(), locHistAccidWeightFactor);
//
//				dHist_Mprecoil_Measured->Fill(locPrecoil_P4_Measured.M(), locHistAccidWeightFactor);
//				dHist_Mprecoil->Fill(locPrecoil_P4.M(), locHistAccidWeightFactor);
//
//				dHist_MKsKL_phi->Fill(locKSKL_P4.M(), locHistAccidWeightFactor);
//				dHist_MKsKL_phi_Measured->Fill(locKSKL_Measured_P4.M(), locHistAccidWeightFactor);
//				
//				dHist_Mprecoil_phi_Measured->Fill(locPrecoil_P4_Measured.M(), locHistAccidWeightFactor);
//				dHist_Mprecoil_phi->Fill(locPrecoil_P4.M(), locHistAccidWeightFactor);
//			}
//		}

		/****************************************** FILL FLAT TREE (IF DESIRED) ******************************************/

		/*
		//FILL ANY CUSTOM BRANCHES FIRST!!
		Int_t locMyInt_Flat = 7;
		dFlatTreeInterface->Fill_Fundamental<Int_t>("flat_my_int", locMyInt_Flat);

		TLorentzVector locMyP4_Flat(4.0, 3.0, 2.0, 1.0);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("flat_my_p4", locMyP4_Flat);

		for(int loc_j = 0; loc_j < locMyInt_Flat; ++loc_j)
		{
			dFlatTreeInterface->Fill_Fundamental<Int_t>("flat_my_int_array", 3*loc_j, loc_j); //2nd argument = value, 3rd = array index
			TLorentzVector locMyComboP4_Flat(8.0, 7.0, 6.0, 5.0);
			dFlatTreeInterface->Fill_TObject<TLorentzVector>("flat_my_p4_array", locMyComboP4_Flat, loc_j);
		}
		*/

//		//FILL FLAT TREE
//		if(locBeamP4.E() > 8.2 && locBeamP4.E() < 8.8 && locPathLengthSignificance > 5 && dComboWrapper->Get_ChiSq_KinFit("")/dComboWrapper->Get_NDF_KinFit("") < 4)
//			Fill_FlatTree(); //for the active combo
	} // end of combo loop

	//FILL HISTOGRAMS: Num combos / events surviving actions
	Fill_NumCombosSurvivedHists();

	/******************************************* LOOP OVER THROWN DATA (OPTIONAL) ***************************************/
/*
	//Thrown beam: just use directly
	if(dThrownBeam != NULL)
		double locEnergy = dThrownBeam->Get_P4().E();

	//Loop over throwns
	for(UInt_t loc_i = 0; loc_i < Get_NumThrown(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dThrownWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}
*/
	/****************************************** LOOP OVER OTHER ARRAYS (OPTIONAL) ***************************************/
/*
	//Loop over beam particles (note, only those appearing in combos are present)
	for(UInt_t loc_i = 0; loc_i < Get_NumBeam(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dBeamWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}

	//Loop over charged track hypotheses
	for(UInt_t loc_i = 0; loc_i < Get_NumChargedHypos(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dChargedHypoWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}

	//Loop over neutral particle hypotheses
	for(UInt_t loc_i = 0; loc_i < Get_NumNeutralHypos(); ++loc_i)
	{
		//Set branch array indices corresponding to this particle
		dNeutralHypoWrapper->Set_ArrayIndex(loc_i);

		//Do stuff with the wrapper here ...
	}
*/

	/************************************ EXAMPLE: FILL CLONE OF TTREE HERE WITH CUTS APPLIED ************************************/
/*
	Bool_t locIsEventCut = true;
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i) {
		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);
		// Is used to indicate when combos have been cut
		if(dComboWrapper->Get_IsComboCut())
			continue;
		locIsEventCut = false; // At least one combo succeeded
		break;
	}
	if(!locIsEventCut && dOutputTreeFileName != "")
		Fill_OutputTree();
*/

	return kTRUE;
}

void DSelector_kskl_M16::Finalize(void)
{
	//Save anything to output here that you do not want to be in the default DSelector output ROOT file.

	//Otherwise, don't do anything else (especially if you are using PROOF).
		//If you are using PROOF, this function is called on each thread,
		//so anything you do will not have the combined information from the various threads.
		//Besides, it is best-practice to do post-processing (e.g. fitting) separately, in case there is a problem.

	//DO YOUR STUFF HERE

	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
