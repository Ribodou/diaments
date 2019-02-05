#ifndef __GRILLE_H__
#define __GRILLE_H__

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "Diamond.hpp"
#include "usefull_functions.hpp"

class Grid {
	protected:
		SDL_Renderer *pRenderer;
		int width;
		int height;
		int width_pixel;
		int height_pixel;
		SDL_Point point_haut_gauche;
		
		std::vector<std::vector<Diamond*> > tab;
	public:
		Grid(SDL_Renderer *pRenderer,
            int width,
            int height,
            int width_pixel,
            int height_pixel,
            SDL_Point point_haut_gauche);
		~Grid();
		virtual void draw(int taille_pixel_bords);
		
};


#endif