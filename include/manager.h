#if (not defined(see_manager_h)) || (not defined(see_inside_manager_h))
#if (not defined(see_manager_h))

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


typedef char* local_String;
#endif /*  (not defined(see_manager_h)) */

#ifdef IMPLEMENTED
#if (not defined(see_inside_manager_h))
#define PERMISSION 0600

#if defined(__WINNT__)
#define NO_SHARE_MEMORY
#endif /*  defined(__WINNT__) */

#ifndef NO_SHARE_MEMORY
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/sem.h>
#endif /* def NO_SHARE_MEMORY */

Any creat_share(char *file,UI32 sz,Any ad)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait creat_share\n");
#else
  extern FILE* ouvrir(Cste_String s,Cste_String p);
  char* res;
  char ID='F';
  key_t k;
  int shm;
  fclose(ouvrir(file,"w"));
  k=ftok(file,ID);
  if (k EQ -1)
    {
      fprintf(stderr,"File: %s\n",file);
      perror("error in ftok (creat)");
      exit(3);
    }
  shm=shmget(k,sz,IPC_CREAT|IPC_EXCL|PERMISSION);
  if (shm<0)
    {
#ifdef VERBOSITY
      perror("retry, shmget");
#endif /*  VERBOSITY */
      shm=shmget(k,sz,PERMISSION);
    }
  if (shm<0)
    {
      perror("error 2 in shmget");
      exit(2);
    }
  res=(char*)(shmat(shm,(char*)(ad),0));
  if ((int)(res) EQ -1)
    {
      perror("error in shmat");
      exit(1);
    }
  return res;
#endif /* def NO_SHARE_MEMORY */
}

/* Usage:

  Info *x=creat_share("/tmp/infosys",sizeof(t),0);

  */

typedef ushort SemInt;
#ifdef __alpha
union semun {
  int val;
  struct semid_ds *buf;
  u_short *array;
};
#else /* __alpha */
#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun {
  int val;                    /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};
#endif /*  defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED) */
#endif /* def __alpha */

typedef union semun Semun;

I32 creat_semaphore(char *file,SemInt* val,UI32 n)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait creat_semaphore\n");
#else
  I32 semaphore_GB;
  char ID='F';
  Semun arg;
  key_t k=ftok(file,ID);
  if (k EQ -1)
    {
      perror("error in ftok ");
      exit(1);
    }
  semaphore_GB=semget(k,n,IPC_EXCL|IPC_CREAT|PERMISSION);
  if (semaphore_GB<0)
    {
      perror("error in creat semget");
      exit(1);
    }
  arg.array=val;
  if (semctl(semaphore_GB,0,SETALL,arg)<0)
    {
      perror("error in init semctl");
      exit(1);
    }
  return semaphore_GB;
#endif /* def NO_SHARE_MEMORY */
}

/*
  Usage:
      SemInt val[2] = {0,0};
      creer_semaphore("toto",val,2);
    */

Any attach_share(char *file,Any ad)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait creat_share\n");
#else
  char* res;
  char ID='F';
  key_t k=ftok(file,ID);
  int shm;
  if (k EQ -1)
    {
      fprintf(stderr,"File: %s\n",file);
      perror("error in ftok (attach)");
      exit(3);
    }
#define PERMISSION 0600
  shm=shmget(k,0,PERMISSION);
  if (shm<0)
    {
      perror("error 2 in shmget");
      exit(2);
    }
  res=(char*)(shmat(shm,(char*)(ad),0));
  if ((int)(res) EQ -1)
    {
      perror("error in shmat");
      exit(1);
    }
  return res;
#endif /* def NO_SHARE_MEMORY */
}

/* Usage:

  Info *t=attach_share("/tmp/infosys",0);
  printf(".x=%d .y=%d\n",t->x,t->y);

  */

I32 attach_semaphore(char *file,unsigned n)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait attach_semaphore\n");
#else
  char ID='F';
  I32 semaphore_GB;
  key_t k=ftok(file,ID);
  if (k EQ -1)
    {
      perror("error in ftok ");
      exit(1);
    }
  semaphore_GB=semget(k,n,PERMISSION);
  if (semaphore_GB<0)
    {
      perror("error in semget");
      exit(1);
    }
  return semaphore_GB;
