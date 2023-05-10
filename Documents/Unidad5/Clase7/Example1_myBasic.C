//credit: https://root.cern/doc/master/rf101__basics_8C.html

#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;
 
void Example1_myBasic()
{
  // S e t u p   m o d e l
   // ---------------------
 
   // Declare variables x,mean,sigma with associated name, title, initial value and allowed range
   RooRealVar x("x", "x", -10, 10);
   RooRealVar mean("mean", "mean of gaussian", 1, -10, 10);
   RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);
 
   // Build gaussian pdf in terms of x,mean and sigma
   RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);
 
   // G e n e r a t e   e v e n t s
   // -----------------------------
 
   // Generate a dataset of 1000 events in x from gauss
   RooDataSet *data = gauss.generate(x, 10000);
 
 
   // F i t   m o d e l   t o   d a t a
   // -----------------------------
 
   // Fit pdf to data
   gauss.fitTo(*data);
 
   //Print values of mean and sigma (that now reflect fitted values and errors)
   //mean.Print();
   //sigma.Print();
 
   // Draw frame on a canvas
   // -----------------------------

   //TCanvas *c = new TCanvas("basic", "basic", 800, 400);
   //RooPlot *xframe2 = x.frame(Title("Gaussian pdf with data"));
   RooPlot *xframe2 = x.frame();
   data->plotOn(xframe2);
   gauss.plotOn(xframe2);
   xframe2->Draw();
}
