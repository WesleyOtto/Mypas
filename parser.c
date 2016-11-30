/**@<parser.c>::**/

#include <stdio.h>
#include <stdlib.h>
// #include <malloc.h>
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
char **namelist(void)
{
	char** symvec = calloc(MAX_ARG_NUM, sizeof(char**));
	int i = 0;

	_namelist_begin:

	symvec[i] = malloc(sizeof(lexeme)+1);
	strcpy(symvec[i],lexeme);
	i++;
	match(ID);
	if(lookahead == ',') {
		match(',');
		goto _namelist_begin;
	}
	return symvec;
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
	int sbpmod, type, i;
	char **namev;
	if(lookahead == VAR) {
		match(VAR);
		do{
			namev = namelist();
			match(':');
			type = vartype();
			for(i = 0; namev[i]; i++) {
				symtab_append(namev[i], type);
			}
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
		case TRUE:
		case FALSE:
		case NOT:
		case '-':
		case '(':
			expr(0);
			break;
		default:
			/*<epsilon>*/
			;
	}
}

/* IF simple_expr THEN stmt [ ELSE stmt ] */
void ifstmt(void)
{
	int _endif, _else;

	match(IF);
	if(expr(BOOLEAN) < 0 ) {
		fprintf(stderr, "Invalid conditional statment\n");
        	semanticErr++;
	}

	_endif = _else = go_false(labelcounter++);

	match(THEN);
	stmt();

	if(lookahead == ELSE) {
		match(ELSE);
		_endif = jump(labelcounter++);
		mklabel(_else);
		stmt();
	}
	mklabel(_endif);
}

/* WHILE simple_expr DO stmt */
void whilestmt(void)
{
	int _while = labelcounter++, _endwhile;

	match(WHILE);

	mklabel(_while);

	if(expr(BOOLEAN) < 0 ) {
		fprintf(stderr, "Invalid conditional statment\n");
		semanticErr++;
	}
	_endwhile = go_false(labelcounter++);

	match(DO);
	stmt();

	jump(_while);
	mklabel(_endwhile);
}

/* REPEAT stmtlist UNTIL simple_expr */
void repstmt(void)
{
	int _repeat = labelcounter++, _endrepeat;

	match(REPEAT);

	mklabel(_repeat);

	stmtlist();
	match(UNTIL);

	if(expr(BOOLEAN) < 0 ) {
		fprintf(stderr, "Invalid conditional statment\n");
		semanticErr++;
	}

	_endrepeat = go_false(labelcounter++);
	jump(_repeat);
	mklabel(_endrepeat);
}

/*
* OP    |  BOOLEAN  | NUMERIC |
* NOT   |     X     |    NA   |
* OR    |     X     |    NA   |
* AND   |     X     |    NA   |
*
* CHS   |     NA    |    X    |
* '+'   |     NA    |    X    |
* '-'   |     NA    |    X    |
* '*'   |     NA    |    X    |
* '/'   |     NA    |    X    |
* DIV   |     NA    | INTEGER |
* MOD   |     NA    | INTEGER |
*
* RELOP |BOOL X BOOL| NUM NUM |
*
*
*
* EXPRESS || INTEGER |  REAL  | DOUBLE |
* ===================================
* INTEGER || INTEGER |  REAL  | DOUBLE |
* REAL    || REAL    |  REAL  | DOUBLE |
* DOUBLE  || DOUBLE  | DOUBLE | DOUBLE |
*
*
* LVALUE  || BOOLEAN  | INTEGER | REAL | DOUBLE
* =============================================
* BOOLEAN || BOOLEAN  |    NA   |  NA  |  NA
* INTEGER ||    NA    | INTEGER |  NA  |  NA
* REAL    ||    NA    |   REAL  | REAL |  NA
* DOUBLE  ||    NA    | DOUBLE  |DOUBLE| DOUBLE
*
*/
int is_compatible(int ltype, int rtype)
{
	switch(ltype) {
		case BOOLEAN:
		case INTEGER:
			if(rtype == ltype) return ltype;
			break;
		case REAL:
			switch(rtype) {
				case INTEGER:
				case REAL:
				return ltype;
			}
			break;
		case DOUBLE:
			switch(rtype) {
				case INTEGER:
				case REAL:
				case DOUBLE:
				return ltype;
			}
			break;
		case 0:
			return rtype;
	}
	return 0;
}

int is_relop()
{
	switch(lookahead) {
		case '>':
			match('>');
			if(lookahead == '=') {
				match('=');
				return GEQ;
			}
			return '>';
		case '<':
			match('<');
			if(lookahead == '>') {
				match('>');
				return NEQ;
			}
			if(lookahead == '=') {
				match('=');
				return LEQ;
			}
			return '<';
		case '=':
			match('=');
			return '=';
	}
	return 0;
}

/*expr -> simple_expr [opref simple_expr]*/
int expr(int inherited_type)
{
	int t1, t2;
	t1 = simple_expr(0);
	if(is_relop()) {
		t2 = simple_expr(0);
		if( (t1 == BOOLEAN && t2 != BOOLEAN) || (t2 == BOOLEAN && t1 != BOOLEAN)) {
			return -1;
		}
		return min(BOOLEAN, t2);
	}
	if(!is_compatible(inherited_type, t1)) {
		return -1;
	}
	return max(BOOLEAN, t1);
}

int check_neg(int acctype)
{
	if (lookahead == '-') {
		match('-');
		if(acctype == BOOLEAN) {
			fprintf(stderr, "incompatible unary operator: fatal error.\n");
			semanticErr++;
		} else if (acctype == 0) {
			acctype = INTEGER;
		}
	} else if (lookahead == NOT) {
		match(NOT);
		if(acctype > BOOLEAN) {
			fprintf(stderr, "incompatible unary operator: fatal error.\n");
			semanticErr++;
		}
		acctype = BOOLEAN;
	}
	return acctype;
}

int check_locality(int varlocality)
{
	if(varlocality < 0) {
		fprintf(stderr, "parser: %s not declared -- fatal error!\n", lexeme);
		return -1;
	}else{
		return symtab[varlocality][1];
	}
}

int check_compatibility(int type1, int type2) {
	return type1 == 0 || (type1 != BOOLEAN && type2 != BOOLEAN)
			||(type1 == BOOLEAN && type2 == BOOLEAN)? 1:0;
}

int simple_expr (int inherited_type)
{
	int varlocality, lvalue = 0, acctype = inherited_type, syntype, ltype, rtype, addFlag, mulFlag;

	acctype = check_neg(acctype);

	T_entry:
	F_entry:
	switch (lookahead) {
		case ID :
			syntype = check_locality( varlocality = symtab_lookup(lexeme));

			match(ID);

			if(lookahead == ASGN){
			/* located variable is ltype */
				match(ASGN);
				
				lvalue = 1;
				ltype = syntype;
				rtype = expr(ltype);

				if(is_compatible(ltype, rtype)) {
					acctype = max(rtype, acctype);
				}
				else{
					acctype = -1;
					fprintf(stderr, "Incompatible type...fatal error.\n");
					semanticErr++;
				}

			}else if(varlocality > -1) {
		
				fprintf(object, "\tpushl %%eax\n\tmovl %s, %%eax\n", symtab_stream + symtab[varlocality][0]);

				if( check_compatibility(acctype, symtab[varlocality][1])){
					acctype = max(acctype, symtab[varlocality][1]);
				}
				else{
					acctype = -1;
					fprintf(stderr, "Incompatible type...fatal error.\n");
					semanticErr++;
				}
			}
			break;

		case TRUE:
		case FALSE:
			if(!is_compatible(acctype, BOOLEAN)) {
				fprintf(stderr, "Incompatible type, expected boolean...fatal error.\n");
				semanticErr++;
			}
			else{
				acctype = BOOLEAN;
			}
			match(lookahead);
			break;

		case DEC:
			if(acctype != BOOLEAN) {
				acctype = max(acctype, INTEGER);
				{
					int lexval= atoi(lexeme);
					char *intIEEE = malloc(sizeof(lexeme)+1);
					sprintf(intIEEE, "$%i", *((int*)&lexval));
					rmove_int(intIEEE);
					free(intIEEE);
				}
			}else{
				fprintf(stderr, "Incompatible type, expected integer...fatal error.\n");
				semanticErr++;
			}
			match(DEC);
			break;

		case FLT:
			if(acctype != BOOLEAN) {
				acctype = max(acctype, REAL);
				{
					float lexval= atof(lexeme);
					char *fltIEEE = malloc(sizeof(lexeme)+1);
					sprintf(fltIEEE, "$%i", *((int*)&lexval));
					rmove_int(fltIEEE);
					free(fltIEEE);
				}
			}else{
				fprintf(stderr, "Incompatible type, expected real...fatal error.\n");
				semanticErr++;
			}
			match(FLT);
			break;

		case DBL:
			if(acctype != BOOLEAN) {
				acctype = max(acctype, DOUBLE);
				{
					double lexval= strtod(lexeme, NULL);
					char *dblIEEE = malloc(sizeof(lexeme)+1);
					sprintf(dblIEEE, "$%lli", *((long long int*)&lexval));
					rmove_int(dblIEEE);
					free(dblIEEE);
				}
			}else{
				fprintf(stderr, "Incompatible type, expected double...fatal error.\n");
				semanticErr++;
			}
			match(DBL);
			break;

		default :
			match('(');
			syntype = expr(0);
			if( check_compatibility(acctype, syntype)) {
				acctype = max(acctype, syntype);
			}else{
				fprintf(stderr, "parenthesized type incompatible with accumulated type...fatal error.\n");
				semanticErr++;
			}
			match(')');
	}

	if ( mulFlag = mulop() ) goto F_entry;

	if ( addFlag = addop() ) goto T_entry;
	
	/* expression ends donw here */
	if (lvalue && varlocality > -1) {
		switch(ltype) {
			case INTEGER:
			case REAL:
				lmove_int(symtab_stream + symtab [varlocality][0]);
				break;
			case DOUBLE:
				lmove_q(symtab_stream + symtab [varlocality][0]);
				break;
			//default://case BOOLEAN:

		}
	}
	return acctype;
}

/* vrbl -> ID
 *
 * cons -> DEC
 *
 * ID = [A-Za-z][A-Za-z0-9]*
 *
 * DEC = [1-9][0-9]* | 0
 *
 * addop -> '+' | '-' */
int addop (void) {
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

/*mulop -> '*' | '/' */
int mulop (void) {
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

void match (int expected) {
	if ( expected == lookahead) {
		lookahead = gettoken (source);
	} else {
		fprintf(stderr,"parser: token mismatch error. found # %d ", lookahead);
		fprintf(stderr,"whereas expected # %d\n", expected);
		exit (SYNTAX_ERR);
	}
}
