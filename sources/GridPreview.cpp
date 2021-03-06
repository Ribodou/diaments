#include "GridPreview.hpp"

GridPreview::GridPreview(SDL_Renderer *_pRenderer,
               int _width,
               int _height,
               int _width_pixel,
               int _height_pixel,
               SDL_Point _point_haut_gauche)
               :
               Grid(_pRenderer,
                    _width,
                    _height,
                    _width_pixel,
                    _height_pixel,
                    _point_haut_gauche)
               {
    this->coordonnees_piece = SDL_Point({
        0,
        0
    });
    this->piece = Piece::createAleatPiece(this->pRenderer);
}


GridPreview::~GridPreview() {
    if (this->piece != NULL) {
        delete this->piece;
        this->piece = NULL;
    }
}


void GridPreview::draw(int taille_pixel_bords) {
    Grid::draw(taille_pixel_bords);
    int xScreen, yScreen;
    SDL_Point point_haut_gauche_piece;
    xScreen = this->point_haut_gauche.x + (this->width_pixel + taille_pixel_bords) * this->coordonnees_piece.x;
    yScreen = this->point_haut_gauche.y + (this->height_pixel + taille_pixel_bords) * this->coordonnees_piece.y;

    point_haut_gauche_piece = SDL_Point({
        xScreen,
        yScreen
    });

    if (this->piece != NULL) {
        this->piece->draw(point_haut_gauche_piece,
                            this->width_pixel,
                            this->height_pixel,
                            taille_pixel_bords);
    }
}

bool GridPreview::deplacerPiece(int delatCaseX, int delatCaseY) {
    if (this->piece != NULL) {
        int x = this->coordonnees_piece.x + delatCaseX;
        int y = this->coordonnees_piece.y + delatCaseY;
        bool testX, testY;
        testX = ((0 <= x) && (x + this->piece->getLargeur() <= this->width));
        testY = ((0 <= y) && (y + this->piece->getHauteur() <= this->height));
        if (testX && testY) {
            this->coordonnees_piece.x = x;
            this->coordonnees_piece.y = y;
            return true;
        }
    }
    return false;
}


void GridPreview::retourner_piece() {
    if (this->piece != NULL) {
        int y_max_apres = this->coordonnees_piece.x + this->piece->getHauteur();
        // si on tourne sur nous-même autour d'un point (mettons celui en haut à gauche)
        // ce point ne prends pas plus de place
        y_max_apres -= 1;
        if (y_max_apres < this->width) {
            return this->piece->retourner();
        }
    }
}


void GridPreview::projeter_ombre(GridGame &grid_game) {
    int offset = this->coordonnees_piece.x;
    for (int ligne = this->piece->getHauteur() - 1; ligne >= 0; ligne--) {
        std::vector<Diamond*> envoi = this->piece->getLigneOmbre(ligne);
        grid_game.recevoir_ligne_ombre(offset, envoi);
    }
}


bool GridPreview::projeter_piece(GridGame &grid_game) {
    if (this->piece != NULL) {
        int offset = this->coordonnees_piece.x;
        bool success = true;
        for (int ligne = this->piece->getHauteur() - 1; ligne >= 0; ligne--) {
            std::vector<Diamond*> envoi = this->piece->getLigne(ligne);
            success = grid_game.recevoir_ligne_piece(offset, envoi);
            if (success == false) {
                return false;
            }
        }
        // let's create a new piece
        Piece::destroyPiece(this->piece);
        this->piece = Piece::createAleatPiece(this->pRenderer);
        return true;
    } else {  // no piece is found
        return false;
    }
}