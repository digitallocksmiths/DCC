
// Note duplicate entries in the struct are tollerated! { int iA, char iA }

typedef unsigned char u8;
typedef unsigned char u16;

//int I = 1;
//char b = 2;
//char *pC = "hello";
//char *pD = 42;

typedef struct TagRecord1 {
    int iR1A;
    u8 cR1B,cR1C;
    char baR1D[5];
    char * pcR1E;
} TRecord1, *TPRecord1;

TRecord1 R1 = { 1,2, 3, "what", "next" };

typedef struct TagRecord2 {
    u16 iR2A;
    TRecord1 R2B;
    char cR2C;
    TRecord1 R2D;
} TRecord2, *TPRecord2;

//TRecord2 R2a = { 1,{ 10,11,12,13 }, 2, {20,21,22,23}, "help" };
//TRecord2 R2b = { 1,2, 3};
TRecord2 _R2c;
const TRecord2 R2c = { 1, { 10,11, }, 2, { 5,6,7, "help", "me"} };
//TRecord2 R2d = { 1,2, };
// 
// // typedef struct TagRecord3 {
// //     TRecord2 R3A;
// //     char c3B;
// // } TRecord3, *TPRecord3;
// // 
// // TRecord3 _R3;
// // TRecord3 R3 = { { 1,{ 10,11, }, 2, "yee", "ha" } , 0x55 };
// // 
// 
// eof