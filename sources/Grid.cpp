#include "Grid.hpp"
#include <SDL2/SDL.h>

Grid::Grid(SDL_Renderer *_pRenderer,
               int _largeur,
               int _hauteur,
               int _largeur_pixel,
               int _hauteur_pixel,
               SDL_Point _point_haut_gauche)
               :
               pRenderer(_pRenderer),
               largeur(_largeur),
               hauteur(_hauteur),
               largeur_pixel(_largeur_pixel),
               hauteur_pixel(_hauteur_pixel),
               point_haut_gauche(_point_haut_gauche) {
    for (int i = 0; i < this->hauteur; i++) {
        std::vector<Diamond*> temp;
        for (int j = 0; j < this->largeur; j++) {
            temp.push_back(NULL);
        }
        this->tab.push_back(temp);
    }
}


Grid::~Grid() {
    for (int i = 0; i < this->hauteur; i++) {
        for (int j = 0; j < this->largeur; j++) {
            if (this->tab[i][j] != NULL) {
                delete this->tab[i][j];
            }
        }
    }
}


void Grid::dessiner(int taille_pixel_bords) {
    int x, y, color, indice;
    x = y = color = indice = 0;
    int xdeb, xfin, ydeb, yfin;
    /* dessin des contours de la grille */
    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    for(int i = 0; i <= hauteur; i++) {
        y = this->point_haut_gauche.y + (this->hauteur_pixel + taille_pixel_bords) * i - taille_pixel_bords;
        xdeb = this->point_haut_gauche.x - taille_pixel_bords;
        xfin = xdeb + (this->largeur_pixel + taille_pixel_bords) * largeur;
        for(int j = 0; j < taille_pixel_bords; j++) {
            SDL_RenderDrawLine(pRenderer, xdeb, y+j, xfin, y+j);
        }
    }
    for(int j = 0; j <= largeur; j++) {
        x = this->point_haut_gauche.x + (this->largeur_pixel + taille_pixel_bords) * j - taille_pixel_bords;
        ydeb = this->point_haut_gauche.y - taille_pixel_bords;
        yfin = ydeb + (this->hauteur_pixel + taille_pixel_bords) * hauteur;
        for(int i = 0; i < taille_pixel_bords; i++) {
            SDL_RenderDrawLine(pRenderer, x + i, ydeb, x + i, yfin);
        }
    }
    /* remplissage de la grille */
    for(int i = 0; i < hauteur; i++) {
        y = this->point_haut_gauche.y + (this->hauteur_pixel + taille_pixel_bords) * i;
        for(int j = 0; j < largeur; j++) {
            x = this->point_haut_gauche.x + (this->largeur_pixel + taille_pixel_bords) * j;
            if (this->tab[i][j] != NULL) {
                this->tab[i][j]->draw(x, y);
            }
        }
    }
}