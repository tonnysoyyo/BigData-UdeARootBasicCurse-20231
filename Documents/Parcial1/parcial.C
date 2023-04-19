{

   auto c1 = new TCanvas();

   TMultiGraph *mg = new TMultiGraph();
   //LHCb data
   const Int_t n = 12;
   Double_t x[n]  = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5,7.5,8.5,9.5,10.75,12.5,27};
   Double_t y[n]  = {0.125,0.127,0.125,0.128,0.128,0.127,0.127,0.126,0.125,0.125,0.118,0.120};
   Double_t ex[n] = {.75,0.5,0.5,.5,.5,.5,.5,.5,.5,0.75,0.75,13};
   Double_t ey[n] = {0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.002};
   auto gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetTitle("TGraphErrors Example");
   gr->SetMarkerColor(kRed);
   gr->SetLineColor(kRed);
   gr->SetMarkerStyle(25);
   //CMS data
   const Int_t k = 12;
   Double_t x2[k]  = {12.5,13.5,14.5, 15.5, 17, 19,  21.5,  24.5, 27.5,31.5, 39.5, 57.5};
   Double_t y2[k]  = {0.1314,0.1196,0.1165,0.1154,0.1135,0.1106,0.1105,0.1110,0.1091,0.1095,0.1088,0.1117};
   Double_t ex2[k] = {0.5,0.5,0.5,0.5,1,1,1.5,1.5,1.5,2.5,5.5,12.5};
   Double_t esis[k] = {2.1,1.6,1.3,1.2,0.8,0.8,0.7,0.8,0.9,0.9,0.9,1.3};
   Double_t ey2[k] = {0,0,0,0,0,0,0,0,0,0,0,0};
   for (int i=0; i<k; i++){ey2[i] = y2[i]*esis[i]/100;}//convierte el error de % 
   //Double_t ey2[k] = {0.1314*0.021,0.1196*0.016,0.1165*0.013};
   auto gr2 = new TGraphErrors(k,x2,y2,ex2,ey2);
   gr2->SetTitle("TGraphErrors Example");
   gr2->SetMarkerColor(kBlack);
   gr2->SetLineColor(kBlack);
   gr2->SetMarkerStyle(20);
   mg->Add(gr);
   mg->Add(gr2);
   mg->Draw("AP");
}

