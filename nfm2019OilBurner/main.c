/*
 * main.c
 *
 *  Created on: 23 dec. 2018
 *      Authors:
 *      Nicolas Rapin
 *      Boutheina Bannour
 *
 */


#include "Z_itv.h"
#include "bct.h"

#define RESERVERN(x,y) (y *) calloc(x,sizeof(y));

void test_oilburner2pumps_subst_loop_detect()
{

	FILE * out, * out2;

	BDD FT, elec, c_lowLvl6, c_lowLvl3, c_lowLvl1, maint, air, regul, pp_fm, bp_fm;

	diconode * cs_lowLvl6, *cs_lowLvl3, * cs_lowLvl1;

	BDD cc_oil1_in, cc_oil2_in, pp_oil_out, bp_oil_out, pp_elec_in, bp_elec_in;
	BDD t_fm;

	BDD * S;
	NAT * var_tab;
	NAT i, j = 0;
	NAT at_least_one_subst;
	NAT bool_vars;

	out = fopen("bdd_graph.dot","w");

#ifdef PRIME
	out2 = fopen("bdd_cut_set.dot","w");
#endif


	bdd_prime_initHash(33,1000,1000,0,all_relevant); //0 : mcs of any size
	bool_vars = 33;
	init_Z_itv_list(64);
	set_proba_Range(0,1000);
	init_Heffective_for_Z_itv_lib();

	Var* v_elec = bdd_prime_create_var("elec", 1, 1);
	set_Var_Proba(v_elec, 0.00044);
	elec = bdd_get_Var_bdd(v_elec);
	pp_elec_in = bdd_get_Var_bdd(bdd_prime_create_var("pp.elec_in", 1, 1));
	bp_elec_in = bdd_get_Var_bdd(bdd_prime_create_var("bp.elec_in", 1, 1));
	Var* v_maint = bdd_prime_create_var("maint", 1, 1);
	set_Var_Proba(v_maint, 0.5);
	maint = bdd_get_Var_bdd(v_maint);
	Var* v_air = bdd_prime_create_var("air", 1, 1);
	set_Var_Proba(v_air, 0.00044);
	air = bdd_get_Var_bdd(v_air);
	Var* v_pp_fm = bdd_prime_create_var("pp.fm", 1, 1);
	set_Var_Proba(v_pp_fm, 0.00309);
	pp_fm = bdd_get_Var_bdd(v_pp_fm);
	Var * v_bp_fm = bdd_prime_create_var("bp.fm", 1, 1);
	set_Var_Proba(v_bp_fm, 0.00309);
	bp_fm = bdd_get_Var_bdd(v_bp_fm);
	cc_oil1_in = bdd_get_Var_bdd(bdd_prime_create_var("ch.oil1_in", 1, 1));
	cc_oil2_in = bdd_get_Var_bdd(bdd_prime_create_var("ch.oil2_in", 1, 1));
	Var * v_t_fm = bdd_prime_create_var("t.fm", 1, 1);
	set_Var_Proba(v_t_fm, 0.000117);
	t_fm = bdd_get_Var_bdd(v_t_fm);

	pp_oil_out = bdd_get_Var_bdd(bdd_prime_create_var("pp.oil_out", 1, 1));
	bp_oil_out = bdd_get_Var_bdd(bdd_prime_create_var("bp.oil_out", 1, 1));

	regul = bdd_get_Var_bdd(bdd_prime_create_var("regul", 1, 1));

	Z_itv_list * l_lowLvl1 = new_Z_itv_list();
	Z_itv_list * l_lowLvl6 = new_Z_itv_list();
	Z_itv_list * l_lowLvl3 = new_Z_itv_list();

	Z_itv_list_pushback(l_lowLvl1, 0,0);
	Z_itv_list_pushback(l_lowLvl6,0,5);
	Z_itv_list_pushback(l_lowLvl3,0,2);



	cs_lowLvl1  = Z_itv_list_to_bdd(l_lowLvl1);
	cs_lowLvl6 = Z_itv_list_to_bdd(l_lowLvl6);
	cs_lowLvl3 = Z_itv_list_to_bdd(l_lowLvl3);

	c_lowLvl1 = bdd_external_modif_Hash(cs_lowLvl1);
	c_lowLvl6 = bdd_external_modif_Hash(cs_lowLvl6);
	c_lowLvl3 = bdd_external_modif_Hash(cs_lowLvl3);

	cc_oil2_in = or(bp_fm, bp_oil_out);

	S = RESERVERN(bool_vars,BDD);
	var_tab = RESERVERN(bool_vars,NAT);

	for(i = 0 ; i < bool_vars ; i++)
	{
		S[i] = BDD_UNDEF;
	}

	S[get_var_index(regul)] = or(and(not(maint),cc_oil1_in),and(maint,cc_oil2_in));
	S[get_var_index(pp_elec_in)] = or(t_fm,elec);
	S[get_var_index(bp_elec_in)] = or(t_fm,elec);
	S[get_var_index(cc_oil1_in)] = pp_oil_out;
	S[get_var_index(pp_oil_out)] = or(pp_fm,or(pp_elec_in,c_lowLvl6));
	S[get_var_index(bp_oil_out)] = or(bp_fm,or(bp_elec_in,c_lowLvl3));

	FT = or(air, or(c_lowLvl1,regul));

	bct * FT_Bct = new_bct();
	bct_insertion(&FT_Bct,FT);

	while (1)
	{
		bdd_get_all_var_index(FT, var_tab);

		at_least_one_subst = 0;
		for(i = 0 ; i < bool_vars ; i++)
		{
			if (var_tab[i] && S[i] != BDD_UNDEF)
			{
				FT = bdd_subst_var_by_bdd(FT,S[i],i);
				at_least_one_subst = 1;
				j++;

				// look for FT in the bct
				if (bct_search(&FT_Bct,FT))
				{
					printf("\n The FT has a loop ! Exit ! \n");
					goto fin;
				}

				bct_insertion(&FT_Bct, FT);
			}
		}

		if (! at_least_one_subst)
			break;

	}

	//  Returned results:
	//	Reference interval (proba): [0,1000]
	//	Primes:
	//	{
	//	  { [0,2] }: 0.002997
	//	  {  t.fm }: 0.000117
	//	  { [3,5],  bp.fm }: 9.26074e-006
	//	  {  bp.fm,  pp.fm }: 9.5481e-006
	//	  {  air }: 0.00044
	//	  { [3,5], ~maint }: 0.0014985
	//	  {  pp.fm, ~maint }: 0.001545
	//	  {  bp.fm,  maint }: 0.001545
	//	  {  elec }: 0.00044
	//	}

	printf("\n\nFT: %d, prime: %d\n\n",FT,bdd_get_Prime(FT));
	bdd_toDot(out,FT);
	fclose(out);

#ifdef PRIME
	 bdd_prime_display_proba(stdout,bdd_get_Prime(FT));
	bdd_toDot(out2,bdd_get_Prime(FT));
	fclose(out2);
#endif

	fin:

	return;

}


#define LIST_TEST_ADD


int main(void)
{
	test_oilburner2pumps_subst_loop_detect();
	return 0;
}
