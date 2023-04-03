void seguimiento1()
{
    auto c=new TCanvas();
    c->SetGrid();

    TGraphErrors *datos_es = new TGraphErrors("macro2_input_expected.txt", "%lg %lg %lg ");
    
    datos_es->SetTitle("Measurement XYZ");
    datos_es->GetXaxis()->SetTitle("length [cm]");
    datos_es->GetYaxis()->SetTitle("Arb.Units");
    datos_es->SetFillColor(5);
    datos_es->Draw("E3AL");
    
    
    datos_es->GetYaxis()->SetRangeUser(0, 100);
    
    TGraphErrors *datos = new TGraphErrors("macro2_input_suyo.txt", "%lg %*s %lg %lg ");

    datos->SetMarkerStyle(4);
    datos->SetMarkerColor(4);
    datos->SetLineColor(1);

    datos->Draw("PEsame");


    auto f = new TF1("Ajuste lineal", "  [0] +x*[1] ",.2,10.5);

    f->SetLineColor(2);
    f->SetLineStyle(2);
    f->Draw("Same");
    

    datos->Fit(f);

    Double_t params[2];
    f->GetParameters(params);
    Double_t param_b = params[0];
    Double_t param_a = params[1];




    auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 2");
    legend->AddEntry(datos_es,"Expected Points");
    legend->AddEntry(f,"Linear fit","L");
    legend->AddEntry(datos,"Measured Points");
    
    auto legend2 = new TLegend(.1,.58,.3,.7,"Parameters of lineal fit");
    legend2->AddEntry( f,("b = " + std::to_string(param_b)).c_str());
    legend2->AddEntry( f,("a = " + std::to_string(param_a)).c_str());
    legend2->SetTextSize(0.03);

    legend->Draw();
    legend2->Draw();

    c->Print("seguimiento1.png");
}