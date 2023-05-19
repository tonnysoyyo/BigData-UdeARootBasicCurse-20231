int Example9_MyEventmanyparticles_read() {
  Int_t Npart;
  std::vector<int>* det = nullptr;
  std::vector<float>* energy = nullptr;
  std::vector<float>* time = nullptr;

  TFile f ("manyparticles.root", "READ");
  TTree *t = (TTree*) f.Get ("tree");

  t->SetBranchAddress ("Npart", &Npart );
  t->SetBranchAddress ("Det"  , &det);
  t->SetBranchAddress ("Time" , &time );
  t->SetBranchAddress ("En"   , &energy);

  cout << "* This tree has " 
       << t->GetEntries() << " entries.\n\n";
  t->Print();
  for (int ievt=0; ievt<t->GetEntries(); ievt++) 
  {
    t->GetEntry (ievt);
    cout << "* Event " << ievt 
         << " has " << Npart << " particles:\n";

    for (int ipart=0; ipart<Npart; ipart++) 
    {
      cout << setw(10) << (*det)[ipart]
           << setw(12) << (*time)[ipart]
           << setw(12) << (*energy)[ipart] << endl;
      
    }
  }
  t->ResetBranchAddresses();
  return 0;
}
