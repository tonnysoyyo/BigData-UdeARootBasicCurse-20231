#include "TCanvas.h"
#include "TGraphMultiErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TPad.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TFitResult.h"
#include "TMath.h"
#include "TFrame.h"

int GrapParcial1(){

  gStyle->SetOptFit(0);
  
  auto Canvas1 = new TCanvas("Canvas1","Canvas Parcial 1",700,450);
  // Canvas1->SetGrid();
  Canvas1->GetFrame()->SetBorderSize(12);

  // Creando Pads
  TPad *pad1 = new TPad("pad1","This is pad1",0.0,0.0,0.687,1.);
  TPad *pad2 = new TPad("pad2","This is pad2",0.62,0.0,1.0,1.);
  pad1->Draw();
  pad2->Draw();

  // En el Pad1:
  pad1->cd();

  auto MGraph1 = new TMultiGraph("MGraph1","");


  //-------- CMS Points ------------
  const Int_t N_points1 = 12;

  // Data Points
  Double_t X[N_points1]           = {12.5, 13.5, 14.5, 15.5, 17.0,  19.0,  21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
  Double_t Y[N_points1]           = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.111,  0.1091, 0.1095, 0.1088, 0.1117};
  Double_t errX_l[N_points1]      = {0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
  Double_t errX_h[N_points1]      = {0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
  Double_t errY_stat_l[N_points1] = {0.0027594, 0.0019136, 0.0015145, 0.0013848, 0.000908, 0.0008848, 0.0007735, 0.000888, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
  Double_t errY_stat_h[N_points1] = {0.0027594, 0.0019136, 0.0015145, 0.0013848, 0.000908, 0.0008848, 0.0007735, 0.000888, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
  Double_t errY_sys_l[N_points1]  = {0.0040734, 0.0032292, 0.002796, 0.0030004, 0.002951, 0.0030968, 0.0032045, 0.002886,  0.0034912, 0.0025185, 0.0030464, 0.0029042};
  Double_t errY_sys_h[N_points1]  = {0.0040734, 0.0032292, 0.002796, 0.0030004, 0.002951, 0.0030968, 0.0032045, 0.002886,  0.0034912, 0.0025185, 0.0030464, 0.0029042};

  // Se crea el objeto TGraphMultiErrors
  auto MultiError1 = new TGraphMultiErrors("MultiError1", "", N_points1,X , Y, errX_l, errX_h, errY_stat_l, errY_stat_h);
  MultiError1->AddYError(N_points1, errY_sys_l, errY_sys_h);
  
  // Se estiliza
  MultiError1->SetMarkerStyle(20);
  MultiError1->SetMarkerSize(0.9);
  MultiError1->GetAttFill(1)->SetFillStyle(0);
  

  // Se añade al MultiGraph
  MGraph1->Add(MultiError1);

  // Fit CMS Points

  // Definimos funcion exponencial para el fit
  auto Func = new TF1("Fit","[0]+[1]*TMath::Exp(-1*[2]*(x-[3]))",0,72);
  
  // Definimos los Parametros iniciales de manera que sea mas facil que se realice el fit
  Func->SetParameters(MultiError1->GetMean(2),.1,.4,X[0]);

  Func->SetLineColor(kBlue); // Color de la linea

  // Se realiza el fit
  TFitResultPtr Fit_Result = MultiError1->Fit(Func,"SR"); 
  // Definimos Objeto TFitResultPtr para obtener los parametros del fit

  //------- LHCb Points -------

  const Int_t N_points2 = 12;

  // Data Points
  Double_t X2[N_points2]           = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.5, 19.0};
  Double_t Y2[N_points2]           = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.12};
  Double_t errX_l2[N_points2]      = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.0, 5.0};
  Double_t errX_h2[N_points2]      = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.5, 21.0};
  Double_t errY_stat_l2[N_points2] = {0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002};
  Double_t errY_stat_h2[N_points2] = {0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002};
  
  // Se crea el objeto TGraphMultiErrors
  auto MultiError2 = new TGraphMultiErrors("MultiError2", "",N_points2,X2 , Y2, errX_l2, errX_h2, errY_stat_l2, errY_stat_h2);

  // Se estiliza
  MultiError2->SetMarkerStyle(25);
  MultiError2->SetMarkerColor(kRed);
  MultiError2->SetMarkerSize(0.6);
  MultiError2->SetLineColor(kRed);
  MultiError2->GetAttLine(0)->SetLineColor(kRed);
  MultiError2->SetFillColor(kRed);
  MultiError2->GetAttFill(0)->SetFillColor(kRed);

  // Se añade al MultiGraph
  MGraph1->Add(MultiError2);

  // Se estiliza el MultiGraph
  MGraph1->GetXaxis()->SetTitle("#it{p_{t}} (GeV)");
  MGraph1->GetXaxis()->CenterTitle(true);
  MGraph1->GetXaxis()->SetNdivisions(4,4,0);
  MGraph1->GetXaxis()->SetRangeUser(0.,72.);
  MGraph1->GetYaxis()->SetTitle("R_{s}");
  MGraph1->GetYaxis()->SetTitleOffset(1.4);
  MGraph1->GetYaxis()->SetNdivisions(4,4,0);
  MGraph1->GetYaxis()->SetRangeUser(0.07,0.14);
  MGraph1->GetYaxis()->SetLabelSize(0.03);

  // Se dibujan los puntos
  MGraph1->Draw("APES ; ; 5 s=0.5");

  Canvas1->Update(); 

  // Leyenda
  auto Leg1 = new TLegend(0.15,.18,.55,.35);
  Leg1->SetBorderSize(0.0);
  Leg1->AddEntry(MultiError1,"CMS data; |#it{y}| < 2.4","PE");
  Leg1->AddEntry(Func,"Fit to the CMS data","L");
  Leg1->AddEntry(MultiError2,"LHCb data; 2 > #it{y} < 4.5","PE");
  
  Leg1->Draw("same");

  // Texto adicional, se uriliza el objeto TPaveText
  TPaveText *paves = new TPaveText(43,0.075,72,0.102);

  paves->AddText("Fit Function: #bf{a+b*exp(c*(x-d))}");
  paves->AddText(Form("#bf{a = %1.2f #pm %1.2f}",Fit_Result->Parameter(0),Fit_Result->ParError(0)));
  paves->AddText(Form("#bf{b = %1.2f #pm %1.2f}",Fit_Result->Parameter(1),Fit_Result->ParError(1)));
  paves->AddText(Form("#bf{c = %1.2f #pm %1.2f}",Fit_Result->Parameter(2),Fit_Result->ParError(2)));
  paves->AddText(Form("#bf{d = %1.2f #pm %1.2f}",Fit_Result->Parameter(3),Fit_Result->ParError(3)));
  paves->AddText(Form("#bf{#chi^{2} = %1.2f}",Fit_Result->Chi2()));

  // Para que la margen sea transparente
  paves->SetFillColor(0);
  paves->SetMargin(0.0);

  paves->Draw("same"); // Se dibuja

  TPaveText *pave2 = new TPaveText(50,0.125,70,0.136);

  pave2->AddText("CMS       ");
  pave2->AddText("#bf{L = 61.6 fb^{-1}}");
  pave2->AddText("#bf{#sqrt{s} = 13 TeV}");

  // Para que la margen sea transparente
  pave2->SetFillColor(0);
  pave2->SetMargin(0.0);
  
  pave2->Draw("same"); // Se dibuja

  Canvas1->Update();
  
  // En el Pad2:
  pad2->cd();
  // -------- CMS Points ---------

  const Int_t N_points3 = 7;

  // Data Points
  Double_t X3[N_points3]           = {0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2.0};
  Double_t Y3[N_points3]           = {0.111, 0.1104, 0.11, 0.1126, 0.1117, 0.1069, 0.1099};
  Double_t errX_l3[N_points3]      = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
  Double_t errX_h3[N_points3]      = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
  Double_t errY_stat_l3[N_points3] = {0.000666, 0.0006624, 0.00066, 0.0007882, 0.0008936, 0.001069, 0.001099};
  Double_t errY_stat_h3[N_points3] = {0.000666, 0.0006624, 0.00066, 0.0007882, 0.0008936, 0.001069, 0.001099};
  Double_t errY_sys_l3[N_points3]  = {0.001998,  0.002208, 0.00209,  0.0043914, 0.0048031, 0.0045967, 0.0048356};
  Double_t errY_sys_h3[N_points3]  = {0.001998,  0.002208, 0.00209,  0.0043914, 0.0048031, 0.0045967, 0.0048356};

  // Se crea el objeto TGraphMultiErrors
  auto MultiError3 = new TGraphMultiErrors("MultiError3", "",N_points3,X3 , Y3, errX_l3, errX_h3, errY_stat_l3, errY_stat_h3);
  MultiError3->AddYError(N_points3, errY_sys_l3, errY_sys_h3);

  // Se configura el estilo
  MultiError3->SetMarkerStyle(20);
  MultiError3->SetMarkerSize(0.9);
  MultiError3->GetAttFill(1)->SetFillStyle(0);

  MultiError3->GetXaxis()->SetTitle("|#it{y}|");
  MultiError3->GetXaxis()->CenterTitle(true);
  MultiError3->GetXaxis()->SetTitleSize(.05);
  MultiError3->GetXaxis()->SetTitleOffset(0.8);
  MultiError3->GetXaxis()->SetNdivisions(4,6,0); 
  MultiError3->GetXaxis()->SetRangeUser(-0.5,2.5);
  MultiError3->GetXaxis()->SetLabelSize(.05);

  MultiError3->GetYaxis()->SetRangeUser(0.07,0.14);
  MultiError3->GetYaxis()->SetNdivisions(4,4,0);
  MultiError3->GetYaxis()->SetLabelSize(0.0);

  // Se dibuja
  MultiError3->Draw("APS ; ; 5 s=0.5");

  // Texto Adicional
  TPaveText *pave3 = new TPaveText(0.65,0.08,2.05,0.095);
  pave3->AddText("#bf{12 < #it{p}_{T} < 70 GeV}");

  pave3->SetFillColor(0);
  pave3->SetMargin(0.0);

  pave3->Draw("same"); // Se dibuja

  Canvas1->Update();
  
  // Se guarda la figura en un archivo .png
  Canvas1->SaveAs("Plot_Parcial1.png");

  return 0;
}
