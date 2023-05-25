#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TAxis.h"
using namespace RooFit;
void toyMonteCarlo(){
    Float_t a0f, a1f, meanf, meanfErr, sigmaf, sigmafErr, nbkgf, nbkgfErr, nsigf, nsigfErr;

    ifstream entrada("fitData.txt");
    if ( !entrada ) 
    {
      cout << "No se pudo abrir el archivo entrada fit pr bins" << endl;
      exit( 1 );
    }
    entrada >> a0f >> a1f >> meanf >> meanfErr >> nbkgf >> nbkgfErr >> nsigf >> nsigfErr;
    entrada.close();

    RooRealVar m("m", "m", 6.05, 6.5);

    //Señal
    RooRealVar mean("mean", "mean", 6.25, 6.3); mean.setVal(meanf); mean.setError(meanfErr);
    RooRealVar sigma("sigma", "sigma", 0.005, 0.05); sigma.setVal(sigmaf); sigma.setError(sigmafErr);
    RooGaussian sig("sig", "sig", m, mean, sigma);

    //Background
    RooRealVar a0("a0", "a0", -10,10); a0.setVal(a0f);
    RooRealVar a1("a1", "a1", -10,10); a1.setVal(a1f);

    RooChebychev bkg("bkg", "bkg", m, RooArgList(a0, a1));

    //Numero de eventos
    RooRealVar nsig("nsig","nsig",1000,0.,13000); nsig.setVal(nsigf); nsig.setError(nsigfErr);
    RooRealVar nbkg("nbkg","nbkg",2000,0.,13000); nbkg.setVal(nbkgf); nbkg.setError(nbkgfErr);
    
    //Pdf total
    RooAddPdf model("model","sig+bkg", RooArgList(sig,bkg), RooArgList(nsig,nbkg));

    //Fit
    RooRealVar massPull("massPUll", "massPull", -3,3);
    RooRealVar nsigPull("nsigPull", "nsigPull", -3,3);
    RooRealVar nbkgPull("nbkgPull", "nbkgPull", -3,3);

    RooDataSet mpDset("massPUll", "massPull", RooArgSet(massPull));
    RooDataSet nsigDset("nsigDset", "nsigDset", RooArgSet(nsigPull));
    RooDataSet nbkgDset("nbkgDset", "nbkgDset", RooArgSet(nbkgPull));

    for(int i=0; i<100; i++){
      //RooRandom::randomGenerator()->SetSeed(1);
      RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
      RooMsgService::instance().setSilentMode(kTRUE);
      RooMsgService::instance().setStreamStatus(1,false);
      RooMsgService::instance().getStream(1).removeTopic(Integration);  
      RooMsgService::instance().getStream(1).removeTopic(Minimization);  
      RooMsgService::instance().getStream(1).removeTopic(Fitting);  
      RooMsgService::instance().getStream(1).removeTopic(NumIntegration);
      RooMsgService::instance().getStream(1).removeTopic(Optimization);
      RooMsgService::instance().getStream(1).removeTopic(ObjectHandling);
      RooMsgService::instance().getStream(1).removeTopic(Eval);
      RooMsgService::instance().Print();

      RooDataSet *toyData = model.generate(RooArgSet(m), Extended(kTRUE));
      RooFitResult* result = model.fitTo(*toyData, Extended(kTRUE), Save(kTRUE));

      massPull.setVal((mean.getVal() - meanf) / mean.getError());
      mpDset.add(RooArgSet(massPull));

      nsigDset.add(RooArgSet((nsig.getVal() - nsigf) / nsig.getError()));
      nbkgDset.add(RooArgSet((nbkg.getVal() - nbkgf) / nbkg.getError()));
    }

    TCanvas* c2 = new TCanvas("c2", "c2", 800, 600);
    RooPlot* mframe2 = massPull.frame();
    mpDset.plotOn(mframe2);
    mframe2->Draw();
    c2->Draw();
    c2->SaveAs("./plots/monteCarlo.png");
}