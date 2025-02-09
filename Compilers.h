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
***********************************************************
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Author: [Ngoc Phuong Khanh Le, 041004318], [Dan McCue, 040772626]
* Course: CST 8152 � Compilers, Lab Section: [011]
* Assignment: A12.
* Date: Oct 01 2022
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), printLogo().
************************************************************
*/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */
 
/* Logical constants - adapt for your language */
#define RID_TRUE  1
#define RID_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/
/* TO_DO: Define your typedefs */
typedef char			rid_char;
typedef int				rid_int;
typedef float			rid_float;
typedef void			rid_void;

typedef unsigned char	rid_boln;
typedef unsigned char	rid_byte;

typedef long			rid_long;
typedef double			rid_double;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'R',
	PGM_SCANNER = 'S',
	PGM_PARSER	= 'P'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
rid_int mainReader  (rid_int argc, rid_char** argv);
rid_int mainScanner (rid_int argc, rid_char** argv);
rid_int mainParser  (rid_int argc, rid_char** argv);
rid_void printLogo();

#endif
