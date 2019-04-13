
#ifndef AST_H
#define AST_H

#include "general.h"
#include "lexer.h"

struct Atom;

enum Ast_Type {
    AST_UNINITIALIZED,
    AST_BINARY_EXPRESSION,
    AST_IDENTIFIER,
    AST_DECLARATION,
    AST_SCOPE,
    AST_FUNCTION,
};

struct Ast {
    Span span;

    Ast_Type type;
};

struct Ast_Type_Info {
    enum Type {
        UNINITIALIZED = 0,
        VOID,
        INTEGER,
        FLOAT,
        STRING,
        STRUCT,
        FUNCTION,
    };

    Type type = UNINITIALIZED;

    bool is_signed = false; // for INTEGER

    // Ast_Function *function;

    s64 size = -1;
};

struct Ast_Expression : Ast {
    Ast_Type_Info *type_info;
};

struct Ast_Binary_Expression : Ast_Expression {
    Ast_Binary_Expression() { type = AST_BINARY_EXPRESSION; }

    Token::Type operator_type;
    Ast_Expression *left  = nullptr;
    Ast_Expression *right = nullptr;
};

struct Ast_Identifier : Ast_Expression {
    Ast_Identifier() { type = AST_IDENTIFIER; }
    Atom *name = nullptr;
};

struct Ast_Declaration : Ast_Expression {
    Ast_Declaration() { type = AST_DECLARATION; }
    Ast_Identifier *identifier = nullptr;
    Ast_Expression *initializer_expression = nullptr;
};

struct Ast_Scope : Ast_Expression {
    Ast_Scope() { type = AST_SCOPE; }
    Ast_Scope *parent = nullptr;
    Array<Ast_Expression *> statements;
};

struct Ast_Function : Ast_Expression {
    Ast_Function() { type = AST_FUNCTION; }

    Ast_Identifier *identifier;

    Array<Ast_Declaration *> arguments;
    Array<Ast_Declaration *> returns;

    Ast_Scope *scope = nullptr;
};

#endif
