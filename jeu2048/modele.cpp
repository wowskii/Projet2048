#include "modele.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <ncurses.h>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace std;
using namespace sf;

using Plateau = vector<vector<int>>;

int tireDeuxOuQuatre()
{
    int random = rand() % 10;
    if (random < 9)
    {
        return 2;
    }
    return 4;
}

Plateau plateauVide()
{
    vector<vector<int>> tab;
    tab = vector<vector<int>>(4);
    for (int i = 0; i < tab.size(); i++)
    {
        tab[i] = vector<int>(4);
    }
    for (int i = 0; i < tab.size(); i++)
    {
        for (int j = 0; j < tab[i].size(); j++)
        {
            tab[i][j] = 0;
        }
    }
    return tab;
}

Plateau plateauInitial()
{
    Plateau tab = plateauVide();
    int ligne = rand() % 4;
    int colonne = rand() % 4;
    int ligne2;
    int colonne2;
    do
    {
        ligne2 = rand() % 4;
        colonne2 = rand() % 4;
    } while (ligne == ligne2 && colonne == colonne2);
    tab[ligne][colonne] = tireDeuxOuQuatre();
    tab[ligne2][colonne2] = tireDeuxOuQuatre();
    return tab;
}

Plateau deplacementGauche(Plateau plateau)
{
    int case0 = 0;          // Dernière valeur non nulle rencontrée
    int case0Abscisse;      // Position de cette valeur
    int espaceVideAbscisse; // Position du premier espace vide
    bool dansUnEspaceVide;  // True si un espace vide est trouvé et False sinon
    for (int i = 0; i < plateau.size(); i++)
    {
        case0 = 0;
        case0Abscisse = 0;
        dansUnEspaceVide = false;
        espaceVideAbscisse = 0;
        // Parcours des cases de gauche à droite
        for (int j = 0; j < plateau.size(); j++)
        {
            if (plateau[i][j] != 0) // On ne fait rien si notre case est vide
            {
                if (plateau[i][j] != case0)
                {
                    // Mettre à jour la dernière valeur rencontrée
                    case0 = plateau[i][j];
                    case0Abscisse = j;
                }
                else if (plateau[i][j] == case0)
                {
                    // Combinaison des cases si elles ont la même valeur
                    plateau[i][case0Abscisse] = plateau[i][j] + case0;
                    plateau[i][j] = 0;
                    case0 = 0; // Réinitialiser la valeur combinée pour éviter une double combinaison
                }
            }
        }
        // Décaler toutes les cases non nulles vers la gauche
        for (int j = 0; j < plateau.size(); j++)
        {
            if (plateau[i][j] == 0 && !dansUnEspaceVide)
            {
                // Début d'un espace vide
                espaceVideAbscisse = j;
                dansUnEspaceVide = true;
            }
            else if (plateau[i][j] != 0 && dansUnEspaceVide)
            {
                // Déplacement d'une case non nulle dans l'espace vide
                plateau[i][espaceVideAbscisse] = plateau[i][j];
                plateau[i][j] = 0;
                espaceVideAbscisse++;
            }
        }
    }
    return plateau;
}

Plateau deplacementDroite(Plateau plateau)
{
    int case0 = 0;          // Dernière valeur non nulle rencontrée
    int case0Abscisse;      // Position de cette valeur
    int espaceVideAbscisse; // Position du premier espace vide
    bool dansUnEspaceVide;  // True si un espace vide est trouvé et False sinon

    for (int i = 0; i < plateau.size(); i++)
    {
        case0 = 0;
        case0Abscisse = 0;
        dansUnEspaceVide = false;
        espaceVideAbscisse = 0;

        // Parcours des cases de droite à gauche
        for (int j = plateau.size() - 1; j >= 0; j--)
        {
            if (plateau[i][j] != 0) // On ne fait rien si notre case est vide
            {
                if (plateau[i][j] != case0)
                {
                    // Mettre à jour la dernière valeur rencontrée
                    case0 = plateau[i][j];
                    case0Abscisse = j;
                }
                else if (plateau[i][j] == case0)
                {
                    // Combinaison des cases si elles ont la même valeur
                    plateau[i][case0Abscisse] = 2 * case0;
                    // cout << "mul a" << i << j << " ";
                    plateau[i][j] = 0;
                    case0 = 0; // Réinitialiser la valeur combinée pour éviter une double combinaison
                }
                // cout << plateau[i][j] << " ";
            }
        }

        // Décaler toutes les cases non nulles vers la droite
        for (int j = plateau.size() - 1; j >= 0; j--)
        {
            if (plateau[i][j] == 0 && !dansUnEspaceVide)
            {
                // Début d'un espace vide
                espaceVideAbscisse = j;
                dansUnEspaceVide = true;
            }
            else if (plateau[i][j] != 0 && dansUnEspaceVide)
            {
                // Déplacement d'une case non nulle dans l'espace vide
                plateau[i][espaceVideAbscisse] = plateau[i][j];
                plateau[i][j] = 0;
                espaceVideAbscisse--;
            }
        }
        // cout << endl;
    }
    return plateau;
}

