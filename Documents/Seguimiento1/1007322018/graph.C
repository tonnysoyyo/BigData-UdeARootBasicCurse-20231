{
// Create a canvas and two TGraphErrors objects for expected and measured values
auto canvas = new TCanvas("canvas", "Graph Draw Options", 800, 600);
auto graph_expected = new TGraphErrors("macro2_input_expected.txt", "%lg %lg %lg");
auto graph_measured = new TGraphErrors("macro2_input_suyo.txt", "%lg, %lg %lg");

// Customize the appearance of the graphs
graph_expected->SetFillColor(kBlue-10);
graph_measured->SetMarkerStyle(20);
graph_measured->SetMarkerSize(1.5);
graph_measured->SetMarkerColor(kBlue);

// Create a TF1 object for linear fit and fit the measured graph
auto fit_func = new TF1("fit_func", "pol1", 1.0, 10.0);
graph_measured->Fit(fit_func);

// Customize the appearance of the fit line
fit_func->SetLineColor(kRed);
fit_func->SetLineStyle(2);

// Draw the expected and measured graphs, as well as the fit line, on the canvas
graph_expected->Draw("A3");
graph_measured->Draw("P SAME");
fit_func->Draw("SAME");

// Customize the appearance of the canvas
canvas->SetGrid();
graph_expected->SetTitle("Measurement XYZ and Expectation");
graph_expected->GetXaxis()->SetTitle("length [cm]");
graph_expected->GetYaxis()->SetTitle("Arb.Units");
graph_expected->GetYaxis()->SetRangeUser(0.1, 80);

// Create and customize the legend
auto legend = new TLegend(0.15, 0.7, 0.55, 0.9);
legend->SetHeader("Lab. lesson #2", "C");
legend->SetBorderSize(1);
legend->AddEntry(graph_expected, "Expected values", "F");
legend->AddEntry(graph_measured, "Measured values", "P");
legend->AddEntry(fit_func, TString::Format("Linear fit: y = %.2fx + %.2f", fit_func->GetParameter(1), fit_func->GetParameter(0)), "L");
legend->Draw();

// Save the canvas as a PDF file
canvas->SaveAs("measurement.pdf");
}