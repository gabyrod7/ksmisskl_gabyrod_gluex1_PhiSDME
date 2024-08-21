void apply_weight(string run = "gluex1");

void apply_weight_to_acc_data() {
    vector<string> runs = {"sp17", "sp18", "fa18", "gluex1"};
    // vector<string> runs = {"sp17", "sp18", "fa18"};
    // vector<string> runs = {"gluex1"};

    for(auto run : runs) {
        apply_weight(run);
    }
}


void apply_weight(string run = "gluex1") {
    float	particle_es[3], particle_pxs[3], particle_pys[3], particle_pzs[3];
    float weight = 0.0;

    TFile *inf, *inf2;
    TTree *old_tree, *new_tree;

    TLorentzVector recoil_p4;
    TLorentzVector p1_p4;
    TLorentzVector p2_p4;

    inf2 = TFile::Open("hists/ratio.root");

    TH1F *hist = (TH1F*)inf2->Get(run.c_str());

    string file_name = "ftree_acc_"+run+".root";

    if(gSystem->AccessPathName(file_name.c_str())) {
        cout << "File " << file_name << " does not exist." << endl;
        exit(1);
    }
    else
        cout << "Open file: " << file_name << endl;
    
    inf = new TFile(file_name.c_str(), "update");
    old_tree = (TTree*)inf->Get("kin");
    new_tree = old_tree->CloneTree(0);

    new_tree->SetBranchAddress("Weight", &weight);

    old_tree->SetBranchAddress("E_FinalState", particle_es);
    old_tree->SetBranchAddress("Px_FinalState", particle_pxs);
    old_tree->SetBranchAddress("Py_FinalState", particle_pys);
    old_tree->SetBranchAddress("Pz_FinalState", particle_pzs);

    Long64_t nentries = old_tree->GetEntries();
    cout << "There are nentries: " << nentries << endl;

    for(Long64_t i = 0; i < nentries; i++) {
        old_tree->GetEntry(i);

        recoil_p4.SetPxPyPzE(particle_pxs[0],particle_pys[0],particle_pzs[0],particle_es[0]);
        p1_p4.SetPxPyPzE(particle_pxs[1],particle_pys[1],particle_pzs[1],particle_es[1]);
        p2_p4.SetPxPyPzE(particle_pxs[2],particle_pys[2],particle_pzs[2],particle_es[2]);

        TLorentzVector resonance = p1_p4 + p2_p4;
        TLorentzVector mom_transfer = recoil_p4 - TLorentzVector(0,0,0,0.9382720813);

        weight = hist->GetBinContent(hist->FindBin(resonance.M()));
        
        new_tree->Fill();
        // if(i > 10000) break;
    } // end of entries

    new_tree->Write("kin", TObject::kOverwrite);
    // new_tree->Write("kin");
    inf->Close();
}