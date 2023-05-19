int EventosParticulasWrite() {
    // Declaración de variables:
    Int_t Npart;
    vector<Int_t> Det;
    vector<Float_t> Energia;
    vector<Float_t> Tiempo;

    // Creación del archivo ROOT y del árbol:
    TFile f("Particulas.root", "RECREATE");
    TTree t("tree", "Mi tree");

    // Asociación de las ramas del árbol a las variables:
    t.Branch("Npart", &Npart, "Npart/I");
    t.Branch("Det", &Det);
    t.Branch("Tiempo", &Tiempo);
    t.Branch("En", &Energia);

    // Configuración del generador de números aleatorios:
    TRandom3 r;
    r.SetSeed();

    // Generación de eventos:
    for (int ievt = 0; ievt < 100; ievt++) {
        // Generación del número de partículas para el evento actual:
        Npart = r.Integer(6);

        cout << "El evento " << ievt
			 << " tiene " << Npart << " partículas:\n";

        // Limpieza de los vectores para el nuevo evento:
        Det.clear();
        Tiempo.clear();
        Energia.clear();

        // Generación de partículas para el evento actual:
        for (int ipart = 0; ipart < Npart; ipart++) {
            // Generación de valores aleatorios para det, tiempo y energía:
            Det.push_back(r.Integer(24));
            Tiempo.push_back(r.Rndm() * 20.0);
            Energia.push_back(r.Rndm() * 30.0);

            // Impresión en pantalla de los valores generados:
            cout << setw(10) << Det[ipart]
				 << setw(12) << Tiempo[ipart]
				 << setw(12) << Energia[ipart] << endl;
	        }

        // Llenado del árbol con los valores del evento actual:
        t.Fill();
	    }

    // Escritura del árbol en el archivo ROOT:
    t.Write();

    return 0;
	}

