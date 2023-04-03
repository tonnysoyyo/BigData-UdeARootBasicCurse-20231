#include <TCanvas.h>
#include <TF1.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLatex.h>


void Graf(){

    auto myc1=new TCanvas("myc1","seguimiento_1");
    /////////////////////////////////////////////////////////////
    auto *graph = new TGraphErrors("macro2_input_suyo.txt");
    graph->SetMarkerStyle(kOpenCircle);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);
    graph->SetLineWidth(2);


    auto *graph1 = new TGraphErrors("macro2_input_expected.txt");
    graph1-> SetFillColor(5);

    auto *multi = new TMultiGraph();
    multi -> Add(graph1, "A3");
	multi -> Add(graph, "APE");

    multi->SetTitle("Measurement XYZ and Expectation;length [cm];Arb.Units");
    multi->GetXaxis()->SetRangeUser(0, 12);
    multi->GetYaxis()->SetRangeUser(0, 65);
    multi->GetXaxis()->SetNdivisions(15, 4, 0);
    multi->GetYaxis()->SetNdivisions(10, 5, 0);
    multi -> Draw("APE");
    //////////////////////////////////////////////////////////////
    auto *f = new TF1("Linear law","[0]+x*[1]",0,11);
    f->SetParameters(-3,5);
    f->SetParNames("m","b");
    f->SetLineColor(kRed);
    f->SetLineStyle(2);
    graph->Fit(f);
    /////////////////////////////////////////////////
    auto *legend = new TLegend(.1,.7,.3,.9);
    legend->AddEntry(graph,"Valores experimentales","PE");
    legend->AddEntry(f,"Ajuste  experimental y(x)=mx+b","L");
    legend->AddEntry(graph1, "Valores teoricos", "LF" );
    legend->Draw();
    /////////////////////////////////////////////////
    auto *text1 = new TLatex(5,6," b=5.18756 ;   #Delta b= 0.53072");
    text1->Draw();
    auto *text = new TLatex(5,12," m=-1.01604  ;   #Delta m=3.33409");
    text->Draw();
    //////////////////////////////////////////////////////////////
    myc1->SetGrid();
    myc1->Print("Graf.svg");

}
