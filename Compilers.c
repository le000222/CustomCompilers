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
* File name: Compilers.c
* Compiler: MS Visual Studio 2022
* Author: [Ngoc Phuong Khanh Le, 041004318], [Dan McCue, 040772626]
* Course: CST 8152 � Compilers, Lab Section: [011]
* Assignment: A12.
* Date: Oct 01 2022
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main(), printLogo().
************************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Paramters: Command line parameters - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

rid_int main(int argc, char** argv) {
	rid_int i;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	rid_char option = toupper(argv[1][0]);

	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER ....]\n\n");
		mainScanner(argc, argv);
		break;

	case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;

	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: pRINT lOGO
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: -
* parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/
rid_void printLogo() {
	/*
	boa_char* strLogo = " _________________________________\n|                                 |\n| ........ RID LANGUAGE ......... |\n|     __    __    __    __        |\n|    /  \\  /  \\  /  \\  /  \\       |\n| __/  __\\/  __\\/  __\\/  __\\__    |\n| _/  /__/  /__/  /__/  /_____|   |\n|  \\_/ \\   / \\   / \\   / \\  \\___  |\n|       \\_/   \\_/   \\_/   \\___o_> |\n|                                 |\n| .. ALGONQUIN COLLEGE - 2022F .. |\n|_________________________________|\n";
	printf("%s", strLogo);
	*/
	printf("%s%s%s%s%s%s%s%s%s%s%s%s%s",
		" _____________________________________\n",
		"|                                    |\n",
		"| ....... 'RID' LANGUAGE ........    |\n",
		"|    _____    _______    _____       |\n",
		"|   ||   \\\\    || ||    ||    \\\\     |\n",
		"|   ||    \\\\   || ||    ||     \\\\    |\n",
		"|   || ___//   || ||    ||      \\\\   |\n",
		"|   ||  \\\\     || ||    ||      //   |\n",
		"|   ||   \\\\    || ||    ||     //    |\n",
		"| __||__  \\\\___||_||____||____//     |\n",
		"|                                    |\n",
		"|  ..ALGONQUIN COLLEGE - 2022F ..    |\n",
		"|____________________________________|\n"
	);
}
