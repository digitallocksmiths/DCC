
// Note duplicate entries in the struct are tollerated! { int iA, char iA }

typedef unsigned char u8, *pu8;
typedef unsigned short u16;
typedef struct {
    u8  s1;
    u16 s2;
    char *pszA;
    char baA[10];
    int  i;
} Ts;


u16 A0[8];
u16 A1[8] = { 10, 11, 12, 13, 14, 15, 16, };
u16 A2[8] = { 20, 21, 22, 23, 24, 25, 26, 27 };
u16 A3[8] = { 30, 31, 32, 33, 34, 35, 36, 37, 38 };   // too many inits
u16 A4[]  = { 30, 31, 32, 33, 34, 35, 36, 37, 38 };

u8  B0[3][2];
u8  B1[3][2] = { { 11, 12 }, {21,22},  };
u8  B2[3][2] = { { 11, 12 }, {21,22}, {31,32} };
u8  B3[3][2] = { { 11, 12 }, {21,22}, {31,32}, {41,42} };   // too many inits
u8  B4[][] = { { 11, 12 }, {21,22}, {31,32}, {41,42} };
u8  B5[][] = { { 11, 12 }, {21,22}, {31,32}, {41,42,43} };   // too many inits
u8  B6[2][3] = { 11, 12, 21,22, 31,32, 41,42 };              // too many inits

Ts  C0[3];
Ts  C1[3] = {{ 11, 12 }, {21,22}, {31,32}};



u8 D0[2] = 1;
short D1a[5] = "Hello";   // too many inits
short D1b[6] = "Hello";
short D1c[7] = "Hello";
short D1d[8] = "Hello";
short D1e[16] = "Hello";
short D1f[] = "Hello";
 
Ts T0;
Ts T1 = { 1, 2, "hello", "world" };

Ts aT0[4];
Ts aT1[2] = {{ 1, 2, "hello", "world" }, { 1, 2, "hello", } };

u8 D2[3][1] = { { 1  }, { 2 }, { 3 }, { 4 } };          // too many inits
u8 D3[][] = { "once", "two", "Three" };                 // too many inits "three" longer than "once"
u8 D4[4][] = { "once", "two", "Three" };                // too many inits "three" longer than "once"
pu8 D5[]   = { "ten", "twenty", "Thirty" };



