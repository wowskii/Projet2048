#include "../modele.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;
using Plateau = vector<vector<int>>;

int main()
{
    srand(static_cast<unsigned int>(time(0))); // pour le fonctionnement du générateur de nombres aléatoires dans la fonction tireDeuxOuQuatre
    RenderWindow w(VideoMode(850, 850), "Jeu 2048");
    Plateau plateau = plateauInitial();
    //dessine(plateau);
    int score;
    cout << "Score: " << scoreboard(plateau) << endl;
    cout << "Bienvenue au jeu 2048! Utilisez les flèches pour jouer." << endl;


    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();

            

                    Plateau plateau = plateauInitial();

        // Tant que le jeu n'est pas terminé
        while (!estGagnant(plateau) && !estTermine(plateau))
        {
            score = scoreboard(plateau);
            int direction;

            direction = choisirMeilleurDeplacementExpectiminimax(plateau, 4);
            // 80% de succes pour profondeur 4, 10% de succes pour profondeur 3, 40% de gains pour profondeur 2, 10% de gains pour profondeur 2
            // Si l'IA choisit une direction valide
            if (direction != -1)
            {
                Plateau nouveauPlateau = deplacement(plateau, direction);
                if (nouveauPlateau == plateau)
                {
                    cout << "Aucun mouvement possible dans cette direction !" << endl;
                }
                else
                {
                    plateau = nouveauPlateau;
                }
            }

            SFMLdessine(plateau,w,score,estGagnant(plateau),estTermine(plateau));
            cout << "Score: " << score << endl;
            // this_thread::sleep_for(chrono::nanoseconds(100000));
        }

        if (estTermine(plateau))
        {
            cout << "Partie terminée. Vous avez perdu. :(" << endl;
            //perdu++;
        }
        else
        {
            cout << "Félicitations, vous avez gagné !! ;)" << endl;
            //gagne++;
        }
        }
        return 0;
    }
}