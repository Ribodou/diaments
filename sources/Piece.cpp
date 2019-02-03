#include "Piece.hpp"


Piece::Piece(SDL_Renderer *_pRenderer,
             std::string _forme)
             :
             pRenderer(_pRenderer),
             forme(_forme) {
    if (this->forme.compare("L") == 0) {
        this->hauteur = 4;
        this->largeur = 2;
        for (int i = 0; i < this->hauteur; i++) {
            std::vector<Diamond*> temp;
            for (int j = 0; j < this->largeur; j++) {
                temp.push_back(NULL);
            }
            this->tab.push_back(temp);
        }
        this->tab[0][0] = new Diamond(this->pRenderer);
        this->tab[1][0] = new Diamond(this->pRenderer);
        this->tab[2][0] = new Diamond(this->pRenderer);
        this->tab[3][0] = new Diamond(this->pRenderer);
        this->tab[3][1] = new Diamond(this->pRenderer);
    } else if (this->forme.compare("T") == 0) {
        this->hauteur = 4;
        this->largeur = 3;
        for (int i = 0; i < this->hauteur; i++) {
            std::vector<Diamond*> temp;
            for (int j = 0; j < this->largeur; j++) {
                temp.push_back(NULL);
            }
            this->tab.push_back(temp);
        }
        this->tab[0][0] = new Diamond(this->pRenderer);
        this->tab[0][1] = new Diamond(this->pRenderer);
        this->tab[0][2] = new Diamond(this->pRenderer);
        this->tab[1][1] = new Diamond(this->pRenderer);
        this->tab[2][1] = new Diamond(this->pRenderer);
    } else if (this->forme.compare("Z") == 0) {
        this->hauteur = 2;
        this->largeur = 3;
        for (int i = 0; i < this->hauteur; i++) {
            std::vector<Diamond*> temp;
            for (int j = 0; j < this->largeur; j++) {
                temp.push_back(NULL);
            }
            this->tab.push_back(temp);
        }
        this->tab[0][0] = new Diamond(this->pRenderer);
        this->tab[0][1] = new Diamond(this->pRenderer);
        this->tab[1][1] = new Diamond(this->pRenderer);
        this->tab[1][2] = new Diamond(this->pRenderer);
    } else {
        exit(2);
    }
}



Piece *Piece::createAleatPiece(SDL_Renderer *_pRenderer) {
    std::vector<std::string> shapes = {"L", "T", "Z"};
    const unsigned long n = std::distance(shapes.begin(), shapes.end());
    const unsigned long divisor = RAND_MAX / n;

    unsigned int k;
    do {
        k = std::rand() / divisor;
    } while (k >= n);

    std::string choice = shapes[k];
    return new Piece(_pRenderer, choice);
}


void Piece::destroyPiece(Piece *&piece) {
    delete piece;
}


Piece::~Piece() {
    for (int i = 0; i < this->hauteur; i++) {
        for (int j = 0; j < this->largeur; j++) {
            if (this->tab[i][j] != NULL) {
                delete this->tab[i][j];
            }
        }
    }
}


int Piece::getHauteur() {
    return this->hauteur;
}


int Piece::getLargeur() {
    return this->largeur;
}


void Piece::dessiner(SDL_Point point_haut_gauche_piece,
                     int largeur_pixel,
                     int hauteur_pixel,
                     int taille_pixel_bords) {
    int x, y;
    for (int i = 0; i < this->hauteur; i++) {
        y = point_haut_gauche_piece.y + (hauteur_pixel + taille_pixel_bords) * i;
        for (int j = 0; j < largeur; j++) {
            x = point_haut_gauche_piece.x + (largeur_pixel + taille_pixel_bords) * j;
            if (this->tab[i][j] != NULL) {
                this->tab[i][j]->draw(x, y);
            }
        }
    }
}


void Piece::retourner() {
    std::vector<std::vector<Diamond*> > temp_tab = this->tab;
    int hauteur_ancienne = this->hauteur;
    int largeur_ancienne = this->largeur;
    this->hauteur = largeur_ancienne;
    this->largeur = hauteur_ancienne;
    while (!this->tab.empty()) {
        this->tab.pop_back();
    }

    for (int j = 0; j < largeur_ancienne; j++) {
        std::vector<Diamond*> ligne;
        for (int i = 0; i < hauteur_ancienne; i++) {
            ligne.push_back(temp_tab[i][this->hauteur - j - 1]);
        }
        this->tab.push_back(ligne);
    }
}


std::vector<Diamond*> Piece::getLigneOmbre(int ligne) {
    std::vector<Diamond*> retour;
    Diamond *d = NULL;
    for (uint i = 0; i < this->tab[ligne].size(); i++) {
        if (this->tab[ligne][i] != NULL) {
            int couleur = this->tab[ligne][i]->getColor();
            d = new Diamond(this->pRenderer, couleur);
            d->darken();
        } else {
            d = NULL;
        }
        retour.push_back(d);
    }
    return retour;
}


std::vector<Diamond*> Piece::getLigne(int ligne) {
    std::vector<Diamond*> retour;
    Diamond *d = NULL;
    for (uint i = 0; i < this->tab[ligne].size(); i++) {
        if (this->tab[ligne][i] != NULL) {
            int couleur = this->tab[ligne][i]->getColor();
            d = new Diamond(this->pRenderer, couleur);
        } else {
            d = NULL;
        }
        retour.push_back(d);
    }
    return retour;
}