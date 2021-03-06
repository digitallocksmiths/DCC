
// Note duplicate entries in the struct are tollerated! { int iA, char iA }

typedef unsigned char u8;
typedef unsigned char u16;

typedef struct TagRecord1 {
    u8   bR1;
    u16  nR1;
} TRecord1;

typedef struct TagRecord2 {
    u8 * pR2;
    u16  nR2;
} TRecord2;

typedef union TagUnion1 {
    u8   bU1;
    u16  nU1;
    long lU1;
} TUnion1;

typedef union TagUnion2 {
    long lU2;
    u16  nU2;
    u8   bU2;
} TUnion2;

typedef union TagUnion3{
    TRecord1  R1;
    TRecord2  R2;
} TUnion3;

TUnion1 A0;
TUnion1 A1 = { 5 };
TUnion1 A2 =  5 ;
TUnion1 A3 = { 5, 6 };

TUnion2 B0;
TUnion2 B1 = { 5 };
TUnion2 B2 =  5 ;
TUnion2 B3 = { 5, 6 };

TUnion3 C0;
TUnion3 C1 = { { 11,22 } };
TUnion3 C2 = {  11,22  };
TUnion3 C3 =   11;
