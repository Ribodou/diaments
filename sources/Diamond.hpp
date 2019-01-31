#ifndef __DIAMOND_H__
#define __DIAMOND_H__

#include <vector>
#include <SDL2/SDL.h>


class Diamond {
	protected:
		//see couling's response at https://www.developerfusion.com/thread/49467/how-do-i-initialise-clean-up-static-variables
		SDL_Renderer *pRenderer;
		std::vector<SDL_Surface*> sprites;
		std::vector<SDL_Texture*> textures;
		int color;
		bool ombre;
/*
		class Initialiser {
			public:
				//Initialiser();
				~Initialiser();
		};
		friend class Initialiser;
		static Initialiser m_initialiser;
*/
	public:
		Diamond(SDL_Renderer *_pRenderer, int _color);
		~Diamond();

		int getColor();
		void draw(int x, int y);
		void assombrir();
		bool estUneOmbre();
};


#endif

