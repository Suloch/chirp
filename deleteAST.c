
#include "AST.h"
#include "symbol_table.h"
#include <stdio.h>
#include<stdlib.h>

void deleteIfStatement(node *);
void deleteIfElseStatement(node *);
void deleteWhileStatement(node*);
void deleteAssignment(node *);
void deleteScan(node *);
void deletePrint(node *);
void deletePoeticAssignment(node *);
void deleteExpression(node *);
void deleteBlock(node *);
void deleteNumLiteral(node *);
void deleteLogicalLiteral(node *);
void deleteStringLiteral(node *);
void deleteNullLiteral(node *);
void deleteIdentifier(node *);
void deleteDecrement(node *);
void deleteFunctionDefinition(node *);
void deleteFunctionCall(node *);
void deleteList(node *);
void deleteCallList(node *);
void deleteContinue(node *);
void deleteBreak(node *);


void deleteStatement(node *s)
{
  switch (s -> type)
  {
    case assignmentType:        deleteAssignment(s); break;
    case incrementType:
    case decrementType:         deleteDecrement(s); break;
    case poeticAssignmentType:  deletePoeticAssignment(s); break;
    case scanType:              deleteScan(s); break;
    case printType:             deletePrint(s); break;
    case ifType:                deleteIfStatement(s); break;
    case ifElseType:            deleteIfElseStatement(s); break;
    case whileType:             deleteWhileStatement(s); break;
    case continueType:          deleteContinue(s); break;
    case breakType:             deleteBreak(s);
    case functionDefinitionType: break;
    default : fprintf(stderr, "%dnot valid statement\n", s->type);
  }
}

void deleteAssignment(node *s)
{
  deleteExpression(s -> left);
  deleteIdentifier(s -> right);
  free(s);
}

void deleteDecrement(node *s)
{
  free(s -> value.e);
  free(s);
}
void deletePoeticAssignment(node *s)
{
    deleteIdentifier(s -> left);
    free(s);
}

void deleteScan(node *s)
{
  deleteIdentifier(s -> left);
  free(s);
}

void deletePrint(node *s)
{
  deleteExpression(s -> left);
  free(s);
}
void deleteIfStatement(node *s)
{
  deleteBlock(s->left);
  deleteExpression(s->value.e);

  free(s);
}

void deleteWhileStatement(node *s)
{
  deleteBlock(s -> left);
  deleteExpression(s->value.e);

  free(s);
}
void deleteIfElseStatement(node *s)
{
  deleteBlock(s->left);
  deleteBlock(s->right);
  deleteExpression(s->value.e);

  free(s);
}
void deleteBlock(node *s)
{
  if(s == NULL)
  {
    return;
  }
  deleteBlock(s -> left);
  deleteStatement(s -> right);

  free(s);
}

void deleteExpression(node *s)
{
  switch(s->type)
  {
    case expressionType :      deleteExpression(s->left); deleteExpression(s->right); free(s);break;
    case numLiteralType :      deleteNumLiteral(s); break;
    case booleanLiteralType :  deleteLogicalLiteral(s); break;
    case stringLiteralType :   deleteStringLiteral(s); break;
    case identifierType :      deleteIdentifier(s); break;
    case nullLiteralType:      deleteNullLiteral(s);break;
    case functionCallType:     deleteFunctionCall(s); break;
    default             :      break;
  }

}

void deleteIdentifier(node *s)
{
    free(s -> value.s);
    free(s);
}

void deleteNumLiteral(node *s)
{
  free(s);
}

void deleteStringLiteral(node *s)
{
  free(s->value.s);
  free(s);
}

void deleteLogicalLiteral(node *s)
{
  free(s);
}

void deleteNullLiteral(node *s)
{
  free(s);
}

void deleteFunctionDefinition(node *s)
{
  deleteBlock(s->right->left);
  deleteExpression(s->right->right);
  free(s->right);
  deleteList(s->left);
  free(s);
}
void deleteFunctionCall(node *s)
{
  deleteIdentifier(s->left);
  deleteCallList(s->right);
  free(s);
}

void deleteList(node *s)
{
  if(s == NULL)
  {
    return;
  }
  deleteList(s -> left);
  deleteIdentifier(s -> right);
  free(s);
}

void deleteCallList(node *s)
{
  if(s == NULL)
  {
    return;
  }
  deleteCallList(s -> left);
  deleteExpression(s -> right);
  free(s);
}

void deleteBreak(node *s)
{
  free(s);
}

void deleteContinue(node *s)
{
  free(s);
}
