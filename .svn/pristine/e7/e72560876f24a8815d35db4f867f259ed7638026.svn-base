//#define GENERICPOINTER      *        // generic pointer
//#define RAMPOINTER          *        // pointer to RAM
//#define ROMPOINTER          *        //            ROM/DATA
//#define NVMPOINTER          *        //            NVM/DATA
//#define CODEPOINTER         *        //            CODE/FUNCTION


typedef unsigned char    u8;
typedef unsigned short   u16;
typedef                  u8       *  pgu8;

typedef void       (* pxvoid_pgu8)(pgu8);

pgu8            pA;    
pxvoid_pgu8     xXor;               // xor copro-data reg with new.

//extern u8 baA[10];
//extern void DesSetCypherMethods(u8 bLen, pgu8 Fn, u8 bAlg);


//solo param when p0 can't be regified because of nested call....
//frame screwed up!!!


//void  SysCryptoSymSigSetup(u8 bAlg) {
//    DesSetCypherMethods(55, 6666, bAlg);
//}


extern       void foo(pgu8 x);
extern const u8   baBlob[20];

void bar(pgu8 x, u16 y) {
    
    int i = 10;
    int j = 2;
    
    i -= j;
    

        
}


//void bar(void) {
////    pA = baA;
////    xXor = foo;
//    foo(0x1111, 0x2222);
//    SysCryptoSymSigSetup(3333);
//}