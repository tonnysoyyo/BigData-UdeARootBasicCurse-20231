#include <vector>

#include "TFile.h"
#include "TTree.h"

void Example9_MyEventmanyparticles_read()
{

    // Read File
    TFile *f = TFile::Open("manyparticles.root", "READ");

    if (!f)
    {
        return;
    }

    // Get Tree
    TTree *t = (TTree *)f->Get("tree");


    // Vectors 
    std::vector<int> *det = new vector<Int_t>();
    std::vector<float> *time = new vector<Float_t>();
    std::vector<float> *energy = new vector<Float_t>();
    Int_t Npart;

    // Branches
    t->SetBranchAddress("Npart", &Npart);

    t->SetBranchAddress("det", &det);

    t->SetBranchAddress("time", &time);

    t->SetBranchAddress("energy", &energy);


    // Events
    for (Int_t i = 0; i < t->GetEntries(); i++)
    {
        // Each entry 
        t->GetEntry(i);
        cout << "* Event " << i
         << " has " << Npart << " particles:\n";

        // Particles in the event 
        for (UInt_t j = 0; j < Npart; ++j)
        {
            cout << setw(10) << det->at(j)
                 << setw(10) << time->at(j)
                 << setw(10) << energy->at(j)
                 << endl;
        }
    }

    // Since we passed the address of a local variable we need
    // to remove it.
    t->ResetBranchAddresses();
}