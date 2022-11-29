/* I pledge my Honor that I have not cheated, and will not cheat, on this assignment. - Igli Duro */


/* File codegen.c */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "typecheck.h"



#define MAX_DISM_ADDR 65535
/* Global for the DISM output file */
FILE *fout;

/* Global to access memory locations of main block local variables */
int varMapping[MAX_DISM_ADDR];

/* Global to remember the next unique label number to use */
unsigned int labelNumber = 0;

/* Declare mutually recursive functions (defs and docs appear below) */
void codeGenExpr(ASTree *t, int classNumber, int methodNumber);
void codeGenExprs(ASTree *expList, int classNumber, int methodNumber);

/* Print a message and exit under an exceptional condition */
void internalCGerror(char *msg){
}

/* Using the global classesST, calculate the total number of fields,
 including inherited fields, in an object of the given type */
int getNumObjectFields(int type){
}

/* Generate code that increments the stack pointer */
void incSP(){
	fprintf(fout,"	mov 1 1\n");
	fprintf(fout,"	add 6 6 1	; SP++\n");
}

/* Generate code that decrements the stack pointer */
void decSP(){
	fprintf(fout,"	mov 1 1\n");
	fprintf(fout,"	sub 6 6 1	; SP--\n");
	fprintf(fout,"	bgt 6 5 #%d	; branch if SP>HP\n", labelNumber);
	fprintf(fout,"	mov 1 77	; error code 77 => out of stack memory\n");
	fprintf(fout,"	hlt 1	; out of stack memory (SP <= HP)\n");
	fprintf(fout,"#%d:	mov 0 0\n",labelNumber);
	labelNumber++;
}

void incHP(){
	fprintf(fout,"	mov 1 1\n");
	fprintf(fout,"	add 5 5 1	; HP++\n");
}



/* Output code to check for a null value at the top of the stack.
 If the top stack value (at M[SP+1]) is null (0), the DISM code
 output will halt. */
void checkNullDereference(){
}




/* Generate DISM code for the given single expression, which appears
 in the given class and method (or main block).
 If classNumber < 0 then methodNumber may be anything and we assume
 we are generating code for the program's main block. */
