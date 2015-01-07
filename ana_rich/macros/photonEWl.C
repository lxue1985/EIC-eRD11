void photonEWl () {
	gROOT->Reset();
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);
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


	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.15);
        c1->SetGridy(0);
        c1->SetGridx(0);
	c1->cd();

	TFile *f1 = new TFile("aerogel.root");
	hPhotonWL->SetLineWidth(2.);
	hPhotonWL->GetXaxis()->SetRangeUser(250.,650.);
	hPhotonWL->GetYaxis()->SetTitle("Counts");
	hPhotonWL->GetXaxis()->SetTitle("optical photon wavelength (nm)");
	hPhotonWL->GetYaxis()->SetTitleColor(kBlack);
	hPhotonWL->GetYaxis()->SetTitleSize(0.05);
	hPhotonWL->GetXaxis()->SetTitleSize(0.05);
	hPhotonWL->Draw("");
	c1->SaveAs("hPhotonWL.png");

	hPhotonE->SetLineWidth(2.);
        hPhotonE->GetXaxis()->SetRangeUser(1.5,4.5);
        hPhotonE->GetYaxis()->SetTitle("Counts");
        hPhotonE->GetXaxis()->SetTitle("optical photon energy (eV)");
        hPhotonE->GetYaxis()->SetTitleColor(kBlack);
        hPhotonE->GetYaxis()->SetTitleSize(0.05);
        hPhotonE->GetXaxis()->SetTitleSize(0.05);
        hPhotonE->Draw("");
	c1->SaveAs("hPhotonE.png");
}
