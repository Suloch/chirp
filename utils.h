
#define NUMBER 0
#define STRING 1
#define ANSI_BLUE "\x001B[34m"
#define ANSI_RESET "\x001B[0m"


char *getInput();
int checkInput(char *);
char *concat(char *, char *);
char *newNumberString(double);
char *newBoolString(unsigned int);
double numberPoetic(char *);
