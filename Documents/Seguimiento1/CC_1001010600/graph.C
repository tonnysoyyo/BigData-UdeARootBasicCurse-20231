void graph(){

  TCanvas* canvas = new TCanvas("canvas", "canvas", 800, 600);
  canvas->SetTitle("Firts task");

  //Multiples graphics
  TMultiGraph* multiG = new TMultiGraph();
  multiG->SetTitle("Measurement and Expectation; Length [cm]; Arb. Units");

  //Expected data
  TGraphErrors* exp = new TGraphErrors("macro2_input_expected.txt", "%lg %lg %lg");
  exp->SetFillColor(kAzure+6);
  exp->SetFillStyle(1001);
  
  //Measurement
  TGraphErrors* measure = new TGraphErrors("macro2_input_suyo.txt", "%lg %lg %lg");
  measure->SetMarkerStyle(kOpenFourTrianglesX);

  //Fit
  TF1* fit = new TF1("myFit", "[0]+x*[1]", 1, 9);
  fit->SetParameters(1,5);
  fit->SetLineStyle(9);
  fit->SetLineWidth(3);
  fit->SetLineColor(kMagenta-2);
  measure->Fit("myFit");

  Double_t a = fit->GetParameter(0);
  Double_t aErr = fit->GetParError(0);
  Double_t b = fit->GetParameter(1);
  Double_t bErr = fit->GetParError(1);
  //Draw
  multiG->Add(exp, "A3");
  multiG->Add(measure, "APE");
  multiG->Draw("a");
  
  //Legend
  TLegend* legend = new TLegend(.1,.6,.5,.9,"Lab. Lesson 2");
  legend->AddEntry(exp,"Expected Points","F");
  legend->AddEntry(measure,"Measured Points","LP");
  legend->AddEntry(fit,"Data Fit","L");
  legend->AddEntry((TObject*)0, TString::Format("Fit par. constant: %g #pm %g", a, aErr), "");
  legend->AddEntry((TObject*)0, TString::Format("Fit par. slope: %g #pm %g", b, bErr), "");
  legend->SetTextSize(0.025);
  legend->Draw();

  canvas->Print("graph.png");
}
