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

//atoi kullanmayý unuttum çalýþmayabilir

int evaluatePostfixExpression( char *expr, const int *multiDigits, TableEntry *tablePtr,
	int *tempLocationCounter, int instructionArry[], int *instructionCounter )
{	
	/*
	char postfixModifyEval[ 50 ];
	c = 0;
	tokenPtr = strtok( postfixEval, " " );
	while( tokenPtr != NULL  ) {
		postfixModifyEval[ c ] = tokenPtr[ 0 ];
		tokenPtr = strtok( NULL, " " );
		c++;
	}
	postfixModifyEval[ c ] = NULL;
	*/
	
	perror( "START evaluatePostfixExpression" );
	printf( "%s\n", expr );
	
	StackNodePtr topPtr = NULL;
	int x, y, result;
	int temp;
	size_t i;
	int symbolsLocation;
	
	for( i = 0; i < 50 && expr[ i ] != NULL; i++ ) {
		//düzenleme gerekli
		if( expr[ i ] == ' ' ) {
			;
		}
		else if( isdigit( expr[ i ] ) || multiDigits[ i ] == 1 || isalpha( expr[ i ] ) ) {
			
			if( multiDigits[ i ] == 1 ) {
				symbolsLocation = returnLocationCV( expr[ i ] , tablePtr );
				printf( "expr[ %d ]: %c\n", i, expr[ i ] );
				printf( "symbolsLocation: %d %c\n", symbolsLocation, symbolsLocation );
				push( &topPtr, symbolsLocation );
			}	
			else if( isSingleLetter( expr[ i ] ) ) {
				symbolsLocation = returnLocationCV( expr[ i ] , tablePtr );
				printf( "expr[ %d ]: %c\n", i, expr[ i ] );
				printf( "symbolsLocation: %d %c\n", symbolsLocation, symbolsLocation );
				push( &topPtr, symbolsLocation );
			}
			else {
				symbolsLocation = returnLocationCV( expr[ i ] , tablePtr );
				printf( "expr[ %d ]: %c\n", i, expr[ i ] );
				printf( "symbolsLocation: %d %c\n", symbolsLocation, symbolsLocation );
				push( &topPtr, symbolsLocation );
			}
			printStack( topPtr );
			
		}
		else if( isOperator( expr[ i ] ) ) {
			puts( "isOperator" );
			printStack( topPtr );
			x = pop( &topPtr );
			printStack( topPtr );
			y = pop( &topPtr );
			printStack( topPtr );
			
			printf( "CALCULATE_CALCULATE_CALCULATE_CALCULATE\n" );
			printf( "y: %d %c\n", y, y );
			printf( "x: %d %c\n", x, x );
			printf( "expr[ i ]: %d %c\n", expr[ i ], expr[ i ] );
			printf( "tempLocationCounter: %d %c\n", *tempLocationCounter, *tempLocationCounter );
			printf( "instructionArry: %d %d\n", instructionArry[ *instructionCounter ], instructionArry[ *instructionCounter - 1 ] );
			printf( "instructionCounter: %d %c\n", *instructionCounter, *instructionCounter );
			
			temp = calculate( y, x, expr[ i ], tempLocationCounter, instructionArry,
								instructionCounter );
			printf( "temp=calculate: %d %c\n", temp, temp );
			
			printf( "tempLoacationCounter %d\n^^^^^^^^^^^^^^^^^^^^^\n", *tempLocationCounter );
								
			push( &topPtr, temp );
			printStack( topPtr );
		}
		else{
			puts( "MARK" );
			printf( "_ %c_\n", expr[ i ] );
			puts( "MARK" );
		}
	}
	
	result = pop( &topPtr );
	printStack( topPtr );
	return result;
	
}

int returnLocationCV( char c, TableEntry *arr )
{
	size_t i;
	
	for( i = 0; i < 99; i++ ) {
		if( arr[ i ].symbol == c && arr[ i ].type != 'L' )
			return arr[ i ].location;
	}
	return -1;
}

