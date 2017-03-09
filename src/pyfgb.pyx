from libc.stdlib cimport malloc, free

cimport numpy as np

from sympy import Poly

cdef extern from "fgb_int.h":
    ctypedef np.uint32_t UI32
    ctypedef np.int32_t I32
    ctypedef int Boolean
    ctypedef void* Dpol
    ctypedef void* Dpol_INT
    ctypedef int FGB_Comp_Desc
    ctypedef struct SFGB_Options:
        pass
    ctypedef SFGB_Options* FGB_Options
    ctypedef int Expos

    ctypedef void* mpz_ptr

    void FGb_int_enter_INT()
    void FGb_int_exit_INT()
    void init_FGb_Integers()
    void FGb_int_PowerSet(UI32 bl1, UI32 bl2, char** liste)
    void threads_FGb(int)
    void FGb_reset_memory();

    void FGb_set_default_options(FGB_Options opt)
    void FGb_set_max_matrix_size(FGB_Options opt, UI32 max_matrix_size)

    #String FGb_int_alloc(UI32 n)
    void FGb_int_reset_memory()
    #void FGb_int_init_urgent(UI32 szDom, UI32 szNNI, String expos, UI32 maxi_FGb_BASE, Boolean rec)
    #void FGb_int_init(Boolean wp, Boolean wp2, Boolean wc, FILE* file)
    Dpol FGb_int_creat_poly(UI32 n)
    Expos FGb_int_assign_expos(I32* buf, I32 n)
    void FGb_int_PowerSet(UI32 bl1, UI32 bl2, char** liste)
    void FGb_int_reset_expos(UI32 bl1, UI32 bl2, char** liste)
    void threads_FGb(int t)
    void init_FGb_Integers()
    void FGb_int_reset_coeffs(UI32 n)
    void FGb_int_set_coeff_raw(Dpol p, UI32 i0, UI32* buf, UI32 sz)
    mpz_ptr* FGb_int_export_poly_INT_gmp(I32 n, I32 m, I32* E, Dpol_INT p)
    int FGb_int_export_poly_INT_gmp2(I32 n, I32 m, mpz_ptr* res, I32* E, Dpol_INT p)

    void init_FGb_Modp(const int p)
    void FGb_int_reset_coeffs(UI32 n, UI32* p)
    void FGb_int_set_coeff_I32(Dpol p, UI32 i0, I32 buf)
    void FGb_int_set_expos_d(Dpol p, UI32 i0, Expos buf)
    void FGb_int_full_sort_poly(Dpol p)
    I32 FGb_int_export_poly(I32 n, I32 m, I32* E, I32* P, Dpol p)
    #endif /*  LIBMODE EQ 2 */
    UI32 FGb_int_groebner(Dpol* p, UI32 n, Dpol* q, Boolean mini, UI32 elim, double* t0, const UI32 bk0, const UI32 pas0, const Boolean elim0, FGB_Comp_Desc env)
    UI32 FGb_int_fgb(Dpol* p, UI32 np, Dpol* q, UI32 nq, double* t0, FGB_Options options)
    UI32 FGb_int_hilbert(Dpol* p, const UI32 n_orig, Dpol* q, Boolean mini, UI32 elim, double* t0, UI32 bk0, UI32 pas0, Boolean elim0)
    UI32 FGb_int_nb_terms(Dpol p)
    void FGb_int_set_expos2(Dpol p, UI32 i0, I32* e, const UI32 nb)
    void FGb_int_full_sort_poly2(Dpol p)
    I32 FGb_int_export_poly_INT(I32 n, I32 m, I32* E, UI32* P, UI32* Plim, Dpol p, UI32* B)

cdef extern from "fgb_gmp.h":
    ctypedef int mpz_t
    int mpz_init_set_str(mpz_t dest_integer, char *src_cstring, int base)
    void FGb_int_set_coeff_gmp(Dpol_INT p, UI32 i0, mpz_t x)


class FGB(object):

    def __init__(self, threads=1):
        threads_FGb(threads)

    def groebner(self, polynomials, max_matrix_size=2000000):
        FGb_int_enter_INT()
        init_FGb_Integers()

        variables = set()
        for polynomial in polynomials:
            variables.update(polynomial.free_symbols)
        # now fixing some particular order of variables
        variables = list(variables)
        cdef mpz_t mpz_coef
        cdef int num_variables = len(variables)

        max_degree = max(Poly(polynomial, variables).total_degree() for polynomial in polynomials)
        print("Got %d polynomials with total of %d variables and max total degree %d." % (len(polynomials), num_variables, max_degree))

        cdef char** variable_names = <char**>malloc(num_variables * sizeof(char*))
        for v, variable in enumerate(variables):
            variable_names[v] = variable.name
        FGb_int_PowerSet(num_variables, 0, variable_names)

        cdef I32* powers_buff = <I32*>malloc(num_variables * sizeof(I32));

        cdef int FGb_MAXI_BASE = 10000
        cdef Dpol* fgb_polynomials = <Dpol*>malloc(len(polynomials) * sizeof(Dpol));
        cdef Dpol* output_basis = <Dpol*>malloc(FGb_MAXI_BASE * sizeof(Dpol))

        for fgbp_idx, polynomial in enumerate(polynomials):
            monomials = Poly(polynomial, variables).as_dict()
            num_monomials = len(monomials)
            #print("Creating new polynomial with %d monomial(s)..." % num_monomials)
            fgb_polynomials[fgbp_idx] = FGb_int_creat_poly(num_monomials)
            for monomial_idx, (powers, coef) in enumerate(monomials.items()):
                for k, power in enumerate(powers):
                    powers_buff[k] = power
                # add monomial term
                FGb_int_set_expos2(fgb_polynomials[fgbp_idx], monomial_idx, powers_buff, num_variables)
                str_coef = str(coef)
                mpz_init_set_str(mpz_coef, str_coef, 10)
                # set monomial term coefficient
                FGb_int_set_coeff_gmp(fgb_polynomials[fgbp_idx], monomial_idx, mpz_coef)
            # sort polynomial with respect to chosen ordering (grevlex)
            FGb_int_full_sort_poly2(fgb_polynomials[fgbp_idx])

        cdef SFGB_Options fgb_options
        FGb_set_default_options(&fgb_options)
        FGb_set_max_matrix_size(&fgb_options, max_matrix_size)

        cdef double time
        nb = FGb_int_fgb(fgb_polynomials, len(polynomials), output_basis, FGb_MAXI_BASE, &time, &fgb_options);

        free(powers_buff)
        free(fgb_polynomials)
        free(output_basis)

        FGb_int_reset_memory()
        FGb_int_exit_INT()

        return nb