#endif /* def NO_SHARE_MEMORY */
}

/*
  Usage:
    attach_semaphore("toto",2);
    */

void delete_share(char *file)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait delete_share\n");
#else
  char* res;
  char ID='F';
  key_t k=ftok(file,ID);
  int shm;
  if (k EQ -1)
    {
      fprintf(stderr,"File: %s\n",file);
      perror("error in ftok (delete)");
      exit(3);
    }
#define PERMISSION 0600
  shm=shmget(k,0,PERMISSION);

  if (shm<0)
    {
      perror("error 2 in shmget");
      exit(2);
    }
  if (shmctl(shm,IPC_RMID,NULL)<0)
    {
      perror("shmctl in delete_share");
      exit(4);
    }
  if (unlink(file)<0)
    {
      fprintf(stderr,"File: %s",file);
      perror("unlink");
    }
#endif /* def NO_SHARE_MEMORY */
}

/* Usage:
  delete_share("/tmp/infosys");

  */

void delete_semaphore(char *file,UI32 n)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait delete_semaphore\n");
#else
  char* res;
  char ID='F';
  key_t k=ftok(file,ID);
  int sem;
  Semun arg;
  arg.val=0;
  if (k EQ -1)
    {
      fprintf(stderr,"File: %s\n",file);
      perror("error in ftok (delete)");
      exit(3);
    }
#define PERMISSION 0600
  sem=semget(k,n,PERMISSION);

  if (sem<0)
    {
      perror("error 2 in semget");
      exit(2);
    }
  if (semctl(sem,0,IPC_RMID,arg)<0)
    {
      perror("semctl in delete_share");
      exit(4);
    }
  if (unlink(file)<0)
    {
      fprintf(stderr,"File: %s",file);
      perror("unlink");
    }
#endif /* def NO_SHARE_MEMORY */
}

/* Usage:
    delete_share("toto",2);
  */

void detach_share(Any adr)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait creat_share\n");
#else
#if defined(__linux__) or defined(SOLARIS)
  shmdt((char *)adr);
#else
  shmdt(adr);
#endif
#endif /* def NO_SHARE_MEMORY */
}


void detach_semaphore()
{
}

void get_semaphores(I32 sem,SemInt* val,UI32 n)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait get_semaphores\n");
#else
  Semun arg;
  I32 res;
  arg.val=0;
  res=semctl(sem,0,GETVAL,arg);
  if (res<0)
    {
      perror("semctl GETALL ");
      exit(1);
    }
  {
    UI32 i;
    for(i=0;i<n;i++)
      val[i]=arg.array[i];
  }
#endif /* def NO_SHARE_MEMORY */
}

SemInt get_semaphore(I32 sem,UI32 i)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait get_semaphore\n");
#else
  Semun arg;
  I32 res;
  arg.val=0;
  res=semctl(sem,i,GETVAL,arg);
  if (res<0)
    {
      perror("semctl GETVAL ");
      exit(1);
    }
  return (SemInt)(res);
#endif /* def NO_SHARE_MEMORY */
}


void set_semaphores(I32 sem,SemInt* val,UI32 n)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait set_semaphores\n");
#else
  Semun arg;
  arg.array=val;
  if (semctl(sem,0,SETALL,arg)<0)
    {
      perror("semctl SETALL ");
      exit(1);
    }
#endif /* def NO_SHARE_MEMORY */
}

void set_semaphore(I32 sem,UI32 i,SemInt val)
{
#ifdef NO_SHARE_MEMORY
  Fatal("Pas fait set_semaphore\n");
#else
  Semun arg;
  arg.val=val;
  if (semctl(sem,i,SETVAL,arg)<0)
    {
      perror("semctl SETVAL ");
      exit(1);
    }
#endif /* def NO_SHARE_MEMORY */
}

#endif /*  (not defined(see_inside_manager_h)) */
#else
extern Any creat_share(char *file,UI32 sz,Any ad);
extern Any attach_share(char *file,Any ad);
extern void delete_share(char *file);
extern void detach_share(Any adr);
#endif /* def IMPLEMENTED */

/* Usage
  delete_share(t);
  */