int calculate( int op1, int op2, char operator, int *tempLocationCounter,
	int instructionArry[], int *instructionCounter )
{
	int instructionRegister;
	int operationCode;
	int operand;
	
    switch( operator ) {
        case '+':
        	puts( "case '+' " );
        	
        	//load op1
        	operand = op1;
        	operationCode = 20;
        	instructionRegister = operationCode * 100 + operand;
        	instructionArry[ ( *instructionCounter )++ ] = instructionRegister;
        	
        	printf( "opcod20: instruc: %d\n", instructionArry[ *instructionCounter - 1 ] );
        	
        	//add op2
        	operand = op2;
        	operationCode = 30;
        	instructionRegister = operationCode * 100 + operand;
        	instructionArry[ ( *instructionCounter )++ ] = instructionRegister;
        	
        	printf( "opcod30: instruc: %d\n", instructionArry[ *instructionCounter - 1 ] );
        	
        	//stored in a temporary
        	operand = *tempLocationCounter;
        	operationCode = 21;
        	instructionRegister = operationCode * 100 + operand;
        	instructionArry[ ( *instructionCounter )++ ] = instructionRegister;
        	
        	printf( "opcod21: instruc: %d\n", instructionArry[ *instructionCounter - 1 ] );
        	
        	//load from temporary
        	operand = ( *tempLocationCounter )--;//--
        	operationCode = 20;
        	instructionRegister = operationCode * 100 + operand;
        	instructionArry[ ( *instructionCounter )++ ] = instructionRegister;
        	printf( "opcod20: instruc: %d\n", instructionArry[ *instructionCounter - 1 ] );
        	
        	//store left operand as a assignment
        		//in simple.c
        	
            break;
        case '-':
            instructionRegister = op1 - op2;
            break;
        case '*':
            instructionRegister = op1 * op2;
            break;
        case '/':
            instructionRegister = op1 / op2;
            break;
        case '^':
        	puts( "^ operator fail: set to l0 l1 l2 l3 string." );
            instructionRegister = pow( op1, op2 );
            break;
        case '%':
            instructionRegister = op1 % op2;
            break;
        default:
        	puts( "calculate error: default case." );
            break;
    }
    
    return *tempLocationCounter--;
}//end calculate

StackNodePtr convertToPostfix( char infix[][10], char postfix[], int *multiDigits ) 
{
	/*
	char *infixModify[ 50 ];
	char *tokenPtr = NULL;
	size_t c = 0;
	tokenPtr = strtok( infix, " " );
	while( tokenPtr != NULL  ) {
		infixModify[ c ] = tokenPtr;
		tokenPtr = strtok( NULL, " " );
		c++;
	}
	*/
	if( infix[ 3 ][ 0 ] == '\0' )
		printf( "infix: %d\n", 666 );
	if( infix[ 3 ][ 0 ] == NULL )
		printf( "infix: %d\n", 555 );
	if( infix[ 3 ] == NULL )
		printf( "infix: %d\n", 444 );
	
	StackNodePtr topPtr = NULL; //fonksiyondan tamamen pop lamadan çýkýlýrsa bellek?
	size_t i, j, currentIndex;
	
	//1
	push( &topPtr, '(' );
	
	//2
	j = 0;
	while( infix[ j ][ 0 ] != NULL ) {
		printf( "infix: %s\n", infix[ j ] );
		j++;
	}
	
	currentIndex = j;
	//printf( "%d", strlen( infix ) );
	infix[ currentIndex ][0] = ')';
	//infix[ currentIndex + 1 ][ 0 ] = NULL;
	infix[ currentIndex + 1 ][ 0 ] = '\0';
	
	//3
	j = 0;
	for( i = 0; i < currentIndex + 1 && infix[ i ][ 0 ] != '\0' && !isEmpty( topPtr ); i++ ) {
		if( isdigit( infix[ i ][ 0 ] ) ) {
			if( isdigit( infix[ i ][ 1 ] ) ) {
				char *remainderPtr = NULL;
				postfix[ j /*i + 1*/ ] = strtol( infix[ i ], &remainderPtr, 0 );
				multiDigits[ j++ ] = 1;
				postfix[ j++ ] = ' ';
			}
			else {
				postfix[ j /*i + 1*/ ] = infix[ i ][ 0 ];
				multiDigits[ j++ ] = -1;
				postfix[ j++ ] = ' ';
			}
		}
		/*
		else if( isSingleLetter( infix[ i ][ 0 ] ) ) {
			perror( "3 convertToPostfix" );
			postfix[ j++ /*i + 1*//* ] = infix[ i ][ 0 ];
			postfix[ j++ ] = ' ';
		}
		*/
		else if( isalpha( infix[ i ][ 0 ] ) ) {
			postfix[ j++ /*i + 1*/ ] = infix[ i ][ 0 ];
			postfix[ j++ ] = ' ';
		}
		else if( infix[ i ][ 0 ] == '(' ) {
			
			push( &topPtr, infix[ i ][ 0 ] );
		}
		else if( isOperator( infix[ i ][ 0 ] ) ) {
			
			//printf( "i: %d, j: %d, %d\n", i, j, isOperator( stackTop( topPtr ) ) );
			if( isOperator( stackTop( topPtr ) ) ) {
				if( precedence( stackTop( topPtr ), infix[ i ][ 0 ] ) >= 0 ) {
					postfix[ j++ ] = pop( &topPtr );
					postfix[ j++ ] = ' ';
					printStack( topPtr );
					//printf( "%d:postfix[ %d ] = pop( &topPtr ) //%c;\n", i, j, postfix[ j++ ] );
				}
				push( &topPtr, infix[ i ][ 0 ] );
				printStack( topPtr );
			}
			else{
				push( &topPtr, infix[ i ][ 0 ] );
				printStack( topPtr );
			}
		}
		else if( infix[ i ][ 0 ] == ')' ) {
			
			while( stackTop( topPtr ) != '(' ) {
				postfix[ j++ ] = pop( &topPtr );
				postfix[ j++ ] = ' ';
				printStack( topPtr );
			}
			pop( &topPtr );
			printStack( topPtr );
		}
		else {
			puts( "convertToPostfix error: default case." );
		}
		//printf( "i: %d, j: %d, infix[%d]=%c, postfix[%d]=%c\n",i,j-1,i,infix[i],j-1,postfix[j-1] );
	}
	postfix[ j ] = '\0';
}

