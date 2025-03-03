//
// Created by Antonin Jean on 18/02/2025.
//

#include "Graphics.h"
#include "ncurses.h"


/**
* global value containing the program window to be initialized within graphic_init function
 */
WINDOW *win;

// UNUSED
void graphic_color_init() {
    init_pair(CP_BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
}

void graphic_init() {
    initscr(); // Initialisation
    noecho(); // Pas d'affichage de l'entrée clavier
    cbreak(); // Mode caractère par caractère
    keypad(stdscr, TRUE); // Activation des touches spéciales
    nodelay(stdscr, TRUE); // Rend getch() non bloquant
    refresh();
    attron(A_ALTCHARSET);
    win = newwin(16, 80, (LINES - 16) / 2, (COLS - 80) / 2);
}

void graphic_clear() {
    attroff(A_ALTCHARSET);
    endwin(); // Fin de ncurses
}

 void graphic_refresh(const Chrono *chrono) {
    werase(win);
    box(win, 0, 0);
    mvwprintw(win, 1, (getmaxx(win) - 21) / 2, "== Chronometre ==");

    long ms = chrono->timeValue % 1000;
    long sec = (chrono->timeValue / 1000) % 60;
    long min = (chrono->timeValue / 60000) % 60;
    long hr = chrono->timeValue / 3600000;
    mvwprintw(win, 3, (getmaxx(win) - 21) / 2, "%02ld : %02ld : %02ld . %02ld", hr, min, sec, ms / 10);

    sec = (chrono->alertTime / 1000) % 60;
    min = (chrono->alertTime / 60000) % 60;
    hr = chrono->alertTime / 3600000;
    mvwprintw(win, 5, (getmaxx(win) - 28) / 2, "Avertissement : %02ld : %02ld : %02ld . 00", hr, min, sec);

    mvwprintw(win, 7, 4, "-----------------------------------------------------------------------");
    mvwprintw(win, 8, 2, "Espace : lancer / mettre en pause");
    mvwprintw(win, 9, 2, "r : reinitialiser");
    mvwprintw(win, 10, 2, "t : marquer tour");
    mvwprintw(win, 11, 2, "F1/F2 : incrementer / decrementer heure avertissement");
    mvwprintw(win, 12, 2, "F3/F4 : incrementer / decrementer minute avertissement");
    mvwprintw(win, 13, 2, "F5/F6 : incrementer / decrementer seconde avertissement");
    mvwprintw(win, 14, 2, "q : quitter");

    wrefresh(win);
}

bool gui_refresh(Chrono *chrono) {
    int chInput = getch();
    switch (chInput) {
        case 'q':
            return false;
        case ' ':
            Chrono_pauseSwitch(chrono);
            break;
        case 'r':
            Chrono_reset(chrono);
            break;
        case KEY_F(1): chrono->alertTime += 3600000;
            break;
        case KEY_F(2): chrono->alertTime -= 3600000;
            break;
        case KEY_F(3): chrono->alertTime += 60000;
            break;
        case KEY_F(4): chrono->alertTime -= 60000;
            break;
        case KEY_F(5): chrono->alertTime += 1000;
            break;
        case KEY_F(6): chrono->alertTime -= 1000;
            break;
        default: break;
    }
    return true;
}
