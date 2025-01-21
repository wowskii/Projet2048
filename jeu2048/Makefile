
#jeu complet
jeu: modele.o jeuSFML.o
	g++ modele.o jeuSFML.o -o jeu -lsfml-graphics -lsfml-window -lsfml-system -lcurses

jeuSFML.o: fichiers-jeu-complet/jeuSFML.cpp
	g++ -c fichiers-jeu-complet/jeuSFML.cpp


#IA
IA: modele.o IA.o
	g++ modele.o IA.o -o IA -lsfml-graphics -lsfml-window -lsfml-system -lcurses

IA.o: fichiers-IA/IA.cpp
	g++ -c fichiers-IA/IA.cpp


#jeu16
jeu16: modele.o jeu16.o
	g++ modele.o jeu16.o -o jeu16 -lsfml-graphics -lsfml-window -lsfml-system -lcurses

jeu16.o: bareme16/jeu16.cpp
	g++ -c bareme16/jeu16.cpp


#jeu12
jeu12: modele.o jeu12.o
	g++ modele.o jeu12.o -o jeu12 -lsfml-graphics -lsfml-window -lsfml-system -lcurses

jeu12.o: bareme12/jeu12.cpp
	g++ -c bareme12/jeu12.cpp


#test
test: modele.o test.o
	g++ modele-test.o modele.o -o test -lsfml-graphics -lsfml-window -lsfml-system -lcurses

test.o: modele-test.cpp
	g++ -c modele-test.cpp

#modele
modele.o: modele.cpp
	g++ -c modele.cpp


#nettoyage
clean:
	rm -f *.o fichiers-jeu-complet/*.o jeu IA jeu12 jeu16 test