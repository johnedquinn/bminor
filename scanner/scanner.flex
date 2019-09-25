%{
#include "token.h"
#include "scanner.h"
%}
DIGIT  [0-9]
LETTER [a-zA-Z]
%%
(" "|\t|\n)         /* skip whitespace */
while               { return TOKEN_WHILE;               }
string              { return TOKEN_TYPE_STRING;         }
char                { return TOKEN_TYPE_CHAR;           }
array               { return TOKEN_TYPE_ARRAY;          }
integer             { return TOKEN_TYPE_INTEGER;        }
for                 { return TOKEN_FOR;                 }
if                  { return TOKEN_IF;                  }
else                { return TOKEN_ELSE;                }
print               { return TOKEN_PRINT;               }
return              { return TOKEN_RETURN;               }
function            { return TOKEN_TYPE_FUNCTION;            }
void                { return TOKEN_TYPE_VOID;                }
boolean             { return TOKEN_TYPE_BOOLEAN;        }
true                { return TOKEN_TRUE;                }
false               { return TOKEN_FALSE;               }
auto                { return TOKEN_TYPE_AUTO;                }
\/\*.*\*\/		      { return TOKEN_C_COMMENT;           }
\/\/.*$             { return TOKEN_COMMENT;             }
(_|{LETTER})({LETTER}|{DIGIT}|_)*  { if (stringOrIdentSizeIsOkay()) return TOKEN_IDENT; else return TOKEN_ERROR; }
\'\\?.\'            {	stripStringChar(); return TOKEN_CHAR;  }
\"([^(\n)(\")]|(\\\"))*[^\\\n]?\"  { stripStringChar(); if (stringOrIdentSizeIsOkay()) return TOKEN_STRING; else return TOKEN_ERROR;}
\&\&                { return TOKEN_AND;                 }
\|\|                { return TOKEN_OR;                  }
{DIGIT}+            { return TOKEN_NUMBER;              }
\-\-                { return TOKEN_DECREMENT;           }
\+\+                { return TOKEN_INCREMENT;           }
\;                  { return TOKEN_SEMICOLON;           }
\<                  { return TOKEN_LESS;                }
\<\=                { return TOKEN_LESS_EQUAL;          }
\=\=                { return TOKEN_EQUAL;               }
\!\=                { return TOKEN_NOT_EQUAL;           }
\!                  { return TOKEN_NOT;                 }
\>                  { return TOKEN_GREATER;             }
\>\=                { return TOKEN_GREATER_EQUAL;       }
\:                  { return TOKEN_COLON;								}
\[                  { return TOKEN_L_BRACKET;		        }
\]                  { return TOKEN_R_BRACKET;		        }
\(                  { return TOKEN_L_PAREN;		          }
\)                  { return TOKEN_R_PAREN;		          }
\{                  { return TOKEN_L_BRACE;		          }
\}                  { return TOKEN_R_BRACE;		          }
\=                  { return TOKEN_ASSIGN;		          }
\,                  { return TOKEN_COMMA;		            }
\+                  { return TOKEN_ADD;                 }
\*                  { return TOKEN_MULTIPLY;            }
\/                  { return TOKEN_DIVIDE;              }
\%                  { return TOKEN_MOD;                 }
\-                  { return TOKEN_SUBTRACT;            }
\^                   { return TOKEN_POWER;		          }
.                   { return TOKEN_ERROR;               }
%%
int yywrap() { return 1; }


