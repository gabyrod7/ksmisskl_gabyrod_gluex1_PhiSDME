{
  TCanvas *c = new TCanvas ("c","c",1300,1200);

  gStyle->SetPadLeftMargin(0.12);
  
  c->Divide(3,5);

  const char hname[15][30] = {
    "PxPullVsPhi_Proton","PyPullVsPhi_Proton","PzPullVsPhi_Proton",
    "PxPullVsPhi_DecayingKShort","PyPullVsPhi_DecayingKShort","PzPullVsPhi_DecayingKShort",
    "PxPullVsPhi_MissingKLong","PyPullVsPhi_MissingKLong","PzPullVsPhi_MissingKLong",
    "PxPullVsPhi_PiPlus","PyPullVsPhi_PiPlus","PzPullVsPhi_PiPlus",
    "PxPullVsPhi_PiMinus","PyPullVsPhi_PiMinus","PzPullVsPhi_PiMinus"};

  TH2I *h;
  
  for (int i=0; i<15; i++) {
    c->cd(i+1);
    h = (TH2I*)gDirectory->Get(hname[i]);
    h->Draw("colz");
    gPad->SetGrid();
  }

  c->Print("pulls.pdf"); 
}

