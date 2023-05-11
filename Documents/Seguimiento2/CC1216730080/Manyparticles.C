#include <vector>

int Manyparticles() {

    /*Fuente: https://root.cern/doc/master/hvector_8C_source.html*/

  Int_t Npart;
  vector<int> det (500, 0);
  vector<float> energy (500, 0);
  vector<float> time (500, 0);

  TFile f ("manyparticles.root", "RECREATE");
  TTree t ("tree", "My tree");
  
  t.Branch ("Npart", &Npart, "Npart/I");
  t.Branch ("Det"  , &det);
  t.Branch ("Time" , &time);
  t.Branch ("En"   , &energy);

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
      cout << setw(10) << det   [ipart] 
           << setw(12) << time  [ipart] 
           << setw(12) << energy[ipart] << endl;
    }
    t.Fill ();
  }
  t.Write();
  return 0;
}
