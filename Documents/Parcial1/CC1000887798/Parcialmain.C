#include <iostream>
#include <fstream>
#include <vector>

void Parcialmain() {

    //Se crea el canva y los dos pads
    auto *c1 = new TCanvas("c1", "c1",1000,600);
    auto *pad1 = new TPad("pad1", "pad1", 0, 0.0, 0.68, 1);
    auto *pad2 = new TPad("pad2", "pad2", 0.615, 0.0, 1, 1);
    pad1->Draw();
    pad2->Draw();

    pad1->cd();
    // Lectura de datos de LHCb desde archivo
    vector<double> x, y, exi, exd , eyi; 
    ifstream file("datoslhcb.txt");
    double x_v, y_v, exi_v, exd_v ,eyi_v ;
    while (file >> x_v >> y_v >> exi_v >> exd_v >> eyi_v ) {
        x.push_back(x_v);
        y.push_back(y_v);
        exi.push_back(exi_v);
        exd.push_back(exd_v);
        eyi.push_back(eyi_v);
    }
    int n_points = x.size();
    
    
    Double_t* x_a = x.data();
    Double_t* y_a = y.data();
    Double_t* exi_a = exi.data();
    Double_t* exd_a = exd.data();
    Double_t* eyi_a = eyi.data();


    // Creación del TGraphMultiErrors de LHCb
    auto *lhcb = new TGraphMultiErrors("lhcb","lhcb",n_points, x_a , y_a, exi_a , exd_a , eyi_a, eyi_a);
    
    
    lhcb->SetMarkerStyle(25);
    lhcb->SetMarkerSize(0.6);
    lhcb->SetMarkerColor(2);
    lhcb->SetLineColor(2);
    lhcb->SetLineWidth(1);
    lhcb->GetAttLine(0)->SetLineColor(kRed);
    

    // Lectura de datos de CMS desde archivo
    vector<double> xc, yc, exc, eyc , eyc_s; 
    ifstream file1("datoscms.txt");
    double x_vc, y_vc, ex_vc, eyd_vc ,eycs_v ;
    while (file1>> x_vc >> y_vc >> ex_vc >> eyd_vc >> eycs_v ) {
        xc.push_back(x_vc);
        yc.push_back(y_vc);
        exc.push_back(ex_vc);
        eyc.push_back(eyd_vc);
        eyc_s.push_back(eycs_v);
    }
    int n_c = xc.size();

    
    Double_t* x_ac = xc.data();
    Double_t* y_ac = yc.data();
    Double_t* exi_ac = exc.data();
    Double_t* ey_ac = eyc.data();
    Double_t* eys_ac = eyc_s.data();

    
    // Creación del TGraphMultiErrors de CMS
    auto *cms = new TGraphMultiErrors("cms","cms",n_c, x_ac , y_ac, exi_ac, exi_ac , ey_ac, ey_ac);
    
    cms->AddYError(n_c, eys_ac, eys_ac);   //cajas
    cms->SetMarkerStyle(20);
    cms->SetMarkerSize(.9);
    cms->SetLineWidth(1);
    //cms->GetAttLine(0)->SetLineColor(kRed);   // pinta el error en y
    //cms->GetAttLine(1)->SetLineColor(kBlue);     // pinta la caja
    cms->GetAttFill(1)->SetFillStyle(0);  // dibuja error en y
    //cms->SetMarkerColor(4);
    cms->GetXaxis()->SetTitleSize(0.05);
    cms->GetYaxis()->SetTitleSize(0.05);
    cms->GetXaxis()->SetLabelSize(0.05);


    //fit
    auto *fit1 = new TF1("fit1" , "[0]* exp(-[1]*(x-[2]))+ [3]" ,8, 75);
    fit1->SetParameter(0, 1);
    fit1->SetParameter(1,0.423 );
    fit1->SetParameter(2,8 );
    fit1->SetParameter(3, 0.11);
    fit1->SetLineColor(4);

    auto r = cms->Fit("fit1","S","",8,75);
    

    Double_t par0   = r->Parameter(0);          
    Double_t err0   = r->ParError(0);           
    Double_t par1   = r->Parameter(1);          
    Double_t err1   = r->ParError(1); 
    Double_t par2   = r->Parameter(2);
    Double_t err2   = r->ParError(2);
    Double_t par3   = r->Parameter(3);
    Double_t err3   = r->ParError(3);

    //MultiGraph
    auto *mg = new TMultiGraph();
    mg->Add(cms);
    mg->Add(lhcb);
    mg->GetXaxis()->SetLimits(0, 75);
    mg->GetYaxis()->SetRangeUser(0.075, 0.1399);
    mg->GetXaxis()->SetNdivisions(6, 4,0);
    mg->GetYaxis()->SetNdivisions(4, 4,0);
    mg->GetXaxis()->SetTitle("\\mathit {p_{T} (GeV)}" );
    mg->GetYaxis()->SetTitle("\\mathit R_{s}");
    mg->GetXaxis()->SetTitleOffset(1);
    mg->GetYaxis()->SetTitleOffset(1); 
    mg->GetXaxis()->CenterTitle();
    mg->Draw("APES ; ; 5 s=0.5");

    //Legends
    auto legend = new TLegend(.15,.17,.35,.3 );
    legend->AddEntry(cms,"CMS data; |y| < 2.4" ,"PE" );
    legend->AddEntry(fit1,"Fit to CMS data" ,"L" );
    legend->AddEntry(lhcb,"LHCB data; 2 < |y| < 4.5" ,"PE" );
    legend->SetTextSize(.04);
    legend->SetBorderSize(0);
    legend->Draw();

    auto legend2 = new TLegend(.60,.72,0.88,0.88 ," \n \n \\mathbf{CMS}");
    legend2->AddEntry("0" ,"L = 61.6 fb^{-1}","");
    legend2->AddEntry("0" ,"\\sqrt{s} = 13 TeV" ,"");
    legend2->SetTextSize(.04);
    legend2->SetBorderSize(0);
    legend2->Draw();

    auto legend4 = new TLegend(.55 , .22,.85,.42);
    legend4->AddEntry("0" ,"Fit: A * exp ( b(x-c)+d)" , "");
    legend4->AddEntry("",Form("a = %1.4f #pm %1.4f ",par0,err0),"");
    legend4->AddEntry("",Form("b = %1.4f #pm %1.4f ",par1,err1),"");
    legend4->AddEntry("",Form("c = %1.4f #pm %1.4f ",par2,err2),"");
    legend4->AddEntry("",Form("d = %1.4f #pm %1.4f ",par3,err3),"");
    legend4->SetTextSize(.03);
    legend4->SetBorderSize(0);
    legend4->Draw();
   

    pad2->cd();
    // Lectura de datos de CMS_y desde archivo

    vector<double> xc1, yc1, exc1, eyc1 , eyc_s1; 
    ifstream file1y("datoscms_y.txt");
    double x_vc1, y_vc1, ex_vc1, eyd_vc1 ,eycs_v1 ;
    while (file1y>> x_vc1 >> y_vc1 >> ex_vc1 >> eyd_vc1 >> eycs_v1 ) {
        xc1.push_back(x_vc1);
        yc1.push_back(y_vc1);
        exc1.push_back(ex_vc1);
        eyc1.push_back(eyd_vc1);
        eyc_s1.push_back(eycs_v1);
    }
    
    int n_c1 = xc1.size();

    
    Double_t* x_ac1 = xc1.data();
    Double_t* y_ac1 = yc1.data();
    Double_t* exi_ac1 = exc1.data();
    Double_t* ey_ac1 = eyc1.data();
    Double_t* eys_ac1 = eyc_s1.data();

    
    // Creación del TGraphMultiErrors de CMS
    auto *cms_y = new TGraphMultiErrors("cms_y","",n_c1, x_ac1 , y_ac1, exi_ac1, exi_ac1 , ey_ac1, ey_ac1);

    cms_y->AddYError(n_c1, eys_ac1, eys_ac1);   //caja

    cms_y->SetMarkerStyle(20);
    cms_y->SetMarkerSize(.9);
    cms_y->SetLineWidth(1);
    cms_y->GetAttFill(1)->SetFillStyle(0);  // dibuja error en y


    cms_y->GetYaxis()->SetLabelSize(0);
    // cms_y->GetXaxis()->SeTitleSize(0.1);
    cms_y->GetXaxis()->SetTitle("|\\mathit{y}|");
    cms_y->GetXaxis()->SetLimits(0, 2.5);
    cms_y->GetYaxis()->SetRangeUser(0.075, 0.14);
    cms_y->GetXaxis()->SetTitleSize(0.05);
    cms_y->GetXaxis()->SetLabelSize(0.05);
    
    cms_y->GetXaxis()->SetNdivisions(4, 4,0);
    cms_y->GetYaxis()->SetNdivisions(4, 4,0);
    cms_y->GetXaxis()->SetTitleOffset(0.6);
    cms_y->GetXaxis()->CenterTitle();
    
    cms_y->Draw("APES ; ; 5 s=0.5");

    auto legend3 = new TLegend(.22,.28,.65,.32 );
    legend3->AddEntry("" , "12 < \\mathit{p_{T}} < 70 GeV", "");
    legend3->SetTextSize(.05);
    legend3->SetBorderSize(0);
    legend3->Draw();
    
    c1->Update();   
    c1->Print("plot.png");
}

