#include "classreduce.C"

#include <TROOT.h>
#include "TMath.h"
#include <iostream>
#include <fstream>

#include "RooFit.h"
#include "RooFitResult.h"
#include "RooGlobalFunc.h"
#include "RooArgusBG.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooExponential.h"
#include "RooGenericPdf.h"
#include "RooFFTConvPdf.h"
#include "RooPolynomial.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"

#include "TPaveText.h"
#include "TLegend.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGaxis.h"
#include "TAxis.h"
#include "TLatex.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooNumIntConfig.h"

//#include "../../analisis/tdrstyle.C"

using namespace RooFit;
using namespace std;


void save_resultTfit(ofstream& salida, RooRealVar Ns, RooRealVar Nb, RooRealVar c, RooRealVar fs, RooRealVar mean,  RooRealVar width, RooRealVar width2)
{
  salida <<  Ns.getVal() << " " << Ns.getError() << " " << Nb.getVal() << " " << Nb.getError() <<" " <<  c.getVal() << " " << c.getError() << " "  
	 << fs.getVal() << " " << fs.getError() << " " << mean.getVal() << " " << mean.getError() << " "
	 <<  width.getVal() << " " << width.getError() << " " <<  width2.getVal() << " " << width2.getError()
    ;
  cout << " el archivo se escribio bien" << endl; 
  return;
}


void save_result(ofstream& salida, RooRealVar Ns, RooRealVar Nb)
{
  salida <<  Ns.getVal() << " " << Ns.getError() << " " << Nb.getVal() << " " << Nb.getError();
  cout << " el archivo se escribio bien" << endl; 
  return;
}

