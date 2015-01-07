void RadiusvsMom () {
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

	char ofile[256];
	sprintf(ofile,"figs/hist_RadiusvsMom.png"); 
	for(int i=0; i<5; i++){
	cout<<"processing file: "<<rootf[i]<<";    output file: "<<ofile<<endl;
	
	TFile *f1 = new TFile(rootf[i]);
	hRadiusvsMom->GetYaxis()->SetRangeUser(0.,20.);
	hRadiusvsMom->GetXaxis()->SetTitle("Momentum (GeV/c)");
	hRadiusvsMom->GetYaxis()->SetTitle("Ring radius (mm)");
	hRadiusvsMom->GetYaxis()->SetTitleColor(kBlack);
	hRadiusvsMom->GetYaxis()->SetTitleSize(0.05);
	hRadiusvsMom->GetXaxis()->SetTitleSize(0.05);
	if(i==0) hRadiusvsMom->Draw("col");
	else hRadiusvsMom->Draw("colSAME");
	}
	c1->SaveAs(ofile);
}
