void nHitsPerEvtAgel () {
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
	hnHitAeglPerEvtvsMom->ProjectionY();
	hnHitAeglPerEvtvsMom_py->SetLineWidth(2.);
	hnHitAeglPerEvtvsMom_py->GetXaxis()->SetRangeUser(40.,120.);
	hnHitAeglPerEvtvsMom_py->GetYaxis()->SetTitle("Counts");
	hnHitAeglPerEvtvsMom_py->GetXaxis()->SetTitle("N_{#gamma}");
	hnHitAeglPerEvtvsMom_py->GetYaxis()->SetTitleColor(kBlack);
	hnHitAeglPerEvtvsMom_py->GetYaxis()->SetTitleSize(0.05);
	hnHitAeglPerEvtvsMom_py->GetXaxis()->SetTitleSize(0.05);
	hnHitAeglPerEvtvsMom_py->Draw("");
	hnHitAeglPerEvtvsMom_py->Fit("gaus","","",60,92);
	c1->SaveAs("hnHitAeglPerEvt.png");
}
