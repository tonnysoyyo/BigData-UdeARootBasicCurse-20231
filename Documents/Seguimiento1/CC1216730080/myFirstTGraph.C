{
  
  auto c1 = new TCanvas();
  auto Tsuyo = new TGraphErrors("macro2_input_suyo.txt", "%lg, %lg %lg");
  auto Texpected = new TGraphErrors("macro2_input_expected.txt", "%lg %lg %lg");
  auto line = new TF1("Linear law"," [1]+ x *[0] ");
  auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 2");
  auto params = new TPaveText(.6,.1,.9,.3,"NDC");

  line->SetParameters(1., 1.);
  line->SetParNames("Slope", "Intercept");
  line->SetLineStyle(2);
  line->SetLineColor(kRed);

  Tsuyo->Fit("Linear law");

  auto f = Tsuyo->GetFunction("Linear law");
  auto fit = TVirtualFitter::GetFitter();

  params->AddText(Form("#chi^{2} / ndf = %.3f / %d", f->GetChisquare(), f->GetNDF()));
  params->AddText(Form("%s: %.3f #pm %.4f", fit->GetParName(0) , fit->GetParameter(0), fit->GetParError(0)));
  params->AddText(Form("%s: %.3f #pm %.3f", fit->GetParName(1) , fit->GetParameter(1), fit->GetParError(1)));

  c1->SetTitle("Seguimiento 1");
  c1->SetGrid();
  Texpected->SetTitle("Measurement XYZ and Expectation; length [cm]; Arb.Units");
  Texpected->SetFillColor(kYellow);
  Tsuyo->SetMarkerStyle(4);
  
  legend->AddEntry(Texpected,"Expected Points","LF");
  legend->AddEntry(Tsuyo,"Measured Points","LP");
  legend->AddEntry(line,"Linear Fit","L");

  Texpected->Draw("AE3");
  Tsuyo->Draw("PESame");
  line->Draw("LSame");
  legend->Draw("Same");
  params->Draw("Same");

  c1->SaveAs("Seguimiento1.pdf");

}
