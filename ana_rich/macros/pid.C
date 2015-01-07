void pid () {
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


 	char rootf[6][256]={ "../../output/eic_rich_output_e-_hist.root",
			     "../../output/eic_rich_output_mu-_hist.root",
			     "../../output/eic_rich_output_pi-_hist.root",
			     "../../output/eic_rich_output_kaon-_hist.root", 
			     "../../output/eic_rich_output_proton_hist.root"};
 	char particle[6][256]={ "electron","muon", "pion", "kaon", "proton"};

	TH2D *pid = new TH2D ("pid","pid",400,0.,10.,200,0.,20.);

	double plowStep[16] = {  0.0, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.6, 3.0, 3.5, 4.0, 4.5 };
	double phighStep[16] = { 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.6, 3.0, 3.5, 4.0, 4.5, 5.0 };

	TCanvas *c1 = new TCanvas("c1","c1",700,500);
	c1->cd();

	char ofile[256];
	sprintf(ofile,"pid/hist_RadiusvsMom.png"); 
	for(int i=0; i<5; i++){
		cout<<"processing file: "<<rootf[i]<<";    output file: "<<ofile<<endl;
		TFile *f1 = new TFile(rootf[i]);
		pid->Add(hRadiusvsMom);
	}

	pid->GetYaxis()->SetRangeUser(0.,20.);
	pid->GetXaxis()->SetTitle("Momentum (GeV/c)");
	pid->GetYaxis()->SetTitle("Ring radius");
	pid->GetYaxis()->SetTitleColor(kBlack);
	pid->GetYaxis()->SetTitleSize(0.05);
	pid->GetXaxis()->SetTitleSize(0.05);
	pid->Draw("col");
	c1->SaveAs(ofile);

	TCanvas *c2 = new TCanvas("c2","c2",1200,1000);
	c2->Divide(4,4);
	char title[256], filename[256], sigs[256];
	sprintf(filename,"pid/pid_hist_PID.pdf");
	for(int i=0; i<16; i++){
	c2->cd(i+1);
	double plow = plowStep[i];
	double phigh = phighStep[i];
	sprintf(title,"mementum range: [%0.1f GeV, %0.1f GeV]",plow, phigh);
	sprintf(sigs,"signal_%0.1f_%0.1f",plow, phigh);

	int binlow = pid->GetXaxis()->FindBin(plowStep[i]); 
	int binhigh = pid->GetXaxis()->FindBin(phighStep[i]); 
	TH1D *pid_py = pid->ProjectionY(sigs,binlow,binhigh-1);
	pid_py->SetTitle(title);
	pid_py->GetXaxis()->SetTitle("Ring radius");
	pid_py->GetYaxis()->SetTitle("Counts");
	pid_py->GetYaxis()->SetTitleColor(kBlack);
	pid_py->GetYaxis()->SetTitleSize(0.05);
	pid_py->GetXaxis()->SetTitleSize(0.05);
	pid_py->GetXaxis()->SetRangeUser(10.,20.);
	pid_py->Draw("");
	}
	c2->SaveAs(filename);
	 
}
