void GraficaParcial(){
	
	auto canvas = new TCanvas("canvas", "canvas", 400, 10, 1000, 500);
	canvas -> SetTitle("Parcial 1");
	
	// Subplots:
	TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 0.7, 1);
	TPad *pad2 = new TPad("pad2", "pad2", 0.6, 0, 1, 1);
	
	pad1 -> Draw();
	pad1 -> cd();
	
	// Datos CMS:
	const Int_t N = 12;
	Double_t CMSx[N] = {12.5, 13.5,14.5, 15.5, 17, 19, 21.5, 24.5, 27.5, 31.5, 39.5, 57.5};
	Double_t CMSy[N] = {0.1314, 0.1196, 0.1165, 0.1154, 0.1135, 0.1106, 0.1105, 0.1110, 0.1091, 0.1095, 0.1088, 0.1117};
	Double_t err_CMSx[N] = {0.5, 0.5, 0.5, 0.5, 1, 1, 1.5, 1.5, 2, 2, 5.5, 12.5};
	Double_t err_CMSy_est[N] = {0.0028, 0.0019, 0.0015, 0.0014, 0.0009, 0.0009, 0.0008, 0.0009, 0.0009, 0.0009, 0.0009, 0.0014};
	Double_t err_CMSy_sis[N] = {0.0041, 0.0032, 0.0028, 0.0030, 0.0029, 0.0031, 0.0032, 0.0029, 0.0035, 0.0025, 0.0030, 0.0029};	
	
	auto CMS = new TGraphMultiErrors("CMS", "", N, CMSx, CMSy, err_CMSx, err_CMSx, err_CMSy_est, err_CMSy_est);
	CMS -> AddYError(N, err_CMSy_sis, err_CMSy_sis);
	CMS -> GetAttFill(1) -> SetFillStyle(0);
	CMS -> GetYaxis() -> SetNdivisions(5, 5, 0);
	CMS -> SetMarkerSize(1);
	CMS -> SetMarkerStyle(20);
	CMS -> GetXaxis() -> SetNdivisions(5, 5, 0);
	CMS -> GetYaxis() -> SetTitleOffset(1.17);
	CMS -> GetXaxis() -> SetLimits(0, 75);
	CMS -> SetMinimum(0.07);
	CMS -> SetMaximum(0.13999);
	CMS -> SetTitle(";#it{p}_{T}(GeV);#it{R_{s}}");
	CMS -> GetXaxis() -> CenterTitle();
	
	CMS -> Draw("APS; 5 s=0.5");
	
	// Fit de los datos del CMS:
	auto exp = new TF1("exp", "[0]*exp(-[1]*(x-[2]))+[3]", 12, 70);
	exp -> SetParameter(0, 1);
	exp -> SetParameter(1, 1); 
	exp -> SetParameter(2, 10); 
	exp -> SetParameter(3, 0.11); 
	
	auto f = CMS -> Fit("exp","SQ","",11.9,70);
	f -> Print();
	auto fit = CMS -> GetFunction("exp");
	fit -> SetLineColor(kMagenta+1);
	fit -> SetLineWidth(3);
	Double_t *params = fit -> GetParameters();
	auto errs = fit -> GetParErrors();
	
	// Datos LHCb:
	const Int_t n=12+1;
	Double_t LHCx[n] = {1.25, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.75, 12.75, 18.2};
	Double_t LHCy[n] = {0.125, 0.127, 0.125, 0.128, 0.128, 0.127, 0.127, 0.126, 0.125, 0.125, 0.118, 0.12};
	Double_t err_LHCx1[n] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 4.2};
	Double_t err_LHCx2[n] = {0.75, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.75, 1.25, 21.8};
	Double_t err_LHCy[n] = {0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.0015, 0.001};
	
	auto LHC = new TGraphMultiErrors("LHC", "LHC", n, LHCx, LHCy, err_LHCx1, err_LHCx2, err_LHCy, err_LHCy);
	LHC -> SetMarkerColor(kCyan+1);
	LHC -> SetMarkerStyle(25);
	LHC -> SetLineColor(kCyan+1);
	LHC -> SetMarkerSize(0.5);
	LHC -> Draw("same P");
	
	// Leyendas gráfica izquierda:
	auto legendTR = new TLegend(0.60, 0.7, 0.9, 0.875, "");
	legendTR -> AddEntry(LHC, "#bf{CMS}", "");
	legendTR -> AddEntry(LHC, "L = 61.1fb^{-1}", "");
	legendTR -> AddEntry(LHC, "#sqrt{s} = 13 TeV", "");
	legendTR -> SetBorderSize(0);
	legendTR -> SetFillStyle(0);
	legendTR -> Draw();
	
	auto legendBL = new TLegend(0.145, 0.18, 0.49, 0.38, "");
	legendBL -> AddEntry(CMS, "CMS data; |#it{y}| < 2.4", "EP");
	legendBL -> AddEntry(fit, "Fit to the CMS data", "L");
	legendBL -> AddEntry(LHC, "\\text{LHCb data; } \\textit 2<y<4.5", "EP");
	legendBL -> SetBorderSize(0);
	legendBL -> SetFillStyle(0);
	legendBL -> SetMargin(0.1);
	legendBL -> Draw();

	auto legendBR = new TLegend(0.55, 0.20, 0.9, 0.40, "");
	legendBR -> AddEntry(fit, "Fit: A*e^{B(C-x)} + D","");
	legendBR -> AddEntry(fit, TString::Format("A = %.4f #pm %.4f", params[0], errs[0]), "");
	legendBR -> AddEntry(fit, TString::Format("B = %.4f #pm %.4f", params[1], errs[1]), "");
	legendBR -> AddEntry(fit, TString::Format("C = %.4f #pm %.4f", params[2], errs[2]), "");
	legendBR -> AddEntry(fit, TString::Format("D = %.4f #pm %.4f", params[3], errs[3]), "");
	legendBR -> SetBorderSize(0);
	legendBR -> SetFillStyle(0);
	legendBR -> Draw();
	
	canvas -> cd();
	
	pad2 -> Draw();
	pad2 -> cd();
	pad2 -> SetFillStyle(4000);

	// Datos figura derecha:
	const Int_t n2=7;
	Double_t x2[n2]={0.125, 0.375, 0.625, 0.875, 1.150, 1.450, 2.000};
	Double_t y2[n2]={0.1110, 0.1104, 0.1100, 0.1126, 0.1117, 0.1069, 0.1099};
	Double_t err_x2[n2]={0.125, 0.125, 0.125, 0.125, 0.150, 0.150, 0.400};
	Double_t err_y_est2[n2]={0.0006, 0.0006, 0.0006, 0.0007, 0.0008, 0.0011, 0.0011};
	Double_t err_y_sis2[n2]={0.0019, 0.0022, 0.0020, 0.0044, 0.0048, 0.0046, 0.0048};
	
	auto Dizq = new TGraphMultiErrors("Dizq", "", 7, x2, y2, err_x2, err_x2, err_y_est2, err_y_est2);
	Dizq -> AddYError(7, err_y_sis2, err_y_sis2);
	Dizq -> SetMarkerStyle(20);
	Dizq -> GetAttFill(1) -> SetFillStyle(0);
	Dizq -> SetMarkerSize(1);
	Dizq -> SetMinimum(0.07);
	Dizq -> SetMaximum(0.14);
	Dizq -> GetXaxis() -> SetLimits(-0.1, 2.5);
	Dizq -> GetYaxis() -> SetLabelOffset(999);
	Dizq -> GetXaxis() -> SetNdivisions(5, 5, 0);
	Dizq -> GetYaxis() -> SetNdivisions(4, 5, 0);
	Dizq -> GetXaxis() -> SetLabelSize(0.05);
	Dizq -> GetXaxis() -> SetTitle("|#it{y}|");
	Dizq -> GetXaxis() -> SetTitleSize(0.055);
	Dizq -> GetXaxis() -> SetTitleOffset(0.7);
	Dizq -> GetXaxis() -> CenterTitle();
	Dizq -> Draw("APS; 5 s=0.5");
	
	// Leyenda figura derecha:
	auto legendL = new TLegend(0.15, 0.30, 0.9, 0.35, "");
	legendL -> AddEntry(LHC, "12 < #it{p_{T}} < 70 GeV", "");
	legendL -> SetBorderSize(0);
	legendL -> SetFillStyle(0);
	legendL -> Draw();
	
	}
	
