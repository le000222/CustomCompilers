/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2022
* Author: Svillen Ranev - Paulo Sousa
* Professors: Paulo Sousa
************************************************************
 _________________________________
|                                 |
| ........ rid LANGUAGE ......... |
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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*
************************************************************
 * Process Parser
 ***********************************************************
 */
/* TO_DO: This is the function to start the parser - check your program definition */

rid_void startParser() {
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
/* TO_DO: This is the main code for match - check your definition */
rid_void matchToken(rid_int tokenCode, rid_int tokenAttribute) {
	rid_int matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute) {
			matchFlag = 0;
		}
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
/* TO_DO: This is the function to handler error - adjust basically datatypes */
rid_void syncErrorHandler(rid_int syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
/* TO_DO: This is the function to error printing - adjust basically datatypes */
rid_void printError() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LBRACK_T:
		printf("LBRACK_T\n");
		break;
	case RBRACK_T:
		printf("RBRACK_T\n");
		break;
	case LPAREN_T:
		printf("LPAREN_T\n");
		break;
	case RPAREN_T:
		printf("RPAREN_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
	}
}

rid_void printWarning() {
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Warning:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LBRACK_T:
		printf("LBRACK_T\n");
		break;
	case RBRACK_T:
		printf("RBRACK_T\n");
		break;
	case LPAREN_T:
		printf("LPAREN_T\n");
		break;
	case RPAREN_T:
		printf("RPAREN_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner warning: token code: ", t.code);
	}
}

/*
 ************************************************************
 * Program start
 * BNF: <MNID_T> -> main { <body> | ϵ }
 * FIRST(<MNID_T>) = main
 * 
 ***********************************************************
 */
rid_void program() {
	switch (lookahead.code) {
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_MAIN, 5) == 0) {
			matchToken(MNID_T, NO_ATTR);
			matchToken(LBRACK_T, NO_ATTR);
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(LPAREN_T, NO_ATTR);
			while (lookahead.code != RPAREN_T) {
				bodySession();
			}
			matchToken(RPAREN_T, NO_ATTR);
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * Program oprtional statements
 * BNF: <body> -> <body><data_session><code_session> | <data_session><code_session>
 * FIRST(<body>) = ( <data_session> = { KW_T (KW Type) | (VAR_T) ) | <code_session> = (MNID_T)
 *
 ***********************************************************
 */
rid_void bodySession() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case 0:
		case 1:
		case 2:
			dataSession();
			break;
		case KW_while:
		case KW_if:
		case KW_do:
			statements();
			break;
		default:
			;
		}
		break;
	case MNID_T:
		codeSession();
		break;
	case VAR_T:
		statements();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	case RPAREN_T:
		return;
	default:
		printError();
	}
	return;
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> <opt_varlist_declarations>
 * FIRST(<opt_varlist_declarations>) = {KW_T | ϵ }.
 ***********************************************************
 */
rid_void dataSession() {
	switch (lookahead.code) {
	case KW_T:
		optVarListDeclarations();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Opt Var list parsed");

}

/*
 ************************************************************
 * optVarlistDeclarations
 * BNF: <opt_varlist_declarations> -> <varListDeclarations>
 * FIRST(<opt_varlist_declarations>) = {KW_T | ϵ }.
 ***********************************************************
 */
rid_void optVarListDeclarations() {
	switch (lookahead.code) {
	case KW_T:
		varListDeclarations();
		break;
	default:
		; // MT
	}
}

/*
 ************************************************************
 * varListDeclarations
 * BNF: <varListDeclarations> -> <varlist_declaration> <varlist_declarationsPrime> | ϵ
 * FIRST ( <varListDeclarations> ) = { KW_T (KW_type) | ϵ  }.
 ***********************************************************
 */
rid_void varListDeclarations() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_int:
			varListDeclaration();
			break;
		case KW_string:
			varListDeclaration();
			break;
		case KW_float:
			varListDeclaration();
			break;
		default:
			; //MT
		}
	}
}

