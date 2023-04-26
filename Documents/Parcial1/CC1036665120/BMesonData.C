#include <fstream>
#include <iostream>

TGraphMultiErrors* process_data_CMS(const std::string& fileName, int n) {

    // -------------------------------------------
    // PRE-PROCESS DATA
    // -------------------------------------------

    // Open the input file
    std::ifstream infile(fileName);

    // Create arrays to store the data
    const int nPoints = n;

    double x[nPoints], y[nPoints], exl[nPoints], exh[nPoints],
    ey_stat[nPoints], ey_sys[nPoints];

    // Read the data from the input file and fill the arrays
    int i = 0;
    double x1, x2, yy, stat, sys;
    while (infile >> x1 >> x2 >> yy >> stat >> sys) {
        x[i] = (x1 + x2) / 2;
        exl[i] = (x2 - x1) / 2;
        exh[i] = (x2 - x1) / 2;
        y[i] = yy;
        ey_stat[i] = yy * (stat / 100.0);
        ey_sys[i] = yy * (sys / 100.0);
        i++;
    }

    // Close the input file
    infile.close();

    // -------------------------------------------
    // GRAPH DATA
    // -------------------------------------------

    // Create a TGraphErrors object from the arrays
    auto graph_cms_pt = new TGraphMultiErrors("graph_cms_pt", "", nPoints, x, y, exl, exh, ey_stat, ey_stat);
    graph_cms_pt->AddYError(nPoints, ey_sys, ey_sys);
    
    // Set the graph title and axis labels
    graph_cms_pt->SetMarkerStyle(20);
    graph_cms_pt->GetAttFill(1)->SetFillStyle(0);

    return graph_cms_pt;
}


TGraphMultiErrors* process_data_LHC(const std::string& fileName, int n) {

    // -------------------------------------------
    // PRE-PROCESS DATA
    // -------------------------------------------

    // Open the input file
    std::ifstream infile(fileName);

    // Create arrays to store the data
    const int nPoints = n;

    double x[nPoints], y[nPoints], exl[nPoints], exh[nPoints], ey_stat[nPoints];

    // Read the data from the input file and fill the arrays
    int i = 0;
    double x1, x2, yy, stat;
    while (infile >> x1 >> x2 >> yy >> stat) {
        x[i] = (x1 + x2) / 2;
        exl[i] = (x2 - x1) / 2;
        exh[i] = (x2 - x1) / 2;
        y[i] = yy;
        ey_stat[i] = stat;
        i++;
    }

    // Close the input file
    infile.close();

    // -------------------------------------------
    // GRAPH DATA
    // -------------------------------------------

    // Create a TGraphErrors object from the arrays
    auto graph_lch_pt = new TGraphMultiErrors("graph_lch_pt", "", nPoints, x, y, exl, exh, ey_stat, ey_stat);

    // Set the graph title and axis labels
    graph_lch_pt->SetMarkerStyle(24);
    graph_lch_pt->SetMarkerColor(kRed);
    graph_lch_pt->SetMarkerSize(0.5);
    graph_lch_pt->SetLineColor(kRed);
    graph_lch_pt->GetAttLine(0)->SetLineColor(kRed);
    

    return graph_lch_pt;
}



