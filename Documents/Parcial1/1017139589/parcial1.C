//TGraphMultiErrors

void parcial1(){

    // Definición Canvas
   auto c47 = new TCanvas("c47","c47",1500,800);
   c47->Divide(2,1);


   //Definición gráfico 
   TMultiGraph *lienzo = new TMultiGraph();

   TMultiGraph *lienzo2 = new TMultiGraph();



   // Datos Measurement of the dependence of the hadron production fraction ratio fs/fu on B meson kinematic variables in proton-proton collisions at 13 TeV
   double ax[]      = {12.5, 13.5, 14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
   double ay[]      = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
   double aexl[]    = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
   double aexh[]    = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
   double* aeylstat = new double[12]  {0.0027594, 0.0019136, 0.0015145, 0.0013848, 0.000908, 0.0008848, 0.0007735, 0.000888, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
   double* aeyhstat = new double[12]  {0.0027594, 0.0019136, 0.0015145, 0.0013848, 0.000908, 0.0008848, 0.0007735, 0.000888, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
   double* aeylsys   = new double[12]  {0.0040734, 0.0032292, 0.002796, 0.0030004, 0.002951, 0.0030968, 0.0032045, 0.002886, 0.0034912, 0.0025185, 0.0030464, 0.0029042};
   double* aeyhsys  = new double[12]   {0.0040734, 0.0032292, 0.002796, 0.0030004, 0.002951, 0.0030968, 0.0032045, 0.002886, 0.0034912, 0.0025185, 0.0030464, 0.0029042};
 
  // LHCb measurement, for comparision
   const Int_t n = 12;
   Double_t xc[n]  = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 12.25, 12.75, 18};
   Double_t yc[n]  = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.120};
   Double_t excl[n] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 4};
   Double_t eycl[n] = {0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002};
   Double_t exch[n] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 22};
   Double_t eych[n] = {0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002};

// Datos |y|
   double bx[]      = {0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2};
   double by[]      = {0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
   double bexl[]    = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
   double bexh[]    = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
   double* beylstat = new double[7]  {0.000666, 0.0006624, 0.00066, 0.0007882, 0.0008936, 0.001069, 0.001099};
   double* beyhstat = new double[7]  {0.000666, 0.0006624, 0.00066, 0.0007882, 0.0008936, 0.001069, 0.001099};
   double* beylsys   = new double[7]  {0.001998, 0.002208, 0.00209, 0.0043914, 0.0048031, 0.0045967, 0.0048356};
   double* beyhsys  = new double[7]   {0.001998, 0.002208, 0.00209, 0.0043914, 0.0048031, 0.0045967, 0.0048356};

// Definición graph multierrors sistematicos y estadisticos grafico 1
   TGraphMultiErrors* gme = new TGraphMultiErrors("gme", "Parcial 1", 12, ax, ay, aexl, aexh, aeylstat, aeyhstat);
   gme->AddYError(12, aeylsys, aeyhsys);
   gme->SetMarkerStyle(20);
   gme->GetAttFill(1)->SetFillStyle(0);
   gme->SetMinimum(0.05);
   gme->SetMaximum(0.15);
  
 // Definición graph multierrors 
   auto gr = new TGraphAsymmErrors(n,xc,yc,excl,exch,eycl,eych);
   gr->SetMarkerColor(2);
   gr->SetMarkerStyle(4);
   gr->SetLineColor(kRed);
 

// Definición graph multierrors sistematicos y estadisticos grafico 2
   TGraphMultiErrors* gmb = new TGraphMultiErrors("gmb", "Parcial 1", 7, bx, by, bexl, bexh, beylstat, beyhstat);
   gmb->AddYError(7, beylsys, beyhsys);
   gmb->SetMarkerStyle(20);
   gmb->GetAttFill(1)->SetFillStyle(0);
   gmb->SetMinimum(0.05);
   gmb->SetMaximum(0.15);

//Fit de la función 

  auto myfit = new TF1("myfit","expo",-2,-0.012);
  //auto myfit = new TF1("myfit","expo+gaus(2)",0,1);
  
  myfit->SetParameters(2,-0.6);
  gme->Fit("myfit");

   // Se adicionan las graficas
   c47->cd(1);
   lienzo -> Add(gme, "a p s ; ; 12 s=0.5");
   lienzo -> Add(gr, "APE");
   lienzo -> Draw("APE");
   lienzo -> SetTitle(";pT[GeV];Rs");

   auto legend = new TLegend(0.15,0.15,.5,.3,"Parcial 1");
   legend->AddEntry(gme, "CMS data; |y|<2.4","ep");
   legend->AddEntry(gr,"LHCB data; 2<y<4.5","ep");

   legend->Draw("Same");

   auto legend2 = new TLegend(0.8,0.8,.9,.9,"CMS");

   legend2->Draw("Same");

   c47->cd(2);
   lienzo2 -> Add(gmb,  "a p s ; ;7 s=0.5");
   lienzo2 -> Add(gmb, "APS");
   lienzo2 -> Draw("APS");
   lienzo2 -> SetTitle(";|y|;Rs");

  
}

