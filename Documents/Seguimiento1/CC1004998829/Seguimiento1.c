{//Deffino el canvas y los graficos del expected y el medido
auto c1 = new TCanvas("c1","Graph Draw Options",1000,100,600,400);
auto gr1 = new TGraphErrors("macro2_input_expected.txt","%lg %lg %lg");
auto gr2 = new TGraphErrors("macro2_input_suyo.txt","%lg, %lg %lg");
gr1->SetFillColor(29);//se asigna color al expected
gr1->Draw("A3");
gr2->SetMarkerStyle(kOpenCircle);
gr2->SetMarkerColor(kBlue);
gr2->Draw("P SAME");
auto f = new TF1("macro2_input_suyo.txt","pol1",0.9,10.1);//Se hace el fit
f->SetLineColor(kMagenta-6);
f->SetLineStyle(1);
gr2->Fit(f);
f->Draw("Same");   
c1->SetGrid();
gr1->SetTitle("Measurement XYZ and Expectation");//Se añaden titulos
gr1->GetXaxis()->SetTitle("length [cm]");
gr1->GetYaxis()->SetTitle("Arb.Units");
gr1->GetXaxis()->SetNdivisions(20, 1, 0);
gr1->GetYaxis()->SetNdivisions(10, 9, 0);
gr1->GetYaxis()->SetRangeUser(-2,75);//Se ajustan los limites para mejor visualizacion
gr1->GetXaxis()->SetRangeUser(0,14);
auto legend = new TLegend(.1,.69,.65,.9);//Se añade la legenda
legend->SetHeader("Lab. lesson #2","C");
legend->SetBorderSize(4);
legend->AddEntry(gr1,"Rango de valores esperados","F");
legend->AddEntry(gr2,"Valores medidos","kOpenCircle");
legend->AddEntry(f,TString::Format("Fit con pendiente: %g y punto de corte: %g",f->GetParameter(1),f->GetParameter(0)));//En la legenda se muestra el fit
legend->Draw();
}