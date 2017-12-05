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

int main(int argc, char ** argv) {

    init(argc, argv);

    DebugConfigure(DEBUG_ENABLE | DEBUG_LINE /* | DEBUG_TIME */ );

    globalArgs.filePathInput = "./tests/Parser/Test_02_Define_Function.bas";

    parser_init(globalArgs.filePathInput);
    parser_run();

    return 0;
}
