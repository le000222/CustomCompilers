/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ BOA LANGUAGE ......... |
|     __    __    __    __        |
|    /  \  /  \  /  \  /  \       |
| __/  __\/  __\/  __\/  __\__    |
| _/  /__/  /__/  /__/  /_____|   |
|  \_/ \   / \   / \   / \  \___  |
|       \_/   \_/   \_/   \___o_> |
|                                 |
| .. ALGONQUIN COLLEGE - 2022F .. |
|_________________________________|

*/

/*
************************************************************
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A12.
* Date: Sep 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */
#include <stdlib.h> /* including so can use C lic funtions */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR (-1)						/* General error message */
#define READER_TERMINATOR '\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX		-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for RID */
/* BITS                                (7654.3210) */
/* Whenever any of the flag is called, these bits must be set */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
/* TO_DO: BIT 3: FUL = Full */
#define READER_SET_FULL		0x08	/* 0000.1000 */
#define READER_CHK_FULL		0x08	/* 0000.1000 */
#define READER_RST_FULL		0xF7	/* 1111.0111 */
/* TO_DO: BIT 2: EMP: Empty */
#define READER_SET_EMP		0x04	/* 0000.0100 */
#define READER_CHK_EMP		0x04	/* 0000.0100 */
#define READER_RST_EMP		0xFC	/* 1111.1011 */
/* TO_DO: BIT 1: REL = Relocation */
#define READER_SET_REL		0x02	/* 0000.0010 */
#define READER_CHK_REL		0x02	/* 0000.0010 */
#define READER_RST_REL		0xFD	/* 1111.1101 */
/* TO_DO: BIT 0: END = EndOfBuffer */
#define READER_SET_END		0x01	/* 0000.0001 */
#define READER_CHK_END		0x01	/* 0000.0001 */
#define READER_RST_END		0xFE	/* 1111.1110 */

#define NCHAR				128			/* Chars from 0 to 127 */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	rid_int		mark;			/* the offset to the mark position (in chars) */
	rid_int		read;			/* the offset to the get a char position (in chars) */
	rid_int		wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	rid_char*	content;			/* pointer to the beginning of character array (character buffer) */
	rid_int		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	rid_int		increment;			/* character array increment factor */
	rid_int		mode;				/* operational mode indicator */
	rid_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position	position;			/* Offset / position field */
	rid_int		histogram[NCHAR];	/* Statistics of chars */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate(rid_int, rid_int, rid_int);
ReaderPointer	readerAddChar(ReaderPointer const, rid_char);
rid_boln		readerClear(ReaderPointer const);
rid_boln		readerFree(ReaderPointer const);
rid_boln		readerIsFull(ReaderPointer const);
rid_boln		readerIsEmpty(ReaderPointer const);
rid_boln		readerSetMark(ReaderPointer const, rid_int);
rid_int			readerPrint(ReaderPointer const);
rid_int			readerLoad(ReaderPointer const, FILE* const);
rid_boln		readerRecover(ReaderPointer const);
rid_boln		readerRetract(ReaderPointer const);
rid_boln		readerRestore(ReaderPointer const);
/* Getters */
rid_char		readerGetChar(ReaderPointer const);
rid_char*		readerGetContent(ReaderPointer const, rid_int);
rid_int			readerGetPosRead(ReaderPointer const);
rid_int			readerGetPosWrte(ReaderPointer const);
rid_int			readerGetPosMark(ReaderPointer const);
rid_int			readerGetSize(ReaderPointer const);
rid_int			readerGetInc(ReaderPointer const);
rid_int			readerGetMode(ReaderPointer const);
rid_byte		readerGetFlags(ReaderPointer const);
rid_int			readerShowStat(ReaderPointer const);
rid_void		readerPrintHistogram(ReaderPointer const readerPointer);

#endif