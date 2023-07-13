#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h> //rand ve srand için buna halen gerek var mý?
#include <stdbool.h>
#include <time.h> // contains prototype for function time
#include <ctype.h>
#include <string.h>

#include "simple.h"
#include "sml.h"
#include "unnecessary.h"
#include "postfix_.h"

void dump( int *const memory, int *const accumulator,
	int *const instructionCounter, int *const instructionRegister,
	int *const operationCode, int *const operand )
{
	puts( "" );
	puts( "REGISTERS:" );
	printf( "accumulator	%0-5d\n", *accumulator );
	printf( "instructionCounter	%0-5d\n", *instructionCounter );
	printf( "instructionRegister	%0-5d\n", *instructionRegister );
	printf( "operationCode	%0-5d\n", *operationCode );
	printf( "operand	%0-5d\n", *operand );
	puts( "MEMORY:" );puts( "" );
	
	size_t i,j;
	
	printf( "\t%5d	%5d\t%5d	%5d\t%5d	%5d\t%5d	%5d\t%5d	%5d\n", 
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
	for( i = 0; i < 100; i++ ) {
		if( i % 10 == 0 ) {
			puts( "" );
			printf( "%-2d	", i );
		}
		printf( "%+05d	", memory[ i ] );
	}
	
	puts( "Starting to save dump" );
	
	FILE *dumpPtr;
	
	if( ( dumpPtr = fopen( "ch11_17_dump.txt", "w" ) ) == NULL ) {
		puts( "dump save error: File could not opened" );
	}
	else {
		fprintf( dumpPtr, "REGISTERS:\n" );
		fprintf( dumpPtr, "accumulator	%0-5d\n", *accumulator );
		fprintf( dumpPtr, "instructionCounter	%0-5d\n", *instructionCounter );
		fprintf( dumpPtr, "instructionRegister	%0-5d\n", *instructionRegister );
		fprintf( dumpPtr, "operationCode	%0-5d\n", *operationCode );
		fprintf( dumpPtr, "operand	%0-5d\n", *operand );
		fprintf( dumpPtr, "MEMORY:\n" );
		fprintf( dumpPtr, "\t%5d	%5d\t%5d	%5d\t%5d	%5d\t%5d	%5d\t%5d	%5d\n", 
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9 );
		for( i = 0; i < 100; i++ ) {
			if( i % 10 == 0 ) {
				fprintf( dumpPtr, "\n" );
				fprintf( dumpPtr, "%-2d	", i );
			}
			fprintf( dumpPtr, "%+05d	", memory[ i ] );
		}
		
		fclose( dumpPtr );
	}
	
	puts( "" );
	processGui();
	
}

void execute( int *const memory, int *const accumulator,
	int *const instructionCounter, int *const instructionRegister,
	int *const operationCode, int *const operand )
{
	puts( "*** Program execution begins ***" );
	
	while( 1 ) {
		*instructionRegister = memory[ *instructionCounter ];
		*operationCode = *instructionRegister / 100;
		*operand = *instructionRegister % 100;
		
		int i;
		int tmp;
		
		switch( *operationCode ) {
		case READ:
			printf( "input mem[%d]:	", *operand );
			scanf( "%d", &memory[ *operand ] );
			( *instructionCounter )++;
			break;
		case WRITE:
			printf( "WRITE: %d -> mem:%02d	\n", memory[ *operand ], *operand );
			( *instructionCounter )++;
			break;
		case NEWLINE:
			puts( "" );
			break;
		case LOAD:
			*accumulator = memory[ *operand ];
			( *instructionCounter )++;
			break;
		case STORE:
			memory[ *operand ] = *accumulator;
			( *instructionCounter )++;
			break;
		case ADD:
			if( ( memory[ *operand ] > 0 && ( *accumulator > ( 9999 - memory[ *operand ] ) ) )
				||
				( memory[ *operand ] < 0 && ( *accumulator < ( -9999 - memory[ *operand ] ) ) ) 
				) {
					puts( "The addition operation cannot overflow" );
			}
			else {
				*accumulator += memory[ *operand ];
			}
			( *instructionCounter )++;
			break;
		case SUBTRACT:
			if( ( memory[ *operand ] > 0 && ( *accumulator < ( -9999 + memory[ *operand ] ) ) )
				||
				( memory[ *operand ] < 0 && ( *accumulator > ( 9999 + memory[ *operand ] ) ) ) 
				) {
				puts( "The subtraction operation cannot overflow" );
			}
			else {
				*accumulator -= memory[ *operand ];
			}
			( *instructionCounter )++;
			break;
		case DIVIDE:
			if( ( 0 == memory[ *operand ] )
				||
				( *accumulator == -9999 && memory[ *operand ] == -1 ) 
				) {
				puts( "The divison operation cannot overflow" );
			}
			else {
				*accumulator /= memory[ *operand ];
			}
			( *instructionCounter )++;
			break;
		case MULTIPLY:
			if( *accumulator * memory[ *operand ] > 9999 
				||
				*accumulator * memory[ *operand ] < -9999 ) {
				puts( "sacmalik-yani daha mathsel bir yolu olmali-" );
				puts( "geç ayýktým ^_- halen daha mantikli bir yolu olmalý" );
			}
			else {
				*accumulator *= memory[ *operand ];
			}
			( *instructionCounter )++;
			break;
		case REMAINDER:
			if( ( 0 == memory[ *operand ] )
				||
				( *accumulator == -9999 && memory[ *operand ] == -1 ) ) {
				puts( "The remainder uyumaz" );
				puts( "Burda neden taþma oluyor kalan operatörü bölmeden farklý gibi geliyor?" );
			}
			else {
				*accumulator %= memory[ *operand ];
			}
			( *instructionCounter )++;
			break;
		case EXPONENTIATION:
			i = 1;
			tmp = 1;
			if( memory[ *operand ] > 0 ) {//Mantýklý bir taþma kontrolü ekle
				for( ; i <= memory[ *operand ]; i++ ) {
					tmp *= *accumulator;
				}
			}
			else if( memory[ *operand ] == 0 ) {
				tmp = 0;
			}
			else {
				puts( "only + int" );
			}
			if( tmp > 9999  ) {
				puts( "There are not information about exp in INT32-C" );
			}
			else {
				*accumulator = tmp;
			}
			( *instructionCounter )++;
			break;
		case BRANCH:
			*instructionCounter = *operand;
			break;
		case BRANCHNEG:
			if( *accumulator < 0 ) {
				*instructionCounter = *operand;
			}
			else {
				( *instructionCounter )++;
			}
			break;
		case BRANCHZERO:
			if( *accumulator == 0 ) {
				*instructionCounter = *operand;
			}
			else {
				( *instructionCounter )++;
			}
			break;
		case HALT:
			puts( "*** Simpletron execution terminated ***" );
			( *instructionCounter )++;
			return;
			break;
		case 0:
			puts( "mallýk" );//0 larý memory'e yüklemenin bedeli
		default:
			printf( "countOp: %d swtchCase default\n", instructionCounter );
			break;
		}//end switch
	}//end while
}//end execute()

void load( int *const mmry )
{
	int var;
	size_t i = 0, j;
	
	/*Actually need the special registers are initialized 0
	int accumulator = 0;
	int instructionCounter = 0;
	int instructionRegister = 0;
	int operationCode = 0;
	int operand = 0;
	int nextProgram = 0;
	*/
	
	FILE *smlPtr;
	
	if( ( smlPtr = fopen( "ch11_17_SML.txt", "r" ) ) == NULL ) {
		puts( "File could not be opened." );
	}
	else{
		fscanf_s( smlPtr, "%6d", &var );
		while( !feof( smlPtr ) ) {
			mmry[ i++ ] = var;
			fscanf_s( smlPtr, "%6d", &var );
		}
		
		fclose( smlPtr );
	}
	
	for( j = 0; j <= i; j++ ) {
		printf( "%02d ? %+05d\n", j, mmry[ j ] );
	}
	
	puts( "*** Program loading completed ***" );
}

void simpletron( int *const memory, int *const accumulator,
	int *const instructionCounter, int *const instructionRegister,
	int *const operationCode, int *const operand )
{
	void load( int *const mmry );
	void execute( int *const memory, int *const accumulator,
	int *const instructionCounter, int *const instructionRegister,
	int *const operationCode, int *const operand );
	void dump( int *const memory, int *const accumulator,
	int *const instructionCounter, int *const instructionRegister,
	int *const operationCode, int *const operand );
	
	puts( "*** Welcome to Simpletron! ***" );
	puts( "*** Please enter your program one instruction ***" );
	puts( "*** (or data word) at a time. I will type the ***" );
	puts( "*** location number and a question mark (?).  ***" );
	puts( "*** You then type the word for that location. ***" );
	puts( "*** Type the sentinel -99999 to stop entering ***" );
	puts( "*** your program. ***" );
	
	load( memory );
	
	execute( memory, accumulator, instructionCounter, instructionRegister,
		operationCode, operand );
	
	dump( memory, accumulator, instructionCounter, instructionRegister,
		operationCode, operand );
}


