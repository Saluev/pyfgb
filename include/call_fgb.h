/*
 Jean-Charles Faugere (Jean-Charles.Faugere@inria.fr)
*/
#include <stdio.h>
#include <stdlib.h>

#include "call_fgb_basic.h"

#define MAPLE_FGB_BIGNNI 2
#ifndef LIBMODE
#define LIBMODE 2
#endif /* ndef LIBMODE */

#if LIBMODE==2
#define FGB(fn) FGb_int_ ## fn
#else
#define FGB(fn) FGb_ ## fn
#endif /*  LIBMODE==2 */

#include "fgb_types.h"

extern String FGB(alloc)(UI32 n);
extern void FGB(reset_memory)();
extern void FGB(init_urgent)(UI32 szDom,UI32 szNNI,String expos,UI32 maxi_FGb_BASE,Boolean rec);
extern void FGB(init)(Boolean wp,Boolean wp2,Boolean wc,FILE* file);
extern Dpol FGB(creat_poly)(UI32 n);
extern Expos FGB(assign_expos)(I32* buf,I32 n);
/* Define the monomial ordering: DRL(k1,k2) where
   k1 is the size of the 1st block of variables
   k2 is the size of the 2nd block of variables
   and vars is the name of the variable
*/
extern void FGB(PowerSet)(UI32 bl1,UI32 bl2,char** liste);
extern void FGB(reset_expos)(UI32 bl1,UI32 bl2,char** liste);
extern void threads_FGb(int t);

#if LIBMODE EQ 2
extern void init_FGb_Integers();
extern void FGB(reset_coeffs)(UI32 n);
extern void FGB(set_coeff_raw)(Dpol p,UI32 i0,UI32* buf,UI32 sz);
extern void FGB(enter_INT)();
extern void FGB(exit_INT)();
#else
extern void init_FGb_Modp(const int p);
extern void FGB(reset_coeffs)(UI32 n,UI32* p);
extern void FGB(set_coeff_I32)(Dpol p,UI32 i0,I32 buf);
extern void FGB(set_expos_d)(Dpol p,UI32 i0,Expos buf);
extern void FGB(full_sort_poly)(Dpol p);
extern I32 FGB(export_poly)(I32 n,I32 m,I32* E,I32* P,Dpol p);
#endif /*  LIBMODE EQ 2 */

extern UI32 FGB(groebner)(Dpol* p,UI32 n,Dpol* q,Boolean mini,UI32 elim,double* t0,const UI32 bk0,const UI32 pas0,const Boolean elim0,FGB_Comp_Desc env);
extern UI32 FGB(fgb)(Dpol* p,UI32 np,Dpol* q,UI32 nq,double* t0,FGB_Options options);
extern UI32 FGB(hilbert)(Dpol* p,const UI32 n_orig,Dpol* q,Boolean mini,UI32 elim,double* t0,UI32 bk0,UI32 pas0,Boolean elim0);
extern UI32 FGB(nb_terms)(Dpol p);
extern void FGB(set_expos2)(Dpol p,UI32 i0,I32* e,const UI32 nb);
extern void FGB(full_sort_poly2)(Dpol p);
extern I32 FGB(export_poly_INT)(I32 n,I32 m,I32* E,UI32* P,UI32* Plim,Dpol p,UI32* B);

#if LIBMODE EQ 2
void FGb_int_saveptr();
void FGb_int_restoreptr();
#else /*  LIBMODE EQ 2 */
static void inline FGb_nop() {}
void FGb_saveptr();
void FGb_restoreptr();
#endif /*  LIBMODE EQ 2 */