/*
 ************************************************************
 * varListDeclarationsPrime
 * BNF: <varListDeclarationsPrime> -> <varlist_declaration> <varlist_declarationsPrime> | ϵ
 * FIRST ( <varListDeclarationsPrime> ) = { KW_T (KW_int), KW_T (KW_float), KW_T (KW_string), ϵ  }.
 ***********************************************************
 */
rid_void varListDeclarationsPrime() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_int:
			varListDeclaration();
			varListDeclarationsPrime();
			break;
		case KW_float:
			varListDeclaration();
			varListDeclarationsPrime();
			break;
		case KW_string:
			varListDeclaration();
			varListDeclarationsPrime();
			break;
		default:
			; //MT
		}
	}
}
/*
 ************************************************************
 * varListDeclaration
 * BNF: <varListDeclaration> -> <integerVarlistDeclaration> | <floatVarlistDeclaration> | <stringVarlistDeclaration>
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (KW_int), KW_T (KW_float), KW_T (KW_string)}.
 ***********************************************************
 */

rid_void varListDeclaration() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_int:
			integerVarlistDeclaration();
			varListDeclarationsPrime();
			break;
		case KW_float:
			floatVarlistDeclaration();
			varListDeclarationsPrime();
			break;
		case KW_string:
			stringVarlistDeclaration();
			varListDeclarationsPrime();
			break;
		default:
			;
		}
	}
}

/*
 ************************************************************
 * integerVarlistDeclaration
 * BNF: <integerVarlistDeclaration> -> INL_T <integerVarlist>
 * FIRST( <INL_T> ) = <integerVarlist>;
 ***********************************************************
 */
rid_void integerVarlistDeclaration() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_int:
			matchToken(KW_T, KW_int);
			integerVariableList();
			break;
		default:
			;
		}
		printf("%s%s\n", STR_LANGNAME, ": integer Var list parsed");
	}
}

/*
 ************************************************************
 * integerVariablelist
 * BNF: <integerVariablelist> -> <integerVariable> | <integerVariablelist>, <integerVariable>
 * FIRST( <integerVariable> ) = INL_T
 ***********************************************************
 */
rid_void integerVariableList() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		integerVariable();
		break;
	case ARG_SEP_T:
		integerVariable();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		printError();
		printf("variable expected here\n");
	}
}

/*
 ************************************************************
 * integerVariable
 * BNF: <integerVariable> -> VAR_T
 * FIRST( <VAR_T> )
 ***********************************************************
 */
rid_void integerVariable() {
	switch (lookahead.code) {
	case ASSIGN_T:
		matchToken(ASSIGN_T, NO_ATTR);
		switch (lookahead.code) {
		case INL_T:
			matchToken(INL_T, lookahead.attribute.intValue);
			if (lookahead.code == ARG_SEP_T) {
				matchToken(ARG_SEP_T, NO_ATTR);
				integerVariableList();
			}
			break;
		default:
			printError();
			printf("integer literal expected here\n");
		}
		break;
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
		integerVariableList();
		break;
	case INL_T:
		matchToken(INL_T, lookahead.attribute.intValue);
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		printError();
		printf("integer variable expected here\n");
	}
	printf("%s%s\n", STR_LANGNAME, ": integer variable parsed");
}

/*
 ************************************************************
 * floatVarlistDeclaration
 * BNF: <floatVarlistDeclaration> -> FLT_PT_T <floatVariableList>
 * FIRST( <FLT_PT_T> ) = <floatVariableList>;
 ***********************************************************
 */
rid_void floatVarlistDeclaration() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_float:
			matchToken(KW_T, KW_float);
			floatVariableList();
			break;
		default:
			;
		}
		printf("%s%s\n", STR_LANGNAME, ": float Var list parsed");
	}
}
/*
 ************************************************************
 * floatVariableList
 * BNF: <floatVariableList> -> <floatVariable> | <floatVariableList>, <floatVariable>
 * FIRST( <VAR_T> ) = <floatVariable>
 ***********************************************************
 */
rid_void floatVariableList() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		floatVariable();
		break;
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
		floatVariableList();
		break;
	default:
		printError();
		printf("variable expected here");
	}
}

/*
 ************************************************************
 * floatVariable
 * BNF: <floatVariable> -> VAR_T -> { ASSIGN_T -> FLT_PT_T }
 * FIRST( <VAR_T> ) -> EOS_T | ARG_SEP_T
 ***********************************************************
 */
