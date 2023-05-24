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
void fitData(){
    Float_t mass, tau, tErr;

    TFile f("BcData.root", "READ");
    TTree *tree = (TTree*) f.Get("tree");

    tree->SetBranchAddress("mass", &mass);
    tree->SetBranchAddress("tau", &tau);
    tree->SetBranchAddress("tErr", &tErr);

    RooRealVar MASS("MASS", "MASS", 6, 7);
    RooDataSet massDS("dataSet", "dataSet", RooArgSet(MASS));

    //Se crea dataset para la masa
    for(int event = 0; event < tree->GetEntries(); event++){
        tree->GetEntry(event);
        MASS = mass;
        massDS.add(RooArgSet(MASS));
    }

    //Variable m
    RooRealVar m("m", "m", 6, 6.5);

    //Señal
    RooRealVar mean1("mean1", "mean1", 6.27, 6.25, 6.3);
    RooRealVar sigma1("sigma1", "sigma1", .1, 0, 0.5);
    RooGaussian sig1("sig1", "sig1", m, mean1, sigma1);

    // RooRealVar mean2("mean2", "mean2", 6.2, 6.15, 6.25);
    // RooRealVar sigma2("sigma2", "sigma2", .05, 0, 0.1);
    // RooGaussian sig2("sig2", "sig2", m, mean2, sigma2);

    // RooRealVar sig1frac("sig1frac", "sig1frac", 0.8, 0., 1.);
    // RooAddPdf signal("sig", "sig", RooArgList(sig1, sig2), sig1frac);

    //Background
    RooRealVar a0("a0", "a0", 0.5, 0., 1);
    RooRealVar a1("a1", "a1", 0.5, 0, 1);

    RooPolynomial bkg("bkg", "bkg", m, RooArgList(a0));

    //Numero de eventos
    RooRealVar nsig("nsig","nsig",1000,0.,3000);
    RooRealVar nbkg("nbkg","nbkg",2000,0.,3000);
    
    //Pdf total
    RooAddPdf model("model","sig+bkg", RooArgList(sig1,bkg), RooArgList(nsig,nbkg));

    //Fit
    model.fitTo(massDS, Extended(kTRUE), Save(kTRUE));
    
    //Histograma de masa
    TH1F mhist("hist", "hist", 100, 6, 6.5);
    mhist.Fill(mass);
    RooDataHist mh("mh", "mh", m, Import(mhist));

    //Grafico
    TCanvas* c = new TCanvas("c", "c", 800, 600);
    RooPlot* frame = m.frame();

    mh.plotOn(frame);
    model.plotOn(frame);

    frame->Draw();
    c->Draw();
}