#include "Diamond.hpp"
#include <iostream>

#include "usefull_functions.hpp"

Diamond::Diamond(SDL_Renderer *_pRenderer) {
    this->pRenderer = _pRenderer;

    this->ombre = false;

    // this can be done in a loop, but I prefer to do it manually => :-(
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

    /* sprite 3 = jaune */
    SDL_Surface* spriteJaune = SDL_LoadBMP("./ressources/sprites/jaune.bmp");
    verify<SDL_Surface>(spriteJaune);
    SDL_Texture* textureJaune;
    textureJaune = SDL_CreateTextureFromSurface(Diamond::pRenderer, spriteJaune);
    verify<SDL_Texture>(textureJaune);
    this->sprites.push_back(spriteJaune);
    this->textures.push_back(textureJaune);

    /* sprite 4 = orange */
    SDL_Surface* spriteOrange = SDL_LoadBMP("./ressources/sprites/orange.bmp");
    verify<SDL_Surface>(spriteOrange);
    SDL_Texture* textureOrange;
    textureOrange = SDL_CreateTextureFromSurface(Diamond::pRenderer, spriteOrange);
    verify<SDL_Texture>(textureOrange);
    this->sprites.push_back(spriteOrange);
    this->textures.push_back(textureOrange);

    /* sprite 4 = vert */
    SDL_Surface* spriteVert = SDL_LoadBMP("./ressources/sprites/vert.bmp");
    verify<SDL_Surface>(spriteVert);
    SDL_Texture* textureVert;
    textureVert = SDL_CreateTextureFromSurface(Diamond::pRenderer, spriteVert);
    verify<SDL_Texture>(textureVert);
    this->sprites.push_back(spriteVert);
    this->textures.push_back(textureVert);


    const unsigned long n = std::distance(this->sprites.begin(), this->sprites.end());
    const unsigned long divisor = RAND_MAX / n;

    unsigned int k;
    do {
        k = std::rand() / divisor;
    } while (k >= n);

    this->color = k + 1;
}


Diamond::Diamond(SDL_Renderer *_pRenderer, int color) : Diamond(_pRenderer) {
    this->color = color;
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