/*IONESCU Ioana - 312CB*/

#include "header.h"

//functii pentru coada

TCoada* InitQ ()  /* creeaza coada vida cu elemente de dimensiune d;
				   anumite implementari pot necesita si alti parametri */
{ 
  TCoada* c;          /* spatiu pentru descriptor coada */
  c = (TCoada*)malloc(sizeof(TCoada));
  if ( ! c ) return NULL;                  /* nu exista spatiu -> "esec" */

  c->inc = c->sf = NULL;
  return c;          /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, TArb x)  /* adauga element la sfarsitul cozii */
{ 
  TLista aux;
  aux = (TLista)malloc(sizeof(TCelula));      /* aloca o noua celula */
  if ( ! aux) return 0;             /* alocare imposibila -> "esec" */

  aux->info = x;
  aux->urm = NULL;

  if (c->sf != NULL)          /* coada nevida */
    c->sf->urm = aux;                   /* -> leaga celula dupa ultima din coada */
  else                              /* coada vida */
    c->inc = aux;                    /* -> noua celula se afla la inceputul cozii */
  c->sf = aux;  	            /* actualizeaza sfarsitul cozii */
  return 1;                         /* operatie reusita -> "succes" */
}

void ExtrQ(TCoada *c)  /* extrage primul element din coada */
{ 
  TLista aux;
  if(c->inc == c->sf)
  {
  	aux = c->inc;
  	free(aux);
  	c->inc = NULL;
  	c->sf = NULL;
  }
  else
  {
  	aux = c->inc;
  	c->inc = aux->urm;
  	free(aux);
  }  
}

void DistrQ(TCoada **c) /* distruge coada */
{
  TLista p, aux;
  p = (*c)->inc;
  while(p)
  {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*c);
  *c = NULL;
}