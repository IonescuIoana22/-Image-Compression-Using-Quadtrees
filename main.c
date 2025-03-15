/*Ionescu Ioana - 312CB*/

#include "header.h"

int main(int argc, char const *argv[]) {
    FILE *fin, *fout, *fbout, *ppm;  //fin - fisierul ppm, fout - fisier_iesire
    int factor = 0, n = 0, size = 0;  // n - dimensiunea matricei, size = 255
    char tipfisier[2] = "\0";
    TPixel **mat;
    TArb a = NULL; // a - arbore
    if(strcmp(argv[1],"-d") == 0) {
        fin = fopen(argv[2], "rb");
        ppm = fopen(argv[3], "wb");
    } else {
        if(strcmp(argv[1], "-c1") == 0) {
        fin = fopen(argv[3], "rb");
        fout = fopen(argv[4], "w");
        factor = *argv[2] - '0';
        } else {
            fin = fopen(argv[3], "rb");
            fbout = fopen(argv[4], "wb");
            factor = *argv[2] - '0';
        }
        fgets(tipfisier, 2, fin);
        fscanf(fin, "%d %d", &n, &n);
        fscanf(fin, "%d", &size);
        mat = malloc(n * sizeof(TPixel));
        if(mat == NULL) {
            fprintf(fout, "Nu s-a facut alocarea");
            return 0;
        }
        for(int i = 0; i < n; i++) {
            mat[i] = malloc(n * sizeof(TPixel *));
            if(mat[i] == NULL) {
                fprintf(fout, "Nu s-a facut alocarea");
                for(int j = 0; j <= i; j++)free(mat[j]);
                return 0;
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                fread(&mat[i][j], sizeof(TPixel), 1, fin);
            }
        }
        ConstrArb(&a, mat, n, 0, 0, factor);
    }
    if(strcmp(argv[1],"-c1") == 0) {
        cerinta1(a, fout, n);
    }
    if(strcmp(argv[1], "-c2") == 0) {
        if(cerinta2(a, fbout, n) == 0)printf("Nu s-a facut alocarea");
    } else {
        if(cerinta3(fin, ppm) == 0)printf("Nu s-a facut alocarea");
    }
    //eliberez matricea
    for(int i = 0; i < n; i++)free(mat[i]);
    free(mat);
    //distrug arborele
    DistrArb(&a);
    //inchid fisierele
    fclose(fin);
    fclose(fout);
    fclose(fbout);
    fclose(ppm);
}