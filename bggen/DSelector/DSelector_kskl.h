#ifndef DSelector_kskl_h
#define DSelector_kskl_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"

class DSelector_kskl : public DSelector
{
	public:

		DSelector_kskl(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_kskl(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Get_ComboWrappers(void);
		void Finalize(void);

		// BEAM POLARIZATION INFORMATION
		UInt_t dPreviousRunNumber;
		bool dIsPolarizedFlag; //else is AMO
		bool dIsPARAFlag; //else is PERP or AMO

		bool dIsMC;

		// ANALYZE CUT ACTIONS
		// // Automatically makes mass histograms where one cut is missing
		DHistogramAction_AnalyzeCutActions* dAnalyzeCutActions;

		//CREATE REACTION-SPECIFIC PARTICLE ARRAYS

		//Step 0
		DParticleComboStep* dStep0Wrapper;
		DBeamParticle* dComboBeamWrapper;
		DChargedTrackHypothesis* dProtonWrapper;
		DKinematicData* dMissingKLongWrapper;

		//Step 1
		DParticleComboStep* dStep1Wrapper;
		DChargedTrackHypothesis* dPiMinusWrapper;
		DChargedTrackHypothesis* dPiPlusWrapper;

		// DEFINE YOUR HISTOGRAMS HERE
		// EXAMPLES:
		TH1I* dHist_MissingMassSquared;
		TH1I* dHist_BeamEnergy;

		TH1F *dHistThrownTopologies;
		TH1F *dHistThrownTopologies_nominalCuts;
		TH1F *dHistSelectThrownTopologies_noCuts;
		TH1F *dHistSelectThrownTopologies_nominalCuts;

		map<TString, TH1I*> dHistInvariantMass_ThrownTopology;
		map<TString, TH1I*> dHistPiPiInvariantMass_ThrownTopology;
		map<TString, TH1I*> dHistMissingMass_ThrownTopology;
		map<TString, TH1I*> dHistChiSqNdf_ThrownTopology;
		map<TString, TH1I*> dHistFlightSignificance_ThrownTopology;
		map<TString, TH1I*> dHistMandelsamt_ThrownTopology;
		map<TString, TH1I*> dHistPathLength_ThrownTopology;
		map<TString, TH1I*> dHistNumUnusedTracks_ThrownTopology;
		map<TString, TH1I*> dHistNumUnusedShowers_ThrownTopology;
		map<TString, TH1I*> dHistNumUnusedTracks_ThrownTopology_AfterCuts;
		map<TString, TH1I*> dHistNumUnusedShowers_ThrownTopology_AfterCuts;

		TH1F *h1_beam_energy;

		TH1F *im_miss;
		TH1F *im_pipi;

		TH1F *im_kskl;
		TH1F *im_kskl_sig;
		TH1F *im_kskl_bkg;

	ClassDef(DSelector_kskl, 0);
};

void DSelector_kskl::Get_ComboWrappers(void)
{
	//Step 0
	dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
	dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
	dProtonWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));
	dMissingKLongWrapper = dStep0Wrapper->Get_FinalParticle(2);

	//Step 1
	dStep1Wrapper = dComboWrapper->Get_ParticleComboStep(1);
	dPiMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep1Wrapper->Get_FinalParticle(0));
	dPiPlusWrapper = static_cast<DChargedTrackHypothesis*>(dStep1Wrapper->Get_FinalParticle(1));
}

#endif // DSelector_kskl_h
