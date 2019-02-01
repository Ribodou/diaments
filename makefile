CPP=g++ # Commande du compilateur
CFLAGS=-Wall -Wextra -g -std=c++17 # Option d'optimisation du programme -O3
LDFLAGS=-lSDL2 -lSDL2_ttf
LDFLAGSPLUS=-lcwiid -lbluetooth -lSDL2_mixer

EXEC=bin/main # Nom du programme
OBJECTS = tmp/main.o tmp/Diamond.o tmp/Grid.o tmp/GridGame.o tmp/GridPreview.o tmp/Piece.o tmp/Score.o # Objets nécessaires à la compilation

all: ${EXEC}

$(EXEC): $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

tmp/%.o: sources/%.cpp # sources/%.hpp
	$(CPP) -c $(CFLAGS) $< -o $@

clean:	
	rm -fr tmp/*.o

mrproper: clean
	rm -fr ${EXEC}
