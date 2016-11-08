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
	NOT,
	VAR,
	BOOLEAN,
	INTEGER,
	REAL,
	DOUBLE,
	DIV,
	PROCEDURE,
	FUNCTION,
	MOD,
	AND,
	OR,
	END,
};

extern char *keywords[];
int iskeyword ( char const *);
