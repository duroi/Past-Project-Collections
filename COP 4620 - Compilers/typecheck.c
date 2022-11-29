/* I pledge my Honor that I have not cheated, and will not cheat, on this assignment. - Igli Duro */


/* File typecheck.c */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "typecheck.h"



/* Level I: typecheckProgram correctly type checks all DJ programs that 
(1) declare no classes and 
(2) declare no local variables (hence you never even need to use the symbol tables). 

Please note that at this level you can only assume that DJ programs
input to your type checker declare no classes and no variables; input programs may
still contain expressions with identifiers, the new keyword, the null keyword, etc.
Expect to write about 250 lines of code for this level. 

Level II: typecheckProgram correctly type checks all DJ programs that declare no classes. 
For this level, expect to write about 50 lines of code beyond that of Level I. 8^)

*/
void typecheckProgram()
{
  int type;
  //printf("Start type checking\n");
  

  int i;
  int j;
  //Check for variable duplicates
  for(i = 0; i < numMainBlockLocals; i++){
    for (j = i + 1; j < numMainBlockLocals; j++){
      if( strcmp(mainBlockST[i].varName, mainBlockST[j].varName) == 0){
	printf("Semantic analysis error on line %d:\n", mainBlockST[j].varNameLineNumber);
  	printf("    Variable '%s' declared multiple times in 'main'\n", mainBlockST[j].varName);
	exit(1); 
      }
    }
  }
  //Print statement for testing
  //printAST(wholeProgram); 
  //printAST(mainExprs);

  type = typeExprs(mainExprs, 0, 0);
  //printf("%d\n", type);
  //printf("Type checking complete: No errors found\n");	

}


