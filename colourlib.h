#ifndef COLOUR_H
#define COLOUR_H

#include "TXLib.h"
#define PRINTFRED(...)  do                                           \
                        {                                            \
                            txSetConsoleAttr (FOREGROUND_RED);       \
                            printf(__VA_ARGS__);                     \
                            txSetConsoleAttr (FOREGROUND_LIGHTGRAY); \
                        } while (0);

#define PRINTFGREEN(...)  do                                           \
                          {                                            \
                            txSetConsoleAttr (FOREGROUND_LIGHTGREEN);  \
                            printf(__VA_ARGS__);                       \
                            txSetConsoleAttr (FOREGROUND_LIGHTGRAY);   \
                          } while (0);


#endif //COLOUR_H