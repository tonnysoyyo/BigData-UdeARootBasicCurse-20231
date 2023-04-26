#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void parcial1(){

    //Datos de R_s en función de p_t en CMS
    Double_t x[12] = {12.5, 13.5, 14.5, 15.5, 17.0, 19.0, 21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
    Double_t y[12] = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
    Double_t ex[12] = {0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.5, 1.5, 1.5, 2.5, 5.5, 12.5};
    Double_t ey[12] = {0.0027593999999999995, 0.0019136000000000001, 0.0015145, 0.0013847999999999998, 0.0009080000000000001, 0.0008848, 0.0007735, 0.000888, 0.0009819, 0.0009855, 0.0009792, 0.0014521};
    Double_t bey[12] = {0.0040734, 0.0032292, 0.0027960000000000003, 0.0030004000000000003, 0.0029510000000000005, 0.0030968000000000002, 0.0032045000000000003, 0.002886, 0.0034912000000000003, 0.0025184999999999995, 0.0030463999999999995, 0.0029042};

    //Datos de R_s en función de y en CMS
    Double_t x_y[7] = {0.125, 0.375, 0.625, 0.875, 1.15, 1.4500000000000002, 2.0};
    Double_t y_y[12] = {0.111, 0.1104, 0.11, 0.1126, 0.1117, 0.1069, 0.1099};
    Double_t ex_y[12] = {0.125, 0.125, 0.125, 0.125, 0.15000000000000002, 0.15000000000000002, 0.3999999999999999};
    Double_t ey_y[12] = {0.0006659999999999999, 0.0006624, 0.00066, 0.0007882, 0.0008935999999999999, 0.0010689999999999999, 0.001099};
    Double_t bey_y[12] = {0.001998, 0.002208, 0.00209, 0.0043914, 0.004803099999999999, 0.0045967, 0.004835600000000001};

    auto c1 = new TCanvas("c1", "", 1000, 700);
    //Histogramas sólo por motivos del plot.
    auto h0 = new TH1D("h0", "", 1, 0, 75);
    auto h1 = new TH1D("h1", "", 1, -0.05, 2.5);

    //Datos de R_s en función de p_t en LHCb
    auto LHCb_pt = new TGraphAsymmErrors("LHCb_pt.txt", "%lg, %lg, %lg, %lg, %lg, %lg");
    auto CMS_pt = new TGraphMultiErrors("cmspt", "", 12, x, y, ex, ex, ey, ey);
    CMS_pt->AddYError(12, bey, bey);
    auto CMS_y = new TGraphMultiErrors("cmsy", "", 7, x_y, y_y, ex_y, ex_y, ey_y, ey_y);
    CMS_y->AddYError(7, bey_y, bey_y);
    //auto func = new TF1("fit", "[0]/(x-[1])+[2]", 12, 70);

    //Ajuste de los datos a función A*exp(B*x)+C.
    auto func = new TF1("fit", "[0]*exp(-[1]*x)+[2]", 12, 70);
    func->SetParNames("Amplitude", "Lambda", "YShift");
    func->SetParameter(0,0.29);
    func->SetParameter(1, 0.24);
    func->SetParameter(2,0.11);

    TFitResultPtr r = CMS_pt->Fit("fit","ISRN");

    r->Print();
    //COnfiguración de estilos para el plot.
    CMS_pt->SetMarkerStyle(20);
    CMS_pt->SetLineColor(kBlack);
    CMS_pt->GetAttLine(0)->SetLineColor(kBlack);
    CMS_pt->GetAttLine(1)->SetLineColor(kBlack);
    CMS_pt->GetAttFill(1)->SetFillStyle(0);
    CMS_pt->GetXaxis()->CenterTitle(true);

    CMS_y->SetMarkerStyle(20);
    CMS_y->SetLineColor(kBlack);
    CMS_y->GetAttLine(0)->SetLineColor(kBlack);
    CMS_y->GetAttLine(1)->SetLineColor(kBlack);
    CMS_y->GetAttFill(1)->SetFillStyle(0);
    CMS_y->GetXaxis()->CenterTitle(true);

    func->SetLineColor(kBlue);

    auto legend11 = new TLegend(.14,.14,.5,.4);
    auto legend12 = new TPaveText(.5,.7,.87,.87, "NDC");
    auto legend13 = new TPaveText(.6, .14, .87, .4, "NDC");
    auto legend2 = new TPaveText(.3, .2, .7, .4, "NDC");

    legend11->SetFillColor(0);
    legend11->SetLineColor(0);
    legend12->SetFillColor(0);
    legend12->SetLineColor(0);
    legend13->SetFillColor(0);
    legend13->SetLineColor(0);
    legend2->SetFillColor(0);
    legend2->SetLineColor(0);

    LHCb_pt->SetMarkerStyle(25);
    LHCb_pt->SetLineColor(kRed);
    LHCb_pt->SetMarkerColor(kRed);
    LHCb_pt->SetMarkerSize(0.5);
    LHCb_pt->SetTitle(Form("CMS Measurement of R_{s}; p_{T} (GeV); R_{s}"));

    legend11->AddEntry(CMS_pt,Form("CMS data; |y| < 2.4"),"LP");
    legend11->AddEntry(func,Form("Fit to the CMS data"));
    legend11->AddEntry(LHCb_pt,Form("LHCb data; 2 < y < 4.5"),"LP");
    legend12->AddText(Form("#bf{CMS}"));
    legend12->AddText(Form("L = 61.6 fb^{-1}"));
    legend12->AddText(Form("#sqrt{s} = 13 TeV"));
    legend13->AddText(Form("Fitting function: Ae^{#lambdax}+C"));
    legend13->AddText(Form("#chi^{2} / ndf = %.3f / %d", r->Chi2(), func->GetNDF()));
    legend13->AddText(Form("A: %.3f #pm %.3f", r->Parameter(0), r->ParError(0)));
    legend13->AddText(Form("#lambda: %.3f #pm %.3f", r->Parameter(1), r->ParError(1)));
    legend13->AddText(Form("C: %.3f #pm %.3f", r->Parameter(2), r->ParError(2)));

    c1->Divide(2, 1);

    TPad* pad1 = (TPad*)c1->cd(1);
    c1->cd(1)->SetPad(0.1, 0.0, 0.7, 1.0);

    h0->SetStats(0);
    h0->GetXaxis()->SetTitle("p_{T} (GeV)");
    h0->GetYaxis()->SetTitle("R_{s}");
    h0->GetYaxis()->SetRangeUser(0.07, 0.14);
    h0->GetYaxis()->SetNdivisions(504);
    h0->GetXaxis()->SetNdivisions(505);
    h0->GetXaxis()->CenterTitle(true);
    h0->Draw();
    CMS_pt->Draw("PSSame; ;5 s=0.5");
    func->Draw("C Same");
    LHCb_pt->Draw("PE Same");
    legend11->Draw("Same");
    legend12->Draw("Same");
    legend13->Draw("Same");

    TPad* pad2 = (TPad*)c1->cd(2);
    c1->GetPad(2)->SetPad(0.65, 0.0, 1.0, 1.0);
    c1->GetPad(2)->SetLeftMargin(.01);
    pad2->SetBottomMargin(0.1);
    h1->SetStats(0);
    h1->GetXaxis()->SetTitle("|y|");
    h1->GetYaxis()->SetRangeUser(0.07, 0.14);
    h1->GetYaxis()->SetNdivisions(504);
    h1->GetXaxis()->SetNdivisions(504);
    h1->GetYaxis()->SetLabelSize(0);
    h1->GetXaxis()->SetTitleSize(0.05);
    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetXaxis()->CenterTitle(true);

    legend2->AddText("12 < p_{T} < 70 GeV");

    h1->Draw();
    CMS_y->Draw("PS ; Z ; 5 s=0.5");
    legend2->Draw("Same");
    TLatex leg2;

    c1->SaveAs("Parcial1.pdf");
    
    return 0;
}