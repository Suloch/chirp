
typedef enum nodeType
{
  blockType,
  identifierType,
  scanType,
  printType,
  assignmentType,
  poeticAssignmentType,
  expressionType,
  numLiteralType,
  booleanLiteralType,
  stringLiteralType,
  nullLiteralType,
  ifType,
  ifElseType,
  whileType,
  incrementType,
  decrementType,
  functionDefinitionType,
  functionCallType,
  breakType,
  continueType
}nodeType;

typedef struct node
{
  nodeType type;

  union
  {
    double num;
    unsigned int boolean;
    char op;
    char *s;
    struct node *e;
  }value;
  struct node *left, *right;

}node;

//functions to generate the tree
node *makeBlock(node *, node*);
node *makeScan(node *);
node *makePrint(node *);
node *makeAssignment(node *, node *);
node *makeAssignmentPoetic(node *, double);
node *makeIdentifier(char *);
node *makeNumLiteral(double num);
node *makeStringLiteral(char *);
node *makeLogicalLiteral(unsigned int);
node *makeExpression(node *, char, node *);
node *makeIfStatement(node *, node *);
node *makeNullLiteral(void);
node *makeIfElseStatement(node *, node *, node *);
node *makeWhileStatement(node *, node *);
node *makeIncrement(node *);
node *makeDecrement(node *);
node *makeAddItemToList(node *, node *);
node *makeAddItemToCallList(node *, node *);
node *makeFunctionDefinition(node *, node *, node *, node*);
node *makeFunctionCall(node *, node *);
node *makeContinue();
node *makeBreak();


//functions to traverse the tree
int executeStatement(node *);

//functions to delete the tree
void deleteStatement(node *);
void deleteFunctionDefinition(node *);
