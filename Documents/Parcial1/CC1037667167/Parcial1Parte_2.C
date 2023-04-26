#include <iostream>
#include <stdio.h>
#include "TF1.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TGraphMultiErrors.h"
#include "TGraphAsymmErrors.h" 
#include "TLegend.h"

{
//Funcion para fitear---------------------------------------------------------------------------------------------------
Double_t Fit_Func(Double_t *X , Double_t *par){
    Double_t x = X[0] , A = par[0] , B = par[1] ,  C = par[2]  , D = par[3]   ;
    return    A*TMath::Exp(-B*x + C) + D ;}    


// Canvas y Pads -------------------------------------------------------------------------------------------------------
TCanvas *c1 = new TCanvas("c1","Parcial 1 Parte 2",0,0, 800 , 450);
//c1->Divide(2. , 1. , 0.01 , 0.1 );
TPad *pad1 = new TPad("pad1" , "" , 0.01 , 0.0 , 0.6098, 0.99);
TPad *pad2 = new TPad("pad2" , "" , 0.5489 , 0.0 , 0.99 , 0.99 );
pad1->SetBorderSize (0);
pad2->SetBorderSize (0);
pad1->Draw();
pad2->Draw();

//Grafico Izquiedo:-------------------------------------------------------------------------------------------
pad1->cd();
//Datos Negros:
const Int_t npl1 = 12;
Double_t Intervalosl1[npl1+1] = {12. , 13. , 14. , 15. ,16. , 18. ,20. ,23. ,26. , 29. ,34. ,45. , 70. };     
Double_t *xl1 = new Double_t [npl1];  //puntos x
for (int i = 0 ; i<npl1 ; i++){ xl1[i] = .500*(Intervalosl1[i] + Intervalosl1[i + 1]);}
Double_t yl1[npl1] = {0.1314 , 0.1196 , 0.1165 , 0.1154 , 0.1135 , 0.1106 , 0.1105 , 0.1110  , 0.1091  , 0.1095 , 0.1088 , 0.1117}; //puntos y
Double_t *exll1 = new Double_t[npl1]; //Lon barra izquierda=Derecha
for (int i = 0 ; i<npl1 ; i++){exll1[i] = .500*( - Intervalosl1[i] + Intervalosl1[i + 1]);}
Double_t eylstatl1[npl1] = {0.021*0.1314 , .016*0.1196 , .013*0.1165 , .012*0.1154 , .008*0.1135 , 0.008*0.1106 , 0.007*0.1105 , 0.008*0.1110  , 0.009*0.1091  , 0.009*0.1095 , 0.009*0.1088 , 0.013*0.1117}; //Lon barra Inferior = Superior
Double_t eylsysl1[npl1]  = {0.031*0.1314 , 0.027*0.1196 , 0.024*0.1165 , 0.026*0.1154 , 0.026*0.1135 , 0.028*0.1106 , 0.029*0.1105 , 0.026*0.1110  , 0.032*0.1091  , 0.023*0.1095 , 0.028*0.1088 , 0.026*0.1117};

auto l1 = new TGraphMultiErrors("l1", "", npl1, xl1, yl1, exll1, exll1, eylstatl1, eylstatl1);
l1->AddYError(npl1, eylsysl1, eylsysl1);
l1->SetMarkerStyle(20);
l1->GetAttFill(1)->SetFillStyle(1);
l1->GetXaxis()->SetTitle("p_{T}(GeV)");
l1->GetXaxis()->CenterTitle(true);
l1->GetXaxis()->SetTitleFont(52);
l1->GetXaxis()->SetTitleSize(.04);
l1->GetXaxis()->SetLimits(-0.01, 75);
//l1->GetXaxis()->SetTitleOffset(0.8);
l1->GetXaxis()->SetNdivisions(4., 4. , 0.);

l1->GetYaxis()->SetRangeUser(0.07, .139);
l1->GetYaxis()->SetNdivisions(4.,4.,0.);
l1->GetYaxis()->SetTitle("R_{s}");
l1->GetYaxis()->SetTitleFont(52);
l1->GetYaxis()->SetTitleSize(.04);
l1->GetYaxis()->SetTitleOffset(0.8);
l1->Draw("APSE ; ; 5 s=0.5" ); 

//Fit------------------------------------------------------------------------------------

TF1 *My_Fit = new TF1("My_Fit" , Fit_Func , 11.97 , 70 , 4);
My_Fit->SetParNames("A","B","C","D");
My_Fit->SetParameters(.3,.4,2.42,.1);
My_Fit->SetLineWidth(2);
My_Fit->SetLineColor(kBlue);
l1->Fit(My_Fit,"LR");

//Obtener parametros del ajuste:
Double_t A = My_Fit->GetParameter(0); B = My_Fit->GetParameter(1) , C = My_Fit->GetParameter(2) , D = My_Fit->GetParameter(3);
Double_t eA = My_Fit->GetParError(0) , eB = My_Fit->GetParError(1) , eC = My_Fit->GetParError(2) , eD = My_Fit->GetParError(3); 

//Datos Rojos: voy a asumir que todos los datos excepto el ultimo son simetricos (a ojo)
const int nl2 = 12;
double xl2[nl2] = { 1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 18.5 };
double yl2[nl2] = { 0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.120 };
double exll2[nl2] = { 0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 4.5 };
double exhl2[nl2] = { 0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 22 };
double eyll2[nl2] = { 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002 };
double eyhl2[nl2] = { 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002 };
  
TGraphAsymmErrors *l2 = new TGraphAsymmErrors(nl2, xl2, yl2, exll2, exhl2, eyll2, eyhl2);
l2->SetMarkerStyle(25);
l2->SetMarkerSize(.5);
l2->SetLineColor(kRed);
l2->SetMarkerColor(kRed);
l2->Draw("Same , PE");

TLegend *Leyenda = new TLegend(.11, 0.13, .63, .42, "");
Leyenda->SetBorderSize(0);
Leyenda->AddEntry(l1, Form("CMS data; |y| < 2.4"), "pe");
Leyenda->AddEntry(My_Fit, Form("Fit to the CMS data"), "l");
Leyenda->AddEntry((TObject*)0, "#bf{#alpha e^{(#beta p_{T} + #gamma)} + #delta}", ""); // Esto es solo para agregar un espacio en blanco en la leyenda
Leyenda->AddEntry(l2, Form("LHCb data; 2 < y < 4.5"), "pe");
//Leyenda->SetEntrySeparation(0.01);
Leyenda->Draw("Same");

TLatex *Annotation0 = new TLatex ();             
Annotation0->SetTextSize (.045); 
//Annotation0->SetTextAlign(20);  //align at top
Annotation0->DrawLatex (50, .133,"CMS");

TLatex *Annotation1 = new TLatex ();             
Annotation1->SetTextSize (.045); 
//Annotation1->SetTextAlign(13);  //align at top
Annotation1->DrawLatex (50, .129,"#bf{L = 61.6 fb^{-1}}");

TLatex *Annotation2 = new TLatex ();             
Annotation2->SetTextSize (.045); 
Annotation2->SetTextAlign(1);  //align at top
Annotation2->DrawLatex (49.1, .124,"#bf{#sqrt{s} = 13 TeV}");

TLatex *Annotation3 = new TLatex ();             
Annotation3->SetTextSize (.035); 
Annotation3->DrawLatex (49.1, .1,"Fit Parameters: ");

TLatex *Annotation4 = new TLatex ();             
Annotation4->SetTextSize (.03); 
Annotation4->DrawLatex (49.1, .097,Form("#alpha = %.3f #pm %.3f" , A , eA));

TLatex *Annotation5 = new TLatex ();             
Annotation5->SetTextSize (.03); 
Annotation5->DrawLatex (49.1, .094,Form("#beta = %.3f #pm %.3f" , B , eB));

TLatex *Annotation6 = new TLatex ();             
Annotation6->SetTextSize (.03); 
Annotation6->DrawLatex (49.1, .091,Form("#gamma = %.3f #pm %.3f" , C , eC));

TLatex *Annotation7 = new TLatex ();             
Annotation7->SetTextSize (.03); 
Annotation7->DrawLatex (49.1, .088,Form("#delta = %.3f #pm %.3f" , D , eD));

//Grafico Derecho :--------------------------------------------------------------------------------------------------------------
pad2->cd();
//Datos:
const Int_t npr = 7;
Double_t Intervalos[npr+1] = {.00 , .25 , .50 , .75 , 1.00 , 1.30 , 1.60 , 2.40};      
Double_t *x = new Double_t [npr];  //puntos x
for (int i = 0 ; i<npr ; i++){x[i] = .5*(Intervalos[i] + Intervalos[i + 1]);}
Double_t y[npr] = {0.1110,0.1104,0.1100,0.1126,0.1117,0.1069,0.1099}; //puntos y
Double_t *exl = new Double_t[npr]; //Lon barra izquierda=Derecha
for (int i = 0 ; i<npr ; i++){exl[i] = .5*( - Intervalos[i] + Intervalos[i + 1]);}
Double_t eylstat[npr] = {.006*0.1110,.006*0.1104,.006*0.1100,.007*0.1126,.008*0.1117,.01*0.1069,.01*0.1099}; //Lon barra Inferior = Superior
Double_t eylsys[npr]  = {.018*0.1110,.02*0.1104,.019*0.1100,.039*0.1126,.043*0.1117,.043*0.1069,.044*0.1099}; //lon box Inferior = Superior

auto R = new TGraphMultiErrors("R", "", npr, x, y, exl, exl, eylstat, eylstat);
R->AddYError(npr, eylsys, eylsys);
R->SetMarkerStyle(20);
R->GetAttFill(1)->SetFillStyle(0);
R->GetXaxis()->SetTitle("|y|");
R->GetXaxis()->CenterTitle(true);
R->GetXaxis()->SetTitleFont(52);
R->GetXaxis()->SetTitleSize(.04);
R->GetXaxis()->SetLimits(-0.1, 2.5);
//R->GetXaxis()->SetTitleOffset(0.);
R->GetXaxis()->SetNdivisions(3., 5. , 0.);

R->GetYaxis()->SetRangeUser(0.07, .138);
R->GetYaxis()->SetNdivisions(4.,4.,0.);
R->GetYaxis()->SetLabelOffset(-999); 
R->Draw("a p s ; ; 5 s=0.5");

TLatex *Annotation = new TLatex ();              
Annotation->SetTextSize (.06); 
Annotation->DrawLatex (.6, .085,"#bf{#it{12 < p_{T} < 70 GeV}}");

c1->Draw();
c1->SaveAs("Parcial1_Parte2.png");

}