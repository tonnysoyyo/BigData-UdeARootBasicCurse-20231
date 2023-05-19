int Example9_MyEventmanyparticles() {

  Int_t Npart;
  std::vector<int> det;
  std::vector<float> energy, time;

  TFile f ("manyparticles.root", "RECREATE");
  TTree t ("tree", "My tree");
  t.Branch ("Npart", &Npart);
  t.Branch ("Det"  , &det  );
  t.Branch ("Time" , &time );
  t.Branch ("En"   , &energy);

  TRandom3 r; r.SetSeed ();
  for (int ievt=0; ievt<100; ievt++) {
    Npart = r.Integer(6);

    cout << "Event " << ievt 
         << " has " << Npart << " particles.\n";
    for (int ipart=0; ipart<Npart; ipart++) 
    {
      det.push_back(r.Integer (24));
      time.push_back(r.Rndm() * 20.);
      energy.push_back(r.Rndm() * 30.);

      cout << setw(10) << det.back() 
           << setw(12) << time.back() 
           << setw(12) << energy.back() << endl;
    }
    t.Fill ();

    det.clear();
    time.clear();
    energy.clear();

    
  }
  t.Write();
  return 0;
}
