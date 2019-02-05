#include "Score.hpp"

#include <SDL2/SDL.h>

Score::Score(SDL_Renderer *_pRenderer,
             SDL_Point _point_haut_gauche,
             int _largeur_pixel,
             int _height_pixel,
             int _score)
             :
             pRenderer(_pRenderer),
             point_haut_gauche(_point_haut_gauche),
             largeur_pixel(_largeur_pixel),
             height_pixel(_height_pixel),
             score(_score) {
    // do nothing
}

Score::~Score() {
    // do nothing
}

void Score::draw(int taille_pixel_bords) {
    TTF_Font* font = TTF_OpenFont("fonts/VeraMono.ttf", 14);
    std::string score_number = std::to_string(this->score);
    SDL_Color scoreColor = { 0, 0, 0, 0 };
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, score_number.c_str(), scoreColor);
    int score_width = scoreSurface->w;
    int score_height = scoreSurface->h;
    SDL_Rect rect_score = {this->point_haut_gauche.x + this->largeur_pixel - score_width - 2,
                           this->point_haut_gauche.y + this->height_pixel - score_height - 2,
                           score_width,
                           score_height};
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(this->pRenderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);
    
    

    SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    int x, y, xfin, yfin;
    for (int i = 0; i < taille_pixel_bords; i++) {
        x = this->point_haut_gauche.x - i -1;
        y = this->point_haut_gauche.y - i -1;
        xfin = x - i + this->largeur_pixel + i +1;
        yfin = y - i + this->height_pixel + i +1;
        SDL_RenderDrawLine(pRenderer, x, y, xfin, y);
        SDL_RenderDrawLine(pRenderer, xfin, y, xfin, yfin);
        SDL_RenderDrawLine(pRenderer, xfin, yfin, x, yfin);
        SDL_RenderDrawLine(pRenderer, x, yfin, x, y);
    }
    SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    std::string score_text = "Score";
    SDL_Color textColor = { 0, 0, 0, 0 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
    int text_width = textSurface->w;
    int text_height = textSurface->h;



    SDL_Rect rect_text = {this->point_haut_gauche.x - 5,
                          this->point_haut_gauche.y - 10,
                          text_width,
                          text_height};
    
    SDL_Rect rect = {rect_text.x - 10,
                     rect_text.y - 10,
                     rect_text.w + 15,
                     rect_text.h + 10};


    /*
    SDL_Surface *background = SDL_CreateRGBSurface(0, text_width, text_height, 32, 0, 0, 0, 0);
    SDL_FillRect(background, &rect, SDL_MapRGB(background->format, 255, 0, 0));
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(this->pRenderer, background);
    SDL_RenderCopy(this->pRenderer, backgroundTexture, NULL, &rect);*/
    SDL_RenderFillRect(this->pRenderer, &rect );

    SDL_Texture* text = SDL_CreateTextureFromSurface(this->pRenderer, textSurface);
    SDL_FreeSurface(textSurface);
    
    //SDL_FreeSurface(background);
    SDL_RenderCopy(this->pRenderer, text, NULL, &rect_text);
    SDL_RenderCopy(this->pRenderer, scoreTexture, NULL, &rect_score);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(scoreTexture);
}


void Score::add(int x) {
    this->score += x;
}