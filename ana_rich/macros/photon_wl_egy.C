void photon_wl_egy () {
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

	TCanvas *c1 = new TCanvas("c1","c1",1400,500);
	c1->Divide(2,1);

	char ofile[256];
	sprintf(ofile,"figs/photon_wl_egy.png"); 
	cout<<"processing file: "<<rootf<<";    output file: "<<ofile<<endl;
	
	TFile *f1 = new TFile(rootf);
	c1->cd(1);
	hPhotonE->GetXaxis()->SetTitle("photon energy");
	hPhotonE->GetYaxis()->SetTitle("Counts");
	hPhotonE->GetYaxis()->SetTitleColor(kBlack);
	hPhotonE->GetYaxis()->SetTitleSize(0.05);
	hPhotonE->GetXaxis()->SetTitleSize(0.05);
	hPhotonE->GetYaxis()->SetTitleOffset(1.1);
	hPhotonE->GetXaxis()->SetTitleOffset(1.);
	hPhotonE->GetXaxis()->SetRangeUser(1.5,4.0);
	hPhotonE->Draw("");
	TLegend *leg = new TLegend(0.2,0.94,0.5,1.);
	leg->SetTextSize(0.05);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hPhotonE,"cherenkov photon energy distribution","");
	leg->Draw();

	c1->cd(2);
	hPhotonWL->GetXaxis()->SetTitle("photon wave length (nm)");
	hPhotonWL->GetYaxis()->SetTitle("Counts");
	hPhotonWL->GetYaxis()->SetTitleColor(kBlack);
	hPhotonWL->GetYaxis()->SetTitleSize(0.05);
	hPhotonWL->GetXaxis()->SetTitleSize(0.05);
	hPhotonWL->GetYaxis()->SetTitleOffset(1.1);
	hPhotonWL->GetXaxis()->SetTitleOffset(1.);
	hPhotonWL->GetXaxis()->SetRangeUser(300,650);
	hPhotonWL->Draw("");
	TLegend *leg = new TLegend(0.12,0.94,0.6,1.);
	leg->SetTextSize(0.05);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hPhotonWL,"cherenkov radiation wavelength distribution","");
	leg->Draw();

	c1->cd();
	c1->SaveAs(ofile);
}
