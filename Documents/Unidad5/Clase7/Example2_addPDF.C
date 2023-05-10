#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooArgusBG.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void Example2_addPDF(){
  
  // Build two Gaussian PDFs
  RooRealVar x("x","x",0,10) ;
  RooRealVar mean1("mean1","mean of gaussian 1",2) ;
  RooRealVar mean2("mean2","mean of gaussian 2",3) ;
  RooRealVar sigma("sigma","width of gaussians",1) ;
  RooGaussian gauss1("gauss1","gaussian PDF",x,mean1,sigma) ;  
  RooGaussian gauss2("gauss2","gaussian PDF",x,mean2,sigma) ;  
  
  // Build Argus background PDF 
  RooRealVar argpar("argpar","argus shape parameter",-1.0) ;
  RooRealVar cutoff("cutoff","argus cutoff",9.0) ;
  RooArgusBG argus("argus1","Argus PDF",x,cutoff,argpar) ;
  
  // Add the components
  RooRealVar g1frac("g1frac","fraction of gauss1",0.5) ;
  RooRealVar g2frac("g2frac","fraction of gauss2",0.1) ;
  RooAddPdf  sum("sum","g1+g2+a",RooArgList(gauss1,gauss2,argus),RooArgList(g1frac,g2frac)) ;

  // Generate a toyMC sample
  RooDataSet *data = sum.generate(x,10000) ;
  
  // Plot data and PDF overlaid
  RooPlot* xframe = x.frame() ;
  data->plotOn(xframe) ;
  sum.plotOn(xframe) ;
  
  // Plot only argus and gauss2
  sum.plotOn(xframe,Components(RooArgSet(argus,gauss2))) ;//Multiple component selection
  //sum.plotOn(xframe,Components(argus),LineStyle(kDashed)) ;//by name
  //sum.plotOn(xframe,Components("argus1"),LineStyle(kDashed)) ;//by reference
  //sum.plotOn(xframe,Components(argus,gauss2)) ;//Multiple component selection
  //sum.plotOn(xframe,Components("argus1,gauss2")) ;//Multiple component selection

  xframe->Draw() ;

  //RooArgSet *paramList = sum.getParameters(data) ;
  //paramList->Print("v") ;
  //sum.Print("t") ;

  
}
