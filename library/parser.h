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
//	@File				parser.h
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


// Vytvoreni promenne
struct DIM {
    string Name;
    string value_string;
    int    value_int;
    double value_double;
};

struct TVariable DIM;

// Parametry
struct TParameters {

};

// Prikaz
struct Comand {
    short int instruction
functionCreate
};

struct TCommands {

};

// Founkce
struct TFunctions {

} TFunctions;

// Telo funkce
typedef struct Function {
    string       Name;
    short int    priority;
    TParameters  parameters;
    TVariables   variables;
    TCommands    commands;
    DIM          _return;
};

typedef struct TFunctions {
    int        count;
    Function * functions;
}
