// # ---------------------------------------------------------------------------------------------
// #  $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Utilities/ArgsParse.h $
// # ---------------------------------------------------------------------------------------------
// #  File:                  $Id: ArgsParse.h 306 2019-11-11 23:04:43Z sean $
// #  Last committed:  $Revision: 306 $
// # ---------------------------------------------------------------------------------------------

// Title: ArgsParse.h
// 
//  Implementation details.
//
//

#ifndef __ARGSPARSE_H__
#define __ARGSPARSE_H__

#ifdef DEBUG_INCLUDE_FILES 
#pragma message("     including " __FILE__)
#endif // DEBUG_INCLUDE_FILES

// Example 
// //                        type        var          key     default        help message
// TArgParam Params[] = {  { ARG_FLAG,   &fBool1,     "-f1",   "0",          "Flag1"                         },
//                         { ARG_INT,    &nInt1,      "-i1=",  "1",          "Int 2  default = %s"           },
//                         { ARG_STRING, &pcString2,  "-s2=",  "String2",    "String default = \"%s\""       },
//                         { ARG_HEX,    &pcHex1,     "-h1=",  "12345678",   "Hex2"                          },
//                         { ARG_END,    NULL,        NULL,    NULL,         "<infile> <outfile> {Options}*" }  // command line help message
// };


#define ARGS_MAX_FILES 256


typedef enum {  ARG_END,
                ARG_FLAG,       // int                  set to (values 0 & 1)   Matching key sets the var to not the default.
                ARG_CHAR,       // char                 set to s8 from text input
                ARG_INT,        // int                  set to int from number input
                ARG_STRING,     // char *               set to point to a null terminated char array
                ARG_HEX         // char *               set to point to a char array (byte zero indicates the length)
    } TArgType;


typedef struct TagParam {
    TArgType    type;
    char *      pcName;
    void *      pVar;
    char *      pcKey;
    char *      pcDefault;
    char *      pcHelpString;
} TArgParam;


char * * ArgsParse(int argc, char * argv[], TArgParam *pParams);
void    ArgsDumpParams(TArgParam *pParams, char *aFiles[]);


#endif // __ARGSPARSE_H__

// eof  $Workfile: ArgsParse.h $
