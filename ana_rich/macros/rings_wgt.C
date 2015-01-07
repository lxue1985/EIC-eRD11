void rings_wgt () {
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


 	char rootf[256]="../../output_pftcase/eic_rich_output_mu-_hist.root";

	TCanvas *c1 = new TCanvas("c1","c1",2100,500);
	c1->Divide(3,1);

	char ofile[256];
	sprintf(ofile,"figs/rings.png"); 
	cout<<"processing file: "<<rootf<<";    output file: "<<ofile<<endl;
	
	TFile *f1 = new TFile(rootf);
	c1->cd(1);
	hPhotoDetXY_Weight1Evt_SbKCs->SetTitle("cherenkov ring weighted by QE (SbCsK)");
	hPhotoDetXY_Weight1Evt_SbKCs->GetXaxis()->SetTitle("X (mm)");
	hPhotoDetXY_Weight1Evt_SbKCs->GetYaxis()->SetTitle("Y (mm)");
	hPhotoDetXY_Weight1Evt_SbKCs->GetZaxis()->SetTitle("photon electron");
	hPhotoDetXY_Weight1Evt_SbKCs->GetYaxis()->SetTitleColor(kBlack);
	hPhotoDetXY_Weight1Evt_SbKCs->GetYaxis()->SetTitleSize(0.05);
	hPhotoDetXY_Weight1Evt_SbKCs->GetXaxis()->SetTitleSize(0.05);
	hPhotoDetXY_Weight1Evt_SbKCs->GetYaxis()->SetTitleOffset(1.2);
	hPhotoDetXY_Weight1Evt_SbKCs->GetXaxis()->SetTitleOffset(1.2);
	hPhotoDetXY_Weight1Evt_SbKCs->GetZaxis()->SetTitleOffset(1.3);
	hPhotoDetXY_Weight1Evt_SbKCs->Draw("surf");
	TLegend *leg = new TLegend(0.1,0.94,0.5,1.);
	leg->SetTextSize(0.055);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hPhotoDetXY_Weight1Evt_GaAsP,"cherenkov ring weighted by QE (SbCsK)","");
	leg->Draw();

	c1->cd(2);
	hPhotoDetXY_Weight1Evt_GaAsP->GetXaxis()->SetTitle("X (mm)");
	hPhotoDetXY_Weight1Evt_GaAsP->GetYaxis()->SetTitle("Y (mm)");
	hPhotoDetXY_Weight1Evt_GaAsP->GetZaxis()->SetTitle("photon electron");
	hPhotoDetXY_Weight1Evt_GaAsP->GetYaxis()->SetTitleColor(kBlack);
	hPhotoDetXY_Weight1Evt_GaAsP->GetYaxis()->SetTitleSize(0.05);
	hPhotoDetXY_Weight1Evt_GaAsP->GetXaxis()->SetTitleSize(0.05);
	hPhotoDetXY_Weight1Evt_GaAsP->GetYaxis()->SetTitleOffset(1.2);
	hPhotoDetXY_Weight1Evt_GaAsP->GetXaxis()->SetTitleOffset(1.2);
	hPhotoDetXY_Weight1Evt_GaAsP->GetZaxis()->SetTitleOffset(1.3);
	hPhotoDetXY_Weight1Evt_GaAsP->Draw("surf");
	TLegend *leg = new TLegend(0.1,0.94,0.5,1.);
	leg->SetTextSize(0.055);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hPhotoDetXY_Weight1Evt_GaAsP,"cherenkov ring weighted by QE (GaAsP)","");
	leg->Draw();

	c1->cd(3);
	hPhotoDetXY_Weight1Evt_GaAs->SetTitle("cherenkov ring weighted by QE (GaAs)");
	hPhotoDetXY_Weight1Evt_GaAs->GetXaxis()->SetTitle("X (mm)");
	hPhotoDetXY_Weight1Evt_GaAs->GetYaxis()->SetTitle("Y (mm)");
	hPhotoDetXY_Weight1Evt_GaAs->GetZaxis()->SetTitle("photon electron");
	hPhotoDetXY_Weight1Evt_GaAs->GetYaxis()->SetTitleColor(kBlack);
	hPhotoDetXY_Weight1Evt_GaAs->GetYaxis()->SetTitleSize(0.05);
	hPhotoDetXY_Weight1Evt_GaAs->GetXaxis()->SetTitleSize(0.05);
	hPhotoDetXY_Weight1Evt_GaAs->GetYaxis()->SetTitleOffset(1.2);
	hPhotoDetXY_Weight1Evt_GaAs->GetXaxis()->SetTitleOffset(1.2);
	hPhotoDetXY_Weight1Evt_GaAs->GetZaxis()->SetTitleOffset(1.3);
	hPhotoDetXY_Weight1Evt_GaAs->Draw("surf");
	TLegend *leg = new TLegend(0.1,0.94,0.5,1.);
	leg->SetTextSize(0.055);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hPhotoDetXY_Weight1Evt_GaAsP,"cherenkov ring weighted by QE (GaAs)","");
	leg->Draw();

	c1->cd();
	c1->SaveAs(ofile);
}
