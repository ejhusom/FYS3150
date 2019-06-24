// CREATE LATTICE
cout << "=====================================\n";
double **Lattice = new double*[dim+2];
for (int i = 0; i < dim+2; i++){
  Lattice[i] = new double[dim+2];
}


for(int i=1 ; i < dim+1 ; i++) {
  for(int j=1 ; j < dim+1 ; j++) {
    Lattice[i][j] = 1;
  }
}
cout << "Real lattice at start:\n";
for (int i=0; i<dim+2; i++){
    for (int j=0; j<dim+2; j++){
      cout << setw(8) << setprecision(4) << Lattice[i][j];
    }
  cout << endl;
}

// CREATE POINTER LATTICE
double ***PointerLattice = new double**[dim+2];
for (int i = 0; i < dim+2; i++){
  PointerLattice[i] = new double*[dim+2];
}

for(int i=0 ; i < dim+2 ; i++) {
  for(int j=0 ; j < dim+2 ; j++) {
    PointerLattice[i][j] = &Lattice[i][j];
  }
}
cout << "Pointer lattice at start:\n";
for (int i=0; i<dim+2; i++){
    for (int j=0; j<dim+2; j++){
      // PointerLattice[i][j] = &Lattice[i][j];
      cout << setw(8) << setprecision(4) << *PointerLattice[i][j];
    }
  cout << endl;
}
cout << "============================\n";



// filling four "ghost vectors"
for (int i = 1; i < dim+1; i++) {
  PointerLattice[i][dim+1] = &Lattice[i][1];
  PointerLattice[i][0] = &Lattice[i][dim];
  PointerLattice[dim+1][i] = &Lattice[1][i];
  PointerLattice[0][i] = &Lattice[dim][i];
}




Lattice[1][1] = 1000;

cout << "Real lattice after change:\n";
for (int i=0; i<dim+2; i++){
  for (int j=0; j<dim+2; j++){
    // PointerLattice[i][j] = &Lattice[i][j];
    cout << setw(8) << setprecision(4) << Lattice[i][j];
  }
  cout << endl;
}
cout << "Pointer lattice after change:\n";
for (int i=0; i<dim+2; i++){
  for (int j=0; j<dim+2; j++){
    // PointerLattice[i][j] = &Lattice[i][j];
    cout << setw(8) << setprecision(4) << *PointerLattice[i][j];
  }
  cout << endl;
}
