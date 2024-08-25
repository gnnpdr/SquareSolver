#include "TXLib.h"

#define PRINTFRED(...)  txSetConsoleAttr (FOREGROUND_RED);\
                        printf(__VA_ARGS__);\
                        txSetConsoleAttr (FOREGROUND_LIGHTGRAY);

#define PRINTFGREEN(...)  txSetConsoleAttr (FOREGROUND_LIGHTGREEN);\
                          printf(__VA_ARGS__);\
                          txSetConsoleAttr (FOREGROUND_LIGHTGRAY);