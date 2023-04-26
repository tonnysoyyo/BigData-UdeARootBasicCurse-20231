void Parcial1(){

auto c = new TCanvas("c","canva",500,10,775,470);
TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 0.7, 1);
TPad *pad2 = new TPad("pad2", "pad2", 0.6, 0, 1, 1);

pad1->Draw();
pad1->cd();
const Int_t N = 12;
    Double_t y[N] = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
    Double_t x[N] = {12.5, 13.5,14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
    Double_t ex[N] = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 2, 2, 5.5, 12.5};
    Double_t eystat[N] = {0.0028, 0.0019, 0.0015, 0.0014, 0.0009, 0.0009, 0.0008, 0.0009, 0.0009, 0.0009, 0.0009, 0.0014} ;
    Double_t eysys[N] = {0.0041, 0.0032, 0.0028, 0.0030, 0.0029, 0.0031, 0.0032, 0.0029, 0.0035, 0.0025, 0.0030, 0.0029};

auto Ldots = new TGraphMultiErrors("Ldots", "", N, x, y, ex, ex, eystat, eystat);
    Ldots->AddYError(N, eysys, eysys);
    Ldots->GetAttFill(1)->SetFillStyle(0);
    Ldots->GetYaxis()->SetNdivisions(5, 5, 0);
    Ldots->SetMarkerSize(1);
    Ldots->SetMarkerStyle(20);
    Ldots->GetXaxis()->SetNdivisions(5, 5, 0);
    Ldots->GetYaxis()->SetTitleOffset(1.17);
    Ldots->GetXaxis()->SetLimits(0, 75);
    Ldots->SetMinimum(0.07);
    Ldots->SetMaximum(0.13999);
    Ldots->SetTitle(";#it{p}_{T}(GeV);#it{R_{s}}");
    Ldots->GetXaxis()->CenterTitle();

    Ldots->Draw("APS; 5 s=0.5");

auto exponencial = new TF1("exponencial","[0]*exp(-[1]*(x-[2]))+[3]",12,70);
    exponencial->SetParameter(0, 1);
    exponencial->SetParameter(1, 1); 
    exponencial->SetParameter(2, 10); 
    exponencial->SetParameter(3, 0.11); 

auto r = Ldots->Fit("exponencial","SQ","",11.9,70);
    r->Print();
    auto linea = Ldots->GetFunction("exponencial");
    linea->SetLineColor(4);
    linea->SetLineWidth(2);
    Double_t *params = linea->GetParameters();
    auto errs = linea->GetParErrors();



const Int_t n=12+1;
    Double_t rojasx[n] = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 18.2};
    Double_t rojasy[n] = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.12};
    Double_t rojasexl[n] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 4.2};
    Double_t rojasexh[n] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 21.8};
    Double_t rojasey[n] = {0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.001};

auto rojas = new TGraphMultiErrors("rojas", "rojas", n, rojasx, rojasy, rojasexl, rojasexh, rojasey, rojasey);
    rojas->SetMarkerColor(2);
    rojas->SetMarkerStyle(25);
    rojas->SetLineColor(2);
    rojas->SetMarkerSize(0.5);
    rojas->Draw("same P");

auto legend = new TLegend(.145,.18,.49,.38,"");
    legend->AddEntry(Ldots,"CMS data; |#it{y}| < 2.4","EP");
    legend->AddEntry(linea,"Fit to the CMS data","L");
    legend->AddEntry(rojas,"\\text{LHCb data; } \\textit 2<y<4.5","EP");
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetMargin(0.1);
    legend->Draw();

auto legend2 = new TLegend(0.55,.7,.9,.875,"");
    legend2->AddEntry(rojas,"#bf{CMS}","");
    legend2->AddEntry(rojas,"L = 61.1fb^{-1}","");
    legend2->AddEntry(rojas,"#sqrt{s} = 13 TeV","");
    legend2->SetBorderSize(0);
    legend2->SetFillStyle(0);
    legend2->Draw();

auto legend3 = new TLegend(.45,.25,.9,.45,"");
    legend3->AddEntry(linea,"Fit: A*exp( b(x-c) )+d","");
    legend3->AddEntry(linea,TString::Format("A = %.4f #pm %.4f",params[0],errs[0]),"");
    legend3->AddEntry(linea,TString::Format("b = %.4f #pm %.4f",params[1],errs[1]),"");
    legend3->AddEntry(linea,TString::Format("c = %.4f #pm %.4f",params[2],errs[2]),"");
    legend3->AddEntry(linea,TString::Format("d = %.4f #pm %.4f",params[3],errs[3]),"");

    legend3->SetBorderSize(0);
    legend3->SetFillStyle(0);
    legend3->Draw();

c->cd();

pad2->Draw();
pad2->cd();
pad2->SetFillStyle(4000);

const Int_t n2=7;
    Double_t eystat2[n2]={0.0006, 0.0006, 0.0006, 0.0007, 0.0008, 0.0011, 0.0011};
    Double_t ex2[n2]={0.125, 0.125, 0.125, 0.125, 0.150, 0.150, 0.400};
    Double_t x2[n2]={0.125, 0.375, 0.625, 0.875, 1.150, 1.450, 2.000};
    Double_t y2[n2]={0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
    Double_t eysys2[n2]={0.0019, 0.0022, 0.0020, 0.0044, 0.0048, 0.0046, 0.0048};

auto Rdots = new TGraphMultiErrors("Rdots", "", 7, x2, y2, ex2, ex2, eystat2, eystat2);
    Rdots->AddYError(7, eysys2, eysys2);
    Rdots->SetMarkerStyle(20);
    Rdots->GetAttFill(1)->SetFillStyle(0);
    Rdots->SetMarkerSize(1);
    Rdots->SetMinimum(0.07);
    Rdots->SetMaximum(0.14);
    Rdots->GetXaxis()->SetLimits(-0.1, 2.5);
    Rdots->GetYaxis()->SetLabelOffset(999);
    Rdots->GetXaxis()->SetNdivisions(5, 5, 0);
    Rdots->GetYaxis()->SetNdivisions(4, 5, 0);
    Rdots->GetXaxis()->SetLabelSize(0.05);
    Rdots->Draw("APS; 5 s=0.5");
    Rdots->GetXaxis()->SetTitle("|#it{y}|");
    Rdots->GetXaxis()->SetTitleSize(0.055);
    Rdots->GetXaxis()->SetTitleOffset(0.7);
    Rdots->GetXaxis()->CenterTitle();

auto legend4 = new TLegend(.1,.275,.9,.35,"");
    legend4->AddEntry(rojas,"12 < #it{p_{T}} < 70 GeV","");
    legend4->SetBorderSize(0);
    legend4->SetFillStyle(0);
    legend4->Draw();

}