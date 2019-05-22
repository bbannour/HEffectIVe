/*
 * bicolTree.h
 *
 *  Created on: 10 déc. 2018
 *      Author: Nico
 *  Modified on: 23 déc 2018
 *  	Editor: Boutheina
 */

#ifndef BICOLTREE_H_
#define BICOLTREE_H_

#include <stdlib.h>
#include <stdio.h>

#define RESERVER(x,y) (y *) malloc(sizeof(y)*x);
#define RESERVERN(x,y) (y *) calloc(x,sizeof(y));
#define LIBERER(x,y,z) free(z);

#define MARKED(x) x->mark
#define SETMARK(x) (x->mark = 1)

#define CLE_TYPE unsigned int

#define BCT_KEY_INF(x,y) (x->cle < y->cle)

enum clr {ROUGE,NOIR};

#define COULEUR(x) x->couleur

#define IS_ROUGE(x) (COULEUR(x) == ROUGE)

#define PARENT(x) x->parent
#define GAUCHE(x) x->gauche
#define DROIT(x) x->droit

#define GRAND_P(x) PARENT(PARENT(x))
#define ONCLE_DROIT(x) DROIT(GRAND_P(x))
#define ONCLE_GAUCHE(x) GAUCHE(GRAND_P(x))

// t est un bct ** (typiquement &b où b est un b bct *)
#define RACINE(t) (*t)
// le NIL d'un bct est le parent de la racine
#define NIL(t) PARENT(RACINE(t))

#define IS_DROIT(x) (y == DROIT(PARENT(x)))
#define IS_GAUCHE(x) (x == GAUCHE(PARENT(x)))
#define IS_LEAF(x,n) ((DROIT(x) == n) && (GAUCHE(x) == n))


typedef struct bicolTree_
{
	CLE_TYPE cle;

	char mark;
	enum clr couleur;

	struct bicolTree_ * parent;
	struct bicolTree_ * gauche;
	struct bicolTree_ * droit;

} bct;

void bct_rotation_gauche(bct ** bct_ref, bct * x);
void bct_rotation_droite(bct ** bct_ref, bct * x);
void bct_insertion(bct ** T_Ref, CLE_TYPE key);
unsigned int bct_search(bct ** T_Ref, CLE_TYPE key);

// un bct vide est son propre NIL
// donc PARENT(NIL) = NIL
bct * new_bct();

bct * new_nodes(CLE_TYPE);

void bct_toDot(FILE * f, bct ** r);


#endif /* BICOLTREE_H_ */
