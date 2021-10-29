// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/C.y $
// # $Revision: 433 $


%{
/* ************************************ */
/* Ansi C Grammar:                      */
/* Sean Kelly:                          */
/* Based on K & R (Ansi C) Ed. 2        */
/* ************************************ */

#include <Windows.h>
#include <stdio.h>
//#include <ext\types.h>

#include "utilities\Console.h"

#include "lex.h"
#include "typectrl.h"
#include "expr.h"
#include "Statements.h"
#include "main.h"

// Yacc generates two unreferenced labels for 'yynewerror' & 'yyerrlab'
#pragma warning(disable : 4102)


void    yyerror(PSTR s);
%}

/* Define terminal tokens */


/* keywords */
%token _AUTO            _DOUBLE          _INT             _STRUCT
%token _BREAK           _ELSE            _LONG            _SWITCH
%token _CASE            _ENUM            _REGISTER        _TYPEDEF
%token _CHAR            _EXTERN          _RETURN          _UNION
%token _CONST           _FLOAT           _SHORT           _UNSIGNED
%token _CONTINUE        _FOR             _SIGNED          _VOID
%token _DEFAULT         _GOTO            _SIZEOF          _VOLATILE
%token _DO              _IF              _STATIC          _WHILE
%token _NEAR            _FAR
%token _IOREG
%token _NORETURN        _UNDEFENDED


/* ANSI Grammar suggestions */
%token  IDENTIFIER              STRINGliteral
%token  INTEGERconstant         CHARACTERconstant
%token  FLOATINGconstant        ENUMERATIONconstant 


%token  TYPEDEFname

/* Multi-Character operators */
%token  ARROW            /*    ->                              */
%token  INC DEC          /*    ++      --                      */
%token  LS RS            /*    <<      >>                      */
%token  LE GE EQ NE      /*    <=      >=      ==      !=      */
%token  ANDAND OROR      /*    &&      ||                      */
%token  ELLIPSIS         /*    ...                             */

/* modifying assignment operators */
%token MULTassign  DIVassign    MODassign   /*   *=      /=      %=      */
%token PLUSassign  MINUSassign              /*   +=      -=              */
%token LSassign    RSassign                 /*   <<=     >>=             */
%token ANDassign   XORassign     ORassign   /*   &=      ^=      |=      */


%union {
    DWORD   Integer;         // integral values
    DOUBLE  Real;            // Floating point
    BOOL    Bool;            // Boolean Stuff eg Struct or Union
    struct  {
            DOUBLE  pack;
            DWORD   LineNo,LinePos,OldNo,OldPos;
    } LineInfo;

    LPSTR               Ident;              // labels/strings/identifiers etc.
    TPDeclSpec          pDecl;              // Declarations
    TPEnumSet           pEnumSet;           //
    TPEnumElement       pEnumElement;       //
    TPStructSet         pStructSet;         //
//  TIdExprAssign       nAssign;            // ebum for assignments.
    TIdExprUnOp         nUnaryOp;           // enum for unary operators.
    TPStatement         pStatement;         // program statements.
    TPExprNode          pExpr;              // arirmetic expressions.
}

%type <Ident>           IDENTIFIER

%type <pEnumElement>    enumerator.list
%type <pEnumElement>    enumerator
%type <pEnumSet>        enum.specifier
%type <pStructSet>      struct.or.union.specifier
%type <Bool>            struct.or.union

