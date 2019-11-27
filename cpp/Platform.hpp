
#ifndef PLATFORM_H
#define PLATFORM_H

#if defined(__linux__)
    #define PLATFORM "linux"
#elif defined(__unix__) || defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM "bsd" // BSD, FreeBSD, OpenBSD, NetBSD, , DragonFly 
        
    #endif
#elif defined(__APPLE__) && defined(__MACH__)
    
    #if TARGET_OS_MAC == 1
        #define PLATFORM "osx"
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM "ios"
    #elif TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM "ios"
    #endif
#elif defined(_WIN32) || defined(_WIN64)
    #define PLATFORM "windows"
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM "windows"
#endif

#endif