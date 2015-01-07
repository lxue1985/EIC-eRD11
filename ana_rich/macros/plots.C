void plots () {
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


 	char rootf[5][256]={ "../../../output_HT/frodo_5GeVmuon_1Evts_0degTheta_hist_ringht.root",
			     "../../../output_HT/frodo_5GeVmuon_1Evts_5degTheta_hist_ringht.root",
			     "../../../output_HT/frodo_5GeVmuon_2Evts_5degTheta_hist_ringht.root",
			     "../../../output_HT/frodo_5GeVmuon_3Evts_5degTheta_hist_ringht.root", 
			     "../../../output_HT/frodo_5GeVmuon_3Evts_10degTheta_hist_ringht.root"};
 	char filenname[5][256]={ "h5GeV_1Evts_0degTheta","h5GeV_1Evts_5degTheta", "h5GeV_2Evts_5degTheta_RndPhi", "h5GeV_3Evts_5degTheta_RndPhi", "h5GeV_3Evts_10degTheta_RndPhi"};

	TCanvas *c1 = new TCanvas("c1","c1",1500,500);
	c1->Divide(3,1);

	for(int i=0; i<5; i++){
	char outfile[256];
	sprintf(outfile,"figs/%s.pdf",filenname[i]);
	cout<<"processing file: "<<rootf[i]<<"output figure: "<<outfile<<endl;
	
	TFile *f1 = new TFile(rootf[i]);
	HoughF->GetYaxis()->SetTitleColor(kBlack);

	c1->cd(1);
	gPad->SetTopMargin(0.12);
        gPad->SetBottomMargin(0.12);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.12);
	HoughF->Project3D("XY");
	HoughF_xy->GetYaxis()->SetTitleSize(0.05);
	HoughF_xy->GetXaxis()->SetTitleSize(0.05);
	HoughF_xy->GetZaxis()->SetTitleSize(0.05);
	HoughF_xy->GetYaxis()->SetTitleOffset(1.3);
	HoughF_xy->GetXaxis()->SetTitleOffset(1.3);
	HoughF_xy->GetZaxis()->SetTitleOffset(1.3);
	HoughF_xy->GetZaxis()->SetTitle("Counts");
	HoughF_xy->GetXaxis()->SetTitle("Y (mm)");
	HoughF_xy->GetYaxis()->SetTitle("X (mm)");
	HoughF_xy->Draw("SURF");

	c1->cd(2);
	gPad->SetTopMargin(0.12);
        gPad->SetBottomMargin(0.12);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.12);
	HoughF->Project3D("XZ");
	HoughF_xz->GetYaxis()->SetTitleSize(0.05);
        HoughF_xz->GetXaxis()->SetTitleSize(0.05);
        HoughF_xz->GetZaxis()->SetTitleSize(0.05);
	HoughF_xz->GetYaxis()->SetTitleOffset(1.3);
	HoughF_xz->GetXaxis()->SetTitleOffset(1.3);
	HoughF_xz->GetZaxis()->SetTitleOffset(1.3);
	HoughF_xz->GetZaxis()->SetTitle("Counts");
	HoughF_xz->GetXaxis()->SetTitle("Radius (mm)");
	HoughF_xz->GetYaxis()->SetTitle("X (mm)");
	HoughF_xz->Draw("SURF");

	c1->cd(3);
	gPad->SetTopMargin(0.12);
        gPad->SetBottomMargin(0.12);
        gPad->SetLeftMargin(0.12);
        gPad->SetRightMargin(0.12);
	HoughF->Project3D("YZ");
	HoughF_yz->GetYaxis()->SetTitleSize(0.05);
        HoughF_yz->GetXaxis()->SetTitleSize(0.05);
        HoughF_yz->GetZaxis()->SetTitleSize(0.05);
	HoughF_yz->GetYaxis()->SetTitleOffset(1.3);
	HoughF_yz->GetXaxis()->SetTitleOffset(1.3);
	HoughF_yz->GetZaxis()->SetTitleOffset(1.3);
	HoughF_yz->GetZaxis()->SetTitle("Counts");
	HoughF_yz->GetXaxis()->SetTitle("Radius (mm)");
	HoughF_yz->GetYaxis()->SetTitle("Y (mm)");
	HoughF_yz->Draw("SURF");

	c1->SaveAs(outfile);
	}
}
