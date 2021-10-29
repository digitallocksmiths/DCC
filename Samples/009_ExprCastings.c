void Castings(void) {
      char  c;
      short s;
      // long  l;
      // char *x;
   
    (char)(c*0+0xFFFF);
    (unsigned char)c;
    c;
    (short)c;
    (short)(char)s;
    
    (char)(c*0+0xFF7F);                     // 127
    (short)(char)(c*0+0x12FF);              // 65535
    (short)(char)(c*0+0x127F);              // 127
    (short)(unsigned char)(c*0+0x12FF);     // 255
    (short)(char)(c*0+0x80);                // 65408

}

