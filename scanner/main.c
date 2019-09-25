#include "token.h"
#include "main.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yylex();
extern char *yytext;

int main(int argc, char * argv[]) {

	/* Open file to scan */
	yyin = fopen(argv[1],"r");
	if(!yyin) {
		printf("Could not open %s\n", argv[1]);
		return 1;
	}

	// Scan tokens and print info
	while (1) {
		token_t t = yylex();
		if (t == TOKEN_EOF) break;
		if (scanInfo(t) == false) exit(1);
	}

	return 0;

}
