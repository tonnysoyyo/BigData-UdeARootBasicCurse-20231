//https://root.cern.ch/doc/master/rf204a__extendedLikelihood_8C.html

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
//#include "RooArgusBG.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void Example5_pull(){

  // Declare observable x
  RooRealVar x("x","x",0,11) ;
  
  // Create two Gaussian PDFs g1(x,mean1,sigma) anf g2(x,mean2,sigma) and their parameters
  RooRealVar mean("mean","mean of gaussians",5) ;
  RooRealVar sigma1("sigma1","width of gaussians",0.5) ;
  RooRealVar sigma2("sigma2","width of gaussians",1) ;
  
  RooGaussian sig1("sig1","Signal component 1",x,mean,sigma1) ;
  RooGaussian sig2("sig2","Signal component 2",x,mean,sigma2) ;
  
  // Build Chebychev polynomial pdf
  RooRealVar a0("a0","a0",0.5,0.,1.) ;
  RooRealVar a1("a1","a1",0.2,0.,1.) ;
  RooChebychev bkg("bkg","Background",x,RooArgSet(a0,a1)) ;
  
  // Sum the signal components into a composite signal pdf
  RooRealVar sig1frac("sig1frac","fraction of component 1 in signal",0.8,0.,1.) ;
  RooAddPdf sig("sig","Signal",RooArgList(sig1,sig2),sig1frac) ;
  
  // Associated nsig/nbkg as expected number of events with sig/bkg _in_the_range_ "signalRange"
  RooRealVar nsig("nsig","number of signal events",300,0.,2000) ;
  RooRealVar nbkg("nbkg","number of background events",700,0,2000) ;
  
  // Use AddPdf to extend the model. Giving as many coefficients as pdfs switches
  // on extension.
  RooAddPdf  model("model","(sig+bkg", RooArgList(sig,bkg), RooArgList(nsig,nbkg)) ;
  
  
  // S a m p l e   d a t a ,   f i t   m o d e l
  // -------------------------------------------
  //https://root.cern/doc/master/classRooRandom.html
  //RooRandom::randomGenerator()->SetSeed(3);  
  //RooRandom::randomGenerator()->SetSeed(seed);

  
  // Generate events from model so that nsig,nbkg come out to numbers in fit
  //RooDataSet *data = model.generate(x,2000) ;
  RooDataSet *data = model.generate(x) ;
  //RooDataSet *data = model.generate(RooArgSet(x), Extended(kTRUE));

  // Fit model to data
  //model.fitTo(*data, Extended(kTRUE)) ;
  RooFitResult* result = model.fitTo(*data,Extended(kTRUE),Save(kTRUE)); 

  // Plot data and PDF overlaid
  TCanvas *c = new TCanvas("rf109_chi2residpull", "rf109_chi2residpull", 900, 300);
  c->Divide(2);
  c->cd(1);

  //Int_t nbin=100;
  //RooPlot* xframe = x.frame(0,11,nbin);
  RooPlot* xframe = x.frame() ;
  data->plotOn(xframe) ;
  model.plotOn(xframe) ;

  // Construct a histogram with the pulls of the data w.r.t the curve
  RooHist* hpullm2 = xframe->pullHist() ;

  // Show the chi^2 of the curve w.r.t. the histogram
  /*
  Double_t nfloatpars = result->floatParsFinal().getSize();
  Double_t ndof = nbin - nfloatpars;
  Double_t chi2tmp = xframe->chiSquare()*nbin;
  Double_t probChi2 = TMath::Prob(chi2tmp, ndof)*100.0;
  cout<<" Chi2/ndof : "<<xframe->chiSquare()<<" Chi2Prob : "<< probChi2 <<  endl;
  cout<<" Ndof : "<<ndof<< endl;
  cout<<" Chi2 : "<<chi2tmp<< endl; 
  */
  
  model.plotOn(xframe,Components(bkg), LineStyle(kDashed)) ;
  xframe->Draw() ;
  //data->Print("v");

  c->cd(2);
  // Create a new frame to draw the pull distribution
  //RooPlot* framem2 = x.frame(0,11,nbin) ;
  RooPlot* framem2 = x.frame(Title("Pull Distribution")) ;
  framem2->addPlotable(hpullm2,"P") ;
  //framem2->addPlotable(hpullm2,"XP") ;// setting Y error to cero
  framem2->SetYTitle(" (Data-Fit)/#sigma");
  framem2->Draw();

}
