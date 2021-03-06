#ifndef __PIECE_H__
#define __PIECE_H__

#include <vector>
#include <string>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>

#include "Diamond.hpp"


class Piece {
	protected:
		std::vector<std::string> shapes;
		SDL_Renderer *pRenderer;
		std::string forme;
		int largeur;
		int hauteur;
		std::vector<std::vector<Diamond*> > tab;
	public:
		Piece(SDL_Renderer *_pRenderer, std::string _forme);
		static Piece * createAleatPiece(SDL_Renderer *_pRenderer);
		static void destroyPiece(Piece *&piece);
		~Piece();
		int getHauteur();
		int getLargeur();
		void draw(SDL_Point point_haut_gauche_piece,
                     int largeur_pixel,
                     int hauteur_pixel,
                     int taille_pixel_bords);
		void retourner();
		std::vector<Diamond*> getLigneOmbre(int ligne);
		std::vector<Diamond*> getLigne(int ligne);
};


#endif

