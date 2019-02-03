#include "GridGame.hpp"
#include <SDL2/SDL.h>


GridGame::GridGame(SDL_Renderer *_pRenderer,
               int _largeur,
               int _hauteur,
               int _largeur_pixel,
               int _hauteur_pixel,
               SDL_Point _point_haut_gauche)
               :
               Grid(_pRenderer, _largeur, _hauteur, _largeur_pixel, _hauteur_pixel, _point_haut_gauche)
               {
    /*
    int temp [9][2] = {{1, 0}, {3, 5}, {4, 3}, {1, 4}, {3, 6}, {4, 8}, {1, 9}, {3, 1}, {4, 0}};
    for (int i = 0; i < 9; i++) {
        int y = temp[i][0];
        int x = temp[i][1];
        std::vector<int> coord;
        coord.push_back(y);
        coord.push_back(x);
        this->not_verified.push_back(coord);
        this->tab[y][x] = new Diamond(this->pRenderer, 1);
    }
    */
}


GridGame::~GridGame() {
    
}


bool GridGame::exists(int x, int y) {  //TODO : test
    if (x >= 0 && x < this->largeur && y >= 0 && y < this->hauteur) {
        if (this->tab[y][x] != NULL) {
            return true;
        }
    }
    return false;
}


bool GridGame::fixed(int x, int y) {  //TODO : test
    while (this->exists(x, y)) {
        y++;
    }
    if (y == (this->hauteur)) {
        return true;
    }
    return false;
}

//TODO: faire tomber par demi case
bool GridGame::faire_tomber() {
    // TODO: pourquoi 0
    bool tombe = false;
    for (int i = this->hauteur - 2; i >= 0; i--) {
        for (int j=0; j < this->largeur; j++) {
            if ((this->tab[i][j] != 0) && (this->tab[i+1][j] == 0)) {
                this->tab[i+1][j] = this->tab[i][j];
                this->tab[i][j] = 0;
                // std::cout << i << " " << j << " tombe en " << i+1 << " " << j << std::endl;
                if (this->fixed(j, i+1)) {
                    std::vector<int> temp;
                    temp.push_back(i+1);
                    temp.push_back(j);
                    this->not_verified.push_back(temp);
                }
                tombe = true;
            }
        }
    }
    return tombe;
}


void GridGame::recevoir_ligne_ombre(int offset, std::vector<Diamond*> ligneDiamant) {
    for (uint x = 0; x < ligneDiamant.size(); x++) {
        int ligneLibre = 0;
        bool fond = false;
        while (ligneLibre < this->hauteur && not(fond)) {
            if ((this->tab[ligneLibre][x + offset] != NULL) ){
                ligneLibre--;
                fond = true;
            } else if (ligneLibre == this->hauteur - 1) {
                fond = true;
            } else {
                //std::cout << ligneLibre<< "est pris" << std::endl;
                ligneLibre++;
            }
        }
        if (ligneLibre >= 0) {
            //std::cout << "place dans la grille trouvee " << ligneLibre << " " << x+offset << std::endl;
            this->tab[ligneLibre][x + offset] = ligneDiamant[x];
        }
    }
}


bool GridGame::recevoir_ligne_piece(int offset, std::vector<Diamond*> ligneDiamant) {
    for (uint x = 0; x < ligneDiamant.size(); x++) {
        int ligneLibre = 0;
        bool fond = false;
        while (ligneLibre < this->hauteur && not(fond)) {
            if ((this->tab[ligneLibre][x + offset] != NULL) ){
                ligneLibre--;
                fond = true;
            } else if (ligneLibre == this->hauteur - 1) {
                fond = true;
            } else {
                ligneLibre++;
            }
        }
        if (ligneLibre >= 0) {
            this->tab[ligneLibre][x + offset] = ligneDiamant[x];
            std::vector<int> couple;
            couple.push_back(ligneLibre);
            couple.push_back(x + offset);
            if (ligneDiamant[x] != NULL) {
                this->not_verified.push_back(couple);
            }
        } else {
            return false;
        }
    }
    return true;
}


int GridGame::getColor(int x, int y) {
    if (this->exists(x, y)) {
        return this->tab[y][x]->getColor();
    }
    return -1;
}


std::vector<std::vector<int>> GridGame::check(std::vector<int> couple,
                                              int nbMinAlignes,
                                              int horizontal,
                                              int vertical)
                                              {
    std::vector<std::vector<int> > aligneds;
    // because we will go from right to left
    std::vector<std::vector<int> > aligneds_reversed;
    int x = couple[1];
    int y = couple[0];
    int color = this->tab[y][x]->getColor();
    int nbAlignes = 1;
    bool left = true;
    bool continuer = true;
    int decalage = 1;

    while (continuer) {
        if (left) {
            int x_dec = x - decalage * horizontal;
            int y_dec = y - decalage * vertical;
            if (this->getColor(x_dec, y_dec) == color) {  // we are in the tab
                std::vector<int> continuus;
                continuus.push_back(y_dec);
                continuus.push_back(x_dec);
                aligneds_reversed.push_back(continuus);
                decalage++;
                nbAlignes++;
            } else {  // outside the tab or not the same color
                while(!aligneds_reversed.empty()) {
                    aligneds.push_back(aligneds_reversed.back());
                    aligneds_reversed.pop_back();
                }
                aligneds.push_back(couple);
                decalage = 1;
                left = false;  // let's go to the right way ;)
            }
        } else {  // right
            int x_dec = x + decalage * horizontal;
            int y_dec = y + decalage * vertical;
            if (this->getColor(x_dec, y_dec) == color) {  // we are in the tab
                std::vector<int> continuus;
                continuus.push_back(y_dec);
                continuus.push_back(x_dec);
                aligneds.push_back(continuus);
                decalage++;
                nbAlignes++;
            } else {
                continuer = false;
            }
        }
    }
    if (nbAlignes >= nbMinAlignes) {
        return aligneds;
    }
    while (!aligneds.empty()) {
        aligneds.pop_back();
    }
    return aligneds;
}



