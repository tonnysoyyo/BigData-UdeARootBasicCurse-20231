
int Eventos() {
  Int_t Npart;
  std::vector<Int_t> Det;
  std::vector<Float_t> time; 
  std::vector<Float_t> energy;

  TFile f ("manyparticles.root", "RECREATE");
  TTree t ("tree", "My tree");
  t.Branch ("Npart", &Npart);
  t.Branch ("Det"  , &Det   );
  t.Branch ("Time" , &time  );
  t.Branch ("En"   , &energy);

  TRandom3 r; r.SetSeed ();
  for (int ievt=0; ievt<100; ievt++) {
    Npart = r.Integer(6);
    cout << "Event " << ievt << " has " << Npart << " particles.\n";
    Det.clear();
    time.clear();
    energy.clear();
    for (int ipart=0; ipart<Npart; ipart++) 
    {
      Det.push_back(r.Integer (24));
      time.push_back(r.Rndm() * 20.);
      energy.push_back(r.Rndm() * 30.);
      cout << Det [ipart]<<setw(10)<< time [ipart]<<setw(10) << energy[ipart]<< endl;
    }
    t.Fill ();
  }
  t.Write();
  return 0;
}
