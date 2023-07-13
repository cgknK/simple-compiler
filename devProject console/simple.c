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



void firstPass( int instructionArry[], TableEntry tableArray[], int flagsArray[] )
{
	//1) simple program file read into memory
	
	FILE *simplePtr = NULL;
	char code[ 50 ][ 50 ];
	char fdata;
	//char *code2[ 50 ];//try
	//char **code3 = NULL;//try
	size_t i, j, k, t;
	
	if( ( simplePtr = fopen( "ch_11_17_simple.txt", "r" ) ) == NULL ) {
		puts( "File could not be opened." );
	}
	else{
		i = 0;
		j = 0;
		while( fgets( code[ i++ ], 49, simplePtr ) ) {
			printf( "%s\n", code[ i - 1 ] );
		}
		code[ i ][ 0 ] = '\0';//biri gereksiz
		code[ i + 1 ][ 0 ] = '\0';
		// bu neden çalýþmýyor ve ya bu code[ i ] = NULL;
		//code[ i ][ 0 ] = NULL;
		
		fclose( simplePtr );
	}
	
	//2) line seperated
	
	char *tokenPtr = NULL;
	char *temp[ 20 ];
	
	char type;
	int symbol;
	int searchLocation;
	int instructionCounter = 0;
	int dataCounter = 99;
	
	int resultTemp;
	int index;
	int state;
	
	int instructionRegister;
	int operationCode;
	int operand;
	
	j = 0;
	for( i = 0; code[ i ][ 0 ] != '\0'; i++ ) {// != NULL
		
		t = 0;
		
		//burda bir iç döngü kullanýlacak gibi duruyor
		tokenPtr = strtok( code[ i ], " " );
		temp[ t++ ] = tokenPtr;
		printf( "temp[%d]: %s\n", t, temp[ t - 1] );
		while( tokenPtr != NULL ) {
			tokenPtr = strtok( NULL, " " );
			temp[ t++ ] = tokenPtr;
			printf( "temp[%d]: %s\n", t, temp[ t - 1] );
		}//end while
		temp[ t ] = tokenPtr;//temp[ t ] = NULL;
		
		t = 0;
		state = 0;
		//type = whatType( temp[ t + 1 ] );
		
		printf( "swichUpper %s\n", temp[ t ] );
		printf( "swichUpper %s\n", temp[ t + 1 ] );
		
		printf( "caseNumber(%s) = caseNumber: %d\n\n\n",temp[ t + 1 ], caseNumber( temp[ t + 1 ] ) );
		
		switch( caseNumber( temp[ t + 1 ] ) ) {
			case 0://"rem"
				symbol = atoi( temp[ t ] );
				
				//searchLocation = searchSymbol( symbol, tableArray )
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				break;
			case 1://"input"
				//line'larý kontrol etmek anlamsýz duruyor, programcý yanlýþ yazmadýðý sürece
				symbol = atoi( temp[ t ] );
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				//yine gereksiz zaten char location gibi bir char dizisi deðil, olmamalý
				//symbol = atoi( temp[ t + 2 ] );
				symbol = temp[ t + 2 ][ 0 ];
				
				if( searchSymbolCV( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'V';
					tableArray[ j ].location = dataCounter--;
				}
				
				operand = tableArray[ j ].location;
				operationCode = READ;
				instructionRegister = operationCode * 100 + operand;
				
				instructionArry[ instructionCounter++ ] = instructionRegister;
				//1 instruction was produced
				break;
			case 2://"let"
				
				
				symbol = atoi( temp[ t ] );
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				k = 0;
				while( temp[ t + 2 + k ] != NULL ) {
					printf( "tempt+2+%d %s %c\n", k, temp[ t + 2 + k ], temp[ t + 2 + k ][ 0 ] );
					if( isalnum( temp[ t + 2 + k ][ 0 ] ) ) {
						
						if( searchSymbolCV( temp[ t + 2 + k ][ 0 ], tableArray ) == -1 ) {
							//symbol = atoi( temp[ t + 2 + k ] )//hani avrupa birliði multi digit
							symbol = temp[ t + 2 + k ][ 0 ];
							type = whatType( temp[ t + 2 + k ] );
							puts( "----------------------------------------------------" );
							printf( "symbol: %d_%c	type: %c\n", symbol, symbol, type );
							puts( "----------------------------------------------------" );
							type = whatType( temp[ t + 2 + k ] );
							
							j++;
							tableArray[ j ].symbol = symbol;
							tableArray[ j ].type = type;
							tableArray[ j ].location = dataCounter;
							
							if( tableArray[ j ].type == 'C' ) {
								instructionArry[ dataCounter ] = tableArray[ j ].symbol - 48;
								puts( "atoi-------------------------------------------atoi" );
								printf( "instructionArry[ dataCounter-- ]: %d\n", instructionArry[ dataCounter + 1 ] );
								puts( "----------------------------------------------------" );
							}
							
							dataCounter--;
							
							/*
							operand = tableArray[ j ].location;
							operationCode = 0;
							instructionRegister = operationCode * 100 + operand;
				
							instructionArry[ instructionCounter++ ] = instructionRegister;
							*/
							printf( "/*LETinstructionArry[ %d ]: %d*/\n", instructionCounter - 1, instructionArry[ instructionCounter - 1 ] );
						}//end if
					}//end if
					
					k++;
				}//end while
				
				//order instead of fix key to avoid conflicts
				char inOrder[ 10 ][ 10 ];
				char postOrder[ 50 ];
				int multiDigit[ 50 ] = { 0 };
				
				k = 0;
				while( temp[ t + 4 + k ] != NULL ) {
					//perror( "part of let PASS" );
					
					printf( "strcpy: %s\n", strcpy( inOrder[ k ], temp[ t + 4 + k ] ) );
					
					/*
					if( strcpy( inOrder[ k ], temp[ t + 4 + k ] ) == NULL )
						perror( "strcpy" );
					*/
					//perror( "after-_-strcpy" );
					k++;
				}
				inOrder[ k ][ 0 ] = '\0';
				
				convertToPostfix( inOrder, postOrder, multiDigit );
				
				resultTemp = evaluatePostfixExpression( postOrder, multiDigit, tableArray,
								&dataCounter, instructionArry, &instructionCounter );
				
				index = searchSymbolCV( temp[ t + 2 ][ 0 ], tableArray );
				printf( "index %d\n", index );
				printf( "tableArray[ %d ] %d\n", index, tableArray[ index ].location );
				printf( "%c_%d\n", tableArray[ index ].symbol, tableArray[ index ].symbol );
				printf( "%c_%d\n", tableArray[ index ].type, tableArray[ index ].type );
				
				//store left operand as a assignment ( to temp )
				operand = tableArray[ index ].location;
				operationCode = 21;
				instructionRegister = operationCode * 100 + operand;
				
				instructionArry[ instructionCounter++ ] = instructionRegister;
				
				perror( "part of let after evaluatePostfixExpression success -only fenotip-" );
				
				//bunlar kaldý heralde
				//left operand-assignment
				//( temp[ t + 5 ] )
				//convert2postfix: atamanýn sað tarafýný
				
				printf( "%s", "let success -only fenotip-\n" );
				
				break;
			case 3://"print"
				symbol = atoi( temp[ t ] );
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				symbol = temp[ t + 2 ][ 0 ];
				
				if( searchSymbolCV( symbol, tableArray ) == -1 ) {
					puts( "COMPILER ERROR" );
					printf( "%c is not defination\n", temp[ t + 2 ][ 0 ] );
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'V';
					tableArray[ j ].location = dataCounter--;
				}
				
				operand = tableArray[ searchSymbolCV( symbol, tableArray ) ].location;
				operationCode = 11;
				instructionRegister = operationCode * 100 + operand;
				
				instructionArry[ instructionCounter++ ] = instructionRegister;
				//1 instruction was produced
				break;
			case 4://"goto"
				symbol = atoi( temp[ t ] );
				
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				symbol = atoi( temp[ t + 2 ] );
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}//if tamamlanmadý
				else {
					operand = tableArray[ searchSymbolL( symbol, tableArray ) ].location;
					operationCode = 40;
					instructionRegister = operationCode * 100 + operand;
				
					instructionArry[ instructionCounter++ ] = instructionRegister;
				}
				
				
				break;
			case 5://"if"
				symbol = atoi( temp[ t ] );
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				//atoi
				symbol = temp[ t + 2 ][ 0 ];
				
				type = whatType( temp[ t + 2 ] );
				if( searchSymbolCV( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = type;
					tableArray[ j ].location = dataCounter--;
					
					operand = tableArray[ j ].location;
					operationCode = 20;
					instructionRegister = operationCode * 100 + operand;
				
					instructionArry[ instructionCounter++ ] = instructionRegister;
					
					//gereksiz
					state = 1;
				}
				
				//symbol = atoi( temp[ t + 4 ] );
				symbol = temp[ t + 4 ][ 0 ];
				
				type = whatType( temp[ t + 4 ] );
				
				if( searchSymbolCV( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = type;
					tableArray[ j ].location = dataCounter--;
					
					operand = tableArray[ j ].location;
					operationCode = 0;
					instructionRegister = operationCode * 100 + operand;
				
					instructionArry[ instructionCounter++ ] = instructionRegister;
					
					//gereksiz
					if( state == 0 )
						state = 2;
					else if( state == 1)
						state = 3;
				}
				
				type = whichIf( temp[ t + 3 ] );
				
				if( type == 41 ) {
					
				}
				// if _ == _ goto __
				else if( type == 42 ) {
					/*
					k = searchSymbolCV( temp[ t + 2 ][ 0 ], tableArray );
					operationCode = 31;//or SUB
					operand = tableArray[ k ].location;
					instructionRegister = operationCode * 100 + operand;
					
					instructionArry[ instructionCounter++ ] = instructionRegister;
					*/
					k = searchSymbolCV( temp[ t + 4 ][ 0 ], tableArray );
					operationCode = 31;
					operand = tableArray[ k ].location;
					instructionRegister = operationCode * 100 + operand;
					
					instructionArry[ instructionCounter++ ] = instructionRegister;
					
					//goto __
					//atoi
					symbol = atoi( temp[ t + 6 ] );
					
					if( searchSymbolL( symbol, tableArray ) == -1 ) {
						flagsArray[ instructionCounter ] = symbol;
						
						operationCode = 42;
						operand = 0;
						instructionRegister = operationCode * 100 + operand;
						
						instructionArry[ instructionCounter++ ] = instructionRegister;
					}
					else {
						puts( "else flags" );
					}
					
				}
				else {
					puts( "ifIFif" );
				}
				
				
				break;
			case 6://"end"
				symbol = atoi( temp[ t ] );
				puts( "endendendendendendendendendendendendendendendend" );
				printf( "%d	%c\n", symbol, symbol );
				symbol = atoi( temp[ t ] );
				
				puts( "end" );
				printf( "%s", "\nend-----------------------------------------\n" );
				printf( "%d	%c", symbol, symbol );
				printf( "%s", "\n-----------------------------------------\n" );
				
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				//searchLocation = searchSymbol( symbol, tableArray )
				if( searchSymbolL( symbol, tableArray ) == -1 ) {
					j++;
					tableArray[ j ].symbol = symbol;
					tableArray[ j ].type = 'L';
					tableArray[ j ].location = instructionCounter;
				}
				
				operationCode = 43;
				operand = 0;
				instructionRegister = operationCode * 100 + operand;
						
				instructionArry[ instructionCounter++ ] = instructionRegister;
				
				state = 1;
				break;
			default:
				printf( "i %d , t %d ", i, t );
				puts( "switch( caseNumber() ) error: default" );
				break;
		}//end switch
		
		j++;
		
		if( outOfMemory( instructionCounter, dataCounter ) )
			return;
		
		if( /*state == 1*/0 )
			break;
		
		printf( "instructionArry[ instructionCounter ]: %d\n", instructionArry[ instructionCounter - 2 ] );
		printf( "instructionArry[ instructionCounter ]: %d\n", instructionArry[ instructionCounter - 1 ] );
	}//end for
	
	
	
	
	
}//end firstPass


/*
We must keep track of the next instruction location in the SML array because
there is not a one-to-one correspondence between Simple statements and SML
instructions. For example, the if…goto statement of line 20 compiles into three
SML instructions. Each time an instruction is produced, we must increment the
instruction counter to the next SML array location. The Simpletron’s limited memory size could present a problem for Simple programs with many statements, variables
and constants. It’s conceivable that the compiler could run out of Simpletron memory. To test for this case, your program should contain a data counter to keep track of
the location at which the next variable or constant will be stored in the SML array. If
the value of the instruction counter is larger than the data counter’s value, the SML
array is full. In this case, the compilation process should terminate, and the compiler
should display an “out-of-memory” error message. 
*/
int outOfMemory( int instructionCounter, int dataCounter )
{
	dataCounter = ( dataCounter - 99 ) * -1;
	
	if( instructionCounter + dataCounter > 99 ) {
		puts( "Error: out-of-memory, instructionCounter + dataCounter > 99." );
		return 1;
	}
	
	return 0;
}

int searchSymbolL( int symbol, TableEntry arr[ 99 ] )//1 it was here, 0 it is here now-insert-, yada konumunu return //symbol is not found, it’s insert
{
	size_t i;
	
	//search
	for( i = 0; i < 99; i++ ) {
		if( arr[ i ].symbol == symbol && arr[ i ].type == 'L' ) {
			return i;
		}
	}
	
	return -1;
}

int searchSymbolCV( int symbol, TableEntry arr[ 99 ] )//1 it was here, 0 it is here now-insert-, yada konumunu return //symbol is not found, it’s insert
{
	size_t i;
	
	//search
	for( i = 0; i < 99; i++ ) {
		if( arr[ i ].symbol == symbol && arr[ i ].type != 'L' ) {
			return i;
		}
	}
	
	return -1;
}

void helper( void )
{
	
}

int insertTablo( void )
{
	//eklenmeli
}

//idareten
int whichIf( char *str )
{
	if( strstr( str, "==" ) )
		return 42;//branchZero
	if( strstr( str, "<" ) )
		return 41;//branchNeg
	return -1;
}

char whatType( char *str )
{	
	if( str != NULL ) {
		
		//need to multidigits update
		if( isdigit( str[ 0 ] ) ) {
			return 'C';
		}
		else if( isalpha( str[ 0 ] ) /* str[ 1 ] == ' '*/ ) {
			return 'V';
		}
		else {
			printf( "whatType Func prblm inner: %s\n", str );
			return NULL;
			//return '\0';
		}
		
	}
	else {
		printf( "whatType Func prblm outer: %s\n", str );
		return NULL;
	}
		
}

void secondPass( int instructionArry[], TableEntry tableArray[], int flagsArray[] )
{
	//resolve any unresolved reference -forward reference-
	size_t i;
	int hold;//temp
	
	for( i = 0; i < 99; i++ ) {
		if( flagsArray[ i ] != -1 ) {
			hold = searchSymbolL( flagsArray[ i ], tableArray );
			
			if( instructionArry[ i ] % 100 == 0 ) {
				if( tableArray[ hold ].location >= 0 && tableArray[ hold ].location <= 99 ) {
					instructionArry[ i ] += tableArray[ hold ].location;
				}
				else {
					puts( "secondPass" );
				}
			}
			else {
				puts( "secondPass" );
			}
			
		}//end if
	}//end for
	
	//SML code to file
	FILE *secondPassPtr;
	
	if( ( secondPassPtr = fopen( "ch11_17_SML.txt", "w" ) ) == NULL ) {
		puts( "SML save error: File could not opened" );
	}
	else {
		//gereksiz yere tüm belleði geçirmek yerine dataCounter ve instructer counter kullan
		for( i = 0; i < 99; i++ ) {
			//þimdilik kalsýn
			fprintf( secondPassPtr, "%5d\n", instructionArry[ i ]  );
		}
		//en son dosyaya -99999 yazdýr bu kaldý ve neden ex7.27'de -99999 yazdýrmýþým?
		
		fclose( secondPassPtr );
	}
	
	
	
}
/*
TableEntry symbolTable[ SIZE ] = { 0 };//You can increase or decrease its size once the program is working.
	size_t sT_beg = 0;
	size_t sT_end = SIZE - 1;
	
	int flags[ SIZE ] = { 0 };
	size_t f_i = 0;
	for( i = 0; i < SIZE; i++ ) {
		flags[ i ] = -1;
	}
	f_i = 0;
*/

//use to preprocessor directives
int caseNumber( char *str )
{
	if( strstr( str, "rem" ) != NULL )
		return 0;
	if( strstr( str, "input" ) != NULL )
		return 1;
	if( strstr( str, "let" ) )
		return 2;
	if( strstr( str, "print" ) )
		return 3;
	if( strstr( str, "goto" ) )
		return 4;
	if( strstr( str, "if" ) )
		return 5;
	if( strstr( str, "end" ) )
		return 6;
	puts( "case number problem" );
	return -1;
}
