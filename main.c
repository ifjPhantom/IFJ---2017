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

#include "./library/init.h"

int main() {

    scanner_init("./tests/scanner_test.txt");

	for (int i = 0; i < 22; i++) {

		Token token = scanner_next_token();
		printf("%d  :: %s \n", token.flag, token.ID);
	}

    return 0;
}
