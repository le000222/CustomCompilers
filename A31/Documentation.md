# RID Language LANGUAGE SPECIFICATION1

## General View
This document focusses on RID LS (Language Specification) that is based RIDEAN language, created by Eri and Dan.
A context-free grammar is used to define the lexical and syntactical parts of the RID LANGUAGE language and the lexical and syntactic structure of a RID LANGUAGE program.

### 1. The RID LANGUAGE Lexical Specification
####  1.1. White Space

White space is defined as the ASCII space, horizontal and vertical tabs, and form feed characters, as well as line terminators. White space is discarded by the scanner.
    <white space> --> one of  {  SPACE, TAB, FF, NL, CR, NLCR }

####  1.2. Comments
RID LANGUAGE supports single-line comments and multi line comments composed of any sequence of characters from the text from the ASCII table. Single line comments are denoted by ( // ) to the end of the line ( \n ). Everything in between is ignored by the scanner. Multi-line comments are denoted by a sequence of ( < and !  ) ASCII table chars, and end with ( ! and > ). Same as single line comments, everything in between this sequence and characters is ignored by the scanner.

    <single line comments> 	-->   //  -->   { any sequence of ASCII chars } -->  \n
    <multi line comments> 	-->   <! -->   { any sequence of ASCII chars } -->  !>

#### 1.3. Variable Identifiers
variable identifiers (VID) tokens are produced by the scanner as VAR_T: Variables can be two kinds of arithmetic tokens: INL_T (integer) and FLT_PT_T (float-point numbers) and can be one kind of string (sequence of ASCII chars): STR_T.

    <variable identifier> --> VAR_T 

#### 1.4. Keywords
The scanner produces a single token: KW_T. The type of the keyword is defined by the attribute of the token (the index of the keywordTable [ ] ). The list of keywords in RID LANGUAGE is given by: 
    if, int, string, float, else, while do, return, break, continue, input, true, false, program
 
#### 1.5. Integer Literals
The scanner produces a single token: INL_T with an integer value as an attribute.

    <integer_literal> --> INL_T

#### 1.6. Floating-point Literals
FLT_PT_T token with a real decimal value as an attribute is produced by the scanner.

    <float_literal> --> FLT_PT_T

#### 1.7. String Literals
STR_T token is produced by the scanner. 

    <string_literal> --> STR_T

#### 1.8. Separators
Separator tokens in RID language are produced to separate a list of arguments or to include a list of arguments to be passed. 

    <separator> --> one of  { ( ){ } , ; }

Six different tokens can be produced by the scanner - LBRACK_T, RBRACK_T, LPAREN_T, RPAREN_T, ARG_SEP_T, EOS_T.

#### 1.9. Operators

    <separator> --> one of { (, ), {, }, ,, ; }

Four tokens can be produced by the scanner: ADDITION_T, SUBTRACT_T, MULTIPLY_T, DIV_T. The type of the operator is defined by the attribute of the token: enum( 0, 1, 2, 3 ): OP_ADD, OP_SUB, OP_MUL, OP_DIV.

    <arithmetic operator> --> one of { +, -, *, / }

Four tokens can be produced by the scanner for relational operators GTR_T, LESS_T, EQUAL_TO_T, NOT_EQ_T and are given attribute number from an enum( 0, 1, 2, 3 ): OP_EQ, OP_NE, OP_GT, OP_LT. The type of the operator is defined by the attribute of the token.

    <relational operator> --> one of { >, <, ==, <> }

Three tokens can be produced by the scanner: AND_OP_T, OR_OP_T, NOT_OP_T. The type of the operator is defined by the attribute of the toke. enum( 0, 1, 2 ): OP_AND, OP_OR, OP_NOT

    <logical operator> --> one of { &  , | , ! }

A single token is produced by the scanner: ASSIGN_T.

    <assignment operator> -->  =


### 2. The RID LANGUAGE Syntactic Specification

#### 2.1. RID LANGUAGE Program

##### 2.1.1. Program
RID LANGUAGE program is composed by one special function: “main” (Method name) defined as follows. The starting point of the program.

    <program> --> main {
    	 <body> | ϵ
    }
    <body> --> <body> <data_session><code_session> | <data_session><code_session>

##### 2.1.2. BODY
The first part (body) is the place we declare the variables or define code recursively:

###### Data Session
    <data_session> --> <opt_varlist_declarations>

###### Variable Lists
The optional variable list declarations are used to define several datatype declarations:

    <opt_varlist_declarations> --> <varlist_declarations> | ϵ
Variable lists are optional and can be denoted as epsilon ( ϵ ). No variable list.

###### Variable Declarations
Variable list declarations can be composed of one single declaration or multiple declarations in the list. Variable declarations start with a keyword token followed by a name attribute and succeeded by assignment of data

 <varlist_declarations>   <varlist_declaration>
			      | <varlist_declaration> <varlist_declarations>

    • PROBLEM DETECTED: Left recursion – SOLVING FOR YOU:

###### New Grammar
<varlist_declarations> --> <varlist_declaration> <varlist_declarationsPrime>
<varlist_declarationsPrime> --> <varlist_declaration> <varlist_declarationsPrime> | ϵ

Each variable declaration can be done as follows:

<varlist_declaration> --> <integer_varlist_declaration>	
		                     | <float_varlist_declaration>
                         | <string_varlist_declaration>

##### 2.1.3. Declaration of Lists:
The variables list declaration is defined here:

    <integer_varlist_declaration> 	-->  int <integer_variable_list>;
    <float_varlist_declaration> 	-->  float <float_variable_list>;
    <string_varlist_declaration> 	-->  string <string_variable_list>;

##### 2.1.4. List of Variables:
The list of variables is defined here:

Integers:
    <integer_variable_list>	 --> 	<integer_variable> | <integer_variable_list>, <integer_variable>
    <integer_variable>	-->  VAR_T
Float-points:
    <float_variable_list>	 --> 	<float_variable> | <float_variable_list>, <float_variable>
    <float_variable>	--> 	VAR_T
Strings:
    <string_variable_list>	--> 	<string_variable> | <float_variable_list>, <string_variable>
    <string_variable>		--> 	VAR_T

##### 2.1.5. Code Session:
The second part is where we can have statements:

    <code_session> --> <opt_statements>

Optional Statements:

    <opt_statements> --> <statements> | ϵ

##### 2.1.6. Statements
    <statements> --> <statement> | <statement> <statements>

• PROBLEM DETECTED: Left recursion – SOLVING FOR YOU:

New Grammar:
    <statements> --> <statement><statementPrime> | <statement>
    <statementPrime> --> <statement><statementPrime> | ϵ


#### 2.2. Statement
    <statement> --> <assignment statement> | <selection statement> | <iteration statement> | <input statement> | <output statement> | <method statement>

##### 2.2.1. Assignment Statement
    <assignment statement> --> <assignment expression>

##### 2.2.2. Assignment Expression
 		<assignment expression> --> <integer_variable> = <arithmetic expression> 
						                  | <float_variable> = <arithmetic expression>
 						                  | <string_variable> = <string expression>
       
##### 2.2.3. Selection Statement (if statement)
 		<selection statement> --> if (<conditional expression>) { <statements> }
   					                  else { <opt_statements> }

##### 2.2.4. Iteration Statement (the loop statement)
 			<iteration statement> --> while (<conditional expression>);
                                | do { <statements>}
						                   while (<conditional expression>);

##### 2.2.5. Input Statement 

    <input statement> --> input (<variable list>);

###### Variable List:
  <variable list> --> <variable identifier> | <variable list>, <variable identifier>

###### Variable Identifier:

 			<variable identifier> --> <integer_variable>
                     					| <integer_variable>
                     					| <string_variable> 

##### 2.2.6. Output Statement 

    <output statement> -->  print (<opt_variable list> | STR_T); 

###### Optional Variable List:

    <opt_variable list> --> <variable list> | ϵ 

##### 2.2.7. Output Statement 
    <method statement> --> MNID_T (<opt_variable list>) { <statements> }
    
#### 2.3. Expressions

##### 2.3.1. Arithmetic Expression

    <arithmetic expression> --> <unary arithmetic expression> | <additive arithmetic expression>	

###### Unary Arithmetic Expression:
    <unary arithmetic expression> --> - <primary arithmetic expression> 
     				| + <primary arithmetic expression>

###### Additive Arithmetic Expression:
    <additive arithmetic expression> -->								
     		  <additive arithmetic expression>  +  <multiplicative arithmetic expression>
     		  | <additive arithmetic expression>  -  <multiplicative arithmetic expression>
     			| <multiplicative arithmetic expression>  

###### Multiplicative Arithmetic Expression:
 	<multiplicative arithmetic expression> --> 
 			 <multiplicative arithmetic expression> * <primary arithmetic expression>
 			| <multiplicative arithmetic expression> / <primary arithmetic expression>
 			| <primary arithmetic expression>
    
###### Primary Arithmetic Expression:
    <primary arithmetic expression> --> <integer_variable>
     					| <float_variable>
     					| FLT_PT_T | INL_T
     					| ( <arithmetic expression> )
      
##### 2.3.2. String Expression
###### Primary String Expression:
    <primary string expression>  -->  <string_variable> |  STR_T

##### 2.3.3. Conditional Expression
    <conditional expression> -->  <logical OR expression>

###### Logical OR Expression:
    <logical  OR expression> --> <logical AND expression>			
        				| <logical OR expression>  |  <logical AND expression>

###### Logical AND Expression:
    <logical AND expression> -->  <logical NOT expression>				
        					| <logical AND expression>  &  <logical NOT expression>
             
###### Logical NOT Expression:
    <logical NOT expression> -->  ! <relational expression> | <relational expression>			 

##### 2.3.4. Relational Expression
    <relational expression> --> <relational a_expression> 

###### Relational Arithmetic Expression:
 	<relational a_expression> -->
  		    <primary a_relational expression>  ==  <primary a_relational expression>
     		| <primary a_relational  expression>  <>  <primary a_relational  expression>
     		| <primary a_relational  expression>  >   <primary a_relational  expression>
     		| <primary a_relational expression>  <   <primary a_relational expression>

###### Primary Arithmetic Relational Expression:
<primary a_relational expression> --> <integer_variable> | <float_variable> | FLT_PT_T  | INL_T