Plateau deplacementHaut(Plateau plateau)
{
    int case0 = 0;          // Dernière valeur non nulle rencontrée
    int case0Ordonnee;      // Position de cette valeur
    int espaceVideOrdonnee; // Position du premier espace vide
    bool dansUnEspaceVide;  // True si un espace vide est trouvé et False sinon
    for (int j = 0; j < plateau.size(); j++)
    {
        case0 = 0;
        case0Ordonnee = 0;
        dansUnEspaceVide = false;
        espaceVideOrdonnee = 0;
        // Parcours des cases de haut en bas
        for (int i = 0; i < plateau.size(); i++)
        {
            if (plateau[i][j] != 0) // On ne fait rien si notre case est vide
            {
                if (plateau[i][j] != case0)
                {
                    // Mettre à jour la dernière valeur rencontrée
                    case0 = plateau[i][j];
                    case0Ordonnee = i;
                }
                else if (plateau[i][j] == case0)
                {
                    // Combinaison des cases si elles ont la même valeur
                    plateau[case0Ordonnee][j] = plateau[i][j] + case0;
                    plateau[i][j] = 0;
                    case0 = 0; // Réinitialiser la valeur combinée pour éviter une double combinaison
                }
            }
        }
        // Décaler toutes les cases non nulles vers le haut
        for (int i = 0; i < plateau.size(); i++)
        {
            if (plateau[i][j] == 0 && !dansUnEspaceVide)
            {
                // Début d'un espace vide
                espaceVideOrdonnee = i;
                dansUnEspaceVide = true;
            }
            else if (plateau[i][j] != 0 && dansUnEspaceVide)
            {
                // Déplacement d'une case non nulle dans l'espace vide
                plateau[espaceVideOrdonnee][j] = plateau[i][j];
                plateau[i][j] = 0;
                espaceVideOrdonnee++;
            }
        }
    }
    return plateau;
}

Plateau deplacementBas(Plateau plateau)
{
    int case0 = 0;          // Dernière valeur non nulle rencontrée
    int case0Ordonnee;      // Position de cette valeur
    int espaceVideOrdonnee; // Position du premier espace vide
    bool dansUnEspaceVide;  // True si un espace vide est trouvé et False sinon
    for (int j = plateau.size() - 1; j >= 0; j--)
    {
        case0 = 0;
        case0Ordonnee = 0;
        dansUnEspaceVide = false;
        espaceVideOrdonnee = 0;
        // Parcours des cases de haut en bas
        for (int i = plateau.size() - 1; i >= 0; i--)
        {
            if (plateau[i][j] != 0) // On ne fait rien si notre case est vide
            {
                if (plateau[i][j] != case0)
                {
                    // Mettre à jour la dernière valeur rencontrée siiuuuu
                    case0 = plateau[i][j];
                    case0Ordonnee = i;
                }
                else if (plateau[i][j] == case0)
                {
                    // Combinaison des cases si elles ont la même valeur
                    plateau[case0Ordonnee][j] = plateau[i][j] + case0;
                    plateau[i][j] = 0;
                    case0 = 0; // Réinitialiser la valeur combinée pour éviter une double combinaison
                }
            }
        }
        // Décaler toutes les cases non nulles vers le haut
        for (int i = plateau.size() - 1; i >= 0; i--)
        {
            if (plateau[i][j] == 0 && !dansUnEspaceVide)
            {
                // Début d'un espace vide
                espaceVideOrdonnee = i;
                dansUnEspaceVide = true;
            }
            else if (plateau[i][j] != 0 && dansUnEspaceVide)
            {
                // Déplacement d'une case non nulle dans l'espace vide
                plateau[espaceVideOrdonnee][j] = plateau[i][j];
                plateau[i][j] = 0;
                espaceVideOrdonnee--;
            }
        }
    }
    return plateau;
}

