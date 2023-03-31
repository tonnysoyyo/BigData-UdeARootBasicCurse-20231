void MyGraph(){
	auto canvas = new TCanvas("canvas","canvas",400,10,800,600);
	canvas -> SetGrid();
	canvas -> SetTitle("Seguimiento 1");
	
	TMultiGraph *multi = new TMultiGraph();
	multi -> SetTitle("Measurement XYZ and Expectation;length [cm];Arb.Units");
	
	// Datos esperados:
	auto teo = new TGraphErrors("macro2_input_expected.txt");
	teo -> SetFillColor(kCyan-6);
	teo -> SetFillStyle(1001);
	
	// Datos medidos:
	auto exp = new TGraphErrors("macro2_input_suyo.txt");
	exp -> SetMarkerStyle(kOpenCircle);
	
	// Fit linear:
	auto fit = new TF1("LinearFit","[0]+x*[1]",.5,10);
	fit -> SetParameters(-1,5);
	fit -> SetLineColor(kBlue-7);
	fit -> SetLineStyle(2);
	
	exp -> Fit("LinearFit");
	
	// Añadiendo las gráficas en diferentes estilos:
	multi -> Add(teo, "A3");
	multi -> Add(exp, "APE");
	multi -> Draw("APE");
	
	multi -> GetXaxis()->SetNdivisions(5, 5, 0);

	// Leyendas:
	auto legend = new TLegend(.1,.7,.3,.9,"Lab. Lesson 2");
	legend -> AddEntry(teo,"Expected Points","LF");
	legend -> AddEntry(exp,"Measured Points","LP");
	legend -> AddEntry(fit,"Linear Fit","L");
	legend -> Draw();
	}
	
