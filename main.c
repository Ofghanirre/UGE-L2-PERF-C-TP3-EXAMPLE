#include "Time.h"
#include "Graphics.h"

#define ALERT_TIME_INITIAL_VALUE 25000
#define LOOP_DELAY_MS 10

void kernelLoop(Timer *timer, Chrono *chrono) {
    bool continue_loop;
    do {
        Timer_refresh(timer);
        Chrono_refresh(chrono);
        graphic_refresh(chrono);
        continue_loop = gui_refresh(chrono);
        usleep_ms(LOOP_DELAY_MS);
    } while (continue_loop);
}

int main(void) {
    // Struct Declaration
    Timer timer;
    Chrono chrono;

    // Initialization
    Timer_init(&timer);
    Chrono_init(&chrono, &timer, ALERT_TIME_INITIAL_VALUE);
    graphic_init();

    // Loop
    kernelLoop(&timer, &chrono);

    // Free / Cleaning
    graphic_clear();
    return 0;
}
