#ifndef _TEXTUREMANAGER_HPP_
#define _TEXTUREMANAGER_HPP_


#include "Game.hpp"

class TextureManager 
{
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);
    static void Draw(const std::string& textureId, const anoEngine::Rectangle& source, const anoEngine::Rectangle& destination, const anoEngine::Sprite::Flip& flip);
};

#endif
