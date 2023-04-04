void tarea() {
    TCanvas *canva = new TCanvas("canva","canva",200,10,700,500);
    canva->SetGrid();
    
    TGraphErrors *esperado = new TGraphErrors("macro2_input_expected.txt","%lg %lg %lg");
    
    esperado->SetFillColor(5);
    esperado->SetTitle("Measurement XYZ and Expectation;length [cm];Arb.Units");
    esperado->SetMinimum(-1);
    esperado->Draw("AP3");

    
    TGraph *puntos = new TGraph("macro2_input_mio.txt","%lg %lg %*lg",", ");
    puntos->SetMarkerStyle(24);
    puntos->Draw("same P");
    
    TGraphErrors *errordummy = new TGraphErrors("macro2_input_mio.txt","%lg %lg %lg",", ");
    
    TGraphErrors *error = new TGraphErrors(10,errordummy->GetX(),errordummy->GetY(),nullptr,errordummy->GetEX());
    error->Draw("same p");

    auto lineal = new TF1("lineal","[0]*x+[1]",0,11);
    error->Fit("lineal");
    TF1 *linea = error->GetFunction("lineal");
    linea->SetLineStyle(2);

    double *params = linea->GetParameters();

    auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 2");
    legend->AddEntry(esperado,"Expected Points","FL");
    legend->AddEntry(puntos,"Measured Points","PL");
    legend->AddEntry(linea,"Linear fit","L");
    legend->Draw();

    auto legend2 = new TLegend(.1,.58,.3,.7,"Fit ax+b");
    legend2->AddEntry(linea,TString::Format("a = %g",params[0]),"");
    legend2->AddEntry(linea,TString::Format("b = %g",params[1]),"");
    legend2->Draw();
}