
// //int a[4] = {0.5 < 0.4 , 2, 0.3+2, "hello"};
// //
// typedef enum anon{a=-2, b, _c, d='@'} Tenum;
// // 
// // Tenum e = d;
// // Tenum f = -5;
// // //Tenum g = "wibble";
// // Tenum h = 'a';
// // //Tenum i = e;
// 
// typedef struct {
//     int i;
// } TStructure;
// 
// short              s8  = -1;
// short   const     _s8  = -2;
// 
// char *             ps  = "hello";
// char * const      _ps  = "world";
// 
// char               ba[5] = "goodbye";
// char   const      _ba[5] = "mars";
// 
// char               baa[4][] = { { 5 } };
// char   const      _baa[4][] = { { 6 } };
// 
// Tenum              e   = a;
// Tenum  const      _e   = b;
// 
// TStructure         st  = { 7 };
// TStructure const  _st  = { 8 };
// 
 
//const unsigned int * const _pu16 = _u16;     // bad init


// char szString[] = "this string";

//int a1[sizeof(a *)];
//int b1[sizeof(b *)];

// a       a2;
// a _near a3;                     // bug ?? setting far/near 
// a _far  a4;

//char a[0xff];                               //    255
//char b[(char)0xff];                         //     -1
//char c[(int)(char)0xff];                    //     -1
//char d[(unsigned int)(char)0xff];           //  65535
//char e[(int)(unsigned char)0xff];             //    255

//char h[(int _far  *)(char _far  *)-1];
//char i[(int _far  *)(char _near *)-1];
//char j[(int _near *)(char _far  *)-1];
//char k[(int _near *)(char _near *)-1];

//char m[(int *)0 + 10];
          
//int v[a-1.0];
//int w[1-a];
//int x[a-c];
//int y[a-b];

//int a[(int*)10  +1];
//int b[(int *)10 +2];
//int c[(int *)10 +3.0];
//int d[(long*)10  -(long*)6];
//int e[(int *)10 -(int*)6];
//int f[(int *)10 -(int*)6.0];


//int a[sizeof(*1)];
//int b[sizeof(*(void *)1)];
//int c[sizeof(*(char *)1)];
//int d[sizeof(*(int *)1)];
//int e[sizeof(*(long *)1)];
//int f[sizeof(*(void*)1)];


//char _near * _far x;
//char _far  * _near y;
//int a[sizeof(*x)];
//int b[sizeof(x)];
//int c[sizeof(&x)];
//int d[sizeof(*y)];
//int e[sizeof(y)];
//int f[sizeof(&y)];
//int g[sizeof(&1)];


//int     f1();
//int     f1(int *,...);
//int     f1(int *x,int y);
//int     f1(int [],int);
//int     f1();
//int     f1(int*,...);
//int     f1(int *x,int y,int z);
//int     f1(int *x,char);


//int *fred(void);
//int *fred(int);
//char *fred(void);
//typedef struct str {int x;} STR;
//typedef STR *LPSTR;
//extern LPSTR *z;
//LPSTR *z;
//extern struct str **z;
//struct str **z;

//typedef int x;
//x a;
//extern x b;
//static x c;


//long double a;
//long float  a;

// int x[] = { 1,2,3 };

//typedef unsigned int WORD;
//extern int fred;
//
//typedef union x {
//    WORD Int;
//    WORD Real;
//    WORD Ident;
//} YYSTYPE;

//extern YYSTYPE yylval;
//int r;
//extern YYSTYPE yylval;

//  struct s{
//      int i;
//      char c;
//      long l;
//  };
//  typedef struct s Ts;
//  
//  struct s Vars;
//  Ts t;
//  Ts ts[5];
//  
//  typedef union u {
//      int i;
//      char c;
//      long l;
//  } Tu;
//  
//  union u Varu;
//  Tu u;
//  Tu tu[5];
//  
//  //int i1,i2,i3;
//  
//  int a0[sizeof(int)];
//  int a1[0];
//  int a2[];
//  char a3[3][4][5];
//  
//  //int a3[4] = { 30,31,32 };             // underflow OK
//  //int a4[4] = { 40,41,42,43 };          // spot on OK
//  //int a5[4] = { 50,51,52,53,54 };       // overflow
//  int a6[4] = "hello";                    // size should overflow
//  int a7[] = "hello";                     // size should not be zero!
//  
//  int b0[sizeof(a0)];
//  int b6[sizeof(a7)];
//  unsigned char b7[sizeof(a6)];
//  unsigned int  b8[sizeof(a6)];
//  unsigned long b9[sizeof(a6)];
//  
//  //char * pX = "this is px";
//  
//  int a44[4][4] = { { 40,41,42,43 }, { 50,51,52,53 }, { 60,61,62,63 }, { 70,71,72,73 } };
//  
//  int foo(char, int);



//int a[1+2];
//int b[1+n];
//int c[n+2];
//int d[n+n];


//int s;

