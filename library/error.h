///////////////////////////////////////////////////////////////////////////////////
//
//	@Project 			IFJ 2017
//
//  @Authors
//  Jandov� Krisn�na 	xjando04
//  Vil�m Faigel		xfaige00
//  Nikola Timkov�		xtimko01
//	Bc. V�slav Dole�al	xdolez76
//
//	@File				error.h
//	@Description		
//			
//
///////////////////////////////////////////////////////////////////////////////////

void ErrorException(int e, char* format, ...);

//
// ERROR CODE
//

enum Errors {
	SUCCESS	= 0,   		// Bez chyb
	ERROR_LEXICAL,  	// Lexikalni chyba
	ERROR_SYNTAX,   	// Syntakticka chyba
	ERROR_DEFINE,   	// Nedefinovana fce/prom, redefinace fce/prom
	ERROR_TYPE,     	// Typova nekompatibilita operace, spatny pocet param
	ERROR_CONVERT,  	// Chyba odvozovani datoveho typu
	ERROR_SEMANTIC, 	// Ostatni semanticke chyby
	ERROR_READ_NUM, 	// Chyba pri cteni cisla ze vstupu
	ERROR_UNINIT,   	// Prace s neinicializovanou prom
	ERROR_ZERO_DIV, 	// Deleni nuou
	ERROR_RUNTIME,      // Ostatni behove chyby
	ERROR_INTERN  =	99  // Interni chyba interpretu
}



