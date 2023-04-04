#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TMultiGraph.h"
#include "TLegend.h"

void Graph() {
    // Lienzo
    TCanvas *c1  = new TCanvas("c1", "Seguimiento 1");
    c1->SetGrid();
    
    // Datos medidos
    TGraphErrors *measured = new TGraphErrors("macro2_input_suyo.txt");
    measured->SetMarkerStyle(kCircle);

    // Datos esperados
    TGraphErrors *expected = new TGraphErrors("macro2_input_expected.txt");
    expected->SetFillColor(5);

    // Ajuste
    TF1 *tf1 = new TF1("Linear law", "[0]*x+[1]");
    tf1->SetParameters(1, 0);
    tf1->SetParNames("m", "b");
    tf1->SetLineColor(kRed);
    tf1->SetLineStyle(2);
    measured->Fit(tf1);

    // Combinar en multigraph
    TMultiGraph *multigraph = new TMultiGraph();
    multigraph->Add(expected, "A3");
    multigraph->Add(measured, "APE");
    multigraph->SetTitle("Measurement XYZ and Expectation;length [cm];Arb.Units");
    multigraph->GetXaxis()->SetRangeUser(0, 13);
    multigraph->GetYaxis()->SetRangeUser(0, 75);
    multigraph->Draw("APE");

    // Añadir leyenda
    TLegend *legend = new TLegend(.1, .7, .3, .9, "Lab. Lesson 2");
    legend->AddEntry(expected, "Expected Points");
    legend->AddEntry(measured, "Measured Points");
    legend->AddEntry(tf1, "Linear fit y=5.2*x-1.0");
    legend->Draw();

    // Crear archivo
    c1->Print("Graph.png");
}