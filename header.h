/*Ionescu Ioana - 312CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definirea unui pixel
typedef struct pixel {
    unsigned char r;  //valoarea pentru rosu
    unsigned char g; //valoarea pentru verde
    unsigned char b;  //valoarea pentru albastru   
}TPixel;

//definirea unui nod
typedef struct nod {
    unsigned char tip_nod;  //valoarea 0 sau 1
    TPixel valori;
    struct nod *f1, *f2, *f3, *f4;  //fiii nodului
} TNod, *TArb;

//definire coada pentru parcurgerea in latime a arborelui
typedef struct celula  //o celula din coada
{ 
  TArb info;
  struct celula* urm;
} TCelula, *TLista;

typedef struct coada
{ 
  TLista inc, sf;       /* adresa primei si ultimei celule */
} TCoada;

void culori(TPixel **mat, int n, int x, int y, int *red, int *green, int *blue);
int medie(TPixel **mat, int n, int x, int y);
int similaritate(int factor, TPixel **mat, int n, int x, int y);
int nivmin(TArb a);
int NrNiv(TArb a);
int NrFr(TArb a);
void cerinta1(TArb a, FILE *fout, int n);
int ParcNiv(TCoada *c, TArb a, FILE *fbout);
int cerinta2(TArb a, FILE *fbout, int n);
int cerinta3(FILE *fin, FILE *ppm);
TArb ConstrArb3(FILE *fin);
int matrice(int n, TArb a, int nrfiu, TPixel **mat);

TArb ConstrFr(TPixel pixel);
TArb ConstrNod();
TArb ConstrArb(TArb *a, TPixel **mat, int n, int x, int y, int factor);
void distruge(TArb r);
void DistrArb(TArb *a);

TCoada* InitQ ();
int IntrQ(TCoada *c, TArb x);
void ExtrQ(TCoada *c);
void DistrQ(TCoada **c);
