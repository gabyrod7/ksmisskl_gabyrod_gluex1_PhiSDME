#include "DSelector_cp_intime_fdc_4_pulls.h"


void DSelector_cp_intime_fdc_4_pulls::Init(TTree *locTree)
{
	// USERS: IN THIS FUNCTION, ONLY MODIFY SECTIONS WITH A "USER" OR "EXAMPLE" LABEL. LEAVE THE REST ALONE.

	// The Init() function is called when the selector needs to initialize a new tree or chain.
	// Typically here the branch addresses and branch pointers of the tree will be set.
	// Init() will be called many times when running on PROOF (once per file to be processed).

	//USERS: SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = "hist_cp_intime_fdc_4_pulls.root"; //"" for none
	dOutputTreeFileName = ""; //"" for none
	dFlatTreeFileName = "tree_cp_intime_fdc_4_pulls.root"; //output flat tree (one combo per tree entry), "" for none
	dFlatTreeName = "kin"; //if blank, default name will be chosen
	dSaveDefaultFlatBranches = false; // don't save default branches, reduce disk footprint.

	//Because this function gets called for each TTree in the TChain, we must be careful:
		//We need to re-initialize the tree interface & branch wrappers, but don't want to recreate histograms
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	Get_ComboWrappers();
	dPreviousRunNumber = 0;

	dAnalysisActions.push_back(new DHistogramAction_BeamEnergy(dComboWrapper, true,"Before_cut"));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, true,"Before_cut"));
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, true, "Before_cut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, {KPlus,KMinus},800, 0, 4, "Before_cut"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 1000, -0.1, 0.1,"Before_cut"));

	// BEAM ENERGY
	dAnalysisActions.push_back(new DCutAction_BeamEnergy(dComboWrapper, true, 8.2, 8.8));

	dAnalysisActions.push_back(new DHistogramAction_BeamEnergy(dComboWrapper, true,"After_BE_cut"));
	dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, true,"After_BE_cut"));
	dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, true, "After_BE_cut"));
	dAnalysisActions.push_back(new DHistogramAction_InvariantMass(dComboWrapper, true, 0, {KPlus,KMinus},800, 0, 4, "After_BE_cut"));
	dAnalysisActions.push_back(new DHistogramAction_MissingMassSquared(dComboWrapper, false, 1000, -0.1, 0.1,"After_BE_cut"));


	Initialize_Actions();




		dHist_PxPull_Phi_Proton = new TH2I("PxPullVsPhi_Proton", ";#phi^{o};p_{x}(measured) #minus p_{x}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);
		dHist_PyPull_Phi_Proton = new TH2I("PyPullVsPhi_Proton", ";#phi^{o};p_{y}(measured) #minus p_{y}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);
		dHist_PzPull_Phi_Proton = new TH2I("PzPullVsPhi_Proton", ";#phi^{o};p_{z}(measured) #minus p_{z}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);

		dHist_PxPull_Phi_KPlus = new TH2I("PxPullVsPhi_KPlus", ";#phi^{o};p_{x}(measured) #minus p_{x}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);
		dHist_PyPull_Phi_KPlus = new TH2I("PyPullVsPhi_KPlus", ";#phi^{o};p_{y}(measured) #minus p_{y}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);
		dHist_PzPull_Phi_KPlus = new TH2I("PzPullVsPhi_KPlus", ";#phi^{o};p_{z}(measured) #minus p_{z}(kinfit) (GeV/c)",90,-180,180,100,-1.5,1.5);

		dHist_PxPull_Phi_KMinus = new TH2I("PxPullVsPhi_KMinus", ";#phi^{o};p_{x}(measured) #minus p_{x}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);
		dHist_PyPull_Phi_KMinus = new TH2I("PyPullVsPhi_KMinus", ";#phi^{o};p_{y}(measured) #minus p_{y}(kinfit) (GeV/c)",90,-180,180,100,-0.1,0.1);
		dHist_PzPull_Phi_KMinus = new TH2I("PzPullVsPhi_KMinus", ";#phi^{o};p_{z}(measured) #minus p_{z}(kinfit) (GeV/c)",90,-180,180,100,-1.5,1.5);
		




	
	SetupAmpTools_FlatTree();

	dFlatTreeInterface->Create_Branch_Fundamental<Float_t>("t");
	dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("IM");
	dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("MM2");
	dFlatTreeInterface->Create_Branch_Fundamental<Float_t>("Phi_Prod");
	dFlatTreeInterface->Create_Branch_Fundamental<Int_t>("PolarizationAngle");
	dFlatTreeInterface->Create_Branch_Fundamental<Float_t>("ChiSq_NDF");
	dFlatTreeInterface->Create_Branch_Fundamental<Float_t>("VertexZ");	

}

Bool_t DSelector_cp_intime_fdc_4_pulls::Process(Long64_t locEntry)
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


	Reset_Actions_NewEvent();


	//cout << "RUN " << Get_RunNumber() << ", EVENT " << Get_EventNumber() << endl;
	TLorentzVector locProductionX4 = Get_X4_Production();




	/************************************************* LOOP OVER COMBOS *************************************************/

        Int_t NCombos = (Int_t)Get_NumCombos();

        Int_t dPolarizationAngle = Get_Fundamental<Int_t>("PolarizationAngle");

	//Loop over combos
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{

		//Set branch array indices for combo and all combo particles
		dComboWrapper->Set_ComboIndex(loc_i);

		if(dComboWrapper->Get_IsComboCut()) continue; // Combo has been cut previously

		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locKPlusP4 = dKPlusWrapper->Get_P4();
		TLorentzVector locKMinusP4 = dKMinusWrapper->Get_P4();
		TLorentzVector locProtonP4 = dProtonWrapper->Get_P4();

                TLorentzVector locKpKm = locKPlusP4 + locKMinusP4;
                
                // Mandelstam t= (p1- p3)^2 = (p2-p4)^2 where p3=phi and p1=photon, p2=ptgt and p4=precoil
		// 4 vector squared is -1* 4vector.M2
                // Using target and recoil protons, t_min is 0.

                // Set the weighting factor +ve because the in and out of time events will be in separate files.
                Double_t locHistAccidWeightFactor = fabs(Get_Fundamental<Double_t>("HistAccidWeightFactor", loc_i));
		Int_t locRelBeamBucket = Get_Fundamental<Int_t>("RelBeamBucket",loc_i);
                Float_t loct = Get_Fundamental<Float_t>("Mandelstam_t", loc_i);
                Double_t IM = Get_Fundamental<Double_t>("IM", loc_i);
                Double_t MM2 = Get_Fundamental<Double_t>("MM2", loc_i);

	        Float_t chisq = Get_Fundamental<Float_t>("ChiSq_KinFit", loc_i);
                Int_t ndf = Get_Fundamental<Int_t>("NDF_KinFit", loc_i);

                Float_t chi2dof = chisq/(Float_t)ndf;


		Bool_t locSkipNearestOutOfTimeBunch = true; // True: skip events from nearest out-of-time bunch on either side (recommended).		
		if(locSkipNearestOutOfTimeBunch && abs(locRelBeamBucket)==1) { // Skip nearest out-of-time bunch: tails of in-time distribution also leak in
		 	dComboWrapper->Set_IsComboCut(true); 
		 	continue; 
	        } 

		
                if (locRelBeamBucket !=0) dComboWrapper->Set_IsComboCut(true);  
		if(dComboWrapper->Get_IsComboCut()) continue; 


                // find distance from vertex to fdc

		Float_t dz = 176.939-(Float_t)locProductionX4.Z();
		Float_t dr = dz*tan(locKPlusP4.Theta());
		if (dr<4.0) dComboWrapper->Set_IsComboCut(true);   // dead radius is 3cm
		
		dr = dz*tan(locKMinusP4.Theta());
		if (dr<4.0) dComboWrapper->Set_IsComboCut(true);   // dead radius is 3cm
		
		if(dComboWrapper->Get_IsComboCut()) continue;


		

		// Loop through the analysis actions, executing them in order for the active particle combo

		if(!Execute_Actions()) //this just fills histograms
			continue;



		// put the kinfit pull code in here


		TLorentzVector locKPlusP4_Measured = dKPlusWrapper->Get_P4_Measured();
		TLorentzVector locKMinusP4_Measured = dKMinusWrapper->Get_P4_Measured();
		TLorentzVector locProtonP4_Measured = dProtonWrapper->Get_P4_Measured();

		double pxpull_Proton = locProtonP4_Measured.Px() - locProtonP4.Px();
		double pypull_Proton = locProtonP4_Measured.Py() - locProtonP4.Py();
		double pzpull_Proton = locProtonP4_Measured.Pz() - locProtonP4.Pz();		

		double pxpull_KPlus = locKPlusP4_Measured.Px() - locKPlusP4.Px();
		double pypull_KPlus = locKPlusP4_Measured.Py() - locKPlusP4.Py();
		double pzpull_KPlus = locKPlusP4_Measured.Pz() - locKPlusP4.Pz();		

		double pxpull_KMinus = locKMinusP4_Measured.Px() - locKMinusP4.Px();
		double pypull_KMinus = locKMinusP4_Measured.Py() - locKMinusP4.Py();
		double pzpull_KMinus = locKMinusP4_Measured.Pz() - locKMinusP4.Pz();		
		
		const double degrees = 180.0/3.14159;
		



		dHist_PxPull_Phi_Proton->Fill(degrees*locProtonP4.Phi(),pxpull_Proton);
		dHist_PyPull_Phi_Proton->Fill(degrees*locProtonP4.Phi(),pypull_Proton);
		dHist_PzPull_Phi_Proton->Fill(degrees*locProtonP4.Phi(),pzpull_Proton);		

		dHist_PxPull_Phi_KPlus->Fill(degrees*locKPlusP4.Phi(),pxpull_KPlus);
		dHist_PyPull_Phi_KPlus->Fill(degrees*locKPlusP4.Phi(),pypull_KPlus);
		dHist_PzPull_Phi_KPlus->Fill(degrees*locKPlusP4.Phi(),pzpull_KPlus);		

		dHist_PxPull_Phi_KMinus->Fill(degrees*locKMinusP4.Phi(),pxpull_KMinus);
		dHist_PyPull_Phi_KMinus->Fill(degrees*locKMinusP4.Phi(),pypull_KMinus);
		dHist_PzPull_Phi_KMinus->Fill(degrees*locKMinusP4.Phi(),pzpull_KMinus);		
		


		
		vector<TLorentzVector> locFinalStateP4;
		locFinalStateP4.push_back(locProtonP4);
                locFinalStateP4.push_back(locKPlusP4);
                locFinalStateP4.push_back(locKMinusP4);

		dFlatTreeInterface->Fill_Fundamental<Float_t>("Phi_Prod", (Float_t)locKpKm.Phi());
		dFlatTreeInterface->Fill_Fundamental<Float_t>("t", (Float_t)loct);
		dFlatTreeInterface->Fill_Fundamental<Double_t>("IM", (Double_t)IM);
		dFlatTreeInterface->Fill_Fundamental<Double_t>("MM2", (Double_t)MM2);
                dFlatTreeInterface->Fill_Fundamental<Float_t>("Weight", (Float_t)locHistAccidWeightFactor);  
         	dFlatTreeInterface->Fill_Fundamental<Int_t>("PolarizationAngle",dPolarizationAngle); 
		dFlatTreeInterface->Fill_Fundamental<Float_t>("ChiSq_NDF", (Float_t)chi2dof);
                dFlatTreeInterface->Fill_Fundamental<Float_t>("VertexZ",(Float_t)locProductionX4.Z());
				// set ordered final state P4 for filling flat tree
      		FillAmpTools_FlatTree(locBeamP4, locFinalStateP4); 
				//FillAmpTools_FlatTree(locBeamP4, locFinalStateThrownP4);

       		Fill_FlatTree(); //for the active combo

	} // end of combo loop


	//FILL HISTOGRAMS: Num combos / events surviving actions
	Fill_NumCombosSurvivedHists();


	/************************************ EXAMPLE: FILL CLONE OF TTREE HERE WITH CUTS APPLIED ************************************/
	
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
	

	return kTRUE;
}

void DSelector_cp_intime_fdc_4_pulls::Finalize(void)
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
