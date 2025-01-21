#include "../modele.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <ncurses.h>
#include <cstdlib>

using namespace std;
using Plateau = vector<vector<int>>;


int main()
{
    srand(static_cast<unsigned int>(time(0))); 

    initscr();              // Initialisation de ncurses
    keypad(stdscr, TRUE);   // Activation des flèches directionnelles
    curs_set(0);            // Masquage du curseur

    Plateau plateau = plateauInitial();

    printw("Bienvenue au jeu 2048! Utilisez les flèches pour jouer.\n");
    dessine(plateau);
    refresh();

    while (!estTermine(plateau) && !estGagnant(plateau))
    {
        int direction = -1;
        int lecture = getch();

        switch (lecture)
        {
        case KEY_LEFT:
            direction = 0;
            break;
        case KEY_RIGHT:
            direction = 1;
            break;
        case KEY_UP:
            direction = 2;
            break;
        case KEY_DOWN:
            direction = 3;
            break;
        default:
            printw("Touche invalide, utilisez les flèches !\n");
            refresh();
            continue;
        }

        Plateau nouveauPlateau = deplacement(plateau, direction);
        if (nouveauPlateau == plateau)
        {
            printw("Aucun mouvement possible dans cette direction !\n");
        }
        else
        {
            plateau = nouveauPlateau;
        }

        dessine(plateau);
        refresh();
    }

    if (estTermine(plateau))
    {
        printw("Partie terminée. Vous avez perdu. :(");
    }
    else
    {
        printw("Félicitations, vous avez gagné !! ;)");
    }

    refresh();
    getch(); 
    endwin(); //Fin de ncurses

    return 0;
}