//fred x;

//int z;

//enum {one,two, three};
//enum {a=-1, b, c='@'};
//enum {x, y=2+3*4, z};

// register int *a(void);
// int (*b)(void);
// int *(c(void));

// typedef int *z,*y;

//union fred {
//        unsigned char a;
//        unsigned      b;
//        long          c;
//        float         d;
//        double        e;
//} ;


//struct fred {
//        unsigned char a;
//        unsigned      b;
//        long          c;
//        float         d;
//        double        e;
//} ;

// struct fred z;  

//typedef int fred(void)[];
//typedef int fred[](void);
//extern  register int fred;
//static  int fred;

//typedef struct fred bert;
//extern  fart bert;

//int *foo(void);


//enum fred { one, two, three, four };
//enum jim {a,b=9,c,d };
//enum {v,w,x,y,z};

//int static typedef jim;
//char int typedef extern const volatile crap;
//char     typedef        const          crap;
//     int         extern       volatile crap;

//enum {A,B,C};

//enum fred  var1;
//enum fred  var1;


//enum fred { a,b,c=42,d };
//enum fred1  * const          var1;
//enum fred2  *       volatile var1;
//enum fred3  * const volatile var1;

// int a,*b=0,**c[][4];

//int *fred1a(),fred1b();
//int (*fred2)();
//int *(fred3());

//int *fred4[2];
//int *(*fred5)[2];
//int *(fred6[2]);

//enum e1 { a,b,c,d } full;
//typedef enum e1             back;
//enum e2             fore;
//enum e2 { e,f,g,d };
//int ;
//int fred8;

// int  * const * * volatile * var1[];

// int a;
// 
// extern int foward_fred(int, int);
// int foward_fred(int ip1, char ip2) {            // warning redefinition
// //     a= 1;
// //     if (a) 
// //         goto foo;
// //     else {
// //         a = 2;
// //     }
// // foo:
// 
//     switch (a) {
//         case 1: a=1; break;
//         case 2:
//         case 3: a=3; break;
//         case 4: a=4; break;
//         case 5: a=5; break;
//         default: a=6; break;
//     }
// 
//      for (1; 2; 3, 4) {
//          ;
//      }
//      

// int global1;
// int cA1[3];
// int cA2[3][4];
// int cA3[3][4][5];
// 
// 
// void foo(int param1) {
//     int   x;
//     cA1;
//     cA1[2];
//     cA2;
//     cA2[2];
//     cA2[2][2];
//     
//     &cA2[2][2];
// 
//     
//     //global1 = iArray[2] +6;
// }
// 


// int iG1;
// void TestScope(int iP1, int *iP2) {         // OK 24/11/19
//     int     iL1;
//     int     iL2;
//     
//     iG1;
//     iL1;
//     iL2;
//     
// 
//     {   int w,x,y,z;
//         int iL1;
//         iG1;
//         iL1;
//         iL2;
//     }
//     
//     {   int iG1;
//         int iL2;
//         int iL1;
//         iG1;
//         iL1;
//         iL2;
//         iP1;
//     }
//     
//     iG1;
//     iL1;
//     iL2;
// }
   
// int TestDecl(int iP1, int iP2, char cP3, char cP4) {
//     int a,b,c,d,e,f;
//     
//     a = 1;
//     b = a;
//     e;
//     
// }
    
// typedef struct S1 {
//     char a1;
//     int  b1;
//     long c1;
// } T1;
// 
// typedef struct S2 {
//     char a2;
//     int  b2;
//     long c2;
//     T1   t2;
//     T1   *p2;
// } T2;
// 
// T1 Glb1;
// T2 Glb2;
// T1 *P1;
// 
// void TestCompound(void) {
//     int i;
//     T1 Local1;
//     T2 Local2;
//    
//     T1 **P2;
//    
//     
//     Glb1.a1;
//     Glb1.b1;
//     Glb1.c1;
//     
//     Local1.a1; 
//     Local1.b1;
//     Local1.c1;
//     
//     Glb2.a2;
//     Glb2.b2;
//     Glb2.c2;
//     Glb2.t2.a1;
//     Glb2.t2.b1;
//     Glb2.t2.b1;
//     Glb2.t2.b1;
//     
//     P1->b1;
//     (*P2)->c1;
//     
//     //Glb2.p2.a1;
//     Glb2.p2->a1;
//     
// }
    
    //Pointer;
    //Array1;
    //Array1[1];
    
    // 0x100+2*3;       // OK - [X]
    // Simple;          // OK - [X]
    // Pointer;         // OK - [X]
    // *Pointer;        // OK - ptr([X])
    // Pointer[2];      // OK - array(X,4)
    // Array1;          // OK - X 
    // Array1[2];       // OK - array(X,4)
    // Array2;          // OK - X
    // Array2[1];       // OK - array(X,2)
    // Array2[1][2];    // OK   array(array(X,8),4)

    // &1;              // OK Error
    //(char *)1;        // OK 1
    // &(char*)1;       // OK Error
    // *(char*)1;       // OK ptr(X)
    // &*(char*)1;      // OK X
    // Array1;
    // &Array1;
    // &Array1[3];
    
    
    //(char*)Simple;    // OK cast(X)
    // *(char*)Simple;  // OK (ptr(cast(X))
    // &*(char*)Simple; // OK cast(X)
    
    // 1+2;                     // OK 3
    // Simple+2;                // OK add(X,2)
    // Simple+cSimple;          // OK add(X,c2S(Y))
    // (char)Simple+cSimple;    // OK add(S2C(X),2)
    // Pointer+2;               // OK @X+4
    // *Pointer+2;              // OK (*@X) + 4
    // *(Pointer+2);            // OK @(@X + 4)
    // Pointer[2];
    // Pointer[2]+1;
