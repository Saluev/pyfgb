/*
       *** Frisco PROJECT ***
   Last Revision: 23/7/98
   Author: Jean-Charles Faugere
           Fabrice Rouillier
   Version SCCS: 4.%I%  %W%  %G%
*/

/* Dynamic Protocol by Fabrice Rouillier */
/* test sur l'entier 1+2*2^8+3*2^16+4*2^24=67305985 puis
   dans le cas ou la machine est 64 bits, test sur l'entier
   1+2*2^8+3*2^16+4*2^24+5*2^32+6*2^40+7*2^48+8*2^56=578437695752307201
   le resultat donne la facon dont sont arranges les octets 
sparc (vallin) :  [4,3,2,1]
sgi (hermite)  :  [4,3,2,1]
alpha (javelet) : [1,2,3,4]
*/

#define package2(p,m)  p ## _ ## m
#define package(p,m)  package2(p,m)
#define m_UI16_0 package(PACKAGE_NAME,m_UI16_0)
#define m_UI16_1 package(PACKAGE_NAME,m_UI16_1)

#define m_UI32_0 package(PACKAGE_NAME,m_UI32_0)
#define m_UI32_1 package(PACKAGE_NAME,m_UI32_1)
#define m_UI32_2 package(PACKAGE_NAME,m_UI32_2)
#define m_UI32_3 package(PACKAGE_NAME,m_UI32_3)

extern void test_protocol(void);

typedef char B8;
typedef unsigned long int UILong;

#define bitSizeOfB8 4
#define defaultSizeOfLong 4
#define sizeOfUI32 4
#define sizeOfUI16 2

#define test64Hi 134678021
#define pow2_16 65536

extern B8 sizeOfLong;

#define p_UI16_1 2
#define p_UI16_2 1

#define p_UI32_1 4
#define p_UI32_2 3
#define p_UI32_3 2
#define p_UI32_4 1

/* low part */
#define p_UI64_1 4
#define p_UI64_2 3
#define p_UI64_3 2
#define p_UI64_4 1
/* hi part */
#define p_UI64_5 8
#define p_UI64_6 7
#define p_UI64_7 6
#define p_UI64_8 5

/* place de l'octet _i  du codage 
   machine sans le codage du protocol 
*/
extern B8 m_UI16_0;
extern B8 m_UI16_1;

extern B8 m_UI32_0;
extern B8 m_UI32_1;
extern B8 m_UI32_2;
extern B8 m_UI32_3;

extern void init_protocol_16();
extern void init_protocol_32();

extern UILong test64;
extern void reinit_64();
extern void init_protocol_64();

extern void C__initProtocol();

INLINE  void conv_machine_2_prot_UI8(String p,Cste_String m)
{
  p[0]=m[0];
}

INLINE  void reorder_UI8(String m)
{
}

INLINE void conv_machine_2_prot_UI16(String p,Cste_String m)
{
  p[m_UI16_0]=m[0];
  p[m_UI16_1]=m[1];
}

INLINE  void reorder_UI16(String m)
{
  B8 m0=m[m_UI16_0];
  B8 m1=m[m_UI16_1];
  m[0]=m0;
  m[1]=m1;
}

INLINE  void conv_machine_2_prot_UI32(String p,Cste_String m)
{
  p[m_UI32_0]=m[0];
  p[m_UI32_1]=m[1];
  p[m_UI32_2]=m[2];
  p[m_UI32_3]=m[3];  
}


INLINE  void reorder_UI32(String m)
{
  B8 m0=m[m_UI32_0];
  B8 m1=m[m_UI32_1];
  B8 m2=m[m_UI32_2];
  B8 m3=m[m_UI32_3];
  m[0]=m0;
  m[1]=m1;
  m[2]=m2;
  m[3]=m3;
}


/* Implementation of low level functions */

#define genere_send(nb,step)\
INLINE void send_n_ ## nb ## bits(BUS bus,Cste_String buf,I32 n)\
{\
  I32 i;\
  if (VERB_BUS)\
  {\
    fprintf(stderr,"Send %d bits ",nb);\
    for(i=0;i<n;i+=step)\
      {\
	I32 k;\
	I ## nb x;\
	String s=(String)(&x);\
	for(k=0;k<step;k++)\
	  s[k]=buf[i+k];\
	k=(I32)(x);\
        if (step EQ 4)\
          fprintf(stderr,"%d(%s) ",k,C__debugMessages((Messages)(k)));\
        else\
	  fprintf(stderr,"%d ",k);\
      }\
    fprintf(stderr,"\n");\
  }\
  i=0;\
  while(i<n)\
    {\
      if ((bus->x__out)<(GB_BUFF_SIZE-step))\
	{\
	  conv_machine_2_prot_UI ## nb(&(bus->__out[bus->x__out]),&(buf[i]));\
	  bus->x__out+=step;\
	  i+=step;\
	}\
      else\
	C__flush(bus);\
    }\
}

genere_send(32,4)
genere_send(16,2)
genere_send(8,1)

#undef genere_send

INLINE void send_n_64bits(BUS bus,Cste_String buf,I32 n)
{
#ifdef __GNUC__
  UI64* t=(UI64*)(buf),i;
  UI32 tmp[2];
  n/=8;
  for(i=0;i<n;i++)
    {
      UI64 x=t[i];
      UI64 y=x%4294967296LLU;
      x/=4294967296LLU;
      tmp[0]=(UI32)(x);
      tmp[1]=(UI32)(y);
      send_n_32bits(bus,(String)(&tmp[0]),8);
    }
#else
  Fatal("send_n_64bits not done\n");
#endif /* def __GNUC__ */
}

extern void internal_read(BUS bus,String buf,I32 n);

#define genere_read(nb,step)\
INLINE void read_n_ ## nb ## bits(BUS bus,String buf,I32 n)\
{\
  I32 i;\
  internal_read(bus,buf,n);\
  for(i=0;i<n;i+=step)\
    reorder_UI ## nb(buf+i);\
  if (VERB_BUS)\
  {\
    fprintf(stderr,"Read %d bits ",nb);\
    for(i=0;i<n;i+=step)\
      {\
	I32 k;\
	I ## nb x;\
	String s=(String)(&x);\
	for(k=0;k<step;k++)\
	  s[k]=buf[i+k];\
	k=(I32)(x);\
        if (step EQ 4)\
          fprintf(stderr,"%d(%s) ",k,C__debugMessages((Messages)(k)));\
        else\
	  fprintf(stderr,"%d ",k);\
      }\
    fprintf(stderr,"\n");\
  }\
}

genere_read(32,4)
genere_read(16,2)
genere_read(8,1)

#undef genere_read

INLINE void read_n_64bits(BUS bus,String buf,I32 n)
{
#ifdef __GNUC__
  UI64* t=(UI64*)(buf),i;
  UI32 tmp[2];
  n/=8;
  for(i=0;i<n;i++)
    {
      read_n_32bits(bus,(String)(&tmp[0]),8);
      {
	const UI64 x=(UI64)(tmp[0]);
	const UI64 y=(UI64)(tmp[1]);
	t[i]=x*4294967296LLU+y;
      }
    }
#else
  Fatal("read_n_64bits not done\n");
#endif /* def __GNUC__ */
}

