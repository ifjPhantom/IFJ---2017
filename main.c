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

struct pos {
    int x;
    int y;
};

int main() {

    FILE * a = fopen("./stdout.txt", "w+");
    FILE * b = fopen("./stderr.txt", "w+");

    ErrorInit(stdout, stdout);


    //scanner_debug("./tests/Scanner/Test_01_Tokens.txt");

    //parser_init("./tests/Parser/Test_01_Declare_Function.bas");
    parser_init("./tests/Parser/Test_02_Define_Function.bas");
    parser_run();

    fclose(a);
    fclose(b);
    //tests_run("./tests");

    /*
    struct pos * a = malloc(sizeof(struct pos));
    a->x = 5;
    a->y = 42;

    struct tree * t = new_tree(TREE_PLAIN);
    tree_add(t, "ahoj", a);


    struct pos * b;
    tree_get(t, "ahoj", (void *) &b);

    printf("%d %d", b->x, b->y);
    return 0;
    */
}
