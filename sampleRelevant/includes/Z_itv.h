/*
 * Z_itv.h
 *
 *  Created on: 20 déc. 2018
 *      Author: Nico
 */

#ifndef Z_ITV_H_
#define Z_ITV_H_

#include "HEffectIVe.h"

typedef int Z;

typedef struct diconode_ diconode;

typedef struct Z_itv_ Z_itv;
typedef struct Z_itv_list_ Z_itv_list;

// init de la librairie
void init_Z_itv_list(unsigned int);

Z_itv_list * new_Z_itv_list();

// ajout d'itv dans n'importe quel ordre
void Z_itv_list_add(Z_itv_list * l, Z lb, Z ub);

// ajout d'itv non adjacents et croissants
void Z_itv_list_pushback(Z_itv_list * l, Z lb, Z ub);

void init_Heffective_for_Z_itv_lib();

diconode * Z_itv_list_to_bdd(Z_itv_list * l);

#ifdef HOMOGENEOUS_PROBA
extern Z_itv * proba_Range;
Z len_proba_Range;
void set_proba_Range(unsigned int lb, unsigned int ub);
probaType get_node_Z_itv_list_proba(diconode * n);
#endif



#endif /* Z_ITV_H_ */
