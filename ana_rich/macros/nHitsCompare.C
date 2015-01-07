void nHitsCompare() {
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


 	char rootf[256]= "output_pftcase/display_hist.root";

	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->cd();
	c1->SetTopMargin(0.1);
	c1->SetBottomMargin(0.1);
	c1->SetLeftMargin(0.1);
	c1->SetRightMargin(0.1);

	char infile[256];
	sprintf(infile,"../../%s",rootf); 
	cout<<"processing file: "<<infile<<endl;
	

	TF1 *fit1 = new TF1("fit1","gaus",17.,40.);
	fit1->SetLineColor(kRed);
	TF1 *fit2 = new TF1("fit2","gaus",55.,100.);
	fit2->SetLineColor(kBlue);

	TFile *f1 = new TFile(infile);
	TH1D *hnHitPerEvtvsMom_py=hnHitPerEvtvsMom->ProjectionY();
	hnHitPerEvtvsMom_py->GetXaxis()->SetRangeUser(0.,120.);
	hnHitPerEvtvsMom_py->GetYaxis()->SetRangeUser(0.,110.);
	hnHitPerEvtvsMom_py->GetXaxis()->SetTitle("Number of Optical Photons");
	hnHitPerEvtvsMom_py->GetYaxis()->SetTitle("Counts");
	hnHitPerEvtvsMom_py->GetXaxis()->SetTitleOffset(1.2);
	hnHitPerEvtvsMom_py->GetYaxis()->SetTitleOffset(1.2);
	hnHitPerEvtvsMom_py->GetYaxis()->SetTitleColor(kBlack);
	hnHitPerEvtvsMom_py->GetXaxis()->SetTitleSize(0.04);
	hnHitPerEvtvsMom_py->GetYaxis()->SetTitleSize(0.04);
	hnHitPerEvtvsMom_py->Draw("");
	hnHitPerEvtvsMom_py->Fit("fit1","RMN","",17.,40.);
	fit1->Draw("SAME");
	TH1D *hnHitAeglPerEvtvsMom_py=hnHitAeglPerEvtvsMom->ProjectionY();
	hnHitAeglPerEvtvsMom_py->Draw("SAME");
	hnHitAeglPerEvtvsMom_py->Fit("fit2","RMN","",55.,100.);
	fit2->Draw("SAME");

	float m1 = fit1->GetParameter(1);
	float s1 = fit1->GetParameter(2);
	float m2 = fit2->GetParameter(1);
	float s2 = fit2->GetParameter(2);

	TLatex *tex = new TLatex(20.,95.,"Photon Detector");
	tex->SetTextSize(0.038);
	tex->SetLineWidth(2);
	tex->SetTextFont(42);
	tex->Draw();

	TLatex *tex = new TLatex(65.,58.,"Radiator (Aerogel)");
        tex->SetTextSize(0.038);
        tex->SetLineWidth(2);
        tex->SetTextFont(42);
        tex->Draw();

	char agel[256], phodet[256];
	sprintf(agel,"     mean: %.1f, #sigma: %.1f",m1,s1);
	sprintf(phodet,"     mean: %.1f, #sigma: %.1f",m2,s2);

	TLegend *leg = new TLegend(0.6,0.65,0.8,0.8);
	leg->SetTextSize(0.04);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(fit1,agel,"pl");
	leg->AddEntry(fit2,phodet,"pl");
	leg->Draw();

	c1->SaveAs("figs/nHitsCompare.png");
}
