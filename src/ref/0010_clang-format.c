Stringa *loadFile(FILE *file, int n_rows, int dim_row) {
  Stringa *vett_document;
  Stringa row;
  int i;

  vett_document = malloc(n_rows * sizeof(Stringa));
  row = malloc(dim_row * sizeof(char));

  i = 0;
  while (fgets(row, dim_row, file) != NULL) {

    writeString(vett_document, i, row);
    i = i + 1;
  }

  return vett_document;
}

