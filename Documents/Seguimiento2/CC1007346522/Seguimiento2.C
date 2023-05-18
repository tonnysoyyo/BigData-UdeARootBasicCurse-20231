#include "iostream"
#include "TFile.h"
#include "TTree.h"
#include "TRandom3.h"

using namespace std;

int Seguimiento2() {

    // Inicializando Objetos a utilizar
    Int_t Npart;
    vector<Int_t> Det; // STL Vectors
    vector<Float_t> Energy;
    vector<Float_t> Time;

    // Creamos o sobrescribimos un archivo .root
    TFile File1 ("Particles1.root", "RECREATE");
    
    // Creamos un Tree que contendrá todos los datos
    TTree Tree1 ("tree", "Tree 1");

    // Se inicializan todas las Branches
    Tree1.Branch ("Npart", &Npart);
    Tree1.Branch ("Det"  , &Det  );
    Tree1.Branch ("Time" , &Time  );
    Tree1.Branch ("En"   , &Energy);

    // Usando TRandom3 para generar datos aleatorios
    TRandom3 Random1; Random1.SetSeed ();


    for (int ievt=0; ievt<100; ievt++) {

        Npart = Random1.Integer(6); // Número aleatorio de partículas

        cout << "Event " << ievt 
            << " has " << Npart << " particles.\n";
            
    // Llenando las Branches
        for (int ipart=0; ipart<Npart; ipart++) 
        {
            Det.push_back( Random1.Integer (24));
            Time.push_back( Random1.Rndm() * 20.);
            Energy.push_back( Random1.Rndm() * 30.);

            // Muestra en pantalla el valor creado
            cout << setw(10) << Det   [ipart] 
                << setw(12) << Time  [ipart] 
                << setw(12) << Energy[ipart] << endl;
        }
        Tree1.Fill (); // Llenar el Tree
        Det.clear(); Time.clear(); Energy.clear(); // Borramos los datos del STL Vector
    }
    Tree1.Write(); // Se escribe lo realizado en el Tree
    
    return 0;
}