rid_void floatVariable() {
	switch (lookahead.code) {
	case ASSIGN_T:
		matchToken(ASSIGN_T, NO_ATTR);
		switch (lookahead.code) {
		case FLT_PT_T:
			matchToken(FLT_PT_T, KW_float);
			if (lookahead.code == ARG_SEP_T) {
				floatVariableList();
			}
			break;
		default:
			printError();
			printf("float literal expected here");
		}
		break;
	case ARG_SEP_T:
		floatVariableList();
		break;
	case FLT_PT_T:
		matchToken(FLT_PT_T, KW_float);
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		printError();
		printf("float variable expected here");
	}
	printf("%s%s\n", STR_LANGNAME, ": float variable parsed");
}


/*
 ************************************************************
 * stringVarlistDeclaration
 * BNF: <stringVarlistDeclaration> -> STR_T <stringVarlist>
 * FIRST( <KW_string> ) = <stringVarlist>;
 ***********************************************************
 */
rid_void stringVarlistDeclaration() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_string:
			matchToken(KW_T, KW_string);
			stringVariableList();
			break;
		default:
			;
		}
		printf("%s%s\n", STR_LANGNAME, ": string Var list parsed");
	}
}
/*
 ************************************************************
 * stringVariableList
 * BNF: <stringVariableList> -> <stringVariable> | <stringVariableList>, <stringVariable>
 * FIRST( <VAR_T> ) = <stringVariable>
 ***********************************************************
 */
rid_void stringVariableList() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		stringVariable();
		break;
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
		stringVariableList();
		break;
	default:
		printError();
		printf("variable expected here");
	}
}

/*
 ************************************************************
 * stringVariable
 * BNF: <stringVariable> -> VAR_T -> { ASSIGN_T -> STR_T }
 * FIRST( <VAR_T> ) -> EOS_T | ARG_SEP_T
 ***********************************************************
 */
rid_void stringVariable() {
	switch (lookahead.code) {
	case ASSIGN_T:
		matchToken(ASSIGN_T, NO_ATTR);
		switch (lookahead.code) {
		case STR_T:
			matchToken(STR_T, lookahead.attribute.contentString);
			if (lookahead.code == ARG_SEP_T) {
				stringVariableList();
			}
			break;
		default:
			printError();
			printf("string literal expected here");
		}
		break;
	case ARG_SEP_T:
		stringVariableList();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, lookahead.attribute.contentString);
		break;
	default:
		printError();
		printf("string variable expected here");
	}
	printf("%s%s\n", STR_LANGNAME, ": string variable parsed");
}
/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
rid_void codeSession() {
	optionalStatements();
	printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
}

/* TO_DO: Continue the development (all non-terminal functions) */

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
rid_void optionalStatements() {
	switch (lookahead.code) {
	case MNID_T:
		if ((strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) ||
			(strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0)) {
			statements();
			break;
		}
		else {
			matchToken(MNID_T, NO_ATTR);
			matchToken(LBRACK_T, NO_ATTR);
			optionalVarlist();
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(EOS_T, NO_ATTR);
		}
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
rid_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
rid_void statementsPrime() {
	statement();
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement> | <argument statement>
 * FIRST(<statement>) = { KW_T { INL_T, PLT_PT_T, STR_T }, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input), MNID_T(print), MNID_T { ... }
 ***********************************************************
 */
rid_void statement() {
	switch (lookahead.code) {
	case KW_T:
		switch(lookahead.attribute.codeType) {
		case KW_while:
			matchToken(KW_T, KW_while);
			matchToken(LBRACK_T, NO_ATTR);
			conditonalExpression();
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(LPAREN_T, NO_ATTR);
			statements();
			matchToken(RPAREN_T, NO_ATTR);
			break;
		case KW_if:
			matchToken(KW_T, KW_if);
			matchToken(LBRACK_T, NO_ATTR);
			conditonalExpression();
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(LPAREN_T, NO_ATTR);
			statements();
			matchToken(RPAREN_T, NO_ATTR);
			if (lookahead.attribute.codeType == KW_else) {
				matchToken(KW_T, KW_else);
				matchToken(LPAREN_T, NO_ATTR);
				statements();
				matchToken(RPAREN_T, NO_ATTR);
			}
			break;
		case KW_do:
			matchToken(KW_T, KW_do);
			matchToken(LPAREN_T, NO_ATTR);
			statements();
			matchToken(RPAREN_T, NO_ATTR);
			matchToken(KW_T, KW_while);
			matchToken(LBRACK_T, NO_ATTR);
			conditonalExpression();
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(EOS_T, NO_ATTR);
			break;
		case 0:
		case 1:
		case 2:
			dataSession();
			statementsPrime();
			break;
		}
		break;
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 6) == 0) {
			outputStatement();
			statementsPrime();
		}
		else if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 6) == 0) {
			inputStatements();
		}
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		assignmentStatement();
		break;
	case RPAREN_T:
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}


