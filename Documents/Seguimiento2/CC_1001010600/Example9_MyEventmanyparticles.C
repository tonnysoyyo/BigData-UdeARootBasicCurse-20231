#include <vector>

int Example9_MyEventmanyparticles() {
  Int_t Npart;
  vector<int> det(500);
  vector<float> energy(500);
  vector<float> time(500);

  TFile f ("manyparticles.root", "RECREATE");
  TTree t ("tree", "My tree");
  t.Branch ("Npart", &Npart, "Npart/I");
  t.Branch ("Det"  , &det   , "det[Npart]/I");
  t.Branch ("Time" , &time  , "time[Npart]/F");
  t.Branch ("En"   , &energy, "energy[Npart]/F");

  TRandom3 r; r.SetSeed ();
  for (int ievt=0; ievt<100; ievt++) {
    Npart = r.Integer(6);
    cout << "Event " << ievt 
         << " has " << Npart << " particles.\n";
    for (int ipart=0; ipart<Npart; ipart++) 
    {
      det.at(ipart) = r.Integer (24);
      time.at(ipart) = r.Rndm() * 20.;
      energy.at(ipart) = r.Rndm() * 30.;
      cout << setw(10) << det.at(ipart) 
           << setw(12) << time.at(ipart)
           << setw(12) << energy.at(ipart) << endl;
    }
    t.Fill ();
  }
  t.Write();
  return 0;
}
