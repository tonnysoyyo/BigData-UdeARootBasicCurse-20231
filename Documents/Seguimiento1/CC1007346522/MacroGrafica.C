#include <iostream>
#include <cmath>
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TAxis.h"
#include "TLegend.h"


void MacroGrafica(){
    // Creando el Canvas
    auto Canvas1 = new TCanvas("Canvas1","Canvas1");
    Canvas1->SetFillColor(17);
    Canvas1->SetGrid();
    Canvas1->SetBorderMode(-1);
    Canvas1->SetBorderSize(5);
    
    // Graficando los puntos esperados
    auto GrafExp = new TGraphErrors("macro2_input_expected.txt","%lg %lg %lg");
    GrafExp->SetFillColor(38);
    GrafExp->SetTitle("Measurement XYZ");
    GrafExp->GetXaxis()->SetTitle("length [cm]");
    GrafExp->GetYaxis()->SetTitle("Arb.Units");
    GrafExp->GetYaxis()->SetRangeUser(0,70);

    GrafExp->Draw("A3");

    // Graficando los puntos experimentales
    auto Graf1 = new TGraphErrors("macro2_input_suyo.txt","%lg %*s %lg %lg");
    Graf1->Draw("SPE");  
    Graf1->SetMarkerStyle(24);

    // Ajuste Lineal
    auto LinearFun = new TF1("Linear law","[0]+x*[1]",-1,11);
    LinearFun->SetLineColor(8);
    LinearFun->SetLineStyle(1);
    LinearFun->Draw("Same");

    // Haciendo el ajuste con Fit()
    Graf1->Fit(LinearFun);
    Double_t Parameters[2];
    LinearFun->GetParameters(Parameters);

    
    // Dando un Legend
    auto legend = new TLegend(.1,.7,.5,.9);
    legend->SetNColumns(2);
    legend->SetHeader("Lab. Lesson 2");
    legend->AddEntry(Graf1,"Experiment","PE");
    legend->AddEntry(GrafExp,"Expected","F");
    legend->AddEntry(LinearFun,"Linear Fit","L");
    legend->AddEntry(LinearFun,"Linear Fit (m*x+b)","L");
    legend->AddEntry(LinearFun,("m = "+std::to_string(Parameters[1])).c_str(),"L");
    legend->AddEntry(LinearFun,("b = "+std::to_string(Parameters[0])).c_str(),"L");
    legend->Draw();

    // Guardando Gráfica
    Canvas1->Print("Plot.png");
}