rid_void argumentStatement() {
	switch(lookahead.attribute.codeType) {
	case KW_int:
		matchToken(KW_T, KW_int);
		if (lookahead.code == INL_T) {
			matchToken(INL_T, NO_ATTR);
		}
		else if (lookahead.code == VAR_T) {
			matchToken(VAR_T, NO_ATTR);
		}
		break;
	case KW_string:
		matchToken(KW_T, KW_string);
		if (lookahead.code == STR_T) {
			matchToken(STR_T, lookahead.attribute.contentString);
		}
		else if (lookahead.code == VAR_T) {
			matchToken(VAR_T, NO_ATTR);
		}
		break;
	case KW_float:
		matchToken(KW_T, KW_float);
		if (lookahead.code == FLT_PT_T) {
			matchToken(FLT_PT_T, NO_ATTR);
		}
		else if (lookahead.code == VAR_T) {
			matchToken(VAR_T, NO_ATTR);
		}
		break;
	default:
		printError();
	}
}
/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print) }
 ***********************************************************
 */
rid_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LBRACK_T, NO_ATTR);
	outputVariableList();
	matchToken(RBRACK_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

/*
 ************************************************************
 * input Statement
 * BNF: <input statement> -> input (<input statementPrime>);
 * FIRST(<input statement>) = { MNID_T(input) }
 ***********************************************************
 */
rid_void inputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LBRACK_T, NO_ATTR);
	inputVariableList();
	matchToken(RBRACK_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Intput statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void outputVariableList() {
	variableList();
	switch (lookahead.code) {
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
		outputVariableList();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

/*
 ************************************************************
 * intput Variable List
 * BNF: <inputVariableList> -> <variable list> | ϵ
 * FIRST(<inputVariableList>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void inputVariableList() {
	variableList();
	switch (lookahead.code) {
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
		inputVariableList();
		break;		
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": input variable list parsed");
}

/*
 ************************************************************
 * optionalVarlist
 * BNF: <optionalVarlist> -> <statements>
 * FIRST(<optionalVarlist>) = { VAR_T,  }
 ***********************************************************
 */
rid_void optionalVarlist() {
	switch(lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case INL_T:
		matchToken(INL_T, NO_ATTR);
		break;
	case FLT_PT_T:
		matchToken(FLT_PT_T, NO_ATTR);
		break;
	case STR_T:
		matchToken(STR_T, lookahead.attribute.contentString);
		break;
	case MNID_T:
		matchToken(MNID_T, NO_ATTR);
		matchToken(LBRACK_T, NO_ATTR);
		optionalVarlist();
		matchToken(RBRACK_T, NO_ATTR);
		break;
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case 10:
			matchToken(KW_T, KW_true);
			break;
		case 11:
			matchToken(KW_T, KW_false);
			break;
		default:
			printError();
		}
	default:
		;
	}

	if (lookahead.code == ARG_SEP_T) {
		matchToken(ARG_SEP_T, NO_ATTR);
		optionalVarlist();
	}
}
/*
 ************************************************************
 * variableList
 * BNF: <variableList> -> <variableList> | ϵ
 * FIRST(<variableList>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void variableList() {
	switch (lookahead.code) {
	case STR_T:
		stringVariable();
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case INL_T:
		integerVariable();
		break;
	case FLT_PT_T:
		floatVariable();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": argument parsed");
}

/*
 ************************************************************
 * assignmentStatement
 * BNF: <assignmentStatement> -> <assignmentStatementExpression>
 * FIRST(<assignmentStatement>) = { ASSIGN_T }
 ***********************************************************
 */
rid_void assignmentStatement() {
	switch (lookahead.code) {
	case ASSIGN_T:
		matchToken(ASSIGN_T, NO_ATTR);
		assignmentExpression();
		break;
	case EOS_T:
		matchToken(EOS_T, NO_ATTR);
		printWarning();
		printf("variable statement with no assignment");
		statementsPrime();
	default:
		printError();
		printf("Assignment expression expected here");
	}
}

/*
 ************************************************************
 * assignmentExpression
 * BNF: <assignmentExpression> -> <integerVariable> = <arithmetic expression>
								| <floatVariable> = <arithmetic expression>
								| <stringVariable> = <string expression>
 * FIRST(<integerVariable>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void assignmentExpression() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case INL_T:
		integerVariable();
		break;
	case FLT_PT_T:
		floatVariable();
		break;
	case STR_T:
		stringExpression();
		break;
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case 10:
			matchToken(KW_T, KW_true);
			break;
		case 11:
			matchToken(KW_T, KW_false);
			break;
		default:
			;
		}
	default:
		;
	}
	arithmaticExpression();
	if (lookahead.code != EOS_T) {
		assignmentExpression();
	}
	else {
		matchToken(EOS_T, NO_ATTR);
		statementsPrime();
	}
}

rid_void arithmaticExpression() {
	switch (lookahead.code) {
	case MULTIPLY_T:
		matchToken(MULTIPLY_T, OP_MUL);
		break;
	case SUBTRACT_T:
		matchToken(SUBTRACT_T, OP_SUB);
		break;
	case ADDITION_T:
		matchToken(ADDITION_T, OP_ADD);
		break;
	case DIV_T:
		matchToken(DIV_T, OP_DIV);
		break;
	default:
		;
	}
}

rid_void conditonalExpression() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	case INL_T:
		integerVariable();
		break;
	case FLT_PT_T:
		floatVariable();
		break;
	case STR_T:
		stringVariable();
		break;
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case 10:
			matchToken(KW_T, KW_true);
			break;
		case 11:
			matchToken(KW_T, KW_false);
			break;
		default:
			printError();
		}
		break;
	default:
		;
	}

	switch (lookahead.code) {
	case LESS_T:
		matchToken(LESS_T, OP_LT);
		break;
	case GTR_T:
		matchToken(GTR_T, OP_GT);
		break;
	case AND_OP_T:
		matchToken(AND_OP_T, OP_AND);
		break;
	case OR_OP_T:
		matchToken(OR_OP_T, OP_OR);
		break;
	case NOT_OP_T:
		matchToken(NOT_OP_T, OP_NOT);
		break;
	case NOT_EQ_T:
		matchToken(NOT_EQ_T, OP_NOT);
		break;
	case EQUAL_TO_T:
		matchToken(EQUAL_TO_T, OP_EQ);
		break;
	default:
		arithmaticExpression();
	}

	if (lookahead.code != RBRACK_T) {
		conditonalExpression();
	}
}
rid_void stringExpression() {
	primaryStringExpression();
	stringExpressionPrime();
}

rid_void primaryStringExpression() {
	stringVariable();
	switch (lookahead.code) {
	case ADDITION_T:
		matchToken(ADDITION_T, OP_ADD);
		stringExpressionPrime();
		break;
	}
}

rid_void stringExpressionPrime() {
	switch (lookahead.code) {
	case STR_T:
		stringExpression();
		break;
	default:
		;
	}
}

rid_void inputStatements() {
	inputStatement();
}


/*
 ************************************************************
 * iterationStatement
 * BNF: <iterationStatement> -> while (<conditional expression>);
      						   | do { <statements>}
							     while (<conditional expression>);

 * FIRST(<iterationStatement>) = { KW_T (KW_while) | (KW_do) }
 ***********************************************************
 */
rid_void iterationStatement() {

}