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
//	@File				main.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#define DEBUG      1
#define DEBUG_LINE 1
//#define DEBUG_TIME 1

#include "./library/init.h"

int main() {


    scanner_init("./tests/Test_0.bas");

    Token tok;

	do {
        tok = scanner_next_token();

        if (tok.flag == TOKEN_ID) {
            const char * nameToken = getTokenName(tok.flag);

            //////////////////////////////
            tok.ID = strUpper(&(tok.ID));
            //////////////////////////////
            Dump("%d (%s) :: %s", tok.flag, nameToken, tok.ID);
        }

	} while( tok.flag != TOKEN_END_OF_FILE);

    return 0;
}
