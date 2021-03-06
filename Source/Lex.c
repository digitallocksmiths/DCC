// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Lex.c $
// # $Revision: 433 $


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>

//#include <ext\types.h>
#include "typectrl.h"
#include "Expr.h"
#include "lex.h"
#include "C_Yacced.tab.h"

extern  YYSTYPE yylval;

/* ***************************************************************** */

//???? keep track of previous symbol and line.
//???? fix error/warning to permint print of current or previous symbol

//?? why does grammar fail after rebuild of only type.c ?

DWORD           PreviousLineNo;
DWORD           PreviousLinePos;
CHAR            PreviousLine[LINESIZE];

DWORD           LineNo  = 0;
DWORD           LinePos = LINESIZE;
CHAR            CurrentLine[LINESIZE];


/* ***************************************************************** */

typedef struct TagKeyWord {
        LPSTR   Name;
        int     Value;
} KEYWORD;

typedef KEYWORD  * PKEYWORD;

KEYWORD TplOpTable[] = {
            { "...",      ELLIPSIS  },
            { "<<=",      LSassign  },
            { ">>=",      RSassign  },
            
            { "",       0 }
};

KEYWORD DblOpTable[] = {
            { "->",      ARROW       },
            { "++",      INC         },
            { "--",      DEC         },
            { "<<",      LS          },
            { ">>",      RS          },
            { "<=",      LE          },
            { ">=",      GE          },
            { "==",      EQ          },
            { "!=",      NE          },
            { "&&",      ANDAND      },
            { "||",      OROR        },
            { "*=",      MULTassign  },
            { "/=",      DIVassign   },
            { "%=",      MODassign   },
            { "+=",      PLUSassign  },
            { "-=",      MINUSassign },
            { "&=",      ANDassign   },
            { "^=",      XORassign   },
            { "|=",      ORassign    },
            
            { "",       0 }
    
};

KEYWORD KeyWordTable[] = {
            { "auto",       _AUTO       },              // Keywords
            { "break",      _BREAK      },
            { "case",       _CASE       },
            { "char",       _CHAR       },
            { "const",      _CONST      },
            { "continue",   _CONTINUE   },
            { "default",    _DEFAULT    },
            { "do",         _DO         },
            { "double",     _DOUBLE     },
            { "else",       _ELSE       },
            { "enum",       _ENUM       },
            { "extern",     _EXTERN     },
            { "float",      _FLOAT      },
            { "for",        _FOR        },
            { "goto",       _GOTO       },
            { "if",         _IF         },
            { "int",        _INT        },
            { "long",       _LONG       },
            { "register",   _REGISTER   },
            { "return",     _RETURN     },
            { "short",      _SHORT      },
            { "signed",     _SIGNED     },
            { "sizeof",     _SIZEOF     },
            { "static",     _STATIC     },
            { "struct",     _STRUCT     },
            { "switch",     _SWITCH     },
            { "typedef",    _TYPEDEF    },
            { "union",      _UNION      },
            { "unsigned",   _UNSIGNED   },
            { "void",       _VOID       },
            { "volatile",   _VOLATILE   },
            { "while",      _WHILE      },
            { "_near",      _NEAR       },
            { "_far",       _FAR        },
            { "_ioreg",     _IOREG      }, 
            { "_noreturn",  _NORETURN   },
            { "_undefended",_UNDEFENDED },

            { "",       0 }
};

/* ***************************************************************** */

static int
MatchKeyWord(PSTR sym,PKEYWORD pKeyWord) {
    while (pKeyWord->Value) {
     // if (stricmp(pKeyWord->Name, sym) == 0) return pKeyWord->Value;
        if (strcmp(pKeyWord->Name, sym) == 0) return pKeyWord->Value;
        pKeyWord++;
    }
    return 0;
}


/* **************************************************** */
static FILE *infile = 0;

BOOL
StartInput(LPSTR Name) {
    LineNo  = 0;
    LinePos = LINESIZE;
    infile  = fopen(Name,"rt");
    return (infile != NULL);
}

BOOL
EndInput(void) {
    fclose(infile);
    return TRUE;
}

