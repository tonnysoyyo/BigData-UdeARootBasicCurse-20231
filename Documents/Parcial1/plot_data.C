void plot_data() {
  
    // Crear el canvas para el gráfico
    TCanvas* c = new TCanvas("c", "Gráfico de p_T vs R_s", 800, 600);
    c->SetGrid();
    c->Divide(2, 1, 0, 0);
    
     // Crear el primer TPad
    TPad* pad1 = (TPad*) c->cd(1);
    //pad1->SetGrid();
    pad1->SetTopMargin(0.001);
    pad1->SetRightMargin(0.005); // 0.005 mejor
    pad1->SetLeftMargin(0.1);
    pad1->SetPad(0, 0, 0.7, 0.9);// esta gráfica(pad) es el 70% del gráfico total
    pad1->Draw();

    // Crear el segundo TPad
    TPad* pad2 = (TPad*) c->cd(2);
    //pad2->SetGrid();
    //pad2->SetTopMargin(0.10);
    pad2->SetLeftMargin(0.01); //0.01 mejor 
    pad2->SetRightMargin(0.05);
    pad2->SetPad(0.7, 0, 1, 0.9); // esta gráfica(pad) es el 30% del gráfico total 
    pad2->Draw();
 
    

    // Definir los datos
    int n= 12; //número de datos 
    double pt[] = {12.5, 13.5, 14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
    double pt_low[] = {0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
    double pt_high[]= {0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
    double rs[] = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.111, 0.1091, 0.1095, 0.1088, 0.1117};
    double* stat_p = new double[n]{0.0028, 0.0019, 0.0015, 0.0014, 0.0009, 0.0009, 0.0008, 0.0009, 0.001, 0.001, 0.001, 0.0015};
    double* stat_m = new double[n] {0.0028, 0.0019, 0.0015, 0.0014, 0.0009, 0.0009, 0.0008, 0.0009, 0.001, 0.001, 0.001, 0.0015};
    double* sys_p = new double[n] {0.0041, 0.0032, 0.0028, 0.003, 0.003, 0.0031, 0.0032, 0.0029, 0.0035, 0.0025, 0.003, 0.0029};
    double* sys_m = new double[n] {0.0041, 0.0032, 0.0028, 0.003, 0.003, 0.0031, 0.0032, 0.0029, 0.0035, 0.0025, 0.003, 0.0029};

    // Calcular el número total de datos
    //Int_t n = sizeof(pt)/sizeof(Double_t);

    // Crear el gráfico y definir los ejes
    TGraphMultiErrors* gr = new TGraphMultiErrors("gr","",n, pt, rs, pt_low, pt_high, stat_m, stat_p);
                     
    gr->AddYError(n, sys_m, sys_p);
    //gr->SetMarkerStyle(10);
    gr->SetLineColor(kBlack);
    gr->GetAttLine(0)->SetLineColor(kBlack);
    gr->GetAttLine(1)->SetLineColor(kBlue);
    gr->GetAttFill(1)->SetFillStyle(0);
    //gr->SetTitle("Gráfico de p_T vs R_s");
    //gr->GetXaxis()->SetTitleFont(52);
    gr->GetXaxis()->SetTitle("p_{T} [GeV/c]");
    //gr->GetYaxis()->SetTitleFont(52);
    gr->GetYaxis()->SetTitle("\R_{s}");
    gr->GetYaxis()->SetRangeUser(0.07, 0.139);
    //gr->GetXaxis()->SetRangeUser(0.0, 75.0);
    gr->SetMarkerStyle(kOpenCircle); //20 valor
    gr->SetMarkerSize(0.4);
    pad1->cd();
    gr->Draw("a p s ; ; 5 s=0.5");
    
    //No se pudo agregar los datos del LHCB porque no escalaba 
    /*
    // Definir datos de LHCB
    
    double x[] = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75,27  };
    double y_[] = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118,0.120};
    double ex[] = {0.75, 0.5,0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75,1.25, 13};
    double ey[] = {0.003,0.003,0.003,0.003, 0.003, 0.003, 0.003,0.003, 0.003, 0.003, 0.003, 0.002 };
    TGraphErrors* gr3= new TGraphErrors(12, x, y_, ex, ey);  
    
    gr3->SetMarkerStyle(20);
    gr3->SetMarkerSize(1.2);
    
    // Establecer el color de los errores
    gr3->SetFillColor(kRed);
    
    
    // Dibujar el gráfico
    gr3->GetYaxis()->SetRangeUser(0.07, 0.139);
    gr3->GetXaxis()->SetRangeUser(0.01, 75.0);
    gr3->Draw("same");
    */

    
    // Definir la función de ajuste exponencial
TF1* fitFunc = new TF1("fitFunc", "[0]*exp(-[1]*x) + [2]", 12.5, 75);

fitFunc->SetParameters(-0.434, 1, 0.11 );
fitFunc->SetLineColor(kBlue);

// Realizar el ajuste
gr->Fit("fitFunc", "R");


fitFunc->Draw("Same");


// Agregar las leyendas en la parte inferior del gráfico
TLegend* leg = new TLegend(0.15,0.15,0.45,0.45);
leg->SetFillColor(0);
leg->SetFillStyle(0);
leg->SetBorderSize(0);
leg->SetTextFont(62);
leg->AddEntry(gr,"CMS data ;\|y|< 2.4 ","PE");
//Puede ser útil 
//leg->AddEntry(fitFunc, Form(" a = %.2f, b = %.2f, c = %.2f", fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2) ),"L" );
//char fitParams[100];
//sprintf(fitParams, "Fit parameters: A=%0.3f, B=%0.3f, C=%0.3f", fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2));
//leg->AddEntry((TObject*)0, fitParams, "");
//leg->AddEntry(fitFunc, Form("Fit function: %0.3f*exp(-%0.3f*x) + %0.3f", fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2)), "l");
leg->Draw();

TLegend* leg2 = new TLegend(0.8,0.8,0.99,0.99);
leg2->SetFillColor(kWhite);
//leg2->SetHeader("CMS");
leg2->SetBorderSize(0);
leg2->SetTextFont(62);
leg2->AddEntry((TObject*)0,"CMS","");

leg2->AddEntry("","\L= 61.6 fb^{-1}","");
leg2->AddEntry("","#sqrt{s}= 13 TeV","");
leg->AddEntry(fitFunc,"Fit to CMS data","l");
leg2->Draw();

TLegend* leg3 = new TLegend(0.60,0.35,0.99,0.55);
leg3->SetFillColor(0);
leg3->SetFillStyle(0);
leg3->SetBorderSize(0);
leg3->SetTextFont(62);
leg3->AddEntry(fitFunc, Form("Fit function: %0.2f*exp(-%0.2f*x) + %0.2f", fitFunc->GetParameter(0), fitFunc->GetParameter(1), fitFunc->GetParameter(2)), "l");
leg3->Draw();



    


    // Definir los datos

    
    int m= 7; //número de datos 
    double y[] = {0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2.0};
    double y_low[] = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
    double y_high[]= {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
    double rs_y[] = {0.111, 0.1104, 0.11, 0.1126, 0.1117, 0.1069, 0.1099};
    double* staty_p = new double[m]{0.0007, 0.0007, 0.0007, 0.0008, 0.0009, 0.0011, 0.0011};
    double* staty_m = new double[m]{0.0007, 0.0007, 0.0007, 0.0008, 0.0009, 0.0011, 0.0011};
    double* sysy_p = new double[m] {0.002, 0.0022, 0.0021, 0.0044, 0.0048, 0.0046, 0.0048};
    double* sysy_m = new double[m] {0.002, 0.0022, 0.0021, 0.0044, 0.0048, 0.0046, 0.0048};
    
        // Crear el gráfico y definir los ejes
    TGraphMultiErrors* gr2 = new TGraphMultiErrors("gr2", "",m, y, rs_y, y_low, y_high, staty_m, staty_p);
                     
    gr2->AddYError(m, sysy_m, sysy_p);
    gr2->SetMarkerStyle(10);
    gr2->SetLineColor(kRed);
    gr2->GetAttLine(0)->SetLineColor(kRed);
    gr2->GetAttLine(1)->SetLineColor(kBlue);
    gr2->GetAttFill(1)->SetFillStyle(0);
    gr2->GetYaxis()->SetLabelSize(0); //No mostrar los números en el eje y  
    //gr2->SetTitle("Gráfico de p_T vs R_s");
    gr2->GetXaxis()->SetTitle("|y| [B]");
    //gr2->GetYaxis()->SetTitle("R_s");
    
    gr2->GetYaxis()->SetRangeUser(0.07, 0.139);
    gr2->SetMarkerStyle(10);
    gr2->SetMarkerSize(0.2);
    pad2->cd();
    gr2->Draw("a p s ; ; 5 s=0.5");

// Crear un objeto TPaveText
TPaveText *t = new TPaveText(0.4, 0.2, 0.6, 0.5, "NDC");

// Agregar el texto a TPaveText
t->AddText("12 < p_{T} < 70 GeV");

// Ajustar el tamaño de fuente del texto
t->SetTextSize(0.08);

// Configurar el estilo de borde y fondo de TPaveText
t->SetFillColor(0);
t->SetFillStyle(0);
t->SetBorderSize(0);

// Dibujar TPaveText en el canvas
t->Draw();

    c->Print("atlasplots/Grap_LinearFit.pdf");  
  
    

}
