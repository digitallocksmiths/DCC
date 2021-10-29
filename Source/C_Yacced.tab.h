#define _AUTO 257
#define _DOUBLE 258
#define _INT 259
#define _STRUCT 260
#define _BREAK 261
#define _ELSE 262
#define _LONG 263
#define _SWITCH 264
#define _CASE 265
#define _ENUM 266
#define _REGISTER 267
#define _TYPEDEF 268
#define _CHAR 269
#define _EXTERN 270
#define _RETURN 271
#define _UNION 272
#define _CONST 273
#define _FLOAT 274
#define _SHORT 275
#define _UNSIGNED 276
#define _CONTINUE 277
#define _FOR 278
#define _SIGNED 279
#define _VOID 280
#define _DEFAULT 281
#define _GOTO 282
#define _SIZEOF 283
#define _VOLATILE 284
#define _DO 285
#define _IF 286
#define _STATIC 287
#define _WHILE 288
#define _NEAR 289
#define _FAR 290
#define _IOREG 291
#define _NORETURN 292
#define _UNDEFENDED 293
#define IDENTIFIER 294
#define STRINGliteral 295
#define INTEGERconstant 296
#define CHARACTERconstant 297
#define FLOATINGconstant 298
#define ENUMERATIONconstant 299
#define TYPEDEFname 300
#define ARROW 301
#define INC 302
#define DEC 303
#define LS 304
#define RS 305
#define LE 306
#define GE 307
#define EQ 308
#define NE 309
#define ANDAND 310
#define OROR 311
#define ELLIPSIS 312
#define MULTassign 313
#define DIVassign 314
#define MODassign 315
#define PLUSassign 316
#define MINUSassign 317
#define LSassign 318
#define RSassign 319
#define ANDassign 320
#define XORassign 321
#define ORassign 322
typedef union {
    DWORD   Integer;         /* integral values*/
    DOUBLE  Real;            /* Floating point*/
    BOOL    Bool;            /* Boolean Stuff eg Struct or Union*/
    struct  {
            DOUBLE  pack;
            DWORD   LineNo,LinePos,OldNo,OldPos;
    } LineInfo;

    LPSTR               Ident;              /* labels/strings/identifiers etc.*/
    TPDeclSpec          pDecl;              /* Declarations*/
    TPEnumSet           pEnumSet;           /**/
    TPEnumElement       pEnumElement;       /**/
    TPStructSet         pStructSet;         /**/
/*  TIdExprAssign       nAssign;            // ebum for assignments.*/
    TIdExprUnOp         nUnaryOp;           /* enum for unary operators.*/
    TPStatement         pStatement;         /* program statements.*/
    TPExprNode          pExpr;              /* arirmetic expressions.*/
} YYSTYPE;
extern YYSTYPE yylval;
