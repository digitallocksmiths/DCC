
int iGlbSimple;
int *piGlbPointer;
int iaGlbArray1[5];
int iaGlbArray2[5][4];

void TestSimple(int iParamSimple1, int *piParamPointer, int iaParamArray1[5], int iaParamArray2[5][4]) {

    unsigned char cSimple;
    int iLocalSimple;
    int *piLocalPointer;
    int iaLocalArray1[5];
    int iaLocalArray2[5][4];
    
    iGlbSimple;
    piGlbPointer;
    iaGlbArray1;
    iaGlbArray2;

    iParamSimple1;
    piParamPointer;
    iaParamArray1;
    iaParamArray2;
    
    cSimple;
    iLocalSimple;
    piLocalPointer;
    iaLocalArray1;
    iaLocalArray2;
}


void TestDuplicates(int iGlbSimple, int *piGlbPointer, int iaGlbArray1[]) {
    int     iGlbSimple;         // redef param
    int     iGlbSimple;         // redef local that redefs a param
    char    *piGlbPointer;      // redef param and change type
    char    iaGlbArray1[9];     // redef arry while defining assert size
    
    iGlbSimple;     
    *piGlbPointer;
    iaGlbArray1;
    iaGlbArray1[2];
    
    iGlbSimple;             // expect param version
    
    { int w, x;
      char y, z;
    }
    
    { int iGlbSimple;       // permisable redef in new scope.
      char a, b;
      long b, d;            // redef b
      
      iGlbSimple;           // expect local version
    }
    
    iGlbSimple;             // expect param version
}
