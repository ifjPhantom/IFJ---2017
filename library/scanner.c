///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Krist�na Jandov�  	xjando04
//  Vil�m Faigel		xfaige00
//  Nikola Timkov�		xtimko01
//	Bc. V�clav Dole�al	xdolez76
//
//	@File				scanner.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "scanner.h"

FILE *__scanner_file;

void scanner_init(char * path) {
    FILE * f;
    f = loadFile(path);
    if (f) {
       __scanner_file = f;
    } else {
       ErrorException(ERROR_RUNTIME, "NO FILE: %s", path);
    }
}

Token scanner_next_token() {
    Token t;
    string word;
    strInit(&word);
    t.flag = _scanner_next(&word);
    t.ID   = strUpper(&(word));
    return t;
}

int _scanner_next(string *word){

	char c;
	int i;
	strClear(word);

	int state = SCANNER_START;	//because start

	while(1) {
		c = getc(__scanner_file);
		switch(state){
			case SCANNER_START: //every new statement
				if(isspace(c)) {  //blank makes it start again
					if(c == TOKEN_END_OF_LINE){
						if((c = fgetc(__scanner_file)) == TOKEN_END_OF_LINE){
							state = SCANNER_START;						
						}						
						else{
							ungetc(c, __scanner_file);
							return TOKEN_END_OF_LINE;
						}
					}						
				state = SCANNER_START;
				}
                	 else if(isdigit(c)) {  		 // Getting first digit

					state = SCANNER_DIGIT;
					strAddChar(word, c);

				} else if(isalpha(c) || c =='_') { // Getting first letter

					state =  SCANNER_WORD;
					strAddChar(word, c);

				} else {

				switch(c) {
					case TOKEN_EXCLAMATION_MARK: 			// !
						state = SCANNER_EXCLAMATION_MARK; 	// Can be string
						break;
					case TOKEN_QUOTE:						// '
						state = SCANNER_LINE_COMMENT;	    // Make it ignore whole line
						break;
					case TOKEN_SLASH:								// /
						state =  SCANNER_SLASH; 			// can be for dividing or comments
						break;
					case TOKEN_ADD:		// +
						return TOKEN_ADD; 					// Adding
						break;
					case TOKEN_SUB:							// -		
						return TOKEN_SUB;					// Subtracting
						break;
					case TOKEN_MUL:							// *
						return TOKEN_MUL; 					// Multiplication
						break;
					case TOKEN_BACKSLASH:					// "\\"
						state = SCANNER_BACKSLASH; 			// Can be for integer dividing or escape sequence
						break;
					case TOKEN_EQUALS:						// =
						return TOKEN_EQUALS;					// Equals
						break;
					case TOKEN_LESS:						// <
						state = SCANNER_LESS_THAN; 			// Can be less than or less than_or_equal or not equal
						break;
					case TOKEN_MORE:						// >
						state = SCANNER_MORE_THAN; 			// Can be more than or more than_or_equal
						break;
					case TOKEN_SEMICOLON:								// ;
						return TOKEN_SEMICOLON;			// semicolon
						break;
				   	case EOF :
						return TOKEN_END_OF_FILE;
					break;
					default:
						ErrorException(ERROR_LEXICAL, "Lexical error, lexeme unknown");				// Something else, what is this? Can this happen || not?
					break;
				}
			}

			break;
			case SCANNER_DIGIT:
				if(isdigit(c)) { 					// Getting next digit
					strAddChar(word, c);

				} else if(c == '.') { 				// Getting point
					state = SCANNER_FLOAT;
					strAddChar(word, c);

				} else if(c == 'e' || c == 'E') { 	// Getting E or e
					state = SCANNER_EXPONENT_TRY;
					strAddChar(word, c);

				} else {
					ungetc(c, __scanner_file);
					return TOKEN_INTEGER;			
				}
			break;
			case SCANNER_FLOAT:
				if(isdigit(c)) {
					strAddChar(word, c);
				} else {
					ungetc(c, __scanner_file);
					return DATA_TYPE_DOUBLE; 		
				}
			break;
			case SCANNER_EXPONENT_TRY:
				if(c == '+' || c == '-') {  		// Digit is looking like [0-9]+(e|E)(+|-)
					strAddChar(word, c);
					state = SCANNER_EXPONENT;
				} else {
					ErrorException(ERROR_LEXICAL, "Lexical error, wrong double exponent");			// Digit is looking like [0-9]+(e|E) and then something bad
				}
			break;
			case SCANNER_EXPONENT:
				if(isdigit(c)) {
					strAddChar(word, c);
				} else {
					ungetc(c, __scanner_file);
					return DATA_TYPE_DOUBLE; 		
				}
			break;
			case SCANNER_EXCLAMATION_MARK:
				if(c == TOKEN_DOUBLE_QUOTE) {  		// " after ! (!")
					state = SCANNER_STRING;
				}
				else{
					ErrorException(ERROR_LEXICAL, "Lexical error, ! standing alone"); 			// Only ! standing alone
				}
			break;
			case SCANNER_STRING:
				if(c == TOKEN_DOUBLE_QUOTE) {  		// " after ! (!")
					return DATA_TYPE_STRING; 		
				} else {
					strAddChar(word, c); 			// Saving next char to word
				}
			break;
			case SCANNER_WORD:
				if(!(isalnum(c) || c == '_')){
		        		ungetc(c, __scanner_file); 				
				
					for(i = 0; i<35; i++) {
						if (strCmpConstStrI(word, reserved[i].word) == 0) {
							return reserved[i].token;
							break;
						}
					}
							
					return TOKEN_ID;
					
					
				} else {
					strAddChar(word, c); 			// Saving next char to word
				}
			break;

			case SCANNER_SLASH:
				if(c == TOKEN_QUOTE) {
					state = SCANNER_COMMENT; 		// As /'
					Dump("starting of commentary");
				} else {
					return TOKEN_DIV; 				// Slash used for dividing
				}
			break;
			case SCANNER_LINE_COMMENT:
				if(c == TOKEN_END_OF_LINE) {
					Dump("end of line comentary");
					state = SCANNER_START;
				}
			break;
			case SCANNER_COMMENT:
				if(c == TOKEN_QUOTE) {
					state = SCANNER_COMMENT_TRY;
				} else {
					state = SCANNER_COMMENT; 		// Still commentary
				}
			break;
			case SCANNER_COMMENT_TRY:
				if(c == TOKEN_SLASH) {
					state = SCANNER_START; 			// '/
					Dump("ending of comentary");
				} else {
					state = SCANNER_COMMENT; 		// There was just ', returning to state of comment
				}
			break;
			case SCANNER_LESS_THAN:
				if (c == TOKEN_EQUALS) {
					return TOKEN_LESS_OR_EQUAL;
				} else {
					return TOKEN_LESS; 				// There was just ', returning to state of comment
				}
			break;
			case SCANNER_MORE_THAN:
				if (c == TOKEN_EQUALS) {
					return TOKEN_MORE_OR_EQUAL;
				} else {
					return TOKEN_MORE; 				// There was just ', returning to state of comment
				}
			break;
		}
	}
return 0;
}




