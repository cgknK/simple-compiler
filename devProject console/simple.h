#ifndef simple
#define simple

/*
#define REM 0
#define INPUT 1 
#define LET 2
#define PRINT 3 
#define GOTO 4
#define IF_GOTO 5
#define END 6
*/

//may be use enum for member's char type
struct tableEntry {
	int symbol;
	char type; /* 'C', 'L' or 'V' */
	int location; /* 00 to 99 */
};

typedef struct tableEntry TableEntry; 
typedef TableEntry *TableEntryPtr;

void firstPass( int instructionArry[], TableEntry tableArray[], int flagsArray[] );
void secondPass( int instructionArry[], TableEntry tableArray[], int flagsArray[] );

int outOfMemory( int instructionCounter, int dataCounter );
int searchSymbolL( int symbol, TableEntry arr[ 99 ] );
int searchSymbolCV( int symbol, TableEntry arr[ 99 ] );
char whatType( char *str );
int caseNumber( char *str );

#endif
