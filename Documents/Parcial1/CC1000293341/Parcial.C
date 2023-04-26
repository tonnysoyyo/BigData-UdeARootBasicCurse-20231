{   
    // Data

    // Data for the first graph
    // First dataset
    const Int_t np_1 = 12;
    Double_t x_1[np_1]       = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 18};
    Double_t y_1[np_1]       = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.120};
    Double_t exl_1[np_1]     = {0.75, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 0.75, 1.25, 4};
    Double_t exh_1[np_1]     = {0.75, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 0.75, 1.25, 22};
    Double_t eylstat_1[np_1] = {0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.001};
    Double_t eyhstat_1[np_1] = {0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.001};

    // Second dataset
    const Int_t np_2 = 12;
    Double_t x_2[np_2]       = {12.5, 13.5, 14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
    Double_t y_2[np_2]       = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
    Double_t exl_2[np_2]     = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
    Double_t exh_2[np_2]     = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
    Double_t eylstat_por_2[np_2] = {2.1, 1.6, 1.3, 1.2, 0.8, 0.8, 0.7, 0.8, 0.9, 0.9, 0.9, 1.3};
    Double_t eyhstat_por_2[np_2] = {2.1, 1.6, 1.3, 1.2, 0.8, 0.8, 0.7, 0.8, 0.9, 0.9, 0.9, 1.3};
    Double_t eylsys_por_2[np_2]  = {3.1, 2.7, 2.4, 2.6, 2.6, 2.8, 2.9, 2.6, 3.2, 2.3, 2.8, 2.6};
    Double_t eyhsys_por_2[np_2]  = {3.1, 2.7, 2.4, 2.6, 2.6, 2.8, 2.9, 2.6, 3.2, 2.3, 2.8, 2.6};

    Double_t eylstat_2[np_2];
    Double_t eyhstat_2[np_2];
    Double_t eylsys_2[np_2];
    Double_t eyhsys_2[np_2];

    for(int i=0;i<np_2;i++){
        eylstat_2[i] = eylstat_por_2[i]*y_2[i]/100;
        eyhstat_2[i] = eyhstat_por_2[i]*y_2[i]/100;
        eylsys_2[i] = eylsys_por_2[i]*y_2[i]/100;
        eyhsys_2[i] = eyhsys_por_2[i]*y_2[i]/100;
    }

    // Data for the second graph
    // Third dataset
    const Int_t np_3 = 7;

    Double_t x_3[np_3]       = {0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2.0};
    Double_t y_3[np_3]       = {0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
    Double_t exl_3[np_3]     = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
    Double_t exh_3[np_3]     = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
    Double_t eylstat_por_3[np_3] = {0.6, 0.6, 0.6, 0.7, 0.8, 1.0, 1.0};
    Double_t eyhstat_por_3[np_3] = {0.6, 0.6, 0.6, 0.7, 0.8, 1.0, 1.0};
    Double_t eylsys_por_3[np_3]  = {1.8, 2.0, 1.9, 3.9, 4.3, 4.3, 4.4};
    Double_t eyhsys_por_3[np_3]  = {1.8, 2.0, 1.9, 3.9, 4.3, 4.3, 4.4};

    Double_t eylstat_3[np_3];
    Double_t eyhstat_3[np_3];
    Double_t eylsys_3[np_3];
    Double_t eyhsys_3[np_3];

    for(int i=0;i<np_3;i++){
        eylstat_3[i] = eylstat_por_3[i]*y_3[i]/100;
        eyhstat_3[i] = eyhstat_por_3[i]*y_3[i]/100;
        eylsys_3[i] = eylsys_por_3[i]*y_3[i]/100;
        eyhsys_3[i] = eyhsys_por_3[i]*y_3[i]/100;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Code to read the data from the file and create the TGraphMultiErrors //

    auto c1 = new TCanvas("c1", "Parcial 1", 200, 10, 800, 500);
    c1->SetGrid();
    c1->GetFrame()->SetBorderSize(12);

    TPad *pad1 = new TPad("pad1", "Pad 1", 0.0, 0.0, 0.65, 1.0);
    pad1->Draw();
    pad1->cd();

    auto multi = new TMultiGraph();

    auto gme_11 = new TGraphMultiErrors("gme_11", "TGraphMultiErrors Example", np_1, x_1, y_1, exl_1, exh_1, eylstat_1, eyhstat_1);
    gme_11->SetMarkerStyle(25);
    gme_11->SetMarkerColor(kRed);
    gme_11->SetMarkerSize(0.5);
    gme_11->SetLineColor(kRed);
    multi->Add(gme_11, "APE");
    
    auto gme_12 = new TGraphMultiErrors("gme_12", "TGraphMultiErrors Example", np_2, x_2, y_2, exl_2, exh_2, eylstat_2, eyhstat_2);
    gme_12->AddYError(np_2, eylsys_2, eyhsys_2);
    gme_12->SetMarkerStyle(20);
    gme_12->SetLineColor(kBlack);
    //gme_12->GetAttLine(0)->SetLineColor(kBlack);
    //gme_12->GetAttLine(1)->SetLineColor(kBlack);
    gme_12->GetAttFill(1)->SetFillStyle(0);
    multi->Add(gme_12);
    //gme_12->Draw("APS ; Z ; 5 s=0.5");
    //multi->Draw("APES ; Z ; 5 s=0.5"); // La Z me desaparece el error de la barra en x
    multi->GetXaxis()->SetNdivisions(5, 5, 0);
    multi->GetYaxis()->SetNdivisions(5, 5, 0);

    multi->GetYaxis()->SetTitle("#it{R}_{s}");
    multi->GetYaxis()->SetTitleOffset(1.2);
    multi->GetXaxis()->SetTitle("#it{p}_{T} (GeV)");
    multi->GetXaxis()->CenterTitle();
    multi->GetXaxis()->SetTitleOffset(1.2);

    multi->GetXaxis()->SetRangeUser(0.0, 75.0);
    multi->GetYaxis()->SetRangeUser(0.07, 0.139);

    multi->Draw("APES; 5 s=0.5");

    // Define a fit
    auto LFit = new TF1("Exponential", "[0]*exp([1]*x)+[2]", x_2[0]-exl_2[0], x_2[np_2-1]+exl_2[np_2-1]);
    
    LFit->SetParameter(0, y_2[0]);
    LFit->SetParameter(1, -0.5);
    LFit->SetParameter(2, x_2[0]);
    
    gme_12->Fit(LFit, "R");

    LFit->SetLineColor(kBlue);
    LFit->SetLineWidth(3);
    LFit->DrawClone("Same");
    pad1->cd();

    auto legend1 = new TLegend(.15,.19,.35,.37);
    legend1->AddEntry(gme_12,"CMS data; |#it{y}| < 2.4","EP");
    legend1->AddEntry(LFit,"Fit to the CMS data","L");
    legend1->AddEntry(gme_11,"LHCb data; 2 < #it{y} < 4.5","EP");
    legend1->SetTextSize(0.04);
    legend1->SetFillStyle(0);
    legend1->SetBorderSize(0);
    legend1->Draw("Same");

    auto legend2 = new TLegend(.55,.7,.9,.88);
    legend2->AddEntry((TObject*)nullptr, " #bf{CMS}", ""); // The (TObject*) casting specifies that you want to use the version of AddEntry() that takes a TObject* as the first argument, rather than the version that takes a const char*
    legend2->AddEntry((TObject*)nullptr, " L = 61.6 fb^{-1}", "");
    legend2->AddEntry((TObject*)nullptr, "#sqrt{s} = 13 TeV", "");
    legend2->SetTextSize(0.04);
    legend2->SetFillStyle(0);
    legend2->SetBorderSize(0);
    legend2->Draw("Same");

    auto legend3 = new TLegend(.5,.38,.9,.46);
    legend3->AddEntry((TObject*)nullptr, "Function", ""); // The (TObject*) casting specifies that you want to use the version of AddEntry() that takes a TObject* as the first argument, rather than the version that takes a const char*
    legend3->AddEntry((TObject*)nullptr, "and fit parameters", "");
    legend3->SetTextSize(0.032);
    legend3->SetFillStyle(0);
    legend3->SetBorderSize(0);
    legend3->Draw("Same");


    c1->cd(); // Return to canvas
    TPad *pad2 = new TPad("pad2", "Pad 2", 0.6, 0.0, 1.0, 1.0);
    pad2->Draw();
    pad2->cd();


    auto gme_2 = new TGraphMultiErrors("gme", "", np_3, x_3, y_3, exl_3, exh_3, eylstat_3, eyhstat_3);
    gme_2->AddYError(np_3, eylsys_3, eyhsys_3);
    gme_2->SetMarkerStyle(20);
    gme_2->SetLineColor(kBlack);
    gme_2->GetAttFill(1)->SetFillStyle(0);

    gme_2->GetXaxis()->SetNdivisions(5, 5, 0);
    gme_2->GetYaxis()->SetNdivisions(5, 5, 0);
    gme_2->GetXaxis()->SetRangeUser(-0.1, 2.5);
    gme_2->GetYaxis()->SetRangeUser(0.07, 0.139);

    gme_2->GetYaxis()->SetLabelOffset(-999);
    gme_2->GetXaxis()->SetLabelOffset(0.005);
    gme_2->GetYaxis()->SetLabelSize(0.0);
    gme_2->GetXaxis()->SetLabelSize(0.05);

    gme_2->GetXaxis()->SetTitle("|#it{y}|");
    gme_2->GetXaxis()->SetTitleSize(0.055);
    gme_2->GetXaxis()->CenterTitle();
    gme_2->GetXaxis()->SetTitleOffset(0.8);

    gme_2->Draw("APS; 5 s=0.5");

    pad2->cd();

    TLatex* latex = new TLatex();
    latex->SetTextSize(0.062);
    latex->SetNDC();
    latex->DrawLatex(0.28, 0.285, "#bf{12 < #it{p}_{T} < 70 GeV}");
}