%type <pDecl>           TYPEDEFname                 // TPDeclSpec
%type <pDecl>           declaration.specifiers      // TPDeclSpec
%type <pDecl>           storage.class.specifier     // TPDeclSpec
%type <pDecl>           type.specifier              // TPDeclSpec
%type <pDecl>           type.qualifier              // TPDeclSpec
%type <pDecl>           pointer                     // TPDeclSpec
%type <pDecl>           type.qualifier.list         // TPDeclSpec
%type <pDecl>           declarator                  // TPDeclSpec
%type <pDecl>           direct.declarator           // TPDeclSpec
%type <pDecl>           init.declarator             // TPDeclSpec
%type <pDecl>           init.declarator.list        // TPDeclSpec
%type <pDecl>           function.definition         // TPDeclSpec
%type <pDecl>           declaration                 // TPDeclSpec
%type <pDecl>           struct.declaration.list     // TPDeclSpec
%type <pDecl>           struct.declaration          // TPDeclSpec
%type <pDecl>           specifier.qualifier.list    // TPDeclSpec
%type <pDecl>           struct.declarator.list      // TPDeclSpec
%type <pDecl>           struct.declarator           // TPDeclSpec
%type <pDecl>           declaration.list            // TPDeclSpec
%type <pDecl>           parameter.type.list         // TPDeclSpec
%type <pDecl>           parameter.list              // TPDeclSpec
%type <pDecl>           parameter.declaration       // TPDeclSpec
// K&R %type <pDecl>           identifier.list             // TPDeclSpec
%type <pDecl>           type.name                   // TPDeclSpec
%type <pDecl>           abstract.declarator         // TPDeclSpec
%type <pDecl>           direct.abstract.declarator  // TPDeclSpec

%type <pStatement>      statement.list              // TPStatement
%type <pStatement>      statement
%type <pStatement>      labeled.statement
%type <pStatement>      expression.statement
%type <pStatement>      compound.statement
%type <pStatement>      selection.statement
%type <pStatement>      iteration.statement
%type <pStatement>      jump.statement
%type <pStatement>      case
%type <pStatement>      case.list
%type <pStatement>      switch.list
    
//%type <nAssign>         assignment.operator
%type <nUnaryOp>        unary.operator
    
%type <pExpr>           initializer
%type <pExpr>           initializer.list
    
%type <pExpr>           expression
%type <pExpr>           assignment.expression
%type <pExpr>           conditional.expression
%type <pExpr>           constant.expression
%type <pExpr>           logical.OR.expression
%type <pExpr>           logical.AND.expression
%type <pExpr>           inclusive.OR.expression
%type <pExpr>           exclusive.OR.expression
%type <pExpr>           AND.expression
%type <pExpr>           equality.expression
%type <pExpr>           relational.expression
%type <pExpr>           shift.expression
%type <pExpr>           additive.expression
%type <pExpr>           multiplicative.expression
%type <pExpr>           cast.expression
%type <pExpr>           unary.expression
%type <pExpr>           postfix.expression
%type <pExpr>           primary.expression
%type <pExpr>           argument.expression.list
%type <pExpr>           constant

%type <Ident>           STRINGliteral
%type <Integer>         INTEGERconstant
%type <Integer>         CHARACTERconstant
%type <Real>            FLOATINGconstant
%type <Integer>         ENUMERATIONconstant 


%start prog.start

%%
prog.start:
      translation.unit
    ;

translation.unit:
      external.declaration
    | translation.unit external.declaration
    ;

external.declaration:
      function.definition                                                       { Declaration($1);  }
    | declaration                                                               { Declaration($1);  }
    ;

function.definition:                                                            
                             declarator { FuncParams(NewSpecType(TypeINT, NULL), $1); } compound.statement  { $$ = FunctionBody($1, NULL, $3 ); }    // ANSI definition assuming 'int'
    | declaration.specifiers declarator { FuncParams($1, $2); }                         compound.statement  { $$ = FunctionBody($2, NULL, $4 );                         }    // ANSI fully typed
// K&R     |                        declarator declaration.list                         compound.statement  { $$ = FunctionBody($1, $2, $3 );   }    // K&R definition assuming 'int'
// K&R     | declaration.specifiers declarator declaration.list                         compound.statement  { $$ = FunctionBody($2, $3, $4 );                          }    // K&R  fully typed
    ;
    
declaration:
      declaration.specifiers                      ';'                           { $$ = $1;                      }
    | declaration.specifiers init.declarator.list ';'                           { $$ = AppendDecl($2,$1);   }
    ;

declaration.list:
      declaration                                                               {  DeclareLocal($1), $$ = $1;     }
    | declaration.list declaration                                              {  DeclareLocal($2), $$ = DeclVarAddBrother($1,$2); }
    ;

