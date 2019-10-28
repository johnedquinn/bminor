// @file   : token.h
// @author : John Ed Quinn
// @desc   : declares the token enum
// @notes  : NA

#ifndef TOKEN_H
#define TOKEN_H

typedef enum
{

     TOKEN_EOF = 258,

     /* KEYWORDS */
     TOKEN_WHILE,
     TOKEN_IF,
     TOKEN_ELSE,
     TOKEN_FOR,
     TOKEN_PRINT,
     TOKEN_TRUE,
     TOKEN_FALSE,
     TOKEN_RETURN,

     /* MATH */
     TOKEN_ADD,
     TOKEN_MULTIPLY,
     TOKEN_DIVIDE,
     TOKEN_MOD,
     TOKEN_SUBTRACT,
     TOKEN_POWER,
     TOKEN_DECREMENT,
     TOKEN_INCREMENT,

     /* IDENTIFIER */
     TOKEN_IDENT,

     /* LITERALS */
     TOKEN_C_COMMENT,
     TOKEN_COMMENT,
     TOKEN_NUMBER,
     TOKEN_STRING,
     TOKEN_CHAR,

     /* TYPES */
     TOKEN_TYPE_STRING,
     TOKEN_TYPE_INTEGER,
     TOKEN_TYPE_BOOLEAN,
     TOKEN_TYPE_FUNCTION,
     TOKEN_TYPE_VOID,
     TOKEN_TYPE_AUTO,
     TOKEN_TYPE_CHAR,
     TOKEN_TYPE_ARRAY,

     /* EXPRESSIONS */
     TOKEN_GREATER_EQUAL,
     TOKEN_GREATER,
     TOKEN_EQUAL,
     TOKEN_LESS,
     TOKEN_LESS_EQUAL,
     TOKEN_NOT_EQUAL,
     TOKEN_AND,
     TOKEN_OR,
     TOKEN_NOT,

     /* SYMBOLS */
     TOKEN_COLON,
     TOKEN_SEMICOLON,
     TOKEN_L_BRACKET,
     TOKEN_R_BRACKET,
     TOKEN_L_PAREN,
     TOKEN_R_PAREN,
     TOKEN_L_BRACE,
     TOKEN_R_BRACE,
     TOKEN_ASSIGN,
     TOKEN_COMMA,

     /* ERROR */
     TOKEN_ERROR
} token_t;

#endif
