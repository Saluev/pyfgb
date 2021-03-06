/*
 Jean-Charles Faugere (Jean-Charles.Faugere@inria.fr)
*/
#ifndef stamp_maple_protocol

#define stamp_maple_protocol

#include <string.h>
#include "fgb_types.h"

static void FGb_set_default_env(FGB_Comp_Desc env)
{
  env->_compute=FGB_COMPUTE_GBASIS;
  env->_nb=0;
  env->_force_elim=0; /* if force_elim=1 then return only the result of the elimination
			 (need to define a monomial ordering DRL(k1,k2) with k2>0 ) */
  env->_off=0;        /* use to select another subset of prime numbers */
  env->_index=500000; /* This is is the maximal size of the matrices generated by F4
			  you can increase this value according to your memory */
  env->_zone=0;        /* should be 0 */
  env->_memory=0;      /* should be 0 */

}

void FGb_set_default_options(FGB_Options opt)
{
  opt->_mini=1;
  opt->_elim=0;
  opt->_bk0=0;
  opt->_step0=-1;
  opt->_elim0=0;
  opt->_verb=0;
  FGb_set_default_env(&(opt->_env));
}

void FGb_set_max_matrix_size(FGB_Options opt, UI32 max_matrix_size)
{
    opt->_env._index = max_matrix_size;
}


static char* maple_protocol_to_string(FGB_Comp_Desc env)
{
  switch (env->_compute)
    {
    case FGB_COMPUTE_GBASIS:
      return "FGB_COMPUTE_GBASIS";
    case FGB_COMPUTE_RRFORM:
      return "FGB_COMPUTE_RRFORM";
    case FGB_COMPUTE_RRFORM_SQFR:
      return "FGB_COMPUTE_RRFORM_SQFR";
    case FGB_COMPUTE_MINPOLY:
      return "FGB_COMPUTE_MINPOLY";
    case FGB_COMPUTE_MINPOLY_SQFR:
      return "FGB_COMPUTE_MINPOLY_SQFR";
    case FGB_COMPUTE_GBASIS_NF:
      return "FGB_COMPUTE_GBASIS_NF";
    case FGB_COMPUTE_GBASIS_NF_RECOMPUTE:
      return "FGB_COMPUTE_GBASIS_NF_RECOMPUTE";
    case FGB_COMPUTE_RADICAL_STRATEG1:
      return "FGB_COMPUTE_RADICAL_STRATEG1";
    case FGB_COMPUTE_RADICAL_STRATEG2:
      return "FGB_COMPUTE_RADICAL_STRATEG2";
    case FGB_COMPUTE_NOP:
      return "FGB_COMPUTE_NOP";
    case FGB_COMPUTE_GBASIS_MULTI:
      return "FGB_COMPUTE_GBASIS_MULTI";
    case FGB_COMPUTE_MATRIXN:
      return "FGB_COMPUTE_MATRIXN";
    default:
      return "FGB_???";
    }
}

static FGB_TYP_COMPUTE string_to_maple_protocol(char* s)
{
  if (strcmp(s,"FGB_COMPUTE_RRFORM") EQ 0)
    return FGB_COMPUTE_RRFORM;
  if (strcmp(s,"FGB_COMPUTE_MINPOLY") EQ 0)
    return FGB_COMPUTE_MINPOLY;
  if (strcmp(s,"FGB_COMPUTE_MINPOLY_SQFR") EQ 0)
    return FGB_COMPUTE_MINPOLY_SQFR;
  if (strcmp(s,"FGB_COMPUTE_RRFORM_SQFR") EQ 0)
    return FGB_COMPUTE_RRFORM_SQFR;
  if (strcmp(s,"FGB_COMPUTE_GBASIS_NF") EQ 0)
    return FGB_COMPUTE_GBASIS_NF;
  if (strcmp(s,"FGB_COMPUTE_GBASIS_NF_RECOMPUTE") EQ 0)
    return FGB_COMPUTE_GBASIS_NF_RECOMPUTE;
  if (strcmp(s,"FGB_COMPUTE_RADICAL_STRATEG1") EQ 0)
    return FGB_COMPUTE_RADICAL_STRATEG1;
  if (strcmp(s,"FGB_COMPUTE_RADICAL_STRATEG2") EQ 0)
    return FGB_COMPUTE_RADICAL_STRATEG2;
  if (strcmp(s,"FGB_COMPUTE_NOP") EQ 0)
    return FGB_COMPUTE_NOP;
  if (strcmp(s,"FGB_COMPUTE_GBASIS_MULTI") EQ 0)
    return FGB_COMPUTE_GBASIS_MULTI;
  if (strcmp(s,"FGB_COMPUTE_MATRIXN") EQ 0)
    return FGB_COMPUTE_MATRIXN;
  return FGB_COMPUTE_GBASIS;
}
#endif /* ndef stamp_maple_protocol */
