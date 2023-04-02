#include <iostream>
#include <stdio.h>
#include <cmath>
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TH1F.h"
#include "TGraphErrors.h" 
#include "TMultiGraph.h"
#include "TLegend.h"



{

Double_t LinearFunc(Double_t *X , Double_t *par){
    Double_t x = X[0] , m = par[0] , b = par[1];
    return m*x + b;}    

//------------------------------------------------------------------------------------

//Generar un Canvas:
TCanvas *Lienzo = new TCanvas("Lienzo", "Tarea Seguimiento 1", 0, 0, 600, 400);
Lienzo->SetGrid();

//Datos Medidos:
TGraphErrors *Measured = new TGraphErrors("macro2_input_suyo.txt");
/*Measured->GetXaxis()->SetLimits(0,10);
Measured->GetYaxis()->SetRange(0,70);*/
Measured -> SetMarkerStyle(kCircle);
//Measured ->Draw("AP Same");

//Fit:
TF1 *Linear_Fit = new TF1("Linear Fit" , LinearFunc , 0 , 10 , 2);
Linear_Fit->SetParNames("a","b");
Double_t X_min = Measured->GetX()[0] ; X_max = Measured->GetX()[Measured->GetN()];
Double_t Y_min = Measured->GetY()[0] ; Y_max = Measured->GetY()[Measured->GetN()];
Linear_Fit->SetParameters((Y_max - Y_min)/(X_max - X_min),0.);
Linear_Fit->SetLineWidth(2);
Linear_Fit->SetLineStyle(kDashed);
Linear_Fit->SetLineColor(kBlue);
Measured->Fit(Linear_Fit);

//Obtener parametros del ajuste:
Double_t m = Linear_Fit->GetParameter(0); b = Linear_Fit->GetParameter(1);
Double_t em = Linear_Fit->GetParError(0); eb = Linear_Fit->GetParError(1);

//Datos Esperados:
TGraphErrors *Expected = new TGraphErrors("macro2_input_expected.txt");
/*Expected -> GetXaxis()->SetLimits(0,10);
Expected -> GetYaxis()->SetRange(0,70);*/
Expected->SetFillColor(kAzure-9);
Expected->SetFillStyle(1001);
//Expected -> Draw("A3");

//Leyendas:

TLegend *Leyenda = new TLegend(.1 , .9 , .6 , .7 , "Lab. Lesson 2");

Leyenda->AddEntry(Measured,"Measured Points");
auto Text = Form("$y = (%.2f \\pm %.2f) x + (%.2f \\pm %.2f)$", m, em, b, eb);
Leyenda->AddEntry(Linear_Fit,Text,"l");
Leyenda->AddEntry(Expected,"Expected Points");

//-------------------------------------------------------------------------------------------------

//Objeto MultiGraph:
TMultiGraph *mg = new TMultiGraph();
mg -> SetTitle("Measurement  XYZ and Expectation");
mg -> GetXaxis()->SetTitle("lenght[cm]");
mg -> GetYaxis()->SetTitle("Arbs.Units");

//Agregar objetos al MultiGraph:
mg->Add(Expected, "3");
mg->Add(Measured, "AP");

//Dibujar el MultiGraph en el Canvas y las leyendas:
mg->Draw("A");
Leyenda->Draw();

Lienzo->Modified(); Lienzo->Update(); //https://root-forum.cern.ch/t/problems-with-setting-the-range-of-tgraph-tmultigraph/9025/7
mg->GetXaxis()->SetLimits(0, 11.);    //No tengo ni idea de porque no grafica sin esto.
mg->SetMinimum(0.);
mg->SetMaximum(70);
Lienzo->Modified(); Lienzo->Update();

Lienzo->SaveAs("Seguimiento1.png");
}
