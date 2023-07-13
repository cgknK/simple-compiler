//CH12: Q27 \
	Building A Compiler; Prerequisite: Complete Exercise 7.27, Exercise 7.28, Exercise 12.12, \
		Exercise 12.13 and Exercise 12.26

//Düzenle eksik senaryolarý tamamla

//Ptr olmayan pointerlarý düzelt, postfix de atoi kullan yada kullanmaya çalýþ

//tüm code düzeltilecek

//tüm include lar düzenlenecek

//Bunlar eklenmedi, 
//d) Modify the simulator to use hexadecimal values rather than integer values to represent Simpletron Machine Language instructions.
//f) Modify the simulator to process floating-point values in addition to integer values.
//g) Modify the simulator to handle string input. 
//h) Modify the simulator to handle output of strings stored in the format of part (g).
// ve eklenenler test edilmedi.

//https://github.com/AndrewLaing/CHowToProgramExercises/blob/master/Chapter7/ex07_29.c \
	En altta silinmesine karþý bir örnek yer alýyor.
	
//fprintf i de mi tek argümanlý kullanmak bir güvenlik açýðý? fprintf leri fprintf_s yap

//Pozitif tamsayýlarý okumak,... için pozitif kontrolü gerekebilir? bilmiyorum

//( *accumulator == -9999 && memory[ *operand ] == -1 ) ) \
		puts( "The remainder uyumaz" ); \
		puts( "Burda neden taþma oluyor kalan operatörü bölmeden farklý gibi geliyor?" );

//EXPONENTIATION:	if( memory[ *operand ] > 0 ) {//taþma kontrolü ekle

/*
d)Modify the simulator to use hexadecimal values rather than integer values to represent
Simpletron Machine Language instructions.
g) Modify the simulator to handle string input. [Hint: Each Simpletron word can be divided into two groups, each holding a two-digit integer. Each two-digit integer represents the ASCII decimal equivalent of a character. Add a machine-language instruction
that will input a string and store it beginning at a specific Simpletron memory location.
The first half of the word at that location will be a count of the number of characters in
the string (i.e., the length of the string). Each succeeding half word contains one ASCII
character expressed as two decimal digits. The machine-language instruction converts
each character into its ASCII equivalent and assigns it to a half word.]
h) Modify the simulator to handle output of strings stored in the format of part (g). [Hint:
Add a machine-language instruction that prints a string beginning at a specified Simpletron memory location. The first half of the word at that location is the length of the
string in characters. Each succeeding half word contains one ASCII character expressed
as two decimal digits. The machine-language instruction checks the length and prints
the string by translating each two-digit number into its equivalent character.]
*/

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

//#define SIZE_MAX 1000
//#define SIZE 100

void setFlags( int flags[] );

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main( void )
{	
	
	
	
	//simple.c
	//first pass
	int instructionArry[ 99 ] = { 0 };
	TableEntry tableArray[ 99 ];//You can increase or decrease its size once the program is working.
	int flagsArray[ 99 ] = { 0 };
	setFlags( flagsArray );
	
	firstPass( instructionArry, tableArray, flagsArray );
	
	perror( "firstPass" );
	
	size_t i; 
	puts( "firstpass" );
	puts( "instructionArry" );
	for( i = 0; i < 99; i++ ) {
		printf( "%d ", instructionArry[ i ] );
	}
	puts( "flagsArray" );
	for( i = 0; i < 99; i++ ) {
		printf( "%d ", flagsArray[ i ] );
	}
	
	
	//second pass
	secondPass( instructionArry, tableArray, flagsArray );
	
	puts( "secondpass" );
	puts( "instructionArry" );
	for( i = 0; i < 99; i++ ) {
		printf( "%d ", instructionArry[ i ] );
	}
	puts( "flagsArray" );
	for( i = 0; i < 99; i++ ) {
		printf( "%d ", flagsArray[ i ] );
	}
	
	//sml.c
	puts( "sml.c" );
	
	
	
	//int memory[ 1000 ] = { 0 };
	int memory[ 100 ] = { 0 };
	int *const memPtr = memory;
	int accumulator = 0;
	int *const accuPtr = &accumulator;
	int instructionCounter = 0;
	int *const icPtr = &instructionCounter;
	int instructionRegister = 0;
	int *const irPtr = &instructionRegister;
	int operationCode = 0;
	int *const ocPtr = &operationCode;
	int operand = 0;
	int *const oPtr = &operand;
	int nextProgram = 0;
	
	puts( "if you wish start simpletron press 1 or press 0 for exit" );
	scanf( "%d", &nextProgram );
	while( nextProgram ) {
		simpletron( memPtr, accuPtr, icPtr, irPtr, ocPtr, oPtr );
		puts( "" );
		puts( "---------------------------------------------------------" );
		puts( "if you wish continue simpletron press 1 or press 0 for exit" );
		scanf( "%d", &nextProgram );
	}
		
	return 0;
} // end main

void setFlags( int flags[] )
{
	size_t i;
	
	for( i = 0; i < 99; i++ ) {
		flags[ i ] = -1;
	}
	
}