Plateau deplacement(Plateau plateau, int direction)
{
    // Gauche: 0 / Droite: 1 / Haut: 2 / Bas: 3
    Plateau plateauDeplace;
    if (direction == 0)
    {
        plateauDeplace = deplacementGauche(plateau);
    }
    else if (direction == 1)
    {
        plateauDeplace = deplacementDroite(plateau);
    }
    else if (direction == 2)
    {
        plateauDeplace = deplacementHaut(plateau);
    }
    else
    {
        plateauDeplace = deplacementBas(plateau);
    }

    if (plateauDeplace != plateau)
    {
        int ligneNouvelleTuile;
        int colonneNouvelleTuile;
        do
        {
            ligneNouvelleTuile = rand() % 4;
            colonneNouvelleTuile = rand() % 4;
        } while (plateauDeplace[ligneNouvelleTuile][colonneNouvelleTuile] != 0);
        plateauDeplace[ligneNouvelleTuile][colonneNouvelleTuile] = tireDeuxOuQuatre();
    }
    return plateauDeplace;
}

string consoleDessine(Plateau p)
{
    cout << "*************************" << endl;
    for (int i = 0; i < p.size(); i++)
    {
        cout << "*";
        for (int j = 0; j < p.size(); j++)
        {
                        if (p[i][j] == 0)
            {
                cout << "     *";
            }
            else if (p[i][j] < 10)
            {
                cout << "  " << p[i][j] << "  " << "*";
            }
            else if (p[i][j] < 100)
            {
                cout << " " << p[i][j] << "  " << "*";
            }
            else if (p[i][j] < 1000)
            {
                cout << " " << p[i][j] << " " << "*";
            }
            else if (p[i][j] < 10000)
            {
                cout << " " << p[i][j] << "*";
            }
            else
            {
                cout << p[i][j] << "*";
            }
        }
        cout << endl
             << "*************************" << endl;
    }
    return "Done";
}

void dessine(Plateau p) {
    // Initialisation de ncurses
    initscr();
    start_color();
    noecho();
    curs_set(0);

    // Définir des paires de couleurs pour les cases
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Par défaut
    init_pair(2, COLOR_WHITE, COLOR_YELLOW); // 2
    init_pair(3, COLOR_WHITE, COLOR_RED);    // 4
    init_pair(4, COLOR_WHITE, COLOR_GREEN);  // 8
    init_pair(5, COLOR_WHITE, COLOR_BLUE);   // 16
    init_pair(6, COLOR_WHITE, COLOR_MAGENTA);// 32
    init_pair(7, COLOR_WHITE, COLOR_CYAN);   // 64
    init_pair(8, COLOR_BLACK, COLOR_YELLOW); // 128 e
    init_pair(9, COLOR_BLACK, COLOR_RED);    // 256
    init_pair(10, COLOR_BLACK, COLOR_GREEN); // 512
    init_pair(11, COLOR_BLACK, COLOR_BLUE);  // 1024
    init_pair(12, COLOR_BLACK, COLOR_MAGENTA);// 2048

    // Taille du plateau
    int size = p.size();


    clear();
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value = p[i][j];
            int color = 1;  // Couleur par défaut

            // Assigner la couleur en fonction de la valeur
            switch (value) {
                case 2: color = 2; break;
                case 4: color = 3; break;
                case 8: color = 4; break;
                case 16: color = 5; break;
                case 32: color = 6; break;
                case 64: color = 7; break;
                case 128: color = 8; break;
                case 256: color = 9; break;
                case 512: color = 10; break;
                case 1024: color = 11; break;
                case 2048: color = 12; break;
            }

            // Afficher la case
            attron(COLOR_PAIR(color));
            mvprintw(i * 5 + 1, j * 10 + 1, "+---------+");
            mvprintw(i * 5 + 2, j * 10 + 1, "|         |");
            mvprintw(i * 5 + 3, j * 10 + 1, "|         |");
            if (value != 0) {
                mvprintw(i * 5 + 3, j * 10 + 5 - (value < 10 ? 0 : value < 100 ? 1 : value < 1000 ? 2 : 3), "%d", value);
            }
            mvprintw(i * 5 + 4, j * 10 + 1, "|         |");
            mvprintw(i * 5 + 5, j * 10 + 1, "+---------+");
            attroff(COLOR_PAIR(color));
        }
    }

    mvprintw(size * 5 + 2, 1, "SCORE : %d", scoreboard(p));
    refresh();
}

