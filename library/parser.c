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
//	@File				tokens.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
//
//  PARSER
//

#include "parser.h"

enum ParserStats {
    PARSER_START,
    PARSER_DECLARE_FUNCTION,
    PARSER_DECLARE_VARIABLE,
    PARSER_END
};

struct Program      *__parser_program;


/*
*   @function      parserInit
*   @param         char * fileNameSource
*   @param         string       name
*   @description
*/
void parser_init(char * fileNameSource) {
    Token               tok;
    struct Function     *_function;

    scanner_init(fileNameSource);

    program_init(&__parser_program);

    int stateMain   = PARSER_START,
        stateReturn = PARSER_START;

    while(stateMain != PARSER_END) {
        switch(stateMain) {

            ////////////////////////////////////
            //
            case PARSER_START: {
                tok = scanner_next_token();
                switch(tok.flag) {
                    case TOKEN_DECLARE:
                        stateMain = PARSER_DECLARE_FUNCTION;
                    break;
                }
            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_FUNCTION: {

                // Declare >Function<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_FUNCTION) {
                    LineErrorException(tok, ERROR_SYNTAX, "Function is missing");
                }

                // Declare Function >ID<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_ID) {
                    LineErrorException(tok, ERROR_SYNTAX, "ID of function is missing");
                }

                /////////////////////////////////////////////
                // DEFINE FUNCTION
                _function = defFunction(__parser_program, &(tok.ID));

                // Declare Function ID >(<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_BRACKET_RIGHT) {
                    LineErrorException(tok, ERROR_SYNTAX, "( is missing");
                }


                // Declare Function ID ([<STATEMENT> <STATEMENT_LIST>]>)<
                tok = scanner_next_token();
                if (tok.flag == TOKEN_ID) {
                    stateReturn = PARSER_DECLARE_FUNCTION;
                    stateMain   = PARSER_DECLARE_VARIABLE;
                    break;
                }

                /////////////////////////////////////////////
                /**/ LABEL_EndDeclareFunction:
                /////////////////////////////////////////////

                // Declare Function ID (>)<
                if (tok.flag != TOKEN_BRACKET_LEFT) {
                    LineErrorException(tok, ERROR_SYNTAX, ") is missing");
                }

                // Declare Function ID () >AS<
                tok = scanner_next_token();
                if (tok.flag != TOKEN_AS) {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }


                program_dump(__parser_program);
                exit(0);

            } break;

            ///////////////////////////////////////////////////////////////////////
            // Declare Function ID (ID As DT[, ID As DT] ..) As DT
            //
            case PARSER_DECLARE_VARIABLE: {

                /////////////////////////////////////////////
                /**/ LABEL_DataType:
                /////////////////////////////////////////////

                // >ID< As DT
                if (tok.flag != TOKEN_ID) {
                    LineErrorException(tok, ERROR_SYNTAX, "ID is missing");
                }

                string tmpID = tok.ID;

                // ID >As< DT
                tok = scanner_next_token();
                if (tok.flag != TOKEN_AS) {
                    LineErrorException(tok, ERROR_SYNTAX, "AS is missing");
                }

                // ID As >DT<
                tok = scanner_next_token();

                switch (tok.flag) {
                    case TOKEN_INTEGER: {
                        defFunctionParameter(&_function, tmpID, DATA_TYPE_INT);
                    } break;

                    case TOKEN_DOUBLE: {
                        defFunctionParameter(&_function, tmpID, DATA_TYPE_DOUBLE);
                    } break;

                    case TOKEN_STRING: {
                        defFunctionParameter(&_function, tmpID, DATA_TYPE_STRING);
                    } break;

                    default: {
                        LineErrorException(tok, ERROR_SYNTAX, "Data Type is missing");
                    }
                }

                tok = scanner_next_token();

                // ID As DT>[, ID As DT ..]<
                if (tok.flag == TOKEN_COMMA)                goto LABEL_DataType;
                if (stateReturn == PARSER_DECLARE_FUNCTION) goto LABEL_EndDeclareFunction;

            } break;

        }
    }
}
///////////////////////////////////////////////////////////////////////////////////
//
//  FUNCTIONS
//



