
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "utils.h"


char * getInput(char *buffer)
{
  int bufferSize = 1;
  int n = 0;
  buffer = malloc(bufferSize*sizeof(char));
  if(buffer == NULL)
  {
    fprintf(stderr, "Input buffer couldn't be allocated\n");
    return NULL;
  }


  char ch = fgetc(stdin);

  while(ch != '\n')
  {
    if(n == bufferSize - 1)
    {
      bufferSize = bufferSize * 2;
      buffer = realloc(buffer, bufferSize);
      if(buffer == NULL)
      {
        fprintf(stderr, "Input buffer couldn't be allocated\n");
        return NULL;
      }
    }
    buffer[n] = ch;
    n++;
    ch = fgetc(stdin);
  }

  buffer[n] = '\0';
  return buffer;
}


char *concat(char *str1, char *str2)
{
  const size_t len1 = strlen(str1);
  const size_t len2 = strlen(str2);

  char *str = malloc(len1 + len2 +1);
  if(str == NULL)
  {
    fprintf(stderr, "Cant allocate memory for Identifier string\n");
    return NULL;
  }

  memcpy(str, str1, len1);
  memcpy(str + len1, str2, len2 + 1);

  return str;
}

//convert a poetic literal to a double
double numberPoetic(char *pl)
{
  double number = 0;
  double power = 10;
  int count = 0;
  int i = 0;

  while(pl[i] != '\0')
  {
    count = 0;
    while(pl[i] != ' ' && pl[i] != '.' && pl[i] != ',' && pl[i] != '\0')
    {
      i++;
      count++;
    }
    number = number * power + count ;
    if(pl[i] == '.')
    {
      i++;
      break;
    }
    i++;
  }

  power = 1;
  while(pl[i] != '\0')
  {
    count = 0;
    while(pl[i] != ' ' && pl[i] != ',' && pl[i] != '\0')
    {
      i++;
      count++;
    }
    number = number + count * power;
    power = power / 10;
    i++;
  }

  return number;
}
