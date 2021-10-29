
void Adding(void) {
    int a, a1, a2;
    
       1 +  3  + 4;             // 8
      (1 +  a) + 2;             // a + 3
      (a +  1) + 2;             // a + 3
       1 + (a  + 2);            // a + 3
       1 + (2  + a);            // a + 3
      (1+a1) + (a2+2);          // (a + a) + 3
       a + 0;                   // a
}

void Subtracting(void) {
    int a, a1, a2;
   
   10 - 1 - 2 - 3;             // 4
   (9 - a) - 3;                // 6 - a
   (a - 2) - 3;                // a - 5
   1 - (a - 2);                // -1 - a  
   1 - (2 - a);                // -1 - a
   a - 0;                      // a
}

void Multiplying(void) {
    int a, a1, a2;
    
    a=0x123;
    a1=2;
    a3=3;
   
      1 *  3  * 4;             // 12
     (4 *  a) * 3;             // a * 12
     (a *  3) * 4;             // a * 12
      4 * (a  * 3);            // a * 12
      4 * (3  * a);            // 3 * 12
      (4*a1) * (a2*3);         // (a1 * a2) * 12
      a * 0;                   // 0
      a * 1;                   // a
      a * 2;                   // a+a
}

void Dividing(void) {
   int a, b, c;
   
   24 / 3 / 2;                     //  4
   (24 / 3) / 3;                   //  4
   24 / (3 / 2);                   // 24
   24 / (a * 0);                   // -1 (warning div 0)
   24 / ((a * 0) + 1);             // 24
   ((a * 0) + 28) / ((a * 0) + 7); //  4
}
 
void Moding(void) {
    int a, b, c;
    
    24 % 13 % 7;                     //  4
    (24 % 13) % 7;                   //  4
    24 % (13 % 7);                   //  0
    24 % (a * 0);                    //  0 (warning div 0)
     a % ((a * 0) + 1);              //  0
    24 % ((a * 0) + 7);              //  3
     a % ((a * 0) + 7);              //  a % 7
    ((a * 0) + 29) % ((a * 0) + 7);  //  1
}
 
void Anding(void) {
    char  c;
    short s;
    long  l;
    int a,a1,a2;
    
    1 &  3  & 4;             // 0
   (1 &  a) & 2;             // 0
   (a &  1) & 2;             //
    1 & (a  & 2);            
    1 & (2  & a);            
   (1&a1) & (a2&2);  
    (a*0)&(a*0);

    c & 0x7F;
    s & 0x7F;
    l & 0x7F;
    
    c & 0xFF;
    s & 0xFF;
    l & 0xFF;

    c & 0xFFFF;
    s & 0xFFFF;
    l & 0xFFFF;
    
    c & 0xFFFFFFFF;
    s & 0xFFFFFFFF;
    l & 0xFFFFFFFF;
}

void Oring(void) {
     char  c;
     short s;
     long  l;
    
    1 | 2 | 4;          // 7    
    1 | c | 2 | 4;      // c | 7
    1 | c | 2 | 4;      // c | 7
    (1 | c) | 2 | 4;    // c | 7
    1 | (c | 2) | 4;    // c | 7
    (1 | c) | (c | 4);  // c | 5
    (c*0)|(s*0);        // 0
    
     c | 0x7F;
     s | 0x7F;
     l | 0x7F;
       
     c | 0xFF;
     s | 0xFF;
     l | 0xFF;
       
     c | 0xFFFF;
     s | 0xFFFF;
     l | 0xFFFF;
       
     c | 0xFFFFFFFF;
     s | 0xFFFFFFFF;
     l | 0xFFFFFFFF;
}

void Xoring(void) {
     char  c;
     short s;
     long  l;
    
    1 ^ 2 ^ 5;          // 6    
    1 ^ c ^ 2 ^ 5;      // c | 6
    (1 ^ c) ^ 2 ^ 5;    // c | 6
    1 ^ (c ^ 2) ^ 5;    // c | 6
    (1 ^ c) ^ (c ^ 5);  // c | 4
    (c*0)^(s*0 +3);     // 3
    c ^ (c*0);          // c
    
     c ^ 0x7F;
     s ^ 0x7F;
     l ^ 0x7F;
       
     c ^ 0xFF;
     s ^ 0xFF;
     l ^ 0xFF;
       
     c ^ 0xFFFF;
     s ^ 0xFFFF;
     l ^ 0xFFFF;
       
     c ^ 0xFFFFFFFF;
     s ^ 0xFFFFFFFF;
     l ^ 0xFFFFFFFF;
}

