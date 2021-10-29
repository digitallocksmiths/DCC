

void Shift(void) {
    char s8;
    short s16;
    long s32;
    unsigned char u8;
    unsigned short u16;
    unsigned long u32;
    
    ((char)0xff) >> 1;              // FF
    (char)0x7F >> 1;                // 3F
    (unsigned char)0xff >> 1;       // 7F
    (unsigned char)0x7F >> 1;       // 3F

    ((short)0xff00) >> 1;           // FF80
    (short)0x7F00 >> 1;             // 3F80
    (unsigned short)0xff00 >> 1;    // 7F80
    (unsigned short)0x7F00 >> 1;    // 3F80

    s8 >> 7;                        // s8 >> 7;
    s8 >> 8;                        // s8 >> 8;
    s16 >> 15;                      // s16 >> 15;
    s16 >> 16;                      // s16 >> 16;
    s32 >> 31;                      // s32 >> 31;
    s16 >> 32;                      // s16 >> 32;

    u8 >> 7;                        // u8 >> 7;
    u8 >> 8;                        // 0
    u16 >> 15;                      // u16 >> 15;
    u16 >> 16;                      // 0
    u32 >> 31;                      // u32 >> 31;
    u16 >> 32;                      // 0

    ((char)0xff) << 1;              // FE
    (char)0x7F << 1;                // FE
    (unsigned char)0xff << 1;       // FE
    (unsigned char)0x7F << 1;       // FE

    ((short)0xff00) << 1;           // FE80
    (short)0x7F00 << 1;             // FE80
    (unsigned short)0xff00 << 1;    // FE80
    (unsigned short)0x7F00 << 1;    // FE80

    s8 << 7;                        // s8 << 7
    s8 << 8;                        // 0
    s16 << 15;                      // s16 << 15
    s16 << 16;                      // 0
    s32 << 31;                      // s32 << 31
    s16 << 32;                      // 0

    u8 << 7;                        // u8 << 7
    u8 << 8;                        // 0
    u16 << 15;                      // u16 << 15
    u16 << 16;                      // 0
    u32 << 31;                      // u32 << 31
    u16 << 32;                      // 0
    
}

