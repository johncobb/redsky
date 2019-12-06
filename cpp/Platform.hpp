/**
 * @file Platform.hpp
 *
 * @author John Cobb
 * Contact: emailjohncobb@gmail.com
 * Github: github.com/johncobb
 * Tweet: @johncobbtweets
 */

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

#include <time.h>
#include <sys/time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

typedef unsigned long clock_time_t;
extern clock_time_t _get_millis();


struct timespec ts;

/*
 * Time:
 * https://stackoverflow.com/questions/3756323/how-to-get-the-current-time-in-milliseconds-from-c-in-linux
 * https://gist.github.com/jbenet/1087739
 * http://www.raspberry-projects.com/pi/programming-in-c/timing/clock_gettime-for-acurate-timing
 */
void current_utc_time(struct timespec *ts)
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif
}

clock_time_t _get_millis()
{

    current_utc_time(&ts);

    // printf("s:  %lu\n", ts.tv_sec);
    // printf("ns: %lu\n", ts.tv_nsec);

    // return ts.tv_nsec;
    return round(ts.tv_nsec /1.0e6f);

}

#endif