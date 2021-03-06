
typedef char           s8,  *ps8;
typedef unsigned char  u8,  *pu8;
typedef short          s16, *ps16;
typedef unsigned short u16, *pu16;
typedef long           s32, *ps32;
typedef unsigned long  u32, *pu32;

char           bss_s8;
unsigned char  bss_u8;
short          bss_s16;
unsigned short bss_u16;
long           bss_s32;
unsigned long  bss_u32;

const int iConst = 0x1234;
const long lConst = 0x12345678;

u8     baArray[]; 
u16    baArray2[10];

s8      data_s8   = 1;
ps8     data_ps8  = 2;
u8      data_u8   = 3;
pu8     data_pu8  = 4;
s16     data_s16  = 5; 
ps16    data_ps16 = 6;
u16     data_u16  = 7;
pu16    data_pu16 = 8;
s32     data_s32  = 9;
ps32    data_ps32 = 10;
u32     data_u32  = 11;
pu32    data_pu32 = 12;


char * pc = "hello";
//  //int    i  = { 1,2,3};           // error expected
//  //int  * pi = { 1,2,3};           // error expected
pu8   p0 = baArray;
pu8   p1 = &baArray;                  // common forgivable error
pu8   p2 = &data_u32;

// pu8    p3 = &baArray[1];                // can't fix up
// pu32   p4 = &data_u32+1;                // can't fix up
// pu32   p5 = &(&data_u32)[1];            // can't fix up
// pu32   p6 = (&data_u32)[1];             // can't fix up
