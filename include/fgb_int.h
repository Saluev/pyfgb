#ifndef FGB_INT_H
#define FGB_INT_H

#define LIBMODE 2

#include "fgb_types.h"
#include "call_fgb.h"

extern void FGb_set_default_options(FGB_Options opt);
extern void FGb_set_max_matrix_size(FGB_Options opt, UI32 max_matrix_size);

#endif // FGB_INT_H
