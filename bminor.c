/*
 * File: bminor.c
 * Author: John Ed Quinn
 * Description: NA
*/

/* INCLUDES */
#include "token.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* DEFINITIONS */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* EXTERNS */
extern FILE *yyin;
extern int yylex();
extern char *yytext;

/* PROTOTYPES */
char * getTokenString(token_t t);
bool scanInfo (token_t t);
void printTokenInfo(token_t t);

/// Function: main
/// Description: main driver for bminor
int main (int argc, char * argv[]) {

	/* Parse Arguments */
	bool SCAN = false;
	bool PARSE = false;
	if (argc != 3) {
		fprintf(stderr, ANSI_COLOR_RED "USAGE ERROR" ANSI_COLOR_RESET " -- Correct Syntax Usage: " ANSI_COLOR_CYAN "bminor -FLAG FILE\n" ANSI_COLOR_RESET);
		exit(1);
	}
	if (!strcmp(argv[1], "-scan")) SCAN = true;
	if (!strcmp(argv[1], "-parse")) PARSE = true;

	/* Open file to scan */
	yyin = fopen(argv[2],"r");
	if(!yyin) {
		printf("Could not open %s\n", argv[2]);
		return 1;
	}

	/* Scan tokens and print info */
	while (1) {
		if (SCAN) {
			token_t t = yylex();
			if (t == TOKEN_EOF) break;
			if (scanInfo(t) == false) exit(1);
		}
	}

	return 0;

}

/// Function: getTokenString
/// Description: returns representative string for tokens
char * getTokenString(token_t t) {
	switch (t) {
		case TOKEN_EOF:
			return "EOF";
		case TOKEN_WHILE:
			return "WHILE";
		case TOKEN_RETURN:
			return "RETURN";
		case TOKEN_ADD:
			return "ADD";
		case TOKEN_IDENT:
			return "IDENT";
		case TOKEN_NUMBER:
			return "NUMBER";
		case TOKEN_STRING:
			return "LITERAL";
		case TOKEN_TYPE_STRING:
			return "STRING";
		case TOKEN_TYPE_INTEGER:
			return "INTEGER";
		case TOKEN_SEMICOLON:
			return "SEMICOLON";
		case TOKEN_IF:
			return "IF";
		case TOKEN_NOT:
			return "NOT";
		case TOKEN_ELSE:
			return "ELSE";
		case TOKEN_FOR:
			return "FOR";
		case TOKEN_CHAR:
			return "CHAR_LITERAL";
		case TOKEN_ERROR:
			return "ERROR";
		case TOKEN_COMMENT:
			return "COMMENT";
		case TOKEN_C_COMMENT:
			return "C_COMMENT";
		case TOKEN_MULTIPLY:
			return "MULTIPLY";
		case TOKEN_DIVIDE:
			return "DIVIDE";
		case TOKEN_MOD:
			return "MOD";
		case TOKEN_SUBTRACT:
			return "SUBTRACT";
		case TOKEN_POWER:
			return "POWER";
		case TOKEN_DECREMENT:
			return "DECREMENT";
		case TOKEN_INCREMENT:
			return "INCREMENT";
		case TOKEN_COLON:
			return "COLON";
		case TOKEN_L_BRACKET:
			return "LEFT_BRACKET";
		case TOKEN_R_BRACKET:
			return "RIGHT_BRACKET";
		case TOKEN_L_PAREN:
			return "LEFT_PAREN";
		case TOKEN_R_PAREN:
			return "RIGHT_PAREN";
		case TOKEN_L_BRACE:
			return "LEFT_BRACE";
		case TOKEN_R_BRACE:
			return "RIGHT_BRACE";
		case TOKEN_ASSIGN:
			return "ASSIGN";
		case TOKEN_COMMA:
			return "COMMA";
    case TOKEN_GREATER_EQUAL:
			return "GREATER_EQUAL";
    case TOKEN_GREATER:
			return "GREATER";
    case TOKEN_EQUAL:
			return "EQUAL";
    case TOKEN_LESS:
			return "LESS";
    case TOKEN_LESS_EQUAL:
			return "LESS_EQUAL";
    case TOKEN_NOT_EQUAL:
			return "NOT_EQUAL";
    case TOKEN_TRUE:
			return "TRUE";
    case TOKEN_FALSE:
			return "FALSE";
    case TOKEN_TYPE_VOID:
			return "VOID";
    case TOKEN_TYPE_BOOLEAN:
			return "BOOLEAN";
		case TOKEN_TYPE_AUTO:
			return "AUTO";
    case TOKEN_TYPE_FUNCTION:
			return "FUNCTION";
    case TOKEN_TYPE_CHAR:
			return "CHAR";
    case TOKEN_TYPE_ARRAY:
			return "ARRAY";
    case TOKEN_PRINT:
			return "PRINT";
		case TOKEN_AND:
			return "AND";
		case TOKEN_OR:
			return "OR";
		default:
			return "NO TOKEN ALLOCATED";
	}
}

/// Function: printTokenInfo
/// Description: prints necessary info about token
void printTokenInfo(token_t t) {
	if (t == TOKEN_STRING || t == TOKEN_CHAR || t == TOKEN_IDENT || t == TOKEN_NUMBER)
		printf("%s %s\n", getTokenString(t), yytext);
	else
		printf("%s\n", getTokenString(t));
}

/// Function: scanInfo
/// Description: performs the scan operation on an input file
bool scanInfo (token_t t) {
	if (t == TOKEN_EOF) return false;
	if (t == TOKEN_ERROR) {
		fprintf(stderr, "Scan error: %s is not a valid token.\n", yytext);
		return false;
	}
	printTokenInfo(t);
	return true;
}
