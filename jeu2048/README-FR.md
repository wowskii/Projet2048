# Projet 2048

## Organisation des fichiers
!!!Tout se passe dans le dossier jeu2048!!!

Le dossier jeu2048 comprend 5 dossiers :

- bareme12: 
    Ancienne version du jeu jouable à travers la console, interface graphique minimale.
- bareme16: 
    Ancienne version du jeu plus dynamique qui utilise la bibliothèque ncurses.
- fichiers-IA:
    Le code permettant de lancer l'IA qui tentera de gagner le jeu.
- fichiers-jeu-complet:
    Version finale du jeu, avec une meilleure interface graphique qui utilise SFML (autrement dit, le barème des 20 points).
- ressources:
    Contient un fichier de police utile pour SFML.

Idéalement, ce sont les deux derniers fichiers seront les plus utiles.

modele.cpp et modele.hpp se trouvent également dans le dossier jeu2048, et sont accessibles par tous les autres fichier .cpp.

## Comment jouer
Une fois dans le dossier jeu2048, executez `jeu` pour jouer, ou `IA` pour regarder l'IA jouer.

Si besoin, voici quelques commandes Makefile, à executer dans le terminal, qui s'appliquent a notre projet:

```Makefile
make clean    #nettoie le dossier en supprimant tous fichiers de compilation et fichiers executables

make jeu     #compile la version finale du jeu dans le dossier jeu2048, sous le nom "jeu"

make IA      #compile le fichier de lancement de l'IA dans le dossier jeu2048 sous le nom "IA"

make jeu16   #compile la version "barème des 16 points" du jeu dans le dossier jeu2048, sous le nom "jeu16"

make jeu12   #compile la version "barème des 12 points" du jeu dans le dossier jeu2048, sous le nom "jeu12"

make test    #compile le fichier modele-test.cpp dans le dossier jeu2048, sous le nom "test"
```

