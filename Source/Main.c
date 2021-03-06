// # $URL: https://eboracum-vss.digitallocksmiths.local/svn/Dls/Sean/RoyalHolloway/CC_Avr/Source/Main.c $
// # $Revision: 773 $


#pragma message("Todo: static is ignored for local vars.")
//#pragma message("Todo: initializers are ignored for local vars.")                                     // Done but see below.
//#pragma message("Todo: initializers can't see sibling variables")                                     // Done also. //  "int i=1; int j=i;" will fail.
#pragma message("Todo: Local and parameters:  read before set warnings.")
//#pragma message("Todo: anon structure sub-structures?")                                               // Done
#pragma message("Todo: const array of function pointers miss-allocated to init-data.")
#pragma message("Todo: Lex.  0L error.  L instrumentation not recognozed.")                             // dirty hack just ignores it!
#pragma message("Todo: function definition with empty params. crashes")                                 //
#pragma message("Todo: String init with extra '{ '.")                                                   //  char szS[] = { "foo" };          fails. should forgive the {}s
#pragma message("Todo: String init with internal '\0' looses data.")                                    //  char szS[] = "Hello\0World";     looses World.


#pragma message("Todo: Declaration function names to start with Decl? (tidy up the source code)")
//#pragma message("Todo: Globals dump to use depth and indent correctly")                               // Done
//#pragma message("Todo: Local and parameters:  allocate and remove as scope changes.")                 // Done
//#pragma message("ToDo: Casting should be case node with sub clasification of case type.")             // Done
//#pragma message("Todo: Local and parameters:  unused variable warnings.")                             // Done
//#pragma message("Todo: Local variables and parameters. how to find them when parsing expressions.")   // Done
//#pragma message("Todo: Local variables. generate expression code.")


#pragma message("Todo: No concept of alignmnent. All vars occupy their own size and no packing is generated.")   
// this is also true of parameters on the stack.
// Given we have an 8 bit target this is not considered to be a problem.

//#pragma message("Todo: void Foo(void). Parameters display incorrectly.")                              // Done
#pragma message("Todo: Subtraction of arrays looks odd. Debug and comment the code.")   

#pragma message("ToDo: C-parsing expression optimisation could be skipped and left for the optimizer?") // except constants. they need to be reduced ASAP for array size definition or enum initializers.
//#pragma message("ToDo: Array could be translated to arithmetic?")                                     // Done
//#pragma message("ToDo: Arrow could be translated to arithmetic?")                                     // Done
//#pragma message("ToDo: Dot could be translated to arithmetic?")                                       // Done

#pragma message("ToDo: Structures optimization. See comment here")                                       // Done
// Make the Var node take a vaR name and displacment. then the maths of the displacement cam be added tint the collection of the var address.
//          ldi rx, #Foo
//          add rx,#disp
// becomes
//          ldi rx#(Foo+disp)
//

#pragma message("ToDo: Call defence for indirect calls has lost the address when the function returns.")                                       // Done


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>

#include "Utilities\Console.h"
#include "Utilities\ArgsParse.h"
#include "Utilities\VersionInfo.h"

#include "lex.h"
#include "typectrl.h"
#include "Expr.h"
#include "GenAvr\Gen.h"
#include "Main.h"
#include "C_Yacced.tab.h"

// *******************************************
// Command line 

TArgs CmdLine;

TArgParam Params[] = {
    //  { type          name                                var                           key               default      help message                         }
        { ARG_FLAG,     "Verbose",                          &CmdLine.fVerbose,            "-v",             "0",         "Verbose mode." },
        { ARG_FLAG,     "Echo to stdout",                   &CmdLine.fEcho,               "-debug_output",  "0",         "Echo to screen." },
        { ARG_FLAG,     "Expression debug",                 &CmdLine.fExpr,               "-debug_expr",    "0",         "Expression debug." },
        { ARG_FLAG,     "Object debug",                     &CmdLine.fObjects,            "-Debug_objects", "0",         "Object debug." },
        { ARG_INT,      "Defensive Call Return",            &CmdLine.iDefendCallRet,      "-d1=",           "0",         "Call return defence level." },
        { ARG_INT,      "Defensive branching",              &CmdLine.iDefendBranches,     "-d2=",           "0",         "Unconditional jump defences." },
        { ARG_INT,      "Defensive conditional",            &CmdLine.iDefendConditionals, "-d3=",           "0",         "Conditional branching." },
        { ARG_END,      NULL,                               NULL,                         NULL,             NULL,        "Command line options." }
};

char** ppFileList;                                                        // File list retrieved from the Command line


// *******************************************
YYSTYPE     yylval;
void        yyparse(void);
FILE        *hGlbOut = NULL;               // target generation.

DWORD dwErrorCount   = 0;
DWORD dwWarningCount = 0;
int   iFinalColour   = 0;               // Colour of the error count summary.
    
void ErrorLocator0(int iColour) {
    WORD i;
    fprintf(stderr, "\r                   \r");
    fprintf(stderr, "%6ld: %s\n", yylval.LineInfo.LineNo, CurrentLine);
    ConsoleSetColour(iColour);
    for (i=0; i<yylval.LineInfo.LinePos+7; i++) fprintf(stderr, " ");
    fprintf(stderr, "^\n");
    
}

void ErrorLocator1(int iColour) {
    WORD i;
    fprintf(stderr, "\r                   \r");
    fprintf(stderr, "%6ld: %s\n",yylval.LineInfo.OldNo, PreviousLine);
    ConsoleSetColour(iColour);
    for (i=0; i<yylval.LineInfo.OldPos+7; i++) fprintf(stderr, " ");
    fprintf(stderr, "^\n");
}

