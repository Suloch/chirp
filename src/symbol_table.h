
#define ADDED 1
#define NOT_ADDED 0
#define LITERAL_HEADER "__var__"
#define LENGTH 100

#define NULL_TYPE 0
#define NUMBER_TYPE 1
#define STRING_TYPE 2
#define BOOLEAN_TYPE 3
#define OBJECT_TYPE 4
#define MYSTERIOUS_TYPE 5
#define LIST_TYPE 6

typedef struct symbol
{
  char *varName;
  int varType;
  int size;
  struct symbol *next;

  union
  {
    double num;
    char *string;
    void *ptr;
    unsigned int boolean;
  }value;

}symbol;


extern char *lastSymbol;

void initializeTable(void);
symbol *addSymbol(char *, int, void *);
symbol *findSymbol(char *);
symbol *updateSymbol(char *, int, void *);
symbol *copySymbol(char *);
int deleteSymbol(symbol *);
void printSymbol(symbol *);
void renameSymbol(symbol *, char *);
symbol **getTable();
