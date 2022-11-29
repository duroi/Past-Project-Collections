/* I pledge my Honor that I have not cheated, and will not cheat, on this assignment. - Igli Duro */

/* This bison-input file simply declares tokens for DJ programs
     (enumerated below on all the lines that begin with %token)
     and has a main funtion to repeatedly invoke the lexer.
*/

%code provides {
  #include "lex.yy.c"

  /* Function for printing generic syntax-error messages */
  void yyerror(const char *str) {
    printf("Syntax error on line %d at token %s\n",
           yylineno,yytext);
    printf("Halting compiler.\n");
    exit(-1);
  }
}

%token CLASS ID EXTENDS MAIN NATTYPE OBJECT
%token NATLITERAL PRINTNAT READNAT IF ELSE FOR
%token PLUS MINUS TIMES EQUALITY GREATER OR NOT 
%token ASSIGN NUL NEW THIS DOT SEMICOLON
%token LBRACE RBRACE LPAREN RPAREN ENDOFFILE

%start pgm

%right ASSIGN
%left PLUS MINUS
%left TIMES
%nonassoc OR
%nonassoc EQUALITY GREATER
%right NOT
%nonassoc DOT

%%

pgm : class main ENDOFFILE 
      { return 0; }
    ;

class 	: class CLASS ID EXTENDS sclass LBRACE var methodb RBRACE
	|
	;

sclass 	: OBJECT
	| ID
	;

var 	: var NATTYPE ID SEMICOLON
	| var ID ID SEMICOLON
	| var OBJECT ID SEMICOLON
	|
	;

method 	: method NATTYPE ID LPAREN type ID RPAREN varex
	| NATTYPE ID LPAREN type ID RPAREN varex
	| method OBJECT ID LPAREN type ID RPAREN varex
	| OBJECT ID LPAREN type ID RPAREN varex
	| method ID ID LPAREN type ID RPAREN varex
	| ID ID LPAREN type ID RPAREN varex
	;

type 	: NATTYPE
	| OBJECT
	| ID
	;

methodb : method
	|
	;

varex	: LBRACE var elist RBRACE
	;

main 	: MAIN varex
	;

elist	: elist expr SEMICOLON
	| expr SEMICOLON
	;

expr	: expr PLUS expr
	| expr MINUS expr
	| expr TIMES expr
	| expr EQUALITY expr
	| expr GREATER expr
	| NOT expr
	| expr OR expr
	| NATLITERAL
	| NUL
	| IF LPAREN expr RPAREN LBRACE elist RBRACE ELSE LBRACE elist RBRACE
	| FOR LPAREN expr SEMICOLON expr SEMICOLON expr RPAREN LBRACE elist RBRACE
	| NEW ID LPAREN RPAREN
	| THIS 
	| PRINTNAT LPAREN expr RPAREN
	| READNAT LPAREN RPAREN
	| ID
	| expr DOT ID
	| ID ASSIGN expr
	| expr DOT ID ASSIGN expr
	| ID LPAREN expr RPAREN
	| expr DOT ID LPAREN expr RPAREN
	| LPAREN expr RPAREN
	| ASSIGN expr
	;

%%

int main(int argc, char **argv) {
  if(argc!=2) {
    printf("Usage: dj-parse filename\n");
    exit(-1);
  }
  yyin = fopen(argv[1],"r");
  if(yyin==NULL) {
    printf("ERROR: could not open file %s\n",argv[1]);
    exit(-1);
  }
  /* parse the input program */
  return yyparse();
}