void ErrorLocatorX(int iColour) {
    fprintf(stderr, "Somewhere on or before line %d: ", yylval.LineInfo.OldNo);
}


void Error(TErrorType e, const char *pbFormat, ...) {
char szOutString[256];
    va_list ArgList;
    int iColour;
    char *pszErrClass = "";

    switch (e) {
    case WARNING0:
    case WARNING1:
    case WARNINGX: dwWarningCount++;
                   iColour = CON_YELLOW; // +CON_BRIGHT;
                   iFinalColour = max(iFinalColour, 1);
                   pszErrClass = "Warning";
                   break;
    case ERROR0:
    case ERROR1:
    case ERRORX:   dwErrorCount++;
                   iColour = CON_RED; // +CON_BRIGHT;
                   iFinalColour = max(iFinalColour, 2);
                   pszErrClass = "Error";
                   break;
    case FATAL:
    default:       iColour = CON_MAGENTA + CON_BRIGHT;
                   iFinalColour = max(iFinalColour, 3);
                   pszErrClass = "Fatal";
                   break;
    }

    switch (e) {
    case WARNING0: 
    case ERROR0:   ErrorLocator0(iColour);          // current symbol
                   break;
    case WARNING1:  
    case ERROR1:   ErrorLocator1(iColour);          // previous symbol
                   break;

    case WARNINGX:                                  // long lost symbol
    case ERRORX:   ErrorLocatorX(iColour);
                   break;

    case FATAL:
    default:       if (hGlbOut == NULL) {      // no source to display if we are generating output.
                       ErrorLocator0(iColour);
                    }
                   break;
    }

    va_start(ArgList, pbFormat);
    _vsnprintf(szOutString, sizeof(szOutString), pbFormat, ArgList);
    ConsolePrintf(iColour, "%s: %s\n", pszErrClass, szOutString);
    if (e == FATAL) {
#ifdef _DEBUG
//        if (_getch() == 0x1b)
#endif // _DEBUG
        ConsolePrintf(iColour, "   Processing: %s\n", ppFileList[0]);
        exit(-1);
    }
}


/* **************************************************************** */

char szSource[_MAX_PATH];
char szDest[_MAX_PATH];
char szDrive[_MAX_DRIVE];
char szDir[_MAX_DIR];
char szExt[_MAX_EXT];
char szFile[_MAX_FNAME];

void
SortOutFileNames(LPSTR pszIn, LPSTR pszOut) {

	if (pszIn == NULL) {
		pszIn = "Code";
	}

	_splitpath(pszIn, szDrive, szDir, szFile, szExt);
	_makepath(szSource, szDrive, szDir, szFile, ((*szExt == '.') && szExt[1]) ? szExt : ".c" );

	if (pszOut == NULL) {
		_makepath(  szDest,   szDrive, szDir, szFile, ".asm" );
	}
	else {
		_splitpath(pszOut, szDrive, szDir, szFile, szExt);
        _makepath(szDest, szDrive, szDir, szFile, ((*szExt == '.') && szExt[1]) ? szExt : ".asm");

	}
}

void Tidyup(void) {
    if (hGlbOut != NULL) {
        fclose(hGlbOut);
    }
}

void
main(int Argc, char *Argv[]) {
    // testing();
    // exit(0);

    VersionProcessInfo(Argv[0]);

    //char  * *ppFileList;                                                        // File list retrieved from the Command line
    ppFileList = ArgsParse(Argc, Argv, Params);                                 // Parse the command line 
    if (CmdLine.fVerbose) {                                                     //
        ArgsDumpParams(Params, ppFileList);                                     //   print the settings we will be using
    }                                                                           //

    SortOutFileNames(ppFileList[0], ppFileList[1]);

//  if (Argc > 2)      { SortOutFileNames(Argv[1], Argv[2]); }
//  else if (Argc > 1) { SortOutFileNames(Argv[1], NULL);    }
//  else               { SortOutFileNames(NULL, NULL);       }
    
    if (!StartInput(szSource)) {
            fprintf(stderr, "Failed opening source file '%s'\n", szSource);
            exit(-1);
    }

    yyparse();
    EndInput();
     
    switch (iFinalColour) {
    case 0: iFinalColour = CON_GREEN + CON_BRIGHT; break;
    case 1: iFinalColour = CON_YELLOW + CON_BRIGHT; break;
    case 2: iFinalColour = CON_RED + CON_BRIGHT; break;
    }
    ConsolePrintf(iFinalColour, "%ld Errors, %ld Warnings.\n\n", dwErrorCount, dwWarningCount);

    //ListGlobalTypes();

    if (dwErrorCount == 0) {
        if(CmdLine.fObjects) {
            EnumSetPrintList(0);
            PrintStructSets(0);
            ListGlobalTypes();
            ListGlobalObjects();
            ListParameterObjects();
            ListLocalObjects();
        }

        //ListGlobalTypes();
        //ListGlobalObjects();

        hGlbOut = fopen(szDest, "wt");
        atexit(Tidyup);
        GenIntro();
        GenConst(GlobalObjects);
        GenData(GlobalObjects);
        GenBss(GlobalObjects);
        GenText(GlobalObjects);
        GenTail();
        fclose(hGlbOut);
        hGlbOut = NULL;
    }

    if (dwErrorCount) {
        exit(-1);
    }
    else if (dwWarningCount) {
        exit(1);
    }
    else {
        exit(0);
    }
 }

/* eof */

