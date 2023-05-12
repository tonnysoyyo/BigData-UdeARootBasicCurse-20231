/*El siguiente macro simula un experimento donde en cada evento se genera un numero aleatorio de particulas con diferentes
variables medidas*/
{
Int_t NumEvents = 10; //Numero de eventos
Int_t Npart; //Numero de particulas

/*
Int_t Det[500];
Float_t Energy[500] , Time[500]; //500 numero de eventos */

std::vector<Int_t> *Det;
std::vector<Float_t> *Energy ;
std::vector<Float_t> *Time;

//Creamos un Tfile donde almacenaremos nuestro Ttree con los datos:

TFile* file = new TFile("manyparticles.root" , "RECREATE");
TTree* tree = new TTree("tree" , "My tree");

tree->Branch ("Npart", &Npart );     //defino mis ramas
tree->Branch ("Det" , &Det );
tree->Branch ("Time" , &Time);
tree->Branch ("Energy" , &Energy);

//Creo un objeto TRandom3 que ultilizare para generar los datos aleatorios.
TRandom3* random = new TRandom3();
random->SetSeed();

//Doble ciclo for para generar los datos aleatorios y guardarlos en el tree
for(int i = 0 ; i<NumEvents ; i++){
Npart = random->Integer(6); //Evento con un numero de particulas entre 0 y 6
cout << "El evento # " << i << " Detecto " << Npart << " Particulas. ------------------------------------"<<endl;

for (int j = 0; j<Npart; j++)
{
    
    Det->push_back(random->Integer(24));
    Time->push_back(random->Rndm()*20.);
    Energy->push_back(random->Rndm()*30.);

    cout << "Det = " << Det->at(j)<<"  ";
    cout << "Time = " << Time->at(j)<<"  ";
    cout << "Energy = " << Energy->at(j) << endl;
    /*
    cout << setw(10) << Det [j]
    << setw(12) << Time [j]
    << setw(12) << Energy[j] << endl;*/
}
    tree->Fill (); //lleno el arbol

    Det->clear(); //Limpio los vectores para evitar que se llenen con los mimos datos en cada iteracion!
    Time->clear();
    Energy->clear();
}

tree->Write(); //Guardo el arbol en el ttree
file->Close();
}