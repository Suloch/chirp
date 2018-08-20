
%{
  void yyerror(char *s);
  int yylex();
  #include<stdio.h>
  #include<stdlib.h>
  #include<string.h>
  #include "symbol_table.h"
  #include "utils.h"
  #include "operations.h"
  #include "AST.h"

  extern FILE *yyin;
  int cmd = 1;
  void success();
  void deleteTable();

%}
%union{double num; char *string; unsigned int boolean; void *ptr;}
%start Program
%token PRINT SCAN QUIT NL COMMENT COMMENT_START COMMENT_END SPACE STRING_END STRING_START ASSIGN PUT INTO BUILD UP KNOCK DOWN TAKING GIVE CONTINUE
%token AND OR PLUS MINUS TIMES OVER EQUALS NOT_EQUALS LESS_THAN LESS_EQUALS MORE_THAN MORE_EQUALS NULL_LITERAL IF ELSE WHILE TAKES COMMA BACK BREAK
%left PLUS MINUS
%left TIMES OVER
%left EQUALS NOT_EQUALS LESS_THAN LESS_EQUALS MORE_THAN MORE_EQUALS
%token <string> COMMON_IDENTIFIER PRONOUN PROPER_IDENTIFIER FIND_COMMON_IDENTIFIER FIND_PROPER_IDENTIFIER STRING_LITERAL POETIC_LITERAL
%token <boolean> LOGICAL_LITERAL
%token <num> NUM_LITERAL
%type <string> ProperIdentifier
%type <ptr> Expression Literal Block Assignment Statement Identifier FunctionDefiniton FunctionCall List CallList ConditionalExpression

%%
Program :                                                                       {}
        | Program COMMENT_START COMMENT COMMENT_END                             {}
        | Program Statement NL                                                  {executeStatement($2);deleteStatement($2);success();}
        | Program error                                                         {yyerror("invalid character");}
        | Program NL                                                            {success();}
        ;

Block :                                                                         {$$ = NULL;}
      | Block Statement NL                                                      {$$ = makeBlock($1, $2);}
      ;

Statement : Assignment                                                          {$$ = $1;}
          | CONTINUE                                                            {$$ = makeContinue();}
          | BREAK                                                               {$$ = makeBreak();}
          | SCAN Identifier                                                     {$$ = makeScan($2);}
          | PRINT Expression                                                    {$$ = makePrint($2);}
          | IF ConditionalExpression NL Block                                   {$$ = makeIfStatement($2, $4);}
          | IF ConditionalExpression NL Block ELSE NL Block                     {$$ = makeIfElseStatement($2, $4, $7);}
          | WHILE ConditionalExpression NL Block                                {$$ = makeWhileStatement($2, $4);}
          | FunctionDefiniton                                                   {$$ = $1;}
          | QUIT                                                                {printf("Mata ne~ 0/\n");exit(EXIT_SUCCESS);}
          ;

FunctionDefiniton : Identifier TAKES List NL Block  GIVE BACK Expression        {$$ = makeFunctionDefinition($1, $3, $5, $8);}
                  ;

List : Identifier AND List                                                      {$$ = makeAddItemToList($3, $1);}
     | Identifier                                                               {$$ = makeAddItemToList(NULL, $1);}
     ;

Assignment : PUT Expression INTO Identifier                                     {$$ = makeAssignment($2, $4);}
           | BUILD Identifier UP                                                {$$ = makeIncrement($2);}
           | KNOCK Identifier DOWN                                              {$$ = makeDecrement($2);}
           | Identifier ASSIGN POETIC_LITERAL                                   {char * s =  concat("", $3); double num = numberPoetic(s); free(s); $$ = makeAssignmentPoetic($1, num);}
           ;

Expression : Expression PLUS Expression                                         {$$ = makeExpression($1, '+', $3);}
           | Expression MINUS Expression                                        {$$ = makeExpression($1, '-', $3);}
           | Expression TIMES Expression                                        {$$ = makeExpression($1, '*', $3);}
           | Expression OVER Expression                                         {$$ = makeExpression($1, '/', $3);}
           | FunctionCall                                                       {$$ = $1;}
           | Identifier                                                         {$$ = $1;}
           | Literal                                                            {$$ = $1;}
           ;

ConditionalExpression :   Expression MORE_THAN Expression                       {$$ = makeExpression($1, '>', $3);}
                        | Expression LESS_THAN Expression                       {$$ = makeExpression($1, '<', $3);}
                        | Expression EQUALS Expression                          {$$ = makeExpression($1, '=', $3);}
                        | Expression MORE_EQUALS Expression                     {$$ = makeExpression($1, 'm', $3);}
                        | Expression LESS_EQUALS Expression                     {$$ = makeExpression($1, 'l', $3);}
                        | Expression NOT_EQUALS Expression                      {$$ = makeExpression($1, 'n', $3);}
                        ;

FunctionCall : Identifier TAKING CallList                                       {$$ = makeFunctionCall($1, $3);}
             ;

CallList : Expression COMMA CallList                                            {$$ = makeAddItemToCallList($3, $1);}
         | Expression                                                           {$$ = makeAddItemToCallList(NULL, $1);}
          ;

Identifier : ProperIdentifier                                                   {$$ = makeIdentifier($1); free($1);}
           | FIND_COMMON_IDENTIFIER COMMON_IDENTIFIER                           {char *varName = concat($1, $2); $$ = makeIdentifier(varName); free(varName);}
           | PRONOUN                                                            {$$ = makeIdentifier("_");}
           ;

ProperIdentifier : ProperIdentifier PROPER_IDENTIFIER                           {$$ = concat($1, $2); free($1);}
                 | PROPER_IDENTIFIER                                            {$$ = concat("", $1);}
                 ;

Literal : NUM_LITERAL                                                           {$$ = makeNumLiteral($1);}
        | STRING_START STRING_LITERAL STRING_END                                {$2[strlen($2) - 1] = '\0'; $$ = makeStringLiteral($2);}
        | LOGICAL_LITERAL                                                       {$$ = makeLogicalLiteral($1);}
        | NULL_LITERAL                                                          {$$ = makeNullLiteral();}
        ;



%%

int main(int argc, char **argv)
{
  if(argc > 1)
  {
    cmd = 0;
  }
  yyin = fopen(argv[1], "r");
  printf("\\m/\n");
  success();
  initializeTable();
  yyparse();
  deleteTable();
  return 0;
}

void yyerror(char *s)
{
  fprintf(stderr, "%s\n", s);
}

void success(void)
{
  if(cmd == 0)
  {
    return;
  }
  printf(ANSI_BLUE "(chirp)>>" ANSI_RESET);
}

void deleteTable()
{
  symbol **t = getTable();
  int i;
  for(i = 0; i < LENGTH; i++)
  {
    symbol *curr = t[i];
    while(curr != NULL)
    {
      symbol *del = curr;
      curr = curr -> next;
      if(deleteSymbol(del) == 1)
      {
        deleteFunctionDefinition(del -> value.ptr);
        free(del -> varName);
        free(del);
      }
    }
  }
}
