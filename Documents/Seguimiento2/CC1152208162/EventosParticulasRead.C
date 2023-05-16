int EventosParticulasRead() {
    // Declaración de variables:
    Int_t Npart;
    vector<Int_t>* Det = nullptr;
    vector<Float_t>* Energia = nullptr;
    vector<Float_t>* Tiempo = nullptr;

    // Apertura del archivo ROOT en modo de lectura:
    TFile f("Particulas.root", "READ");
    // Obtención del árbol del archivo:
    TTree* t = (TTree*)f.Get("tree");
    // Asociación de las ramas del árbol a las variables:
    t -> SetBranchAddress("Npart", &Npart);
    t -> SetBranchAddress("Det", &Det);
    t -> SetBranchAddress("Tiempo", &Tiempo);
    t -> SetBranchAddress("En", &Energia);

    // Obtención del número de entradas en el árbol:
    cout << "Este árbol tiene " << t -> GetEntries() << " entradas\n\n";

    // Iteración sobre las entradas del árbol:
    for (int ievt = 0; ievt < t -> GetEntries(); ievt++) {
        // Obtención de los valores de la entrada actual:
        t -> GetEntry(ievt);
        cout << "El evento " << ievt
			 << " tiene " << Npart << " partículas:\n";

        // Iteración sobre las partículas del evento actual:
        for (int ipart = 0; ipart < Npart; ipart++) {
            // Impresión de los valores de la partícula:
            cout << setw(10) << (*Det)[ipart]
				 << setw(12) << (*Tiempo)[ipart]
				 << setw(12) << (*Energia)[ipart] << endl;
	        }
	    }

    return 0;
	}
