#include "Grid.hpp"
#include <SDL2/SDL.h>

Grid::Grid(SDL_Renderer *_pRenderer,
               int _width,
               int _height,
               int _width_pixel,
               int _height_pixel,
               SDL_Point _point_haut_gauche)
               :
               pRenderer(_pRenderer),
               width(_width),
               height(_height),
               width_pixel(_width_pixel),
               height_pixel(_height_pixel),
               point_haut_gauche(_point_haut_gauche) {
    for (int i = 0; i < this->height; i++) {
        std::vector<Diamond*> temp;
        for (int j = 0; j < this->width; j++) {
            temp.push_back(NULL);
        }
        this->tab.push_back(temp);
    }
}


Grid::~Grid() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (this->tab[i][j] != NULL) {
                delete this->tab[i][j];
                this->tab[i][j] = NULL;
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
    for(int i = 0; i <= height; i++) {
        y = this->point_haut_gauche.y + (this->height_pixel + taille_pixel_bords) * i - taille_pixel_bords;
        xdeb = this->point_haut_gauche.x - taille_pixel_bords;
        xfin = xdeb + (this->width_pixel + taille_pixel_bords) * width;
        for(int j = 0; j < taille_pixel_bords; j++) {
            SDL_RenderDrawLine(pRenderer, xdeb, y+j, xfin, y+j);
        }
    }
    for(int j = 0; j <= width; j++) {
        x = this->point_haut_gauche.x + (this->width_pixel + taille_pixel_bords) * j - taille_pixel_bords;
        ydeb = this->point_haut_gauche.y - taille_pixel_bords;
        yfin = ydeb + (this->height_pixel + taille_pixel_bords) * height;
        for(int i = 0; i < taille_pixel_bords; i++) {
            SDL_RenderDrawLine(pRenderer, x + i, ydeb, x + i, yfin);
        }
    }
    /* remplissage de la grille */
    for(int i = 0; i < height; i++) {
        y = this->point_haut_gauche.y + (this->height_pixel + taille_pixel_bords) * i;
        for(int j = 0; j < width; j++) {
            x = this->point_haut_gauche.x + (this->width_pixel + taille_pixel_bords) * j;
            if (this->tab[i][j] != NULL) {
                this->tab[i][j]->draw(x, y);
            }
        }
    }
}