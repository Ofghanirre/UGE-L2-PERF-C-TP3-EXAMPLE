cmake_minimum_required(VERSION 3.29)
project(TP3 C)

set(CMAKE_C_STANDARD 23)

# Inclure le dossier "inc" pour les fichiers d'en-tête
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CURSES_INCLUDE_DIR})

# Trouver la bibliothèque ncurses
find_package(Curses REQUIRED)

# Définition de l'exécutable
add_executable(TP3
        main.c
        src/Time.c
        src/Graphics.c
        inc/Time.h
        inc/Graphics.h
)

# Lien avec ncurses
target_link_libraries(TP3 ${CURSES_LIBRARIES})
