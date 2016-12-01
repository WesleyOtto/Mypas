/**@<parser.h>::**/

extern int lookahead; // @ local

extern int gettoken (FILE *); // @ lexer.c

extern FILE *source, *object; // @ main.c

extern void match (int); // @ local

/* syntax names */
void mypas(void);
void body(void);
void namelist(void);
int vartype(void);
void parmdef(void);
void declarative(void);
void imperative(void);
void stmtlist(void);
void stmt(void);
void ifstmt(void);
void whilestmt(void);
void repstmt(void);

int is_relop(void);
void expr(void);
void simple_expr(void);
int addop(void);
int mulop(void);
