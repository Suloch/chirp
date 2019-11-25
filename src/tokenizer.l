
%{
  #include "y.tab.h"
  void yyerror(char *s);
  int yylex();
  int i = 0;
%}

%s FindCommonIdentifier
%x FindProperIdentifier
%x Comments
%x String
%s Poetic
%s Condition

Digit [0-9]
LowerCase [a-z]
UpperCase [A-Z]
Letter [a-zA-Z]
Print Say|Shout|Whisper|Scream
Scan  "Listen to"|Hear
Quit  sayonara

StartCommonIdentifier a|an|the|my|your
Pronoun it|he|she|him|her|they|them|ze|hir|zie|zir|xe|xem|ve|ver
Add plus|with
Substract minus|without
Multiply times|of
Divide over
While While|Until
True true|right|okay|yes
False false|wrong|no|lies
assign is|were|was|are
null nothing|nobody|nowhere
greater higher|greater|bigger|stronger
lesser lower|lesser|smaller|weaker
greaterEqual high|great|big|strong
lesserEqual low|less|small|weak

%%
"("                                                           {BEGIN(Comments); return COMMENT_START;}
<Comments>[^)]*                                               {return COMMENT;}
<Comments>")"                                                 {BEGIN(INITIAL); return COMMENT_END;}
\"                                                            {BEGIN(String); return STRING_START;}
<String>[^\"]*                                                {yylval.string = yytext; return STRING_LITERAL;}
<String>\"                                                    {BEGIN(INITIAL); return STRING_END;}
{Digit}+(\.{Digit}+)?                                         {yylval.num = atof(yytext); return NUM_LITERAL;}
<Poetic>({Letter}*[,\.]?[\ ]?)*                               {yylval.string = yytext; BEGIN(INITIAL); return POETIC_LITERAL;}
{True}                                                        {yylval.boolean = 1; return LOGICAL_LITERAL;}
{False}                                                       {yylval.boolean = 0; return LOGICAL_LITERAL;}
{null}                                                        {BEGIN(INITIAL); i = 0; return NULL_LITERAL;}
<Condition>is                                                 {BEGIN(INITIAL); i = 0; return EQUALS;}
<Condition>"is not "                                          {BEGIN(INITIAL); i = 0; return NOT_EQUALS;}
<Condition>"ain't"                                            {BEGIN(INITIAL); i = 0; return NOT_EQUALS;}
<Condition>is\ {greater}\ than                                {BEGIN(INITIAL); i = 0; return MORE_THAN;}
<Condition>is\ {lesser}\ than                                 {BEGIN(INITIAL); i = 0; return LESS_THAN;}
<Condition>is\ as\ {greaterEqual}\ as                         {BEGIN(INITIAL); i = 0; return MORE_EQUALS;}
<Condition>is\ as\ {lesserEqual}\ as                          {BEGIN(INITIAL); i = 0; return LESS_EQUALS;}
<Condition>"\'s"                                              {unput('s'); unput('i');}
{assign}                                                      {BEGIN(Poetic); return ASSIGN;}
and                                                           {return AND;}
"\'s"                                                         {unput('s'); unput('i');}
"Take it to the top"                                          {return CONTINUE;}
"Break it down"                                               {return BREAK;}
Give                                                          {return GIVE;}
back                                                          {return BACK;}
taking                                                        {return TAKING;}
takes                                                         {return TAKES;}
Put                                                           {return PUT;}
into                                                          {return INTO;}
{Print}                                                       {return PRINT;}
{Scan}                                                        {return SCAN;}
{Quit}                                                        {return QUIT;}
{While}                                                       {BEGIN(Condition); i = 1; return WHILE;}
If                                                            {BEGIN(Condition); i = 1; return IF;}
Else                                                          {return ELSE;}
Build                                                         {return BUILD;}
up                                                            {return UP;}
Knock                                                         {return KNOCK;}
down                                                          {return DOWN;}
{Add}                                                         {return PLUS;}
{Substract}                                                   {return MINUS;}
{Multiply}                                                    {return TIMES;}
{Divide}                                                      {return OVER;}
{Pronoun}[\ \n]                                               {unput(yytext[yyleng-1]); return PRONOUN;}
{StartCommonIdentifier}\                                      {yylval.string = strdup(yytext); BEGIN(FindCommonIdentifier); return FIND_COMMON_IDENTIFIER;}
{UpperCase}{Letter}*                                          {yylval.string = strdup(yytext); return PROPER_IDENTIFIER;}
<FindCommonIdentifier>{LowerCase}+                            {yylval.string = strdup(yytext); if(i == 1){BEGIN(Condition);}else{BEGIN(INITIAL);} return COMMON_IDENTIFIER;}
[\n]                                                          {return NL;}
[,]                                                           {return COMMA;}
.                                                             ;

%%

int yywrap(void)
{
  return 1;
}
