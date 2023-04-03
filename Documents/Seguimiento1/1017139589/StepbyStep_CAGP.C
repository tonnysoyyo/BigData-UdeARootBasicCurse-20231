void StepbyStep_CAGP(){

//Se defin canvas para poder establecer el grid
auto myc1 = new TCanvas("myc1","myc1",800,600);
myc1-> SetGrid();


//Definición gráfico 
TMultiGraph *lienzo = new TMultiGraph();


// Datos esperados
TGraphErrors * graphexp = new TGraphErrors("macro2_input_expected.txt");

// Datos experimentales obtenidos 
TGraphErrors * graph = new TGraphErrors("macro2_input_suyo.txt");

//Titulo del gráfico 
lienzo -> SetTitle("Measurement XYZ and Expectation;length [cm];Arb.Units");

//Definición de estilos gráfico experimental
graph->SetMarkerStyle(kOpenCircle);
graph->SetMarkerColor(kBlack);
graph->SetLineColor(kBlack);

//Definición de estilos gráfico esperado
graphexp->SetFillColor(kYellow);
graphexp->SetFillStyle(1001);

//Fit lineal de la función 
TF1 * f1 = new TF1 ("Linear fit","[0]+x*[1]",0,10);
// Se entregan los parametros para iniciar en -1 y 5 y poder visualizar completo
f1 -> SetParameters(-1,5); 
f1->SetLineColor(kRed);
f1->SetLineStyle(5);
f1->SetParNames("A","B");

graph-> Fit(f1);  

// Se adicionan las graficas
lienzo -> Add(graphexp, "A3");
lienzo -> Add(graph, "APE");
lienzo -> Draw("APE");
	
//lienzo -> GetXaxis()->SetNdivisions(5, 5, 0);
lienzo->GetXaxis()->SetNdivisions(5, 5, 0); 


auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 2");
legend->AddEntry(graphexp,"Expected Points","LF");
legend->AddEntry(graph,"Measured Points","LP");
legend->AddEntry(f1,"Linear fit","L");

legend->Draw("Same");
cout <<"Correlación X y Y =" <<graph -> GetCorrelationFactor()<<endl;

}