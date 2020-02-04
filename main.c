#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

// constants
#define EOS	257
#define NUM	258

// prototypes 
void error( char * );
int get_token();

/* bounded memory calculator */
int main()
{
	int current_token;

	current_token = get_token();
	while ( current_token != EOS ) {
		current_token = get_token();
	}
}

/* calculator */

// handles addition
int expr()
{
	int value = term();
	while (1) {
		if ( current_token == '+' ) {
			match( '+' );
			value += term();
		}
		else break;
	}
	return value;
}

// handles multiplication
int term()
{
	int value = factor();
	while (1) {
		if ( current_token == '*' ) {
			match( '*' );
			value *= factor();
		}
		else break;
	}
	return value;
}

// handles brackets and numbers
int factor()
{
	int value;

	if ( current_token == '(' ) {
		match( '(' );
		value = expr();
		match( ')' );
		return value;
	}
	else if ( current_token == NUM ) {
		value = current_attribute;
		return value;
	}
	else error( "Unexpected token in factor()" );

}


/* get next token */
int get_token()
{
	int c;		// current character from the stream
	int value;	// value of a number

	while (1) {
		switch ( c = getchar() ) {
		case '+': case '*': case '(': case ')':
			fprintf( stderr, "[OP:%c]", c );
			return c;	// return operators and brackets as is
		case ' ': case '\t':
			continue;	// ignore spaces and tabs
		default:
			if ( isdigit(c) ) {
				value = c - '0';
				while ( isdigit( c = getchar() )) {
					value = value * 10 + (c - '0');
				}
				ungetc( c, stdin );
				fprintf( stderr, "[NUM:%d]", value );
				return NUM;
			}
			else if ( c == '\n' ) {
				return EOS;
			}
			else {
				fprintf( stderr, "{%c}", c );
				error( "Unknown token" );
			}
		}
	}
}

// error reporting function
void error( char *message )
{
	fprintf( stderr, "Error: %s\n", message );
	exit(1);
}