TCanvas* CreateCanvasNom(TString cname, RooFitResult* result, RooDataSet data, RooRealVar M, Double_t supM, Double_t infM,  RooAddPdf MassModel, RooAddPdf sumgau, RooExponential bkg1, RooRealVar Ns, RooRealVar Nb, RooRealVar width, RooRealVar width2, RooRealVar fs, RooRealVar mean, Double_t ptl, Double_t pth) 
{

 //Double_t nbin = ((supM-infM)/0.010) + 1;
 Double_t nbin = ((supM-infM)/0.010);

 int H = 600;
 int W = 800;
 TCanvas *c1 = new TCanvas("c1","",50,50,W,H);
 c1->cd();
 c1->SetLeftMargin(0.13);
 c1->SetRightMargin(0.02);
 c1->SetTopMargin(0.09);
 c1->SetBottomMargin(0.13);
 
 gPad->SetLogy(); 
 
 RooPlot* Mframe = M.frame(infM,supM,nbin);
 data.plotOn(Mframe,DataError(RooAbsData::SumW2),MarkerSize(1.0),XErrorSize(0));
 //MassModel.plotOn(Mframe);
 MassModel.plotOn(Mframe,DrawOption("F"),FillColor(0),LineWidth(2),Name("fittotal"));
 MassModel.plotOn(Mframe,Components(sumgau),LineColor(kRed),LineWidth(2),Name("Signal")); 
 MassModel.plotOn(Mframe,Components(bkg1),LineColor(kGreen),LineWidth(2),Name("bkg")); 
 //MassModel.plotOn(Mframe,DrawOption("F"),FillColor(kBlue-9),LineColor(1),LineWidth(1),Name("fittotal"));
 //MassModel.plotOn(Mframe,Components(sumgau),DrawOption("F"),FillColor(kBlue-9),LineColor(kBlue-9),LineWidth(2),Name("Signal")); 
 //MassModel.plotOn(Mframe,Components(bkg1),DrawOption("F"),FillColor(kCyan),LineColor(kCyan),LineWidth(2),Name("bkg"));
 data.plotOn(Mframe,DataError(RooAbsData::SumW2),MarkerSize(1.0),XErrorSize(0),Name("Data"));
 MassModel.plotOn(Mframe);
 
 Mframe->SetYTitle("Events / 10 MeV");    
 Mframe->SetLabelSize(0.04,"XY");
 Mframe->SetTitleSize(0.05,"XY");
 Mframe->GetYaxis()->CenterTitle();   
 Mframe->GetXaxis()->CenterTitle();
 Mframe->GetYaxis()->SetNdivisions(505,1);
 Mframe->GetXaxis()->SetNdivisions(505,1);   
 Mframe->GetXaxis()->SetDecimals(1); 
 Mframe->SetTitleOffset(0.9,"X");
 Mframe->SetTitleOffset(1.1,"Y");
 Mframe->SetTitleSize(0.06,"XY");
 Mframe->SetMinimum(2.0);
 Mframe->SetMaximum(800000.0);    
 Mframe->Draw();
 
 //TLegend *leg = new TLegend(0.15,0.68,0.35,0.88);
 TLegend *leg = new TLegend(0.18,0.68,0.38,0.88); 
 leg->SetTextSize(0.035);
 leg->SetFillColor(0);
 leg->SetBorderSize(0);
 leg->SetFillStyle(0);
 leg->AddEntry(Mframe->findObject("Data")," Data","ep"); 
 leg->AddEntry(Mframe->findObject("fittotal")," Fit result","l");
 leg->AddEntry(Mframe->findObject("Signal")," Signal","l");
 leg->AddEntry(Mframe->findObject("bkg"),"Comb. backg.","l");
 //leg->AddEntry(Mframe->findObject("Signal")," Signal","f");
 //leg->AddEntry(Mframe->findObject("bkg"),"Comb. backg.","f");
 leg->Draw();
 
 Double_t Mpsi = mean.getVal()*1000.0;
 Double_t MpsiE = mean.getError()*1000.0;
 //Double_t G = width.getVal()*1000.0;
 //Double_t GE = width.getError()*1000.0;
 Double_t G = sqrt( fs.getVal()*width.getVal()*width.getVal() + (1-fs.getVal())*width2.getVal()*width2.getVal() )*1000.0;
 Double_t GE = (1/G)*sqrt( (fs.getVal()*fs.getVal())*(width.getVal()*width.getVal())*(width.getError()*width.getError()) + ((1-fs.getVal())*(1-fs.getVal()))*(width2.getVal()*width2.getVal())*(width2.getError()*width2.getError()) )*1000.0*1000.0;
 
 TLegend *legpar = new TLegend(0.6,0.68,0.8,0.88);
 legpar->SetTextSize(0.035);
 legpar->SetFillColor(0);
 legpar->SetBorderSize(0);
 legpar->SetFillStyle(0);
 //legpar->AddEntry("",Form("M(B_{s}^{0}) = %1.2f #pm %1.2f MeV",Mpsi,MpsiE),"");
 //legpar->AddEntry("",Form("#sigma = %1.2f #pm %1.2f MeV",G,GE),"");
 legpar->AddEntry("",Form("N_{B_{s}^{0}} = %1.0f #pm %1.0f",Ns.getVal(),Ns.getError()),"");
 legpar->AddEntry("",Form("N_{bkg} = %1.0f #pm %1.0f",Nb.getVal(),Nb.getError()),"");
 legpar->Draw();

 TLegend *legMass = new TLegend(0.64,0.57,0.83,0.65);
 legMass->SetTextFont(43); 
 legMass->SetTextSize(20);  
 legMass->SetFillColor(0); 
 legMass->SetBorderSize(0);
 legMass->SetFillStyle(0); 
 legMass->SetHeader(Form("%1.1f #leq p_{T}(B_{s}^{0}) < %1.1f GeV ",ptl,pth));
 //legMass->Draw(); 
 

 TLatex *   tex1 = new TLatex(0.92,0.926,"61.2 fb^{-1} (13 TeV)");
 tex1->SetNDC();
 tex1->SetTextAlign(31);
 tex1->SetTextFont(42);
 tex1->SetTextSize(0.05); 
 tex1->SetLineWidth(2);
 
 TLatex *tex2 = new TLatex(0.2,0.926,"CMS");
 tex2->SetNDC();
 tex2->SetTextFont(61);
 tex2->SetTextSize(0.05); 
 tex2->SetLineWidth(2);

 TLatex *tex3 = new TLatex(0.29,0.926,"Preliminary");
 tex3->SetNDC();
 tex3->SetTextFont(52);
 tex3->SetTextSize(0.05); 
 tex3->SetLineWidth(2);

 tex1->Draw();  
 tex2->Draw();
 tex3->Draw();

 c1->Modified();
 gPad->Update();
 gPad->RedrawAxis();
 //TLine l;
 //l.DrawLine(gPad->GetUxmax(), gPad->GetUymax(), gPad->GetUxmax(), gPad->GetUymin());

 TLine lr;
 Double_t lm = gPad->GetLeftMargin();
 Double_t rm = 1.-gPad->GetRightMargin();
 Double_t tm = 1.-gPad->GetTopMargin();
 Double_t bm = gPad->GetBottomMargin();
 //Double_t x = 2.0;  
 //Double_t xndc = (rm-lm)*((x-gPad->GetUxmin())/(gPad->GetUxmax()-gPad->GetUxmin()))+lm;
 //l.DrawLineNDC(xndc,bm,xndc,tm);
 lr.DrawLineNDC(rm,bm,rm,tm);
 
 return c1; 
 
}

