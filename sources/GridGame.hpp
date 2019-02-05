#ifndef __GRIDGAME_H__
#define __GRIDGAME_H__

#include "Grid.hpp"
#include "Diamond.hpp"
#include "Piece.hpp"
#include "Score.hpp"

class GridGame : public Grid {
	protected:
        std::vector<std::vector<int>> not_verified;
	public:
		GridGame(SDL_Renderer *pRenderer,
                     int width,
                     int hauteur,
                     int width_pixel,
                     int hauteur_pixel,
                     SDL_Point point_haut_gauche);
		~GridGame();
		bool faire_tomber();
                bool exists(int x, int y);
                bool fixed(int i, int j);
                void recevoir_ligne_ombre(int offset, std::vector<Diamond*> ligne);
                bool recevoir_ligne_piece(int offset, std::vector<Diamond*> ligne);
                int getColor(int x, int y);
                std::vector<std::vector<int>> check(std::vector<int> couple, int nbMinAlignes, int horizontal, int vertical);
                std::vector<std::vector<int>> horizontal_check(std::vector<int> couple, int nbMinAlignes);
                std::vector<std::vector<int>> vertical_check(std::vector<int> couple, int nbMinAlignes);
                std::vector<std::vector<int>> diagonal_check0(std::vector<int> couple, int nbMinAlignes);
                std::vector<std::vector<int>> diagonal_check1(std::vector<int> couple, int nbMinAlignes);
                bool detruireAlignements(Score &score);
                void effacerOmbre();
};
#endif

