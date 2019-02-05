#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
//#include <cwiid.h>  // apt-get install libcwiid-dev  //Copyright (C) 2007 L. Donnie Smith <cwiid@abstrakraft.org>
#include "GridGame.hpp"
#include "GridPreview.hpp"
#include "Piece.hpp"
#include "Score.hpp"
#include "usefull_functions.hpp"

// error : Couldn't open ./ressources/sprites/bleu2.bmp
/*
On a deux grilles: GrigGame et GridPreview (toutes deux heritant de Grid)
GridGame est la grille dans laquelle se mettent les diamants tombés
GridPreview est la grille dans laquelle la pièce est placée avant de pouvoir la jouer

On place une piece, composée de plusieurs Diamants, dans GridPreview.
Pour l'envoyer dans GridGame, on transforme le pièce en plein de Diamant.
Chaque Diamant tombe dans la grille indépandamment les uns les autres
(ie: pas comme Tetris)
*/
// TODO : gérer a rotation (on peut se décaler - ne pas tourner autour du centre de gravité de la piece)
// TODO: gérer la wiimote
// TODO: gérer le fait de faire tomber les pieces par petit bout
void initSDL(int largeur_fenetre, int hauteur_fenetre, SDL_Window *&pWindow, SDL_Renderer *&pRenderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    pWindow = SDL_CreateWindow("Ma première application SDL2",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            largeur_fenetre,
                            hauteur_fenetre,
                            SDL_WINDOW_SHOWN
                            );
    verify<SDL_Window>(pWindow);

    pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    verify<SDL_Renderer>(pRenderer);
}


void afficher(SDL_Renderer *&pRenderer,
              int time_to_wait,
              GridGame &grid_game,
              GridPreview &grid_preview,
              Score score) {
    SDL_Delay(time_to_wait);
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    grid_game.draw(2);
    grid_preview.draw(2);
    score.draw(2);
    SDL_RenderPresent(pRenderer);  // Affichage
}

#ifdef CWIID_H
void initWii(cwiid_wiimote_t *wiimote) {
    bdaddr_t bdaddr = (bdaddr_t) {{0, 0, 0, 0, 0, 0}};	/* bluetooth device address */
	std::cout << ("Put Wiimote in discoverable mode now (press 1+2)...\n");
	if (!(wiimote = cwiid_open(&bdaddr, 0))) {
		fprintf(stderr, "Unable to connect to wiimote\n");
		return -1;
	}
}
#endif


int main(/*int argc, char *argv[]*/)
{
    int hauteur_fenetre = 480;
    int largeur_fenetre = 700;
    int nombre_lignes = 8;
    int nombre_colonnes = 15;
    SDL_Window *pWindow = NULL;
    SDL_Renderer *pRenderer = NULL;
    SDL_Event e;
    bool jeu_en_cours = true;

#ifdef CWIID_H
    cwiid_wiimote_t *wiimote = NULL;
    initWii(wiimote);
#endif

    initSDL(largeur_fenetre, hauteur_fenetre, pWindow, pRenderer);
    TTF_Init();

    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
    SDL_RenderClear(pRenderer);
    
    SDL_Point point_haut_gauche_preview({
        3 * largeur_fenetre / 7 - (nombre_colonnes * 25) / 2,
        hauteur_fenetre / 4 - (nombre_lignes * 25) / 2 + hauteur_fenetre / 8
    });
    GridPreview grid_preview(pRenderer, nombre_colonnes, 4, 25, 25, point_haut_gauche_preview);
    
    SDL_Point point_haut_gauche({
        3 * largeur_fenetre / 7 - (nombre_colonnes * 25) / 2,
        hauteur_fenetre / 2 - (nombre_lignes * 25) / 2 + hauteur_fenetre / 8
    });
    GridGame grid_game(pRenderer, nombre_colonnes, nombre_lignes, 25, 25, point_haut_gauche);

    SDL_Point point_haut_gauche_score({
        largeur_fenetre / 2 + (nombre_colonnes * 25) / 2,
        point_haut_gauche_preview.y
    });
    Score score(pRenderer, point_haut_gauche_score, 80, 30, 0);

    afficher(pRenderer, 0, grid_game, grid_preview, score);
    while (jeu_en_cours) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            //SDL_Log("Program quit after %i ticks", e.quit.timestamp);
            break;
        }
        if (e.type == SDL_KEYDOWN) {
            grid_game.effacerOmbre();
            switch( e.key.keysym.sym ) {
                case SDLK_LEFT:
                    grid_preview.deplacerPiece(-1, 0);
                    break;
                case  SDLK_RIGHT:
                    grid_preview.deplacerPiece(1, 0);
                    break;
                case SDLK_SPACE:
                    grid_preview.retourner_piece();
                    break;
                case SDLK_RETURN:
                    jeu_en_cours = grid_preview.projeter_piece(grid_game);
                    break;
            }
            afficher(pRenderer, 0, grid_game, grid_preview, score);

            while(grid_game.detruireAlignements(score)) {
                afficher(pRenderer, 100, grid_game, grid_preview, score);
                SDL_Delay(100);
                while(grid_game.faire_tomber()){
                    afficher(pRenderer, 100, grid_game, grid_preview, score);
                }
                afficher(pRenderer, 0, grid_game, grid_preview, score);
            }
            grid_preview.projeter_ombre(grid_game);
            afficher(pRenderer, 0, grid_game, grid_preview, score);
            SDL_Delay(70);
        }
    }

#ifdef CWIID_H
	if (cwiid_close(wiimote)) {
		fprintf(stderr, "Error on wiimote disconnect\n");
		return -1;
	}
#endif

    TTF_Quit();
    SDL_DestroyRenderer(pRenderer);  // Libération de la mémoire du SDL_Renderer
    SDL_DestroyWindow(pWindow);  // Close and destroy the window
    SDL_Quit();  // Quit the SDL2
    //std::cout << "exiting" << std::endl;
    return EXIT_SUCCESS;  // Yay!
}
