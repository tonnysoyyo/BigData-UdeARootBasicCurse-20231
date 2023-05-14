#include <vector>

#include "TFile.h"
#include "TTree.h"

void Example9_MyEventmanyparticles()
{

    // Recreate File
    TFile *f = TFile::Open("manyparticles.root", "RECREATE");

    if (!f)
    {
        return;
    }

    // Vectors 
    std::vector<float> det;
    std::vector<float> time;
    std::vector<float> energy;
    Int_t Npart;

    // Create a TTree
    TTree *t = new TTree("tree", "My tree");

    // Branches
    t->Branch ("Npart", &Npart, "Npart/I");
    t->Branch("det", &det);
    t->Branch("time", &time);
    t->Branch("energy", &energy);

    TRandom3 r; r.SetSeed ();


    //  100 Events
    for (Int_t i = 0; i < 100; i++)
    {
        // Number of particles in the event. Max 6
        Npart = r.Integer(6); 

        cout << "Event " << i
             << " has " << Npart << " particles.\n";

        det.clear();
        time.clear();
        energy.clear();

        // Particles
        for (Int_t j = 0; j < Npart; ++j)
        {
            det.emplace_back(r.Integer (24));
            time.emplace_back(r.Rndm() * 20.);
            energy.emplace_back(r.Rndm() * 30.);

            cout << setw(10) << det.back()
                << setw(12) << time.back()
                << setw(12) << energy.back() << endl;
        }
        // Fill for event 
        t->Fill();
    }
    f->Write();

    delete f;
}
