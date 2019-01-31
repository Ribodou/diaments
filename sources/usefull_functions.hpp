#ifndef USEFULL_FUNCTIONS_HPP
#define USEFULL_FUNCTIONS_HPP

#include <iostream>
template <typename T>
void verify(T* t)
{
    if (not(t))
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(-1);
    }
}

#endif