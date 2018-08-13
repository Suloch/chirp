
#include "AST.h"
#include "utils.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <stdio.h>


node *allocateMemory(char *s)
{
  node *b = malloc(sizeof(node));
  if(b == NULL)
  {
    fprintf(stderr, "Cannot allocate memory for %s\n", s);
    return NULL;
  }

  return b;
}


node *makeBlock(node *block, node *statement)
{
  node *b = allocateMemory("block");

  b -> type = blockType;
  b -> left = block;
  b -> right = statement;

  return b;
}

node *makeScan(node *Identifier)
{
  node *s = allocateMemory("scan");

  s -> type = scanType;
  s -> left = Identifier;
  s -> right = NULL;

  return s;
}

node *makePrint(node *Expression)
{
  node *p = allocateMemory("print");

  p -> type = printType;
  p -> left = Expression;
  p -> right = NULL;

  return p;
}

node *makeAssignment(node *Expression, node *Identifier)
{
  node *a = allocateMemory("assignment");

  a -> type = assignmentType;
  a -> left = Expression;
  a -> right = Identifier;

  return a;
}

node *makeAssignmentPoetic(node *Identifier, double num)
{
  node * a = allocateMemory("poetic assignment");

  a -> type = poeticAssignmentType;
  a -> value.num = num;
  a -> left = Identifier;
  a -> right = NULL;

  return a;
}

node *makeExpression(node *el, char op, node *er)
{
  node *e = allocateMemory("expression");

  e -> type = expressionType;
  e -> value.op = op;
  e -> left = el;
  e -> right = er;

  return e;
}


node *makeIdentifier(char *varName)
{
  node *i = allocateMemory("identifier");

  i -> type = identifierType;
  if(varName[0] == '_')
  {
    i -> value.s = concat("", lastSymbol);
  }
  else
  {
    i -> value.s = concat("", varName);
  }
  i -> left = NULL;
  i -> right = NULL;

  return i;
}

node *makeNumLiteral(double num)
{
  node *l = allocateMemory("number literal");

  l -> type = numLiteralType;
  l -> value.num = num;
  l -> left = NULL;
  l -> right = NULL;

  return l;
}

node *makeStringLiteral(char *s)
{
  node * l = allocateMemory("string literal");

  l -> type = stringLiteralType;
  l -> value.s = concat("", s);
  l -> left = NULL;
  l -> right = NULL;

  return l;
}

node *makeLogicalLiteral(unsigned int boolean)
{
  node * l = allocateMemory("boolean literal");

  l -> type = booleanLiteralType;
  l -> value.boolean = boolean;
  l -> left = NULL;
  l -> right = NULL;

  return l;
}

node *makeNullLiteral(void)
{
  node * l = allocateMemory("NULL Literal");

  l -> type = nullLiteralType;
  l -> left = NULL;
  l -> right = NULL;

  return l;
}

node *makeIfStatement(node *e, node *b)
{
  node * i = allocateMemory("if statement");
  i -> type = ifType;
  i -> value.e = e;
  i -> left = b;
  i -> right = NULL;

  return i;
}

node *makeIfElseStatement(node *e, node *bif, node *belse)
{
  node *i = allocateMemory("if else statement");
  i -> type = ifElseType;
  i -> value.e = e;
  i -> left = bif;
  i -> right = belse;

  return i;
}

node *makeWhileStatement(node *e, node *b)
{
  node * i = allocateMemory("if statement");
  i -> type = whileType;
  i -> value.e = e;
  i -> left = b;
  i -> right = NULL;

  return i;
}

node *makeIncrement(node *id)
{
  node *i = allocateMemory("increment");
  i -> type = incrementType;
  i -> value.e = id;
  i -> left = NULL;
  i -> right = NULL;

  return i;
}

node *makeDecrement(node *id)
{
  node *i = allocateMemory("decrement");
  i -> type = decrementType;
  i -> value.e = id;
  i -> left = NULL;
  i -> right = NULL;

  return i;
}



node *makeFunctionDefinition(node *i, node *l, node *b, node *re)
{
  node *fd = allocateMemory("function definition");

  node *temp = allocateMemory("block + expression");

  temp -> left = b;
  temp -> right = re;

  fd -> type = functionDefinitionType;

  fd -> value.e = i;
  fd -> left = l;
  fd -> right = temp;
  return fd;
}

node *makeAddItemToList(node *l, node *i)
{
  node *ai = allocateMemory("adding item to list");
  ai -> left = l;
  ai -> right = i;
  return ai;
}

node *makeFunctionCall(node *i, node *l)
{
  node *fc = allocateMemory("function call");
  fc -> type = functionCallType;
  fc -> left = i;
  fc -> right = l;
  return fc;
}

node *makeAddItemToCallList(node *l, node *e)
{
  node *cl = allocateMemory("adding item to list");
  cl -> left = l;
  cl -> right = e;
  return cl;
}

node *makeBreak()
{
  node *b = allocateMemory("break");
  b -> type = breakType;
  b -> right = NULL;
  b -> left = NULL;
  return b;
}

node *makeContinue()
{
  node *c = allocateMemory("continue");
  c -> type = continueType;
  c -> right = NULL;
  c -> left = NULL;
  return c;
}