void codeGenExpr(ASTree *t, int classNumber, int methodNumber){

	
  switch(t->typ) {
///////////////////////////////////////////////////////////////////////////////
    case DOT_METHOD_CALL_EXPR:
      break;
///////////////////////////////////////////////////////////////////////////////
    case METHOD_CALL_EXPR:
      break;
///////////////////////////////////////////////////////////////////////////////
    case DOT_ID_EXPR:
      break;
///////////////////////////////////////////////////////////////////////////////
    case ID_EXPR:
	; //Just found out you can't have a var decl immediatly following a label. Very cool, C!
      int i;
      for(i = 0; i < numMainBlockLocals; i++){
    	if(strcmp(mainBlockST[i].varName, t->children->data->idVal) == 0){
	  fprintf(fout,"	lod 1 0 %d	;  load \"%s\" from memory\n", varMapping[i], t->children->data->idVal);
      	  fprintf(fout,"	str 6 0 1	;  M[SP]<-R[r1](variable of type nat)\n");
      	  decSP();
	}
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case DOT_ASSIGN_EXPR:
      break;
///////////////////////////////////////////////////////////////////////////////
    case ASSIGN_EXPR:
      ;
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      fprintf(fout,"	lod 1 6 1	;  r1 gets 2nd operand\n");

      for(i = 0; i < numMainBlockLocals; i++){
    	if(strcmp(mainBlockST[i].varName, t->children->data->idVal) == 0){
	  fprintf(fout,"	str 0 %d 1	;  Assign r1 to \"%s\" in memory\n", varMapping[i], t->children->data->idVal);
	}
      }

      break;
///////////////////////////////////////////////////////////////////////////////
    case PLUS_EXPR:
      codeGenExpr(t->children->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      fprintf(fout,"	lod 1 6 2	; r1 gets the 1st operand\n");
      fprintf(fout,"	lod 2 6 1	; r2 gets the 2nd operand\n");
      fprintf(fout,"	add 1 1 2	; r1<- r1+r2\n");
      fprintf(fout,"	str 6 2 1	; store sum\n");
      incSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case MINUS_EXPR:
      codeGenExpr(t->children->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      fprintf(fout,"	lod 1 6 2	; r1 gets the 1st operand\n");
      fprintf(fout,"	lod 2 6 1	; r2 gets the 2nd operand\n");
      fprintf(fout,"	sub 1 1 2	; r1<- r1-r2\n");
      fprintf(fout,"	str 6 2 1	; store difference\n");
      incSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case TIMES_EXPR:
      codeGenExpr(t->children->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      fprintf(fout,"	lod 1 6 2	; r1 gets the 1st operand\n");
      fprintf(fout,"	lod 2 6 1	; r2 gets the 2nd operand\n");
      fprintf(fout,"	mul 1 1 2	; r1<- r1*r2\n");
      fprintf(fout,"	str 6 2 1	; store product\n");
      incSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case EQUALITY_EXPR: 
      codeGenExpr(t->children->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      int trueLabel = labelNumber++;
      int endTFLabel = labelNumber++;
      fprintf(fout,"	lod 1 6 2	; r1 gets the 1st operand\n");
      fprintf(fout,"	lod 2 6 1	; r2 gets the 2nd operand\n");

      fprintf(fout,"	beq 1 2 #%d	; r1 == r2 check\n", trueLabel);
      fprintf(fout,"	str 6 2 0	; store equality test result (false)\n");
      fprintf(fout,"	jmp 0 #%d	; skip true branch\n", endTFLabel);
      fprintf(fout,"#%d:	mov 1 1		; \n", trueLabel); 
      fprintf(fout,"	str 6 2 1	; store equality test result (true)\n");
      fprintf(fout,"#%d:	mov 0 0	;  end true-false equality test\n", endTFLabel);
      incSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case GREATER_THAN_EXPR: 	//done      break;
      codeGenExpr(t->children->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      trueLabel = labelNumber++;
      int endGTLabel = labelNumber++;
      fprintf(fout,"	lod 1 6 2	; r1 gets the 1st operand\n");
      fprintf(fout,"	lod 2 6 1	; r2 gets the 2nd operand\n");

      fprintf(fout,"	bgt 1 2 #%d	; r1 > r2 check\n", trueLabel);
      fprintf(fout,"	str 6 2 0	; store greater than test result (false)\n");
      fprintf(fout,"	jmp 0 #%d	; skip true branch\n", endGTLabel);
      fprintf(fout,"#%d:	mov 1 1		; \n", trueLabel); 
      fprintf(fout,"	str 6 2 1	; store greater than test result (true)\n");
      fprintf(fout,"#%d:	mov 0 0	;  end true-false greater than test\n", endGTLabel);
      incSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case NOT_EXPR:  	//done
      codeGenExpr(t->children->data, classNumber, methodNumber);
      trueLabel = labelNumber++;
      int endNTLabel = labelNumber++;

      fprintf(fout,"	lod 1 6 1	; r1 gets the 1st operand\n");
      fprintf(fout,"	beq 1 0 #%d	; true false check\n", trueLabel);
      fprintf(fout,"	mov 1 1	\n");
      fprintf(fout,"	str 6 1 1	; store !(false) test result\n");
      fprintf(fout,"	jmp 0 #%d	; skip true branch\n", endNTLabel);
      fprintf(fout,"#%d:	str 6 1 0	; store !(true) test result\n", trueLabel); 
      fprintf(fout,"#%d:	mov 0 0	;  end true-false greater than test\n", endNTLabel);
      break;
///////////////////////////////////////////////////////////////////////////////
    case OR_EXPR:  	//done
      break;
///////////////////////////////////////////////////////////////////////////////
    case IF_THEN_ELSE_EXPR:
	//e1
      codeGenExpr(t->children->data, classNumber, methodNumber);
      int elseLabel = labelNumber++;
      int endLabel = labelNumber++;
      fprintf(fout,"	lod 1 6 1	; load test results into r1\n");
      fprintf(fout,"	beq 0 1 #%d\n", elseLabel);
      incSP();
	//el1
      codeGenExprs(t->children->next->data, classNumber, methodNumber);
      fprintf(fout,"	jmp 0 #%d	;  skip else branch\n", endLabel);
      fprintf(fout,"#%d:	mov 0 0	;  begin else branch\n", elseLabel);
      incSP();
	//el2
      codeGenExprs(t->children->next->next->data, classNumber, methodNumber);
      fprintf(fout,"#%d:	mov 0 0	;  end if-then-else statement\n", endLabel);
    break;


///////////////////////////////////////////////////////////////////////////////

    case FOR_EXPR:
      codeGenExpr(t->children->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->data, classNumber, methodNumber);
      codeGenExpr(t->children->next->next->data, classNumber, methodNumber);
      codeGenExprs(t->children->next->next->next->data, classNumber, methodNumber);


      break;

///////////////////////////////////////////////////////////////////////////////
    case PRINT_EXPR:
      codeGenExpr(t->children->data, classNumber, methodNumber);
      fprintf(fout,"	lod 1 6 1	; load M[SP+1] for printing\n");
      fprintf(fout,"	ptn 1\n");
      decSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case READ_EXPR:
      fprintf(fout,"	rdn 1	;  read nat literal into r1\n");
      fprintf(fout,"	str 6 0 1	;  M[SP]<-R[r1](a nat literal)\n");
      decSP();    
      break;
///////////////////////////////////////////////////////////////////////////////
    case THIS_EXPR:
      break;
///////////////////////////////////////////////////////////////////////////////
    case NEW_EXPR:
	incHP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case NULL_EXPR:     
      fprintf(fout,"	str 6 0 0	; M[SP]<-R[r1](a nat literal)\n");
      decSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case NAT_LITERAL_EXPR: 
      fprintf(fout,"	mov 1 %d\n", t->natVal);
      fprintf(fout,"	str 6 0 1	; M[SP]<-R[r1](a nat literal)\n");
      decSP();
      break;
///////////////////////////////////////////////////////////////////////////////
    case OBJ_TYPE:
      break;
    case NAT_TYPE:
      break;
    default:
      break;

  }
}


/* Generate DISM code for an expression list, which appears in
 the given class and method (or main block).
 If classNumber < 0 then methodNumber may be anything and we assume
 we are generating code for the program's main block. */

void codeGenExprs(ASTree *expList, int classNumber, int methodNumber){

	
  ASTList *childListIterator = expList->children;
  while(childListIterator != NULL) {
    codeGenExpr(childListIterator->data, classNumber, methodNumber);
    childListIterator = childListIterator->next;
  }
}




/* Generate DISM code as the epilogue to the given method or main
 block. If classNumber < 0 then methodNumber may be anything and we
 assume we are generating code for the program's main block. */

void genEpilogue(int classNumber, int methodNumber){
	fprintf(fout,"	hlt 0	;   NORMAL TERMINATION AT END OF MAIN BLOCK\n");
}

/* Generate DISM code for the given method or main block.
 If classNumber < 0 then methodNumber may be anything and we assume
 we are generating code for the program's main block. */

void genBody(int classNumber, int methodNumber){
	codeGenExprs(mainExprs,classNumber, methodNumber);
	genEpilogue(classNumber, methodNumber);
}


/* Generate DISM code as the prologue to the given method or main
 block. If classNumber < 0 then methodNumber may be anything and we
 assume we are generating code for the program's main block. */
void genPrologue(int classNumber, int methodNumber){

	fprintf(fout,"	mov 7 65535	;  initilize FP\n");
	fprintf(fout,"	mov 6 65535	;  initialize SP\n");
	fprintf(fout,"	mov 5 1	;  initilize HP\n");
	fprintf(fout,"	mov 0 0	;  ALLOCATE STACK SPACE FOR MAIN LOCALS\n");
	int i;
	for(i = 0; i < numMainBlockLocals; i++){
		varMapping[i] = 65535 - i;
		fprintf(fout,"	mov 0 0	;  Memory location for variable \"%s\" is M[%d]\n",mainBlockST[i].varName, 65535-i);
		decSP();
	} 
	fprintf(fout,"	mov 0 0	;  BEGIN METHOD/MAIN-BLOCK BODY\n");
	genBody(classNumber, methodNumber);


}


/* Map a given (1) static class number, (2) a method number defined
 in that class, and (3) a dynamic object's type to:
 (a) the dynamic class number and (b) the dynamic method number that
 actually get called when an object of type (3) dynamically invokes
 method (2).
 This method assumes that dynamicType is a subtype of staticClass. */
void getDynamicMethodInfo(int staticClass, int staticMethod,
 int dynamicType, int *dynamicClassToCall, int *dynamicMethodToCall){
}

/* Emit code for the program's vtable, beginning at label #VTABLE.
 The vtable jumps (i.e., dispatches) to code based on
 (1) the dynamic calling object's address (at M[SP+4]),
 (2) the calling object's static type (at M[SP+3]), and
 (3) the static method number (at M[SP+2]). */
void genVtable(){
}




/* Perform code generation for the compiler's input program.
   The code generation is based on the enhanced symbol tables built
   in setupSymbolTables, which is declared in symtbl.h.

   This method writes DISM code for the whole program to the 
   specified outputFile (which must be open and ready for writes 
   before calling generateDISM).

   This method assumes that setupSymbolTables(), declared in 
   symtbl.h, and typecheckProgram(), declared in typecheck.h, 
   have already executed.
*/
void generateDISM(FILE* outputFile) {
	fout = outputFile;
	printf("Start Code Generation\n");
	genPrologue(0,0);
	printf("End Code Generation\n");
}