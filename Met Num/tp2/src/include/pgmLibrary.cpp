#include "pgmLibrary.h"

void SkipComments(FILE *fp)
{
    int ch;
    char line[100];
 
    while ((ch = fgetc(fp)) != EOF && isspace(ch))
        ;
    if (ch == '#') {
        if (fgets(line, sizeof(line), fp) != NULL) {
          SkipComments(fp);
        }
    } else
        fseek(fp, -1, SEEK_CUR);
}

/*for reading:*/
MatrixXd readPGM(string file_name)
{
    int rows;
    int cols;
    int max_gray;
    
    FILE *pgmFile;
    char version[3];
    int i, j;
    int lo, hi;
 
    pgmFile = fopen(file_name.c_str(), "rb");
    if (pgmFile == NULL) {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }
 
    if (fgets(version, sizeof(version), pgmFile) != NULL) {
      if (strcmp(version, "P5")) {
          fprintf(stderr, "Wrong file type!\n");
          exit(EXIT_FAILURE);
      }
    }
 
    SkipComments(pgmFile);
    if (fscanf(pgmFile, "%d", &cols) >= 0)
      SkipComments(pgmFile);
    if (fscanf(pgmFile, "%d", &rows) >= 0)
      SkipComments(pgmFile);
    if (fscanf(pgmFile, "%d", &max_gray) >= 0)
      fgetc(pgmFile);

    MatrixXd m = MatrixXd::Zero(rows, cols);
 
    if (max_gray > 255)
        for (i = 0; i < rows; ++i)
            for (j = 0; j < cols; ++j) {
                hi = fgetc(pgmFile);
                lo = fgetc(pgmFile);
                m(i, j) = (hi << 8) + lo;
            }
    else
        for (i = 0; i < rows; ++i)
            for (j = 0; j < cols; ++j) {
                lo = fgetc(pgmFile);
                m(i, j) = lo;
            }
 
    fclose(pgmFile);
    return m;
}