declaration.specifiers:
      storage.class.specifier                                                   { $$ = $1;                              }       
    | storage.class.specifier declaration.specifiers                            { $$ = ConcatDeclSpecClass($1,$2);      }
    | type.specifier                                                            { $$ = $1;                              }
    | type.specifier declaration.specifiers                                     { $$ = ConcatDeclSpecTypes($1,$2);      }
    | type.qualifier                                                            { $$ = $1;                              }
    | type.qualifier declaration.specifiers                                     { $$ = ConcatDeclSpecQualifiers($1,$2); }       // eg "const$1 X$2"
    ;

storage.class.specifier:
      _AUTO                                                                     { $$ = NewSpecClass(ClassAUTO);         }
    | _REGISTER                                                                 { $$ = NewSpecClass(ClassREGISTER);     }
    | _STATIC                                                                   { $$ = NewSpecClass(ClassSTATIC);       }
    | _EXTERN                                                                   { $$ = NewSpecClass(ClassEXTERN);       }
    | _TYPEDEF                                                                  { $$ = NewSpecClass(ClassTYPEDEF);      }
    ;

type.specifier:
      _VOID                                                                     { $$ = NewSpecType(TypeVOID,    NULL); } // basic types
    | _CHAR                                                                     { $$ = NewSpecType(TypeCHAR,    NULL); }
    | _SHORT                                                                    { $$ = NewSpecType(TypeSHORT,   NULL); }
    | _INT                                                                      { $$ = NewSpecType(TypeINT,     NULL); }
    | _LONG                                                                     { $$ = NewSpecType(TypeLONG,    NULL); }
    | _FLOAT                                                                    { $$ = NewSpecType(TypeFLOAT,   NULL); }
    | _DOUBLE                                                                   { $$ = NewSpecType(TypeDOUBLE,  NULL); }
    | _SIGNED                                                                   { $$ = NewSpecType(TypeSIGNED,  NULL); }
    | _UNSIGNED                                                                 { $$ = NewSpecType(TypeUNSIGNED,NULL); }
    | struct.or.union.specifier                                                 { $$ = NewSpecType(TypeSTRUCT,  $1);   }
    | enum.specifier                                                            { $$ = NewSpecType(TypeENUM,    $1);   }
    | TYPEDEFname                                                               { $$ = $1;                             }
    ;

type.qualifier:
      _CONST                                                                    { $$ = NewSpecQual(QualCONST);         }
    | _VOLATILE                                                                 { $$ = NewSpecQual(QualVOLATILE);      }
    | _NEAR                                                                     { $$ = NewSpecQual(QualNEAR);          }
    | _FAR                                                                      { $$ = NewSpecQual(QualFAR);           }
    | _NORETURN                                                                 { $$ = NewSpecQual(QualNORETURN);      }
    | _UNDEFENDED                                                               { $$ = NewSpecQual(QualUNDEFENDEF);    }

    ;

struct.or.union.specifier:
      struct.or.union            '{' struct.declaration.list '}'                { $$ = AddStructSet("", $1, $3);    }
    | struct.or.union IDENTIFIER '{' struct.declaration.list '}'                { $$ = AddStructSet($2, $1, $4);    }
    | struct.or.union IDENTIFIER                                                { $$ = AddStructSet($2, $1, NULL);  }
    ;

struct.or.union:
      _STRUCT                                                                   { $$ = FALSE;  }
    | _UNION                                                                    { $$ = TRUE;   }
    ;

struct.declaration.list:
      struct.declaration                                                        { $$ = $1;                  }
    | struct.declaration.list struct.declaration                                { $$ = DeclVarAddBrother($1,$2);  }
    ;
    
    
init.declarator.list:
      init.declarator                                                           { $$ = $1;                       }
    | init.declarator.list ',' init.declarator                                  { $$ = DeclVarAddBrother($1,$3); }
    ;

init.declarator:
      declarator                                                                { $$ = $1;                      }
    | declarator '=' initializer                                                { $$ = AddInitializer($1,$3);   }
    ;

struct.declaration:
       specifier.qualifier.list struct.declarator.list ';'                      { $$ = AppendDecl($2,$1);       }
    | specifier.qualifier.list ';'                                              { $$ = AppendDecl(NewIdentifier("") ,$1);  }   // define struct without naming var 
    ;