static BOOL
LineInput(LPSTR Line) {
    BOOL  Ok;
    DWORD n;
    char  Name[256];
    INT   s;
    char *pL;

    if (Line == NULL) {
        return FALSE;
    }

    for (;;) {
        LinePos = 0;
        LineNo++;
        pL = fgets(Line, LINESIZE, infile);
        Ok = (pL != NULL);
        if (Ok && (*Line == '#')) {                                             // # in the preprocessed file must be the line number/file indicator
            s = sscanf(Line+1,"line %ld %s",&n,Name);                           // format = "#line" <white space> <number> <white space> <file name>  
            if (s >  0) LineNo = n-1;
            //if (s >  1) printf("[%s]\n",Name);
        }
        else {
            break;
        }
    }
    printf("Line %5ld:\r", LineNo);
    if (Ok) {
        for (Line; *Line; Line++) {
            if (*Line == '\n' || *Line == '\r') *Line = '\0';
            if (*Line == '\t')                  *Line = ' ';
        }
    }
    return Ok;
 }

static char
GetChar(void) {
    char c;
    c = CurrentLine[LinePos++];
    // printf("[%c:%02x]",c,c);
    return c;
 }


static void
UnGetChar(void) {
    if (LinePos != 0) LinePos--;
}


/* ****************************************** */

LPVOID New(INT n) {
    LPVOID p;
    if ((p = malloc(n)) == NULL) {
        fprintf(stderr, "Disaster: Malloc out of space !\n");
        exit(-1);
    }
    memset(p, 0, n);
    return p;
}

void
Dispose(LPVOID n) {
    free(n);
}

static void
LexWarn(LPSTR Msg) {
    WORD i;
    fprintf(stderr, "%6ld:%s\n", LineNo, CurrentLine);
    for (i=0; i<LinePos+6; i++) fprintf(stderr, " ");
    fprintf(stderr, "^\n");
    fprintf(stderr, "Warning:\t%s\n", Msg);
}


/* ******************************************************** */
/*  Input Numbers in various Bases  */
/* ******************************** */


static char NumericAlphabet[] = "0123456789abcdef";

static char
LowerCase(char c) {
    if ('A' <= c && c <= 'Z') return c | 0x20;
    else return c;
}

static BOOL
IsNumeric(char c, int base) {
    char *hit;
    hit = strchr(NumericAlphabet, LowerCase(c));
    return (hit && (hit -  NumericAlphabet) < base);
}

static LONG
Number(char c) {
    char *hit;
    hit = strchr(NumericAlphabet, LowerCase(c));
    return (LONG)(hit -  NumericAlphabet);
}

static LONG
CollectNumber(int base) {
    LONG Tmp=0;
    char c;
    while (IsNumeric(c=GetChar(), base)) 
        Tmp = Tmp * (LONG)base + Number(c);
    UnGetChar();
    return Tmp;
}

#define CollectBinary()     CollectNumber(2)
#define CollectOctal()      CollectNumber(8)
#define CollectDecimal()    CollectNumber(10)
#define CollectHex()        CollectNumber(16)

static int
CollectNumeric(void) {
    int c;
    DOUBLE tmp;
    c = GetChar();
    if (c == '0') {
        c = GetChar();
        if (c == 'x')   {                               // Hex #
            yylval.Integer = CollectHex();
            c = GetChar();
            switch (c) {
            case 'L':                                    // Long ignored.
            case 'u':                                    // unsigned
                break;
            default: UnGetChar();                       // others are part of next token.
            }
            return INTEGERconstant;
        }
        if (isdigit(c)) {                               // Octal #
            UnGetChar();
            yylval.Integer = CollectOctal();
            return INTEGERconstant;
        }
    }
    UnGetChar();

    yylval.Integer = CollectDecimal();                  // Decimal #
    c = GetChar();
    if (c == '.') {
        tmp = (DOUBLE)CollectDecimal();
        while (tmp > 1.0) tmp /= 10.0;
        yylval.Real = (DOUBLE)(yylval.Integer) + tmp;
        return FLOATINGconstant;
    }
    switch (c) {
    case 'L':                                    // Long ignored.
    case 'u':                                    // unsigned
        break;
    default: UnGetChar();                       // others are part of next token.
    }
    return INTEGERconstant;
}

/* **************************************************** */
/*  Ascii character collection  */
/* **************************** */


static LONG CollectEscapedChar(void) {
    char c;
    c = GetChar();
    switch (c) {
        case '\\':  return (LONG)'\\';
        case '\"':  return (LONG)'\"';
        case 'n':   return (LONG)'\n';
        case 'r':   return (LONG)'\r';
        case 'b':   return (LONG)'\b';
        case 'a':   return (LONG)'\a';
        case 'x':   return CollectHex();
        case '0':   return CollectOctal();
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':   UnGetChar();
                    return CollectDecimal();
    }
    return 0;
}

