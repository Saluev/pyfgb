












 
             C__int   C__open (              BUS , String , String , String ) ;
                                  void   C__kill (              BUS ) ;
                                  void   C__flush (             BUS ) ;
                             String   C__debugMessages (     Messages ) ;
                    void   C__sendDomainGDMP (    BUS , C__int , C__int ) ;
                    void   C__sendInt (           BUS , C__int , C__int ) ;
                                  C__int   C__receiveInt (        BUS ) ;
                                  Messages   C__receiveMessages (   BUS ) ;
                         C__int   C__sendMessages (      BUS , Messages ) ;
                           void   C__sendString (        BUS , String ) ;
    void   C__sendExpos (         BUS ,  C__int *  , C__int ) ;
    void   C__receiveExpos (      BUS ,  C__int *  , C__int ) ;
                                  C__float   C__receiveFloat (      BUS ) ;
    C__int   C__receiveInteger (    BUS ,  C__int *  , C__int ) ;
                    String   C__receiveString (     BUS , String , C__int ) ;
    void   C__sendInteger (       BUS ,  C__int *  , C__int ) ;
    void   C__sendPOSSOInteger (  BUS ,  C__int *  , C__int ) ;
                    void   C__reopen (            BUS , C__int , String ) ;
                         void   C__sendFLoat (         BUS , C__float ) ;
                                           void   C__initProtocol (void) ;
 
