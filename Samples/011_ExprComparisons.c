
 void Comparison(void) {
     char c;
     
      (short)1 == (unsigned)1;                   // 1 (byte)
      1 == -1;                                   // 0 (byte)
      -1 == 1;                                   // 0 (byte)
      (c*0+1) == (c*0+1);                        // 1 (byte)
      (c*0+1) == (c*0-1);                        // 0 (byte)
      (c*0-1) == (c*0+1);                        // 0 (byte)
      (unsigned)(c*0+1) == (int)(c*0-1);         // 0 (byte)
                                                       
      (short)1 != (unsigned)1;                   // 0 (byte)
      1 != -1;                                   // 1 (byte)
      -1 != 1;                                   // 1 (byte)
      (c*0+1) != (c*0+1);                        // 0 (byte)
      (c*0+1) != (c*0-1);                        // 1 (byte)
      (c*0-1) != (c*0+1);                        // 1 (byte)
      (unsigned)(c*0+1) != (int)(c*0-1);         // 1 (byte)
                                                       
      (short)1 < (unsigned)1;                    // 0 (byte)
      1 < -1;                                    // 0 (byte)
      -1 < 1;                                    // 1 (byte)
      (c*0+1) < (c*0+1);                         // 0 (byte)
      (c*0+1) < (c*0-1);                         // 0 (byte)
      (c*0-1) < (c*0+1);                         // 1 (byte)
      (unsigned)(c*0+1) < (int)(c*0-1);          // 1 (byte)
                                                       
      (short)1 >= (unsigned)1;                   // 1 (byte)
      1 >= -1;                                   // 1 (byte)
      -1 >= 1;                                   // 0 (byte)
      (c*0+1) >= (c*0+1);                        // 1 (byte)
      (c*0+1) >= (c*0-1);                        // 1 (byte)
      (c*0-1) >= (c*0+1);                        // 0 (byte)
      (unsigned)(c*0+1) >= (int)(c*0-1);         // 0 (byte)
                                                       
      (short)1 > (unsigned)1;                    // 0 (byte)
      1 > -1;                                    // 1 (byte)
      -1 > 1;                                    // 0 (byte)
      (c*0+1) > (c*0+1);                         // 0 (byte)
      (c*0+1) > (c*0-1);                         // 1 (byte)
      (c*0-1) > (c*0+1);                         // 0 (byte)
      (unsigned)(c*0+1) > (int)(c*0-1);          // 0 (byte)
                                                       
      (short)1 <= (unsigned)1;                   // 1 (byte)
      1 <= -1;                                   // 0 (byte)
      -1 <= 1;                                   // 1 (byte)
      (c*0+1) <= (c*0+1);                        // 1 (byte)
      (c*0+1) <= (c*0-1);                        // 0 (byte)
      (c*0-1) <= (c*0+1);                        // 1 (byte)
      (unsigned)(c*0+1) <= (int)(c*0-1);         // 1 (byte)
      c;                                         // type unchanged/still char
 
 }
