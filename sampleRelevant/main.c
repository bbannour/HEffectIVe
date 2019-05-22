/*
 * main.c
 *
 *  Created on: 20 déc. 2018
 *      Author: Nico
 */



#include "Z_itv.h"


void relevant_with_cst()
{

	BDD FT, c1_active, f1, f2, level_bdd;

	diconode * level;
	Z_itv_list * level_list;

	// init of libs
	bdd_prime_initHash(24,1000,100,0,specified_relevant); //0 : prime of any size

	init_Z_itv_list(128);
	set_proba_Range(0,9);
	init_Heffective_for_Z_itv_lib();


	// config variable: both positive and negative are significant
	c1_active = bdd_get_Var_bdd(bdd_prime_create_var("c1_runs", 1, 1));

	// fault variables: only positive is significant
	f1 = bdd_get_Var_bdd(bdd_prime_create_var("f1", 1, 0));
	f2 = bdd_get_Var_bdd(bdd_prime_create_var("f2", 1, 0));

	// constrait creation
	level_list = new_Z_itv_list();
	Z_itv_list_pushback(level_list, 0,1);
	level = Z_itv_list_to_bdd(level_list);
	level_bdd = bdd_external_modif_Hash(level);



	BDD c1_ft = and(c1_active,f1);
	BDD c2_ft = and(not(c1_active),f2);

	FT = or( or(c1_ft,c2_ft), level_bdd);


	bdd_prime_display(stdout,bdd_get_Prime(FT));


	return;

}

void relevant()
{

	BDD FT, c1_active, f1, f2;

	// init of libs
	bdd_prime_initHash(24,1000,100,0,specified_relevant); //0 : prime of any size
	//init_Z_itv_list(64);
	//set_proba_Range(0,9);
	//init_Heffective_for_Z_itv_lib();

	// config variable: both positive and negative are significant
	c1_active = bdd_get_Var_bdd(bdd_prime_create_var("c1_runs", 1, 1));

	// fault variables: only positive is significant
	f1 = bdd_get_Var_bdd(bdd_prime_create_var("f1", 1, 0));
	f2 = bdd_get_Var_bdd(bdd_prime_create_var("f2", 1, 0));


	BDD c1_ft = and(c1_active,f1);
	BDD c2_ft = and(not(c1_active),f2);

	FT = or(c1_ft,c2_ft);


	bdd_prime_display(stdout,bdd_get_Prime(FT));


	return;

}

int main(void)
{

	//relevant();
	relevant_with_cst();
	return 0;
}
