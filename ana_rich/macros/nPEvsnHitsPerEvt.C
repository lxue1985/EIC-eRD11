void nPEvsnHitsPerEvt () {
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


 	char rootf[5][256]={ "../../output_pftcase/eic_rich_output_e-_hist.root",
			     "../../output_pftcase/eic_rich_output_mu-_hist.root",
			     "../../output_pftcase/eic_rich_output_pi-_hist.root",
			     "../../output_pftcase/eic_rich_output_kaon-_hist.root", 
			     "../../output_pftcase/eic_rich_output_proton_hist.root"};
 	char particle[5][256]={ "electron","muon", "pion", "kaon", "proton"};

	TCanvas *c1 = new TCanvas("c1","c1",2100,500);
	c1->Divide(3,1);

	for(int i=0; i<5; i++){
		char ofile[256];
		sprintf(ofile,"figs/nPEvsnHitPerEvt_%s.pdf",particle[i]); 
		cout<<"processing file: "<<rootf[i]<<";    output file: "<<ofile<<endl;

		TFile *f1 = new TFile(rootf[i]);

		c1->cd(1);
		hnPhotonElvsnHits_SbKCs->GetYaxis()->SetRangeUser(0.,20.);
		hnPhotonElvsnHits_SbKCs->GetYaxis()->SetTitle("N_{e^{-}}");
		hnPhotonElvsnHits_SbKCs->GetXaxis()->SetTitle("N_{#gamma}");
		hnPhotonElvsnHits_SbKCs->GetYaxis()->SetTitleColor(kBlack);
		hnPhotonElvsnHits_SbKCs->GetYaxis()->SetTitleSize(0.05);
		hnPhotonElvsnHits_SbKCs->GetXaxis()->SetTitleSize(0.05);
		hnPhotonElvsnHits_SbKCs->Draw("colz");
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
		leg->AddEntry(hnPhotonElvsnHits_SbKCs,"N_{e^{-}} vs. N_{#gamma} per cherenkov ring (SbCsK)","");
		leg->Draw();

		c1->cd(2);
                hnPhotonElvsnHits_GaAsP->GetYaxis()->SetRangeUser(0.,20.);
                hnPhotonElvsnHits_GaAsP->GetYaxis()->SetTitle("N_{e^{-}}");
                hnPhotonElvsnHits_GaAsP->GetXaxis()->SetTitle("N_{#gamma}");
                hnPhotonElvsnHits_GaAsP->GetYaxis()->SetTitleColor(kBlack);
                hnPhotonElvsnHits_GaAsP->GetYaxis()->SetTitleSize(0.05);
                hnPhotonElvsnHits_GaAsP->GetXaxis()->SetTitleSize(0.05);
                hnPhotonElvsnHits_GaAsP->Draw("colz");
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
                leg->AddEntry(hnPhotonElvsnHits_GaAsP,"N_{e^{-}} vs. N_{#gamma} per cherenkov ring (GaAsP)","");
                leg->Draw();

		c1->cd(3);
                hnPhotonElvsnHits_GaAs->GetYaxis()->SetRangeUser(0.,20.);
                hnPhotonElvsnHits_GaAs->GetYaxis()->SetTitle("N_{e^{-}}");
                hnPhotonElvsnHits_GaAs->GetXaxis()->SetTitle("N_{#gamma}");
                hnPhotonElvsnHits_GaAs->GetYaxis()->SetTitleColor(kBlack);
                hnPhotonElvsnHits_GaAs->GetYaxis()->SetTitleSize(0.05);
                hnPhotonElvsnHits_GaAs->GetXaxis()->SetTitleSize(0.05);
                hnPhotonElvsnHits_GaAs->Draw("colz");
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
                leg->AddEntry(hnPhotonElvsnHits_GaAs,"N_{e^{-}} vs. N_{#gamma} per cherenkov ring (GaAs)","");
                leg->Draw();

		c1->SaveAs(ofile);
	}
}
