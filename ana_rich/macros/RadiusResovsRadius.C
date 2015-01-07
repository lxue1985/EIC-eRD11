void RadiusResovsRadius () {
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
	sprintf(ofile,"figs/hist_RadiusResovsRadius_%s.png",particle[i]); 
	cout<<"processing file: "<<rootf[i]<<";    output file: "<<ofile<<endl;
	
	TFile *f1 = new TFile(rootf[i]);
	hResvsRadius->GetYaxis()->SetRangeUser(0.,5);
	hResvsRadius->GetXaxis()->SetTitle("Radius (mm)");
	hResvsRadius->GetYaxis()->SetTitle("#sigma_{R} (mm)");
	hResvsRadius->GetYaxis()->SetTitleColor(kBlack);
	hResvsRadius->GetYaxis()->SetTitleSize(0.05);
	hResvsRadius->GetXaxis()->SetTitleSize(0.05);
	hResvsRadius->Draw("col");
	hResvsRadius->ProfileX();
        hResvsRadius_pfx->Rebin(8);
        hResvsRadius_pfx->SetMarkerStyle(21);
        hResvsRadius_pfx->SetMarkerSize(0.6);
        hResvsRadius_pfx->SetMarkerColor(kRed);
        //hResvsRadius_pfx->Draw("SAME");
	c1->SaveAs(ofile);
	}
}