TCanvas* CreateCanvasNomPull(TString cname, RooFitResult* result, RooDataSet data, RooRealVar M, Double_t supM, Double_t infM,  RooAddPdf MassModel, RooAddPdf sumgau, RooExponential bkg1, RooRealVar Ns, RooRealVar Nb, RooRealVar width, RooRealVar width2, RooRealVar fs, RooRealVar mean, Double_t ptl, Double_t pth) 
{
  //Double_t nbin = ((supM-infM)/0.0025);
  Double_t nbin = ((supM-infM)/0.005)+1;

  int H = 600;
  int W = 800;

  TCanvas *c1 = new TCanvas(cname,cname,50,50,W,H);
  //TCanvas *c1 = new TCanvas(cname,cname,W,H);
  //c1->Divide(1,2);
  //c1->cd(1) ;
  c1->cd() ;  
  c1->SetLeftMargin(0.005);
  c1->SetRightMargin(0.01);
  c1->SetTopMargin(0.09);
  c1->SetBottomMargin(0.1);

  TPad *pad1 = new TPad("pad1", "padi",0.01,0.411,0.9903769, 0.99 );
  pad1->SetLeftMargin(0.09);   
  pad1->SetRightMargin(0.019);
  pad1->SetTopMargin(0.09);
  pad1->SetBottomMargin(0.0);  

  TPad *pad2 = new TPad("pad2", "pad2",0.01,0.01,0.9903769,0.41);
  pad2->SetLeftMargin(0.09);
  pad2->SetRightMargin(0.019);  
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.25);
  //pad2->SetTickx(0);
  pad2->SetFillColor(0);
  pad2->SetGridx(0);
  pad2->SetGridy(0);

  pad1->Draw();
  pad2->Draw();
  pad1->cd(); 

  RooPlot* Mframe = M.frame(infM,supM,nbin);
  data.plotOn(Mframe,DataError(RooAbsData::SumW2),MarkerSize(1.0),XErrorSize(0));
  //MassModel.plotOn(Mframe);
  MassModel.plotOn(Mframe,DrawOption("F"),FillColor(0),LineWidth(2),Name("fittotal"));
  
  RooHist* hpullm2 = Mframe->pullHist() ;
  
  
  MassModel.plotOn(Mframe,Components(sumgau),LineColor(kRed),LineWidth(2),Name("Signal")); 
  MassModel.plotOn(Mframe,Components(bkg1),LineColor(kGreen),LineWidth(2),Name("bkg")); 
  //MassModel.plotOn(Mframe,DrawOption("F"),FillColor(kBlue-9),LineColor(1),LineWidth(1),Name("fittotal"));
  //MassModel.plotOn(Mframe,Components(sumgau),DrawOption("F"),FillColor(kBlue-9),LineColor(kBlue-9),LineWidth(2),Name("Signal")); 
  //MassModel.plotOn(Mframe,Components(bkg1),DrawOption("F"),FillColor(kCyan),LineColor(kCyan),LineWidth(2),Name("bkg"));
  data.plotOn(Mframe,DataError(RooAbsData::SumW2),MarkerSize(1.0),XErrorSize(0),Name("Data"));
  MassModel.plotOn(Mframe);
  
  Mframe->SetYTitle("Events / 2.5 MeV"); 
  Mframe->SetLabelSize(0.07,"XY");
  Mframe->SetTitleSize(0.08,"XY");
  Mframe->GetYaxis()->CenterTitle();   
  Mframe->GetXaxis()->CenterTitle();
  Mframe->GetYaxis()->SetNdivisions(505,1);
  Mframe->GetXaxis()->SetNdivisions(505,1);
  Mframe->GetXaxis()->SetTickLength(0.06);    
  Mframe->GetXaxis()->SetDecimals(1); 
  Mframe->SetTitleOffset(0.8,"X");
  Mframe->SetTitleOffset(0.6,"Y");
  Mframe->SetMinimum(1.0); 
  Mframe->Draw();
  
  //TLegend *leg = new TLegend(0.15,0.68,0.35,0.88);
  TLegend *leg = new TLegend(0.18,0.58,0.38,0.88); 
  leg->SetTextSize(0.06);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(Mframe->findObject("Data")," Data","ep"); 
  leg->AddEntry(Mframe->findObject("fittotal")," Fit result","l");
  leg->AddEntry(Mframe->findObject("Signal")," Signal","l");
  leg->AddEntry(Mframe->findObject("bkg"),"Comb. backg.","l");
  //leg->AddEntry(Mframe->findObject("Signal")," Signal","f");
  //leg->AddEntry(Mframe->findObject("bkg"),"Comb. backg.","f");
  leg->Draw();
  
  Double_t Mpsi = mean.getVal()*1000.0;
  Double_t MpsiE = mean.getError()*1000.0;
  //Double_t G = width.getVal()*1000.0;
  //Double_t GE = width.getError()*1000.0;
  Double_t G = sqrt( fs.getVal()*width.getVal()*width.getVal() + (1-fs.getVal())*width2.getVal()*width2.getVal() )*1000.0;
  Double_t GE = (1/G)*sqrt( (fs.getVal()*fs.getVal())*(width.getVal()*width.getVal())*(width.getError()*width.getError()) + ((1-fs.getVal())*(1-fs.getVal()))*(width2.getVal()*width2.getVal())*(width2.getError()*width2.getError()) )*1000.0*1000.0;
  
  TLegend *legpar = new TLegend(0.6,0.58,0.8,0.88);
  legpar->SetTextSize(0.06);
  legpar->SetTextFont(42);
  legpar->SetFillColor(0);
  legpar->SetBorderSize(0);
  legpar->SetFillStyle(0);
  legpar->AddEntry("",Form("M(B_{s}^{0}) = %1.2f #pm %1.2f MeV",Mpsi,MpsiE),"");
  legpar->AddEntry("",Form("#sigma = %1.2f #pm %1.2f MeV",G,GE),"");
  legpar->AddEntry("",Form("N_{B_{s}^{0}} = %1.0f #pm %1.0f",Ns.getVal(),Ns.getError()),"");
  legpar->AddEntry("",Form("N_{bkg} = %1.0f #pm %1.0f",Nb.getVal(),Nb.getError()),"");
  legpar->Draw();
  
  TLegend *legMass = new TLegend(0.64,0.47,0.83,0.55);
  legMass->SetTextFont(42); 
  legMass->SetTextSize(0.06);  
  legMass->SetFillColor(0); 
  legMass->SetBorderSize(0);
  legMass->SetFillStyle(0); 
  legMass->SetHeader(Form("%1.1f #leq p_{T}(B_{s}^{0}) < %1.1f GeV ",ptl,pth));
  legMass->Draw();
  
  pad2->cd();
  
  // Create a new frame to draw the pull distribution 
  RooPlot* framem2 = M.frame(infM,supM,nbin) ;
  framem2->addPlotable(hpullm2,"P") ;
  
  framem2->SetYTitle(" (Data-Fit)/#sigma");
  framem2->SetLabelSize(0.1,"XY");
  framem2->SetTitleSize(0.13,"X");
  framem2->SetTitleSize(0.11,"Y");  
  framem2->GetYaxis()->CenterTitle();   
  framem2->GetXaxis()->CenterTitle();
  framem2->GetYaxis()->SetNdivisions(505,1);
  framem2->GetXaxis()->SetNdivisions(505,1);
  framem2->GetXaxis()->SetTickLength(0.07);   
  framem2->SetTitleOffset(0.9,"X");
  framem2->SetTitleOffset(0.4,"Y");
  framem2->SetMaximum(4.9);
  framem2->SetMinimum(-4.9);
  
  framem2->Draw();

  TLine *line1 = new TLine(infM,0.0,supM,0.0);
  line1->SetLineColor(1);
  //line1->SetLineStyle(2);
  line1->SetLineWidth(1);
  line1->Draw();
  
  c1->cd();

  TLatex *   tex1 = new TLatex(0.88,0.95,"L = 61.6 fb^{-1} (#sqrt{s} = 13 TeV)");
  tex1->SetNDC();
  tex1->SetTextAlign(31);
  tex1->SetTextFont(42);
  tex1->SetTextSize(0.04); 
  tex1->SetLineWidth(2);
  
  TLatex *tex2 = new TLatex(0.15,0.95,"CMS");
  tex2->SetNDC();
  tex2->SetTextFont(61);
  tex2->SetTextSize(0.04); 
  tex2->SetLineWidth(2);
  
  TLatex *tex3 = new TLatex(0.22,0.95,"Preliminary");
  tex3->SetNDC();
  tex3->SetTextFont(52);
  tex3->SetTextSize(0.04); 
  tex3->SetLineWidth(2);
  

  tex1->Draw();  
  tex2->Draw();
  tex3->Draw();
  
  c1->Modified();
  gPad->Update();
  gPad->RedrawAxis();
  TLine l;
  l.DrawLine(gPad->GetUxmax(), gPad->GetUymax(), gPad->GetUxmax(), gPad->GetUymin());
  return c1; 
  
}


