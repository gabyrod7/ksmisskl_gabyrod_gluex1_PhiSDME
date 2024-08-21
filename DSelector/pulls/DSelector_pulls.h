#ifndef DSelector_pulls_h
#define DSelector_pulls_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"

#include "TH1I.h"
#include "TH2I.h"

class DSelector_pulls : public DSelector
{
	public:

		DSelector_pulls(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_pulls(){}

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

                TH1I* dHist_IM;

                TH2I* dHist_IM_KF;
                TH2I* dHist_MM_KF;


		TH2I* dHist_PxPull_Phi_Proton;
  		TH2I* dHist_PyPull_Phi_Proton;
  		TH2I* dHist_PzPull_Phi_Proton;
  
		TH2I* dHist_PxPull_Phi_DecayingKShort;
  		TH2I* dHist_PyPull_Phi_DecayingKShort;
  		TH2I* dHist_PzPull_Phi_DecayingKShort;
  
		TH2I* dHist_PxPull_Phi_MissingKLong;
  		TH2I* dHist_PyPull_Phi_MissingKLong;
  		TH2I* dHist_PzPull_Phi_MissingKLong;  

		TH2I* dHist_PxPull_Phi_PiPlus;
  		TH2I* dHist_PyPull_Phi_PiPlus;
  		TH2I* dHist_PzPull_Phi_PiPlus;  

		TH2I* dHist_PxPull_Phi_PiMinus;
  		TH2I* dHist_PyPull_Phi_PiMinus;
  		TH2I* dHist_PzPull_Phi_PiMinus;  

	ClassDef(DSelector_pulls, 0);
};

void DSelector_pulls::Get_ComboWrappers(void)
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

#endif // DSelector_pulls_h
