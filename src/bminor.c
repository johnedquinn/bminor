/*
 * File: bminor.c
 * Author: John Ed Quinn
 * Description: NA
*/

/* INCLUDES */
#include "token.h"
#include "stmt.h"
#include "library.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* GLOBALS */
int NUM_SCAN_ERRORS = 0;
int NUM_PARSE_ERRORS = 0;
int NUM_RESOLVE_ERRORS = 0;
int NUM_TYPECHECK_ERRORS = 0;
int NUM_CODEGEN_ERRORS = 0;
unsigned int SCRATCH_COUNTER = 0;
unsigned int ARG_COUNTER = 0;

/* EXTERNS */
extern FILE *yyin;
extern int yylex();
extern char *yytext;
extern int yyparse();
extern struct stmt * parser_result;

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
	bool PRINT = false;
	bool RESOLVE = false;
	bool TYPECHECK = false;
	bool CODEGEN = false;
	bool COMPLETE = false;
	char * FILE_NAME = "a.out.s";

	if (argc < 3) {
		fprintf(stderr, AC_RED "USAGE ERROR" AC_RESET " -- Correct Syntax Usage: " AC_CYAN "bminor -FLAG FILE\n" AC_RESET);
		exit(1);
	}

	if (!strcmp(argv[1], "-scan")) SCAN = true;
	else if (!strcmp(argv[1], "-parse")) PARSE = true;
	else if (!strcmp(argv[1], "-print")) PRINT = true;
	else if (!strcmp(argv[1], "-resolve")) RESOLVE = true;
	else if (!strcmp(argv[1], "-typecheck")) TYPECHECK = true;
	else if (!strcmp(argv[1], "-codegen")) {
		if (argc == 4) FILE_NAME = argv[3];
		CODEGEN = true;
	} else {
		COMPLETE = true;
	}

	/* Open file to scan */
	yyin = fopen(argv[2],"r");
	if(!yyin) {
		printf("Could not open %s\n", argv[2]);
		return 1;
	}

	/* Scan tokens and print info */
	if (SCAN) {
		while (1) {
			token_t t = yylex();
			if (t == TOKEN_EOF || t == 0) break;
			if (scanInfo(t) == false) exit(1);
		}
	}
	if (PARSE || PRINT || RESOLVE || TYPECHECK || CODEGEN || COMPLETE) {
		if (yyparse() == 0) {
			if (PARSE) {
				printf("parse successful: \n");
			}
			if (PRINT) {
				stmt_print(parser_result, 0);
			}
			if (RESOLVE || TYPECHECK || CODEGEN || COMPLETE) {
				struct hash_table * head = NULL;
				stmt_resolve(parser_result, head);
				if (NUM_RESOLVE_ERRORS) {
					fprintf(stderr, AC_CYAN "=======> " AC_RED "name resolution failed: " AC_RESET "%d resolution errors\n", NUM_RESOLVE_ERRORS);
					return 1;
				}
			}
			if (TYPECHECK || CODEGEN || COMPLETE) {
				stmt_typecheck(parser_result, NULL);
				if (NUM_TYPECHECK_ERRORS) {
					fprintf(stderr, AC_CYAN "=======> " AC_RED "typechecking failed: " AC_RESET "%d typechecking errors\n", NUM_TYPECHECK_ERRORS);
					return 1;
				}
			}
			if (CODEGEN || COMPLETE) {
				int scratch_table [6] = {0};
				FILE * OUTPUT_FILE = fopen(FILE_NAME, "w");
				if (!OUTPUT_FILE) {
					fprintf(stderr, "Could not write to %s.\n", FILE_NAME);
					return 1;
				}
				stmt_codegen(parser_result, scratch_table, OUTPUT_FILE);
				fclose(OUTPUT_FILE);
				if (NUM_CODEGEN_ERRORS > 0) {
					fprintf(stderr, AC_CYAN "=======> " AC_RED "codegen failed: " AC_RESET "%d typechecking errors\n", NUM_CODEGEN_ERRORS);
					return 1;
				}
			if (COMPLETE) {
				if (execvp("gcc", "-c %s -o %s.o", FILE_NAME) < 0) {
					fprintf(stderr, AC_RED "assembly failed\n");
					return 1;
				}
				if (execvp("gcc", "%s.o bin/library.o", FILE_NAME) < 0) {
					fprintf(stderr, AC_RED "linking failed\n");
					return 1;
				}
				if (execvp("rm", "%s.o %s", FILE_NAME) < 0) {
					fprintf(stderr, AC_RED "removing garbage files failed\n");
					return 1;
				}
			}
			}
			return 0;
		} else {
			printf("Parse Failed!\n");
			return 1;
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