specifier.qualifier.list:
      type.specifier                                                            { $$ = $1;                      }
    | type.specifier specifier.qualifier.list                                   { $$ = ConcatDeclSpec($2,$1);   }
    | type.qualifier                                                            { $$ = $1;                      }
    | type.qualifier specifier.qualifier.list                                   { $$ = ConcatDeclSpec($2,$1);   }
    ;

struct.declarator.list:
      struct.declarator                                                         { $$ = $1;                      }
    | struct.declarator.list ',' struct.declarator                              { $$ = DeclVarAddBrother($1,$3);      }
    ;

struct.declarator:
      declarator                                                                { $$ = $1;                      }
    |            ':' constant.expression                                        { $$ = NULL;                    ConsolePrintf(CON_CYAN,"struct.declarator 2\n"); }
    | declarator ':' constant.expression                                        { $$ = $1;                      ConsolePrintf(CON_CYAN,"struct.declarator 3\n");  }
    ;

enum.specifier:
      _ENUM '{' enumerator.list '}'                                             { $$ = EnumSetAdd("",$3);       }
    | _ENUM IDENTIFIER '{' enumerator.list '}'                                  { $$ = EnumSetAdd($2,$4);       }
    | _ENUM IDENTIFIER                                                          { $$ = EnumSetAdd($2,NULL);     }
    ;

enumerator.list:
      enumerator                                                                { $$ = EnumElementAdd(NULL,$1); }
    | enumerator.list ',' enumerator                                            { $$ = EnumElementAdd($1,$3);   }
    | enumerator.list ','                                                       { $$ = $1;                      } // forgive excess ',' as per gcc behaviour
    ;

enumerator:
      IDENTIFIER                                                                { $$ = EnumElementMake($1,NULL);}
    | IDENTIFIER '=' constant.expression                                        { $$ = EnumElementMake($1,$3);  }
    ;

declarator:
              direct.declarator                                                 { $$ = $1;                      }
    | pointer direct.declarator                                                 { $$ = AppendDecl($2,$1);       }
    ;

direct.declarator:
      IDENTIFIER                                                                { $$ = NewIdentifier($1);       }
    | '(' declarator ')'                                                        { $$ = $2;                      }
    | direct.declarator '['                     ']'                             { $$ = NewArray($1,NULL);       }
    | direct.declarator '[' constant.expression ']'                             { $$ = NewArray($1,$3);         }
    | direct.declarator '(' parameter.type.list ')'                             { $$ = DeclNewFunc($1,$3,NULL);     }
    | direct.declarator '('                     ')'                             { $$ = DeclNewFunc($1,NULL,NULL);   }
// K&R    | direct.declarator '(' identifier.list     ')'                             { $$ = DeclNewFunc($1,NULL,$3);     }       // K&R
    ;

pointer:
      '*'                                                                       { $$ = NewPointer(NULL, NULL);  }
    | '*' type.qualifier.list                                                   { $$ = NewPointer($2, NULL);    }
    | '*'                     pointer                                           { $$ = NewPointer(NULL, $2);    }
    | '*' type.qualifier.list pointer                                           { $$ = NewPointer($2, $3);      }
    ;

type.qualifier.list:
      type.qualifier                                                            { $$ = $1;                      }
    | type.qualifier.list type.qualifier                                        { $$ = ConcatDeclSpec($1,$2);   }
    ;

parameter.type.list:
      parameter.list                                                            { $$ = $1;                      }
    | parameter.list ',' ELLIPSIS                                               { $$ = DeclAddVarToParameterList($1,NewIdentifier("..."));  }
    ;

parameter.list:
      parameter.declaration                                                     { $$ = $1;                      }
    | parameter.list ',' parameter.declaration                                  { $$ = DeclAddVarToParameterList($1,$3);      }
    ;

parameter.declaration:
      declaration.specifiers declarator                                         { $$ = AppendDecl($2,$1);                              }
    | declaration.specifiers                                                    { $$ = AppendDecl(NewIdentifier(""),$1);               }
    | declaration.specifiers abstract.declarator                                { $$ = AppendDecl(NewIdentifier(""),AppendDecl($2,$1));}
    ;

