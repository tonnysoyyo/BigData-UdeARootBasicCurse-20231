{  //Valores de 12 puntos de color negro, el error stadistico es el cuadro, el estadistico las lineas.
   double ax[]      = {12.5, 13.5, 14.5, 15.5, 17, 19, 21.5 ,24.5, 27.5, 31.5, 39.5, 57.5};
   double ay[]      = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106 , 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
   double aexl[]    = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
   double aexh[]    = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
   double* aeylstat = new double[12]  {0.1314*0.021, 0.1196*0.016, 0.1165*0.013, 0.1154*0.012, 0.1135*0.008, 0.1106*0.008 , 0.1105*0.007, 0.1110*0.008, 0.1091*0.009, 0.1095*0.009, 0.1088*0.009, 0.1117*0.013};
   double* aeyhstat = new double[12]  {0.1314*0.021, 0.1196*0.016, 0.1165*0.013, 0.1154*0.012, 0.1135*0.008, 0.1106*0.008 , 0.1105*0.007, 0.1110*0.008, 0.1091*0.009, 0.1095*0.009, 0.1088*0.009, 0.1117*0.013};
   double* aeylsys  = new double[12]  {0.1314*0.031, 0.1196*0.027, 0.1165*0.024, 0.1154*0.026, 0.1135*0.026, 0.1106*0.028 , 0.1105*0.029, 0.1110*0.026, 0.1091*0.032, 0.1095*0.023, 0.1088*0.028, 0.1117*0.026};
   double* aeyhsys  = new double[12]  {0.1314*0.031, 0.1196*0.027, 0.1165*0.024, 0.1154*0.026, 0.1135*0.026, 0.1106*0.028 , 0.1105*0.029, 0.1110*0.026, 0.1091*0.032, 0.1095*0.023, 0.1088*0.028, 0.1117*0.026};
   //Valores de 12 puntos de color rojo.
   double xtwere[]      = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5 ,8.5, 9.5, 10.75, 12.75, 18};
   double ytwere[]      = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127 , 0.127, 0.126, 0.125, 0.125, 0.118, 0.12};
   double extweresup[]    = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 4};
   double extwereinf[]    = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 22};
   double* eytwerestasup = new double[12]  {0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.002};   
   double* eytwerestainf = new double[12]  {0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.003,0.002};
   //Valores de 7 puntos negros.
   double xsvenbla[]      = {0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2};
   double ysvenbla[]      = {0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069 , 0.1099};
   double exsvenbsup[]    = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
   double exsvenbinf[]    = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
   double* eysvenblastasup = new double[7]  {0.1110*0.006, 0.1104*0.006, 0.1100*0.006, 0.1126*0.007, 0.1117*0.008, 0.1069*0.01 , 0.1099*0.01};   
   double* eysvenblastainf = new double[7]  {0.1110*0.006, 0.1104*0.006, 0.1100*0.006, 0.1126*0.007, 0.1117*0.008, 0.1069*0.01 , 0.1099*0.01};
   double* eysvenblasyssup  = new double[7]  {0.1110*0.018, 0.1104*0.02, 0.1100*0.019, 0.1126*0.039, 0.1117*0.043, 0.1069*0.043 , 0.1099*0.044};
   double* eysvenblasysinf  = new double[7]  {0.1110*0.018, 0.1104*0.02, 0.1100*0.019, 0.1126*0.039, 0.1117*0.043, 0.1069*0.043 , 0.1099*0.044}; 
   auto Parcial1JJMS = new TCanvas("Parcial1JJMS","Parcial1JJMS",200,10,600,400);//Creacion del canvas
   Parcial1JJMS->Divide(2,1); Parcial1JJMS->cd(1)->SetPad(0, 0.0, 0.67, 1.0); //Se divide en dos pads y trabajamos en el primer pad.
   TGraphMultiErrors* TwelBlacPoints = new TGraphMultiErrors("TwelBlacPoints", " ", 12, ax, ay, aexl, aexh, aeylstat, aeyhstat);//puntos negros de primer pad
   TwelBlacPoints->AddYError(12, aeylsys, aeyhsys);
   TwelBlacPoints->SetMarkerStyle(20);
   TwelBlacPoints->GetAttFill(1)->SetFillStyle(0);//Transparencia de las cajas
   TwelBlacPoints->SetMaximum(0.1385);TwelBlacPoints->SetMinimum(0.07);   //limites en verticales
   TwelBlacPoints->GetXaxis()->SetLimits(0, 75);//limites en x
   TwelBlacPoints->GetXaxis()->SetTitle("P_{T} (GeV)");//nombres de ejes
   TwelBlacPoints->GetYaxis()->SetTitle("R_{s}");
   TwelBlacPoints->GetYaxis()->SetTitleOffset(0.8);//Acercar "R_{s}" a la imagen para que no se corte 
   TwelBlacPoints->GetXaxis()->CenterTitle(true);// Centrar el titulo horizontal
   TwelBlacPoints->GetXaxis()->SetNdivisions(4,4,0);TwelBlacPoints->GetYaxis()->SetNdivisions(4,4,0);//Divisiones
   TwelBlacPoints->Draw("a p s ; ; 5 s=0.5");//dibujo de puntos negros del primer pad
   auto TwelRedPoints = new TGraphMultiErrors("TwelRedPoints", " ", 12, xtwere, ytwere, extweresup, extwereinf, eytwerestasup, eytwerestainf);//puntos rojos
   TwelRedPoints->SetMarkerStyle(25); TwelRedPoints->SetMarkerColor(kRed); TwelRedPoints->SetLineColor(kRed);//cuadrados abiertos rojos
   TwelRedPoints->SetMarkerSize(0.43);
   TwelRedPoints->Draw("same p ");//puntos rojos
   auto fit = new TF1("fit","([0]*exp([1]*([2]-x)))+[3]",13,65);//Fit a los 12 puntos negros del primer pad
   fit->SetParameters(0.05,0.45,12.5,0.1);//Parametros que luego de muchos intentos dan un error menor al valor central
   fit->SetLineColor(kBlue);  
   TwelBlacPoints->Fit(fit);//fit a los 12 puntos negros
   auto CMSContent = new TPaveText(0.6,0.83,0.87,0.71, "NDC");//Texto de la esquina superior derecha
   CMSContent->SetBorderSize(0); CMSContent->SetFillStyle(0);//trasnparente y sin borde
   CMSContent->SetTextSize(0.04); CMSContent->SetTextFont(42); //Tipo de texto
   CMSContent->AddText(" L = 61.6 fb^{-1}");
   CMSContent->AddText("#sqrt{s} = 13 TeV");
   CMSContent->Draw();
   auto CMSTitle = new TPaveText(0.51,0.88,0.87,0.8, "NDC");//Titulo del texto superior, aparte debido a que el tipo de fuente es distinto
   CMSTitle->SetBorderSize(0); CMSTitle->SetFillStyle(0);//trasnparente y sin borde
   CMSTitle->SetTextSize(0.04);
   CMSTitle->AddText("CMS");
   CMSTitle->Draw();
   auto legend = new TLegend(0.14,.16,.55,.41);//leyenda con la descripcion de los puntos y el fit
   legend->SetBorderSize(0); legend->SetFillStyle(0);//trasnparente y sin borde
   legend->AddEntry(TwelBlacPoints,"CMS data; |y| < 2.4","PE");
   legend->AddEntry(fit,"Fit to the CMS data","L");
   legend->AddEntry(TwelRedPoints,"LHCb data; 2 < y < 4.5","PE");
   legend->Draw();
   auto FitFunAndValues = new TPaveText(0.55,.13,.89,.48,"NDC");//leyenda exponiendo las constantes obtenidas con sus errores redondeados
   FitFunAndValues->SetBorderSize(0); FitFunAndValues->SetFillStyle(0);//trasnparente y sin borde
   FitFunAndValues->SetTextFont(42);
   FitFunAndValues->AddText("Function Ae^{B(C-x)}+D");FitFunAndValues->AddText("and fit parameters;");
   FitFunAndValues->AddText(TString::Format("A = %.2f #pm %.2f",fit->GetParameter(0),fit->GetParError(0)));
   FitFunAndValues->AddText(TString::Format("B = %.3f #pm %.3f",fit->GetParameter(1),fit->GetParError(1)));
   FitFunAndValues->AddText(TString::Format("C = %.2f #pm %.2f",fit->GetParameter(2),fit->GetParError(2)));
   FitFunAndValues->AddText(TString::Format("D = %.4f #pm %.4f",fit->GetParameter(3),fit->GetParError(3)));
   FitFunAndValues->Draw();
   Parcial1JJMS->cd(2)->SetPad(0.61, 0.0, 1.0, 1.0); ///Trabajamos en el segundo pad
   TGraphMultiErrors* Sevenblackpoints = new TGraphMultiErrors("Sevenblackpoints", " ", 7, xsvenbla, ysvenbla, exsvenbsup, exsvenbinf, eysvenblastasup, eysvenblastainf);//7 ountos negros de pad 2
   Sevenblackpoints->AddYError(7, eysvenblasyssup, eysvenblasysinf);
   Sevenblackpoints->SetMarkerStyle(20);
   Sevenblackpoints->GetAttFill(1)->SetFillStyle(0); //Transparencia de las cajas
   Sevenblackpoints->SetMaximum(0.1355); Sevenblackpoints->SetMinimum(0.077);   //limites verticales
   Sevenblackpoints->GetXaxis()->SetLimits(-0.1, 2.5);//limites horizontales
   Sevenblackpoints->GetYaxis()->SetNdivisions(0,14,1); Sevenblackpoints->GetXaxis()->SetNdivisions(3,5,0);//divisiones
   Sevenblackpoints->GetXaxis()->SetTitle("|y|");
   Sevenblackpoints->GetXaxis()->CenterTitle(true);//Centrar el titulo
   Sevenblackpoints->Draw("a p s ; ; 5 s=0.5"); 
   auto Sentence = new TPaveText(0.1, 0.1, 0.9, 0.5, "NDC");
   Sentence->SetBorderSize(0); Sentence->SetFillStyle(0);//caja del texto trasnparente
   Sentence->SetTextFont(42); Sentence->SetTextSize(0.051); //Tipo de texto
   Sentence->AddText("  12 < P_{T} < 70 GeV");
   Sentence->Draw();
}
