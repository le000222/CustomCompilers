/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _____________________________________
|                                    |
| ....... 'RID' LANGUAGE ........    |
|    _____    _______    _____       |
|   ||   \\    || ||    ||    \\     |
|   ||    \\   || ||    ||     \\    |
|   || ___//   || ||    ||      \\   |
|   ||  \\     || ||    ||      //   |
|   ||   \\    || ||    ||     //    |
| __||__  \\___||_||____||____//     |
|                                    |
|  .. ALGONQUIN COLLEGE - 2022F ..   |
|____________________________________|

*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: 4 Dec 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
extern BufferReader* stringLiteralTable;
extern rid_int line;
extern Token tokenizer();
extern rid_char* keywordTable[];
rid_int syntaxErrorNumber = 0;

#define STR_LANGNAME	"RIDEAN"
#define LANG_WRTE		"print"
#define LANG_READ		"input"
#define LANG_MAIN		"main"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum PARSER_KEYWORDS {
	NO_ATTR = -1,
	KW_int,
	KW_float,
	KW_string,
	KW_if,
	KW_else,
	KW_do,
	KW_while,
	KW_continue,
	KW_return,
	KW_break,
	KW_true,
	KW_false
	/*
	"int",
	"float",
	"string",
	"if",
	"else",
	"do",
	"while",
	"continue",	
	"return",
	"break",
	"true",
	"false",
	*/

};

/* Function definitions */
rid_void startParser();
rid_void matchToken(rid_int, rid_int);
rid_void syncErrorHandler(rid_int);
rid_void printError();
rid_void printWarning();

/* TO_DO: Place ALL non-terminal function declarations */
rid_void bodySession();
rid_void codeSession();
rid_void dataSession();
rid_void optVarListDeclarations();
rid_void varListDeclarations();
rid_void varListDeclarationsPrime();
rid_void varListDeclaration();
rid_void integerVarlistDeclaration();
rid_void integerVariableList();
rid_void integerVariable();
rid_void floatVariableList();
rid_void floatVariable();
rid_void stringVariableList();
rid_void stringVariable();
rid_void stringVarlistDeclaration();
rid_void floatVarlistDeclaration();
rid_void optionalVarlist();
rid_void optionalStatements();
rid_void outputStatement();
rid_void inputStatement();
rid_void inputStatements();
rid_void inputVariableList();
rid_void parameterList();
rid_void outputVariableList();
rid_void program();
rid_void assignmentStatement();
rid_void assignmentExpression();
rid_void arithmaticExpression();
rid_void stringExpression();
rid_void primaryStringExpression();
rid_void conditionalExpression();
rid_void stringExpressionPrime();
rid_void statements();
rid_void statement();
rid_void statementsPrime();

#endif
