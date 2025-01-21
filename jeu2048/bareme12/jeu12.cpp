#include "../modele.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;
using Plateau = vector<vector<int>>;

int main() {
    srand(static_cast<unsigned int>(time(0))); //pour le fonctionnement du générateur de nombres aléatoires dans la fonction tireDeuxOuQuatre

    Plateau plateau = plateauInitial();
    string touche;
    int direction;
    cout << "Bienvenue au jeu 2048! Jouez en entrant z, q, s ou d et en appuyant sur Entrée." << endl;

    while (!(estGagnant(plateau) || estTermine(plateau))) {
        system("clear");
        consoleDessine(plateau);
        cout << "Score: " << scoreboard(plateau) << endl;
        cin >> touche;
        plateau = deplacement(plateau, toucheConversion(touche));

    }

    if (estTermine(plateau)){
        cout << "perdu :(" << endl;
    }
    else {
        cout << "gagné!! ;)" << endl;
    }

    return 0;
}