//}


 
//     for (; 2; 3) {
//         ;
//     }
//     for (; ; 3) {
//         ;
//     }
//     for (1; ; 3) {
//         ;
//     }
//     while (1) ;
//     do ; while (2);
//     
//     return 3;
//}
//int foward_fred(int iX1, char iX2);              // acceptable redeclaration.
//


// fred1(int ip1, int ip2) {                   // function.definition 2
//     int il1;
//     int il2;
//     return 1;
//  }
// 
// char fred2(int ip1, int ip2) {              // function.definition 2
//     int il1;
//     int il2;
//     return 1;
//  }

 
// K&R specifications.
// fred3() int ip1; int ip2; {                 // function.definition 3
//     int il1;
//     int il2;
//     return 1;
//  }
// 
// char fred4() int ip1; int ip2; {            // function.definition 4
//     int il1;
//     int il2;
//     return 1;
//  }
// 

// const char cRomVar = 0x12;
//       short nRamVar = 0x5678;
//       long  lRamVar = 0x12345678;  



//const char cRom    = 1;
//      char cData   = 2;
//      char cBss;
//
//const char caRom[4] = { 1,2,3,4 };
//      char caData[4] = { 5,6,7,8 };
//      char caBss[4];
// 
//const char *pbaRom[] = { "one", "two", "three" };
//      char *pbaData[] = { "four", "five", "six" };
//      char *pbaBss[];
      

//      char  *pcRamPtr;
//      short *psRamPtr;
//      long  *plRamPtr;

const char  cRom = 1;
char  cData = 1;
short sData = 2;
long  lData = 3;

char * pcBss;
const char * pcBsstoRom;
char * const pcRomtoBss;
int * * ppiData;

char  * pcData = 0x150;
short * psData = 0x160;
long  * plData = &lData;


unsigned int main(char cParam, int iParam, long lParam) {
      
        cData = cData++;
        cData = sData++;
        cData = lData++;
        cData = cParam++;
        cData = iParam++;
        cData = lParam++;
    
        cData = cData--;
        cData = sData--;
        cData = lData--;
        cData = cParam--;
        cData = iParam--;
        cData = lParam--;
        
        cData = ++cData;
        cData = ++sData;
        cData = ++lData;
        cData = ++cParam;
        cData = ++iParam;
        cData = ++lParam;
    
        cData = --cData;
        cData = --sData;
        cData = --lData;
        cData = --cParam;
        cData = --iParam;
        cData = --lParam;
    
        
        cData = *pcData++;
        sData = *psData++;
        lData = (*plData)++;
        lData = ++(*plData);
        lData = (*plData)--;
        lData = --(*plData);
    
        *pcData++ = (char)*psData++;
    
        *(char*)100   = 42;
        cData = (*(char*)100)++;
     
}


typedef char TbaA[7];

    char  cX;
    char  *pcX;
    char  * *ppcX;

    short  sX;
    short  *psX;
    short  * *ppsX;
    
    long   lX;
    long   *plX;
    long   * *pplX;
    
    TbaA   tA;  
    TbaA   *ptA;  
    TbaA   * *pptA;  

void foo(void) {
    
//  cX++;               // 8/+1
//  pcX++;              // 16/+1
//  (*pcX)++;           // 8/+1
//  (*ppcX)++;          // 16/+1
    
//ok    sX++;               // 16/+1
//ok    psX++;              // 16/+2
//ok    (*psX)++;           // 16/+1
//ok    (*ppsX)++;          // 16/+2
    
//ok    lX++;               // 32/+1
//ok    plX++;              // 16/+4
//ok    (*plX)++;           // 32/+1
//ok    (*pplX)++;          // 16/+4
  
    //tA++;  
    ptA++;  
    //(*ptA)++;  
    (*pptA)++;  
    
//ok    ++lX;               // 32/+1
//ok    ++plX;              // 16/+4
//ok    ++(*plX);           // 32/+1
//ok    ++(*pplX);          // 16/+4
    
 //ok    //tA++;  
    ++ptA;  
    //++(*ptA);  
    ++(*pptA);  
   
}




