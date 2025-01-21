#ifndef MODELE_HPP
#define MODELE_HPP

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

using Plateau = vector<vector<int>>;

// Modèle du jeu

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 *  @note Implémenté par Quentin le 19/11
 **/
int tireDeuxOuQuatre();

/** génère un plateau de dimensions 4*4 ne contenant que des 0
 *  @return un plateau vide
 *  @note Implémenté par Nghia le 20/11
 **/
Plateau plateauVide();

/** génère deux nombres sur des cases aléatoires d'un plateau vide
 *  @return un plateau en début de jeu
 *  @note Implémenté par Nghia le 20/11
 **/
Plateau plateauInitial();

/** déplace les tuiles d'un plateau vers la gauche et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la gauche
 *  @note Implémenté par Quentin le 20/11.
 *  @note Cette fonction a nécessité de prévoir et schématiser
 * tous les cas en avance, mais fournit une base pour les trois fonctions suivantes.
 * Après de nombreux tests affichant graphiquement l'effet de la fonction sur un
 * Plateau, la fonction semble fonctionner correctement.
 **/
Plateau deplacementGauche(Plateau plateau);

/** déplace les tuiles d'un plateau vers la droite et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers la droite
 *  @note Implémenté par Nghia le 20/11
 *  @note (inspiré par le modèle déjà crée par Quentin). Cette fonction a nécessité de prévoir et schématiser
 * tous les cas en avance, mais fournit une base pour les trois fonctions suivantes.
 * Après de nombreux tests affichant graphiquement l'effet de la fonction sur un
 * Plateau, la fonction semble fonctionner correctement.
 **/
Plateau deplacementDroite(Plateau plateau);

/** déplace les tuiles d'un plateau vers le haut et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers le haut
 *  @note Implémenté par Quentin le 22/11
 **/
Plateau deplacementHaut(Plateau plateau);

/** déplace les tuiles d'un plateau vers le haut et les combine si possible
 *  @param plateau le plateau
 *  @return le plateau une fois déplacé vers le haut
 *  @note Implémenté par Nghia le 25/11
 **/
Plateau deplacementBas(Plateau plateau);

/** déplace les tuiles d'un plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le plateau
 *  @param direction la direction
 *  @return le plateau déplacé dans la direction
 *  @note Implémenté par Quentin le 25/11
 **/
Plateau deplacement(Plateau plateau, int direction);

/** affiche un plateau avec le module ncurses
 * @param p le plateau
 * @note Implémenté par Nghia le 7/12
 **/
// string dessine(Plateau p);
void dessine(Plateau p);

/** permet de savoir si une partie est terminée
 *  @param plateau un plateau
 *  @return true si plus aucun mouvement est possible, false sinon
 *  @note Implémenté par Quentin le 25/11
 **/
bool estTermine(Plateau plateau);

/** permet de savoir si une partie est gagnée
 * @param plateau un plateau
 * @return true si le plateau contient un 2048, false sinon
 * @note Implémenté par Quentin le 25/11
 **/
bool estGagnant(Plateau plateau);

// Fonctions supplémentaires



/** calculer le score actuel de la partie jouée
 * @param plateau un plateau
 * @return le score actuel du jeu
 * @note Implémenté par Nghia le 25/11
 **/
int scoreboard(Plateau plateau);



// Fonctions servant à la version jeu12

/** affiche un plateau
 * @param p le plateau
 * @note Implémenté par Quentin le 25/11
 **/
// string dessine(Plateau p);
string consoleDessine(Plateau p);

/** convertit la touche entrée en entier pour la fonction deplacement selon les touches de jeu choisis
 * @param touche une chaine de caracteres
 * @return direction d'un entier
 * @note Implémenté par Quentin le 25/11. Fonction basée sur la fonction cin, inutile pour les version du jeu
 * ou les touches sont directement enregistrées par le jeu
 **/
int toucheConversion(string touche);



// Fonctions IA

