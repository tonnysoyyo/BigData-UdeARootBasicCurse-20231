void Homework(){
    auto myc = new TCanvas("myc","Homework",200,10,600,400);

    myc -> SetGrid();

    auto multi = new TMultiGraph();
    multi -> SetTitle("Measurement XYZ and Expectation;length [cm];Arb.Units");

    auto graph_me = new TGraphErrors("macro2_input_suyo.txt");
    auto graph_exp = new TGraphErrors("macro2_input_expected.txt");
    
    graph_exp->SetFillColor(kYellow);
    graph_exp->SetFillStyle(1001); // 1001: solid

    graph_me->SetMarkerStyle(kOpenCircle);

    myc->Print("plots/Homework.png");

    multi -> Add(graph_exp, "A3");
	multi -> Add(graph_me, "APE");
	multi -> Draw("APE");

    multi -> GetXaxis()->SetNdivisions(5, 5, 0);
    
    // Define a fit
    auto LFit = new TF1("linear", "[0] + [1]*x", 1, 10);
    
    double fitRangeMin = 1.0;
    double fitRangeMax = 10.0;
    LFit->SetRange(fitRangeMin, fitRangeMax);
    
    graph_me->Fit(LFit);

    LFit->SetLineColor(kRed);
    LFit->SetLineStyle(0);

    //LFit->Draw("Same");

    // Retrieve the values of fit
    double slope = LFit->GetParameter(1);
    double intercept = LFit->GetParameter(0);
    double chi2 = LFit->GetChisquare();
    double ndf = LFit->GetNDF();

    // Legend
    auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 2");
    legend->AddEntry(graph_exp,"Expected Points","LF");
    legend->AddEntry(graph_me,"Measured Points","LP");
    legend->AddEntry(LFit,"Linear Fit","L");
    legend->Draw("Same");
    
    auto legend2 = new TLegend(.7, .1, .9, .3,"Fit Solution");
    legend2->AddEntry((TObject*)0, Form("Slope = %.2f", slope), "");
    legend2->AddEntry((TObject*)0, Form("Intercept = %.2f", intercept), "");
    legend2->AddEntry((TObject*)0, Form("#chi^{2}/ndf = %.2f", chi2/ndf), "");
    legend2->Draw("Same");
    
    myc->Print("plots/Tarea.png");
}