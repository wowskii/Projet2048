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
    int score;

    cout << "Score: " << scoreboard(plateau) << endl;
    cout << "Bienvenue au jeu 2048! Utilisez les flèches pour jouer." << endl;

    debutDessine(w);
    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {

            // Debut d'une partie
            while (!(estGagnant(plateau) || (estTermine(plateau))))
            {
                score = scoreboard(plateau);

                if (w.waitEvent(event))
                {
                    if (event.type == sf::Event::KeyPressed)
                    {
                        int direction = -1;
                        if (Keyboard::isKeyPressed(Keyboard::Left))
                        {
                            direction = 0;
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Right))
                        {
                            direction = 1;
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Up))
                        {
                            direction = 2;
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Down))
                        {
                            direction = 3;
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Q))
                        {
                            w.close();
                            return 0;
                        }

                        else
                        {
                            cout << "Touche invalide, utilisez les flèches !" << endl;
                            continue;
                        }

                        Plateau nouveauPlateau = deplacement(plateau, direction);
                        if (nouveauPlateau == plateau)
                        {
                            cout << "Aucun mouvement possible dans cette direction !" << endl;
                        }
                        else
                        {
                            plateau = nouveauPlateau;
                        }

                        SFMLdessine(plateau, w, score, estGagnant(plateau), estTermine(plateau));

                        cout << "Score: " << score << endl;
                    }
                }
            }

            while (estTermine(plateau) || estGagnant(plateau))
            {
                if (Keyboard::isKeyPressed(Keyboard::R))
                {
                    plateau = plateauInitial();
                    SFMLdessine(plateau, w, 0, false, false);
                }
            }
            w.clear();
        }
    }
    return 0;
}