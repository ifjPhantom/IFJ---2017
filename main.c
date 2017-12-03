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

    scanner_debug("./tests/Scanner/Test_01_Tokens.txt");

    //parser_init("./tests/Parser/Test_01_Declare_Function.bas");
    //parser_run();

    tests_run("./tests");

    return 0;
}