void BMesonData(){

    auto c = new TCanvas("c", "", 800,600);
    c->GetFrame()->SetBorderSize(12);

    TGraphMultiErrors* pt_result_cms = process_data_CMS("CMS_PT.txt", 12);
    TGraphMultiErrors* y_result_cms = process_data_CMS("CMS_y.txt", 7);
    TGraphMultiErrors* pt_result_lhc = process_data_LHC("LHCb_PT.txt", 12);


    // -------------------------------------------
    // FITTING
    // -------------------------------------------

    // Fit: from 12 to 70
    auto fit = new TF1("fitting", "[0] + [1] * TMath::Exp(-(x - [2])*[3])", 12, 70);
    fit->SetRange(13., 70);
    fit->SetParameters(0.11, 1, 12.5, 1);
    fit->SetLineColor(kBlue);
    

    // call TH1::Fit with the name of the TF1 object
    auto cms_fit = pt_result_cms->Fit("fitting", "S", "",12, 70);

    // Get parameters of the fitting
    Double_t p1 = fit->GetParameter(0);
    Double_t p2 = fit->GetParameter(1);
    Double_t p3 = fit->GetParameter(2);
    Double_t p4 = fit->GetParameter(3);

    Double_t e1 = fit->GetParError(0);
    Double_t e2 = fit->GetParError(1);
    Double_t e3 = fit->GetParError(2);
    Double_t e4 = fit->GetParError(3);

    

    // -------------------------------------------
    // LEGENDS
    // -------------------------------------------


    // TLegend: P: draw polymarker
    auto legend_1 = new TLegend(.1, .2, .5, .4); 
    legend_1->AddEntry(pt_result_cms, "CMS data; |y| < 2.4", "PE"); 
    legend_1->AddEntry(pt_result_lhc, "LHCb data; 2 < y < 4.5", "PE"); 
    legend_1->SetBorderSize(0);
    legend_1->SetFillStyle(0);
    legend_1->SetTextSize(0.05);
    legend_1->AddEntry(fit, "Fit to the CMS data", "L");


    auto legend_2 = new TLegend(.6, .8, .99, .99); 
    legend_2->AddEntry("", Form("#bf{CMS}"), ""); 
    legend_2->AddEntry("", Form("L = 61.6 fb^{-1}"), ""); 
    legend_2->AddEntry("", Form("#sqrt{s} = 13 TeV"), ""); 
    legend_2->SetBorderSize(0);
    legend_2->SetFillStyle(0);

    // Fit: params in the legend 
    auto legend_3 = new  TLegend(.6, .2, .9, .4); 
    legend_3->AddEntry("", Form("y = a + b*e^{-(x-c)*d}"), ""); 
    legend_3->AddEntry("",Form("a = %1.2f #pm %1.2f ", p1, e1),""); 
    legend_3->AddEntry("",Form("b = %1.2f #pm %1.2f ", p2, e2),""); 
    legend_3->AddEntry("",Form("c = %1.2f #pm %1.2f ", p3, e3),""); 
    legend_3->AddEntry("",Form("d = %1.2f #pm %1.2f ", p4, e4),""); 
    legend_3->SetBorderSize(0);
    legend_3->SetFillStyle(0);


    auto legend_4 = new TLatex();
    legend_4->SetTextSize(0.08);
    legend_4->SetTextFont(42);
    
    


    // -------------------------------------------
    // DRAW
    // -------------------------------------------

    auto mg = new TMultiGraph("mg","");

    // Axis' limits setting PT
    mg->GetXaxis()->SetLimits(0.0, 75); // X
    mg->SetMinimum(0.07); //Y 
    mg->SetMaximum(0.139); // Y

    mg->GetYaxis()->SetTitle("R_{s} "); 
    mg->GetXaxis()->CenterTitle(true);
    mg->GetXaxis()->SetTitle("P_{T} (GeV) ");

    // Set the number of  divisions 
    mg->GetXaxis()->SetNdivisions(404);
    mg->GetYaxis()->SetNdivisions(404);
    mg->GetYaxis()->SetTitleOffset(0.7); //  title offset

       
    // Draw: option "3" shows the errors as a band, P point, E errors
    mg->Add( pt_result_cms, "APES; 5 s=0.5" );
    mg->Add( pt_result_lhc , "APE" );

    // -------------------------------------------

    // Axis' limits setting Y
    y_result_cms->GetXaxis()->SetLimits(-0.2, 2.5); // X
    y_result_cms->SetMinimum(0.07); //Y 
    y_result_cms->SetMaximum(0.139); // Y

    y_result_cms->GetXaxis()->SetTitle("|y|"); 
    y_result_cms->GetXaxis()->CenterTitle(true);

    // Set the number of  divisions 
    y_result_cms->GetYaxis()->SetLabelOffset(999);
    y_result_cms->GetXaxis()->SetNdivisions(504);
    y_result_cms->GetYaxis()->SetNdivisions(504);
    y_result_cms->GetXaxis()->SetLabelSize(0.06);

    
        
    // -------------------------------------------
    // PADS
    // -------------------------------------------


    c->Divide(2,1,0,1);
    c->cd(1);
    c->GetPad(1)->SetRightMargin(.02);
    c->GetPad(1)->SetPad(0.01,0.01,0.65,0.9);
    mg->Draw("APES"); 
    legend_1->Draw();
    legend_2->Draw();
    legend_3->Draw();
    
    c->cd(2);
    c->GetPad(2)->SetPad(0.67,0.01,0.99,0.9);
    y_result_cms->GetYaxis()->SetRangeUser(0,0.15);
    c->GetPad(2)->SetRightMargin(.01);
    y_result_cms->Draw("APES; 5 s=0.5");
    legend_4->DrawLatex(0.4, 0.05, "12 < p_{T} < 70 GeV");

    c->Print("CMS_LHCb.png");




}