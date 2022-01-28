/**
 * Event logger implementation.
 * @author your name
 */

#include "logger.h"

/** Used by loggerFmtTime() helper function. **/
char loggerTimeString[20];

/**
 * Convert time_t time to a textual representation.  Storage for the
 * returned string is statically allocated.
 * @param time time_t value to convert
 * @return pointer to a static null-terminated string representing date and time
 */
char *loggerFmtTime(time_t time) {
	strftime(loggerTimeString, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
	return loggerTimeString;
}


/**
 * Your #include directives, typedefs, global variables and helper
 * functions here.
 */


/**
 * Complete the following functions.  Function documentation is found in
 * logger.h.
 */

bool loggerInit(size_t numLogs) {
	return false;
}

bool loggerLog(LEVEL level, time_t time, const char *fileName,
		int lineNumber, const char *message) {
	return false;
}

void loggerPrintByLevel(LEVEL minLevel) {
}

void loggerPrintByMsg(const char *searchString) {
}

