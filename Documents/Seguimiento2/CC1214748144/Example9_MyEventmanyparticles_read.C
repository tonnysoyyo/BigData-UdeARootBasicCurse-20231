int Example9_MyEventmanyparticles_read() {
  vector<int> *det=nullptr;
  vector<float> *time= nullptr;
  vector<float> *energy=nullptr;
  int Npart;

  TFile f ("manyparticles.root", "READ");
  TTree *t = (TTree*) f.Get ("tree");

  t->SetBranchAddress ("Npart", &Npart );
  t->SetBranchAddress ("Det"  , &det    );
  t->SetBranchAddress ("Time" , &time   );
  t->SetBranchAddress ("En"   , &energy );

  cout << "* This tree has " 
       << t->GetEntries() << " entries.\n\n"; //entries = events. número de veces que se le dio Fill. 

  for (int ievt=0; ievt<t->GetEntries(); ievt++) 
  {
    t->GetEntry (ievt);
    cout << "* Event " << ievt 
         << " has " << Npart << " particles:\n";

    for (int ipart=0; ipart<Npart; ipart++) 
    {
      cout << setw(10) << det->at(ipart)
           << setw(12) << time->at(ipart)
           << setw(12) << energy->at(ipart) << endl;

    }
  }
  return 0;
}