#include <vector>

void Graph_(){

    //LHCb Data
    std::vector<double> x_LHCb{1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 20};
    std::vector<double> y_LHCb{0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.120};
    std::vector<double> ex_LHCb{0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 4.5};
    std::vector<double> ex2_LHCb{0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 20.5};
    std::vector<double> ey_LHCb{0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.001};
    const int n1 = x_LHCb.size();

    //CMS data
    std::vector<double> x_CMS{12.5, 13.5, 14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 38.5, 57.5};
    std::vector<double> y_CMS{0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
    std::vector<double> ex_CMS{0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 1.5, 2.5, 4.5, 12.5};
    std::vector<double> ey_statCMS{0.0028, 0.0019, 0.0015, 0.0014, 0.0009, 0.0009, 0.0008, 0.0009, 0.0010, 0.0010, 0.0010, 0.0014};
    std::vector<double> ey_sysCMS{0.0041, 0.0032, 0.0028, 0.0030, 0.0029, 0.0031, 0.0032, 0.0029, 0.0035, 0.0025, 0.0030, 0.0029};
    const int n2 = ex_CMS.size();

    //|y| data
    std::vector<double> y{0.125, 0.375, 0.625, 0.875, 1.150, 1.450, 2.000};
    std::vector<double> Ry{0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
    std::vector<double> Sy{0.125, 0.125, 0.125, 0.125, 0.150, 0.150, 0.400};
    std::vector<double> y_staty{0.0006, 0.0006, 0.0006, 0.0007, 0.0008, 0.0011, 0.0011};
    std::vector<double> y_sysy{0.0019, 0.0022, 0.0020, 0.0044, 0.0048, 0.0046, 0.0048};
    const int n3 = y.size();

    //canvas
    TCanvas *C = new TCanvas("Graph", "Graph", 1200, 600);

    TPad *P1 = new TPad("P1", "P1", .0, .0, .7, 1.);

    TPad *P2 = new TPad("P2", "P2", .65, .0, 1.0, 1.0);

    P1->Draw(); P2->Draw(); P1->cd();
 
    auto G = new TMultiGraph();

    auto LHCb = new TGraphMultiErrors("LHCb","",n1, x_LHCb.data(), y_LHCb.data(), ex_LHCb.data(), ex2_LHCb.data(), ey_LHCb.data(), ey_LHCb.data());
    LHCb->SetMarkerSize(0.5);
    LHCb->SetMarkerStyle(25); LHCb->SetMarkerColor(2);
    LHCb->SetLineColor(2);

    auto CMSGraph = new TGraphMultiErrors("CMSGraph","",n2, x_CMS.data(), y_CMS.data(), ex_CMS.data(), ex_CMS.data(),ey_statCMS.data(),ey_statCMS.data());
    CMSGraph->AddYError(n2, ey_sysCMS.data(), ey_sysCMS.data());
    CMSGraph->GetAttFill(1)->SetFillStyle(0);
    CMSGraph->SetMarkerSize(1);
    CMSGraph->SetMarkerStyle(20);
    CMSGraph->SetTitle(";#it{p}_{T}(GeV);#it{R_{s}}");
    CMSGraph->GetXaxis()->CenterTitle();
    //fit
    auto fit = new TF1("CMS data fit", "[0] + [1] * exp(-(x - [2])*[3])", 12.5, 70);
    fit->SetParameters(0.11, 1, 12.5, 1);
    fit->SetLineColor(4);
    fit->SetLineWidth(2);
    fit->SetRange(12., 70);
    auto fitResults = CMSGraph->Fit("CMS data fit", "SR");
    //gráfica
    G->SetTitle(";p_{T} (GeV/c);#it{R}_{s}");
    G->GetXaxis()->SetTitle("p_{t} (GeV)"); G->GetXaxis()->CenterTitle(true);
    G->GetYaxis()->SetTitle("R_{s}");
    G->GetXaxis()->SetLimits(0.,75); G->GetXaxis()->SetLabelSize(0.025);
    G->GetXaxis()->SetNdivisions(8, 1, 4);
    G->GetYaxis()->SetRangeUser(0.07,0.139); G->GetYaxis()->SetLabelSize(0.025); G->GetYaxis()->SetNdivisions(4, 4, 2);
    G->Add(CMSGraph, "APS ; 5 s=0.5");
    G->Add(LHCb, "AP");
    G->Draw("a");
    //legends
    auto legend = new TLegend(.14,.15,.45,.35,"");
    legend->AddEntry(CMSGraph,"CMS data; |#it{y}| < 2.4","EP");
    legend->AddEntry(fit,"Fit to the CMS data","L");
    legend->AddEntry(LHCb,"LHCb data; 2< #it{y} <4.5","EP");
    legend->SetBorderSize(0);
    legend->Draw();

    auto legend0 = new TLegend(.55,.25,1.,.45,"");
    legend0->AddEntry(fit,"Fit: a + be^{-d(x-c)}","");
    legend0->AddEntry(fit,TString::Format("a = %.4f #pm %.4f",fitResults->Parameter(0), fitResults->ParError(0)),"");
    legend0->AddEntry(fit,TString::Format("b = %.4f #pm %.4f",fitResults->Parameter(1), fitResults->ParError(1)),"");
    legend0->AddEntry(fit,TString::Format("c = %.4f #pm %.4f",fitResults->Parameter(2), fitResults->ParError(2)),"");
    legend0->AddEntry(fit,TString::Format("d = %.4f #pm %.4f",fitResults->Parameter(3), fitResults->ParError(3)),"");

    legend0->SetBorderSize(0);
    legend0->SetFillStyle(0);
    legend0->Draw();

    auto legendCMS = new TLegend(0.575,.75,.9,.9,"");
    legendCMS->AddEntry(fit,"#bf{CMS}","");
    legendCMS->AddEntry(fit,"L = 61.1fb^{-1}","");
    legendCMS->AddEntry(fit,"#sqrt{s} = 13 TeV","");
    legendCMS->SetBorderSize(0);
    legendCMS->SetFillStyle(0);
    legendCMS->Draw();

    //Pad 2
    P2->cd();

    auto yGraph = new TGraphMultiErrors("y","",n3, y.data(), Ry.data(), Sy.data(), Sy.data(),y_staty.data(),y_staty.data());
    //gráfica |y|
    yGraph->AddYError(n3, y_sysy.data(), y_sysy.data());
    yGraph->SetMarkerStyle(20);
    yGraph->GetAttFill(1)->SetFillStyle(0);
    yGraph->SetMarkerSize(1);
    yGraph->GetYaxis()->SetRangeUser(0.07,0.14); 
    yGraph->GetXaxis()->SetRangeUser(-0.8, 2.5);
    yGraph->GetYaxis()->SetLabelOffset(-1000);
    yGraph->GetXaxis()->SetNdivisions(5, 5, 0);
    yGraph->GetYaxis()->SetNdivisions(4, 5, 0);
    yGraph->GetXaxis()->SetLabelSize(0.05);
    yGraph->Draw("APS; 5 s=0.5");
    yGraph->GetXaxis()->SetTitle("|#it{y}|");
    yGraph->GetXaxis()->CenterTitle(true);
    yGraph->GetXaxis()->SetTitleSize(0.04);
    //legend pad2
   auto legendpad2 = new TLegend(.08,.25,.85,.4,"");
    legendpad2->AddEntry(yGraph,"12 < p_{T} < 70 GeV","");
    legendpad2->SetBorderSize(0);
    legendpad2->SetFillStyle(0);
    legendpad2->Draw(); 

    C->Print("PLOT.pdf");

    }