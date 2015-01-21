//////*********************************//////
//////***** Author: Dr. Liang Xue *****//////
//////******  Date: 01/06/2015  *******//////
//////*********************************//////

// This class is to define the ntuple and histogram
// for EIC RICH detector analysis


#include "../include/ntuple.h"

ntuple::ntuple()
{
hntp = new TNtuple("hntp","hntp","pid:px:py:pz:vx:vy:vz:theta:phi:nhit:nhitAegl:nhitPhoDet:nelSbKCs:nelGaAsP:nelGaAs:RrecSbKCs:XrecSbKCs:YrecSbKCs:RrecGaAsP:XrecGaAsP:YrecGaAsP:RrecGaAs:XrecGaAs:YrecGaAs");
hnHitPerEvtvsMom = new TH2D ("hnHitPerEvtvsMom","hnHitPerEvtvsMom",100,0.,10.,200,0.,200.);
hnHitAeglPerEvtvsMom = new TH2D ("hnHitAeglPerEvtvsMom","hnHitAeglPerEvtvsMom",100,0.,10.,200,0.,200.);
hPhDetXY_bfSmear = new TH2D ("hPhDetXY_bfSmear","hPhDetXY_bfSmear",88,-44.,44.,88,-44.,44.);
hPhDetXY_afSmear = new TH2D ("hPhDetXY_afSmear","hPhDetXY_afSmear",88,-44.,44.,88,-44.,44.);
hPhDetXY_SbKCs = new TH2D ("hPhDetXY_SbKCs","hPhDetXY_SbKCs",88,-44.,44.,88,-44.,44.);
hPhDetXY_GaAsP = new TH2D ("hPhDetXY_GaAsP","hPhDetXY_GaAsP",88,-44.,44.,88,-44.,44.);
hPhDetXY_GaAs = new TH2D ("hPhDetXY_GaAs","hPhDetXY_GaAs",88,-44.,44.,88,-44.,44.);

hPhotonWL = new TH1D ("hPhotonWL","hPhotonWL",100,250.,750.);
hPhotonE = new TH1D ("hPhotonE","hPhotonE",100,0.,5.);
hnPhotonElvsnHits_SbKCs = new TH2D ("hnPhotonElvsnHits_SbKCs","hnPhotonElvsnHits_SbKCs",50,0.,50.,25,0.,25.);
hnPhotonElvsnHits_GaAsP = new TH2D ("hnPhotonElvsnHits_GaAsP","hnPhotonElvsnHits_GaAsP",50,0.,50.,25,0.,25.);
hnPhotonElvsnHits_GaAs = new TH2D ("hnPhotonElvsnHits_GaAs","hnPhotonElvsnHits_GaAs",50,0.,50.,25,0.,25.);
}
