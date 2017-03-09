#ifndef FGB_GMP_H
#define FGB_GMP_H

#include "gmp.h"
#include "fgb_types.h"

extern void FGb_int_set_coeff_gmp(Dpol_INT p,UI32 i0,mpz_ptr x);
extern mpz_ptr* FGb_int_export_poly_INT_gmp(I32 n,I32 m,I32* E,Dpol_INT p);
extern int FGb_int_export_poly_INT_gmp2(I32 n,I32 m,mpz_ptr* res,I32* E,Dpol_INT p);

#endif // FGB_GMP_H
