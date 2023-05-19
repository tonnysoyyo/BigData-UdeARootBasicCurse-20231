
int Example9_MyEventmanyparticles_readVec() {

   Int_t Npart;
   
   std::vector<Int_t> *det= new std::vector<Int_t>();
   std::vector<Float_t> *energy = new std::vector<Float_t>();
   std::vector<Float_t>*time = new std::vector<Float_t>();


  TFile f ("manyparticles.root", "READ");
  TTree *t = (TTree*) f.Get ("tree"); // lo saco del archivo y lo llevo a t
  t->SetBranchAddress ("Npart", &Npart );//"Npart"-- nombre de la variable en el branch, &Npart nombre de la variable
  t->SetBranchAddress ("Det"  , &det    );
  t->SetBranchAddress ("Time" , &time  );
  t->SetBranchAddress ("En"   , &energy);

  cout << "* This tree has " 
       << t->GetEntries() << " entries.\n\n";

  for (int ievt=0; ievt<t->GetEntries(); ievt++) 
  {
    t->GetEntry (ievt); // Siempre se debe poner esta línea
    cout << "* Event " << ievt 
         << " has " << Npart << " particles:\n";

    for (int ipart=0; ipart<det->size(); ipart++) 
    {
      std::cout << &det[ipart] <<endl; //<<time &[ipart]<< &energy[ipart] 

    
    }

     for (int ipart=0; ipart<time->size(); ipart++) 
    {
      std::cout << &time[ipart] <<endl; //<<time &[ipart]<< &energy[ipart] 

    
    }

     for (int ipart=0; ipart<energy->size(); ipart++) 
    {
      std::cout << &energy[ipart] <<endl; //<<time &[ipart]<< &energy[ipart] 

    
    }

  
 
     
  }
  return 0;
}
