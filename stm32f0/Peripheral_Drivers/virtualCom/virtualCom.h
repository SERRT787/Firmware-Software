#include "stm32f0xx.h"
#include "stdio.h"
#include "stdlib.h"
#include <stdint.h>
#include "stdarg.h"
#include "string.h"

#ifndef DEBUG
#define DEBUG

void serialPrintInit(void);

void serialPrint(const char *msg, ...);

#endif
