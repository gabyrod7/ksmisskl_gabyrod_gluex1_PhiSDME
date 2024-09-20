
void estimate_number_of_ksks_events() {
    double flux = 9.64512e+13;
    double target_thickness = 1.2e-9; // nano-barns^-1
    double integratedCrossSection_gammap_to_ksks = 0.50; // nano-barns
    double efficiency_ksks_to_pippimpippim = 0.002;
    double efficiency_ksks_to_pippimpi0pi0 = 0.007;
    double branchinRato_ks_to_pippim = 0.69;
    double branchinRato_ks_to_pi0pi0 = 0.30;

    double estimated_number_of_ksks_events = flux * target_thickness * integratedCrossSection_gammap_to_ksks 
        * (efficiency_ksks_to_pippimpippim * branchinRato_ks_to_pippim * branchinRato_ks_to_pippim 
            + efficiency_ksks_to_pippimpi0pi0 * branchinRato_ks_to_pippim* branchinRato_ks_to_pi0pi0);

    cout << "Estimated number of KsKs events: " << estimated_number_of_ksks_events << endl;
}
