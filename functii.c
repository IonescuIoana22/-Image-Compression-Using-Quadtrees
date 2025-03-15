/*Ionescu Ioana - 312CB*/

#include "header.h"

    /* n - dimensiunea matricei
    x - indicele primei linii
    y - indicele primei coloane */

//calculeaza valoarea medie a fiecarei culori
void culori(TPixel **mat, int n, int x, int y, int *red, int *green, int *blue) {
    int sr = 0, sg = 0, sb = 0;
    /*sr - suma pentru culoarea rosu
    sg - suma pentru culoarea verde
    sb - suma pentru culoarea albastru*/
    for(int i = x; i < x+n; i++) {
        for(int j = y; j < y+n; j++) {
            sr = mat[i][j].r + sr;
            sg = mat[i][j].g + sg;
            sb = mat[i][j].b + sb;
        }
    }
    *red = sr / (n*n);
    *green = sg / (n*n);
    *blue = sb / (n*n);
}
//calculeaza scorul de similaritate
int medie(TPixel **mat, int n, int x, int y) {
    int red = 0, green = 0, blue = 0, s = 0, mean = 0;
    culori(mat, n, x, y, &red, &green, &blue);
    for(int i = x; i < x+n; i++) {
        for(int j = y; j < y+n; j++) {
            int a = red - mat[i][j].r;
            int b = green - mat[i][j].g;
            int c = blue - mat[i][j].b;
            s = a*a + b*b + c*c + s;
        }
    }
    mean = s / (3*n*n);
    return mean;
}
//verifica relatia dintre scorul de similaritate si pragul impus
int similaritate(int factor, TPixel **mat, int n, int x, int y) {
    int mean = medie(mat, n, x, y);
    if(mean > factor) {
        return 0;
    }else return 1;
}
//calculez minimul a 4 numere
int minim(int a, int b, int c, int d) {
    if(a <= b && a <= c && a <= d)return a;
    if(b <= a && b <= c && b <= d)return b;
    if(c <= a && c <= b && c <= d)return c;
    if(d <= a && d <= b && d <= c)return d;
    return 0;
}
//calculez maximul a 4 numere
int maxim(int a, int b, int c, int d) {
    if(a >= b && a >= c && a >= d) return a;
    if(b >= a && b >= c && b >= d) return b;
    if(c >= a && c >= b && c >= d) return c;
    if(d >= a && d >= b && d >= c) return d;
    return 0;
}
// calculeaza nivelul minim
int nivmin(TArb a) {
    int nf1, nf2, nf3, nf4;
    if(a == NULL) return 0;  //este vid
    //parcurg fiecare subarbore al nodului
    nf1 = NrNiv(a->f1);
    nf2 = NrNiv(a->f2);
    nf3 = NrNiv(a->f3);
    nf4 = NrNiv(a->f4);
    //numarul maxim de niveluri este numarul maxim de niveluri de pe fiecare subarbore + radacina
    return 1 + minim(nf1, nf2, nf3, nf4);
}
//calculeaza nivelul maxim
int NrNiv(TArb a) {
    int nf1, nf2, nf3, nf4;
    if(a == NULL) return 0;  //este vid
    //parcurg fiecare subarbore al nodului
    nf1 = NrNiv(a->f1);
    nf2 = NrNiv(a->f2);
    nf3 = NrNiv(a->f3);
    nf4 = NrNiv(a->f4);
    //numarul maxim de niveluri este numarul maxim de niveluri de pe fiecare subarbore + radacina
    return 1 + maxim(nf1, nf2, nf3, nf4);
}
//calculez numarul de frunze
int NrFr(TArb a) {
    int ct = 0;
    if(a == NULL) return 0;
    if(a->f1 == NULL && a->f2 == NULL && a->f3 == NULL && a->f4 == NULL) ct++;  //este frunza
    //parcurg fiecare subarbore al nodului
    ct = ct + NrFr(a->f1);
    ct = ct + NrFr(a->f2);
    ct = ct + NrFr(a->f3);
    ct = ct + NrFr(a->f4);
    return ct;
}
//execut sarcinile din cerinta 1
void cerinta1(TArb a, FILE *fout, int n) {
    int nivelmax = 0, nrfrunze = 0, nivelmin = 0, dimensiune = n;
    nivelmax = NrNiv(a);  //nivelul maxim al arborelui
    nrfrunze = NrFr(a);  //numarul de frunze
    nivelmin = nivmin(a);  //nivelul cel mai mic pe care se afla o frunza
    while(nivelmin > 1) {
        dimensiune = dimensiune / 2;
        nivelmin--;
    }
    fprintf(fout, "%d %d %d", nivelmax, nrfrunze, dimensiune);
}
//parcurg arborele pe nivel
int ParcNiv(TCoada *c, TArb a, FILE *fbout) {
    if(IntrQ(c, a) == 0) return 0;
    while(c->inc) {
        fwrite(&(c->inc->info->tip_nod), sizeof(unsigned char), 1, fbout);
        if(c->inc->info->tip_nod == 1) {
            fwrite(&(c->inc->info->valori.r), sizeof(unsigned char), 1, fbout);
            fwrite(&(c->inc->info->valori.g), sizeof(unsigned char), 1, fbout);
            fwrite(&(c->inc->info->valori.b), sizeof(unsigned char), 1, fbout);
        }
        ExtrQ(c);
        if(IntrQ(c, a->f1) == 0) return 0;
        if(IntrQ(c, a->f2) == 0) return 0;
        if(IntrQ(c, a->f3) == 0) return 0;
        if(IntrQ(c, a->f4) == 0) return 0;
    }
    return 0;
}
//execut sarcinile din cerinta 2
int cerinta2(TArb a, FILE *fbout, int n) {
    TCoada *c;
    c = InitQ();
    fwrite(&n, sizeof(int), 1, fbout);
    DistrQ(&c);
    return 0;
}
//execut sarcinile din cerinta 3
int cerinta3(FILE *fin, FILE *ppm) {
    TArb a;
    TPixel **mat;
    int n;
    fread(&n, sizeof(int), 1, fin);
    fprintf(ppm, "P6");
    fprintf(ppm, "%d", n);
    fprintf(ppm, "%d", n);
    fprintf(ppm, "255");
    //aloc memorie pentru matrice
    mat = malloc(n * sizeof(TPixel));
    if(mat == NULL) {
        return 0;
    }
    for(int i = 0; i < n; i++) {
        mat[i] = malloc(n * sizeof(TPixel *));
        if(mat[i] == NULL) {
            for(int j = 0; j <= i; j++)free(mat[j]);
            return 0;
        }
    }
    a = ConstrArb3(fin);
    if(matrice(n, a, 0, mat) == 0)return 0;
    //am scris matricea in fisierul ppm
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            fwrite(&mat[i][j], sizeof(TPixel), 1, ppm);
        }
    }
    //dezaloc memorie matrice
    for(int i = 0; i < n; i++)free(mat[i]);
    free(mat);
}
TArb ConstrArb3(FILE *fin) {   //construiesc arborele pentru cerinta 3
    TPixel p;
    TArb a = NULL, nod;
    unsigned char tip;
    unsigned char r,g,b;
    TCoada *c = NULL;
    c = InitQ();
    fread(&tip, sizeof(unsigned char), 1, fin);
    if(tip == 1) {
        fread(&r, sizeof(unsigned char), 1, fin);
        fread(&g, sizeof(unsigned char), 1, fin);
        fread(&b, sizeof(unsigned char), 1, fin);
        p.r = r;
        p.g = g;
        p.b = b;
        nod = ConstrFr(p);
    } else {
        nod = ConstrNod();
    }
    a = nod;
    if(IntrQ(c, nod) == 0)return NULL;
    while(fread(&tip, sizeof(unsigned char), 1, fin) && c->inc) {
        if(c->inc->info->tip_nod == 0) {
            for(int i = 1; i <= 4; i++) {
                fread(&tip, sizeof(unsigned char), 1, fin);
                if(tip == 1) {
                    fread(&r, sizeof(unsigned char), 1, fin);
                    fread(&g, sizeof(unsigned char), 1, fin);
                    fread(&b, sizeof(unsigned char), 1, fin);
                    p.r = r;
                    p.g = g;
                    p.b = b;
                    nod = ConstrFr(p);
                } else {
                    nod = ConstrNod();
                }
                if(i == 1)c->inc->info->f1 = nod;
                if(i == 2)c->inc->info->f2 = nod;
                if(i == 3)c->inc->info->f3 = nod;
                if(i == 4)c->inc->info->f4 = nod;
            }
            ExtrQ(c);
        }
    }
    DistrQ(&c);
    return a;
}
//construiesc matricea de adiacenta
int matrice(int n, TArb a, int nrfiu, TPixel **mat) {  //nrfiu - pentru a stii pozitia in matricea de pixeli
    if(a == NULL)return 0;
    if(a->tip_nod == 1) {  //este frunza
        if(nrfiu == 1) {
            for(int i = 0; i < n/2; i++) {
                for(int j = 0; j < n/2; j++) {
                mat[i][j].r = a->valori.r;
                mat[i][j].g = a->valori.g;
                mat[i][j].b = a->valori.b;
                }
            }
        } else if(nrfiu == 2) {
            for (int i = 0; i < n/2; i++) {
                for(int j = n/2; j < n; j++) {
                    mat[i][j].r = a->valori.r;
                    mat[i][j].g = a->valori.g;
                    mat[i][j].b = a->valori.b;
                }
            }
        } else if(nrfiu == 3) {
            for(int i = n/2; i < n; i++) {
                for(int j = n/2; j < n; j++) {
                    mat[i][j].r = a->valori.r;
                    mat[i][j].g = a->valori.g;
                    mat[i][j].b = a->valori.b;
                }
            }
        } else {
            for(int i = n/2; i < n; i++) {
                for(int j = 0; j < n/2; j++) {
                    mat[i][j].r = a->valori.r;
                    mat[i][j].g = a->valori.g;
                    mat[i][j].b = a->valori.b;
                }
            }
        }
    }
    matrice(n/2, a->f1, 1, mat);
    matrice(n/2, a->f2, 2, mat);
    matrice(n/2, a->f3, 3, mat);
    matrice(n/2, a->f4, 4, mat);
}