// K&R identifier.list:
// K&R      IDENTIFIER                                                                { $$ = NewIdentifier($1);                       }
// K&R    | identifier.list ',' IDENTIFIER                                            { $$ = DeclVarAddBrother($1,NewIdentifier($3)); }
// K&R    ;

initializer:
      assignment.expression                                                     { $$ = ExprMakeInitNode($1);        }
    | '{' initializer.list '}'                                                  { $$ = ExprMakeInitList($2);        }
    | '{' initializer.list ',' '}'                                              { $$ = ExprMakeInitList($2);        }
    ;

initializer.list:
      initializer                                                               { $$ = $1;                  }
    | initializer.list ',' initializer                                          { $$ = ExprConcat($1,$3);   }
    ;

type.name:
      specifier.qualifier.list                                                  { $$ = $1;                  } 
    | specifier.qualifier.list abstract.declarator                              { $$ = AppendDecl($2,$1);   }
    ;

abstract.declarator:
      pointer                                                                   { $$ = $1;                  }
    | pointer direct.abstract.declarator                                        { $$ = AppendDecl($2,$1);   }
    |         direct.abstract.declarator                                        { $$ = $1;                  }
    ;

direct.abstract.declarator:
      '(' abstract.declarator ')'                                               { $$ = $2;                      }
    |                            '['                     ']'                    { $$ = NewArray(NULL,NULL);     }
    | direct.abstract.declarator '['                     ']'                    { $$ = NewArray($1,NULL);       }
    |                            '[' constant.expression ']'                    { $$ = NewArray(NULL,$2);       }
    | direct.abstract.declarator '[' constant.expression ']'                    { $$ = NewArray($1,$3);         }
    |                            '('                     ')'                    { $$ = DeclNewFunc(NULL,NULL,NULL); }
    | direct.abstract.declarator '('                     ')'                    { $$ = DeclNewFunc($1,NULL,NULL);   }
    |                            '(' parameter.type.list ')'                    { $$ = DeclNewFunc(NULL,NULL,NULL); ConsolePrintf(CON_CYAN, "direct.abstract.declarator 8\n"); }
    | direct.abstract.declarator '(' parameter.type.list ')'                    { $$ = DeclNewFunc($1,NULL,NULL);   ConsolePrintf(CON_CYAN, "direct.abstract.declarator 9\n"); }
    ;

statement:
      labeled.statement                                                         { $$ = $1; }
    | expression.statement                                                      { $$ = $1; }
    | compound.statement                                                        { $$ = $1; }
    | selection.statement                                                       { $$ = $1; }
    | iteration.statement                                                       { $$ = $1; }
    | jump.statement                                                            { $$ = $1; }
    ;

labeled.statement:
      IDENTIFIER ':' statement                                                  { $$ = StatementAddLabel($1, $3);   }
/*  | _CASE constant.expression ':' statement                                   { $$ = StatementMakeCase($2, $4);   } SK revison                */
/*  | _DEFAULT ':' statement                                                    { $$ = StatementMakeCase(NULL, $3); } added switch.list grammar */
    ;

expression.statement:
                 ';'                                                            { $$ = NULL; }
    | expression ';'                                                            { $$ = StatementMakeExpression($1); }
    ;

compound.statement:
      '{'                                  '}'                                  { $$ = StatementMakeCompound( NULL, NULL ); }
    | '{'                   statement.list '}'                                  { $$ = StatementMakeCompound( NULL, $2   ); }
    | '{' declaration.list                 '}'                                  { $$ = StatementMakeCompound( $2,   NULL );   UndeclareLocals($2); }
    | '{' declaration.list  statement.list '}'                                  { $$ = StatementMakeCompound( $2,   $3   );   UndeclareLocals($2); }
    ;

statement.list:
      statement                                                                 { $$ = $1; }
    | statement.list statement                                                  { $$ = StatementAppend($1,$2); }
    ;

case:
      _CASE constant.expression ':'                                             { $$ = StatementMakeCase($2, NULL); }
    | _CASE constant.expression ':' statement.list                              { $$ = StatementMakeCase($2, $4);   }
    ;
    
