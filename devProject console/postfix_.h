#ifndef postfix_
#define postfix_

struct stackNode{
	char data;
	struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

//stack funcs
void printStack( StackNodePtr topPtr );
int isEmpty( StackNodePtr topPtr );
char stackTop( StackNodePtr topPtr );
char pop( StackNodePtr *topPtr );
void push( StackNodePtr *topPtr, char value );

//Infix-to-Postfix Converter funcs
StackNodePtr convertToPostfix( char infix[][10], char postfix[], int *multiDigits );
int isOperator( char c );
int precedence( char operator1, char operator2 );
int isSingleLetter( char c );

//Postfix Evaluator implement "HOOK" funcs
int evaluatePostfixExpression( char *expr, const int *multiDigits, TableEntry *tablePtr,
	int *tempLocationCounter, int instructionArry[], int *instructionCounter );
int calculate( int op1, int op2, char operator, int *tempLocationCounter,
	int instructionArry[], int *instructionCounter );

int returnLocationCV( char c, TableEntry *arr );

//start func ?

#endif
