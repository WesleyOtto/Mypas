/**@<keywords.h>::**/

enum {
	BEGIN = 0x10001,
	REPEAT,
	UNTIL,
	IF,
	THEN,
	ELSE,
	WHILE,
	DO,
	VAR,
	PROCEDURE,
	FUNCTION,
	BOOLEAN,
	INTEGER,
	REAL,
	DOUBLE,
	DIV,
	MOD,
	AND,
	OR,
	NOT,
	TRUE,
	FALSE,
	END,
};

extern char *keywords[];
int iskeyword ( char const *);
