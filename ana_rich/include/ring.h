//////*********************************//////
//////***** Author: Dr. Liang Xue *****//////
//////******  Date: 01/06/2015  *******//////
//////*********************************//////

// This class is to define the variables for 
// rings on photonsensor of EIC RICH detector


#ifndef RING_H
#define RING_H


#include <vector>
#include <TVector3.h>
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"

using namespace std;

class ring
{
	public:
		ring(); 
		virtual ~ring() {}

		double RFindX (double X1, double Y1, double X2, double Y2, double X3, double Y3);
		double RFindY (double X1, double Y1, double X2, double Y2, double X3, double Y3);
		double RFindR (TVector3 P1, TVector3 P2, TVector3 P3);

		void FindARing (vector<double> X, vector<double> Y);
		double GetR() {return Rrec;}
		double GetX() {return Xrec;}
		double GetY() {return Yrec;}

	protected:
		TH3D *HoughF;
		double Rrec;
		double Xrec;
		double Yrec;

		std::vector<TVector3> PseudoPoints;
		std::vector<TVector3> J1_PseudoPoints;
		std::vector<TVector3> J2_PseudoPoints;
		std::vector<TVector3> J3_PseudoPoints;
		std::vector<TVector3> J4_PseudoPoints;
		std::vector<double> Y1;
		std::vector<double> X1;
		std::vector<double> Y2;
		std::vector<double> X2;
		std::vector<double> Y3;
		std::vector<double> X3;
		std::vector<double> Y4;
		std::vector<double> X4;
		std::vector<double> AllX;
		std::vector<double> AllY;
};

#endif
