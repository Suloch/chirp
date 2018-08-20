
#include "symbol_table.h"
#include "utils.h"
#include<string.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>

symbol * calc(double a, double b, char op)
{
  double r;
  unsigned int s;
  switch(op)
  {
    case '+': r = a + b; return updateSymbol("_", NUMBER_TYPE, &r);
    case '-': r = a - b; return updateSymbol("_", NUMBER_TYPE, &r);
    case '*': r = a * b; return updateSymbol("_", NUMBER_TYPE, &r);
    case '/': r = a / b; return updateSymbol("_", NUMBER_TYPE, &r);
    case '>': s = a > b; return updateSymbol("_", BOOLEAN_TYPE, &s);
    case '<': s = a < b; return updateSymbol("_", BOOLEAN_TYPE, &s);
    case 'l': s = a <= b; return updateSymbol("_", BOOLEAN_TYPE, &s);
    case 'm': s = a >= b; return updateSymbol("_", BOOLEAN_TYPE, &s);
    case '=': s = a == b; return updateSymbol("_", BOOLEAN_TYPE, &s);
    case 'n': s = a != b; return updateSymbol("_", BOOLEAN_TYPE, &s);
  }
  return updateSymbol("_", NULL_TYPE, NULL);
}

symbol * evalaute(symbol *op1, symbol *op2, char op)
{
  if(op1 -> varType == NUMBER_TYPE)
  {
    if(op2 -> varType == NUMBER_TYPE)
    {
      return calc(op1->value.num, op2->value.num, op);
    }
    else if(op2 -> varType == BOOLEAN_TYPE)
    {
      return calc(op1->value.num, (double)(op2->value.boolean), op);
    }
    else if(op2 -> varType == NULL_TYPE)
    {
      return calc(op1->value.num, 0, op);
    }
  }

  if(op1 -> varType == BOOLEAN_TYPE)
  {
    if(op2 -> varType == NUMBER_TYPE)
    {
      return calc((double)(op1->value.boolean), op2->value.num, op);
    }
    else if(op2 -> varType == BOOLEAN_TYPE)
    {
      return calc((double)(op1->value.boolean), (double)(op2->value.boolean), op);
    }
    else if(op2 -> varType == NULL_TYPE)
    {
      return calc((double)(op1->value.boolean), 0, op);
    }
  }

  if(op1 -> varType == NULL_TYPE)
  {
    if(op2 -> varType == NUMBER_TYPE)
    {
      return calc(0, op2->value.num, op);
    }
    else if(op2 -> varType == BOOLEAN_TYPE)
    {
      return calc(0, (double)(op2->value.boolean), op);
    }
    else if(op2 -> varType == NULL_TYPE)
    {
      return calc(0, 0, op);
    }
  }

  if(op1 -> varType == STRING_TYPE)
  {
    if(op2 -> varType == STRING_TYPE)
    {
      if(op == '+')
      {
        char * res = concat(op1 -> value.string, op2 -> value.string);
        symbol * r = updateSymbol("_", STRING_TYPE, res);
        free(res);
        return r;
      }
    }
  }
  return updateSymbol("_", NULL_TYPE, NULL);
}
