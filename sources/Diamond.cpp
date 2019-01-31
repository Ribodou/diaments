#include "Diamond.hpp"
#include <iostream>

#include "usefull_functions.hpp"



Diamond::Diamond(SDL_Renderer *_pRenderer, int _color) {
    this->pRenderer = _pRenderer;

    this->ombre = false;

    // this can be done in a loop, but I prefer to do it manually
    /* sprite 1 = bleu */
    SDL_Surface* spriteBleu = SDL_LoadBMP("./ressources/sprites/bleu2.bmp");
    verify<SDL_Surface>(spriteBleu);
    SDL_Texture* textureBleue;
    textureBleue = SDL_CreateTextureFromSurface(Diamond::pRenderer, spriteBleu);
    verify<SDL_Texture>(textureBleue);
    this->sprites.push_back(spriteBleu);
    this->textures.push_back(textureBleue);

    /* sprite 2 = rouge */
    SDL_Surface* spriteRouge = SDL_LoadBMP("./ressources/sprites/rouge.bmp");
    verify<SDL_Surface>(spriteRouge);
    SDL_Texture* textureRouge;
    textureRouge = SDL_CreateTextureFromSurface(Diamond::pRenderer, spriteRouge);
    verify<SDL_Texture>(textureRouge);
    this->sprites.push_back(spriteRouge);
    this->textures.push_back(textureRouge);

    this->color = _color;
}


Diamond::~Diamond() {
    for (uint i = 0; i < this->textures.size(); i++) {
        //std::cout << "Libération de la mémoire associée à la texture" << std::endl;
        //std::cout << this->textures.size() << std::endl;
        SDL_DestroyTexture(this->textures[i]);
    }
    for (uint i = 0; i < this->sprites.size(); i++) {
        //std::cout << "Libération de la ressource occupée par le sprite" << std::endl;
        SDL_FreeSurface(this->sprites[i]);
    }
}


int Diamond::getColor() {
    return this->color;
}


void Diamond::draw(int x, int y) {
    int indice = this->color - 1;
    if (indice >= 0) {
        SDL_Rect dest = {
            x,
            y,
            this->sprites[indice]->w,
            this->sprites[indice]->h,
        };
        // Copie du sprite grâce au SDL_Renderer
        SDL_RenderCopy(this->pRenderer, this->textures[indice], NULL, &dest);
    }
}


void Diamond::assombrir() {
    for (uint i = 0; i < this->textures.size(); i++) {
        SDL_SetTextureColorMod(this->textures[i], 64, 64, 64);
    }
    this->ombre = true;
}


bool Diamond::estUneOmbre() {
    return this->ombre;
}