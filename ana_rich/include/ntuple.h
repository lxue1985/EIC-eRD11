//////*********************************//////
//////***** Author: Dr. Liang Xue *****//////
//////******  Date: 01/06/2015  *******//////
//////*********************************//////

// This class is to define the ntuple and histogram
// for EIC RICH detector analysis


#include <vector>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TNtuple.h>

#ifndef NTUPLE_H
#define NTUPLE_H

using namespace std;

class ntuple
{
	public:
		ntuple();
		virtual ~ntuple() {}

		TNtuple *hntp;
		TH2D *hnHitPerEvtvsMom;
		TH2D *hnHitAeglPerEvtvsMom;
		TH2D *hPhDetXY_bfSmear;
		TH2D *hPhDetXY_afSmear;
		TH1D *hPhotonWL;
		TH1D *hPhotonE;
		TH2D *hnPhotonElvsnHits_SbKCs;
		TH2D *hnPhotonElvsnHits_GaAsP;
		TH2D *hnPhotonElvsnHits_GaAs;
};

#endif