std::vector<std::vector<int>> GridGame::horizontal_check(std::vector<int> couple, int nbMinAlignes) {
    std::vector<std::vector<int>> retour = this->check(couple, nbMinAlignes, 1, 0);
    //std::cout << "Horizontal : " << retour.size() << std::endl;
    return retour;
}


std::vector<std::vector<int>> GridGame::vertical_check(std::vector<int> couple, int nbMinAlignes) {
    return this->check(couple, nbMinAlignes, 0, 1);
}


std::vector<std::vector<int>> GridGame::diagonal_check0(std::vector<int> couple, int nbMinAlignes) {
    return this->check(couple, nbMinAlignes, 1, 1);
}


std::vector<std::vector<int>> GridGame::diagonal_check1(std::vector<int> couple, int nbMinAlignes) {
    return this->check(couple, nbMinAlignes, 1, -1);
}


bool isInside(std::vector<std::vector<std::vector<int> > > container,
              std::vector<std::vector<int> > mayBeContained) {
    for(auto it = container.begin(); it != container.end(); it++) {
        //verify if two vectors are equals
        bool equal = true;
        std::vector<std::vector<int> > en_cours = (*it);
        if (en_cours.size() == mayBeContained.size()) {
            for (uint i = 0; i < en_cours.size(); i++) {
                equal &= (en_cours[i][1] == mayBeContained[i][1]);
                equal &= (en_cours[i][0] == mayBeContained[i][0]);
            }
            if (equal) {
                return equal;
            }
        }
    }
    return false;
}


void affiche(std::vector<std::vector<int> > vect) {
    for (uint i = 0; i < vect.size(); i++) {
        std::cout << "(" << vect[i][1] << "," << vect[i][0] << ")  ";
    }
    std::cout << std::endl;
}


bool GridGame::detruireAlignements(Score &score) {
    std::vector<std::vector<std::vector<int> > > aligneds;
    std::vector<std::vector<int> > temp_aligneds;
    bool alignementsDetruits = false;
    int nbMinAlignes = 3;
    // TODO : n'itérer que sur y = nbAlignes - 1; y < this->hauteur - (nbAlignes - 1); y++) (par exemple)
    for (uint i = 0; i < this->not_verified.size(); i++) {
        std::vector<int> couple = this->not_verified[i];
        // horizontal check
        temp_aligneds = this->horizontal_check(couple, nbMinAlignes);
        if (not(isInside(aligneds, temp_aligneds))) {
            score.add(temp_aligneds.size());
            aligneds.push_back(temp_aligneds);
        }

        // vertical check
        temp_aligneds = this->vertical_check(couple, nbMinAlignes);
        if (not(isInside(aligneds, temp_aligneds))) {
            score.add(temp_aligneds.size());
            aligneds.push_back(temp_aligneds);
        }

        // diagonal check
        temp_aligneds = this->diagonal_check0(couple, nbMinAlignes);
        if (not(isInside(aligneds, temp_aligneds))) {
            score.add(temp_aligneds.size());
            aligneds.push_back(temp_aligneds);
        }
        temp_aligneds = this->diagonal_check1(couple, nbMinAlignes);
        if (not(isInside(aligneds, temp_aligneds))) {
            score.add(temp_aligneds.size());
            aligneds.push_back(temp_aligneds);
        }
    }
    for(auto it = aligneds.begin(); it != aligneds.end(); it++) {
        for(auto itint = (*it).begin(); itint != (*it).end(); itint++) {
            std::vector<int> couple = *itint;
            int x = couple[1];
            int y = couple[0];
            if (this->tab[y][x] != NULL) {
                delete this->tab[y][x];
                this->tab[y][x] = NULL;
            }
            alignementsDetruits = true;
        }
    }
    while (!this->not_verified.empty()) {
        this->not_verified.pop_back();
    }
    return alignementsDetruits;
}


void GridGame::effacerOmbre() {
    for (int i = 0; i < this->hauteur; i++) {
        for (int j = 0; j < this->largeur; j++) {
            if (this->tab[i][j] != NULL) {
                if (this->tab[i][j]->isAShadow()) {
                    delete this->tab[i][j];
                    this->tab[i][j] = NULL;
                }
            }
        }
    }
}