/**
 * Applique l'algorithme Expectiminimax pour évaluer un plateau.
 * @param plateau Le plateau actuel de jeu.
 * @param profondeur La profondeur maximale de recherche dans l'arbre des états du jeu.
 * @param mouvement Le mouvement associé à cette itération.
 * @return Une estimation heuristique de la valeur du plateau.
 * @note Implémenté par Quentin le 07/12
 */
double expectiminimax(Plateau plateau, int profondeur, int mouvement);

/**
 * Choisit le meilleur déplacement possible à l'aide de l'algorithme Expectiminimax.
 * @param plateau Le plateau actuel de jeu.
 * @param profondeur La profondeur maximale de recherche dans l'arbre des états du jeu.
 * @return L'entier correspondant au mouvement optimal (0 : haut, 1 : droite, 2 : bas, 3 : gauche).
 * @note Implémenté par Quentin le 07/12
 */
int choisirMeilleurDeplacementExpectiminimax(Plateau plateau, int profondeur);

// Aides à l'IA

/**
 * Obtient tous les mouvements valides pour le plateau donné.
 * @param plateau Le plateau actuel de jeu.
 * @return Un vecteur contenant les mouvements possibles sous forme d'entiers (0 : haut, 1 : droite, 2 : bas, 3 : gauche).
 * @note Implémenté par Quentin le 07/12
 */
std::vector<int> obtenirMouvementsValides(Plateau plateau);

/**
 * Trouve toutes les positions vides où une nouvelle tuile peut être placée.
 * @param plateau Le plateau actuel de jeu.
 * @return Un vecteur contenant les paires d'indices (ligne, colonne) des positions vides.
 * @note Implémenté par Quentin le 07/12
 */
std::vector<std::pair<int, int>> obtenirPositionsNouvellesTuilesPossibles(Plateau plateau);

/**
 * Simule l'ajout d'une nouvelle tuile sur un plateau donné.
 * @param plateau Le plateau actuel de jeu.
 * @param position La position (ligne, colonne) où placer la nouvelle tuile.
 * @param valeur La valeur de la tuile (par exemple : 2 ou 4).
 * @return Une copie du plateau avec la nouvelle tuile ajoutée.
 * @note Implémenté par Quentin le 07/12
 */
Plateau simulerNouvelleTuile(Plateau plateau, std::pair<int, int> position, int valeur);

// Interface graphique SFML

/**
 * Dessine le plateau de jeu à l'aide de SFML.
 * @param p Le plateau actuel de jeu.
 * @param w La fenêtre SFML dans laquelle dessiner le plateau.
 * @note Implémenté par Quentin le 07/12
 */
void SFMLdessine(Plateau p, sf::RenderWindow &w, int score, bool estGagnant, bool estTermine);

/**
 * Choisit une paire de couleurs en fonction de la valeur d'une tuile.
 * @param valeur Un entier représentant la valeur de la tuile.
 * @return Une paire de couleurs associée à la valeur donnée.
 * @note Les couleurs sont définies pour les valeurs de 0 à 2048, 
 *       avec une couleur noire pour les valeurs supérieures à 2048.
 * @note Implémenté par Quentin le 09/12
 */
pair<Color, Color> choisirCouleur(int valeur);

void debutDessine(RenderWindow &w);



// Fonctions non utilisées

// int evaluerPlateau(const Plateau& plateau);

// int choisirMeilleurMouvement(const Plateau& plateau);

// int evaluerPlateauPoidsVariables(const Plateau &plateau, float poidsScore, float poidsCasesVides, float poidsMaxDansUnCoin, float poidsDiversite);

// int choisirMeilleurMouvementPoidsVariables(const Plateau& plateau, float poidsScore, float poidsCasesVides, float poidsMaxDansUnCoin, float poidsDiversite);

// double minimax(Plateau plateau, int profondeur, bool isMaximizingPlayer, double alpha, double beta);

// float moyenneTableau (vector<float> t);

// float ecartTypeTableau (vector<float> t);

#endif