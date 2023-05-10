//https://root.cern/doc/master/rf102__dataimport_8C.html

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "TFile.h"

using namespace RooFit;
 
void Example4_ImporOurtree()
{
  // I m p o r t   T T r e e   i n t o   a   R o o D a t a S e t
  // -----------------------------------------------------------
  TFile f("../Clase6/simple.root");
  TTree* t = (TTree*) f.Get ("tree");

  std::cout << "These are the columns Det, En, and Time:" << std::endl;
  for (auto branch : *t->GetListOfBranches()) {
    std::cout << "Branch: " << branch->GetName() << std::endl;
  }

  Double_t emin = 0.0;
  Double_t emax = 30.0;
  Double_t tmin = 0.0;
  Double_t tmax = 20.0;
  
  RooRealVar det("Det","Det",0.0,24.0);// take in count the name, This RooRealvar is complety necesary
  RooRealVar en("En","En",emin,emax);
  RooRealVar time("Time","Time",tmin,tmax);

  RooDataSet *data = new RooDataSet("data", "data", RooArgSet(det,en,time), Import(*t) );
  //RooDataSet *data = new RooDataSet("data", "data", RooArgSet(det,en,time), Import(*t), Cut("Det>5.0 && En>5 && Time<15") );
  data->Print("V");

  
  // I m p o r t   T T r e e   i n t o   a   R o o D a t a S e t (looping and filling)
  // -----------------------------------------------------------
  std::cout << "\n looping and filling " << std::endl;
    
  Int_t mydet;
  Float_t myen , mytime;
  t->SetBranchAddress ("Det" , &mydet);
  t->SetBranchAddress ("En" , &myen);
  t->SetBranchAddress ("Time", &mytime );
  
  RooRealVar det2("det2","det2",0.0,24.0);// take in count the name, This RooRealvar is complety necesary
  RooRealVar en2("en2","en2",emin,emax);
  RooRealVar time2("time2","time2",tmin,tmax);
  RooDataSet *data2 = new RooDataSet("data2", "data2", RooArgSet(det2,en2,time2));
  
  for(int i=0; i<t->GetEntries(); i++)
    {
      t->GetEntry (i);
      /*
      cout << setw( 5) << mydet
	   << setw(12) << mytime
	   << setw(12) << myen << endl;
      */
      det2=mydet;
      en2=myen;
      time2 = mytime;
      data2->add(RooArgSet(det2,en2,time2));   
    }
  data2->Print("V");
}
 
