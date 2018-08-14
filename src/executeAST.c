
#include "AST.h"
#include "symbol_table.h"
#include "operations.h"
#include "utils.h"
#include <stdio.h>
#include<stdlib.h>

int executeBlock(node *);
int executeStatement(node *);
void executeAssignment(node *);
void executePoeticAssignment(node *);
void executeIncrement(node *);
void executeDecrement(node *);
void executePrint(node *);
void executeScan(node *);
int executeIfStatement(node *);
void executeIfElseStatement(node *);
void executeWhileStatement(node *);
void executeFunctionDefinition(node *);
void executeList(node *, node *);
symbol * executeFunctionCall(node *);
symbol *executeAddItemToList(node *);
symbol *executeAddItemCallList(node *);
symbol *executeExpression(node *);
char *executeIdentifier(node *);
symbol *executeLogicalLiteral(node *);
symbol *executeNumLiteral(node *);
symbol *executeStringLiteral(node *);
symbol *executeNullLiteral(node *);


int executeBlock(node *block)
{
  if(block == NULL)
  {
    return 0;
  }
  int b = executeBlock(block -> left);


  if(b != 0)
  {
    return b;
  }
  if(block -> right -> type == continueType)
  {
    return 1;
  }
  if(block -> right -> type == breakType)
  {
    return 2;
  }
  return executeStatement(block -> right);

}

int executeStatement(node *s)
{
  switch (s -> type)
  {
    case assignmentType:        executeAssignment(s); break;
    case incrementType:         executeIncrement(s); break;
    case decrementType:         executeDecrement(s); break;
    case poeticAssignmentType:  executePoeticAssignment(s); break;
    case scanType:              executeScan(s); break;
    case printType:             executePrint(s); break;
    case ifType:                return executeIfStatement(s);
    case ifElseType:            executeIfElseStatement(s); break;
    case whileType:             executeWhileStatement(s); break;
    case functionDefinitionType:executeFunctionDefinition(s); break;
    default : fprintf(stderr, "not valid statement\n");
  }
  return 0;
}

void executeIncrement(node *s)
{
  char *varName = executeIdentifier(s -> value.e);
  symbol * v = findSymbol(varName);
  if(v -> varType == NUMBER_TYPE)
  {
    double value = v->value.num + 1;
    updateSymbol(varName, NUMBER_TYPE, &value);
    free(varName);
    return;
  }
  if(v -> varType == NULL_TYPE)
  {
    double value = 1;
    updateSymbol(varName, NUMBER_TYPE, &value);
    free(varName);
    return;
  }
  if(v -> varType == BOOLEAN_TYPE)
  {
    double value = v -> value.boolean + 1;
    updateSymbol(varName, NUMBER_TYPE, &value);
    free(varName);
  }

  fprintf(stderr, "%s is not a number type\n", varName);
  free(varName);

}

void executeDecrement(node *s)
{
  char *varName = executeIdentifier(s -> value.e);
  symbol * v = findSymbol(varName);
  if(v -> varType == NUMBER_TYPE)
  {
    double value = v->value.num - 1;
    updateSymbol(varName, NUMBER_TYPE, &value);
    free(varName);
    return;
  }
  if(v -> varType == NULL_TYPE)
  {
    double value = -1;
    updateSymbol(varName, NUMBER_TYPE, &value);
    free(varName);
    return;
  }
  if(v -> varType == BOOLEAN_TYPE)
  {
    double value = v -> value.boolean - 1;
    updateSymbol(varName, NUMBER_TYPE, &value);
    free(varName);
  }

  fprintf(stderr, "%s is not a number type\n", varName);
  free(varName);

}



void executeWhileStatement(node *s)
{
  symbol * value = executeExpression(s -> value.e);
  while(value -> value.boolean == 1)
  {
    int b = executeBlock(s -> left);
    if(b == 2)
    {
      break;
    }
    value = executeExpression(s -> value.e);
  }
  deleteSymbol(value);
}
int executeIfStatement(node *s)
{
  symbol * value = executeExpression(s -> value.e);
  int b = 0;
  if(value -> value.boolean == 1)
  {
    b = executeBlock(s -> left);
  }
  deleteSymbol(value);
  return b;
}