#if (not defined(see_manager_h))
/* Les zones */
typedef enum {DESC_WAIT=100000, DESC_OK, DESC_NOT_ENOUGH_PRECISION, DESC_COMPILE_NNI, DESC_INCREASE_HASH, DESC_BAD_PRIME, DESC_STARTUP, DESC_INFO} Descriptor;

#define COMP_LEXICO 1
#define COMP_RR 2

typedef char String32[32];

typedef struct {
  Descriptor state;
  F32 cpu;  /* output */
  I32 memory;  /* output */
  char errorMessage[1000];  /* output */

  /* Options */
  Boolean want_mingbasis;
  UI32 vectorize;
  Boolean want_display;
  Boolean want_lift;
  Boolean want_raw_output;
  char archive_output[256];
  UI32 offset_primes;
  UI32 var_second_block;
  Boolean want_quiet;
  Boolean want_skel;
  Boolean want_pipe;
  Boolean want_immediate_display;
  char format_input[256];
  UI32 nb_input;
  Boolean want_scan;
  UI32 max_simul,index_in_simul;
#define MAX_SIMUL 131072
  UI32 simul[MAX_SIMUL];
  UI32 basPols;  /* output */
  char todo[MAX_SIMUL];
  Boolean want_outprotocol;
  char outprotocol_file[256];
  Boolean want_inprotocol;
  UI32 nb_of_primes;
  Boolean want_change;
  UI32 nbVars;  /* output */
  UI32 message;
  I32 degreeVariety;  /* output */
  UI32 nbComposantes;
  Boolean want_rr;
#define MAXI_COMPONENTS 256
  char state_components[MAXI_COMPONENTS];
  char key_manager[64];
#define MAXI_LIST_OF_FILES 32
  String32 list_of_files[MAXI_LIST_OF_FILES];
  UI32 nb_merging;
  Boolean want_elim;
  I32 dimensionVariety;  /* output */
  Boolean voidVariety;   /* output */
} Describe_F4;
#endif /*  (not defined(see_manager_h)) */

#ifdef IMPLEMENTED
#if (not defined(see_inside_manager_h))
Describe_F4* current_manager=nil;

Cste_String Descrip2String(Descriptor msg)
{
  static Cste_String all_descript[]={"DESC_WAIT", "DESC_OK", "DESC_NOT_ENOUGH_PRECISION", "DESC_COMPILE_NNI", "DESC_INCREASE_HASH", "DESC_BAD_PRIME", "DESC_STARTUP", "DESC_INFO",0};
  static Boolean deja_init_Desc2String=(Boolean)(false);
  static UI32 lim_desc=0;
  const I32 deb_desc=(I32)(DESC_WAIT);
  I32 n;
  if (not deja_init_Desc2String)
    {
      UI32 k;
      deja_init_Desc2String=(Boolean)(true);
      for(k=0;all_descript[k];k++);
      lim_desc=k+deb_desc;
    }
  n=(I32)(msg);
  if (n>lim_desc)
    return "??? ext";
  if (n<deb_desc)
    return "??? in";
  return all_descript[n-deb_desc];
}

void display_F4(Describe_F4* m)
{
  printf("   Statut: %s\n",Descrip2String(m->state));
  printf("   CPU: %.2f sec\n",m->cpu);
  printf("   Memory: %d kbytes\n",m->memory);
  printf("   Message: %s\n",m->errorMessage);
}

void init_F4(Describe_F4* m)
{
  m->state=DESC_STARTUP;
  m->cpu=0;
  m->memory=0;
  m->errorMessage[0]=0;
  m->want_change=(Boolean)(false);
}

void debug_reset()
{
  current_manager->state=DESC_STARTUP;
}
#endif /*  (not defined(see_inside_manager_h)) */
#else
extern Describe_F4* current_manager;
extern Cste_String Descrip2String(Descriptor msg);
extern void init_F4(Describe_F4* m);
extern void display_F4(Describe_F4* m);
extern void debug_reset();
#endif /* def IMPLEMENTED */

#ifdef IMPLEMENTED
#if (not defined(see_inside_manager_h))
#define see_inside_manager_h
#endif /*  (not defined(see_inside_manager_h)) */
#endif /* def IMPLEMENTED */

#if (not defined(see_manager_h))
#define see_manager_h
#endif /*  (not defined(see_manager_h)) */

#endif /* ndef see_manager_h */
