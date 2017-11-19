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
//	@File				error.c
//	@Description
//
///////////////////////////////////////////////////////////////////////////////////

#include "error.h"

/*
*	@function ErrorException
*	@param    e      - Error Flag
*	@param    format - Fprint format
*   @param    ...    - Arguments
*/
void ErrorException (int e, char* format, ...) {

    va_list arg;
    va_start(arg, format);
    vfprintf(stderr, format, arg);
    va_end(arg);

    if (e) {
       exit(e);
    }
}

void Dump (char* format, ...) {
    #ifdef DEBUG
    if (DEBUG) {
        va_list arg;
        va_start(arg, format);
        #ifdef DEBUG_TIME
        if (DEBUG_TIME) {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            printf("%d-%d-%d %d:%d:%d ", tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
        }
        #endif
        printf("DUMP :: ");
        vprintf(format, arg);
        printf("\n");
        va_end(arg);
    }
    #else
        va_list arg;
        va_start(arg, format);
        va_end(arg);
    #endif
}
