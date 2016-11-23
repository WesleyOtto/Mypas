/**@<keywords.c>::**/

#include <string.h>
#include <keywords.h>

char *keywords[] = {"begin", "repeat", "until", "if",
			"then", "else", "while", "do", "var", "procedure", "function",
			"boolean", "integer", "real", "double", "div",
			 "mod", "and", "or", "not", "true", "false", "end"};

int iskeyword ( char const *identifier) {
	int token;
	for ( token = BEGIN; token <= END; token++) {
		if ( strcmp ( keywords [token-BEGIN], identifier) == 0 ) return token;
	}
	return 0 ;
}
