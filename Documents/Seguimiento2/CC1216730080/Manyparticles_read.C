#include <vector>

int Manyparticles_read() {
  Int_t Npart;
  vector<int> *det = 0;
  vector<float> *energy = 0;
  vector<float> *time = 0;

  TBranch *bdet = 0;
  TBranch *benergy = 0;
  TBranch *btime = 0;

  TFile f ("manyparticles.root", "READ");
  TTree *t = (TTree*) f.Get ("tree");
  t->SetBranchAddress ("Npart", &Npart );
  t->SetBranchAddress ("Det"  , &det , &bdet);
  t->SetBranchAddress ("Time" , &time , &btime);
  t->SetBranchAddress ("En"   , &energy , &benergy);

  cout << "* This tree has " 
       << t->GetEntries() << " entries.\n\n";

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