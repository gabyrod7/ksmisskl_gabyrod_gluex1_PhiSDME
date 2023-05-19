void list_events() {
    string root_file = "ftree_bggen_batch1.root";
    string tree_name = "kskl";

    std::ofstream my_csv("list_of_kskl_events.csv");

    TFile *inf = TFile::Open(root_file.c_str());
    TTree *tree = (TTree*)inf->Get(tree_name.c_str());
    Long64_t nentries = tree->GetEntries();

    unsigned int run;
    ULong64_t event;
    char line[100];

    tree->SetBranchAddress("run", &run);
    tree->SetBranchAddress("event", &event);

    for(Long64_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);

        sprintf(line, "%d,%llu\n", run, event);
        // cout << text;
        my_csv << line;
    }

    my_csv.close();
}
