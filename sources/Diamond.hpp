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
		bool shadow;
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
		/* Create a Diamond with a random color */
		Diamond(SDL_Renderer *_pRenderer);
		/* Create a Diamond with the color n° _color */
		Diamond(SDL_Renderer *_pRenderer, int _color);
		/* Destroy the Diamond and free everything inside it */
		~Diamond();

		/* Return the color used to create the Diamond */
		int getColor();
		/* Draw the Diamond on the pRender inside it */
		void draw(int x, int y);
		/* Darken the Diamond (ie: change its color) */
		void darken();
		/* Return true if and only if the Diamond is a shadow */
		bool isAShadow();
};


#endif

