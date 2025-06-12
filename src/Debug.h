#ifndef DEBUG_H_
#define DEBUG_H_
#define PRINT(level, code)                                                                         \
    {                                                                                              \
        if (MODE >= level)                                                                         \
            code;                                                                                  \
    }
#endif
