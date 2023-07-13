#ifndef sml
#define sml

//Operation Codes
//input/output operations
#define READ 10
#define WRITE 11
#define NEWLINE 12
//load/store operations
#define LOAD 20
#define STORE 21
//arithmetic operations
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define REMAINDER 34
#define EXPONENTIATION 35 //only pozitif exp
//transfer-of-control operations
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

void simpletron( int *const memory, int *const accumulator,
	int *const instructionCounter, int *const instructionRegister,
	int *const operationCode, int *const operand );

#endif