case.list:
      case                                                                      { $$ = $1;                          }
    | case.list case                                                            { $$ = StatementAppend($1,$2);      }
    ;
    
switch.list:
      case.list                                                                 { $$ = $1; }
    | case.list _DEFAULT ':' statement.list                                     { $$ = StatementAppend($1,StatementMakeCase(NULL, $4)); }
    ;
    
selection.statement:
      _IF '(' expression ')' statement                                          { $$ = StatementMakeIf($3, $5, NULL); }
    | _IF '(' expression ')' statement _ELSE statement                          { $$ = StatementMakeIf($3, $5, $7);   }
    | _SWITCH '(' expression ')' '{' switch.list '}'                            { $$ = StatementMakeSwitch($3, $6);   }
    ;

iteration.statement:
      _WHILE '(' expression ')' statement                                       { $$ = StatementMakeWhile($3, $5);             }      
    | _DO statement _WHILE '(' expression ')'                                   { $$ = StatementMakeDo($2, $5);                }      
    | _FOR '('            ';'            ';'            ')' statement           { $$ = StatementMakeFor(NULL, NULL, NULL, $6); }
    | _FOR '(' expression ';'            ';'            ')' statement           { $$ = StatementMakeFor($3,   NULL, NULL, $7); }
    | _FOR '('            ';' expression ';'            ')' statement           { $$ = StatementMakeFor(NULL, $4,   NULL, $7); }
    | _FOR '(' expression ';' expression ';'            ')' statement           { $$ = StatementMakeFor($3,   $5,   NULL, $8); }
    | _FOR '('            ';'            ';' expression ')' statement           { $$ = StatementMakeFor(NULL, NULL, $5,   $7); }
    | _FOR '(' expression ';'            ';' expression ')' statement           { $$ = StatementMakeFor($3,   NULL, $6,   $8); }
    | _FOR '('            ';' expression ';' expression ')' statement           { $$ = StatementMakeFor(NULL, $4,   $6,   $8); }
    | _FOR '(' expression ';' expression ';' expression ')' statement           { $$ = StatementMakeFor($3,   $5,   $7,   $9); }
    ;

jump.statement:
      _GOTO IDENTIFIER ';'                                                      { $$ = StatementMakeGoto($2);     }
    | _CONTINUE ';'                                                             { $$ = StatementMakeContinue();   }
    | _BREAK ';'                                                                { $$ = StatementMakeBreak();      } 
    | _RETURN            ';'                                                    { $$ = StatementMakeReturn(NULL); }
    | _RETURN expression ';'                                                    { $$ = StatementMakeReturn($2);   }
    ;

expression:
      assignment.expression                                                     { $$ = $1;                  }
    | expression ',' assignment.expression                                      { $$ = ExprConcat($1, $3);  }
    ;

//assignment.expression:
//      conditional.expression                                                    { $$ = $1;                              }
//    | unary.expression assignment.operator assignment.expression                { $$ = ExprMakeAssignNode($2, $1, $3);  }
//    ;
//
//assignment.operator:
//      '='                                                                       { $$ = AsNop;   }
//    | MULTassign                                                                { $$ = AsMul;   }
//    | DIVassign                                                                 { $$ = AsDiv;   }
//    | MODassign                                                                 { $$ = AsMod;   }
//    | PLUSassign                                                                { $$ = AsAdd;   }
//    | MINUSassign                                                               { $$ = AsSub;   }
//    | LSassign                                                                  { $$ = AsSL;    }
//    | RSassign                                                                  { $$ = AsSR;    }
//    | ANDassign                                                                 { $$ = AsBAnd;  }
//    | XORassign                                                                 { $$ = AsBXor;  }
//    | ORassign                                                                  { $$ = AsBOr;   }
//    ;
    
