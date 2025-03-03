//
// Created by Antonin Jean on 18/02/2025.
//

#include "Time.h"
#include <sys/time.h>

// == UTILS ==

long getMilliSeconds(const struct timeval tv) {
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void usleep_ms(const int ms) {
    usleep(ms * 1000);
}

// ----------------------------------------------
// == TIMER ==

void Timer_refresh(Timer *timer) {
    struct timeval now, result;
    gettimeofday(&now, NULL);
    timersub(&now, &(timer->start), &result);
    timer->deltaTime = getMilliSeconds(result);
    timer->start = now;
}

void Timer_init(Timer *timer) {
    gettimeofday(&(timer->start), NULL);
    timer->deltaTime = 0;
}

// ----------------------------------------------
// == CHRONO ==

void Chrono_init(Chrono *chrono, Timer *timer, long alertTime) {
    *chrono = (Chrono){
        .g_timer = timer,
        .timeValue = 0,
        .isPaused = true,
        .alertTime = alertTime
    };
}

void Chrono_refresh(Chrono *chrono) {
    if (chrono->isPaused) return;
    chrono->timeValue += chrono->g_timer->deltaTime;
}

void Chrono_pause(Chrono *chrono) {
    if (chrono->isPaused) return;
    Timer_refresh(chrono->g_timer);
    Chrono_refresh(chrono);
    chrono->isPaused = true;
}

void Chrono_unpause(Chrono *chrono) {
    if (!chrono->isPaused) return;
    Timer_refresh(chrono->g_timer);
    chrono->isPaused = false;
}

void Chrono_reset(Chrono *chrono) {
    chrono->timeValue = 0;
}

void Chrono_pauseSwitch(Chrono *chrono) {
    chrono->isPaused ? Chrono_unpause(chrono) : Chrono_pause(chrono);
}
