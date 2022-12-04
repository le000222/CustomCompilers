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
* File name: mainBuffer.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
* Assignment: A32.
* Date: 4 Dec 2022
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
	printf("%s%s\n", STR_LANGNAME, ": source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
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

/*
 ************************************************************
 * Print Warning
 ***********************************************************
 */
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
	printf("%s%s\n", STR_LANGNAME, ": program parsed");
}

/*
 ************************************************************
 * Program oprtional statements
 * BNF: <body> -> <data_session> | <code_session> | <statements>
 * FIRST(<body>) = { KW_T ( KW Type | VAR_T ) ) }
 ***********************************************************
 */
rid_void bodySession() {
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_int:
		case KW_float:
		case KW_string:
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
 * data session
 * BNF: <dataSession> -> <opt_varlist_declarations>
 * FIRST(<opt_varlist_declarations>) = {KW_T | ϵ }.
 ***********************************************************
 */
rid_void dataSession() {
	optVarListDeclarations();
	printf("%s%s\n", STR_LANGNAME, ": optional variable list parsed");

}

/*
 ************************************************************
 * optional variable list declarations
 * BNF: <opt_varlist_declarations> -> <varList_declarations> | ϵ
 * FIRST(<opt_varlist_declarations>) = { KW_T | ϵ }.
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
 * variable list declarations
 * BNF: <varList_declarations> -> <varlist_declaration> | ϵ
 * FIRST ( <var_list_declarations> ) = { KW_T (KW_type) | ϵ  }.
 ***********************************************************
 */
rid_void varListDeclarations() {
	varListDeclaration();
}

/*
 ************************************************************
 * variable list declaration
 * BNF: <varList_declaration> -> <integerVarlistDeclaration><varListDeclarations> | <floatVarlistDeclaration><varListDeclarations> | <stringVarlistDeclaration><varListDeclarations> | ϵ 
 * FIRST(<opt_varlist_declarations>) = { KW_T (KW_int), KW_T (KW_float), KW_T (KW_string), ϵ }.
 ***********************************************************
 */
rid_void varListDeclaration() {
	if (lookahead.code == KW_T) {
		switch (lookahead.attribute.codeType) {
		case KW_int:
			integerVarlistDeclaration();
			varListDeclarations();
			break;
		case KW_float:
			floatVarlistDeclaration();
			varListDeclarations();
			break;
		case KW_string:
			stringVarlistDeclaration();
			varListDeclarations();
			break;
		default:
			;
		}
	}

}


/*
 ************************************************************
 * integerVarlistDeclaration
 * BNF: <integerVarlistDeclaration> -> INL_T <integerVariableList>
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
		printf("%s%s\n", STR_LANGNAME, ": integer variable list parsed");
	}
}

/*
 ************************************************************
 * integerVariableList
 * BNF: <integerVariableList> -> <integerVariable> | <integerVariableList>, <integerVariable>
 * FIRST( <VAR_T> ) = <integerVariable>
 ***********************************************************
 */
rid_void integerVariableList() {
	switch (lookahead.code) {
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		integerVariable();
		break;
	default:
		printError();
		printf("variable expected here\n");
	}
}

/*
 ************************************************************
 * integerVariable
 * BNF: <integerVariable> -> VAR_T -> { ASSIGN_T -> INL_T }
 * FIRST( <integerVariable> ) = { ASSIGN_T, ARG_SEP_T, INL_T, EOS_T }
 ***********************************************************
 */
rid_void integerVariable() {
	switch (lookahead.code) {
	case ASSIGN_T:
		matchToken(ASSIGN_T, NO_ATTR);
		switch (lookahead.code) {
		case INL_T:
			matchToken(INL_T, NO_ATTR);
			if (lookahead.code == ARG_SEP_T) {
				matchToken(ARG_SEP_T, NO_ATTR);
				integerVariableList();
			}
			else {
				matchToken(EOS_T, NO_ATTR);
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
		matchToken(INL_T, NO_ATTR);
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
		printf("%s%s\n", STR_LANGNAME, ": float variable list parsed");
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
	default:
		printError();
		printf("variable expected here");
	}
}

/*
 ************************************************************
 * floatVariable
 * BNF: <floatVariable> -> VAR_T -> { ASSIGN_T -> FLT_PT_T }
 * FIRST( <floatVariable> ) -> { ASSIGN_T, ARG_SEP_T, FLT_PT_T, EOS_T }
 ***********************************************************
 */
rid_void floatVariable() {
	switch (lookahead.code) {
	case ASSIGN_T:
		matchToken(ASSIGN_T, NO_ATTR);
		switch (lookahead.code) {
		case FLT_PT_T:
			matchToken(FLT_PT_T, NO_ATTR);
			if (lookahead.code == ARG_SEP_T) {
				matchToken(ARG_SEP_T, NO_ATTR);
				floatVariableList();
			}
			else {
				matchToken(EOS_T, NO_ATTR);
			}
			break;
		default:
			printError();
			printf("float literal expected here");
		}
		break;
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
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
		printf("float variable expected here\n");
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
		printf("%s%s\n", STR_LANGNAME, ": string variable list parsed");
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
	default:
		printError();
		printf("variable expected here");
	}
}

/*
 ************************************************************
 * stringVariable
 * BNF: <stringVariable> -> VAR_T -> { ASSIGN_T -> STR_T }
 * FIRST( <stringVariable> ) -> { ASSIGN_T, ARG_SEP_T, STR_T, EOS_T }
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
				matchToken(ARG_SEP_T, NO_ATTR);
				stringVariableList();
			}
			else {
				matchToken(EOS_T, NO_ATTR);
			}
			break;
		default:
			printError();
			printf("string literal expected here");
		}
		break;
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
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
 * BNF: <codeSession> -> <opt_statements>
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
rid_void codeSession() {
	optionalStatements();
	printf("%s%s\n", STR_LANGNAME, ": code session parsed");
}

/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print), MNID_T(input) }
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
	printf("%s%s\n", STR_LANGNAME, ": optional statements parsed");
}

/*
 ************************************************************
 * optionalVarlist
 * BNF: <optionalVarlist> -> VAR_T | INL_T | FLT_PT_T | STR_T | MNID_T | KW_T | ϵ
 * FIRST(<optionalVarlist>) = { VAR_T, INL_T, FLT_PT_T, STR_T, MNID_T, KW_T, ϵ }
 ***********************************************************
 */
rid_void optionalVarlist() {
	switch (lookahead.code) {
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
		case KW_true:
			matchToken(KW_T, KW_true);
			break;
		case KW_false:
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
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 ***********************************************************
 */
rid_void statements() {
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement>
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
			conditionalExpression();
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(LPAREN_T, NO_ATTR);
			statements();
			matchToken(RPAREN_T, NO_ATTR);
			break;
		case KW_if:
			matchToken(KW_T, KW_if);
			matchToken(LBRACK_T, NO_ATTR);
			conditionalExpression();
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
			conditionalExpression();
			matchToken(RBRACK_T, NO_ATTR);
			matchToken(EOS_T, NO_ATTR);
			break;
		case KW_int:
		case KW_float:
		case KW_string:
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
	printf("%s%s\n", STR_LANGNAME, ": statement parsed");
}

/*
 ************************************************************
 * Output Statement
 * BNF: <output_statement> -> print (<output_variable_list>);
 * FIRST(<output statement>) = { MNID_T(print) }
 ***********************************************************
 */
rid_void outputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LBRACK_T, NO_ATTR);
	outputVariableList();
	matchToken(RBRACK_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": output statement parsed");
}

/*
 ************************************************************
 * Output Variable List
 * BNF: <output_variable_list> -> <arguments_list> | <output_variable_list> <arguments_list> | ϵ
 * FIRST(<opt_variable_list>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void outputVariableList() {
	argumentsList();
	switch (lookahead.code) {
	case ARG_SEP_T:
		matchToken(ARG_SEP_T, NO_ATTR);
		outputVariableList();
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": output variable list parsed");
}

/*
 ************************************************************
 * input Statements
 * BNF: <input statements> -> <input statement>;
 ***********************************************************
 */
rid_void inputStatements() {
	inputStatement();
}

/*
 ************************************************************
 * input Statement
 * BNF: <input statement> -> input (<input_variable_list>);
 * FIRST(<input statement>) = { MNID_T(input) }
 ***********************************************************
 */
rid_void inputStatement() {
	matchToken(MNID_T, NO_ATTR);
	matchToken(LBRACK_T, NO_ATTR);
	inputVariableList();
	matchToken(RBRACK_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": input statement parsed");
}

/*
 ************************************************************
 * Intput Variable List
 * BNF: <input_variable_list> -> <arguments_list> | <arguments_list> <input_variable_list> | ϵ
 * FIRST(<inputVariableList>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void inputVariableList() {
	argumentsList();
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
 * arguments List
 * BNF: <arguments_list> -> INL_T | FLT_PT_T | STR_T | ϵ
 * FIRST(<variableList>) = { INL_T, FLT_PT_T, STR_T, ϵ }
 ***********************************************************
 */
rid_void argumentsList() {
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
 * BNF: <assignmentStatement> -> <assignmentExpression>
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
		printf("assignment expression expected here");
	}
}

/*
 ************************************************************
 * assignmentExpression
 * BNF: <assignmentExpression> -> <integerVariable> = <arithmetic expression>
								| <floatVariable> = <arithmetic expression>
								| <stringVariable> = <string expression>
 * FIRST(<integerVariable>) = { VAR_T, INL_T, FLT_PT_T, STR_T, ϵ }
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
		case KW_true:
			matchToken(KW_T, KW_true);
			break;
		case KW_false:
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

/*
 ************************************************************
 * Arithmetic Expression
 * BNF: <arithmetic_expression> -> MULTIPLY_T | SUBTRACT_T | ADDITION_T | DIV_T | ϵ
 * FIRST(<integerVariable>) = { MULTIPLY_T, SUBTRACT_T, ADDITION_T, DIV_T, ϵ }
 ***********************************************************
 */
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

/*
 ************************************************************
 * Conditional Expression
 * BNF: <conditional_expression> -> { <integer_variable> | <float_variable> | <string_variable> | KW_T | ϵ }
 *	{ LESS_T | GTR_T | AND_OP_T | OR_OP_T | NOT_OP_T | NOT_EQ_T | EQUAL_TO_T | <arithmetic_expression> } 
 * FIRST(<statement>) = { VAR_T, INL_T, FLT_PT_T, STR_T, KW_T, ϵ, LESS_T, 
							GTR_T, AND_OP_T, OR_OP_T, NOT_OP_T, EQUAL_TO_T }
 ***********************************************************
 */
rid_void conditionalExpression() {
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
		conditionalExpression();
	}
}

/*
 ************************************************************
 * String Expression
 * BNF: <string_expression> -> <primary_string_expression> <string_expression_prime>
 ***********************************************************
 */
rid_void stringExpression() {
	primaryStringExpression();
	stringExpressionPrime();
}

/*
 ************************************************************
 * Primary String Expression
 * BNF: <primary_string_expression> -> <string_variable> <string_expression_prime>
 ***********************************************************
 */
rid_void primaryStringExpression() {
	stringVariable();
	switch (lookahead.code) {
	case ADDITION_T:
		matchToken(ADDITION_T, OP_ADD);
		stringExpressionPrime();
		break;
	}
}

/*
 ************************************************************
 * String Expression Prime
 * BNF: <string_expression_prime> -> <string_expression> 
 ***********************************************************
 */
rid_void stringExpressionPrime() {
	switch (lookahead.code) {
	case STR_T:
		stringExpression();
		break;
	default:
		;
	}
}

