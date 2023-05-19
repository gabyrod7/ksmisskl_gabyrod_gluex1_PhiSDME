
void list_topologies() {
	TFile *inf = TFile::Open("hist_bggen.root");
	int num_topologies = 20;
	string hist_name = "hThrownTopologies_nominalCuts";
	
	auto h = (TH1F*)inf->Get( hist_name.c_str() );
	h->GetXaxis()->LabelsOption(">");
	for(int i = 1; i <= num_topologies; i++) {
		cout << h->GetXaxis()->GetBinLabel(i) << endl;
		cout << "   -> Number of events: " << h->GetBinContent(i) << endl;
	}
}
