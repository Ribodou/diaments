#ifndef __SCORE_H__
#define __SCORE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

class Score {
	protected:
		SDL_Renderer *pRenderer;
		SDL_Point point_haut_gauche;
		int largeur_pixel;
		int hauteur_pixel;
		int score;
	public:
		Score(SDL_Renderer *_pRenderer,
			  SDL_Point _point_haut_gauche,
			  int _largeur_pixel,
			  int _hauteur_pixel,
			  int _score);
		~Score();
		void dessiner(int taille_pixel_bords);
		void add(int x);
};


#endif

