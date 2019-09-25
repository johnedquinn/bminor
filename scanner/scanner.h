#include <stdio.h>
#include <stdbool.h>

void stripStringChar();
bool nextIsEscapable(char * s, int subLength);

void stripStringChar() {
	int length = strlen(yytext);
	int subLength = 1;
	for (int i = 1; i < length; i++) {
		yytext[i - subLength] = yytext[i];
		if (yytext[i] == '\\') {
			if (nextIsEscapable(&yytext[i], subLength)) {
				i += 1;
				subLength += 1;
			}
		}
	}
	for (int i = length - 1; i >= length - subLength - 1; i--) {
		yytext[i] = 0;
	}
}

bool stringOrIdentSizeIsOkay() {
	if (strlen(yytext) > 255) return false;
	return true;
}


bool nextIsEscapable(char * s, int subLength) {
	subLength *= -1;
	switch (s[1]) {
		case ('"'): s[subLength] = '"'; break;
		case ('n'): s[subLength] = '\n'; break;
		case ('\''): s[subLength] = '\''; break;
		case ('t'): s[subLength] = '\t'; break;
		case ('0'): s[subLength] = '\0'; break;
		case ('r'): s[subLength] = '\r'; break;
		case ('1'): s[subLength] = '\1'; break;
		default: return false;
	}
	return true;
}
