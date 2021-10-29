
//char *pSubKeys;
//char *pInputData;
//int i;
//int nLength;
//int nSize;
//
//void foo(void) {
//    
//    //char c;
//    pInputData[nLength - nSize];
//    pInputData[nLength - nSize +1];
//    
//    //c = pInputData[nLength - nSize +1];
//    //c = pInputData[nLength - nSize + i];
//    
//    
//}

typedef struct {
    char baBuff0[7];
    char baBuff1[8];
    int c;
    struct {
       int j;
       char baBuff2[9];
    } s;
} T_S;

T_S S;
    




const int iGlbConst;
      int iGlbVar;

const int iGlbConstArray[2] = { 3, 4 };
      int iGlbVarArray[2]   = { 4, 6 };

int  * pI;
char * pC;

void foo(int iParam1, int iParam2) {

    int iLocal;
    int iLocalArray[2];
    
//    1;
    
//  iGlbConst;                      // OK
//  iGlbVar;                        // OK
//  iGlbConstArray;                 // OK
//  iGlbConstArray[1];              // OK 
//  iGlbVarArray;                   // OK
//  iGlbVarArray[2];                // OK

//  iLocal;                         // OK
//  iLocalArray;                    // OK
//  iLocalArray[2];
    
//  iParam1 = 1;                    // OK
//  iParam2 = 2;                    // OK
    
//  iGlbVarArray[iLocal];           // OK

//  iGlbVarArray[iLocal + iLocal];      // OK
//  iGlbVarArray[iLocal + iLocal + 1];  // OK

//  iGlbVarArray[iLocal - iGlbVar + iGlbVar];  // OK
    
//   pI;      // OK
//   *pI;      // OK
//     pI[2];      // OK

//    pI[iLocal + iLocal];      // OK

//    pI[iLocal + iLocal + iLocal];      // OK
//  pI[iLocal - iLocal + iGlbVar];      // OK
//    pC[iLocal - iLocal - iGlbVar];      // OK
//    pC[5 + iLocal -10];                 // OK

 
    iGlbVarArray;
    iGlbVarArray[2];
    
    S.baBuff1;
    S.baBuff1[2];

    
    //    S.baBuff1[1];
//    &S.baBuff1[1];
    
    S.s.baBuff2;
    S.s.baBuff2[1];
    &S.s.baBuff2[1];
  
}
