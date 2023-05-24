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
void fit2D(){
    Float_t mass, tau, tErr;

    TFile f("BcData.root", "READ");
    TTree *tree = (TTree*) f.Get("tree");

    tree->SetBranchAddress("mass", &mass);
    tree->SetBranchAddress("tau", &tau);
    tree->SetBranchAddress("tErr", &tErr);

    RooRealVar MASS("MASS", "Mass (GeV)", 6.05, 6.5); //Observable
    RooRealVar TAU("TAU", "tau (ps)", .3, 2.6); 
    RooRealVar tERR("tERR", "tau_{e} (ps)", .0001, .5); 

    RooDataSet massDS("mdataSet", "mdataSet", RooArgSet(MASS));
    RooDataSet tauDS("tdataSet", "tdataSet", RooArgSet(TAU));
    RooDataSet data("data", "data", RooArgSet(MASS, TAU));

    //Se crea dataset para la masa
    for(int event = 0; event < tree->GetEntries(); event++){
        tree->GetEntry(event);
        if(mass<=6.0 || mass>=6.5) continue;
        if(tau<=.3 || tau>=2.6) continue;
        if(tErr<=.0001 || tErr>=.5) continue;

        if((tau/tErr)<5.0) continue;

        MASS = mass;
        TAU = tau;
        tERR = tErr;
        data.add(RooArgSet(MASS, TAU));
    }

    //Masa
    RooRealVar mean1("mean1", "mean1", 6.27, 6.25, 6.3);
    RooRealVar sigma1("sigma1", "sigma1", .015, 0.005, 0.05);
    RooGaussian sig1("sig1", "sig1", MASS, mean1, sigma1);

    RooRealVar a0("a0", "a0", -10,10);
    RooRealVar a1("a1", "a1", -10,10);

    RooChebychev bkg("bkg", "bkg", MASS, RooArgList(a0, a1));

    //Numero de eventos
    RooRealVar nsig("nsig","nsig",1000,0.,13000);
    RooRealVar nbkg("nbkg","nbkg",2000,0.,13000);
    
    //Pdf total para la masa
    RooAddPdf masa("model","sig+bkg", RooArgList(sig1,bkg), RooArgList(nsig,nbkg));

    //Tiempo de vida
    RooRealVar c("c", "c", -10,10);
    RooExponential lifet("lifet", "lifet", TAU, c);

    RooProdPdf massLifeTime("massLifeTime", "massLifeTime", RooArgSet(masa, lifet));

    RooFitResult* result = massLifeTime.fitTo(data);


    TCanvas* canvas = new TCanvas("c", "c", 1000, 600);

    TPad *pad1 = new TPad("p1", "", 0.01,0.05,0.49, 0.99);
    pad1->SetLeftMargin(0.09);   
    pad1->SetRightMargin(0.019);
    pad1->SetTopMargin(0.09);
    pad1->Draw();

    TPad *pad2 = new TPad("p2", "", 0.51,0.05,0.99,0.99);
    pad2->SetLeftMargin(0.09);
    pad2->SetRightMargin(0.019);  
    pad2->SetTopMargin(0.09);
    pad2->Draw();

    pad1->cd();
    RooPlot* framem = MASS.frame();
    framem->SetTitle("Mass for B_{c} meson");
    framem->SetXTitle("Mass (GeV)");

    data.plotOn(framem);
    massLifeTime.plotOn(framem, LineColor(kViolet-6));
    framem->Draw();

    pad2->cd();
    RooPlot* framet = TAU.frame();
    framet->SetTitle("Life time for B_{c} meson");
    framet->SetXTitle("#tau (ps)");

    data.plotOn(framet);
    massLifeTime.plotOn(framet, LineColor(kViolet-6));
    framet->Draw();

    canvas->Draw();
    canvas->SaveAs("2Dfit.png");
}