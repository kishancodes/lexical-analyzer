/* front.c - a lexical analyzer system for simple arithmetic expressions */
//Author: Kishan Bhakta
//CMPSCI-4250 Project 1
#include <stdio.h>
#include <ctype.h>
#include <string.h>
/* Global declarations */
/* Variables */
int charClass;
int prevClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
int prevToken = 0;
 FILE *in_fp, *fopen();
char string[100];
/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();
/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEM_COL 27
#define COMM 28
/******************************************************/
/* main driver */
int main() {

 /* Open the input data file and process its contents */
     /*please enter the desired path according to your system.*/
     /* For Example: if ((in_fp = fopen("C:\\temp\\desired_file.txt", “r"))
== NULL) */
     if ((in_fp = fopen("r.txt", "r")) == NULL)
          printf("ERROR - cannot open r.txt \n");
     else {
          printf("Reading the file....\n");
          getChar();
          do {
               lex();
          } while (nextToken != EOF);
} }
/*****************************************************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
     prevToken=nextToken;
     switch (ch) {
          case '(':
               addChar();
               nextToken = LEFT_PAREN;
               break;
          case ')':
               addChar();
               nextToken = RIGHT_PAREN;
               break;
          case '+':
               addChar();
               nextToken = ADD_OP;
               break;

 }
case '-':
     addChar();
     nextToken = SUB_OP;
     break;
case '*':
     addChar();
     nextToken = MULT_OP;
     break;
case '/':
     addChar();
     nextToken = DIV_OP;
     break;
case ';':
     addChar();
     nextToken = SEM_COL;
     break;
case ',':
     addChar();
     nextToken = COMM;
     break;
case '=':
     addChar();
     nextToken = ASSIGN_OP;
     break;
default:
     addChar();
     nextToken = EOF;
     break;
     return nextToken;
}
/*****************************************************/
 /* addChar - a function to add nextChar to lexeme */
void addChar() {

      if (lexLen <= 98) {
          lexeme[lexLen++] = nextChar;
          lexeme[lexLen] = 0;
} else
     printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
     if ((nextChar = getc(in_fp)) != EOF) {
          if (isalpha(nextChar))
               charClass = LETTER;
          else if (isdigit(nextChar))
               charClass = DIGIT;
          else charClass = UNKNOWN;
     }
     else
          charClass = EOF;
}
/*****************************************************/
 /* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
     while (isspace(nextChar))
getChar();
}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
expressions */

 int lex() {
     lexLen = 0;
     getNonBlank();
     switch (charClass) {
          /* Parse identifiers */
          case LETTER:
               addChar();
               getChar();
               while (charClass == LETTER || charClass == DIGIT) {
                    addChar();
                    prevClass = charClass;
                    getChar();
               }
               nextToken = IDENT;
               break;
          /* Parse integer literals */
          case DIGIT:
               addChar();
               getChar();
               while (charClass == DIGIT) {
addChar();
getChar(); }
               nextToken = INT_LIT;
               break;
          /* Parentheses and operators */
          case UNKNOWN:
               lookup(nextChar);
               getChar();
               if (prevToken == 24 && nextToken == 23) {
addChar();
getChar(); }
               else if (prevToken == 23 && nextToken == 24) {
                    addChar();
getChar();

}
               break;
          /* EOF */
          case EOF:
               nextToken = EOF;
               lexeme[0] = 'E';
               lexeme[1] = 'O';
               lexeme[2] = 'F';
               lexeme[3] = 0;
               break;
     }
     /* End of switch */
     memcpy(string, lexeme,4);
     string[4] = '\0';
     if (strcmp(string,"int")==0) {
          printf("Next token is reserved, Next lexeme is %s\n", lexeme);
     }
     else {
          printf("Next token is: %d, Next lexeme is %s\n",nextToken, lexeme);
}
     return nextToken;
}
/* End of function lex */
