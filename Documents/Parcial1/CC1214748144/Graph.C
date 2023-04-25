void Graph(){
    auto *c1 = new TCanvas("c1", "", 200, 10, 700, 500);
    ///////////////////////////////////////////
    //se definene los subplots

    auto *p1 = new TPad("p1", "", .05, .05, .6, .95);
    auto *p2 = new TPad("p2", "", .55, .05, .95, .95);
    p1->Draw(); 
    p2->Draw();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    p1->cd();
    auto *multi = new TMultiGraph();

    //CMS1
    const Int_t n=12; 
    Double_t pt[n] = {12.5, 13.5, 14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 38.5, 57.5};
    Double_t Rs[n] = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
    Double_t Spt[n] = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 4.5, 12.5};
    Double_t Sstat_rs[n] = {0.0027594, 0.0019136, 0.0015145, 0.0013848, 0.0009080, 0.0008848, 
    0.0007735, 0.0008880, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
    Double_t Ssys_rs[n] = {0.0040734, 0.0032292, 0.0027960, 0.0030004, 0.0029510, 0.0030968, 0.0032045, 
    0.0028860, 0.0034912, 0.0025185, 0.0030464, 0.0029042};


    auto *CMS1 = new TGraphMultiErrors("", " " , n , pt, Rs, Spt, Spt, Sstat_rs, Sstat_rs);
    CMS1->AddYError(n, Ssys_rs, Ssys_rs);
    CMS1->SetMarkerStyle(20);
    CMS1->GetAttFill(1)->SetFillStyle(0);

    //LHCB1
    Double_t pt1[n] = {1.27, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 27};
    Double_t Rs1[n] = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.120};
    Double_t Spt1[n] = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 13};
    Double_t Srs1[n] = {0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.003, 0.002};

    auto LHCB1 = new TGraphMultiErrors("", "", n, pt1, Rs1, Spt1, Spt1, Srs1, Srs1);
    LHCB1->SetMarkerStyle(24); 
    LHCB1->SetMarkerColor(kRed);
    LHCB1->SetLineColor(kRed);

    //ajuste 
    auto f = new TF1("f", "[0] + [1] * TMath::Exp(-[3]*(x - [2]))", 11, 70);
    f->SetParameters(0.11, 1, 12.5, 1);
    f->SetLineColor(kBlue);
    f->SetRange(11., 70);
    f->SetLineColor(kBlue);
    f->SetLineWidth(2);
    CMS1->Fit("f");
    auto params = CMS1->Fit("f", "SR");


    //juntando los plots
    multi->GetXaxis()->SetTitle("p_{t} [GeV]"); 
    multi->GetXaxis()->CenterTitle(true);
    multi->GetYaxis()->SetTitle("R_{s}");
    multi->GetXaxis()->SetLimits(0.,75); 
    multi->GetXaxis()->SetLabelSize(0.025); 
    multi->GetXaxis()->SetNdivisions(8, 1, 4);
    multi->GetYaxis()->SetRangeUser(0.07,0.14); 
    multi->GetYaxis()->SetLabelSize(0.025); 
    multi->GetYaxis()->SetNdivisions(4, 4, 2);
    multi->Add(CMS1, "APS ; 5 s=0.5");
    multi->Add(LHCB1, "AP");
    multi->Draw("AP");

    //Texto
    auto CMS = new TLatex();
    CMS->SetTextSize(0.045);
    CMS->SetTextFont(42);

    CMS->DrawLatex(50, 0.125, "#sqrt{s} = 13 TeV");
    CMS->DrawLatex(50, 0.131, "L = 61.6 fb^{-1}");
    CMS->DrawLatex(50, 0.135, "CMS");



    auto fitText = new TLatex();
    fitText->SetTextSize(0.035);
    fitText->SetTextFont(42);
    fitText->DrawLatex(47, 0.095, "R_{s}(P_{t}) = a + be^{-d(x-c)}");
    fitText->DrawLatex(47, 0.086, Form("a = %.2f #pm %.2f", params->Parameter(0), params->ParError(0)));
    fitText->DrawLatex(47, 0.083, Form("b = %.2f #pm %.2f", params->Parameter(1), params->ParError(1)));
    fitText->DrawLatex(47, 0.08, Form("c = %.2f #pm %.2f", params->Parameter(2), params->ParError(2)));
    fitText->DrawLatex(47, 0.077, Form("d = %.2f #pm %.2f", params->Parameter(3), params->ParError(3)));


    //Leyenda
    auto *legend = new TLegend(.13,.15,.55,.35);
    legend->AddEntry(CMS1, "CMS data; |y|<2.4");
    legend->AddEntry(f, "Fit to the CMS data");
    legend->AddEntry(LHCB1, "LHCb data; 2 < y < 4.5");
    legend->SetBorderSize(0);
    legend->Draw();


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   //segunda gráfica
    p2->cd();
    //CMS2  
    const Int_t np = 7;
    Double_t x[np]={0.125, 0.375, 0.625, 0.875, 1.15, 1.45, 2};
    Double_t y[np]={0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
    Double_t ex[np]={0.125, 0.125, 0.125, 0.125, 0.15, 0.15, 0.4};
    Double_t eystat[np] = {0.000666, 0.0006624, 0.00066, 0.0007882, 0.0008936, 0.001069, 0.001099};
    Double_t eysys[np]  = {0.001998, 0.002208, 0.00209, 0.0043914, 0.0048031, 0.0045967, 0.0048356};


    auto CMS2 = new TGraphMultiErrors("", "",np ,x, y, ex, ex, eystat, eystat);
    CMS2->AddYError(10, eysys, eysys);
    CMS2->GetXaxis()->SetTitle("|y|"); 
    CMS2->GetXaxis()->CenterTitle(true); 
    CMS2->GetYaxis()->SetRangeUser(0.05,0.15); 
    CMS2->GetYaxis()->SetLabelSize(0);
    CMS2->GetYaxis()->SetNdivisions(20);
    CMS2->SetMarkerStyle(20);
    CMS2->GetAttFill(1)->SetFillStyle(0);  
    CMS2->Draw("APS ; 5 s=0.5");

    //texto 
    auto text1 = new TLatex(0.7, 0.08, "12 <p_{t}< 70 GeV");
    text1->SetTextSize(0.06);
    text1->Draw();

    ///////////////////////////////////////
    c1->Print("Graf.svg");
}