#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;

void Example1_myBasic(){
  RooRealVar x("x", "x", -10, 10);
  RooRealVar mean("mean", "mean of gaussian", 1, -10, 10);
  RooRealVar sigma("sigma", "width of gaussian", 1, 0.1, 10);
  
  RooGaussian gauss("gauss", "gaussian PDF", x, mean, sigma);
  
  RooDataSet *data = gauss.generate(x, 10000);
  
  gauss.fitTo(*data);
 
  RooPlot *xframe2 = x.frame();
  data->plotOn(xframe2);
  gauss.plotOn(xframe2);
  xframe2->Draw();

}