void _dumpFunctions(struct tree_node * node) {
    if (!node) return;
    _dumpFunctions(node->left);


    struct Function * f = node->payload;
    printf("Function(%s) %s\n", node->key, (f->name).str);

    Dump("%d", f->parameters->root);

    _dumpParameters((f->parameters)->root);

    _dumpFunctions(node->right);

    return;
}


void _dumpParameters(struct tree_node * node) {
    Dump("Param");
    if (!node) return;
    Dump("Param run");

    _dumpParameters(node->left);

    struct DIM * var = node->payload;

    printf("  Parameter (%s) :: %s@%s (%s)\n", node->key, getTokenName(var->dataType), var->name);

    _dumpParameters(node->right);

    return;
}

void dumpFunctions(struct Program * p) {
    _dumpFunctions(p->functions->root);
}

void program_dump(struct Program * p) {
    printf(":: SCOPE     ::\n");

    printf(":: FUNCTIONS ::\n");
    dumpFunctions(p);
}

/*
*   @function      functions_init
*   @description
*/
void program_init(struct Program ** p) {

    struct Program * _p = malloc(sizeof(struct Program));

    _p->functions       = new_tree(TREE_PLAIN);
    _p->globalVariables = new_tree(TREE_PLAIN);

    *p = _p;
}

/*
*   @function      defFunction
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
struct Function * defFunction(struct Program * p, string * name) {

    Dump("> Define Function");

    if (p == NULL) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add :: Program is NULL");
    }

    if (!name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Function Add :: ID is NULL");
    }

    struct Function * f = malloc( sizeof(struct Function));

    f->priority   = 0;
    f->parameters = new_tree(TREE_PLAIN);
    f->variables  = new_tree(TREE_PLAIN);

    strInit(&(f->name));
    strCopyString(&(f->name), name);

    tree_add(p->functions, name->str, f);

    return f;
}

/*
*   @function      defFunctionParameter
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
void defFunctionParameter(struct Function * f, string * name, DataType dType) {

    if (f == NULL || !name->length) {
        ErrorException(ERROR_INTERN, "Parser :: Add Parameter");
    }


    Dump("Define Function Param");

    struct DIM * var = defParameter(name, dType);

    Dump(": : : : %s", (f->name).str);

    tree_add(f->parameters, name->str , var);

    Dump("Def END2");
}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
struct DIM * createVariable(string * name, string * value, DataType dType, DIMFrame frame) {

    if (!name->length) {
        ErrorException(ERROR_RUNTIME, "Create Variable :: NAME IS NULL");
    }


    Dump("Create Variable");
    struct DIM * variable;

    strInit(&(variable->name));
    strCopyString(&(variable->name), name);

    variable->dataType = dType;
    variable->frame    = frame;
    if (value->length) {
        switch (dType) {
            case DATA_TYPE_INT: {
                variable->valueInteger = atoi(value->str);
            } break;
            case DATA_TYPE_DOUBLE: {
                char *ptr;
                variable->valueDouble  = strtod(value->str, &ptr);
            } break;
            case DATA_TYPE_STRING: {
                strInit(&(variable->valueString));
                strCopyString(&(variable->valueString), value);
            } break;
        }
    }

    return variable;
}

/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/

struct DIM * defParameter(string * name, DataType dType) {

    string value;
    strInit(&value);

    struct DIM * parameter = createVariable(name, &value, dType, FRAME_PARAMETERS);

    return parameter;
}

/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void parser_set_setting(parserSetting setting);



/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void parser_run(char * fileNameDestiny) {}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void addFunctionParam(Function * fce, string name, short int dateType) {}


/*
*   @function      functionAdd
*   @param         TFunctions * fceTable
*   @param         string       name
*   @description
*/
//void dumpFunctionParams(Function * fce) {}

