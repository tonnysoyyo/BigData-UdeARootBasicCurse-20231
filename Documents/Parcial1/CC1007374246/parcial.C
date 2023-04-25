{
   auto c1 = new TCanvas();
   TPad *pad1 = new TPad("pad1","pad1",0.0,0.0,0.7,0.97,-1,-1); //Para la figura de la izquierda
   TPad *pad2 = new TPad("pad2","This is pad2",0.65,0.0,0.95,0.97,-1,1); //Para la figura de la derecha
   //pad2->Range(-2, -4, 10, 10);
   pad1->Draw();
   pad2->Draw();
   pad2->SetLeftMargin(0.001);
   pad1->Update();
   
   //LHCb data
   const Int_t n = 12;
   Double_t x[n]  = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5,7.5,8.5,9.5,10.75,12.5,18};
   Double_t y[n]  = {0.125,0.127,0.125,0.128,0.128,0.127,0.127,0.126,0.125,0.125,0.118,0.120};
   Double_t exl[n] = {.75,0.5,0.5,.5,.5,.5,.5,.5,.5,0.75,0.75,4};
   Double_t exh[n] = {.75,0.5,0.5,.5,.5,.5,.5,.5,.5,0.75,1.4,22};
   Double_t ey[n] = {0.0015,0.0015,0.0015,0.0015,0.0015,0.0015,0.0015,0.0015,0.0015,0.0015,0.0015,0.0015};
   auto gr = new TGraphMultiErrors(n,x,y,exl,exh,ey,ey);
   gr->SetMarkerColor(kRed);
   gr->SetLineColor(kRed);
   gr->SetMarkerSize(0.4);
   gr->SetMarkerStyle(25);
   
   //CMS data
   const Int_t k = 12;
   Double_t x2[k]  = {12.5,13.5,14.5, 15.5, 17, 19,  21.5,  24.5, 27.5,31.5, 39.5, 57.5};
   Double_t y2[k]  = {0.1314,0.1196,0.1165,0.1154,0.1135,0.1106,0.1105,0.1110,0.1091,0.1095,0.1088,0.1117};
   Double_t ex2[k] = {0.5,0.5,0.5,0.5,1,1,1.5,1.5,1.5,2.5,5.5,12.5};
   Double_t estat[k] = {2.1,1.6,1.3,1.2,0.8,0.8,0.7,0.8,0.9,0.9,0.9,1.3}; //error estadistico: barras
   Double_t esis[k] = {3.1,2.7,2.4,2.6,2.6,2.8,2.9,2.6,3.2,2.3,2.8,2.6}; //error sistematico: cajas
   Double_t eyestad[k] = {0,0,0,0,0,0,0,0,0,0,0,0};
   Double_t ey23[k] = {0,0,0,0,0,0,0,0,0,0,0,0};
   for (int i=0; i<k; i++){eyestad[i] = y2[i]*estat[i]/100;}//convierte el error de % 
   for (int i=0; i<k; i++){ey23[i] = y2[i]*esis[i]/100;}//convierte el error de % 
   auto gme = new TGraphMultiErrors("gme", "", k, x2, y2, ex2, ex2, eyestad, eyestad);
   gme->AddYError(k, ey23, ey23);
   gme->SetLineColor(kBlack);
   gme->GetAttLine(0)->SetLineColor(kBlack);
   gme->GetAttLine(1)->SetLineColor(kBlack);
   gme->GetAttFill(1)->SetFillStyle(0);
   gme->SetMarkerSize(0.9);
   gme->SetMarkerStyle(20);

   //B-meson transverse momentum: grafico derecha
   const Int_t l = 7;
   Double_t x3[l]  = {0.125,0.375,0.625,0.875,1.15,1.45,2};
   Double_t y3[l]  = {0.1110, 0.1104,0.1100,0.1126,0.1117,0.1069,0.1099};
   Double_t ex3[l] = {0.125, 0.125,0.125,0.125,0.15,0.15,0.4};
   Double_t estat3[l] = {0.6,0.6,0.6,0.7,0.8,1.0,1.0}; //error estadistico: barras
   Double_t esis3[l] = {1.8,2.0,1.9,3.9,4.3,4.3,4.4}; //error sistematico: cajas
   Double_t ey3[l] = {0,0,0,0,0,0,0}; //Error estadistico
   Double_t ey34[l] = {0,0,0,0,0,0,0}; //Error sistematico
   for (int i=0; i<l; i++){ey3[i] = y3[i]*estat3[i]/100;}//convierte el error de % 
   for (int i=0; i<l; i++){ey34[i] = y3[i]*esis3[i]/100;}//convierte el error de % 
   auto gme2 = new TGraphMultiErrors("gme", "", l, x3, y3, ex3, ex3, ey3, ey3);
   gme2->AddYError(k, ey34, ey34);
   gme2->SetMarkerStyle(20);
   gme2->SetLineColor(kBlack);
   gme2->GetAttLine(0)->SetLineColor(kBlack);
   gme2->GetAttLine(1)->SetLineColor(kBlack);
   gme2->GetAttFill(1)->SetFillStyle(0);


   pad1->cd(); 
   TLatex* latex = new TLatex(50, 0.135, "CMS");   latex->SetTextFont(62);    latex->SetTextSize(0.045);
   TLatex* latex2 = new TLatex(50, 0.130, "L  = 61.6 fb^{-1}");
   latex2->SetTextFont(42);
   latex2->SetTextSize(0.045);
   TLatex* latex3 = new TLatex(49.95, 0.125, "#sqrt{s} = 130 TeV");
   latex3->SetTextFont(42);
   latex3->SetTextSize(0.045);

   gme->Draw("APS ;  ; 5 s=0.5");
   gme->GetYaxis()->SetRangeUser(0.07, 0.14);
   gme->GetXaxis()->SetLimits(0, 75);
   gme->GetYaxis()->SetTitle("R_{s}");
   gme->GetXaxis()->SetTitle("P_{T} (GeV)");
   gme->GetXaxis()->ChangeLabel(2,-1,0.);
   gme->GetXaxis()->ChangeLabel(4,-1,0.);
   gme->GetXaxis()->ChangeLabel(6,-1,0.);
   gme->GetXaxis()->ChangeLabel(8,-1,0.);
   gme->GetYaxis()->ChangeLabel(1,-1,0.);
   gme->GetYaxis()->ChangeLabel(3,-1,0.);
   gme->GetYaxis()->ChangeLabel(5,-1,0.);
   gme->GetYaxis()->ChangeLabel(7,-1,0.);
   gme->GetYaxis()->ChangeLabel(8,-1,0.);
   gme->GetYaxis()->SetTitleOffset(0.6);
   gme->GetXaxis()->CenterTitle();
   gr->Draw("P");
   latex->Draw();
   latex2->Draw();
   latex3->Draw();

   //Fit
   auto myfit = new TF1("myfit","[0]*exp( (-[1]*(x-[2]))) +[3]",12,70);
   myfit->SetLineColor(4);
   myfit->SetLineWidth(2);
   myfit->SetParameters(0.05,0.45,12.5,0.1);  
   gme->Fit("myfit","S","",11.9,70);
   Double_t parametros[4];
   myfit->GetParameters(parametros);
   auto linea = gme->GetFunction("myfit");
   auto errs = linea->GetParErrors();

   TLatex* latexp0 = new TLatex(45, 0.095,"Fit: D+ A*e^{(B(x-C) )}");   latexp0->SetTextFont(42);    latexp0->SetTextSize(0.03); latexp0->Draw();
   TLatex* latexp = new TLatex(45, 0.092,TString::Format("A = %.4f #pm %.4f ",parametros[0],errs[0]));   latexp->SetTextFont(42);    latexp->SetTextSize(0.025); latexp->Draw();
   TLatex* latexp2 = new TLatex(45, 0.09,TString::Format("B = %.4f #pm %.4f",parametros[1],errs[1]));   latexp2->SetTextFont(42);    latexp2->SetTextSize(0.025); latexp2->Draw();
   TLatex* latexp3 = new TLatex(45, 0.088,TString::Format("C = %.4f #pm %.4f",parametros[2],errs[2]));   latexp3->SetTextFont(42);    latexp3->SetTextSize(0.025); latexp3->Draw();
   TLatex* latexp4 = new TLatex(45, 0.086,TString::Format("D = %.4f #pm %.4f",parametros[3],errs[3]));   latexp4->SetTextFont(42);    latexp4->SetTextSize(0.025); latexp4->Draw();

   auto legend = new TLegend(.145,.18,.49,.38,"");
    legend->AddEntry(gme,"CMS data; |#it{y}| < 2.4","EP");
    legend->AddEntry(myfit,"Fit to the CMS data","L");
    legend->AddEntry(gr,"\\text{LHCb data; } \\textit 2<y<4.5","EP");
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetMargin(0.1);
    legend->Draw();

   pad2->cd(); 
   gme2->Draw("APS ;  ; 5 s=0.5");
   gme2->GetYaxis()->SetRangeUser(0.07, 0.14);
   gme2->GetXaxis()->SetTitle("|y|");
   gme2->GetXaxis()->CenterTitle();
   gme2->GetXaxis()->SetTitleOffset(0.52);
   gme2->GetXaxis()->SetLabelSize(0.055);
   gme2->GetXaxis()->SetTitleSize(0.07);
   gme2->GetXaxis()->ChangeLabel(1,-1,0.);
   gme2->GetXaxis()->ChangeLabel(2,-1,0.);
   gme2->GetXaxis()->ChangeLabel(4,-1,0.);
   gme2->GetXaxis()->ChangeLabel(6,-1,0.);
   TLatex* latex4 = new TLatex(0.5, 0.09, "12< p_{T} <70 GeV  ");
   latex4->SetTextFont(42);
   latex4->SetTextSize(0.075);
   latex4->Draw();
   c1->SaveAs("plot.jpg")
}     