static LONG CollectAscii(void) {
    LONG Tmp=0;
    if (GetChar() != '\'') LexWarn("expected '");
    Tmp = (LONG)GetChar();
    if (Tmp == '\\') Tmp = CollectEscapedChar();
    if (GetChar() != '\'') LexWarn("expected '");
    return Tmp;
}

static LPSTR
CollectString(void) {
    char  c, sbuf[LINESIZE], *p = sbuf;
    if (GetChar() != '"') LexWarn("expected \"");
    for (;;) {
        c = GetChar();
        if ((c == '\n') || (c == '\r') || (c == '\0')) {
            LexWarn("expected '\"'");
            LinePos = LINESIZE;
            break;
        }
        if (c == '"') { // check for follow on "
            do {
                c = GetChar();
            } while (c == ' ' || c == '\t');
            if (c != '"') {
                UnGetChar();
                break;
            }
        }
        else {
            if (c == '\\') {
                c = (char)CollectEscapedChar();
            }
            *p++ = c;
        }
    }
    *p++ = '\0';
    int nlen = p - sbuf;
    p = New(nlen);
    memcpy(p,sbuf, nlen);
    return p;
}

/* ************************************************* */

int
yylex(void) {
    int             c;
    char            TestOp[4];
    int             token;
    TPDeclSpec      LpTmpDecl;
    TPEnumElement   LpTmpEnum;

    PreviousLineNo = LineNo;
    PreviousLinePos = LinePos;
    strcpy (PreviousLine,CurrentLine);
    
    for (;;) {
        if ((LinePos >= LINESIZE) && (!LineInput(CurrentLine)))
                return EOF;

        do {                                        // swallow WhiteSpace
            c=GetChar();
        } while (c == ' ' || c == '\t');

        if ( c == '\n' ||                           // End of line
             c == '\r' ||
             c == '\0' ) {
            LinePos = LINESIZE;
            continue;
        }
        if ( c == '/' ) {                           // ? begin of comment ?
            if ((char)GetChar() == '/')  {
                LinePos = LINESIZE;
                continue;
            }
            UnGetChar();
        }
        break;
    }
    
    yylval.LineInfo.LineNo = LineNo;                // record origin of the symbol
    yylval.LineInfo.LinePos= LinePos;
    yylval.LineInfo.OldNo  = PreviousLineNo;        // record origin of the symbol
    yylval.LineInfo.OldPos = PreviousLinePos;

    TestOp[0] = (char)c;                            // "xxx" string
    TestOp[1] = (char)GetChar();
    TestOp[2] = (char)GetChar();
    TestOp[3] = (char)0;
    token = MatchKeyWord(TestOp,TplOpTable);        // test Triple operators
    if (token) return token;
    UnGetChar();
    TestOp[2] = (char)0;
    token = MatchKeyWord(TestOp,DblOpTable);                // test Double operators
    if (token) return token;
    UnGetChar();
    

    if (isdigit(c)) {                                       // Numeric #
        UnGetChar();                                        // FLOATINGconstant / INTEGERconstant/OCTALconstant/HEXconstant
        return CollectNumeric();                            // OCTALconstant    / HEXconstant
    }
    
    if (c == '\'') {                                        // Quote Char
        UnGetChar();
        yylval.Integer = (DWORD)CollectAscii();
        return CHARACTERconstant;
    }

    if (c == '\"') {                                        // Quote String
        UnGetChar();
        yylval.Ident = CollectString();
        return STRINGliteral;
    }

    if (isalpha(c) || (c == '_')) {                         // label
        char sbuf[100], *p = sbuf;
        do {
            *p++ = c;
            c=GetChar();
        } while (c != '\0' && (isalnum(c) || c == '_'));
        UnGetChar();
        *p = '\0';
        token = MatchKeyWord(sbuf,KeyWordTable);            // test Keyword
        if (token) return token;
        if (LpTmpDecl = FindType(sbuf)) {                   // test Typedef
            yylval.pDecl = LpTmpDecl->Use.DecId.pTarget;
            return TYPEDEFname;
        }
        if (LpTmpEnum = EnumElementFind(sbuf)) {            // Enumerated Constant
            yylval.Integer = (DWORD)(LpTmpEnum->dwValue);
            return ENUMERATIONconstant;
        }
        p = New(strlen(sbuf) +1);                           // Must Assume Identifier
        strcpy(p,sbuf);
        yylval.Ident = p;
        return IDENTIFIER;
    }
    return (int)c;                                  // boaring old character.
}


/* eof */