void BsFit_ptbins(Double_t ptl=12.0, Double_t pth=70.0)
{
gStyle->SetOptTitle(0);
gStyle->SetOptFit(0);
gStyle->SetOptStat(0);
//gStyle->SetErrorX(0);
 
//Double_t Mmin = 5.180; 
//Double_t Mmax = 5.550;
Double_t Mmin = 5.240; 
Double_t Mmax = 5.490; 
 
TChain *ch = new TChain("bstree","");
ch->Add("reducetree_Bsphi_AOD_3_best1.root/bstree");

TTree *tree = (TTree*) ch;
classreduce t(tree);
Long64_t nentries = t.fChain->GetEntries();
cout<<" Entries : "<<nentries<<endl;
  
//------------------------------
RooRealVar M("M"," M(J/#psi K^{+}K^{#font[122]{\55}}) (GeV)",Mmin,Mmax);
RooDataSet data("data","data",RooArgSet(M));

Int_t nTen = nentries/10;
Int_t k=0;
Int_t nbytes = 0, nb = 0;
for(Long64_t jentry=0; jentry<nentries;jentry++)
    {
      Long64_t ientry = t.LoadTree(jentry);
      if (ientry < 0) break;
      nb = t.fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%nTen==0) cout<<10*(jentry/nTen)<<"%-"<<flush;
      if(jentry==nentries-1) cout<<endl;

      //Mass windows cuts
      if(t.B_mass<=Mmin || t.B_mass>=Mmax) continue;	
      //if(t.J_mass<=2.9 || t.J_mass>=3.3) continue;
      if(t.J_mass<=3.0969-0.150 || t.J_mass>=3.0969+0.150) continue;
      if(t.phi_mass<=1.01946-0.010 || t.phi_mass>=1.01946+0.010) continue;// pdgM = 1.019461 

      if(t.bcpt<ptl || t.bcpt>=pth)continue; 
      //if(t.bcpt<10.0)continue;

      if(abs(t.rapidityB)>2.4)continue;
      
      //if(t.cphaB<0.999)continue;
      //if(t.pdl<0.01)continue;
      if((t.pdl/t.pdle)<5.0)continue;
      if(t.pion1pt<1.2)continue;
      if(t.pion2pt<1.2)continue;

       //trigger machint
      //if(t.trijkjk!=1)continue;
      //if(t.trijk<1)continue;
      if(t.trijk>10 || t.trijk<1)continue;
      if(abs(t.dxysig1)<2.0)continue;


      M=t.B_mass;    
      data.add(RooArgSet(M));

    }

 cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
 data.Print("v");
 //return;
 
 //RooAbsReal::defaultIntegratorConfig()->setEpsAbs(1e-10) ;
 //RooAbsReal::defaultIntegratorConfig()->setEpsRel(1e-10) ;
 
 //---- Mass model -------
 Double_t supM = Mmax;
 Double_t infM = Mmin;
 
 // ****define nominal background ****
 RooRealVar a0("a0","a0",0.23,-10.0,10.0);
 RooRealVar a1("a1","a1",-0.04,-10.0,10.0);
 RooRealVar a2("a2","a2",0.2,-10.0,10.0);
 RooRealVar a3("a3","a3",0.2,-10.0,10.0);
 //RooChebychev bkg1("bkg1","Background",M,RooArgList(a0)); 
 //RooChebychev bkg1("bkg1","Background",M,RooArgList(a0,a1));
 //RooChebychev bkg1("bkg1","Background",M,RooArgList(a0,a1,a2));

 RooRealVar c("c","c",-10.0,10.0);
 RooExponential bkg1("bkg1","Exp. Background",M,c);

 //**** define nominal signal ****
 //http://hadron.physics.fsu.edu/~skpark/document/RooFit_Users_Manual_2.07-29.pdf  (Johnson SU Distribution)
 
 //gaussians       
 //RooRealVar mean("mean"," Mass mean",3.686097);
 RooRealVar mean("mean"," Mass mean",5.366,5.320,5.400,"GeV");
 RooRealVar width("width"," Mass width",0.010,0.001,0.015,"GeV");
 RooGaussian Sig("Sig"," Signal PDF",M,mean,width);

 //RooRealVar meanB("#muB"," Mass mean B",3.63,3.75,"GeV");
 RooRealVar width2("width2"," Mass width2 ",0.020,0.015,0.05,"GeV");
 RooGaussian Sig2("Sig2"," Signal PDF B",M,mean,width2);

 //********final PDF ********
 RooRealVar Ns("Ns","Ns",0.,100000);
 RooRealVar Nb("Nb","Nb",0.,100000);   
 RooRealVar fs("fs","fs",0.8,0.,1.);

 RooAddPdf sumgau("sumgau","sumgau",RooArgList(Sig,Sig2),RooArgList(fs));

 //RooAddPdf MassModel("MassModel","MassModel",RooArgList(Sig,bkg1),RooArgList(Ns,Nb));
 RooAddPdf MassModel("MassModel","MassModel",RooArgList(sumgau,bkg1),RooArgList(Ns,Nb));

 //------------ Fit procedure -------------------
 Ns.setVal(10000.0);
 Nb.setVal(10000.0);
 
 //Ns.setConstant(kTRUE);

 RooFitResult* fitres = MassModel.fitTo(data,Extended(),Minos(kFALSE),Save(kTRUE), NumCPU(4));
 //RooFitResult* fitres = MassModel.fitTo(data,Extended(),Minos(kTRUE),Save(kTRUE), NumCPU(4)); 
 data.Print("v"); 
 fitres->Print("v");

 Double_t Gt = sqrt( fs.getVal()*width.getVal()*width.getVal() + (1-fs.getVal())*width2.getVal()*width2.getVal() )*1000.0;
 Double_t GtE = (1/Gt)*sqrt( (fs.getVal()*fs.getVal())*(width.getVal()*width.getVal())*(width.getError()*width.getError()) + ((1-fs.getVal())*(1-fs.getVal()))*(width2.getVal()*width2.getVal())*(width2.getError()*width2.getError()) )*1000.0*1000.0;

 //parameters output file
 ofstream salida_TotalFit(Form("plots_ptandeta/output_TotalFit_BsFit_nominal_%1.0f_%1.0f.txt",ptl,pth));
 salida_TotalFit.is_open();
 save_resultTfit(salida_TotalFit, Ns, Nb, c, fs, mean, width, width2);


 //parameters output file
 //ofstream *salida_nominal = save_result(Form("plots/output_BsFit_nominal_%1i_%1i.txt",era,vq),mean, Gt, GtE, Ns, Nb);
 ofstream salida_nominal(Form("plots_ptandeta/output_BsFit_nominal_%1.0f_%1.0f.txt",ptl,pth));
 salida_nominal.is_open();
 save_result(salida_nominal, Ns, Nb);// OJO esta es la funciona a la que se le pasa el archivo por referencia
 
 //made canvas
 TCanvas* canv_nominal = CreateCanvasNom("canv_nominal", fitres, data, M, supM, infM, MassModel, sumgau, bkg1, Ns, Nb, width, width2, fs, mean,ptl,pth);
 canv_nominal->Print(Form("plots_ptandeta/mass_BsFit_ptbins_%1.0f_%1.0f_NOpull.png",ptl,pth));
 canv_nominal->Print(Form("plots_ptandeta/mass_BsFit_ptbins_%1.0f_%1.0f_NOpull.pdf",ptl,pth));
 TCanvas* canv_nominalpull = CreateCanvasNomPull("canv_nominalpull", fitres, data, M, supM, infM, MassModel, sumgau, bkg1, Ns, Nb, width, width2, fs, mean,ptl,pth);  
 canv_nominalpull->Print(Form("plots_ptandeta/mass_BsFitpull_ptbins_%1.0f_%1.0f.png",ptl,pth));
 canv_nominalpull->Print(Form("plots_ptandeta/mass_BsFitpull_ptbins_%1.0f_%1.0f.pdf",ptl,pth));
 
}//End analysis
