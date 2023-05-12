/*El siguiente macro lee los datos de un  experimento y los imprime usando std::vector*/
{

//Abro el Tfile en modo lectura y obtengo el arbol.
TFile* file = new TFile("manyparticles.root" , "READ");
TTree* tree = (TTree*) file->Get("tree");

if(!file->IsOpen()){cout << "Paila!!"; exit(1);}
else{cout << "Apertura correcta!"<<endl;}

tree->Print();

//defino las variables en las que voy en las que mapeare las branches
Int_t Npart;
std::vector<Int_t> *Det;
std::vector<Float_t> *Energy ;
std::vector<Float_t> *Time ;

tree->SetBranchAddress("Npart", &Npart);
tree->SetBranchAddress("Det", &Det );
tree->SetBranchAddress("Time", &Time );
tree->SetBranchAddress("Energy", &Energy);

//Imprimo los datos:
for (int i = 0 ; i < tree->GetEntries() ; i++){
    tree->GetEvent(i);
    cout<<"El evento # "<<i<<" tiene "<<Npart<<" Particulas------------------------------------------------"<<endl;
    
    for (int j = 0 ; j < Npart ; j++){
    cout << "Det = " << Det->at(j)<<"  ";
    cout << "Time = " << Time->at(j)<<"  ";
    cout << "Energy = " << Energy->at(j) << endl;}
}

file->Close(); //ciero el tfile


}