assignment.expression:
      conditional.expression                                            { $$ = $1;                                 }
    | unary.expression '='         assignment.expression                { $$ = ExprMakeAssignNode(binNop, $1, $3); }
    | unary.expression MULTassign  assignment.expression                { $$ = ExprMakeAssignNode(binNop, $1, ExprMakeBinaryNode(binMul, $1, $3)); }
    | unary.expression DIVassign   assignment.expression                { $$ = ExprMakeAssignNode(binNop, $1, ExprMakeBinaryNode(binDiv, $1, $3)); }
    | unary.expression MODassign   assignment.expression                { $$ = ExprMakeAssignNode(binNop, $1, ExprMakeBinaryNode(binMod, $1, $3)); }
    | unary.expression PLUSassign  assignment.expression                { $$ = ExprMakeAssignNode(binAdd, $1, $3); }
    | unary.expression MINUSassign assignment.expression                { $$ = ExprMakeAssignNode(binSub, $1, $3); }
    | unary.expression LSassign    assignment.expression                { $$ = ExprMakeAssignNode(binNop, $1, ExprMakeBinaryNode(binShl, $1, $3)); }
    | unary.expression RSassign    assignment.expression                { $$ = ExprMakeAssignNode(binNop, $1, ExprMakeBinaryNode(binShr, $1, $3)); }
    | unary.expression ANDassign   assignment.expression                { $$ = ExprMakeAssignNode(binAnd, $1, $3); }
    | unary.expression XORassign   assignment.expression                { $$ = ExprMakeAssignNode(binXor, $1, $3); }
    | unary.expression ORassign    assignment.expression                { $$ = ExprMakeAssignNode(binOr,  $1, $3); }
    ;

conditional.expression:
      logical.OR.expression                                                     { $$ = $1;                                          }
    | logical.OR.expression '?' expression ':' conditional.expression           { $$ = ExprMakeTernaryNode(CondExp, $1, $3, $5);    }
    ;

constant.expression:
      conditional.expression                                                    { $$ = $1;                              }
    ;

logical.OR.expression:
      logical.AND.expression                                                    { $$ = $1;                              }
    | logical.OR.expression OROR logical.AND.expression                         { $$ = ExprMakeBinaryNode(binLOr,$1,$3);   }
    ;

logical.AND.expression:
      inclusive.OR.expression                                                   { $$ = $1;                              }
    | logical.AND.expression ANDAND inclusive.OR.expression                     { $$ = ExprMakeBinaryNode(binLAnd,$1,$3);  }
    ;

inclusive.OR.expression:
      exclusive.OR.expression                                                   { $$ = $1;                              }
    | inclusive.OR.expression '|' exclusive.OR.expression                       { $$ = ExprMakeBinaryNode(binOr,$1,$3);   }
    ;

exclusive.OR.expression:
      AND.expression                                                            { $$ = $1;                              }
    | exclusive.OR.expression '^' AND.expression                                { $$ = ExprMakeBinaryNode(binXor,$1,$3);  }
    ;

AND.expression:
      equality.expression                                                       { $$ = $1;                              }
    | AND.expression '&' equality.expression                                    { $$ = ExprMakeBinaryNode(binAnd,$1,$3);  }
    ;

equality.expression:
      relational.expression                                                     { $$ = $1;                              }
    | equality.expression EQ relational.expression                              { $$ = ExprMakeBinaryNode(binCEQ,$1,$3);   }
    | equality.expression NE relational.expression                              { $$ = ExprMakeBinaryNode(binCNE,$1,$3);   }
    ;

relational.expression:
      shift.expression                                                          { $$ = $1;                              }
    | relational.expression '<' shift.expression                                { $$ = ExprMakeBinaryNode(binCLT,$1,$3);   }
    | relational.expression '>' shift.expression                                { $$ = ExprMakeBinaryNode(binCGT,$1,$3);   }
    | relational.expression LE  shift.expression                                { $$ = ExprMakeBinaryNode(binCLE,$1,$3);   }
    | relational.expression GE  shift.expression                                { $$ = ExprMakeBinaryNode(binCGE,$1,$3);   }
    ;

shift.expression:
      additive.expression                                                       { $$ = $1;                              }
    | shift.expression LS additive.expression                                   { $$ = ExprMakeBinaryNode(binShl,$1,$3);   }
    | shift.expression RS additive.expression                                   { $$ = ExprMakeBinaryNode(binShr,$1,$3);   }
    ;

