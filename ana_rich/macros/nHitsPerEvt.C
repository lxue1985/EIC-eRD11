void nHitsPerEvt () {
	gROOT->Reset();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(000);
	gStyle->SetPalette(1);
	gStyle->SetOptDate(0);
	gStyle->SetOptTitle(0000);

	gStyle->SetCanvasColor(kWhite);
	gStyle->SetFrameFillStyle(1001);
	gStyle->SetFrameFillColor(kWhite);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(kWhite);
	gStyle->SetStatColor(kWhite);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	// gStyle->SetLabelSize(.05,"X");
	// gStyle->SetLabelSize(.05,"Y");
	gStyle->SetLabelColor(1,"X");
	gStyle->SetLabelColor(1,"Y");


 	char rootf[6][256]={ "../../output_pftcase/eic_rich_output_e-_hist.root",
			     "../../output_pftcase/eic_rich_output_mu-_hist.root",
			     "../../output_pftcase/eic_rich_output_pi-_hist.root",
			     "../../output_pftcase/eic_rich_output_kaon-_hist.root", 
			     "../../output_pftcase/eic_rich_output_proton_hist.root"};
 	char particle[6][256]={ "electron","muon", "pion", "kaon", "proton"};

	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->cd();

	for(int i=0; i<5; i++){
	char ofile[256];
	sprintf(ofile,"hist_nHitPerEvt_%s.png",particle[i]); 
	cout<<"processing file: "<<rootf[i]<<";    output file: "<<ofile<<endl;
	
	TFile *f1 = new TFile(rootf[i]);
	hnHitPerEvtvsMom->GetYaxis()->SetRangeUser(0.,50.);
	hnHitPerEvtvsMom->GetXaxis()->SetTitle("Momentum (GeV/c)");
	hnHitPerEvtvsMom->GetYaxis()->SetTitle("Number of Hits / Event");
	hnHitPerEvtvsMom->GetYaxis()->SetTitleColor(kBlack);
	hnHitPerEvtvsMom->GetYaxis()->SetTitleSize(0.05);
	hnHitPerEvtvsMom->GetXaxis()->SetTitleSize(0.05);
	hnHitPerEvtvsMom->Draw("");
	hnHitPerEvtvsMom->ProfileX();
	hnHitPerEvtvsMom_pfx->Rebin(4)
	hnHitPerEvtvsMom_pfx->SetMarkerStyle(21);
	hnHitPerEvtvsMom_pfx->SetMarkerSize(0.6);
	hnHitPerEvtvsMom_pfx->SetMarkerColor(kRed);
	hnHitPerEvtvsMom_pfx->Draw("SAME");
	c1->SaveAs(ofile);
	}
}