int typeExpr(ASTree *t, int classContainingExpr, int methodContainingExpr)
{
  //printf("Start typeExpr\n");

  if(t == NULL) {
    printf("Internal Type Checking error"); 
    exit(1);}
	
  switch(t->typ) {

    case DOT_METHOD_CALL_EXPR: break;

    case METHOD_CALL_EXPR:     break;

    case DOT_ID_EXPR:          break;
///////////////////////////////////////////////////////////////////////////////
    case ID_EXPR:             
      if( t->children == NULL) {
	printf("Null child in 'id'\n");
	exit(1);}
      int i;
	//Check if ID was declared
      for(i = 0; i < numMainBlockLocals; i++){
      	if(strcmp(mainBlockST[i].varName, t->children->data->idVal) == 0) return -1; 
      }  
      printf("Semantic analysis error on line %d:\n",t->lineNumber);
      printf("    '%s' was not declared 'main'\n", t->children->data->idVal);
      exit(1); 
      break;
///////////////////////////////////////////////////////////////////////////////

    case DOT_ASSIGN_EXPR:      break;

    case ASSIGN_EXPR:          break;
///////////////////////////////////////////////////////////////////////////////
    case PLUS_EXPR:	//done;
      if( t->children == NULL || t->children->next == NULL) {
	printf("Null child in plus\n");
	exit(1);}
      if(typeExpr(t->children->data,0,0) == -1){
	if(typeExpr(t->children->next->data,0,0) == -1) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     non-nat type in 'plus' expression\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     non-nat type in 'plus' expression\n");
        exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case MINUS_EXPR:	//done           
      if( t->children == NULL || t->children->next == NULL) {
	printf("Null child in minus\n");
	exit(1);}
      if(typeExpr(t->children->data,0,0) == -1){
	if(typeExpr(t->children->next->data,0,0) == -1) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     non-nat type in 'minus' expression\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     non-nat type in 'minus' expression\n");
        exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case TIMES_EXPR:	//done
      if( t->children == NULL || t->children->next == NULL) {
	printf("Null child in times\n");
	exit(1);}
      if(typeExpr(t->children->data,0,0) == -1){
	if(typeExpr(t->children->next->data,0,0) == -1) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     non-nat type in 'times' expression\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     non-nat type in 'times' expression\n");
        exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case EQUALITY_EXPR: //done
      if( t->children == NULL || t->children->next == NULL) {
	printf("Null child in equality\n");
	exit(1);}

	//both children are type nat
      if(typeExpr(t->children->data,0,0) == -1){
	if(typeExpr(t->children->next->data,0,0) == -1) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     mismatched nat/non-nat in 'equality' expression\n");
	  exit(1);
	}
      }
	//both children are type object/null
      else if((0 == typeExpr(t->children->data,0,0)) || (typeExpr(t->children->data,0,0) == -2)){

	if((0 == typeExpr(t->children->next->data,0,0)) || (typeExpr(t->children->next->data,0,0) == -2)) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     mismatched object/non-object type in 'equality' expression\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     illegal type in 'equality' expression\n");
        exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case GREATER_THAN_EXPR: 	//done
      if( t->children == NULL || t->children->next == NULL) {
	printf("Null child in greater than\n");
	exit(1);}
      if(typeExpr(t->children->data,0,0) == -1){
	if(typeExpr(t->children->next->data,0,0) == -1) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     non-nat type in 'greater than' expression\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     non-nat type in 'greater than' expression\n");
        exit(1);
      }
      break;

///////////////////////////////////////////////////////////////////////////////
    case NOT_EXPR:  	//done
      if( t->children == NULL) {
        printf("Null child in 'not'\n");
	exit(1);}
      if(typeExpr(t->children->data,0,0) == -1) return -1;
      else {
	printf("Semantic analysis error on line %d:\n", t->lineNumber);
	printf("     non-nat type in 'not' expression\n");
	exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case OR_EXPR:  	//done
      if( t->children == NULL || t->children->next == NULL) {
	printf("Null child in 'or'\n");
	exit(1);}
      if(typeExpr(t->children->data,0,0) == -1){
	if(typeExpr(t->children->next->data,0,0) == -1) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     non-nat type in 'or' expression\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     non-nat type in 'or' expression\n");
        exit(1);
      }
      break;


///////////////////////////////////////////////////////////////////////////////
    case IF_THEN_ELSE_EXPR:	//done
      if(t->children == NULL || t->children->next == NULL || t->children->next->next == NULL) {
	printf("Null child in if-then-else\n");
	exit(1);}

	//if is type nat
      if(typeExpr(t->children->data,0,0) == -1){
	//both children expression lists are nat type
        if(typeExprs(t->children->next->data,0,0) == -1){
            if(typeExprs(t->children->next->next->data,0,0) == -1) return -1;
            else{
                printf("Semantic analysis error on line %d:\n", t->lineNumber);
                printf("     mismatched nat/non nat type in 'then' and 'else' expression \n");
                exit(1);
            }
        }
	//both children expression lists are object type
        else if((0 == typeExprs(t->children->next->data,0,0)) || (typeExprs(t->children->next->data,0,0) == -2)){
            if((0 == typeExprs(t->children->next->next->data,0,0)) || (typeExprs(t->children->next->next->data,0,0) == -2)) return 0;
            else {
                printf("Semantic analysis error on line %d:\n", t->lineNumber);
                printf("     mismatched object/non-object nat type in 'then' and 'else' expressionn");
                exit(1);
            }
        }
        else {
          printf("Semantic analysis error on line %d:\n", t->lineNumber);
          printf("     illegal type in 'if-then-else' expression\n");
          exit(1);
         }
    }
    else {
	printf("Semantic analysis error on line %d:\n", t->lineNumber);
	printf("     non-nat type in 'if' expression\n");
	exit(1);
    }
    break;


///////////////////////////////////////////////////////////////////////////////

    case FOR_EXPR:	//Done
      if(t->children == NULL || t->children->next == NULL || t->children->next->next == NULL || t->children->next->next->next == NULL) {
	printf("Null child in 'for'\n");
	exit(1);}
	//check loop expressions
      if(typeExpr(t->children->data,0,0) == -1 && typeExpr(t->children->next->data,0,0) == -1 
         && typeExpr(t->children->next->next->data,0,0) == -1) {
	//check expression list 
	if(typeExprs(t->children->next->next->next->data,0,0) != -3) return -1;
	else {
	  printf("Semantic analysis error on line %d:\n", t->lineNumber);
	  printf("     illegal type in 'for' expression list\n");
	  exit(1);
	}
      }
      else {
        printf("Semantic analysis error on line %d:\n", t->lineNumber);
        printf("     non-nat type in 'for-loop' expression\n");
        exit(1);
      }
      break;

///////////////////////////////////////////////////////////////////////////////
    case PRINT_EXPR:
      if( t->children == NULL) {
        printf("Null child in printNat\n");
	exit(1);
      }
      if(typeExpr(t->children->data,0,0) == -1) return -1;
      else {
	printf("Semantic analysis error on line %d:\n", t->lineNumber);
	printf("     non-nat type in 'printNat' expression\n");
	exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case READ_EXPR:
      return -1; 
      break;

    case THIS_EXPR:            break;
///////////////////////////////////////////////////////////////////////////////
    case NEW_EXPR:	//null
      if( t->children == NULL) {
        printf("Null child in new\n");
	exit(1);
      }
      if(typeExpr(t->children->data,0,0) == 0) return 0;
      else {
	printf("Semantic analysis error on line %d:\n", t->lineNumber);
	printf("     non Object or illegal type in 'new' expression\n");
	exit(1);
      }
      break;
///////////////////////////////////////////////////////////////////////////////
    case NULL_EXPR:     
      return -2;
      break;
    case NAT_LITERAL_EXPR: 
      return -1; 
      break;
    case OBJ_TYPE:
      return 0;
      break;
    case NAT_TYPE:
      return -1;
      break;
    default:
      return -3;  
      break;
  }	
}


int typeExprs(ASTree *t, int classContainingExprs, int methodContainingExprs){

  //printf("Start typeExprs\n");

  int type;

  if(t == NULL){
    printf("Internal Type Checking error");
    exit(1);	
  }
  ASTList *childListIterator = t->children;
  while(childListIterator!=NULL) {
    type = typeExpr(childListIterator->data, 0, 0);
    childListIterator = childListIterator->next;
  }	
  //printf("%d\n", type);
  return type;
}




