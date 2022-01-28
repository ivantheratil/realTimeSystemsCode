/**
 * Test program for event logger.  A different test program will be used for
 * marking.  It's up to you to test your program thoroughly by creating
 * your own test cases.  Remember to set your compiler for C99 and to warn
 * if you use uninitialized variables.
 *
 * @author Andrew Morton
 */

#include "logger.h"

int main(void) {
	loggerInit(5);

	log(INFO, "This is a test program.");
	log(WARNING, "These are sample test cases.");
	log(ERROR, "This is a false statement.");
	log(SEVERE, "Doh!");

	loggerPrintByLevel(ERROR);
	loggerPrintByMsg("Th");
}

