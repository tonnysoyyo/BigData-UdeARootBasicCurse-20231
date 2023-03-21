#include <iostream>
#include <cmath>
#include <TH1.h>
#include <TF1.h>
#include <TApplication.h>

// define a function with 3 parameters
Double_t myGf(Double_t *x,Double_t *par) {
  Double_t arg = 0;
  if (par[2]!=0) arg = (x[0] - par[1])/par[2];
  Double_t mygval = par[0]*TMath::Exp(-0.5*arg*arg);
  return mygval; 
}

void myGaussfun() {

  //Defin a histogram
  TH1F *myh1 = new TH1F("myh1","myh1",100,-3,3);
  myh1->FillRandom("gaus",10000);

  TF1 *myfit = new TF1("myfit",myGf,-3,3,3);
  // set the parameters to the mean and RMS of the histogram
  myfit->SetParameters(500,myh1->GetMean(),myh1->GetRMS());
  //myfit->SetParameters(500,0,1);

  // give the parameters meaningful names
  myfit->SetParNames ("Constant","Mean","Sigma");
  
  // call TH1::Fit with the name of the TF1 object
  myh1->Fit("myfit");
}

void StandaloneApplication(int argc, char** argv) {
  // eventually, evaluate the application parameters argc, argv
  // ==>> here the ROOT macro is called
  myGaussfun();

}

int main(int argc, char** argv){

  //myGaussfun();
  TApplication app("ROOT Application", &argc, argv);
  StandaloneApplication(app.Argc(), app.Argv());
  app.Run();

  return 0;
}



