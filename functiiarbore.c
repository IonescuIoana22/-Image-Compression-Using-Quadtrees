/*Ionescu Ioana - 312CB*/
     
#include "header.h"

    /* n - dimensiunea matricei
    x - indicele primei linii
    y - indicele primei coloane */

//construiesc o frunza
TArb ConstrFr(TPixel pixel) {
    TArb aux = (TArb)malloc(sizeof(TNod));
    if(!aux) return NULL;
    aux->f1 = aux->f2 = aux->f3 = aux->f4 = NULL;
    aux->tip_nod = 1;
    aux->valori.r = pixel.r;
    aux->valori.g = pixel.g;
    aux->valori.b = pixel.b;
    return aux;
}
//construiesc un nod neterminal
TArb ConstrNod() {
    TArb aux = (TArb)malloc(sizeof(TNod));
    if(!aux) return NULL;
    aux->f1 = aux->f2 = aux->f3 = aux->f4 = NULL;
    aux->tip_nod = 0;
    aux->valori.r = -1;
    aux->valori.g = -1;
    aux->valori.b = -1;
    return aux;
}
//construiesc arborele
TArb ConstrArb(TArb *a, TPixel **mat, int n, int x, int y, int factor) {
    TArb nod;
    if(similaritate(factor, mat, n, x, y) == 0) {
        nod = ConstrNod();
        if(nod == NULL) return NULL;
        *a = nod;
        ConstrArb((*a)->f1, mat, n/2, 0, 0, factor);
        ConstrArb((*a)->f2, mat, n/2, 0, n/2, factor);
        ConstrArb((*a)->f3, mat, n/2, n/2, n/2, factor);
        ConstrArb((*a)->f4, mat, n/2, n/2, 0, factor);
    } else {
        TPixel p;  //retine informatiile mediei fiecarei culori
        int red = 0, green = 0, blue = 0;
        culori(mat, n, x, y, &red, &green, &blue);
        p.r = red;
        p.g = green;
        p.b = blue;
        nod = ConstrFr(p);
        if(nod == NULL) return NULL;
    }
}
void distruge(TArb r) 	/* functie auxiliara - distruge toate nodurile */
{
	if (!r) return;
	distruge (r->f1);     /* distruge subarborele f1 */
	distruge (r->f2);     /* distruge subarborele f2 */
    distruge (r->f3);     /* distruge subarborele f3 */
	distruge (r->f4);     /* distruge subarborele f4 */
	free (r);             /* distruge nodul radacina */
}
void DistrArb(TArb *a) /* distruge toate nodurile arborelui de la adresa a */
{
	if (!(*a)) return;       /* arbore deja vid */
	distruge (*a);           /* distruge toate nodurile */
	*a = NULL;               /* arborele este vid */
}