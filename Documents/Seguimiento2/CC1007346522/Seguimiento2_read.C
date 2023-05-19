#include<iostream>
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

using namespace std;

int Seguimiento2_read() {
    // Inicializando Objetos a utilizar
    Int_t Npart;
    vector<Int_t> *Det = nullptr; // STL Vectors
    vector<Float_t> *Energy = nullptr;
    vector<Float_t> *Time= nullptr;
    // Se inicializan vacíos

    // Leemos el archivo .root ya creado
    TFile File1 ("Particles1.root", "READ");

    // Leemos el Tree que está dentro del archivo .root
    TTree *Tree1 = (TTree*) File1.Get ("tree");

    // Asigamos cada rama
    Tree1->SetBranchAddress ("Npart", &Npart );
    Tree1->SetBranchAddress ("Det"  , &Det    );
    Tree1->SetBranchAddress ("Time" , &Time   );
    Tree1->SetBranchAddress ("En"   , &Energy );

    cout << "* This tree has "  // Información del Tree
        << Tree1->GetEntries() << " entries.\n\n";

    // Recorremos cada evento 
    for (int ievt=0; ievt<Tree1->GetEntries(); ievt++) 
    {
        Tree1->GetEntry (ievt); // Para acceder a cada evento
        cout << "* Event " << ievt 
            << " has " << Npart << " particles:\n";
        // Se imprime en pantalla todos los datos por evento
        for (int ipart=0; ipart<Npart; ipart++) 
        {
            cout<< setw(10) << Det->at(ipart)
                << setw(12) << Time->at(ipart)
                << setw(12) << Energy->at(ipart) << endl;
        }
    }
    return 0;
}
