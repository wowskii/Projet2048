#include "modele.hpp"
#include <iostream>
#include <vector>
/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl
using namespace std;

void jeuTest () {
    // --- Test de plateauVide ---
    // Vérifie que le plateau initial est bien vide (toutes les cases à 0)
    Plateau pVide = plateauVide();
    CHECK(pVide == Plateau({{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}));

    // --- Test de plateauInitial ---
    // Vérifie qu'il y a exactement deux cases non nulles dans le plateau initial
    Plateau pInitial = plateauInitial();
    int nombreNonNul = 0;
    for (const auto& ligne : pInitial) {
        for (int val : ligne) {
            if (val != 0) {
                nombreNonNul++;
                CHECK(val == 2 || val == 4); // Vérifie que les valeurs sont soit 2, soit 4
            }
        }
    }
    CHECK(nombreNonNul == 2);

    // --- Tests de déplacement ---
    Plateau plateauTestDeplacement = {{2,4,8,16},{2,2,4,4},{0,0,0,0},{0,2,0,4}};
    CHECK(deplacementGauche(plateauTestDeplacement) == Plateau({{2,4,8,16},{4,8,0,0},{0,0,0,0},{2,4,0,0}}));
    CHECK(deplacementDroite(plateauTestDeplacement) == Plateau({{2,4,8,16},{0,0,4,8},{0,0,0,0},{0,0,2,4}}));
    CHECK(deplacementHaut(plateauTestDeplacement) == Plateau({{4,4,8,16},{0,4,4,8},{0,0,0,0},{0,0,0,0}}));
    CHECK(deplacementBas(plateauTestDeplacement) == Plateau({{0,0,0,0},{0,0,0,0},{0,4,8,16},{4,4,4,8}}));

    // --- Test estGagnant ---
    CHECK(!(estGagnant({{2,4,8,16},{2,2,4,4},{0,0,0,0},{0,2,0,4}})));
    CHECK(estGagnant({{2,4,8,16},{2,2,4,4},{0,2048,0,0},{0,2,0,4}}));

    // --- Test estTermine ---
    CHECK(!(estTermine({{2,4,32,16},{16,32,16,8},{4,16,8,4},{4,8,4,2}})));
    CHECK(estTermine({{2, 4, 8, 16}, {16, 32, 16, 8}, {4, 16, 8, 4}, {2, 4, 2, 8}}));


  
}


int main () {
    jeuTest();
    return 0;
}



