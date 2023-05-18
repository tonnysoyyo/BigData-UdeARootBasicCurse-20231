int read_Eventos() {
  Int_t Npart;
  std::vector<Int_t> *det = nullptr;
  std::vector<Float_t> *time = 0; 
  std::vector<Float_t> *energy = 0;


  TFile f ("manyparticles.root", "READ");
  TTree *t = (TTree*) f.Get ("tree");
  t->SetBranchAddress ("Npart", &Npart );
  t->SetBranchAddress ("Det"  , &det    );
  t->SetBranchAddress ("Time" , &time   );
  t->SetBranchAddress ("En"   , &energy );

  cout << "This tree has "  << t->GetEntries() << " entries.\n\n";

  for (int ievt=0; ievt<t->GetEntries(); ievt++) 
  {
    t->GetEntry (ievt);
    cout << "* Event " << ievt << " has " << Npart << " particles:\n";

    for (int ipart=0; ipart<Npart; ipart++) 
    {
      cout << det->at(ipart)<<setw(10)<< time->at(ipart)<<setw(10) << energy->at(ipart)<< endl;

    }
  }
  return 0;
}
