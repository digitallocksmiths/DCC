
void Unary(void) {
    char c;
    long l;
    char *x;
    char **y;
    
     !1;
     !(c|0xff);
     !(c*0);
 
     -1;                 // -1
     -(c|0xff);          //  1
     -(1+c*0);           // -1
    
     +1;                 // 1
     +(c|0xff);          // 255
     +(1+c*0);           // 1
    
     ~0x55;              // -86 (0xAA)
     ~(c|0xff);          // 0
     ~(0xaa+c*0);        // 85 (0x55)
     ~(0xaa+l*0);        // -171 (0xFFFFFF55)
     ~(-2+l*0);          // 1 

      &c;
      &l;
        
        *&c;
        *&l;
        
        x;
        y;
        *x;
        *y;
        
}
