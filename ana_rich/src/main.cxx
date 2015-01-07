//////*********************************//////
//////***** Author: Dr. Liang Xue *****//////
//////******  Date: 01/06/2015  *******//////
//////*********************************//////

// This is to the main program to study the 
// Electron Ion Collider Ring Image Cherenkov
// detector


#include <iostream> 
#include <fstream>
#include <stdlib.h>
#include <cmath> 
#include <math.h> 
#include <TFile.h>
#include <TF1.h>
#include <TTree.h>
#include <TChain.h>
#include <TRandom.h>
#include "../include/event.h"
#include "../include/hit.h"
#include "../include/material.h"
#include "../include/ring.h"
#include "../include/ntuple.h"

using namespace std;

void writeHist(TFile *filename);
bool IsPhoton(hit *ahit, int i);
bool IsReflection(hit *ahit, int i);
bool IsOnAerogel(hit *ahit, int i);
bool IsOnPhotonSensor(hit *ahit, int i);
void Smearing2D(double inx, double iny, double& outx, double& outy);

int main(int argc, char **argv)
{
	cout<<"//////////////////////////////////////////////"<<endl;
	cout<<endl;
	cout<<"this program start at "<<endl;
	system("date");
	cout<<endl;
	cout<<"//////////////////////////////////////////////"<<endl;

	if(argc!=3 && argc!=1) return 0;

	char *FileInput=0;
	char *FileOutput=0;

	if(argc==1){
		FileInput  = "example.list";
		FileOutput = "example.root";
	}
	else if(argc==3){
		FileInput = argv[1];
		FileOutput = argv[2];
	}

	const double DEG=180./3.1415926;
	bool use_SbKCs=true;
	bool use_GaAsP=false;
	bool use_GaAs=false;

	char fspace[256];
	sprintf(fspace,"%s",FileOutput);
	TFile *fFile = new TFile(fspace,"RECREATE");
	ntuple *ntp = new ntuple();

	TChain *fevt  = new TChain("generated");
	TChain *fhit  = new TChain("eic_rich");

	int fileNumber = 0;
	char FileList[512];
	ifstream* inputStream = new ifstream;
	inputStream->open(FileInput);
	if (!(inputStream)) {
		printf("can not open list file\n");
		return 0;
	}
	for (;inputStream->good();) {
		inputStream->getline(FileList,512);

		if(strstr(FileList,".root")==NULL) {
			printf("%s is not a root-file address!!!\n",FileList);
			continue;
		}
		if  ( inputStream->good()) {
			TFile *ftmp = new TFile(FileList);
			if(!ftmp||!(ftmp->IsOpen())||!(ftmp->GetNkeys())) {
				printf(" file %s error in opening!!!\n",FileList);
			}
			else {
				printf(" read in file %s\n",FileList);
				fevt->Add(FileList);
				fhit->Add(FileList);
				fileNumber++;
			}
			delete ftmp;
		}
	}
	delete inputStream;
	printf(" files read in %d\n",fileNumber);

	event *aevt = new event(fevt);  /// declear and save info to branchs for event
	hit *ahit = new hit(fhit);	/// declear and save info to branchs for track
	material *mat = new material(); //// initialize the material
	TRandom *rd = new TRandom();    /// random number generator

	int nevent = (int)fevt->GetEntries();
	cout << "total number of events:  " << nevent << endl;
	for (Int_t i=0;i<nevent;i++) { 
		if(i%100==0) cout << "processing event:  " << i << " ;"<<endl;
		fevt->GetEntry(i);  

		int pid_gen=0;
		double px_gen=0;
		double py_gen=0;
		double pz_gen=0;
		double vx_gen=0;
		double vy_gen=0;
		double vz_gen=0;
		double p_gen=0;
		double theta_gen=0;
		double phi_gen=0;
		// cout<< "tree generated size: "<< aevt->get_pid()->size() <<";    tree flux size:  "<< ahit->get_hitn()->size() <<endl;
		for (unsigned int j=0;j<aevt->get_pid()->size();j++) {
		// cout << aevt->get_pid()->at(j) << " " << aevt->get_px()->at(j) << " " << aevt->get_py()->at(j) << " " << aevt->get_pz()->at(j) << " " << aevt->get_vx()->at(j) << " " << aevt->get_vy()->at(j) << " " << aevt->get_vz()->at(j) << endl; 
			pid_gen=aevt->get_pid()->at(j);
			px_gen=aevt->get_px()->at(j)/1e3;    //in MeV, convert to GeV
			py_gen=aevt->get_py()->at(j)/1e3;	//in MeV, convert to GeV
			pz_gen=aevt->get_pz()->at(j)/1e3;    //in MeV, convert to GeV
			vx_gen=aevt->get_vx()->at(j)/1e1;    //in mm, convert to cm
			vy_gen=aevt->get_vy()->at(j)/1e1;	//in mm, convert to cm
			vz_gen=aevt->get_vz()->at(j)/1e1;    //in mm, convert to cm
			p_gen=sqrt(px_gen*px_gen+py_gen*py_gen+pz_gen*pz_gen);
			theta_gen=acos(pz_gen/p_gen)*DEG;  	//in deg
			phi_gen=atan2(py_gen,px_gen)*DEG;     	//in deg            
		}  

		if(pid_gen==11 && p_gen<0) continue; ///electron
		if(pid_gen==13 && p_gen<0.2) continue; ///muon
		if(pid_gen==-211 && p_gen<0.4) continue; ///pi-
		if(pid_gen==-321 && p_gen<2.) continue; ///kaon-
		if(pid_gen==2212 && p_gen<4.) continue; ///proton

		fhit->GetEntry(i);

		std::vector<double> X;
		std::vector<double> Y;
		X.clear();
		Y.clear();
		double nhitPhoDet(0.0), nhitAerogel(0.0), nel_SbKCs(0.0), nel_GaAsP(0.0), nel_GaAs(0.0);

		int nhits = ahit->get_hitn()->size();
		for (int j=0;j<nhits;j++) {
			if(IsPhoton(ahit,j)&&!IsReflection(ahit,j)&&IsOnAerogel(ahit, j)) nhitAerogel++;
			if(IsPhoton(ahit,j)&&!IsReflection(ahit,j)&&IsOnPhotonSensor(ahit,j)) {
				nhitPhoDet++;
				double out_x(0.), out_y(0.);
				ntp->hPhDetXY_bfSmear->Fill(ahit->get_out_x()->at(j),ahit->get_out_y()->at(j));
				Smearing2D(ahit->get_out_x()->at(j), ahit->get_out_y()->at(j), out_x, out_y);
				//cout<<"in_x: "<<ahit->get_out_x()->at(j)<<";   out_x: "<<out_x
				//<<"in_y: "<<ahit->get_out_y()->at(j)<<";   out_y: "<<out_y << endl;
				if(fabs(out_x)>44.||fabs(out_y)>44.) continue;
				ntp->hPhDetXY_afSmear->Fill(out_x,out_y);

				double photonE = ahit->get_trackE()->at(j);   /// in MeV (GEANT4 default)
				double wavelength = 1240./(photonE*1.e6);  /// MeV->eV,wavelength in "nm"
				ntp->hPhotonWL->Fill(wavelength);
				ntp->hPhotonE->Fill(photonE*1.e6);

				double QE_SbKCs=mat->extrapQE_SbKCs(wavelength);
				if(use_SbKCs && QE_SbKCs>rd->Uniform(0.,1.)){
					nel_SbKCs++;
					X.push_back(out_x);
					Y.push_back(out_y);
				}

				double QE_GaAsP=mat->extrapQE_GaAsP(wavelength);
				if(use_GaAsP && QE_GaAsP>rd->Uniform(0.,1.)){
					nel_GaAsP++; 
					X.push_back(out_x);
					Y.push_back(out_y);
				}

				double QE_GaAs=mat->extrapQE_GaAs(wavelength);
				if(use_GaAs && QE_GaAs>rd->Uniform(0.,1.)){
					nel_GaAs++;
					X.push_back(out_x);
					Y.push_back(out_y);
				}
			}
		}
		ntp->hnHitPerEvtvsMom->Fill(p_gen,nhitPhoDet);
		ntp->hnHitAeglPerEvtvsMom->Fill(p_gen,nhitAerogel);
		ntp->hnPhotonElvsnHits_SbKCs->Fill(nhitPhoDet,nel_SbKCs);
		ntp->hnPhotonElvsnHits_GaAsP->Fill(nhitPhoDet,nel_GaAsP);
		ntp->hnPhotonElvsnHits_GaAs->Fill(nhitPhoDet,nel_GaAs);

		///// Identify the rings after photon position smearing
		ring r;
		r.FindARing(X,Y);
		double Rrec=r.GetR();
		double Xrec=r.GetX();
		double Yrec=r.GetY();
		float ontp[18] = {pid_gen,px_gen,py_gen,pz_gen,vx_gen,vy_gen,vz_gen,theta_gen,phi_gen,nhits,nhitAerogel,nhitPhoDet,nel_SbKCs,nel_GaAsP,nel_GaAs,Rrec,Xrec,Yrec};
		ntp->hntp->Fill(ontp);
	}

	writeHist(fFile);
	delete rd;
	delete mat;
	delete ahit;
	delete aevt;
	delete fhit;
	delete fevt;
	delete ntp;
	delete fFile;

	return 0;
}



