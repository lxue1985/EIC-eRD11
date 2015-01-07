void display() {
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


 	char rootf[256]= "output_pftcase/display.root";

	TCanvas *c1 = new TCanvas("c1","c1",700,700);
	c1->cd();
	c1->SetTopMargin(0.1);
	c1->SetBottomMargin(0.1);
	c1->SetLeftMargin(0.1);
	c1->SetRightMargin(0.1);

	char infile[256];
	sprintf(infile,"../../%s",rootf); 
	cout<<"processing file: "<<infile<<endl;
	
	TFile *f1 = new TFile(infile);
	flux->Draw("avg_ly:avg_lx:avg_lz>>detector(110,-11.,11.,480,-60.,60,480,-60,60)","avg_z<80 && pid==0","");
	detector->GetXaxis()->SetTitle("Z (mm)");
	detector->GetYaxis()->SetTitle("X (mm)");
	detector->GetZaxis()->SetTitle("Y (mm)");
	detector->GetXaxis()->SetTitleOffset(1.45);
	detector->GetYaxis()->SetTitleOffset(1.55);
	detector->GetZaxis()->SetTitleOffset(1.2);
	detector->GetYaxis()->SetTitleColor(kBlack);
	detector->GetXaxis()->SetTitleSize(0.04);
	detector->GetYaxis()->SetTitleSize(0.04);
	detector->GetZaxis()->SetTitleSize(0.04);
	detector->Draw("");
	c1->SaveAs("figs/displayAegl.png");
}
