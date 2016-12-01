/**@<parser.c>::**/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <macros.h>
#include <tokens.h>
#include <lexer.h>
#include <keywords.h>
#include <symtab.h>
#include <mypas.h>
#include <pseudoassembly.h>
#include <parser.h>

#define MAX_ARG_NUM 1024

/*mypas -> body'.' */
void mypas(void)
{
    lookahead = gettoken (source);
    body();
    match('.');
}

/* body -> declarative imperative */
void body(void)
{
    declarative();
    imperative();
}

/* namelist -> ID {, ID} */
void namelist(void)
{
    _namelist_begin:
    match(ID);
    if(lookahead == ',') {
        match(',');
        goto _namelist_begin;
    }
}

int vartype(void)
{
    switch(lookahead) {
    case INTEGER:
        match(INTEGER);
        return INTEGER;

    case REAL:
        match(REAL);
        return REAL;

    case DOUBLE:
        match(DOUBLE);
        return DOUBLE;

    default:
        match(BOOLEAN);
        return BOOLEAN;
    }
}

/* parmdef -> [ ( [VAR] namelist ':' vartype { ';' [VAR] namelist ':' vartype } ) ] */
void parmdef(void)
{
    if(lookahead == '(') {
        match('(');
        par_begin:
        if(lookahead == VAR) match(VAR);
        namelist();
        match(':');
        vartype();
        if(lookahead == ';') {
            match(';');
            goto par_begin;
        }
        match(')');
    }
}

/* declarative -> [ VAR namelist ':' vartype ';' { namelist ':' vartype ';' } ]
                { sbpmod sbpname parmdef [ ':' fnctype ] ';' body ';' } */
void declarative(void)
{
    int sbpmod;
    if(lookahead == VAR) {
        match(VAR);
        do{
            namelist();
            match(':');
            vartype();
            match(';');
        }while(lookahead == ID);
    }

    while(lookahead == PROCEDURE || lookahead == FUNCTION) {
        sbpmod = lookahead;
        match(lookahead);
        match(ID); //sbpname
        parmdef();
        if(sbpmod == FUNCTION && lookahead == ':'){
            match(':');
            vartype();//vartype == fnctype
        }
        match(';');
        body();
        match(';');
    }
}

/* imperative -> BEGIN stmtlist END */
void imperative(void)
{
    match(BEGIN);
    stmtlist();
    match(END);
}

/* stmtlist -> stmt { ';' stmt } */
void stmtlist(void)
{
    stmt();
    while(lookahead == ';') {
        match(';');
        stmt();
    }
}

void stmt(void)
{
    switch (lookahead) {
        case BEGIN:
            imperative();
            break;
        case IF:
            ifstmt();
            break;
        case WHILE:
            whilestmt();
            break;
        case REPEAT:
            repstmt();
            break;

        case ID:
        case DEC:
        case FLT:
        case DBL:
        case TRUE:
        case FALSE:
        case NOT:
        case '-':
        case '(':
            expr();
            break;
        default:
            /*<epsilon>*/
            ;
    }
    fprintf(object,"\n");
}

/* IF expr THEN stmt [ ELSE stmt ] */
void ifstmt(void)
{
    match(IF);
    expr();

    match(THEN);
    stmt();

    if(lookahead == ELSE) {
        match(ELSE);
        stmt();
    }
}

/* WHILE expr DO stmt */
void whilestmt(void)
{
    match(WHILE);
    expr();
    match(DO);
    stmt();
}

/* REPEAT stmtlist UNTIL expr */
void repstmt(void)
{
    match(REPEAT);

    stmtlist();
    match(UNTIL);

    expr();
}

int is_relop(void)
{
    switch(lookahead) {
        case '>':
            match('>');
            if(lookahead == '=') {
                match('=');
                return GEQ; //Greater or equal
            }
            return '>'; //Greater
        case '<':
            match('<');
            if(lookahead == '>') {
                match('>');
                return NEQ; //Not Equal
            }
            if(lookahead == '=') {
                match('=');
                return LEQ; //Less or equal
            }
            return '<'; //Less
        case '=':
            match('=');
            return '='; //Equal
    }
    return 0;
}

/*expr -> simple_expr [opref simple_expr]*/
void expr(void)
{
    simple_expr();
    if( is_relop()) {
        simple_expr();
    }
}

void simple_expr(void)
{
    if (lookahead == '-') {
        match('-');
    } else if (lookahead == NOT) {
        match(NOT);
    }

    T_entry:
    F_entry:
    switch (lookahead) {
        case ID :
            match(ID);

            if(lookahead == ASGN){
                match(ASGN);
                expr();
            }
            break;

        case TRUE:
        case FALSE:
            match(lookahead);
            break;

        case DEC:
            match(DEC);
            break;

        case FLT:
            match(FLT);
            break;

        case DBL:
            match(DBL);
            break;

        default :
            match('(');
            expr();
            match(')');
    }


    if ( mulop()) goto F_entry;
    if ( addop()) goto T_entry;
}

 // addop -> '+' | '-'
int addop (void)
{
    switch(lookahead){
        case '+':
            match('+'); return '+';
        case '-':
            match('-'); return '-';
        case OR:
            match(OR); return OR;
    }
    return 0;
}

// mulop -> '*' | '/'
int mulop (void)
{
    switch(lookahead) {
        case '*':
            match('*');
            return '*';
        case '/':
            match('/');
            return '/';
        case AND:
            match(AND);
            return AND;
        case MOD:
            match(MOD);
            return MOD;
    }
    return 0;
}


/***************************** lexer-to-parser interface **************************/
int lookahead; // @ local

void match (int expected)
{
    if ( expected == lookahead) {
        lookahead = gettoken (source);
    } else {
        fprintf(stderr,"parser: token mismatch error. found # %d ", lookahead);
        fprintf(stderr,"whereas expected # %d\n", expected);
        printf("lex: %s\n", lexeme);
        remove(output_file_name);
        exit (SYNTAX_ERR);
    }
}