void writeHist(TFile *filename)
{
        if(filename != NULL) filename->Write();
        return;
}

bool IsPhoton(hit *ahit, int i)
{
	if(ahit->get_pid()->at(i)==0) return true;
	else return false;
}

bool IsReflection(hit *ahit, int i)
{
	if(ahit->get_out_pz()->at(i)<0.) return true;
	else return false;
}

bool IsOnAerogel(hit *ahit, int i)
{
	if(ahit->get_out_z()->at(i)>=50.5 && ahit->get_out_z()->at(i)<=70.5) return true;
	else return false;
}

bool IsOnPhotonSensor(hit *ahit, int i)
{
	if(ahit->get_out_z()->at(i)>143 && ahit->get_out_z()->at(i)<147) return true;
	else return false;
}

void Smearing2D(double inx, double iny, double& outx, double& outy)
{
	TF1 *fx = new TF1("fx","1/([1]*sqrt(2*3.1415926))*exp(-1*pow(x-[0],2)/(2.*[1]*[1]))",inx-20.,inx+20.);
	fx->SetParameter(0,inx);
	fx->SetParameter(1,1.); //// 1 mm smearing in photon position x
	outx = fx->GetRandom();

	TF1 *fy = new TF1("fy","1/([1]*sqrt(2*3.1415926))*exp(-1*pow(x-[0],2)/(2.*[1]*[1]))",iny-20.,iny+20.);
	fy->SetParameter(0,iny);
	fy->SetParameter(1,1.); //// 1 mm smearing in photon position y
	outy = fy->GetRandom();

	delete fx;
	delete fy;
	return ;
}
