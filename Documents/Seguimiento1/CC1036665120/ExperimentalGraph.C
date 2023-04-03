// define a linear function 
Double_t linearFunct(Double_t *x, Double_t *par) {
      return par[0] + par[1]*x[0];
}

void ExperimentalGraph(){

    auto c1 = new TCanvas("c1", "DMeasurement XYZ and Expectation", 800, 500);
    c1->SetGrid();
    c1->GetFrame()->SetBorderSize(12);

    auto mg = new TMultiGraph("mg","Measurement XYZ and Expectation");


    // --------------------------
    // ----- EXPECTED DATA ------
    // --------------------------

    // File: Omit the X errors 
    auto expected = new TGraphErrors("../../Unidad2/Clase3/macro2_input_expected.txt", "%lg %lg %lg");
    expected -> SetFillColor(kViolet);
	expected -> SetFillStyle(kFDotted1);



    // --------------------------
    // ----- MEASURED DATA ------
    // --------------------------

    // %*s: skip the "," in the second column
    auto measured = new TGraphErrors("../../Unidad2/Clase3/macro2_input_suyo.txt", "%lg  %*s %lg %lg");
    measured->SetMarkerStyle(kOpenCircle);
    measured->SetMarkerColor(kBlue);



    // --------------------------
    // ---------- FIT -----------
    // --------------------------

    // Fit: from 0 to 10
    auto fit = new TF1("linearFit", linearFunct, 0, 0, 10);
    fit->SetLineColor(kBlue);
    fit->SetLineStyle(kDashed);

    // call TH1::Fit with the name of the TF1 object
    measured->Fit("linearFit");

    // Get parameters of the fitting
    Double_t p1 = fit->GetParameter(0);
    Double_t p2 = fit->GetParameter(1);
    Double_t e1 = fit->GetParError(0);
    Double_t e2 = fit->GetParError(1);
   

    
    // --------------------------
    // ---------- DRAW ----------
    // --------------------------

    // TLegend: L: draw line, P: draw polymarker, F: draw a box 
    auto legend = new TLegend(.1,.7,.48,.9,"Lab. Lesson 2"); 
    legend->AddEntry(expected, "Expected points","FL"); 
    legend->AddEntry(measured, "Measured Points","PE");

    // Fit: params in the legend 
    char paramStr[60];
    sprintf( paramStr, "(%.2f \\pm  %.2f) + (%.2f \\pm  %.2f) X", p1, e1, p2, e2);
    legend->AddEntry(fit, paramStr, "L");
    

    // Axis' limits setting
    mg->GetXaxis()->SetLimits(0.0, 11); // X
    mg->SetMinimum(-2.); //Y 
    mg->SetMaximum(80.); // Y

    // Labels
    mg->GetXaxis()->SetTitle("Length (cm)");
    mg->GetYaxis()->SetTitle("Arb. Units");
    
    // Draw: option "3" shows the errors as a band, P point, E errors
    mg->Add( expected, "A3" );
    mg->Add( measured , "APE" );
    
    mg->Draw("APE3"); 
    legend->Draw();

    // save
    c1->Print("linearFit.png");  


}