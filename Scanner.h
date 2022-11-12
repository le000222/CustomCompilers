/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Winter, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
*/

/*
************************************************************
* File name: scanner.h
* Compiler: MS Visual Studio 2022
* Author: [Ngoc Phuong Khanh Le, 041004318], [Dan McCue, 040772626]
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A22, A32.
* Date: Jul 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20    /* variable identifier length */
#define ERR_LEN 40    /* error message length */
#define NUM_LEN 5     /* maximum number of digits for IL */
#define FLT_PT_LEN 6  /* maximum number of digits for FLT_PT */
#define RTE_CODE 1    /* Value for run-time error */
#define RID_SUCCESS 0 /* Value for sucessful execution */

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,			/*  0: Error token */
	MNID_T,			/*  1: Method name identifier token */
	STR_T,			/*  2: String literal token */
	LBRACK_T,		/*  3: Left brace token */
	RBRACK_T,		/*  4: Right brace token */
	LPAREN_T,		/*  5: Left parenthesis token */
	RPAREN_T,		/*  6: Right parenthesis token */
	KW_T,			/*  7: Keyword token */
	EOS_T,			/*  8: End of statement (semicolon) */
	RTE_T,			/*  9: Run-time error token */
	INL_T,			/* 10: Integer literal token */
	RID_FLT_PT_T,   /* 11: Floating points token*/
	VAR_T,			/* 12: Variable name Identifier */
	ASSIGN_T,		/* 13: Assignment operator Identifier */
	LESS_T,			/* 14: Less than operator */
	GTR_T,			/* 15: Greater than operator */
	SUBTRACT_T,		/* 16: Subtraction operator */
	ADDITION_T,		/* 17: Addition Operator */
	MULTIPLY_T,		/* 18: Multpily operator */
	DIV_T,			/* 19: Division operator */
	ARG_SEP_T,		/* 20: Argument seperator */
	EQUAL_TO_T,		/* 21: Equal (to check if values are equal) */
	COMM_T,			/* 22: Comments (no tokens created for comments)*/
	NOT_EQ_T,		/* 23: Not Equal token */
	AND_OP_T,		/* 24: Logical and & */
	OR_OP_T,		/* 25: Logical OR | */
	NOT_OP_T,		/* 26: Logical not ! */
	SEOF_T			/* 27: Source end-of-file token */
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	rid_int codeType;					/* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	rid_int intValue;					/* integer literal attribute (value) */
	rid_int keywordIndex;				/* keyword index in the keyword table */
	rid_int contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	rid_float floatValue;				/* floating-point literal attribute (value) */
	rid_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	rid_char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	rid_byte flags;			/* Flags information */
	union {
		rid_int intValue;			/* Integer value */
		rid_float floatValue;		/* Float value */
		rid_char* stringContent;	/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	rid_int code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;



/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, #comment\n , ',' , ';' , '-' , '+' , '*' , '/', # ,  
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '('
#define CHRCOL4 '\''
#define CHRCOL7 '.'

/* TO_DO: Error states and illegal state */
#define FS		100		/* Final / Illegal state */
#define ESWR	101		/* Error state with retract */
#define ESNR	102		/* Error state with no retract */

 /* TO_DO: State transition table definition */
#define TABLE_COLUMNS 12

/* TO_DO: Transition table - type of states defined in separate table */
static rid_int transitionTable[][TABLE_COLUMNS] = {
/*
   [A-z] , [0-9], ' _ ',  ' ( ',    ' " ',  SEOF, other,    period
   RC(0),  RI(1), US(2), LPAREN(3), RS(4),  E(5),  O(6),    P(7)		*/
{    1,      7,      1,   ESNR,        3,   ESWR,  ESNR,   ESNR}, // S00: NOAS
{    1,      1,      1,      2,     ESNR,   ESWR,    12,     11}, // S01: NOAS
{   FS,     FS,     FS,     FS,       FS,     FS,    FS,     FS}, // S02: ASWR (KEY) or (METHOD)
{    3,      3,      3,      3,        4,   ESWR,     3,	  3}, // S03: NOAS
{   FS,     FS,     FS,     FS,       FS,     FS,     FS,	 FS}, // S04: ASNR (SL)
{   FS,     FS,     FS,     FS,       FS,     FS,     FS,    FS}, // S05: ASNR (ES)
{   FS,     FS,     FS,     FS,       FS,     FS,     FS,    FS}, // S06: ASWR (ER)
{   11,      7,     11,      8,       11,   ESWR,      8,     9}, // S07: NOAS 
{   FS,     FS,     FS,     FS,       FS,     FS,     FS,    FS}, // S08: ASNR (IL)
{   11,      9,		11,     11,       11,   ESWR,     10,    11}, // S09: NOAS
{   FS,     FS,     FS,     FS,       FS,     FS,     FS,    FS}, // S10: ASNR (RID_FLOAT)
{   11,     11,     11,		 6,       11,   ESWR,      6,    11}, // S11: NOAS error tokens
{   FS,     FS,     FS,     FS,       FS,     FS,     FS,    FS}  // S12: ASWR KEY or VAR 
};
/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static rid_int stateType[] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSWR, /* 02 (KEY),(METHOD) - keys, Methods */
	NOFS, /* 03 */
	FSNR, /* 04 (SL) */
	FSNR, /* 05 (Err1 - no retract) */
	FSWR, /* 06 (Err2 - retract) */
	NOFS, /* 07 */
	FSWR, /* 08 (INT L) - Integer literal */
	NOFS, /* 09 */
	FSWR, /* 10 (FLT_PT) Floating point */
	NOFS, /* 11 */
	FSWR  /* 12 ( KEY OR VAR )*/
};

/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
rid_int startScanner(ReaderPointer psc_buf);
static rid_int nextClass(rid_char c);			/* character class function */
static rid_int nextState(rid_int, rid_char);	/* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(rid_char* lexeme);

/* Declare accepting states functions */
Token funcIL	(rid_char lexeme[]);
Token funcSL	(rid_char lexeme[]);
Token funcID	(rid_char lexeme[]);
Token funcKEY	(rid_char lexeme[]);
Token funcErr	(rid_char lexeme[]);
Token funcFLOAT (rid_char lexeme[]);
Token funcVAR   (rid_char lexeme[]);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
	NULL,		/* -			[00] */
	NULL,		/* -			[01] */
	funcID,     /*KEY or METHOD	[02] */
	NULL,		/* -			[03] */
	funcSL,		/* SL			[04] */
	funcErr,	/* ERR1			[05] */
	funcErr,	/* ERR2			[06] */
	NULL,		/* -			[07] */
	funcIL,     /* INTL			[08] */
	NULL,		/* -			[09] */
	funcFLOAT,  /* FLT_PT		[10] */
	NULL,		/* -			[11] */
	funcVAR		/* KEY or VAR   [12] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language
#define KWT_SIZE 10

 TO_DO: Define the list of keywords */
#define KWT_SIZE 17

static rid_char* keywordTable[KWT_SIZE] = {
	"if",
	"else",
	"do",
	"while",
	"int",
	"float",
	"double",
	"string",
	"is",
	"def",
	"return",
	"break",
	"continue",
	"or",
	"and",
	"true",
	"false"
};
/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	rid_char indentationCharType;
	rid_int indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

#endif
