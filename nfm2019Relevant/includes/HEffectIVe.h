/*
 * HEffectIVe.h
 *
 *  Created on: 20 déc. 2018
 *      Author: Nico
 */

#ifndef HEFFECTIVE_H_
#define HEFFECTIVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory.h"

#define BDD_UNDEF 	 0b11111111111111111111111111111111

typedef unsigned int BDD;
typedef unsigned int NAT;
typedef struct Var_ Var;

extern NAT bool_vars_index;


#ifdef EXTERN_THEO
BDD bdd_external_modif_Hash(void * cst);
#endif


#ifndef PRIME

void bdd_init_Hash(NAT nb_vars, NAT nb_nodes, NAT cash_size);
Var * bdd_create_var(char *);


#else

extern NAT nb_prime;

BDD bdd_get_Prime(BDD r);

typedef double probaType;
#define proba_mult(a,b) (a*b)

probaType get_Var_Proba(Var *);

enum prime_type {all_relevant, positive_relevant , specified_relevant};

void bdd_prime_initHash(NAT nb_vars, NAT nb_nodes, NAT cash_size, NAT prime_size, enum prime_type);
Var * bdd_prime_create_var(const char * name, NAT relevance, NAT neg_relevance);
void bdd_prime_display(FILE *, BDD);
void bdd_prime_display_proba(FILE * f, BDD b);

BDD bdd_get_Var_bdd(Var * v);

#endif


#define not(x) bdd_not(x)
#define and(x,y) bdd_and(x,y)
#define or(x,y) bdd_or(x,y)
#define imp(x,y) or(not(x),y)


NAT get_var_index(BDD r);

BDD bdd_not(BDD r);

BDD bdd_and(BDD g,  BDD d);

BDD bdd_or(BDD g,  BDD d);

BDD bdd_imp(BDD g,  BDD d);

BDD bdd_exists(BDD r, NAT var_id_new);

BDD bdd_subst_var_by_cst(BDD r, NAT cst , NAT var);

BDD bdd_subst_var_by_var(BDD r, NAT var_id_new, NAT var_id_old);

BDD bdd_subst_var_by_bdd(BDD r, BDD f, NAT var_id_old);

void bdd_toDot(FILE * f, BDD r);





#endif /* HEFFECTIVE_H_ */