int precedence( char operator1, char operator2 )
{
	//char l0 = "()"; char l1 = "^";
	char l1[] = "()^";//3
	char l2[] = "/*%";//2
	char l3[] = "+-";//1
	
	int opValue1 = 0, opValue2 = 0;
	
	if( strchr( l1, operator1 ) || strchr( l2, operator1 ) || strchr( l3, operator1 ) )
	;
	else 
		puts( "debug" );
	
	if( strchr( l1, operator1 ) /*!= NULL*/ )
		opValue1 = 2;
	else if( strchr( l2, operator1 ) )
		opValue1 = 1;
	
	if( strchr( l1, operator2 ) )
		opValue2 = 2;
	else if( strchr( l2, operator2 ) )
		opValue2 = 1;
	
	if( opValue1 == opValue2 ) 
		return 0;
	else if( opValue1 > opValue2 )
		return 1;
	else if( opValue1 < opValue2 )
		return -1;
	puts( "-99" );
	return -99;
	
}

int isOperator( char c )
{
	char operators[] = "+-*/^%";
	size_t i, size;
	
	size = strlen( operators );
	//printf( "%u	", size );//NULL check
	
	for( i = 0; i < size; i++ ) {
		if( c == operators[ i ] )
			return 1;
	}
	
	return 0;
}

int isSingleLetter( char c )
{
	char operators[] = "abcdefghijklmnopqrstuvwxyz";
	size_t i, size;
	
	size = strlen( operators );
	
	for( i = 0; i < size; i++ ) {
		if( c == operators[ i ] )
			return 1;
	}
	
	return 0;
}

char stackTop( StackNodePtr topPtr ){
	if( topPtr != NULL )
		return topPtr->data;
	return '\0';
}

int isEmpty( StackNodePtr topPtr ){
	return topPtr == NULL;
}

char pop( StackNodePtr *topPtr )
{
	StackNodePtr tempPtr;
	
	if( *topPtr != NULL ) {
		int popValue = ( *topPtr )->data;
		tempPtr = *topPtr;
		*topPtr = ( *topPtr )->nextPtr;
		free( tempPtr );
		tempPtr = NULL;//unnecessary
		return popValue;
	}
	else {
		puts( "pop error: list is empty." );
		return '\0';
	}
	
}

void printStack( StackNodePtr topPtr ){
	if( topPtr == NULL )
		puts( "Stack is empty.\n" );
	else {
		while( topPtr != NULL ) {
			printf( "%d --> ", topPtr->data );
			topPtr = topPtr->nextPtr;
		}
		puts( "NULL\n" );
	}
	
}

void push( StackNodePtr *topPtr, char value )
{
	StackNodePtr newPtr = NULL;
	
	newPtr = malloc( sizeof( StackNode ) );
	
	if( newPtr != NULL ){
		newPtr->data = value;
		newPtr->nextPtr = *topPtr;
		*topPtr = newPtr;
	}
	else{
		puts( "Push error: No mem available." );
	}
	
}

