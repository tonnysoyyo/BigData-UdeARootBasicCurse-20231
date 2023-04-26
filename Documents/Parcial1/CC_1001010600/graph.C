void graph(){
    TCanvas *c1 = new TCanvas("Graph", "Graph", 1200, 800);
    c1->SetTitle("Efficiency-corrected yield ratio #R_s");

    //Creamos dos pads
    auto p1 = new TPad("p1", "", .05, .05, .6, .95);
    auto p2 = new TPad("p2", "", .55, .05, .95, .95);
    p1->Draw(); p2->Draw();

    //Pad 1
    p1->cd();

    auto multiG = new TMultiGraph();

    //LHCb Data
    double LCHb_Pt[12] = {1.27, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 27};
    double Rs_LHCb[12] = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.120};
    double SLHCb[12] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 13};
    double Sstat_LHCb[12] = {0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002};

    auto LHCbPt = new TGraphMultiErrors("LHCbPt", "", 12, LCHb_Pt, Rs_LHCb, SLHCb, SLHCb, Sstat_LHCb, Sstat_LHCb);
    LHCbPt->SetMarkerStyle(24); LHCbPt->SetMarkerColor(kRed);
    LHCbPt->SetLineColor(kRed);

    //CMS pt data
    double pt[12] = {12.5, 13.5, 14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 38.5, 57.5};
    double Rs_pt[12] = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
    double Spt[12] = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 4.5, 12.5};
    double Sstat_pt[12] = {0.0027594, 0.0019136, 0.0015145, 0.0013848, 0.0009080, 0.0008848, 0.0007735, 0.0008880, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
    double Ssys_pt[12] = {0.0040734, 0.0032292, 0.0027960, 0.0030004, 0.0029510, 0.0030968, 0.0032045, 0.0028860, 0.0034912, 0.0025185, 0.0030464, 0.0029042};

    auto CMSpt = new TGraphMultiErrors("CMSpt", "", 12, pt, Rs_pt, Spt, Spt, Sstat_pt, Sstat_pt);
    CMSpt->AddYError(12, Ssys_pt, Ssys_pt);
    CMSpt->SetMarkerStyle(20);
    CMSpt->GetAttFill(1)->SetFillStyle(0);

    //FIT
    auto fit = new TF1("CMS data fit", "[0] + [1] * TMath::Exp(-(x - [2])*[3])", 12.5, 70);
    fit->SetParameters(0.11, 1, 12.5, 1);
    fit->SetLineColor(kBlue);
    fit->SetRange(12., 70);
    auto fitResults = CMSpt->Fit("CMS data fit", "SR");

    //Dibuja los graficos
    multiG->GetXaxis()->SetTitle("p_{t} (GeV)"); multiG->GetXaxis()->CenterTitle(true);
    multiG->GetYaxis()->SetTitle("R_{s}");
    multiG->GetXaxis()->SetLimits(0.,75); multiG->GetXaxis()->SetLabelSize(0.025); multiG->GetXaxis()->SetNdivisions(8, 1, 4);
    multiG->GetYaxis()->SetRangeUser(0.07,0.14); multiG->GetYaxis()->SetLabelSize(0.025); multiG->GetYaxis()->SetNdivisions(4, 4, 2);
    multiG->Add(CMSpt, "APS ; 5 s=0.5");
    multiG->Add(LHCbPt, "AP");
    multiG->Draw("a");
    
    //Leyenda
    auto legend = new TLegend(.13,.15,.55,.35,"");
    legend->AddEntry(CMSpt, "CMS data; |y|<2.4");
    legend->AddEntry(fit, "Fit to the CMS data");
    legend->AddEntry(LHCbPt, "LHCb data; 2 < y < 4.5");
    legend->SetFillStyle(0); legend->SetBorderSize(0);
    legend->Draw();

    //Texto
    auto CMS = new TLatex();
    CMS->SetTextSize(0.045);
    CMS->DrawLatex(49, 0.13, "CMS");
    CMS->SetTextFont(42);
    CMS->DrawLatex(49, 0.125, "L = 61.6 fb^{-1}");
    CMS->DrawLatex(49, 0.12, "#sqrt{s} = 13 TeV");

    auto fitText = new TLatex();
    fitText->SetTextSize(0.035);
    fitText->SetTextFont(42);
    fitText->DrawLatex(47, 0.095, "Function");
    fitText->DrawLatex(47, 0.092, "and fit parameters");
    fitText->DrawLatex(47, 0.089, "Fit = a + be^{-(x-c)d}");
    fitText->DrawLatex(47, 0.086, Form("a = %1.2f #pm %1.5f", fitResults->Parameter(0), fitResults->ParError(0)));
    fitText->DrawLatex(47, 0.083, Form("b = %1.2f #pm %1.5f", fitResults->Parameter(1), fitResults->ParError(1)));
    fitText->DrawLatex(47, 0.08, Form("c = %1.2f #pm %1.5f", fitResults->Parameter(2), fitResults->ParError(2)));
    fitText->DrawLatex(47, 0.077, Form("d = %1.2f #pm %1.5f", fitResults->Parameter(3), fitResults->ParError(3)));

    //Pad 2
    p2->cd();
    
    //CMS y data
    double y[7] = {0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2};
    double Rs_y[7] = {0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
    double Sy[7] = {0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
    double Sstat_y[7] = {0.000666, 0.0006624, 0.00066, 0.0007882, 0.0008936, 0.001069, 0.001099};
    double Ssys_y[7] = {0.001998, 0.002208, 0.00209, 0.0043914, 0.0048031, 0.0045967, 0.0048356};

    auto CMSy = new TGraphMultiErrors("CMSy", "", 7, y, Rs_y, Sy, Sy, Sstat_y, Sstat_y);
    CMSy->AddYError(12, Ssys_y, Ssys_y);
    
    CMSy->GetXaxis()->SetTitle("|y|"); CMSy->GetXaxis()->CenterTitle(true); 
    CMSy->GetXaxis()->SetRangeUser(-0.5,2.5); CMSy->GetXaxis()->SetNdivisions(8, 1, 5);
    CMSy->GetYaxis()->SetRangeUser(0.07,0.14); CMSy->GetYaxis()->SetLabelSize(0); CMSy->GetYaxis()->SetNdivisions(20);
    
    CMSy->SetMarkerStyle(20);
    CMSy->GetAttFill(1)->SetFillStyle(0);  
    CMSy->Draw("APS ; 5 s=0.4");
    
    //Texto
    auto pt_text = new TLatex();
    CMS->SetTextSize(0.06);
    CMS->SetTextFont(42);
    CMS->DrawLatex(0.8, 0.09, "12 < p_{t} < 70 GeV");
    
    c1->Print("Graph.png");
}