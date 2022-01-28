#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#define c_assert(e) ((e) ? (true) : \
        (printf("%s,%d: assertion '%s' failed\n", \
        __FILE__, __LINE__, #e), false))

#define ATTACK 'A'
#define RETREAT 'R'

bool setup(uint8_t nGeneral, bool loyal[], uint8_t reporter);
void cleanup(void);
void broadcast(char command, uint8_t commander);
void general(void *args);

#endif
