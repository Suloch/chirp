
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "symbol_table.h"
#define RANDOM 17

symbol *table[LENGTH];

int literalCount = 0;
char *lastSymbol;


void updateLastSymbol(char *varName)
{
  free(lastSymbol);
  lastSymbol = strdup(varName);
}

void initializeTable()
{
  int i;
  for(i = 0; i < LENGTH; i++)
  {
    table[i] = NULL;
  }
}

int hashGenerator(char *varName)
{
  int num = RANDOM;
  int n = strlen(varName);
  int i;
  for(i = 0; i < n; i++)
  {
    num = num + varName[i];
  }

  num = num % LENGTH;

  return num;
}


void insertAtTail(symbol *newsymbol, int pos)
{
  if(table[pos] == NULL)
  {
    table[pos] = newsymbol;
    return;
  }
  symbol *curr = table[pos];

  while(curr -> next != NULL)
  {
    curr = curr -> next;
  }

  curr -> next = newsymbol;
}

/*add symbols to the symbol table according to the data type
if the varName = '_', then sets the function generated variable name to varName.
This is used for storing the literals and the value of expressions
dont use this, use updateSymbol
*/
symbol * addSymbol(char *varName, int varType, void *data)
{
  if(varName[0] == '_')
  {
    varName = malloc(20*sizeof(char));
    sprintf(varName, LITERAL_HEADER"%d", literalCount);
    literalCount++;
  }
  else
  {
    updateLastSymbol(varName);
  }
  int pos = hashGenerator(varName);
  symbol * newsymbol = NULL;

  newsymbol = malloc(sizeof(symbol));
  newsymbol -> varName = malloc(strlen(varName)+1);
  newsymbol -> next = NULL;
  strcpy(newsymbol -> varName, varName);
  newsymbol -> varType = varType;

  if(newsymbol -> varType == NUMBER_TYPE)
  {
    newsymbol -> value.num = *(double *)data;
    insertAtTail(newsymbol,pos);
    return newsymbol;
  }

  if(varType == STRING_TYPE)
  {
    newsymbol -> value.string = malloc(strlen((char *)data)+1);
    strcpy(newsymbol -> value.string, (char *)data);

    insertAtTail(newsymbol,pos);
    return newsymbol;
  }

  if(varType == NULL_TYPE)
  {
    newsymbol -> value.boolean = 0;
    insertAtTail(newsymbol, pos);
    return newsymbol;
  }

  if(varType == BOOLEAN_TYPE)
  {
    newsymbol -> value.boolean = *(unsigned int *)data;
    insertAtTail(newsymbol, pos);
    return newsymbol;
  }
  if(varType == MYSTERIOUS_TYPE)
  {
    insertAtTail(newsymbol, pos);
    return newsymbol;
  }
  if(varType == LIST_TYPE)
  {
    newsymbol -> value.ptr = data;
    newsymbol -> size = 1;
    insertAtTail(newsymbol, pos);
    return newsymbol;
  }
  if(varType == OBJECT_TYPE)
  {
    newsymbol -> value.ptr = data;
    insertAtTail(newsymbol, pos);
    return newsymbol;
  }
  free(newsymbol);
  return NULL;
}

//always updateSymbol should be called and never addSymbol
symbol * updateSymbol(char *varName, int varType, void *data)
{
  symbol * found = findSymbol(varName);
  if(found == NULL)
  {
    return addSymbol(varName, varType, data);
  }

  deleteSymbol(found);

  return addSymbol(varName, varType, data);
}

symbol * findSymbol(char *varName)
{
  if(varName[0] != '_')
  {
    updateLastSymbol(varName);
  }
  int pos = hashGenerator(varName);

  symbol *curr = table[pos];
  while(curr != NULL)
  {

    if(strcmp(curr -> varName, varName) == 0)
    {
      return curr;
    }
    curr = curr -> next;
  }
  return NULL;
}


//function to make a copy of the symbol and return it
symbol * copySymbol(char *varName)
{
  symbol *s  = findSymbol(varName);
  if(s == NULL)
  {
    return NULL;
  }

  if(s->varType == STRING_TYPE)
  {
    return updateSymbol("_", STRING_TYPE, s->value.string);
  }

  if(s->varType == NUMBER_TYPE)
  {
    return updateSymbol("_", NUMBER_TYPE, &(s->value.num));
  }

  if(s -> varType == BOOLEAN_TYPE)
  {
    return updateSymbol("_", BOOLEAN_TYPE, &(s -> value.boolean));
  }
  if(s->varType == NULL_TYPE)
  {
    return updateSymbol("_", NULL_TYPE, NULL);
  }
  fprintf(stderr, "could not copy %s%d\n", varName, s->varType);
  return NULL;
}

//function to delete symbol from table
int deleteSymbol(symbol *s)
{
    int pos = hashGenerator(s->varName);
    symbol * curr = table[pos];
    if(curr == s)
    {
      table[pos] = table[pos] -> next;
    }
    else
    {
      while(curr -> next != s)
      {
        curr = curr -> next;
      }
      curr -> next = s -> next;
    }

    if(s->varType == STRING_TYPE)
    {
      free(s->value.string);
    }

    if(s->varType == MYSTERIOUS_TYPE)
    {
      free(s->value.string);
    }

    if(s -> varType == OBJECT_TYPE)
    {
      return 1;
    }
    free(s->varName);
    free(s);
    return 0;
}

void printSymbol(symbol *s)
{
  if(s->varType == STRING_TYPE)
  {
    printf("%s\n", s->value.string);
  }

  else if(s->varType == NUMBER_TYPE)
  {
    printf("%f\n", s->value.num);
  }
  else if(s->varType == NULL_TYPE)
  {
    printf("NULL\n");
  }
  else if(s ->varType == BOOLEAN_TYPE)
  {
    if(s -> value.boolean == 1)
    {
      printf("true\n");
    }
    else
    {
      printf("false\n");
    }
  }
  else
  {
    fprintf(stderr, "Unknown type\n");
  }
}


void renameSymbol(symbol * n, char * varName)
{
  if(n -> varType == NUMBER_TYPE)
  {
    updateSymbol(varName, NUMBER_TYPE, &(n->value.num));
  }
  else if(n -> varType == STRING_TYPE)
  {
    updateSymbol(varName, STRING_TYPE, n->value.string);
  }
  else if(n -> varType == BOOLEAN_TYPE)
  {
    updateSymbol(varName, BOOLEAN_TYPE, &(n->value.boolean));
  }
  else
  {
    fprintf(stderr, "Cannot rename %s to %s\n", n -> varName, varName);
    return;
  }
  deleteSymbol(n);
}

symbol ** getTable()
{
  return table;
}
