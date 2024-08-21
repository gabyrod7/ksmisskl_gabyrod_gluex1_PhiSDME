#ifndef DSelector_cp_intime_fdc_4_pulls_h
#define DSelector_cp_intime_fdc_4_pulls_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"


#include "TH1I.h"
#include "TH2I.h"

class DSelector_cp_intime_fdc_4_pulls : public DSelector
{
	public:

		DSelector_cp_intime_fdc_4_pulls(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DSelector_cp_intime_fdc_4_pulls(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Get_ComboWrappers(void);
		void Finalize(void);

		// BEAM POLARIZATION INFORMATION
		UInt_t dPreviousRunNumber;
		bool dIsPolarizedFlag; //else is AMO
		bool dIsPARAFlag; //else is PERP or AMO

                Int_t dPolarizationAngle;

		bool dIsMC;

		// ANALYZE CUT ACTIONS
		// // Automatically makes mass histograms where one cut is missing
		DHistogramAction_AnalyzeCutActions* dAnalyzeCutActions;

		//CREATE REACTION-SPECIFIC PARTICLE ARRAYS

		//Step 0
		DParticleComboStep* dStep0Wrapper;
		DBeamParticle* dComboBeamWrapper;
		DChargedTrackHypothesis* dKPlusWrapper;
		DChargedTrackHypothesis* dKMinusWrapper;
		DChargedTrackHypothesis* dProtonWrapper;

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
  
		TH2I* dHist_PxPull_Phi_KPlus;
  		TH2I* dHist_PyPull_Phi_KPlus;
  		TH2I* dHist_PzPull_Phi_KPlus;
  
		TH2I* dHist_PxPull_Phi_KMinus;
  		TH2I* dHist_PyPull_Phi_KMinus;
  		TH2I* dHist_PzPull_Phi_KMinus;  


  
	ClassDef(DSelector_cp_intime_fdc_4_pulls, 0);
};

void DSelector_cp_intime_fdc_4_pulls::Get_ComboWrappers(void)
{
	//Step 0
	dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
	dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
	dKPlusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(0));
	dKMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));
	dProtonWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(2));
}

#endif // DSelector_cp_intime_fdc_4_pulls_h
