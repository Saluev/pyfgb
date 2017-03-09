#include <stdio.h>
#include <stdlib.h>

#include "fgb_prime.h"
#include "fgb_int.h"

int FGb_verb_info=0;
extern FILE* log_output;

void info_Maple(const char* s)
{
  if (FGb_verb_info)
    {
      fprintf(stderr,"%s",s);
      fflush(stderr);
    }
}

void FGb_int_error_Maple(const char* s)
{
  fprintf(stderr,"%s",s);
  fflush(stderr);
  exit(3);
}

void FGb_error_Maple(const char* s)
{
  FGb_int_error_Maple(s);
}

void init_FGb_Integers()
{
  FGb_int_init_urgent(4,2,"DRLDRL",100000,0); /* Do not change the following parameters
					      4 is the number of bytes of each coefficients
					        so the maximal prime is <2^32
					      2 is the number of bytes of each exponent :
					        it means that each exponent should be < 2^15 */
  FGb_int_init(1,1,0,log_output);/* do not change */
  FGb_int_reset_coeffs(1); /* We compute in Q[x1,x2,x3,x4,x5,x6] */
}

extern int FGb_int_internal_threads(const int tr0);
extern int FGb_internal_threads(const int tr0);
void threads_FGb(int t)
{
  I32 code=FGb_int_internal_threads(t);
  code=FGb_internal_threads(t);
}

void FGb_checkInterrupt()
{
}

void FGb_int_checkInterrupt()
{
}

void FGb_push_gmp_alloc_fnct(void *(*alloc_func) (size_t),
			     void *(*realloc_func) (void *, size_t, size_t),
			     void (*free_func) (void *, size_t))
{
}

void FGb_pop_gmp_alloc_fnct()
{
}

void init_FGb_Modp(const int p)
{
  FGb_init_urgent(2,MAPLE_FGB_BIGNNI,"DRLDRL",100000,0); /* meaning of the second parameter:
							     2 is the number of bytes of each coefficients
							     so the maximal prime is 65521<2^16
							     1 is the number of bytes of each exponent :
							     it means that each exponent should be < 128 */
  FGb_init(1,1,0,log_output); /* do not change */
  if (p>65521)
    {
      exit (1);
    }
  {
    UI32 pr[]={(UI32)(p)};
    FGb_reset_coeffs(1,pr);
  }
}

void FGb_PowerSet(UI32 bl1,UI32 bl2,char** liste)
{
  FGb_reset_expos(bl1,bl2,liste);
}

void FGb_int_PowerSet(UI32 bl1,UI32 bl2,char** liste)
{
  FGb_int_reset_expos(bl1,bl2,liste);
}

UI32 FGb_fgb(Dpol* p,UI32 np,Dpol* q,UI32 nq,double* t0,FGB_Options opt)
{
  FGb_verb_info =opt->_verb;
  return FGb_groebner(p,np,q,opt->_mini,opt->_elim,t0,opt->_bk0,opt->_step0,opt->_elim0,&(opt->_env));
}

UI32 FGb_int_fgb(Dpol* p,UI32 np,Dpol* q,UI32 nq,double* t0,FGB_Options opt)
{
  FGb_verb_info =opt->_verb;
  return FGb_int_groebner(p,np,q,opt->_mini,opt->_elim,t0,opt->_bk0,opt->_step0,opt->_elim0,&(opt->_env));
}

void FGb_int_saveptr() {
    FGb_int_enter_INT();
}

void FGb_int_restoreptr() {
    FGb_int_exit_INT();
}

void FGb_saveptr() {
}

void FGb_restoreptr() {
}
