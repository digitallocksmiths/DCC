
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

u16      aInvokeCounts[16];     
u16 *    pA;
    
long lGlbVar;
const long lGlbConst;
u8         baGlbRamArray[10];
const u8   baGlbRomArray[10];
 
      u8  *       pGlbVar;
const u16 *       pGlbConst1;
      u16 * const pGlbConst2;
const u16 * const pGlbConst3;


int foo0(void) {
    return 0;
}

int foo1(int a) {
    a=1;
    return 1;
}

int foo2(int a, char b) {
    a=1;
    b=2;
    return 2;
}

int foo3(long a, int b, char *c) {
    int l1;
    a=1;
    b=2;
    c=3;
    l1=4;
 
    return 3;
}

int foo4(void) {
    int a,b,c;
    a=1;
    b=2;
    c=3;
    return foo3(a,b,c);
}


void    foo5(long a, int b, char *c, long d) {
    int l1;
    char l2;
    
    a=1;
    b=2;
    c=3;
    d=4;
    l1=5;
    l2=6;

//    int a,b;
//    a = foo0();
//    if (a == 1) {
//         b = foo1(a);
//    }
//    else {
//        b = foo1(a) + foo2(1,2);
//    }
//    
    foo2((char)foo3(1,2,3), foo4());
    
}

