void graph(){
    // Crear los objetos TGraphErrors para los datos esperados y medidos
        
    auto canvas = new TCanvas("canvas", "Graph Draw Options", 800, 600);
    auto g_expected = new TGraphErrors("macro2_input_expected.txt", "%lg %lg %lg");
    auto g_measured = new TGraphErrors("macro2_input_suyo.txt", "%lg, %lg %lg");
    
    
    
    // Configurar los títulos de los ejes y el título del gráfico
    
    g_measured->SetTitle("Measurement XYZ and Expectation");
    g_measured->GetXaxis()->SetTitle("length [cm]");
    g_measured->GetYaxis()->SetTitle("Arb.Units");
    
    // Configurar el color y estilo de la línea para los datos esperados y dibujar la zona sombreada
    
    //g_expected->SetLineColor(kGray+1);
    g_expected->SetFillColorAlpha(kGray+1, 0.5); // Color y transparencia de la banda
    g_expected->Draw("AE3");
   
    // Make the plot esthetically better
    g_measured->SetMarkerStyle(kOpenCircle);
    g_measured->SetMarkerColor(kBlue);
    g_measured->SetLineColor(kBlue);
    g_measured->Draw("P same");
   
    // ajustar la línea lineal y agregarla al gráfico
    TF1* fit = new TF1("fit", "pol1");
    g_measured->Fit(fit, "Q");
    fit->SetLineStyle(2);
    fit->SetLineColor(kRed);
    fit->Draw("Same");   
    
    // etiquetas para los datos y el ajuste 
    auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 1");
    legend->SetFillColor(kBlue);
    legend->AddEntry(g_measured,"Meas. Points","PE");
    legend->AddEntry(fit, Form("Fit: %.2f x + %.2f", fit->GetParameter(1), fit->GetParameter(0)), "L");
    //legend->AddEntry(fit,"Th. Law","L");
    legend->AddEntry(g_expected,"Exp. Points","F");
    legend->Draw(); 
    
    //Finalmente se agrega el grid para un gráfico un poco más estético
    gPad->SetGridy();
    gPad->SetGridx();






}