void executeIfElseStatement(node *s)
{
  symbol * value = executeExpression(s -> value.e);
  if(value -> value.boolean == 1)
  {
    executeBlock(s -> left);
  }
  else if(value -> value.boolean == 0)
  {
    executeBlock(s -> right);
  }
  deleteSymbol(value);
}

void executeAssignment(node *s)
{
  symbol * value = executeExpression(s -> left);
  char *varName = executeIdentifier(s -> right);

  switch (value -> varType)
  {
    case NUMBER_TYPE:   updateSymbol(varName, NUMBER_TYPE, &(value->value.num)); break;
    case STRING_TYPE:   updateSymbol(varName, STRING_TYPE, (value->value.string)); break;
    case BOOLEAN_TYPE:  updateSymbol(varName, BOOLEAN_TYPE, &(value->value.boolean)); break;
    case NULL_TYPE:     updateSymbol(varName, NULL_TYPE, NULL); break;
    default : fprintf(stderr, "assignment not supported\n");
  }
  free(varName);
  deleteSymbol(value);
}


void executePoeticAssignment(node *s)
{
  char *varName = executeIdentifier(s->left);
  updateSymbol(varName, NUMBER_TYPE, &(s -> value.num));
  free(varName);
}

void executePrint(node *s)
{
  symbol * value = executeExpression(s -> left);
  printSymbol(value);
  deleteSymbol(value);
}

void executeScan(node *s)
{
  char *varName = executeIdentifier(s->left);
  char * i = getInput();
  updateSymbol(varName, STRING_TYPE, i);
  free(i);
  free(varName);
}


symbol *executeExpression(node *s)
{

  symbol *leftValue, *rightValue, *result;
  char *varName;
  switch(s->type)
  {
    case expressionType :      leftValue = executeExpression(s->left); rightValue = executeExpression(s->right); result = evalaute(leftValue, rightValue, s -> value.op);   deleteSymbol(leftValue);   deleteSymbol(rightValue); return result;
    case numLiteralType :      return executeNumLiteral(s);
    case booleanLiteralType :  return executeLogicalLiteral(s);
    case stringLiteralType :   return executeStringLiteral(s);
    case identifierType :      varName = executeIdentifier(s); result = copySymbol(varName); free(varName); return result;
    case nullLiteralType:      return executeNullLiteral(s);
    case functionCallType:     return executeFunctionCall(s);
    default             :      return NULL;
  }
  return NULL;
}

char *executeIdentifier(node *s)
{
  return concat("", s->value.s);
}

symbol *executeNumLiteral(node *s)
{
  return updateSymbol("_", NUMBER_TYPE, &(s->value.num));
}

symbol *executeStringLiteral(node *s)
{
  return updateSymbol("_", STRING_TYPE, s->value.s);
}

symbol *executeLogicalLiteral(node *s)
{
  return updateSymbol("_", BOOLEAN_TYPE, &(s->value.boolean));
}

symbol *executeNullLiteral(node *s)
{
  return updateSymbol("_", NULL_TYPE, NULL);
}

void executeFunctionDefinition(node *s)
{
  char *fname = executeIdentifier(s->value.e);
  updateSymbol(fname, OBJECT_TYPE, s);
  free(fname);
}

symbol * executeFunctionCall(node *s)
{
  char * varName = executeIdentifier(s->left);
  symbol *f = findSymbol(varName);
  if(f -> varType != OBJECT_TYPE)
  {
    fprintf(stderr, "%s is not a function\n", varName);
    return NULL;
  }
  free(varName);
  node *func = (node *)(f -> value.ptr);
  executeList(func ->left, s -> right);
  executeBlock(func -> right -> left);

  return executeExpression(func -> right -> right);
}

void executeList(node *id, node *ex)
{

  if(id  == NULL )
  {
    if(ex != NULL)
    {
      fprintf(stderr, "lalalaDifferent number of arguments\n");
      return ;
    }
  }

  if(ex == NULL)
  {
    if(id != NULL)
    {
      fprintf(stderr, "Different number of arguments\n");
      return;
    }
  }

  if(ex == NULL && id == NULL)
  {
    return;
  }

  executeList(id -> left, ex -> left);
  char *varName = executeIdentifier(id -> right);
  renameSymbol(executeExpression(ex->right), varName);
  free(varName);
}