bool estTermine(Plateau plateau)
{
    if ((deplacement(plateau, 0) == plateau) && (deplacement(plateau, 1) == plateau) && (deplacement(plateau, 2) == plateau) && (deplacement(plateau, 3) == plateau))
    {
        return true;
    }
    return false;
}

bool estGagnant(Plateau plateau)
{
    for (int i = 0; i < plateau.size(); i++)
    {
        for (int j = 0; j < plateau.size(); j++)
        {
            if (plateau[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}

int toucheConversion(string touche)
{
    if (touche == "q")
    {
        return 0;
    }
    else if (touche == "d")
    {
        return 1;
    }
    else if (touche == "z")
    {
        return 2;
    }
    else if (touche == "s")
    {
        return 3;
    }
    return 0;
}

int scoreboard(Plateau plateau)
{
    int scoreactuel = 0;

    for (int i = 0; i < plateau.size(); i++)
    {
        for (int j = 0; j < plateau[i].size(); j++)
        {
            scoreactuel += plateau[i][j];
        }
    };

    return scoreactuel;
}

int heuristiqueSerpent(Plateau plateau)
{
    double h = 0;
    Plateau serpentParfait =
        {{65536, 32768, 16384, 8192},
         {512, 1024, 2048, 4096},
         {256, 128, 64, 32},
         {2, 4, 8, 16}};

    for (int i = 0; i < plateau.size(); i++)
    {
        for (int j = 0; j < plateau.size(); j++)
        {
            h += plateau[i][j] * serpentParfait[i][j];
        }
    }
    return h;
}

double expectiminimax(Plateau plateau, int profondeur, int mouvement)
{
    if (estTermine(plateau))
    {
        return -INFINITY;
    }
    else if (profondeur == 0)
    {
        return heuristiqueSerpent(plateau);
    }

    double a = 0;
    if (profondeur % 2 != 0)
    {
        a = -INFINITY;

        for (auto mouvement : obtenirMouvementsValides(plateau))
        {
            Plateau nouveauPlateau = deplacement(plateau, mouvement); 
            double res = expectiminimax(nouveauPlateau, profondeur - 1, mouvement);
            a = max(a, res);
        }
    }
    else if (profondeur % 2 == 0)
    {
        // renvoyer la moyenne des valeurs Expectiminimax du successeur du plateau
        a = 0;
        vector<pair<int, int>> positions = obtenirPositionsNouvellesTuilesPossibles(plateau);
        for (auto positionNouvelleTuile : positions)
        {
            Plateau plateauSimule2 = simulerNouvelleTuile(plateau, positionNouvelleTuile, 2);
            a += 1.0 / positions.size() * 0.9 * expectiminimax(plateauSimule2, profondeur - 1, mouvement);
            Plateau plateauSimule4 = simulerNouvelleTuile(plateau, positionNouvelleTuile, 4);
            a += 1.0 / positions.size() * 0.1 * expectiminimax(plateauSimule4, profondeur - 1, mouvement);
        }
    }
    return a;
}

int choisirMeilleurDeplacementExpectiminimax(Plateau plateau, int profondeur)
{
    double maxScore = -INFINITY;
    int meilleurDeplacement = 0;

    for (auto mouvement : obtenirMouvementsValides(plateau))
    {
        Plateau nouveauPlateau = deplacement(plateau, mouvement);
        double score = expectiminimax(nouveauPlateau, profondeur, mouvement);

        if (score > maxScore)
        {
            maxScore = score;
            meilleurDeplacement = mouvement;
        }
    }

    // cout << "Current Depth: " << profondeur << ", Valid Moves: " << obtenirMouvementsValides(plateau).size() << " " << maxScore << endl;

    return meilleurDeplacement;
}

vector<int> obtenirMouvementsValides(Plateau plateau)
{
    vector<int> mouvements = {};
    for (int i = 0; i < 4; i++)
    {
        if (deplacement(plateau, i) != plateau)
        {
            mouvements.push_back(i);
            // cout << i;
        }
    }
    return mouvements;
}

vector<pair<int, int>> obtenirPositionsNouvellesTuilesPossibles(Plateau plateau)
{
    vector<pair<int, int>> tuilesVides;
    for (int i = 0; i < plateau.size(); i++)
    {
        for (int j = 0; j < plateau.size(); j++)
        {
            if (plateau[i][j] == 0)
            {
                tuilesVides.push_back({i, j});
            }
        }
    }
    return tuilesVides;
}

Plateau simulerNouvelleTuile(Plateau plateau, pair<int, int> position, int valeur)
{
    Plateau nouveauPlateau = plateau;
    nouveauPlateau[position.first][position.second] = valeur;
    return nouveauPlateau;
}

// SFML

void SFMLdessine(Plateau p, RenderWindow &w, int score, bool estGagnant, bool estTermine)
{
    
    Font police; // initialiser la police
    if (!police.loadFromFile("/home/quentin/Projet2048WSL/Projet2048QN-1/jeu2048/ressources/LEMONMILK-Regular.otf"))
    {
        cerr << "SFML font error" << endl;
    }
    w.clear();
    if (!estGagnant && !estTermine)
    {
        // ordonnee
        for (int i = 0; i < p.size(); i++)
        {
            // abscisse
            for (int j = 0; j < p.size(); j++)
            {
                int pos_x = (26 + 200 * j);
                int pos_y = (26 + 200 * i);

                int pos_x_text = pos_x + 20;
                int pos_y_text = pos_y + 10;

                RectangleShape tuile(Vector2f(198.f, 198.f));
                tuile.setPosition(pos_x, pos_y); 

                Text nombre;
                nombre.setFont(police);
                nombre.setCharacterSize(70);
                nombre.setPosition(pos_x_text, pos_y_text);

                Text textScore;
                string stringScore = "Score : " + to_string(score);
                textScore.setFont(police);
                textScore.setCharacterSize(20);
                textScore.setFillColor(Color::White);
                textScore.setPosition(25, 0);
                textScore.setString(stringScore);

                pair<Color, Color> couleurs = choisirCouleur(p[i][j]);
                tuile.setFillColor(couleurs.first);
                nombre.setFillColor(couleurs.second);
                nombre.setString(to_string(p[i][j]));
                w.draw(tuile);
                w.draw(nombre);
                w.draw(textScore);
                
            }
        }
    }
    if (estGagnant)
    {
        RectangleShape fondGagnant(Vector2f(850.f, 850.f));
        fondGagnant.setFillColor(Color(237, 224, 200, 255));
        Text texteGagnant;
        fondGagnant.setPosition(0, 0);
        texteGagnant.setFont(police);
        texteGagnant.setCharacterSize(35);
        texteGagnant.setFillColor(Color::Yellow);
        texteGagnant.setPosition(50, 400);
        texteGagnant.setString("Vous avez gagne!!!\nAppuyez sur 'R' pour recommencer");
        w.draw(fondGagnant);
        w.draw(texteGagnant);
        
    }
    if (estTermine)
    {
        // Création d'un rectangle pour le fond de l'état de perte
        RectangleShape fondPerdant(Vector2f(850.f, 850.f));
        fondPerdant.setPosition(0, 0); // Position du fond
        fondPerdant.setFillColor(Color(237, 224, 200, 255));
        // Création du texte pour indiquer la perte
        Text textePerdant;
        textePerdant.setFont(police);                 // Définir la police
        textePerdant.setCharacterSize(35);            // Taille du texte
        textePerdant.setFillColor(Color::Red);        // Couleur du texte (rouge pour indiquer une perte)
        textePerdant.setPosition(50, 400);           // Position du texte
        textePerdant.setString("Vous avez perdu!!!\nAppuyez sur 'R' pour recommencer"); // Message de perte

        // Dessiner le fond et le texte dans la fenêtre
        w.draw(fondPerdant);
        w.draw(textePerdant);
        
    }
    w.display();
    
}

void debutDessine(RenderWindow &w)
{
    Font police; // initialiser la police
    if (!police.loadFromFile("/home/quentin/Projet2048WSL/Projet2048QN-1/jeu2048/ressources/LEMONMILK-Regular.otf"))
    {
        cerr << "SFML font error" << endl;
    }
    // Création d'un rectangle pour le fond du message de début
    RectangleShape fondDebut(Vector2f(850.f, 850.f));
    fondDebut.setPosition(0,0); // Position du fond
    fondDebut.setFillColor(Color(237, 224, 200, 255));

    // Création du texte pour indiquer comment commencer
    Text texteDebut;
    texteDebut.setFont(police);                                  // Définir la police
    texteDebut.setCharacterSize(35);                             // Taille du texte
    texteDebut.setFillColor(Color::Black);                       // Couleur du texte (noir)
    texteDebut.setPosition(50, 400);                            // Position du texte
    texteDebut.setString("Bienvenue au jeu 2048!\nUtilisez les fleches pour jouer\nAppuyez sur 'Q' pour quitter"); // Message de début

    // Dessiner le fond et le texte dans la fenêtre
    w.draw(fondDebut);
    w.draw(texteDebut);
    w.display();
}

pair<Color, Color> choisirCouleur(int valeur)
{
    pair<Color, Color> resultat;
    if (valeur == 0)
    {
        resultat.first = Color(50, 50, 50, 255);
        resultat.second = Color(50, 50, 50, 255);   // Couleurs identiques pour ne pas afficher le 0
    }
    else if (valeur == 2)
    {
        resultat.first = Color(242, 238, 220, 255); // Beige clair
        resultat.second = Color::Black;
    }
    else if (valeur == 4)
    {
        resultat.first = Color(237, 224, 200, 255); // Beige
        resultat.second = Color::Black;
    }
    else if (valeur == 8)
    {
        resultat.first = Color(242, 177, 121, 255); // Orange clair
        resultat.second = Color::Black;
    }
    else if (valeur == 16)
    {
        resultat.first = Color(245, 149, 99, 255); // Orange
        resultat.second = Color::Black;
    }
    else if (valeur == 32)
    {
        resultat.first = Color(246, 124, 95, 255); // Orange foncé
        resultat.second = Color::Black;
    }
    else if (valeur == 64)
    {
        resultat.first = Color(246, 94, 59, 255); // Rouge-orange
        resultat.second = Color::Black;
    }
    else if (valeur == 128)
    {
        resultat.first = Color(237, 207, 114, 255); // Jaune doré
        resultat.second = Color::Black;
    }
    else if (valeur == 256)
    {
        resultat.first = Color(237, 204, 97, 255); // Or
        resultat.second = Color::Black;
    }
    else if (valeur == 512)
    {
        resultat.first = Color(237, 200, 80, 255); // Or profond
        resultat.second = Color::Black;
    }
    else if (valeur == 1024)
    {
        resultat.first = Color(237, 197, 63, 255); // Ambre
        resultat.second = Color::Black;
    }
    else if (valeur == 2048)
    {
        resultat.first = Color(237, 194, 46, 255); // Ambre brillant
        resultat.second = Color::Black;
    }
    else if (valeur > 2048)
    {
        resultat.first = Color::Black;  // Les tuiles au-dessus de 2048 sont noires
        resultat.second = Color::White; // Changer la couleur du texte pour la visibilité
    }
    return resultat;
}

// Pourquoi return score + casesVides * 100 ?

// Chaque case vide ajoute 100 points à la note (la valeur du point est arbitraire).
// Cela rend les plateaux avec plus de cases vides plus attirants pour l'IA, car avoir de l'espace rend le jeu plus sûr et permet de continuer plus longtemps.
// Exemple :
//  Imaginons deux plateaux avec le même score total, mais un nombre différent de cases vides :

// Plateau A :

// Score : 500
// Cases vides : 2
// Note : 500 + 2 * 100 = 700
// Plateau B :

// Score : 500
// Cases vides : 4
// Note : 500 + 4 * 100 = 900
// L'IA préfère le plateau B parce qu'il a plus de cases vides, même si les deux ont le même score.

// int choisirMeilleurMouvement(const Plateau &plateau)
// {
//     int meilleurscore = 0;
//     int meilleurdirection = 0;
//     int score;
//     for (int direction = 0; direction <= 3; direction++)
//     {
//         Plateau nouveauPlateau = deplacement(plateau, direction);
//         if (nouveauPlateau != plateau)
//         {
//             score = evaluerPlateau(nouveauPlateau);
//             if (score > meilleurscore)
//             {
//                 meilleurscore = score;
//                 meilleurdirection = direction;
//             }
//         }
//     }
//     return meilleurdirection;
// }

// MINIMAX
// double minimax(Plateau plateau, int profondeur, bool isMaximizingPlayer, double alpha, double beta)
// {
//     if (profondeur == 0 || estTermine(plateau))
//     {
//         return heuristiqueSerpent(plateau); // Evaluate plateau at the leaf node
//     }

//     if (isMaximizingPlayer)
//     {
//         double maxEval = -INFINITY;
//         // Explore all valid moves (up, down, left, right)
//         for (auto mouvement : obtenirMouvementsValides(plateau))
//         {
//             Plateau nouveauPlateau = deplacement(plateau, mouvement); // Apply move
//             // Simulate new tile placements in all empty spaces
//             for (auto positionNouvelleTuile : obtenirPositionsNouvellesTuilesPossibles(nouveauPlateau))
//             {
//                 Plateau plateauSimule = simulerNouvelleTuile(nouveauPlateau, positionNouvelleTuile, 2);
//                 double eval = minimax(plateauSimule, profondeur - 1, false, alpha, beta); // Simulate tile spawn and minimize next
//                 maxEval = max(maxEval, eval);
//                 alpha = max(alpha, eval);
//                 if (beta <= alpha)
//                     break; // Prune
//             }
//         }
//         return maxEval;
//     }
//     else
//     {
//         // No "minimizing" player in this case, just simulate tile placements
//         double minEval = INFINITY;
//         // For each empty spot, simulate placing a tile (either 2 or 4)
//         for (auto positionNouvelleTuile : obtenirPositionsNouvellesTuilesPossibles(plateau))
//         {
//             Plateau plateauSimule = simulerNouvelleTuile(plateau, positionNouvelleTuile, 2);
//             double eval = minimax(plateauSimule, profondeur - 1, true, alpha, beta); // Maximize next
//             minEval = min(minEval, eval);
//             beta = min(beta, eval);
//             if (beta <= alpha)
//                 break; // Prune
//         }
//         return minEval;
//     }
// }

// int evaluerPlateau(const Plateau &plateau)
// {
//     int score = scoreboard(plateau);
//     int casesVides = 0;
//     int maximum = 0;
//     int imax = 0;
//     int jmax = 0;
//     int maxDansUnCoin = 0;
//     int maxAuBord = 0;
//     int diversite = 0;
//     int nbCouples = 0;
//     int densite = 0;
//     int jouable = 0;
//     vector<int> nombresPresents = {};
//     for (int i = 0; i < plateau.size(); i++)
//     {
//         for (int j = 0; j < plateau[i].size(); j++)
//         {
//             if (plateau[i][j] == 0)
//             {
//                 casesVides++;
//             }
//             // position du plus grand nombre
//             if (plateau[i][j] > maximum)
//             {
//                 maximum = plateau[i][j];
//                 imax = i;
//                 jmax = j;
//             }
//             // calcul de la diversite
//             for (int i = 0; i < nombresPresents.size(); i++)
//             {
//                 if (plateau[i][j] != nombresPresents[i])
//                 {
//                     nombresPresents.push_back(plateau[i][j]);
//                 }
//             }
//             if (i > 0 && i < plateau.size() - 1){
//                 if (plateau[i-1][j] == plateau[i][j] || plateau[i+1][j] == plateau[i][j]){
//                     nbCouples++;
//                 }
//             }
//             if (j > 0 && j < plateau.size() - 1){
//                 if (plateau[i][j+1] == plateau[i][j] || plateau[i][j-1] == plateau[i][j]){
//                     nbCouples++;
//                 }
//             }
//         }
//     }

//     for (int indicePlateauxOptimaux = 0; indicePlateauxOptimaux < plateauxOptimaux.size(); indicePlateauxOptimaux++)
//     {
//         int ressemblanceAUnPlateauOptimal = 0;
//         for (int i = 0; i < plateau.size(); i++)
//         {
//             for (int j = 0; j < plateau[i].size(); j++)
//             {

//                 // etudie la similarite avec les plateaux optimaux
//                 double valeurNormalisee = (double)plateau[i][j] / maximum;
//                 double valeurNormaliseeOptimale = (double)plateauxOptimaux[indicePlateauxOptimaux][i][j] / 32768;
//                 if (abs(valeurNormalisee - valeurNormaliseeOptimale) < 0.05)
//                 {
//                     ressemblanceAUnPlateauOptimal++;
//                     // cout << ressemblanceAUnPlateauOptimal << endl;
//                 }
//             }
//         }
//         maxRessemblancePlateau = max(maxRessemblancePlateau, ressemblanceAUnPlateauOptimal);
//     }
//     // cout << maxRessemblancePlateau << endl;
//     if ((imax == 0 || imax == 3) && (jmax == 0 || jmax == 3))
//     {
//         maxDansUnCoin = 1;
//     }
//     if (imax == 0 || imax == 3 || jmax == 0 || jmax == 3)
//     {
//         maxAuBord = 1;
//     }
//     // la valeur moyenne d'une case
//     densite = score/(16-casesVides);
//     // le nombre d'elements differents du plateau
//     diversite = nombresPresents.size();

//     // 1 si le plateau est jouable, 0 sinon (1 si tous les plateaux suivants, et tous les plateaux suivant ces dernieres sont jouables, 0 sinon)
//     //if (estTermine(deplacement(deplacement(plateau,0),0)) || estTermine(deplacement(deplacement(plateau,1),1)) || estTermine(deplacement(deplacement(plateau,2),2)) || estTermine(deplacement(deplacement(plateau,3),3))){
//     if (estTermine(plateau)){
//         jouable = 0;
//     } else {
//         jouable = 1;
//     }

//     // cout << (score + casesVides * 150 + maxDansUnCoin * 100 + maxAuBord * 100 + densite * 100 + diversite * (-1) + nbCouples * 100) * jouable << endl;
//     return score + casesVides * 150 + maxDansUnCoin * 1000 + maxAuBord * 100 + densite * 100 + diversite * (-1) + nbCouples * 500 + maximum * 100 + maxRessemblancePlateau * 100;
// }

// Machine learning stuff, kinda mid

// int evaluerPlateauPoidsVariables(const Plateau &plateau, float poidsScore, float poidsCasesVides, float poidsMaxDansUnCoin, float poidsDiversite)
// {
//     int score = scoreboard(plateau);
//     int casesVides = 0;
//     int maximum = 0;
//     int imax = 0;
//     int jmax = 0;
//     int maxDansUnCoin = 0;
//     int maxAuBord = 0;
//     int diversite = 0;
//     vector<int> nombresPresents = {};
//     for (int i = 0; i < plateau.size(); i++)
//     {
//         for (int j = 0; j < plateau[i].size(); j++)
//         {
//             if (plateau[i][j] == 0)
//             {
//                 casesVides++;
//             }
//             // position du plus grand nombre
//             if (plateau[i][j] > maximum)
//             {
//                 maximum = plateau[i][j];
//                 imax = i;
//                 jmax = j;
//             }
//             // calcul de la diversite
//             for (int i = 0; i < nombresPresents.size(); i++)
//             {
//                 if (plateau[i][j] != nombresPresents[i])
//                 {
//                     nombresPresents.push_back(plateau[i][j]);
//                 }
//             }
//         }
//     }
//     if ((imax == 0 || imax == 3) && (jmax == 0 || jmax == 3))
//     {
//         maxDansUnCoin = 1;
//     }
//     if (imax == 0 || imax == 3 || jmax == 0 || jmax == 3)
//     {
//         maxAuBord = 1;
//     }

//     diversite = nombresPresents.size();

//     return score * poidsScore + casesVides * poidsCasesVides + maxDansUnCoin * poidsMaxDansUnCoin + diversite * poidsDiversite;
// }

// int choisirMeilleurMouvementPoidsVariables(const Plateau &plateau, float poidsScore, float poidsCasesVides, float poidsMaxDansUnCoin, float poidsDiversite)
// {
//     int meilleurscore = 0;
//     int meilleurdirection = 0;
//     int score;
//     for (int direction = 0; direction <= 3; direction++)
//     {
//         Plateau nouveauPlateau = deplacement(plateau, direction);
//         if (nouveauPlateau != plateau)
//         {
//             score = evaluerPlateauPoidsVariables(nouveauPlateau, poidsScore, poidsCasesVides, poidsMaxDansUnCoin, poidsDiversite);
//             if (score > meilleurscore)
//             {
//                 meilleurscore = score;
//                 meilleurdirection = direction;
//             }
//         }
//     }
//     return meilleurdirection;
// }

// C'est juste une tentative de predire plusieurs plateaux en avance
// On pourrait predire tous les cas jusqu'a la fin, mais c pas une IA et ca pourrait prendre dix mille ans

// int choisirMeilleurJeu(Plateau plateau){
//     for (int i = 0; i<5; i++){
//         plateau = deplacement(plateau, choisirMeilleurMouvement(plateau));
//     }
// }

// float moyenneTableau(vector<float> t)
// {
//     int somme = 0;
//     for (int i = 0; i < t.size(); i++)
//     {
//         somme += t[i];
//     }
//     return somme / t.size();
// }

// float ecartTypeTableau(vector<float> t)
// {
//     int somme = 0;
//     for (int i = 0; i < t.size(); i++)
//     {
//         somme += pow((t[i] - moyenneTableau(t)), 2);
//     }
//     return somme / t.size();
// }
