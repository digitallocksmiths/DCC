
    int a=0x123;
    int a1=2;
    int a2=3;
    
    char x,y,z;

unsigned int main(char  bY, short sY, long lY) {
 
//    if (0x100) {
//        a2=0x1234;
//    }
//    else {
//        a2=0x4321;
//    }
//    
//    if (a1)   a2=0x1234;
//    if (a1+2) a2=0x1234;
//    if (a < a1) a2=0x1234;

//    if (a) a2=0x1234;
//    if (a1 < a2) a2=0x1234;
//    if (a1=a2+1) a2=0x1234;
    
//    if (a && a)    a2=0x1234; 
//    else           a2=0x2345; 

//    if (x || y)    z=0x1234; 
//      else           z=0x2345; 

//      if (x)    z=0x1234; 
//      if (!x)   z=0x1234; 

    
        if (!(x && y)) z=0x1234;    // logical results.
        else z=0x2345; 
        if (!x || !y)  z=0x2345; 
        else z=0x2345; 
        
        a = x < y;                  // arithmetic result
        
    
}






