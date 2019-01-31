#ifndef __GRILLEPREVIEW_H__
#define __GRILLEPREVIEW_H__

#include "Grid.hpp"
#include "GridGame.hpp"
#include "Piece.hpp"

class GridPreview : public Grid {
	protected:
            Piece *piece;
            // Attention: les coordonnées de la piece sont les coordonnées
            // du Diamant le plus en haut à gauche
            // ce sont des entiers qui representent la CASE sur laquelle est
            // situé ce diament. 
            SDL_Point coordonnees_piece;
	public:
		GridPreview(SDL_Renderer *pRenderer,
                  int largeur,
                  int hauteur,
                  int largeur_pixel,
                  int hauteur_pixel,
                  SDL_Point point_haut_gauche);
		~GridPreview();
            void dessiner(int taille_pixel_bords);
            bool deplacerPiece(int delatCaseX, int delatCaseY);
            void retourner_piece();
            void projeter_ombre(GridGame &grid_game);
            bool projeter_piece(GridGame &grid_game);
};


#endif

