/* Interface types */
typedef int C__int;
typedef float C__float;

/* Protocol with Gb and RS */

typedef enum {
#include "PROTOCOL_GB.h"
,
#include "PROTOCOL_RS.H"
} Messages;

#define TIMEOUT_BUS 5

#ifndef VERB_BUS
#define VERB_BUS 0
#endif /* ndef VERB_BUS */

#define GB_BUFF_SIZE 4096

#include "callgb.h"
#define BUS_def

/* Exported functions */
#define C__open  C_open
#define C__kill  C_kill
#define C__killAll  C_killAll
#define C__flush C_flush
#define C__sendDomainGDMP C_sendDomainGDMP
#define C__sendMessages C_sendMessages
#define C__sendInt C_sendInt
#define C__receiveMessages C_receiveMessages
#define C__receiveInt C_receiveInt
#define C__receiveExpos C_receiveExpos
#define C__sendExpos C_sendExpos
#define C__receiveFloat C_receiveFloat
#define C__sendInteger C_sendInteger
#define C__receiveInteger C_receiveInteger
#define C__sendPOSSOInteger C_sendPOSSOInteger
#define C__sendString C_sendString
#define C__receiveString C_receiveString
#define C__initProtocol C_initProtocol
#define C__debugMessages C_debugMessages

/* Exported functions */
#include "signature.h"

extern void sendMessage(BUS bus,Messages msg);
extern void open_WBUS(BUS bus,String file);
extern void wait_BUS(BUS bus);

#include "callgb_dynamic_protocol.h"


INLINE void send_n_32bits_ptr(BUS bus,I32* buf,I32 n)
{
  send_n_32bits(bus,(char*)(buf),n*sizeof(I32));
}

INLINE void send_n_u32bits_ptr(BUS bus,UI32* buf,I32 n)
{
  send_n_32bits(bus,(char*)(buf),n*sizeof(UI32));
}

INLINE void read_n_32bits_ptr(BUS bus,I32* buf,I32 n)
{
  read_n_32bits(bus,(char*)(buf),n*sizeof(I32));
}

INLINE void read_n_u32bits_ptr(BUS bus,UI32* buf,I32 n)
{
  read_n_32bits(bus,(char*)(buf),n*sizeof(UI32));
}

INLINE void send_n_bits(BUS bus,Cste_String s,UI32 sz,UI32 n)
{
  switch(sz) {
  case 1:
    send_n_8bits(bus,s,n);
    break;
  case 2:
    send_n_16bits(bus,s,n);
    break;
  case 4:
    send_n_32bits(bus,s,n);
    break;
  default:
    Fatal("send_n_bits for object of size %u not yet available\n",sz);
    break;
  }
}

INLINE void send_n_bits_ptr(BUS bus,void* s0,UI32 sz,UI32 n)
{
  String s=(String)(s0);
  switch(sz) {
  case 1:
    send_n_8bits(bus,s,n);
    break;
  case 2:
    send_n_16bits(bus,s,n*2);
    break;
  case 4:
    send_n_32bits(bus,s,n*4);
    break;
  default:
    Fatal("send_n_bits for object of size %u not yet available\n",sz);
    break;
  }
}

INLINE void read_n_bits(BUS bus,String s,UI32 sz,UI32 n)
{
  switch(sz) {
  case 1:
    read_n_8bits(bus,s,n);
    break;
  case 2:
    read_n_16bits(bus,s,n);
    break;
  case 4:
    read_n_32bits(bus,s,n);
    break;
  default:
    Fatal("read_n_bits for object of size %u not yet available\n",sz);
    break;
  }
}

INLINE void read_n_bits_ptr(BUS bus,void* s0,UI32 sz,UI32 n)
{
  String s=(String)(s0);
  switch(sz) {
  case 1:
    read_n_8bits(bus,s,n);
    break;
  case 2:
    read_n_16bits(bus,s,n*2);
    break;
  case 4:
    read_n_32bits(bus,s,n*4);
    break;
  default:
    Fatal("read_n_bits for object of size %u not yet available\n",sz);
    break;
  }
}
