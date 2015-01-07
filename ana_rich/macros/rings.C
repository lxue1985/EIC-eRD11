void rings() {
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


	char rootf[5][256]={ "../../../output_HT/frodo_5GeVmuon_1Evts_0degTheta_hist.root",
		"../../../output_HT/frodo_5GeVmuon_1Evts_5degTheta_hist.root",
		"../../../output_HT/frodo_5GeVmuon_2Evts_5degTheta_hist.root",
		"../../../output_HT/frodo_5GeVmuon_3Evts_5degTheta_hist.root", 
		"../../../output_HT/frodo_5GeVmuon_3Evts_10degTheta_hist.root"};
	char filenname[5][256]={ "h5GeV_1Evts_0degTheta","h5GeV_1Evts_5degTheta", "h5GeV_2Evts_5degTheta_RndPhi", "h5GeV_3Evts_5degTheta_RndPhi", "h5GeV_3Evts_10degTheta_RndPhi"};

	TCanvas *c1 = new TCanvas("c1","c1",700,700);
	c1->cd();
	c1->SetTopMargin(0.12);
	c1->SetBottomMargin(0.12);
	c1->SetLeftMargin(0.12);
	c1->SetRightMargin(0.12);

	for(int i=0; i<5; i++){
	char outfile[256];
	sprintf(outfile,"figs/%s_Ring.pdf",filenname[i]);
	cout<<"processing file: "<<rootf[i]<<"output figure: "<<outfile<<endl;
	
	TFile *f1 = new TFile(rootf[i]);
	hPhotoDetXY->GetXaxis()->SetTitle("X (mm)");
	hPhotoDetXY->GetYaxis()->SetTitle("Y (mm)");
	hPhotoDetXY->GetYaxis()->SetTitleColor(kBlack);
	hPhotoDetXY->GetYaxis()->SetTitleSize(0.05);
	hPhotoDetXY->GetXaxis()->SetTitleSize(0.05);
	hPhotoDetXY->SetMarkerStyle(21);
	hPhotoDetXY->SetMarkerSize(1);
	hPhotoDetXY->SetMarkerColor(kRed);
	hPhotoDetXY->Draw("");
	c1->SaveAs(outfile);
	}

}
