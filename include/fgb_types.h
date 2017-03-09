#ifndef FGB_TYPES_H
#define FGB_TYPES_H

#include "style.h"

typedef void* Expos;
typedef void* Dpol;
typedef Dpol Dpol_INT;

typedef enum {
  FGB_COMPUTE_GBASIS=1,
  FGB_COMPUTE_RRFORM,
  FGB_COMPUTE_RRFORM_SQFR,
  FGB_COMPUTE_MINPOLY,
  FGB_COMPUTE_MINPOLY_SQFR,
  FGB_COMPUTE_GBASIS_NF,
  FGB_COMPUTE_GBASIS_NF_RECOMPUTE,
  FGB_COMPUTE_RADICAL_STRATEG1,
  FGB_COMPUTE_RADICAL_STRATEG2,
  FGB_COMPUTE_NOP,
  FGB_COMPUTE_GBASIS_MULTI,
  FGB_COMPUTE_MATRIXN
} FGB_TYP_COMPUTE;

typedef struct sFGB_Comp_Desc
{
  FGB_TYP_COMPUTE _compute;
  I32 _nb;
  I32 _force_elim;
  UI32 _off;
  UI32 _index;
  UI32 _zone;
  UI32 _memory;

  I32 _nb2;
  I32 _force_elim2;
  UI32 _bk2;
  I32 _aggressive2;
  I32 _dlim;
  I32 _skip;
} SFGB_Comp_Desc;

typedef SFGB_Comp_Desc *FGB_Comp_Desc;

typedef struct sFGB_Options
{
  SFGB_Comp_Desc _env;
  Boolean _mini;
  UI32 _elim;
  UI32 _bk0;
  UI32 _step0;
  Boolean _elim0;
  I32 _verb;
} SFGB_Options;

typedef SFGB_Options *FGB_Options;

#endif // FGB_TYPES_H
