//////*********************************//////
//////***** Author: Dr. Liang Xue *****//////
//////******  Date: 01/06/2015  *******//////
//////*********************************//////

// This class is to define the variables for 
// rings on photonsensor of EIC RICH detector


#include <iostream> 
#include <fstream>
#include <stdlib.h>
#include "../include/ring.h"


ring::ring()
{
	Rrec = -999.;
	Xrec = -999.;
	Yrec = -999.;
}

ring::ring(vector<double> X, vector<double> Y)
{
	Rrec = -999.;
	Xrec = -999.;
	Yrec = -999.;
	FindARing(X,Y);
}

void ring::FindARing(vector<double> X, vector<double> Y)
{
	Y1.clear();
	X1.clear();
	Y2.clear();
	X2.clear();
	Y3.clear();
	X3.clear();
	Y4.clear();
	X4.clear();
	J1_PseudoPoints.clear();
	J2_PseudoPoints.clear();
	J3_PseudoPoints.clear();
	J4_PseudoPoints.clear();
	AllX.clear();
	AllY.clear();
	PseudoPoints.clear();

	/// Forming J1,J2,J3,J4 
	if( !X.size() || X.size()!=Y.size()) return;
	for(unsigned int i=0; i<X.size(); i++){
		if(X[i]<0. && Y[i]<0.) {
			X1.push_back(X[i]);
			Y1.push_back(Y[i]);
		}
		else if(X[i]>0. && Y[i]<0.){
			X2.push_back(X[i]);
			Y2.push_back(Y[i]);
		}
		else if(X[i]<0. && Y[i]>0.){
			X3.push_back(X[i]);
			Y3.push_back(Y[i]);
		}
		else if(X[i]>0. && Y[i]>0.){
			X4.push_back(X[i]);
			Y4.push_back(Y[i]);
		}
	}

	cout<< "J1 size: "<<X1.size()<<" X "<<Y1.size()<<"\t J2 size: "<<X2.size()<<" X "<<Y2.size()<< 
	"\t J3 size: "<<X3.size()<<" X "<<Y3.size()<<"\t J4 size: "<<X4.size()<<" X "<<Y4.size()<<endl;
	if(X1.size()!=Y1.size() || X2.size()!=Y2.size() || X3.size()!=Y3.size()||X4.size()!=Y4.size()) cout<<"fatal error happened !!!"<<endl;
	for(unsigned int s=0; s<Y1.size(); s++) J1_PseudoPoints.push_back(TVector3(X1[s],Y1[s],0));
	for(unsigned int s=0; s<Y2.size(); s++) J2_PseudoPoints.push_back(TVector3(X2[s],Y2[s],0));
	for(unsigned int s=0; s<Y3.size(); s++) J3_PseudoPoints.push_back(TVector3(X3[s],Y3[s],0));
	for(unsigned int s=0; s<Y4.size(); s++) J4_PseudoPoints.push_back(TVector3(X4[s],Y4[s],0));
	cout<< "J1 PseudoPoints size: "<<J1_PseudoPoints.size()<<
		"\t J2 PseudoPoints size: "<<J2_PseudoPoints.size()<< 
		"\t J3 PseudoPoints size: "<<J3_PseudoPoints.size()<<
		"\t J4 PseudoPoints size: "<<J4_PseudoPoints.size()<<endl;

	TH3D *HoughF = new TH3D ("HoughF","HoughF",88,-44.,44.,88,-44,44,50,0,50);
	HoughF->Reset();
	//Selecting 3 PseudoPoints in three different quadrants:
	//J1,J2,J3:
	cout<< "Looking for rings in (J1 J2 J3) ...." <<endl;
	if(J1_PseudoPoints.size() >= 1 && J2_PseudoPoints.size() >= 1 && J3_PseudoPoints.size() >= 1)
	{
		for(unsigned int i=0; i<J1_PseudoPoints.size(); i++)
		{
			for(unsigned int j=0; j<J2_PseudoPoints.size(); j++)
			{
				for(unsigned int k=0; k<J3_PseudoPoints.size(); k++)
				{

					double Rad  = RFindR(J1_PseudoPoints[i],J2_PseudoPoints[j],J3_PseudoPoints[k]);
					double Xcen = RFindX(J1_PseudoPoints[i].X(),J1_PseudoPoints[i].Y(),J2_PseudoPoints[j].X(),J2_PseudoPoints[j].Y(),J3_PseudoPoints[k].X(),J3_PseudoPoints[k].Y());
					double Ycen = RFindY(J1_PseudoPoints[i].X(),J1_PseudoPoints[i].Y(),J2_PseudoPoints[j].X(),J2_PseudoPoints[j].Y(),J3_PseudoPoints[k].X(),J3_PseudoPoints[k].Y());
					HoughF->Fill(Xcen,Ycen,Rad);
				}
			}
		}
	}

	//J1,J2,J4:
	cout<< "Looking for rings in (J1 J2 J4) ...." <<endl;
	if(J1_PseudoPoints.size() >= 1 && J2_PseudoPoints.size() >= 1 && J4_PseudoPoints.size() >= 1)
	{
		for(unsigned int i=0; i<J1_PseudoPoints.size(); i++)
		{
			for(unsigned int j=0; j<J2_PseudoPoints.size(); j++)
			{
				for(unsigned int k=0; k<J4_PseudoPoints.size(); k++)
				{
					double Rad  = RFindR(J1_PseudoPoints[i],J2_PseudoPoints[j],J4_PseudoPoints[k]);
					double Xcen = RFindX(J1_PseudoPoints[i].X(),J1_PseudoPoints[i].Y(),J2_PseudoPoints[j].X(),J2_PseudoPoints[j].Y(),J4_PseudoPoints[k].X(),J4_PseudoPoints[k].Y());
					double Ycen = RFindY(J1_PseudoPoints[i].X(),J1_PseudoPoints[i].Y(),J2_PseudoPoints[j].X(),J2_PseudoPoints[j].Y(),J4_PseudoPoints[k].X(),J4_PseudoPoints[k].Y());
					HoughF->Fill(Xcen,Ycen,Rad);
				}
			}
		}
	}

	//J1,J3,J4:
	cout<< "Looking for rings in (J1 J3 J4) ...." <<endl;
	if(J1_PseudoPoints.size() >= 1 && J3_PseudoPoints.size() >= 1 && J4_PseudoPoints.size() >= 1)
	{
		for(unsigned int i=0; i<J1_PseudoPoints.size(); i++)
		{
			for(unsigned int j=0; j<J3_PseudoPoints.size(); j++)
			{
				for(unsigned int k=0; k<J4_PseudoPoints.size(); k++)
				{
					double Rad  = RFindR(J1_PseudoPoints[i],J3_PseudoPoints[j],J4_PseudoPoints[k]);
					double Xcen = RFindX(J1_PseudoPoints[i].X(),J1_PseudoPoints[i].Y(),J3_PseudoPoints[j].X(),J3_PseudoPoints[j].Y(),J4_PseudoPoints[k].X(),J4_PseudoPoints[k].Y());
					double Ycen = RFindY(J1_PseudoPoints[i].X(),J1_PseudoPoints[i].Y(),J3_PseudoPoints[j].X(),J3_PseudoPoints[j].Y(),J4_PseudoPoints[k].X(),J4_PseudoPoints[k].Y());
					HoughF->Fill(Xcen,Ycen,Rad);
				}
			}
		}
	}

	//J2,J3,J4;
	cout<< "Looking for rings in (J2 J3 J4) ...." <<endl;
	if(J2_PseudoPoints.size() >= 1 && J3_PseudoPoints.size() >= 1 && J4_PseudoPoints.size() >= 1)
	{
		for(unsigned int i=0; i<J2_PseudoPoints.size(); i++)
		{
			for(unsigned int j=0; j<J3_PseudoPoints.size(); j++)
			{
				for(unsigned int k=0; k<J4_PseudoPoints.size(); k++)
				{
					double Rad  = RFindR(J2_PseudoPoints[i],J3_PseudoPoints[j],J4_PseudoPoints[k]);
					double Xcen = RFindX(J2_PseudoPoints[i].X(),J2_PseudoPoints[i].Y(),J3_PseudoPoints[j].X(),J3_PseudoPoints[j].Y(),J4_PseudoPoints[k].X(),J4_PseudoPoints[k].Y());
					double Ycen = RFindY(J2_PseudoPoints[i].X(),J2_PseudoPoints[i].Y(),J3_PseudoPoints[j].X(),J3_PseudoPoints[j].Y(),J4_PseudoPoints[k].X(),J4_PseudoPoints[k].Y());
					HoughF->Fill(Xcen,Ycen,Rad);
				}
			}
		}
	}

	/*
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!DO NOT ERASE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Forming PseudoPoints:
	for(unsigned int i=0; i<X.size(); i++){
		AllX.push_back(X[i]);
		AllY.push_back(Y[i]);
	}
	for(unsigned int s=0; s<AllY.size(); s++) PseudoPoints.push_back(TVector3(AllX[s],AllY[s],0));
	cout<< "PseudoPoints size: "<<PseudoPoints.size()<<endl;

	//Full Combinatorial:
	for(unsigned int i=0; i<PseudoPoints.size()-2; i++)
	{
		for(unsigned int j=i+1; j<PseudoPoints.size()-1; j++)
		{
			for(unsigned int k=j+1; k<PseudoPoints.size(); k++)
			{
				double Rad = RFindR(PseudoPoints[i],PseudoPoints[j],PseudoPoints[k]);
				double Xcen = RFindX(PseudoPoints[i].X(),PseudoPoints[i].Y(),PseudoPoints[j].X(),PseudoPoints[j].Y(),PseudoPoints[k].X(),PseudoPoints[k].Y());
				double Ycen = RFindY(PseudoPoints[i].X(),PseudoPoints[i].Y(),PseudoPoints[j].X(),PseudoPoints[j].Y(),PseudoPoints[k].X(),PseudoPoints[k].Y());
				HoughF->Fill(Xcen,Ycen,Rad);
				HoughFxy->Fill(Xcen,Ycen);
				HoughFyr->Fill(Ycen,Rad);
				HoughFxr->Fill(Xcen,Rad);
			}
		}
	}
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	*/

	int xbin, ybin, zbin;
	xbin=0; ybin=0; zbin=0;
	HoughF->GetMaximumBin(xbin, ybin, zbin);

	TAxis *xaxis = HoughF->GetXaxis();
	Xrec=xaxis->GetBinCenter(xbin);

	TAxis *yaxis = HoughF->GetYaxis();
	Yrec=yaxis->GetBinCenter(ybin);

	TAxis *zaxis = HoughF->GetZaxis();
	Rrec=zaxis->GetBinCenter(zbin);

	delete HoughF;

	return;
}

//Define a function which computes the center of the ring from 3 points.
double ring::RFindX (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
	double D = 2*(X1*(Y2-Y3)+X2*(Y3-Y1)+X3*(Y1-Y2));
	double x = ((X1*X1+Y1*Y1)*(Y2-Y3)+(X2*X2+Y2*Y2)*(Y3-Y1)+(X3*X3+Y3*Y3)*(Y1-Y2))/D;
	return x;
}


double ring::RFindY (double X1, double Y1, double X2, double Y2, double X3, double Y3)
{
	double D = 2*(X1*(Y2-Y3)+X2*(Y3-Y1)+X3*(Y1-Y2));
	double y = ((X1*X1+Y1*Y1)*(X3-X2)+(X2*X2+Y2*Y2)*(X1-X3)+(X3*X3+Y3*Y3)*(X2-X1))/D;
	return y;
}

//Define a function which computes the radius of the ring from 3 points.
double ring::RFindR (TVector3 P1, TVector3 P2, TVector3 P3)
{
	double r = ((P1-P2).Mag()*(P2-P3).Mag()*(P3-P1).Mag())/(2*((P1-P2).Cross(P2-P3)).Mag());
	return r;
}

