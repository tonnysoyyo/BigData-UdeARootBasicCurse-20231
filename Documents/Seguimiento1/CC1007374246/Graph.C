#include <iostream>
#include "TGraphErrors.h" 
#include "TCanvas.h"
#include "TF1.h"
#include "TLegend.h"

void Graph(){

//Lienzo
TCanvas *c = new TCanvas("c1","Canvas Example",200,10,600,480);
c->SetGrid();


TGraphErrors *gr1 = new TGraphErrors("macro2_input_expected.txt","%lg %lg %lg "); //Puntos esperados
gr1->SetFillColor(kGreen-10);
gr1->SetTitle("Measurement XYZ and Expectation;""lenght [cm];""Arb.Units");
gr1->Draw("E3ALC");
gr1->GetYaxis()->SetRangeUser(0, 75); //Ajuste de visualización

TGraphErrors *gr2 = new TGraphErrors("macro2_input_suyo.txt","%lg %*s %lg %lg ");//puntos experimentales
gr2->SetMarkerStyle(32);
gr2->SetMarkerColor(kViolet+1);
gr2->SetLineColor(kViolet+1);
gr2->Draw("P");

auto f = new TF1("Linear law","[0]+x*[1]",.5,10);//Ajuste lineal
f->SetLineColor(kRed);
f->SetLineStyle(2);
gr2->Fit(f);
f->Draw("Same");

Double_t parametros[2];
f->GetParameters(parametros);
Double_t b = parametros[0];//intercepto
Double_t m = parametros[1];//pendiente

auto legend = new TLegend(.1,.7,.4,.9); //leyendas del grafico
legend->AddEntry(gr2,"Exp. Points","PE");
legend->AddEntry(gr1,"Teorical points"); 
legend->AddEntry(f,TString::Format("Linear fit \n y = %.2fx %.2f",m,b),"L");
legend->Draw();
c->SaveAs("Tarea1.png");

}