additive.expression:
      multiplicative.expression                                                 { $$ = $1;                              }
    | additive.expression '+' multiplicative.expression                         { $$ = ExprMakeBinaryNode(binAdd,$1,$3);   }
    | additive.expression '-' multiplicative.expression                         { $$ = ExprMakeBinaryNode(binSub,$1,$3);   }
    ;

multiplicative.expression:
      cast.expression                                                           { $$ = $1;                              }
    | multiplicative.expression '*' cast.expression                             { $$ = ExprMakeBinaryNode(binMul,$1,$3);   }
    | multiplicative.expression '/' cast.expression                             { $$ = ExprMakeBinaryNode(binDiv,$1,$3);   }
    | multiplicative.expression '%' cast.expression                             { $$ = ExprMakeBinaryNode(binMod,$1,$3);   }
    ;

cast.expression:
      unary.expression                                                          { $$ = $1;                              }
    | '(' type.name ')' cast.expression                                         { $$ = ExprMakeCastNode($2,$4);         }
    ;

unary.expression:
      postfix.expression                                                        { $$ = $1;                              }
    | INC unary.expression                                                      { $$ = ExprMakeUnaryNode(unPreInc,$2);    }
    | DEC unary.expression                                                      { $$ = ExprMakeUnaryNode(unPreDec,$2);    }
    | unary.operator cast.expression                                            { $$ = ExprMakeUnaryNode($1,$2);        }
    | _SIZEOF unary.expression                                                  { $$ = ExprMakeUnaryNode(unSizeOf,$2);    }
    | _SIZEOF '(' type.name ')'                                                 { $$ = ExprMakeConstI(CalcSizeOf($3));  }
    ;

unary.operator:
      '&'                                                                       { $$ = unAddr;    }
    | '*'                                                                       { $$ = unPtr;     }
    | '+'                                                                       { $$ = unPlus;    }
    | '-'                                                                       { $$ = unMinus;   }
    | '~'                                                                       { $$ = unNeg;     }
    | '!'                                                                       { $$ = unNot;     }
    ;

postfix.expression:
      primary.expression                                                        { $$ = $1;                              }
    | postfix.expression '[' expression ']'                                     { $$ = ExprMakeArrayNode($1,$3);        }
    | postfix.expression '('                          ')'                       { $$ = ExprMakeFuncNode($1,NULL);       }
    | postfix.expression '(' argument.expression.list ')'                       { $$ = ExprMakeFuncNode($1,$3);         }
    | postfix.expression '.' IDENTIFIER                                         { $$ = ExprMakeDotNode($1,$3);          }
    | postfix.expression ARROW IDENTIFIER                                       { $$ = ExprMakeArrowNode($1,$3);        }
    | postfix.expression INC                                                    { $$ = ExprMakeUnaryNode(unPostInc,$1); }
    | postfix.expression DEC                                                    { $$ = ExprMakeUnaryNode(unPostDec,$1); }
    ;

primary.expression:
      IDENTIFIER                                                                { $$ = ExprMakeVar($1);                 }
    | constant                                                                  { $$ = $1;                              }
    | STRINGliteral                                                             { $$ = ExprMakeConstS($1);              }
    | '(' expression ')'                                                        { $$ = $2;                              }
    | _IOREG '(' INTEGERconstant ',' STRINGliteral ')'                          { $$ = ExprMakeIoReg($3, $5);           }
    ;

argument.expression.list:
      assignment.expression                                                     { $$ = $1;                              }
    | argument.expression.list ',' assignment.expression                        { $$ = ExprConcatArgs($1, $3);          }
    ;

constant:
      INTEGERconstant                                                           { $$ = ExprMakeConstI($1);              }
    | CHARACTERconstant                                                         { $$ = ExprMakeConstC($1);              }
    | FLOATINGconstant                                                          { $$ = ExprMakeConstF($1);              }
    | ENUMERATIONconstant                                                       { $$ = ExprMakeConstI($1);              }
    ;


%%

/* ----end of grammar----*/


void
yyerror(PSTR s) {
    Error(ERROR0, s,0L);
}


/* eof */
