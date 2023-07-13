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

void displayBits( unsigned int value )
{
	unsigned int displayMask = 1 << CHAR_BIT * sizeof( unsigned int ) - 1;
	unsigned int i;
	
	printf( "%10u = ", value );
	
	for( i = 1; i <= CHAR_BIT * sizeof( unsigned int ); i++ ) {
		putchar( value & displayMask ? '1' : '0' );
		value <<= 1;
		
		if( i % 8 == 0 ) {
			putchar( ' ' );
		}
	}
	putchar( '\n' );
	
}

void getline( char *str, size_t size )
{
	size_t i;
	int c;
	
	i = 0;
	printf_s( "%s%d:", "Enter a line of text ", i + 1 );
	while( i < size - 1 && ( c = getchar() ) != '\n' ) {
		str[ i++ ] = c;
	}
	str[ i ] = '\0';
	
}

void processGui( void )
{
	int pauseCounter;
	int pauseC;
	printf( "%s", "Save dump process in progress: " );
	for( pauseC = 0; pauseC < 3; pauseC++ ){
		printf( "%s", "-" );
		
		pauseCounter = 0;
		while( pauseCounter < 150000000 ) {
			pauseCounter++;
		}
		printf( "%s", "\b\\" );
		
		pauseCounter = 0;
		while( pauseCounter < 150000000 ) {
			pauseCounter++;
		}
		printf( "%s", "\b|" );
		
		pauseCounter = 0;
		while( pauseCounter < 150000000 ) {
			pauseCounter++;
		}
		printf( "%s", "\b/" );
		pauseCounter = 0;
		while( pauseCounter < 150000000 ) {
			pauseCounter++;
		}
		printf( "%s", "\b" );
	}
	printf( "%s", "Done\n" );
}

