/**
 * Message logging tool.
 * @author Andrew Morton
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>
#include <time.h>

/* Use this macro to validate inputs. */
#define c_assert(e) ((e) ? (true) : \
		(printf("%s,%d: assertion '%s' failed\n", \
		__FILE__, __LINE__, #e), false))

typedef enum { INFO, WARNING, ERROR, SEVERE } LEVEL;
#define MAX_MSG_SIZE (256-1)

/*
 * This macro is used to log events.  It turns it into a call to
 * loggerLog().
 */
#define log(level, message) \
	loggerLog(level, time(NULL), __FILE__, __LINE__, message)


/* Function prototypes. */

/**
 * Dynamically allocates storage for event log. The storage should be
 * resized if called more than once, truncating events if necessary.
 * @param numLogs event log capacity
 * @return true on success or false on failure
 */
bool loggerInit(size_t numLogs);

/**
 * Logs event if there is room for it.
 * @param level severity
 * @param time as returned by a call to time()
 * @param fileName pointer to const string containing filename
 * @param lineNumber source code line number
 * @param message pointer to const string containing message
 * @return true if logged, false if not logged
 */
bool loggerLog(LEVEL level, time_t time, const char *fileName,
		int lineNumber, const char *message);

/**
 * Print all events with level at least minLevel.  The level order is
 * { INFO < WARNING < ERROR < SEVERE }.  Events to be printed in
 * order logged.
 * @param minLevel minimum event level to print
 */
void loggerPrintByLevel(LEVEL minLevel);

/**
 * Print events containing a given search string.  Events to be printed in
 * order logged.
 * @param searchString string to search for in event messages
 */
void loggerPrintByMsg(const char *searchString);

#endif
