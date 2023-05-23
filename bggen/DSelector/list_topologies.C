void list_topologies() {
	TFile *inf = TFile::Open("hist_bggen.root");
	string hist_name = "hThrownTopologies_nominalCuts";

	std::ofstream file("topologies.txt");
	
	auto h = (TH1F*)inf->Get( hist_name.c_str() );
	int num_topologies = h->GetNbinsX();
	h->GetXaxis()->LabelsOption(">");
	for(int i = 1; h->GetBinContent(i) > 0; i++) {
		file << "$" << h->GetXaxis()->GetBinLabel(i) << "$ & " << h->GetBinContent(i) << " \\\\" << std::endl;
	}
}
