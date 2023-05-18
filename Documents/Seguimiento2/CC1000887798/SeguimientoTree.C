int SeguimientoTree() {
  Int_t Npart;
  std::vector<Int_t> det;
  std::vector<Float_t> energy , time;

  TFile f ("manyparticles.root", "RECREATE");
  TTree t ("tree", "My tree");
  t.Branch ("Npart", &Npart);
  t.Branch ("Det"  , &det   );
  t.Branch ("Time" , &time  );
  t.Branch ("En"   , &energy);

  TRandom3 r; r.SetSeed ();
  for (int ievt=0; ievt<100; ievt++) {
    Npart = r.Integer(6);
    cout << "Event " << ievt 
         << " has " << Npart << " particles.\n";
    for (int ipart=0; ipart<Npart; ipart++) 
    {
      // det   [ipart] = r.Integer (24);
      // time  [ipart] = r.Rndm() * 20.;
      // energy[ipart] = r.Rndm() * 30.;
      
      det.push_back(r.Integer (24));
      time.push_back(r.Rndm() * 20.);
      energy.push_back(r.Rndm() * 30.);

      
      cout << setw(10) << det.at(ipart) 
           << setw(12) << time.at(ipart) 
           << setw(12) << energy.at(ipart) << endl;
    }
    t.Fill ();

    det.resize(Npart);
    time.resize(Npart);
    energy.resize(Npart);
  }
  t.Write();
  return 0;
}
